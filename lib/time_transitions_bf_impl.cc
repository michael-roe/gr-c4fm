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
#include "time_transitions_bf_impl.h"

namespace gr {
  namespace c4fm {

    time_transitions_bf::sptr
    time_transitions_bf::make()
    {
      return gnuradio::get_initial_sptr
        (new time_transitions_bf_impl());
    }


    /*
     * The private constructor
     */
    time_transitions_bf_impl::time_transitions_bf_impl()
      : gr::block("time_transitions_bf",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      d_last = -1;
      d_count = 0;
      d_bits = 0;
    }

    /*
     * Our virtual destructor.
     */
    time_transitions_bf_impl::~time_transitions_bf_impl()
    {
    }

    void
    time_transitions_bf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    time_transitions_bf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      float *out = (float *) output_items[0];
      int i;
      int produced = 0;

      for (i=0; i<noutput_items; i++)
      {
        if (in[i] == d_last)
        {
	  d_count++;
	  if (((float) d_count)*1200.0/44100.0 - d_bits > 0.5)
          {
	    out[produced] = 2.0*((float) in[i]) - 1.0;
	    produced++;
	    d_bits++;
	  }
	}
	else
	{
	  d_last = in[i];
	  d_count = 1;
	  d_bits = 0;
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

