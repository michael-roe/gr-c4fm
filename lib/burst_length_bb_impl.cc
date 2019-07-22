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
      d_max_zeros = max_zeros;
      d_burst = 0;
      d_zeros = 0;
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
	      fprintf(stderr, "burst length = %d\n", d_burst - d_max_zeros);
	      d_burst = 0;
	      d_zeros = 0;
	    }
	  }
	  else
          {
	    d_zeros = 0;
	  }
	}
	in++;
	out++;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

