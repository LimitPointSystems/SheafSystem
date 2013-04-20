

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class average_push_action

#ifndef AVERAGE_PUSH_ACTION_H
#define AVERAGE_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_PUSHER_PUSH_ACTION_H
#include "section_pusher_push_action.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace fiber_bundle
{
class sec_vd;
}

namespace fields
{

///
/// Functor to compute the dofs at a destination discretization point
/// by averaging the source values form all branches containing the point.
///
class SHEAF_DLL_SPEC average_push_action : public section_pusher_push_action
{

  // =============================================================================
  /// @name AVERAGE_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Creates an instance with dst_df() == xdst_df.
  ///
  average_push_action(int xdst_df);

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~average_push_action();

protected:

  ///
  /// Buffer for destination dofs.
  ///
  block<sec_vd_dof_type> _dst_dofs;

  ///
  /// Number of branches accumulated for each discretization member.
  ///
  block<int> _branch_cts;

  ///
  /// Discretization sequence id space for destination section.
  ///
  index_space_handle* _disc_seq_id_space;

  ///
  /// Discretization count of destination.
  ///
  int _disc_ct;

private:

  ///
  /// Default constructor; disabled
  ///
  average_push_action() {};

  //@}


  // =============================================================================
  /// @name SECTION_PUSHER_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Computes xdst_dofs using xitr and the dofs already in xdst, as needed.
  ///
  virtual void operator()(pullback_map::iterator& xitr,
                          sec_vd& xdst,
                          block<sec_vd_dof_type>& xdst_dofs);

  ///
  /// Initializes xdst as needed.
  ///
  virtual void initialize(sec_vd& xdst);

  ///
  /// Finalizes xdst as needed.
  ///
  virtual void finalize(sec_vd& xdst);


  //@}


  // =============================================================================
  /// @name ANY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual average_push_action* clone() const;

  ///
  /// Assignment operator
  ///
  virtual average_push_action& operator=(const section_pusher_push_action& xother);

  ///
  /// Assignment operator
  ///
  average_push_action& operator=(const average_push_action& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
  
} // namespace fields

#endif // ifndef AVERAGE_PUSH_ACTION_H
