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
#include "crc16_bb_impl.h"

namespace gr {
  namespace c4fm {

    crc16_bb::sptr
    crc16_bb::make(int check)
    {
      return gnuradio::get_initial_sptr
        (new crc16_bb_impl(check));
    }

    /*
     * The private constructor
     */
    crc16_bb_impl::crc16_bb_impl(int check)
      : gr::block("crc16_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      set_output_multiple(32);
      d_offset = 0;
      d_crc_error_key = pmt::string_to_symbol("crc_error");
    }

    /*
     * Our virtual destructor.
     */
    crc16_bb_impl::~crc16_bb_impl()
    {
    }

    void
    crc16_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items/32)*48;
    }

    int
    crc16_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      int blocks;
      int i;
      int j;
      unsigned int feedback;
      unsigned int crc;

      blocks = noutput_items/32;

      for (i=0; i<blocks; i++)
      {
	crc = 0;
        for (j=0; j<32; j++)
        {
          out[i*32+j] = in[i*48+j];
	  feedback = in[i*48+j] ^ (crc >> 15);
	  crc = (crc << 1) & 0xffff;
	  if (feedback)
	    crc ^= 1 | (1 << 5) | (1 << 12);
	}
	for (j=32; j<48; j++)
        {
          feedback = in[i*48+j] ^ (crc >> 15) ^ 0x1;
	  crc = (crc << 1) & 0xffff;
	  if (feedback)
            crc ^= 1 | (1 << 5) | (1 << 12);
	}
        if (crc != 0)
          add_item_tag(0, d_offset+i*32, d_crc_error_key, pmt::PMT_T);
	else
          add_item_tag(0, d_offset+i*32, d_crc_error_key, pmt::PMT_F);
      }


      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (blocks*48);

      d_offset += noutput_items;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

