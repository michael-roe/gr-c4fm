/* -*- c++ -*- */
/* 
 * Copyright 2019 Michael Roe
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
#include "c4fm_soft_decision_fc_impl.h"

namespace gr {
  namespace c4fm {

    c4fm_soft_decision_fc::sptr
    c4fm_soft_decision_fc::make(double gain)
    {
      return gnuradio::get_initial_sptr
        (new c4fm_soft_decision_fc_impl(gain));
    }

    /*
     * The private constructor
     */
    c4fm_soft_decision_fc_impl::c4fm_soft_decision_fc_impl(double gain)
      : gr::sync_block("c4fm_soft_decision_fc",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      d_gain = gain;
    }

    /*
     * Our virtual destructor.
     */
    c4fm_soft_decision_fc_impl::~c4fm_soft_decision_fc_impl()
    {
    }

    int
    c4fm_soft_decision_fc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      float f;
      int i;

      for (i = 0; i < noutput_items; i++)
      {
	f = in[i];
	if (f < -3.0)
        {
          out[i] = gr_complex(d_gain, d_gain);
	}
	else if (f < -1.0)
        {
	  out[i] = gr_complex(d_gain, d_gain*(-2-f));
	}
        else if (f < 1.0)
        {
	  out[i] = gr_complex(-d_gain*f, -d_gain);
        }
        else if (f < 3.0)
	{
	  out[i] = gr_complex(-d_gain, d_gain*(f-2));
        }
        else
	{	
          out[i] = gr_complex(-d_gain, d_gain);
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

