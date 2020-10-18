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
#include "c4fm_reencode_soft_decision_cf_impl.h"

namespace gr {
  namespace c4fm {

    static float graycode[4] = {1.0, -1.0, 3.0, -3.0};

    c4fm_reencode_soft_decision_cf::sptr
    c4fm_reencode_soft_decision_cf::make(float gain)
    {
      return gnuradio::get_initial_sptr
        (new c4fm_reencode_soft_decision_cf_impl(gain));
    }


    /*
     * The private constructor
     */
    c4fm_reencode_soft_decision_cf_impl::c4fm_reencode_soft_decision_cf_impl(float gain)
      : gr::sync_block("c4fm_reencode_soft_decision_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      d_gain = gain;
    }

    /*
     * Our virtual destructor.
     */
    c4fm_reencode_soft_decision_cf_impl::~c4fm_reencode_soft_decision_cf_impl()
    {
    }

    int
    c4fm_reencode_soft_decision_cf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      int i;
      int bit0;
      int bit1;

      for (i=0; i<noutput_items; i++)
      {
        bit0 = (in[i].real() >= 0) ? 1 : 0;
	bit1 = (in[i].imag() >= 0) ? 1 : 0;
	out[i] = graycode[bit1*2 + bit0];
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

