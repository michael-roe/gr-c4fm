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
#include "frame_sync_bb_impl.h"

namespace gr {
  namespace c4fm {

    frame_sync_bb::sptr
    frame_sync_bb::make(int frame_size, int sync_size, int bps, unsigned long long sync)
    {
      return gnuradio::get_initial_sptr
        (new frame_sync_bb_impl(frame_size, sync_size, bps, sync));
    }

    /*
     * The private constructor
     */
    frame_sync_bb_impl::frame_sync_bb_impl(int frame_size, int sync_size, int bps, unsigned long long sync)
      : gr::block("frame_sync_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      d_frame_size = frame_size;
      d_sync_size = sync_size;
      d_sync = sync;
      d_bps = bps;
      d_word = 0;
      d_todo = 0;
      d_mask = (1ULL << (sync_size*bps)) - 1;
      d_symbol_mask = (1 << bps) - 1;
    }

    /*
     * Our virtual destructor.
     */
    frame_sync_bb_impl::~frame_sync_bb_impl()
    {
    }

    void
    frame_sync_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    frame_sync_bb_impl::general_work (int noutput_items,
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
	if (d_todo > d_sync_size)
        {
	  *out = *in;
	  out++;
	  in++;
	  produced++;
	  d_todo--;
	}
        else if (d_todo > 0)
        {
          d_word = (d_word << d_bps) | (*in & d_symbol_mask);
	  *in++;
	  d_todo--;
        }
	else if ((d_word & d_mask) != d_sync)
        {
          /* fprintf(stderr, "Did not find sync word\n"); */
	  d_word = (d_word << d_bps) | (*in & d_symbol_mask);
	  /* fprintf(stderr, "word = %llx\n", d_word); */
	  *in++;
        }
	else
        {
          /* fprintf(stderr, "Found sync word\n"); */
	  *out = *in;
	  out++;
	  in++;
	  produced++;
	  d_todo = d_frame_size - 1;
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

