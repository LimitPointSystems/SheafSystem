
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
/// Interface for class print_property_dofs_action

#ifndef PRINT_PROPERTY_DOFS_ACTION_H
#define PRINT_PROPERTY_DOFS_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DISCRETIZATION_PUSH_ACTION_H
#include "discretization_push_action.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace sheaf
{
class index_space_handle;
}

namespace fiber_bundle
{
class sec_vd;
}

namespace fields
{

using namespace fiber_bundle;
using namespace sheaf;

///
/// A discretization push action for field_vds::print_property_dofs.
///
class SHEAF_DLL_SPEC print_property_dofs_action : public discretization_push_action
{

  // ===========================================================
  /// @name PRINT_PROPERTY_DOFS_ACTION FACET
  // ===========================================================
  //@{

public:

  // No default constructor.

  ///
  /// Creates an instance using global coordinates xdomain_coords
  /// and pullback map xmap.
  ///
  print_property_dofs_action(sec_vd& xproperty,
                             property_dof_function_type xfcn,
                             bool xzero_specified = false);

  // Default memberwise copy constructor will do.

  ///
  /// Destructor
  ///
  virtual ~print_property_dofs_action();

  ///
  /// The push action.
  ///
  virtual void operator () (const scoped_index& xdisc_id,
                            block<sec_vd_value_type>& xglobal_coords);

  ///
  /// The property section being acted on.
  ///
  sec_vd& property();

  ///
  /// The function for computing the property dofs at
  /// given global coordinates.
  ///
  property_dof_function_type dof_function();


private:

  ///
  /// The property section being acted on.
  ///
  sec_vd& _property;

  ///
  /// Buffer for property dofs.
  ///
  block<sec_vd_dof_type> _dofs;

  ///
  /// Buffer for property dofs specified by dof function.
  ///
  block<sec_vd_dof_type> _specified_dofs;

  ///
  /// The function for computing the property dofs
  /// at given global coordinates.
  ///
  property_dof_function_type _dof_function;

  ///
  /// True if 0.0 should be treated as the specified value
  /// whenever it is the value of the property.
  ///
  bool _zero_specified;

  ///
  /// The sequence id map for the property discretization.
  ///
  index_space_handle* _seq_id_space;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace fields

#endif // ifndef PRINT_PROPERTY_DOFS_ACTION_H
