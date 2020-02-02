/* -*- c++ -*- */
/*
 * Copyright 2020 Michael Roe.
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

#ifndef INCLUDED_C4FM_SIGN_SCRAMBLER_FF_IMPL_H
#define INCLUDED_C4FM_SIGN_SCRAMBLER_FF_IMPL_H

#include <c4fm/sign_scrambler_ff.h>
#include <gnuradio/digital/lfsr.h>

namespace gr {
  namespace c4fm {

    class sign_scrambler_ff_impl : public sign_scrambler_ff
    {
     private:
      digital::lfsr d_lfsr;
      int d_counter;
      int d_count;

     public:
      sign_scrambler_ff_impl(int mask, int seed, int len, int count);
      ~sign_scrambler_ff_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_SIGN_SCRAMBLER_FF_IMPL_H */

