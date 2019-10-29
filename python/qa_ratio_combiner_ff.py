#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 <+YOU OR YOUR COMPANY+>.
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

class qa_ratio_combiner_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        src_data0 = (1, 1, -1, -1)
        src_data1 = (1, -1, 1, -1)
        expected_result = (1, 0, 0, -1)
        src0 = blocks.vector_source_f(src_data0)
        src1 = blocks.vector_source_f(src_data1)
        combiner = c4fm.ratio_combiner_ff(45)
        dst = blocks.vector_sink_f()
        self.tb.connect(src0, (combiner, 0))
        self.tb.connect(src1, (combiner, 1))
        self.tb.connect(combiner, dst)
        self.tb.run ()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 4)
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_ratio_combiner_ff, "qa_ratio_combiner_ff.xml")
