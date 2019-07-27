# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

install(FILES
    c4fm_c4fm_soft_decision_fc.xml
    c4fm_bernoulli_source_b.xml
    c4fm_golay_encoder_bb.xml
    c4fm_parity_check_bb.xml
    c4fm_discard_parity_errors_bb.xml
    c4fm_golay_decoder_bb.xml
    c4fm_frame_sync_bb.xml
    c4fm_quaternary_slicer_cb.xml
    c4fm_frame_sync_cc.xml
    c4fm_crc16_bb.xml
    c4fm_whiten_ff.xml
    c4fm_pad_missing_bb.xml
    c4fm_crc16_encode_bb.xml
    c4fm_correlate_access_code_tag_cc.xml
    c4fm_dupe_skipped_cc.xml
    c4fm_burst_length_bb.xml
    c4fm_type_demux_cc.xml DESTINATION share/gnuradio/grc/blocks
)
