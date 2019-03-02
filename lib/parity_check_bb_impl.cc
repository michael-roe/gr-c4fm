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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "parity_check_bb_impl.h"

namespace gr {
  namespace c4fm {

    parity_check_bb::sptr
    parity_check_bb::make(int blocksize)
    {
      return gnuradio::get_initial_sptr
        (new parity_check_bb_impl(blocksize));
    }

    /*
     * The private constructor
     */
    parity_check_bb_impl::parity_check_bb_impl(int blocksize)
      : gr::sync_block("parity_check_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      set_output_multiple(blocksize);
      d_blocksize = blocksize;
      d_block_len_pmt = pmt::from_long(blocksize);
      d_parity_error_key = pmt::string_to_symbol("parity_error");
      d_offset = 0;
    }

    /*
     * Our virtual destructor.
     */
    parity_check_bb_impl::~parity_check_bb_impl()
    {
    }

    int
    parity_check_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      const char *inp;
      char *outp;
      int i;
      int j;
      int parity;


      inp = in;
      outp = out;
      for (i=0; i<noutput_items/d_blocksize; i++)
      {
        parity = 0;
	for (j=0; j<d_blocksize; j++)
	{
          *outp = *inp;
	  parity ^= (*inp) & 0x1;
	  outp++;
	  inp++;
	}
	if (parity)
        {
	  add_item_tag(0, d_offset+i*d_blocksize, d_parity_error_key, pmt::PMT_T);
	  d_previous_error = 1;
	}
	else if (d_previous_error)
	{
	  add_item_tag(0, d_offset+i*d_blocksize, d_parity_error_key, pmt::PMT_F);
	  d_previous_error = 0;
	}
      }

      d_offset += noutput_items;
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

