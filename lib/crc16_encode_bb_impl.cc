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
#include "crc16_encode_bb_impl.h"

namespace gr {
  namespace c4fm {

    crc16_encode_bb::sptr
    crc16_encode_bb::make(int length)
    {
      return gnuradio::get_initial_sptr
        (new crc16_encode_bb_impl(length));
    }

    /*
     * The private constructor
     */
    crc16_encode_bb_impl::crc16_encode_bb_impl(int length)
      : gr::block("crc16_encode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      set_output_multiple(length + 16);
      set_tag_propagation_policy(TPP_DONT);
      d_offset = 0;
      d_length = length;
    }

    /*
     * Our virtual destructor.
     */
    crc16_encode_bb_impl::~crc16_encode_bb_impl()
    {
    }

    void
    crc16_encode_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items/(d_length + 16))*d_length;
    }

    int
    crc16_encode_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      std::vector<tag_t> tags;
      unsigned long long block_num;
      int block_offset;
      int blocks;
      int feedback;
      unsigned int crc;
      int i;
      int j;
 
      blocks = noutput_items/(d_length + 16);

      for (i=0; i<blocks; i++)
      {
        crc = 0;
        for (j=0; j<d_length; j++)
        {
          out[i*(d_length + 16) + j] = in[i*d_length + j];
          feedback = in[i*d_length + j] ^ (crc >> 15);
          crc = (crc << 1) & 0xffff;
          if (feedback)
            crc ^= 1 | (1 << 5) | (1 << 12);
        }
	for (j=0; j<16; j++)
        {
	  out[i*(d_length + 16) + d_length + j] = ((crc >> 15) & 0x1) ^ 0x1;
	  crc = (crc << 1) & 0xffff;
	}
      }

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+blocks*d_length);
      for (i=0; i<tags.size(); i++)
      {
        block_num = tags[i].offset/d_length;
        block_offset = tags[i].offset - block_num*d_length;
        add_item_tag(0, (d_length + 16)*block_num+block_offset, tags[i].key,
	  tags[i].value);
      }
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (blocks*d_length);

      // Tell runtime system how many output items we produced.
      return blocks*(d_length + 16);
    }

  } /* namespace c4fm */
} /* namespace gr */

