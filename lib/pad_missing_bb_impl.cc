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
#include "pad_missing_bb_impl.h"

namespace gr {
  namespace c4fm {

    pad_missing_bb::sptr
    pad_missing_bb::make(int length, int subframes)
    {
      return gnuradio::get_initial_sptr
        (new pad_missing_bb_impl(length, subframes));
    }

    /*
     * The private constructor
     */
    pad_missing_bb_impl::pad_missing_bb_impl(int length, int subframes)
      : gr::block("pad_missing_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    
    {
      set_tag_propagation_policy(TPP_DONT);
      d_offset = 0;
      d_length = length;
      d_subframes = subframes;
      d_pad = 0;
      d_copy = 0;
      d_frame = -1;
      d_missed = 0;
    }

    /*
     * Our virtual destructor.
     */
    pad_missing_bb_impl::~pad_missing_bb_impl()
    {
    }

    void
    pad_missing_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    pad_missing_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      int produced = 0;
      int consumed = 0;
      int tag_index = 0;
      int tag_index2;
      int frame_number;
      std::vector<tag_t> tags;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+noutput_items); 

      while (produced < noutput_items)
      {
        if (d_pad > 0)
        {
	  if (d_pad == d_length)
          {
            add_item_tag(0, d_offset + produced, pmt::intern("frame_number"),
	      pmt::from_long(d_frame));
          }
	  if ((d_length - d_pad) % (d_length/d_subframes) == 0)
          {
	    add_item_tag(0, d_offset + produced, pmt::intern("deleted_frame"),
	      pmt::PMT_T);
          }
          *out = 0xff;
	  out++;
	  produced++;
	  d_pad--;
  	}
	else if (d_copy > 0)
	{
	  while ((tag_index < tags.size()) &&
	    (tags[tag_index].offset == nitems_read(0) + consumed))
	  {
	    add_item_tag(0, d_offset + produced, tags[tag_index].key,
	      tags[tag_index].value);
	    tag_index++;
	  }
	  *out = *in;
	  out++;
	  in++;
	  produced++;
	  consumed++;
	  d_copy--;
	}
	else
	{
	  tag_index2 = tag_index;
          while ((tag_index2 < tags.size()) &&
	    ! pmt::equal(pmt::intern("frame_number"), tags[tag_index2].key))
	  {
	    tag_index2++;
	  }
	  if (tag_index2 >= tags.size())
	  {
	    fprintf(stderr, "pad_missing_bb: tag not found\n");
	  }
	  else
	  {
	    /* fprintf(stderr, "FN = %d\n", pmt::to_long(tags[tag_index2].value)); */
	    frame_number = pmt::to_long(tags[tag_index2].value);
	    if ((d_frame >= 0) && (frame_number != ((d_frame + 1) & 0x7)))
	    {
	      d_missed++;
	      /* fprintf(stderr, "Missing frame! (%d missed)\n", d_missed); */
	      d_pad = d_length;
	      d_frame = (d_frame + 1) & 0x7;
	    }
	    else
            {
	      d_copy = d_length;
	      d_frame = frame_number;
	    }
	  }
        }
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (consumed);

      d_offset += noutput_items;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

