
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
/// Implementation for class partial_poset_member.

#include "partial_poset_member.h"
#include "assert_contract.h"

#include "array_poset_dof_map.h"
#include "namespace_poset.h"
#include "pool.h"
#include "poset.h"
#include "poset_crg_state.h"
#include "poset_dof_map.h"
#include "poset_joiner.h"
#include "poset_slicer.h"
#include "poset_state.h"
#include "poset_state_handle.h"
#include "postorder_iterator.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "subposet_state.h"
#include "zn_to_bool.h"

// ===========================================================
// PARTIAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::partial_poset_member::
partial_poset_member()
    : _schema(0)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

sheaf::partial_poset_member::
partial_poset_member(const abstract_poset_member& xother, bool xnew_jem)
    : _schema(0)
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
  ensure(is_attached() == const_cast<abstract_poset_member&>(xother).is_attached() );
}

sheaf::partial_poset_member&
sheaf::partial_poset_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&(const_cast<abstract_poset_member&>(xother))));

  // Exit

  return *this;
}

sheaf::partial_poset_member&
sheaf::partial_poset_member::
operator=(const partial_poset_member& xother)
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

sheaf::partial_poset_member::
~partial_poset_member()
{

  // Preconditions:

  // Body:

  // Delete the restricted schema handle

  if(_schema != 0)
  {
    delete _schema;
  }

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

sheaf::partial_poset_member::
partial_poset_member(poset_state_handle* xhost,
                     poset_dof_map* xdof_map,
                     bool xcopy_dof_map,
                     bool xauto_access)
    : _schema(0)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  require(postcondition_of(new_jim_state(same args)));
}

sheaf::partial_poset_member::
partial_poset_member(poset_state_handle* xhost,
                     const scoped_index* xexpansion,
                     int xexpansion_ct,
                     const tern& xnew_jem,
                     bool xauto_access)
    : _schema(0)
{

  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem, xauto_access);

  // Postconditions:

  require(postcondition_of(new_jrm_state(same args)));
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

sheaf::partial_poset_member::
partial_poset_member(const poset_state_handle* xhost, pod_index_type xhub_id)
    : _schema(0)
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

sheaf::partial_poset_member::
partial_poset_member(const poset_state_handle* xhost, const scoped_index& xid)
    : _schema(0)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

sheaf::partial_poset_member::
partial_poset_member(const poset_state_handle* xhost, const std::string& xname)
    : _schema(0)
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

sheaf::partial_poset_member::
partial_poset_member(const namespace_poset* xnamespace,
                     const poset_path& xpath,
                     bool xauto_access)
    : _schema(0)
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

sheaf::partial_poset_member::
partial_poset_member(schema_poset_member* xschema)
    : _schema(xschema)
{
  // Preconditions:

  require(xschema != 0);
  require(!xschema->is_attached());

  // Body:

  // Postconditions:

  // Exit

  return;
}

void
sheaf::partial_poset_member::
init_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Have just attached to a new or different host.
  // Initialize the handle data members for the different host.

  if(_schema != 0)
  {
    _schema->detach_from_state();
    delete _schema;
  }

  _schema = host()->schema().clone();

  // Postconditions:

  ensure(!_schema->is_attached());

  // Exit

  return;
}

void
sheaf::partial_poset_member::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(is_valid(dof_tuple_id(false)))
  {
    // This member has a dof tuple; it is a jim in some version of the host.
    // Schema is the same as the dof map schema.

    _schema->attach_to_state(&(dof_map().schema()));
  }
  else
  {
    // This is not a jim in any version; use the host schema
    /// @issue what does the schema feature mean for a member that doesn't have a dof map?

    _schema->attach_to_state(&(host()->schema()));
  }

  // Postconditions:

  ensure(schema().is_attached() == host()->schema().is_attached());
  ensure(!is_restricted());

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::schema_poset_member&
sheaf::partial_poset_member::
schema()
{
  // Preconditions:

  // The implementation of this only requires is_attached(),
  // but both ancestors and descendants require state_is_read_accessible().

  require(state_is_read_accessible());

  // Body:

  schema_poset_member& result = *_schema;

  // Postconditions:

  ensure(result.le(&(unrestricted_schema())));

  // Exit

  return result;
}

const sheaf::schema_poset_member&
sheaf::partial_poset_member::
schema() const
{
  // Preconditions:

  // The implementation of this only requires is_attached(),
  // but both ancestors and descendants require state_is_read_accessible().

  require(state_is_read_accessible());

  // Body:

  const schema_poset_member& result = *_schema;

  // Postconditions:

  ensure(result.le(&(unrestricted_schema())));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESTRICTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
sheaf::partial_poset_member::
restrict_to(const abstract_poset_member* xschema)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xschema != 0);
  require(xschema->state_is_read_accessible());
  require(schema().is_ancestor_of(xschema));
  require(xschema->le(&(unrestricted_schema())));

  // Body:

  // Attach the handle schema to xschema

  _schema->attach_to_state(xschema);

  // Postconditions:

  ensure(schema().is_same_state(xschema));

  // Exit

  return;
}

void
sheaf::partial_poset_member::
restrict_to_same(const abstract_poset_member* xother)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());
  require(has_same_host(xother));
  require(xother->schema().le(&(unrestricted_schema())));

  // Body:

  _schema->attach_to_state(&(xother->schema()));

  // Postconditions:

  ensure(is_same_restriction(xother));

  // Exit

  return;
}

void
sheaf::partial_poset_member::
unrestrict()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  _schema->attach_to_state(&(unrestricted_schema()));

  // Postconditions:

  ensure(!is_restricted());

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
sheaf::partial_poset_member::
dof_ct() const
{
  return is_attached() ? _schema->row_dof_ct() : 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::partial_poset_member::
detach_from_state()
{
  // Preconditions:

  // Body:

  if(_schema != 0)
  {
    _schema->detach_from_state();
  }

  abstract_poset_member::detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::partial_poset_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const partial_poset_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::partial_poset_member*
sheaf::partial_poset_member::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  partial_poset_member *result = new partial_poset_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
sheaf::partial_poset_member::
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

    result = result && (is_attached() ? (_schema != 0) : true);
    result = result && (is_attached() ? _schema->is_attached() : true);
    result = result && (is_attached() ? _schema->leqv(host()->schema().index()) : true);

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
 

