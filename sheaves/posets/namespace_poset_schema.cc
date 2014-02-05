
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
/// Implementation for class namespace_poset_schema

#include "namespace_poset_schema.h"

#include "assert_contract.h"
#include "array_poset_dof_map.h"
#include "namespace_poset.impl.h"
#include "poset_handle_factory.h"
#include "poset_type.h"
#include "primitives_poset_dof_map.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "total_poset_member.h"
#include "tern.h"

// ===========================================================
// NAMESPACE_POSET_SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

const std::string&
sheaf::namespace_poset_schema::
standard_name()
{
  // Preconditions:

  // Body:

  static const std::string result("namespace_poset_schema");

  // Postconditions:

  ensure(result == "namespace_poset_schema");

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

sheaf::namespace_poset_schema::
namespace_poset_schema()
{
  // Preconditions:

  // Body:

  // Nothing to do; poset_state_handle constructor
  // does what needs to be done

  // Postconditions:

  ensure(!is_attached());

  return;
}

sheaf::namespace_poset_schema::
namespace_poset_schema(abstract_poset_member* xschema, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new state(same args)));

  // Body:

  new_state(xschema, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit:

  return;
}

sheaf::namespace_poset_schema::
~namespace_poset_schema()
{

  // Preconditions:

  // Body:

  // Deleted by namespace_poset destructor; nothing to do.

  // Exit

  return;
}

bool
sheaf::namespace_poset_schema::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  poset_type ltype = NAMESPACE_POSET_SCHEMA_ID;

  namespace_poset_schema* lproto = new namespace_poset_schema;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}


// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
sheaf::namespace_poset_schema::
type_id() const
{
  return NAMESPACE_POSET_SCHEMA_ID;
}

const char*
sheaf::namespace_poset_schema::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "namespace_poset_schema";

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset_schema::
row_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // Row dofs must be primitives_poset_dof_map

  result = dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0;

  // Postconditions:

  ensure(result ? (dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0) : true);

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

void
sheaf::namespace_poset_schema::
initialize_standard_members()
{
  // Preconditions:

  // Body:

  // First create the standard members of the base class

  poset_state_handle::initialize_standard_members();

  // All jims will be members of "row_dofs" subposet;
  // there are no table dofs

  // Must be created in order specified by enum namespace_member_index.

  // Enter edit mode

  begin_jim_edit_mode();

  total_poset_member lmbr;
  poset_dof_map* lmap;

  block<scoped_index> lio_dofs(7);

  // Create jim for pointer to member poset.

  lmap = new primitives_poset_dof_map(this, VOID_STAR);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("pointer", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  // Pointer is not included in i/o dofs.

  // Create jim for type id of member poset

  lmap = new primitives_poset_dof_map(this, INT);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("type_id", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jim for class of member poset

  lmap = new primitives_poset_dof_map(this, C_STRING);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("class", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jim for schema poset seq id.

  lmap = new primitives_poset_dof_map(this, INT);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("prereq_id_0", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jim for other prerequisite seq id 1.

  lmap = new primitives_poset_dof_map(this, INT);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("prereq_id_1", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jim for other prerequisite seq id 2.

  lmap = new primitives_poset_dof_map(this, INT);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("prereq_id_2", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jim for other prerequisite seq id 3.

  lmap = new primitives_poset_dof_map(this, INT);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("prereq_id_3", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jim for other prerequisite seq id 4.

  lmap = new primitives_poset_dof_map(this, INT);
  lmbr.new_jim_state(this, lmap, false, false);
  lmbr.put_name("prereq_id_4", true, false);
  _row_dof_subposet->insert_member(&lmbr);
  lio_dofs.push_back(lmbr.index());

  // Create jrm for dofs that get written to file.
  //
  // Manually construct lover cover to ensure order.
  // Join constructor does not ensure any particular order
  // to the lower cover of the join, but the layout of
  // the namespace_poset dof tuple requires the jims
  // of the schema appear in a particular order;
  // see namespace_poset_dof_map.
  //
  /// @hack This isn't strictly necessary, because
  /// the dof id map is supposed to map whatever order
  /// the lower cover is created in to the fixed order
  /// of the top id space, which is consistent with
  /// namespace_poset_dof_map, see abstract_poset_member::make_schema_info.
  /// But update_cache erroneously generates a different order
  /// for the dof descriptors. So until we've fixed that,
  /// the order of the lower cover is critical.

  lmbr.new_jrm_state();
  lmbr.put_name("io", true, false);

  // Manually construct lover cover to ensure order.

  for(int i=0; i<lio_dofs.ct(); ++i)
  {
    new_link(lmbr.index(), lio_dofs[i]);
  }

  // Finished creating jims, exit edit mode

  end_jim_edit_mode();

  // Detach member so state won't be deleted.

  lmbr.detach_from_state();

  // Now there's 11 standard members,
  // top, bottom, pointer, type_id, class, prereq_id_0,1,2,3,4 and io.

  // All the members and row dof tuples are standard.

  put_standard_member_ct(member_ct());
  put_standard_row_dof_tuple_ct(row_dof_tuple_ct());

  // Postconditions:

  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  // Exit:

  return;
}

void
sheaf::namespace_poset_schema::
initialize_standard_subposets(const std::string& xname)
{

  // Preconditions:

  require(poset_path::is_valid_name(xname));
  require(state_is_read_write_accessible());

  // Body:

  // Initialize the subposets common to all posets.

  poset_state_handle::initialize_standard_subposets(xname);

  // Create empty table and row dof subposets;
  // Standard names will be given in member function schematize.

  _table_dof_subposet = new subposet(this);
  _row_dof_subposet   = new subposet(this);

  put_standard_subposet_ct(subposet_ct());

  // Standard subposet count will be reset in new_state
  // after schematizing, since that creates new subposets.

  // Postconditions:

  ensure(has_standard_subposet_ct());

  // Exit:

  return;
}

// PRIVATE FUNCTIONS

void
sheaf::namespace_poset_schema::
new_state(const abstract_poset_member* xschema, bool xauto_access)
{
  // Preconditions:

  require(xschema != 0);
  require(!xauto_access ? xschema->state_is_read_accessible() : true);
  require(dynamic_cast<primitives_poset_schema*>(xschema->host()) != 0);


  // If xauto_access == true we must get read access to the schema before
  // testing host type.

  if(xauto_access)
    xschema->get_read_access();

  require(dynamic_cast<primitives_poset_schema*>
          (xschema->host()) != 0);

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the poset state object.
  // This is a schema poset, so it must have the same
  // schema as the primitives poset.
  // Initial space for 4 members, 8 links, 4 subposets.

  _state = new poset_state(xschema, NAMESPACE_POSET_SCHEMA_ID, standard_name());

  // Get write access

  get_read_write_access();

  // Initialize the table dof map.
  // This class has no table dofs, but we want a non-null dof map anyway.

  initialize_table_dofs(0,0);

  // Initialize additional row structure

  // Create subposets for jims and whole, and schema subposets for top.

  initialize_standard_subposets(standard_name());

  // Create the bottom, top, and jims.

  initialize_standard_members();

  // Now that the standard members have all been inserted in the row dofs,
  // we can initialize the other schema info derived from the dofs subposets

  schematize(_table_dof_subposet, _row_dof_subposet, true);

  // Schematize has created new subposets, reset the standard subposet count.
  // Every subposet is a standard subposet.

  put_standard_subposet_ct(subposet_ct());

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // We won't use the two subposet handles again;
  // detach and delete them

  _table_dof_subposet->detach_from_state();
  delete _table_dof_subposet;
  _table_dof_subposet = 0;

  _row_dof_subposet->detach_from_state();
  delete _row_dof_subposet;
  _row_dof_subposet = 0;

  // Now the invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(!in_jim_edit_mode());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());

  // release thread access to poset state

  release_access();

  // release schema access if auto access was requested

  if(xauto_access)
    xschema->release_access();

  ensure(state_is_not_read_accessible());
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::namespace_poset_schema::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const namespace_poset_schema*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset_schema::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && poset_state_handle::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    if(is_attached())
    {
      /// @todo finish invariant
    }

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

sheaf::namespace_poset_schema*
sheaf::namespace_poset_schema::
clone() const
{
  namespace_poset_schema* result;

  // Preconditions:

  // Body:

  result = new namespace_poset_schema();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


