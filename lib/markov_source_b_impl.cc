/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "markov_source_b_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace c4fm {

markov_source_b::sptr markov_source_b::make(double p_start, double p_stop,
                                            unsigned int seed) {
  return gnuradio::make_block_sptr<markov_source_b_impl>(p_start, p_stop, seed);
}

/*
 * The private constructor
 */
markov_source_b_impl::markov_source_b_impl(double p_start, double p_stop,
                                           unsigned int seed)
    : gr::sync_block(
          "markov_source_b",
          gr::io_signature::make(0, 0, 0),
          gr::io_signature::make(1, 1, sizeof(char)))
{
    d_rng = new gr::random(seed);
    d_p_start = p_start;
    d_p_stop = p_stop;
    d_state = 0;
}

/*
 * Our virtual destructor.
 */
markov_source_b_impl::~markov_source_b_impl()
{
    delete d_rng;
}

int markov_source_b_impl::work(int noutput_items,
                               gr_vector_const_void_star &input_items,
                               gr_vector_void_star &output_items)
{
  char *out = (char *)output_items[0];
  int i;
  float q;

  q = d_rng->ran1();
  for (i=0; i<noutput_items; i++)
  {
    if (d_state)
    {
      q = d_rng->ran1();
      if (q < d_p_stop)
      {
        out[i] = 1;
	d_state = 0;
      }
      else
      {
        q = d_rng->ran1();
	if (q < 0.5)
	{
	  out[i] = 0;
	}
	else
	{
	  out[i] = 1;
	}
      }
    }
    else
    {
      q = d_rng->ran1();
      if (q < d_p_start)
      {
        out[i] = 1;
	q = d_rng->ran1();
	if (q < d_p_stop)
	{
          d_state = 0;
	}
	else
	{
	  d_state = 1;
	}
      }
      else
      {
        out[i] = 0;
      }
    }
  }

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

} /* namespace c4fm */
} /* namespace gr */
