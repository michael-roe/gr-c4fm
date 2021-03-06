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

#ifndef INCLUDED_C4FM_CORRELATE_ACCESS_CODE_TAG_CC_IMPL_H
#define INCLUDED_C4FM_CORRELATE_ACCESS_CODE_TAG_CC_IMPL_H

#include <c4fm/correlate_access_code_tag_cc.h>

namespace gr {
  namespace c4fm {

    class correlate_access_code_tag_cc_impl : public correlate_access_code_tag_cc
    {
     private:
      unsigned long long d_sync;
      unsigned long long d_offset;
      double d_threshold;
      double d_threshold2;
      int d_length;
      int d_skip;

     public:
      correlate_access_code_tag_cc_impl(int sync_len, unsigned long long sync, int length, double threshold, double threshold2);
      ~correlate_access_code_tag_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_CORRELATE_ACCESS_CODE_TAG_CC_IMPL_H */

