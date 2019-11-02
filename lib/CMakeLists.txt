# Copyright 2011,2012,2016 Free Software Foundation, Inc.
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

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND c4fm_sources
    c4fm_soft_decision_fc_impl.cc
    bernoulli_source_b_impl.cc
    golay_encoder_bb_impl.cc
    parity_check_bb_impl.cc
    discard_parity_errors_bb_impl.cc
    golay_decoder_bb_impl.cc
    frame_sync_bb_impl.cc
    quaternary_slicer_cb_impl.cc
    frame_sync_cc_impl.cc
    crc16_bb_impl.cc
    whiten_ff_impl.cc
    pad_missing_bb_impl.cc
    crc16_encode_bb_impl.cc
    correlate_access_code_tag_cc_impl.cc
    dupe_skipped_cc_impl.cc
    burst_length_bb_impl.cc
    type_demux_cc_impl.cc
    tags_to_stream_cf_impl.cc
    ratio_combiner_ff_impl.cc
    tag_to_message_f_impl.cc
    tag_to_message_c_impl.cc
    maximal_ratio_impl.cc
    splitter_cc_impl.cc
    frequency_locked_loop_ff_impl.cc
)

set(c4fm_sources "${c4fm_sources}" PARENT_SCOPE)
if(NOT c4fm_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT c4fm_sources)

add_library(gnuradio-c4fm SHARED ${c4fm_sources})
target_link_libraries(gnuradio-c4fm ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-c4fm PROPERTIES DEFINE_SYMBOL "gnuradio_c4fm_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-c4fm PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-c4fm RUNTIME_COMPONENT "c4fm_runtime" DEVEL_COMPONENT "c4fm_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_c4fm_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_c4fm.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_c4fm.cc
)

add_executable(test-c4fm ${test_c4fm_sources})

target_link_libraries(
  test-c4fm
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-c4fm
)

GR_ADD_TEST(test_c4fm test-c4fm)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

