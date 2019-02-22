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


#ifndef INCLUDED_C4FM_C4FM_SOFT_DECISION_FC_H
#define INCLUDED_C4FM_C4FM_SOFT_DECISION_FC_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Decode a 4 level FSK symbol into a pair of single bit soft decisions
     * \ingroup symbol_coding_blk
     *
     * \details
     * The input is a floating point number where the values -3, -1, +1 and +3
     * represent the Gray-coded dibits 11, 10, 00 and 01. The output is a complex
     * number whose real part is a soft decision for the first bit and whose
     * imaginary part is a soft decision for the second bit. In the output, -1
     * represents a bit value of 0 and +1 represents a bit value of 1; values between
     * -1 and +1 are output when the input value lies between a point of the
     *  constellation.
     */
    class C4FM_API c4fm_soft_decision_fc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<c4fm_soft_decision_fc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::c4fm_soft_decision_fc.
       *
       * To avoid accidental use of raw pointers, c4fm::c4fm_soft_decision_fc's
       * constructor is in a private implementation
       * class. c4fm::c4fm_soft_decision_fc::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_C4FM_SOFT_DECISION_FC_H */

