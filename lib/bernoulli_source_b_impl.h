/* -*- c++ -*- */
/*
 * Copyright 2019-2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_BERNOULLI_SOURCE_B_IMPL_H
#define INCLUDED_C4FM_BERNOULLI_SOURCE_B_IMPL_H

#include <gnuradio/c4fm/bernoulli_source_b.h>
#include <gnuradio/random.h>

namespace gr {
namespace c4fm {

class bernoulli_source_b_impl : public bernoulli_source_b
{
private:
    float d_p;
    gr::random *d_rng; 

public:
    bernoulli_source_b_impl(double p, unsigned int seed);
    ~bernoulli_source_b_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_BERNOULLI_SOURCE_B_IMPL_H */
