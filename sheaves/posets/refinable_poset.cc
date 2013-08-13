

//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

sheaf::refinable_poset::
refinable_poset(namespace_poset* xhost,
                const poset_path& xschema_path,
                const string& xname,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(refinable_poset::new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xschema_path, xname, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refinable_poset::new_state(same args)));
}

sheaf::refinable_poset::
refinable_poset(namespace_poset* xhost,
                const poset_path& xschema_path,
                const string& xname,
                void* xtable_dofs,
                size_t xtable_dofs_ub,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(refinable_poset::new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xschema_path, xname, xtable_dofs, xtable_dofs_ub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refinable_poset::new_state(same args)));
}

sheaf::refinable_poset::
refinable_poset(namespace_poset* xhost,
                const poset_path& xschema_path,
                const string& xname,
                array_poset_dof_map* xdof_map,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(refinable_poset::new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xschema_path, xname, xdof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refinable_poset::new_state(same args)));
}


sheaf::refinable_poset::
refinable_poset(namespace_poset* xhost,
                abstract_poset_member* xschema,
                const string& xname,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(refinable_poset::new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xschema, xname, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refinable_poset::new_state(same args)));
}

sheaf::refinable_poset::
refinable_poset(namespace_poset* xhost,
                abstract_poset_member* xschema,
                const string& xname,
                void* xtable_dofs,
                size_t xtable_dofs_ub,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(refinable_poset::new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xschema, xname, xtable_dofs, xtable_dofs_ub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refinable_poset::new_state(same args)));
}

sheaf::refinable_poset::
refinable_poset(namespace_poset* xhost,
                abstract_poset_member* xschema,
                const string& xname,
                array_poset_dof_map* xdof_map,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(refinable_poset::new_state(same args)));

  // Body:

  // make the new state

  new_state(xhost, xschema, xname, xdof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refinable_poset::new_state(same args)));
}

sheaf::refinable_poset::
refinable_poset(const namespace_poset* xhost, pod_index_type xindex)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));
  require(xhost->is_jim(xindex));

  // Body:

  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state()));
}

sheaf::refinable_poset::
refinable_poset(const namespace_poset* xhost, const scoped_index& xindex)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));
  require(xhost->is_jim(xindex));

  // Body:

  attach_to_state(xhost, xindex.hub_pod());

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state()));
}

sheaf::refinable_poset::
refinable_poset(const namespace_poset* xhost, const string& xname)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state()));
}

sheaf::refinable_poset::
refinable_poset(const abstract_poset_member* xmbr)
{
  // Preconditions:

  require(xmbr != 0);
  require(dynamic_cast<namespace_poset*>(xmbr->host()) != 0);
  require(xmbr->state_is_read_accessible());

  // Body:

  attach_to_state(xmbr);

  // Postconditions:

  ensure(postcondition_of(state_handle::attach_to_state(abstract_poset_member*)));
}

sheaf::refinable_poset::
refinable_poset(const refinable_poset& xother)
    : poset(xother)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset::poset(const poset&)));
}

sheaf::refinable_poset&
sheaf::refinable_poset::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(dynamic_cast<refinable_poset*>(&const_cast<poset_state_handle&>(xother))!=0);

  // Body:

  poset::operator=(const_cast<poset_state_handle&>(xother));

  // Postconditions:

  ensure(is_same_state(&const_cast<poset_state_handle&>(xother)));

  // Exit:

  return *this;
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
new_member_interval(const string& xinterval_type, size_type xsize)
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
new_member_interval(const scoped_index& xindex, const string& xinterval_type, size_type xsize)
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

