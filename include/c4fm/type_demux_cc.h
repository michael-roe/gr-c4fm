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


#ifndef INCLUDED_C4FM_TYPE_DEMUX_CC_H
#define INCLUDED_C4FM_TYPE_DEMUX_CC_H

#include <c4fm/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief <+description of block+>
     * \ingroup c4fm
     *
     */
    class C4FM_API type_demux_cc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<type_demux_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::type_demux_cc.
       *
       * To avoid accidental use of raw pointers, c4fm::type_demux_cc's
       * constructor is in a private implementation
       * class. c4fm::type_demux_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int frame_type, int data_type, int length);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_TYPE_DEMUX_CC_H */

