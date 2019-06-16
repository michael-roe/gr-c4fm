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
#include "whiten_ff_impl.h"

namespace gr {
  namespace c4fm {

    whiten_ff::sptr
    whiten_ff::make(int length)
    {
      return gnuradio::get_initial_sptr
        (new whiten_ff_impl(length));
    }

    /*
     * The private constructor
     */
    whiten_ff_impl::whiten_ff_impl(int length)
      : gr::sync_block("whiten_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      d_length = length;
      d_todo = length;
      d_state = 0x1c9;
    }

    /*
     * Our virtual destructor.
     */
    whiten_ff_impl::~whiten_ff_impl()
    {
    }

    int
    whiten_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      int i;
      int fb;

      for (i=0; i<noutput_items; i++)
      {
        if (d_state & 0x1)
          out[i] = -in[i];
	else
          out[i] = in[i];
	fb = ((d_state >> 4) ^ d_state) & 0x1;
	d_state = d_state >> 1;
	if (fb)
          d_state ^= 1 << 8;
	d_todo--;
	if (d_todo == 0)
        {
          d_todo = d_length;
	  d_state = 0x1c9;
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

