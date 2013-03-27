// $RCSfile: constant_base_space_map_push_action.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:26 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class constant_base_space_map_push_action

#ifndef CONSTANT_BASE_SPACE_MAP_PUSH_ACTION_H
#define CONSTANT_BASE_SPACE_MAP_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_MAP_PUSH_ACTION_H
#include "base_space_map_push_action.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace fields
{

///
/// Abstract functor to compute the dofs at a destination discretization point.
///
class SHEAF_DLL_SPEC constant_base_space_map_push_action : public base_space_map_push_action
{

  // =============================================================================
  /// @name CONSTANT_BASE_SPACE_MAP_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Default constructor; creates an instance with out_dofs.ct() == 0.
  ///
  constant_base_space_map_push_action();

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~constant_base_space_map_push_action();

  ///
  /// Constant values for output dofs.
  ///
  block< block<sec_vd_dof_type> >& out_dofs();

protected:

  ///
  /// Constant value for destination dofs.
  ///
  block< block<sec_vd_dof_type> > _out_dofs;

  //@}

  // =============================================================================
  /// @name BASE_SPACE_MAP_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Sets xout_dofs to constant out_dofs().
  ///
  virtual void operator()(pullback_map::iterator& xitr,
                          block<sec_vd*>& xoutputs,
                          block< block<sec_vd_dof_type>* >& xout_dofs);

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
  virtual constant_base_space_map_push_action* clone() const;

  ///
  /// Assignment operator
  ///
  virtual constant_base_space_map_push_action& operator=(const base_space_map_push_action& xother);

  ///
  /// Assignment operator
  ///
  constant_base_space_map_push_action& operator=(const constant_base_space_map_push_action& xother);

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

#endif // ifndef CONSTANT_BASE_SPACE_MAP_PUSH_ACTION_H
