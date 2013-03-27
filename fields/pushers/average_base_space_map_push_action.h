// $RCSfile: average_base_space_map_push_action.h,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:26 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class average_base_space_map_push_action

#ifndef AVERAGE_BASE_SPACE_MAP_PUSH_ACTION_H
#define AVERAGE_BASE_SPACE_MAP_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_MAP_PUSH_ACTION_H
#include "base_space_map_push_action.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace sheaf
{
class mutable_index_space_handle;
}

namespace fields
{

using namespace sheaf;

///
/// Functor to compute the dofs at a output discretization point
/// by averaging the input values from all branches containing the point.
///
class SHEAF_DLL_SPEC average_base_space_map_push_action : public base_space_map_push_action
{

  // =============================================================================
  /// @name AVERAGE_BASE_SPACE_MAP_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  average_base_space_map_push_action();

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~average_base_space_map_push_action();

protected:

  ///
  /// Discretization id space shared by all output sections.
  ///
  mutable_index_space_handle* _disc_id_space;

  ///
  /// Number of branches accumulated for each discretization member.
  ///
  block<int> _branch_cts;

  ///
  /// Buffer for output dofs.
  ///
  block< block<sec_vd_dof_type> > _out_dofs;

  //@}


  // =============================================================================
  /// @name BASE_SPACE_MAP_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Computes xout_dofs using xitr and the dofs already in xoutputs, as needed.
  ///
  virtual void operator()(pullback_map::iterator& xitr,
                          block<sec_vd*>& xoutputs,
                          block< block<sec_vd_dof_type>* >& xout_dofs);

  ///
  /// Initializes outputs as needed.
  ///
  virtual void initialize(block<sec_vd*>& xoutputs);

  ///
  /// Finalizes outputs as needed.
  ///
  virtual void finalize(block<sec_vd*>& xoutputs);

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
  virtual average_base_space_map_push_action* clone() const;

  ///
  /// Assignment operator
  ///
  virtual average_base_space_map_push_action& operator=(const base_space_map_push_action& xother);

  ///
  /// Assignment operator
  ///
  average_base_space_map_push_action& operator=(const average_base_space_map_push_action& xother);

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

#endif // ifndef AVERAGE_BASE_SPACE_MAP_PUSH_ACTION_H
