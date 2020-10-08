/* -*- c++ -*- */
/*
 * Copyright 2020 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "interleaved_float_to_complex_impl.h"

namespace gr {
  namespace c4fm {

    interleaved_float_to_complex::sptr
    interleaved_float_to_complex::make()
    {
      return gnuradio::get_initial_sptr
        (new interleaved_float_to_complex_impl());
    }


    /*
     * The private constructor
     */
    interleaved_float_to_complex_impl::interleaved_float_to_complex_impl()
      : gr::sync_decimator("interleaved_float_to_complex",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), 2)
    {}

    /*
     * Our virtual destructor.
     */
    interleaved_float_to_complex_impl::~interleaved_float_to_complex_impl()
    {
    }

    int
    interleaved_float_to_complex_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int i;

      for (i=0; i<noutput_items; i++)
      {
        out[i] = gr_complex(in[2*i], in[2*i+1]);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

