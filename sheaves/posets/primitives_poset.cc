
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
/// Implementation for class primitives_poset

#include "primitives_poset.h"

#include "assert_contract.h"
#include "array_poset_dof_map.h"
#include "namespace_poset.impl.h"
#include "poset_handle_factory.h"
#include "primitive_attributes.h"
#include "primitives_poset_dof_map.h"
#include "primitives_poset_schema.h"
#include "poset_type.h"
#include "primitive_type.h"
#include "std_iomanip.h"
#include "total_poset_member.h"

using namespace std;

// ===========================================================
// PRIMITIVES_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

const std::string&
sheaf::primitives_poset::
standard_name()
{
  // Preconditions:


  // Body:

  static const string result("primitives");

  // Postconditions:

  ensure(result == "primitives");

  // Exit:

  return result;
}

bool
sheaf::primitives_poset::
primitive_members_attached() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && bool_type().is_attached();
  result = result && (bool_type().index() == BOOL);

  result = result && char_type().is_attached() ;
  result = result && (char_type().index() == CHAR);

  result = result && signed_char_type().is_attached();
  result = result && (signed_char_type().index() == SIGNED_CHAR);

  result = result && short_int_type().is_attached();
  result = result && (short_int_type().index() == SHORT_INT);

  result = result && int_type().is_attached();
  result = result && (int_type().index() == INT);

  result = result && long_int_type().is_attached();
  result = result && (long_int_type().index() == LONG_INT);

  result = result && long_long_int_type().is_attached();
  result = result && (long_long_int_type().index() == LONG_LONG_INT);

  result = result && unsigned_char_type().is_attached();
  result = result && (unsigned_char_type().index() == UNSIGNED_CHAR);

  result = result && unsigned_short_int_type().is_attached();
  result = result && (unsigned_short_int_type().index() == UNSIGNED_SHORT_INT);

  result = result && unsigned_int_type().is_attached();
  result = result && (unsigned_int_type().index() == UNSIGNED_INT);

  result = result && unsigned_long_int_type().is_attached();
  result = result && (unsigned_long_int_type().index() == UNSIGNED_LONG_INT);

  result = result && unsigned_long_long_int_type().is_attached();
  result = result && (unsigned_long_long_int_type().index() == UNSIGNED_LONG_LONG_INT);

  result = result && float_type().is_attached();
  result = result && (float_type().index() == FLOAT);

  result = result && double_type().is_attached();
  result = result && (double_type().index() == DOUBLE);

  result = result && long_double_type().is_attached();
  result = result && (long_double_type().index() == LONG_DOUBLE);

  result = result && void_star_type().is_attached();
  result = result && (void_star_type().index() == VOID_STAR);

  result = result && c_string_type().is_attached();
  result = result && (c_string_type().index() == C_STRING);

  result = result && namespace_relative_member_index_type().is_attached();
  result = result && (namespace_relative_member_index_type().index() == NAMESPACE_RELATIVE_MEMBER_INDEX);

  result = result && namespace_relative_subposet_index_type().is_attached();
  result = result && (namespace_relative_subposet_index_type().index() == NAMESPACE_RELATIVE_SUBPOSET_INDEX);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

sheaf::primitives_poset::
primitives_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do; poset_state_handle constructor
  // does what needs to be done

  // Postconditions:

  ensure(!is_attached());

  return;
}

sheaf::primitives_poset::
~primitives_poset()
{

  // Preconditions:

  // Body:

  // Deleted by namespace destructor; nothing to do.

  // Postconditions:

  // Exit

  return;
}

void
sheaf::primitives_poset::
initialize_primitive_member(total_poset_member& xmbr, primitive_type xtype)
{
  // Preconditions:

  require(!xmbr.is_attached());

  // Body:

  primitives_poset_dof_map* lmap =
    new primitives_poset_dof_map(this, xtype);

  xmbr.new_jim_state(this, lmap, false, false);

  string lname = primitive_attributes::name(xtype);
  xmbr.put_name(lname, true, false);

  _row_dof_subposet->insert_member(&xmbr);

  // Postconditions:

  ensure(xmbr.is_attached());
  ensure(xmbr.index() == xtype);
  ensure(xmbr.name() == primitive_attributes::name(xtype));

  // Exit:

  return;
}

bool
sheaf::primitives_poset::
make_prototype()
{
  // Preconditions:


  // Body:

  poset_type ltype = PRIMITIVES_POSET_ID;

  primitives_poset* lproto = new primitives_poset;

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
sheaf::primitives_poset::
type_id() const
{
  return PRIMITIVES_POSET_ID;
}

const char*
sheaf::primitives_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "primitives_poset";

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::primitives_poset::
row_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // Row dofs must be primitives_poset_dof_map

  result = (dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0);

  // Postconditions:

  ensure(result ? (dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0) : true);

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

void
sheaf::primitives_poset::
attach_to_state(const namespace_poset* xhost, pod_index_type xindex)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex, false));

  // Body:


  disable_invariant_check();

  poset_state_handle::attach_to_state(xhost, xindex);

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Get read access

  get_read_access();

  // Attach primitives

  bool_type().attach_to_state(this, BOOL);
  char_type().attach_to_state(this, CHAR);

  signed_char_type().attach_to_state(this, SIGNED_CHAR);
  short_int_type().attach_to_state(this, SHORT_INT);
  int_type().attach_to_state(this, INT);
  long_int_type().attach_to_state(this, LONG_INT);
  long_long_int_type().attach_to_state(this, LONG_LONG_INT);

  unsigned_char_type().attach_to_state(this, UNSIGNED_CHAR);
  unsigned_short_int_type().attach_to_state(this, UNSIGNED_SHORT_INT);
  unsigned_int_type().attach_to_state(this, UNSIGNED_INT);
  unsigned_long_int_type().attach_to_state(this, UNSIGNED_LONG_INT);
  unsigned_long_long_int_type().attach_to_state(this, UNSIGNED_LONG_LONG_INT);

  float_type().attach_to_state(this, FLOAT);
  double_type().attach_to_state(this, DOUBLE);
  long_double_type().attach_to_state(this, LONG_DOUBLE);

  void_star_type().attach_to_state(this, VOID_STAR);
  c_string_type().attach_to_state(this, C_STRING);

  namespace_relative_member_index_type().
    attach_to_state(this, NAMESPACE_RELATIVE_MEMBER_INDEX);

  namespace_relative_subposet_index_type().
    attach_to_state(this, NAMESPACE_RELATIVE_SUBPOSET_INDEX);

  enable_invariant_check();

  // Postconditions:

  ensure(poset_state_handle::invariant());
  ensure(is_attached());
  ensure(primitive_members_attached());
  ensure(host() == xhost);
  ensure(index() == xindex);

  // release access to poset state

  release_access();

  ensure(access_request_depth() == old_access_request_depth);

  return;
}

void
sheaf::primitives_poset::
detach_from_state()
{

  // Preconditions:

  // Body:

  // Detach the primitives

  bool_type().detach_from_state();
  char_type().detach_from_state();

  signed_char_type().detach_from_state();
  short_int_type().detach_from_state();
  int_type().detach_from_state();
  long_int_type().detach_from_state();
  long_long_int_type().detach_from_state();

  unsigned_char_type().detach_from_state();
  unsigned_short_int_type().detach_from_state();
  unsigned_int_type().detach_from_state();
  unsigned_long_int_type().detach_from_state();
  unsigned_long_long_int_type().detach_from_state();

  float_type().detach_from_state();
  double_type().detach_from_state();
  long_double_type().detach_from_state();

  void_star_type().detach_from_state();;
  c_string_type().detach_from_state();;

  namespace_relative_member_index_type().detach_from_state();
  namespace_relative_subposet_index_type().detach_from_state();

  // Detach from the standard subposets, members, and state

  poset_state_handle::detach_from_state();

  // Postconditions:

  ensure(!is_attached());
  ensure(!primitive_members_attached());

  // Exit

  return;
}

void
sheaf::primitives_poset::
new_state(const abstract_poset_member* xschema)
{
  // Preconditions:

  require(xschema != 0);
  require(unexecutable("schema is primitives schema"));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the poset state object; without a schema because we don't have one yet.
  // Initial space for 16 members, 32 links, 4 subposets.

  //  _state = new poset_state(xschema, PRIMITIVES_POSET_ID, 16, 32, 4);
  _state = new poset_state(xschema, PRIMITIVES_POSET_ID, standard_name());

  // Get write access

  get_read_write_access();

  // Initialize the table dof map.
  // This class has no table dofs, but we want a non-null dof map anyway.

  initialize_table_dofs(0,0);

  // Create subposets for jims and whole, and schema subposets for top

  initialize_standard_subposets(standard_name());

  // Create bottom, top, and primitives.

  initialize_standard_members();

  // Schematize all members of this so it can be used as schema

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

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(primitive_members_attached());
  ensure(!in_jim_edit_mode());
  //  ensure(host() == xhost);
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());

  // release thread access to poset state

  release_access();

  ensure(state_is_not_read_accessible());
}

void
sheaf::primitives_poset::
initialize_standard_members()
{
  // Preconditions:

  // Body:

  // First create the standard members of the base class

  poset_state_handle::initialize_standard_members();

  // All jims will be members of the row dof subposet;
  // the table dof subposet is empty

  // Enter edit mode

  begin_jim_edit_mode();

  // Create members for the standard primitive types

  initialize_primitive_member(_bool_type, BOOL); // 2
  initialize_primitive_member(_char_type, CHAR); // 3

  initialize_primitive_member(_signed_char_type, SIGNED_CHAR); // 4
  initialize_primitive_member(_short_int_type, SHORT_INT); // 5
  initialize_primitive_member(_int_type, INT); // 6
  initialize_primitive_member(_long_int_type, LONG_INT); // 7
  initialize_primitive_member(_long_long_int_type, LONG_LONG_INT); // 8

  initialize_primitive_member(_unsigned_char_type, UNSIGNED_CHAR); // 9
  initialize_primitive_member(_unsigned_short_int_type, UNSIGNED_SHORT_INT); // 10
  initialize_primitive_member(_unsigned_int_type, UNSIGNED_INT); // 11
  initialize_primitive_member(_unsigned_long_int_type, UNSIGNED_LONG_INT); // 12
  initialize_primitive_member(_unsigned_long_long_int_type, UNSIGNED_LONG_LONG_INT); // 13

  initialize_primitive_member(_float_type, FLOAT); // 14
  initialize_primitive_member(_double_type, DOUBLE); // 15
  initialize_primitive_member(_long_double_type, LONG_DOUBLE); // 16

  initialize_primitive_member(_void_star_type, VOID_STAR); // 17
  initialize_primitive_member(_c_string_type, C_STRING); // 18

  initialize_primitive_member(_namespace_relative_member_index_type, NAMESPACE_RELATIVE_MEMBER_INDEX); // 19
  initialize_primitive_member(_namespace_relative_subposet_index_type, NAMESPACE_RELATIVE_SUBPOSET_INDEX); // 20

  // Exit edit mode

  end_jim_edit_mode();

  // Now there's 21 standard members and 19 standard dof tuples,
  // top, bottom, and the 19 primitive types.

  // All the members and dof tuples are standard.

  put_standard_member_ct(member_ct());
  put_standard_row_dof_tuple_ct(row_dof_tuple_ct());

  // Postconditions:

  ensure(primitive_members_attached());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  // Exit:

  return;
}

void
sheaf::primitives_poset::
initialize_standard_subposets(const std::string& xname)
{

  // Preconditions:

  require(poset_path::is_valid_name(xname));
  require(state_is_read_write_accessible());

  // Body:

  // Initialize the subposets common to all posets:

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


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::primitives_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const primitives_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::primitives_poset::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    result = result && poset_state_handle::invariant();

    disable_invariant_check();

    if(is_attached())
    {
      result = result && primitive_members_attached();
      /// @todo in primitive_poset::invariant() actual type of dof maps must be primitives_poset_dof_map
    }

    enable_invariant_check();
  }


  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

sheaf::primitives_poset*
sheaf::primitives_poset::
clone() const
{
  primitives_poset* result;

  // Preconditions:

  // Body:

  result = new primitives_poset();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit

  return result;
}


