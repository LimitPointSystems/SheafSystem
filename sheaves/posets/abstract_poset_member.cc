

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class abstract_poset_member.

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"

#include "array_poset_dof_map.h"
#include "array_index_space_state.h"
#include "dof_descriptor_array.h"
#include "error_message.h"
#include "index_space_iterator.h"
#include "mutable_index_space_handle.h"
#include "namespace_poset.h"
#include "pool.h"
#include "poset.h"
#include "poset_crg_state.h"
#include "poset_dof_map.h"
#include "poset_joiner.h"
#include "poset_path.h"
#include "poset_slicer.h"
#include "poset_state.h"
#include "poset_state_handle.h"
#include "postorder_itr.h"
#include "preorder_itr.h"
#include "primitives_poset.h"
#include "primitives_poset_dof_map.h"
#include "primitives_poset_schema.h"
#include "schema_poset_member.h"
#include "sheaves_namespace.h"
#include "hub_index_space_handle.h"
#include "std_set.h"
#include "std_strstream.h"
#include "std_vector.h"
#include "stop_watch.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "subposet_state.h"
#include "tern.h"
#include "triorder_itr.h"
#include "zn_to_bool.h"

//#define DIAGNOSTIC_OUTPUT

// ============================================================================
// CLASS ABSTRACT_POSET_MEMBER_TABLE_DOFS_TYPE
// ============================================================================
  
// ===========================================================
// ABSTRACT_POSET_MEMBER_TABLE_DOFS_TYPE FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_poset_member_table_dofs_type::dof_type&
sheaf::abstract_poset_member_table_dofs_type::
operator[](size_type xi)
{
  return reinterpret_cast<dof_type*>(this)[xi];
}

const sheaf::abstract_poset_member_table_dofs_type::dof_type&
sheaf::abstract_poset_member_table_dofs_type::
operator[](size_type xi) const
{
  return reinterpret_cast<const dof_type*>(this)[xi];
}

sheaf::abstract_poset_member_table_dofs_type*
sheaf::abstract_poset_member_table_dofs_type::
clone() const
{
  return new abstract_poset_member_table_dofs_type;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ============================================================================
// CLASS ABSTRACT_POSET_MEMBER_ROW_DOFS_TYPE
// ============================================================================
  
// ===========================================================
// ABSTRACT_POSET_MEMBER_ROW_DOFS_TYPE FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_poset_member_row_dofs_type::dof_type&
sheaf::abstract_poset_member_row_dofs_type::
operator[](size_type xi)
{
  return reinterpret_cast<dof_type*>(this)[xi];
};

const sheaf::abstract_poset_member_row_dofs_type::dof_type&
sheaf::abstract_poset_member_row_dofs_type::
operator[](size_type xi) const
{
  return reinterpret_cast<const dof_type*>(this)[xi];
};

sheaf::abstract_poset_member_row_dofs_type*
sheaf::abstract_poset_member_row_dofs_type::
clone() const
{
  return new abstract_poset_member_row_dofs_type;
};

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ============================================================================
// CLASS ABSTRACT_POSET_MEMBER
// ============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::abstract_poset_member::
new_host(namespace_type& xns, const poset_path& xpath, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering abstract_poset_member::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(unexecutable("xschema_path conforms to standard_schema_path"));
  

  // Body:

  host_type::new_table(xns, xpath, xschema_path, xauto_access);

  // Postconditions:

  ensure(xns.contains_path(xpath, xauto_access));
  ensure(!xns.poset_state_is_read_accessible(xpath, xauto_access));
  ensure(xns.member_poset(xpath, xauto_access).schema(true).path(true) == xschema_path);

  // Exit:

  // cout << "Leaving abstract_poset_member::new_host." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
  
// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_poset_member&
sheaf::abstract_poset_member::
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

sheaf::abstract_poset_member::
~abstract_poset_member()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit

  return;
}

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
clone(bool xnew_state, bool xauto_access) const
{

  // Preconditions:

  require(is_attached());
  require(xauto_access || (xnew_state ? host()->in_jim_edit_mode() :
                           host()->state_is_read_accessible()));

  // Body:

  // create new version of current

  abstract_poset_member *result = clone();

  // Either attach to a new state or attach to the current state.

  if(xnew_state)
  {
    result->new_jim_state(host(), 0, false, xauto_access);
  }
  else
  {
    if(xauto_access)
      host()->get_read_access();

    result->attach_to_state(this);

    if(xauto_access)
      host()->release_access();
  }

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

void
sheaf::abstract_poset_member::
new_jim_state(poset_dof_map* xdof_map, bool xcopy_dof_map, bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? host()->in_jim_edit_mode() : true);
  require(!xauto_access && xdof_map != 0 ? xdof_map->host()->state_is_read_accessible() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    host()->begin_jim_edit_mode();

    if(xdof_map != 0)
      xdof_map->host()->get_read_access();
  }

  require(xdof_map != 0 ? host()->row_dof_map_conforms(xdof_map) : true);
  require(xdof_map != 0 ? dof_map_is_ancestor_of(xdof_map) : true);
  require(xdof_map != 0 ? xdof_map->schema().row_conforms_to(host()->schema()) : true);

  // Body:

  //   new_jim_state(_host, xdof_map, xcopy_dof_map);

  // Create new jim and attach to it.
  // Attach_to_state(xindex) attaches but does not reinitialize handle data members.

  pod_index_type lindex = _host->new_member(true, xdof_map, xcopy_dof_map);
  attach_to_state(lindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    host()->end_jim_edit_mode();

    if(xdof_map != 0)
      xdof_map->host()->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jim_state(pod_index_type xtuple_id, bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? host()->in_jim_edit_mode() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    host()->begin_jim_edit_mode();

  require(host()->contains_row_dof_tuple(xtuple_id));

  // Body:

  // Get auto access

  // Create new jim and attach to it.
  // Attach_to_state(xindex) attaches but does not reinitialize handle data members.

  pod_index_type lindex = _host->new_member(true, xtuple_id);
  attach_to_state(lindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(dof_tuple_id(false) == xtuple_id);

  // Release access if auto access was requested.

  if(xauto_access)
    host()->end_jim_edit_mode();

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jim_state(const scoped_index& xtuple_id, bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? host()->in_jim_edit_mode() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    host()->begin_jim_edit_mode();

  require(host()->contains_row_dof_tuple(xtuple_id));

  // Body:

  new_jim_state(xtuple_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(dof_tuple_id(false) == xtuple_id.hub_pod());

  // Release access if auto access was requested.

  if(xauto_access)
    host()->end_jim_edit_mode();

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jim_state(poset_state_handle* xhost, poset_dof_map* xdof_map, bool xcopy_dof_map, bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->in_jim_edit_mode() : true);
  require(!xauto_access && xdof_map != 0 ? xdof_map->host()->state_is_read_accessible() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode();

    if(xdof_map != 0)
      xdof_map->host()->get_read_access();
  }

  require(host_is_ancestor_of(xhost));
  require(xdof_map != 0 ? xhost->row_dof_map_conforms(xdof_map) : true);
  require(xdof_map != 0 ? dof_map_is_ancestor_of(xdof_map) : true);
  require(xdof_map != 0 ? xdof_map->schema().row_conforms_to(xhost->schema()) : true);

  // Body:

  // Create new jim and attach to it.
  // Attach_to_state(xhost, xindex) reinitializes and attaches handle data members.

  pod_index_type lindex = xhost->new_member(true, xdof_map, xcopy_dof_map);
  attach_to_state(xhost, lindex);

  // Postconditions:

  ensure(abstract_poset_member::invariant()); /// @todo remove scope when debugged
  ensure(unexecutable(host()->member_ct() == old host->member_ct() + 1));
  ensure(is_attached());
  ensure(!is_restricted());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->end_jim_edit_mode();

    if(xdof_map != 0)
      xdof_map->host()->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jim_state(poset_state_handle* xhost, pod_index_type xtuple_id, bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->in_jim_edit_mode() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    xhost->begin_jim_edit_mode();

  require(host_is_ancestor_of(xhost));
  require(xhost->contains_row_dof_tuple(xtuple_id));

  // Body:

  // Create new jim and attach to it.
  // Attach_to_state(xhost, xindex) reinitializes and attaches handle data members.

  pod_index_type lindex = xhost->new_member(true, xtuple_id);
  attach_to_state(xhost, lindex);

  // Postconditions:

  ensure(abstract_poset_member::invariant()); /// @todo remove scope when debugged
  ensure(unexecutable(host()->member_ct() == old host->member_ct() + 1));
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(dof_tuple_id(false) == xtuple_id);

  // Release access if auto access was requested.

  if(xauto_access)
    xhost->end_jim_edit_mode();

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jim_state(poset_state_handle* xhost, const scoped_index& xtuple_id, bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->in_jim_edit_mode() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    xhost->begin_jim_edit_mode();

  require(host_is_ancestor_of(xhost));
  require(xhost->contains_row_dof_tuple(xtuple_id));

  // Body:

  new_jim_state(xhost, xtuple_id.hub_pod(), false);

  // Postconditions:

  ensure(abstract_poset_member::invariant()); /// @todo remove scope when debugged
  ensure(unexecutable(host()->member_ct() == old host->member_ct() + 1));
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(dof_tuple_id(false) == xtuple_id.hub_pod());

  // Release access if auto access was requested.

  if(xauto_access)
    xhost->end_jim_edit_mode();

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jrm_state(bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? is_attached() : state_is_read_write_accessible());

  // Body:

  if(xauto_access)
  {
    host()->get_read_write_access(true);
  }


  /// @issue should we allow direct creation and linking of jrms?

  // Create new jrm and attach to it.
  // Attach_to_state(xindex) attaches but does not reinitialize handle data members.

  attach_to_state(host()->new_member(false));

  // Postconditions:

  ensure(abstract_poset_member::invariant()); /// @todo remove scope when debugged
  ensure(is_attached());
  ensure(!is_restricted());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    host()->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jrm_state(poset_state_handle* xhost, bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(!xauto_access ? xhost->state_is_read_write_accessible() : true);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  // Body:

  /// @issue should we allow direct creation and linking of jrms?

  // Create new jrm and attach to it.
  // Attach_to_state(xhost, xindex) reinitializes and attaches handle data memebrs.

  pod_index_type lmbr_id = xhost->new_member(false);
  attach_to_state(xhost, lmbr_id);

  // Postconditions:

  ensure(abstract_poset_member::invariant()); /// @todo remove scope when debugged
  ensure(is_attached());
  ensure(!is_restricted());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jrm_state(const scoped_index* xexpansion,
              int xexpansion_ct,
              const tern& xgreatest,
              bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? is_attached() : state_is_read_write_accessible());
  require(precondition_of(new_jrm_state(host(), xexpansion, xexpansion_ct, xgreatest, xauto_access)));

  // Body:

  new_jrm_state(host(), xexpansion, xexpansion_ct, xgreatest, false);

  // Postconditions:

  ensure(postcondition_of(new_jrm_state(host(), xexpansion, xexpansion_ct, xgreatest, xauto_access)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jrm_state(poset_state_handle* xhost,
              const scoped_index* xexpansion,
              int xexpansion_ct,
              const tern& xgreatest,
              bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_auto_read_write_accessible(xauto_access));
  require(xexpansion != 0);

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  require(xhost->contains_members(xexpansion, xexpansion_ct));

  // Body:

  // Joiner attaches this to result using attach_to_state(xhost, xindex);
  // reinitializes and attaches handle data members.

  poset_joiner joiner(xhost);

  joiner.join(xexpansion, xexpansion_ct, xgreatest, *this);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(host() == xhost);
  ensure(unexecutable(is_jim() == this is max member of xexpansion));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jem_state(abstract_poset_member* xother, bool xgreatest, bool xauto_access)
{
  // Preconditions:

  require(xother != 0);
  require(xother->state_is_auto_read_write_accessible(xauto_access));
  require(precondition_of(new_jem_state(xother->host(), xother->index(), xgreatest, xauto_access)));

  // Body:

  new_jem_state(xother->host(), xother->index(), xgreatest, xauto_access);

  // Postconditions:

  require(postcondition_of(new_jem_state(xother->host(), xother->index(), xgreatest, xauto_access)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jem_state(poset_state_handle* xhost,
              pod_index_type xhub_id,
              bool xgreatest,
              bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_auto_read_write_accessible(xauto_access));
  require(host_is_ancestor_of(xhost));
  require(xhost->contains_member(xhub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    xhost->get_read_write_access(true);
  }

  // Create new jem and attach to it;
  // new_member ensures upper and lower cover empty.
  // Attach_to_state(xhost, xhub_id) reinitializes and attaches handle data members.

  pod_index_type lindex = xhost->new_member(false);
  if(xgreatest)
  {
    xhost->link_greatest_jem(lindex, xhub_id);
  }
  else
  {
    xhost->link_least_jem(lindex, xhub_id);
  }

  attach_to_state(xhost, lindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(host()->is_jem(xhub_id, index().pod()));

  // If xgreatest, then either this is greatest jem or top is,
  // otherwise either this is least jem or bottom is.

  ensure(xgreatest ?
         (host()->greatest_jem(xhub_id) == index().pod() ||
          host()->greatest_jem(xhub_id) == TOP_INDEX) :
         (host()->least_jem(xhub_id) == index().pod() ||
          host()->is_jim(host()->least_jem(xhub_id)) ||
          host()->least_jem(xhub_id) == BOTTOM_INDEX));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
new_jem_state(poset_state_handle* xhost,
              const scoped_index& xid,
              bool xgreatest,
              bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jem_state(xhost, xindex.hub_pod(), xgreatest, xauto_access)));

  // Body:

  new_jem_state(xhost, xid.hub_pod(), xgreatest, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jem_state(xhost, xindex.hub_pod(), xgreatest, xauto_access)));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::abstract_poset_member::
abstract_poset_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

void
sheaf::abstract_poset_member::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(unexecutable(data members created));

  // Body:

  // Have just attached to a new or different member in the same host.
  // Attach the handle data members for the different member.

  // This routine is conceptually abstract.
  // Implemented as empty body here to define the postcondition.
  // Does nothing in this class.
  // Intended for redefinition in derived classes,
  // c.f. partial_poset_member and schema_poset_member.

  // Postconditions:

  ensure(!is_restricted());

  // Exit

  return;
}

char*
sheaf::abstract_poset_member::
table_dof_ptr(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());

  // Body:

  char* result = host()->table_dof_map(xrequire_write_access).dofs();

  // Postconditions:

  /// @hack can't call invariant because not const
  // ensure(invariant());
  ensure(result != 0);

  // Exit:

  return result;
}

char*
sheaf::abstract_poset_member::
row_dof_ptr(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());

  // Body:

  char* result =
    reinterpret_cast<char*>(dof_map(xrequire_write_access).dof_tuple());

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MEMBER ATTRIBUTE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::abstract_poset_member::
is_jim(bool xin_current_version) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = host()->is_jim(index(), xin_current_version);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
is_atom() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = host()->is_atom(index());

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::schema_poset_member&
sheaf::abstract_poset_member::
schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // This routine is conceptually abstract;
  // implemented here only to establish the contract.

  // The following implementation is overidden
  // in all direct descendants, and is used here
  // only to make the compiler happy with the postcondition.

  schema_poset_member& result = unrestricted_schema();

  // Postconditions:

  ensure(result.le(&(unrestricted_schema())));

  // Exit:

  return result;
}

const sheaf::schema_poset_member&
sheaf::abstract_poset_member::
schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // This routine is conceptually abstract;
  // implemented here only to establish the contract.

  // The following implementation is overidden
  // in all direct descendants, and is used here
  // only to make the compiler happy with the postcondition.

  const schema_poset_member& result = unrestricted_schema();

  // Postconditions:

  ensure(result.le(&(unrestricted_schema())));

  // Exit:

  return result;
}

sheaf::schema_poset_member&
sheaf::abstract_poset_member::
schema(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  
  schema_poset_member& result = schema();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(postcondition_of(schema()));

  // Exit:

  return result;
}

const sheaf::schema_poset_member&
sheaf::abstract_poset_member::
schema(bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  const schema_poset_member& result = schema();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(postcondition_of(schema()));

  // Exit:

  return result;
}

sheaf::schema_poset_member&
sheaf::abstract_poset_member::
unrestricted_schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // If this has a dof map, the unrestricted schema of this is the schema of
  // its dof map, otherwise, use the schema of the host.
  // Note that the version of the schema used by the dof map is
  // not necessarily the version currently used by the host.
  // Also note that if the host has multiple versions, a member
  // has a dof map if it is a jim in some version of the host.

  /// @issue what does the schema feature mean for a member that doesn't have a dof map?

  schema_poset_member& result = is_jim(false) ? dof_map().schema() : host()->schema();

  // Postconditions:

  ensure(result.leqv(host()->schema().index()));

  // Exit

  return result;
}

const sheaf::schema_poset_member&
sheaf::abstract_poset_member::
unrestricted_schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // If this has a dof map, the unrestricted schema of this is the schema of
  // its dof map, otherwise, use the schema of the host.
  // Note that the version of the schema used by the dof map is
  // not necessarily the version currently used by the host.
  // Also note that if the host has multiple versions, a member
  // has a dof map if it is a jim in some version of the host.

  /// @issue what does the schema feature mean for a member that doesn't have a dof map?

  const schema_poset_member& result = is_jim(false) ? dof_map().schema() : host()->schema();

  // Postconditions:

  ensure(result.leqv(host()->schema().index()));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
schema_is(const string& xschema_name) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = schema().name() == xschema_name;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
same_schema(const abstract_poset_member* xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());


  // Body:

  result = schema().is_same_state(&(xother->schema()));

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESTRICTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::abstract_poset_member::
is_restricted() const
{
  bool result;

  // Preconditions:

  require(is_attached() ? state_is_read_accessible() : true); // required by host()->schema()

  // Body:

  result = ( is_attached() && !schema().is_same_state(&(unrestricted_schema())) );

  // Postconditions:

  ensure(result == ( is_attached() && !schema().is_same_state(&(unrestricted_schema())) ));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
is_same_restriction(const abstract_poset_member* xother) const
{
  bool result;

  // Preconditions:

  require(is_attached() ? state_is_read_accessible() : true); // may be required by schema()
  require(xother != 0);
  require(xother->is_attached() ? xother->state_is_read_accessible() : true);

  // Body:

  if(is_attached())
  {
    result = xother->is_attached() && schema().is_same_state(&(xother->schema()));
  }
  else
  {
    result = !xother->is_attached();
  }

  // Postconditions:

  ensure(unexecutable(result == this and xother are attached and have the same schema or both are unattached));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_dof_map&
sheaf::abstract_poset_member::
dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  return  _host->member_dof_map(_index.pod(), xrequire_write_access);
}

const sheaf::poset_dof_map&
sheaf::abstract_poset_member::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  return  _host->member_dof_map(_index.pod(), xrequire_write_access);
}

bool
sheaf::abstract_poset_member::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // This handle requires xdof_map to be of type poset_dof_map,
  // so the result is always true.

  result = true;

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
dof_tuple(const void* xbuf, size_t xbuflen) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(!is_restricted());
  require(xbuf != 0);
  require(unexecutable(xbuf points to a buffer of length xbuflen));
  require(xbuflen >= dof_map().dof_tuple_ub());

  // Body:

  dof_map().get_dof_tuple(const_cast<void*>(xbuf), xbuflen);

  // Postconditions:

  ensure(unexecutable(xbuf contains copy of dof tuple));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
put_dof_tuple(const void* xbuf, size_t xbuflen)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_restricted());
  require(xbuf != 0);
  require(unexecutable(xbuf points to a buffer of length xbuflen));
  require(xbuflen >= dof_map().dof_tuple_ub());
  require(unexecutable(xbuf contains copy of dof tuple));

  // Body:

  dof_map().put_dof_tuple(xbuf, xbuflen);

  // Postconditions:

  ensure(unexecutable(dof tuple has been copied to internal storage));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::abstract_poset_member::
dof_tuple_id(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  pod_index_type result = host()->member_dof_tuple_id(index().pod(), xauto_access);

  // Postconditions:

  ensure(host()->contains_row_dof_tuple(result) || (!is_valid(result)));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
dof_tuple_id(scoped_index& result, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  host()->member_dof_tuple_id(index(), result, xauto_access);

  // Postconditions:

  ensure(host()->contains_row_dof_tuple(result) || (!is_valid(result)));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
put_dof_tuple_id(pod_index_type xtuple_index, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(host()->contains_row_dof_tuple(xtuple_index) || !is_valid(xtuple_index));

  // Body:

  host()->put_member_dof_tuple_id(_index.pod(), xtuple_index, xauto_access);

  // Postconditions:

  ensure(dof_tuple_id(xauto_access) == xtuple_index);

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
put_dof_tuple_id(const scoped_index& xtuple_index, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(host()->contains_row_dof_tuple(xtuple_index) || !is_valid(xtuple_index));

  // Body:

  host()->put_member_dof_tuple_id(_index, xtuple_index, xauto_access);

  // Postconditions:

  ensure(dof_tuple_id(xauto_access) == xtuple_index.hub_pod());

  // Exit

  return;
}

void*
sheaf::abstract_poset_member::
table_dofs()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  
  // Body:

  void* result = _host->table_dof_map(true).dof_tuple();

  // Postconditions:

  // Exit:

  return result;
}

const void*
sheaf::abstract_poset_member::
table_dofs() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  const void* result = _host->table_dof_map(false).dof_tuple();

  // Postconditions:

  // Exit:

  return result;
}

void*
sheaf::abstract_poset_member::
table_dofs(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  void* result = table_dofs();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

const void*
sheaf::abstract_poset_member::
table_dofs(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const void* result = table_dofs();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

void*
sheaf::abstract_poset_member::
row_dofs()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  
  // Body:

  void* result = _host->member_dof_map(_index.pod(), true).dof_tuple();

  // Postconditions:

  // Exit:

  return result;
}

const void*
sheaf::abstract_poset_member::
row_dofs() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  const void* result = _host->member_dof_map(_index.pod(), false).dof_tuple();

  // Postconditions:

  // Exit:

  return result;
}

void*
sheaf::abstract_poset_member::
row_dofs(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  void* result = row_dofs();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

const void*
sheaf::abstract_poset_member::
row_dofs(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const void* result = row_dofs();

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
// DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primitive_value
sheaf::abstract_poset_member::
dof(pod_index_type xdof_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().row_dof_id_space().contains(xdof_id));

  // Body:

  primitive_value result = dof_map(false).dof(xdof_id);

  // Postconditions:

  // Exit:

  return result;
}
 
sheaf::primitive_value
sheaf::abstract_poset_member::
dof(const scoped_index& xdof_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(schema(xauto_access).row_dof_id_space(xauto_access).contains(xdof_id));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  primitive_value result = dof_map(false).dof(xdof_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::abstract_poset_member::
put_dof(pod_index_type xdof_id, const primitive_value& xdof)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().row_dof_id_space().contains(xdof_id));
  require(xdof.id() == schema().type(xdof_id, false));

  // Body:

  dof_map(true).put_dof(xdof_id, xdof);

  // Postconditions:

  ensure(dof(xdof_id) == xdof);

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
put_dof(const scoped_index& xdof_id, const primitive_value& xdof, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).row_dof_id_space(xauto_access).contains(xdof_id));
  require(xdof.id() == schema(xauto_access).type(xdof_id, false, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).put_dof(xdof_id, xdof);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(dof(xdof_id) == xdof);

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().row_dof_id_space().contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, false));

  // Body:

  dof_map(false).get_dof(xdof_id, xdof, xdof_size);

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
get_dof(const scoped_index& xdof_id, void* xdof, size_type xdof_size, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(schema(xauto_access).row_dof_id_space(xauto_access).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema(xauto_access).size(xdof_id, false, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  dof_map(false).get_dof(xdof_id, xdof, xdof_size);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().row_dof_id_space().contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, false));

  // Body:

  dof_map(true).put_dof(xdof_id, xdof, xdof_size);

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
put_dof(const scoped_index& xdof_id, const void* xdof, size_type xdof_size, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).row_dof_id_space(xauto_access).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema(xauto_access).size(xdof_id, false, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).put_dof(xdof_id, xdof, xdof_size);

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
// ORDERING RELATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::abstract_poset_member::
le(pod_index_type xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = _host->le(xother_index, _index.pod());

  // Postconditions:

  ensure(unexecutable(other is in the up set
                        of this));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
le(const scoped_index& xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = le(xother_index.hub_pod());

  // Postconditions:

  ensure(unexecutable(other is in the up set
                        of this));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
le(const abstract_poset_member* other) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:
  
  result = has_same_host(other) && _host->le(other->index().pod(),
					     _index.pod());

  // Postconditions:

  ensure(unexecutable(other is in the up set
                        of this));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
leqv(pod_index_type xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = _host->leqv(xother_index, _index.pod());

  // Postconditions:

  ensure(unexecutable("other is in the up set of this or other is_jem(this)"));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
leqv(const scoped_index& xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = leqv(xother_index.hub_pod());

  // Postconditions:

  ensure(unexecutable("other is in the up set of this or other is_jem(this)"));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
lt(pod_index_type xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = le(xother_index) && (_index.pod() != xother_index);

  // Postconditions:

  ensure(result == (le(xother_index) && (index().pod() != xother_index)));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
lt(const scoped_index& xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = lt(xother_index.hub_pod());

  // Postconditions:

  ensure(result == (le(xother_index) && (index() !=~ xother_index)));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
lt(const abstract_poset_member* other) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = le(other) && (_index != other->index());

  // Postconditions:

  ensure(result == (le(other) && (index() != other->index())));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
ge(pod_index_type xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  // This is >= other if other is <= this.

  result = _host->le(_index.pod(), xother_index);

  // Postconditions:

  ensure(unexecutable(other is in the up set
                        of this));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
ge(const scoped_index& xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = ge(xother_index.hub_pod());

  // Postconditions:

  ensure(unexecutable(other is in the up set
                        of this));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
ge(const abstract_poset_member* other) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // This is >= other if other is <= this.

  result = has_same_host(other) && _host->le(_index.pod(),
					     other->index().pod());

  // Postconditions:

  ensure(unexecutable(other is in the up set
                        of this));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
geqv(pod_index_type xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  // This is >= other if other is <= this.

  result = _host->leqv(_index.pod(), xother_index);

  // Postconditions:

  ensure(unexecutable("this is in the up set of other or this is_jem of other"));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
geqv(const scoped_index& xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = geqv(xother_index.hub_pod());

  // Postconditions:

  ensure(unexecutable("this is in the up set of other or this is_jem of other"));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
gt(pod_index_type xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = ge(xother_index) && (_index.pod() != xother_index);

  // Postconditions:

  ensure(result == (ge(xother_index) && (index().pod() != xother_index)));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
gt(const scoped_index& xother_index) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xother_index));

  // Body:

  result = ge(xother_index.hub_pod());

  // Postconditions:

  ensure(result == (ge(xother_index) && (index() !=~ xother_index)));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
gt(const abstract_poset_member* other) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = ge(other) && (_index != other->index());

  // Postconditions:

  ensure(result == (ge(other) && (index() != other->index())));

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
is_jem(const abstract_poset_member* xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = _host->is_jem( index(), xother->index() );

  // Postconditions:

  // Exit

  return result;
}

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
greatest_jem() const
{
  abstract_poset_member* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = clone();
  greatest_jem_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
greatest_jem_pa(abstract_poset_member* result) const
{

  // Preconditions:

  require(state_is_read_accessible());
  require(result->is_ancestor_of(this));

  // Body:

  result->attach_to_state(_host, _host->greatest_jem(_index.pod()));

  // Postconditions:

  // Exit

  return;
}

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
least_jem() const
{
  abstract_poset_member* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = clone();
  least_jem_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
least_jem_pa(abstract_poset_member* result) const
{

  // Preconditions:

  require(state_is_read_accessible());
  require(result->is_ancestor_of(this));

  // Body:

  result->attach_to_state(_host, _host->least_jem(_index.pod()));

  // Postconditions:

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
merge_jem(const abstract_poset_member* xjem)
{

  // Preconditions:

  require(has_same_host(xjem));
  require(!xjem->is_jem(&(host()->bottom())));
  require(state_is_read_write_accessible());
  require(!is_jim());
  require(!xjem->is_jim());
  require(unexecutable(xjem really is join-equivalent to this));

  // Body:

  _host->merge_jems(_index.pod(), xjem->index().pod());

  // Postconditions:

  ensure(is_jem(xjem));
  ensure(xjem->le(this));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER RELATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::abstract_poset_member::
covers(const abstract_poset_member* xother) const
{
  bool result = false;

  // Preconditions:

  require(xother->host() == host());
  require(state_is_read_accessible());

  // Body:

  result = host()->contains_link(_index.pod(), xother->index().pod());

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
covers(pod_index_type xhub_id) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xhub_id));

  // Body:

  result = host()->contains_link(_index.pod(), xhub_id);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
covers(const scoped_index& xid) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->contains_member(xid));

  // Body:

  return covers(xid.hub_pod());
}

void
sheaf::abstract_poset_member::
create_cover_link(abstract_poset_member* xlesser)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require(host()->in_jim_edit_mode());
  require(has_same_host(xlesser));

  /// @issue should we allow direct creation and linking of jrms?
  /// require(is_jim() && xlesser->is_jim());

  // ensure acyclic and intransitive
  require(!le(xlesser) && !xlesser->le(this));


  // Body:

  (void) _host->new_link(_index.pod(), xlesser->index().pod());

  // Postconditions:

  ensure(invariant());
  ensure(covers(xlesser));

  return;
}

void
sheaf::abstract_poset_member::
delete_cover_link(abstract_poset_member* xlesser)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(host()->in_jim_edit_mode());

  /// @issue should we allow direct creation and linking of jrms?
  /// require(is_jim() && xlesser->is_jim());

  // Body:

  _host->delete_link(_index.pod(), xlesser->index().pod());

  // Postconditions:

  ensure(invariant());
  ensure(!covers(xlesser));

  // Exit

  return;
}

sheaf::index_space_handle&
sheaf::abstract_poset_member::
get_cover_id_space(bool xlower) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return _host->get_cover_id_space(xlower, _index.pod());
}

void
sheaf::abstract_poset_member::
release_cover_id_space(index_space_handle& xcover_id_space) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  _host->release_cover_id_space(xcover_id_space);

  // Postconditions:

  // Exit:

  return;
}

sheaf::index_space_iterator&
sheaf::abstract_poset_member::
get_cover_id_space_iterator(bool xlower) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return _host->get_cover_id_space_iterator(xlower, _index.pod());
}

void
sheaf::abstract_poset_member::
release_cover_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  _host->release_cover_id_space_iterator(xitr);

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::abstract_poset_member::
cover_contains_iterator(bool xlower, const index_space_iterator& xitr) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body

  return _host->cover_contains_iterator(xlower, _index.pod(), xitr);
}

bool
sheaf::abstract_poset_member::
cover_is_empty(bool xlower) const
{
  // Preconditions:

  require(state_is_read_accessible());

  return _host->cover_is_empty(xlower, _index.pod());
}

bool
sheaf::abstract_poset_member::
cover_is_singleton(bool xlower) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  return _host->cover_is_singleton(xlower, _index.pod());
}

sheaf::size_type
sheaf::abstract_poset_member::
cover_ct(bool xlower) const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = _host->cover_ct(xlower, _index.pod());

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
cover_contains_member(bool xlower, pod_index_type xother_mbr_index) const
{
  // Preconditions:

  require(state_is_read_accessible());

  return _host->cover_contains_member(xlower, _index.pod(), xother_mbr_index);
}

bool
sheaf::abstract_poset_member::
cover_contains_member(bool xlower, const scoped_index& xother_mbr_index) const
{
  // Preconditions:

  require(state_is_read_accessible());

  return cover_contains_member(xlower, xother_mbr_index.hub_pod());
}

bool
sheaf::abstract_poset_member::
cover_is_equal(bool xlower, pod_index_type xother_mbr_index) const
{
  // Preconditions:

  require(state_is_read_accessible());

  return _host->cover_is_equal(xlower, _index.pod(), xother_mbr_index);
}

bool
sheaf::abstract_poset_member::
cover_is_equal(bool xlower, const scoped_index& xother_mbr_index) const
{
  // Preconditions:

  require(state_is_read_accessible());

  return cover_is_equal(xlower, xother_mbr_index.hub_pod());
}

sheaf::pod_index_type
sheaf::abstract_poset_member::
first_cover_member(bool xlower) const
{
  // Preconditions:

  require(state_is_read_accessible());

  return _host->first_cover_member(xlower, _index.pod());
}

void
sheaf::abstract_poset_member::
first_cover_member(bool xlower, scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  result.put(_host->member_hub_id_space(false), first_cover_member(xlower));
}

void
sheaf::abstract_poset_member::
insert_cover_member(pod_index_type xother_mbr_index, bool xlower)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  _host->insert_cover_member(xother_mbr_index, xlower, _index.pod());

  // Postconditions:

  ensure(unexecutable(cover_contains_member(xlower, xother_mbr_index)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
insert_cover_member(const scoped_index& xother_mbr_index, bool xlower)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  insert_cover_member(xother_mbr_index.hub_pod(), xlower);

  // Postconditions:

  ensure(unexecutable(cover_contains_member(xlower, xother_mbr_index)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
remove_cover_member(pod_index_type xother_mbr_index, bool xlower)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  _host->remove_cover_member(xother_mbr_index, xlower, _index.pod());

  // Postconditions:

  ensure(unexecutable(!cover_contains_member(xlower, xother_mbr_index)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
remove_cover_member(const scoped_index& xother_mbr_index, bool xlower)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  remove_cover_member(xother_mbr_index.hub_pod(), xlower);

  // Postconditions:

  ensure(unexecutable(!cover_contains_member(xlower, xother_mbr_index)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
remove_cover_member(index_space_iterator& xitr, bool xlower)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  _host->remove_cover_member(xitr, xlower, _index.pod());

  // Postconditions:

  ensure(unexecutable(!cover_contains_member(xlower, xother_mbr_index)));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
clear_cover(bool xlower)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  _host->clear_cover(xlower, _index.pod());

  // Postconditions:

  ensure(cover_is_empty(xlower));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
copy_cover(bool xlower, pod_index_type xother_mbr_index)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(host()->contains_member(xother_mbr_index));

  // Body:

  _host->copy_cover(xlower, _index.pod(), xother_mbr_index);

  // Postconditions:

  ensure(cover_is_equal(xlower, xother_mbr_index));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
copy_cover(bool xlower, const scoped_index& xother_mbr_index)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(host()->contains_member(xother_mbr_index));

  // Body:

  copy_cover(xlower, xother_mbr_index.hub_pod());

  // Postconditions:

  ensure(cover_is_equal(xlower, xother_mbr_index));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOWN SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
sheaf::abstract_poset_member::
down_ct() const
{
  // Preconditions:

  // Body:

  int result = down_ct(WHOLE_INDEX);

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

int
sheaf::abstract_poset_member::
down_ct(pod_index_type xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  // Traverse down set

  zn_to_bool_postorder_itr itr(*this, xfilter_index, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    result++;
    itr.next();
  }

  // Postconditions:

  ensure(result >= 0 );

  // Exit

  return result;
}

int
sheaf::abstract_poset_member::
down_ct(const scoped_index& xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = down_ct(xfilter_index.hub_pod());

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
sheaf::abstract_poset_member::
down() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host(), 0, false);
  down_pa(result);


  // Postconditions:

  require(result != 0);
  require(postcondition_of(down_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
down_pa(subposet* result) const
{

  // Preconditions:

  // Body:

  // Traverse down set, inserting members into result

  poset_slicer slicer(_host);
  abstract_poset_member* cthis = const_cast<abstract_poset_member*>(this);
  slicer.down_set_pa(cthis, result);

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is down set
                        of this));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
delete_down(bool xdelete_exterior, bool xenter_jim_edit_mode)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!xenter_jim_edit_mode ? host()->in_jim_edit_mode() : true);
  require(!name().empty());
  require(host()->contains_member(poset_path::boundary_name(name())));
  require(host()->includes_subposet("__boundary_jims"));

  // Body:

  poset_state_handle* lhost = host();
  bool old_host_in_jim_edit_mode = lhost->in_jim_edit_mode();

  if(!old_host_in_jim_edit_mode)
  {
    lhost->begin_jim_edit_mode();
  }

  // Block containing a single element is a special case:

  total_poset_member lbdy(host(), poset_path::boundary_name(name()));
  pod_index_type lblock_bdy_index = lbdy.index();

  subposet lelements(lhost, "__elements");
  if(_host->cover_is_singleton(LOWER, _index.pod()))
  {
    pod_index_type lfirst_mbr = lhost->first_cover_member(LOWER, _index.pod());
    if(lelements.contains_member(lfirst_mbr))
    {
      // This block contains only a single element.
      // The block doesn't cover the boundary, the element does.
      // The algorithm below depends on the block covering the
      // boundary, so explicitly delete the element and
      // attach the boundary to the block.

      total_poset_member lele(lhost, lfirst_mbr);
      lele.delete_state();
      create_cover_link(&lbdy);
    }
  }

  lelements.detach_from_state();
  lbdy.detach_from_state();

  // The down set traversal:
  // Mark the members of the down set.

  zn_to_bool ldown_set(lhost->member_index_ub().pod());
  zn_to_bool_postorder_itr down_itr(*this, DOWN, NOT_STRICT);
  while(!down_itr.is_done())
  {
    ldown_set.put(down_itr.index().pod(), true);
    down_itr.next();
  }

  // The lower cover traversal:
  // Initialize the deletion traversal by removing the
  // links from this to the internal members of its lower cover.
  // A member is internal if this is the only member of its
  // upper cover and it is not the block boundary.

  index_space_iterator& lc_itr = _host->get_cover_id_space_iterator(LOWER, _index.pod());
  while(!lc_itr.is_done())
  {
    pod_index_type lindex = lc_itr.hub_pod();

    if(_host->cover_is_singleton(UPPER, lindex) &&
        (xdelete_exterior || (lindex != lblock_bdy_index)))
    {
      // This is an internal member of the lower cover.
      // Delete the only entry in its upper cover.

      _host->clear_cover(UPPER, lindex);

      // The upper cover should now be empty.
      // This is essential for the deletion algorithm.

      assertion(_host->cover_is_empty(UPPER, lindex));

      // Delete the entry from the lower cover of this.

      // Note that remove_cover_member invalidates the itr
      // passed to it, but the postfix increment passes a copy of lc_itr.

      _host->remove_cover_member(lc_itr, LOWER, _index.pod());
    }

    lc_itr.next();
  }
  _host->release_cover_id_space_iterator(lc_itr);

  // The deletion traversal:
  // Traverse the poset in postorder up from the bottom.
  // The actions are defined to detect internal members,
  // delete them, and remove them from the up set of bottom.

  subposet lbdy_jims(lhost, "__boundary_jims");
  set<pod_index_type> lclean_up_set;
  zn_to_bool lin_other_down_set(lhost->member_index_ub().pod());
  scoped_index lanchor = index();
  bool lnot_in_down_set = false;

  zn_to_bool_triorder_itr up_itr(lhost->bottom(), UP, NOT_STRICT);
  while(!up_itr.is_done())
  {
    const scoped_index& lindex = up_itr.index();

    switch(up_itr.action())
    {
    case zn_to_bool_triorder_itr::PREVISIT_ACTION:

      lnot_in_down_set = !ldown_set[lindex.pod()];

      if(lnot_in_down_set)
      {
        // The current member is not in the down set
        // of this, so it is in the down set of some
        // other block.

        lin_other_down_set.put(lindex.pod(), true);
      }

      // Don't need to go deeper if the current
      // member is not in the down set or if we're at this.

      up_itr.next(lnot_in_down_set || (lindex ==~ lanchor));

      break;

    case zn_to_bool_triorder_itr::LINK_ACTION:

      if(!lhost->contains_member(up_itr.lesser_index()))
      {
        // We've previously deleted the upper member of the link.

        // Remove it from the upper cover of the greater member.
        // Note that this is an ascending traversal, so
        // greater and lesser with respect to the link are
        // reversed with respect to the ordering relation.
        // The lesser member is the upper member.

        up_itr.erase_cover();
      }
      else
      {
        // The upper member of the link still exists.

        if(lin_other_down_set[up_itr.lesser_index().pod()])
        {
          // The lower member is in the other down set if
          // any member of its upper cover is.

          lin_other_down_set.put(lindex.pod(), true);
        }

      }

      up_itr.next();
      break;

    case zn_to_bool_triorder_itr::POSTVISIT_ACTION:

      if(lhost->cover_is_empty(UPPER, lindex))
      {
        // The entire upper cover of the current member
        // has been deleted, so it must be an internal member.
        // If it is not the bottom, delete it.

        if(lindex != BOTTOM_INDEX)
        {
          lhost->delete_member(lindex);
        }
      }
      else if(lbdy_jims.contains_member(lindex) &&
              lin_other_down_set[lindex.pod()] &&
              ldown_set[lindex.pod()])
      {
        // This boundary jim is shared with another block
        // and hence is not external. We'll delete it,
        // but first we have to save its upper cover for
        // clean up later.

        index_space_iterator& uc_itr = _host->get_cover_id_space_iterator(UPPER, lindex);
        while(!uc_itr.is_done())
        {
          lclean_up_set.insert(uc_itr.hub_pod());

          // Note that remove_cover_member invalidates the itr
          // passed to it, but the postfix increment passes a copy of lc_itr.

          _host->remove_cover_member(uc_itr, UPPER, lindex);

	  uc_itr.next();
        }
	_host->release_cover_id_space_iterator(uc_itr);

        lhost->delete_member(lindex);
      }

      up_itr.next();
      break;
    }
  }

  lbdy_jims.detach_from_state();

  // Clean up the lower covers of the members
  // we have deleted boundary jims from.

  set<pod_index_type>::iterator cu_itr = lclean_up_set.begin();
  while(cu_itr != lclean_up_set.end())
  {
    index_space_iterator& lc_itr = _host->get_cover_id_space_iterator(LOWER, *cu_itr);
    while(!lc_itr.is_done())
    {
      if(!lhost->contains_member(lc_itr.hub_pod()))
      {
        // This member has been deleted, remove it from the lower cover.
        // Note tha remove_cover_member invalidates the iterator passed
        // to it, but the postfix increment operator passes a copy.

        _host->remove_cover_member(lc_itr, LOWER, *cu_itr);
      }

      lc_itr.next();
    }
    _host->release_cover_id_space_iterator(lc_itr);

    cu_itr++;
  }

  // Clean up this member itself.

  // We've removed the interior of this member.
  // There are two interpretations depending on whether
  // this member was ever a jim or not.

  if(is_jim(false))
  {
    // This member was originally a jim. Its interior
    // constitued a refinement and we've now unrefined it.
    // In order to maintain the semantics of this and its place in the
    // order relation, this must now go back to being a jim.

    lhost->jims().insert_member(this);
  }
  else if(lhost->cover_is_empty(LOWER, _index.pod()))
  {
    // This member was always a jrm, defined by the join
    // of its down set. The down set is now empty, so this
    // must be join-equivalent to the bottom.

    /// @hack just link it to the bottom.

    create_cover_link(&(lhost->bottom()));

    /// @error the order relation is now incorrect; this is now
    /// a jrm and an atom but is not linked as a jem of the bottom.
  }

  // Restore jim edit mode.

  if(!old_host_in_jim_edit_mode)
  {
    lhost->end_jim_edit_mode();
  }

  // Postconditions:

  define_old_variable(poset_state_handle* old_host = lhost);

  ensure(old_host->in_jim_edit_mode() == old_host_in_jim_edit_mode);

  // Exit:

  return;
}

int
sheaf::abstract_poset_member::
up_ct() const
{
  // Preconditions:

  // Body:

  int result = up_ct(WHOLE_INDEX);

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

int
sheaf::abstract_poset_member::
up_ct(pod_index_type xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  // Traverse up set, including top

  zn_to_bool_postorder_itr itr(*this, xfilter_index, sheaf::UP);
  while(!itr.is_done())
  {
    result++;
    itr.next();
  }

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

int
sheaf::abstract_poset_member::
up_ct(const scoped_index& xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = up_ct(xfilter_index.hub_pod());

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
sheaf::abstract_poset_member::
up() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host(), 0, false);
  up_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(up_pa));

  // Exit

  return result;
}


void
sheaf::abstract_poset_member::
up_pa(subposet* result) const
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

int
sheaf::abstract_poset_member::
jim_ct() const
{
  // Preconditions:

  // Body:

  zn_to_bool_postorder_itr itr(*this, host()->jims(), DOWN, NOT_STRICT);
  int result = itr.ct();

  // Postconditions:

  ensure(is_jem(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
sheaf::abstract_poset_member::
jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host(), 0, false);
  jims_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(jims_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
jims_pa(subposet* result)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Traverse down set, inserting jims into result

  poset_slicer slicer(_host);
  slicer.find_jims_pa(this, result);

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is jims set
                        of this));

  // Exit

  return;
}

int
sheaf::abstract_poset_member::
maximal_jim_ct() const
{
  int result = 0;

  // Preconditions:

  // Body:

  // Don't have an iterator for the maximal jims yet
  /// @hack implementation of abstract_poset_member::maximal_jim_ct is inefficient.
  /// @todo make more efficient implementation of abstract_poset_member::maximal_jim_ct().

  abstract_poset_member* cthis = const_cast<abstract_poset_member*>(this);
  subposet* lmax_jims = cthis->maximal_jims();
  result = lmax_jims->member_ct();
  delete lmax_jims;

  // Postconditions:

  ensure(is_jem(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}

// Issue is that this ultimately requires poset_slicer::find_pa() to be const
// yet this member sets attributes so it can't be const.

sheaf::subposet*
sheaf::abstract_poset_member::
maximal_jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host(), 0, false);
  maximal_jims_pa(result);

  // Postconditions:

  ensure(has_same_host(result));
  ensure(postcondition_of(maximal_jims_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
maximal_jims_pa(subposet* result) const
{

  // Preconditions:

  require(has_same_host(result));

  // Body:

  abstract_poset_member* cthis = const_cast<abstract_poset_member*>(this);

  if(is_jim())
  {
    // This member is a jim, hence it is the only
    // member of its set of maximal jims

    result->insert_member(cthis);
  }
  else
  {
    // Traverse down set, inserting maximal jims into result

    poset_slicer slicer(_host);
    slicer.find_jims_pa( cthis, result, poset_slicer::MAXIMAL );
  }

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is union of maximal_jims of this with old result));

  // Exit

  return;
}

int
sheaf::abstract_poset_member::
atom_ct() const
{
  int result = 0;

  // Preconditions:

  // Body:

  zn_to_bool_preorder_itr itr(*this, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    if(host()->is_atom(itr.index()))
    {
      result++;
      itr.truncate();
    }
    else
    {
      itr.next();
    }
  }

  // Postconditions:

  ensure(is_same_state(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
sheaf::abstract_poset_member::
atoms() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  result = new subposet(host(), 0, false);
  atoms_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(atoms_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
atoms_pa(subposet* result) const
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  zn_to_bool_preorder_itr itr(*this, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    if(host()->is_atom(itr.index()))
    {
      result->insert_member(itr.index());
      itr.truncate();
    }
    else
    {
      itr.next();
    }
  }

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable("for all members p of result: p.is_atom()"));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET ALGEBRA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
p_join(abstract_poset_member* other) const
{
  abstract_poset_member* result;

  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  result = clone();
  p_join_pa(other, result);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(p_join_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
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

  // if there is a unique minimal member of
  // the intersection of the up sets of this and other,
  // it is the p_join

  // get the up sets of this and other

  subposet tsp(host());
  up_pa(&tsp);

  subposet osp(host());
  other->up_pa(&osp);

  // intersect them

  tsp.p_intersection_sa(&osp);

  // find the minimal members of the intersection

  osp.make_empty();
  tsp.minimals_pa(&osp);

  subposet_member_iterator* itr = osp.member_iterator();
  if(!itr->is_done())
  {
    // at least one minimal member
    // assume it is unique and attach to it
    result->attach_to_state(host(), itr->index());
    // now lets see if it is unique
    itr->next();
    if(!itr->is_done())
    {
      // found a second minimal member
      // p_join does not exist
      result->detach_from_state();
    };
  };

  delete itr;

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
p_join_sa(abstract_poset_member* other)
{
  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  p_join_pa(other, this);

  // Postconditions:

  ensure(postcondition_of(p_join_pa));

  // Exit

  return;
}

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
p_meet(abstract_poset_member* other)
{
  abstract_poset_member* result;

  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  result = clone();
  p_meet_pa(other, result);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(p_meet_pa));


  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
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

  // if there is a unique maximal member of
  // the intersection of the down sets of this and other,
  // it is the p_meet

  // get the down sets of this and other

  subposet tds(host());
  down_pa(&tds);

  subposet ods(host());
  other->down_pa(&ods);

  // intersect them

  tds.p_intersection_sa(&ods);

  // find the maximal members of the intersection

  ods.make_empty();
  tds.maximals_pa(&ods);

  subposet_member_iterator* itr = ods.member_iterator();
  if(!itr->is_done())
  {
    // at least one minimal member
    // assume it is unique and attach to it
    result->attach_to_state(host(), itr->index());
    // now lets see if it is unique
    itr->next();
    if(!itr->is_done())
    {
      // found a second minimal member
      // p_meet does not exist
      result->detach_from_state();
    };
  };
  delete itr;

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
p_meet_sa(abstract_poset_member* other)
{
  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  p_meet_pa(other, this);

  // Postconditions:

  ensure(postcondition_of(p_meet_pa));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// LATTICE ALGEBRA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
l_join(abstract_poset_member* other, bool xnew_jem)
{
  abstract_poset_member* result;

  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  result = clone();
  l_join_pa(other, result, xnew_jem);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(l_join_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
l_join_pa(abstract_poset_member* other, abstract_poset_member* result, bool xnew_jem)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(!host()->in_jim_edit_mode());
  require(has_same_host(other));
  require(result->is_ancestor_of(this));

  // Body:

  scoped_index larray[2] = {_index, other->index()};

  /// @hack join operator should support tern argument.
  /// @todo convert xnew_jem to tern.

  result->new_jrm_state(_host, larray, 2, (xnew_jem ? tern::TRUE : tern::NEITHER));

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
l_join_sa(abstract_poset_member* other, bool xgreatest)
{
  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  l_join_pa(other, this, xgreatest);

  // Postconditions:

  ensure(postcondition_of(l_join_pa));

  // Exit

  return;
}

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
l_meet(abstract_poset_member* other, bool xnew_jem)
{
  abstract_poset_member* result;

  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  result = clone();
  l_meet_pa(other, result, xnew_jem);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(l_meet_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
l_meet_pa(abstract_poset_member* other, abstract_poset_member* result, bool xnew_jem)
{
  // Preconditions:

  require(has_same_host(other));
  require(!result->is_attached());
  // this precondition ensures the attachment below will not
  // leave an orphan temporary in the poset
  require(result->is_ancestor_of(this));
  require(state_is_read_accessible());

  // Body:

  // Birkhoff representation theorem states that any jrm is equal to
  // the l_join of the jims contained in it.
  // The jims of c = a l_meet b are defined by:
  // J(c) = J(a) intersection J(b)
  // so we have:
  // c = l_join( J(a) intersection J(b) )

  // get the jim sets of this and other

  subposet jthis(host());
  jims_pa(&jthis);

  subposet jother(other->host());
  other->jims_pa(&jother);

  // intersect them

  jthis.p_intersection_sa(&jother);

  // join them

  jthis.l_join_jims_pa(result, xnew_jem);

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
l_meet_sa(abstract_poset_member* other, bool xnew_jem)
{
  // Preconditions:

  require(has_same_host(other));
  require(state_is_read_accessible());

  // Body:

  l_meet_pa(other, this, xnew_jem);

  // Postconditions:

  ensure(postcondition_of(l_meet_pa));

  // Exit

  return;
}

sheaf::abstract_poset_member*
sheaf::abstract_poset_member::
l_not(bool xnew_jem) const
{
  abstract_poset_member* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = clone();
  l_not_pa(result, xnew_jem);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(l_not_pa));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
l_not_pa(abstract_poset_member* result, bool xnew_jem) const
{
  // Preconditions:

  require(!result->is_attached());
  // this precondition ensures the attachment below will not
  // leave an orphan temporary in the poset
  require(result->is_ancestor_of(this));
  require(state_is_read_accessible());

  // Body:

  // Birkhoff representation theorem states that any jrm is equal to
  // the l_join of the jims contained in it. Let J(p) denote the jims in p.
  // The jims of a* = a.l_not() are defined by:
  // J(a*) = J(host) - (up set of J(a)), where the up set is computed
  // w.r.t. the poset J(host) not the lattice for which J is the set of jims.
  // So we have:
  // a* = l_join( J(host) - (up set in J(host) of J(a)) )
  // See exercise 8.22 in Davey and Priestley


  /// @todo reimplement abstract_poset_member::l_not_pa using poset_slicer

  not_implemented();

  // get J(a), the jim set of this

  subposet tsp1(host());
  abstract_poset_member* cthis = const_cast<abstract_poset_member*>(this);
  cthis->jims_pa(&tsp1);

  // intersect the up set of J(a) in host with J(host)
  // to get the up set in the set of jims

  poset_slicer slicer(host());
  subposet tsp2(host());
  slicer.find_pa(&tsp1, &(host()->jims()), false, &tsp2);

  // compute all jims - up set of jims in this

  host()->jims().p_minus_pa(&tsp2, &tsp1);

  // join the difference

  tsp1.l_join_jims_pa(result, xnew_jem);

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
l_not_sa(bool xnew_jem) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  abstract_poset_member* cthis = const_cast<abstract_poset_member*>(this);
  l_not_pa(cthis, xnew_jem);

  // Postconditions:

  ensure(postcondition_of(l_not_pa));

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
sheaf::abstract_poset_member::
is_valid_index(const poset_state_handle* xhost, pod_index_type xhub_id, int xversion) const
{
  bool result;

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(host_is_ancestor_of(xhost));

  // Body:

  result = xhost->contains_member(xhub_id, xversion, false);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
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

const sheaf::index_space_family&
sheaf::abstract_poset_member::
id_spaces() const
{
  // Precondtions:

  require(state_is_read_accessible());

  // Body:

  const index_space_family& result = _host->member_id_spaces(false);

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::abstract_poset_member::
hub_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const hub_index_space_handle& result = _host->member_hub_id_space(false);

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::scoped_index&
sheaf::abstract_poset_member::
hub_id() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const scoped_index& result = _host->member_id(false);

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::abstract_poset_member::
hub_id(pod_index_type xid) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result = _host->member_id(xid, false);

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::abstract_poset_member::
get_index_from_name(const poset_state_handle* xhost, const string& xname) const
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  pod_index_type result = xhost->member_id(xname, false);

  // Postconditions:

  ensure(unexecutable(result.is_valid() implies member with index = result has name xname));

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
get_index_from_name(const poset_state_handle* xhost, const string& xname,
		    scoped_index& result) const
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  xhost->member_id(xname, result, false);

  // Postconditions:

  ensure(unexecutable(result.is_valid() implies member with index = result has name xname));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

string
sheaf::abstract_poset_member::
name(bool xauto_access) const
{
  string result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = host()->member_name(index(), xauto_access);

  // Postconditions:

  ensure(unexecutable(result.empty() implies this has no name));

  // Exit:

  return result;
}

void
sheaf::abstract_poset_member::
all_names(block<string>& xresult, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  host()->all_member_names(_index.pod(), xresult, xauto_access);

  // Postconditions:

  ensure(xresult.ct() == name_ct(xauto_access));
  ensure_for_all(i, 0, xresult.ct(), !xresult[i].empty());

  // Exit:

  return;
}

sheaf::size_type
sheaf::abstract_poset_member::
name_ct(bool xauto_access) const
{
  size_type result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = host()->member_name_ct(index(), xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::abstract_poset_member::
has_name(const string& xname, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!xname.empty());

  // Body:

  bool result = host()->member_has_name(_index.pod(), xname, xauto_access);

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::abstract_poset_member::
put_name(const string& xname, bool xunique, bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));

  // Body:

  host()->put_member_name(index(), xname, xunique, xauto_access);

  // Postconditions:

  //  ensure(invariant()); // requires access.
  ensure(xunique ? (name(xauto_access) == xname) : has_name(xname, xauto_access));

  // Exit

  return;
}

void
sheaf::abstract_poset_member::
delete_name(const string& xname, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(!xname.empty());

  // Body:

  // poset_state_handle::delete_member_name will delete the name
  // whatever member it belongs to. Not what we want here.
  // Only delete the name is it belongs to this.

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  if(has_name(xname, false))
  {
    host()->delete_member_name(xname, false);
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
sheaf::abstract_poset_member::
delete_all_names(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());

  // Body:

  host()->delete_all_member_names(_index.pod(), xauto_access);

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
sheaf::abstract_poset_member::
attach_to_state(const namespace_poset* xns,
                const poset_path& xpath,
                bool xauto_access)
{

  // Preconditions:

  require(xns != 0);
  require(xauto_access || xns->state_is_read_accessible());
  require(xpath.full());
  require(xauto_access || xns->member_poset(xpath).state_is_read_accessible());
  require(xns->contains_poset_member(xpath));

  /// @todo add precondition to require conformance between this and host.

  // Body:

  if(xauto_access)
  {
    xns->get_read_access();
  }

  poset_state_handle& lposet = xns->member_poset(xpath, false);

  if(xauto_access)
  {
    lposet.get_read_access();
  }

  attach_to_state(&lposet, xpath.member_name());

  // Postconditions:

  ensure(invariant());
  ensure(name_space()->is_same_state(xns));
  ensure(has_path(xpath, xauto_access));
  ensure(postcondition_of(attach_handle_data_members()));

  if(xauto_access)
  {
    lposet.release_access();
    xns->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
attach_to_state(const namespace_poset* xnamespace,
                pod_index_type xposet_index,
                pod_index_type xmember_index,
                bool xauto_access)
{

  // Preconditions:

  require(xnamespace != 0);
  require(!xauto_access ? xnamespace->state_is_read_accessible() : true);

  if(xauto_access)
  {
    xnamespace->get_read_access();
  }

  require(xnamespace->contains_poset_member(xposet_index, xmember_index));

  /// @todo add precondition to require conformance between this and host.

  // Body:

  poset_state_handle& lposet = xnamespace->member_poset(xposet_index);

  lposet.get_read_access();

  attach_to_state(&lposet, xmember_index);

  // Postconditions:

  ensure(invariant());
  ensure(name_space()->is_same_state(xnamespace));
  ensure(host()->index() == xposet_index);
  ensure(index() == xmember_index);
  ensure(postcondition_of(attach_handle_data_members()));

  lposet.release_access();

  if(xauto_access)
  {
    xnamespace->release_access();
  }

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
attach_to_state(const namespace_poset* xnamespace,
                const scoped_index& xposet_index,
                const scoped_index& xmember_index,
                bool xauto_access)
{

  // Preconditions:

  require(xnamespace != 0);
  require(!xauto_access ? xnamespace->state_is_read_accessible() : true);
  require(xnamespace->contains_poset_member(xposet_index, xmember_index, xauto_access));

  // Body:

  attach_to_state(xnamespace,
		  xposet_index.hub_pod(),
		  xmember_index.hub_pod(),
		  xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(name_space()->is_same_state(xnamespace));
  ensure(host()->index() ==~ xposet_index);
  ensure(index() ==~ xmember_index);
  ensure(postcondition_of(attach_handle_data_members()));

  // Exit:

  return;
}

void
sheaf::abstract_poset_member::
delete_state(bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xauto_access ||
          (is_jim() ? host()->in_jim_edit_mode() : state_is_read_write_accessible()));

  /// @todo should not be able to delete a
  /// standard member unless called from destructor

  // Body:

  bool lis_jim = is_jim();
  poset_state_handle* lhost = _host;

  if(xauto_access)
  {
    if(lis_jim)
    {
      lhost->begin_jim_edit_mode(true);
    }
    else
    {
      get_read_write_access(true);
    }
  }

  // Note: deleting a jim redefines the order relation. It is up to
  // the client to relink the remaining jims as desired. Deleting a
  // jrm however should leave the order relation for the remaining
  // members invariant. Hence, for a jim we just remove its links,
  // while for a jrm, we patch things up to maintain the order relation.

  // Whether it's a jim or a jrm, we remove the links to the member.

  index_space_iterator& lc_itr = lhost->get_cover_id_space_iterator(LOWER, _index.pod());
  index_space_iterator& uc_itr = lhost->get_cover_id_space_iterator(UPPER, _index.pod());

  // Remove this from the lower cover of its upper cover.

  while(!uc_itr.is_done())
  {
    lhost->remove_cover_member(_index.pod(), LOWER, uc_itr.hub_pod());
    uc_itr.next();
  }

  // Remove this from the upper cover of its lower cover.

  while(!lc_itr.is_done())
  {
    lhost->remove_cover_member(_index.pod(), UPPER, lc_itr.hub_pod());
    lc_itr.next();
  }

  if(!is_jim())
  {
    // Deleting a jrm;
    // ensure the order relation will remain invariant
    // after deleting state.

    // Link the the upper cover of this to the lower cover of this.

    uc_itr.reset();
    while(!uc_itr.is_done())
    {
      lc_itr.reset();
      while(!lc_itr.is_done())
      {
        if(!lhost->le(uc_itr.hub_pod(), lc_itr.hub_pod()) &&
            !lhost->le(lc_itr.hub_pod(), uc_itr.hub_pod()))
        {
          lhost->new_link(uc_itr.hub_pod(), lc_itr.hub_pod());
        }
        lc_itr.next();
      }
      uc_itr.next();
    }
  }

  // Release the cover iterators.

  _host->release_cover_id_space_iterator(lc_itr);
  _host->release_cover_id_space_iterator(uc_itr);

  // Clear the upper and lower cover of this.

  lhost->clear_cover(LOWER, _index.pod());
  lhost->clear_cover(UPPER, _index.pod());

  // Now just detach and delete the state.

  pod_index_type lindex = _index;
  detach_from_state();
  lhost->delete_member(lindex);

  if(xauto_access)
  {
    if(lis_jim)
    {
      lhost->end_jim_edit_mode(true, true);
    }
    else
    {
      lhost->release_access();
    }
  }

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable("!old host()->contains_member(old index())"));

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
sheaf::abstract_poset_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const abstract_poset_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::abstract_poset_member::
invariant() const
{
  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(poset_component::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    // Actual dof map conforms to type needed by this class.
    /// @hack assertion should be true with or without read access, but
    /// dof_map requires read access and this doesn't have it in bootstrap.
    /// @todo change read_write_monitor ctor to grant access by default.

    invariance(state_is_read_accessible() && is_jim(false) ? dof_map_is_ancestor_of(&(dof_map())) : true);

    /// @issue what are the other invariants for this class
    /// @todo finish implementing abstract_poset_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::abstract_poset_member::
to_stream(ostream& xos) const
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
// NON-MEMBER FUNCTIONS FACET
// ===========================================================
 
ostream & 
sheaf::
operator<<(ostream &os, const abstract_poset_member& p)
{

  // Preconditions:

  // Body:

  if (p.is_attached())
  {
    p.get_read_access();
    p.disable_invariant_check();
    os << "member:"
    << " host = \'" << p.host()->name() << "\'"
    << " index = " << p.index().hub_pod()
    << " name = \'" << p.name() << '\''
    << " version= " << p.version(false)
    << " unaliased version= " << p.version()
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

ostream & 
sheaf::
operator<<(ostream &os, const abstract_poset_member* p)
{
  // Preconditions:

  require(p != 0);

  // Body:

  /// @hack when we've found the calls to this routine, remove it.

  post_fatal_error_message("change this call to use operator<<(ostream& abstract_poset_member&)");

  //  os << *p;

  // Exit:

  return os;
}
