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
#include "dupe_skipped_cc_impl.h"

namespace gr {
  namespace c4fm {

    dupe_skipped_cc::sptr
    dupe_skipped_cc::make()
    {
      return gnuradio::get_initial_sptr
        (new dupe_skipped_cc_impl());
    }

    /*
     * The private constructor
     */
    dupe_skipped_cc_impl::dupe_skipped_cc_impl()
      : gr::block("dupe_skipped_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      set_history(21);
      set_tag_propagation_policy(TPP_DONT);
      d_tag_key = pmt::intern("skip");
    }

    /*
     * Our virtual destructor.
     */
    dupe_skipped_cc_impl::~dupe_skipped_cc_impl()
    {
    }

    void
    dupe_skipped_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items + 21;
    }

    int
    dupe_skipped_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int i;
      int tag_index;
      long skip;
      int produced = 0;
      int consumed = 0;
      int next_skip;
      std::vector<tag_t> tags;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+noutput_items);

        while ((tag_index < tags.size()) &&
	  (! pmt::equal(d_tag_key, tags[tag_index].key) ||
	  pmt::to_long(tags[tag_index].value) != -1))
        {
          tag_index++;
        }

        if (tag_index < tags.size())
        {
          fprintf(stderr, "Found a skip -1 tag, offset = %ld\n",
	    tags[tag_index].offset - nitems_read(0));
	  next_skip = tags[tag_index].offset - nitems_read(0);
        }
	else
        {
	  next_skip = -1;
	}

      while (produced < noutput_items)
      {
        if ((next_skip < 0) || (consumed < next_skip))
	{
          out[produced] = in[consumed];
	  produced++;
	  consumed++;
	}
	else if (produced < noutput_items - 1)
	{
	  out[produced] = gr_complex(0.0,0.0);
	  produced++;
	  out[produced] = in[consumed];
	  consumed++;
          produced++;
	  /* fprintf(stderr, "Duplicating a bit\n"); */
	  tag_index++;
	  while ((tag_index < tags.size()) &&
            (! pmt::equal(d_tag_key, tags[tag_index].key) ||
            pmt::to_long(tags[tag_index].value) != -1))
          {
            tag_index++;
          }

          if (tag_index < tags.size())
          {
		  /*
            fprintf(stderr, "Found a skip -1 tag, offset = %ld\n",
              tags[tag_index].offset - nitems_read(0));
	      */
            next_skip = tags[tag_index].offset - nitems_read(0);
          }
          else
          {
            next_skip = -1;
          }
	}
	else
	{
	  produced++;
	}
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (consumed);

      // Tell runtime system how many output items we produced.
      return produced;
    }

  } /* namespace c4fm */
} /* namespace gr */

