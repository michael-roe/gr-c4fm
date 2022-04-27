/* -*- c++ -*- */
/*
 * Copyright 2019-2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bernoulli_source_b_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace c4fm {

bernoulli_source_b::sptr bernoulli_source_b::make(double p, unsigned int seed)
{
    return gnuradio::make_block_sptr<bernoulli_source_b_impl>(p, seed);
}


/*
 * The private constructor
 */
bernoulli_source_b_impl::bernoulli_source_b_impl(double p, unsigned int seed)
    : gr::sync_block("bernoulli_source_b",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(1, 1, sizeof(char)))
{
  d_p = p;
  d_rng = new gr::random(seed);
}

/*
 * Our virtual destructor.
 */
bernoulli_source_b_impl::~bernoulli_source_b_impl()
{
  delete d_rng;
}

int bernoulli_source_b_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    int i;
    char *out = (char *) output_items[0];
    float q;

    for (i=0; i<noutput_items; i++)
    {
      q = d_rng->ran1();
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
