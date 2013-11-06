
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
/// Interface for class subposet.

#ifndef SUBPOSET_H
#define SUBPOSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
#endif

#ifndef POSET_COMPONENT_H
#include "poset_component.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef SUBPOSET_STATE_H
#include "subposet_state.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace sheaf
{

template <typename T> class block;
template <typename T> class depth_first_itr;
class abstract_poset_member;
class depth_first_iterator;
class dof_descriptor_array;
class index_iterator;
class poset;
class poset_member;
class poset_member_iterator;
class primitives_poset_schema;
class section_space_schema_subposet;
class storage_agent;
class subposet_member_iterator;
  
///
/// A client handle for a subposet. <br>
///
/// A subposet is a handle for a specific subposet state within the poset_state
/// of a specific poset object. The subposet state is identified by a unique
/// subposet index within a host poset object. The subposet can be created
/// either attached to a specific subposet state, or it can be created
/// unattached. In the latter case it is treated as if attached to a unique
/// "void" subposet state. When a subposet object is deleted, the subposet
/// state it is attached to, if any, is also deleted.  If the client wishes to
/// delete the subposet object, but leave the subposet state in the poset_state
/// for later use, the subposet object must be detached before it is deleted.
///
class SHEAF_DLL_SPEC subposet : public poset_component
{

  friend class abstract_poset_member;
  friend class depth_first_iterator;
  template<typename T>
  friend class depth_first_itr; // needs members()
  friend class filtered_depth_first_iterator;
  friend class poset_state_handle;
  friend class postorder_iterator;
  friend class preorder_iterator;
  friend class primitives_poset_schema;
  friend class section_space_schema_subposet;
  friend class storage_agent;
  friend class subposet_member_iterator;
  friend SHEAF_DLL_SPEC ostream & operator << (ostream &os, const subposet& s);

  // ===========================================================
  /// @name SUBPOSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor, creates a new, unattached subposet
  ///
  subposet();

  ///
  /// Copy constructor; if xdeep_copy, creates a new state and copies
  /// the membership of xother, else creates a new handle attached to
  /// the same state as xother.
  ///
  subposet(const subposet& xother, bool xdeep_copy = false);

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Create a new handle attached to a new subposet state in xhost
  /// If xmembers != 0, initialize the membership to xmembers,
  /// ("explicit"  prevents interpretation as implicit conversion from
  /// poset_state_handle* to subposet&)
  ///
  explicit subposet(poset_state_handle* xhost,
		    const block<pod_index_type>* xmembers = 0,
		    bool xauto_access = true);

  ///
  /// Create a new handle attached to a new subposet state in xhost
  /// If xmembers != 0, initialize the membership to xmembers,
  /// ("explicit"  prevents interpretation as implicit conversion from
  /// poset_state_handle* to subposet&)
  ///
  subposet(poset_state_handle* xhost,
	   const block<scoped_index>& xmembers,
	   bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new subposet and attaches it to the state with hub id xhub_id in
  /// poset xhost.
  ///
  subposet(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new subposet and attaches it to the state with id xid in
  /// poset xhost.
  ///
  subposet(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new subposet handle attached to the subposet state
  /// with name xname in xhost
  ///
  subposet(const poset_state_handle* xhost, const string& xname);

  ///
  /// Deletes this subposet and the state it is attached to, if any
  ///
  ~subposet();

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual subposet& operator=(const subposet& xother);

  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  ///
  /// Creates a new subposet state in host() and attaches this object to it.
  /// If xinitialize, initialize the membership to xmembers,
  /// If !xinitialize, leave the membership uninitialized.
  ///
  virtual void new_state(bool xinitialize = true, bool xauto_access = true);

  ///
  /// Creates a new subposet state in host() and attaches this object to it.
  /// Initialize the members to xmembers.
  ///
  virtual void new_state(const block<pod_index_type>& xmembers, bool xauto_access = true);

  ///
  /// Creates a new subposet state in host() and attaches this object to it.
  /// Initialize the members to xmembers.
  ///
  virtual void new_state(const block<scoped_index>& xmembers, bool xauto_access = true);

  ///
  /// Creates a new subposet state in host xhost and attaches this object to it.
  /// If xinitialize, initialize the membership to xmembers,
  /// If !xinitialize, leave the membership uninitialized.
  ///
  virtual void new_state(poset_state_handle* xhost,
                         bool xinitialize = true,
                         bool xauto_access = true);

  ///
  /// Creates a new subposet state in host xhost and attaches this object to it.
  /// Initialize the members to xmembers.
  ///
  virtual void new_state(poset_state_handle* xhost,
                         const block<pod_index_type>& xmembers,
                         bool xauto_access = true);

  ///
  /// Creates a new subposet state in host xhost and attaches this object to it.
  /// Initialize the members to xmembers.
  ///
  virtual void new_state(poset_state_handle* xhost,
                         const block<scoped_index>& xmembers,
                         bool xauto_access = true);

protected:

private:

  //@}


  // ===========================================================
  /// @name ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id space for the members of with this (const version).
  ///
  const mutable_index_space_handle& id_space() const;

  ///
  /// The id space for the members of with this (mutable version).
  ///
  mutable_index_space_handle& id_space();

  ///
  /// Creates an id space for the members of this.
  ///
  virtual mutable_index_space_handle& new_id_space(const string& xstate_class_name);

  ///
  /// True if this already has an id space.
  ///
  virtual bool has_id_space() const;

  ///
  /// True if this id space should be written to disk.
  ///
  bool is_persistent() const;

  ///
  /// Sets is_persistent() to xvalue.
  ///
  void put_is_persistent(bool xvalue);

protected:

  ///
  /// The name of the id space associated with this.
  ///
  virtual string id_space_name() const;

  ///
  /// Attach the id space to the id_space_name().
  ///
  void attach_id_space();

private:

  //@}


  // ===========================================================
  /// @name DOF SUBPOSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is a dofs subposet
  ///
  virtual bool is_dof_subposet() const;

  ///
  /// True if this is a dofs subposet
  ///
  virtual void put_is_dof_subposet(bool xis_dof_subposet);

  ///
  /// Get the number of dofs defined this, considered as a dof_subposet;
  /// <b>Note:</b> dof_ct() == member_ct(), but is more efficient to evaluate.
  ///
  virtual int dof_ct() const;

  ///
  /// Set the number of dofs defined this, considered as a dof_subposet, to xct;
  /// <b>Note:</b> dof_ct() == member_ct(), but is more efficient to evaluate.
  ///
  virtual void put_dof_ct(int xct);

  ///
  /// The offset from beginning of the dof tuple of each dof.
  ///
  virtual dof_descriptor_array* dof_descriptors() const;

  ///
  /// Set the offset from beginning of the dof tuple of each dof to xoffsets.
  ///
  virtual void put_dof_descriptors(const dof_descriptor_array* xoffsets);

protected:

private:

  //@}


  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of members of this subposet.
  ///
  int member_ct() const;

  ///
  /// An iterator for members of this poset; handle version.
  ///
  subposet_member_iterator* member_iterator() const;

  ///
  /// An iterator for members of this poset; index version.
  ///
  virtual index_iterator indexed_member_iterator() const;

  ///
  /// True if this poset contains poset member with hub id xmbr_hub_id.
  ///
  virtual bool contains_member(pod_index_type xmbr_hub_id) const;

  ///
  /// True if this poset contains poset member with id xmbr_id.
  ///
  bool contains_member(const scoped_index& xmbr_id) const;

  ///
  /// True if this poset contains poset member with name xname.
  ///
  bool contains_member(const string& xname) const;

  ///
  /// True if this poset contains poset members with hub ids in xmbr_hub_ids.
  ///
  bool contains_members(const block<pod_index_type>& xmbr_hub_ids) const;

  ///
  /// True if this poset contains poset members with ids in xmbr_ids.
  ///
  bool contains_members(const block<scoped_index>& xmbr_ids) const;

  ///
  /// True if this poset contains xmbr
  ///
  bool contains_member(const abstract_poset_member* xmbr) const;

  ///
  /// Inserts the member of host() with hub id xmbr_hub_id.
  ///
  virtual void insert_member(pod_index_type xmbr_hub_id);

  ///
  /// Inserts the member of host() with id xmbr_id.
  ///
  void insert_member(const scoped_index& xmbr_id);

  ///
  /// Inserts the members of host() with hub ids in xmbr_hub_ids.
  ///
  virtual void insert_members(const block<pod_index_type>& xmbr_hub_ids);

  ///
  /// Inserts the members of host() with ids in xmbr_ids.
  ///
  virtual void insert_members(const block<scoped_index>& xmbr_ids);

  ///
  /// Inserts member xmbr of host() into this subposet.
  ///
  virtual void insert_member(const abstract_poset_member* xmbr);

  ///
  /// Removes the member of host() with hub id xmbr_hub_id.
  ///
  virtual void remove_member(pod_index_type xmbr_hub_id);

  ///
  /// Removes the member of host() with id xmbr_id.
  ///
  void remove_member(const scoped_index& xmbr_id);

  ///
  /// Removes member xmbr of host() from this subposet.
  ///
  virtual void remove_member(const abstract_poset_member* xmbr);

protected:

  ///
  /// The characteristic function for the members of this.
  ///
  zn_to_bool* members() const;

  ///
  /// The membership bit vector
  ///
  zn_to_bool::word_t* membership() const;

//   ///
//   /// True if all the members of other are also members of this.
//   ///
//   bool includes(const list_cover_set* other) const;

private:

  //@}


  // ===========================================================
  /// @name SET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this poset is empty.
  ///
  bool is_empty() const;

  ///
  /// Make this subposet the empty subposet.
  ///
  void make_empty();

  ///
  /// True if this subposet has the same members as other.
  ///
  bool is_equal_to(const subposet* other) const;

  ///
  /// Make this subposet have the same members as other.
  ///
  void make_equal_to(const subposet* other);

  ///
  /// True if all the members of other are also members of this.
  ///
  bool includes(const subposet* other) const;

  ///
  /// Union of this with other, auto-allocated.
  ///
  subposet* p_union(const subposet* other);

  ///
  /// Union of this with other, pre-allocated.
  ///
  void p_union_pa(const subposet* other, subposet* result);

  ///
  /// Union of this with other, self-allocated.
  ///
  void p_union_sa(const subposet* other);

  ///
  /// Intersection of this with other, auto-allocated.
  ///
  subposet* p_intersection(const subposet* other);

  ///
  /// Intersection of this with other, pre-allocated.
  ///
  void p_intersection_pa(const subposet* other, subposet* result);

  ///
  /// Intersection of this with other, self-allocated.
  ///
  void p_intersection_sa(const subposet* other);

  ///
  /// Difference of this and other (this minus other), auto-allocated.
  ///
  subposet* p_minus(const subposet* other);

  ///
  /// Difference of this and other (this minus other), pre-allocated.
  ///
  void p_minus_pa(const subposet* other, subposet* result);

  ///
  /// Difference of this and other (this minus other), self-allocated.
  ///
  void p_minus_sa(const subposet* other);

  ///
  /// Poset complement of this, auto-allocated.
  ///
  subposet* p_not();

  ///
  /// Poset complement of this, pre-allocated.
  ///
  void p_not_pa(subposet* result);

  ///
  /// Poset complement of this, self-allocated.
  ///
  void p_not_sa();

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The subposet containing the extremal members of this, auto-allocated
  ///
  subposet* extremals(bool xmaximals);

  ///
  /// The subposet containing the extremal members of this, pre-allocated
  ///
  void extremals_pa(bool xmaximals, subposet* result);

  ///
  /// The subposet containing the maximal members of this, auto-allocated
  ///
  subposet* maximals();

  ///
  /// The subposet containing the maximal members of this, pre-allocated
  ///
  void maximals_pa(subposet* result);

  ///
  /// The subposet containing the minimal members of this, auto-allocated
  ///
  subposet* minimals();

  ///
  /// The subposet containing the minimal members of this, pre-allocated
  ///
  void minimals_pa(subposet* result);

  ///
  /// The down set of this subposet, auto-allocated
  ///
  subposet* down() const;

  ///
  /// The down set of this subposet, pre-allocated
  ///
  void down_pa(subposet* result) const;

  // The down set of this subposet, self-allocated
  // void down_sa();

  ///
  /// The up set of this subposet, auto-allocated
  ///
  subposet* up() const;

  ///
  /// The up set of this subposet, pre-allocatd
  ///
  void up_pa(subposet* result) const;

  // The up set of this subposet, self-allocated
  // void up_sa();

  ///
  /// The set of jims contained in the down set of this subposet, auto-allocated
  ///
  subposet* jims();

  ///
  /// The set of jims contained in the down set of this subposet, pre-allocated
  ///
  void jims_pa(subposet* result);

  ///
  /// The maximal members of the set of jims contained in the down set of this
  /// subposet, auto-allocated
  ///
  subposet* maximal_jims();

  ///
  /// The maximal members of the set of jims contained in the down set of this
  /// subposet, pre-allocated
  ///
  void maximal_jims_pa(subposet* result);

  ///
  /// The minimal members of the set of jims contained in the down set of this
  /// subposet, auto-allocated
  ///
  subposet* minimal_jims();

  ///
  /// The minimal members of the set of jims contained in the down set of this
  /// subposet, pre-allocated
  ///
  void minimal_jims_pa(subposet* result);

  ///
  /// Poset join of the members of this this, auto-allocated <br>
  /// The poset join is the least upper bound in the poset.
  ///
  poset_member* p_join();

  ///
  /// Poset join of the members of this this, pre-allocated <br>
  /// The poset join is the least upper bound in the poset.
  ///
  void p_join_pa(abstract_poset_member* result);

  ///
  /// Poset meet of the members of this, auto-allocated <br>
  /// The poset meet is the greatest lower bound in the poset.
  ///
  poset_member* p_meet();

  ///
  /// Poset meet of the members of this, pre-allocated <br>
  /// The poset meet is the greatest lower bound in the poset.
  ///
  void p_meet_pa(abstract_poset_member* result);

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// Lattice join of the members of this, auto-allocated <br>
  /// The lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset.
  ///
  poset_member* l_join(bool xnew_jem = true);

  ///
  /// Lattice join of the members of this, pre-allocated <br>
  /// The lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset.
  ///
  void l_join_pa(abstract_poset_member* result, bool xnew_jem = true);

  ///
  /// Lattice join of the members of this, auto-allocated <br>
  /// Requires this is a down set of jims. (Optimized for this case.)
  ///
  poset_member* l_join_jims(bool xnew_jem = true);

  ///
  /// Lattice join of the members of this, pre-allocated <br>
  /// Requires this is a down set of jims. (Optimized for this case.)
  ///
  void l_join_jims_pa(abstract_poset_member* result, bool xnew_jem = true);

  ///
  /// Lattice meet of the members of this, auto-allocated <br>
  /// The lattice meet is the greatest lower bound in the lattice generated
  /// by the jims in the poset.
  ///
  poset_member* l_meet(bool xnew_jem = true);

  ///
  /// Lattice meet of the members of this, pre-allocated <br>
  /// The lattice meet is the greatest lower bound in the lattice generated
  /// by the jims in the poset.
  ///
  void l_meet_pa(abstract_poset_member* result, bool xnew_jem = true);

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

  ///
  /// Detach this from its state and delete the state.
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
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor;
  /// makes a new instance of the same type as this
  ///
  virtual subposet* clone() const;

  ///
  /// Class invariant
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
  /// Prints out useful information for debugging
  ///
  void to_stream(ostream& os = cout);

  ///
  /// Get useful information for debugging as a string.
  ///
  string to_string();

protected:

private:

  //@}
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert subposet& s into ostream& os
///
SHEAF_DLL_SPEC
ostream & operator << (ostream &os, const subposet& s);

///
/// The deep size of the referenced object of type subposet.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const subposet& xsp, bool xinclude_shallow = true);

 
} // namespace sheaf

#endif // ifndef SUBPOSET_H
