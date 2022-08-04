#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2022 Michael Roe.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from gnuradio import gr, gr_unittest
# from gnuradio import blocks
try:
  from gnuradio.c4fm import markov_source_b
  from gnuradio import blocks
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.c4fm import markov_source_b
    from gnuradio import blocks

class qa_markov_source_b(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        instance = markov_source_b(0.25, 0.75, 0)

    def test_001_descriptive_test_name(self):
        rng = markov_source_b(0.25, 0.75, 0)
        head = blocks.head(gr.sizeof_char, 20000)
        convert = blocks.uchar_to_float()
        integrate = blocks.integrate_ff(10000)
        dst = blocks.vector_sink_f()
        self.tb.connect(rng, head)
        self.tb.connect(head, convert)
        self.tb.connect(convert, integrate)
        self.tb.connect(integrate, dst)
        self.tb.run ()
        # check data
        # The result is a random variable of mean
        # 10000*0.5*0.25/(0.25+0.75) = 1250
        # This test is statistical: there is a small probablity that it will
        # fail.
        self.assertLess(dst.data()[0], 1300.0)
        self.assertGreater(dst.data()[0], 1200.0)
        self.assertLess(dst.data()[1], 1300.0)
        self.assertGreater(dst.data()[1], 1200.0)

if __name__ == '__main__':
    gr_unittest.run(qa_markov_source_b)
