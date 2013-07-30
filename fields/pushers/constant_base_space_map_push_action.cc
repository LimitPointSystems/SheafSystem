

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class constant_base_space_map_push_action

#include "constant_base_space_map_push_action.h"

#include "assert_contract.h"
#include "block.impl.h"
#include "error_message.h"
#include "sec_vd.h"

using namespace fields; // Workaround for MS C++ bug.


// =============================================================================
// CONSTANT_BASE_SPACE_MAP_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::constant_base_space_map_push_action::
constant_base_space_map_push_action()
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(out_dofs().ct() == 0);

  // Exit:

  return;
}

fields::constant_base_space_map_push_action::
~constant_base_space_map_push_action()
{
  // Preconditions:


  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

sheaf::block< sheaf::block<fiber_bundle::sec_vd_dof_type> >&
fields::constant_base_space_map_push_action::
out_dofs()
{
  return _out_dofs;
}


// =============================================================================
// BASE_SPACE_MAP_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::constant_base_space_map_push_action::
operator()(pullback_map::iterator& xitr,
           block<sec_vd*>& xoutputs,
           block< block<sec_vd_dof_type>* >& xout_dofs)
{
  // Preconditions:

  require(xoutputs.ct() > 0);
  require(xout_dofs.ct() >= xoutputs.ct());
  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_accessible());
  require_for_all(i, 0, xoutputs.ct(),
                  xout_dofs[i]->ub() >= xoutputs[i]->schema().df());

  // Body:

  for(int i=0; i<xout_dofs.ct(); ++i)
  {
    xout_dofs[i]->set_ct(xout_dofs[i]->ub());
    if((i < _out_dofs.ct()) && (xout_dofs[i]->ct() == _out_dofs[i].ct()))
    {
      *xout_dofs[i] = _out_dofs[i];
    }
    else
    {
      xout_dofs[i]->assign(0.0);
    }
  }


  // Postconditions:

  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::constant_base_space_map_push_action::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this

  bool result = dynamic_cast<const constant_base_space_map_push_action*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::constant_base_space_map_push_action*
fields::constant_base_space_map_push_action::
clone() const
{
  constant_base_space_map_push_action* result;

  // Preconditions:

  // Body:

  result = new constant_base_space_map_push_action(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::constant_base_space_map_push_action&
fields::constant_base_space_map_push_action::
operator=(const base_space_map_push_action& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fields::constant_base_space_map_push_action&
fields::constant_base_space_map_push_action::
operator=(const constant_base_space_map_push_action& xother)
{

  // Preconditions:


  // Body:

  _out_dofs = xother._out_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::constant_base_space_map_push_action::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(base_space_map_push_action::invariant());

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

