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
#include "tag_to_message_b_impl.h"

namespace gr {
  namespace c4fm {

    tag_to_message_b::sptr
    tag_to_message_b::make(const std::string &key)
    {
      return gnuradio::get_initial_sptr
        (new tag_to_message_b_impl(key));
    }

    /*
     * The private constructor
     */
    tag_to_message_b_impl::tag_to_message_b_impl(const std::string &key)
      : gr::sync_block("tag_to_message_b",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(0, 0, 0))
    {
      d_tag_key = pmt::intern(key.c_str());
      d_port = pmt::mp("out");
      message_port_register_out(d_port);
    }

    /*
     * Our virtual destructor.
     */
    tag_to_message_b_impl::~tag_to_message_b_impl()
    {
    }

    int
    tag_to_message_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      std::vector<tag_t> tags;
      int i;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+noutput_items);

      for (i=0; i<tags.size(); i++)
      {
        if (pmt::equal(tags[i].key, d_tag_key))
        {
          message_port_pub(d_port, pmt::cons(d_tag_key, tags[i].value));
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace c4fm */
} /* namespace gr */

