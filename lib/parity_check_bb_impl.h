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

#ifndef INCLUDED_C4FM_PARITY_CHECK_BB_IMPL_H
#define INCLUDED_C4FM_PARITY_CHECK_BB_IMPL_H

#include <c4fm/parity_check_bb.h>

namespace gr {
  namespace c4fm {

    class parity_check_bb_impl : public parity_check_bb
    {
     private:
      int d_blocksize;
      pmt::pmt_t d_block_len_pmt;
      pmt::pmt_t d_parity_error_key;
      int d_offset;
      int d_previous_error;

     public:
      parity_check_bb_impl(int blocksize);
      ~parity_check_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_PARITY_CHECK_BB_IMPL_H */

