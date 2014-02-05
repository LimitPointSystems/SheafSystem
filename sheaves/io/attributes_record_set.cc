
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

// Implementation for class attributes_record_set

#include "attributes_record_set.h"

#include "assert_contract.h"
#include "error_message.h"
#include "interval_index_space_handle.h"
#include "namespace_poset.h"
#include "poset_bounds.h"
#include "poset_bounds_descriptor.h"
#include "sheaf_file.h"

using namespace std;

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace
{
  //
  // The rank of the dataspace for the data set.
  //
  const int DATASPACE_RANK = 1;

  //
  // The number of HDF records
  //
  const int RECORD_BUFFER_UB = 12;
}



// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
sheaf::attributes_record_set::
attributes_record_set(const attributes_record_set& xother)
    : record_set(xother),
    _general_attributes(xother._general_attributes),
    _table_dof_tuple(xother._table_dof_tuple),
    _member_names(xother._member_names),
    _member_class_names(xother._member_class_names),
    _subposet_names(xother._subposet_names),
    _id_space_names(xother._id_space_names),
    _dof_tuple_types(xother._dof_tuple_types),
    _dof_tuple_class_names(xother._dof_tuple_class_names),
    _dof_tuple_schema_versions(xother._dof_tuple_schema_versions),
    _dof_tuple_schema_ids(xother._dof_tuple_schema_ids),
    _dof_tuple_col_bounds(xother._dof_tuple_col_bounds),
    _dof_tuple_domain_offsets(xother._dof_tuple_domain_offsets)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



///
sheaf::attributes_record_set*
sheaf::attributes_record_set::
clone() const
{
  attributes_record_set* result;

  // Preconditions:

  // Body:

  result = new attributes_record_set(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
sheaf::attributes_record_set::
~attributes_record_set()
{

  // Preconditions:

  // Body:

  delete [] _ext_dataspace_dims;
  delete [] _hdf_bufs;

  // Postconditions:

  // Exit:

  return;
}


///
bool
sheaf::attributes_record_set::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && record_set::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(record_buffer_ub() == RECORD_BUFFER_UB);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::attributes_record_set::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const attributes_record_set*>(other) != 0;

  // Postconditions:

  return result;

}



// ATTRIBUTES_RECORD_SET INTERFACE

///
sheaf::attributes_record_set::
attributes_record_set(const sheaf_file& xfile, const poset_scaffold& xscaffold)
    : record_set(xfile, RECORD_BUFFER_UB, xscaffold),
      _general_attributes(const_cast<poset_scaffold&>(xscaffold)),
      _table_dof_tuple(const_cast<poset_scaffold&>(xscaffold)),
      _member_names(const_cast<poset_scaffold&>(xscaffold)),
      _member_class_names(const_cast<poset_scaffold&>(xscaffold)),
      _subposet_names(const_cast<poset_scaffold&>(xscaffold)),
      _id_space_names(const_cast<poset_scaffold&>(xscaffold)),
      _dof_tuple_types(const_cast<poset_scaffold&>(xscaffold)),
      _dof_tuple_class_names(const_cast<poset_scaffold&>(xscaffold)),
      _dof_tuple_schema_versions(const_cast<poset_scaffold&>(xscaffold)),
      _dof_tuple_schema_ids(const_cast<poset_scaffold&>(xscaffold)),
      _dof_tuple_col_bounds(const_cast<poset_scaffold&>(xscaffold)),
      _dof_tuple_domain_offsets(const_cast<poset_scaffold&>(xscaffold))
{

  // Preconditions:

  require(xfile.is_open());
  require(!xscaffold.structure().name().empty());

  // Body:

  // _name has been initialized to poset name in record_set;
  // add attributes dataset suffix to it.

  _name  = data_set_name(scaffold().structure().name());
  _alias  = data_set_alias(scaffold().structure().name());

  _ext_dataspace_rank = DATASPACE_RANK;
  _ext_dataspace_dims = new hsize_t[DATASPACE_RANK];

  // Create the HDF record buffer

  _hdf_bufs = new hdf_buf_type[_record_buffer_ub];

  // Create the interior dataspace to describe the HDF record buffer.

  hsize_t linit_dims[DATASPACE_RANK];
  linit_dims[0] = _record_buffer_ub;

  _int_dataspace_hdf_id = H5Screate_simple(DATASPACE_RANK, linit_dims, NULL);
  if(_int_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("can't create interior data space");
  }

  // No records are active yet.

  _record_buffer_ct = 0;

  // Postconditions:

  ensure(invariant());
  ensure(name() == data_set_name(scaffold().structure().name()));
  ensure(alias() == data_set_alias(scaffold().structure().name()));
  ensure(!is_open());
  ensure(record_buffer_ub() == RECORD_BUFFER_UB);
  ensure(record_buffer_ct() == 0);
}

const std::string&
sheaf::attributes_record_set::
suffix() const
{
  // cout << endl << "Entering attributes_record_set::suffix." << endl;

  // Preconditions:


  // Body:

  static const string result(".attributes");

  // Postconditions:


  // Exit:

  // cout << "Leaving attributes_record_set::suffix." << endl;
  return result;
}


///
void
sheaf::attributes_record_set::
internalize()
{
  // Preconditions:

  require(!scaffold().structure().is_external() ? scaffold().structure().state_is_read_write_accessible() : true);

  // Body:

  hdf_buf_type* lhdf_buf = _hdf_bufs;

  // Read all the records.

  read_selection();

  // Internalize the general attributes record.

  _general_attributes.internalize(lhdf_buf);

  // Read the table dof tuple and create the poset if needed.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _table_dof_tuple.internalize(lhdf_buf);

  // Populate the member names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _member_names.internalize(lhdf_buf);

  // Populate the member class names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _member_class_names.internalize(lhdf_buf);

  // Create the subposets and populate the subposet names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _subposet_names.internalize(lhdf_buf);

  // Create the id soaces and populate the id space names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _id_space_names.internalize(lhdf_buf);

  // Populate the dof tuple types table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_types.internalize(lhdf_buf);

  // Populate the dof tuple class names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_class_names.internalize(lhdf_buf);

  // Populate the dof tuple schema versions table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_schema_versions.internalize(lhdf_buf);

  // Populate the dof tuple schema ids table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_schema_ids.internalize(lhdf_buf);

  // Populate the dof tuple col bounds table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_col_bounds.internalize(lhdf_buf);

  // Populate the dof tuple domain offsets table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_domain_offsets.internalize(lhdf_buf);

  // We're finished with the hdf record buffer;
  // let hdf do garbage collection.

  herr_t lstatus =
    H5Dvlen_reclaim(_int_data_type_hdf_id, _int_dataspace_hdf_id, H5P_DEFAULT, _hdf_bufs);

  if(lstatus < 0)
  {
    post_warning_message("Unable to reclaim memory from HDF variable length data.");
  }

  // Postconditions:

  ensure(!scaffold().structure().is_external());
  ensure(scaffold().structure().state_is_read_write_accessible());

  // Exit

  return;
}


///
void
sheaf::attributes_record_set::
externalize()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  hdf_buf_type* lhdf_buf = _hdf_bufs;

  // Externalize the general attributes record.

  _general_attributes.externalize(lhdf_buf);

  // Externalize the table dof tuple.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _table_dof_tuple.externalize(lhdf_buf);

  // Externalize the member names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _member_names.externalize(lhdf_buf);

  // Externalize the member class names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _member_class_names.externalize(lhdf_buf);

  // Externalize the subposet names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _subposet_names.externalize(lhdf_buf);

  // Externalize the id space names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _id_space_names.externalize(lhdf_buf);

  // Externalize the dof tuple types table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_types.externalize(lhdf_buf);

  // Externalize the dof tuple class names table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_class_names.externalize(lhdf_buf);

  // Externalize the dof tuple schema versions table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_schema_versions.externalize(lhdf_buf);

  // Externalize the dof tuple schema ids table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_schema_ids.externalize(lhdf_buf);

  // Externalize the dof tuple col bounds table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_col_bounds.externalize(lhdf_buf);

  // Externalize the dof tuple domain offsets table.

  lhdf_buf++;
  assertion(lhdf_buf < _hdf_bufs+_record_buffer_ub);

  _dof_tuple_domain_offsets.externalize(lhdf_buf);

  // Write all the records.

  write_selection();

  // Postconditions:

  // Exit

  return;
}


///
hid_t
sheaf::attributes_record_set::
create_dataset()
{
  hid_t result;

  // Preconditions:

  require(file().mode() == sheaf_file::READ_WRITE);

  // Body:

  // Create an fixed size dataspace.

  hsize_t linit_dims[DATASPACE_RANK];
  linit_dims[0]  = record_buffer_ub();

  _ext_dataspace_hdf_id = H5Screate_simple(DATASPACE_RANK, linit_dims, NULL);

  // Create the dataset with the internal data type.
  // External data type will be set in record_set::open by querying the dataset.

  result = H5Dcreate1(file().hdf_id(),
                     name().c_str(),
                     _int_data_type_hdf_id,
                     _ext_dataspace_hdf_id,
                     H5P_DEFAULT);

  if(result < 0)
  {
    post_fatal_error_message("Unable to create dataset.");
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

///
void
sheaf::attributes_record_set::
create_int_data_type()
{
  // Preconditions:

  require(file().is_open());

  // Body:

  // Data type is variable length char; see file_type_map::create_internal_types.

  /// @hack the hdf type H5T_C_S1 with len set to H5T_VARIABLE hides the
  /// hdf variable length data type hvl_t, so this class doesn't quite fit the
  /// structure provided by base class variable_length_record. Make it work anyway.

  // Copy the type so we can handle all types the same in record_set::close().

  _int_data_type_hdf_id = H5Tcopy(type_map().converter(C_STRING)->internal_type());

  if(_int_data_type_hdf_id < 0)
  {
    post_fatal_error_message("Can't create internal data type");
  }

  // Postconditions:

  ensure(int_data_type_hdf_id() >= 0);

  // Exit:

  return;
}

///
void
sheaf::attributes_record_set::
read_selection()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Read all the records

  herr_t status = H5Dread(_hdf_id, _int_data_type_hdf_id, H5S_ALL,
                          H5S_ALL, H5P_DEFAULT, _hdf_bufs);
  if(status < 0)
  {
    post_fatal_error_message("unable to read poset attributes dataset");
  }

  // Now the records are active

  _record_buffer_ct = _record_buffer_ub;

  // Postconditions:

  ensure(record_buffer_ct() == record_buffer_ub());

  // Exit

  return;
}


///
void
sheaf::attributes_record_set::
write_selection()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Read all the records

  herr_t status = H5Dwrite(_hdf_id, _ext_data_type_hdf_id,
                           _int_dataspace_hdf_id, _ext_dataspace_hdf_id,
                           H5P_DEFAULT, _hdf_bufs);
  if(status < 0)
  {
    post_fatal_error_message("unable to write poset attributes dataset");
  }

  // Now the records are active

  _record_buffer_ct = _record_buffer_ub;

  // Postconditions:

  ensure(record_buffer_ct() == record_buffer_ub());

  // Exit

  return;
}


// PROTECTED MEMBER FUNCTIONS


///
void
sheaf::attributes_record_set::
read_dataset_attributes()
{
  // Preconditions:

  require(is_open());

  // Body:

  read_toc_bounds_attribute();

  // Postconditions:

  ensure(unexecutable("all attributes opened, read, and closed"));

  // Exit

  return;
}

///
void
sheaf::attributes_record_set::
write_dataset_attributes()
{
  // Preconditions:

  require(is_open());

  // Body:

  write_toc_bounds_attribute();

  // Postconditions:

  ensure(unexecutable("all attributes created, written, and closed"));

  // Exit

  return;
}

const char*
sheaf::attributes_record_set::
TOC_BOUNDS_ATTRIBUTE_NAME()
{
  static const char result[] = "toc_bounds";
  return result;
}

const hsize_t sheaf::attributes_record_set::TOC_BOUNDS_EXTENT = 3;  // mode, lb_id, ub_id

///
void
sheaf::attributes_record_set::
read_toc_bounds_attribute()
{
  // Preconditions:

  require(is_open());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "attributes_record_set::read_toc_bounds_attribute poset name: " << scaffold().structure().name() << endl;
#endif

  herr_t lstatus;

  // Open the toc_bounds attribute.

  hid_t ltoc_bounds_hdf_id = H5Aopen_name(_hdf_id, TOC_BOUNDS_ATTRIBUTE_NAME());
  if(ltoc_bounds_hdf_id >= 0)
  {
    // Open succeeded; get the toc_bounds attribute data space and extent.

    hid_t ltoc_bounds_dataspace_hdf_id = H5Aget_space(ltoc_bounds_hdf_id);
    if(ltoc_bounds_dataspace_hdf_id < 0)
    {
      post_fatal_error_message("Unable to get dof tuple toc_bounds attribute dataspace.");
    }

    hsize_t ltoc_bounds_ct;
    lstatus = H5Sget_simple_extent_dims(ltoc_bounds_dataspace_hdf_id, &ltoc_bounds_ct, NULL);
    if(lstatus < 0)
    {
      post_fatal_error_message("Unable to get dof tuple toc_bounds attribute extent.");
    }

    // Extent must be TOC_BOUNDS_EXTENT.

    assertion(ltoc_bounds_ct == TOC_BOUNDS_EXTENT);

    // Create some storage for the toc_bounds map that HDF can access.

    record_index::pod_type ltoc_bounds[TOC_BOUNDS_EXTENT];

    // Read the toc_bounds attribute

    lstatus = H5Aread(ltoc_bounds_hdf_id,
                      type_map().converter(POD_INDEX_TYPE)->internal_type(),
                      ltoc_bounds);
    if(lstatus < 0)
    {
      post_fatal_error_message("Unable to read dof tuple toc_bounds attribute.");
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << "attribute_record_set::read_toc_bounds_attribute toc_bounds:"
    << " " << ltoc_bounds[0]
    << " " << ltoc_bounds[1]
    << " " << ltoc_bounds[2]
    << endl;
#endif

    // Transfer toc_bounds into the scaffold.

    poset_bounds_descriptor::specification_mode lmode;

    if(ltoc_bounds[0] == 1)
    {
      // Lower bound is member

      lmode = poset_bounds_descriptor::MEMBER_MEMBER;
    }
    else
    {
      // Lower bound is subposet

      lmode = poset_bounds_descriptor::SUBPOSET_MEMBER;
    }

    poset_bounds_descriptor ldesc(lmode, ltoc_bounds[1], ltoc_bounds[2]);

    scaffold().update_toc_bounds(ldesc);

    // Close the attribute and dataspace.

    H5Sclose(ltoc_bounds_dataspace_hdf_id);
    H5Aclose(ltoc_bounds_hdf_id);

  }
  else
  {
    // Open failed.

    post_fatal_error_message("Unable to open toc_bounds attribute");
  }

  // Postconditions:

  // Exit


  return;
}

///
void
sheaf::attributes_record_set::
write_toc_bounds_attribute()
{
  // Preconditions:

  require(is_open());
  require(scaffold().row_bounds().lb_is_singleton() ? 
	  scaffold().member_id_space().contains_hub(scaffold().row_bounds().lb_id()) :
	  true);
  

  // Body:

  // Transfer the toc lb into storage HDF can access.

  record_index::pod_type ltoc_bounds[TOC_BOUNDS_EXTENT];

  pod_index_type lint_lb_id = scaffold().row_bounds().lb_id();

  if(scaffold().row_bounds().lb_is_singleton())
  {
    // lb_id is a member index

    ltoc_bounds[0] = 1;

    pod_index_type lext_lb_id = scaffold().member_id_space().pod(lint_lb_id);
    if(is_valid(lext_lb_id))
    {
      ltoc_bounds[1] = lext_lb_id;
    }
    else
    {
      // Should never reach here.

      post_fatal_error_message("Invalid lower bound for table of contents.");
    }
  }
  else
  {
    // lb_id is a subposet id.

    ltoc_bounds[0] = 0;
    ltoc_bounds[1] = scaffold().subposet_id_space().pod(lint_lb_id);
  }

  // Upper bound of toc may not have been written out yet and so may not
  // have an entry in the index space. But the upper bound is top by definition
  // and the external id of top is the same as the internal id.
  /// @issue this won't be true when we replace HDF variable length data types
  /// with libSheaf variable length records.

  ltoc_bounds[2] = TOP_INDEX;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "attribute_record_set::write_toc_bounds_attribute for poset: "
  << scaffold().structure().name()
  << " toc_bounds:"
  << " " << ltoc_bounds[0]
  << " " << ltoc_bounds[1]
  << " " << ltoc_bounds[2]
  << endl;
#endif

  herr_t lstatus;

  // Open the toc_bounds attribute.

  hid_t ltoc_bounds_hdf_id = H5Aopen_name(_hdf_id, TOC_BOUNDS_ATTRIBUTE_NAME());
  if(ltoc_bounds_hdf_id < 0)
  {
    // toc_bounds attribute doesn't exist yet; create it.

    // Create the toc_bounds attribute data space.

    hid_t ltoc_bounds_dataspace_hdf_id = H5Screate(H5S_SIMPLE);
    if(ltoc_bounds_dataspace_hdf_id < 0)
    {
      post_fatal_error_message("Unable to create dof tuple toc_bounds attribute dataspace.");
    }

    // Set the extent of the dataspace.

    lstatus = H5Sset_extent_simple(ltoc_bounds_dataspace_hdf_id, 1, &TOC_BOUNDS_EXTENT, NULL);
    if(lstatus < 0)
    {
      post_fatal_error_message("Unable to set dof tuple toc_bounds attribute extent.");
    }

    // Create the toc_bounds attribute.

    //    ltoc_bounds_hdf_id = H5Acreate(_hdf_id,
    ltoc_bounds_hdf_id = H5Acreate1(_hdf_id,
                                   TOC_BOUNDS_ATTRIBUTE_NAME(),
                                   type_map().converter(POD_INDEX_TYPE)->external_type(),
                                   ltoc_bounds_dataspace_hdf_id,
                                   H5P_DEFAULT);

    if(ltoc_bounds_hdf_id < 0)
    {
      post_fatal_error_message("Unable to create dof tuple toc_bounds attribute.");
    }

    // Close the attribute dataspace.

    H5Sclose(ltoc_bounds_dataspace_hdf_id);
  }

  // Write the toc_bounds attribute.

  lstatus = H5Awrite(ltoc_bounds_hdf_id,
                     type_map().converter(POD_INDEX_TYPE)->internal_type(),
                     ltoc_bounds);
  if(lstatus < 0)
  {
    post_fatal_error_message("Unable to write dof tuple toc_bounds attribute.");
  }

  // Close the attribute.

  H5Aclose(ltoc_bounds_hdf_id);

  // Postconditions:

  ensure(unexecutable("all attributes created, written, and closed"));

  // Exit

  return;
}





