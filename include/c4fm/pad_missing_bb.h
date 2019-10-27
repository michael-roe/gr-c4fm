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


#ifndef INCLUDED_C4FM_PAD_MISSING_BB_H
#define INCLUDED_C4FM_PAD_MISSING_BB_H

#include <c4fm/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief This block expects its input to stream to contain fixed length frames,
     * with the start of each frame having a "frame_number" tag containing a sequence
     * number modulo frame_total. If the frame_number tag indicates that one or
     * more frames have been lost (i.e. it is not the previous frame_number plus
     * one modulo frame_total), then additional frames of all zeros are inserted
     * to fill the gap. The inserted frames are divided into fixed length subframes,
     * and a "deleted_frame" tag with value True is added at the start of each
     * subframe.
     * \ingroup c4fm
     *
     */
    class C4FM_API pad_missing_bb : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<pad_missing_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::pad_missing_bb.
       *
       * To avoid accidental use of raw pointers, c4fm::pad_missing_bb's
       * constructor is in a private implementation
       * class. c4fm::pad_missing_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make(int length, int subframes);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_PAD_MISSING_BB_H */

