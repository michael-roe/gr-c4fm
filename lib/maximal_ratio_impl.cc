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
#include "maximal_ratio_impl.h"

namespace gr {
  namespace c4fm {

    maximal_ratio::sptr
    maximal_ratio::make()
    {
      return gnuradio::get_initial_sptr
        (new maximal_ratio_impl());
    }

    void maximal_ratio_impl::set_snr0(pmt::pmt_t msg)
    {
      double delta;

      if (pmt::is_pair(msg) && pmt::is_real(pmt::cdr(msg)))
      {
        d_snr0 =  pmt::to_double(pmt::cdr(msg));
        if (d_snr1 != 0.0)
        {
          delta = (d_snr0 - d_snr1)*0.1*0.5/0.767;
          d_angle = atan(exp10(delta))*180.0/M_PI;
        }
        else
        {
          d_angle = 90.0;
	}
	message_port_pub(d_port_out, pmt::cons(d_tag_key, pmt::from_double(d_angle)));
      }
    }

    void maximal_ratio_impl::set_snr1(pmt::pmt_t msg)
    {
      double delta;

      if (pmt::is_pair(msg) && pmt::is_real(pmt::cdr(msg)))
      {
        d_snr1 =  pmt::to_double(pmt::cdr(msg));
	if (d_snr0 != 0.0)
        {
          delta = (d_snr0 - d_snr1)*0.1*0.5/0.767;
	  d_angle = atan(exp10(delta))*180.0/M_PI;
        }
	else
	{
	  d_angle = 0.0;
	}
	message_port_pub(d_port_out, pmt::cons(d_tag_key, pmt::from_double(d_angle)));
      }
    }


    /*
     * The private constructor
     */
    maximal_ratio_impl::maximal_ratio_impl()
      : gr::sync_block("maximal_ratio",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
      d_port_in0 = pmt::mp("in0");
      d_port_in1 = pmt::mp("in1");
      d_port_out = pmt::mp("out");
      message_port_register_in(d_port_in0);
      message_port_register_in(d_port_in1);
      message_port_register_out(d_port_out);
      set_msg_handler(d_port_in0,
        boost::bind(&maximal_ratio_impl::set_snr0, this, _1));
      set_msg_handler(d_port_in1,
        boost::bind(&maximal_ratio_impl::set_snr1, this, _1));
      d_tag_key = pmt::intern("angle");
      d_snr0 = 0.0;
      d_snr1 = 0.0;
      d_angle = 45.0;

    }

    /*
     * Our virtual destructor.
     */
    maximal_ratio_impl::~maximal_ratio_impl()
    {
    }

    int
    maximal_ratio_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

