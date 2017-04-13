
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
/// Implementation for class discretization_push_action

#include "SheafSystem/discretization_push_action.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// DISCRETIZATION_PUSH_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::discretization_push_action::
~discretization_push_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


void
fields::discretization_push_action::
operator()(const scoped_index& xmbr_id, block<sec_vd_value_type>& xglobal_coords)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fields::discretization_push_action::
discretization_push_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

