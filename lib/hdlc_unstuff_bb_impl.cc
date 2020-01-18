/* -*- c++ -*- */
/*
 * Copyright 2020 Michael Roe.
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
#include "hdlc_unstuff_bb_impl.h"

namespace gr {
  namespace c4fm {

    hdlc_unstuff_bb::sptr
    hdlc_unstuff_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new hdlc_unstuff_bb_impl());
    }


    /*
     * The private constructor
     */
    hdlc_unstuff_bb_impl::hdlc_unstuff_bb_impl()
      : gr::block("hdlc_unstuff_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      d_ones = 0;
    }

    /*
     * Our virtual destructor.
     */
    hdlc_unstuff_bb_impl::~hdlc_unstuff_bb_impl()
    {
    }

    void
    hdlc_unstuff_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    hdlc_unstuff_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      int i;
      int produced;

      produced = 0;

      for (i=0; i<noutput_items; i++)
      {
        if (in[i])
        {
          out[produced] = in[i];
	  produced++;
	  d_ones++;
	}
	else if (d_ones == 5)
        {
	  d_ones = 0;
	}
	else
	{
	  out[produced] = in[i];
          produced++;
          d_ones = 0;
	}
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return produced;
    }

  } /* namespace c4fm */
} /* namespace gr */

