# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND c4fm_python_files
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(c4fm 
   ../..
   gr::c4fm
   "${c4fm_python_files}")

install(TARGETS c4fm_python DESTINATION ${GR_PYTHON_DIR}/c4fm COMPONENT pythonapi)
