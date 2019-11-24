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
    crc16_encode_bb::make(const std::string &length_tag)
    {
      return gnuradio::get_initial_sptr
        (new crc16_encode_bb_impl(length_tag));
    }


    /*
     * The private constructor
     */
    crc16_encode_bb_impl::crc16_encode_bb_impl(const std::string &length_tag)
      : gr::block("crc16_encode_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      set_tag_propagation_policy(TPP_DONT);
      d_length_tag = pmt::intern(length_tag.c_str());
      d_offset = 0;
      d_data_todo = 0;
      d_crc_todo = 0;
    }

    /*
     * Our virtual destructor.
     */
    crc16_encode_bb_impl::~crc16_encode_bb_impl()
    {
    }

    static int predict(int noutput_items)
    {
      if (noutput_items > 16)
        return noutput_items - 16;
      else
        return 1;
    }

    void
    crc16_encode_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = predict(noutput_items);
    }

    int
    crc16_encode_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      std::vector<tag_t> tags;
      unsigned int feedback;
      int consumed;
      int produced;
      int available;
      int i;
      int tag_index;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items);

      tag_index = 0;
      consumed = 0;
      produced = 0;
      available = predict(noutput_items);
      while ((produced < noutput_items) &&
        ((consumed < available) || (d_crc_todo > 0)))
      {
	if (d_data_todo > 0)
        {
	  out[produced] = in[consumed];
	  feedback = in[consumed] ^ (d_crc >> 15);
	  while ((tag_index < tags.size()) &&
	    (tags[tag_index].offset == nitems_read(0) + consumed))
          {
            /* Discard length tags that are not at the start of a packet */
	    if (!pmt::equal(d_length_tag, tags[tag_index].key))
	    {
              add_item_tag(0, d_offset + produced, tags[tag_index].key,
                tags[tag_index].value);
	    }
            tag_index++;
          }
	  produced++;
	  consumed++;
	  d_crc = (d_crc << 1) & 0xffff;
	  if (feedback)
            d_crc ^= 1 | (1 << 5) | (1 << 12);
	  d_data_todo--;
	  if (d_data_todo == 0)
	  {
            d_crc_todo = 16;
	  }
	}
	else if (d_crc_todo > 0)
        {
          out[produced] = ((d_crc >> 15) & 0x1) ^ 0x1;
	  produced++;
	  d_crc = (d_crc << 1) & 0xffff;
	  d_crc_todo--;
	}
	else
	{
	  d_data_todo = 0;
	  d_crc = 0;
	  out[produced] = in[consumed];
	  feedback = in[consumed] ^ (d_crc >> 15);
	  while ((tag_index < tags.size()) &&
	    (tags[tag_index].offset == nitems_read(0) + consumed))
          {
	    if (pmt::equal(d_length_tag, tags[tag_index].key))
	    {
	      d_data_todo = pmt::to_long(tags[tag_index].value);
	      add_item_tag(0, d_offset + produced, tags[tag_index].key,
	        pmt::from_long(pmt::to_long(tags[tag_index].value) + 16));
	    }
	    else
	    {
              add_item_tag(0, d_offset + produced, tags[tag_index].key,
                tags[tag_index].value);
	    }
            tag_index++;
          }
	  if (d_data_todo == 0)
	  {
	    fprintf(stderr, "crc16_encode_bb: didn't find a length tag\n");
	  }
	  produced++;
	  consumed++;
	  d_crc = (d_crc << 1) & 0xffff;
          if (feedback)
            d_crc ^= 1 | (1 << 5) | (1 << 12);
	  d_data_todo--;
	  /* Should we handle the length = 1 case? */
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

