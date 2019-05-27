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

#ifndef INCLUDED_C4FM_FRAME_SYNC_CC_IMPL_H
#define INCLUDED_C4FM_FRAME_SYNC_CC_IMPL_H

#include <c4fm/frame_sync_cc.h>

namespace gr {
  namespace c4fm {

    class frame_sync_cc_impl : public frame_sync_cc
    {
     private:
       int d_frame_size;
       int d_sync_size;
       unsigned long long d_sync;
       double d_threshold;
       int d_todo;
       int d_skip;

     public:
      frame_sync_cc_impl(int frame_size, int sync_size, int bps, unsigned long long sync, double threshold);
      ~frame_sync_cc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_FRAME_SYNC_CC_IMPL_H */

