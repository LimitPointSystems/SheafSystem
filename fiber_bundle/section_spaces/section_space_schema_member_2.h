
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
/// Interface for class section_space_schema_member.

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#define SECTION_SPACE_SCHEMA_MEMBER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCHEMA_POSET_MEMBER_H
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#endif

namespace sheaf
{
class cover_set_iterator;
}

namespace fiber_bundle
{

using namespace sheaf;

class sec_rep_descriptor;
class section_space_schema_poset;
class section_space_schema_jims_index_space_handle;


///
/// A client handle for a poset member which has been
/// prepared for use as a schema for a section space.
///
/// @todo create immutable base class so this doesn't
/// inherit new_state methods.
///
/// @hack temporarily redefine all new state functions
/// as unimplemented to trap calls to them.
///
class SHEAF_DLL_SPEC section_space_schema_member : public schema_poset_member
{
  friend class section_space_schema_poset; // For access to get_ext_ids.

  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual section_space_schema_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  section_space_schema_member& operator=(const section_space_schema_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~section_space_schema_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline section_space_schema_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<section_space_schema_member*>(schema_poset_member::clone(xnew_state, xauto_access));
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  // None - section_space_schema_member is abstract

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  // None - section_space_schema_member is abstract

  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  // FEATURES:

  ///
  /// The representation for section spaces on this schema (mutable version).
  ///
  sec_rep_descriptor& rep();

  ///
  /// The representation for section spaces on this schema (const version).
  ///
  const sec_rep_descriptor& rep() const;

  ///
  /// True if this has the same rep as xother.
  ///
  bool same_rep(const section_space_schema_member& xother) const;

  ///
  /// The member id of the base space component of this.
  ///
  pod_index_type base_space_id() const;

  ///
  /// The member id of the base space component of this.
  ///
  void base_space_id(scoped_index& result) const;

  ///
  /// The base space component of this (mutable version).
  ///
  total_poset_member& base_space();

  ///
  /// The base space component of this (const version).
  ///
  const total_poset_member& base_space() const;

  ///
  /// True if this has the same base as xother.
  ///
  bool same_base_space(const section_space_schema_member& xother) const;

  ///
  /// The member id of the fiber schema component of this.
  ///
  pod_index_type fiber_schema_id() const;

  ///
  /// The member id of the fiber schema component of this.
  ///
  void fiber_schema_id(scoped_index& result) const;

  ///
  /// The fiber schema component of this (mutable version).
  ///
  schema_poset_member& fiber_schema();

  ///
  /// The fiber schema component of this (const version).
  ///
  const schema_poset_member& fiber_schema() const;

  ///
  /// True if this has the same fiber schema as xother.
  ///
  bool same_fiber_schema(const section_space_schema_member& xother) const;

  ///
  /// The fiber space for section spaces on this schema (mutable version).
  ///
  poset& fiber_space();

  ///
  /// The fiber space for section spaces on this schema (const version).
  ///
  const poset& fiber_space() const;

  ///
  /// The dimension of the base space component.
  ///
  int db() const;

  ///
  /// The dimension of the fiber space component.
  ///
  int df() const;

  ///
  /// The dimension of the fiber space component.
  ///
  int df(bool xauto_access);

  ///
  /// True if this member is factorable into base space and fiber schema
  /// components.
  ///
  bool is_factorable() const;

  ///
  /// The number of members in the intersection of the
  /// evaluation subposet and the down set of the base space component.
  ///
  int evaluation_ct() const;

  ///
  /// The number of members in the intersection of the
  /// discretization subposet and the down set of the base space component.
  ///
  int discretization_ct() const;

  ///
  /// The discretization subposet for section spaces on this schema (mutable version).
  ///
  subposet& discretization();

  ///
  /// The discretization subposet for section spaces on this schema (const version).
  ///
  const subposet& discretization() const;

  ///
  /// True if this has the same discretization as xother.
  ///
  bool same_discretization(const section_space_schema_member& xother) const;

  ///
  /// The evaluation subposet for section spaces on this schema (mutable version).
  ///
  subposet& evaluation();

  ///
  /// The evaluation subposet for section spaces on this schema (const version).
  ///
  const subposet& evaluation() const;

  ///
  /// True if this has the same evaluation as xother.
  ///
  bool same_evaluation(const section_space_schema_member& xother) const;

  ///
  /// The name of the evaluator family for section spaces on schemae hosted by this.
  ///
  string evaluator_family_name() const;

  ///
  /// The name of the id space for intersection of xsp
  /// with the down set of the member with index xindex.
  ///
  static string intersection_id_space_name(const subposet& xsp, const pod_index_type xindex);

  ///
  /// The name of the id space for intersection of xsp
  /// with the down set of the member with index xindex.
  ///
  static string intersection_id_space_name(const subposet& xsp, const scoped_index& xindex);

  /// @todo Remove.
//   ///
//   /// The number of bytes in this dof
//   ///
//   virtual size_t size() const = 0;

//   ///
//   /// The alignment for this dof
//   ///
//   virtual size_t alignment() const = 0;

//   ///
//   /// The primitive type index of the dof defined by this.
//   ///
//   virtual sheaf::primitive_type type() const = 0;

  ///
  /// A postorder iterator over the table (xis_table_dofs == true)
  /// or row (xis_table_dofs == false) dofs defined by version
  /// version of this.
  ///
  virtual poset_dof_iterator* dof_iterator(bool xis_table_dofs,
					   int xversion = CURRENT_MEMBER_VERSION) const = 0;

  ///
  /// True if this schema contains all the table dofs (xis_table_dofs true)
  /// or row dofs (xis_is_table_dofs false) contained in xother.
  /// (This schema may contain additional dofs as well.)
  ///
  virtual bool conforms_to(const schema_poset_member& xother, bool xis_table_dofs) const;

protected:

  ///
  /// Default constructor; creates a new,
  /// unattached section_space_schema_member handle.
  /// Intended for use only by descendants.
  ///
  section_space_schema_member();

  ///
  /// Initializes the handle data members when
  /// this handle is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// The member id of the base space component of this.
  ///
  pod_index_type _base_space_id;

  ///
  /// The base space component of this.
  ///
  total_poset_member _base_space;

  ///
  /// The member id of the fiber schema component of this.
  ///
  pod_index_type _fiber_schema_id;

  ///
  /// The fiber schema component of this.
  ///
  schema_poset_member _fiber_schema;

  ///
  /// The dimension of the base space component.
  ///
  mutable int _db;

  ///
  /// The number of members in the intersection of the
  /// evaluation subposet the down set of the base space component.
  ///
  mutable int _evaluation_ct;

  ///
  /// The number of members in the intersection of the
  /// discretization subposet the down set of the base space component.
  ///
  mutable int _discretization_ct;

private:

  //@}


  // ===========================================================
  /// @name SCHEMA_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  /// @todo Remove.
//   ///
//   /// The type of table dofs (xis_table_dof == true) or
//   /// row dofs (xis_table_dof == false) defined by this schema.
//   /// Returns NOT_A_PRIMITIVE_TYPE if the dofs are
//   /// not all the same type.
//   ///
//   virtual primitive_type dof_tuple_type(bool xis_table_dof) const = 0;

  /// @hack using declaration broken, must explicitly propagate
  /// the next six declarations.
  ///
  /// @error can not use inherited version, must over ride it.
  /// Inherited version uses dof subposet, which doesn't exist
  /// for this class.
  ///

  ///
  /// True if xother is a dof in the table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false) of the schema defined by this.
  ///
  inline bool contains_dof(const schema_poset_member& xother, bool xin_table_dofs) const
  {
    return schema_poset_member::contains_dof(xother, xin_table_dofs);
  };

  ///
  /// True if this is in the table dofs part of the schema defined by this.
  /// Synonym for contains_dof(xother, true).
  ///
  inline bool contains_table_dof(const schema_poset_member& xother) const
  {
    return contains_dof(xother, true);
  };

  ///
  /// True if this is in the row dofs part of the schema defined by this.
  /// Synonym for contains_dof(xother, false).
  ///
  inline bool contains_row_dof(const schema_poset_member& xother) const
  {
    return contains_dof(xother, false);
  };

  ///
  /// True if xother_id is the index of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  inline bool contains_dof(pod_index_type xother_id, bool xin_table_dofs) const
  {
    return schema_poset_member::contains_dof(xother_id, xin_table_dofs);
  };

  ///
  /// True if xother_id is the index of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  inline bool contains_dof(const scoped_index& xother_id, bool xin_table_dofs) const
  {
    return schema_poset_member::contains_dof(xother_id, xin_table_dofs);
  };

  ///
  /// True if xother_id is the index of a dof in the table dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, true).
  ///
  inline bool contains_table_dof(pod_index_type xother_id) const
  {
    return contains_dof(xother_id, true);
  };

  ///
  /// True if xother_id is the index of a dof in the table dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, true).
  ///
  inline bool contains_table_dof(const scoped_index& xother_id) const
  {
    return contains_dof(xother_id, true);
  };

  ///
  /// True if xother_id is the index of a dof in the row dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, false).
  ///
  inline bool contains_row_dof(pod_index_type xother_id) const
  {
    return contains_dof(xother_id, false);
  };

  ///
  /// True if xother_id is the index of a dof in the row dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, false).
  ///
  inline bool contains_row_dof(const scoped_index& xother_id) const
  {
    return contains_dof(xother_id, false);
  };

  ///
  /// True if xother_id is the index of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  bool contains_dof(pod_index_type xbase_id,
		    pod_index_type xfiber_id,
		    bool xin_table_dofs) const;

  ///
  /// True if xother_id is the index of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  bool contains_dof(const scoped_index& xbase_id,
                    const scoped_index& xfiber_id,
                    bool xin_table_dofs) const;

  ///
  /// True if xother_id is the index of a dof in the table dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, true).
  ///
  inline bool contains_table_dof(pod_index_type xbase_id,
                                 pod_index_type xfiber_id) const
  {
    return contains_dof(xbase_id, xfiber_id, true);
  };

  ///
  /// True if xother_id is the index of a dof in the table dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, true).
  ///
  inline bool contains_table_dof(const scoped_index& xbase_id,
                                 const scoped_index& xfiber_id) const
  {
    return contains_dof(xbase_id, xfiber_id, true);
  };

  ///
  /// True if xother_id is the index of a dof in the row dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, false).
  ///
  inline bool contains_row_dof(pod_index_type xbase_id,
                               pod_index_type xfiber_id) const
  {
    return contains_dof(xbase_id, xfiber_id, false);
  };

  ///
  /// True if xother_id is the index of a dof in the row dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, false).
  ///
  inline bool contains_row_dof(const scoped_index& xbase_id,
                               const scoped_index& xfiber_id) const
  {
    return contains_dof(xbase_id, xfiber_id, false);
  };

  /// @todo Remove.
//   ///
//   /// True if this is in the table dofs part (xin_table_dofs == true)
//   /// or in the row dofs part (xin_table_dofs == false) of some schema.
//   ///
//   virtual bool is_dof(bool xin_table_dofs) const = 0;

protected:

  ///
  /// The dof_descriptors_array for the table dof tuple
  /// (xis_table_dof true) or row dof tuple defined by this schema.
  /// The offsets in the descriptors are defined by post-ordered,
  /// contiguous, properly aligned allocation of the dofs.
  /// Note: although returned by pointer,
  /// the client must not delete the dof offsets array.
  /// Not implemented for xis_table_dof false.
  ///
  ///
  virtual dof_descriptor_array* dof_descriptors(bool xis_table_dof) const = 0;

  ///
  /// Updates table dof id space.
  ///
  virtual void update_table_dof_id_space() const;

  ///
  /// Update the table dof descriptors.
  ///
  virtual void update_table_dof_descriptors() const;

private:

  //@}


  // ===========================================================
  /// @name NEW DOF ACCESS FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// The id space for the discretization members
  /// in the down set of the base space of this (const version).
  ///
  const index_space_handle& discretization_id_space() const;
 
  ///
  /// The id space for the discretization members
  /// in the down set of the base space of this (const version).
  ///
  const index_space_handle& discretization_id_space(bool xauto_access) const;
 
  ///
  /// The id space for the discretization members
  /// in the down set of the base space of this (mutable version).
  ///
  index_space_handle& discretization_id_space();
 
  ///
  /// The id space for the discretization members
  /// in the down set of the base space of this (mutable version).
  ///
  index_space_handle& discretization_id_space(bool xauto_access);
 
  ///
  /// The id space for the dofs in the 
  /// down set of the fiber schema of this.
  ///
  const index_space_handle& fiber_schema_id_space(bool xis_table_dofs) const;
 
  ///
  /// The id space for the dofs in the 
  /// down set of the fiber schema of this.
  ///
  const index_space_handle& fiber_schema_id_space(bool xis_table_dofs, bool xauto_access) const;
  
  using schema_poset_member::size;
  
  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type size(pod_index_type xdof_id,
			 bool xis_table_dof) const = 0;
 
  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  /// 
  /// @issue This signature is redundant for xis_table_dof true, but without
  /// the xis_table_dof argument this signature creates an overload ambiguity
  /// with size(pod_index_type, bool). Similar problem occurs with alignment,
  /// type, and offset.
  ///
  virtual size_type size(pod_index_type xdisc_id, 
			 pod_index_type xfiber_dof_id, 
			 bool xis_table_dof) const = 0;

  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type size(const scoped_index& xdisc_id,
			 const scoped_index& xfiber_dof_id,
			 bool xis_table_dof,
			 bool xauto_access) const = 0;

  using schema_poset_member::alignment;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type alignment(pod_index_type xdof_id,
			      bool xis_table_dof) const = 0;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type alignment(pod_index_type xdisc_id,
			      pod_index_type xfiber_dof_id,
			      bool xis_table_dof) const = 0;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type alignment(const scoped_index& xdisc_id,
			      const scoped_index& xfiber_dof_id,
			      bool xis_table_dof,
			      bool xauto_access) const = 0;

  using schema_poset_member::type;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual primitive_type type(pod_index_type xdof_id,
			      bool xis_table_dof) const = 0;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual primitive_type type(pod_index_type xdisc_id,
			      pod_index_type xfiber_dof_id,
			      bool xis_table_dof) const = 0;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual primitive_type type(const scoped_index& xdisc_id,
			      const scoped_index& xfiber_dof_id,
			      bool xis_table_dof, 
			      bool xauto_access) const = 0;

  using schema_poset_member::offset;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type offset(pod_index_type xdof_id,
			   bool xis_table_dof) const = 0;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type offset(pod_index_type xdisc_id,
			   pod_index_type xfiber_dof_id,
			   bool xis_table_dof) const = 0;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type offset(const scoped_index& xdisc_id,
			   const scoped_index& xfiber_dof_id,
			   bool xis_table_dof, 
			   bool xauto_access) const = 0;

  ///
  /// The number of bytes in the fiber.
  ///
  size_type fiber_size() const;

  ///
  /// The number of bytes in the fiber.
  ///
  size_type fiber_size(bool xauto_access) const;

  ///
  /// The number of bytes in the component referred to by xfiber_dof_id.
  ///
  size_type component_size(pod_index_type xfiber_dof_id) const;

  ///
  /// The number of bytes in the component referred to by xfiber_dof_id.
  ///
  size_type component_size(const scoped_index& xfiber_dof_id, bool xauto_access) const;

protected:
 
  ///
  /// The id space for the discretization members
  /// in the down set of the base space of this.
  ///
  mutable index_space_handle* _discretization_id_space;

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Gets an external id corresponding to index() in the id space
  /// with name xid_space_name.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual pod_index_type get_ext_id(const std::string& xid_space_name) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

  /// @todo Remove.
//   ///
//   /// Prepare this for use as a schema.
//   /// @error host is immutable; remove this member.
//   ///
//   virtual void schematize();

  ///
  /// The unrestricted schema for this poset member (mutable version).
  ///
  virtual schema_poset_member& unrestricted_schema();

  ///
  /// The unrestricted schema for this poset member (const version).
  ///
  virtual const schema_poset_member& unrestricted_schema() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name COMPONENT INDEX FACET
  // ===========================================================
  //@{

public:

  /// @todo Remove.
  // $$SCRIBBLE: Remove version hack.

//   ///
//   /// Sets version to (possibly aliased) xversion. If unalias == true,
//   /// set version to the actual version alias refers to.
//   ///
//   virtual void put_version(int xversion, bool xunalias = false);

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  using schema_poset_member::attach_to_state;

  ///
  /// Attach to the state in host() with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  virtual void attach_to_state(pod_index_type xbase_space_id,
                               pod_index_type xfiber_schema_id);

  ///
  /// Attach to the state in host() with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  void attach_to_state(const scoped_index& xbase_space_id,
		       const scoped_index& xfiber_schema_id);

  ///
  /// Attach to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  virtual void attach_to_state(const section_space_schema_poset* xhost,
                               pod_index_type xbase_space_id,
                               pod_index_type xfiber_schema_id);

  ///
  /// Attach to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  void attach_to_state(const section_space_schema_poset* xhost,
		       const scoped_index& xbase_space_id,
		       const scoped_index& xfiber_schema_id);

  ///
  /// Attach to the state in xhost specified by
  /// paths xbase_path and xfiber_schema_path.
  ///
  virtual void attach_to_state(const section_space_schema_poset* xhost,
                               const poset_path& xbase_path,
                               const poset_path& xfiber_schema_path);

  ///
  /// Detach this handle from its state, if any.
  ///
  virtual void detach_from_state();

protected:

private:

  //@}


  // ===========================================================
  /// @name HOST POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The poset which this is a handle to a component of.
  ///
  inline section_space_schema_poset* host() const
  {
    return reinterpret_cast<section_space_schema_poset*>(schema_poset_member::host());
  }

  ///
  /// True if other conforms to host
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

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
  /// Make a new handle, no state instance of current
  ///
  virtual section_space_schema_member* clone() const = 0;

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
  /// Virtual stream insertion.
  ///
  virtual void to_stream(std::ostream& xos = std::cout) const;

protected:

private:

  //@}
};

// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert section_space_schema_member& p into ostream& os.
///
SHEAF_DLL_SPEC std::ostream& operator << (std::ostream &os, section_space_schema_member& p);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle

#endif // SECTION_SPACE_SCHEMA_MEMBER_H
