
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class constant_base_space_map_push_action

#ifndef CONSTANT_BASE_SPACE_MAP_PUSH_ACTION_H
#define CONSTANT_BASE_SPACE_MAP_PUSH_ACTION_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_MAP_PUSH_ACTION_H
#include "base_space_map_push_action.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
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
