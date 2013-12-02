
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
/// Implementation for class REFINABLE_POSET

#include "refinable_poset.h"

#include "namespace_poset.impl.h"
#include "abstract_poset_member.h"
#include "implicit_crg_interval.h"
class index_iterator;
#include "poset_dof_map.h"
#include "poset_handle_factory.h"
#include "poset_member_iterator.h"
#include "poset_state.h"
#include "poset_type.h"
#include "schema_poset_member.h"
#include "std_strstream.h"
#include "subposet.h"


// ===========================================================
// REFINABLE_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::refinable_poset&
sheaf::refinable_poset::
new_table(namespace_type& xns, const poset_path& xpath, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering refinable_poset::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef refinable_poset table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the table dof map; must be newed 
  // because poset_state::_table keeps a pointer to it.
  // No table dofs to set.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);  

  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  refinable_poset& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  // Exit:

  // cout << "Leaving refinable_poset::new_table." << endl;
  return result;
}

void
sheaf::refinable_poset::
put_version(int xversion)
{
  // Preconditions:

  require( has_version(xversion) );

  // Body:

  // Just to change the visibility of put_version
  // from protected to public.

  poset::put_version(xversion);

  // Postconditions:

  ensure(version() == xversion);

  // Exit

  return;
}

sheaf::subposet&
sheaf::refinable_poset::
coarsest_common_refinement()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet& result = state_obj()->powerset()->coarsest_common_refinement();

  // Postconditions:

  ensure(result.state_is_read_accessible());

  // Exit

  return result;
}

const sheaf::subposet&
sheaf::refinable_poset::
coarsest_common_refinement() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet& result = state_obj()->powerset()->coarsest_common_refinement();

  // Postconditions:

  ensure(result.state_is_read_accessible());

  // Exit

  return result;
}

sheaf::subposet&
sheaf::refinable_poset::
coarsest_common_refinement_jims()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet& result = state_obj()->powerset()->coarsest_common_refinement_jims();

  // Postconditions:

  ensure(result.state_is_read_accessible());

  // Exit

  return result;
}

const sheaf::subposet&
sheaf::refinable_poset::
coarsest_common_refinement_jims() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet& result = state_obj()->powerset()->coarsest_common_refinement_jims();

  // Postconditions:

  ensure(result.state_is_read_accessible());

  // Exit

  return result;
}

void
sheaf::refinable_poset::
begin_refine_mode(bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? state_is_read_write_accessible() : true);

  if(xauto_access)
    get_read_write_access(true);


  // Body:

  define_old_variable(int old_version_ct = version_ct());

  poset_state_handle::begin_jim_edit_mode(false);

  int lnew_ver = version_ct();
  if(lnew_ver == 1)
  {
    // We're moving from version 0 to version 1.
    // Until this point, version 0 has been just
    // an alias for the ccr. But now version 0 will
    // be constant and ccr will continue to change,
    // so we need to make separate subposets for
    // version 0.

    // First, delete the version 0 aliases.

    string lname = version_to_name(0);
    delete_subposet_name(lname, false);
    delete_subposet_name(lname+"_jims", false);

    assertion(version_ct() == 0);

    // Now create a separate version 0.

    new_version(0);

    assertion(version_ct() == old_version_ct);
  }

  new_version(lnew_ver);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(in_jim_edit_mode());
  ensure(version_ct() == old_version_ct + 1);

  // Exit

  return;
}

void
sheaf::refinable_poset::
end_refine_mode(bool xensure_lattice_invariant, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(end_jim_edit_mode(xensure_lattice_invarinat, xauto_access)));

  // Body:

  end_jim_edit_mode(xensure_lattice_invariant, xauto_access);

  // Postconditions:

  ensure(postcondition_of(end_jim_edit_mode(xensure_lattice_invarinat, xauto_access)));

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

sheaf::refinable_poset::
refinable_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset::poset()));
}

sheaf::refinable_poset::
~refinable_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.
  // Currently, this routine exists mostly for the precondition,
  // which is the same as poset::~poset.
  // With this precondition in place, the source of a precondition
  // violation will be clearer to the client.

  // Postconditions:

  // Exit

  return;
}

// PRIVATE FUNCTIONS

void
sheaf::refinable_poset::
new_version(int xversion)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!includes_subposet(version_to_name(xversion), false));

  define_old_variable(int old_version_ct = version_ct());

  // Body:

  // Construct the names for the new version

  string whole_name = version_to_name(xversion);
  string jims_name(whole_name);
  jims_name += "_jims";

  // Create the new whole() subposet and copy
  // the old membership to it.

  subposet old_whole(whole());
  powerset().whole().new_state();
  powerset().whole().put_name(whole_name, true, false);
  powerset().whole().make_equal_to(&old_whole);

  // Create the new jims() subposet and copy
  // the old membership to it.

  subposet old_jims(jims());
  jims().new_state();
  jims().put_name(jims_name, true, false);
  jims().make_equal_to(&old_jims);

  old_whole.detach_from_state();
  old_jims.detach_from_state();

  // Postconditions:

  ensure(version_ct() == old_version_ct + 1);

  // Exit

  return;
}


// ===========================================================
// POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

bool
sheaf::refinable_poset::
make_prototype()
{
  // Preconditions:

  // Body:

  // refinable poset uses POSET_ID.

  poset_type ltype = POSET_ID;

  refinable_poset* lproto = new refinable_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
sheaf::refinable_poset::
type_id() const
{
  return REFINABLE_POSET_ID;
}

const char*
sheaf::refinable_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "refinable_poset";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::refinable_poset::
new_member(bool xis_jim, pod_index_type xdof_tuple_id)
{
  // Preconditions:

  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require(contains_row_dof_tuple(xdof_tuple_id) || !is_valid(xdof_tuple_id));


  // Body:

  define_old_variable(int old_member_ct = member_ct());

  // Create the new member

  pod_index_type result = poset::new_member(xis_jim, xdof_tuple_id);

  // Insert the new member in the ccr.

  coarsest_common_refinement().insert_member(result);
  if(xis_jim)
  {
    coarsest_common_refinement_jims().insert_member(result);
  }

  // Postconditions:

  ensure(invariant());
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

void
sheaf::refinable_poset::
new_member(const scoped_index& xindex, bool xis_jim, const scoped_index& xdof_tuple_id)
{
  // Preconditions:

  require(precondition_of(poset::new_member(same args)));

  // Body:

  define_old_variable(int old_member_ct = member_ct());

  // Create the new member

  poset::new_member(xindex.hub_pod(), xis_jim, xdof_tuple_id);

  // Insert the new member in the ccr.

  coarsest_common_refinement().insert_member(xindex);
  if(xis_jim)
  {
    coarsest_common_refinement_jims().insert_member(xindex);
  }

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xindex));
  ensure(cover_is_empty(LOWER, xindex));
  ensure(cover_is_empty(UPPER, xindex));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::refinable_poset::
new_member_interval(const std::string& xinterval_type, size_type xsize)
{
  // Preconditions:

  require(in_jim_edit_mode());

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(size_type old_member_ct = member_ct());

  // Create the new member

  pod_index_type result = poset::new_member_interval(xinterval_type, xsize);

  implicit_crg_interval& linterval = *crg().implicit_member(result);

  // Insert the new member in the ccr.

  for(pod_index_type i=result; i<member_index_ub().pod(); ++i)
  {
    coarsest_common_refinement().insert_member(i);
    if(linterval.is_jim(i))
    {
      coarsest_common_refinement_jims().insert_member(i);
    }
  }

  // Postconditions:

  ensure(postcondition_of(poset::new_member_interval(xinterval_type, xsize)));
  ensure_for_range(pod_index_type i=result, i<member_index_ub().pod(), ++i,
                   coarsest_common_refinement().contains_member(i));

  // Exit

  return result;
}

void
sheaf::refinable_poset::
new_member_interval(const scoped_index& xindex, const std::string& xinterval_type, size_type xsize)
{
  // Preconditions:

  require(precondition_of(poset::new_member_interval(same args)));

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(size_type old_member_ct = member_ct());

  // Create the new member

  poset::new_member_interval(xindex.hub_pod(), xinterval_type, xsize);

  implicit_crg_interval& linterval = *crg().implicit_member(xindex.hub_pod());

  // Insert the new member in the ccr.

  for(pod_index_type i = linterval.begin(); i < linterval.end(); ++i)
  {
    coarsest_common_refinement().insert_member(i);
    if(linterval.is_jim(i))
    {
      coarsest_common_refinement_jims().insert_member(i);
    }
  }

  // Postconditions:

  ensure(postcondition_of(poset::new_member_interval(xindex, xinterval_type, xsize)));
  ensure_for_range(pod_index_type i=0, i<xsize, ++i, coarsest_common_refinement().contains_member(xindex.hub_id() + i));

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::refinable_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const refinable_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::refinable_poset*
sheaf::refinable_poset::
clone() const
{
  refinable_poset* result;

  // Preconditions:

  // Body:

  result = new refinable_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
sheaf::refinable_poset::
invariant() const
{
  bool result = true;

  result = result && poset::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    /// @todo finish refinable_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

