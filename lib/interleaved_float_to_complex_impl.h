/* -*- c++ -*- */
/*
 * Copyright 2020 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_INTERLEAVED_FLOAT_TO_COMPLEX_IMPL_H
#define INCLUDED_C4FM_INTERLEAVED_FLOAT_TO_COMPLEX_IMPL_H

#include <c4fm/interleaved_float_to_complex.h>

namespace gr {
  namespace c4fm {

    class interleaved_float_to_complex_impl : public interleaved_float_to_complex
    {
     private:
      // Nothing to declare in this block.

     public:
      interleaved_float_to_complex_impl();
      ~interleaved_float_to_complex_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_INTERLEAVED_FLOAT_TO_COMPLEX_IMPL_H */

