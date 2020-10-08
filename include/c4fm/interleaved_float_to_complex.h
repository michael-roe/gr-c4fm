/* -*- c++ -*- */
/*
 * Copyright 2020 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_INTERLEAVED_FLOAT_TO_COMPLEX_H
#define INCLUDED_C4FM_INTERLEAVED_FLOAT_TO_COMPLEX_H

#include <c4fm/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief <+description of block+>
     * \ingroup c4fm
     *
     */
    class C4FM_API interleaved_float_to_complex : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<interleaved_float_to_complex> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::interleaved_float_to_complex.
       *
       * To avoid accidental use of raw pointers, c4fm::interleaved_float_to_complex's
       * constructor is in a private implementation
       * class. c4fm::interleaved_float_to_complex::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_INTERLEAVED_FLOAT_TO_COMPLEX_H */

