
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
/// Implementation for class sec_rep_space_member

#include "sec_rep_space_member.h"

#include "arg_list.h"
#include "array_index_space_state.h"
#include "array_section_dof_map.h"
#include "assert_contract.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "index_space_iterator.h"
#include "poset_dof_map.h"
#include "postorder_iterator.h"
#include "preorder_iterator.h"
#include "primitives_poset.h"
#include "sec_rep_space.h"
#include "section_dof_map.h"
#include "sheaves_namespace.h"
#include "subposet_member_iterator.h"
#include "std_typeinfo.h"
#include "tern.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SEC_REP_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_rep_space_member::
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

const string&
fiber_bundle::sec_rep_space_member::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_rep_space_member");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
fiber_bundle::sec_rep_space_member::
standard_schema_poset_name(const string& xschema_member_name)
{
  // Preconditions:


  // Body:

  string result(xschema_member_name + "_host");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
fiber_bundle::sec_rep_space_member::
standard_fiber_space_name(const poset_path& xschema_path)
{
  // Preconditions:

  // Body:

  string result;

  string lschema("_schema");

  string lschema_member_name(xschema_path.member_name());

  int lroot_size = lschema_member_name.size() - lschema.size();

  if(lschema_member_name.substr(lroot_size) == lschema)
  {
    // Schema name ends in suffix _schema; strip the suffix

    result = lschema_member_name.substr(0, lroot_size);
  }
  else
  {
    // Schema doesn't end with suffix; just append "_fiber".

    result = lschema_member_name + "_fiber";
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
fiber_bundle::sec_rep_space_member::
standard_section_space_name(const string& xfiber_space_name,
                            const string& xbase_space_name)
{
  string result;

  // Preconditions:

  require(poset_path::is_valid_name(xfiber_space_name));
  require(poset_path::is_valid_name(xbase_space_name));

  // Body:

  result = xfiber_space_name + "_on_" + xbase_space_name;

  // Postconditions:

  ensure(poset_path::is_valid_name(result));

  // Exit:

  return result;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const sec_rep_space_member& xother, bool xnew_jem)
{
  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  if(xnew_jem)
  {
    new_jem_state(const_cast<sec_rep_space_member*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member&
fiber_bundle::sec_rep_space_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));
  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::sec_rep_space_member&
fiber_bundle::sec_rep_space_member::
operator=(const sec_rep_space_member& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

fiber_bundle::sec_rep_space_member::
~sec_rep_space_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(sec_rep_space* xhost,
                     section_dof_map* xdof_map,
                     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(sec_rep_space* xhost,
                     abstract_poset_member& xbase_mbr,
                     int xbase_version,
                     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jrm_state(xhost, xbase_parts, xauto_access)));

  // Body:

  new_jrm_state(xhost, xbase_parts, xauto_access);

  // Postconditions:

  require(postcondition_of(new_jrm_state(xhost, xbase_parts, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(sec_rep_space* xhost,
                     scoped_index* xexpansion,
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

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const sec_rep_space* xhost, pod_index_type xindex)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // Body:

  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xindex);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const sec_rep_space* xhost, const scoped_index& xindex)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // Body:

  attach_to_state(xhost, xindex.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xindex);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const sec_rep_space* xhost, const string& xname)
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
  ensure(!is_restricted());
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const namespace_poset* xnamespace,
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

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const namespace_poset* xnamespace,
                     pod_index_type xposet_index,
                     pod_index_type xmember_index)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xposet_index, xmember_index);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const namespace_poset* xnamespace,
                     const scoped_index& xposet_index,
                     const scoped_index& xmember_index)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace,
		  xposet_index.hub_pod(),
		  xmember_index.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_space_member::
sec_rep_space_member(const sec_rep_space_member* xother)
{
  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));
  ensure(is_same_restriction(xother));

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_space_member::
new_jim_state(abstract_poset_member& xbase_mbr, int xbase_version,
              bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(precondition_of(\
    new_jim_state(host(), xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(host(), xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of\
    (new_jim_state(host(), xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_space_member::
new_jim_state(sec_rep_space* xhost,
              const abstract_poset_member& xbase_mbr,
              int xbase_version,
              bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->in_jim_edit_mode() : true);

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode();
  }

  require(xbase_mbr.leqv(xhost->base().index()));
  require(xbase_mbr.has_version(xbase_version));

  // Body:

  const scoped_index& ltuple_id =
    xhost->new_row_dof_map(xbase_mbr.index().pod(), xbase_version);
  new_jim_state(xhost, ltuple_id, false);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(is_attached());
  ensure(base().is_same_state(&xbase_mbr));
  ensure(version() == schema().unaliased_version(xbase_version));
  ensure(unexecutable(host()->member_ct() == old host->member_ct() + 1));
  ensure(!is_restricted());

  if(xauto_access)
  {
    xhost->end_jim_edit_mode();
  }

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_space_member::
new_jrm_state(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->is_attached());
  require(xauto_access || xhost->state_is_read_write_accessible());

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  require(xhost->schema().host()->base_space().includes_subposet(&xbase_parts));
  require(!xbase_parts.is_empty());

  require(unexecutable("for all m in xbase_parts, m.le(xhost->schema().base_space())"));

  // Body:

  // Create the branches.

  block<scoped_index> lbranches(256); // Arbitrary; avoids small reallocs.
  xhost->begin_jim_edit_mode(false);

  subposet_member_iterator* litr = xbase_parts.member_iterator();
  while(!litr->is_done())
  {
    new_jim_state(xhost, *litr, CURRENT_HOST_VERSION, false);
    lbranches.push_back(index());
    litr->next();
  }
  delete litr;

  xhost->end_jim_edit_mode(true, false);

  // Create the multi-section itself.
  // The jrm should always be a distinct member that directly cover the branches,
  // so set the tern argument to tern::FALSE. Under most conditions the jrm is
  // unique so tern::NEITHER or TRUE would produce the sme result. But if the
  // section space is empty before we create the branches then the jrm is equivalent
  // to top, so we have to force it to be distinct.

  new_jrm_state(xhost, lbranches.base(), lbranches.ct(), tern::FALSE, false);

  // Get a sequence id for this multisection.

  host()->multisection_id_space(false).push_back(index());

  // Create an id space for the branches.

  const string& lbranch_space_name =
    host()->branch_id_space_name(index(), false);

  arg_list largs = array_index_space_state::make_arg_list(0);

  pod_index_type lspace_id =
    host()->member_id_spaces(false).
    new_secondary_state(lbranch_space_name,
			"array_index_space_state",
			largs, true);

  mutable_index_space_handle lbranch_id_space(host()->member_id_spaces(false),
					      lspace_id);

  int lbranch_ct = lbranches.ct();
  for(int i=0; i<lbranch_ct; ++i)
  {
    lbranch_id_space.push_back(lbranches[i]);
  }


  if(xauto_access)
  {
    xhost->release_access();
  }

  // Postconditions:

  ensure(unexecutable("this has a branch for each member of xbase_parts"));
  ensure(has_branch_id_space(true));
  

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MULTISECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_rep_space_member::
is_multisection(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = host()->is_multisection(index(), xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::sec_rep_space_member::
has_branch_id_space(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = host()->member_id_spaces(xauto_access).
    contains(host()->branch_id_space_name(index(), xauto_access));

  // Postconditions:


  // Exit:

  return result;
}

sheaf::mutable_index_space_handle&
fiber_bundle::sec_rep_space_member::
get_branch_id_space(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(has_branch_id_space(xauto_access));

  // Body:

  mutable_index_space_handle& result =
    host()->get_branch_id_space(index(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_space_member::
release_branch_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(allocated_branch_handle(xid_space, xauto_access));

  // Body:

  host()->release_branch_id_space(xid_space, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::sec_rep_space_member::
allocated_branch_handle(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  bool result = host()->allocated_branch_handle(xid_space, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::sec_rep_space_member::
get_branch_id_space_iterator(bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(has_branch_id_space(xauto_access));

  // Body:

  index_space_iterator& result =
    host()->get_branch_id_space_iterator(index(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_space_member::
release_branch_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(allocated_branch_iterator(xitr, xauto_access));

  // Body:

  host()->release_branch_id_space_iterator(xitr, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::sec_rep_space_member::
allocated_branch_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  bool result = host()->allocated_branch_iterator(xitr, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space_member::
schema()
{
  // Preconditions:

  // The implementation of this only requires is_attached(),
  // but both ancestors and descendants require state_is_read_accessible().

  require(state_is_read_accessible());

  // Body:

  section_space_schema_member& result =
    *reinterpret_cast<section_space_schema_member*>(_schema);

  // Postconditions:

  ensure(result.is_attached());

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space_member::
schema() const
{
  // Preconditions:

  // The implementation of this only requires is_attached(),
  // but both ancestors and descendants require state_is_read_accessible().

  require(state_is_read_accessible());

  // Body:

  const section_space_schema_member& result =
    *reinterpret_cast<const section_space_schema_member*>(_schema);

  // Postconditions:

  ensure(result.is_attached());

  // Exit

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space_member::
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

  ensure(postcondition_of(schema()));

  // Exit:

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space_member::
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

  ensure(postcondition_of(schema()));

  // Exit:

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space_member::
unrestricted_schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>
      (partial_poset_member::unrestricted_schema());

  // Postconditions:

  ensure(is_jim(false) ?
         result.is_same_state(&(dof_map().schema())) :
         result.is_same_state(&(host()->schema())));

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::sec_rep_space_member::
unrestricted_schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const section_space_schema_member& result =
    reinterpret_cast<const section_space_schema_member&>
      (partial_poset_member::unrestricted_schema());

  // Postconditions:

  ensure(is_jim(false) ?
         result.is_same_state(&(dof_map().schema())) :
         result.is_same_state(&(host()->schema())));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESTRICTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_poset_member&
fiber_bundle::sec_rep_space_member::
base()
{
  // Preconditions:

  require(is_attached());

  // Body:

  abstract_poset_member& result = schema().base_space();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::abstract_poset_member&
fiber_bundle::sec_rep_space_member::
base() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const abstract_poset_member& result = schema().base_space();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space_member::
same_base(const sec_rep_space_member* xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());

  // Body:

  result = schema().same_base_space(xother->schema());

  // Postconditions:


  // Exit:

  return result;
}

int
fiber_bundle::sec_rep_space_member::
db() const
{
  int result;

  // Preconditions:

  require(is_attached());

  // Body:

  result = schema().db();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space_member::
same_rep(const sec_rep_space_member* xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());

  // Body:

  /// @hack this definition used for backwards compatibility
  /// with previous implementation.

  /// @todo distinguish betwee rep desc equality and rep equality.

  result = schema().same_rep(xother->schema()) && same_base(xother);

  // Postconditions:


  // Exit:

  return result;
}

int
fiber_bundle::sec_rep_space_member::
discretization_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Get the disc count from the dof tuple schema because it must have
  // already been evaluated while disc ct in schema of handle may need
  // updating.

  if(is_jim())
  {
    // This is an ordinary section,
    // discretization count given by schema.

    if(is_restricted())
    {
      // Have to use handle schema, even if less efficient.

      result = schema().discretization_ct();
    }
    else
    {
      result = dof_map().schema().discretization_ct();
    }
  }
  else
  {
    // This is a multi-section;
    // discretization count is sum of counts of branches.

    result = 0;
    preorder_iterator litr(*this, "jims", DOWN, NOT_STRICT);
    while(!litr.is_done())
    {
      result +=
        host()->member_dof_map(litr.index()).schema().discretization_ct();

      litr.truncate();
    }
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::sec_rep_space_member::
discretization_ct(bool xauto_access) const
{
  int result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = discretization_ct();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(postcondition_of(discretization_ct()));

  // Exit:

  return result;
}

int
fiber_bundle::sec_rep_space_member::
evaluation_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Get the disc count from the dof tuple schema because it must have
  // already been evaluated while disc ct in schema of handle may need
  // updating.

  if(is_jim())
  {
    // This is an ordinary section,
    // evaluation count given by schema.

    if(is_restricted())
    {
      // Have to use handle schema, even if less efficient.

      result = schema().evaluation_ct();
    }
    else
    {
      result = dof_map().schema().evaluation_ct();
    }
  }
  else
  {
    // This is a multi-section;
    // evaluation count is sum of counts of branches.

    result = 0;

    preorder_iterator litr(*this, "jims", DOWN, NOT_STRICT);

    ///@todo Change member_dof_map to take scoped_index. (WEM)

    while(!litr.is_done())
    {
      result += host()->member_dof_map(litr.index()).schema().evaluation_ct();

      litr.truncate();
    }
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

sheaf::schema_poset_member&
fiber_bundle::sec_rep_space_member::
fiber_schema()
{
  // Preconditions:

  require(is_attached());

  // Body:

  schema_poset_member& result = schema().fiber_schema();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::schema_poset_member&
fiber_bundle::sec_rep_space_member::
fiber_schema() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const schema_poset_member& result = schema().fiber_schema();

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset&
fiber_bundle::sec_rep_space_member::
fiber()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset& result = schema().fiber_space();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset&
fiber_bundle::sec_rep_space_member::
fiber() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const poset& result = schema().fiber_space();

  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::sec_rep_space_member::
df() const
{
  int result;

  // Preconditions:

  require(is_attached());

  // Body:

  result = schema().df();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_space_member::
restrict_to(pod_index_type xbase_id, pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @todo implement preconditions equivalent to the following:
  ///   require(xbase != 0);
  ///   require(xbase->le(&(unrestricted_schema().base_space())));
  ///   require(xfiber_schema != 0);
  ///   require(xfiber_schema->le(&(unrestricted_schema().fiber_schema())));

  // Body:

  schema().attach_to_state(xbase_id, xfiber_schema_id);

  // Postconditions:

  /// @todo implement postconditions equivalent to the following:
  ///   ensure(base().is_same_state(xbase));
  ///   ensure(fiber_schema().is_same_state(xfiber_schema));

  // Exit

  return;
}

void
fiber_bundle::sec_rep_space_member::
restrict_to(const scoped_index& xbase_id, const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @todo implement preconditions equivalent to the following:
  ///   require(xbase != 0);
  ///   require(xbase->le(&(unrestricted_schema().base_space())));
  ///   require(xfiber_schema != 0);
  ///   require(xfiber_schema->le(&(unrestricted_schema().fiber_schema())));

  // Body:

  restrict_to(xbase_id.hub_pod(), xfiber_schema_id.hub_pod());

  // Postconditions:

  /// @todo implement postconditions equivalent to the following:
  ///   ensure(base().is_same_state(xbase));
  ///   ensure(fiber_schema().is_same_state(xfiber_schema));

  // Exit

  return;
}

void
fiber_bundle::sec_rep_space_member::
restrict_to(const abstract_poset_member* xbase, const abstract_poset_member* xfiber_schema)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xbase != 0);
  require(xbase->le(&(unrestricted_schema().base_space())));
  require(xfiber_schema != 0);
  require(xfiber_schema->le(&(unrestricted_schema().fiber_schema())));

  // Body:

  schema().attach_to_state(xbase->index(), xfiber_schema->index());

  // Postconditions:

  ensure(base().is_same_state(xbase));
  ensure(fiber_schema().is_same_state(xfiber_schema));

  // Exit

  return;
}

bool
fiber_bundle::sec_rep_space_member::
base_is_restricted() const
{
  bool result;

  // Preconditions:

  require(is_attached() ? state_is_read_accessible() : true);
  require(is_attached() ? base().state_is_read_accessible() : true);

  // Body:

  result = is_attached() &&
           !(base().is_same_state(&(unrestricted_schema().base_space())));

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space_member::
fiber_schema_is_restricted() const
{
  bool result;

  // Preconditions:

  require(is_attached() ? state_is_read_accessible() : true);

  // Body:

  result = is_attached() &&
           !(fiber_schema().is_same_state(&(unrestricted_schema().fiber_schema())));

  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::sec_rep_space_member::
version() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(is_jim())
  {
    result = dof_map().version();
  }
  else
  {
    result = NOT_A_STANDARD_VERSION_INDEX;
  }

  // Postconditions:

  ensure(is_jim() ? host()->base().host()->has_version(result) :
         result == NOT_A_STANDARD_VERSION_INDEX);

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NEW DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::sec_rep_space_member::
get_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false));

  // Body:

  dof_map(false).get_dof(xdisc_id, xfiber_dof_id, xdof, xdof_size);

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
get_dof(const scoped_index& xdisc_id, 
	const scoped_index& xfiber_dof_id, 
	void* xdof,
	size_type xdof_size,
	bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  require(schema(xauto_access).fiber_schema_id_space(false, xauto_access).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema(xauto_access).size(xdisc_id, xfiber_dof_id, false, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  dof_map(false).get_dof(xdisc_id, xfiber_dof_id, xdof, xdof_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
put_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false));

  // Body:

  dof_map(true).put_dof(xdisc_id, xfiber_dof_id, xdof, xdof_size);

  // Postconditions:

  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
put_dof(const scoped_index& xdisc_id, 
	const scoped_index& xfiber_dof_id, 
	const void* xdof,
	size_type xdof_size,
	bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  require(schema(xauto_access).fiber_schema_id_space(false, xauto_access).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema(xauto_access).size(xdisc_id, xfiber_dof_id, false, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).put_dof(xdisc_id, xfiber_dof_id, xdof, xdof_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());

  // Body:

  dof_map(false).get_fiber(xdisc_id, xfiber, xfiber_size);

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
get_fiber(const scoped_index& xdisc_id, void* xfiber, size_type xfiber_size, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema(xauto_access).fiber_size(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  dof_map(false).get_fiber(xdisc_id, xfiber, xfiber_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("dof_map().fiber_in_bounds(xdisc_id, false)"));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());

  // Body:

  dof_map(true).put_fiber(xdisc_id, xfiber, xfiber_size);

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
put_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  require(unexecutable("dof_map().fiber_in_bounds(xdisc_id, false)"));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema(xauto_access).fiber_size(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).put_fiber(xdisc_id, xfiber, xfiber_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
force_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());

  // Body:

  dof_map(true).force_fiber(xdisc_id, xfiber, xfiber_size);

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
force_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema(xauto_access).fiber_size(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).force_fiber(xdisc_id, xfiber, xfiber_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));

  // Body:

  dof_map(false).get_component(xfiber_dof_id, xcomponent, xcomponent_size);

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
get_component(const scoped_index& xfiber_dof_id, 
	      void* xcomponent, 
	      size_type xcomponent_size, 
	      bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(schema(xauto_access).fiber_schema_id_space(false, xauto_access).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema(xauto_access).component_size(xfiber_dof_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  dof_map(false).get_component(xfiber_dof_id, xcomponent, xcomponent_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));

  // Body:

  dof_map(true).put_component(xfiber_dof_id, xcomponent, xcomponent_size);

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_rep_space_member::
put_component(const scoped_index& xfiber_dof_id, 
	      const void* xcomponent,
	      size_type xcomponent_size,
	      bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).fiber_schema_id_space(false, xauto_access).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema(xauto_access).component_size(xfiber_dof_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).put_component(xfiber_dof_id, xcomponent, xcomponent_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

size_t
fiber_bundle::sec_rep_space_member::
dof_tuple_size()
{
  size_t result = 0;

  // Preconditions:

  // Body:

  /// @todo implement sec_rep_space_member::dof_tuple_size()

  not_implemented();

  // Postconditions:

  // Exit

  return result;
}


size_t
fiber_bundle::sec_rep_space_member::
fiber_size()
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema().state_is_read_accessible());

  // Body:

  result = schema().fiber_schema().dof_tuple_ub(false);

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_dof_map&
fiber_bundle::sec_rep_space_member::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  const section_dof_map& result =
    reinterpret_cast<const section_dof_map&>(partial_poset_member::dof_map(xrequire_write_access));

  // Postconditions:

  // Exit:

  return  result;
}

fiber_bundle::section_dof_map&
fiber_bundle::sec_rep_space_member::
dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  section_dof_map& result =
    reinterpret_cast<section_dof_map&>(partial_poset_member::dof_map(xrequire_write_access));

  // Postconditions:

  // Exit:

  return  result;
}

bool
fiber_bundle::sec_rep_space_member::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  result = dynamic_cast<const section_dof_map*>(xdof_map) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_rep_space*
fiber_bundle::sec_rep_space_member::
host() const
{
  sec_rep_space* result;

  // Preconditions:

  // Body:

  result = dynamic_cast<sec_rep_space*>(_host);

  // Postconditions:

  ensure( (_host != 0) == (result != 0) );

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_space_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_rep_space*>(xother) != 0;

  // Postconditions:

  ensure(result == (dynamic_cast<const sec_rep_space*>(xother) != 0));

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
fiber_bundle::sec_rep_space_member::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_rep_space_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_rep_space_member*
fiber_bundle::sec_rep_space_member::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_rep_space_member *result = new sec_rep_space_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_rep_space_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && poset_member::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    result = result &&
             (is_attached()
               ? dynamic_cast<section_space_schema_member*>(_schema) != 0
               : true);

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
