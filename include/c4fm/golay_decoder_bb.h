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


#ifndef INCLUDED_C4FM_GOLAY_DECODER_BB_H
#define INCLUDED_C4FM_GOLAY_DECODER_BB_H

#include <c4fm/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Decode using the extended binary Golay code
     * \ingroup c4fm
     * \details
     * The input stream is divided into blocks of 24 bits. The output stream contains
     * the first twelve bits of each input block. If the input block is not a valid
     * codeword, then a parity_error tag with a value of PMT_T will be added to the
     * first bit of the output block. A parity_error tag with a value of PMT_F will be
     * added at the start of the first valid block after a block containing an error.
     *
     */
    class C4FM_API golay_decoder_bb : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<golay_decoder_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::golay_decoder_bb.
       *
       * To avoid accidental use of raw pointers, c4fm::golay_decoder_bb's
       * constructor is in a private implementation
       * class. c4fm::golay_decoder_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_GOLAY_DECODER_BB_H */

