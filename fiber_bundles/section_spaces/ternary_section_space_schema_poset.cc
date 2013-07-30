

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

// Implementation for class POSET

#include "ternary_section_space_schema_poset.h"

#include "abstract_poset_member.h"
#include "array_poset_dof_map.h"
#include "list_cover_set.h"
#include "index_iterator.h"
#include "namespace_poset.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "poset_member_iterator.h"
#include "poset_state.h"
#include "poset_type.h"
#include "postorder_member_iterator.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sheaves_namespace.h"
#include "subposet.h"
#include "ternary_section_space_schema_member.h"
#include "wsv_block.h"

const int fiber_bundle::ternary_section_space_schema_poset::table_dof_tuple_type::LOCAL_SCHEMA_MEMBER_ID_UB;
const int fiber_bundle::ternary_section_space_schema_poset::table_dof_tuple_type::FIBER_SCHEMA_MEMBER_ID_UB;
const int fiber_bundle::ternary_section_space_schema_poset::table_dof_tuple_type::BASE_SPACE_MEMBER_ID_UB;

///
sheaf::poset_type
sheaf::ternary_section_space_schema_poset::
type_id() const
{
  return TERNARY_SECTION_SPACE_SCHEMA_POSET_ID;
}

///@todo static_class_name

///
const char*
fiber_bundle::ternary_section_space_schema_poset::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "ternary_section_space_schema_poset";

  // Postconditions:

  // Exit:

  return result;
}



///
const sheaf::poset_path&
fiber_bundle::ternary_section_space_schema_poset::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path
  result(standard_schema_poset_name(), "ternary_section_space_schema_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

///
void
fiber_bundle::ternary_section_space_schema_poset::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(xns.member_poset(standard_schema_poset_name(), false)->state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs;
  ldof_specs =  "local_schema_id NAMESPACE_RELATIVE_MEMBER_INDEX true";
  ldof_specs += " local_schema_member_id_ub INT true";
  ldof_specs += " local_schema_stride INT true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              section_space_schema_poset::standard_schema_path(),
                              ldof_specs,
                              false,
                              false);

  lschema.detach_from_state();


  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit

  return;
}


// CANONICAL MEMBERS

///
fiber_bundle::ternary_section_space_schema_poset::
ternary_section_space_schema_poset()
    : section_space_schema_poset(new ternary_section_space_schema_member,
                                 new ternary_section_space_schema_member)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(!is_attached());
  ensure(!top().is_attached());
  ensure(!bottom().is_attached());
}


///
fiber_bundle::ternary_section_space_schema_poset::
ternary_section_space_schema_poset(const ternary_section_space_schema_poset& xother)
    : section_space_schema_poset(new ternary_section_space_schema_member,
                                 new ternary_section_space_schema_member)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(is_same_state(&const_cast<ternary_section_space_schema_poset&>(xother)));
}


///
fiber_bundle::ternary_section_space_schema_poset*
fiber_bundle::ternary_section_space_schema_poset::
clone() const
{
  ternary_section_space_schema_poset* result;

  // Preconditions:

  // Body:

  result = new ternary_section_space_schema_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}


///
fiber_bundle::ternary_section_space_schema_poset&
fiber_bundle::ternary_section_space_schema_poset::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&const_cast<poset_state_handle&>(xother)));

  // Body:

  poset_state_handle::operator=(const_cast<poset_state_handle&>(xother));

  // Postconditions:

  ensure(is_same_state(&const_cast<poset_state_handle&>(xother)));

  // Exit:

  return *this;
}


///
fiber_bundle::ternary_section_space_schema_poset::
~ternary_section_space_schema_poset()
{
  // Preconditions:

  require(is_attached() ? state_is_read_write_accessible() : true);

  // Body:

  _local_schema.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
bool
fiber_bundle::ternary_section_space_schema_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const ternary_section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


///
bool
fiber_bundle::ternary_section_space_schema_poset::
invariant() const
{
  bool result = true;

  result = result && poset_state_handle::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    result = result && 
      (is_attached() ? local_schema_poset_id() == local_schema().host()->index().hub_pod() : true);

    /// @todo finish ternary_section_space_schema_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}


// NEW HANDLE, NEW STATE CONSTRUCTORS

///
fiber_bundle::ternary_section_space_schema_poset::
ternary_section_space_schema_poset(namespace_poset* xhost,
                                   const string& xname,
                                   sec_rep_descriptor& xrep,
                                   poset_state_handle& xbase_space,
                                   poset_state_handle& xfiber_space,
                                   poset_state_handle& xlocal_schema,
                                   bool xauto_access)
    : section_space_schema_poset(new ternary_section_space_schema_member,
                                 new ternary_section_space_schema_member)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xname, xrep, xbase_space, xfiber_space, xlocal_schema, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));
}



// NEW HANDLE, EXISTING STATE CONSTRUCTORS

///
fiber_bundle::ternary_section_space_schema_poset::
ternary_section_space_schema_poset(namespace_poset* xns, const scoped_index& xindex)
    : section_space_schema_poset(new ternary_section_space_schema_member,
                                 new ternary_section_space_schema_member)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());
  require(xns->contains_member(xindex));
  require(xns->is_jim(xindex));

  // Body:

  attach_to_state(xns, xindex);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}


///
fiber_bundle::ternary_section_space_schema_poset::
ternary_section_space_schema_poset(namespace_poset* xns, const string& xname)
    : section_space_schema_poset(new ternary_section_space_schema_member,
                                 new ternary_section_space_schema_member)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());
  require(xns->contains_member(xname));

  // Body:

  attach_to_state(xns, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}


///
fiber_bundle::ternary_section_space_schema_poset::
ternary_section_space_schema_poset(namespace_poset_member* xmbr)
    : section_space_schema_poset(new ternary_section_space_schema_member,
                                 new ternary_section_space_schema_member)
{
  // Preconditions:

  require(xmbr != 0);
  require(xmbr->is_jim());
  require(xmbr->state_is_read_accessible());

  // Body:

  attach_to_state(xmbr);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}


// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

///
void
fiber_bundle::ternary_section_space_schema_poset::
new_state(namespace_poset* xns,
          const string& xname,
          sec_rep_descriptor& xrep,
          poset_state_handle& xbase_space,
          poset_state_handle& xfiber_space,
          poset_state_handle& xlocal_schema,
          bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(xns,
                                    xname,
                                    xrep.host()->index(),
                                    xrep.index(),
                                    xbase_space.index(),
                                    xfiber_schema.index(),
                                    xlocal_schema.index(),
                                    xauto_access)));

  // Body:

  new_state(xns,
            xname,
            xrep.host()->index(),
            xrep.index(),
            xbase_space.index(),
            xfiber_space.index(),
            xlocal_schema.index(),
            xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(xns,
                                    xname,
                                    xrep.host()->index(),
                                    xrep.index(),
                                    xbase_space.index(),
                                    xfiber_schema.index(),
                                    xlocal_schema.index(),
                                    xauto_access)));

  // Exit:

  return;
}



///
void
fiber_bundle::ternary_section_space_schema_poset::
new_state(namespace_poset* xns,
          const string& xname,
          const scoped_index& xrep_poset_id,
          const scoped_index& xrep_member_id,
          const scoped_index& xbase_space_poset_id,
          const scoped_index& xfiber_space_poset_id,
          const scoped_index& xlocal_schema_poset_id,
          bool xauto_access)
{

  // Preconditions:

  require(xns != 0);
  require(xauto_access || xns->state_is_read_write_accessible());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    xns->get_read_write_access(true);

  require(poset_path::is_valid_name(xname));
  require(!xns->contains_poset(xname, false));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.

  require(xname != xns->name());

  require(xns->contains_poset_member(xrep_poset_id, xrep_member_id));
  require(xns->contains_poset(xbase_space_poset_id));
  require(xns->contains_poset(xfiber_space_poset_id));
  require(xns->contains_poset(xlocal_schema_poset_id));
  require(rep_is_valid(xns, xrep_poset_id, xrep_member_id, xbase_space_poset_id));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Create the schema.

  schema_poset_member lschema(xns, standard_schema_path());
  lschema.get_read_access();

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&lschema, TERNARY_SECTION_SPACE_SCHEMA_POSET_ID);

  // Clean up the temporary schema handle.

  lschema.release_access();
  lschema.detach_from_state();

  // Attach the component handles.

  attach_handle_data_members(xns,
                             xrep_poset_id,
                             xrep_member_id,
                             xbase_space_poset_id,
                             xfiber_space_poset_id,
                             xlocal_schema_poset_id);

  // Get write access.

  get_read_write_access();

  // Initialize the row structure.

  initialize_standard_subposets(xname);
  initialize_standard_members();

  // Initialize the namespace features.

  initialize_namespace(*xns, xname);

  // Initialize the table dofs

  initialize_table_dofs(xrep_poset_id,
                        xrep_member_id,
                        xbase_space_poset_id,
                        xfiber_space_poset_id,
                        xlocal_schema_poset_id);

  // Set the standard number of id spaces.

  put_standard_id_space_ct(id_space_ct());

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());
  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(!is_valid(local_schema_poset_id()) == local_schema().is_attached());
  ensure(rep().is_attached());
  ensure(rep_poset_id() ==~ xrep_poset_id);
  ensure(rep_member_id() ==~ xrep_member_id);
  ensure(base_space_poset_id() == xbase_space_poset_id.hub_pod());
  ensure(base_space_member_id_ub().is_positive_definite());
  ensure(base_space_stride() == fiber_schema_member_id_ub().pod()*fiber_schema_stride());
  ensure(db() >= 0);
  ensure(fiber_schema_poset_id() == fiber_schema().index().hub_pod());
  ensure(fiber_schema_stride() == local_schema_member_id_ub().pod()*local_schema_stride());
  ensure(df() > 0);
  ensure(fiber_space_poset_id() == xfiber_space_poset_id.hub_pod());
  ensure(local_schema_poset_id() == xlocal_schema_poset_id.hub_pod());
  ensure(local_schema_member_id_ub().is_positive_definite());
  ensure(local_schema_stride() == 1);

  // Now we're finished, release all access

  release_access();

  if(xauto_access)
    xns->release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  return;
}

// STATE FACET

///
void
fiber_bundle::ternary_section_space_schema_poset::
detach_from_state()
{
  // Preconditions:

  // Body:

  _local_schema.detach_from_state();

  section_space_schema_poset::detach_from_state();

  // Postconditions:

  ensure(!is_attached());
  ensure(!rep().is_attached());
  ensure(!base_space().is_attached());
  ensure(!fiber_schema().is_attached());
  ensure(!local_schema().is_attached());

  // Exit

  return;
}


// SCHEMATIZATION FACET

///
bool
fiber_bundle::ternary_section_space_schema_poset::
is_schematized(bool xauto_access)
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result =
    fiber_schema().is_schematized(false) &&
    local_schema().is_schematized(false);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}


///
bool
fiber_bundle::ternary_section_space_schema_poset::
is_schematized(const scoped_index& xindex, bool xauto_access)

{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  scoped_index lfiber_id = get_fiber_schema_id_from_index(xindex);
  scoped_index llocal_id = get_local_schema_id_from_index(xindex);
  result =
    fiber_schema().is_schematized(lfiber_id, false) &&
    local_schema().is_schematized(llocal_id, false);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  /// @todo implement postconditions.

  //   ensure(result == includes_subposet(table_dof_subposet_name(xindex)));
  //   ensure(unexecutable(result == table dof subposet is_dof_subposet()));
  //   ensure(result == includes_subposet(row_dof_subposet_name(xindex)));
  //   ensure(unexecutable(result == row dof subposet is_dof_subposet()));

  // Exit

  return result;
}

///
void
fiber_bundle::ternary_section_space_schema_poset::
schematize(subposet* xtable_dof_subposet,
           subposet* xrow_dof_subposet,
           bool xall_members)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(dynamic_cast<primitives_poset_schema*>(schema().host()) != 0);
  // can only schematize posets which have same schema as primitives_poset
  require(xtable_dof_subposet != 0);
  require(includes_subposet(xtable_dof_subposet));
  require(xrow_dof_subposet != 0);
  require(includes_subposet(xrow_dof_subposet));


  // Body:

  not_implemented();

  /// @error this poset is immutable and does not support this operation

  // Postconditions:

  ensure(is_schematized(false));

  // Exit

  return;
}


// MEMBERSHIP INTERFACE

///
int
fiber_bundle::ternary_section_space_schema_poset::
member_ct()
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result =
    base_space().member_ct()*
    fiber_schema().member_ct()*
    local_schema().member_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}





///
int
fiber_bundle::ternary_section_space_schema_poset::
standard_member_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result =
    base_space().standard_member_ct()*
    fiber_schema().standard_member_ct()*
    local_schema().standard_member_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
member_index_ub()
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result(internal_id());

  result =
    base_space().member_index_ub().pod()*
    fiber_schema().member_index_ub().pod()*
    local_schema().member_index_ub().pod();


  // Postconditions:

  //   ensure(result >= 0);
  ensure(result.is_positive());

  return result;
}

///
sheaf::index_iterator
fiber_bundle::ternary_section_space_schema_poset::
member_iterator()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  not_implemented();

  /// @todo implement ternary_section_space_schema_poset::member_iterator()

  index_iterator  result;

  // Postconditions:

  // Exit

  return result;
}


///
bool
fiber_bundle::ternary_section_space_schema_poset::
contains_member(const scoped_index& xindex)

{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = base_space().contains_member(get_base_space_id_from_index(xindex)) &&
           fiber_schema().contains_member(get_fiber_schema_id_from_index(xindex)) &&
           local_schema().contains_member(get_local_schema_id_from_index(xindex));

  return result;
}

///
bool
fiber_bundle::ternary_section_space_schema_poset::
contains_member(const scoped_index& xindex, int xversion)

{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = base_space().contains_member(get_base_space_id_from_index(xindex), xversion) &&
           fiber_schema().contains_member(get_fiber_schema_id_from_index(xindex)) &&
           local_schema().contains_member(get_local_schema_id_from_index(xindex));

  return result;
}


///
bool
fiber_bundle::ternary_section_space_schema_poset::
is_jim(const scoped_index& xindex, bool xin_current_version)
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = base_space().is_jim(get_base_space_id_from_index(xindex), xin_current_version) &&
           fiber_schema().is_jim(get_fiber_schema_id_from_index(xindex)) &&
           local_schema().is_jim(get_local_schema_id_from_index(xindex));

  // Postconditions:

  // Exit

  return result;
}



///
bool
fiber_bundle::ternary_section_space_schema_poset::
is_atom(const scoped_index& xindex)

{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = base_space().is_atom(get_base_space_id_from_index(xindex)) &&
           fiber_schema().is_atom(get_fiber_schema_id_from_index(xindex)) &&
           local_schema().is_atom(get_local_schema_id_from_index(xindex));

  // Postconditions:

  // Exit

  return result;
}


///
bool
fiber_bundle::ternary_section_space_schema_poset::
contains_link(const scoped_index& xgreater, const scoped_index& xlesser)
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser));
  require(contains_member(xgreater));

  // Body:

  scoped_index lgreater_base_id = get_base_space_id_from_index(xgreater);
  scoped_index lgreater_fiber_id = get_fiber_schema_id_from_index(xgreater);
  scoped_index lgreater_local_id = get_local_schema_id_from_index(xgreater);
  scoped_index llesser_base_id = get_base_space_id_from_index(xlesser);
  scoped_index llesser_fiber_id = get_fiber_schema_id_from_index(xlesser);
  scoped_index llesser_local_id = get_local_schema_id_from_index(xlesser);

  result =
    (
      base_space().contains_link(lgreater_base_id, llesser_base_id) &&
      (lgreater_fiber_id == llesser_fiber_id) &&
      (lgreater_local_id == llesser_local_id)
    ) ||
    (
      (lgreater_base_id == llesser_base_id) &&
      fiber_schema().contains_link(lgreater_fiber_id, llesser_fiber_id)  &&
      (lgreater_local_id == llesser_local_id)
    ) ||
    (
      (lgreater_base_id == llesser_base_id) &&
      (lgreater_fiber_id == llesser_fiber_id) &&
      local_schema().contains_link(lgreater_local_id, llesser_local_id)
    );

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
fiber_bundle::ternary_section_space_schema_poset::
cover_ct(bool xlower, const scoped_index& xindex)

{
  size_type result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xindex));

  // Body:

  result = base_space().cover_ct(xlower, get_base_space_id_from_index(xindex)) +
           fiber_schema().cover_ct(xlower, get_fiber_schema_id_from_index(xindex)) +
           local_schema().cover_ct(xlower, get_local_schema_id_from_index(xindex));

  // Postconditions:

  // Exit

  return result;
}

///
bool
fiber_bundle::ternary_section_space_schema_poset::
le(const scoped_index& xgreater, const scoped_index& xlesser)
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser));
  require(contains_member(xgreater));

  // Body:

  scoped_index lgreater_base_id = get_base_space_id_from_index(xgreater);
  scoped_index llesser_base_id = get_base_space_id_from_index(xlesser);
  scoped_index lgreater_fiber_id = get_fiber_schema_id_from_index(xgreater);
  scoped_index llesser_fiber_id = get_fiber_schema_id_from_index(xlesser);
  scoped_index lgreater_local_id = get_local_schema_id_from_index(xgreater);
  scoped_index llesser_local_id = get_local_schema_id_from_index(xlesser);

  result = base_space().le(lgreater_base_id, llesser_base_id) &&
           fiber_schema().le(lgreater_fiber_id, llesser_fiber_id) &&
           local_schema().le(lgreater_local_id, llesser_local_id);

  // Postconditions:

  ensure(unexecutable(upset of xlesser contains xgreater));

  // Exit

  return result;
}

///
bool
fiber_bundle::ternary_section_space_schema_poset::
leqv(const scoped_index& xgreater, const scoped_index& xlesser)
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser));
  require(contains_member(xgreater));

  // Body:

  scoped_index lgreater_base_id = get_base_space_id_from_index(xgreater);
  scoped_index llesser_base_id = get_base_space_id_from_index(xlesser);
  scoped_index lgreater_fiber_id = get_fiber_schema_id_from_index(xgreater);
  scoped_index llesser_fiber_id = get_fiber_schema_id_from_index(xlesser);
  scoped_index lgreater_local_id = get_local_schema_id_from_index(xgreater);
  scoped_index llesser_local_id = get_local_schema_id_from_index(xlesser);

  result = base_space().leqv(lgreater_base_id, llesser_base_id) &&
           fiber_schema().leqv(lgreater_fiber_id, llesser_fiber_id) &&
           local_schema().leqv(lgreater_local_id, llesser_local_id);

  // Postconditions:

  ensure(unexecutable(upset of xlesser contains xgreater));

  // Exit

  return result;
}

///
bool
fiber_bundle::ternary_section_space_schema_poset::
is_jem(const scoped_index& xindex, const scoped_index& xother)

{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xindex));
  require(contains_member(xother));

  // Body:

  result =
    base_space().is_jem(get_base_space_id_from_index(xindex), get_base_space_id_from_index(xother)) &&
    fiber_schema().is_jem(get_fiber_schema_id_from_index(xindex), get_fiber_schema_id_from_index(xother)) &&
    local_schema().is_jem(get_local_schema_id_from_index(xindex), get_local_schema_id_from_index(xother));


  // Postconditions:

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
greatest_jem(const scoped_index& xindex)
{
  scoped_index result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xindex));

  // Body:

  scoped_index lbase_jem = base_space().greatest_jem(get_base_space_id_from_index(xindex));
  scoped_index lfiber_jem = fiber_schema().greatest_jem(get_fiber_schema_id_from_index(xindex));
  scoped_index llocal_jem = local_schema().greatest_jem(get_local_schema_id_from_index(xindex));

  result = get_index_from_components(lbase_jem, lfiber_jem, llocal_jem);

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
least_jem(const scoped_index& xindex)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xindex));

  // Body:

  scoped_index lbase_jem = base_space().least_jem(get_base_space_id_from_index(xindex));
  scoped_index lfiber_jem = fiber_schema().least_jem(get_fiber_schema_id_from_index(xindex));
  scoped_index llocal_jem = local_schema().least_jem(get_local_schema_id_from_index(xindex));

  scoped_index result = get_index_from_components(lbase_jem, lfiber_jem, llocal_jem);

  // Postconditions:

  // Exit

  return result;
}


///
void
fiber_bundle::ternary_section_space_schema_poset::
merge_jems(const scoped_index& xjem1, const scoped_index& xjem2)
{
  // Preconditions:

  require(xjem1 !=~ xjem2);
  require(!is_jem(xjem1, BOTTOM_INDEX));
  require(state_is_read_write_accessible());
  require(contains_member(xjem1));
  require(contains_member(xjem2));
  require(!is_jim(xjem1));
  require(!is_jim(xjem2));
  require(cover_is_equal(LOWER, xjem1, xjem2));

  // Body:

  not_implemented();

  /// @todo make this class immutable; remove this function

  // Postconditions:

  ensure(le(xjem1, xjem2));

  // Exit

  return;
}


// SUBPOSET INTERFACE

///
int
fiber_bundle::ternary_section_space_schema_poset::
subposet_ct()
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result =
    base_space().subposet_ct()*
    fiber_schema().subposet_ct()*
    local_schema().subposet_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

///
int
fiber_bundle::ternary_section_space_schema_poset::
standard_subposet_ct()
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result =
    base_space().standard_subposet_ct()*
    fiber_schema().standard_subposet_ct()*
    local_schema().standard_subposet_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
subposet_index_ub()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result; // Unscoped.
  result.put_pod( base_space().subposet_index_ub().pod()*
                  fiber_schema().subposet_index_ub().pod()*
                  local_schema().subposet_index_ub().pod() );

  // Postconditions:

  ensure(result >= 0);

  return result;
}


///
int
fiber_bundle::ternary_section_space_schema_poset::
version_ct()
{
  int result = 0;

  // Preconditions:

  // Body:

  not_implemented();

  ensure(result >= 0);

  // Exit

  return result;
}

///
int
fiber_bundle::ternary_section_space_schema_poset::
version()
{
  int result = 0;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure( has_version(result) );

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
version_index(int xversion)
{
  scoped_index result;

  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(includes_subposet(result));

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
version_jims_index(int xversion)
{
  scoped_index result;

  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(includes_subposet(result));

  // Exit

  return result;
}


///
sheaf::pod_index_type
fiber_bundle::ternary_section_space_schema_poset::
local_schema_poset_id()
{
  //  scoped_index result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  pod_index_type result = table_dof_tuple_ptr()->local_schema_id.poset_id;

  // Postconditions:

  ensure(name_space()->contains_member(result));

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
local_schema_member_id_ub()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result(_local_schema.internal_id());
  result = table_dof_tuple_ptr()->local_schema_member_id_ub;

  // Postconditions:


  // Exit

  return result;
}

///
int
fiber_bundle::ternary_section_space_schema_poset::
local_schema_stride()
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = table_dof_tuple_ptr()->local_schema_stride;

  // Postconditions:

  ensure(result > 0);

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
get_index_from_components(const scoped_index& xbase_space_id,
                          const scoped_index& xfiber_schema_id,
                          const scoped_index& xlocal_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().contains_member(xbase_space_id));
  require(fiber_schema().contains_member(xfiber_schema_id));
  require(local_schema().contains_member(xlocal_schema_id));


  // Body:

  scoped_index result(internal_id());

  result =
    xbase_space_id.pod()*base_space_stride() +
    xfiber_schema_id.pod()*fiber_schema_stride() +
    xlocal_schema_id.pod();

  // Postconditions:

  // Exit

  return result;
}



///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
get_base_space_id_from_index(const scoped_index& xindex) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space_stride() > 0);

  // Body:

  scoped_index result(_base_space.internal_id());

  // Assumes base space id is first index, fiber schema id is second.

  result = xindex.pod()/base_space_stride();

  // Postconditions:

  ensure(result < base_space_member_id_ub());

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
get_fiber_schema_id_from_index(const scoped_index& xindex)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_stride() > 0);

  require(fiber_schema_member_id_ub().is_positive_definite());

  // Body:

  scoped_index result(_fiber_schema.internal_id());

  pod_index_type lfiber_schema_member_id_ub =
    table_dof_tuple_ptr()->fiber_schema_member_id_ub;

  pod_index_type lfiber_schema_stride =
    table_dof_tuple_ptr()->fiber_schema_stride;

  result = (xindex.pod()/lfiber_schema_stride) % lfiber_schema_member_id_ub;

  // Postconditions:

  ensure(result < fiber_schema_member_id_ub());

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
get_local_schema_id_from_index(const scoped_index& xindex)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(local_schema_stride() == 1);

  // Body:

  scoped_index result(_local_schema.internal_id());

  pod_index_type llocal_schema_member_id_ub =
    table_dof_tuple_ptr()->local_schema_member_id_ub;

  result = xindex % llocal_schema_member_id_ub;

  // Postconditions:

  ensure(result < local_schema_member_id_ub());

  // Exit

  return result;
}


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

///
sheaf::schema_poset_member*
fiber_bundle::ternary_section_space_schema_poset::
new_schema_handle(const string& xid_space_name,
                  pod_index_type xschema_member_ext_id,
                  pod_index_type xbase_space_ext_id,
                  pod_index_type xfiber_schema_ext_id,
                  pod_index_type xlocal_schema_ext_id)
{
  // Preconditions:

  // Body:

  // Create a handle of the type appropriate for members of this
  // which will be used as a schema.

  schema_poset_member* result = new ternary_section_space_schema_member();

  // Get the internal id for the base space.

  scoped_index lbase_id =
    base_space().get_int_id(xbase_space_ext_id, xid_space_name, false);

  // Get the internal id for the fiber schema.

  scoped_index lfiber_id =
    fiber_schema().get_int_id(xfiber_schema_ext_id, xid_space_name, false);

  // Get the internal id for the local schema.

  scoped_index llocal_id =
    local_schema().get_int_id(xlocal_schema_ext_id, xid_space_name, false);

  // Get the member id from its components

  scoped_index lint_id =
    get_index_from_components(lbase_id, lfiber_id, llocal_id);

  // Attach the handle.

  result->attach_to_state(this, lint_id);

  // Postconditions:

  ensure(result != 0);
  ensure(schema_is_ancestor_of(result));
  ensure(result->is_attached());

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::ternary_section_space_schema_poset::
prereq_id(int xi) const
{
  scoped_index result; // Unscoped.

  // Preconditions:

  // Body:

  switch(xi)
  {
  case 0: // schema
    result = schema().host()->index();
    break;
  case 1: // rep
    result = _rep.host()->index();
    break;
  case 2: // fiber space
    result = _fiber_space.index();
    break;
  case 3: // base
    result = _base_space.index();
    break;
  case 4: // local schema
    result = _local_schema.index();
    break;
  default:
    result.invalidate();
    break;
  }


  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS


///
void
fiber_bundle::ternary_section_space_schema_poset::
new_state(schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(is_external());
  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());
  require(xschema.host()->name_space()->is_same_state(name_space()));
  require(name_space()->le(index(), xschema.host()->index()));
  require(xschema.is_schematized(false));

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable(xschema.is_same_state(xdof_map.schema())));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&xschema, TERNARY_SECTION_SPACE_SCHEMA_POSET_ID);

  // Attach the component handles.

  table_dof_tuple_type* ltable_dofs = reinterpret_cast<table_dof_tuple_type*>(xdof_map.dof_tuple());

  // $$SCRIBBLE: auto conversion from pod_index_type to scoped_index in
  // following call will make args unscoped, which is what we want here.

  attach_handle_data_members(name_space(),
                             ltable_dofs->rep_id.poset_id,
                             ltable_dofs->rep_id.member_id,
                             ltable_dofs->base_space_id.poset_id,
                             ltable_dofs->fiber_space_id.poset_id,
                             ltable_dofs->local_schema_id.poset_id);

  // Get write access.

  get_read_write_access();

  // Initialize the table dofs.
  // Must be called before initialize_standard_members
  // because precondition contains_member in put_member_dof_tuple_id
  // called from new_member indirectly needs table dofs.

  initialize_table_dof_tuple(&xdof_map);

  // Initialize the row structure.

  initialize_standard_subposets(name_space()->member_name(index()));
  initialize_standard_members();

  // Set the standard number of id spaces.

  put_standard_id_space_ct(id_space_ct());

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());
  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(fiber_space().is_attached());
  ensure(local_schema().is_attached());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  return;
}

///
fiber_bundle::ternary_section_space_schema_poset::table_dof_tuple_type::
table_dof_tuple_type()
{
  // Preconditions:

  // Body:

  base_space_member_id_ub   = LOCAL_SCHEMA_MEMBER_ID_UB;
  local_schema_member_id_ub = LOCAL_SCHEMA_MEMBER_ID_UB;
  local_schema_stride       = 0;

  local_schema_id = namespace_relative_member_index::INVALID().pod();


  // Postconditions:

  ensure(!rep_id.is_valid());
  ensure(!base_space_id.is_valid());
  ensure(base_space_member_id_ub == BASE_SPACE_MEMBER_ID_UB/LOCAL_SCHEMA_MEMBER_ID_UB);
  ensure(base_space_stride == 0);
  ensure(db == 0);
  ensure(!fiber_schema_id.is_valid());
  ensure(fiber_schema_member_id_ub == FIBER_SCHEMA_MEMBER_ID_UB);
  ensure(fiber_schema_stride == 0);
  ensure(df == 0);
  ensure(!fiber_space_id.is_valid());
  ensure(!local_schema_id.is_valid());
  ensure(local_schema_member_id_ub == LOCAL_SCHEMA_MEMBER_ID_UB);
  ensure(local_schema_stride == 0);

  // Exit

  return;
}

///
void
fiber_bundle::ternary_section_space_schema_poset::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  section_space_schema_poset::attach_handle_data_members();

  scoped_index lposet_id(name_space()->internal_id());
  lposet_id = table_dof_tuple_ptr()->local_schema_id.poset_id;
  local_schema().attach_to_state(name_space(), lposet_id);

  // Postconditions:

  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(local_schema().is_attached());

  // Exit

  return;
}

// ===========================================================
// PRIVATE MEMBR FUNCTIONS
// ===========================================================


///
void
fiber_bundle::ternary_section_space_schema_poset::
attach_handle_data_members(namespace_poset* xns,
                           const scoped_index& xrep_poset_id,
                           const scoped_index& xrep_member_id,
                           const scoped_index& xbase_space_poset_id,
                           const scoped_index& xfiber_space_poset_id,
                           const scoped_index& xlocal_schema_poset_id)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());
  require(xns->contains_poset_member(xrep_poset_id, xrep_member_id));
  require(xns->contains_poset(xbase_space_poset_id));
  require(xns->contains_poset(xfiber_space_poset_id));
  require(xns->contains_poset(xlocal_schema_poset_id));

  // Body:

  // Attach the rep handle.

  rep().attach_to_state(xns, xrep_poset_id, xrep_member_id);

  // Attach the component handles.

  base_space().attach_to_state(xns, xbase_space_poset_id);
  fiber_space().attach_to_state(xns, xfiber_space_poset_id);
  fiber_schema().attach_to_state(fiber_space().schema().host());
  local_schema().attach_to_state(xns, xlocal_schema_poset_id);

  // Attach the subposet handles.

  discretization().attach_to_state(&(base_space()), rep().discretization_subposet_name());
  if(is_multivalued())
  {
    multivalued().attach_to_state(&(base_space()), rep().multivalued_subposet_name());
  }
  evaluation().attach_to_state(&(base_space()), rep().evaluation_subposet_name());

  // Postconditions:

  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(local_schema().is_attached());
  ensure(discretization().is_attached());
  ensure(is_multivalued() ? multivalued().is_attached() : true);
  ensure(evaluation().is_attached());

  // Exit

  return;
}

///
void
fiber_bundle::ternary_section_space_schema_poset::
initialize_table_dofs(const scoped_index& xrep_poset_id,
                      const scoped_index& xrep_member_id,
                      const scoped_index& xbase_space_poset_id,
                      const scoped_index& xfiber_space_poset_id,
                      const scoped_index& xlocal_schema_poset_id)
{
  // Preconditions:

  require(base_space().is_attached());
  require(fiber_space().is_attached());
  require(fiber_schema().is_attached());
  require(local_schema().is_attached());

  /// @issue given the preconditions, what have any arguements at all?

  // Body:

  table_dof_tuple_type ldofs;

  // Initialize the rep ids.

  // $$TYPE_SAFE_IDS:

  ldofs.rep_id.poset_id              = xrep_poset_id.pod();
  ldofs.rep_id.member_id             = xrep_member_id.pod();

  // Initialize the component ids.

  ldofs.base_space_id.poset_id       = xbase_space_poset_id.hub_pod();
  ldofs.fiber_space_id.poset_id      = xfiber_space_poset_id.hub_pod();
  ldofs.fiber_schema_id.poset_id     = fiber_schema().index().hub_pod();
  ldofs.local_schema_id.poset_id     = xlocal_schema_poset_id.hub_pod();

  // Initialize the component id upper bounds

  ldofs.base_space_member_id_ub   = base_space().host()->member_index_ub().pod();
  ldofs.fiber_schema_member_id_ub = fiber_schema().host()->member_index_ub().pod();
  ldofs.local_schema_member_id_ub = local_schema().host()->member_index_ub().pod();

  // Initialize the component strides.

  ldofs.local_schema_stride = 1;
  ldofs.fiber_schema_stride = ldofs.local_schema_member_id_ub*ldofs.local_schema_stride;
  ldofs.base_space_stride   = ldofs.fiber_schema_member_id_ub*ldofs.fiber_schema_stride;

  ldofs.df = fiber_schema().schema().row_dof_ct();

  // Copy the table dof tuple to the state.

  initialize_table_dofs(&ldofs, sizeof(ldofs));

  // Postconditions:

  ensure(rep_poset_id() ==~ xrep_poset_id);
  ensure(rep_member_id() ==~ xrep_member_id);
  ensure(base_space_poset_id() == xbase_space_poset_id.hub_pod());

  ensure(base_space_member_id_ub().is_positive_definite());

  ensure(base_space_stride() == fiber_schema_member_id_ub().pod()*fiber_schema_stride());

  ensure(db() >= 0);
  ensure(fiber_schema_poset_id() == fiber_space().index().hub_pod());

  ensure(fiber_schema_member_id_ub().is_positive_definite());
  ensure(fiber_schema_stride() == local_schema_member_id_ub().pod()*local_schema_stride());

  ensure(df() > 0);
  ensure(fiber_space_poset_id() == xfiber_space_poset_id.hub_pod());
  ensure(local_schema_poset_id() == xlocal_schema_poset_id.hub_pod());

  ensure(local_schema().is_attached() ? local_schema_member_id_ub().is_positive_definite() : local_schema_member_id_ub().pod() == 1);

  ensure(local_schema_stride() == 1);

  // Exit

  return;
}

bool
fiber_bundle::ternary_section_space_schema_poset::
_has_prototype = make_prototype();

///
bool
fiber_bundle::ternary_section_space_schema_poset::
make_prototype()
{
  // Preconditions:


  // Body:

  poset_type ltype = TERNARY_SECTION_SPACE_SCHEMA_POSET_ID;

  ternary_section_space_schema_poset* lproto =
    new ternary_section_space_schema_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);


  // Postconditions:


  // Exit:

  return true;
}

