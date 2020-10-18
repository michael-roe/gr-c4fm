/* -*- c++ -*- */
/*
 * Copyright 2020 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_C4FM_C4FM_REENCODE_SOFT_DECISION_CF_H
#define INCLUDED_C4FM_C4FM_REENCODE_SOFT_DECISION_CF_H

#include <c4fm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace c4fm {

    /*!
     * \brief <+description of block+>
     * \ingroup c4fm
     *
     */
    class C4FM_API c4fm_reencode_soft_decision_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<c4fm_reencode_soft_decision_cf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of c4fm::c4fm_reencode_soft_decision_cf.
       *
       * To avoid accidental use of raw pointers, c4fm::c4fm_reencode_soft_decision_cf's
       * constructor is in a private implementation
       * class. c4fm::c4fm_reencode_soft_decision_cf::make is the public interface for
       * creating new instances.
       */
      static sptr make(float gain);
    };

  } // namespace c4fm
} // namespace gr

#endif /* INCLUDED_C4FM_C4FM_REENCODE_SOFT_DECISION_CF_H */

