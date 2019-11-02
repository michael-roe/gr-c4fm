/* -*- c++ -*- */

#define C4FM_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "c4fm_swig_doc.i"

%{
#include "c4fm/c4fm_soft_decision_fc.h"
#include "c4fm/bernoulli_source_b.h"
#include "c4fm/golay_encoder_bb.h"
#include "c4fm/parity_check_bb.h"
#include "c4fm/discard_parity_errors_bb.h"
#include "c4fm/golay_decoder_bb.h"
#include "c4fm/frame_sync_bb.h"
#include "c4fm/quaternary_slicer_cb.h"
#include "c4fm/frame_sync_cc.h"
#include "c4fm/crc16_bb.h"
#include "c4fm/whiten_ff.h"
#include "c4fm/pad_missing_bb.h"
#include "c4fm/crc16_encode_bb.h"
#include "c4fm/correlate_access_code_tag_cc.h"
#include "c4fm/dupe_skipped_cc.h"
#include "c4fm/burst_length_bb.h"
#include "c4fm/type_demux_cc.h"
#include "c4fm/tags_to_stream_cf.h"
#include "c4fm/ratio_combiner_ff.h"
#include "c4fm/tag_to_message_f.h"
#include "c4fm/tag_to_message_c.h"
#include "c4fm/maximal_ratio.h"
#include "c4fm/splitter_cc.h"
#include "c4fm/frequency_locked_loop_ff.h"
%}


%include "c4fm/c4fm_soft_decision_fc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, c4fm_soft_decision_fc);
%include "c4fm/bernoulli_source_b.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, bernoulli_source_b);
%include "c4fm/golay_encoder_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, golay_encoder_bb);
%include "c4fm/parity_check_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, parity_check_bb);
%include "c4fm/discard_parity_errors_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, discard_parity_errors_bb);
%include "c4fm/golay_decoder_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, golay_decoder_bb);
%include "c4fm/frame_sync_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, frame_sync_bb);
%include "c4fm/quaternary_slicer_cb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, quaternary_slicer_cb);
%include "c4fm/frame_sync_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, frame_sync_cc);
%include "c4fm/crc16_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, crc16_bb);
%include "c4fm/whiten_ff.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, whiten_ff);
%include "c4fm/pad_missing_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, pad_missing_bb);
%include "c4fm/crc16_encode_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, crc16_encode_bb);
%include "c4fm/correlate_access_code_tag_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, correlate_access_code_tag_cc);
%include "c4fm/dupe_skipped_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, dupe_skipped_cc);
%include "c4fm/burst_length_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, burst_length_bb);
%include "c4fm/type_demux_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, type_demux_cc);
%include "c4fm/tags_to_stream_cf.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, tags_to_stream_cf);
%include "c4fm/ratio_combiner_ff.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, ratio_combiner_ff);
%include "c4fm/tag_to_message_f.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, tag_to_message_f);
%include "c4fm/tag_to_message_c.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, tag_to_message_c);
%include "c4fm/maximal_ratio.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, maximal_ratio);
%include "c4fm/splitter_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, splitter_cc);
%include "c4fm/frequency_locked_loop_ff.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, frequency_locked_loop_ff);
