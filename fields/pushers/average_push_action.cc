
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
/// Implementation for class average_push_action

#include "average_push_action.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// =============================================================================
// AVERAGE_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::average_push_action::
average_push_action(int xdst_df)
    : section_pusher_push_action(xdst_df)
{

  // Preconditions:

  require(xdst_df >= 0);

  // Body:

  /// @issue assumes binary schema.

  _dst_dofs.reserve(_dst_df);
  _dst_dofs.set_ct(_dst_df);



  // Postconditions:

  ensure(invariant());
  ensure(dst_df() == xdst_df);

  // Exit:

  return;
}




fields::average_push_action::
~average_push_action()
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
fields::average_push_action::
operator()(pullback_map::iterator& xitr,
           sec_vd& xdst,
           block<sec_vd_dof_type>& xdst_dofs)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering average_push_action::operator()");
#endif

  // Preconditions:

  require(xdst.state_is_read_accessible());
  require(xdst.schema().df() == dst_df());
  require(xdst_dofs.ub() >= dst_df());
  require(unexecutable("xdst_dofs initialized to source value"));
  require(xdst_dofs.ct() == dst_df()); // Partial statement of above

  // Body:

  xdst.get_fiber(xitr->disc_id, _dst_dofs.base(),
		 _dst_dofs.ct()*sizeof(sec_vd_dof_type), false);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "disc id: " << setw(4) << xitr->disc_id
  << " _dst_dofs: " << _dst_dofs;
#endif

  for(int i=0; i<_dst_df; ++i)
  {
    xdst_dofs[i] += _dst_dofs[i];
  }

  pod_index_type lclient_id = _disc_seq_id_space->pod(xitr->disc_id);

  ++_branch_cts[lclient_id];

#ifdef DIAGNOSTIC_OUTPUT

  cout << " xdst_dofs: " << xdst_dofs
  << " ct: " << _branch_cts[lclient_id]
  << endl;
#endif

  // Postconditions:

  ensure(unexecutable("xdst_dofs += xdst dofs"));

  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving average_push_action::operator()");
#endif

  return;
}


void
fields::average_push_action::
initialize(sec_vd& xdst)
{
  // Preconditions:

  require(xdst.state_is_read_write_accessible());

  // Body:

  _dst_dofs.assign(0.0);

  _disc_ct = xdst.schema().discretization_ct();
  _branch_cts.reserve(_disc_ct);
  _branch_cts.set_ct(_disc_ct);

  for(int i= 0; i<_disc_ct; ++i)
  {
    xdst.put_fiber(i, _dst_dofs.base(), _dst_dofs.ct()*sizeof(sec_vd_dof_type));

    _branch_cts[i] = 0;
  }

  _disc_seq_id_space = &xdst.schema().discretization_id_space();

  // Postconditions:


  // Exit:

  return;
}

void
fields::average_push_action::
finalize(sec_vd& xdst)
{
  // Preconditions:

  require(xdst.state_is_read_write_accessible());

  // Body:

  // Normalize the accumulated values.

  for(int i= 0; i<_disc_ct; ++i)
  {
    xdst.get_fiber(i, _dst_dofs.base(), _dst_dofs.ct()*sizeof(sec_vd_dof_type));

    int lbranch_ct = _branch_cts[i];
    if(lbranch_ct != 0)
    {
      for(int j=0; j<_dst_df; ++j)
      {
        _dst_dofs[j] /= lbranch_ct;
      }
    }
    xdst.put_fiber(i, _dst_dofs.base(), _dst_dofs.ct()*sizeof(sec_vd_dof_type));
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
fields::average_push_action::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const average_push_action*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::average_push_action*
fields::average_push_action::
clone() const
{
  average_push_action* result;

  // Preconditions:

  // Body:

  result = new average_push_action(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::average_push_action&
fields::average_push_action::
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


fields::average_push_action&
fields::average_push_action::
operator=(const average_push_action& xother)
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
fields::average_push_action::
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

