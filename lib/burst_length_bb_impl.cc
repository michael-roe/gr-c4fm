/* -*- c++ -*- */
/* 
 * Copyright 2019 Michael Roe.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "burst_length_bb_impl.h"

namespace gr {
  namespace c4fm {

    burst_length_bb::sptr
    burst_length_bb::make(int max_zeros)
    {
      return gnuradio::get_initial_sptr
        (new burst_length_bb_impl(max_zeros));
    }

    /*
     * The private constructor
     */
    burst_length_bb_impl::burst_length_bb_impl(int max_zeros)
      : gr::sync_block("burst_length_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      d_offset = 0;
      d_max_zeros = max_zeros;
      d_burst = 0;
      d_zeros = 0;
      d_error_count = 0;
      d_burst_count = 0;
      d_squared_burst_weights = 0;
    }

    /*
     * Our virtual destructor.
     */
    burst_length_bb_impl::~burst_length_bb_impl()
    {
    }

    int
    burst_length_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      int i;

      for (i=0; i<noutput_items; i++)
      {
        *out = *in;
	if (d_burst == 0)
        {
          if (*in)
	  {
	    d_burst = 1;
	    d_zeros = 0;
	    d_ones = 1;
	    d_burst_count++;
            d_error_count++;
	  }
	}
        else
	{
	  d_burst++;
	  if (*in == 0)
	  {
	    d_zeros++;
	    if (d_zeros == d_max_zeros)
	    {
	      /* fprintf(stderr, "burst length = %d\n", d_burst - d_max_zeros); */
	      /* fprintf(stderr, "burst weight = %d\n", d_ones); */
	      add_item_tag(0, d_offset + i, pmt::intern("burst_weight"),
	        pmt::from_long(d_ones));
	      d_squared_burst_weights += d_ones*d_ones;
	      add_item_tag(0, d_offset + i, pmt::intern("mean_burst_weight"),
	        pmt::from_float(((double) d_error_count)/((double) d_burst_count)));
	      /* fprintf(stderr, "mean burst weight = %lf\n",
                ((double) d_error_count)/((double) d_burst_count)); */
	      /* fprintf(stderr, "mean squared burst weight = %lf\n",
	        ((double) d_squared_burst_weights)/((double) d_burst_count)); */
	      add_item_tag(0, d_offset + i, pmt::intern("mean_squared_burst_weight"),
	        pmt::from_float(((double) d_squared_burst_weights)/((double) d_burst_count)));
	      /* fprintf(stderr, "population standard deviation of weights = %lf\n",
                sqrt(((double) d_burst_count*d_squared_burst_weights - d_error_count*d_error_count))/((double) d_burst_count)); */
	      d_burst = 0;
	      d_zeros = 0;
	    }
	  }
	  else
          {
	    d_zeros = 0;
	    d_ones++;
	    d_error_count++;
	  }
	}
	in++;
	out++;
      }

      d_offset += noutput_items;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

