
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

// Implementation for class poset_general_record

#include "poset_general_record.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "poset.h"
#include "poset_bounds.h"
#include "std_sstream.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// Copy constructor
///
sheaf::poset_general_record::
poset_general_record(const poset_general_record& xother)
  : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

// Virtual constructor
///
sheaf::poset_general_record*
sheaf::poset_general_record::
clone() const
{
  poset_general_record* result;

  // Preconditions:

  // Body:

  result = new poset_general_record(*this);


  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// Destructor
///
sheaf::poset_general_record::
~poset_general_record()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

// Class invariant
///
bool
sheaf::poset_general_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(attributes_record::invariant());

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

// Conformance test
///
bool
sheaf::poset_general_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const poset_general_record*>(other) != 0;

  // Postconditions:

  return result;

}

// POSET_GENERAL_RECORD INTERFACE

///
sheaf::poset_general_record::
poset_general_record(poset_scaffold& xscaffold)
  : attributes_record(xscaffold)
{

  // Preconditions:


  // Body:

  // Get the data converters

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
sheaf::poset_general_record::
transfer_internal_buffer_to_poset()
{
  // Preconditions:

  require(is_internal());
  require(!scaffold().structure().is_external() ?
          scaffold().structure().state_is_read_write_accessible() :
          true);
  require(scaffold().name_space()->state_is_read_accessible());


  // Body:

  // Initialize the stream.

  stringstream lstream(_str_buf);

  lstream << boolalpha;
  
  // Skip the header line:

  lstream.ignore(numeric_limits<streamsize>::max(), '\n');

  // Read each attribute; skipping the name in front and the newline at the end.

  string lskip_name;
  char lend;

  // General attributes

  int ltype_id;
  lstream >> lskip_name >> ltype_id;

  int lmember_ct;
  lstream >> lskip_name >> lmember_ct;

  int ldof_tuple_ct;
  lstream >> lskip_name >> ldof_tuple_ct;

  primitive_type lrow_dof_tuple_type; ///@issue is this field obsolete?
  lstream >> lskip_name >> lrow_dof_tuple_type;

  bool lis_versioned;
  lstream >> lskip_name >> lis_versioned;

  // Subposet attributes

  int lsubposet_ct;
  lstream >> lskip_name >> lsubposet_ct;

  // Type attributes

  int ltoc_type;
  lstream >> lskip_name >> ltoc_type;

  int ldof_tuple_id_type;
  lstream >> lskip_name >> ldof_tuple_id_type;

  int loffset_type;
  lstream >> lskip_name >> loffset_type;

  // Schema attributes

  scoped_index::pod_type lschema_poset_ext_id_pod;
  lstream >> lskip_name >> lschema_poset_ext_id_pod;

  scoped_index::pod_type lschema_member_ext_id_pod;
  lstream >> lskip_name >> lschema_member_ext_id_pod;

  scoped_index::pod_type lbase_space_ext_id_pod;
  lstream >> lskip_name >> lbase_space_ext_id_pod;

  scoped_index::pod_type lfiber_schema_ext_id_pod;
  lstream >> lskip_name >> lfiber_schema_ext_id_pod;

  scoped_index::pod_type llocal_schema_ext_id_pod;
  lstream >> lskip_name >> llocal_schema_ext_id_pod;

  int lschema_version;
  lstream >> lskip_name >> lschema_version;

  // Table of contents attributes.

  bool llb_is_singleton;
  lstream >> lskip_name >> llb_is_singleton;

  int llb_id;
  lstream >> lskip_name >> llb_id;

  int lub_id;
  lstream >> lskip_name >> lub_id;

  // Translate the schema poset external id to internal.

  namespace_poset* lns = scaffold().name_space();

  pod_index_type lschema_poset_int_id =
    lns->get_int_id(lschema_poset_ext_id_pod,
                    scaffold().file_id_space_name(),
                    false);

  // Get a handle to the schema poset.

  poset_state_handle& lschema_poset = lns->member_poset(lschema_poset_int_id, false);

  // Get a handle to the external schema.

  schema_poset_member* lext_schema =
    lschema_poset.new_schema_handle(scaffold().file_id_space_name(),
				    lschema_member_ext_id_pod,
				    lbase_space_ext_id_pod,
				    lfiber_schema_ext_id_pod,
				    llocal_schema_ext_id_pod);

  scaffold().initialize_schema_for_read(lext_schema, lschema_version);

  // Set is_versioned in the scaffold for use in subposet_names_record.

  scaffold().is_versioned() = lis_versioned;

  /// @todo implement mechanism to reserve() eventual size of CRG and powerset,
  /// so we can use _member_ct and _subposet_ct. Will also require storing the total
  /// subposet ct, not just the non-dof subposet ct.
  /// See transfer_poset_to_internal_buffer.

  // We know how many subposet there are now, but we can't
  // create the subposets and load the scaffold subposet vector
  // yet because we can't create the poset state until we've read the table dofs
  // in table_dof_tuple_record::internalize.
  // So just set the size of the scaffold subposet vector now.
  // We'll create and name the subposets in 
  // subposet_names_record::transfer_internal_buffer_to_poset.

  scaffold().subposets().reserve(lsubposet_ct);
  scaffold().subposets().resize(lsubposet_ct);

  // Initialize the member record type aliases.

  scaffold().put_member_record_type_aliases(ltoc_type,
					    ldof_tuple_id_type,
					    loffset_type);


  // Postconditions:

  ensure(scaffold().internal_schema().is_attached());
  ensure(scaffold().transfer_schema().is_attached());
  ensure(scaffold().external_schema().is_attached());

  // Exit

  return;
}

///
void
sheaf::poset_general_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  stringstream lstream;

  lstream << boolalpha;
  
  lstream << "General attributes:" << endl;


  // General attributes

  lstream << "type_id: "
	  << scaffold().structure().type_id()
	  << endl;

  lstream << "member_ct: "
	  << scaffold().structure().member_ct()
	  << endl;
  lstream << "row_dof_tuple_ct: "
	  << scaffold().structure().row_dof_tuple_ct()
	  << endl;

  lstream << "row_dof_tuple_type: "
	  << scaffold().structure().schema().row_dof_tuple_type()
	  << endl;

  lstream << "is_versioned: "
	  << (scaffold().structure().version_ct() > 1)
	  << endl;

  // Subposet attributes

  lstream << "subposet_ct: "
	  << scaffold().subposets().size()
	  << endl;

  // Type attributes

  lstream << "toc_converter: "
	  << type_map().toc_converter()->internal_index()
	  << endl;

  lstream << "dof_tuple_id_converter: "
	  << type_map().dof_tuple_id_converter()->internal_index()
	  << endl;

  lstream << "offset_converter: "
	  << type_map().offset_converter()->internal_index()
	  << endl;

  // Schema attributes.

  // Get external ids for schema poset and schema member:
  /// @hack the product subposet hack, ver 2.

  pod_index_type lschema_poset_ext_id;
  pod_index_type lschema_member_ext_id;
  pod_index_type lbase_space_ext_id;
  pod_index_type lfiber_schema_ext_id;
  pod_index_type llocal_schema_ext_id;

  scaffold().external_schema().get_ext_ids(scaffold().file_id_space_name(),
					   lschema_poset_ext_id,
					   lschema_member_ext_id,
					   lbase_space_ext_id,
					   lfiber_schema_ext_id,
					   llocal_schema_ext_id);

  lstream << "schema_poset_ext_id: " << lschema_poset_ext_id << endl;
  lstream << "schema_member_ext_id: " << lschema_member_ext_id << endl;
  lstream << "base_space_ext_id: " << lbase_space_ext_id << endl;
  lstream << "fiber_schema_ext_id: " << lfiber_schema_ext_id << endl;
  lstream << "local_schema_ext_id: " << llocal_schema_ext_id << endl;

  lstream << "xfr_schema_version: " << scaffold().transfer_schema().version() << endl;

  // Table of contents attributes

  bool lb_is_singleton = scaffold().row_bounds().lb_is_singleton();

  lstream << "lb_is_singleton: " << lb_is_singleton << endl;


  pod_index_type lint_lb_id = scaffold().row_bounds().lb_id();

  if(lb_is_singleton)
  {
    // lb_id is a member index

    lstream << "lb_id: "
	    << scaffold().member_id_space().pod(lint_lb_id)
	    << endl;
  }
  else
  {
    // lb_id is a subpose_id.

    lstream << "lb_id: "
	    << scaffold().subposet_id_space().pod(lint_lb_id)
	    << endl;
  }

  // Upper bound of toc may not have been written out yet and so may not
  // have an entry in the index map. But the upper bound is top by definition
  // and the external id of top is the same as the internal id.
  /// @issue this won't be true when we replace HDF variable length data types
  /// with libSheaf variable length records.

  lstream << "ub_id: " << TOP_INDEX << endl;

  // Have to copy stringstream to string
  // because can't get C string from stringstream.
  // Could use strstream, but that's error-prone and not portable.

  _str_buf = lstream.str();

  put_is_internal(true);
  put_is_external(false);

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit

  return;
}


