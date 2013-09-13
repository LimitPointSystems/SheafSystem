
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

// Interface for class record_set

#ifndef RECORD_SET_H
#define RECORD_SET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POSET_SCAFFOLD_H
#include "poset_scaffold.h"
#endif

#ifndef RECORD_INDEX_H
#include "record_index.h"
#endif

#ifndef STD_HDF5_H
#include "std_hdf5.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class sheaf_file;
class record;
class poset_data_type_map;

///
/// An abstract, indexed collection of records on secondary storage.
///
/// Design overview:
///
/// A record is a group of related data items that the i/o subsystem
/// wants to process as a unit for some reason. There are 5 types
/// of records:
///   poset_general_record
///     various general attributes of a poset
///   member_names_record
///     (index, name) pairs for each entry in the member names table
///   subposet_names_record
///     (index, name) pairs for each entry in the subposet names table
///   id_space_names_record
///     (index, name) pair for each id space
///   member_record
///     all member specific data, including dof_tuple_id, links, and
///     subposet membership, id space membership
///   table_dof_tuple_record.
///     all the dofs for a single table dof tuple
///   dof_tuple_record.
///     all the dofs for a single row dof tuple
///
/// A record_set is a single index array of records. There are
/// three types of record sets:
///   attributes_record_set
///     poset_general_record, table_dof_tuple_record, member_names_record,
///     subposet_names_record, and id_space_names_record
///   member_record_set
///     one member_record for each member
///   dof_tuple_record_set
///     one dof_tuple_record for each dof_tuple
///
/// The attributes_record_set and member_record_set are implemented
/// as HDF datasets containing dataspaces of rank 1 and datatype
/// variable length of char. The single index of the dataspace is
/// the record index and the poset_general_, table_dof_tuple_, member_names_,
/// subposet_names_, id_space_names_and member_ records are all implemented
/// as instances of HDF variable length of char.
///
/// HDF variable length data types require two buffers be allocated:
///  1) a "hdf buffer" storing the hvl_t structs that store the address and
///     length of the variable length data and
///  2) an "external buffer" storing the actual variable length data.
///     this buffer is called "external" because it contains data
///     in external format.
/// In addition, there is an "internal buffer" that stores the data
/// in internal form. The internal buffer collects together the
/// data in the record from whatever diverse locations it is stored
/// in the poset object.

// The hdf buffer is allocated in
// the record set, while the external buffer is currently
// allocated individually in each record, after the length of
// the data has been determined. (This process can and should be
// optimized by some sort of pool allocation scheme for the
// actual data.)
//
// The process for externalizing any of these record sets is the same:
//  allocate the hvl_t buffer in the constructor
//  for each record:
// transfer the poset info to the internal buffer
// initialize the external buffer
// convert the internal buffer to the external buffer
// transfer the external buffer to hdf (i.e. set the hvl_t)
//
// The process for internalizing is essentially the reverse :
//  allocate the hvl_t buffer in the constructor
//  for each record:
// transfer the hdf buffer to the external buffer
//   (i.e. make the external buffer point at the
//   memory allocated by hdf)
// convert the external buffer to the internal buffer
// transfer the internal buffer to the poset
//
//
// The dof_tuple_record_set is different for three reasons:
// 1. Restriction requires random access to individual dofs, not
//    just entire dof tuples. Hence, the dof_tuple_record_set must
//    contain a dataspace of rank 2, the 2 indices being dof_tuple_id
//    and dof id.
// 2. While in general the dofs are of inhomogeneous
//    type and must be implemented as variable length of char, the
//    homogeneous case is an important optimization which must be supported.
//    The data type is thus either variable length of char or some
//    specific primitive type, depending on the case.
// 3. There is no separate internal buffer. The dof tuple itself
//    is used as the internal buffer.
//
//
/// @todo changes to record hierarchy
///  - merge record and variable_length_record
///  - introduce the internal buffer as a separate object,
///    rather than giving the record the features of the internal buffer.
///*/
class SHEAF_DLL_SPEC record_set : public any
{

public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Virtual constructor;
  /// makes a new instance of the same type as this.
  /// Not implemented since this class is abstract.
  ///
  virtual record_set* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;


  // =============================================================================
  // RECORD_SET FACET
  // =============================================================================

  ///
  /// Creates an instance attached to the record_set with
  /// name xname in the file xfile, using record packets
  /// of size xpacket_ub.
  ///
  ///
  record_set(const sheaf_file& xfile, int xrecord_buffer_ub, const poset_scaffold& xscaffold);

  ///
  /// Copy constructor
  ///
  ///
  record_set(const record_set& xother);

  ///
  /// Destructor
  ///
  virtual ~record_set();

  ///
  /// The file this record_set belongs to.
  ///
  const sheaf_file& file() const;

  ///
  /// The name of this data set.
  ///
  string name() const;

  ///
  /// The standard alias for this data set.
  ///
  string alias() const;

  ///
  /// The reserved, standard alias for the namespace in the file
  ///
  static const string& name_space_alias();

  ///
  /// The reserved, standard prefix for namespace dataser names.
  ///
  static const string& name_space_prefix();

  ///
  /// The name suffix for this data set.
  ///
  virtual const string& suffix() const;

  ///
  /// The data set name for a poset with name xname.
  ///
  string data_set_name(const string& xname) const;

  ///
  /// The data set alias for a poset with name xname.
  ///
  string data_set_alias(const string& xname) const;

  ///
  /// The name of the poset this represents, 
  /// extracted from the name of the dataset.
  ///
  string poset_name() const;

  ///
  /// Scaffold for constructing poset associated with this record set (mutable version).
  ///
  poset_scaffold& scaffold();

  ///
  /// Scaffold for constructing poset associated with this record set (const version).
  ///
  const poset_scaffold& scaffold() const;

  ///
  /// Data type map for records in this record set (mutable version)
  ///
  poset_data_type_map& type_map();

  ///
  /// Data type map for records in this record set (const version)
  ///
  const poset_data_type_map& type_map() const;

  ///
  /// Opens the record_set.
  ///
  virtual void open();

  ///
  /// True if this record_set is open.
  ///
  bool is_open() const;

  ///
  /// Closes the record_set.
  ///
  virtual void close();

  ///
  /// The number of active records in record buffer
  ///
  int record_buffer_ct() const;

  ///
  /// The increment the number of active records in record buffer
  ///
  void inc_record_buffer_ct();

  ///
  /// The set the number of active records in record buffer to 0.
  ///
  void reset_record_buffer_ct();

  ///
  /// The maximum number of records the buffer can hold.
  ///
  int record_buffer_ub() const;

  ///
  /// True if there are no active records in the buffer
  ///
  bool record_buffer_is_empty() const;

  ///
  /// True if there are no inactive records in the buffer
  ///
  bool record_buffer_is_full() const;

protected:

  ///
  /// Creates a new HDF datset.
  /// Defined in descendants.
  ///
  virtual hid_t create_dataset() = 0;

  ///
  /// Creates a new HDF internal data type.
  /// Defined in descendants.
  ///
  virtual void create_int_data_type() = 0;

  ///
  /// Extends the dataset dimensions to at least the
  /// dimensions given xdims, an array of length xdims_ub.
  ///
  void extend_dataset(const hsize_t* xdims, int xdims_ub);

  ///
  /// Creates a soft link from alias to the data set.
  ///
  void create_alias();

  ///
  /// Sets the primary name of the dataset from the alias
  ///
  void set_name_from_alias();


  ///
  /// The HDF id for this record set.
  ///
  hid_t hdf_id();

  ///
  /// The HDF id for the external dataspace of this record set.
  ///
  hid_t ext_dataspace_hdf_id();

  ///
  /// The HDF external data type id for this record set.
  ///
  hid_t ext_data_type_hdf_id();

  ///
  /// The rank of the dataspace for the record_set.
  ///
  int ext_dataspace_rank();

  ///
  /// The dimension of xi-th index of the external dataspace
  ///
  hsize_t ext_dataspace_dim(int xi);

  ///
  /// The hdf5 id of the internal dataspace
  /// associated with the record buffer
  ///
  hid_t int_dataspace_hdf_id();

  ///
  /// The HDF internal data type id for this record set.
  ///
  hid_t int_data_type_hdf_id();

  // Default constructor;
  // not supported because can not initialize reference data members
  // record_set();

  ///
  /// The file this record_set belongs to
  ///
  sheaf_file& _file;

  ///
  /// The name of this record_set
  ///
  string _name;

  ///
  /// The standard alias for this record_set
  ///
  string _alias;

  ///
  /// The poset scaffold associated with this.
  ///
  poset_scaffold& _scaffold;

  ///
  /// The HDF id for this record set.
  ///
  hid_t _hdf_id;

  ///
  /// The HDF id for the external dataspace of this record set.
  ///
  hid_t _ext_dataspace_hdf_id;

  ///
  /// The HDF external data type id for this record set.
  ///
  hid_t _ext_data_type_hdf_id;

  ///
  /// The rank of the dataspace for the record_set.
  ///
  int _ext_dataspace_rank;

  ///
  /// The current dimensions of the external dataspace.
  ///
  hsize_t* _ext_dataspace_dims;

  ///
  /// Value indicating an invalid HDf object id.
  //// @issue does HDF have a defined value for this?
  ////
  static const hid_t NOT_AN_HDF_ID;

  ///
  /// The number of active records in record buffer
  ///
  int _record_buffer_ct;

  ///
  /// The maximum number of records the buffer can hold.
  ///
  int _record_buffer_ub;

  ///
  /// The hdf5 id of the dataspace
  /// associated with the record buffer
  ///
  hid_t _int_dataspace_hdf_id;

  ///
  /// The HDF internal data type id for this record set.
  ///
  hid_t _int_data_type_hdf_id;

  ///
  /// Opens and reads the dataset attribute objects from the file.
  /// A stub in this class, intended to be redefined in descendants.
  ///
  virtual void read_dataset_attributes();

  ///
  /// Writes the dataset attribute objects into the file.
  /// A stub in this class, intended to be redefined in descendants.
  ///
  virtual void write_dataset_attributes();

  ///
  /// Reads the attribute with name xatt_name from the file.
  ///
  void read_attribute(const char*& xatt_values,
                      size_type& xatt_ct,
                      const data_converter* xatt_conv,
                      const string& xatt_name);
  ///
  /// Writes the attribute with name xatt_name into the file.
  ///
  void write_attribute(const void* xatt_values,
                       size_type xatt_ct,
                       const data_converter* xatt_conv,
                       const string& xatt_name);


};

} // namespace sheaf

#endif // ifndef RECORD_SET_H






