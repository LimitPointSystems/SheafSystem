
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
/// Interface for class put_property_dofs_action

#ifndef PUT_PROPERTY_DOFS_ACTION_H
#define PUT_PROPERTY_DOFS_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef DISCRETIZATION_PUSH_ACTION_H
#include "SheafSystem/discretization_push_action.h"
#endif

#ifndef BLOCK_H
#include "SheafSystem/block.h"
#endif

namespace fiber_bundle
{
class sec_vd;
}

namespace fields
{

///
/// An abstract discretization push action for field_vds::put_property_dofs.
///
class SHEAF_DLL_SPEC put_property_dofs_action : public discretization_push_action
{

  // ===========================================================
  /// @name PUT_PROPERTY_DOFS_ACTION FACET
  // ===========================================================
  //@{

public:

  // No default constructor.

  ///
  /// Creates an instance using property xproperty.
  ///
  put_property_dofs_action(sec_vd& xproperty, bool xauto_access);

  // Default memberwise copy constructor will do.

  ///
  /// Destructor
  ///
  virtual ~put_property_dofs_action();

  ///
  /// The property section being acted on.
  ///
  sec_vd& property();

protected:

  ///
  /// The property section being acted on.
  ///
  sec_vd& _property;

  ///
  /// Buffer for property dofs.
  ///
  block<sec_vd_dof_type> _dofs;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace fields

#endif // ifndef PUT_PROPERTY_DOFS_ACTION_H
