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


#ifndef INCLUDED_C4FM_FREQUENCY_LOCKED_LOOP_FF_H
#define INCLUDED_C4FM_FREQUENCY_LOCKED_LOOP_FF_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Frequncy Locked Loop
     * \ingroup c4fm
     * \details
     * This block expects its input to be the output of an FM demodulator. It shifts
     * the signal up or down to correct for small errors in the carrier frequency.
     *
     * The shift is chosen to maximize the power passed through a band-edge filter
     * that starts at +/-3 and ends at +/-(3+rolloff). (The signal will be centered on zero
     * when this power is maximized). It is computed by taking the time-average of the
     * derivative of the band-edge filter at the current input value.
     * 
     * The samples parameter gives the number of input samples between updates of the shift.
     *
     * The band-edge filter is a raised cosine. A typical value of the rolloff parameter
     * is 1.6.
     *
     */
    class C4FM_API frequency_locked_loop_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<frequency_locked_loop_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::frequency_locked_loop_ff.
       *
       * To avoid accidental use of raw pointers, c4fm::frequency_locked_loop_ff's
       * constructor is in a private implementation
       * class. c4fm::frequency_locked_loop_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make(double rolloff, int samples);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_FREQUENCY_LOCKED_LOOP_FF_H */

