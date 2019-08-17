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

#include <cstring>
#include <string>
#include <gnuradio/io_signature.h>
#include "discard_parity_errors_bb_impl.h"

namespace gr {
  namespace c4fm {

    discard_parity_errors_bb::sptr
    discard_parity_errors_bb::make(int blocksize, const std::string &key)
    {
      return gnuradio::get_initial_sptr
        (new discard_parity_errors_bb_impl(blocksize, key));
    }

    /*
     * The private constructor
     */
    discard_parity_errors_bb_impl::discard_parity_errors_bb_impl(int blocksize, const std::string &key)
      : gr::block("discard_parity_errors_bb",
              gr::io_signature::make(1, 2, sizeof(char)),
              gr::io_signature::make(1, 2, sizeof(char)))
    {
      d_blocksize = blocksize;
      set_output_multiple(d_blocksize);
      set_tag_propagation_policy(TPP_DONT);
      d_tag_key = pmt::intern(key.c_str());
    }

    /*
     * Our virtual destructor.
     */
    discard_parity_errors_bb_impl::~discard_parity_errors_bb_impl()
    {
    }

    void
    discard_parity_errors_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    discard_parity_errors_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      const char *in1 = (const char *) input_items[1];
      char *out1 = (char *) output_items[1];
      int i;
      int next_tag;
      int produced; 
      int skipped;
      std::vector<tag_t> tags;

      produced = 0;
      skipped = 0;
      next_tag = 0;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+noutput_items);
      while ((next_tag < tags.size()) && ! pmt::equal(d_tag_key, tags[next_tag].key))
      {
        /* fprintf(stderr, "Discarding tag\n"); */
	next_tag++;
      }
      for (i=0; i<noutput_items/d_blocksize; i++)
      {
	if (next_tag >= tags.size())
        {
          /* fprintf(stderr, "Copying block %d, no tags left\n", i); */
	  memcpy(out, in, d_blocksize);
	  memcpy(out1, in1, d_blocksize);
	  out += d_blocksize;
	  in += d_blocksize;
	  out1 += d_blocksize;
	  in1 += d_blocksize;
	  produced += d_blocksize;
	}
	else if (tags[next_tag].offset - nitems_read(0) > d_blocksize*i + d_blocksize - 1)
        {
          /* fprintf(stderr, "Should copy block %d\n", i); */
	  memcpy(out, in, d_blocksize);
	  memcpy(out1, in1, d_blocksize);
	  out += d_blocksize;
	  in += d_blocksize;
	  out1 += d_blocksize;
	  in1 += d_blocksize;
	  produced += d_blocksize;
        }
	else
        {
          /* fprintf(stderr, "Skipping block %d\n", i); */
	  in += d_blocksize;
	  in1 += d_blocksize;
	  skipped += d_blocksize;
	  /* fprintf(stderr, "Relative to start of block = %lld\n", tags[next_tag].offset - nitems_read(0) - d_blocksize*i); */
	  /* Should fix up the offsets of tags */
	  next_tag++;
	  while ((next_tag < tags.size()) && (!pmt::equal(d_tag_key, tags[next_tag].key)) && (!pmt::equal(pmt::PMT_T, tags[next_tag].value)))
          {
	    /* Ought to skip the tag if its in the current block */
            /* fprintf(stderr, "skipping irrelevant tag\n"); */
	    next_tag++;
	  }
	}
      }
      memcpy(out, in, noutput_items);

      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return produced;
    }

  } /* namespace c4fm */
} /* namespace gr */

