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
#include "golay_decoder_bb_impl.h"

namespace gr {
  namespace c4fm {

    golay_decoder_bb::sptr
    golay_decoder_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new golay_decoder_bb_impl());
    }

    /*
     * The private constructor
     */
    golay_decoder_bb_impl::golay_decoder_bb_impl()
      : gr::sync_decimator("golay_decoder_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), 2)
    {
      set_output_multiple(12);
      d_block_len_pmt = pmt::from_long(12);
      d_parity_error_key = pmt::string_to_symbol("parity_error");
      d_offset = 0;
      d_previous_error = 0;
    }

    /*
     * Our virtual destructor.
     */
    golay_decoder_bb_impl::~golay_decoder_bb_impl()
    {
    }

    int
    golay_decoder_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      int i;
      int j;
      int parity;
      unsigned int s;
      unsigned int w1;
      int burst;

      w1 = 1 | (1 << 2) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 10) | (1 << 11);

      for (i=0; i<noutput_items/12; i++)
      {
	parity = 0;
	s = 0;
        for (j=11; j>=0; j--)
        {
	  parity ^= in[24*i+j] & 0x1;
	  s ^= (in[24*i+j] & 1);
          if (s & 1)
          {
            s ^= w1;
	  }
          s = s >> 1;
          out[12*i+j] = in[24*i+j];
	}
	for (j=12; j<23; j++)
	{
          parity ^= in[24*i+j] & 0x1;
	  if (in[24*i+j] & 0x01)
	  {
	    s ^= (1 << (22 - j));
	  }
	}
	parity ^= in[24*i+23];

	burst = 0;
	if (parity)
	{
	  /* If the error is in only one bit, correct it */
	  switch (s)
	  {
	    case 0:
	    case 1:
	    case 2:
	    case 4:
	    case 8:
	    case 16:
	    case 32:
	    case 64:
	    case 128:
	    case 256:
	    case 512:
	    case 1024:
              s = 0;
	      parity = 0;
	      burst = 1;
	      break;
	    case 1594:
	      out[12*i] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 1;
	      break;
	    case 797:
	      out[12*i + 1] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 1;
	      break;
	    case 1972:
	      out[12*i + 2] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 1;
	      break;
	    case 986:
	      out[12*i + 3] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
            case 493:
	      out[12*i + 4] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
            case 1740:
	      out[12*i + 5] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
            case 870:
	      out[12*i + 6] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
	    case 435:
	      out[12*i + 7] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
            case 1763:
	      out[12*i + 8] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
	    case 1355:
	      out[12*i + 9] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
	    case 1183:
	      out[12*i + 10] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
	    case 1141:
	      out[12*i + 11] ^= 1;
              s = 0;
              parity = 0;
	      burst = 1;
              break;
	    /* Correct 3 bit burst errors */
	    case 659:
	      out[12*i] ^= 1;
	      out[12*i + 1] ^= 1;
	      out[12*i + 2] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 3;
	      fprintf(stderr, "correcting syndrome 659\n");
	      break;
	    case 1907:
	      out[12*i + 1] ^= 1;
              out[12*i + 2] ^= 1;
              out[12*i + 3] ^= 1;
              s = 0;
	      parity = 0;
	      burst = 3;
	      fprintf(stderr, "correcting syndrome 1907\n");
	      break;
	    /* Burst is length 4, weight 3 */
	    case 1789:
	      out[12*i] ^= 1;
	      out[12*i + 1] ^= 1;
	      out[12*i + 3] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 1348:
	      out[12*i + 1] ^= 1;
	      out[12*i + 2] ^= 1;
	      out[12*i + 4] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 674:
	      out[12*i + 2] ^= 1;
	      out[12*i + 3] ^= 1;
	      out[12*i + 5] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 337:
	      out[12*i + 3] ^= 1;
	      out[12*i + 4] ^= 1;
	      out[12*i + 6] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 1682:
	      out[12*i + 4] ^= 1;
	      out[12*i + 5] ^= 1;
	      out[12*i + 7] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 841:
	      out[12*i + 5] ^= 1;
	      out[12*i + 6] ^= 1;
	      out[12*i + 8] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 1950:
	      out[12*i + 6] ^= 1;
	      out[12*i + 7] ^= 1;
	      out[12*i + 9] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 975:
	      out[12*i + 7] ^= 1;
	      out[12*i + 8] ^= 1;
	      out[12*i + 10] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 2013:
	      out[12*i + 8] ^= 1;
	      out[12*i + 9] ^= 1;
	      out[12*i + 11] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 1492:
	      out[12*i + 9] ^= 1;
	      out[12*i + 10] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 746:
	      out[12*i + 10] ^= 1;
	      out[12*i + 11] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 373:
	      out[12*i + 11] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 1664:
	    case 832:
	    case 416:
	    case 208:
	    case 104:
	    case 52:
	    case 26:
	    case 13:
	    case 6:
	      s = 0;
	      parity = 0;
	      burst = 4;
	      break;
	    case 1481:
	      /*
	       * This error is not usually correctable by the Golay code.
	       * I'm relying on knowing the statistics of the preceeding
	       * stage.
	       */
	      out[12*i] ^= 1;
	      out[12*i + 2] ^= 1;
	      out[12*i + 4] ^= 1;
	      out[12*i + 5] ^= 1;
	      out[12*i + 6] ^= 1;
	      s = 0;
	      parity = 0;
	      burst = 5;
	      break;
	    case 53:
	      fprintf(stderr, "correcting syndrome 53\n");
	      s = 0;
	      parity = 0;
	      burst = 7;
	      break;
	    default:
	      break;
          }
	}
	else
	{
          switch (s)
	  {
	    case 1:
	    case 3:
	    case 6:
	    case 12:
	    case 24:
	    case 48:
	    case 96:
	    case 192:
	    case 384:
	    case 768:
	    case 1536:
	      s = 0;
	      burst = 2;
	      break;
	    case 117:
	      out[12*i + 11] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 1319:
              out[12*i] ^= 0x01;
	      out[12*i + 1] ^= 0x1;
              s = 0;
	      burst = 2;
              break;
	    case 1193:
	      out[12*i + 1] ^= 1;
	      out[12*i + 2] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 1134:
	      out[12*i + 2] ^= 1;
	      out[12*i + 3] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 567:
	      out[12*i + 3] ^= 1;
	      out[12*i + 4] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 1825:
	      out[12*i + 4] ^= 1;
	      out[12*i + 5] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 1450:
	      out[12*i + 5] ^= 1;
	      out[12*i + 6] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 725:
	      out[12*i + 6] ^= 1;
	      out[12*i + 7] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 1872:
	      out[12*i + 7] ^= 1;
	      out[12*i + 8] ^= 1;
	      s = 0;
	      break;
	    case 936:
	      out[12*i + 8] ^= 1;
	      out[12*i + 9] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 468:
	      out[12*i + 9] ^= 1;
              out[12*i + 10] ^= 1;
	      s = 0;
	      burst = 2;
	      break;
	    case 234:
	      out[12*i + 10] ^= 1;
              out[12*i + 11] ^= 1;
	      s = 0;
	      burst = 2;
	      break;

	    case 398:
	      out[12*i] ^= 1;
	      out[12*i + 2] ^= 1;
              s = 0;
	      burst = 3;
	      break;

	      /* The Golay code can't usually correct these. Here, we guess
	       * the error based on knowledge of the convolutional code
	       * applied before the Golay code.
	       */
	    case 215:
	      fprintf(stderr, "correcting 215\n");
	      s = 0;
	      burst = 8;
	      break;
	    case 430:
	    case 860:
	    case 1720:
	      s = 0;
	      burst = 8;
	      break;
	    case 740:
	      out[12*i] ^= 1;
	      out[12*i + 1] ^= 1;
	      out[12*i + 3] ^= 1;
	      out[12*i + 5] ^= 1;
	      out[12*i + 6] ^= 1;
	      out[12*i + 7] ^= 1;
	      s = 0;
	      burst = 8;
	      break;
	    case 370:
	      out[12*i + 1] ^= 1;
              out[12*i + 2] ^= 1;
              out[12*i + 4] ^= 1;
              out[12*i + 6] ^= 1;
              out[12*i + 7] ^= 1;
              out[12*i + 8] ^= 1;
	      s = 0;
	      burst = 8;
	      break;
	    case 185:
              out[12*i + 2] ^= 1;
              out[12*i + 3] ^= 1;
              out[12*i + 5] ^= 1;
              out[12*i + 7] ^= 1;
              out[12*i + 8] ^= 1;
              out[12*i + 9] ^= 1;
              s = 0;
              burst = 8;
              break;
            case 1638:
	      out[12*i + 3] ^= 1;
              out[12*i + 4] ^= 1;
              out[12*i + 6] ^= 1;
              out[12*i + 8] ^= 1;
              out[12*i + 9] ^= 1;
              out[12*i + 10] ^= 1;
              s = 0;
              burst = 8;
              break;
            case 819:
	      out[12*i + 4] ^= 1;
              out[12*i + 5] ^= 1;
              out[12*i + 7] ^= 1;
              out[12*i + 9] ^= 1;
              out[12*i + 10] ^= 1;
              out[12*i + 11] ^= 1;
              s = 0;
              burst = 8;
              break;
	    case 1955:
	      out[12*i + 5] ^= 1;
              out[12*i + 6] ^= 1;
              out[12*i + 8] ^= 1;
              out[12*i + 10] ^= 1;
              out[12*i + 11] ^= 1;
	      s = 0;
	      burst = 8;
	      break;
	    case 1515:
	      out[12*i + 6] ^= 1;
              out[12*i + 7] ^= 1;
              out[12*i + 9] ^= 1;
              out[12*i + 11] ^= 1;
              s = 0;
	      burst = 8;
	      break;
	    case 1231:
	      out[12*i + 7] ^= 1;
              out[12*i + 8] ^= 1;
              out[12*i + 10] ^= 1;
              s = 0;
	      burst = 8;
	      break;
	    case 1117:
	      out[12*i + 8] ^= 1;
              out[12*i + 9] ^= 1;
              out[12*i + 11] ^= 1;
              s = 0;
	      burst = 8;
	      break;
	    case 1044:
	      out[12*i + 9] ^= 1;
              out[12*i + 10] ^= 1;
              s = 0;
	      burst = 8;
	      break;
	    case 522:
	      out[12*i + 10] ^= 1;
              out[12*i + 11] ^= 1;
              s = 0;
	      burst = 8;
	      break;
	    case 261:
	      out[12*i + 11] ^= 1;
              s = 0;
              burst = 8;
              break;
	      /* Truncated versions of the above bit pattern */
	    case 953:
	      out[12*i] ^= 1;
	      out[12*i + 2] ^= 1;
	      out[12*i + 3] ^= 1;
	      out[12*i + 4] ^= 1;
	      s = 0;
	      burst = 5;
	      break;
	    case 2022:
	      out[12*i + 1] ^= 1;
              out[12*i + 3] ^= 1;
              out[12*i + 4] ^= 1;
              out[12*i + 5] ^= 1;
              s = 0;
              burst = 5;
	      break;
	    default:
	      break;
          }
	}

	if (burst != 0)
        {
	  add_item_tag(0, d_offset+i*12, pmt::intern("burst_length"), pmt::from_long(burst));
	}

	if ((s != 0) || (parity != 0))
        {
          fprintf(stderr, "parity = %d, syndrome = %d\n", parity, s);
          add_item_tag(0, d_offset+i*12, d_parity_error_key, pmt::PMT_T);
	  d_previous_error = 1;
        }
	else if (d_previous_error)
	{
	  add_item_tag(0, d_offset+i*12, d_parity_error_key, pmt::PMT_F);
	  d_previous_error = 0;
	}
      }

      d_offset += noutput_items;
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

