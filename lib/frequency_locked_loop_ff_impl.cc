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
#include "frequency_locked_loop_ff_impl.h"

namespace gr {
  namespace c4fm {

    frequency_locked_loop_ff::sptr
    frequency_locked_loop_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new frequency_locked_loop_ff_impl());
    }

    /*
     * The private constructor
     */
    frequency_locked_loop_ff_impl::frequency_locked_loop_ff_impl()
      : gr::sync_block("frequency_locked_loop_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      int i;

      d_count = 0;
      d_index = 0;
      d_rolloff = 1.6;
      d_delta_f = 0.0;
      d_derivative = 0.0;
      d_second = 0.0;
      for (i=0; i<200; i++)
      {
        d_histogram[i] = 0;
      }
    }

    /*
     * Our virtual destructor.
     */
    frequency_locked_loop_ff_impl::~frequency_locked_loop_ff_impl()
    {
    }

    int
    frequency_locked_loop_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      int i;
      int j;
      int v;
      double delta;
      double variance;

      for (i=0; i<noutput_items; i++)
      {
        if ((in[i] < -3.0 + d_delta_f) && (in[i] > -3.0 - d_rolloff + d_delta_f))
        {
          v = (int)((in[i] + 3 + d_rolloff - d_delta_f)*100.0/d_rolloff);
	  d_histogram[v]++;
	  delta = sin((in[i]+3-d_delta_f)*M_PI/d_rolloff);
	  d_derivative += delta;
	  d_second += cos((in[i]+3-d_delta_f)*M_PI/d_rolloff);
	  d_count++;
	}
	else if ((in[i] > 3 + d_delta_f) && (in[i] < 3 + d_rolloff + d_delta_f))
        {
	  v = (int)((in[i]-3-d_delta_f)*100.0/d_rolloff)+100;
	  d_histogram[v]++;
	  delta = sin((in[i]-3-d_delta_f)*M_PI/d_rolloff);
	  d_derivative += delta;
	  d_second += cos((in[i]-3-d_delta_f)*M_PI/d_rolloff);
	  d_count++;
	}

	out[i] = in[i] - d_delta_f;

	if (d_count == 24000)
        {
#if 0
	  variance = 0.0;
	  for (j=0; j<200; j++)
	  {
	    printf("%f\n", ((float) d_histogram[j])/((float) d_count));
	    variance += (((double) j) - 100.0)*(((double) j) - 100.0)*d_histogram[j];
	    d_histogram[j] = 0;
	  }
	  printf("sd = %lf\n", sqrt(variance/((double) d_count)));
	  printf("derivative = %lf\n", d_derivative/((double) d_count));
	  printf("second derivative = %lf\n", d_second/((double) d_count));
	  printf("***\n");
#endif
	  d_delta_f += d_derivative/((double) d_count);
	  d_count = 0;
	  d_derivative = 0.0;
	  d_second = 0.0;
	}
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
  } /* namespace c4fm */
} /* namespace gr */
