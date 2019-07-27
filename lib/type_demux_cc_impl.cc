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
#include "type_demux_cc_impl.h"

namespace gr {
  namespace c4fm {

    type_demux_cc::sptr
    type_demux_cc::make(int frame_type, int data_type, int length)
    {
      return gnuradio::get_initial_sptr
        (new type_demux_cc_impl(frame_type, data_type, length));
    }

    /*
     * The private constructor
     */
    type_demux_cc_impl::type_demux_cc_impl(int frame_type, int data_type, int length)
      : gr::block("type_demux_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      set_tag_propagation_policy(TPP_DONT);
      d_length = length;
      d_frame_type = frame_type;
      d_data_type = data_type;
      d_skip = 0;
      d_copy = 0;
      d_offset = 0;
    }

    /*
     * Our virtual destructor.
     */
    type_demux_cc_impl::~type_demux_cc_impl()
    {
    }

    void
    type_demux_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    type_demux_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int i;
      int j;
      int produced;
      int consumed;
      int frame_type;
      int data_type;
      int next_tag;
      int tag_index;
      std::vector<tag_t> tags;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items);
      /* fprintf(stderr, "%ld tags found\n", tags.size()); */
      /* if (tags.size() > 0)
        fprintf(stderr, "offset to first tag = %ld\n", tags[0].offset - nitems_read(0)); */

      produced = 0;
      consumed = 0;
      next_tag = 0;

      for (i=0; i<noutput_items; i++)
      {
        if (d_skip > 0)
        {
          while ((next_tag < tags.size()) && (tags[next_tag].offset == nitems_read(0) + consumed))
          {
            /* fprintf(stderr, "skipping tag\n"); */
	    next_tag++;
          }
          in++;
	  consumed++;
	  d_skip--;
	}
	else if (d_copy > 0)
	{
	  *out = *in;
	  while ((next_tag < tags.size()) && (tags[next_tag].offset == nitems_read(0) + consumed))
	  {
	    /* fprintf(stderr, "copying tag\n"); */
	    add_item_tag(0, d_offset + produced, tags[next_tag].key, tags[next_tag].value);
	    next_tag++;
	  }
	  in++;
	  out++;
	  d_copy--;
	  consumed++;
	  produced++;
	}
	else
	{
	  frame_type = -1;
	  data_type = -1;
	  tag_index = next_tag;
	  while ((tag_index < tags.size()) && (tags[tag_index].offset == nitems_read(0) + consumed))
	  {
	    if (pmt::equal(pmt::intern("frame_type"), tags[tag_index].key))
	      frame_type = pmt::to_long(tags[tag_index].value);
	    else if (pmt::equal(pmt::intern("data_type"), tags[tag_index].key))
              data_type = pmt::to_long(tags[tag_index].value);
	    tag_index++;
	  }
	  /* fprintf(stderr, "frame_type = %d\n", frame_type); */
	  /* fprintf(stderr, "data_type = %d\n", data_type); */
	  if (frame_type < 0)
          {
	    fprintf(stderr, "frame_type tag not found.\n");
	  }
	  if (data_type < 0)
	  {
	    fprintf(stderr, "data_type tag not found.\n");
	  }
	  if ((frame_type == d_frame_type) && (data_type == d_data_type))
	  {
	    d_copy = d_length;
	    *out = *in;
	    while ((next_tag < tags.size()) && (tags[next_tag].offset == nitems_read(0) + consumed))
	    {
	      /* fprintf(stderr, "copying tag (start)\n"); */
	      add_item_tag(0, d_offset + produced, tags[next_tag].key, tags[next_tag].value);
	      next_tag++;
	    }
	    out++;
	    in++;
	    d_copy--;
	    consumed++;
	    produced++;
          }
	  else
	  {
	    d_skip = d_length;
	    while ((next_tag < tags.size()) && (tags[next_tag].offset == nitems_read(0) + consumed))
            {
              /* fprintf(stderr, "skipping tag (start)\n"); */
              next_tag++;
            }
	    in++;
	    d_skip--;
	    consumed++;
	  }
	}
      }

      d_offset += produced;

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return produced;
    }

  } /* namespace c4fm */
} /* namespace gr */

