
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
/// Interface for class copy_base_space_map_push_action

#ifndef COPY_BASE_SPACE_MAP_PUSH_ACTION_H
#define COPY_BASE_SPACE_MAP_PUSH_ACTION_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_MAP_PUSH_ACTION_H
#include "base_space_map_push_action.h"
#endif

namespace fields
{

///
/// Functor to compute the dofs at a destination discretization point
/// by copying the source value to the dst dofs.
///
class SHEAF_DLL_SPEC copy_base_space_map_push_action : public base_space_map_push_action
{

  // =============================================================================
  /// @name COPY_BASE_SPACE_MAP_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  copy_base_space_map_push_action();

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~copy_base_space_map_push_action();

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
  virtual copy_base_space_map_push_action* clone() const;

  ///
  /// Assignment operator
  ///
  virtual copy_base_space_map_push_action& operator=(const base_space_map_push_action& xother);

  ///
  /// Assignment operator.
  ///
  copy_base_space_map_push_action& operator=(const copy_base_space_map_push_action& xother);

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

#endif // ifndef COPY_BASE_SPACE_MAP_PUSH_ACTION_H
