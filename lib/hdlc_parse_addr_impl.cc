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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ctype.h>

#include <gnuradio/io_signature.h>
#include "hdlc_parse_addr_impl.h"

namespace gr {
  namespace c4fm {

    hdlc_parse_addr::sptr
    hdlc_parse_addr::make()
    {
      return gnuradio::get_initial_sptr
        (new hdlc_parse_addr_impl());
    }


    void hdlc_parse_addr_impl::rx(pmt::pmt_t msg)
    {
      pmt::pmt_t blob;
      pmt::pmt_t dict;
      std::string addr_str;
      unsigned char *ptr;
      size_t offset;
      unsigned char addr[23];
      int i;
      int len;

      if (pmt::is_pair(msg))
      {
        blob = pmt::cdr(msg);
	offset = 0;
	ptr = (unsigned char *) uniform_vector_elements(blob, offset);
	len = pmt::blob_length(blob);
	if (len > 21)
        {
          len = 21;
	}
        if (ptr)
	  memcpy(addr, ptr, len);
	if (1)
	{
	  len = 1;
	  while ((len < 21) && ((addr[len - 1] & 0x1) == 0))
          {
            len++;
	  }
	  /* fprintf(stderr, "addr len = %d\n", len); */
	  for (i=0; i<len; i++)
          {
	    addr[i] = addr[i] >> 1;
	    if (!isprint(addr[i]))
	    {
	      addr[i] = '?';
	    }
	  }
	  /* fprintf(stderr, "SSID %02x %02x\n", addr[6], addr[13]); */
	  addr[6] = ' ';
	  i = 6;
	  while ((i >=0) && (addr[i] == ' '))
	  {
	    addr[i] = 0;
	    i--;
	  }
	  addr[13] = ' ';
	  i = 13;
	  while ((i >= 7) && (addr[i] == ' '))
	  {
	    addr[i] = 0;
	    i--;
	  }
	  addr[20] = 0;
	  i = 20;
	  while ((i >= 14) && (addr[i] == ' '))
	  {
	    addr[i] = 0;
	    i--;
	  }
	  addr[len] = '\0';
	  dict = pmt::make_dict();
	  dict = pmt::dict_add(dict, pmt::intern("dst_addr"), pmt::string_to_symbol((char *) addr));
	  dict = pmt::dict_add(dict, pmt::intern("src_addr"), pmt::string_to_symbol((char *) addr + 7));
	  if (len > 14)
	  {
	    dict = pmt::dict_add(dict, pmt::intern("via_addr"), pmt::string_to_symbol((char *) addr + 14));
	  }
	  message_port_pub(d_port_out, pmt::cons(dict, blob));
	}
      }
      else
      {
        fprintf(stderr, "msg is not a pair\n");
      }
    }

    /*
     * The private constructor
     */
    hdlc_parse_addr_impl::hdlc_parse_addr_impl()
      : gr::block("hdlc_parse_addr",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
      d_port_in = pmt::mp("in");
      message_port_register_in(d_port_in);
      set_msg_handler(d_port_in,
        boost::bind(&hdlc_parse_addr_impl::rx, this, _1));
      d_port_out = pmt::mp("out");
       message_port_register_out(d_port_out);
    }

    /*
     * Our virtual destructor.
     */
    hdlc_parse_addr_impl::~hdlc_parse_addr_impl()
    {
    }

    void
    hdlc_parse_addr_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    hdlc_parse_addr_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

