// $RCSfile: primitives_poset_schema.cc,v $ $Revision: 1.44 $ $Date: 2013/03/18 02:53:24 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class primitives_poset_schema

#include "primitives_poset_schema.h"

#include "assert_contract.h"
#include "array_index_space_state.h"
#include "array_poset_dof_map.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "primitives_poset_dof_map.h"
#include "poset_type.h"
#include "primitives_index_space_state.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "total_poset_member.h"

// ===========================================================
// PRIMITIVES_POSET_SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

const string&
sheaf::primitives_poset_schema::
standard_name()
{
  // Preconditions:

  // Body:

  static const string result("primitives_schema");

  // Postconditions:

  ensure(result == "primitives_schema");

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

sheaf::primitives_poset_schema::
primitives_poset_schema()
{
  // Preconditions:

  // Body:

  // Nothing to do; poset_state_handle constructor
  // does what needs to be done

  // Postconditions:

  ensure(!is_attached());

  return;
}

sheaf::primitives_poset_schema::
~primitives_poset_schema()
{

  // Preconditions:

  // Body:

  // Deleted by namespace_poset destructor; nothing to do.

  // Exit

  return;
}

bool
sheaf::primitives_poset_schema::
_has_prototype = make_prototype();

bool
sheaf::primitives_poset_schema::
make_prototype()
{
  // Preconditions:

  // Body:

  poset_type ltype = PRIMITIVES_POSET_SCHEMA_ID;

  primitives_poset_schema* lproto = new primitives_poset_schema;

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
sheaf::primitives_poset_schema::
type_id() const
{
  return PRIMITIVES_POSET_SCHEMA_ID;
}

const char*
sheaf::primitives_poset_schema::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "primitives_poset_schema";

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::primitives_poset_schema::
row_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // Row dofs, must be primitives_poset_dof_map

  result = (dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0);

  // Postconditions:

  ensure(result ? (dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0) : true);

  // Exit

  return result;
}

void
sheaf::primitives_poset_schema::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  int old_access_request_depth = access_request_depth();

  read_write_monitor_handle::get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit

  return;
}

void
sheaf::primitives_poset_schema::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);


  // Body:

  int old_access_request_depth = access_request_depth();

  read_write_monitor_handle::get_read_write_access(xrelease_read_only_access);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit

  return;
}

void
sheaf::primitives_poset_schema::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = access_request_depth();

  // Inherited poset_state_handle::release_access also releases schema.
  // But this is its own schema and we don't want cess released twice,
  // so just call the version in read_write_monitor_handle directly.

  read_write_monitor_handle::release_access(xall);

  // Postconditions:

  ensure(!xall ? access_request_depth() == old_access_request_depth - 1 :
         access_request_depth() == 0);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::primitives_poset_schema::
prereq_id(int xi) const
{
  // The primitives poset schema is its own schema and
  // has no other prerequisites.

  return invalid_pod_index();
}

// PROTECTED FUNCTIONS

void
sheaf::primitives_poset_schema::
initialize_standard_members()
{
  // Preconditions:

  // Body:

  // First create the standard members of the base class

  poset_state_handle::initialize_standard_members();

  // All jims will be members of "row_dofs" subposet;
  // there are no table dofs

  // Enter edit mode

  begin_jim_edit_mode();

  primitives_poset_dof_map* ldof_map;
  pod_index_type lmbr_id;

  // Create jim for size of primitive type.

  ldof_map = new primitives_poset_dof_map(this, SIZE_TYPE);
  lmbr_id = new_member(true, ldof_map, false);
  put_member_name(lmbr_id, "size", true, false);
  _row_dof_subposet->insert_member(lmbr_id);

  // Create jim for alignment of primitive type

  ldof_map = new primitives_poset_dof_map(this, SIZE_TYPE);
  lmbr_id = new_member(true, ldof_map, false);
  put_member_name(lmbr_id, "alignment", true, false);
  _row_dof_subposet->insert_member(lmbr_id);

  // Create jim for index of primitive type

  ldof_map = new primitives_poset_dof_map(this, POD_INDEX_TYPE);
  lmbr_id = new_member(true, ldof_map, false);
  put_member_name(lmbr_id, "type_id", true, false);
  _row_dof_subposet->insert_member(lmbr_id);

  // Exit edit mode

  end_jim_edit_mode();

  // Now there's 5 standard members,
  // top, bottom, size, alignment, and index

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
sheaf::primitives_poset_schema::
initialize_standard_subposets(const string& xname)
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

void
sheaf::primitives_poset_schema::
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

  // Initialize the table dof subposet:

  // Initialize the name

  xtable_dof_subposet->put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  // Initialize the dof id space, empty

  xtable_dof_subposet->new_id_space("array_index_space_state",
				    array_index_space_state::make_arg_list(0));

  // Initialize is_dof_subposet

  xtable_dof_subposet->put_is_dof_subposet(true);

  // Initialize dof count

  xtable_dof_subposet->put_dof_ct(0);

  // Initialize the table dof offsets array

  dof_descriptor_array& ltable_dof_descriptors = *(new dof_descriptor_array(0));
  ltable_dof_descriptors[0].size      = 0;
  ltable_dof_descriptors[0].alignment = 0;
  ltable_dof_descriptors[0].type      = NOT_A_PRIMITIVE_TYPE;
  ltable_dof_descriptors[0].offset    = 0;
  xtable_dof_subposet->put_dof_descriptors(&ltable_dof_descriptors);


  // Initialize the row dof subposet:

  // Initialize the name

  xrow_dof_subposet->put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  // Initialize the dof client id map

  string lname = xrow_dof_subposet->name();

  arg_list largs = primitives_index_space_state::make_arg_list();
  member_id_spaces(false).new_secondary_state(lname,
					      "primitives_index_space_state",
					      largs, false);

  // Initialize is_dof_subposet

  xrow_dof_subposet->put_is_dof_subposet(true);

  // Initialize dof count
  // There are 3 dofs: size, alignment, index

  xrow_dof_subposet->put_dof_ct(PRIMITIVES_SCHEMA_DOF_CT);

  // Initialize the dof offsets array.
  // Constructor argument is dof count; allocates dof count + 1 entries

  dof_descriptor_array& lrow_dof_descriptors    = *(new dof_descriptor_array(PRIMITIVES_SCHEMA_DOF_CT));

  // Size dof is type size_t

  const primitive_descriptor size_t_desc = primitive_attributes::descriptor(SIZE_TYPE);

  lrow_dof_descriptors[0].size      = size_t_desc.size;
  lrow_dof_descriptors[0].alignment = size_t_desc.alignment;
  lrow_dof_descriptors[0].type      = size_t_desc.index;
  lrow_dof_descriptors[0].offset    = 0;
  size_t loffset = size_t_desc.size;

  // Alignment dof is type size_t

  lrow_dof_descriptors[1].size      = size_t_desc.size;
  lrow_dof_descriptors[1].alignment = size_t_desc.alignment;
  lrow_dof_descriptors[1].type      = size_t_desc.index;
  loffset = align(loffset, size_t_desc.alignment);
  lrow_dof_descriptors[1].offset    = loffset;
  loffset += size_t_desc.size;

  // Index dof is type int

  const primitive_descriptor int_desc = primitive_attributes::descriptor(INT_TYPE);

  lrow_dof_descriptors[2].size      = int_desc.size;
  lrow_dof_descriptors[2].alignment = int_desc.alignment;
  lrow_dof_descriptors[2].type      = int_desc.index;
  loffset = align(loffset, int_desc.alignment);
  lrow_dof_descriptors[2].offset    = loffset;
  loffset += int_desc.size;

  // Last dof descriptor just stores size of entire dof tuple in offset.

  lrow_dof_descriptors[3].size      = 0;
  lrow_dof_descriptors[3].alignment = 0;
  lrow_dof_descriptors[3].type      = NOT_A_PRIMITIVE_TYPE;
  lrow_dof_descriptors[3].offset    = loffset;

  xrow_dof_subposet->put_dof_descriptors(&lrow_dof_descriptors);

  // Postconditions:

  ensure(is_schematized(false));

  // Exit

  return;
}

void
sheaf::primitives_poset_schema::
terminate_access()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // This is it's own schema;
  // just detach and delete the state.

  poset_state* lstate = _state;
  detach_from_state();
  delete lstate;

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable(state has been deleted));

  // Exit

  return;
}

// PRIVATE FUNCTIONS

void
sheaf::primitives_poset_schema::
new_state()
{
  // Preconditions:

  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Create the poset state object without a schema because we don't have one yet.
  // Initial space for 4 members, 8 links, 4 subposets

  _state = new poset_state(0, PRIMITIVES_POSET_SCHEMA_ID, 8, 16, 32);

  // Get write access.

  get_read_write_access();

  // Initialize additional row structure.

  // Create subposets for jims and whole, and schema subposets for top.

  initialize_standard_subposets(standard_name());

  // Create the bottom, top, and jims.

  initialize_standard_members();

  // Now that the standard members have all been inserted in the row dofs,
  // we can initialize the other schema info derived from the dofs subposets.

  schematize(_table_dof_subposet, _row_dof_subposet);

  // Schematize has created new subposets, reset the standard subposet count.
  // Every subposet is a standard subposet.

  put_standard_subposet_ct(subposet_ct());

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // We won't use the two subposet handles again;
  // detach and delete them.

  _table_dof_subposet->detach_from_state();
  delete _table_dof_subposet;
  _table_dof_subposet = 0;

  _row_dof_subposet->detach_from_state();
  delete _row_dof_subposet;
  _row_dof_subposet = 0;

  // Initialize the schema;
  //
  // Since the jims of any schema poset are necessarily copies
  // of jims of the primitives poset, the schema of any schema
  // poset must be the same as the schema of the primitives
  // poset. Thus, this schema poset must be its own schema.
  // More precisely, the schema for this poset must be
  // its own top member.

  schema().attach_to_state(&(top()));

  // Initialize the table dof map.
  // This class has no table dofs, but we want a non-null dof map anyway.
  // Requires schema.

  initialize_table_dofs(0,0);

  // Now the invariant should be satisfied.

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(!in_jim_edit_mode());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());

  // Release thread access to poset state.

  release_access();

  ensure(state_is_not_read_accessible());
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::primitives_poset_schema::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const primitives_poset_schema*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


bool
sheaf::primitives_poset_schema::
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

sheaf::primitives_poset_schema*
sheaf::primitives_poset_schema::
clone() const
{
  primitives_poset_schema* result;

  // Preconditions:

  // Body:

  result = new primitives_poset_schema();

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}

