/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(markov_source_b.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(1131634337310ca98cdb4d83916acc63)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/c4fm/markov_source_b.h>
// pydoc.h is automatically generated in the build directory
#include <markov_source_b_pydoc.h>

void bind_markov_source_b(py::module& m)
{

    using markov_source_b    = gr::c4fm::markov_source_b;


    py::class_<markov_source_b, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<markov_source_b>>(m, "markov_source_b", D(markov_source_b))

        .def(py::init(&markov_source_b::make),
           D(markov_source_b,make)
        )
        



        ;




}








