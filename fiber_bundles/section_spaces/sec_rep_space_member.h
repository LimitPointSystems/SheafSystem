
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

/// @file
/// Interface for class sec_rep_space_member.

#ifndef SEC_REP_SPACE_MEMBER_H
#define SEC_REP_SPACE_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_MEMBER_H
#include "poset_member.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif
 
#ifndef SECTION_DOF_MAP_H
#include "section_dof_map.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#include "section_space_schema_member.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

namespace sheaf
{
class scattered_insertion_index_space_handle;
class index_space_handle;
class index_space_iterator;
class poset_dof_map;
}

namespace fiber_bundle
{

using namespace sheaf;
class sec_rep_space;
class binary_section_space_schema_member;
class binary_section_space_schema_poset;

///
/// A member of a sec_rep_space; a section.
///
class SHEAF_DLL_SPEC sec_rep_space_member : public poset_member
{
  // ===========================================================
  /// @name SEC_REP_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

  // Typedefs:

  ///
  /// The schema type.
  ///
  typedef binary_section_space_schema_member schema_type;

  ///
  /// The host type of the schema.
  ///
  typedef binary_section_space_schema_poset schema_host_type;

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// The standard name for the section_space_schema_poset constructed
  /// for the schema member with name xschema_member_name.
  //// @hack the "fiber space hack". Currently each section_space_schema_member
  //// used to create a section space must have its own schema poset because the
  //// schema poset owns the fiber space. See additional comments in
  //// section_space_schema_poset.
  ////
  static std::string standard_schema_poset_name(const std::string& xschema_member_name);

  ///
  /// The standard name for the fiber space constructed for the schema member
  /// with path xschema_path.
  ///
  static std::string standard_fiber_space_name(const poset_path& xschema_path);

  ///
  /// The standard name for the section space with fiber space poset name
  /// xfiber_space_name and base space poset name xbase_space_name.
  ///
  static std::string standard_section_space_name(const std::string& xfiber_space_name,
						 const std::string& xbase_space_name);

  ///
  /// Default constructor; creates an unattached handle.
  ///
  sec_rep_space_member();

  ///
  /// Copy constructor; creates new sec_rep_space_member handle
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a
  /// copy (i.e. is join equivalent to) the state of xother.
  ///
  sec_rep_space_member(const sec_rep_space_member& xother,
                       bool xnew_jem = false);

  ///
  /// Assignment operator; synonym for attach_to_state(xother).
  ///
  virtual sec_rep_space_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(xother).
  ///
  sec_rep_space_member& operator=(const sec_rep_space_member& xother);

  ///
  /// Destructor.
  ///
  ~sec_rep_space_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_rep_space_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_rep_space_member*>
        (poset_member::clone(xnew_state, xauto_access));
  }


  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new section handle attached to a new jim state
  /// ("explicit prevents interpretation as implicit conversion from
  /// sec_rep_space* to sec_rep_space_member&)
  ///
  explicit sec_rep_space_member(sec_rep_space* xhost,
                                section_dof_map* xdof_map = 0,
                                bool xauto_access = true);

  ///
  /// Creates a new section handle attached to a new jim state,
  /// a partial section defined only on version xbase_version
  /// of base space member xbase_mbr.
  ///
  sec_rep_space_member(sec_rep_space* xhost,
                       abstract_poset_member& xbase_mbr,
                       int xbase_version = CURRENT_HOST_VERSION,
                       bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jrm state which is
  /// a multi-section with a branch for each member of the base space
  /// contained in xbase_parts.
  ///
  sec_rep_space_member(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_access);

  ///
  /// creates a new jrm (join reducible member) attached to a new member state
  /// in xhost.  The jrm created is the join of the jims with the indices
  /// given in xjims_indices.
  ///
  sec_rep_space_member(sec_rep_space* xhost,
                       scoped_index* xexpansion,
                       int xexpansion_ct,
                       const tern& xnew_jem,
                       bool xauto_access);


  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new sec_rep_space_member handle attached to the member state
  /// with index xindex in xhost
  ///
  sec_rep_space_member(const sec_rep_space* xhost, pod_index_type xindex);

  ///
  /// Creates a new sec_rep_space_member handle attached to the member state
  /// with index xindex in xhost
  ///
  sec_rep_space_member(const sec_rep_space* xhost, const scoped_index& xindex);

  ///
  /// Creates a new sec_rep_space_member handle attached to the member state
  /// with name xname in xhost
  ///
  sec_rep_space_member(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new sec_rep_space_member handle attached to the member state
  /// with path xpath in the namespace xnamespace.
  ///
  sec_rep_space_member(const namespace_poset* xnamespace,
                       const poset_path& xpath,
                       bool xauto_access = true);

  ///
  /// Creates a new sec_rep_space_member handle attached to the member state
  /// with index xmember_index in the poset with index xposet_index in the
  /// namespace xnamespace
  ///
  sec_rep_space_member(const namespace_poset* xnamespace,
                       pod_index_type xposet_index,
                       pod_index_type  xmember_index);

  ///
  /// Creates a new sec_rep_space_member handle attached to the member state
  /// with index xmember_index in the poset with index xposet_index in the
  /// namespace xnamespace
  ///
  sec_rep_space_member(const namespace_poset* xnamespace,
                       const scoped_index& xposet_index,
                       const scoped_index&  xmember_index);

  ///
  /// Creates a new sec_rep_space_member handle attached to the same state as
  /// xother. ("explicit" prevents interpretation as implicit conversion from
  /// sec_rep_space_member* to sec_rep_space_member&)
  ///
  explicit sec_rep_space_member(const sec_rep_space_member* xother);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  using poset_member::new_jim_state;

  ///
  /// Creates a new jim state in host() and attaches this
  /// handle to the state. The state is a partial section defined only
  /// on version xbase_version of base space member xbase_mbr.
  ///
  void new_jim_state(abstract_poset_member& xbase_mbr,
                     int xbase_version = CURRENT_HOST_VERSION,
                     bool xauto_access = true);

  ///
  /// Creates a new jim state in host xhost and attaches this
  /// handle to the state. The state is a partial section defined only
  /// on version xbase_version of base space member xbase_mbr.
  ///
  void new_jim_state(sec_rep_space* xhost,
                     const abstract_poset_member& xbase_mbr,
                     int xbase_version = CURRENT_HOST_VERSION,
                     bool xauto_access = true);

  using poset_member::new_jrm_state;

  ///
  /// Multisection constructor; creates a new jrm state which is a
  /// multi-section with a branch for each member of the base space
  /// contained in xbase_parts and attaches this to it.
  ///
  void new_jrm_state(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_access);

protected:

private:

  //@}


  // =============================================================================
  /// @name MULTISECTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// True if this is a multisection.
  ///
  bool is_multisection(bool xauto_access) const;

  ///
  /// True if this is a multisection and it has a branch sequence id space.
  ///
  bool has_branch_id_space(bool xauto_access) const;

  ///
  /// Allocate an id space handle from the handle pool attached to the
  /// branch id space for this member.
  ///
  scattered_insertion_index_space_handle& get_branch_id_space(bool xauto_access);

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  void release_branch_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// True if the handle pool allocated xid_space.
  ///
  bool allocated_branch_handle(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates an iterator from the iterator pool attached to the
  /// branch id space for this member.
  ///
  index_space_iterator& get_branch_id_space_iterator(bool xauto_access) const;

  ///
  /// Returns the iterator xitr to the iterator pool.
  ///
  void release_branch_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

  ///
  /// True if the id space iterator xitr was allocated by the iterator pool.
  ///
  bool allocated_branch_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

  using poset_member::schema;

  ///
  /// The restricted schema for this (mutable version).
  ///
  virtual section_space_schema_member& schema();

  ///
  /// The restricted schema for this (const version).
  ///
  virtual const section_space_schema_member& schema() const;

  ///
  /// The schema for this, auto-accessible (mutable version).
  ///
  section_space_schema_member& schema(bool xauto_access);

  ///
  /// The schema for this, auto-accessible (const version).
  ///
  const section_space_schema_member& schema(bool xauto_access) const;

  ///
  /// The unrestricted schema for this poset membe (mutable version).
  ///
  virtual section_space_schema_member& unrestricted_schema();
  
  ///
  /// The unrestricted schema for this poset member (const version).
  ///
  virtual const section_space_schema_member& unrestricted_schema() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name RESTRICTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The restricted base of this section space member (mutable version)
  ///
  abstract_poset_member& base();

  ///
  /// The restricted base of this section space member (const version)
  ///
  const abstract_poset_member& base() const;

  ///
  /// True if this has the same base as xother.
  ///
  bool same_base(const sec_rep_space_member* xother) const;


  /// @hack virtual so it can be overridden in sec_ed_invertible
  /// as workaround for bug in schema().db(). Remove when bug fixed.

  ///
  /// The dimension of the restricted base.
  ///
  virtual int db() const;

  ///
  /// True if this has the same rep and same base as xother.
  //// @hack this definition used for backwards compatibility
  //// with previous implementation.
  //// @todo distinguish betwee rep desc equality and rep equality.
  ////
  bool same_rep(const sec_rep_space_member* xother) const;

  ///
  /// The number of members of the discretization subposet
  /// contained in the down set  of the restricted base.
  ///
  int discretization_ct() const;

  ///
  /// The number of members of the discretization subposet
  /// contained in the down set  of the restricted base
  //  (version with access control).
  ///
  int discretization_ct(bool xaxto_access) const;

  ///
  /// The number of members of the evaluation subposet
  /// contained in the down set of the restricted base.
  ///
  int evaluation_ct() const;

  ///
  /// The schema of the restricted fiber of this section space member (mutable version)
  ///
  schema_poset_member& fiber_schema();

  ///
  /// The schema of the restricted fiber of this section space member (const version)
  ///
  const schema_poset_member& fiber_schema() const;

  ///
  /// The unrestricted fiber of host() (mutable version).
  ///
  poset& fiber();

  ///
  /// The unrestricted fiber of host() (const version).
  ///
  const poset& fiber() const;

  ///
  /// The dimension of the restricted fiber.
  ///
  int df() const;

  using poset_member::restrict_to;

  ///
  /// Restricts this section to base with index xbase_id and
  /// fiber schema with index xfiber_schema_id
  ///
  virtual void restrict_to(pod_index_type xbase_id, pod_index_type xfiber_schema_id);

  ///
  /// Restricts this section to base with index xbase_id and
  /// fiber schema with index xfiber_schema_id
  ///
  void restrict_to(const scoped_index& xbase_id, const scoped_index& xfiber_schema_id);

  ///
  /// Restricts this section to base xbase and fiber schema xfiber_schema
  ///
  virtual void restrict_to(const abstract_poset_member* xbase, const abstract_poset_member* xfiber_schema);

  ///
  /// True if base() is not the same as host()->base();
  ///
  bool base_is_restricted() const;

  ///
  /// True if fiber_schema() is not the same as host()->fiber_schema().
  ///
  bool fiber_schema_is_restricted() const;

  ///
  /// The base space version this section is defined on.
  ///
  int version() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name NEW DOF ACCESS FACET
  // ===========================================================
  //@{

public:

  using poset_member::get_dof;

  ///
  /// Copies the dof referred to by xdisc_id, xfiber_dof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       void* xdof, 
		       size_type xdof_size) const;
 
  ///
  /// Copies the dof referred to by xdisc_id, xfiber_dof_id into xdof.
  ///
  void get_dof(const scoped_index& xdisc_id, 
	       const scoped_index& xfiber_dof_id, 
	       void* xdof, 
	       size_type xdof_size,
	       bool xauto_access) const;

  using poset_member::put_dof;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       const void* xdof, 
		       size_type xdof_size);

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  void put_dof(const scoped_index& xdisc_id, 
	       const scoped_index& xfiber_dof_id, 
	       const void* xdof, 
	       size_type xdof_size,
	       bool xauto_access);
 
  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  void get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const;

  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  void get_fiber(const scoped_index& xdisc_id, void* xfiber, size_type xfiber_size, bool xauto_access) const;

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void put_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size, bool xauto_access);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber; 
  /// reallocates dof map memory if necessary.
  ///
  void force_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber;
  /// reallocates dof map memory if necessary.
  ///
  void force_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size, bool xauto_access);
 
  ///
  /// Sets xcomponent to the component referred to by fiber id xfiber_dof_id.
  ///
  void get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const;

  ///
  /// Sets xcomponent to the component referred to by fiber id xfiber_dof_id.
  ///
  void get_component(const scoped_index& xfiber_dof_id, 
		     void* xcomponent, 
		     size_type xcomponent_size, 
		     bool xauto_access) const;
 
  ///
  /// Sets the xcomponent referred to by fiber id xfiber_dof_id to xcomponent.
  ///
  void put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size);

  ///
  /// Sets the component referred to by fiber id xfiber_dof_id to xcomponent.
  ///
  void put_component(const scoped_index& xfiber_dof_id, 
		     const void* xcomponent, 
		     size_type xcomponent_size,
		     bool xauto_access);

protected:

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Get the size in bytes of the restricted dof tuple for this member
  ///
  size_t dof_tuple_size();

  ///
  /// Get the size in bytes of the restricted fiber for this member
  ///
  size_t fiber_size();

  ///
  /// The map from client_ids to dof values for this poset member (mutable version)
  ///
  virtual section_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from client_ids to dof values for this poset member (const version)
  ///
  virtual const section_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// dof map required by this handle.
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HOST POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The section representation space this is a member of
  ///
  sec_rep_space* host() const;

  ///
  /// True if other conforms to host.
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual sec_rep_space_member* clone() const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}
};

} // namespace fiber_bundle

#endif // ifndef SEC_REP_SPACE_MEMBER_H
