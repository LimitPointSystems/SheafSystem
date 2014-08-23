
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
/// Implementation for class copy_push_action

#include "ComLimitPoint/fields/copy_push_action.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// =============================================================================
// COPY_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::copy_push_action::
copy_push_action(int xdst_df)
    : section_pusher_push_action(xdst_df)
{

  // Preconditions:

  require(xdst_df >= 0);

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(dst_df() == xdst_df);

  // Exit:

  return;
}




fields::copy_push_action::
~copy_push_action()
{
  // Preconditions:


  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}


// =============================================================================
// SECTION_PUSHER_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::copy_push_action::
operator()(pullback_map::iterator& xitr,
           sec_vd& xdst,
           block<sec_vd_dof_type>& xdst_dofs)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering copy_push_action::operator()");
#endif

  // Preconditions:

  require(xdst.state_is_read_accessible());
  require(xdst.schema().df() == dst_df());
  require(xdst_dofs.ub() >= dst_df());
  require(unexecutable("dst_dofs initialized to source value"));

  // Body:

  // Do nothing; dst dofs already initalized to source value.

  // Postconditions:

  ensure(unexecutable("xdst_dofs unchanged"));

  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving copy_push_action::operator()");
#endif

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::copy_push_action::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this

  bool result = dynamic_cast<const copy_push_action*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::copy_push_action*
fields::copy_push_action::
clone() const
{
  copy_push_action* result;

  // Preconditions:

  // Body:

  result = new copy_push_action(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::copy_push_action&
fields::copy_push_action::
operator=(const section_pusher_push_action& xother)
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

fields::copy_push_action&
fields::copy_push_action::
operator=(const copy_push_action& xother)
{

  // Preconditions:


  // Body:

  _dst_df = xother._dst_df;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::copy_push_action::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(section_pusher_push_action::invariant());

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

