
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

// Interface for class attributes_record_set

#ifndef COM_LIMITPOINT_SHEAF_ATTRIBUTES_RECORD_SET_H
#define COM_LIMITPOINT_SHEAF_ATTRIBUTES_RECORD_SET_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DOF_TUPLE_CLASS_NAMES_RECORD_H
#include "ComLimitPoint/sheaf/dof_tuple_class_names_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DOF_TUPLE_COL_BOUNDS_RECORD_H
#include "ComLimitPoint/sheaf/dof_tuple_col_bounds_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DOF_TUPLE_DOMAIN_OFFSETS_RECORD_H
#include "ComLimitPoint/sheaf/dof_tuple_domain_offsets_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DOF_TUPLE_SCHEMA_IDS_RECORD_H
#include "ComLimitPoint/sheaf/dof_tuple_schema_ids_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DOF_TUPLE_SCHEMA_VERSIONS_RECORD_H
#include "ComLimitPoint/sheaf/dof_tuple_schema_versions_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DOF_TUPLE_TYPES_RECORD_H
#include "ComLimitPoint/sheaf/dof_tuple_types_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ID_SPACE_NAMES_RECORD_H
#include "ComLimitPoint/sheaf/id_space_names_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_RECORD_SET_H
#include "ComLimitPoint/sheaf/record_set.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_MEMBER_NAMES_RECORD_H
#include "ComLimitPoint/sheaf/member_names_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_MEMBER_CLASS_NAMES_RECORD_H
#include "ComLimitPoint/sheaf/member_class_names_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_GENERAL_RECORD_H
#include "ComLimitPoint/sheaf/poset_general_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SUBPOSET_NAMES_RECORD_H
#include "ComLimitPoint/sheaf/subposet_names_record.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_TABLE_DOF_TUPLE_RECORD_H
#include "ComLimitPoint/sheaf/table_dof_tuple_record.h"
#endif

namespace sheaf
{
  
///
/// A record set for storing various poset attributes.
///
class SHEAF_DLL_SPEC attributes_record_set : public record_set
{

public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  attributes_record_set(const attributes_record_set& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual attributes_record_set* clone() const;

  ///
  /// Destructor
  ///
  virtual ~attributes_record_set();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ATTRIBUTES_RECORD_SET INTERFACE

  ///
  /// Creates an instance attached to the record_set with
  /// name xname in the file xfile, with a record buffer
  /// containing xbuffer_ub records.
  ///
  ///
  attributes_record_set(const sheaf_file& xfile, const poset_scaffold& xscaffold);

  ///
  /// The name suffix for this data set.
  ///
  virtual const std::string& suffix() const;

  ///
  /// Internalize the record set from disk.
  ///
  void internalize();

  ///
  /// Externalize the reccord set to disk.
  ///
  void externalize();
  
protected:

  // Default constructor;
  // not supported because can not initialize reference data members.
  // attributes_record_set();

  ///
  /// Creates the HDF dataset associated with this.
  ///
  virtual hid_t create_dataset();

  ///
  /// Creates a new HDF internal data type.
  ///
  virtual void create_int_data_type();

  ///
  /// Reads the dataset attribute objects from the file.
  ///
  virtual void read_dataset_attributes();

  ///
  /// Writes the dataset attribute objects into the file.
  ///
  virtual void write_dataset_attributes();

  ///
  /// The name of the table of contents lower bound attribute.
  ///
  static const char* TOC_BOUNDS_ATTRIBUTE_NAME();

  ///
  /// The extent of the table of contents lower bound attribute dataspace.
  ///
  static const hsize_t TOC_BOUNDS_EXTENT;

  ///
  /// Reads the table of contents lower bound attribute into the file.
  ///
  virtual void read_toc_bounds_attribute();

  ///
  /// Writes the table of contents lower bound attribute into the file.
  ///
  virtual void write_toc_bounds_attribute();

private:

  ///
  /// Reads all the records in the record set.
  ///
  void read_selection();

  ///
  /// Writes all the records in the record set.
  ///
  void write_selection();

  ///
  /// The type of the hdf record buffers.
  ///
  typedef attributes_record::hdf_buf_type  hdf_buf_type;

  ///
  /// The HDF record buffers
  ///
  hdf_buf_type* _hdf_bufs;

  ///
  /// The poset general attributes record.
  ///
  poset_general_record _general_attributes;

  ///
  /// The table dof tuple record.
  ///
  table_dof_tuple_record _table_dof_tuple;

  ///
  /// The member names record.
  ///
  member_names_record _member_names;

  ///
  /// The member class names record.
  ///
  member_class_names_record _member_class_names;

  ///
  /// The subposet names record.
  ///
  subposet_names_record _subposet_names;

  ///
  /// The id space names record.
  ///
  id_space_names_record _id_space_names;

  ///
  /// The dof tuple types record.
  ///
  dof_tuple_types_record _dof_tuple_types;

  ///
  /// The dof tuple class names record.
  ///
  dof_tuple_class_names_record _dof_tuple_class_names;

  ///
  /// The dof tuple schema versions record.
  ///
  dof_tuple_schema_versions_record _dof_tuple_schema_versions;

  ///
  /// The dof tuple schema ids record.
  ///
  dof_tuple_schema_ids_record _dof_tuple_schema_ids;

  ///
  /// The dof tuple col bounds record.
  ///
  dof_tuple_col_bounds_record _dof_tuple_col_bounds;

  ///
  /// The dof tuple domain offsets record.
  ///
  dof_tuple_domain_offsets_record _dof_tuple_domain_offsets;
};

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_ATTRIBUTES_RECORD_SET_H






