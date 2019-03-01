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
#include "golay_decoder_bb_impl.h"

namespace gr {
  namespace c4fm {

    golay_decoder_bb::sptr
    golay_decoder_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new golay_decoder_bb_impl());
    }

    /*
     * The private constructor
     */
    golay_decoder_bb_impl::golay_decoder_bb_impl()
      : gr::sync_decimator("golay_decoder_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), 2)
    {
      set_output_multiple(12);
      d_block_len_pmt = pmt::from_long(12);
      d_parity_error_key = pmt::string_to_symbol("parity_error");
      d_offset = 0;
    }

    /*
     * Our virtual destructor.
     */
    golay_decoder_bb_impl::~golay_decoder_bb_impl()
    {
    }

    int
    golay_decoder_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      int i;
      int j;
      int parity;

      for (i=0; i<noutput_items/12; i++)
      {
	parity = 0;
        for (j=0; j<12; j++)
        {
	  parity ^= in[24*i+j] & 0x1;
          out[12*i+j] = in[24*i+j];
	}
	for (j=12; j<24; j++)
	{
          parity ^= in[24*i+j] & 0x1;
	}
	if (parity)
        {
          add_item_tag(0, d_offset+i*12, d_parity_error_key, d_block_len_pmt);
        }
      }

      d_offset += noutput_items;
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

