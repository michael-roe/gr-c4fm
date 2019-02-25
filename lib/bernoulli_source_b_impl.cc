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
#include "bernoulli_source_b_impl.h"

namespace gr {
  namespace c4fm {

    bernoulli_source_b::sptr
    bernoulli_source_b::make(double p)
    {
      return gnuradio::get_initial_sptr
        (new bernoulli_source_b_impl(p));
    }

    /*
     * The private constructor
     */
    bernoulli_source_b_impl::bernoulli_source_b_impl(double p)
      : gr::sync_block("bernoulli_source_b",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      d_p = p;
    }

    /*
     * Our virtual destructor.
     */
    bernoulli_source_b_impl::~bernoulli_source_b_impl()
    {
    }

    int
    bernoulli_source_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      int i;
      char *out = (char *) output_items[0];
      double q;

      for (i = 0; i < noutput_items; i++)
      {
        q = ((double) random())/((double) RAND_MAX);
	if (q < d_p)
          out[i] = 1; 
	else
          out[i] = 0;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

