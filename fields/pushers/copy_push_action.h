// $RCSfile: copy_push_action.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:26 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class copy_push_action

#ifndef COPY_PUSH_ACTION_H
#define COPY_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_PUSHER_PUSH_ACTION_H
#include "section_pusher_push_action.h"
#endif

namespace fields
{

///
/// Functor to compute the dofs at a destination discretization point
/// by copying the source value to the dst dofs.
///
class SHEAF_DLL_SPEC copy_push_action : public section_pusher_push_action
{

  // =============================================================================
  /// @name COPY_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Creates an instance with dst_df() == xdst_df.
  ///
  copy_push_action(int xdst_df);

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~copy_push_action();


private:

  ///
  /// Default constructor; disabled
  ///
  copy_push_action() {};

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
  virtual copy_push_action* clone() const;

  ///
  /// Assignment operator
  ///
  virtual copy_push_action& operator=(const section_pusher_push_action& xother);

  ///
  /// Assignment operator
  ///
  copy_push_action& operator=(const copy_push_action& xother);

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

#endif // ifndef COPY_PUSH_ACTION_H
