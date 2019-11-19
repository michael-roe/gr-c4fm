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
#include "quaternary_slicer_cb_impl.h"

namespace gr {
  namespace c4fm {

    quaternary_slicer_cb::sptr
    quaternary_slicer_cb::make()
    {
      return gnuradio::get_initial_sptr
        (new quaternary_slicer_cb_impl());
    }

    /*
     * The private constructor
     */
    quaternary_slicer_cb_impl::quaternary_slicer_cb_impl()
      : gr::sync_block("quaternary_slicer_cb",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {}

    /*
     * Our virtual destructor.
     */
    quaternary_slicer_cb_impl::~quaternary_slicer_cb_impl()
    {
    }

    int
    quaternary_slicer_cb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      char *out = (char *) output_items[0];
      int i;
      char b;

      for (i = 0; i < noutput_items; i++)
      {
        if (in[i].real() >= 0.0)
        {
          b = 2;
	}
	else
	{
	  b = 0;
	}
	if (in[i].imag() >= 0.0)
        {
	  b ^= 1;
	}
	out[i] = b;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

