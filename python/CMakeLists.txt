# Copyright 2011 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-c4fm
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

########################################################################
# Include python install macros
########################################################################
include(GrPython)
if(NOT PYTHONINTERP_FOUND)
    return()
endif()

########################################################################
# Install python sources
########################################################################
GR_PYTHON_INSTALL(
    FILES
    __init__.py
    DESTINATION ${GR_PYTHON_DIR}/c4fm
)

########################################################################
# Handle the unit tests
########################################################################
include(GrTest)

set(GR_TEST_TARGET_DEPS gnuradio-c4fm)
set(GR_TEST_PYTHON_DIRS ${CMAKE_BINARY_DIR}/swig)
GR_ADD_TEST(qa_bernoulli_source_b ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_bernoulli_source_b.py)
GR_ADD_TEST(qa_quaternary_slicer_cb ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_quaternary_slicer_cb.py)
GR_ADD_TEST(qa_c4fm_soft_decision_fc ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_c4fm_soft_decision_fc.py)
GR_ADD_TEST(qa_correlate_access_code_tag_cc ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_correlate_access_code_tag_cc_.py)
GR_ADD_TEST(qa_crc16_encode_bb ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_crc16_encode_bb.py)
GR_ADD_TEST(qa_golay_encoder_bb ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_golay_encoder_bb.py)
GR_ADD_TEST(qa_type_demux_cc ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_type_demux_cc.py)
GR_ADD_TEST(qa_crc16_decode_bb ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_crc16_decode_bb.py)
GR_ADD_TEST(qa_complex_to_interleaved_float ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_complex_to_interleaved_float.py)
GR_ADD_TEST(qa_frequency_locked_loop_ff ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_frequency_locked_loop_ff.py)
GR_ADD_TEST(qa_time_transitions_bf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_time_transitions_bf.py)
GR_ADD_TEST(qa_hdlc_unstuff_bb ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_hdlc_unstuff_bb.py)
GR_ADD_TEST(qa_hdlc_parse_addr ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_hdlc_parse_addr.py)
GR_ADD_TEST(qa_sign_scrambler_ff ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_sign_scrambler_ff.py)
GR_ADD_TEST(qa_pad_missing_bb ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_pad_missing_bb.py)
GR_ADD_TEST(qa_interleaved_float_to_complex ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_interleaved_float_to_complex.py)
GR_ADD_TEST(qa_c4fm_reencode_soft_decision_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_c4fm_reencode_soft_decision_cf.py)
