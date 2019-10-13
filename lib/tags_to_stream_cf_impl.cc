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
#include "tags_to_stream_cf_impl.h"

namespace gr {
  namespace c4fm {

    tags_to_stream_cf::sptr
    tags_to_stream_cf::make(const std::string &key, int samples)
    {
      return gnuradio::get_initial_sptr
        (new tags_to_stream_cf_impl(key, samples));
    }

    /*
     * The private constructor
     */
    tags_to_stream_cf_impl::tags_to_stream_cf_impl(const std::string &key, int samples)
      : gr::block("tags_to_stream_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      d_samples = samples;
      d_tag_key = pmt::intern(key.c_str());
    }


    /*
     * Our virtual destructor.
     */
    tags_to_stream_cf_impl::~tags_to_stream_cf_impl()
    {
    }

    void
    tags_to_stream_cf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items*d_samples;
    }

    int
    tags_to_stream_cf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      std::vector<tag_t> tags;
      int i;
      int produced;

      produced = 0;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+noutput_items*d_samples);

      for (i=0; i<tags.size(); i++)
      {
        if (pmt::equal(tags[i].key, d_tag_key))
	{
          out[produced] = pmt::to_float(tags[i].value);
	  produced++;
	  if (produced == noutput_items)
            break;
	 }
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items*d_samples);

      // Tell runtime system how many output items we produced.
      return produced;
    }
  } /* namespace c4fm */
} /* namespace gr */

