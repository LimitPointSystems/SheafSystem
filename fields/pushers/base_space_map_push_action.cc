
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
/// Implementation for class base_space_map_push_action

#include "SheafSystem/base_space_map_push_action.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/sec_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// =============================================================================
// BASE_SPACE_MAP_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::base_space_map_push_action::
~base_space_map_push_action()
{
  // Preconditions:


  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

void
fields::base_space_map_push_action::
operator()(pullback_map::iterator& xitr,
           block<sec_vd*>& xoutputs,
           block< block<sec_vd_dof_type>* >& xout_dofs)
{
  // Preconditions:

  require(xoutputs.ct() > 0);
  require(xout_dofs.ct() >= xoutputs.ct());
  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_accessible());
  require_for_all(i, 0, xoutputs.ct(), xout_dofs[i]->ub() >= xoutputs[i]->schema().df());

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map_push_action::
initialize(block<sec_vd*>& xoutputs )
{
  // Preconditions:

  require(xoutputs.ct() > 0);
  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_write_accessible());

  // Body:

  // Default version does nothing.

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map_push_action::
finalize(block<sec_vd*>& xoutputs )
{
  // Preconditions:

  require(xoutputs.ct() > 0);
  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_write_accessible());

  // Body:

  // Default version does nothing.

  // Postconditions:


  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

fields::base_space_map_push_action::
base_space_map_push_action()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::base_space_map_push_action::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this

  bool result = dynamic_cast<const base_space_map_push_action*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::base_space_map_push_action*
fields::base_space_map_push_action::
clone() const
{
  base_space_map_push_action* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


fields::base_space_map_push_action&
fields::base_space_map_push_action::
operator=(const base_space_map_push_action& xother)
{

  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit

  return *this;
}

bool
fields::base_space_map_push_action::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

