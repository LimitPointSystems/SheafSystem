
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
/// Implementation for class poset.

#include "abstract_poset_member.h"
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


sheaf::poset&
sheaf::poset::
new_table(namespace_type& xns, const poset_path& xpath, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering poset::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_poset(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef poset table_type;

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

  poset& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true).poset_name() == xpath.poset_name());
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  // Exit:

  // cout << "Leaving poset::new_table." << endl;
  return result;
}


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

// PRIVATE FUNCTIONS

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

  // Create the poset state object;
  // Allocates the data structures but does not (fully) initialize them

  _state = new poset_state(&xschema, type_id(), xpath.poset_name());

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

  initialize_standard_subposets(xpath.poset_name());
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

  initialize_handle_data_members(*xschema.name_space());
  
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

