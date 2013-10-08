
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
/// Implementation for class sec_rep_space

#include "sec_rep_space.h"
#include "arg_list.h"
#include "assert_contract.h"
#include "array_index_space_state.h"
#include "array_section_dof_map.h"
#include "binary_section_space_schema_member.impl.h"
#include "binary_section_space_schema_poset.h"
#include "index_space_iterator.h"
#include "namespace_poset.impl.h"
#include "poset.h"
#include "poset_type.h"
#include "poset_handle_factory.h"
#include "poset_member.h"
#include "poset_state.h"
#include "postorder_iterator.h"
#include "std_string.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_space_member.h"
#include "tern.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// =============================================================================
// SEC_REP_SPACE FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_rep_space::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_rep_space");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::abstract_poset_member&
fiber_bundle::sec_rep_space::
base()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().base_space();
}

const sheaf::abstract_poset_member&
fiber_bundle::sec_rep_space::
base() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().base_space();
}

int
fiber_bundle::sec_rep_space::
db() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = schema().db();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}


int
fiber_bundle::sec_rep_space::
df() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = schema().df();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}


sheaf::schema_poset_member&
fiber_bundle::sec_rep_space::
fiber_schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().fiber_schema();
}

const sheaf::schema_poset_member&
fiber_bundle::sec_rep_space::
fiber_schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().fiber_schema();
}

sheaf::schema_poset_member&
fiber_bundle::sec_rep_space::
fiber_schema(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema(xauto_access).fiber_schema();
}

const sheaf::schema_poset_member&
fiber_bundle::sec_rep_space::
fiber_schema(bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema(xauto_access).fiber_schema();
}

fiber_bundle::sec_rep_descriptor&
fiber_bundle::sec_rep_space::
rep()
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().rep();
}

const fiber_bundle::sec_rep_descriptor&
fiber_bundle::sec_rep_space::
rep() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().rep();
}

bool
fiber_bundle::sec_rep_space::
rep_is_valid(const abstract_poset_member* xbase, const sec_rep_descriptor* xrep)
{
  bool result = true;

  // Preconditions:

  require(xbase != 0);
  require(xbase->state_is_read_accessible());
  require(xrep != 0);
  require(xrep->state_is_read_accessible());

  // Body:

  result = section_space_schema_poset::rep_is_valid(*xrep, *(xbase->host()));

  // Postconditions:

  // Exit

  return result;
}

sheaf::subposet&
fiber_bundle::sec_rep_space::
discretization()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().discretization();
}

const sheaf::subposet&
fiber_bundle::sec_rep_space::
discretization() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().discretization();
}

int
fiber_bundle::sec_rep_space::
discretization_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().discretization_ct();
}

int
fiber_bundle::sec_rep_space::
multiplicity() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().rep().multiplicity();
}

sheaf::subposet&
fiber_bundle::sec_rep_space::
evaluation()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:


  // Exit

  return schema().evaluation();
}

const sheaf::subposet&
fiber_bundle::sec_rep_space::
evaluation() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:


  // Exit

  return schema().evaluation();
}

string
fiber_bundle::sec_rep_space::
evaluator_family() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().rep().evaluator_family_name();
}

string
fiber_bundle::sec_rep_space::
url() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return schema().rep().url();
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_rep_space::
sec_rep_space()
  : poset_state_handle(new sec_rep_space_member, new sec_rep_space_member)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(!is_attached());
  ensure(!top().is_attached());
  ensure(!bottom().is_attached());
}

fiber_bundle::sec_rep_space::
sec_rep_space(sec_rep_space_member* xtop, sec_rep_space_member* xbottom)
  : poset_state_handle(xtop, xbottom)
{
  // Preconditions:

  require(xtop != 0);
  require(xbottom != 0);
  
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::poset_state_handle(xtop, xbottom)));
  
  // Exit:

  return;
}

fiber_bundle::sec_rep_space::
~sec_rep_space()
{

  // Preconditions:

  // Body:

  // Nothing to do; base class does it all

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_rep_space::
make_prototype()
{
  // Preconditions:


  // Body:

  poset_type ltype = SEC_REP_SPACE_ID;

  sec_rep_space* lproto = new sec_rep_space;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return true;
}


// =============================================================================
// MULTISECTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_rep_space::
is_multisection(pod_index_type xhub_id, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xhub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = !is_jim(xhub_id, true);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::sec_rep_space::
is_multisection(const scoped_index& xid, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xid, xauto_access));

  // Body:

  return is_multisection(xid.hub_pod(), xauto_access);
}

string
fiber_bundle::sec_rep_space::
branch_id_space_name(pod_index_type xhub_id, bool xauto_access) const
{
  string result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  pod_index_type lseq_id = multisection_id_space(xauto_access).pod(xhub_id);

  result = poset_path::make_reserved_name("", lseq_id, "_branch_ids");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
fiber_bundle::sec_rep_space::
branch_id_space_name(const scoped_index& xid, bool xauto_access) const
{
  string result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = branch_id_space_name(xid.hub_pod(), xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::mutable_index_space_handle&
fiber_bundle::sec_rep_space::
multisection_id_space(bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  static const string multisection_id_space_name("__multisections");

  /// @hack map should be created in sec rep space constructor.

  if(!_multisection_id_space.is_attached())
  {
    arg_list largs = array_index_space_state::make_arg_list(0);

    sec_rep_space* cthis = const_cast<sec_rep_space*>(this);

    pod_index_type lspace_id =
      cthis->member_id_spaces(false).
      new_secondary_state(multisection_id_space_name,
			  "array_index_space_state",
			  largs, true);

    _multisection_id_space.attach_to(member_id_spaces(false), lspace_id);
  }

  const mutable_index_space_handle& result = _multisection_id_space;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::mutable_index_space_handle&
fiber_bundle::sec_rep_space::
multisection_id_space(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  static const string multisection_id_space_name("__multisections");

  /// @hack map should be created in sec rep space constructor.

  if(!_multisection_id_space.is_attached())
  {
    arg_list largs = array_index_space_state::make_arg_list(0);

    sec_rep_space* cthis = const_cast<sec_rep_space*>(this); 

    pod_index_type lspace_id =
      cthis->member_id_spaces(false).
      new_secondary_state(multisection_id_space_name,
			  "array_index_space_state",
			  largs, true);

    _multisection_id_space.attach_to(member_id_spaces(false), lspace_id);
  }

  mutable_index_space_handle& result = _multisection_id_space;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::mutable_index_space_handle&
fiber_bundle::sec_rep_space::
get_branch_id_space(pod_index_type xhub_id, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xhub_id, xauto_access));
  require(is_multisection(xhub_id, xauto_access));
  require(member_id_spaces(xauto_access).contains(branch_id_space_name(xhub_id, xauto_access)));


  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  mutable_index_space_handle& result =
    member_id_spaces(false).get_id_space<mutable_index_space_handle>(branch_id_space_name(xhub_id, false));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::mutable_index_space_handle&
fiber_bundle::sec_rep_space::
get_branch_id_space(const scoped_index& xid, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xid, xauto_access));
  require(is_multisection(xid, xauto_access));
  require(member_id_spaces(xauto_access).contains(branch_id_space_name(xid, xauto_access)));

  // Body:

  mutable_index_space_handle& result =
    get_branch_id_space(xid.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_space::
release_branch_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(allocated_branch_handle(xid_space, xauto_access));

  // Body:

  member_id_spaces(xauto_access).release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::sec_rep_space::
allocated_branch_handle(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  bool result = member_id_spaces(xauto_access).allocated_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::sec_rep_space::
get_branch_id_space_iterator(pod_index_type xhub_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xhub_id, xauto_access));
  require(is_multisection(xhub_id, xauto_access));
  require(member_id_spaces(xauto_access).contains(branch_id_space_name(xhub_id, xauto_access)));


  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  index_space_iterator& result =
    member_id_spaces(false).get_id_space_iterator(branch_id_space_name(xhub_id, false));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::sec_rep_space::
get_branch_id_space_iterator(const scoped_index& xid, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xid, xauto_access));
  require(is_multisection(xid, xauto_access));
  require(member_id_spaces(xauto_access).contains(branch_id_space_name(xid, xauto_access)));

  // Body:

  index_space_iterator& result =
    get_branch_id_space_iterator(xid.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_space::
release_branch_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(allocated_branch_iterator(xitr, xauto_access));

  // Body:

  member_id_spaces(xauto_access).release_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::sec_rep_space::
allocated_branch_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  bool result = member_id_spaces(xauto_access).allocated_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// STATE FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_type
fiber_bundle::sec_rep_space::
type_id() const
{
  return SEC_REP_SPACE_ID;
}

const char*
fiber_bundle::sec_rep_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_rep_space";

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_space::
begin_jim_edit_mode(bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? state_is_read_write_accessible() : true);

  // Body:

  if(xauto_access)
    get_read_write_access(true);

  // Redefinition here is only to change visibility.

  poset_state_handle::begin_jim_edit_mode(false);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(in_jim_edit_mode());

  // Exit

  return;
}

void
fiber_bundle::sec_rep_space::
end_jim_edit_mode(bool xensure_lattice_invariant, bool xauto_access)
{
  // Preconditions:

  require(in_jim_edit_mode());
  require(state_is_read_write_accessible());

  // Body:

  // Redefinition here is only to change visibility

  poset_state_handle::end_jim_edit_mode(xensure_lattice_invariant, xauto_access);

  // Postconditions:

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_rep_space::
new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable("xschema.is_same_state(xdof_map.schema())"));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the state object;
  // Allocates the data structures but does not (fully) initialize them

  _state = new poset_state(&xschema, type_id(), xpath.poset_name());

  // Get write access

  get_read_write_access();

  // Initialize the table dofs ("class variables")

  initialize_table_dof_tuple(&xdof_map);

  // Initialize the row structure

  initialize_standard_subposets(xpath.poset_name());
  initialize_standard_members();

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(schema().is_same_state(&xschema));
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(base().is_same_state(&(reinterpret_cast<const section_space_schema_member&>(xschema).base_space())));
  ensure(schema().fiber_space().is_same_state(&(reinterpret_cast<const section_space_schema_member&>(xschema).host()->fiber_space())));
  ensure(rep().is_same_state(&(reinterpret_cast<const section_space_schema_member&>(xschema).rep())));

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());
}

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// MEMBERSHIP FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_rep_space_member&
fiber_bundle::sec_rep_space::
top()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<sec_rep_space_member*>(_top));
}

const fiber_bundle::sec_rep_space_member&
fiber_bundle::sec_rep_space::
top() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<sec_rep_space_member*>(_top));
}

fiber_bundle::sec_rep_space_member&
fiber_bundle::sec_rep_space::
bottom()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<sec_rep_space_member*>(_bottom));
}

const fiber_bundle::sec_rep_space_member&
fiber_bundle::sec_rep_space::
bottom() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<const sec_rep_space_member*>(_bottom));
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// SCHEMA FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space::
schema()
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  section_space_schema_member& result =
    dynamic_cast<section_space_schema_member&>(poset_state_handle::schema());

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space::
schema() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const section_space_schema_member& result =
    dynamic_cast<const section_space_schema_member&>(poset_state_handle::schema());

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space::
schema(bool xauto_access)
{

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  section_space_schema_member& result = schema();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space::
schema(bool xauto_access) const
{

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const section_space_schema_member& result = schema();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space::
schema_is_ancestor_of(const schema_poset_member* xother_schema) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_space_schema_member*>(xother_schema) != 0;


  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::sec_rep_space::
dof_ct(bool xis_table_dof) const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());
  // need access to dof subposet, which is in schema().host()

  // Body:

  result = schema().dof_ct(xis_table_dof);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space::
row_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // Row dofs, map must be a section_dof_map

  result = (dynamic_cast<const section_dof_map*>(xdof_map) != 0);

  // Postconditions:

  ensure(result ? (dynamic_cast<const section_dof_map*>(xdof_map) != 0) : true);

  // Exit

  return result;
}


size_t
fiber_bundle::sec_rep_space::
dof_tuple_ub(bool xis_table_dof) const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = schema().dof_tuple_ub(xis_table_dof);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

const sheaf::scoped_index&
fiber_bundle::sec_rep_space::
new_row_dof_map()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  // Create a new dof map using contiguous array rep

  poset_dof_map* lmap = new array_section_dof_map(this);
  state_obj()->table()->put_row_dof_tuple(lmap);
  const scoped_index& result = lmap->index();

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit

  return result;
}

const sheaf::scoped_index&
fiber_bundle::sec_rep_space::
new_row_dof_map(pod_index_type xbase_id, int xbase_version)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().base_space().host()->contains_member(xbase_id));
  require(schema().base_space().geqv(xbase_id));
  require(schema().base_space().has_version(xbase_version));

  // Body:

  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  // Create a new dof map using contiguous array rep

  poset_dof_map* lmap = new array_section_dof_map(this, xbase_id, xbase_version);
  state_obj()->table()->put_row_dof_tuple(lmap);
  const scoped_index& result = lmap->index();

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit

  return result;
}

const sheaf::scoped_index&
fiber_bundle::sec_rep_space::
new_row_dof_map(const scoped_index& xbase_id, int xbase_version)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().base_space().host()->contains_member(xbase_id));
  require(schema().base_space().geqv(xbase_id));
  require(schema().base_space().has_version(xbase_version));

  // Body:
 
  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  const scoped_index& result = new_row_dof_map(xbase_id.hub_pod(),
					       xbase_version);

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit

  return result;
}

fiber_bundle::section_dof_map&
fiber_bundle::sec_rep_space::
member_dof_map(pod_index_type xmbr_index, bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_index));
  require(is_jim(xmbr_index, false));

  // Body:

  poset_dof_map& ldof_map =
    row_dof_map(member_dof_tuple_id(xmbr_index, false), xrequire_write_access);

  section_dof_map& result = reinterpret_cast<section_dof_map&>(ldof_map);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::section_dof_map&
fiber_bundle::sec_rep_space::
member_dof_map(const scoped_index& xmbr_index, bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_index));
  require(is_jim(xmbr_index, false));

  // Body:

  return member_dof_map(xmbr_index.hub_pod(), xrequire_write_access);
}

const fiber_bundle::section_dof_map&
fiber_bundle::sec_rep_space::
member_dof_map(pod_index_type xmbr_index, bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_index));
  require(is_jim(xmbr_index, false));

  // Body:

  poset_dof_map& ldof_map =
    row_dof_map(member_dof_tuple_id(xmbr_index, false), xrequire_write_access);

  section_dof_map& result = reinterpret_cast<section_dof_map&>(ldof_map);

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::section_dof_map&
fiber_bundle::sec_rep_space::
member_dof_map(const scoped_index& xmbr_index, bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_index));
  require(is_jim(xmbr_index, false));

  // Body:

  return member_dof_map(xmbr_index.hub_pod(), xrequire_write_access);
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_rep_space*
fiber_bundle::sec_rep_space::
clone() const
{
  sec_rep_space* result;

  // Preconditions:

  // Body:

  result = new sec_rep_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  poset_state_handle::invariant();
  if(invariant_check())
  {
    disable_invariant_check();

    /// @todo implement sec_rep_space::invariant

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_rep_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


