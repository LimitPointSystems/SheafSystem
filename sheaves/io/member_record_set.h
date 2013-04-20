
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class member_record_set

#ifndef MEMBER_RECORD_SET_H
#define MEMBER_RECORD_SET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef RECORD_SET_H
#include "record_set.h"
#endif

#ifndef INTERVAL_INDEX_SPACE_RECORD_H
#include "interval_index_space_record.h"
#endif

#ifndef MEMBER_RECORD_H
#include "member_record.h"
#endif

#ifndef INTERVAL_INDEX_SPACE_HANDLE_H
#include "interval_index_space_handle.h"
#endif


namespace sheaf
{

class dof_tuple_record_set;
class index_equivalence_iterator;
  
///
/// A record_set containing records of type member_record.
///
class SHEAF_DLL_SPEC member_record_set : public record_set
{

public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual member_record_set* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // =============================================================================
  // MEMBER_RECORD_SET FACET
  // =============================================================================

  ///
  /// Creates an instance attached to the record_set with
  /// name xname in the file xfile, using record packets
  /// of size xpacket_ub.
  ///
  ///
  member_record_set(const sheaf_file& xfile,
                    int xbuffer_ub,
                    const poset_scaffold& xscaffold,
                    const dof_tuple_record_set& xdof_tuple_records);

  ///
  /// Copy constructor
  ///
  ///
  member_record_set(const member_record_set& xother);

  ///
  /// Destructor
  ///
  virtual ~member_record_set();

  ///
  /// Internalize the members of scafold().structure() from disk.
  ///
  void internalize(pod_index_type xmax_row_int_id);

  ///
  /// Internalize the members of scafold().structure() from disk.
  ///
  void internalize(const scoped_index& xmax_row_int_id);

  ///
  /// Externalize the members of scafold().structure() to disk.
  ///
  void externalize(pod_index_type xmax_row_int_id);

  ///
  /// Externalize the members of scafold().structure() to disk.
  ///
  void externalize(const scoped_index& xmax_row_int_id);

  ///
  /// The dof tuple record set associated with this.
  ///
  dof_tuple_record_set& dof_tuple_records();

  ///
  /// The current member record.
  ///
  const member_record& record() const;

  ///
  /// The first record used for members;
  /// the record following the id space records.
  ///
  static pod_index_type first_member_record();

protected:

  // Default constructor;
  // not supported because can not initialize reference data members.
  // member_record_set();

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
  void read_record(const record_index& xext_id);

  ///
  /// Read the records specified by the selection into the record buffer.
  ///
  void read_selection();

  ///
  /// Write the records specified by the selection into the file.
  ///
  void write_selection();

  ///
  /// Create the internal dataspace.
  ///
  void make_internal_dataspace();

private:

  ///
  /// The hdf type for member records.
  ///
  hid_t _member_record_type;

  ///
  /// The HDF record buffers
  ///
  hvl_t* _hdf_bufs;

  ///
  /// Deletes the external record buffers.
  ///
  void delete_external_buffers();

  ///
  /// Deletes the hdf record buffers.
  ///
  void delete_hdf_buffers();

  /// @hack Must use literal 1 below instead of
  /// static const data member to avoid bug
  /// in MS C++ which interprets initialization
  /// as definition and leads to violation
  /// of one-definition-rule at link time.
  /// Must be same value as DATASPACE_RANK in .cc

  ///
  /// The record selection buffer.
  ///
  hsize_t (*_hdf_selection)[1];

  ///
  /// The transfer record
  ///
  member_record _record;

  ///
  /// The poset scaffold associated with this.
  ///
  poset_scaffold& _scaffold;

  ///
  /// The dof tuple record set associated with this.
  ///
  dof_tuple_record_set& _dof_tuple_records;

  ///
  /// Writes the record buffer to disk.
  ///
  void write_record_buffer();

  ///
  /// Removes dangling references from upper covers.
  ///
  void clean_upper_covers();

  ///
  /// File id space transfer record.
  ///
  interval_index_space_record _id_space_record;

  ///
  /// Id space from internal member id to file record id.
  ///
  interval_index_space_handle _record_id_space;

  ///
  /// Record id for record id space.
  ///
  static pod_index_type record_id_space_record();
  
  ///
  /// Record id for interval id space.
  ///
  static pod_index_type interval_id_space_record();

  ///
  /// Name of the interval member space.
  ///
  string _interval_id_space_name;

  ///
  /// Id space from internal member id to interval member.
  ///
  interval_index_space_handle _interval_id_space; 

  ///
  /// Writes the file id space record.
  ///
  void write_id_space_record(const interval_index_space_handle& xid_space, pod_index_type xrecord_id);
  
  ///
  /// Reads the file id space record.
  ///
  void read_id_space_record(interval_index_space_handle& xid_space, pod_index_type xrecord_id);
  
  ///
  /// Read the member with index xindex.
  ///
  void read_member(const scoped_index& xindex, record_index& xext_id);

  ///
  /// Create the record and interval id spaces for the down set of xmbr;
  /// record id space preserves hub id order of crg.
  ///
  void make_idorder_file_id_spaces(const abstract_poset_member& xmbr);

};
 
} // namespace sheaf

#endif // ifndef MEMBER_RECORD_SET_H






