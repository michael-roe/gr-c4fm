#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 Michael Roe.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import c4fm_swig as c4fm

class qa_crc16_encode_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        src_data = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    )
        expected_result = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1,
                )
        src = blocks.vector_source_b(src_data)
        tagger = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, 16, "packet_len")
        crc = c4fm.crc16_encode_bb("packet_len", 0)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, tagger, crc)
        self.tb.connect(crc, dst)
        self.tb.run ()
        result_data = dst.data()
        self.assertEqual(result_data, expected_result)
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_crc16_encode_bb)
