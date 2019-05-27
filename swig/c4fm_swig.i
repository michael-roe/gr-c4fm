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
