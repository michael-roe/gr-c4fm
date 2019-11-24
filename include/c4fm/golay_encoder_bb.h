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


#ifndef INCLUDED_C4FM_GOLAY_ENCODER_BB_H
#define INCLUDED_C4FM_GOLAY_ENCODER_BB_H

#include <c4fm/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Encode bits using the extended binary Golay code
     * \ingroup c4fm
     * \details
     * For each twelve bits of input, the output is the 12 input bits followed by
     * 12 bits of error correction.
     *
     * The error correction bits are formed by regarding the input bits as a polynomial
     * over GF(2), multiplying it by x**11 and taking the remainder after division by
     * x**11+x**9+x**7+x**6+x**5+x+1. The error correction bits are the coefficients of
     * the remainder followed by a parity bit to give the 24 bit output block even parity.
     *
     */
    class C4FM_API golay_encoder_bb : virtual public gr::sync_interpolator
    {
     public:
      typedef boost::shared_ptr<golay_encoder_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::golay_encoder_bb.
       *
       * To avoid accidental use of raw pointers, c4fm::golay_encoder_bb's
       * constructor is in a private implementation
       * class. c4fm::golay_encoder_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_GOLAY_ENCODER_BB_H */

