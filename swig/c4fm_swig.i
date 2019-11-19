/* -*- c++ -*- */

#define C4FM_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "c4fm_swig_doc.i"

%{
#include "c4fm/bernoulli_source_b.h"
%}

%include "c4fm/bernoulli_source_b.h"
GR_SWIG_BLOCK_MAGIC2(c4fm, bernoulli_source_b);
