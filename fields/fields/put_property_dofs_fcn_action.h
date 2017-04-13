
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
/// Interface for class put_property_dofs_fcn_action

#ifndef PUT_PROPERTY_DOFS_FCN_ACTION_H
#define PUT_PROPERTY_DOFS_FCN_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef PUT_PROPERTY_DOFS_ACTION_H
#include "SheafSystem/put_property_dofs_action.h"
#endif

namespace fields
{

///
/// A discretization push action for field_vds::put_property_dofs
/// that uses a client provided function to compute the dofs.
///
class SHEAF_DLL_SPEC put_property_dofs_fcn_action : public put_property_dofs_action
{

  // ===========================================================
  /// @name PUT_PROPERTY_DOFS_FCN_ACTION FACET
  // ===========================================================
  //@{

public:

  // No default constructor.

  ///
  /// Creates an instance using property xproperty and dof function xfcn.
  ///
  put_property_dofs_fcn_action(sec_vd& xproperty,
                               property_dof_function_type xfcn,
                               bool xauto_access);

  // Default memberwise copy constructor will do.

  ///
  /// Destructor
  ///
  virtual ~put_property_dofs_fcn_action();

  ///
  /// The push action.
  ///
  virtual void operator () (const scoped_index& xdisc_id,
                            block<sec_vd_value_type>& xglobal_coords);

  ///
  /// The function for computing the property dofs at
  /// given global coordinates.
  ///
  property_dof_function_type dof_function();


private:

  ///
  /// The function for computing the property dofs
  /// at given global coordinates.
  ///
  property_dof_function_type _dof_function;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

} // namespace fields

#endif // ifndef PUT_PROPERTY_DOFS_FCN_ACTION_H
