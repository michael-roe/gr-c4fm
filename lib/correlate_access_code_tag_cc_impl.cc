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
#include "correlate_access_code_tag_cc_impl.h"

namespace gr {
  namespace c4fm {

    correlate_access_code_tag_cc::sptr
    correlate_access_code_tag_cc::make(int sync_len, unsigned long long sync, int length, double threshold, double threshold2)
    {
      return gnuradio::get_initial_sptr
        (new correlate_access_code_tag_cc_impl(sync_len, sync, length, threshold, threshold2));
    }

    /*
     * The private constructor
     */
    correlate_access_code_tag_cc_impl::correlate_access_code_tag_cc_impl(int sync_len, unsigned long long sync, int length, double threshold, double threshold2)
      : gr::sync_block("correlate_access_code_tag_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      set_history(21);
      d_sync = sync;
      d_threshold = threshold;
      d_threshold2 = threshold2;
      d_length = length;
      d_offset = 0;
      d_skip = 0;
    }

    /*
     * Our virtual destructor.
     */
    correlate_access_code_tag_cc_impl::~correlate_access_code_tag_cc_impl()
    {
    }

    int
    correlate_access_code_tag_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int i;
      int j;
      double correlation;
      unsigned long long bit;

      for (i=0; i<noutput_items; i++)
      {
        out[i] = in[i+20];
	correlation = 0.0;
	bit = 1;
	for (j=0; j<20; j++)
	{
          if (bit & d_sync)
            correlation += in[i+19-j].imag();
          else
            correlation -= in[i+19-j].imag();
          bit = bit << 1;
          if (bit & d_sync)
            correlation += in[i+19-j].real();
          else
            correlation -= in[i+19-j].real();
          bit = bit << 1;
	}
	if (correlation > d_threshold)
	{
          add_item_tag(0, d_offset + i, pmt::intern("correlation"),
	    pmt::from_double(correlation));
	  if (d_skip != d_length)
          {
	    add_item_tag(0, d_offset + i, pmt::intern("skip"),
              pmt::from_long(d_skip - d_length));
          }
	  d_skip = 0;
	}
	else if (((d_skip == d_length) || (d_skip == d_length + 1) ||
	  (d_skip == 2*d_length - 1) || (d_skip == 2*d_length) ||
	  (d_skip == 2*d_length + 1) ||
	  (d_skip == 3*d_length)) && (correlation > d_threshold2))
        {
          if (d_skip >= 2*d_length)
	  {
            fprintf(stderr, "low correlation after missing a frame\n");
	  }
	  add_item_tag(0, d_offset + i, pmt::intern("correlation"),
            pmt::from_double(correlation));
	  add_item_tag(0, d_offset + i, pmt::intern("low_correlation"),
	    pmt::from_double(correlation));
          if (d_skip != d_length)
          {
            add_item_tag(0, d_offset + i, pmt::intern("skip"),
              pmt::from_long(d_skip - d_length));
          }
          d_skip = 0;
	}
	d_skip++;
      }

      d_offset += noutput_items;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

