/* -*- c++ -*- */

#define C4FM_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "c4fm_swig_doc.i"

%{
#include "c4fm/bernoulli_source_b.h"
#include "c4fm/quaternary_slicer_cb.h"
#include "c4fm/c4fm_soft_decision_fc.h"
#include "c4fm/correlate_access_code_tag_cc.h"
#include "c4fm/crc16_encode_bb.h"
#include "c4fm/golay_encoder_bb.h"
#include "c4fm/type_demux_cc.h"
%}

%include "c4fm/bernoulli_source_b.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, bernoulli_source_b);
%include "c4fm/quaternary_slicer_cb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, quaternary_slicer_cb);
%include "c4fm/c4fm_soft_decision_fc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, c4fm_soft_decision_fc);
%include "c4fm/correlate_access_code_tag_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, correlate_access_code_tag_cc);
%include "c4fm/crc16_encode_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, crc16_encode_bb);
%include "c4fm/golay_encoder_bb.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, golay_encoder_bb);
%include "c4fm/type_demux_cc.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, type_demux_cc);
