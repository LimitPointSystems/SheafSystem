
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
/// Implementation for class subposet

#include "SheafSystem/subposet.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/array_index_space_handle.h"
#include "SheafSystem/array_index_space_state.h"
#include "SheafSystem/block.h"
#include "SheafSystem/hash_index_space_handle.h"
#include "SheafSystem/hash_index_space_state.h"
#include "SheafSystem/interval_index_space_handle.h"
#include "SheafSystem/interval_index_space_state.h"
#include "SheafSystem/list_index_space_handle.h"
#include "SheafSystem/list_index_space_state.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/pool.h"
#include "SheafSystem/poset.h"
#include "SheafSystem/poset_member.h"
#include "SheafSystem/poset_powerset_state.h"
#include "SheafSystem/poset_slicer.h"
#include "SheafSystem/preorder_iterator.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/poset_joiner.h"
#include "SheafSystem/subposet_member_iterator.h"
#include "SheafSystem/subposet_state.h"
#include "SheafSystem/tern.h"

using namespace std;

// ===========================================================
// SUBPOSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::subposet::
subposet()
{

  // Preconditions

  // Body:

  // Nothing to do, data members already
  // initialized in poset_component::poset_component

  // Postconditions:

  ensure(invariant());
  ensure( !is_attached() );

  // Exit

  return;
}


sheaf::subposet::
subposet(const subposet& xother, bool xdeep_copy)
{

  // Preconditions

  require(xdeep_copy ? xother.state_is_read_write_accessible() : true);

  // Body:

  subposet& lother = const_cast<subposet&>(xother);

  if(xdeep_copy)
  {
    // Create a new state with the same membership
    // as xother and attach to it.

    new_state(lother.host(), false);
    lother.members()->equal_pa(members());
  }
  else
  {
    // Just attach to the same state as xother.

    attach_to_state(&lother);
  }

  // Postconditions:

  ensure( invariant() );
  ensure( has_same_host(&xother) );
  ensure( xdeep_copy ? is_equal_to(&xother) : is_same_state(&xother) );
  ensure( xdeep_copy ? name().empty() : true);

  // Exit

  return;
}

sheaf::subposet::
~subposet()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

sheaf::subposet::
subposet(poset_state_handle* xhost,
         const block<pod_index_type>* xmembers,
         bool xauto_access)
{

  // Preconditions

  require(xhost != 0);
  require(xhost->state_is_auto_read_write_accessible(xauto_access));
  require(xmembers != 0 ? xhost->contains_members(*xmembers, xauto_access) : true);

  // Body:

  if(xmembers != 0)
  {
    new_state(xhost, *xmembers, xauto_access);
  }
  else
  {
    new_state(xhost, true, xauto_access);
  }

  // Postconditions:

  if(xauto_access)
  {
    get_read_access();
  }

  ensure(invariant());
  ensure(host() == xhost);
  ensure(xmembers != 0 ? contains_members(*xmembers) : is_empty());
  ensure(is_persistent());

  if(xauto_access)
  {
    release_access();
  }

  // Exit

  return;
}

sheaf::subposet::
subposet(poset_state_handle* xhost,
         const block<scoped_index>& xmembers,
         bool xauto_access)
{

  // Preconditions

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xmembers, xauto_access);


  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

sheaf::subposet::
subposet(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->includes_subposet(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index().is_hub_scope());
  ensure(index() == xhub_id);
  ensure(is_attached());
}

sheaf::subposet::
subposet(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->includes_subposet(xid));

  // Body:

  attach_to_state(xhost, xid);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index().is_hub_scope());
  ensure(index() ==~ xid);
  ensure(is_attached());
}

sheaf::subposet::
subposet(const poset_state_handle* xhost, const std::string& xname)
{

  // Preconditions

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->includes_subposet(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure( invariant() );
  ensure( is_attached() );
  ensure( host() == xhost );
  ensure( name() == xname );

  // Exit

  return;
}

sheaf::subposet&
sheaf::subposet::
operator=(const subposet& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

void
sheaf::subposet::
new_state(bool xinitialize,  bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xinitialize, xauto_access)));

  // Body:

  new_state(host(), xinitialize, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xinitialize, xauto_access)));

  // Exit:

  return;
}

void
sheaf::subposet::
new_state(const block<pod_index_type>& xmembers, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xmembers, xauto_access)));

  // Body:

  new_state(host(), xmembers, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xmembers, xauto_access)));

  // Exit:

  return;
}

void
sheaf::subposet::
new_state(const block<scoped_index>& xmembers, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xmembers, xauto_access)));

  // Body:

  new_state(host(), xmembers, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xmembers, xauto_access)));

  // Exit:

  return;
}

void
sheaf::subposet::
new_state(poset_state_handle* xhost,
          bool xinitialize,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_auto_read_write_accessible(xauto_access));

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  // Body:

  _host = xhost;
  _host->new_subposet(xinitialize, _index);
  _version = CURRENT_HOST_VERSION;

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(is_persistent());
  ensure(xinitialize ? is_empty() : true);

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  } 

  // Exit

  return;
}

void
sheaf::subposet::
new_state(poset_state_handle* xhost,
          const block<pod_index_type>& xmembers,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_auto_read_write_accessible(xauto_access));

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  require(xhost->contains_members(xmembers));

  // Body:

  _host = xhost;
  _index.put(host()->subposet_hub_id_space(false), _host->new_subposet(xmembers));
  _version = CURRENT_HOST_VERSION;

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(contains_members(xmembers));
  ensure(is_persistent());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  } 

  // Exit

  return;
}

void
sheaf::subposet::
new_state(poset_state_handle* xhost,
          const block<scoped_index>& xmembers,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_auto_read_write_accessible(xauto_access));

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  require(xhost->contains_members(xmembers));

  // Body:

  _host = xhost;
  _host->new_subposet(xmembers, _index);
  _version = CURRENT_HOST_VERSION;

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(contains_members(xmembers));
  ensure(is_persistent());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  } 

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ID SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::scattered_insertion_index_space_handle&
sheaf::subposet::
id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(has_id_space());

  // Body:

  const scattered_insertion_index_space_handle& result =
    powerset_member(index())->id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::scattered_insertion_index_space_handle&
sheaf::subposet::
id_space()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(has_id_space());

  // Body:

  scattered_insertion_index_space_handle& result =
    powerset_member(index())->id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::scattered_insertion_index_space_handle&
sheaf::subposet::
new_id_space(const std::string& xstate_class_name)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!name().empty());
  require(!has_id_space());
  require(!host()->member_id_spaces(false).contains(id_space_name()));
  require(!xstate_class_name.empty());
  require(unexecutable("xstate_class_name is a descendant of scattered_insertion_index_space_state"));

  // Body:

  /// @hack Using the name of the id space state is a temporary fix
  ///       until subposets become id spaces.  See COM-183.

  pod_index_type lid;

  if(xstate_class_name == "array_index_space_state")
  {
    lid = array_index_space_state::new_space(host()->member_id_spaces(false),
					     id_space_name(),
					     is_persistent(),
					     member_ct()).index();
  }
  else if(xstate_class_name == "hash_index_space_state")
  {
    lid = hash_index_space_state::new_space(host()->member_id_spaces(false),
					    id_space_name(),
					    is_persistent(),
					    member_ct()).index();
  }
  else if(xstate_class_name == "interval_index_space_state")
  {
    lid = interval_index_space_state::new_space(host()->member_id_spaces(false),
						id_space_name(),
						is_persistent(),
						true).index();
  }
  else if(xstate_class_name == "list_index_space_state")
  {
    lid = list_index_space_state::new_space(host()->member_id_spaces(false),
					    id_space_name(),
					    is_persistent()).index();
  }
  else
  {
    post_fatal_error_message("The id space type '" + xstate_class_name + "' is not supported.");
  }

  powerset_member(index())->put_id_space(host()->member_id_spaces(false), lid);

  scattered_insertion_index_space_handle& result = id_space();

  // Postconditions:

  ensure(invariant());
  ensure(has_id_space());
  ensure(id_space() == result);
  ensure(id_space().is_persistent() == is_persistent());

  // Exit:

  return result;
}

bool
sheaf::subposet::
has_id_space() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = powerset_member(index())->has_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::subposet::
is_persistent() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = powerset_member(index())->is_persistent();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::subposet::
put_is_persistent(bool xis_persistent)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  powerset_member(index())->put_is_persistent(xis_persistent);

  // Postconditions:

  ensure(is_persistent() == xis_persistent);
  ensure(has_id_space() ? id_space().is_persistent() == xis_persistent : true);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

std::string
sheaf::subposet::
id_space_name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());
  require(!name().empty());

  // Body:

  result = name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

void
sheaf::subposet::
attach_id_space()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!has_id_space());
  require(host()->member_id_spaces(false).contains(id_space_name()));

  // Body:

  powerset_member(index())->put_id_space(host()->member_id_spaces(false),
					 id_space_name());

  // Postconditions:

  ensure(has_id_space());

  // Exit:

  return;
} 

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF SUBPOSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::subposet::
is_dof_subposet() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = powerset_member(index())->is_dof_subposet();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::subposet::
put_is_dof_subposet(bool xis_dof_subposet)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  powerset_member(index())->put_is_dof_subposet(xis_dof_subposet);

  // Postconditions:

  ensure(is_dof_subposet() == xis_dof_subposet);

  // Exit:

  return;
}

int
sheaf::subposet::
dof_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = powerset_member(index())->dof_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

void
sheaf::subposet::
put_dof_ct(int xct)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(xct >= 0);

  // Body:

  powerset_member(index())->put_dof_ct(xct);

  // Postconditions:

  ensure(dof_ct() == xct);

  // Exit:

  return;
}

sheaf::dof_descriptor_array*
sheaf::subposet::
dof_descriptors() const
{
  dof_descriptor_array* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = powerset_member(index())->dof_descriptors();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::subposet::
put_dof_descriptors(const dof_descriptor_array* xoffsets)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  powerset_member(index())->put_dof_descriptors(xoffsets);

  // Postconditions:

  ensure(dof_descriptors() == xoffsets);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
sheaf::subposet::
member_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  /// @todo in subposet::member_ct(), implement O(1) algorithm
  /// This routine can be made O(1) by storing _member_Ct and updating
  /// it everythime insert or remove is called. The various set operations
  /// will invalidate the count, so they should set _member_ct negative
  /// and the current implementation used in that case

  int result = members()->true_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

sheaf::subposet_member_iterator*
sheaf::subposet::
member_iterator() const
{
  subposet_member_iterator* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet* cthis = const_cast<subposet*>(this);
  result = new subposet_member_iterator(*cthis);

  // Postconditions:

  // Exit

  return result;
}

sheaf::index_iterator
sheaf::subposet::
indexed_member_iterator() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  index_iterator result(members(), _host->member_hub_id_space(false));

  // Postconditions:

  ensure(!result.is_done() ? result.index().same_scope(host()->member_id(false)) : true);
  
  // Exit

  return result;
}

bool
sheaf::subposet::
contains_member(pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  zn_to_bool* lmembers = members();

  // Now query the bit vector.
  // We could incorporate the bounds check into the query
  // but it would be more expensive to evaluate.

  bool result = lmembers->index_in_bounds(xmbr_hub_id) ? (*lmembers)[xmbr_hub_id] : false;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::subposet::
contains_member(const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  return contains_member(xmbr_id.hub_pod());
}

bool
sheaf::subposet::
contains_member(const std::string& xname) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(!xname.empty());

  // Body:

  pod_index_type lindex = host()->member_id(xname, false);
  result = is_valid(lindex) ? contains_member(lindex) : false;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::subposet::
contains_members(const block<pod_index_type>& xmbr_hub_ids) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result = true;
  int i = 0;

  while(result && i < xmbr_hub_ids.ct())
  {
    result = contains_member(xmbr_hub_ids[i]);
    i++;
  };

  // Postconditions:

  ensure(unexecutable("for all i in xmbr_hub_ids: contains_member(i)")) ;

  // Exit

  return result;
}

bool
sheaf::subposet::
contains_members(const block<scoped_index>& xmbr_ids) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result = true;
  int i = 0;

  while(result && i < xmbr_ids.ct())
  {
    result = contains_member(xmbr_ids[i]);
    i++;
  };

  // Postconditions:

  ensure(unexecutable("for all i in xmbr_ids: contains_member(i)")) ;

  // Exit

  return result;
}

bool
sheaf::subposet::
contains_member(const abstract_poset_member* xmbr) const
{
  // Preconditions:

  require(xmbr != 0);

  // Body:

  bool result = contains_member(xmbr->index());

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::subposet::
insert_member(pod_index_type xmbr_hub_id)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  members()->put(xmbr_hub_id, true);

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xmbr_hub_id));

  // Exit:

  return;
}

void
sheaf::subposet::
insert_member(const scoped_index& xmbr_id)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  insert_member(xmbr_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xmbr_id));

  // Exit:

  return;
}

void
sheaf::subposet::
insert_members(const block<pod_index_type>& xmbr_hub_ids)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  for(int i=0; i<xmbr_hub_ids.ct(); i++)
  {
    members()->put(xmbr_hub_ids[i], true);
  }

  // Postconditions:

  ensure(invariant());
  ensure(contains_members(xmbr_hub_ids));

  // Exit:

  return;
}

void
sheaf::subposet::
insert_members(const block<scoped_index>& xmbr_ids)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  for(int i=0; i<xmbr_ids.ct(); i++)
  {
    members()->put(xmbr_ids[i].hub_pod(), true);
  }

  // Postconditions:

  ensure(invariant());
  ensure(contains_members(xmbr_ids));

  // Exit:

  return;
}

void
sheaf::subposet::
insert_member(const abstract_poset_member* xmbr)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  members()->put(xmbr->index().hub_pod(), true);

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xmbr));

  // Exit:

  return;
}

void
sheaf::subposet::
remove_member(pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  members()->put(xmbr_hub_id, false);

  // Postconditions:

  ensure(invariant());
  ensure(!contains_member(xmbr_hub_id));

  // Exit:

  return;
}

void
sheaf::subposet::
remove_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  remove_member(xmbr_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(!contains_member(xmbr_id));

  // Exit:

  return;
}

void
sheaf::subposet::
remove_member(const abstract_poset_member* xmbr)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  members()->put(xmbr->index().hub_pod(), false);

  // Postconditions:

  ensure(invariant());
  ensure(!contains_member(xmbr));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::zn_to_bool*
sheaf::subposet::
members() const
{
  zn_to_bool* result;

  // Preconditions:

  require(is_attached());
  require(state_is_read_accessible());

  // Body:

  /// @todo members() is used by most of the member functions.
  /// subposet should probably have a handle data member to
  /// avoid the cost of this lookup.

  result = powerset_member(index())->members();

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

sheaf::zn_to_bool::word_t*
sheaf::subposet::
membership() const
{
  zn_to_bool::word_t* result;

  // Preconditions:

  require(is_attached());
  require(state_is_read_accessible());

  // Body:

  result = members()->values();

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SET ALGEBRA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::subposet::
is_empty() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = members()->is_false();

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::subposet::
make_empty()
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  members()->make_false_sa();

  // Postconditions:

  // Exit

  return;
}

bool
sheaf::subposet::
is_equal_to(const subposet* other) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(other != 0);
  require(host()->is_same_state(other->host()));

  // Body:

  result = members()->is_equal_to(other->members());

  // Postconditions:

  ensure(unexecutable(other has same mebrs as this));

  // Exit

  return result;
}

void
sheaf::subposet::
make_equal_to(const subposet* other)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(other != 0);
  require(host()->is_same_state(other->host()));

  // Body:

  other->members()->equal_pa(members());

  // Postconditions:

  // Exit

  return;
}

bool
sheaf::subposet::
includes(const subposet* other) const
{
  bool result;

  // Preconditions:

  require(other != 0);

  // Body:

  result = members()->includes(other->members());

  // Postconditions:

  // Exit

  return result;
}

sheaf::subposet*
sheaf::subposet::
p_union(const subposet* other)
{
  subposet* result;

  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0);
  require( host() == other->host());

  // Body:

  result = new subposet( host() );
  p_union_pa(other, result);

  // Postconditions:

  ensure(result != 0);

  // for all i: result->contains_member(i) == contains_member(i) || other->contains_member(i)

  ensure(invariant());

  // Exit

  return result;
}

void
sheaf::subposet::
p_union_pa(const subposet* other, subposet* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0 );
  require( host() == other->host());
  require( result != 0 );
  require( host() == result->host());

  // Body:

  members()->b_or_pa(other->members(), result->members());

  // Postconditions:

  // for all i: result->contains_member(i) == contains_member(i) || other->contains_member(i)

  ensure(invariant());

  // Exit:

  return;
}

void
sheaf::subposet::
p_union_sa(const subposet* other)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0 );
  require( host() == other->host());

  // Body:

  p_union_pa(other, this);

  // Postconditions:

  ensure(unexecutable("for all i: contains_member(i) == old contains_member(i) || other->contains_member(i)"));
  ensure(invariant());

  // Exit:

  return;
}

sheaf::subposet*
sheaf::subposet::
p_intersection(const subposet* other)
{
  subposet* result;

  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0);
  require( host() == other->host());

  // Body:

  result = new subposet( host() );

  p_intersection_pa(other, result);

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);
  ensure(postcondition_of(p_intersection_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
p_intersection_pa(const subposet* other, subposet* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0 );
  require( host() == other->host());
  require( result != 0 );
  require( host() == result->host());

  // Body:

  members()->b_and_pa(other->members(), result->members());

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(forall i: result->contains_member(i) ==
                      old contains_member(i) && other->contains_member(i)));

  // Exit

  return;
}

void
sheaf::subposet::
p_intersection_sa(const subposet* other)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0 );
  require( host() == other->host());

  // Body:

  p_intersection_pa(other, this);

  // Postconditions:

  ensure(postcondition_of(p_intersection_pa));

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
p_minus(const subposet* other)
{
  subposet* result;

  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0);
  require( host() == other->host());

  // Body:

  result = new subposet( host());

  p_minus_pa(other, result);

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);
  ensure(postcondition_of(p_minus_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
p_minus_pa(const subposet* other, subposet * result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0 );
  require( host() == other->host());
  require( result != 0 );
  require( host() == result->host());

  // Body:

  members()->b_and_not_pa(other->members(), result->members());

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable("forall i: result->contains_member(i) == old contains_member(i) && !other->contains_member(i)"));

  // Exit

  return;
}

void
sheaf::subposet::
p_minus_sa(const subposet* other)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( other != 0 );
  require( host() == other->host());

  // Body:

  p_minus_pa(other, this);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(p_minus_pa));

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
p_not()
{
  subposet* result = 0; // initialize just to keep compiler from complaining

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet( host());

  p_not_pa(result);

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

void
sheaf::subposet::
p_not_pa(subposet* result)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(result != 0);

  // Body:

  members()->b_not_pa(result->members());

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

void
sheaf::subposet::
p_not_sa()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  members()->b_not_sa();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET ALGEBRA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::subposet*
sheaf::subposet::
extremals(bool xmaximals)
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host());
  extremals_pa(xmaximals, result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(extremals_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
extremals_pa(bool xmaximals, subposet* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );
  require( result->host() == host() );
  require( result->is_empty() );
  require( !is_same_state(result) );

  // Body:

  // Prepare an down/up set iterator
  // down for maximals, up for minimals

  preorder_iterator itr(host()->top(), "", xmaximals);

  // We want iteration in the loop below to be strict.
  // Since we don't reference itr again until we reset it,
  // can set strict now to keep it out of the loop.

  /// @issue why can't we just created it strict?

  itr.put_strict(true);

  // Iterate over the directional-set of each member of this

  // Must intialize itr outside
  // the loop below and can not
  // avoid marking some member visited when
  // we do. So insert first member in result
  // whether itr has visited it or not.

  bool first = true;

  index_iterator sp_itr = indexed_member_iterator();
  while(!sp_itr.is_done())
  {
    scoped_index lsp_mbr_id = sp_itr.index();

    if(first || !itr.has_visited(lsp_mbr_id))
    {
      first = false;

      // Current member is not bounded by some
      // member that has already been visited so
      // assume it is extremal

      result->insert_member(lsp_mbr_id);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not reseting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      itr.put_anchor(lsp_mbr_id);
      itr.reset(sheaf::NO_RESET);
      while(!itr.is_done())
      {
        result->remove_member(itr.index());
        itr.next();
      }
    }
    sp_itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result contains extremal members of this));

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
maximals()
{
  subposet* result;

  // Preconditions:

  require(precondition_of(extremals(true)));

  // Body:

  result = extremals(true);

  // Postconditions:

  ensure(postcondition_of(extremals(true)));

  // Exit:

  return result;
}

void
sheaf::subposet::
maximals_pa(subposet* result)
{
  // Preconditions:

  require(precondition_of(extremals_pa(true, result)));

  // Body:

  extremals_pa(true, result);

  // Postconditions:

  ensure(postcondition_of(extremals_pa(true, result)));

  // Exit:

  return;
}

sheaf::subposet*
sheaf::subposet::
minimals()
{
  subposet* result;

  // Preconditions:

  require(precondition_of(extremals(false)));

  // Body:

  result = extremals(false);

  // Postconditions:

  ensure(postcondition_of(extremals(false)));

  // Exit:

  return result;
}

void
sheaf::subposet::
minimals_pa(subposet* result)
{
  // Preconditions:

  require(precondition_of(extremals_pa(false, result)));

  // Body:

  extremals_pa(false, result);

  // Postconditions:

  ensure(postcondition_of(extremals_pa(false, result)));

  // Exit:

  return;
}

sheaf::subposet*
sheaf::subposet::
down() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host());
  down_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(down_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
down_pa(subposet* result) const
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );
  require( result->host() == host() );
  require( result->is_empty());

  // Body:

  poset_slicer slicer(host());
  slicer.down_set_pa(this, result);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
up() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host());
  up_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(up_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
up_pa(subposet* result) const
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );
  require( result->host() == host() );
  require( result->is_empty() );

  // Body:

  poset_slicer slicer(host());
  slicer.up_set_pa(this, result);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host());
  jims_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result contains jims in down set
                        of this));

  // Exit

  return result;
}

void
sheaf::subposet::
jims_pa(subposet* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );
  require( result->host() == host());
  require( result->is_empty() );

  // Body:

  poset_slicer slicer(host());
  slicer.find_jims_pa(this, result);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result contains jims in down set
                        of this));

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
maximal_jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host());
  maximal_jims_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(maximal_jims_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
maximal_jims_pa(subposet* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );
  require( result->host() == host() );
  require( result->is_empty() );

  // Body:

  poset_slicer slicer(host());
  slicer.find_jims_pa(this, result, poset_slicer::MAXIMAL);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::subposet*
sheaf::subposet::
minimal_jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host());
  minimal_jims_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(minimal_jims_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
minimal_jims_pa(subposet* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );
  require( result->host() == host() );
  require( result->is_empty() );

  // Body:

  poset_slicer slicer(host());
  slicer.find_jims_pa(this, result, poset_slicer::MINIMAL);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::poset_member*
sheaf::subposet::
p_join()
{
  poset_member* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new poset_member();
  p_join_pa(result);

  // Postconditions:

  require(invariant());
  require(postcondition_of(p_join_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
p_join_pa(abstract_poset_member* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );

  // Body:

  /// @todo implement subposet::p_join_pa

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}


sheaf::poset_member*
sheaf::subposet::
p_meet()
{
  poset_member* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new poset_member();
  p_meet_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(p_meet_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
p_meet_pa(abstract_poset_member* result)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );

  // Body:

  /// @todo implement subposet::p_meet_pa

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// LATTICE ALGEBRA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_member*
sheaf::subposet::
l_join(bool xnew_jem)
{
  poset_member* result;

  // Preconditions:

  require(state_is_read_write_accessible());
  /// @hack the join of the empty subset is well defined (== bottom)
  /// but this implmentation doesn't support it.
  require(!is_empty());

  // Body:

  result = new poset_member();
  l_join_pa(result);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(l_join_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
l_join_pa(abstract_poset_member* result, bool xnew_jem)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );

  // Body:

  if(is_empty())
  {
    // The join of the empty set is the bottom.

    if(xnew_jem)
    {
      result->new_jem_state(&host()->bottom(), true, false);
    }
    else
    {
      result->attach_to_state(&host()->bottom());
    }
  }
  else
  {
    // Join the members.

    poset_joiner joiner(host());
    joiner.join(this, (xnew_jem ? tern::TRUE : tern::NEITHER), *result);
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::poset_member*
sheaf::subposet::
l_join_jims(bool xnew_jem)
{
  poset_member* result;

  // Preconditions:

  require(state_is_read_write_accessible());
  require(unexecutable(this is a down set
                         containing only jims));


  // Body:

  result = new poset_member();
  l_join_jims_pa(result, xnew_jem);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(l_join_jims_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
l_join_jims_pa(abstract_poset_member* result, bool xnew_jem)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require(unexecutable(this is a down set
                         containing only jims));
  require( result != 0 );

  // Body:

  poset_joiner joiner(host());
  joiner.join(this, (xnew_jem ? tern::TRUE : tern::NEITHER), *result);

  // Postconditions:

  ensure(invariant());

  // This routine adds members to this

  ensure(unexecutable(this->includes(old this)));

  // Includes the strict down set but may not contain result itself

  ensure(unexecutable("this includes the strict down set of result"));

  // Exit

  return;
}

sheaf::poset_member*
sheaf::subposet::
l_meet(bool xnew_jem)
{
  poset_member* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new poset_member();
  l_meet_pa(result, xnew_jem);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(l_meet_pa));

  // Exit

  return result;
}

void
sheaf::subposet::
l_meet_pa(abstract_poset_member* result, bool xnew_jem)
{
  // Preconditions:

  require( state_is_read_write_accessible() );
  require( result != 0 );

  // Body:

  /// @todo optimize subposet::l_meet_pa
  /// Sorted list rep would be much more efficient than bitvector rep.
  /// Need to implement version of subposet that switches between reps

  subposet ljims0(host());
  subposet ljims1(host());

  subposet_member_iterator* itr = member_iterator();
  itr->jims_pa(&ljims0);
  itr->next();

  while(!itr->is_done())
  {
    itr->jims_pa(&ljims1);
    ljims0.p_intersection_sa(&ljims1);
    ljims1.make_empty();
    itr->next();
  }

  delete itr;

  ljims0.l_join_jims_pa(result, xnew_jem);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT INDEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::subposet::
is_valid_index(const poset_state_handle* xhost, pod_index_type xhub_id, int xversion) const
{
  bool result;

  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());

  // Body:

  // Subposets are the same for all versions; ignore xversion.

  result = xhost->includes_subposet(xhub_id, false);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::subposet::
is_valid_index(const poset_state_handle* xhost, const scoped_index& xid, int xversion) const
{
  bool result = false;

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(host_is_ancestor_of(xhost));

  // Body:

  return is_valid_index(xhost, xid.hub_pod(), xversion);
}

const sheaf::hub_index_space_handle&
sheaf::subposet::
hub_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const hub_index_space_handle& result = _host->subposet_hub_id_space(false);

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::scoped_index&
sheaf::subposet::
hub_id() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const scoped_index& result = _host->subposet_id(false);

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::subposet::
hub_id(pod_index_type xid) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result = _host->subposet_id(xid, false);

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::subposet::
get_index_from_name(const poset_state_handle* xhost, const std::string& xname) const
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  pod_index_type result = xhost->subposet_id(xname);

  // Postconditions:

  ensure(unexecutable(result.is_valid() implies subposet with index = result has name xname));

  // Exit

  return result;
}

void
sheaf::subposet::
get_index_from_name(const poset_state_handle* xhost, const std::string& xname,
		    scoped_index& result) const
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  xhost->subposet_id(xname, result);

  // Postconditions:

  ensure(unexecutable(result.is_valid() implies subposet with index = result has name xname));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

std::string
sheaf::subposet::
name(bool xauto_access) const
{
  string result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = host()->subposet_name(index(), xauto_access);

  // Postconditions:

  ensure(unexecutable(result.empty() implies this has no name));

  // Exit:

  return result;
}

void
sheaf::subposet::
all_names(block<std::string>& xresult, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  host()->all_subposet_names(_index, xresult, xauto_access);

  // Postconditions:

  ensure(xresult.ct() == name_ct(xauto_access));
  ensure_for_all(i, 0, xresult.ct(), !xresult[i].empty());

  // Exit:

  return;
}

sheaf::size_type
sheaf::subposet::
name_ct(bool xauto_access) const
{
  size_type result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = host()->subposet_name_ct(index(), xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::subposet::
has_name(const std::string& xname, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!xname.empty());

  // Body:

  bool result = host()->subposet_has_name(_index, xname, xauto_access);

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::subposet::
put_name(const std::string& xname, bool xunique, bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));

  // Body:

  host()->put_subposet_name(index(), xname, xunique, xauto_access);

  // Postconditions:

  ensure(xunique ? (name(xauto_access) == xname) : has_name(xname, xauto_access));

  // Exit

  return;
}

void
sheaf::subposet::
delete_name(const std::string& xname, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(!xname.empty());

  // Body:

  // poset_state_handle::delete_subposet_name will delete the name
  // whatever subposet it belongs to. Not what we want here.
  // Only delete the name is it belongs to this.

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  if(has_name(xname, false))
  {
    host()->delete_subposet_name(xname, false);
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!has_name(xname, xauto_access));

  // Exit:

  return;
}

void
sheaf::subposet::
delete_all_names(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());

  // Body:

  host()->delete_all_subposet_names(_index, xauto_access);

  // Postconditions:

  ensure(name_ct(xauto_access) == 0);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::subposet::
delete_state(bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_write_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  poset_state_handle* lhost = _host;
  scoped_index lindex = _index;
  detach_from_state();
  lhost->delete_subposet(lindex);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable(!old host()->includes_subposet(old index())));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::subposet::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const subposet*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::subposet*
sheaf::subposet::
clone() const
{
  subposet* result;

  // Preconditions:

  // Body:

  result = new subposet;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::subposet::
invariant() const
{
  // class invariant

  bool result = true;

  // Base class invariant

  result = result && poset_component::invariant();

  if(invariant_check())
  {
    // prevent recursion in called queries

    disable_invariant_check();

    // Nothing to do

    // restore invariant checking

    enable_invariant_check();
  };

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::subposet::
to_stream(std::ostream& os)
{
  cout  << *this;
}

std::string
sheaf::subposet::
to_string()
{
  ostringstream oss;
  oss << *this;
  return oss.str();
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================


std::ostream&
sheaf::
operator<<(std::ostream& xos, const subposet& xs)
{
  // Preconditions:

  require(xs.is_attached() ? xs.state_is_read_accessible() : true);

  // Body:

 if(xs.is_attached())
 {
   if(!(xs.name().empty()))
   {
     xos << setw(20) << xs.name();
   }
   else
   {
     xos << "<void>";
   }

   xos << " " << xs.host() << " " << xs.index() << " " << *xs.members() << endl;
 }
 else
 {
   xos << "<void>  0x0  " << scoped_index::INVALID() << endl;
 }

  // Postconditions:

  // Exit:

  return xos;
}

size_t
sheaf::
deep_size(const subposet& xsp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

