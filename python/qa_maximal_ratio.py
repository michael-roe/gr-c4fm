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
import time
import pmt
import c4fm_swig as c4fm

class qa_maximal_ratio (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        msg = pmt.cons(pmt.intern("snr"), pmt.from_double(20.0))
        src0 = blocks.message_strobe(msg, 500)
        src1 = blocks.message_strobe(msg, 500)
        ratio = c4fm.maximal_ratio(1.0)
        dst = blocks.message_debug()
        self.tb.msg_connect(src0, "strobe", ratio, "in0")
        self.tb.msg_connect(src1, "strobe", ratio, "in1")
        self.tb.msg_connect(ratio, "out", dst, "store")
        self.tb.start()
        time.sleep(1)
        self.tb.stop()
        self.tb.wait()
        rec_msg = dst.get_message(1)
        self.assertTrue(pmt.eqv(pmt.car(rec_msg), pmt.intern("angle")))
        self.assertAlmostEqual(pmt.to_double(pmt.cdr(rec_msg)), 45.0)

if __name__ == '__main__':
    gr_unittest.run(qa_maximal_ratio, "qa_maximal_ratio.xml")
