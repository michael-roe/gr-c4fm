/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_MARKOV_SOURCE_B_H
#define INCLUDED_C4FM_MARKOV_SOURCE_B_H

#include <gnuradio/c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace c4fm {

/*!
 * \brief Generate random bits by a Markov process
 * \ingroup c4fm
 * \details
 * The Markov process transitions from the idle state to the active state
 * with probability p_start, and from the active state to the idle state
 * with probability p_stop. While in the idle state, the output is 0.
 * While in the active state, the output is 0 with probability 0.5 and 1
 * with probability 0.5.
 *
 */
class C4FM_API markov_source_b : virtual public gr::sync_block {
public:
  typedef std::shared_ptr<markov_source_b> sptr;

  /*!
   * \brief Return a shared_ptr to a new instance of c4fm::markov_source_b.
   *
   * To avoid accidental use of raw pointers, c4fm::markov_source_b's
   * constructor is in a private implementation
   * class. c4fm::markov_source_b::make is the public interface for
   * creating new instances.
   */
  static sptr make(double p_start, double p_stop, unsigned int seed);
};

} // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_MARKOV_SOURCE_B_H */
