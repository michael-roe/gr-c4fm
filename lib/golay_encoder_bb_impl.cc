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
#include "golay_encoder_bb_impl.h"

namespace gr {
  namespace c4fm {

    golay_encoder_bb::sptr
    golay_encoder_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new golay_encoder_bb_impl());
    }

    /*
     * The private constructor
     */
    golay_encoder_bb_impl::golay_encoder_bb_impl()
      : gr::sync_interpolator("golay_encoder_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), 2)
    {
      set_output_multiple(24);
    }

    /*
     * Our virtual destructor.
     */
    golay_encoder_bb_impl::~golay_encoder_bb_impl()
    {
    }

    int
    golay_encoder_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      int i;
      int j;
      unsigned int s;
      unsigned int parity;
      unsigned int w1;

      w1 = 1 | (1 << 2) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 10) | (1 << 11);

      for (i = 0; i < noutput_items/24; i++)
      {
        s = 0;
        parity = 0;
        for (j=11; j>=0; j--)
        {
          parity ^= (in[12*i+j] & 1);
          s ^= (in[12*i+j] & 1);
          if (s & 1)
	  {
            s ^= w1;
	  }
          s = s >> 1;
	  out[24*i+j] = in[12*i+j];
        }
        for (j=10; j>=0; j--)
        {
          out[24*i+j+12] = s & 1;
          parity ^= out[24*i+j+12];
          s = s >> 1;
        }
        out[24*i+23] = parity;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

