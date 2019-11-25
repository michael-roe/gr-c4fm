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
#include "complex_to_interleaved_float_impl.h"

namespace gr {
  namespace c4fm {

    complex_to_interleaved_float::sptr
    complex_to_interleaved_float::make()
    {
      return gnuradio::get_initial_sptr
        (new complex_to_interleaved_float_impl());
    }


    /*
     * The private constructor
     */
    complex_to_interleaved_float_impl::complex_to_interleaved_float_impl()
      : gr::sync_interpolator("complex_to_interleaved_float",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)), 2)
    {}

    /*
     * Our virtual destructor.
     */
    complex_to_interleaved_float_impl::~complex_to_interleaved_float_impl()
    {
    }

    int
    complex_to_interleaved_float_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      int i;

      for (i=0; i<noutput_items/2; i++)
      {
        out[i + i] = in[i].real();
	out[i + i + 1] = in[i].imag();
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

