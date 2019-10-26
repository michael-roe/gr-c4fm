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


#ifndef INCLUDED_C4FM_RATIO_COMBINER_FF_H
#define INCLUDED_C4FM_RATIO_COMBINER_FF_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief The output stream is a weighted sum of the two input streams:
     * out[i] = in0[i]*sin(angle)**2 + in1[i]*cos(angle)**2.
     * Angle is measured in degrees (not radians). Its value can be updated
     * dynamically by sending the block an asynchronous message containing an
     * ordered pair of the keyword "angle" and a double-precision floating
     * point number.
     * \ingroup c4fm
     *
     */
    class C4FM_API ratio_combiner_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<ratio_combiner_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::ratio_combiner_ff.
       *
       * To avoid accidental use of raw pointers, c4fm::ratio_combiner_ff's
       * constructor is in a private implementation
       * class. c4fm::ratio_combiner_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make(double angle);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_RATIO_COMBINER_FF_H */

