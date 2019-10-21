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
#include "splitter_cc_impl.h"

namespace gr {
  namespace c4fm {

    splitter_cc::sptr
    splitter_cc::make(double angle)
    {
      return gnuradio::get_initial_sptr
        (new splitter_cc_impl(angle));
    }

    void splitter_cc_impl::set_angle(pmt::pmt_t msg)
    {
      double angle;

      if (pmt::is_pair(msg) && pmt::is_real(pmt::cdr(msg)))
      {
	angle =  pmt::to_double(pmt::cdr(msg))*M_PI/180,0;
	d_w0 = sin(angle);
	d_w1 = cos(angle);
      }
    }

    /*
     * The private constructor
     */
    splitter_cc_impl::splitter_cc_impl(double angle)
      : gr::sync_block("splitter_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(2, 2, sizeof(gr_complex)))
    {
      d_port = pmt::mp("angle");
      message_port_register_in(d_port);
      set_msg_handler(d_port,
        boost::bind(&splitter_cc_impl::set_angle, this, _1));

      d_w0 = (float) sin(angle*M_PI/180.0);
      d_w1 = (float) cos(angle*M_PI/180.0);
    }

    /*
     * Our virtual destructor.
     */
    splitter_cc_impl::~splitter_cc_impl()
    {
    }

    int
    splitter_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out0 = (gr_complex *) output_items[0];
      gr_complex *out1 = (gr_complex *) output_items[1];
      int i;

      for (i=0; i<noutput_items; i++)
      {
        out0[i] = in[i]*d_w0;
	out1[i] = in[i]*d_w1;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

