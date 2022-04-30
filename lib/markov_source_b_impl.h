/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_MARKOV_SOURCE_B_IMPL_H
#define INCLUDED_C4FM_MARKOV_SOURCE_B_IMPL_H

#include <gnuradio/c4fm/markov_source_b.h>
#include <gnuradio/random.h>

namespace gr {
namespace c4fm {

class markov_source_b_impl : public markov_source_b {
private:
    gr::random *d_rng;
    float d_p_start;
    float d_p_stop;
    int d_state;

public:
  markov_source_b_impl(double p_start, double p_stop, unsigned int seed);
  ~markov_source_b_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_MARKOV_SOURCE_B_IMPL_H */
