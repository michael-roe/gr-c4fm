/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_BERNOULLI_SOURCE_B_H
#define INCLUDED_C4FM_BERNOULLI_SOURCE_B_H

#include <gnuradio/c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace c4fm {

/*!
 * \brief Generate random bits that have a Bernoulli distribution.
 * \ingroup c4fm
 * \details
 * Each byte in the output stream is 1 with probability p and 0 with
 * probability 1-p.
 *
 */
class C4FM_API bernoulli_source_b : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<bernoulli_source_b> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of c4fm::bernoulli_source_b.
     *
     * To avoid accidental use of raw pointers, c4fm::bernoulli_source_b's
     * constructor is in a private implementation
     * class. c4fm::bernoulli_source_b::make is the public interface for
     * creating new instances.
     */
    static sptr make(double p, unsigned int seed);
};

} // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_BERNOULLI_SOURCE_B_H */
