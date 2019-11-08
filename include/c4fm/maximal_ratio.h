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


#ifndef INCLUDED_C4FM_MAXIMAL_RATIO_H
#define INCLUDED_C4FM_MAXIMAL_RATIO_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Calculate the mixing ratio of two streams that will maximize the signal to
     * noise ratio,
     * \ingroup c4fm
     * \details
     * This block forms part of a MIMO/diversity receiver. It takes as input estimates
     * of the signal to noise ratio of two different sources of the same signal (e.g.
     * from different antennas) and outputs the combining ratio that will maximize the
     * SNR (assuming that the the two sources have statistically independent noise).
     * 
     * The SNR estimates are in the form of an asynchronous message containing an ordered
     * pair of "snr" and a double-precision value. The output is an asynchronous message
     * containing an ordered pair of "angle" and the mixing angle, measured in degrees.
     * 
     * angle = atan(exp10((snr0 - snr1)*0.05*gain))*180.0/M_PI
     *
     * If the block receives three asynchronous messages from one channel without
     * receiving anything from the other channel, it assumes that there is no signal
     * on the quiet channel and assigns it an SNR of zero. As asynchronous messages
     * are not guaranteed to be delivered immediately, this can in principle happen
     * if the channel has non-zero SNR but its SNR reports have been delayed by the
     * scheduler.
     *
     * The gain parameter should be set to 1 if the SNR estimates are accurate.
     * It can be set to an different value if the SNR estimates need to be scaled
     * to obtain the true SNR.
     */
    class C4FM_API maximal_ratio : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<maximal_ratio> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::maximal_ratio.
       *
       * To avoid accidental use of raw pointers, c4fm::maximal_ratio's
       * constructor is in a private implementation
       * class. c4fm::maximal_ratio::make is the public interface for
       * creating new instances.
       */
      static sptr make(double gain);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_MAXIMAL_RATIO_H */

