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
#include "sign_scrambler_ff_impl.h"

namespace gr {
  namespace c4fm {

    sign_scrambler_ff::sptr
    sign_scrambler_ff::make(int mask, int seed, int len, int count)
    {
      return gnuradio::get_initial_sptr
        (new sign_scrambler_ff_impl(mask, seed, len, count));
    }


    /*
     * The private constructor
     */
    sign_scrambler_ff_impl::sign_scrambler_ff_impl(int mask, int seed, int len, int count)
      : gr::sync_block("sign_scrambler_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
	d_lfsr(mask, seed, len)
    {
      d_count = count;
      d_counter = 0;
    }

    /*
     * Our virtual destructor.
     */
    sign_scrambler_ff_impl::~sign_scrambler_ff_impl()
    {
    }

    int
    sign_scrambler_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      int i;

      for (i=0; i<noutput_items; i++)
      {
	if (d_lfsr.next_bit())
	{
	  out[i] = -in[i];
	}
	else
	{
	  out[i] = in[i];
        }
	d_counter++;
	if (d_counter == d_count)
	{
	  d_lfsr.reset();
	  d_counter = 0;
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

