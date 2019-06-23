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
#include "frame_sync_cc_impl.h"

namespace gr {
  namespace c4fm {

    frame_sync_cc::sptr
    frame_sync_cc::make(int frame_size, int sync_size, int bps, unsigned long long sync, double threshold)
    {
      return gnuradio::get_initial_sptr
        (new frame_sync_cc_impl(frame_size, sync_size, bps, sync, threshold));
    }

    /*
     * The private constructor
     */
    frame_sync_cc_impl::frame_sync_cc_impl(int frame_size, int sync_size, int bps, unsigned long long sync, double threshold)
      : gr::block("frame_sync_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      set_history(40);
      d_offset = 0;
      d_frame_size = frame_size;
      d_sync_size = sync_size;
      d_sync = sync;
      d_threshold = threshold;
      d_skip = 0;
      d_todo = 0;
    }

    /*
     * Our virtual destructor.
     */
    frame_sync_cc_impl::~frame_sync_cc_impl()
    {
    }

    void
    frame_sync_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items + 40;
    }

    int
    frame_sync_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      double correlation;
      unsigned long long bit;
      int i;
      int j;
      int produced;

      produced = 0;
      for (i=0; i<noutput_items; i++)
      {
        if (d_todo > 0)
	{
          out[produced] = in[i+39];
	  d_todo--;
	  produced++;
	}
	else
	{
	  d_skip++;
          bit = 1;
          correlation = 0.0;
          for (j=0; j<d_sync_size; j++)
          {
            if (bit & d_sync)
              correlation += in[i+39-j].imag();
	    else
              correlation -= in[i+39-j].imag();
	    bit = bit << 1;
	    if (bit & d_sync)
	      correlation += in[i+39-j].real();
	    else
	      correlation -= in[i+39-j].real();
	    bit = bit << 1;
          }
	  if (correlation > d_threshold)
          {
	    add_item_tag(0, d_offset + produced, pmt::intern("correlation"),
	      pmt::from_float(correlation));
	    if (d_skip > d_sync_size)
            {
	      add_item_tag(0, d_offset + produced, pmt::intern("skip"),
	        pmt::from_long(d_skip - d_sync_size));
	    }
	    d_skip = 0;
	    d_todo = d_frame_size;
#if 0
            for (j=d_sync_size-1; j>=0; j--)
	      fprintf(stderr, "%d%d",
	        in[39+i-j].real() > 0 ? 1 : 0,
	        in[39+i-j].imag() > 0 ? 1 : 0);
	    fprintf(stderr, " %f\n", correlation);
#endif
	  }
	}
      }


      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      d_offset += produced;

      // Tell runtime system how many output items we produced.
      return produced;
    }

  } /* namespace c4fm */
} /* namespace gr */

