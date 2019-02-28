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


#ifndef INCLUDED_C4FM_PARITY_CHECK_BB_H
#define INCLUDED_C4FM_PARITY_CHECK_BB_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Check parity of each block.
     * \ingroup c4fm
     * \details
     * The input stream is divided into blocks of length blocksize. The output stream
     * is equal to the input stream, with a parity_error tag added at the start of each
     * block that does not have even parity.
     *
     */
    class C4FM_API parity_check_bb : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<parity_check_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::parity_check_bb.
       *
       * To avoid accidental use of raw pointers, c4fm::parity_check_bb's
       * constructor is in a private implementation
       * class. c4fm::parity_check_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make(int blocksize);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_PARITY_CHECK_BB_H */

