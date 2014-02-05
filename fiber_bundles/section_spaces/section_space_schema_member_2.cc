
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
/// Implementation for class section_space_schema_member.

#include "section_space_schema_member.impl.h"

#include "assert_contract.h"
#include "array_index_space_state.h"
#include "cover_set_iterator.h"
#include "discretization_iterator.h"
#include "index_space_iterator.h"
#include "mutable_index_space_handle.h"
#include "namespace_poset.h"
#include "sec_rep_descriptor.h"
#include "section_space_schema_poset.h"
#include "sheaves_namespace.h"
#include "std_set.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::section_space_schema_member::
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

const std::string&
fiber_bundle::section_space_schema_member::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("section_space_schema_member");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_member::
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

fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_member::
operator=(const section_space_schema_member& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  //Exit:

  return *this;
}

fiber_bundle::section_space_schema_member::
~section_space_schema_member()
{

  // Preconditions:

  // Body:

  _base_space.detach_from_state();
  _fiber_schema.detach_from_state();

  if(_discretization_id_space != 0)
  {
    _discretization_id_space->release_id_space(*_discretization_id_space);
  }

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_rep_descriptor&
fiber_bundle::section_space_schema_member::
rep()
{
  // Preconditions:

  require(is_attached());

  // Body:

  sec_rep_descriptor& result = host()->rep();

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::sec_rep_descriptor&
fiber_bundle::section_space_schema_member::
rep() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  sec_rep_descriptor& result = host()->rep();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
same_rep(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = rep().is_same_state(&xother.rep());

  // Postconditions:


  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_member::
base_space_id() const
{
  return _base_space_id;
}

void
fiber_bundle::section_space_schema_member::
base_space_id(scoped_index& result) const
{
  // Preconditions:

  require(is_factorable());

  // Body:

  result.put(_base_space.hub_id_space(), _base_space_id);

  // Postconditions:

  ensure(result.same_scope(base_space().hub_id_space()));

  // Exit:

  return;
}

sheaf::total_poset_member&
fiber_bundle::section_space_schema_member::
base_space()
{
  // Preconditions:

  require(is_factorable());

  // Body:

  return _base_space;
}

const sheaf::total_poset_member&
fiber_bundle::section_space_schema_member::
base_space() const
{
  // Preconditions:

  require(is_factorable());

  // Body:

  return _base_space;
}

bool
fiber_bundle::section_space_schema_member::
same_base_space(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());
  require(is_factorable());
  require(xother.is_factorable());

  // Body:

  result = base_space().is_same_state(&xother.base_space());

  // Postconditions:


  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_member::
fiber_schema_id() const
{
  return _fiber_schema_id;
}

void
fiber_bundle::section_space_schema_member::
fiber_schema_id(scoped_index& result) const
{
  // Preconditions:

  require(is_factorable());

  // Body:

  result.put(_fiber_schema.hub_id_space(), _fiber_schema_id);

  // Postconditions:

  ensure(result.same_scope(fiber_schema().hub_id_space()));

  // Exit:

  return;
}

sheaf::schema_poset_member&
fiber_bundle::section_space_schema_member::
fiber_schema()
{
  // Preconditions:

  require(is_factorable());

  // Body:

  return _fiber_schema;
}

const sheaf::schema_poset_member&
fiber_bundle::section_space_schema_member::
fiber_schema() const
{
  // Preconditions:

  require(is_factorable());

  // Body:

  return _fiber_schema;
}

bool
fiber_bundle::section_space_schema_member::
same_fiber_schema(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());
  require(is_factorable());
  require(xother.is_factorable());

  // Body:

  result = fiber_schema().is_same_state(&xother.fiber_schema());

  // Postconditions:


  // Exit:

  return result;
}


sheaf::poset&
fiber_bundle::section_space_schema_member::
fiber_space()
{
  // Preconditions:

  require(is_attached());

  // Body:

  poset& result = host()->fiber_space();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset&
fiber_bundle::section_space_schema_member::
fiber_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  poset& result = host()->fiber_space();

  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
db() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _db;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
evaluation_ct() const
{
  int result;

  // Preconditions:

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _evaluation_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
discretization_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _discretization_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
df() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());

  // Body:

  result = fiber_schema().row_dof_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
df(bool xauto_access)
{
  int result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(is_factorable());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = df();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
is_factorable() const
{
  // Preconditions:

  // Body:

  bool result = is_valid(_base_space_id) && is_valid(_fiber_schema_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::section_space_schema_member::
discretization()
{
  // Preconditions:

  // Body:

  subposet& result = host()->discretization();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_member::
discretization() const
{
  // Preconditions:

  // Body:

  subposet& result = host()->discretization();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
same_discretization(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = discretization().is_same_state(&xother.discretization());

  // Postconditions:


  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::section_space_schema_member::
evaluation()
{
  // Preconditions:

  // Body:

  subposet& result = host()->evaluation();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_member::
evaluation() const
{
  // Preconditions:

  // Body:

  subposet& result = host()->evaluation();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
same_evaluation(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = evaluation().is_same_state(&xother.evaluation());

  // Postconditions:


  // Exit:

  return result;
}

string
fiber_bundle::section_space_schema_member::
evaluator_family_name() const
{

  // Preconditions:

  require(is_attached());

  // Body:

  string result = rep().evaluator_family_name();

  // Postconditions:

  // Exit

  return result;
}

string
fiber_bundle::section_space_schema_member::
intersection_id_space_name(const subposet& xsp, pod_index_type xindex)
{
  // Preconditions:

  require(xsp.state_is_read_accessible());
  require(!xsp.name().empty());
  
  // Body:

  string result;

  if(xindex == TOP_INDEX)
  {
    result = xsp.name();
  }
  else
  {
    result = poset_path::make_reserved_name("", xindex,
					    xsp.name() + "_id_space");
  }
  
  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
fiber_bundle::section_space_schema_member::
intersection_id_space_name(const subposet& xsp, const scoped_index& xindex)
{
  // Preconditions:

  require(xsp.state_is_read_accessible());
  require(!xsp.name().empty());
  require(xindex.in_scope());
  
  // Body:

  string result = intersection_id_space_name(xsp, xindex);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_member::
conforms_to(const schema_poset_member& xother, bool xis_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_ancestor_of(&xother));

  // Body:

  // The dofs defined by this must agree in type and in order
  // with those defined by xother. For section_space_schema,
  // this obviously requires that the host, rep, and version
  // of this be the same as those of xother. In addition,
  // the fiber schema of this must exactly match the fiber
  // schema of xother and the initial part of the traversal of this
  // discretization must match the traversal of the xother
  // discretization. The only practical way to ensure this
  // is to require the base space of this and xother to be
  // exactly the same. Hence, section_space_schema only
  // conform if they are identical.

  result = is_same_state(&xother);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_space_schema_member::
section_space_schema_member()
{

  // Preconditions:

  // Body:

  // The following invalidate calls are not really neccessary but serve
  // to make things clearer.

  _base_space_id = invalid_pod_index();
  _fiber_schema_id = invalid_pod_index();

  _discretization_id_space = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
  ensure(!is_factorable());

  // Exit:
}

void
fiber_bundle::section_space_schema_member::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Initialize inherited data members

  schema_poset_member::attach_handle_data_members();

  // Comput the component member ids.

  if(_index == TOP_INDEX || _index == BOTTOM_INDEX)
  {
    // Component ids are the same as _index.

    _base_space_id = _index;
    _fiber_schema_id = _index;
  }
  else if(host()->is_homogeneous(_index))
  {
    // Component ids are factors of _index.

    host()->tuple(_index, _base_space_id, _fiber_schema_id);
  }
  else
  {
    // Components are not factors.

    _base_space_id = invalid_pod_index();
    _fiber_schema_id = invalid_pod_index();
  }
  
  // Attach the component handles

  if(is_valid(_base_space_id))
  {
    _base_space.attach_to_state(&(host()->base_space()), _base_space_id);
  }

  if(is_valid(_fiber_schema_id))
  {
    _fiber_schema.attach_to_state(&(host()->fiber_schema()), _fiber_schema_id);
  }

  /// @todo Remove.
  // $$SCRIBBLE: Remove version hack.

//   /// @hack section_space_schema version hack:
//   /// version of this is same as version of base space.

//   _base_space.put_version(_version, false);

  // Postconditions:

  ensure(!is_valid(base_space_id()) || base_space().is_attached());
  ensure(!is_valid(fiber_schema_id()) || fiber_schema().is_attached());

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_member::
contains_dof(pod_index_type xbase_id,
             pod_index_type xfiber_id,
             bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));
  require(host()->contains_member(xbase_id, xfiber_id, false));

  // Body:

  pod_index_type lid;
  host()->ordinal(xbase_id, xfiber_id, lid);

  result = contains_dof(lid, xin_table_dofs);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
contains_dof(const scoped_index& xbase_id,
             const scoped_index& xfiber_id,
             bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));

  // Body:

  return contains_dof(xbase_id.hub_pod(), xfiber_id.hub_pod());
}

// PROTECTED MEMBER FUNCTIONS

/// @todo Remove.
// void
// fiber_bundle::section_space_schema_member::
// update_table_cache() const
// {
//   // Preconditions:

//   require(state_is_read_accessible());

//   // Body:

//   if(!host()->member_id_spaces(false).contains(table_dof_subposet_name()))
//   {
//     // Create the table dof id space.

//     arg_list largs = array_index_space_state::make_arg_list(0);

//     pod_index_type lspace_id =
//       host()->new_member_id_space(table_dof_subposet_name(),
// 				  "array_index_space_state",
// 				  largs, false, false);

//     _table_dof_id_space =
//       &host()->member_id_spaces(false).get_id_space(lspace_id);

//     // Populate the table dof id map.

//     // The table dofs of the section space schema are the same as 
//     // the table dofs of the fiber space schema and map into
//     // the section space schema id space as (base bottom, fiber schema mbr).

//     mutable_index_space_handle* ltable_dof_id_space =
//       reinterpret_cast<mutable_index_space_handle*>(_table_dof_id_space);
//     ltable_dof_id_space->reserve(fiber_schema().table_dof_id_space().ct());

//     index_space_iterator& litr =
//       fiber_schema().table_dof_id_space().get_iterator();
//     while(!litr.is_done())
//     {
//       // Iterating over the ids of the fiber schema table dof id space
//       // in host (poset) order.

//       ltable_dof_id_space->insert(litr.pod(), litr.hub_pod());

//       litr.next();
//     }
//     fiber_schema().table_dof_id_space().release_iterator(litr);
//   }
//   else
//   {
//     _table_dof_id_space =
//       &host()->member_id_spaces(false).get_id_space(table_dof_subposet_name());
//   }
  
//   schema_poset_member::update_table_cache();

//   // Postconditions:

//   // Exit

//   return;
// }

void
fiber_bundle::section_space_schema_member::
update_table_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(is_factorable())
  {
    // Member is factorable, table dof id space is that same as
    // the fiber schema.

    mutable_index_space_handle* ltable_dof_id_space =
      reinterpret_cast<mutable_index_space_handle*>(_table_dof_id_space);
    ltable_dof_id_space->reserve(fiber_schema().table_dof_id_space().ct());

    // Table dof ids are the same as fiber schema.

    pod_index_type lid;

    index_space_iterator& litr =
      fiber_schema().table_dof_id_space().get_iterator();
    while(!litr.is_done())
    {
      host()->ordinal(BOTTOM_INDEX, litr.hub_pod(), lid);

      ltable_dof_id_space->push_back(lid);

      litr.next();
    }
    fiber_schema().table_dof_id_space().release_iterator(litr);
  }
  else
  {
    // Just another schema member.

    schema_poset_member::update_table_dof_id_space();
  }

  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
update_table_dof_descriptors() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(is_factorable())
  {
    // This member is factorable.  Copy the table dof descriptors from
    // the fiber schema.

    // (Re)allocate the dof descriptors.

    if(_table_dof_descriptors != 0)
    {
      _table_dof_descriptors->remove_reference();
    }
    _table_dof_descriptors = new dof_descriptor_array(_table_dof_ct);
    _table_dof_descriptors->add_reference();

    // Copy fiber schema dof descriptors.

    index_space_iterator& itr = _table_dof_id_space->get_iterator();
    while(!itr.is_done())
    {
      dof_descriptor_array::dof_descriptor& ldesc = (*_table_dof_descriptors)[itr.pod()];

      ldesc.size =      fiber_schema().size(itr.pod(), true);
      ldesc.alignment = fiber_schema().alignment(itr.pod(), true);
      ldesc.type =      fiber_schema().type(itr.pod(), true);
      ldesc.offset =    fiber_schema().offset(itr.pod(), true);

      itr.next();
    }
  
    _table_dof_tuple_ub = fiber_schema().table_dof_tuple_ub();

    // The last offset is the size of the entire tuple

    dof_descriptor_array::dof_descriptor& ldesc = (*_table_dof_descriptors)[_table_dof_ct];
    ldesc.size      = 0;
    ldesc.alignment = 0;
    ldesc.type      = NOT_A_PRIMITIVE_TYPE;
    ldesc.offset    = _table_dof_tuple_ub;
  }
  else
  {
    // Just another schema member.

    schema_poset_member::update_table_dof_descriptors();
  }

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NEW DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  const index_space_handle& result = *_discretization_id_space;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  const index_space_handle& result = *_discretization_id_space;

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space()
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  index_space_handle& result = *_discretization_id_space;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  index_space_handle& result = *_discretization_id_space;

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
fiber_schema_id_space(bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  
  // Body:

  const index_space_handle& result = fiber_schema().dof_id_space(xis_table_dofs);

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
fiber_schema_id_space(bool xis_table_dofs, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(is_factorable());
  
  // Body:

  const index_space_handle& result =
    fiber_schema().dof_id_space(xis_table_dofs, xauto_access);
  
  // Postconditions:


  // Exit:

  return result;
}


sheaf::size_type
fiber_bundle::section_space_schema_member::
size(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(xis_table_dof ? fiber_schema_id_space(xis_table_dof).contains(xdof_id) : true);
  
  // Body:
  
  size_type result = 0;

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
size(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
size(const scoped_index& xdisc_id,
     const scoped_index& xfiber_dof_id,
     bool xis_table_dof,
     bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
alignment(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(xis_table_dof ? fiber_schema_id_space(xis_table_dof).contains(xdof_id) : true);
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
alignment(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
alignment(const scoped_index& xdisc_id,
	  const scoped_index& xfiber_dof_id,
	  bool xis_table_dof,
	  bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::section_space_schema_member::
type(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(xis_table_dof ? fiber_schema_id_space(xis_table_dof).contains(xdof_id) : true);
  
  // Body:

  primitive_type result;

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::section_space_schema_member::
type(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  primitive_type result;

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::section_space_schema_member::
type(const scoped_index& xdisc_id,
     const scoped_index& xfiber_dof_id,
     bool xis_table_dof,
     bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  primitive_type result;

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
offset(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(xis_table_dof ? fiber_schema_id_space(xis_table_dof).contains(xdof_id) : true);
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
offset(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
offset(const scoped_index& xdisc_id,
       const scoped_index& xfiber_dof_id,
       bool xis_table_dof,
       bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result = 0;

  is_abstract();
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
fiber_size() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  
  // Body:

  size_type result = fiber_schema().dof_tuple_ub(false);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
fiber_size(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(is_factorable());
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  size_type result = fiber_size();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
component_size(pod_index_type xfiber_dof_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(is_factorable());
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  size_type result =
    fiber_schema().size(xfiber_dof_id, false)*_discretization_ct;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
component_size(const scoped_index& xfiber_dof_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(fiber_schema_id_space(false, xauto_access).contains(xfiber_dof_id));
  require(is_factorable());
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  pod_index_type lfiber_dof_id =
    fiber_schema_id_space(false).pod(xfiber_dof_id);
  size_type result = component_size(lfiber_dof_id);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::section_space_schema_member::
get_ext_id(const std::string& xid_space_name) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());

  /// @hack product subposet hack, ver 2.
  /// Section space schema member external ids are really base space external ids.

  // Can't support the following precondition:

  //  require(precondition_of(host()->get_ext_id(index(), xid_space_name)));

  // Instead:

  require(precondition_of(host()->base_space().get_ext_id(base_space_id(), xid_space_name)));


  // Body:

  pod_index_type result =
    host()->base_space().get_ext_id(base_space_id(), xid_space_name, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

/// @todo Remove.
// void
// fiber_bundle::section_space_schema_member::
// schematize()
// {
//   // Preconditions:

//   require(state_is_read_write_accessible());
//   require(host()->is_schematized(false));

//   // Body:

//   /// @error host is immutable; remove this member.

//   // Nothing to do.

//   // Postconditions:

//   ensure(is_schematized(false));

//   // Exit

//   return;
// }

fiber_bundle::schema_poset_member&
fiber_bundle::section_space_schema_member::
unrestricted_schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Memebers of this class don't have dof tuples,
  // so the unrestricted schema is always the schema of the host.

  schema_poset_member& result = host()->schema();

  // Postconditions:

  ensure(result.is_same_state(&(host()->schema())));

  // Exit

  return result;
}

const fiber_bundle::schema_poset_member&
fiber_bundle::section_space_schema_member::
unrestricted_schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Memebers of this class don't have dof tuples,
  // so the unrestricted schema is always the schema of the host.

  const schema_poset_member& result = host()->schema();

  // Postconditions:

  ensure(result.is_same_state(&(host()->schema())));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT INDEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

/// @todo Remove.
// $$SCRIBBLE: Remove version hack.

// void
// fiber_bundle::section_space_schema_member::
// put_version(int xversion, bool xunalias)
// {
//   // Preconditions:

//   require(state_is_read_accessible());
//   require(has_version(xversion));
//   require(!xunalias ? xversion != CURRENT_MEMBER_VERSION : true);

//   // Body:

//   schema_poset_member::put_version(xversion, xunalias);

//   if(is_factorable())
//   {
//     /// @hack section_space_schema version hack:
//     /// version of this is same as version of base space.

//     _base_space.put_version(xversion, xunalias);
//   }

//   // Postconditions:

//   ensure(xunalias ?
//          version(false) == unaliased_version(xversion) :
//          version(false) == xversion);

//   // Exit

//   return;
// }

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
attach_to_state(pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  pod_index_type lpod;
  host()->ordinal(xbase_space_id, xfiber_schema_id, lpod);

  _index = hub_id(lpod);
  _version = CURRENT_HOST_VERSION;

  attach_handle_data_members();

  // Postconditions:

  ensure(base_space_id() == xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id);
  ensure(fiber_schema().is_attached());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
attach_to_state(const scoped_index& xbase_space_id,
		const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  attach_to_state(xbase_space_id.hub_pod(),
		  xfiber_schema_id.hub_pod());

  // Postconditions:

  ensure(base_space_id() == xbase_space_id.hub_pod());
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id.hub_pod());
  ensure(fiber_schema().is_attached());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
		pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  pod_index_type lpod;
  xhost->ordinal(xbase_space_id, xfiber_schema_id, lpod);

  _host  = const_cast<section_space_schema_poset*>(xhost);
  _index = hub_id(lpod);
  _version = CURRENT_HOST_VERSION;

  attach_handle_data_members();

  // Postconditions:

  ensure(base_space_id() == xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id);
  ensure(fiber_schema().is_attached());

  // Exit:
  return;
}

void
fiber_bundle::section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
		const scoped_index& xbase_space_id,
		const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  attach_to_state(xhost,
		  xbase_space_id.hub_pod(),
		  xfiber_schema_id.hub_pod());

  // Postconditions:

  ensure(base_space_id() == xbase_space_id.hub_pod());
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id.hub_pod());
  ensure(fiber_schema().is_attached());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
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
  require(xhost->contains_range_member(xhost->base_space().member_id(xbase_path.member_name(), false),
				       xhost->fiber_schema().member_id(xfiber_schema_path.member_name(), false), false));

  // Body:

  attach_to_state(xhost,
                  xhost->base_space().member_id(xbase_path.member_name(), false),
                  xhost->fiber_schema().member_id(xfiber_schema_path.member_name(), false));

  // Postconditions:

  ensure(is_attached());
  ensure(base_space().has_path(xbase_path, false));
  ensure(fiber_schema().has_path(xfiber_schema_path, false));

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
detach_from_state()
{
  // Preconditions:

  // Body:

  _base_space.detach_from_state();
  _base_space_id = _base_space.index().pod();
  _fiber_schema.detach_from_state();
  _fiber_schema_id = _fiber_schema.index().pod();

  schema_poset_member::detach_from_state();

  // Postconditions:

  ensure(!is_attached());

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_member::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_space_schema_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(schema_poset_member::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    invariance(is_factorable() ? base_space().is_attached() : true);
    invariance(is_factorable() ? fiber_schema().is_attached() : true);

    /// @issue what are the invariants for this class
    /// @todo implement section_space_schema_member::invariant() const

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
// DEBUGGING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
to_stream(std::ostream& xos) const
{
  // Preconditions:


  // Body:

  xos << *this;

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

std::ostream& fiber_bundle::operator << (std::ostream &os, section_space_schema_member& p)
{

  // Preconditions:

  // Body:

  if (p.is_attached())
  {
    p.get_read_access();
    p.disable_invariant_check();
    os << "member:"
    << " host = \'" << p.host()->name() << "\'"
    << " index = " << p.index().pod()
    << " name = \'" << p.name() << '\''
    << " version= " << p.version(false)
    << " unaliased version= " << p.version()
    << endl;

    os << "base: member index = " << p.base_space().index().hub_pod()
    << " '" << p.base_space().name() << "'"
    << " in poset '" << p.base_space().host()->name() << "'"
    << endl
    << "fiber space is poset '" << p.fiber_space().name() << "'"
    << endl;

    p.release_access();
    p.enable_invariant_check();

  }
  else
  {
    os << "member: host = \'\'' index = -1 name = \'\''"
    << endl;
  }

  // Exit:

  return os;
}

