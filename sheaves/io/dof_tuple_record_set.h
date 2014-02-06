
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

// Interface for class dof_tuple_record_set

#ifndef DOF_TUPLE_RECORD_SET_H
#define DOF_TUPLE_RECORD_SET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef RECORD_SET_H
#include "record_set.h"
#endif

#ifdef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace sheaf
 {
  
///
/// A record_set which contains dof tuple records.
/// Supports both record selection and record restriction (partial records).
///
//// @hack the transparency hack.
//// The io system was originally designed
//// and implemented to provide record selection, restriction, and data
//// type conversion with as little dependence on HDF as possible.
//// A side effect of this was that HDF did not
//// know what the data types in the dof tuple dataset were and the results
//// of h5dump were unreadable. We subsequently hacked the io system to
//// tell HDF what the types were, thus achieving both dump transparency and
//// portability. This left the most of the record and conversion machinery
//// in place, even though it's no longer needed. The io subsystem was
//// hard to understand and maintain before this hack, now it needs to be
//// completely rewritten.
////
class SHEAF_DLL_SPEC dof_tuple_record_set : public record_set
{

public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  dof_tuple_record_set(const dof_tuple_record_set& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual dof_tuple_record_set* clone() const;

  ///
  /// Destructor
  ///
  virtual ~dof_tuple_record_set();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // DOF_TUPLE_RECORD_SET INTERFACE

  ///
  /// Creates an instance attached to the dof tuple record_set
  /// of the poset associated with  xscaffold in the file xfile,
  /// using a record buffer of size xrecord_buffer_ub.
  ///
  dof_tuple_record_set(const sheaf_file& xfile,
                       size_t xrecord_size,
                       int xrecord_buffer_ub,
                       const poset_scaffold& xscaffold);

  ///
  /// The name suffix for this data set.
  ///
  virtual const std::string& suffix() const;

  ///
  /// Opens the record_set.
  ///
  virtual void open();

  ///
  /// Internalize the members of scafold().structure() from disk.
  ///
  void internalize();

  ///
  /// Externalize the members of scafold().structure() to disk.
  ///
  void externalize();

  ///
  /// Externalize the domain specified by
  /// the schema member with index xschema_id.
  ///
  void externalize_domain(const scoped_index& xtuple_ext_id,
                          const scoped_index& xschema_id);

  ///
  /// The size in bytes of data transfers to disk.
  ///
  size_type record_size() const;

  ///
  /// The queue of dof tuple record requests
  ///
  record_queue& queue();

  ///
  /// The queue of dof tuple record requests
  ///
  const record_queue& queue() const;

  ///
  /// Computes the external id for the dof tuple dof tuple with id xtuple_id.
  ///
  pod_index_type compute_ext_id(const scoped_index& xtuple_id);  

  ///
  /// Computes the external size for the portion of the dof tuple
  /// xdof_map which is described by schema xschema.
  ///
  size_type compute_ext_domain_size(const poset_dof_map& xdof_map,
                                 const schema_poset_member& xschema) const;

protected:

  ///
  /// Creates the HDF dataset associated with this.
  ///
  virtual hid_t create_dataset();

  ///
  /// Creates a new HDF internal data type.
  ///
  virtual void create_int_data_type();

  ///
  /// Read and internalizes all the records.
  ///
  void read_records();

  ///
  /// Read the records specified by the selection into the record buffer.
  ///
  void read_selection();

  ///
  /// Write the records specified by the selection into the file.
  ///
  void write_selection();

  ///
  /// Schematize the table and row dof subposets.
  ///
  void schematize();

  ///
  /// The size in bytes of a record.
  ///
  size_type _record_size;

  /// @hack Must use literal 1 in the next 
  /// 2 declarations instead of
  /// static const data member to avoid bug
  /// in MS C++ which interprets initialization
  /// as definition and leads to violation
  /// of one-definition-rule at link time.
  /// Must be same value as DATASPACE_RANK in .cc

  ///
  /// The HDF internal record selection buffer.
  ///
  hsize_t (*_hdf_int_selection)[1];

  ///
  /// The HDF external record selection buffer.
  ///
  hsize_t (*_hdf_ext_selection)[1];

  ///
  /// The HDF record selection buffers upper bound
  ///
  int _hdf_selection_ub;

  ///
  /// The number of records selected.
  ///
  int _hdf_selection_ct;

  ///
  /// The HDF buffer.
  ///
  char* _hdf_buf;

  ///
  /// The HDF buffer upper bound.
  ///
  size_t _hdf_buf_ub;

  /// @issue ambiguous use of term "record".
  /// We're using "record" in two different ways.
  /// The original meaning was that a record was the external
  /// image of a dof tuple. When we began to support variable
  /// length dof tuples, record came to mean buffer record,
  /// the unit of contiguous data transfer to and from disk.
  /// This meaning of record is more or less the same thing
  /// as an HDF chunk.

  ///
  /// The index of the next buffer record to allocate
  /// for a read or write operation.
  ///
  pod_index_type _next_record_pod;

  ///
  /// True if i-th record is full and should be written out.
  ///
  zn_to_bool _record_is_full;

  ///
  /// The record id map for the hdf buffer.
  ///
  record_map<pod_index_type, pod_index_type> _hdf_buf_record_map;

  ///
  /// Scratch buffer for internalizing dofs
  /// that span record boundaries.
  ///
  char* _hdf_scratch_buf;

  ///
  /// The size of the scratch buffer in bytes.
  ///
  size_t _hdf_scratch_buf_ub;

  ///
  /// The record queue.
  ///
  record_queue _record_queue;

  ///
  /// True if current operation is a write operation
  ///
  bool _writing;

  ///
  /// Externalizes all the dofs in the domain described by xxfr_schema.
  ///
  void externalize_all_dofs(schema_poset_member& xxfr_schema,
                            const poset_dof_map& xint_dof_map,
                            char*& xbuf,
                            size_t& xbuf_remainder);

  ///
  /// Internalizes all the dofs in the domain described by xxfr_schema.
  ///
  void internalize_all_dofs(schema_poset_member& xxfr_schema,
                            poset_dof_map& xext_dof_map,
                            char* xbuf,
                            size_t xbuf_remainder);

  ///
  /// Gathers dofs from xext_dof_map and puts them into xint_dof_map.
  ///
  void populate_internal_dof_map(const poset_dof_map& xext_dof_map,
                                 poset_dof_map& xint_dof_map);

  ///
  /// The next record to use in the record buffer.
  ///
  char* get_next_record(char* xbuf);


  ///
  /// The first record associated with the dof tuple
  /// with external id xext_pod.
  ///
  char* get_first_record(pod_index_type xext_pod);

  ///
  /// Brings external record identified by xext_rec_pod
  /// into memory, if necessary, and returns its internal
  /// record id.
  ///
  pod_index_type get_internal_record(pod_index_type xext_rec_pod);

  ///
  /// Advances the offset xoffset to the smallest offset
  /// which is less than or equal to xoffset and which is
  /// the first byte in a record.
  ///
  pod_index_type advance_to_start_of_record(pod_index_type xext_pod);

  ///
  /// Externalize the domain specified by
  /// the schema member with index xschema_id.
  /// Does not initialize record buffer.
  ///
  void externalize_one_domain(const scoped_index& xtuple_id,
                              const scoped_index& xschema_id);

  ///
  /// Attaches the transfer schema to the lesser of the
  /// dof map schema or the domain schema.
  ///
  void attach_transfer_schema(schema_poset_member& xdof_map_schema,
                              const scoped_index& xdomain_schema_id);
};

 } // namespace sheaf

#endif // ifndef DOF_TUPLE_RECORD_SET_H






