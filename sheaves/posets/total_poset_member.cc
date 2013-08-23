
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Implementation for class total_poset_member.

#include "total_poset_member.h"
#include "assert_contract.h"

#include "array_poset_dof_map.h"
#include "namespace_poset.h"
#include "pool.h"
#include "poset.h"
#include "poset_crg_state.h"
#include "poset_dof_map.h"
#include "poset_state.h"
#include "poset_state_handle.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "std_strstream.h"
#include "subposet.h"
#include "poset_member_iterator.h"
#include "subposet_state.h"
#include "zn_to_bool.h"

// ===========================================================
// TOTAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::total_poset_member::
total_poset_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

sheaf::total_poset_member::
total_poset_member(const abstract_poset_member& xother, bool xnew_jem)
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

sheaf::total_poset_member&
sheaf::total_poset_member::
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

sheaf::total_poset_member&
sheaf::total_poset_member::
operator=(const total_poset_member& xother)
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

sheaf::total_poset_member::
~total_poset_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

sheaf::total_poset_member::
total_poset_member(poset_state_handle* xhost,
                   poset_dof_map* xdof_map,
                   bool xcopy_dof_map,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

}

sheaf::total_poset_member::
total_poset_member(poset_state_handle* xhost,
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

  ensure(postcondition_of(new_jrm_state(same args)));

}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

sheaf::total_poset_member::
total_poset_member(const poset_state_handle* xhost, pod_index_type xhub_id)
{

  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id, false));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

sheaf::total_poset_member::
total_poset_member(const poset_state_handle* xhost, const scoped_index& xid)
{

  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid, false));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

sheaf::total_poset_member::
total_poset_member(const poset_state_handle* xhost, const string& xname)
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


sheaf::total_poset_member::
total_poset_member(const namespace_poset* xnamespace,
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
// SCHEMA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::schema_poset_member&
sheaf::total_poset_member::
schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // The defining property of a toal poset member is that
  // it is never restricted.

  schema_poset_member& result = unrestricted_schema();

  // Postconditions:

  ensure(result.is_same_state(&(unrestricted_schema())));

  // Exit

  return result;
}

const sheaf::schema_poset_member&
sheaf::total_poset_member::
schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // The defining property of a toal poset member is that
  // it is never restricted.

  const schema_poset_member& result = unrestricted_schema();

  // Postconditions:

  ensure(result.is_same_state(&(unrestricted_schema())));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESTRICTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::total_poset_member::
is_restricted() const
{
  bool result;

  // Preconditions:

  // Body:

  result = false;

  // Postconditions:

  ensure(!result);

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
sheaf::total_poset_member::
dof_ct() const
{
  return schema().row_dof_ct();
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::total_poset_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const total_poset_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::total_poset_member*
sheaf::total_poset_member::
clone() const
{
  // Preconditions:

  // Body:

  // create new handle of the current class.

  total_poset_member *result = new total_poset_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

bool
sheaf::total_poset_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && abstract_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    /// @issue what are the invariants for this class
    /// @todo implement total_poset_member::invariant() const

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
// NON-MEMBER FUNCTIONS
// ===========================================================

