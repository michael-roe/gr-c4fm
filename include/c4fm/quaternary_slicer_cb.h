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


#ifndef INCLUDED_C4FM_QUATERNARY_SLICER_CB_H
#define INCLUDED_C4FM_QUATERNARY_SLICER_CB_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief Slice a complex number containing a soft decision into a pair of bits.
     * \ingroup c4fm
     * \details
     * The least significant bit of the output is 1 if the imaginary component
     * of the input is non-negative. The second bit of the output is 1 if the
     * real component of the input is non-negative.
     * 
     * This can be used to slice a complex number containing soft decisions in
     * its real and imaginary components into hard decisions for two bits.
     *
     */
    class C4FM_API quaternary_slicer_cb : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<quaternary_slicer_cb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::quaternary_slicer_cb.
       *
       * To avoid accidental use of raw pointers, c4fm::quaternary_slicer_cb's
       * constructor is in a private implementation
       * class. c4fm::quaternary_slicer_cb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_QUATERNARY_SLICER_CB_H */

