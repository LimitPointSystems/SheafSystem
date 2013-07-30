

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

/// @file
/// Interface for class abstract_poset_member.

#ifndef ABSTRACT_POSET_MEMBER_H
#define ABSTRACT_POSET_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_COMPONENT_H
#include "poset_component.h"
#endif

#ifndef PRIMITIVE_VALUE_H
#include "primitive_value.h"
#endif
 
#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif


namespace sheaf
{

template <typename T> class block;
class subposet;
class tern;
class storage_agent;
class poset_dof_map;
class poset_member_iterator;
class poset_path;
class schema_poset_member;

// ============================================================================
// CLASS ABSTRACT_POSET_MEMBER_TABLE_DOFS_TYPE
// ============================================================================
  
///
/// Table dofs type for class abstract_poset_member.
///
class SHEAF_DLL_SPEC abstract_poset_member_table_dofs_type
{
  // ===========================================================
  /// @name ABSTRACT_POSET_MEMBER_TABLE_DOFS_TYPE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the dofs.
  ///
  typedef unsigned char dof_type;

  ///
  /// The type of the table dofs (type of this).
  ///
  typedef abstract_poset_member_table_dofs_type table_dofs_type;

  ///
  /// Xi-th byte (mutable version).
  ///
  dof_type& operator[] (size_type xi);

  ///
  /// Xi-th byte (const version).
  ///
  const dof_type& operator[] (size_type xi) const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  table_dofs_type* clone() const;

protected:

private:

  //@}
};


// ============================================================================
// CLASS ABSTRACT_POSET_MEMBER_ROW_DOFS_TYPE
// ============================================================================
  
///
/// Row dofs type for class abstract_poset_member.
///
class SHEAF_DLL_SPEC abstract_poset_member_row_dofs_type
{
  // ===========================================================
  /// @name ABSTRACT_POSET_MEMBER_ROW_DOFS_TYPE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the dofs.
  ///
  typedef unsigned char dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef abstract_poset_member_row_dofs_type row_dofs_type;

  ///
  /// Xi-th byte (mutable version).
  ///
  dof_type& operator[] (size_type xi);

  ///
  /// Xi-th byte (const version).
  ///
  const dof_type& operator[] (size_type xi) const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  row_dofs_type* clone() const;

protected:

private:

  //@}
};


// ============================================================================
// CLASS ABSTRACT_POSET_MEMBER
// ============================================================================
  
///
/// A client handle for a member of a poset.
/// A abstract_poset_member is a handle for a specific poset member state
/// within the poset_state of a specific poset object. The poset member state
/// is identified by a unique poset member index within a host poset object.
/// The abstract_poset_member can be created either attached to a specific
/// poset member state, or it can be created unattached. In the latter case it
/// is treated as if attached to a unique "void" poset member state. When a
/// abstract_poset_member object is deleted, the poset member state it is
/// attached to, if any, is also deleted. If the client wishes to delete the
/// abstract_poset_member object, but leave the poset member state in the
/// poset_state for later use, the abstract_poset_member object must be
/// detached before it is deleted.
///
class SHEAF_DLL_SPEC abstract_poset_member : public poset_component
{

  friend class cover_set_iterator;
  friend class filtered_iterator;
  friend class poset_dft;
  friend class poset_joiner;
  friend class poset_orderer;
  friend class poset_state_handle;
  friend class postorder_iterator;
  friend class subposet_joiner;
  friend class storage_agent;
  // friend ostream & operator << (ostream &os, abstract_poset_member& p);

  // ===========================================================
  /// @name ABSTRACT_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the table dofs.
  ///
  typedef abstract_poset_member_table_dofs_type table_dofs_type;

  ///
  /// The type of the row dofs.
  ///
  typedef abstract_poset_member_row_dofs_type row_dofs_type;

  ///
  /// Assignment operator; attaches this to the same state as xother.
  ///
  virtual abstract_poset_member& operator=(const abstract_poset_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~abstract_poset_member();

  ///
  /// Virtual constructor; makes a new handle of the same type as this, attached to
  /// a new state (xnew_state true) or attached to the same state
  /// as this (xnew_state false).
  ///
  abstract_poset_member* clone(bool xnew_state, bool xauto_access = true) const;

  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. If xdof_map == 0 a new dof map is created. If xdof_map != 0
  /// and xcopy_dof_map == false, xdof_map is used as the dof map. If
  /// xdof_map != 0 and xcopy_dof_map is true, a copy of xdof_map is used.
  ///
  virtual void new_jim_state(poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. The existing dof map with index xtuple_id is used as the dof map.
  ///
  virtual void new_jim_state(pod_index_type xtuple_id,
			     bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. The existing dof map with index xtuple_id is used as the dof map.
  ///
  void new_jim_state(const scoped_index& xtuple_id,
		     bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) state in xhost and attaches
  /// this to it.
  ///
  virtual void new_jim_state(poset_state_handle* xhost,
                             poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. The existing dof map with index xtuple_id is used as the dof map.
  ///
  virtual void new_jim_state(poset_state_handle* xhost,
			     pod_index_type xtuple_id,
			     bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. The existing dof map with index xtuple_id is used as the dof map.
  ///
  void new_jim_state(poset_state_handle* xhost,
		     const scoped_index& xtuple_id,
		     bool xauto_access = true);

  ///
  /// Creates a new jrm (join-reducible member) state in host() and attaches
  /// this to it.
  ///
  virtual void new_jrm_state(bool xauto_access = true);

  ///
  /// Creates a new jrm (join-reducible member) state in xhost and attaches
  /// this to it.
  ///
  virtual void new_jrm_state(poset_state_handle* xhost,
                             bool xauto_access = true);

  ///
  /// Computes the join of the members with the indices given in xexpansion.
  /// If the join already exists and xgreatest_jem:
  ///  is_true(), creates a new greatest jem of the existing join and attaches to it;
  ///  is_false(), creates a new least jem of the existing join and attaches to it;
  ///  is_neither(), attaches to the existing join;
  ///
  virtual void new_jrm_state(const scoped_index* xexpansion,
                             int xexpansion_ct,
                             const tern& xgreatest,
                             bool xauto_access = true);

  ///
  /// Computes the join of the members with the indices given in xexpansion.
  /// If the join already exists and xgreatest_jem:
  ///  is_true(), creates a new greatest jem of the existing join and attaches to it;
  ///  is_false(), creates a new least jem of the existing join and attaches to it;
  ///  is_neither(), attaches to the existing join;
  ///
  virtual void new_jrm_state(poset_state_handle* xhost,
                             const scoped_index* xexpansion,
                             int xexpansion_ct,
                             const tern& xgreatest,
                             bool xauto_access = true);


  ///
  /// Creates a new jrm state in host() which is the greatest jem (xgreatest true)
  /// or least jem (xgreatest false) of xother and attaches this to it.
  ///
  virtual void new_jem_state(abstract_poset_member* xother,
                             bool xgreatest,
                             bool xauto_access);

  ///
  /// Creates a new jrm state in xhost which is the greatest jem (xgreatest true)
  /// or least jem (xgreatest false) of hub id xhub_id and attaches this to it.
  ///
  virtual void new_jem_state(poset_state_handle* xhost,
			     pod_index_type xhub_id,
			     bool xgreatest,
			     bool xauto_access);

  ///
  /// Creates a new jrm state in xhost which is the greatest jem (xgreatest true)
  /// or least jem (xgreatest false) of id xid and attaches this to it.
  ///
  void new_jem_state(poset_state_handle* xhost,
		     const scoped_index& xid,
		     bool xgreatest,
		     bool xauto_access);

protected:

private:

  //@}


  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor; creates a new, unattached abstract_poset_member handle.
  ///
  abstract_poset_member();

  ///
  /// Initializes handle data members when attaching
  /// to a different member of the same host;
  /// intended to be redefined in derived classes.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Pointer to the table dofs
  ///
  char* table_dof_ptr(bool xrequire_write_access = false) const;

  ///
  /// Pointer to the row dofs
  ///
  char* row_dof_ptr(bool xrequire_write_access = false);

private:

  //@}


  // ===========================================================
  /// @name MEMBER ATTRIBUTE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this member is join irreducible in the
  /// current version of the host (xin_current_version == true) or
  /// in some version of the host (xin_current_version == false).
  ///
  virtual bool is_jim(bool xin_current_version = true) const;

  ///
  /// True if this member covers the bottom
  ///
  virtual bool is_atom() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The schema for this poset member (mutable version).
  ///
  virtual schema_poset_member& schema();

  ///
  /// The schema for this poset member (const version).
  ///
  virtual const schema_poset_member& schema() const;

  ///
  /// The schema for this poset member, auto-accessible (mutable version).
  ///
  schema_poset_member& schema(bool xauto_access);

  ///
  /// The schema for this poset member, auto-accessible (const version).
  ///
  const schema_poset_member& schema(bool xauto_access) const;

  ///
  /// The unrestricted schema for this poset member (mutable version).
  ///
  virtual schema_poset_member& unrestricted_schema();

  ///
  /// The unrestricted schema for this poset member (const version).
  ///
  virtual const schema_poset_member& unrestricted_schema() const;

  ///
  /// True if the schema of this has name xname
  ///
  bool schema_is(const string& xschema_name) const;

  ///
  /// True if xother has the same schema (column poset) as this
  ///
  bool same_schema(const abstract_poset_member* xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name RESTRICTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if handle is a restriction of the state,
  /// that is, if schema() is not the same as host()->schema().
  ///
  virtual bool is_restricted() const;

  ///
  /// True if this is the same restriction as xother,
  /// that is, if schema().is_same_state(xother.schema()).
  ///
  virtual bool is_same_restriction(const abstract_poset_member* xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of dofs in the dof tuple for jims of this poset;
  ///
  virtual int dof_ct() const = 0;

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member (mutable version)
  ///
  virtual poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member (const version)
  ///
  virtual const poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// dof map required by this handle.
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

  ///
  /// Copies the entire dof tuple between xbuf and internal storage
  ///
  void dof_tuple(const void* xbuf, size_t xbuflen) const;

  ///
  /// Copies the entire dof tuple between xbuf and internal storage
  ///
  void put_dof_tuple(const void* xbuf, size_t xbuflen);

  ///
  /// The dof tuple index of this member.
  ///
  pod_index_type dof_tuple_id(bool xauto_access) const;

  ///
  /// The dof tuple index of this member.
  ///
  void dof_tuple_id(scoped_index& result, bool xauto_access) const;

  ///
  /// Sets dof tuple index to xtuple_index
  ///
  void put_dof_tuple_id(pod_index_type xtuple_index, bool xauto_access);

  ///
  /// Sets dof tuple index to xtuple_index
  ///
  void put_dof_tuple_id(const scoped_index& xtuple_index, bool xauto_access);

  ///
  /// The table dofs for this instance (mutable version).
  ///
  void* table_dofs();

  ///
  /// The table dofs for this instance (const version).
  ///
  const void* table_dofs() const;

  ///
  /// The table dofs for this instance (mutable auto-access version).
  ///
  void* table_dofs(bool xauto_access);

  ///
  /// The table dofs for this instance (const auto-access version).
  ///
  const void* table_dofs(bool xauto_access) const;

  ///
  /// The row dofs for this instance (mutable version).
  ///
  void* row_dofs();

  ///
  /// The row dofs for this instance (const version).
  ///
  const void* row_dofs() const;

  ///
  /// The row dofs for this instance (mutable auto-access version).
  ///
  void* row_dofs(bool xauto_access);

  ///
  /// The row dofs for this instance (const auto-access version).
  ///
  const void* row_dofs(bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DOF ACCESS FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// The dof referred to by xdof_id.
  ///
  primitive_value dof(pod_index_type xdof_id) const;

  ///
  /// The dof referred to by xdof_id.
  ///
  primitive_value dof(const scoped_index& xdof_id, bool xauto_access) const;

  ///
  /// Sets the dof referred to by xdof_id to xdof.
  ///
  void put_dof(pod_index_type xdof_id, const primitive_value& xdof);

  ///
  /// Sets the dof referred to by xdof_id to xdof.
  ///
  void put_dof(const scoped_index& xdof_id, const primitive_value& xdof, bool xauto_access);

  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  void get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const;

  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  void get_dof(const scoped_index& xdof_id, void* xdof, size_type xdof_size, bool xauto_access) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  void put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size);

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  void put_dof(const scoped_index& xdof_id, const void* xdof, size_type xdof_size, bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// True if this is less than or equal to
  /// the member with index xother_index.
  ///
  bool le(pod_index_type xother_index) const;

  ///
  /// True if this is less than or equal to
  /// the member with index xother_index.
  ///
  bool le(const scoped_index& xother_index) const;

  ///
  /// True if this is less than or equal to other
  ///
  bool le(const abstract_poset_member* other) const ;

  ///
  /// True if this is less than or equivalent to
  /// the member with index xother_index.
  ///
  bool leqv(pod_index_type xother_index) const;

  ///
  /// True if this is less than or equivalent to
  /// the member with index xother_index.
  ///
  bool leqv(const scoped_index& xother_index) const;

  ///
  /// True if this is strictly less than
  /// the member with index xother_index.
  ///
  bool lt(pod_index_type xother_index) const;

  ///
  /// True if this is strictly less than
  /// the member with index xother_index.
  ///
  bool lt(const scoped_index& xother_index) const;

  ///
  /// true if this is strictly less than other
  ///
  bool lt(const abstract_poset_member* other) const;

  ///
  /// True if this is greater than or equal to
  /// the member with index xother_index.
  ///
  bool ge(pod_index_type xother_index) const;

  ///
  /// True if this is greater than or equal to
  /// the member with index xother_index.
  ///
  bool ge(const scoped_index& xother_index) const;

  ///
  /// true if this is greater than or equal to other
  ///
  bool ge(const abstract_poset_member* other) const;

  ///
  /// True if this is greater than or equivalent to
  /// the member with index xother_index.
  ///
  bool geqv(pod_index_type xother_index) const;

  ///
  /// True if this is greater than or equivalent to
  /// the member with index xother_index.
  ///
  bool geqv(const scoped_index& xother_index) const;

  ///
  /// True if this is strictly greater than
  /// the member with index xother_index.
  ///
  bool gt(pod_index_type xother_index) const;

  ///
  /// True if this is strictly greater than
  /// the member with index xother_index.
  ///
  bool gt(const scoped_index& xother_index) const;

  ///
  /// True if this is strictly greater than other.
  ///
  bool gt(const abstract_poset_member* other) const;

  ///
  /// True if xother is join equivalent to this
  ///
  bool is_jem(const abstract_poset_member* xother) const;

  ///
  /// The largest member which is join-equivalent to this
  ///
  abstract_poset_member* greatest_jem() const;

  ///
  /// The largest member which is join-equivalent to this
  ///
  void greatest_jem_pa( abstract_poset_member* result) const;

  ///
  /// The smallest member which is join-equivalent to this
  ///
  abstract_poset_member* least_jem() const;

  ///
  /// The smallest member which is join-equivalent to this
  ///
  void least_jem_pa( abstract_poset_member* result) const;

  ///
  /// Merge the join-equivalence class of xjem under
  /// the join equivalence class of this
  ///
  virtual void merge_jem(const abstract_poset_member* xjem);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER RELATION FACET
  // ===========================================================
  //@{

public: 

  ///
  /// True if this covers other.
  ///
  bool covers(const abstract_poset_member* xother) const;

  ///
  /// True if this covers the member with hub id xhub_id.
  ///
  bool covers(pod_index_type xhub_id) const;

  ///
  /// True if this covers the member with id xid.
  ///
  bool covers(const scoped_index& xid) const;

  ///
  /// Insert a link from this to lesser; make lesser <= this.
  ///
  virtual void create_cover_link(abstract_poset_member* xlesser);

  ///
  /// Delete the link from this to lesser; make lesser incomparable to this.
  ///
  virtual void delete_cover_link(abstract_poset_member* lesser);

  ///
  /// Allocates a handle for the lower (xlower true) or upper (xlower false) 
  /// cover id space of this member from the pool of id spaces.
  ///
  index_space_handle& get_cover_id_space(bool xlower) const;

  ///
  /// Returns xcover_id_space to the pool of id spaces.
  ///
  void release_cover_id_space(index_space_handle& xcover_id_space) const;

  ///
  /// Allocates an iterator for the lower (xlower true) or upper (xlower false) 
  /// cover id space of this member from the pool of id space iterators.
  ///
  index_space_iterator& get_cover_id_space_iterator(bool xlower) const;

  ///
  /// Returns xcover_itr to the pool of id spaces.
  ///
  void release_cover_id_space_iterator(index_space_iterator& xcover_itr) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false) 
  /// cover id space of this is the domain of iterator xitr.
  ///
  bool cover_contains_iterator(bool xlower, const index_space_iterator& xitr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover this is empty.
  ///
  bool cover_is_empty(bool xlower) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover set of this  contains exactly one member.
  ///
  bool cover_is_singleton(bool xlower) const;

  ///
  /// The number of members in the lower cover (xlower true)
  /// or upper cover (xlower false) of this.
  ///
  virtual size_type cover_ct(bool lower) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of this contains xother_mbr_index
  ///
  bool cover_contains_member(bool xlower, pod_index_type xother_mbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of this contains xother_mbr_index
  ///
  bool cover_contains_member(bool xlower, const scoped_index& xother_mbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover of this contains the same members as the
  /// lower or upper cover, respectively, of the member
  /// with index xother_mbr_index.
  ///
  bool cover_is_equal(bool xlower, pod_index_type xother_mbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover of this contains the same members as the
  /// lower or upper cover, respectively, of the member
  /// with index xother_mbr_index.
  ///
  bool cover_is_equal(bool xlower, const scoped_index& xother_mbr_index) const;

  ///
  /// The first member of the lower (xlower true) or
  /// upper (xlower false) cover of this.
  ///
  pod_index_type first_cover_member(bool xlower) const;

  ///
  /// The first member of the lower (xlower true) or
  /// upper (xlower false) cover of this.
  ///
  void first_cover_member(bool xlower, scoped_index& result) const;

  ///
  /// Inserts xother_mbr_index in the lower (xlower true) or
  /// upper (xlower false) cover set of this.
  ///
  void insert_cover_member(pod_index_type xother_mbr_index, bool xlower);

  ///
  /// Inserts xother_mbr_index in the lower (xlower true) or
  /// upper (xlower false) cover set of this.
  ///
  void insert_cover_member(const scoped_index& xother_mbr_index, bool xlower);

  ///
  /// Removes xother_mbr_index from the lower (xlower true) or
  /// upper (xlower false) cover set of this.
  ///
  void remove_cover_member(pod_index_type xother_mbr_index, bool xlower);

  ///
  /// Removes xother_mbr_index from the lower (xlower true) or
  /// upper (xlower false) cover set of this.
  /// If xitr is at the end, forces xitr.is_done().  Otherwise,
  /// increments xitr to the next position.
  ///
  void remove_cover_member(const scoped_index& xother_mbr_index, bool xlower);

  ///
  /// Removes the current item of xitr from the lower (xlower true) or
  /// upper (xlower false) cover set of this.
  ///
  void remove_cover_member(index_space_iterator& xitr, bool xlower);

  ///
  /// Clears the lower (xlower true) or upper (xlower false)
  /// cover set of this.
  ///
  void clear_cover(bool xlower);

  ///
  /// Copies the lower (xlower true) or upper (xlower false) cover
  /// of this to the member with index xother_mbr_index.
  ///
  void copy_cover(bool xlower, pod_index_type xother_mbr_index);

  ///
  /// Copies the lower (xlower true) or upper (xlower false) cover
  /// of this to the member with index xother_mbr_index.
  ///
  void copy_cover(bool xlower, const scoped_index& xother_mbr_index);

protected:

private:

  //@}


  // ===========================================================
  /// @name DOWN SET FACET
  // ===========================================================
  //@{

public: 

  ///
  /// The number of members in the down set of this member.
  ///
  int down_ct() const;

  ///
  /// The number of members in the down set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  virtual int down_ct(pod_index_type xfilter_index) const;

  ///
  /// The number of members in the down set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  int down_ct(const scoped_index& xfilter_index) const;

  ///
  /// The down set of this, auto-allocated version.
  ///
  virtual subposet* down() const;

  ///
  /// The down set of this, pre-allocated version.
  ///
  virtual void down_pa(subposet* result) const;

  ///
  /// Delete the strict down set of this, except for the external boundary.
  /// If xdelete_exterior, delete the external boundary as well.
  ///
  void delete_down(bool xdelete_exterior = false,
                   bool xenter_jim_edit_mode = true);

  ///
  /// The number of members in the up set of this member.
  ///
  int up_ct() const;

  ///
  /// The number of members in the up set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  virtual int up_ct(pod_index_type xfilter_index) const;

  ///
  /// The number of members in the up set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  int up_ct(const scoped_index& xfilter_index) const;

  ///
  /// The up set of this member, auto- and pre-allocated versions
  ///
  virtual subposet* up() const;

  ///
  /// The up set of this member, auto- and pre-allocated versions
  ///
  virtual void up_pa(subposet* result) const;

  ///
  /// The number of members in the set of jims contained in the down set of
  /// this member.
  ///
  virtual int jim_ct() const;

  ///
  /// The set of jims contained in the down set of this member, auto-allocated
  ///
  virtual subposet* jims();

  ///
  /// The set of jims contained in the down set of this member, pre-allocated
  ///
  virtual void jims_pa(subposet* result);

  ///
  /// The number of maximal members in the set of jims contained in the down
  /// set of this member.
  ///
  virtual int maximal_jim_ct() const;

  ///
  /// The maximal members of the set of jims contained in this member,
  /// auto-allocated
  ///
  virtual subposet* maximal_jims();

  ///
  /// The maximal members of the set of jims contained in this member,
  /// pre-allocated
  ///
  virtual void maximal_jims_pa(subposet* result) const;

  ///
  /// The number of members in the set of atoms
  /// contained in the down set of this member.
  ///
  virtual int atom_ct() const;

  ///
  /// The set of atomss contained in the down set of this member, auto-allocated
  ///
  virtual subposet* atoms() const;

  ///
  /// The set of atomss contained in the down set of this member, pre-allocated
  ///
  virtual void atoms_pa(subposet* result) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public: 

  ///
  /// poset join of this with other, auto-allocated <br>
  /// the poset join is the least upper bound in the poset
  ///
  abstract_poset_member* p_join(abstract_poset_member* other) const;

  ///
  /// poset join of this with other, pre-allocated <br>
  /// the poset join is the least upper bound in the poset
  ///
  virtual void p_join_pa(abstract_poset_member* other, abstract_poset_member* result) const;

  ///
  /// poset join of this with other, self-allocated <br>
  /// the poset join is the least upper bound in the poset
  ///
  void p_join_sa(abstract_poset_member* other);

  ///
  /// poset meet of this with other, auto-allocated <br>
  /// the poset meet is the greatest lower bound in the poset
  ///
  abstract_poset_member* p_meet(abstract_poset_member* other);

  ///
  /// poset meet of this with other, pre-allocated <br>
  /// the poset meet is the greatest lower bound in the poset
  ///
  virtual void p_meet_pa(abstract_poset_member* other, abstract_poset_member* result);

  ///
  /// poset meet of this with other, self-allocated <br>
  /// the poset meet is the greatest lower bound in the poset
  ///
  void p_meet_sa(abstract_poset_member* other);

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public: 

  ///
  /// lattice join of this with other, auto-allocated <br>
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  abstract_poset_member* l_join(abstract_poset_member* other, bool xnew_jem = true);

  ///
  /// lattice join of this with other, pre-allocated <br>
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  void l_join_pa(abstract_poset_member* other, abstract_poset_member* result, bool xnew_jem = true);

  ///
  /// lattice join of this with other, self-allocated <br>
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  void l_join_sa(abstract_poset_member* other, bool xnew_jem = true);

  ///
  /// lattice meet of this with other, auto-allocated <br>
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  abstract_poset_member* l_meet(abstract_poset_member* other, bool xnew_jem = true);

  ///
  /// lattice meet of this with other, pre-allocated <br>
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  void l_meet_pa(abstract_poset_member* other, abstract_poset_member* result, bool xnew_jem = true);

  ///
  /// lattice meet of this with other, self-allocated <br>
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  void l_meet_sa(abstract_poset_member* other, bool xnew_jem = true);

  ///
  /// lattice pseudo-complement of this, auto-allocated <br>
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  abstract_poset_member* l_not(bool xnew_jem = true) const;
  

  ///
  /// lattice pseudo-complement of this, pre-allocated <br>
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  void l_not_pa(abstract_poset_member* result, bool xnew_jem = true) const;

  ///
  /// lattice pseudo-complement of this, self-allocated <br>
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  void l_not_sa(bool xnew_jem = true) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name COMPONENT INDEX FACET
  // ===========================================================
  //@{

public:

  /// @hack swig doesn't like using poset_component::is_valid_index

  ///
  /// True if there exists a component of the same type as this
  /// with hub id xhub_id in version xversion of xhost.
  ///
  virtual bool is_valid_index(const poset_state_handle* xhost,
                              pod_index_type xhub_id,
                              int xversion = CURRENT_HOST_VERSION) const;

  ///
  /// True if there exists a component of the same type as this
  /// with id xid in version xversion of xhost.
  ///
  bool is_valid_index(const poset_state_handle* xhost,
		      const scoped_index& xid,
		      int xversion = CURRENT_HOST_VERSION) const;

  ///
  /// The id space family for this member.
  ///
  const index_space_family& id_spaces() const;

  /// @issue Do these functions need to virtual?

  ///
  /// The hub id space; const version.
  ///
  virtual const hub_index_space_handle& hub_id_space() const;

  ///
  /// A id in the hub id space for components of this type;
  /// intended for copying to initialize ids to the hub id space.
  ///
  virtual const scoped_index& hub_id() const;

  ///
  /// An id in the member hub id space with pod xid.
  ///
  virtual scoped_index hub_id(pod_index_type xid) const;

  ///
  /// Gets the index of the component in xhost with name xname.
  ///
  virtual pod_index_type get_index_from_name(const poset_state_handle* xhost,
					     const string& xname) const;

  ///
  /// Gets the index of the component in xhost with name xname.
  ///
  virtual void get_index_from_name(const poset_state_handle* xhost,
				   const string& xname,
				   scoped_index& result) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name COMPONENT NAME FACET
  // ===========================================================
  //@{

public:

  /// @hack swig doesn't like using poset_component::name

  //   using poset_component::name;

  ///
  /// A name for this.
  ///
  string name() const
  {
    return poset_component::name();
  };

  ///
  /// A name for this.
  ///
  virtual string name(bool xauto_access) const;

  ///
  /// All the names for this.
  ///
  virtual void all_names(block<string>& xresult, bool xauto_access = false) const;

  ///
  /// The number of names for this.
  ///
  virtual size_type name_ct(bool xauto_access) const;

  ///
  /// True if xname is a name for this.
  ///
  virtual bool has_name(const string& xname, bool xauto_access = false) const;

  ///
  /// Make xname a name for this; if xunique, make xname the only name.
  ///
  virtual void put_name(const string& xname, bool xunique, bool xauto_access);

  ///
  /// Delete all names for this.
  ///
  virtual void delete_name(const string& xname, bool xauto_access = false);

  ///
  /// Delete all the names for this.
  ///
  virtual void delete_all_names(bool xauto_access = false);

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  using poset_component::attach_to_state;

  ///
  /// Attach to the state specified by path xpath in the namespace xns.
  ///
  void attach_to_state(const namespace_poset* xns,
                       const poset_path& xpath,
                       bool xauto_access = true);

  ///
  /// Attach to the state with name xmember_index in the
  /// poset with name xposet_index in the namespace xnamespace
  ///
  void attach_to_state(const namespace_poset* xnamespace,
                       pod_index_type xposet_index,
                       pod_index_type xmember_index,
                       bool xauto_access = true);

  ///
  /// Attach to the state with name xmember_index in the
  /// poset with name xposet_index in the namespace xnamespace
  ///
  void attach_to_state(const namespace_poset* xnamespace,
                       const scoped_index& xposet_index,
                       const scoped_index& xmember_index,
                       bool xauto_access = true);

  ///
  /// Detachs this from its state and then deletes the state
  ///
  virtual void delete_state(bool xauto_access = false);

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor; makes a new unattached handle of the same type as this.
  ///
  virtual abstract_poset_member* clone() const = 0;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DEBUGGING FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual stream insertion.
  ///
  virtual void to_stream(ostream& xos = cout) const;

protected:

private:

  //@}
};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

///
/// The table dofs pod type for x0 (mutable version).
///
template <typename T>
typename T::table_dofs_type& table_dofs(T& x0);

///
/// The table dofs pod type for x0 (const version).
///
template <typename T>
const typename T::table_dofs_type& table_dofs(const T& x0);

///
/// The table dofs pod type for x0 (mutable auto-access version).
///
template <typename T>
typename T::table_dofs_type& table_dofs(T& x0, bool xauto_access);

///
/// The table dofs pod type for x0 (const auto-access version).
///
template <typename T>
const typename T::table_dofs_type& table_dofs(const T& x0, bool xauto_access);

///
/// The row dofs pod type for x0 (mutable version).
///
template <typename T>
typename T::row_dofs_type& row_dofs(T& x0);

///
/// The row dofs pod type for x0 (const version).
///
template <typename T>
const typename T::row_dofs_type& row_dofs(const T& x0);

///
/// The row dofs pod type for x0 (mutable auto-access version).
///
template <typename T>
typename T::row_dofs_type& row_dofs(T& x0, bool xauto_access);

///
/// The row dofs pod type for x0 (const auto-access version).
///
template <typename T>
const typename T::row_dofs_type& row_dofs(const T& x0, bool xauto_access);
  
///
/// Insert abstract_poset_member& p into ostream& os.
///
SHEAF_DLL_SPEC 
ostream& operator << (ostream &os, const abstract_poset_member& p);

SHEAF_DLL_SPEC 
ostream& operator << (ostream &os, const abstract_poset_member* p); 

} // namespace sheaf

#endif // ABSTRACT_POSET_MEMBER_H
