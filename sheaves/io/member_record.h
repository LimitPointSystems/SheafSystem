
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Interface for class member_record

#ifndef MEMBER_RECORD_H
#define MEMBER_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STD_BITSET_H
#include "std_bitset.h"
#endif

#ifndef STD_LIMITS_H
#include "std_limits.h"
#endif

#ifndef VARIABLE_LENGTH_RECORD_H
#include "variable_length_record.h"
#endif

namespace sheaf
{

class member_record_set;
class poset_dof_iterator;
  
///
/// A record buffer for transferring member data
/// between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC member_record : public variable_length_record
{
  // ===========================================================
  // MEMBER_RECORD FACET
  // ===========================================================

public:

  ///
  /// Creates an instance in record set xhost
  /// for reading or writing member data.
  ///
  member_record(member_record_set& xhost);

  ///
  /// Copy constructor
  ///
  member_record(const member_record& xother);

  ///
  /// Destructor
  ///
  virtual ~member_record();

  ///
  /// The implicit interval object for the current member, if any.
  ///
  implicit_crg_interval* interval() const;

  ///
  /// True if and only if member represented 
  /// by this record is fully resident after read.
  ///
  bool is_resident() const;

protected:

  // Default constructor.
  // Default construction prohibited because scaffold must be initialized
  // inline member_record() {} ;

private:

  ///
  /// Type for table of contents
  ///
  typedef bitset<numeric_limits<pod_index_type>::digits> toc_type;

  ///
  /// Names for the toc bit fields.
  ///
  enum toc_bit_field_type
  {
    /// @issue portability.
    /// Don't use first and last bits, they're the
    /// most likely to cause portability problems.
    /// See extenalize_toc for a fuller discussion.

    FIRST_BIT, // Not used.
    IS_JIM,
    HAS_NAMES,
    IS_INTERVAL,
    HAS_PRIVATE_DATA,
    HAS_DOF_TUPLE_IDS,
    HAS_LOWER_COVER,
    HAS_UPPER_COVER,
    HAS_TOC_SUBPOSET_IDS,
    HAS_SUBPOSET_IDS,
    HAS_EQV_IDS,

    // Use the remaining bits to store subposet membership.

    SUBPOSET_BITS_BEGIN,
    SUBPOSET_BITS_END = numeric_limits<pod_index_type>::digits - 1,
    LAST_BIT = SUBPOSET_BITS_END // Not used.
  };

  // Internal buffer

  toc_type _toc;
  block<pod_index_type> _private_data;
  block<pod_index_type> _dof_tuple_ids;
  block<pod_index_type> _lower_cover;
  block<pod_index_type> _upper_cover;
  block<pod_index_type> _subposet_ids;
  block<pod_index_type> _eqv_ids;
  block<string> _names;


  // External buffer layout:
  //  table of contents
  //  private data count
  //  private data
  //  dof tuple id count
  //  dof tuple ids
  //  lower cover count
  //  lower cover
  //  upper cover count
  //  upper cover
  //  subposet_ids count
  //  subposet_ids
  //  eqv_ids

  // Offsets into external buffer

  size_t _end_offset;

  ///
  /// The internal id for the current member.
  ///
  scoped_index _mbr_id;
  
  ///
  /// The external id for the current member.
  ///
  record_index _ext_id;

  ///
  /// The poset for the current member.
  ///
  poset_state_handle* _poset;

  ///
  /// The implicit interval object for the current member, if any.
  ///
  implicit_crg_interval* _interval;

  ///
  /// True if and only if member represented 
  /// by this record is fully resident after read.
  ///
  bool _is_resident;  

  ///
  /// The record set this is a member of.
  ///
  member_record_set& _host;

  ///
  /// The record set this is a member of (mutable version).
  ///
  member_record_set& host();

  ///
  /// The record set this is a member of (const version).
  ///
  const member_record_set& host() const;

  // ===========================================================
  // EQUIVALENCE ITERATOR FACET
  // ===========================================================

public:

  ///
  /// Create the equivalence iterator.
  ///
  void new_equivalence_iterator();

  ///
  /// Destroy the equivalence iterator.
  ///
  void delete_equivalence_iterator();

  ///
  /// True, if the equivalence iterator is initialized.
  ///
  bool has_equivalence_iterator() const;

protected:

private:

  ///
  /// The id equivalence iterator.
  ///
  index_equivalence_iterator* _eqv_itr;

  ///
  /// The id equivalence iterator with representive id xrep_id.
  ///
  index_equivalence_iterator& equivalence_iterator(const scoped_index& xrep_id);

  // ===========================================================
  // EXTERNAL SIZE FACET
  // ===========================================================

public:
 
  ///
  /// The size of the member record in external form.
  ///
  size_type external_size(const scoped_index& xmbr_id);

protected:
private:

  ///
  /// External size of private data field.
  ///
  size_type private_data_external_size();

  //   ///
  //   /// External size of id map field.
  //   ///
  //   size_type id_map_data_external_size();

  ///
  /// External size of dof tuple ids field.
  ///
  size_type dof_tuple_ids_external_size();

  ///
  /// External size of lower cover field.
  ///
  size_type lower_cover_external_size();

  ///
  /// External size of upper cover field.
  ///
  size_type upper_cover_external_size();

  ///
  /// External size of subposet ids field.
  ///
  size_type subposet_ids_external_size();

  ///
  /// External size of equivalent ids field.
  ///
  size_type eqv_ids_external_size();

  ///
  /// External size of toc field.
  ///
  size_type toc_external_size();

  // ===========================================================
  // WRITE FACET
  // ===========================================================

public:

  ///
  /// Converts the record from internal to external form
  ///
  void externalize(const scoped_index& xmbr_id, hvl_t* xhdf_buffer);

private:

  ///
  /// Gahters data from the member with index xmbr_id into the internal buffer.
  ///
  void transfer_member_to_internal_buffer(const scoped_index& xmbr_id);

  ///
  /// Clears the internal buffer.
  ///
  void clear_internal_buffer();

  ///
  /// Transfer member data to toc field.
  ///
  void transfer_member_to_toc(const scoped_index& xmbr_id);

  ///
  /// Transfer member interval data to private data field.
  ///
  void transfer_interval_to_private_data(const scoped_index& xmbr_id);

  ///
  /// Transfer member data to dof tuple id field.
  ///
  void transfer_member_to_dof_tuple_ids(const scoped_index& xmbr_id);

  ///
  /// Transfer member interval data to dof tuple id field.
  ///
  void transfer_interval_to_dof_tuple_ids(const scoped_index& xmbr_id);

  ///
  /// Transfer member data to lower cover field.
  ///
  void transfer_member_to_lower_cover(const scoped_index& xmbr_id);

  ///
  /// Transfer member data to upper cover field.
  ///
  void transfer_member_to_upper_cover(const scoped_index& xmbr_id);

  ///
  /// Transfer member data to subposet ids field.
  ///
  void transfer_member_to_subposet_ids(const scoped_index& xmbr_id);

  ///
  /// Transfer member data to equivalent ids field.
  ///
  void transfer_member_to_eqv_ids(const scoped_index& xmbr_id);

  ///
  /// Transfer member to name map.
  ///
  void transfer_member_to_names(const scoped_index& xmbr_id);

  ///
  /// Transfer interval member to class names and parameters map.
  ///
  void transfer_interval_to_class_names(const scoped_index& xmbr_id);

  ///
  /// Converts the internal buffer to external form
  /// and places the result in the external buffer.
  ///
  void convert_internal_buffer_to_external_buffer();

  ///
  /// Initializes the external buffer from the internal buffer.
  ///
  virtual void initialize_external_buffer();

  ///
  /// Converts the toc field from internal to external format.
  ////
  void externalize_toc(size_t& xnext_field_offset);

  ///
  /// Converts the private_data.ct() field from internal to external format.
  ////
  void externalize_private_data_ct(size_t& xnext_field_offset);

  ///
  /// Converts the private_data field from internal to external format.
  ////
  void externalize_private_data(size_t& xnext_field_offset);

  ///
  /// Converts the dof_tuple_ids.ct() field from internal to external format.
  ////
  void externalize_dof_tuple_ids_ct(size_t& xnext_field_offset);

  ///
  /// Converts the dof_tuple_ids field from internal to external format.
  ////
  void externalize_dof_tuple_ids(size_t& xnext_field_offset);

  ///
  /// Converts the lower_cover_ct field from internal to external format.
  ////
  void externalize_lower_cover_ct(size_t& xnext_field_offset);

  ///
  /// Converts the lower_cover field from internal to external format.
  ////
  void externalize_lower_cover(size_t& xnext_field_offset);

  ///
  /// Converts the upper_cover_ct field from internal to external format.
  ////
  void externalize_upper_cover_ct(size_t& xnext_field_offset);

  ///
  /// Converts the upper_cover field from internal to external format.
  ////
  void externalize_upper_cover(size_t& xnext_field_offset);

  ///
  /// Converts the subposet_ids_ct field from internal to external format.
  ////
  void externalize_subposet_ids_ct(size_t& xnext_field_offset);

  ///
  /// Converts the subposet_ids fields from internal to external format.
  ///
  void externalize_subposet_ids(size_t& xnext_field_offset);

  ///
  /// Converts the eqv_ids fields from internal to external format.
  ///
  void externalize_eqv_ids(size_t& xnext_field_offset);

  ///
  /// Initializes the HDF buffer xbuf from the external buffer.
  ///
  void transfer_external_buffer_to_HDF(hvl_t* xbuf);

  // ===========================================================
  // READ FACET
  // ===========================================================

public:

  ///
  /// Converts the record from external to internal form
  ///
  void internalize(hvl_t* xhdf_buffer, const scoped_index& xmbr_id);

private:

  ///
  /// Initializes the external buffer from xbuf.
  ///
  void transfer_HDF_to_external_buffer(hvl_t* xbuf);

  ///
  /// Converts the external buffer to internal form
  /// and places the result in the internal buffer.
  ///
  void convert_external_buffer_to_internal_buffer();

  ///
  /// Converts the toc field from external to internal format.
  ////
  void internalize_toc(size_t& xnext_field_offset);

  ///
  /// Converts the private_data_ct field from external to internal format.
  ////
  void internalize_private_data_ct(size_t& xnext_field_offset);

  ///
  /// Converts the private_data field from external to internal format.
  ////
  void internalize_private_data(size_t& xnext_field_offset);

  ///
  /// Converts the dof_tuple_ids_ct field from external to internal format.
  ////
  void internalize_dof_tuple_ids_ct(size_t& xnext_field_offset);

  ///
  /// Converts the dof_tuple_ids field from external to internal format.
  ////
  void internalize_dof_tuple_ids(size_t& xnext_field_offset);

  ///
  /// Converts the lower_cover_ct field from external to internal format.
  ////
  void internalize_lower_cover_ct(size_t& xnext_field_offset);

  ///
  /// Converts the lower_cover field from external to internal format.
  ////
  void internalize_lower_cover(size_t& xnext_field_offset);

  ///
  /// Converts the upper_cover_ct field from external to internal format.
  ////
  void internalize_upper_cover_ct(size_t& xnext_field_offset);

  ///
  /// Converts the upper_cover field from external to internal format.
  ////
  void internalize_upper_cover(size_t& xnext_field_offset);

  ///
  /// Converts the subposet_ids_ct field from external to internal format.
  ////
  void internalize_subposet_ids_ct(size_t& xnext_field_offset);

  ///
  /// Converts the subposet_ids fields from external to internal format.
  ///
  void internalize_subposet_ids(size_t& xnext_field_offset);

  ///
  /// Converts the eqv_ids fields from external to internal format.
  ///
  void internalize_eqv_ids(size_t& xnext_field_offset);

  ///
  /// Initializes memebr with index xmbr_id from the internal buffer.
  ///
  void transfer_internal_buffer_to_member(const scoped_index& xmbr_id);

  ///
  /// Transfer toc to member.
  ///
  void transfer_toc_to_member(const scoped_index& xmbr_id);

  ///
  /// Transfer private data to member interval.
  ///
  void transfer_private_data_to_interval(const scoped_index& xmbr_id);

  ///
  /// Transfer dof tuple ids to member interval.
  ///
  void transfer_dof_tuple_ids_to_interval(const scoped_index& xmbr_id);

  ///
  /// Transfer dof tuple ids to member.
  ///
  void transfer_dof_tuple_ids_to_member(const scoped_index& xmbr_id);

  ///
  /// Creates a new dof tuple of type specified by xtype_id
  ///
  const scoped_index& new_row_dof_tuple(pod_index_type xext_dof_tuple_pod);

  ///
  /// Transfer lower_cover to member.
  ///
  void transfer_lower_cover_to_member(const scoped_index& xmbr_id);

  ///
  /// Transfer upper_cover to member.
  ///
  void transfer_upper_cover_to_member(const scoped_index& xmbr_id);

  ///
  /// Creates a new member with index xmbr_id.
  ///
  void new_member(pod_index_type xmbr_id);

  ///
  /// Transfer subposets ids to member.
  ///
  void transfer_subposet_ids_to_member(const scoped_index& xmbr_id);

  ///
  /// Transfer equivalent ids to member.
  ///
  void transfer_eqv_ids_to_member(const scoped_index& xmbr_id);

  ///
  /// Transfer names to member.
  ///
  void transfer_names_to_member(const scoped_index& xmbr_id);

  // ===========================================================
  // VARIABLE_LENGTH_RECORD FACET
  // ===========================================================

  ///
  /// Pointer to record item beginning at offset xoffset
  ///
  inline pod_index_type* int_buf()
  {
    return reinterpret_cast<pod_index_type*>(buf());
  };

  // ===========================================================
  // RECORD FACET
  // ===========================================================

  // ===========================================================
  // ANY FACET
  // ===========================================================

public:

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual member_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

};
 
} // namespace sheaf

#endif // ifndef MEMBER_RECORD_H






