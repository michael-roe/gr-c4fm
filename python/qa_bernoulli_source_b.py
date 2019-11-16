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

class qa_bernoulli_source_b (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        expected_result = (250.0, 250.0)
        rng = c4fm.bernoulli_source_b(0.25, 0)
        head = blocks.head(gr.sizeof_char, 2000)
        convert = blocks.uchar_to_float()
        integrate = blocks.integrate_ff(1000)
        dst = blocks.vector_sink_f()
        self.tb.connect(rng, head)
        self.tb.connect(head, convert)
        self.tb.connect(convert, integrate)
        self.tb.connect(integrate, dst)
        self.tb.run ()
        # check data
        # The result is a random variable of mean 0.25*1000 = 250
        # This test is statistical: there is a small probablity that it will fail
        self.assertLess(dst.data()[0], 350.0) 
        self.assertGreater(dst.data()[0], 150.0)
        self.assertLess(dst.data()[1], 350.0) 
        self.assertGreater(dst.data()[1], 150.0)

        # self.assertFloatTuplesAlmostEqual(expected_result, dst.data(), 1)


if __name__ == '__main__':
    gr_unittest.run(qa_bernoulli_source_b, "qa_bernoulli_source_b.xml")
