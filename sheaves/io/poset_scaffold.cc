
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
/// Implementation for class poset_scaffold

#include "subposet.h"
#include "poset_scaffold.h"
#include "assert_contract.h"
#include "data_converter.h"
#include "error_message.h"
#include "index_space_iterator.h"
#include "interval_index_space_state.h"
#include "namespace_poset.h"
#include "namespace_relative_member_index.h"
#include "namespace_relative_subposet_index.h"
#include "poset.h"
#include "poset_bounds.h"
#include "primitive_type.h"
#include "std_sstream.h"
#include "storage_agent.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

// ===========================================================
// POSET_SCAFFOLD FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_scaffold::
poset_scaffold(const poset_scaffold& xother)
    : _structure(xother._structure),
      _row_bounds(xother._row_bounds),
      _col_bounds(xother._col_bounds),
      _toc_bounds(xother._toc_bounds),
      _type_map(xother._type_map),
      _external_schema(xother._external_schema),
      _member_id_space(xother._member_id_space),
      _subposet_id_space(xother._subposet_id_space),
      _dof_tuple_id_space(xother._dof_tuple_id_space),
      _subposets(xother._subposets)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

sheaf::poset_scaffold::
~poset_scaffold()
{
  // Preconditions:

  // Body:

  // Delete the bounds objects.

  delete _row_bounds;
  delete _col_bounds;
  delete _toc_bounds;

  // Detach the resident subposet.

  _resident.detach_from_state();

  // Detach and delete the schema handles.

  _internal_schema->detach_from_state();
  delete _internal_schema;

  _transfer_schema->detach_from_state();
  delete _transfer_schema;

  _external_schema->detach_from_state();
  delete _external_schema;

  // Delete all the subposet handles.

  vector<subposet*>::iterator itr = _subposets.begin();
  while(itr != _subposets.end())
  {
    subposet* sp = *itr;
    if(sp != 0)
    {
      sp->detach_from_state();
      delete sp;
    }
    itr++;
  }

  // Release id space handles.

  for(int i = 0; i < _id_spaces.ub(); i++)
  {
    if(_id_spaces[i] != 0)
    {
      _id_spaces[i]->release_id_space();
    }
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::poset_scaffold::
poset_scaffold(const poset_state_handle& xposet,
	       const storage_agent::transaction& xtrans,
	       data_type_map& xtype_map,
	       const string& xfile_id_space_name,
	       bool xis_write_transaction)
  : _structure(const_cast<poset_state_handle&>(xposet)),
    _type_map(xtype_map),
    _file_id_space_name(xfile_id_space_name)
{
  // Preconditions:

  require(xis_write_transaction ? !xposet.is_external() : true);
  require(!xposet.is_external() ? xposet.state_is_read_accessible() : true);

  // Body:

  _is_write_transaction = xis_write_transaction;

  _row_bounds = new poset_bounds(xtrans.row_bounds);
  _col_bounds = new poset_bounds(xtrans.col_bounds);
  _toc_bounds = new poset_bounds(poset_bounds_descriptor::BOTTOM_TOP);


  if(xis_write_transaction)
  {
    // Initialize the member index space.

    initialize_member_id_space();

    // Initialize the schema

    initialize_schema_for_write();

    // Initialize the dof tuple index space.

    initialize_dof_tuple_id_space();

    // Initialize the subposet index space.

    initialize_subposet_id_space();

    // Initialize the subposet handle buffer.

    initialize_subposets();
  }
  else
  {
    // Read transaction:
    //
    // Can't initialize index spaces until we've created the poset;
    //
    // see id_space_names_record::transfer_internal_buffer_to_poset() for
    // member index space initialization.
    //
    // see subposet_names_record::transfer_internal_buffer_to_poset() for
    // subposet index space initialization.
    //
    // set member_record::internalize() for dof tuple index space initialization.
  }

  _is_versioned = false; // set on read in poset_general_record.

  // Postconditions:

  ensure(invariant());
  ensure(!resident().is_attached());

  // Exit

  return;
}

sheaf::poset_state_handle&
sheaf::poset_scaffold::
structure()
{
  return _structure;
}

const sheaf::poset_state_handle&
sheaf::poset_scaffold::
structure() const
{
  return _structure;
}

sheaf::poset_powerset_state&
sheaf::poset_scaffold::
powerset()
{
  return _structure.powerset();
}

const sheaf::poset_powerset_state&
sheaf::poset_scaffold::
powerset() const
{
  return _structure.powerset();
}

sheaf::poset_table_state&
sheaf::poset_scaffold::
table()
{
  return _structure.table();
}

const sheaf::poset_table_state&
sheaf::poset_scaffold::
table() const
{
  return _structure.table();
}

bool
sheaf::poset_scaffold::
is_write_transaction() const
{
  return _is_write_transaction;
}

sheaf::poset_bounds&
sheaf::poset_scaffold::
row_bounds()
{
  return *_row_bounds;
}

const sheaf::poset_bounds&
sheaf::poset_scaffold::
row_bounds() const
{
  return *_row_bounds;
}

sheaf::poset_bounds&
sheaf::poset_scaffold::
col_bounds()
{
  return *_col_bounds;
}

const sheaf::poset_bounds&
sheaf::poset_scaffold::
col_bounds() const
{
  return *_col_bounds;
}

const sheaf::poset_bounds&
sheaf::poset_scaffold::
toc_bounds() const
{
  return *_toc_bounds;
}

void
sheaf::poset_scaffold::
update_toc_bounds(const poset_bounds_descriptor& xdesc)
{
  // Preconditions:

  // Body:

  delete _toc_bounds;
  _toc_bounds = new poset_bounds(xdesc);

  // Postconditions:

  // Exit

  return;
}

void
sheaf::poset_scaffold::
evaluate_toc_alias()
{
  // Preconditions:

  // Body:

  if(_row_bounds->lb_id() == TOC_INDEX)
  {
    // Replace row bounds with toc bounds

    delete _row_bounds;
    _row_bounds = _toc_bounds->clone();
  }

  // Postconditions:

  // Exit

  return;
}

sheaf::subposet&
sheaf::poset_scaffold::
resident()
{
  return _resident;
}

const sheaf::subposet&
sheaf::poset_scaffold::
resident() const
{
  return _resident;
}

sheaf::namespace_poset*
sheaf::poset_scaffold::
name_space() const
{
  namespace_poset* result;

  // Preconditions:

  // Body:

  result = dynamic_cast<namespace_poset*>(&_structure);
  if(result == 0)
  {
    result = _structure.name_space();
  }

  // Postconditions:

  ensure(structure_is_namespace() ? result == &(structure()) : result == structure().name_space());

  // Exit

  return result;
}

bool
sheaf::poset_scaffold::
structure_is_namespace() const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<namespace_poset*>(&_structure) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
index() const
{
  return _structure.index();
}

string
sheaf::poset_scaffold::
name() const
{
  return _structure.name();
}

sheaf::schema_poset_member&
sheaf::poset_scaffold::
internal_schema()
{
  return *_internal_schema;
}

const sheaf::schema_poset_member&
sheaf::poset_scaffold::
internal_schema() const
{
  return *_internal_schema;
}

sheaf::schema_poset_member&
sheaf::poset_scaffold::
transfer_schema()
{
  return *_transfer_schema;
}

const sheaf::schema_poset_member&
sheaf::poset_scaffold::
transfer_schema() const
{
  return *_transfer_schema;
}

sheaf::schema_poset_member&
sheaf::poset_scaffold::
external_schema()
{
  return *_external_schema;
}

const sheaf::schema_poset_member&
sheaf::poset_scaffold::
external_schema() const
{
  return *_external_schema;
}

sheaf::poset_data_type_map&
sheaf::poset_scaffold::
type_map()
{
  return _type_map;
}

const sheaf::poset_data_type_map&
sheaf::poset_scaffold::
type_map() const
{
  return _type_map;
}

const string&
sheaf::poset_scaffold::
file_id_space_name() const
{
  return _file_id_space_name;
}

bool&
sheaf::poset_scaffold::
is_versioned()
{
  return _is_versioned;
}

const bool&
sheaf::poset_scaffold::
is_versioned() const
{
  return _is_versioned;
}

void
sheaf::poset_scaffold::
initialize_schema_for_read(schema_poset_member* xext_schema,
			   int xschema_version)
{
  // Preconditions:

  require(xext_schema != 0);
  require(xext_schema->is_attached());

  // Body:

  if(col_bounds().ub_is_singleton() &&
      col_bounds().ub_id() == TOP_INDEX)
  {
    // Adjust the upper bounds.
    // For a read operation, the upper bound can not be greater than
    // the external schema, so the only consistent interpretation is
    // upper bounds == top means use external schema as upper bound.

    col_bounds().put_ub_id(xext_schema->index());
  }

  // Create the schema handles.
  // Ensure right type by cloning top member of poset.

  _external_schema = xext_schema;
  _internal_schema = _external_schema->clone();
  _transfer_schema = _external_schema->clone();


  // Initialize the internal schema.

  if(structure().is_external())
  {
    // Internal poset doesn't have a schema yet;

    if(col_bounds().ub_is_singleton())
    {
      // Upper bound is a single member; use the member specified in the bounds.
      // Internal schema has to be in the same poset as external schema.

      _internal_schema->attach_to_state(_external_schema->host(),
					col_bounds().ub_id());
    }
    else
    {
      // Upper bound is a subposet; internal schema is join of members.

      if(col_bounds().ub_is_decomposition())
      {
        // Join of members equals external schema.

        _internal_schema->attach_to_state(_external_schema);
      }
      else
      {
        // Must compute join of upper bound.

        post_fatal_error_message("non-decomposition upper bound not implemented");
      }
    }
  }
  else
  {
    // Internal poset already has a schema; use it.

    _internal_schema->attach_to_state(&(structure().schema()));
  }

  // Temporarily attach transfer schema to external schema.
  // Sets host, proper member will be set in poset_scaffold::read_records.

  _transfer_schema->attach_to_state(_external_schema);

  // Set the schema version; all use the same version.

  _external_schema->put_version(xschema_version);
  _internal_schema->put_version(xschema_version);
  _transfer_schema->put_version(xschema_version);

  // Postconditions:

  ensure(external_schema().is_attached());
  ensure(internal_schema().is_attached());
  ensure(transfer_schema().is_attached());

  // Exit

  return;
}

void
sheaf::poset_scaffold::
initialize_transfer_schema_for_read(const scoped_index& xindex)
{
  // Preconditions:

  // Postconditions:

  not_implemented();

  // Exit

  return;
}

void
sheaf::poset_scaffold::
insert_id_name_pair(pod_index_type xid, const string& xname, block<char>& xbuf)
{
  // Preconditions:

  // Body:

  // Convert the member id to a string

  stringstream lmbr_id_stream;
  lmbr_id_stream << xid;
  string lmbr_id_str(lmbr_id_stream.str());

  // Put the member id string in the buffer.

  for(int i=0; i<lmbr_id_str.size(); i++)
  {
    xbuf.push_back(lmbr_id_str[i]);
  }

  // Terminate the string in the buffer.

  xbuf.push_back('\0');

  // Put the name into the buffer.

  for(int i=0; i<xname.size(); i++)
  {
    // Nothing prevents a client from padding a
    // C++ string with nulls using << ends. But
    // such nulls will be interprettd as 0-length strings
    // in the file. So make sure we don't put any in the file
    // considering first null as end of string.

    char lchr = xname[i];
    if(lchr == '\0')
      break;

    xbuf.push_back(lchr);
  }

  // Terminate the string in the buffer.

  xbuf.push_back('\0');

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::poset_scaffold::
extract_id_name_pair(pod_index_type& xid, string& xname, char*& xbuf)
{
  // Preconditions:

  // Body:

  // Extract the id.

  xid = atoi(xbuf);

  // Advance xbuf past the member id to
  // the beginning of the name.

  xbuf += strlen(xbuf) + 1;

  // Extract the name

  xname = xbuf;

  // Advance xbuf to the next entry.

  xbuf += strlen(xbuf) + 1;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

void
sheaf::poset_scaffold::
initialize_schema_for_write()
{
  // Preconditions:

  /// @hack the product subposet hack.
  /// Following precondition is not executable because of hack.
  ///   require(col_bounds().ub_is_singleton() &&
  ///    (col_bounds().ub_id() != TOP_INDEX) ?
  ///    structure().schema().ge(col_bounds().ub_id()) :
  ///    true);

  // Body:

  // Get a handle to the schema poset.

  poset_state_handle* lschema_poset = structure().schema().host();

  if(col_bounds().ub_is_singleton() &&
      col_bounds().ub_id() == TOP_INDEX)
  {
    // Adjust the upper bounds. For a write operation,
    // the upper bound can not be greater than the internal schema,
    // so the only consistent interpretation is
    // upper bounds == top means use internal schema as upper bound.

    col_bounds().put_ub_id(structure().schema().index());
  }

  // Create the schema handles.
  // Ensure right type by cloning schema of structure().

  _external_schema = structure().schema().clone();
  _transfer_schema = _external_schema->clone();
  _internal_schema = _external_schema->clone();

  // Initialize internal schema to the schema of the internal poset.

  _internal_schema->attach_to_state(&(structure().schema()));

  // Initialize the external schema.
  // (Currently update is not supported, only write with clobber.)

  if(col_bounds().ub_is_singleton())
  {
    // Upper bound is a single member.

    if(col_bounds().ub_id() == TOP_INDEX)
    {
      // ub_id == top means use internal schema.

      _external_schema->attach_to_state(_internal_schema);
    }
    else
    {
      // Use the member specified in the bounds.

      _external_schema->attach_to_state(_internal_schema->host(),
                                        col_bounds().ub_id());
    }
  }
  else
  {
    // Upper bound is a subposet; in principle the external schema
    // is the join of the meets of the internal schema with each member.

    if(col_bounds().ub_is_decomposition())
    {
      // The join of the ub members is the host schema;
      // join of meets of internal schema with members equals internal schema.

      _external_schema->attach_to_state(_internal_schema);
    }
    else
    {
      // Must compute join of upper bound; but we don't support that yet.

      post_fatal_error_message("non-decomposition upper bound not implemented");
    }
  }

  // Temporarily initialize the transfer schema to the external schema.
  // Sets the host, proper member will be set in ???.

  _transfer_schema->attach_to_state(_external_schema);

  // Set the schema version

  int lver = structure().schema().version();
  _external_schema->put_version(lver);
  _transfer_schema->put_version(lver);
  _internal_schema->put_version(lver);

  // Postconditions:

  ensure(internal_schema().is_attached());
  ensure(external_schema().is_attached());
  ensure(transfer_schema().is_attached());

  // Exit

  return;
}


// ===========================================================
// MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::poset_scaffold::
put_member_record_type_aliases(int xtoc_index,
                               int xdof_tuple_id_index,
                               int xoffset_index)
{

  // Preconditions:

  require(is_primitive_index(xtoc_index));
  require(is_primitive_index(xdof_tuple_id_index));
  require(is_primitive_index(xoffset_index));

  // Body:

  type_map().put_member_record_type_aliases(xtoc_index, xdof_tuple_id_index,  xoffset_index);

  // Postconditions:

  ensure(invariant());
}

void
sheaf::poset_scaffold::
initialize_member_id_space()
{
  // Preconditions:

  require(structure().state_is_read_accessible());

  // Body:

  // Space is created in initialize_poset_index_spaces_for_write() during write.
  // But it is not persistent and must be recreated on read.
  // It persists between partial reads or writes, so if it exists, we don't
  // want to clear it, or otherwise change it.

  if(!_structure.member_id_spaces(false).contains(_file_id_space_name))
  {
    arg_list largs = interval_index_space_state::make_arg_list(true);

    _structure.member_id_spaces(false).new_secondary_state(_file_id_space_name,
							   "interval_index_space_state",
							   largs, false);
  }

  _member_id_space.attach_to(_structure.member_id_spaces(false),
			     _file_id_space_name);

  // Postconditions:

  ensure(member_id_space_initialized());

  // Exit:

  return;
}

bool
sheaf::poset_scaffold::
member_id_space_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _member_id_space.is_attached();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
member_ext_id(const scoped_index& xid) const
{
  // Preconditions:

  require(member_id_space_initialized());

  // Body:

  scoped_index result(_member_id_space, xid);
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
member_ext_id(pod_index_type xid) const
{
  // Preconditions:

  require(member_id_space_initialized());

  // Body:

  scoped_index result(_member_id_space, xid);
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_scaffold::member_index_space_type&
sheaf::poset_scaffold::
member_id_space()
{
  // Preconditions:

  require(member_id_space_initialized());

  // Body:

  member_index_space_type& result = _member_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::poset_scaffold::member_index_space_type&
sheaf::poset_scaffold::
member_id_space() const
{
  // Preconditions:

  require(member_id_space_initialized());

  // Body:

  const member_index_space_type& result = _member_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::poset_scaffold::member_name_map_type&
sheaf::poset_scaffold::
member_name_map()
{
  return _member_name_map;
}

const sheaf::poset_scaffold::member_name_map_type&
sheaf::poset_scaffold::
member_name_map() const
{
  return _member_name_map;
}

sheaf::poset_scaffold::member_class_names_type&
sheaf::poset_scaffold::
member_class_names()
{
  return _member_class_names;
}

const sheaf::poset_scaffold::member_class_names_type&
sheaf::poset_scaffold::
member_class_names() const
{
  return _member_class_names;
}

void
sheaf::poset_scaffold::
convert_member_id_to_record_id(void* xbuf)
{
  // Preconditions:

  require(name_space() != 0);
  require(name_space()->state_is_read_accessible());

  // Body:

  // Some covenient typedefs.

  typedef namespace_relative_member_index nrmi_type;
  typedef namespace_relative_record_index nrri_type;

  // Convert dof from pod type to index type.

  nrmi_type lmbr_id(_structure.member_hub_id_space(false),
		    *reinterpret_cast<nrmi_type::pod_type*>(xbuf));

  // Convert member index to record index.

  nrri_type lrec_id;

  assertion(!lrec_id.is_valid());

  if(name_space()->contains_poset(lmbr_id.poset_id, false))
  {
    lrec_id.poset_id  =
      name_space()->get_ext_id(lmbr_id.poset_id, _file_id_space_name, false);

    poset_state_handle& lposet = name_space()->member_poset(lmbr_id.poset_id, false);
    if(lposet.contains_member(lmbr_id.member_id))
    {
      lrec_id.member_id =
        lposet.get_ext_id(lmbr_id.member_id, _file_id_space_name, true);
    }
  }

  // Convert record index back to pod type.

  *reinterpret_cast<nrri_type::pod_type*>(xbuf) = lrec_id.pod();

  // Postconditions:

  // Exit

  return;
}

void
sheaf::poset_scaffold::
convert_record_id_to_member_id(void* xbuf)
{
  // Preconditions:

  require(name_space()->state_is_read_accessible());
  require(name_space()->member_id_spaces(false).contains(file_id_space_name()));

  // Body:

  // Some covenient typedefs.

  typedef namespace_relative_member_index nrmi_type;
  typedef namespace_relative_record_index nrri_type;

  // Convert dof from pod type to index type.

  nrri_type::pod_type* lrec_id = reinterpret_cast<nrri_type::pod_type*>(xbuf);

  // Conver record index to member index.

  nrmi_type lint_id;

  if(is_valid(lrec_id->poset_id))
  {
    lint_id.poset_id =
      name_space()->get_int_id(lrec_id->poset_id, _file_id_space_name, false);

    if(is_valid(lrec_id->member_id))
    {
      poset_state_handle& lposet =
        name_space()->member_poset(lint_id.poset_id, false);
      lint_id.member_id =
        lposet.get_int_id(lrec_id->member_id, _file_id_space_name, true);
    }
  }

  // Convert member index back to pod type.

  *reinterpret_cast<nrmi_type::pod_type*>(xbuf) = lint_id.pod();

  // Postconditions:

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUBPOSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::poset_scaffold::
initialize_subposet_id_space()
{
  // Preconditions:

  require(structure().state_is_read_accessible());

  // Body:

  // Space is created in initialize_poset_index_spaces_for_write() during write.
  // But it is not persistent and must be recreated on read.
  // It does not persist between partial reads or writes, so if it exists,
  // we want to clear it.

  if(!_structure.subposet_id_spaces(false).contains(_file_id_space_name))
  {
    arg_list largs = interval_index_space_state::make_arg_list(true);
 
    _structure.subposet_id_spaces(false).
      new_secondary_state(_file_id_space_name,
			  "interval_index_space_state",
			  largs, false);
  }

  _subposet_id_space.attach_to(_structure.subposet_id_spaces(false),
			       _file_id_space_name);
  _subposet_id_space.clear();

  // Postconditions:

  ensure(subposet_id_space_initialized());
  ensure(subposet_id_space().is_empty());
  
  // Exit:

  return;
}

bool
sheaf::poset_scaffold::
subposet_id_space_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _subposet_id_space.is_attached();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
subposet_ext_id(const scoped_index& xid) const
{
  // Preconditions:

  require(subposet_id_space_initialized());

  // Body:

  scoped_index result(_subposet_id_space, xid);
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
subposet_ext_id(pod_index_type xid) const
{
  // Preconditions:

  require(subposet_id_space_initialized());

  // Body:

  scoped_index result(_subposet_id_space, xid);
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_scaffold::subposet_index_space_type&
sheaf::poset_scaffold::
subposet_id_space()
{
  // Preconditions:

  require(subposet_id_space_initialized());

  // Body:

  subposet_index_space_type& result = _subposet_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::poset_scaffold::subposet_index_space_type&
sheaf::poset_scaffold::
subposet_id_space() const
{
  // Preconditions:

  require(subposet_id_space_initialized());

  // Body:

  const subposet_index_space_type& result = _subposet_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

vector<sheaf::subposet*>&
sheaf::poset_scaffold::
subposets()
{
  return _subposets;
}

const vector<sheaf::subposet*>&
sheaf::poset_scaffold::
subposets() const
{
  return _subposets;
}

void
sheaf::poset_scaffold::
convert_subposet_id_to_record_id(void* xbuf)
{
  // Preconditions:

  require(name_space()->state_is_read_accessible());
  require(name_space()->member_id_spaces(false).contains(file_id_space_name()));

  // Body:

  // Some convenient typedefs.

  typedef namespace_relative_subposet_index nrsi_type;
  typedef namespace_relative_record_index nrri_type;

  // Convert pod type to subposet index.

  nrsi_type lsp_id(_structure.member_hub_id_space(false),
		   *reinterpret_cast<nrsi_type::pod_type*>(xbuf));

  // Convert subposet index to record index.

  namespace_relative_record_index lrec_id;

  lrec_id.poset_id  =
    name_space()->get_ext_id(lsp_id.poset_id, _file_id_space_name, false);

  poset_state_handle& lposet = name_space()->member_poset(lsp_id.poset_id, false);
  if(lposet.includes_subposet(lsp_id.subposet_id))
  {
    lrec_id.member_id = subposet_ext_id(lsp_id.subposet_id);
  }

  // Convert record index back to pod type.

  *reinterpret_cast<nrri_type::pod_type*>(xbuf) = lrec_id.pod();

  // Postconditions:

  // Exit

  return;
}

void
sheaf::poset_scaffold::
convert_record_id_to_subposet_id(void* xbuf)
{
  // Preconditions:

  // Body:

  // Some convenient typedefs.

  typedef namespace_relative_subposet_index nrsi_type;
  typedef namespace_relative_record_index nrri_type;

  // Convert pod type to record index.

  nrri_type::pod_type* lrec_id = reinterpret_cast<nrri_type::pod_type*>(xbuf);

  // Convert record index to subposet index.

  nrsi_type lint_id;

  if(is_valid(lrec_id->poset_id))
  {
    lint_id.poset_id  =
      name_space()->get_int_id(lrec_id->poset_id, _file_id_space_name, false);

    if(is_valid(lrec_id->member_id))
    {
      poset_powerset_state& lpowerset =
	name_space()->member_poset(lint_id.poset_id, false).powerset();
      lint_id.subposet_id =
	lpowerset.hub_id(_subposet_id_space.hub_pod(lrec_id->member_id));
    }
  }
  
  // Convert subposet index back to pod type.

  *reinterpret_cast<nrsi_type::pod_type*>(xbuf) = lint_id.pod();

  // Postconditions:

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

void
sheaf::poset_scaffold::
initialize_subposets()
{
  // Preconditions:

  require(subposet_id_space_initialized());

  // Body:

  const poset_state_handle& lposet = structure();

  // Initialize iteration.

  _subposets.reserve(lposet.subposet_ct());

  index_space_iterator& itr = lposet.get_subposet_id_space_iterator();
  subposet lsp;

  while(!itr.is_done())
  {
    pod_index_type lid = itr.hub_pod();

    lsp.attach_to_state(&lposet, lid);

    if(lsp.is_persistent())
    {
      // This subposet is a persistent subposet; we'll have to write it out.

      // Assign a sequential external index. Note that this preserves the
      // indexing for the standard subposets, as long as they are sequentially
      // indexed internally, starting at 0.

      _subposet_id_space.push_back(lid);

      // Create a handle and save it in the buffer.

      _subposets.push_back(new subposet(&lposet, lid));
    }
    itr.next();
  }

  lposet.release_subposet_id_space_iterator(itr);

  lsp.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


// ===========================================================
// DOF_TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::poset_scaffold::
initialize_dof_tuple_id_space()
{
  // Preconditions:

  require(structure().state_is_read_accessible());

  // Body:

  // Space is created in initialize_poset_index_space_for_write() during write.
  // But it is not persistent and must be recreated on read.
  // It does not persist between partial reads or writes, so if it exists,
  // we want to clear it.

  if(!_structure.dof_tuple_id_spaces(false).contains(_file_id_space_name))
  {
    arg_list largs = interval_index_space_state::make_arg_list(true);

    _structure.dof_tuple_id_spaces(false).
      new_secondary_state(_file_id_space_name,
			  "interval_index_space_state",
			  largs, false);
  }

  _dof_tuple_id_space.attach_to(_structure.dof_tuple_id_spaces(false),
				_file_id_space_name);
  _dof_tuple_id_space.clear();

  _dof_tuple_scratch_id = 0;

  // Postconditions:

  ensure(dof_tuple_id_space_initialized());
  ensure(dof_tuple_id_space().is_empty());
  
  // Exit:

  return;
}

bool
sheaf::poset_scaffold::
dof_tuple_id_space_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _dof_tuple_id_space.is_attached();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
dof_tuple_ext_id(const scoped_index& xid) const
{
  // Preconditions:

  require(dof_tuple_id_space_initialized());

  // Body:

  scoped_index result(_dof_tuple_id_space, xid);
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_scaffold::
dof_tuple_ext_id(pod_index_type xid) const
{
  // Preconditions:

  require(dof_tuple_id_space_initialized());

  // Body:

  scoped_index result(_dof_tuple_id_space, xid);
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_scaffold::dof_tuple_index_space_type&
sheaf::poset_scaffold::
dof_tuple_id_space()
{
  // Preconditions:

  require(dof_tuple_id_space_initialized());

  // Body:

  dof_tuple_index_space_type& result = _dof_tuple_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::poset_scaffold::dof_tuple_index_space_type&
sheaf::poset_scaffold::
dof_tuple_id_space() const
{
  // Preconditions:

  require(dof_tuple_id_space_initialized());

  // Body:

  const dof_tuple_index_space_type& result = _dof_tuple_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_scaffold::
dof_tuple_scratch_id() const
{
  return _dof_tuple_scratch_id;
}

void
sheaf::poset_scaffold::
put_dof_tuple_scratch_id(pod_index_type xid)
{
  // Preconditions:

  // Body:

  _dof_tuple_scratch_id = xid;

  // Postconditions:

  ensure(dof_tuple_scratch_id() == xid);

  // Exit:

  return;
}

sheaf::poset_scaffold::dof_tuple_types_type&
sheaf::poset_scaffold::
dof_tuple_types()
{
  return _dof_tuple_types;
}

const sheaf::poset_scaffold::dof_tuple_types_type&
sheaf::poset_scaffold::
dof_tuple_types() const
{
  return _dof_tuple_types;
}

sheaf::poset_scaffold::dof_tuple_class_names_type&
sheaf::poset_scaffold::
dof_tuple_class_names()
{
  return _dof_tuple_class_names;
}

const sheaf::poset_scaffold::dof_tuple_class_names_type&
sheaf::poset_scaffold::
dof_tuple_class_names() const
{
  return _dof_tuple_class_names;
}

sheaf::poset_scaffold::dof_tuple_schema_versions_type&
sheaf::poset_scaffold::
dof_tuple_schema_versions()
{
  return _dof_tuple_schema_versions;
}

const sheaf::poset_scaffold::dof_tuple_schema_versions_type&
sheaf::poset_scaffold::
dof_tuple_schema_versions() const
{
  return _dof_tuple_schema_versions;
}

bool
sheaf::poset_scaffold::
dof_tuple_schema_versions_contains(pod_index_type xdof_tuple_ext_id) const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    dof_tuple_schema_versions().find(xdof_tuple_ext_id) !=
    dof_tuple_schema_versions().end();

  // Postconditions:

  // Exit:

  return result;
}

int
sheaf::poset_scaffold::
dof_tuple_schema_version(pod_index_type xdof_tuple_ext_id) const
{
  // Preconditions:

  require(dof_tuple_schema_versions_contains(xdof_tuple_ext_id));

  // Body:

  int result = dof_tuple_schema_versions().find(xdof_tuple_ext_id)->second;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_scaffold::dof_tuple_schema_ids_type&
sheaf::poset_scaffold::
dof_tuple_schema_ids()
{
  return _dof_tuple_schema_ids;
}

const sheaf::poset_scaffold::dof_tuple_schema_ids_type&
sheaf::poset_scaffold::
dof_tuple_schema_ids() const
{
  return _dof_tuple_schema_ids;
}

bool
sheaf::poset_scaffold::
dof_tuple_schema_ids_contains(pod_index_type xdof_tuple_ext_id) const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    dof_tuple_schema_ids().find(xdof_tuple_ext_id) != dof_tuple_schema_ids().end();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_scaffold::
dof_tuple_schema_id(pod_index_type xdof_tuple_ext_id) const
{
  // Preconditions:

  require(dof_tuple_schema_ids_contains(xdof_tuple_ext_id));

  // Body:

  pod_index_type result =
    dof_tuple_schema_ids().find(xdof_tuple_ext_id)->second;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_scaffold::
dof_tuple_schema_int_id(pod_index_type xdof_tuple_ext_id) const
{
  // Preconditions:

  require(dof_tuple_schema_ids_contains(xdof_tuple_ext_id));

  // Body:

  // Get the dof tuple schema ext id.

  pod_index_type lschema_ext_id = dof_tuple_schema_id(xdof_tuple_ext_id);

  // Translate to an internal id.

  /// @hack the product suposet hack, ver 2.
  /// Not all posets have external ids, let the poset translate the pseudo-id.

  /// @error for section space schema, using the poset schema to convert the
  /// external id assumes the dof tuple was written with the same fiber schema
  /// as the host. This is documented with an (unexecutable) preconditionm in
  /// storage_agent::write. The minimum required to fix this is to write the
  /// external tuple id using the same multi-index method we are using for the
  /// host schema in poset_general_record.

  pod_index_type result =
    structure().schema().get_int_id(lschema_ext_id, _file_id_space_name);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_scaffold::dof_tuple_col_bounds_type&
sheaf::poset_scaffold::
dof_tuple_col_bounds()
{
  return _dof_tuple_col_bounds;
}

const sheaf::poset_scaffold::dof_tuple_col_bounds_type&
sheaf::poset_scaffold::
dof_tuple_col_bounds() const
{
  return _dof_tuple_col_bounds;
}

bool
sheaf::poset_scaffold::
dof_tuple_col_bounds_contains(pod_index_type xdof_tuple_ext_id) const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    dof_tuple_col_bounds().find(xdof_tuple_ext_id) != dof_tuple_col_bounds().end();

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::poset_bounds_descriptor&
sheaf::poset_scaffold::
dof_tuple_col_bound(pod_index_type xdof_tuple_ext_id) const
{
  // Preconditions:

  require(dof_tuple_col_bounds_contains(xdof_tuple_ext_id));

  // Body:

  const poset_bounds_descriptor& result =
    dof_tuple_col_bounds().find(xdof_tuple_ext_id)->second;

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::poset_scaffold::
put_dof_tuple_col_bound(pod_index_type xdof_tuple_ext_id)
{
  // Preconditions:

  require(!dof_tuple_col_bounds_contains(xdof_tuple_ext_id) ||
          dof_tuple_col_bound(xdof_tuple_ext_id) == col_bounds().descriptor());

  // Body:

  dof_tuple_col_bounds_type::value_type
  lmap_pair(xdof_tuple_ext_id, col_bounds().descriptor());

  // Insert will not do anything if entry already present.

  _dof_tuple_col_bounds.insert(lmap_pair);

  // Postconditions:

  ensure(dof_tuple_col_bound(xdof_tuple_ext_id) == col_bounds().descriptor());

  // Exit:

  return;
}

void
sheaf::poset_scaffold::
translate_dof_tuple_col_bounds()
{
  // Preconditions:

  // Body:

  schema_poset_member& lschema = external_schema();
  poset_powerset_state& lschema_powerset = lschema.host()->powerset();

  /// @hack product subposet hack, version 2.
  /// Poset has to tell us which map to use to translate subposet id.

#ifdef DIAGNOSTIC_OUTPUT

  cout << *lsp_id_map << endl;
#endif

  for(dof_tuple_col_bounds_type::iterator itr = _dof_tuple_col_bounds.begin();
      itr != _dof_tuple_col_bounds.end();
      ++itr)
  {
    poset_bounds_descriptor& ldesc = itr->second;

#ifdef DIAGNOSTIC_OUTPUT

    cout << "before: "
    << " mode: " << ldesc.mode()
    << " lb: " << ldesc.lb_id()
    << " ub: " << ldesc.ub_id()
    << endl;
#endif

    // Translate the bounds descriptor to internal ids.

    pod_index_type lb_int_id;
    if(ldesc.lb_is_member())
    {
      lb_int_id = lschema.get_int_id(ldesc.lb_id(), _file_id_space_name);
    }
    else
    {
      lb_int_id = ldesc.lb_id();
    }
    ldesc.put_lb_id(lb_int_id);

    pod_index_type ub_int_id;
    if(ldesc.ub_is_member())
    {
      ub_int_id = lschema.get_int_id(ldesc.ub_id(), _file_id_space_name);
    }
    else
    {
      ub_int_id = ldesc.ub_id();
    }
    ldesc.put_ub_id(ub_int_id);

#ifdef DIAGNOSTIC_OUTPUT

    cout << "after:  "
    << " mode: " << ldesc.mode()
    << " lb: " << ldesc.lb_id()
    << " ub: " << ldesc.ub_id()
    << endl;
#endif

  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::poset_scaffold::dof_tuple_domain_offsets_type&
sheaf::poset_scaffold::
dof_tuple_domain_offsets()
{
  return _dof_tuple_domain_offsets;
}

const sheaf::poset_scaffold::dof_tuple_domain_offsets_type&
sheaf::poset_scaffold::
dof_tuple_domain_offsets() const
{
  return _dof_tuple_domain_offsets;
}

bool
sheaf::poset_scaffold::
dof_tuple_domain_offsets_contains(pod_index_type xdof_tuple_ext_id,
                                  pod_index_type xdomain_key) const
{
  bool result;

  // Preconditions:

  // Body:

  dof_tuple_domain_offsets_type::key_type lkey(xdof_tuple_ext_id, xdomain_key);
  result = (_dof_tuple_domain_offsets.find(lkey) != _dof_tuple_domain_offsets.end());

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_scaffold::
dof_tuple_domain_offset(pod_index_type xdof_tuple_ext_id,
			pod_index_type xdomain_key) const
{
  // Preconditions:

  require(dof_tuple_domain_offsets_contains(xdof_tuple_ext_id, xdomain_key));

  // Body:

  dof_tuple_domain_offsets_type::key_type lkey(xdof_tuple_ext_id, xdomain_key);
  pod_index_type result(_dof_tuple_domain_offsets.find(lkey)->second);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ID_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_scaffold::id_spaces_type&
sheaf::poset_scaffold::
id_spaces()
{
  return _id_spaces;
}

const sheaf::poset_scaffold::id_spaces_type&
sheaf::poset_scaffold::
id_spaces() const
{
  return _id_spaces;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_scaffold*
sheaf::poset_scaffold::
clone() const
{
  poset_scaffold* result;

  // Preconditions:

  // Body:

  result = new poset_scaffold(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::poset_scaffold::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();


    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_scaffold::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const poset_scaffold*>(other) != 0;

  // Postconditions:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
