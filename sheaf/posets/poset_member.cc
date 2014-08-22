
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
/// Implementation for class poset_member.

#include "ComLimitPoint/sheaf/poset_member.h"
#include "ComLimitPoint/sheaf/assert_contract.h"

/// @todo remove unnecessary includes

#include "ComLimitPoint/sheaf/array_poset_dof_map.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "ComLimitPoint/sheaf/pool.h"
#include "ComLimitPoint/sheaf/poset.h"
#include "ComLimitPoint/sheaf/poset_crg_state.h"
#include "ComLimitPoint/sheaf/poset_dof_map.h"
#include "ComLimitPoint/sheaf/poset_state.h"
#include "ComLimitPoint/sheaf/poset_state_handle.h"
#include "ComLimitPoint/sheaf/postorder_iterator.h"
#include "ComLimitPoint/sheaf/primitives_poset.h"
#include "ComLimitPoint/sheaf/primitives_poset_schema.h"
#include "ComLimitPoint/sheaf/subposet.h"
#include "ComLimitPoint/sheaf/subposet_member_iterator.h"
#include "ComLimitPoint/sheaf/subposet_state.h"
#include "ComLimitPoint/sheaf/zn_to_bool.h"

// ===========================================================
// POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_member::
poset_member()
{
  // Preconditions:

  // Body:

  // Nothing to do - base does it all

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

sheaf::poset_member::
poset_member(const abstract_poset_member& xother, bool xnew_jem)
{
  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  if(xnew_jem)
  {
    new_jem_state(const_cast<abstract_poset_member*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

sheaf::poset_member&
sheaf::poset_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

sheaf::poset_member&
sheaf::poset_member::
operator=(const poset_member& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

sheaf::poset_member::
~poset_member()
{
  // Preconditions:

  // Body:

  // Nothing to do - base does it all

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

sheaf::poset_member::
poset_member(poset_state_handle* xhost,
             poset_dof_map* xdof_map,
             bool xcopy_dof_map,
             bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(new_jim_state(same args)));
}

sheaf::poset_member::
poset_member(poset_state_handle* xhost,
             const scoped_index* xexpansion,
             int xexpansion_ct,
             const tern& xnew_jem,
             bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(new_jrm_state(same args)));

}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

sheaf::poset_member::
poset_member(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

sheaf::poset_member::
poset_member(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

sheaf::poset_member::
poset_member(const poset_state_handle* xhost, const std::string& xname)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
}

sheaf::poset_member::
poset_member(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESTRICTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::poset_member::
restrict_to(const abstract_poset_member* xschema)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xschema != 0);
  require(xschema->state_is_read_accessible());
  require(schema().is_ancestor_of(xschema));
  require(xschema->le(&(unrestricted_schema())));

  // Body:

  // Redefined only to change access status from protected to public.

  partial_poset_member::restrict_to(xschema);

  // Postconditions:

  ensure(schema().is_same_state(xschema));

  // Exit

  return;
}

void
sheaf::poset_member::
restrict_to_same(const abstract_poset_member* xother)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());
  require(has_same_host(xother));
  require(xother->unrestricted_schema().le(&(unrestricted_schema())));

  // Body:

  // Redefined only to change access status from protected to public.

  partial_poset_member::restrict_to_same(xother);

  // Postconditions:

  ensure(is_same_restriction(xother));

  // Exit

  return;
}

void
sheaf::poset_member::
unrestrict()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Redefined only to change access status from protected to public.

  partial_poset_member::unrestrict();

  // Postconditions:

  ensure(!is_restricted());

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_member*
sheaf::poset_member::
clone() const
{
  // Preconditions:

  // Body:

  // create new handle of the current class.

  poset_member *result = new poset_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
sheaf::poset_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && partial_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS FACET
// ===========================================================
 
