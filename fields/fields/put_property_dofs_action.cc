
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
/// Implementation for class put_property_dofs_action

#include "ComLimitPoint/fields/put_property_dofs_action.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// PUT_PROPERTY_DOFS_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::put_property_dofs_action::
put_property_dofs_action(sec_vd& xproperty, bool xauto_access)
    : _property(xproperty)
{
  // Preconditions:

  require(xauto_access || xproperty.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xproperty.get_read_access();
  }


  /// @issue assuming binary schema, one dof per component.

  int ldf = xproperty.schema().df();
  _dofs.reserve(ldf);
  _dofs.set_ct(ldf);

  if(xauto_access)
  {
    xproperty.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

fields::put_property_dofs_action::
~put_property_dofs_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::sec_vd&
fields::put_property_dofs_action::
property()
{
  // Preconditions:


  // Body:

  sec_vd& result = _property;

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
