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
#include "crc16_decode_bb_impl.h"

namespace gr {
  namespace c4fm {

    crc16_decode_bb::sptr
    crc16_decode_bb::make(const std::string &length_tag, const std::string &error_tag, int default_length)
    {
      return gnuradio::get_initial_sptr
        (new crc16_decode_bb_impl(length_tag, error_tag, default_length));
    }


    /*
     * The private constructor
     */
    crc16_decode_bb_impl::crc16_decode_bb_impl(const std::string &length_tag, const std::string &error_tag, int default_length)
      : gr::block("crc16_decode_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      set_tag_propagation_policy(TPP_DONT);
      d_offset = 0;
      d_data_todo = 0;
      d_default_length = default_length;
      d_crc = 0;
    }

    /*
     * Our virtual destructor.
     */
    crc16_decode_bb_impl::~crc16_decode_bb_impl()
    {
    }

    void
    crc16_decode_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items + 16;
    }

    int
    crc16_decode_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      std::vector<tag_t> tags;
      unsigned int feedback;
      unsigned int mask;
      int produced;
      int consumed;
      int available;
      int i;
      int tag_index;


      available = noutput_items + 16;
      produced = 0;
      consumed = 0;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + available);
      tag_index = 0;

      while ((produced < noutput_items) && (consumed < available - 16))
      {
        if (d_data_todo > 1)
        {
	  out[produced] = in[consumed];
	  feedback = in[consumed] ^ (d_crc >> 15);
	  while ((tag_index < tags.size()) && 
	    (tags[tag_index].offset == nitems_read(0) + consumed))
          {
	    add_item_tag(0, d_offset + produced, tags[tag_index].key,
	      tags[tag_index].value);
	    tag_index++;
	  }
	  produced++;
	  consumed++;
	  d_crc = (d_crc << 1) & 0xffff;
          if (feedback)
            d_crc ^= 1 | (1 << 5) | (1 << 12);
	  d_data_todo--;
        }	
	else if (d_data_todo == 1)
	{
	  out[produced] = in[consumed];
	  feedback = in[consumed] ^ (d_crc >> 15);
	  while ((tag_index < tags.size()) &&
            (tags[tag_index].offset >= nitems_read(0) + consumed) &&
	    (tags[tag_index].offset < nitems_read(0) + consumed + 17))
          {
	    add_item_tag(0, d_offset + produced, tags[tag_index].key,
	      tags[tag_index].value);
            tag_index++;
          }
	  d_crc = (d_crc << 1) & 0xffff;
	  if (feedback)
            d_crc ^= 1 | (1 << 5) | (1 << 12);
	  mask = 0x8000;
	  for (i=1; i<17; i++)
          {
	    if (in[consumed + i])
	    {
	      d_crc ^= mask;
	    }
	    mask = mask >> 1;
	  }
	  /* fprintf(stderr, "recovered crc = %x\n", d_crc); */
	  if (d_crc != 0xffff)
	  {
	    /* fprintf(stderr, "CRC error\n"); */
	    add_item_tag(0, d_offset + produced, pmt::intern("crc_error"), pmt::PMT_T);
	  }
	  produced++;
	  consumed += 17;
	  d_data_todo--;
	}
	else if (d_data_todo == 0)
	{
	  d_data_todo = d_default_length - 16;
	  d_crc = 0;
	  out[produced] = in[consumed];
	  while ((tag_index < tags.size()) &&
            (tags[tag_index].offset >= nitems_read(0) + consumed) &&
	    (tags[tag_index].offset < nitems_read(0) + consumed + 17))
          {
	    add_item_tag(0, d_offset + produced, tags[tag_index].key,
	      tags[tag_index].value);
            tag_index++;
          }
	  d_crc = (d_crc << 1) & 0xffff;
	  feedback = in[consumed] ^ (d_crc >> 15);
          if (feedback)
            d_crc ^= 1 | (1 << 5) | (1 << 12);
          produced++;
	  consumed++;
	  d_data_todo--;
	  /* Should I handle the case where the length is 1? */
        }

      }

      d_offset += produced;

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (consumed);

      // Tell runtime system how many output items we produced.
      return produced;
    }

  } /* namespace c4fm */
} /* namespace gr */

