
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
/// Implementation for class poset_state_handle.

#include "SheafSystem/poset_state_handle.h"

#include "SheafSystem/array_index_space_state.h"
#include "SheafSystem/array_poset_dof_map.h"
#include "SheafSystem/factory.h"
#include "SheafSystem/index_equivalence_iterator.h"
#include "SheafSystem/index_space_interval.h"
#include "SheafSystem/explicit_index_space_state.h"
#include "SheafSystem/implicit_crg_interval.h"
class index_iterator;
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/namespace_poset.impl.h"
#include "SheafSystem/namespace_poset_member.h"
#include "SheafSystem/poset_bounds.h"
#include "SheafSystem/poset_crg_state.h"
#include "SheafSystem/poset_dof_map.h"
#include "SheafSystem/poset_handle_factory.h"
#include "SheafSystem/poset_member.h"
#include "SheafSystem/poset_member_iterator.h"
#include "SheafSystem/poset_dof_iterator.h"
#include "SheafSystem/poset_orderer.h"
#include "SheafSystem/poset_powerset_state.h"
#include "SheafSystem/poset_slicer.h"
#include "SheafSystem/poset_type.h"
#include "SheafSystem/postorder_member_iterator.h"
#include "SheafSystem/preorder_member_iterator.h"
#include "SheafSystem/primitives_poset.h"
#include "SheafSystem/primitives_poset_schema.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_cstdlib.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/subposet.h"
#include "SheafSystem/subposet_state.h"
#include "SheafSystem/subposet_member_iterator.h"
#include "SheafSystem/zn_to_bool.h"

using namespace std;

// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

// PUBLIC FUNCTIONS


sheaf::poset_state_handle*
sheaf::poset_state_handle::
new_poset_handle(const std::string& xclass_name,
                 poset_type xsheaf_base_class_id)
{
  poset_state_handle* result;

  // Preconditions:

  // Body:

  result = factory().new_poset_handle(xclass_name, xsheaf_base_class_id);

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

sheaf::poset_handle_factory&
sheaf::poset_state_handle::
factory()
{
  // Preconditions:

  // Body:

  static poset_handle_factory result;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_state_handle::
poset_state_handle()
{
  _name_space = 0;
  _state = 0;
  _top = new total_poset_member;
  _bottom = new total_poset_member;

}

sheaf::poset_state_handle::
~poset_state_handle()
{
  // Preconditions:

  require(!is_attached());

  // Body:

  delete _top;
  delete _bottom;

  // Postconditions:

  // Exit

  return;
}

sheaf::poset_state_handle::
poset_state_handle(abstract_poset_member* xtop, abstract_poset_member* xbottom)
{
  // Preconditions:

  require(xtop != 0);
  require(!xtop->is_attached());
  require(xbottom != 0);
  require(!xbottom->is_attached());

  // Body:

  _name_space = 0;
  _state = 0;
  _top = xtop;
  _bottom = xbottom;

  // Postconditions:

  ensure(!is_attached());
  ensure(&(top()) == xtop);
  ensure(&(bottom()) == xbottom);
  ensure(!top().is_attached());
  ensure(!bottom().is_attached());

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
sheaf::poset_state_handle::
type_id() const
{
  poset_type result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = state_obj()->type_id();

  // Postconditions:

  // Exit

  return result;
}

const char*
sheaf::poset_state_handle::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "poset_state_handle";

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
is_external() const
{
  bool result;

  // Preconditions:

  // Body:

  result = !is_attached() &&
           (name_space() != 0) &&
           (index().is_valid());

  // Postconditions:

  ensure(result ? !is_attached() : true);
  ensure(result ? name_space() != 0 : true);
  ensure(result ? index().is_valid() : true);

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
begin_jim_edit_mode(bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? state_is_read_write_accessible() : true);

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);

    // Matching release access is in end_jim_edit_mode.
  }

  define_old_variable(int old_jim_edit_depth = crg().jim_edit_depth());

  crg().request_jim_edit_mode();

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(in_jim_edit_mode());
  ensure(jim_edit_depth(false) == old_jim_edit_depth + 1);

  // Exit

  return;
}

void
sheaf::poset_state_handle::
end_jim_edit_mode(bool xensure_lattice_invariant,
                  bool xauto_access)
{
  // Preconditions:

  require(in_jim_edit_mode());
  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_jim_edit_depth = crg().jim_edit_depth());

  crg().release_jim_edit_mode();

  // If we've fully released jim edit mode and the client requested it,
  // re-establish the order relation and lattice invariants

  /// @hack ensure_lattice_invariant should be converted to a combination
  /// of client callable routines and pre/postconditions. Then
  /// xensure_lattice_invariant should be removed.

  if(xensure_lattice_invariant && !crg().jim_edit_mode())
  {
    ensure_lattice_invariant();
  }

  if(xauto_access)
  {
    // Matching get access is in begin_jim_edit_mode().

    release_access();
  }

  // Postconditions:

  ensure(jim_edit_depth(xauto_access) == old_jim_edit_depth - 1);

  // Exit

  return;
}

bool
sheaf::poset_state_handle::
in_jim_edit_mode() const
{
  bool result;

  // Preconditions:

  // Body:

  result = state_is_read_write_accessible() && crg().jim_edit_mode();

  // Postconditions:

  ensure(result ? state_is_read_write_accessible() : true);

  // Exit:

  return result;
}

int
sheaf::poset_state_handle::
jim_edit_depth(bool xauto_access) const
{
  int result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = crg().jim_edit_depth();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

void
sheaf::poset_state_handle::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  int old_access_request_depth = access_request_depth();

  read_write_monitor_handle::get_read_access();
  schema().get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() > old_access_request_depth);

  // Exit

  return;
}

void
sheaf::poset_state_handle::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);

  // Body:

  int old_access_request_depth = access_request_depth();

  read_write_monitor_handle::get_read_write_access(xrelease_read_only_access);
  schema().get_read_access();

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() > old_access_request_depth);

  // Exit

  return;
}

void
sheaf::poset_state_handle::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = access_request_depth();

  // Release at least one level of access for this..
  // If xall, release all levels of access for this.
  // Since each level of access to this also
  // acquired a level of access to the schema,
  // release the same number of levels of access to the schema.
  // Note that this may not be all the levels of access of the schema.

  do
  {
    // Release one level of access.

    schema().release_access(false);
    read_write_monitor_handle::release_access(false);
  }
  while(xall && state_is_read_accessible());


  // Postconditions:

  ensure(xall ?
	 access_request_depth() == 0 :
	 access_request_depth() < old_access_request_depth);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);

  // Exit

  return;
}

bool
sheaf::poset_state_handle::
is_attached() const
{
  bool result;

  // Preconditions:

  // Body:

  /// @issue this implementation appears to be identical to
  /// the inherited version and hence is apparently unnecessary.

  result = (state_obj() != 0);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_same_state(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (state_obj() == xother->state_obj());

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

sheaf::poset_state*
sheaf::poset_state_handle::
state_obj() const
{
  poset_state* result;

  // Preconditions:

  // Body:

  result = _state;

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
attach_to_state(const poset_state_handle* xother)
{
  // Preconditions:

  require(xother != 0);
  require(xother->state_is_read_accessible());

  /// @issue how do we require that the state of other conforms to
  /// the state required by this, especially in descendants,
  /// e.g. namespace_poset.

  // Body:

  _name_space = xother->name_space();
  _index = xother->index();
  _state = xother->state_obj();

  attach_handle_data_members();

  // Postconditions:

  ensure(poset_state_handle::invariant());
  ensure(is_attached());
  ensure(host() == xother->host());
  ensure(index() == xother->index());

  return;
}


void
sheaf::poset_state_handle::
attach_to_state(const namespace_poset* xhost, pod_index_type xindex)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex, false));

  // Body:

  // Create a handle to the xindex  member of the namespace

  total_poset_member mbr(xhost, xindex);

  attach_to_state(&mbr);

  // We're finished with member,
  // detach it so the state won't be deleted.

  mbr.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state(abstract_poset_member*)));

  return;
}

void
sheaf::poset_state_handle::
attach_to_state(const namespace_poset* xhost, const scoped_index& xindex)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex, false));

  // Body:

  attach_to_state(xhost, xindex.hub_pod());

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state(abstract_poset_member*)));

  return;
}

void
sheaf::poset_state_handle::
attach_to_state(const namespace_poset* xhost, const std::string& xname)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xname, false));
  /// @todo require that xname refers to a jim

  // Body:

  // Create a handle to the xindex  member of the namespace

  namespace_poset_member mbr(xhost, xname);

  attach_to_state(&mbr);

  // We're finished with member,
  // detach it so the state won't be deleted.

  mbr.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_to_state(abstract_poset_member*)));

  return;
}

void
sheaf::poset_state_handle::
attach_to_state(const abstract_poset_member* xmbr)
{
  // Preconditions:

  /// @error argument should be a namespace_poset_member

  require(xmbr != 0);
  require(dynamic_cast<namespace_poset*>(xmbr->host()) != 0);
  require(xmbr->state_is_read_accessible());
  require(xmbr->is_jim());
  /// @todo make arg namespace_poset_member, then make the following executable.
  require(unexecutable(xmbr->poset_pointer() == 0 ? xmbr->state_is_read_write_accessible() : true));


  // Body:

  _name_space = dynamic_cast<namespace_poset*>(xmbr->host());
  _index = xmbr->index();

  // $$CONST need to try and remove the const_cast here. The dynamic_cast stays.
  namespace_poset_dof_map& ldof_map = dynamic_cast<namespace_poset_dof_map&>(const_cast<abstract_poset_member*>(xmbr)->dof_map(false));
  poset_state_handle* handle_ptr = ldof_map.poset_pointer();

  if(handle_ptr != 0)
  {
    // Make this a handle for the same state; may be external.

    _state = handle_ptr->state_obj();
  }
  else
  {
    // Make this a handle for an external state;
    // requires write access to dof tuple.

    _state = 0;
    ldof_map.put_poset_pointer(this);
    // ldof_map.put_poset_type_id(type_id());
    /// @error doesn't have a type_id yet; type_id is feature of state.
    /// @issue should haandles have type_ids?
  }

  int old_access_request_depth = 0;
  if(is_attached())
  {
    // State is not external; initialize the
    // handle data members to values from the state.
    // Requires read access.

    old_access_request_depth = access_request_depth();
    poset_state_handle::get_read_access();

    attach_handle_data_members();
  }

  // Postconditions:

  ensure(poset_state_handle::invariant());
  ensure(host() == xmbr->host());
  ensure(index() == xmbr->index());
  ensure(!is_external() ? is_attached() : true);

  // Release access to poset state.

  if(is_attached()) poset_state_handle::release_access();

  // Ensure we left it in the access state we found it in.

  ensure(is_attached() ? access_request_depth() == old_access_request_depth : true);

  return;
}

void
sheaf::poset_state_handle::
detach_from_state()
{

  // Preconditions:

  // Body:

  // Detach standard subposets.

  resident().detach_from_state();

  // Detach standard members.

  top().detach_from_state();
  bottom().detach_from_state();

  // Detach from the name space.

  _name_space = 0;
  _index.invalidate();

  // Detach from the state itself.

  _state      = 0;

  // Postconditions:

  ensure(!is_attached());
  ensure(!is_external());

  // Exit

  return;
}

// void
// sheaf::poset_state_handle::
// delete_state(bool xauto_access)
// {

//   // Preconditions:

//   require(is_attached());
//   require(xauto_access || state_is_read_write_accessible());
//   require(xauto_access || (name_space() == 0) || name_space()->in_jim_edit_mode());

//   // Body:

//   namespace_poset* lns = name_space();

//   if(xauto_access)
//   {
//     get_read_write_access(true);
//   }

//   // Detach from and delete the state.

//   scoped_index lindex = _index;
//   terminate_access();

//   if(lns != 0)
//   {
//     // This is in a namespace; get access to it.

//     if(xauto_access)
//     {
//       lns->begin_jim_edit_mode(true);
//     }

//     // Detach the handle held by the namespace member;
//     // may be this, but another detach won't hurt.

//     lns->member_poset(lindex, false)->detach_from_state();

//     // Clean up the member dof tuple.

//     namespace_poset_member lns_mbr(lns, lindex);
//     lns_mbr.put_poset_pointer(0);
//     lns_mbr.put_poset_type_id(NOT_A_POSET_TYPE);
//     lns_mbr.put_poset_class("");

//     // Delete the member.

//     lns_mbr.delete_state(false);

//     if(xauto_access)
//     {
//       lns->end_jim_edit_mode(true, true);
//     }
//   }

//   // Postconditions:

//   ensure(!is_attached());

//   // Exit

//   return;
// }

void
sheaf::poset_state_handle::
new_state(namespace_poset& xns, const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{
  // cout << endl << "Entering poset_state_handle::new_state." << endl;

  // Preconditions:

  require(!xpath.empty());
  require(!xns.contains_poset(xpath, true));

  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());
  require(xschema.host()->name_space()->is_same_state(&xns));

  // Body:

  // Create the state.

  new_state(xpath, xschema, xdof_map);
  
  // Insert it in the namespace.

  initialize_namespace(xns, xpath.poset_name(), true);

  // Postconditions:

  ensure(is_attached());
  ensure(path(true).poset_name() == xpath.poset_name());
  ensure(schema(true).is_same_state(&xschema));

  get_read_access();
  ensure(&table_dof_map(false) == &xdof_map);
  release_access();


  // Exit:

  // cout << "Leaving poset_state_handle::new_state." << endl;
  return;
}


void
sheaf::poset_state_handle::
new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{
  // cout << endl << "Entering poset_state_handle::new_state." << endl;

  // Preconditions:

  require(!xpath.empty());
  require(!xpath.full());

  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable(xschema.is_same_state(xdof_map.schema())));

  // Body:

  is_abstract();
  
  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(schema().is_same_state(&xschema));
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(version() == COARSEST_COMMON_REFINEMENT_VERSION);

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  // cout << "Leaving poset_state_handle::new_state." << endl;
  return;
}

void
sheaf::poset_state_handle::
initialize_handle_data_members(const namespace_poset& xns)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(unexecutable("table dof tuple is valid"));

  // Body:

  // Initialize and attach those handle data members that
  // are required by the access control routines; especially
  // those that depend on the table dofs.

  // Does nothing in the class;
  // intended to be redefined in descendants.

  // Postconditions:


  // Exit

  return;
}

void
sheaf::poset_state_handle::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  /// @hack Invariant requires all three entities below to be attached,
  /// but invariant gets called within scope of attach_to_state,
  /// so have to disable the invariant.

  disable_invariant_check();

  // Attach the handles for the standard subposets

  resident().attach_to_state(this, RESIDENT_INDEX);

  // Attach the handles for the standard members

  bottom().attach_to_state(this, BOTTOM_INDEX);
  top().attach_to_state(this, TOP_INDEX);

  enable_invariant_check();

  // Postconditions:

  ensure(bottom().is_attached());
  ensure(top().is_attached());
  ensure(jims().is_attached());
  ensure(whole().is_attached());
  ensure(resident().is_attached());

  // Exit

  return;
}

void
sheaf::poset_state_handle::
ensure_lattice_invariant()
{

  // Preconditions:

  // Body:

  // Ensure for all members m: bottom <= m <= top.

  // Get an iterator for all the members.

  index_iterator itr = whole().indexed_member_iterator();

  // Skip by the bottom and top.
  /// @issue Depends on bottom is index 0 and top is index 1.

  itr.next();
  itr.next();

  if(!itr.is_done())
  {
    // The poset is not empty (contains more than just top and bottom).
    // We'll need the least join equivalement member of the top
    // and the greatest join equivalent member of the bottom.

    pod_index_type least_top_jem = least_jem(TOP_INDEX);
    pod_index_type greatest_bottom_jem = greatest_jem(BOTTOM_INDEX);

    // Find all unlinked members and link them up.

    /// @issue this algorithm does not make top cover bottom in empty poset.
    /// The mathematical meaning is unclear, but it seems to work just fine.

    while(!itr.is_done())
    {
      pod_index_type lindex = itr.index().hub_pod();

      if(cover_is_empty(UPPER, lindex))
      {
        // Member is topless, link to to top.

        new_link(TOP_INDEX, lindex);
      }

      if(cover_is_empty(LOWER, lindex))
      {
        // Member is bottomless, link it to
        // least_bottom_jem

        /// @error this action is only correct if lindex is a jim.
        /// Otherwise, lindex should become the greatest bottom jem.

        new_link(lindex, greatest_bottom_jem);
      }
      itr.next();
    }

    // Ensure the order relation.

    poset_orderer orderer(this);
    orderer.restore_order();
  }

  // Postconditions:

  ensure( top().is_attached() );
  ensure(unexecutable(only top has no upper cover));
  ensure(unexecutable(order relation is well defined));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
terminate_access()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_schema_access_request_depth = schema().access_request_depth());
  int old_access_request_depth = access_request_depth();

#ifdef DIAGNOSTIC_OUTPUT
  cout << "poset: " << name()
       << "  old level:" << old_access_request_depth
       << "  schema: " << schema().name();
#endif


  // Release all levels of access this poset has to its schema,
  // but do not release access to the state of this because
  // we are going to delete the state and don't want another
  // client able to sneak in and get access before we do.

  /// @issue we should either prevent termination if other clients
  /// exist or have some mechanism for notifying them of termination.
  /// Currently we can't do either one.

  for(size_type i=0; i<old_access_request_depth; ++i)
  {
    schema().release_access(false);
  }

  define_old_variable(int schema_access_request_depth = schema().access_request_depth());

#ifdef DIAGNOSTIC_OUTPUT
  cout << "  old level:" << old_schema_access_request_depth
       << "  level: " << schema_access_request_depth
       << endl;
#endif

  // Detach and delete the state.

  poset_state* lstate = _state;
  detach_from_state();
  delete lstate;

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable("state has been deleted"));
  ensure(schema_access_request_depth == (old_schema_access_request_depth - old_access_request_depth));

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// GLOBAL ATTRIBUTES FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::namespace_poset*
sheaf::poset_state_handle::
host() const
{
  return name_space();
}

sheaf::namespace_poset*
sheaf::poset_state_handle::
name_space() const
{
  return _name_space;
}

const sheaf::scoped_index&
sheaf::poset_state_handle::
index() const
{
  // Preconditions:

  // Body:

  define_old_variable(const scoped_index& result = _index);

  // Postconditions:

  ensure(result.is_hub_scope() || !result.is_valid());
  ensure(result.is_positive() || !result.is_valid());

  // Exit

  return _index;
}

const sheaf::primitives_poset&
sheaf::poset_state_handle::
primitives() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  primitives_poset& result = host()->primitives();

  // Postconditions:
             
  // Exit

  return result;
}

std::string
sheaf::poset_state_handle::
name() const
{
  string result;

  // Preconditions:

  require(is_external() ? name_space()->state_is_read_accessible() : state_is_read_accessible());

  // Body:

  if(is_external())
  {
    // Poset has no state yet, but nme is
    // same as name of associated member in name space.

    result = name_space()->member_name(index(), false);
  }
  else
  {
    // Retrieve the name from the state.

    //    result = subposet_name(WHOLE_INDEX);
    result = _state->name();
  }

  // Postconditions:

  // Exit

  return result;
}

std::string
sheaf::poset_state_handle::
name(bool xauto_access) const
{
  string result;

  // Preconditions:

  require(is_external() ? 
   	  name_space()->state_is_auto_read_accessible(xauto_access) : 
   	  state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    is_external() ? name_space()->get_read_access() : get_read_access();
  }

  result = name();

  if(xauto_access)
  {
    is_external() ? name_space()->release_access() : release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_path
sheaf::poset_state_handle::
path(bool xauto_access) const
{

  // Preconditions:

  require(is_external() ? 
   	  name_space()->state_is_auto_read_accessible(xauto_access) : 
   	  state_is_auto_read_accessible(xauto_access));

  // Body:

  poset_path result(name(xauto_access));

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

void
sheaf::poset_state_handle::
initialize_namespace(namespace_poset& xns, const std::string& xposet_name, bool xauto_link)
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @hack previously insert_poset called from this routine entered and exited jim_edit_mode
  /// without exporting any precondition. As a result, numerous new_state
  /// routines do not properly provide access before calling this routine.
  /// Continue the old practice until we get a chance to clean the mess up.


  //   require(xns.contains_member(name()) ?
  //           xns.state_is_read_write_accessible() :
  //           xns.in_jim_edit_mode());

  require(xns.state_is_read_write_accessible());

  // Body:

  // Insert this into the namespace and
  // set the namespace and index features.

  disable_invariant_check();

  _name_space = &xns;
  _index = xns.insert_poset(*this, xposet_name, xauto_link, true);

  enable_invariant_check();

  // Postconditions:

  ensure(name_space() == &xns);
  ensure(name_space()->contains_member(index(), false));
  ensure(&name_space()->member_poset(index()) == this);

  // Exit

  return;
}

// PRIVATE FUNCTIONS

// ===========================================================
// POSET ALGEBRA FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC FUNCTIONS


sheaf::pod_index_type
sheaf::poset_state_handle::
new_member(bool xis_jim, pod_index_type xtuple_hub_id)
{
  // Preconditions:

  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require((!is_valid(xtuple_hub_id)) || contains_row_dof_tuple(xtuple_hub_id));

  // Body:

  // Member_ct and member_index_ub requires access to handle data mmembers in descendants,
  // which may no be attached yet. Also, see comment on postcondition.
  //  define_old_variable(const scoped_index& old_member_index_ub = crg().end());
  //  define_old_variable(int old_member_ct = member_ct());

  // Create new node in crg; ensures lower and upper covers empty.

  pod_index_type result = crg().new_member();

  // Set the dof tuple id for the member.

  crg().put_member_dof_tuple_id(result, xtuple_hub_id);

  // If node allocation has extended the member pool,
  // extend the subposet characteristic functions to match.

  if(crg().end() > powerset().subposet_member_index_ub())
  {
    powerset().put_subposet_member_index_ub(crg().end());
  }

  // Put new node in subposet of all members.

  powerset().whole().insert_member(result);

  // New members are not jims, not resident, and not modified by default.
  // Note that since resident and modified refers to the dof tuple,
  // and jrms don't have dof tuples, jrms should never be resident or modified.

  if(xis_jim)
  {
    // Put new member in subposet of all jims.

    jims().insert_member(result);
  }

  // Postconditions:

  ensure(invariant());
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // The following postconditions seems obvious, but it is not
  // true for immutable posets such as section_space_schema_poset.
  // ensure(member_ct() == (old_member_ct + 1));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
new_member(bool xis_jim, const scoped_index& xtuple_id, scoped_index& result)
{
  // Preconditions:

  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require(contains_row_dof_tuple(xtuple_id) || (!xtuple_id.is_valid()));

  // Body:

  result.put(member_hub_id_space(false), new_member(xis_jim, xtuple_id.hub_pod()));

  // Postconditions:

  ensure(invariant());
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // The following postconditions seems obvious, but it is not
  // true for immutable posets such as section_space_schema_poset.
  // ensure(member_ct() == (old_member_ct + 1));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
new_member(bool xis_jim, poset_dof_map* xdof_map, bool xcopy_dof_map)
{
  // Preconditions:

  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require(xdof_map != 0 ? xdof_map->host()->schema().is_same_state(&(schema())) : true);
  // schema is not attached yet when creating std members in namespace_poset, primitive_poset, etc.
  /// @todo propagate this precondition to poset_member constructors

  // Body:

  // Member_ct requires access to handle data mmembers in descendants,
  // which may no be attached yet. Also, see comment on postcondition.
  //  define_old_variable(int old_member_ct = member_ct());

  // Get a dof tuple id.

  scoped_index ldof_map_id;
  if(!xis_jim)
  {
    // This member is a jrm, does not have a dof map.

    ldof_map_id.invalidate();
    ldof_map_id.put_scope(dof_tuple_hub_id_space(false));
  }
  else if(xdof_map == 0)
  {
    // This member is a jim, but client has not provided a dof map.

    // Create a new dof map.

    ldof_map_id = new_row_dof_map();
  }
  else if(xcopy_dof_map || !(xdof_map->host()->is_same_state(this)))
  {
    // This member is a jim and client has provided a dof map,
    // but has requested it be copied, or it is from another host
    // and must be copied.

    // Copy the client-provided dof map.

    ldof_map_id = clone_row_dof_map(*xdof_map);
  }
  else if(!(xdof_map->index().is_valid()))
  {
    // This member is a jim and client has provided a dof tuple
    // from this host, but it has not yet been entered in the table.

    // Put it in the table.

    table().put_row_dof_tuple(xdof_map);
    ldof_map_id = xdof_map->index(); // set by put_row_dof_tuple
  }
  else
  {
    // This member is a jim and client has provided a dof tuple
    // from this host and it is already in the table.

    // Just use it.

    ldof_map_id = xdof_map->index();
  }

  // Create the new member.

  pod_index_type result = new_member(xis_jim, ldof_map_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // The following postcondition seems obvious, but it is not
  // true for immutable posets such as section_space_schema_poset.
  // ensure(member_ct() == (old_member_ct + 1));


  // Exit

  return result;
}

void
sheaf::poset_state_handle::
new_member(bool xis_jim, poset_dof_map* xdof_map, bool xcopy_dof_map, scoped_index& result)
{
  // Preconditions:

  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require(xdof_map != 0 ? xdof_map->host()->schema().is_same_state(&(schema())) : true);
  // schema is not attached yet when creating std members in namespace_poset, primitive_poset, etc.
  /// @todo propagate this precondition to poset_member constructors

  // Body:

  result.put(member_hub_id_space(false), new_member(xis_jim, xdof_map, xcopy_dof_map));

  // Postconditions:

  ensure(invariant());
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // The following postcondition seems obvious, but it is not
  // true for immutable posets such as section_space_schema_poset.
  // ensure(member_ct() == (old_member_ct + 1));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
new_member_interval(const std::string& xinterval_type,
                 size_type xsize,
                 const block<pod_index_type>& xtuple_hub_ids,
                 const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(in_jim_edit_mode());
  require(implicit_crg_interval::interval_factory().contains_prototype(xinterval_type));
  require(xsize > 0);

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(size_type old_member_ct = member_ct());

  pod_index_type result = new_member_interval(xinterval_type, xsize);

  implicit_crg_interval& linterval = *crg().implicit_member(result);

  linterval.initialize_dof_tuple_ids(xtuple_hub_ids);
  linterval.put_private_data(xdata);
  linterval.finalize(*this);

  // Postconditions:

  ensure(member_index_ub() >= old_member_index_ub + xsize);
  ensure(member_ct() == old_member_ct + xsize);
  ensure_for_range(pod_index_type i=result, i<member_index_ub().pod(), ++i, contains_member(i));
  ensure(unexecutable("result is_initialized()"));

  // Exit:

  return result;
}

void
sheaf::poset_state_handle::
new_member_interval(const std::string& xinterval_type,
		    size_type xsize,
		    const block<pod_index_type>& xtuple_hub_ids,
		    const block<pod_index_type>& xdata,
		    scoped_index& result)
{
  // Preconditions:

  require(in_jim_edit_mode());
  require(implicit_crg_interval::interval_factory().contains_prototype(xinterval_type));
  require(xsize > 0);

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(size_type old_member_ct = member_ct());

  result.put(member_hub_id_space(false),
	     new_member_interval(xinterval_type, xsize, xtuple_hub_ids, xdata));

  // Postconditions:

  ensure(member_index_ub() >= old_member_index_ub + xsize);
  ensure(member_ct() == old_member_ct + xsize);
  ensure_for_range(scoped_index i=result, i<member_index_ub(), ++i, contains_member(i));
  ensure(unexecutable("result is_initialized()"));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_member(pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));

  /// @todo should not be able to delete a
  /// standard member unless called from destructor

  // Body:

  // Delete the members name, if any, from the name map.

  delete_all_member_names(xmbr_hub_id, false);

  // Remove member from all subposets.

  powerset().delete_poset_member(xmbr_hub_id);

  // Clear cover sets, delete node in crg and the id from the top id space.

  crg().delete_member(xmbr_hub_id);

  // Postconditions:

  ensure(invariant());
  ensure(!contains_member(xmbr_hub_id, false));
  ensure(unexecutable(member_ct() = old member_ct() - 1));
  ensure(unexecutable("for all subposets s( !s.contains_member(xindex))"));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
delete_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id, false));

  /// @todo should not be able to delete a
  /// standard member unless called from destructor

  // Body:

  delete_member(xmbr_id.hub_pod());  

  // Postconditions:

  ensure(invariant());
  ensure(!contains_member(xmbr_id, false));
  ensure(unexecutable(member_ct() = old member_ct() - 1));
  ensure(unexecutable("for all subposets s( !s.contains_member(xindex))"));

  // Exit

  return;
}

int
sheaf::poset_state_handle::
member_ct() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = crg().member_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

int
sheaf::poset_state_handle::
standard_member_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = crg().standard_member_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

bool
sheaf::poset_state_handle::
has_standard_member_ct() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = (member_ct() == standard_member_ct());

  // Postconditions:

  ensure(result == (member_ct() == standard_member_ct()));

  return result;
}

sheaf::scoped_index
sheaf::poset_state_handle::
member_index_ub() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result = crg().end();

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result >= 0);

  return result;
}

sheaf::index_iterator
sheaf::poset_state_handle::
member_iterator() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  index_iterator  result(whole().members(), member_hub_id_space(false), false);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_member(pod_index_type xmbr_hub_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  bool result = crg().contains_member(xmbr_hub_id);

  // Postconditions:

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
contains_member(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  return contains_member(xmbr_id.hub_pod(), xauto_access);
}

bool
sheaf::poset_state_handle::
contains_member(pod_index_type xmbr_hub_id, int xversion, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(has_version(xversion));

  // Body:

  result = powerset().subposet_contains_member(version_index(xversion), xmbr_hub_id);

  // Postconditions:

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
contains_member(const scoped_index& xmbr_id, int xversion, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  return contains_member(xmbr_id.hub_pod(), xversion, xauto_access);
}

bool
sheaf::poset_state_handle::
contains_member(const std::string& xname, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(!xname.empty());

  // Body:

  // This particular implementation avoids the need for
  // redefining this function in the section_space_schema_poset classes.

  result = is_valid(member_id(xname, false));

  if(xauto_access)
  {
    release_access();
  }

  return result;
}

bool
sheaf::poset_state_handle::
contains_member(const abstract_poset_member* xmbr, bool xauto_access) const
{

  // Preconditions:

  require(xmbr != 0);
  require(xauto_access || state_is_read_accessible());

  // Body:

  bool result =
    is_same_state(xmbr->host()) && contains_member(xmbr->index(), xauto_access);

  // Postconditions:

  return result;
}

bool
sheaf::poset_state_handle::
contains_members(const scoped_index* xmbrs, int xmbrs_ct, bool xauto_access) const
{

  // Preconditions:

  require(xmbrs != 0);
  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int i = 0;

  while(result && i < xmbrs_ct)
  {
    result = contains_member(xmbrs[i], false);
    i++;
  };

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xmbrs( contains_member(i) )"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_members(pod_index_type* xmbrs, int xmbrs_ct, bool xauto_access) const
{

  // Preconditions:

  require(xmbrs != 0);
  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int i = 0;

  while(result && i < xmbrs_ct)
  {
    result = contains_member(xmbrs[i], false);
    i++;
  };

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xmbrs( contains_member(i) )"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_members(const block<pod_index_type>& xmbrs, bool xauto_access) const
{

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int i = 0;

  while(result && i < xmbrs.ct())
  {
    result = contains_member(xmbrs[i], false);

    i++;
  };

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xmbrs( contains_member(i))"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_members(const block<scoped_index>& xmbrs, bool xauto_access) const
{

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int i = 0;

  while(result && i < xmbrs.ct())
  {
    result = contains_member(xmbrs[i], false);

    i++;
  };

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xmbrs( contains_member(i))"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_members(const std::string* xnames, int xnames_ct, bool xauto_access) const
{

  // Preconditions:

  require(xnames != 0);
  require_for_all(i, 0, xnames_ct, !xnames[i].empty());
  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int i = 0;

  while(result && i < xnames_ct)
  {
    result = contains_member(xnames[i], false);
    i++;
  };

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xnames( contains_member(xnames[i]))"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_members(const block<std::string>& xmbrs, bool xauto_access) const
{

  // Preconditions:

  require_for_all(i, 0, xmbrs.ct(), !xmbrs[i].empty());
  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int i = 0;

  while(result && i < xmbrs.ct())
  {
    result = contains_member(xmbrs[i], false);
    i++;
  };

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xmbrs( contains_member(xmbrs[i]) )"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_empty() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = member_ct() == 0;
  /// @issue is this the right definition?

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_jim(pod_index_type xmbr_hub_id, bool xin_current_version ) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(xin_current_version)
  {
    // The member associated with xindex is a jim in the current
    // version if it is a member of the jims subposet.

    result = jims().contains_member(xmbr_hub_id);
  }
  else
  {
    // The member associated with xindex has a dof map if and only if
    // it is a jim in some version of the poset.

    result = is_valid(member_dof_tuple_id(xmbr_hub_id, false));
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_jim(const scoped_index& xmbr_id, bool xin_current_version ) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return is_jim(xmbr_id.hub_pod(), xin_current_version);
}

bool
sheaf::poset_state_handle::
is_jim(const std::string& xname, bool xin_current_version) const
{
  bool result;

  // Preconditions:

  require(!xname.empty());
  require(state_is_read_accessible());

  // Body:

  pod_index_type lindex = member_id(xname, false);
  result = is_valid(lindex) && is_jim(lindex, xin_current_version);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_atom(pod_index_type xmbr_hub_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result =
    (!cover_is_empty(LOWER, xmbr_hub_id)) &&
    (first_cover_member(LOWER, xmbr_hub_id) == BOTTOM_INDEX);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_atom(const scoped_index& xmbr_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return is_atom(xmbr_id.hub_pod());
}

sheaf::abstract_poset_member&
sheaf::poset_state_handle::
top()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *_top;
}

const sheaf::abstract_poset_member&
sheaf::poset_state_handle::
top() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *_top;
}

sheaf::abstract_poset_member&
sheaf::poset_state_handle::
bottom()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *_bottom;
}

const sheaf::abstract_poset_member&
sheaf::poset_state_handle::
bottom() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *_bottom;
}

void
sheaf::poset_state_handle::
initialize_standard_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Enter jim edit mode.

  begin_jim_edit_mode(false);

  // Allocate the bottom member; becomes index 0.
  // No dof tuple allocated.

  bottom().attach_to_state(this, new_member(false));
  bottom().put_name("bottom", true, false);

  // Allocate the top member; becomes index 1.
  // No dof tuple allocated.

  top().attach_to_state(this, new_member(false));
  top().put_name("top", true, false);

  /// @issue top does not cover bottom in empty poset.
  /// The mathematical meaning is unclear, but it seems to work just fine,
  /// except that we have to make sure bottom appears in the file id map,
  /// see member_record_set::make_idorder_file_maps.

  // Only two standard members and no dof tuples so far.
  // (More may be added in descendants.)

  // All the members and row dof tuples are standard.

  put_standard_member_ct(member_ct());
  put_standard_row_dof_tuple_ct(row_dof_tuple_ct());

  end_jim_edit_mode(true, false);

  // Now the cover relation graph invariant is satisfied

  crg().enable_invariant_check();

  assertion(crg().invariant());

  // Postconditions:

  ensure(bottom().is_attached() && (bottom().index() == BOTTOM_INDEX));
  ensure(top().is_attached() && (top().index() == TOP_INDEX));
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  // Exit

  return;
}

bool
sheaf::poset_state_handle::
index_in_bounds(const scoped_index& xmbr_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = xmbr_id.in_range(crg().begin(), crg().end());

  // Postconditions:
  ensure(invariant());
  ensure( result == xmbr_id.in_range(crg().begin(), crg().end()) );

  // Exit

  return(result);
}

bool
sheaf::poset_state_handle::
index_in_bounds(const block<scoped_index>& xindices) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = true;
  int i = 0;
  scoped_index lmember_index_ub = member_index_ub();

  while(i < xindices.ub() && result)
  {
    result = xindices[i].in_range(crg().begin(), crg().end()) && result;
    i++;
  };

  // Postconditions:
  ensure(invariant());

  // Exit

  return(result);
}

void
sheaf::poset_state_handle::
new_member(pod_index_type xmbr_hub_id, bool xis_jim, const scoped_index& xdof_tuple_id)
{
  // Preconditions:

  require(is_valid(xmbr_hub_id));
  require(!contains_member(xmbr_hub_id));
  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require(member_id_spaces(false).is_valid_reserved_id(xmbr_hub_id));
  require((!xdof_tuple_id.is_valid()) || contains_row_dof_tuple(xdof_tuple_id));

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(int old_member_ct = member_ct());

  // Create new node in crg; ensures lower and upper covers empty.

  crg().new_member(xmbr_hub_id);

  // Set the dof tuple id for the member.

  crg().put_member_dof_tuple_id(xmbr_hub_id, xdof_tuple_id.hub_pod());

  // If node allocation has extended the member pool,
  // extend the subposet characteristic functions to match.

  if(crg().end() > powerset().subposet_member_index_ub())
  {
    powerset().put_subposet_member_index_ub(crg().end());
  }

  // Put new node in subposet of all members.

  powerset().whole().insert_member(xmbr_hub_id);

  // New members are not jims, not resident, and not modified by default.
  // Note that since resident and modified refers to the dof tuple,
  // and jrms don't have dof tuples, jrms should never be resident or modified.

  if(xis_jim)
  {
    // Put new member in subposet of all jims.

    jims().insert_member(xmbr_hub_id);
  }

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xmbr_hub_id));
  ensure(cover_is_empty(LOWER, xmbr_hub_id));
  ensure(cover_is_empty(UPPER, xmbr_hub_id));

  // The following postconditions seems obvious, but it is not
  // true for immutable posets such as section_space_schema_poset.
  // ensure(member_ct() == (old_member_ct + 1));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
new_member(pod_index_type xmbr_hub_id, bool xis_jim, poset_dof_map* xdof_map, bool xcopy_dof_map)
{
  // Preconditions:

  require(is_valid(xmbr_hub_id));
  require(!contains_member(xmbr_hub_id));
  require(xis_jim ? in_jim_edit_mode() : state_is_read_write_accessible());
  require(member_id_spaces(false).is_valid_reserved_id(xmbr_hub_id));
  require(xdof_map != 0 ? xdof_map->host()->schema().is_same_state(&(schema())) : true);
  // schema is not attached yet when creating std members in namespace_poset, primitive_poset, etc.
  /// @todo propagate this precondition to poset_member constructors

  // Body:

  define_old_variable(int old_member_ct = member_ct());

  // Get a dof tuple id.

  scoped_index ldof_map_id(dof_tuple_hub_id_space(false));
  if(!xis_jim)
  {
    // This member is a jrm, does not have a dof map.

    ldof_map_id.invalidate();
  }
  else if(xdof_map == 0)
  {
    // This member is a jim, but client has not provided a dof map.

    // Create a new dof map.

    ldof_map_id = new_row_dof_map();
  }
  else if(xcopy_dof_map || !(xdof_map->host()->is_same_state(this)))
  {
    // This member is a jim and client has provided a dof map,
    // but has requested it be copied, or it is from another host
    // and must be copied.

    // Copy the client-provided dof map.

    ldof_map_id = clone_row_dof_map(*xdof_map);
  }
  else if(!(xdof_map->index().is_valid()))
  {
    // This member is a jim and client has provided a dof tuple
    // from this host, but it has not yet been entered in the table.

    // Put it in the table.

    table().put_row_dof_tuple(xdof_map);
    ldof_map_id = xdof_map->index(); // set by put_row_dof_tuple
  }
  else
  {
    // This member is a jim and client has provided a dof tuple
    // from this host and it is already in the table.

    // Just use it.

    ldof_map_id = xdof_map->index();
  }

  // Create the new member.

  new_member(xmbr_hub_id, xis_jim, const_cast<const scoped_index&>(ldof_map_id));

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xmbr_hub_id));
  ensure(cover_is_empty(LOWER, xmbr_hub_id));
  ensure(cover_is_empty(UPPER, xmbr_hub_id));

  // The following postcondition seems obvious, but it is not
  // true for immutable posets such as section_space_schema_poset.
  // ensure(member_ct() == (old_member_ct + 1));


  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
new_member_interval(const std::string& xinterval_type, size_type xsize)
{
  // Preconditions:

  require(in_jim_edit_mode());
  require(implicit_crg_interval::interval_factory().contains_prototype(xinterval_type));
  require(xsize > 0);

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(size_type old_member_ct = member_ct());

  // Allocate the interval in the member id space
  // and create the member emulator for it.

  pod_index_type result =  crg().new_member_interval(xinterval_type, xsize);
  implicit_crg_interval& linterval = *crg().implicit_member(result);

  // If node allocation has extended the member pool,
  // extend the subposet characteristic functions to match.

  if(crg().end() > powerset().subposet_member_index_ub())
  {
    powerset().put_subposet_member_index_ub(crg().end());
  }

  for(pod_index_type i=linterval.begin(); i<linterval.end(); ++i)
  {
    // Set whole() membership.

    powerset().whole().insert_member(i);
  }

  // Postconditions:

  ensure(member_index_ub() >= old_member_index_ub + xsize);
  ensure(member_ct() == old_member_ct + xsize);
  ensure_for_range(pod_index_type i=result, i<member_index_ub().pod(), ++i, contains_member(i));
  ensure(unexecutable("result size_initialized()"));
  ensure(unexecutable("result local_id_space_initialized()"));

  // Exit:

  return result;
}

void
sheaf::poset_state_handle::
new_member_interval(pod_index_type xmbr_hub_id, const std::string& xinterval_type, size_type xsize)
{
  // Preconditions:

  require(is_valid(xmbr_hub_id));
  require_for_range(pod_index_type i=0, i<xsize, ++i, !contains_member(xmbr_hub_id + i));
  require(in_jim_edit_mode());
  require(implicit_crg_interval::interval_factory().contains_prototype(xinterval_type));
  require(xsize > 0);

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(size_type old_member_ct = member_ct());

  // Allocate the interval in the member id space
  // and create the member emulator for it.

  crg().new_member_interval(xmbr_hub_id, xinterval_type, xsize);
  implicit_crg_interval& linterval = *crg().implicit_member(xmbr_hub_id);

  // If node allocation has extended the member pool,
  // extend the subposet characteristic functions to match.

  if(crg().end() > powerset().subposet_member_index_ub())
  {
    powerset().put_subposet_member_index_ub(crg().end());
  }

  for(pod_index_type i=linterval.begin(); i<linterval.end(); ++i)
  {
    // Set whole() membership.

    powerset().whole().insert_member(i);
  }

  // Postconditions:

  ensure(member_index_ub() >= old_member_index_ub);
  ensure(member_ct() == old_member_ct + xsize);
  ensure_for_range(pod_index_type i=0, i<xsize, ++i, contains_member(xmbr_hub_id + i));
  ensure(unexecutable("result size_initialized()"));
  ensure(unexecutable("result local_id_space_initialized()"));

  // Exit:

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBER NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_path
sheaf::poset_state_handle::
member_path(pod_index_type xmbr_hub_id, bool xauto_access) const
{
  // cout << endl << "Entering poset_state_handle::member_path." << endl;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, xauto_access));
  
  // Body:

  poset_path result(name(xauto_access), member_name(xmbr_hub_id, xauto_access));

  // Postconditions:

  ensure(result.poset_name() == name(xauto_access));
  ensure(member_id(result.member_name(), xauto_access) == xmbr_hub_id);
  
  // Exit:

  // cout << "Leaving poset_state_handle::member_path." << endl;
  return result;
}


std::string
sheaf::poset_state_handle::
member_name(pod_index_type xmbr_hub_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  string result(crg().member_name_map().name(xmbr_hub_id));

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

std::string
sheaf::poset_state_handle::
member_name(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  return member_name(xmbr_id.hub_pod(), xauto_access);
}

void
sheaf::poset_state_handle::
all_member_names(pod_index_type xmbr_hub_id,
                 block<std::string>& xresult,
                 bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().member_name_map().all_names(xmbr_hub_id, xresult);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(xresult.ct() == member_name_ct(xmbr_hub_id, xauto_access));
  ensure_for_all(i, 0, xresult.ct(), member_has_name(xmbr_hub_id, xresult[i], xauto_access));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
all_member_names(const scoped_index& xmbr_id,
                 block<std::string>& xresult,
                 bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  all_member_names(xmbr_id.hub_pod(), xresult, xauto_access);

  // Postconditions:

  ensure(xresult.ct() == member_name_ct(xmbr_id, xauto_access));
  ensure_for_all(i, 0, xresult.ct(), member_has_name(xmbr_id, xresult[i], xauto_access));

  // Exit:

  return;
}

sheaf::size_type
sheaf::poset_state_handle::
member_name_ct(pod_index_type xmbr_hub_id, bool xauto_access) const
{
  size_type result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = crg().member_name_map().name_ct(xmbr_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::poset_state_handle::
member_name_ct(const scoped_index& xmbr_id, bool xauto_access) const
{
  size_type result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  return member_name_ct(xmbr_id.hub_pod(), xauto_access);
}

bool
sheaf::poset_state_handle::
member_has_name(pod_index_type xmbr_hub_id, const std::string& xname, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(!xname.empty());
  require(contains_member(xmbr_hub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = crg().member_name_map().contains_entry(xmbr_hub_id, xname);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
member_has_name(const scoped_index& xmbr_id, const std::string& xname, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!xname.empty());
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  return member_has_name(xmbr_id.hub_pod(), xname, xauto_access);
}

void
sheaf::poset_state_handle::
put_member_name(pod_index_type xmbr_hub_id,
                const std::string& xname,
                bool xunique,
                bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, xauto_access));
  require(poset_path::is_valid_name(xname));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  crg().member_name_map().put_entry(xmbr_hub_id, xname, xunique);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition:

  ensure(member_has_name(xmbr_hub_id, xname, xauto_access));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
put_member_name(const scoped_index& xmbr_id,
                const std::string& xname,
                bool xunique,
                bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(contains_member(xmbr_id, xauto_access));
  require(poset_path::is_valid_name(xname));

  // Body:

  put_member_name(xmbr_id.hub_pod(), xname, xunique, xauto_access);

  // Postcondition:

  ensure(member_has_name(xmbr_id, xname, xauto_access));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
delete_member_name(const std::string& xname, bool xauto_access)
{
  // Preconditions:

  require(!xname.empty());
  require(state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  crg().member_name_map().delete_name(xname);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition

  ensure(!contains_member(xname, xauto_access));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_all_member_names(pod_index_type xmbr_hub_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  crg().member_name_map().delete_index(xmbr_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition

  ensure(member_name_ct(xmbr_hub_id, xauto_access) == 0);

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_all_member_names(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());

  // Body:

  delete_all_member_names(xmbr_id.hub_pod(), xauto_access);

  // Postcondition

  ensure(member_name_ct(xmbr_id, xauto_access) == 0);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::poset_state_handle::member_name_map_type&
sheaf::poset_state_handle::
member_name_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());

  // Body:

  member_name_map_type& result = crg().member_name_map();

  // Postconditions:

  // Exit

  return result;
}

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// MEMBER ID SPACE FAMILY FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::index_space_family&
sheaf::poset_state_handle::
member_id_spaces(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const index_space_family& result = crg()._id_spaces;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::poset_state_handle::
member_id_spaces(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  index_space_family& result = crg()._id_spaces;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::poset_state_handle::
member_hub_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const hub_index_space_handle& result = crg().id_spaces().hub_id_space();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::scoped_index&
sheaf::poset_state_handle::
member_id(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const scoped_index& result = crg().hub_id();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.same_scope(member_hub_id_space(xauto_access)));

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_state_handle::
member_id(pod_index_type xid, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  scoped_index result(member_id(false));
  result = xid;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.same_scope(member_hub_id_space(xauto_access)));
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
member_id(const std::string& xname, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(!xname.empty());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  // Lookup the name in the name-to-index map.

  pod_index_type result = crg().member_name_map().index(xname);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition:

  ensure(is_valid(result) ? member_has_name(result, xname, xauto_access) : true);

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
member_id(const std::string& xname, scoped_index& result, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(!xname.empty());

  // Body:

  result.put(member_hub_id_space(xauto_access), member_id(xname, xauto_access));

  // Postcondition:

  ensure(result.is_valid() ? member_has_name(result, xname, xauto_access) : true);

  // Exit

  return;
}

// PROTECTED FUNCTIONS

void
sheaf::poset_state_handle::
update_standard_member_id_spaces()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  crg()._id_spaces.update_standard_id_spaces();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
clear_member_id_spaces(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  crg()._id_spaces.clear_id_spaces();

  // Postconditions:

  ensure(member_id_spaces(false).has_only_standard_id_spaces());

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
extend_last_member_term(size_type xct, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(!member_hub_id_space(xauto_access).is_empty());

  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  define_old_variable(const index_space_handle& last_term = member_id_spaces(false).last_term());
  define_old_variable(scoped_index old_last_term_begin(last_term, last_term.begin()));

  if(xct > crg()._id_spaces.last_term().ct())
  {
    crg()._id_spaces.extend_last_term(xct);
  }
  
  if(xauto_access)
  {
    release_access();
  }

  // Postcondtions:

  ensure_for_range(scoped_index i=old_last_term_begin, i<old_last_term_begin+xct, ++i, i.in_scope());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
new_term(size_type xct, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  pod_index_type result = crg()._id_spaces.new_primary_state(xct);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postcondtions:

  // Exit:

  return result;
}

// PRIVATE FUNCTIONS


// ===========================================================
// ORDER RELATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::poset_state_handle::
le(pod_index_type xgreater, pod_index_type xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser, false));
  require(contains_member(xgreater, false));

  // Body:

  result = xgreater == xlesser;
  if(!result)
  {
    // recur on upper cover
    /// @hack should use upset traverser in poset_state_handle::le

    index_space_iterator& itr = get_cover_id_space_iterator(UPPER, xlesser);
    while((!itr.is_done()) && !result)
    {
      result = le(xgreater, itr.hub_pod());
      itr.next();
    }
    release_cover_id_space_iterator(itr);
  }

  // Postconditions:

  ensure(unexecutable(upset of xlesser contains xgreater));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
le(const scoped_index& xgreater, const scoped_index& xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser, false));
  require(contains_member(xgreater, false));

  // Body:

  result = le(xgreater.hub_pod(), xlesser.hub_pod());

  // Postconditions:

  ensure(unexecutable(upset of xlesser contains xgreater));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
leqv(pod_index_type xgreater, pod_index_type xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser, false));
  require(contains_member(xgreater, false));

  // Body:

  result = le(xgreater, xlesser) || is_jem(xgreater, xlesser);

  // Postconditions:

  ensure(unexecutable(upset of xlesser contains xgreater));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
leqv(const scoped_index& xgreater, const scoped_index& xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser, false));
  require(contains_member(xgreater, false));

  // Body:

  result = leqv(xgreater.hub_pod(), xlesser.hub_pod());

  // Postconditions:

  ensure(unexecutable(upset of xlesser contains xgreater));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_jem(pod_index_type xmbr_hub_id, pod_index_type xother_hub_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(contains_member(xother_hub_id, false));

  // Body:

  result = (greatest_jem(xmbr_hub_id) == greatest_jem(xother_hub_id));

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_jem(const scoped_index& xmbr_id, const scoped_index& xother_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id, false));
  require(contains_member(xother_id, false));

  // Body:

  return is_jem(xmbr_id.hub_pod(), xother_id.hub_pod());
}

sheaf::pod_index_type
sheaf::poset_state_handle::
greatest_jem(pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  pod_index_type result = xmbr_hub_id;

  pod_index_type lfirst_upper_mbr = invalid_pod_index();
  if(!cover_is_empty(UPPER, result))
  {
    lfirst_upper_mbr = first_cover_member(UPPER, result);
  }


  while(is_valid(lfirst_upper_mbr) &&
	!is_jim(lfirst_upper_mbr)  &&
	cover_is_singleton(LOWER, lfirst_upper_mbr))
  {
    result = lfirst_upper_mbr;
    if(cover_is_empty(UPPER, lfirst_upper_mbr))
    {
      lfirst_upper_mbr = invalid_pod_index();
    }
    else
    {
      lfirst_upper_mbr = first_cover_member(UPPER, lfirst_upper_mbr);
    }
  }

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
greatest_jem(const scoped_index& xmbr_id, scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id, false));

  // Body:

  result.put(member_hub_id_space(false), greatest_jem(xmbr_id.hub_pod()));

  // Postconditions:

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
least_jem(pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  pod_index_type result = xmbr_hub_id;
  while(!is_jim(result) && cover_is_singleton(LOWER, result))
  {
    result = first_cover_member(LOWER, result);
  }

  // Postconditions:

  ensure(is_jim(result) || !cover_is_singleton(LOWER, result));
  ensure(le(xmbr_hub_id, result));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
least_jem(const scoped_index& xmbr_id, scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id, false));

  // Body:

  result.put(member_hub_id_space(false), least_jem(xmbr_id.hub_pod()));

  // Postconditions:

  ensure(is_jim(result) || !cover_is_singleton(LOWER, result));
  ensure(le(xmbr_id, result));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
link_greatest_jem(pod_index_type xjem1, pod_index_type xjem2)
{

  // Preconditions:

  require(xjem1 != TOP_INDEX);
  require(xjem1 != BOTTOM_INDEX);
  require(cover_is_empty(LOWER, xjem1));
  require(cover_is_empty(UPPER, xjem1));

  // Body:

  // Make xjem1 the greatest jem of xjem2

  // We want to put xjem1 on top of the current greatest jem of xjem2,
  // unless the current greatest jem is the top. The top must always
  // be the top, so if the current greatest jem is the top, we'll
  // put the new jem immediately under it. Either way, we first find
  // the current greatest jem.

  pod_index_type lgjem = greatest_jem(xjem2);

  if(lgjem != TOP_INDEX)
  {
    // Current greatest jem is not the top;
    // Put new member on top of it.

    transfer_cover(lgjem, xjem1, false);
    new_link(xjem1, lgjem);
  }
  else
  {
    // Other member is the top;
    // Put new member directly under it.

    transfer_cover(lgjem, xjem1, true);
    new_link(lgjem, xjem1);
  }

  // Postconditions:

  ensure(is_jem(xjem2, xjem1));
  ensure(greatest_jem(xjem2) != TOP_INDEX ?
         greatest_jem(xjem2) == xjem1 :
         true );

  // Exit

  return;
}

void
sheaf::poset_state_handle::
link_greatest_jem(const scoped_index& xjem1, const scoped_index& xjem2)
{

  // Preconditions:

  require(xjem1 != TOP_INDEX);
  require(xjem1 != BOTTOM_INDEX);
  require(cover_is_empty(LOWER, xjem1));
  require(cover_is_empty(UPPER, xjem1));

  // Body:

  link_greatest_jem(xjem1.hub_pod(), xjem2.hub_pod());

  // Postconditions:

  ensure(is_jem(xjem2, xjem1));
  ensure(greatest_jem(xjem2.hub_pod()) != TOP_INDEX ?
         greatest_jem(xjem2.hub_pod()) == xjem1.hub_pod() :
         true );

  // Exit

  return;
}

void
sheaf::poset_state_handle::
link_least_jem(pod_index_type xjem1, pod_index_type xjem2)
{
  // Preconditions:

  require(xjem1 != TOP_INDEX);
  require(xjem1 != BOTTOM_INDEX);
  require(cover_is_empty(LOWER, xjem1));
  require(cover_is_empty(UPPER, xjem1));

  // Body:

  // Make xjem1 the least jem of xjem2

  // We want to put xjem1 directly below the current least jem of xjem2,
  // unless the current least jem is the bottom. The bottom must always
  // be the bottom, so if the current least jem is the bottom, we'll
  // put the new jem immediately above it. Either way, we first find
  // the current least jem.

  pod_index_type lljem = least_jem(xjem2);

  if(is_jim(lljem) || lljem == BOTTOM_INDEX)
  {
    // the current least jem is a jim or is the bottom;
    // Put new member directly on top of it.

    transfer_cover(lljem, xjem1, false);
    new_link(xjem1, lljem);
  }
  else
  {
    // Current least jem is a jrm and not the bottom;
    // Put new member below it.

    transfer_cover(lljem, xjem1, true);
    new_link(lljem, xjem1);
  }

  // Postconditions:

  ensure(is_jem(xjem2, xjem1));
  ensure((least_jem(xjem2) == xjem1) ||
         is_jim(least_jem(xjem2)) ||
         (least_jem(xjem2) == BOTTOM_INDEX));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
link_least_jem(const scoped_index& xjem1, const scoped_index& xjem2)
{
  // Preconditions:

  require(xjem1 != TOP_INDEX);
  require(xjem1 != BOTTOM_INDEX);
  require(cover_is_empty(LOWER, xjem1));
  require(cover_is_empty(UPPER, xjem1));

  // Body:

  link_least_jem(xjem1.hub_pod(), xjem2.hub_pod());

  // Postconditions:

  ensure(is_jem(xjem2, xjem1));
  ensure((least_jem(xjem2.hub_pod()) == xjem1.hub_pod()) ||
         is_jim(least_jem(xjem2.hub_pod())) ||
         (least_jem(xjem2.hub_pod()) == BOTTOM_INDEX));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
merge_jems(pod_index_type xjem1, pod_index_type xjem2)
{
  // Preconditions:

  require(xjem1 != xjem2);
  require(!is_jem(xjem1, BOTTOM_INDEX));
  require(state_is_read_write_accessible());
  require(contains_member(xjem1, false));
  require(contains_member(xjem2, false));
  require(!is_jim(xjem1));
  require(!is_jim(xjem2));
  require(cover_is_equal(LOWER, xjem1, xjem2));

  // Body:

  // link join-equivalence class of xjem2
  // linearly below the least jem of xjem1

  // get the least and greatest members of both equivalence classes

  pod_index_type gjem1 = greatest_jem(xjem1);
  pod_index_type gjem2 = greatest_jem(xjem2);

  pod_index_type ljem1 = least_jem(xjem1);
  pod_index_type ljem2 = least_jem(xjem2);

  if(gjem1 != gjem2)
  {
    // Transfer the upper cover of gjem2 to gjem1.

    transfer_cover(gjem2, gjem1, false);
  }


  if(ljem1 != ljem2)
  {
    // Transfer the lower cover of ljem1 to ljem2.

    transfer_cover(ljem1, ljem2, true);
  }


  if(ljem1 != gjem2)
  {
    // Cover gjem2 with ljem1.

    new_link(ljem1, gjem2);
  }

  // Postconditions:

  ensure(le(xjem1, xjem2));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
merge_jems(const scoped_index& xjem1, const scoped_index& xjem2)
{
  // Preconditions:

  require(xjem1 !=~ xjem2);
  require(!is_jem(xjem1, bottom().index()));
  require(state_is_read_write_accessible());
  require(contains_member(xjem1, false));
  require(contains_member(xjem2, false));
  require(!is_jim(xjem1));
  require(!is_jim(xjem2));
  require(cover_is_equal(LOWER, xjem1, xjem2));

  // Body:

  merge_jems(xjem1.hub_pod(), xjem2.hub_pod());

  // Postconditions:

  ensure(le(xjem1, xjem2));

  // Exit

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// COVER RELATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

void
sheaf::poset_state_handle::
new_link(pod_index_type xgreater, pod_index_type xlesser)
{

  // Preconditions:

  require(contains_member(xgreater, false));
  require(xgreater != BOTTOM_INDEX);
  require(contains_member(xlesser, false));
  require(xlesser != TOP_INDEX);

  // Body:

  // Make some useful local variables

  crg().insert_cover_member(xgreater, UPPER, xlesser);
  crg().insert_cover_member(xlesser, LOWER, xgreater);

  // Postconditions:

  /// @hack the following precondition is unexecutable because
  /// contains_cover_link must do a linear search of the lower cover
  /// of xgreater. The lower cover of a block is O(size of block),
  /// which makes assertions non-linear.

  ensure(unexecutable(contains_link(xgreater, xlesser)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
new_link(const scoped_index& xgreater, const scoped_index& xlesser)
{

  // Preconditions:

  require(contains_member(xgreater, false));
  require(xgreater.hub_pod() != BOTTOM_INDEX);
  require(contains_member(xlesser, false));
  require(xlesser.hub_pod() != TOP_INDEX);

  // Body:

  new_link(xgreater.hub_pod(), xlesser.hub_pod());

  // Postconditions:

  /// @hack the following precondition is unexecutable because
  /// cointains_cover_link must do a linear search of the lower cover
  /// of xgreater. The lower cover of a block is O(size of block),
  /// which makes assertions non-linear.

  ensure(unexecutable(contains_link(xgreater, xlesser)));

  // Exit:

  return;

}

void
sheaf::poset_state_handle::
delete_link(pod_index_type xgreater, pod_index_type xlesser)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  crg().remove_cover_member(xgreater, UPPER, xlesser);
  crg().remove_cover_member(xlesser, LOWER, xgreater);

  // Postconditions:

  ensure(invariant());
  ensure(!contains_link(xgreater, xlesser));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_link(const scoped_index& xgreater, const scoped_index& xlesser)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  delete_link(xgreater.hub_pod(), xlesser.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(!contains_link(xgreater, xlesser));

  // Exit:

  return;
}

bool
sheaf::poset_state_handle::
contains_link(pod_index_type xgreater, pod_index_type xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser, false));
  require(contains_member(xgreater, false));

  // Body:

  result =
    crg().cover_contains_member(LOWER, xgreater, xlesser) &&
    crg().cover_contains_member(UPPER, xlesser, xgreater);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_link(const scoped_index& xgreater, const scoped_index& xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser, false));
  require(contains_member(xgreater, false));

  // Body:

  return contains_link(xgreater.hub_pod(), xlesser.hub_pod());
}

sheaf::pod_index_type
sheaf::poset_state_handle::
cover_id_space_id(bool xlower, pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(contains_member(xmbr_hub_id));

  // Body:

  pod_index_type result = crg().cover_id_space_id(xlower, xmbr_hub_id);

  // Postconditions:

  ensure(is_valid(result));

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
cover_id_space_id(bool xlower, const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  pod_index_type result = cover_id_space_id(xlower, xmbr_id.hub_pod());

  // Postconditions:

  ensure(is_valid(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
sheaf::poset_state_handle::
get_cover_id_space(bool xlower, pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  return crg().get_cover_id_space(xlower, xmbr_hub_id);
}

sheaf::index_space_handle&
sheaf::poset_state_handle::
get_cover_id_space(bool xlower, const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id));

  // Body:

  return get_cover_id_space(xlower, xmbr_id.hub_pod());
}

void
sheaf::poset_state_handle::
release_cover_id_space(index_space_handle& xcover_id_space) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  crg().release_cover_id_space(xcover_id_space);

  // Postconditions:

  ensure(!xcover_id_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
sheaf::poset_state_handle::
get_cover_id_space_iterator(bool xlower, pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  return crg().get_cover_id_space_iterator(xlower, xmbr_hub_id);
}

sheaf::index_space_iterator&
sheaf::poset_state_handle::
get_cover_id_space_iterator(bool xlower, const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id));

  // Body:

  return get_cover_id_space_iterator(xlower, xmbr_id.hub_pod());
}

void
sheaf::poset_state_handle::
release_cover_id_space_iterator(index_space_iterator& xcover_itr) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  crg().release_cover_id_space_iterator(xcover_itr);

  // Postconditions:

  ensure(!xcover_itr.is_attached());

  // Exit:

  return;
}

bool
sheaf::poset_state_handle::
cover_contains_iterator(bool xlower,
                        pod_index_type xmbr_hub_id,
                        const index_space_iterator& xitr) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  return crg().cover_contains_iterator(xlower, xmbr_hub_id, xitr);
}

bool
sheaf::poset_state_handle::
cover_contains_iterator(bool xlower,
                        const scoped_index& xmbr_id,
                        const index_space_iterator& xitr) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id));

  // Body:

  return cover_contains_iterator(xlower, xmbr_id.hub_pod(), xitr);
}

bool
sheaf::poset_state_handle::
cover_is_empty(bool xlower, pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  return crg().cover_is_empty(xlower, xmbr_hub_id);
}

bool
sheaf::poset_state_handle::
cover_is_empty(bool xlower, const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id, false));

  // Body:

  return cover_is_empty(xlower, xmbr_id.hub_pod());
}

bool
sheaf::poset_state_handle::
cover_is_singleton(bool xlower, pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  return crg().cover_is_singleton(xlower, xmbr_hub_id);
}

bool
sheaf::poset_state_handle::
cover_is_singleton(bool xlower, const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id, false));

  // Body:

  return cover_is_singleton(xlower, xmbr_id.hub_pod());
}

sheaf::size_type
sheaf::poset_state_handle::
cover_ct(bool xlower, pod_index_type xmbr_hub_id) const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  result = crg().cover_ct(xlower, xmbr_hub_id);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

sheaf::size_type
sheaf::poset_state_handle::
cover_ct(bool xlower, const scoped_index& xmbr_id) const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id, false));

  // Body:

  result = cover_ct(xlower, xmbr_id.hub_pod());

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
cover_contains_member(bool xlower,
                      pod_index_type xmbr_hub_id,
                      pod_index_type xother_mbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  return crg().cover_contains_member(xlower, xmbr_hub_id, xother_mbr_hub_id);
}

bool
sheaf::poset_state_handle::
cover_contains_member(bool xlower,
                      const scoped_index& xmbr_id,
                      const scoped_index& xother_mbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id));

  // Body:

  return cover_contains_member(xlower,
			       xmbr_id.hub_pod(),
			       xother_mbr_id.hub_pod());
}

bool
sheaf::poset_state_handle::
cover_is_equal(bool xlower,
               pod_index_type xmbr_hub_id,
               pod_index_type xother_mbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(contains_member(xother_mbr_hub_id, false));

  // Body:

  return crg().cover_is_equal(xlower, xmbr_hub_id, xother_mbr_hub_id);
}

bool
sheaf::poset_state_handle::
cover_is_equal(bool xlower,
               const scoped_index& xmbr_id,
               const scoped_index& xother_mbr_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id));
  require(contains_member(xother_mbr_id));

  // Body:

  return cover_is_equal(xlower,
			xmbr_id.hub_pod(),
			xother_mbr_id.hub_pod());
}

sheaf::pod_index_type
sheaf::poset_state_handle::
first_cover_member(bool xlower, pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(!cover_is_empty(xlower, xmbr_hub_id));

  // Body:

  return crg().first_cover_member(xlower, xmbr_hub_id);
}

void
sheaf::poset_state_handle::
first_cover_member(bool xlower, const scoped_index& xmbr_id,
		   scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xmbr_id));
  require(!cover_is_empty(xlower, xmbr_id));

  // Body:

  result.put(member_hub_id_space(false),
	     first_cover_member(xlower, xmbr_id.hub_pod()));

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
insert_cover_member(pod_index_type xother_mbr_hub_id,
                    bool xlower,
                    pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(!cover_contains_member(xlower, xmbr_hub_id, xother_mbr_hub_id));

  // Body:

  crg().insert_cover_member(xother_mbr_hub_id, xlower, xmbr_hub_id);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(cover_contains_member(xlower, xmbr_hub_id, xother_mbr_hub_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
insert_cover_member(const scoped_index& xother_mbr_id,
                    bool xlower,
                    const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));

  // Body:

  insert_cover_member(xother_mbr_id.hub_pod(),
		      xlower,
		      xmbr_id.hub_pod());

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(cover_contains_member(xlower, xmbr_id, xother_mbr_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
insert_cover_member(pod_index_type xother_mbr_hub_id,
                    bool xlower,
                    pod_index_type xmbr_hub_id,
                    index_space_iterator& xitr)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(cover_contains_iterator(xlower, xmbr_hub_id, xitr));

  // Body:

  crg().insert_cover_member(xother_mbr_hub_id, xlower, xmbr_hub_id, xitr);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(cover_contains_member(xlower, xmbr_hub_id, xother_mbr_hub_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
insert_cover_member(const scoped_index& xother_mbr_id,
                    bool xlower,
                    const scoped_index& xmbr_id,
                    index_space_iterator& xitr)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));
  require(cover_contains_iterator(xlower, xmbr_id, xitr));

  // Body:

  insert_cover_member(xother_mbr_id.hub_pod(),
		      xlower,
		      xmbr_id.hub_pod(),
		      xitr);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(cover_contains_member(xlower, xmbr_id, xother_mbr_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
remove_cover_member(pod_index_type xother_mbr_hub_id,
                    bool xlower,
                    pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  crg().remove_cover_member(xother_mbr_hub_id, xlower, xmbr_hub_id);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(!cover_contains_member(xlower, xmbr_hub_id, xother_mbr_hub_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
remove_cover_member(const scoped_index& xother_mbr_id,
                    bool xlower,
                    const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));

  // Body:

  remove_cover_member(xother_mbr_id.hub_pod(),
		      xlower,
		      xmbr_id.hub_pod());

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(!cover_contains_member(xlower, xmbr_id, xother_mbr_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
remove_cover_member(index_space_iterator& xitr,
                    bool xlower,
                    pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  crg().remove_cover_member(xitr, xlower, xmbr_hub_id);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(!cover_contains_member(xlower, xmbr_hub_id, old_xitr_item)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
remove_cover_member(index_space_iterator& xitr,
                    bool xlower,
                    const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));

  // Body:

  remove_cover_member(xitr, xlower, xmbr_id.hub_pod());

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(!cover_contains_member(xlower, xmbr_id, old_xitr_item)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
replace_cover_member(pod_index_type xold_other_mbr_hub_id,
		     pod_index_type xnew_other_mbr_hub_id,
		     bool xlower,
		     pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));

  define_old_variable(bool old_cover_contains_old_other_mbr_hub_id = cover_contains_member(xlower, xmbr_hub_id, xold_other_mbr_hub_id));

  // Body:

  crg().replace_cover_member(xold_other_mbr_hub_id, xnew_other_mbr_hub_id, xlower, xmbr_hub_id);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(!cover_contains_member(xlower, xmbr_hub_id, xold_other_mbr_hub_id)));
  ensure(unexecutable(old_cover_contains_old_other_mbr_hub_id ? cover_contains_member(xlower, xmbr_hub_id, xnew_other_mbr_hub_id) : true));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
replace_cover_member(const scoped_index& xold_other_mbr_id,
		     const scoped_index& xnew_other_mbr_id,
		     bool xlower,
		     const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));

  define_old_variable(bool old_cover_contains_old_other_mbr_id = cover_contains_member(xlower, xmbr_id, xold_other_mbr_id));

  // Body:

  replace_cover_member(xold_other_mbr_id.hub_pod(),
		       xnew_other_mbr_id.hub_pod(),
		       xlower,
		       xmbr_id.hub_pod());

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(!cover_contains_member(xlower, xmbr_id, xold_other_mbr_id)));
  ensure(unexecutable(old_cover_contains_old_other_mbr_id ? cover_contains_member(xlower, xmbr_id, xnew_other_mbr_id) : true));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
clear_cover(bool xlower, pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));

  // Body:

  crg().clear_cover(xlower, xmbr_hub_id);

  // Postconditions:

  ensure(cover_is_empty(xlower, xmbr_hub_id));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
clear_cover(bool xlower, const scoped_index& xmbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));

  // Body:

  clear_cover(xlower, xmbr_id.hub_pod());

  // Postconditions:

  ensure(cover_is_empty(xlower, xmbr_id));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
copy_cover(bool xlower, pod_index_type xmbr_hub_id, pod_index_type xother_mbr_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(contains_member(xother_mbr_hub_id, false));

  // Body::

  crg().copy_cover(xlower, xmbr_hub_id, xother_mbr_hub_id);

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(cover_is_equal(xlower, xmbr_hub_id, xother_mbr_hub_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
copy_cover(bool xlower, const scoped_index& xmbr_id, const scoped_index& xother_mbr_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xmbr_id));
  require(contains_member(xother_mbr_id));

  // Body::

  copy_cover(xlower,
	     xmbr_id.hub_pod(),
	     xother_mbr_id.hub_pod());

  // Postconditions:

  // Unexecutable because average performance is O(cover_ct)

  ensure(unexecutable(cover_is_equal(xlower, xmbr_id, xother_mbr_id)));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
append_upper_cover_of_bottom(pod_index_type xmbr_hub_begin,
			     pod_index_type xmbr_hub_end)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require_for_range(pod_index_type i=xmbr_hub_begin, i<xmbr_hub_end, ++i, contains_member(i));

  // Body:

  crg().append_upper_cover_of_bottom(xmbr_hub_begin, xmbr_hub_end);

  // Postconditions:

  ensure_for_range(pod_index_type i=xmbr_hub_begin, i<xmbr_hub_end, ++i, cover_contains_member(UPPER, BOTTOM_INDEX, i));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
append_upper_cover_of_bottom(const scoped_index& xmbr_begin,
			     const scoped_index& xmbr_end)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require_for_range(scoped_index i=xmbr_begin, i<xmbr_end, ++i, contains_member(i));

  // Body::

  append_upper_cover_of_bottom(xmbr_begin.hub_pod(), xmbr_end.hub_pod());

  // Postconditions:

  ensure_for_range(scoped_index i=xmbr_begin, i<xmbr_end, ++i, cover_contains_member(UPPER, BOTTOM_INDEX, i.hub_pod()));

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

void
sheaf::poset_state_handle::
transfer_cover(pod_index_type xsrc, pod_index_type xdst, bool xlower)
{
  // Preconditions:

  require(contains_member(xsrc));
  require(contains_member(xdst));

  // Body:

  index_space_iterator& src_itr = get_cover_id_space_iterator(xlower, xsrc);
  while(!src_itr.is_done())
  {
    // Remove src index from the opposing cover of
    // the current member of src's xlower cover.

    // Could use delete_link if we were careful not to screw up
    // the iterator, but this method is a little faster since it
    // involves only half as many finds.

    // Note that "opposing cover" means the complement of xlower
    // is passed to remve_cover_member.

    remove_cover_member(xsrc, !xlower, src_itr.hub_pod());

    // Insert a link from dst to the current member of src's  cover.

    xlower ? new_link(xdst, src_itr.hub_pod()) : new_link(src_itr.hub_pod(), xdst);

    // Move on.

    src_itr.next();
  }
  release_cover_id_space_iterator(src_itr);

  // Now we can just erase src's cover

  clear_cover(xlower, xsrc);


  // Postconditions:

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// POWERSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::size_type
sheaf::poset_state_handle::
subposet_ct() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  size_type result = powerset().subposet_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

int
sheaf::poset_state_handle::
standard_subposet_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = powerset().standard_subposet_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

bool
sheaf::poset_state_handle::
has_standard_subposet_ct() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = (subposet_ct() == standard_subposet_ct());

  // Postconditions:

  ensure(result == (subposet_ct() == standard_subposet_ct()));

  return result;
}

sheaf::scoped_index
sheaf::poset_state_handle::
subposet_index_ub() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result = powerset().subposet_index_ub();

  // Postconditions:

  ensure(result.is_positive());

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
subposet_id(const std::string& xname) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(!xname.empty());

  // Body:

  pod_index_type result = powerset().subposet_name_map().index(xname);
  
  // Postconditions:

  ensure(invariant());
  ensure(is_valid(result) ? includes_subposet(result) : true);

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
subposet_id(const std::string& xname, scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(!xname.empty());

  // Body:

  result = powerset().hub_id(powerset().subposet_name_map().index(xname));
  
  // Postconditions:

  ensure(invariant());
  ensure(result.is_valid() ? includes_subposet(result) : true);

  // Exit

  return;
}

sheaf::index_space_iterator&
sheaf::poset_state_handle::
get_subposet_id_space_iterator() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return powerset().get_subposet_id_space_iterator();
}

void
sheaf::poset_state_handle::
release_subposet_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  powerset().release_subposet_id_space_iterator(xitr);

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::poset_state_handle::
includes_subposet(pod_index_type xsubposet_hub_id, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = powerset().contains_subposet(xsubposet_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
includes_subposet(const scoped_index& xsubposet_id, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  return includes_subposet(xsubposet_id.hub_pod(), xauto_access);
}

bool
sheaf::poset_state_handle::
includes_subposet(const std::string& xname, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type lid = subposet_id(xname);
  result = is_valid(lid) ? includes_subposet(lid, false) : false;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
includes_subposet(const subposet* xs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(!xauto_access ? state_is_read_accessible() : true);

  // Body:

  result = xs->is_attached() &&
           xs->host()->is_same_state(this) &&
           includes_subposet(xs->index(), xauto_access);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
includes_subposets(const block<pod_index_type>& xhub_ids, bool xauto_access) const
{
  bool result = true;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int i = 0;
  while(i < xhub_ids.ct() && result)
  {
    result = includes_subposet(xhub_ids[i], false);
    i++;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xhub_ids( includes_subposet(i))"));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
includes_subposets(const block<scoped_index>& xids, bool xauto_access) const
{
  bool result = true;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int i = 0;
  while(i < xids.ct() && result)
  {
    result = includes_subposet(xids[i].hub_pod(), false);
    i++;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("result == for all i in xids( includes_subposet(i))"));

  // Exit

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
new_subposet(bool xinitialize)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Get a subposet_state object from the powerset member pool.

  pod_index_type result = powerset().new_subposet(xinitialize);

  // Postconditions:

  ensure(invariant());
  ensure(includes_subposet(result, false));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
new_subposet(bool xinitialize, scoped_index& result)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Get a subposet_state object from the powerset member pool.

  powerset().new_subposet(xinitialize, result);

  // Postconditions:

  ensure(invariant());
  ensure(includes_subposet(result, false));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
new_subposet(const block<pod_index_type>& xmembers)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_members(xmembers));

  // Body:

  // Get a subposet_state object from the powerset member pool.

  pod_index_type result = powerset().new_subposet(xmembers);

  // Postconditions:

  ensure(invariant());
  ensure(includes_subposet(result, false));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
new_subposet(const block<scoped_index>& xmembers, scoped_index& result)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_members(xmembers));

  // Body:

  // Get a subposet_state object from the powerset member pool.

  powerset().new_subposet(xmembers, result);

  // Postconditions:

  ensure(invariant());
  ensure(includes_subposet(result, false));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
delete_subposet(pod_index_type xsubposet_hub_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(includes_subposet(xsubposet_hub_id, false));

  // Body:

  powerset().delete_subposet(xsubposet_hub_id);

  // Postcondition:

  ensure(invariant());
  ensure(!includes_subposet(xsubposet_hub_id, false));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_subposet(const scoped_index& xsubposet_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(includes_subposet(xsubposet_id, false));

  // Body:

  delete_subposet(xsubposet_id.hub_pod());

  // Postcondition:

  ensure(invariant());
  ensure(!includes_subposet(xsubposet_id, false));

  // Exit:

  return;
}

const sheaf::subposet&
sheaf::poset_state_handle::
whole() const
{
  require(state_is_read_accessible());

  return powerset().whole();
}


sheaf::subposet&
sheaf::poset_state_handle::
jims()
{
  require(state_is_read_accessible());

  return powerset().jims();
}

const sheaf::subposet&
sheaf::poset_state_handle::
jims() const
{
  require(state_is_read_accessible());

  return powerset().jims();
}

sheaf::subposet&
sheaf::poset_state_handle::
table_dof_subposet()
{
  require(state_is_read_accessible());

  return powerset().table_dof_subposet();
}

const sheaf::subposet&
sheaf::poset_state_handle::
table_dof_subposet() const
{
  require(state_is_read_accessible());

  return powerset().table_dof_subposet();
}

sheaf::subposet&
sheaf::poset_state_handle::
row_dof_subposet()
{
  require(state_is_read_accessible());

  return powerset().row_dof_subposet();
}

const sheaf::subposet&
sheaf::poset_state_handle::
row_dof_subposet() const
{
  require(state_is_read_accessible());

  return powerset().row_dof_subposet();
}

const std::string&
sheaf::poset_state_handle::
coarsest_common_refinement_name()
{
  // cout << endl << "Entering poset_state_handle::coarsest_common_refinement_name." << endl;

  // Preconditions:


  // Body:

  //  static const string result(poset_path::reserved_prefix() + "coarsest_common_refinement");
  static const string result("whole");

  // Postconditions:


  // Exit:

  // cout << "Leaving poset_state_handle::coarsest_common_refinement_name." << endl;
  return result;
}

// PROTECTED FUNCTIONS

sheaf::subposet&
sheaf::poset_state_handle::
resident()
{
  return _resident;
}

const sheaf::subposet&
sheaf::poset_state_handle::
resident() const
{
  return _resident;
}

sheaf::poset_powerset_state&
sheaf::poset_state_handle::
powerset() const
{
  return *(state_obj()->powerset());
}

void
sheaf::poset_state_handle::
initialize_standard_subposets(const std::string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Allocate the coarsest common refinement jims subposet, becomes member 0.

  subposet& lccr_jims = powerset().coarsest_common_refinement_jims();
  lccr_jims.new_state(this, true, false);
  lccr_jims.put_name("jims", true, false);  

  // Allocate the coarsest common refinement whole subposet, becomes member 1

  subposet& lccr = powerset().coarsest_common_refinement();
  lccr.new_state(this, true, false);
  lccr.put_name(coarsest_common_refinement_name(), true, false);

  // CCR and version 0 are the same thing until we move to version 1.

  string lccr_name(version_to_name(0));
  lccr.put_name(lccr_name, false, false);
  lccr_jims.put_name(lccr_name + "_jims", false, false);

  // Attach the jims subposet to the coarsest common refinement jims.
  // poset_state_handle::jims() is reference to state_obj()->powerset_state()->jims(),
  // but can't use it until the latter is attached to a state.

  powerset().jims().attach_to_state(&lccr_jims);

  // Attach the whole subposet to the coarsest common refinement.
  // poset_state_handle::whole() is reference to state_obj()->powerset_state()->whole(),
  // but can't use it until the latter is attached to a state.

  powerset().whole().attach_to_state(&lccr);

  // Allocate the resident subposet, becomes member 2

  resident().new_state(this, true, false);
  resident().put_name("resident", true, false);

  // All the subposets are standard.

  put_standard_subposet_ct(subposet_ct());

  // Now the powerset() invariant is satisfied

  powerset().enable_invariant_check();

  // Postconditions:

  ensure(powerset().invariant());
  ensure(jims().is_attached() && jims().index() == JIMS_INDEX);
  ensure(whole().is_attached() && whole().index() == WHOLE_INDEX);
  ensure(resident().is_attached() && resident().index() == RESIDENT_INDEX);
  ensure(has_standard_subposet_ct());

  // Exit

  return;
}

void
sheaf::poset_state_handle::
put_standard_subposet_ct(int xct)
{
  powerset().put_standard_subposet_ct(xct);
}

// PRIVATE FUNCTIONS


// ===========================================================
// SUBPOSET NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

std::string
sheaf::poset_state_handle::
subposet_name(pod_index_type xsubposet_hub_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

//   cout << "poset_state_handle::subposet_name: poset " << name() << endl;
//   cout << powerset() << endl;
//   cout << "  subposet namemap:" << endl;
//   cout << powerset().subposet_name_map() << endl;
  
  string result(powerset().subposet_name_map().name(xsubposet_hub_id));

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

std::string
sheaf::poset_state_handle::
subposet_name(const scoped_index& xsubposet_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  return subposet_name(xsubposet_id.hub_pod(), xauto_access);
}

void
sheaf::poset_state_handle::
all_subposet_names(pod_index_type xsubposet_hub_id,
                   block<std::string>& xresult,
                   bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(includes_subposet(xsubposet_hub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  powerset().subposet_name_map().all_names(xsubposet_hub_id, xresult);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(xresult.ct() == subposet_name_ct(xsubposet_hub_id, xauto_access));
  ensure_for_all(i, 0, xresult.ct(), subposet_has_name(xsubposet_hub_id, xresult[i], xauto_access));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
all_subposet_names(const scoped_index& xsubposet_id,
                   block<std::string>& xresult,
                   bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(includes_subposet(xsubposet_id, xauto_access));

  // Body:

  all_subposet_names(xsubposet_id.hub_pod(), xresult, xauto_access);

  // Postconditions:

  ensure(xresult.ct() == subposet_name_ct(xsubposet_id, xauto_access));
  ensure_for_all(i, 0, xresult.ct(), subposet_has_name(xsubposet_id, xresult[i], xauto_access));

  // Exit:

  return;
}

sheaf::size_type
sheaf::poset_state_handle::
subposet_name_ct(pod_index_type xsubposet_hub_id, bool xauto_access) const
{
  size_type result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(includes_subposet(xsubposet_hub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = powerset().subposet_name_map().name_ct(xsubposet_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::poset_state_handle::
subposet_name_ct(const scoped_index& xsubposet_id, bool xauto_access) const
{
  size_type result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(includes_subposet(xsubposet_id, xauto_access));

  // Body:

  return subposet_name_ct(xsubposet_id.hub_pod(), xauto_access);
}

bool
sheaf::poset_state_handle::
subposet_has_name(pod_index_type xsubposet_hub_id,
                  const std::string& xname,
                  bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(!xname.empty());
  require(includes_subposet(xsubposet_hub_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result =
    powerset().subposet_name_map().contains_entry(xsubposet_hub_id, xname);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
subposet_has_name(const scoped_index& xsubposet_id,
                  const std::string& xname,
                  bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!xname.empty());
  require(includes_subposet(xsubposet_id, xauto_access));

  // Body:

  return subposet_has_name(xsubposet_id.hub_pod(), xname, xauto_access);
}

void
sheaf::poset_state_handle::
put_subposet_name(pod_index_type xsubposet_hub_id,
                  const std::string& xname,
                  bool xunique,
                  bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(includes_subposet(xsubposet_hub_id, xauto_access));
  require(poset_path::is_valid_name(xname));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  powerset().subposet_name_map().put_entry(xsubposet_hub_id, xname, xunique);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition:

  ensure(xunique ?
         (subposet_name(xsubposet_hub_id, xauto_access) == xname) :
         subposet_has_name(xsubposet_hub_id, xname, xauto_access));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
put_subposet_name(const scoped_index& xsubposet_id,
                  const std::string& xname,
                  bool xunique,
                  bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(includes_subposet(xsubposet_id, xauto_access));
  require(poset_path::is_valid_name(xname));

  // Body:

  put_subposet_name(xsubposet_id.hub_pod(), xname, xunique, xauto_access);

  // Postcondition:

  ensure(xunique ?
         (subposet_name(xsubposet_id, xauto_access) == xname) :
         subposet_has_name(xsubposet_id, xname, xauto_access));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
delete_subposet_name(const std::string& xname, bool xauto_access)
{
  // Preconditions:

  require(!xname.empty());
  require(state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  powerset().subposet_name_map().delete_name(xname);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition

  ensure(!includes_subposet(xname, xauto_access));

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_all_subposet_names(pod_index_type xsubposet_hub_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  powerset().subposet_name_map().delete_index(xsubposet_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postcondition

  ensure(subposet_name_ct(xsubposet_hub_id, xauto_access) == 0);

  // Exit:

  return;
}

void
sheaf::poset_state_handle::
delete_all_subposet_names(const scoped_index& xsubposet_id, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());

  // Body:

  delete_all_subposet_names(xsubposet_id.hub_pod(), xauto_access);

  // Postcondition

  ensure(subposet_name_ct(xsubposet_id, xauto_access) == 0);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// SUBPOSET ID SPACE FAMILY FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::index_space_family&
sheaf::poset_state_handle::
subposet_id_spaces(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const index_space_family& result = powerset()._id_spaces;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::poset_state_handle::
subposet_id_spaces(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  index_space_family& result = powerset()._id_spaces;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::poset_state_handle::
subposet_hub_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const hub_index_space_handle& result = powerset().id_spaces().hub_id_space();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::scoped_index&
sheaf::poset_state_handle::
subposet_id(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const scoped_index& result = powerset().hub_id();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.same_scope(subposet_hub_id_space(xauto_access)));

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_state_handle::
subposet_id(pod_index_type xid, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  scoped_index result(subposet_id(false));
  result = xid;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.same_scope(subposet_hub_id_space(xauto_access)));
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::schema_poset_member&
sheaf::poset_state_handle::
schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  schema_poset_member& result = table().schema();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::schema_poset_member&
sheaf::poset_state_handle::
schema() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const schema_poset_member& result = table().schema();

  // Postconditions:

  // Exit

  return result;
}

sheaf::schema_poset_member&
sheaf::poset_state_handle::
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

  // Exit

  return result;
}

const sheaf::schema_poset_member&
sheaf::poset_state_handle::
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

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
schema_is_ancestor_of(const schema_poset_member* xother_schema) const
{
  bool result;

  // Preconditions:

  // Body:

  // Always true in this class;
  // intended for redefinition in descendants.

  result = true;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
schema_is(const std::string& xschema_name) const
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
sheaf::poset_state_handle::
same_schema(const poset_state_handle* xother) const
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

bool
sheaf::poset_state_handle::
same_schema(const abstract_poset_member* xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());


  // Body:

  result = same_schema(xother->host());

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// TABLE DOF FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS
 

bool
sheaf::poset_state_handle::
table_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // Table dofs must be an array_poset_dof_map.

  result = (dynamic_cast<const array_poset_dof_map*>(xdof_map) != 0);

  // Postconditions:

  ensure(result == (dynamic_cast<const array_poset_dof_map*>(xdof_map) != 0));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
row_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  /// @issue This routine tests only for covariant conformance.
  /// So an instance of section_dof_map will pass this test because section_dof_map
  /// inherits poset_dof_map. However, section_dof_map does not really functionally
  /// conform to poset_dof_map currently because some member functions
  /// are unimplemented. So passing this test doesn't really ensure the dof map
  /// will work in this poset.

  /// @error dof map schema must conform to poset schema as well.
  /// @todo add schema conformance test.

  // In principle any dof map will do.

  result = true;

  // Postconditions:

  ensure(result ? (dynamic_cast<const poset_dof_map*>(xdof_map) != 0) : true);

  // Exit

  return result;
}

sheaf::array_poset_dof_map&
sheaf::poset_state_handle::
table_dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return *(table().table_dofs());
}

const sheaf::array_poset_dof_map&
sheaf::poset_state_handle::
table_dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());

  // Body:

  // Postconditions:

  // Exit

  return *(table().table_dofs());
}

void
sheaf::poset_state_handle::
table_dof_tuple(void* xbuf, size_t xbuflen) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().table_dof_tuple_ub() > 0);
  require(xbuflen >= schema().table_dof_tuple_ub());

  // Body:

  table_dof_map().get_dof_tuple(xbuf, xbuflen);

  // Postconditions:

  // Exit

  return;
}

void*
sheaf::poset_state_handle::
table_dofs()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  
  // Body:

  void* result = table_dof_map(true).dof_tuple();

  // Postconditions:

  // Exit:

  return result;
}

const void*
sheaf::poset_state_handle::
table_dofs() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  const void* result = table_dof_map(false).dof_tuple();

  // Postconditions:

  // Exit:

  return result;
}

void*
sheaf::poset_state_handle::
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
sheaf::poset_state_handle::
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

sheaf::poset_dof_map&
sheaf::poset_state_handle::
row_dof_map(pod_index_type xtuple_hub_id, bool xrequire_write_access) const
{
  poset_dof_map* result_ptr;

  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_row_dof_tuple(xtuple_hub_id));

  // Body:

  result_ptr = table().row_dof_tuple(xtuple_hub_id);

  // Postconditions:

  // Exit

  return *result_ptr;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::poset_table_state&
sheaf::poset_state_handle::
table() const
{
  return *(state_obj()->table());
}

void
sheaf::poset_state_handle::
initialize_table_dofs(void* xtable_dofs, size_t xtable_dof_ub)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require(xtable_dofs != 0 ? xtable_dof_ub >= schema().table_dof_tuple_ub() : true);


  // Body:

  array_poset_dof_map* lmap = new array_poset_dof_map(this, true);
  lmap->inc_ref_ct();

  if((xtable_dofs != 0) && (lmap->dof_ct() > 0))
  {
    lmap->put_dof_tuple(xtable_dofs, schema().table_dof_tuple_ub());
  }
  table().put_table_dofs(lmap);

  // Postconditions:

  ensure(table().table_dofs() != 0);

  // Exit

  return;
}

void
sheaf::poset_state_handle::
initialize_table_dof_tuple(array_poset_dof_map* xdof_tuple)
{

  // Preconditions:

  require(xdof_tuple != 0);
  require(state_is_read_write_accessible());

  // Body:

  xdof_tuple->put_host(this);
  xdof_tuple->inc_ref_ct();
  table().put_table_dofs(xdof_tuple);

  // Postconditions:

  ensure(&(table_dof_map()) == xdof_tuple);

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// ROW DOF FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS
 
sheaf::poset_dof_map&
sheaf::poset_state_handle::
row_dof_map(const scoped_index& xtuple_id, bool xrequire_write_access) const
{
  poset_dof_map* result_ptr;

  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_row_dof_tuple(xtuple_id));

  // Body:

  return row_dof_map(xtuple_id.hub_pod(), xrequire_write_access);
}

const sheaf::scoped_index&
sheaf::poset_state_handle::
new_row_dof_map()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  // Create a new dof map using contiguous array rep

  poset_dof_map* lmap = new array_poset_dof_map(this, false);
  lmap->put_defaults();
  table().put_row_dof_tuple(lmap);
  const scoped_index& result = lmap->index();

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::poset_state_handle::
clone_row_dof_map(const poset_dof_map& xprototype)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(row_dof_map_conforms(&xprototype));
  require(xprototype.schema().row_conforms_to(schema()));

  // Body:

  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  // Create a new dof map by copying the given prototype.

  poset_dof_map* lmap = xprototype.copy();
  lmap->put_host(this);
  table().put_row_dof_tuple(lmap);
  const scoped_index& result = lmap->index(); // Set by put_row_dof_tuple.

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit

  return result;
}

sheaf::poset_dof_map&
sheaf::poset_state_handle::
member_dof_map(pod_index_type xmbr_hub_id, bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(is_jim(xmbr_hub_id, false));

  // Body:

  poset_dof_map& result =
    row_dof_map(member_dof_tuple_id(xmbr_hub_id, false), xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_dof_map&
sheaf::poset_state_handle::
member_dof_map(const scoped_index& xmbr_id, bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_id, false));
  require(is_jim(xmbr_id, false));

  // Body:

  return member_dof_map(xmbr_id.hub_pod(), xrequire_write_access);
}

const sheaf::poset_dof_map&
sheaf::poset_state_handle::
member_dof_map(pod_index_type xmbr_hub_id, bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_hub_id, false));
  require(is_jim(xmbr_hub_id, false));

  // Body:

  poset_dof_map& result =
    row_dof_map(member_dof_tuple_id(xmbr_hub_id, false), xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::poset_dof_map&
sheaf::poset_state_handle::
member_dof_map(const scoped_index& xmbr_id, bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_member(xmbr_id, false));
  require(is_jim(xmbr_id, false));

  // Body:

  return member_dof_map(xmbr_id.hub_pod(), xrequire_write_access);
}

void
sheaf::poset_state_handle::
member_dof_tuple(pod_index_type xmbr_hub_id, void* xbuf, size_t xbuflen, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, xauto_access));
  require(unexecutable("xbuf points to a buffer of length xbuflen"));
  require(xbuflen >= member_dof_map(xmbr_hub_id, false).dof_tuple_ub());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  member_dof_map(xmbr_hub_id, false).get_dof_tuple(xbuf, xbuflen);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return;
}

void
sheaf::poset_state_handle::
put_member_dof_tuple(pod_index_type xmbr_hub_id, void* xbuf, size_t xbuflen, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, xauto_access));
  require(unexecutable("xbuf points to a buffer of length xbuflen"));
  require(xbuflen >= member_dof_map(xmbr_hub_id, true).dof_tuple_ub());

  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  member_dof_map(xmbr_hub_id, true).put_dof_tuple(xbuf, xbuflen);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
member_dof_tuple_id(pod_index_type xmbr_hub_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, false));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type result = crg().member_dof_tuple_id(xmbr_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_row_dof_tuple(result));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
member_dof_tuple_id(const scoped_index& xmbr_id,
		    scoped_index& result,
		    bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, false));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result.put(dof_tuple_hub_id_space(false),
	     member_dof_tuple_id(xmbr_id.hub_pod(), false));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.is_valid() || contains_row_dof_tuple(result));

  // Exit

  return;
}

void
sheaf::poset_state_handle::
put_member_dof_tuple_id(pod_index_type xmbr_hub_id,
			pod_index_type xtuple_hub_id,
			bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_hub_id, false));
  require(contains_row_dof_tuple(xtuple_hub_id) || !is_valid(xtuple_hub_id));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  crg().put_member_dof_tuple_id(xmbr_hub_id, xtuple_hub_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(member_dof_tuple_id(xmbr_hub_id, xauto_access) == xtuple_hub_id);

  // Exit

  return;
}

void
sheaf::poset_state_handle::
put_member_dof_tuple_id(const scoped_index& xmbr_id,
			const scoped_index& xtuple_id,
			bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, false));
  require(contains_row_dof_tuple(xtuple_id) || !xtuple_id.is_valid());

  // Body:

  put_member_dof_tuple_id(xmbr_id.hub_pod(),
			  xtuple_id.hub_pod(),
			  xauto_access);

  // Postconditions:

  ensure(member_dof_tuple_id(xmbr_id.hub_pod(), xauto_access) == xtuple_id.hub_pod());

  // Exit

  return;
}

bool
sheaf::poset_state_handle::
contains_row_dof_tuple(pod_index_type xtuple_hub_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = table().contains_row_dof_tuple(xtuple_hub_id);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
contains_row_dof_tuple(const scoped_index& xtuple_id) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return contains_row_dof_tuple(xtuple_id.hub_pod());
}

sheaf::size_type
sheaf::poset_state_handle::
row_dof_tuple_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = table().row_dof_tuple_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

int
sheaf::poset_state_handle::
standard_row_dof_tuple_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = table().standard_row_dof_tuple_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
has_standard_row_dof_tuple_ct() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = (row_dof_tuple_ct() == standard_row_dof_tuple_ct());

  // Postconditions:

  ensure(result == (row_dof_tuple_ct() == standard_row_dof_tuple_ct()));

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// DOF TUPLE ID SPACE FAMILY FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::index_space_family&
sheaf::poset_state_handle::
dof_tuple_id_spaces(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const index_space_family& result = table()._id_spaces;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::poset_state_handle::
dof_tuple_id_spaces(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  index_space_family& result = table()._id_spaces;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::poset_state_handle::
dof_tuple_hub_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const hub_index_space_handle& result = table().id_spaces().hub_id_space();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::scoped_index&
sheaf::poset_state_handle::
dof_tuple_id(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const scoped_index& result = table().hub_id();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.same_scope(dof_tuple_hub_id_space(xauto_access)));

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_state_handle::
dof_tuple_id(pod_index_type xid, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  scoped_index result(dof_tuple_id(false));
  result = xid;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.same_scope(dof_tuple_hub_id_space(xauto_access)));
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMATIZATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::poset_state_handle::
is_schematized(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = includes_subposet(schema_poset_member::table_dof_subposet_name("top")) &&
           includes_subposet(schema_poset_member::row_dof_subposet_name("top"));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  /// @todo make the following executable.

  ensure(unexecutable(result == top member has been schematized));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
schematize(subposet* xtable_dof_subposet,
           subposet* xrow_dof_subposet,
           bool xall_members)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(xtable_dof_subposet != 0);
  require(includes_subposet(xtable_dof_subposet));
  require(xrow_dof_subposet != 0);
  require(includes_subposet(xrow_dof_subposet));

  // Body:

  string ltop_table_dof_sp_name(schema_poset_member::table_dof_subposet_name("top"));
  if(xtable_dof_subposet->name() != ltop_table_dof_sp_name)
  {
    xtable_dof_subposet->put_name(ltop_table_dof_sp_name, true, false);
  }
  table_dof_subposet().attach_to_state(xtable_dof_subposet, false);

  if(!table_dof_subposet().has_id_space())
  {
    initialize_dof_id_space(table_dof_subposet());
  }
  
  string ltop_row_dof_sp_name(schema_poset_member::row_dof_subposet_name("top"));
  if(xrow_dof_subposet->name() != ltop_row_dof_sp_name)
  {
    xrow_dof_subposet->put_name(ltop_row_dof_sp_name, true, false);
  }
  row_dof_subposet().attach_to_state(xrow_dof_subposet, false);

  if(!row_dof_subposet().has_id_space())
  {
    initialize_dof_id_space(row_dof_subposet());
  }
  
  // Postconditions:

  ensure(is_schematized(false));

  // Exit

  return;
}

// PROTECTED FUNCTIONS

void
sheaf::poset_state_handle::
initialize_dof_id_space(subposet& xdof_subposet)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  xdof_subposet.put_is_persistent(true);
  if(member_id_spaces(false).contains(xdof_subposet.id_space_name()))
  {
    xdof_subposet.attach_id_space();
  }
  else
  {
    xdof_subposet.new_id_space("array_index_space_state");

    scattered_insertion_index_space_handle& ldof_id_space = xdof_subposet.id_space();

    index_iterator ldof_itr = xdof_subposet.indexed_member_iterator();
    while(!ldof_itr.is_done())
    {
      ldof_id_space.push_back(ldof_itr.index());
      
      ldof_itr.next();
    }
  }

  // Postconditions:

  ensure(xdof_subposet.has_id_space());

  // Exit:

  return;
}

// PRIVATE FUNCTIONS




// ===========================================================
// VERSION FACET
// ===========================================================

// PUBLIC FUNCTIONS

int
sheaf::poset_state_handle::
version_ct() const
{
  int result = 0;

  // Preconditions:

  // Body:

  /// @hack this implementation avoids the need to
  /// modify poset_state or introduce table dofs, but it is slow.
  /// @todo find some more efficient implementation.

//   subposet sp;

//   index_iterator itr = subposet_iterator();
//   while(!itr.is_done())
//   {
//     sp.attach_to_state(this, itr.index());

//     // Count all subposets with names beginning with "__version_".

//     if(is_version_name(sp.name()))
//     {
//       result++;
//     }

//     itr.next();
//   }
//   sp.detach_from_state();


  typedef poset_powerset_state::subposet_name_map_type name_map_type;
  typedef name_map_type::const_iterator name_map_itr_type;
  typedef name_map_type::const_name_iterator name_itr_type;  
  
  for(name_map_itr_type lmap_itr = powerset().subposet_name_map().begin();
      lmap_itr != powerset().subposet_name_map().end();
      ++lmap_itr)
  {
    for(name_itr_type lname_itr = lmap_itr->second.begin();
	lname_itr != lmap_itr->second.end();
	++lname_itr)
    {
      if(is_version_name(*lname_itr))
      {
	result++;
      }
    }
  }

  // Have now double counted the levels, because each
  // level has a whole subposet and a jims subposet.

  assertion(result % 2 == 0);

  result = result/2;

  // Have also counted

  ensure(result >= 0);

  // Exit

  return result;
}

int
sheaf::poset_state_handle::
version() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = version_from_name(whole().name());

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
version_index(int xversion) const
{
  pod_index_type result;

  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  if(xversion == CURRENT_HOST_VERSION)
  {
    result = WHOLE_INDEX;
  }
  else
  {
    string lvl_name = version_to_name(xversion);
    result = subposet_id(lvl_name);
  }

  // Postconditions:

  ensure(includes_subposet(result, false));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
version_index(int xversion, scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  result.put(subposet_hub_id_space(false), version_index(xversion));

  // Postconditions:

  ensure(includes_subposet(result, false));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
version_jims_index(int xversion) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  string lvl_name = version_to_name(xversion);
  lvl_name += "_jims";
  pod_index_type result = subposet_id(lvl_name);

  // Postconditions:

  ensure(includes_subposet(result));

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
version_jims_index(int xversion, scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  result.put(subposet_hub_id_space(false), version_jims_index(xversion));

  // Postconditions:

  ensure(includes_subposet(result));

  // Exit

  return;
}

bool
sheaf::poset_state_handle::
has_version( int xversion ) const
{
  bool result;

  // Preconditions:

  // Body:

  result = ( (xversion == CURRENT_HOST_VERSION) ||
             ( (0 <= xversion) && (xversion < version_ct()) )    ||
             (xversion == COARSEST_COMMON_REFINEMENT_VERSION) );

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
is_version() const
{
  bool result;

  // Preconditions:

  // Body:

  result = version() != COARSEST_COMMON_REFINEMENT_VERSION;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

const std::string&
sheaf::poset_state_handle::
VERSION_PREFIX()
{
  static const string result("__version_");
  return result;
}

int
sheaf::poset_state_handle::
VERSION_PREFIX_LENGTH()
{
  static const int result = VERSION_PREFIX().size();
  return result;
}

bool
sheaf::poset_state_handle::
is_version_name(const std::string& xname) const
{
  bool result;

  // Preconditions:

  // Body:

  // Coarsest_common_refinement has same name as this.
  // Other version names have form "__version_n";
  // number n begins at character position 10.

  result = (xname.substr(0, VERSION_PREFIX_LENGTH()) == VERSION_PREFIX());

  // Postconditions:

  // Exit

  return result;
}

std::string
sheaf::poset_state_handle::
version_to_name(int xversion) const
{
  string result;

  // Preconditions:

  // Body:

  if(xversion == COARSEST_COMMON_REFINEMENT_VERSION)
  {
    result = coarsest_common_refinement_name();
  }
  else
  {
    stringstream str;
    str << VERSION_PREFIX() << xversion;
    str >> result;
  }

  // Postconditions:

  ensure(!result.empty());
  ensure(xversion == COARSEST_COMMON_REFINEMENT_VERSION ? (result == coarsest_common_refinement_name()) : is_version_name(result));

  // Exit

  return result;
}

int
sheaf::poset_state_handle::
version_from_name(const std::string& xname) const
{
  int result;

  // Preconditions:

  require(is_version_name(xname) || xname == coarsest_common_refinement_name());

  // Body:

  /// @todo replace poset name == whole name with something more reasonable!

  if(xname == coarsest_common_refinement_name())
  {
    // Result is coarsest common refinement.

    result = COARSEST_COMMON_REFINEMENT_VERSION;
  }
  else
  {
    // Name of subposet whole() is of form "__version_n";
    // number n begins at c_str[10].

    result = atoi(xname.c_str()+VERSION_PREFIX_LENGTH());
  }

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_state_handle::
put_version(int xversion)
{
  // Preconditions:

  require( has_version(xversion) );

  // Body:

  // The version of a poset is defined by the subposet state that
  // whole() is attached to. So attaching whole() to a new state changes
  // the version. This conflicts with the polcy for managing the version
  // data member in poset_component and leads to a postcondition violation
  // in certain of the attach functions, so we have to use attach_to_state(xindex)
  // and update the version data member in the handle directly.

  if(xversion == COARSEST_COMMON_REFINEMENT_VERSION)
  {
    // Select the coarsest common refinement.

    powerset().whole().attach_to_state(WHOLE_INDEX);
    jims().attach_to_state(JIMS_INDEX);
  }
  else
  {
    // Select version xversion

    // Attach the whole subposet to the new level

    string lname = version_to_name(xversion);
    pod_index_type lid = subposet_id(lname);
    powerset().whole().attach_to_state(lid);

    // Attach the jims subposet to the new level

    lname += "_jims";
    lid = subposet_id(lname);
    jims().attach_to_state(lid);
  }

  // For whole() and jims() the version should always
  // be the alias CURRENT_HOST_VERSION.
  // poset_component::attach_to_state(xindex) ensures that it does not
  // change version(), but there's no way to ensure the client hasn't
  // changed it. So force it just to be sure.

  powerset().whole().put_version(CURRENT_HOST_VERSION);
  jims().put_version(CURRENT_HOST_VERSION);

  // Postconditions:

  ensure(version() == xversion);

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::schema_poset_member*
sheaf::poset_state_handle::
new_schema_handle(const std::string& xid_space_name,
                  pod_index_type xschema_member_ext_id,
                  pod_index_type xbase_space_ext_id,
                  pod_index_type xfiber_schema_ext_id,
                  pod_index_type xlocal_schema_ext_id)
{

  /// @hack this function should be const, but descendants call
  /// mmber functions that are not currently const.

  // Preconditions:

  // Body:

  // Create a handle of the type appropriate for members of this
  // which will be used as a schema.

  schema_poset_member* result = new schema_poset_member();

  // Get the internal id for the schema member.

  pod_index_type lint_id =
    get_int_id(xschema_member_ext_id, xid_space_name, false);

  // Attach the handle.

  result->attach_to_state(this, lint_id);

  // Postconditions:

  ensure(result != 0);
  ensure(schema_is_ancestor_of(result));
  ensure(result->is_attached());

  // Exit

  return result;
}

sheaf::index_iterator*
sheaf::poset_state_handle::
get_decomposition(pod_index_type xindex) const
{
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.

  // Preconditions:

  require(state_is_read_accessible());
  require(includes_subposet(xindex));

  // Body:

  subposet ldecomp_sp(this, xindex);
  index_iterator* result =
    new index_iterator(ldecomp_sp.members(), ldecomp_sp.id_space(), false);
  ldecomp_sp.detach_from_state();

  // Postconditions:


  // Exit:

  return result;
}

sheaf::index_iterator*
sheaf::poset_state_handle::
bound_iterator(const poset_bounds& xbounds, bool xis_ub) const
{
  index_iterator* result;
  
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  pod_index_type lbnd_id;
  bool lsingleton;

  if(xis_ub)
  {
    lbnd_id = xbounds.ub_id();
    lsingleton = xbounds.ub_is_singleton();
  }
  else
  {
    lbnd_id = xbounds.lb_id();
    lsingleton = xbounds.lb_is_singleton();
  }

  if(lsingleton)  
  {
    zn_to_bool* l_lb = new zn_to_bool();
    l_lb->force(lbnd_id, true);
    result = new index_iterator(l_lb, member_hub_id_space(false), true);
  }
  else
  {
    result = get_decomposition(lbnd_id);
  }

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
bound_contains_member(const poset_bounds& xbounds,
		      bool xis_ub,
		      const scoped_index& xindex) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xis_ub ?
	  xbounds.descriptor().ub_is_valid_for(*this) :
	  xbounds.descriptor().lb_is_valid_for(*this));
  require(contains_member(xindex, false));

  // Body:

  pod_index_type lbnd_id;
  bool lsingleton;

  if(xis_ub)
  {
    lbnd_id = xbounds.ub_id();
    lsingleton = xbounds.ub_is_singleton();
  }
  else
  {
    lbnd_id = xbounds.lb_id();
    lsingleton = xbounds.lb_is_singleton();
  }

  if(lsingleton)
  {
    result = (xindex == lbnd_id);
  }
  else
  {
    result = powerset().subposet_contains_member(lbnd_id, xindex.hub_pod());
  }
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
get_int_id(pod_index_type xext_id,
           const std::string& xid_space_name,
           bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(xext_id >= standard_member_ct() ?
          member_id_spaces(false).contains(xid_space_name) : true);
  require(xext_id >= standard_member_ct() ?
	  member_id_spaces(false).contains(xid_space_name, xext_id) : true);


  // Body:

  pod_index_type result;

  if(xext_id < standard_member_ct())
  {
    // Xext_id is standard member;
    // internal id is same as external id.

    result = xext_id;
  }
  else
  {
    // Get internal id from map.

    result = member_id_spaces(false).hub_pod(xid_space_name, xext_id);
  }

  // Postconditions:

  ensure(contains_member(result, false));

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
is_valid_int_id(pod_index_type xint_id,
		const std::string& xid_space_name,
		bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  bool result = true;

  if(xint_id >= standard_member_ct())
  {
    result = member_id_spaces(false).contains(xid_space_name);
    if(result)
    {
      result = member_id_spaces(false).contains_hub(xid_space_name, xint_id);
    }
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_state_handle::
is_valid_int_id(const scoped_index& xint_id,
		const std::string& xid_space_name,
		bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  return is_valid_int_id(xint_id.hub_pod(), xid_space_name, xauto_access);
}

sheaf::pod_index_type
sheaf::poset_state_handle::
get_ext_id(pod_index_type xint_id,
           const std::string& xid_space_name,
           bool xauto_access) const
{
  pod_index_type result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(is_valid_int_id(xint_id, xid_space_name, xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  if(xint_id < standard_member_ct())
  {
    // Xint_id is standard member;
    // external id is same as internal id.

    result = xint_id;
  }
  else
  {
    // Get external id from map.

    result = member_id_spaces(false).pod(xid_space_name, xint_id);
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
get_ext_id(const scoped_index& xint_id,
           const std::string& xid_space_name,
           bool xauto_access) const
{
  pod_index_type result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(is_valid_int_id(xint_id, xid_space_name, xauto_access));

  // Body:

  result = get_ext_id(xint_id.hub_pod(), xid_space_name, xauto_access);
  
  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_state_handle::
prereq_id(int xi) const
{
  pod_index_type result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  switch(xi)
  {
  case 0:
    result = schema().host()->index().pod();
    break;
  default:
    result = invalid_pod_index();
    break;
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC FUNCTIONS

void
sheaf::poset_state_handle::
to_stream(std::ostream& xos)
{
  xos << *this;
}

std::string
sheaf::poset_state_handle::
to_string()
{
  std::ostringstream oss;
  oss << *this;
  return oss.str();
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::poset_state_handle::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_state_handle*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_state_handle*
sheaf::poset_state_handle::
clone() const
{
  poset_state_handle* result;

  // Preconditions:

  // Body:

  result = new poset_state_handle;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit

  return result;
}

bool
sheaf::poset_state_handle::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    disable_invariant_check();


    // Invariants of namespace features

    invariance( !index().is_valid() == (name_space() == 0) );
    invariance( name_space() != 0 ? name_space()->contains_member(index()) : true );

    // Invariants of row structure

    // @issue instances of this class satisfy a stronger invariant than
    // instances of its descendants.

    // @todo modify the taxonomy to properly represent the invariants.
    // invariance(jims().is_attached() && (jims().index() == JIMS_INDEX));
    // invariance(whole().is_attached() && (whole().index() == WHOLE_INDEX));

    invariance(state_is_read_accessible() ? jims().is_attached() : true);
    invariance(state_is_read_accessible() ? whole().is_attached() : true);
    invariance(state_is_read_accessible() ?
               (resident().is_attached() && (resident().index() == RESIDENT_INDEX)) :
               true);
    invariance(state_is_read_accessible() ?
               (top().is_attached() && (top().index() == TOP_INDEX)) :
               true);
    invariance(state_is_read_accessible() ?
               (bottom().is_attached() && (bottom().index() == BOTTOM_INDEX)) :
               true);

    // @todo implement resident applies to dof tuple and hence only to jims
    // for all members: not is jim implies not resident

    // Invariants of column structure

    invariance(state_is_read_accessible() ?
               schema_is_ancestor_of(&(table().schema())) :
               true);
    invariance(state_is_read_accessible() ? schema().state_is_read_accessible() : true);

    // @todo implement column poset must use primitives_poset_dof_map dof maps
    // also: schema of schema is primitives schema

    // @todo propagate index_space_family invariants to here.

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream & 
sheaf::
operator<<(std::ostream &os, const poset_state_handle& p)
{
  // Preconditions:

  // Library policy requires that access requirements be published
  // as preconditions and client is responsible for ensuring them.
  // But in practice, this routine is used mostly for debugging,
  // and forcing the client to get the access is an frustrating
  // and unnecessary burden. what we need is an auto-access mechanism,
  // but it's not clear how to implement it. Perhaps some sort of
  // client-defined manipulator would work. In the mean time, just
  // just get the required access.


  //   require(p.state_is_read_accessible());
  //   require(p.host() == 0 || p.host()->state_is_read_accessible());

  p.get_read_access();
  if(p.host() != 0)
  {
    p.host()->get_read_access();
  }


  // Body:

  // Print header line.

  os << endl
  << endl
  << "#### BEGIN POSET " << p.name() << " ###################"
  << endl
  << endl;

  // Print general info.

  os << "GENERAL" << endl
  << "-------" << endl
  << endl;

  os << "poset: '" << p.name() << "'"
  << " \thost: '" << (p.host() != 0 ? p.host()->name() : "<void>") << "'"
  << " \tindex: " << p.index().hub_pod()
  << " \tversion: " << p.version()
  << endl
  << endl;

  // Print row lattice info.

  os << p.crg() << endl;

  // Print powerset info.

  os << p.powerset() << endl;

  // Print table info.

  os << p.table() << endl;

  // Print footer line.

  os << endl
  << "#### END POSET " << p.name() << " ###################" << endl;


  p.release_access();
  if(p.host() != 0)
  {
    p.host()->release_access();
  }

  // Postconditions:

  // Exit

  return os;
}

size_t
sheaf::
deep_size(const poset_state_handle& xp, bool xinclude_shallow, size_t xresults[4])
{
  size_t result;

  // Preconditions:

  require(xp.state_is_read_accessible());

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Calculate the deep_size of data member: poset_state* _state.

  result += deep_size(*xp._state, true, xresults);

  // Add contribution from _top.

  result += deep_size(*xp._top, true);

  // Add contribution from _bottom.

  result += deep_size(*xp._bottom, true);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

