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
#include "ratio_combiner_ff_impl.h"

namespace gr {
  namespace c4fm {

    ratio_combiner_ff::sptr
    ratio_combiner_ff::make(double angle)
    {
      return gnuradio::get_initial_sptr
        (new ratio_combiner_ff_impl(angle));
    }

    void ratio_combiner_ff_impl::set_angle(pmt::pmt_t msg)
    {
      double angle;
      gr::thread::scoped_lock guard(d_mutex);

      if (pmt::is_pair(msg) && pmt::is_real(pmt::cdr(msg)))
      {
	angle =  pmt::to_double(pmt::cdr(msg))*M_PI/180,0;
	d_w0 = sin(angle)*sin(angle);
	d_w1 = cos(angle)*cos(angle);
      }
    }


    /*
     * The private constructor
     */
    ratio_combiner_ff_impl::ratio_combiner_ff_impl(double angle)
      : gr::sync_block("ratio_combiner_ff",
              gr::io_signature::make(2, 2, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      double radians;

      d_port = pmt::mp("angle");
      message_port_register_in(d_port);
      set_msg_handler(d_port,
        boost::bind(&ratio_combiner_ff_impl::set_angle, this, _1));
      radians = angle*M_PI/180.0;
      d_w0 = (float) sin(radians)*sin(radians);
      d_w1 = (float) cos(radians)*cos(radians);
    }

    /*
     * Our virtual destructor.
     */
    ratio_combiner_ff_impl::~ratio_combiner_ff_impl()
    {
    }

    int
    ratio_combiner_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in0 = (const float *) input_items[0];
      const float *in1 = (const float *) input_items[1];
      float *out = (float *) output_items[0];
      int i;
      gr::thread::scoped_lock guard(d_mutex);

      for (i=0; i<noutput_items; i++)
      {
        out[i] = d_w0*in0[i] + d_w1*in1[i];
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

