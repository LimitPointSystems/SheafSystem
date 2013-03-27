// $RCSfile: poset.cc,v $ $Revision: 1.41 $ $Date: 2013/01/13 17:34:34 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class poset.

#include "abstract_poset_member.h"
#include "arg_list.h"
#include "array_poset_dof_map.h"
class index_iterator;
#include "namespace_poset.impl.h"
#include "poset.h"
#include "poset_handle_factory.h"
#include "poset_member_iterator.h"
#include "poset_state.h"
#include "poset_type.h"
#include "schema_poset_member.h"
#include "subposet.h"

// ===========================================================
// POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

sheaf::poset::
poset()
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::poset_state_handle()));
}

sheaf::poset::
~poset()
{
  // Preconditions:

  require(is_attached() ? state_is_read_write_accessible() : true);

  // Body:

  // Nothing to do; base class does it all.
  // Currently, this routine exists mostly for the precondition,
  // which is the same as poset_state_handle::~poset_state_handle.
  // With this precondition in place, the source of a precondition
  // violation will be clearer to the client.

  // Postconditions:

  // Exit

  return;
}

sheaf::poset::
poset(abstract_poset_member* xtop, abstract_poset_member* xbottom)
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

sheaf::poset::
poset(namespace_poset* xhost,
      const poset_path& xschema_path,
      const string& xname,
      bool xauto_access)
{

  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema_path, xname, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(same args)));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      const poset_path& xschema_path,
      const string& xname,
      void* xtable_dofs,
      size_t xtable_dofs_ub,
      bool xauto_access)
{

  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema_path, xname, xtable_dofs, xtable_dofs_ub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(same args)));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      const poset_path& xschema_path,
      const string& xname,
      arg_list& xargs,
      bool xauto_access)
{

  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema_path, xname, xargs, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(same args)));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      const poset_path& xschema_path,
      const string& xname,
      array_poset_dof_map* xtable_dof_tuple,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema_path, xname, xtable_dof_tuple, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state()));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      abstract_poset_member* xschema,
      const string& xname,
      bool xauto_access)
{

  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema, xname, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(same args)));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      abstract_poset_member* xschema,
      const string& xname,
      void* xtable_dofs,
      size_t xtable_dofs_ub,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema, xname, xtable_dofs, xtable_dofs_ub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state()));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      abstract_poset_member* xschema,
      const string& xname,
      arg_list& xargs,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema, xname, xargs, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state()));

  // Exit:

  return;
}

sheaf::poset::
poset(namespace_poset* xhost,
      abstract_poset_member* xschema,
      const string& xname,
      array_poset_dof_map* xtable_dof_tuple,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema, xname, xtable_dof_tuple, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(same args)));

  // Exit:

  return;
}

sheaf::poset::
poset(const namespace_poset* xhost, pod_index_type xindex)
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

  // Exit:

  return;
}

sheaf::poset::
poset(const namespace_poset* xhost, const scoped_index& xindex)
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

  // Exit:

  return;
}

sheaf::poset::
poset(const namespace_poset* xhost, const string& xname)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state()));

  // Exit:

  return;
}

sheaf::poset::
poset(const abstract_poset_member* xmbr)
{
  // Preconditions:

  require(xmbr != 0);
  require(xmbr->is_jim());
  require(xmbr->state_is_read_accessible());

  // Body:

  attach_to_state(xmbr);

  // Postconditions:

  ensure(postcondition_of(state_handle::attach_to_state(abstract_poset_member*)));

  // Exit:

  return;
}

sheaf::poset::
poset(const poset& xother)
    : poset_state_handle(xother)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::poset_state_handle(const poset_state_handle&)));
}

sheaf::poset&
sheaf::poset::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(dynamic_cast<poset*>(&const_cast<poset_state_handle&>(xother))!=0);

  // Body:

  poset_state_handle::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

// PRIVATE FUNCTIONS

bool
sheaf::poset::
_has_prototype = make_prototype();

bool
sheaf::poset::
make_prototype()
{
  // Preconditions:

  // Body:

  poset* lproto = new poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(lproto->type_id(), lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const poset_path& xschema_path,
          const string& xname,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->state_is_read_write_accessible() : true);
  require(precondition_of(new_state(xhost, xschema, xname, xauto_access)));

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  require(xschema_path.full());
  require(xhost->contains_poset_member(xschema_path));

  // Body:

  // Create a handle to the schema

  schema_poset_member lschema(xhost, xschema_path);

  lschema.get_read_access();

  // Create the new state with the given schema

  new_state(xhost, &lschema, xname, false);

  // Clean up

  lschema.release_access();
  lschema.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xauto_access)));
  ensure(unexecutable("schema().path() == xschema_path"));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const poset_path& xschema_path,
          const string& xname,
          void* xtable_dofs,
          size_t xtable_dofs_ub,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->state_is_read_write_accessible() : true);
  require(precondition_of(new_state(xhost, xschema, xname, xtable_dofs, xtable_dofs_ub, xauto_access)));

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    xhost->get_read_write_access(true);

  require(xschema_path.full());
  require(xhost->contains_poset_member(xschema_path));

  // Body:

  // Create a handle to the schema

  schema_poset_member lschema(xhost, xschema_path);

  lschema.get_read_access();

  // Create the new state with the given schema

  new_state(xhost, &lschema, xname, xtable_dofs, xtable_dofs_ub, false);

  // Clean up

  lschema.release_access();
  lschema.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xtable_dofs, xtable_dofs_ub, xauto_access)));
  ensure(unexecutable("schema().path() == xschema_path"));

  // Release access if auto access was requested.

  if(xauto_access)
    xhost->release_access();

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const poset_path& xschema_path,
          const string& xname,
          arg_list& xargs,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->state_is_read_write_accessible() : true);
  require(precondition_of(new_state(xhost, xschema, xname, xargs, xauto_access)));

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    xhost->get_read_write_access(true);

  require(xschema_path.full());
  require(xhost->contains_poset_member(xschema_path));

  // Body:

  // Create a handle to the schema

  schema_poset_member lschema(xhost, xschema_path);

  lschema.get_read_access();

  // Create the new state with the given schema

  new_state(xhost, &lschema, xname, xargs, false);

  // Clean up

  lschema.release_access();
  lschema.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xargs, xauto_access)));
  ensure(unexecutable("schema().path() == xschema_path"));

  // Release access if auto access was requested.

  if(xauto_access)
    xhost->release_access();

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const poset_path& xschema_path,
          const string& xname,
          array_poset_dof_map* xdof_tuple,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->state_is_read_write_accessible() : true);

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  require(xschema_path.full());
  require(xhost->contains_poset_member(xschema_path));
  require(precondition_of(new_state(xhost, xschema, xname, xdof_tuple, xauto_access)));

  // Body:

  // Create a temporary handle to the schema

  schema_poset_member lschema(xhost, xschema_path);

  lschema.get_read_access();

  // Create the new state with the given schema.

  new_state(xhost, &lschema, xname, xdof_tuple, false);

  // Clean up.

  lschema.release_access();
  lschema.detach_from_state();

  if(xauto_access)
    xhost->release_access();

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xdof_tuple, xauto_access)));
  ensure(unexecutable("schema().path() == xschema_path"));

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const abstract_poset_member* xschema,
          const string& xname,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0  && !xauto_access ? xhost->state_is_read_write_accessible() : true);
  require(xschema != 0);
  require(!xauto_access ? xschema->state_is_read_accessible() : true);
  require(!xname.empty());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xschema->get_read_access();

    if(xhost != 0)
      xhost->get_read_write_access(true);
  }

  require(xhost != 0 ? !xhost->contains_poset(xname) : true);

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.

  require(xhost != 0 ? xname != xhost->name() : true);

  // Body:

  // Create the table dof map, but leave it uninitialized.

  /// @hack temporarily avoid changing signature of this routine

  schema_poset_member lschema(xschema->host(), xschema->index());

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);

  lschema.detach_from_state();

  // Create the new state.

  new_state(xhost, xschema, xname, lmap, false);

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xdof_tuple, xauto_access)));
  ensure(unexecutable("table dofs not initialized"));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xschema->release_access();

    if(xhost != 0)
      xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const abstract_poset_member* xschema,
          const string& xname,
          void* xtable_dofs,
          size_t xtable_dofs_ub,
          bool xauto_access)
{

  // Preconditions:

  /// @issue why do we not require xhost != 0?

  require(xhost != 0 && !xauto_access ? xhost->state_is_read_write_accessible() : true);
  require(xschema != 0);
  require(!xname.empty());
  require(xtable_dofs != 0);
  // require(xtable_dofs_ub >= xschema->table_dof_tuple_ub());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xschema->get_read_access();

    if(xhost != 0)
      xhost->get_read_write_access(true);
  }

  require(xhost != 0 ? !xhost->contains_poset(xname) : true);

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.

  require(xhost != 0 ? xname != xhost->name() : true);

  // Body:

  // Create and initialize the table dofs.

  /// @hack temporarily avoid changing signature of this routine

  schema_poset_member lschema(xschema->host(), xschema->index());

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);

  lschema.detach_from_state();

  lmap->put_dof_tuple(xtable_dofs, xtable_dofs_ub);

  // Create the new state.

  new_state(xhost, xschema, xname, lmap, false);

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xdof_tuple, xauto_access)));
  ensure(unexecutable("table dofs initialized by xtable_dofs"));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xschema->release_access();

    if(xhost != 0)
      xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const abstract_poset_member* xschema,
          const string& xname,
          arg_list& xargs,
          bool xauto_access)
{
  // Preconditions:

  /// @issue why do we not require xhost != 0?

  require(xhost != 0 && !xauto_access ? xhost->state_is_read_write_accessible() : true);
  require(xschema != 0);
  require(!xname.empty());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xschema->get_read_access();

    if(xhost != 0)
      xhost->get_read_write_access(true);
  }

  require(xhost != 0 ? !xhost->contains_poset(xname) : true);

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.

  require(xhost != 0 ? xname != xhost->name() : true);

  /// @hack temporarily avoid changing signature of this routine

  //require(xargs.conforms_to(xschema));


  // Body:

  // Create and initialize the table dofs.

  /// @hack temporarily avoid changing signature of this routine

  schema_poset_member lschema(xschema->host(), xschema->index());

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);

  lschema.detach_from_state();

  lmap->put_dof_tuple(xargs);

  // Create the new state.

  new_state(xhost, xschema, xname, lmap, false);

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xschema, xname, xdof_tuple, xauto_access)));
  ensure(unexecutable("table dofs initialized by xargs"));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xschema->release_access();

    if(xhost != 0)
      xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::poset::
new_state(namespace_poset* xhost,
          const abstract_poset_member* xschema,
          const string& xname,
          array_poset_dof_map* xdof_tuple,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);

  /// @hack should require in_jim_edit_mode;
  /// see poset_state_handle::initialize_namespace
  ///  require(xauto_access || xhost->in_jim_edit_mode());

  require(xauto_access || xhost->state_is_read_write_accessible());

  if(xauto_access)
  {
    xhost->get_read_write_access();
  }

  require(xschema != 0);

  require(!xname.empty());
  require(!xhost->contains_poset(xname, true));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.

  require(xname != xhost->name());

  require(xdof_tuple != 0);
  require(xdof_tuple->schema().conforms_to(xschema->path(true)));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the poset state object;
  // Allocates the data structures but does not (fully) initialize them

  _state = new poset_state(xschema, type_id());

  // Get write access.
  // Descendants may have data members, which aren't attached yet,
  // Derived get access routines will try to get access to data members,
  // so force current scope.

  poset::get_read_write_access();

  // Initialize the table dofs ("class variables").
  // Do this before initializing the row structure so the subposet
  // and member initialization routines can use the table dofs if needed.

  initialize_table_dof_tuple(xdof_tuple);

  // Initialize the row structure

  initialize_standard_subposets(xname);
  initialize_standard_members();

  // Initialize the namespace features

  initialize_namespace(*xhost, xname);

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Initialize any additional handle data members.

  initialize_handle_data_members(*xhost);

  // Release and regain access;
  // will get access to handle data members.

  poset::release_access();
  get_read_write_access();
  
  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(schema().is_same_state(xschema));
  ensure(name() == xname);
  ensure(&(table_dof_map()) == xdof_tuple);
  ensure(!in_jim_edit_mode());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  /// @todo resolve status of following postcondtion
  ///   ensure(has_standard_subposet_ct());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  if(xauto_access)
  {
    xhost->release_access();
  }

  // Exit:

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
sheaf::poset::
type_id() const
{
  return POSET_ID;
}

const char*
sheaf::poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "poset";

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::poset::
begin_jim_edit_mode(bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? state_is_read_write_accessible() : true);

  // Body:

  // Redefinition here is only to change visibility.

  poset_state_handle::begin_jim_edit_mode(xauto_access);

  // Postconditions:

  ensure(in_jim_edit_mode());

  // Exit

  return;
}

void
sheaf::poset::
end_jim_edit_mode(bool xensure_lattice_invariant,
                  bool xauto_access)
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

// PROTECTED FUNCTIONS

void
sheaf::poset::
new_state(const schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(is_external());
  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());
  require(xschema.host()->name_space()->is_same_state(name_space()));

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable(xschema.is_same_state(xdof_map.schema())));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the poset state object;
  // Allocates the data structures but does not (fully) initialize them

  _state = new poset_state(&xschema, type_id());

  // Get write access.
  // Descendants may have data members, which aren't attached yet,
  // Derived get access routines will try to get access to data members,
  // so force current scope.

  poset::get_read_write_access();

  // Initialize the table dofs ("class variables");
  // must be done before row structure since row structure
  // may depend on table dofs.

  initialize_table_dof_tuple(&xdof_map);

  // Initialize the row structure

  initialize_standard_subposets(name_space()->member_name(index()));
  initialize_standard_members();

  /// @issue automatic vs explicit version subposet membership.
  /// The crg of the coarsest_common_refinement (CCR) is what is
  /// written to disk, along with membership info for each of the
  /// version subposets. When we read the file, we want to reconstruct
  /// the CCR graph and the membership for each of the versions.
  /// The CCR graph gets reconstructed without issue, since that
  /// is what is in the file. For non-versioned posets, the subposet
  /// membership gets reconstructed correctly as well, since there
  /// are no version subposets and both CCR and whole() refer to the
  /// same subposet. But for refinable posets, when a member is created
  /// it is automatically entered into the CCR and, separately, into
  /// the current version subposet. This automatic subposet membership
  /// management conflicts with the explicit subposet membership
  /// management provided by the i/o subsystem.

  /// @hack version subposet membership management. We can resolve
  /// the above version subposet membership management issue by setting
  /// the current version to CCR. This makes the refineable posets
  /// behave like non-version posets, at the cost of inserting every member
  /// into the CCR subposet twice, once for the CCR and once for the
  /// current version.

  /// @issue current version. The above hack leaves the poset with
  /// CCR as the current version. What should the current version be,
  /// and where should we restore it?

  put_version(COARSEST_COMMON_REFINEMENT_VERSION);

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Initialize any additional handle data members.

  initialize_handle_data_members(*name_space());

  // Release and regain access;
  // will get access to handle data members.

  poset::release_access();
  get_read_write_access();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(schema().is_same_state(&xschema));
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  //   ensure(has_standard_subposet_ct());
  ensure(version() == COARSEST_COMMON_REFINEMENT_VERSION);

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());
}

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset*
sheaf::poset::
clone() const
{
  poset* result;

  // Preconditions:

  // Body:

  result = new poset;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
sheaf::poset::
invariant() const
{
  bool result = true;

  result = result && poset_state_handle::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    /// @todo finish poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

