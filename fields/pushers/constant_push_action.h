
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
/// Interface for class constant_push_action

#ifndef COM_LIMITPOINT_FIELDS_CONSTANT_PUSH_ACTION_H
#define COM_LIMITPOINT_FIELDS_CONSTANT_PUSH_ACTION_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_SECTION_PUSHER_PUSH_ACTION_H
#include "ComLimitPoint/fields/section_pusher_push_action.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

namespace fields
{

///
/// Abstract functor to compute the dofs at a destination discretization point.
///
class SHEAF_DLL_SPEC constant_push_action : public section_pusher_push_action
{

  // =============================================================================
  /// @name CONSTANT_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Creates an instance with dst_df() == xdst_df and dst_dofs() == xdst_dofs.
  ///
  constant_push_action(int xdst_df, const block<sec_vd_dof_type>& xdst_dofs);

  ///
  /// Creates an instance with dst_df() == xdst_df and dst_dofs()[i] == xdst_dof.
  ///
  constant_push_action(int xdst_df, sec_vd_dof_type xdst_dof);

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~constant_push_action();

  ///
  /// Constant value for destination dofs.
  ///
  block<sec_vd_dof_type>& dst_dofs();

protected:

  ///
  /// Constant value for destination dofs.
  ///
  block<sec_vd_dof_type> _dst_dofs;

private:

  ///
  /// Default constructor; disabled
  ///
  constant_push_action() {};

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
  virtual bool is_ancestor_of(const any*xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual constant_push_action* clone() const;

  ///
  /// Assignment operator
  ///
  virtual constant_push_action& operator=(const section_pusher_push_action& xother);

  ///
  /// Assignment operator
  ///
  constant_push_action& operator=(const constant_push_action& xother);

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

#endif // ifndef COM_LIMITPOINT_FIELDS_CONSTANT_PUSH_ACTION_H
