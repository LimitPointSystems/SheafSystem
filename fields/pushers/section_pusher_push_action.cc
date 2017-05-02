
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
/// Implementation for class section_pusher_push_action

#include "SheafSystem/section_pusher_push_action.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/sec_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// =============================================================================
// SECTION_PUSHER_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::section_pusher_push_action::
~section_pusher_push_action()
{
  // Preconditions:


  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

int
fields::section_pusher_push_action::
dst_df()
{
  return _dst_df;
}

void
fields::section_pusher_push_action::
operator()(pullback_map::iterator& xitr,
           sec_vd& xdst,
           block<sec_vd_dof_type>& xdst_dofs)
{
  // Preconditions:

  require(xdst.state_is_read_accessible());
  require(xdst.schema().df() == dst_df());
  require(xdst_dofs.ub() >= dst_df());

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
fields::section_pusher_push_action::
initialize(sec_vd& xdst)
{
  // Preconditions:

  require(xdst.state_is_read_write_accessible());

  // Body:

  // Default version does nothing.

  // Postconditions:


  // Exit:

  return;
}

void
fields::section_pusher_push_action::
finalize(sec_vd& xdst)
{
  // Preconditions:

  require(xdst.state_is_read_write_accessible());

  // Body:

  // Default version does nothing.

  // Postconditions:


  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

fields::section_pusher_push_action::
section_pusher_push_action()
{

  // Preconditions:

  // Body:

  _dst_df = 0;

  // Postconditions:

  ensure(invariant());
  ensure(dst_df() == 0);

  // Exit:

  return;
}


fields::section_pusher_push_action::
section_pusher_push_action(int xdst_df)
{

  // Preconditions:

  require(xdst_df >= 0);

  // Body:

  _dst_df = xdst_df;

  // Postconditions:

  ensure(invariant());
  ensure(dst_df() == xdst_df);

  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::section_pusher_push_action::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this.

  bool result = dynamic_cast<const section_pusher_push_action*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::section_pusher_push_action*
fields::section_pusher_push_action::
clone() const
{
  section_pusher_push_action* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

fields::section_pusher_push_action&
fields::section_pusher_push_action::
operator=(const section_pusher_push_action& xother)
{

  // Preconditions:


  // Body:

  _dst_df = xother._dst_df;

  // Postconditions:

  // Exit

  return *this;
}

bool
fields::section_pusher_push_action::
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

