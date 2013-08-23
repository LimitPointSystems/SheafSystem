
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

// Implementation for class TERNARY_SECTION_SPACE_SCHEMA_MEMBER

#include "ternary_section_space_schema_member.h"

#include "id_space_map.h"
#include "namespace_poset.h"
#include "postorder_iterator.h"
#include "sec_rep_descriptor.h"
#include "assert_contract.h"
#include "ternary_section_space_schema_poset.h"


///
const string&
fiber_bundle::ternary_section_space_schema_member::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const string&
fiber_bundle::ternary_section_space_schema_member::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("ternary_section_space_schema_member");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// ===========================================================
// CANONICAL MEMBER FACET
// ===========================================================

///
fiber_bundle::ternary_section_space_schema_member::
ternary_section_space_schema_member()
    : section_space_schema_member()
{

  // Preconditions:

  // Body:

  _local_schema_id.invalidate();

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached() );
  ensure(!base_space_id().is_valid());
  ensure(!fiber_schema_id().is_valid());
  ensure(!local_schema_id().is_valid());
  ensure(!base_space().is_attached());
  ensure(!fiber_schema().is_attached());
  ensure(!local_schema().is_attached());

  // Exit:
}


///
fiber_bundle::ternary_section_space_schema_member::
ternary_section_space_schema_member(const ternary_section_space_schema_member& xother)
{

  // Preconditions:

  // Body:

  attach_to_state(const_cast<ternary_section_space_schema_member*>(&xother));

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == const_cast<ternary_section_space_schema_member&>(xother).is_attached() );
}


///
fiber_bundle::ternary_section_space_schema_member&
fiber_bundle::ternary_section_space_schema_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(const_cast<abstract_poset_member*>(&xother));

  // Postconditions:

  ensure(is_same_state(const_cast<abstract_poset_member*>(&xother)));

  // Exit

  return *this;
}


///
fiber_bundle::ternary_section_space_schema_member::
~ternary_section_space_schema_member()
{

  // Preconditions:

  require(is_attached() ? state_is_read_write_accessible() : true);
  require(is_attached() ? is_jim() == host()->in_jim_edit_mode() : true );

  // Body:

  _local_schema.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
bool
fiber_bundle::ternary_section_space_schema_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const ternary_section_space_schema_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


///
bool
fiber_bundle::ternary_section_space_schema_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

///
fiber_bundle::ternary_section_space_schema_member*
fiber_bundle::ternary_section_space_schema_member::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  ternary_section_space_schema_member *result =
    new ternary_section_space_schema_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

///
bool
fiber_bundle::ternary_section_space_schema_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && schema_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    result = result && (is_attached() == local_schema().is_attached());

    /// @issue what are the invariants for this class
    /// @todo implement fiber_bundle::ternary_section_space_schema_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// NEW HANDLE, NEW STATE CONSTRUCTORS

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

///
fiber_bundle::ternary_section_space_schema_member::
ternary_section_space_schema_member(ternary_section_space_schema_poset* xhost,
                                    const scoped_index& xindex)
{

  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // Body:

  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xindex);
  ensure(is_attached());
}


///
fiber_bundle::ternary_section_space_schema_member::
ternary_section_space_schema_member(ternary_section_space_schema_poset* xhost, const string& xname)
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


///
fiber_bundle::ternary_section_space_schema_member::
ternary_section_space_schema_member(namespace_poset* xnamespace,
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

// ===========================================================
// COMPONENT NAME FACET
// ===========================================================



///
string
fiber_bundle::ternary_section_space_schema_member::
name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = abstract_poset_member::name();

  if(result.empty())
  {
    // Provide a default name.

    /// @issue shouldn't name include base and fiber components as well?

    result = local_schema().name();
  }


  // Posetconditions:

  ensure(unexecutable(result.empty() implies this has no name));

  // Exit:

  return result;
}


// ===========================================================
// STATE FACET
// ===========================================================

///
void
fiber_bundle::ternary_section_space_schema_member::
attach_to_state(const scoped_index& xbase_space_id,
                const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().contains_member(xbase_space_id));
  require(host()->fiber_schema().contains_member(xfiber_schema_id));
  require(host()->local_schema_stride() == 1);

  // Body:

  attach_to_state(host(),
                  xbase_space_id,
                  xfiber_schema_id,
                  TOP_INDEX);

  // Postconditions:

  ensure(base_space_id() ==~ xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() ==~ xfiber_schema_id);
  ensure(fiber_schema().is_attached());
  ensure(local_schema_id() == TOP_INDEX);
  ensure(local_schema().is_attached());

  // Exit

  return;
}

///
void
fiber_bundle::ternary_section_space_schema_member::
attach_to_state(section_space_schema_poset* xhost,
                const scoped_index& xbase_space_id,
                const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->base_space().contains_member(xbase_space_id));
  require(xhost->fiber_schema().contains_member(xfiber_schema_id));
  /// @todo fix the following precondition
  ///  require(xhost->local_schema_stride() == 1);

  // Body:


  _host = xhost;

  _index = host()->get_index_from_components(xbase_space_id,
           xfiber_schema_id,
           TOP_INDEX);

  _version = CURRENT_HOST_VERSION;

  /// @issue what are the dof subposets?

  attach_handle_data_members();

  // Postconditions:

  ensure(base_space_id() ==~ xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() ==~ xfiber_schema_id);
  ensure(fiber_schema().is_attached());
  ensure(local_schema_id() == TOP_INDEX);
  ensure(local_schema().is_attached());

  // Exit

  return;
}

///
void
fiber_bundle::ternary_section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
                const poset_path& xbase_path,
                const poset_path& xfiber_schema_path)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xbase_path.full());
  require(xhost->base_space().contains_member(xbase_path.member_name()));
  require(xfiber_schema_path.full());
  require(xhost->fiber_schema().contains_member(xfiber_schema_path.member_name()));

  // Body:

  attach_to_state(xhost,
                  xhost->base_space().member_id(xbase_path.member_name()),
                  xhost->base_space().member_id(xfiber_schema_path.member_name()));

  // Postconditions:

  ensure(is_attached());
  ensure(base_space().has_path(xbase_path, false));
  ensure(fiber_schema().has_path(xfiber_schema_path, false));

  // Exit

  return;
}

///
void
fiber_bundle::ternary_section_space_schema_member::
attach_to_state(ternary_section_space_schema_poset* xhost,
                const scoped_index& xbase_space_id,
                const scoped_index& xfiber_schema_id,
                const scoped_index& xlocal_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->base_space().contains_member(xbase_space_id));
  require(xhost->fiber_schema().contains_member(xfiber_schema_id));
  require(xhost->local_schema().contains_member(xlocal_schema_id));
  require(xhost->local_schema_stride() == 1);

  // Body:


  _host = xhost;
  _index = host()->get_index_from_components(xbase_space_id, xfiber_schema_id, xlocal_schema_id);
  _version = CURRENT_HOST_VERSION;

  /// @issue what are the dof subposets?

  attach_handle_data_members();

  // Postconditions:

  ensure(base_space_id() ==~ xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() ==~ xfiber_schema_id);
  ensure(fiber_schema().is_attached());
  ensure(local_schema_id() ==~ xlocal_schema_id);
  ensure(local_schema().is_attached());

  // Exit

  return;
}


///
void
fiber_bundle::ternary_section_space_schema_member::
detach_from_state()
{
  // Preconditions:

  // Body:

  _local_schema.detach_from_state();
  _local_schema_id = local_schema().index();

  section_space_schema_member::detach_from_state();

  // Postconditions:

  ensure(!is_attached());
  ensure(!base_space().is_attached());
  ensure(!fiber_schema().is_attached());
  ensure(!local_schema().is_attached());

  // Exit

  return;
}



// ===========================================================
// MEMBER ATTRIBUTE FACET
// ===========================================================



///
bool
fiber_bundle::ternary_section_space_schema_member::
is_jim(bool xin_current_version) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // The

  result = base_space().is_jim(xin_current_version) && fiber_schema().is_jim() && local_schema().is_jim();

  // Postconditions:

  // Exit

  return result;
}




///
bool
fiber_bundle::ternary_section_space_schema_member::
is_atom() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = base_space().is_atom() && fiber_schema().is_atom() && local_schema().is_atom();

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================





///
sheaf::primitives_poset_dof_map&
fiber_bundle::ternary_section_space_schema_member::
dof_map(bool xrequire_write_access) const
{

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  primitives_poset_dof_map& result = local_schema().dof_map(xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}



// ===========================================================
// ORDERING RELATION FACET
// ===========================================================




// ===========================================================
// DOWN SET FACET
// ===========================================================



///
int
fiber_bundle::ternary_section_space_schema_member::
down_ct(const scoped_index& xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().down_ct() * fiber_schema().down_ct() * local_schema().down_ct();

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}


///
sheaf::subposet*
fiber_bundle::ternary_section_space_schema_member::
down()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  down_pa(result);


  // Postconditions:

  require(result != 0);
  require(postcondition_of(down_pa));

  // Exit

  return result;
}


///
void
fiber_bundle::ternary_section_space_schema_member::
down_pa(subposet* result)
{

  // Preconditions:

  // Body:

  not_implemented();


  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is down set
                        of this));

  // Exit

  return;
}




///
int
fiber_bundle::ternary_section_space_schema_member::
up_ct(const scoped_index& xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().up_ct() * fiber_schema().up_ct() * local_schema().up_ct();

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}




///
sheaf::subposet*
fiber_bundle::ternary_section_space_schema_member::
up() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  up_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(up_pa));

  // Exit

  return result;
}


///
void
fiber_bundle::ternary_section_space_schema_member::
up_pa(subposet* result)
{

  // Preconditions:

  // Body:

  // Traverse up set, inserting members into result

  /// @todo implement this function

  not_implemented();

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is up set
                        of this));

  // Exit

  return;
}




///
int
fiber_bundle::ternary_section_space_schema_member::
jim_ct() const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().jim_ct() * fiber_schema().jim_ct() * local_schema().jim_ct();

  // Postconditions:

  ensure(is_jem(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}


///
sheaf::subposet*
fiber_bundle::ternary_section_space_schema_member::
jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  jims_pa(result);


  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(jims_pa));

  // Exit

  return result;
}


///
void
fiber_bundle::ternary_section_space_schema_member::
jims_pa(subposet* result)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is jims set
                        of this));

  // Exit

  return;
}


///
int
fiber_bundle::ternary_section_space_schema_member::
maximal_jim_ct()
{
  int result = 0;

  // Preconditions:

  // Body:

  result =
    base_space().maximal_jim_ct() *
    fiber_schema().maximal_jim_ct() *
    local_schema().maximal_jim_ct();

  // Postconditions:

  ensure(is_jem(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}


///
sheaf::subposet*
fiber_bundle::ternary_section_space_schema_member::
maximal_jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  maximal_jims_pa(result);


  // Postconditions:

  ensure(has_same_host(result));
  ensure(postcondition_of(maximal_jims_pa));

  // Exit

  return result;
}


///
void
fiber_bundle::ternary_section_space_schema_member::
maximal_jims_pa(subposet* result)
{

  // Preconditions:

  require(has_same_host(result));

  // Body:

  not_implemented();


  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is union of maximal_jims of this with old result));

  // Exit

  return;
}


// ===========================================================
// POSET ALGEBRA FACET
// ===========================================================



///
void
fiber_bundle::ternary_section_space_schema_member::
p_join_pa(abstract_poset_member* other, abstract_poset_member* result) const
{
  // Preconditions:

  require(has_same_host(other));
  require(!result->is_attached());
  // this precondition ensures the attachment below will not
  // leave an orphan temporary in the poset
  require(result->is_ancestor_of(this));
  require(state_is_read_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

///
void
fiber_bundle::ternary_section_space_schema_member::
p_meet_pa(abstract_poset_member* other, abstract_poset_member* result)
{
  // Preconditions:

  require(has_same_host(other));
  require(!result->is_attached());
  // this precondition ensures the attachment below will not
  // leave an orphan temporary in the poset
  require(result->is_ancestor_of(this));
  require(state_is_read_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}


// ===========================================================
// TERNARY_SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

///
sheaf::primitive_type
fiber_bundle::ternary_section_space_schema_member::
dof_tuple_type(bool xis_table_dof)
{
  primitive_type result = NOT_A_PRIMITIVE_TYPE;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_schematized(false));

  // Body:

  if(xis_table_dof)
  {
    // Table dofs:
    // Table dofs are {base.bottom()} x {fiber schema table dofs}.

    result = fiber_schema().table_dof_tuple_type();
  }
  else
  {
    // Row dofs:
    // Local schema defines dof type

    result = local_schema().row_dof_tuple_type();
  }

  // Postconditions:

  // Exit

  return result;
}



///
sheaf::dof_descriptor_array*
fiber_bundle::ternary_section_space_schema_member::
dof_descriptors(bool xis_table_dof) const
{
  dof_descriptor_array* result = 0;

  // Preconditions:

  require(state_is_read_accessible());

  // Dof descriptors not defined for row dofs.

  require(xis_table_dof);

  // Body:

  result = fiber_schema().dof_descriptors(xis_table_dof);

  // Postconditions:

  ensure(unexecutable(result != 0 implies it points to a buffer of length table_dof_ct()+1));

  // Exit

  return result;
}



///
sheaf::id_space_map&
fiber_bundle::ternary_section_space_schema_member::
dof_client_id_map(bool xis_table_dof) const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Client id map for row dofs is not defined.

  require(xis_table_dof);

  // Body:

  id_space_map& result = fiber_schema().table_dof_client_id_map();

  // Postconditions:

  // Exit

  return result;
}



///
bool
fiber_bundle::ternary_section_space_schema_member::
is_dof(bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));


  // Body:

  if(xin_table_dofs)
  {
    // Table dofs:

    // Table dofs are {base.bottom()} x {fiber schema table dofs}.

    result = (_base_space_id == BOTTOM_INDEX)
             && fiber_schema().is_table_dof();
  }
  else
  {
    // Row dofs:

    result = host()->discretization().contains_member(_base_space_id) &&
             fiber_schema().is_row_dof() && local_schema().is_row_dof();
  }

  // Postconditions:

  // Exit

  return result;
}




///
size_t
fiber_bundle::ternary_section_space_schema_member::
size() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(local_schema().is_jim());

  // Body:

  result = local_schema().size();

  // Postconditions:

  // Exit

  return result;
}



///
size_t
fiber_bundle::ternary_section_space_schema_member::
alignment() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(local_schema().is_jim());

  // Body:

  result = local_schema().alignment();

  // Postconditions:

  // Exit

  return result;
}



///
sheaf::primitive_type
fiber_bundle::ternary_section_space_schema_member::
type() const
{
  sheaf::primitive_type result;

  // Preconditions:

  require(state_is_read_accessible());
  require(local_schema().is_jim());

  // Body:

  result = local_schema().type();

  // Postconditions:

  ensure(is_primitive_index(result));

  // Exit

  return result;
}



///
sheaf::client_index
fiber_bundle::ternary_section_space_schema_member::
client_id(schema_poset_member& xother_schema, bool xin_table_dofs) const
{
  // Preconditions:

  require(is_attached());
  require(is_ancestor_of(&xother_schema));
  require(xother_schema.state_is_read_accessible());
  require(le(&xother_schema));
  require(xother_schema.is_schematized(false));


  // Body:

  ternary_section_space_schema_member& lother = reinterpret_cast<ternary_section_space_schema_member&>(xother_schema);
  client_index lfiber_client_id = fiber_schema().client_id(lother.fiber_schema(), xin_table_dofs);

  client_index result; // Unscoped.

  if(xin_table_dofs)
  {
    result = lfiber_client_id;
  }
  else
  {
    // Row dofs:

    /// @error client ids in discretization only correct sequence ids if
    /// base space == member discretization was computed from.

    client_index::pod_type lbase_client_id  = discretization().client_id_map()->client_id(base_space_id());
    client_index::pod_type llocal_client_id = local_schema().client_id(lother.local_schema(), false);

    result.put_pod( llocal_client_id
                    + lother.local_schema().row_dof_ct()*
                    (lfiber_client_id.pod() + (lother.fiber_schema().row_dof_ct()*lbase_client_id )));

  }


  // Postconditions:

  // Exit

  return result;
}



///
sheaf::client_index
fiber_bundle::ternary_section_space_schema_member::
max_client_id(bool xin_table_dofs) const
{
  // Preconditions:

  require(is_attached());
  require(is_schematized(false));


  // Body:

  client_index result; // Unscoped.

  if(xin_table_dofs)
  {
    // Table schema is fiber schema; result is scoped.

    result = fiber_schema().max_client_id(xin_table_dofs);
  }
  else
  {
    // Row dofs:

    /// @hack Id space of row dofs is implicit,
    /// no explicit id map; result can't be scoped.

    /// @error client ids in discretization only correct sequence ids if
    /// base space == member discretization was computed from.

    ternary_section_space_schema_member* cthis = const_cast<ternary_section_space_schema_member*>(this);
    pod_index_type  lbase_client_id_max  = cthis->discretization().client_id_map()->max_client_id();

    pod_index_type  lfiber_client_id_max = fiber_schema().max_client_id(xin_table_dofs);
    pod_index_type  lfiber_client_id_ub  = lfiber_client_id_max + 1;

    pod_index_type llocal_client_id_max = local_schema().max_client_id(xin_table_dofs);
    pod_index_type llocal_client_id_ub  = llocal_client_id_max + 1;

    result =
      llocal_client_id_max +
      lfiber_client_id_max*llocal_client_id_ub +
      lbase_client_id_max*lfiber_client_id_ub*llocal_client_id_ub;
  }

  // Postconditions:

  // Exit

  return result;
}

// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

///
sheaf::index_iterator*
fiber_bundle::ternary_section_space_schema_member::
get_decomposition(const scoped_index& xindex)
{
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().includes_subposet(xindex));

  // Body:

  zn_to_bool* ldecomp = new zn_to_bool();

  subposet ldecomp_sp(&host()->base_space(), xindex);

  index_iterator litr = ldecomp_sp.indexed_member_iterator();
  while(!litr.is_done())
  {
    scoped_index lschema_mbr_id =
      host()->get_index_from_components(litr.index(),
                                        fiber_schema_id(),
                                        local_schema_id());

    ldecomp->force(lschema_mbr_id.pod(), true);

    litr.next();
  }

  ldecomp_sp.detach_from_state();

  index_iterator* result = new index_iterator(ldecomp, true);

  // Postconditions:

  // Exit:

  return result;
}



sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_member::
get_int_id(pod_index_type xext_id, const string& xid_space_name) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(precondition_of(host()->base_space().get_int_id(xext_id, xid_space_name)));

  // Body:

  /// @hack product subposet hack, ver 2.
  /// Section space schema member external ids are really base space external ids.

  pod_index_type lbase_pod =
    host()->base_space().get_int_id(xext_id, xid_space_name, false);

  scoped_index lbase_id = host()->base_space().internal_id(lbase_pod);

  scoped_index result =
    host()->get_index_from_components(lbase_id, fiber_schema_id(), local_schema_id());

  // Postconditions:

  ensure(host()->contains_member(result));

  // Exit:

  return result;
}



///
void
fiber_bundle::ternary_section_space_schema_member::
get_ext_ids(const string& xid_space_name,
            scoped_index& xschema_poset_ext_id,
            scoped_index& xschema_member_ext_id,
            scoped_index& xbase_space_ext_id,
            scoped_index& xfiber_schema_ext_id,
            scoped_index& xlocal_schema_ext_id) const
{
  // Preconditions:

  require(precondition_of(section_space_schema_member::get_ext_ids(same args)));
  require(host()->local_schema().contains_id_space(xid_space_name));
  require(host()->local_schema().equivalence_map(xid_space_name).contains_internal_id(local_schema_id()));

  // Body:

  // Get the external id for the schema poset (this->host()).

  xschema_poset_ext_id =
    name_space()->get_ext_id(host()->index(), xid_space_name, false);

  // Schema member external id is undefined.

  xschema_member_ext_id.invalidate();

  // Get the external id for the base space component.

  xbase_space_ext_id =
    host()->base_space().get_ext_id(base_space_id(), xid_space_name, false);

  // Get the external id for the fiber schema component.

  xfiber_schema_ext_id =
    host()->fiber_schema().get_ext_id(fiber_schema_id(), xid_space_name, false);

  // Get the external id for the local schema component.

  xlocal_schema_ext_id =
    host()->local_schema().get_ext_id(local_schema_id(), xid_space_name, false);

  // Postconditions:


  // Exit:

  return;
}

///
sheaf::schema_poset_member&
fiber_bundle::ternary_section_space_schema_member::
ext_data_type_schema()
{
  not_implemented();

  return local_schema();
}



///
size_t
fiber_bundle::ternary_section_space_schema_member::
ext_data_type_ct(bool xis_table_schema) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  not_implemented();

  // Postconditions:


  // Exit:

  return 0;
}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

void
fiber_bundle::ternary_section_space_schema_member::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_schematized(false));

  // Body:

  // Initialize inherited data members

  section_space_schema_member::attach_handle_data_members();

  // Compute the component member ids.

  _local_schema_id = host()->get_local_schema_id_from_index(_index);

  // Attach the component handles

  _local_schema.attach_to_state(&(host()->local_schema()), _local_schema_id);

  // Postconditions:

  ensure(table_dof_subposet_index().is_valid());
  ensure(row_dof_subposet_index().is_valid());

  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(local_schema().is_attached());

  // Exit

  return;
}



///
void
fiber_bundle::ternary_section_space_schema_member::
update_row_cache()
{
  // Preconditions:

  // Body:

  section_space_schema_member::update_row_cache();

  _row_dof_ct          = _discretization_ct*fiber_schema().row_dof_ct()*local_schema().row_dof_ct();

  _row_dof_tuple_ub    = _discretization_ub.pod()*fiber_schema().row_dof_ct()*local_schema().row_dof_tuple_ub();

  _row_dof_descriptors = 0;

  _row_cache_index = index();
  _row_cache_version = version();

  // Postconditions:

  // Exit

  return;
}



