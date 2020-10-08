#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 Michael Roe.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import c4fm_swig as c4fm

class qa_interleaved_float_to_complex(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        # set up fg
        src_data = (1, 2, 3, 4)
        expected_result = (1+2j,3+4j);
        src = blocks.vector_source_f(src_data)
        inter = c4fm.interleaved_float_to_complex()
        dst = blocks.vector_sink_c()
        self.tb.connect(src, inter, dst)
        self.tb.run()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_interleaved_float_to_complex)
