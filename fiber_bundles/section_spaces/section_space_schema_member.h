

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class section_space_schema_member.

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#define SECTION_SPACE_SCHEMA_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef SECTION_DOF_ITERATOR_H
#include "section_dof_iterator.h"
#endif

#ifndef SCHEMA_POSET_MEMBER_H
#include "schema_poset_member.h"
#endif

// #ifndef SECTION_SPACE_SCHEMA_POSET_H
// #include "section_space_schema_poset.h"
// #endif

namespace fiber_bundle
{

using namespace sheaf;

class fiber_bundles_namespace;
class sec_rep_descriptor;
class section_component_iterator;
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

  // Typedefs:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of host poset.
  ///
  typedef section_space_schema_poset host_type;

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  ///
  /// The standard member name for a schema with fiber schema member with name
  /// xfiber_schema_member_name and base space member with name xbase_member_name.
  ///
  static string standard_member_name(const string& xfiber_schema_member_name,
				     const string& xbase_member_name);
  
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

  // None - section_space_schema_poset is immutable.

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  // None - section_space_schema_member is abstract

  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  // None - section_space_schema_member is immutable

  ///
  /// Creates a new jim (join-irreducible member) state in xhost and attaches
  /// this to it.
  ///
  virtual void new_jim_state(poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. The existing dof map with index xtuple_id is used as the dof map.
  ///
  virtual void new_jim_state(pod_index_type xtuple_id,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  ///
  /// Creates a new jim (join-irreducible member) state in xhost and attaches
  /// this to it.
  ///
  virtual void new_jim_state(poset_state_handle* xhost,
                             poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. The existing dof map with index xtuple_id is used as the dof map.
  ///
  virtual void new_jim_state(poset_state_handle* xhost,
                             pod_index_type xtuple_id,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  ///
  /// Creates a new jrm (join-reducible member) state in host() and attaches
  /// this to it.
  ///
  virtual void new_jrm_state(bool xauto_access = true)
  {
    not_implemented();
  }

  ///
  /// Creates a new jrm (join-reducible member) state in xhost and attaches
  /// this to it.
  ///
  virtual void new_jrm_state(poset_state_handle* xhost,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  ///
  /// Computes the join of the members with the indices given in xexpansion.
  /// If the join already exists and !xnew_jim, attaches this to the existing
  /// join. Otherwise, creates a new jrm (join reducible member) state in
  /// xhost and attaches this to it.
  ///
  virtual void new_jrm_state(const scoped_index* xexpansion,
                             int xexpansion_ct,
                             const tern& xnew_jem,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  ///
  /// Computes the join of the members with the indices given in xexpansion.
  /// If the join already exists and !xnew_jim, attaches this to the existing
  /// join. Otherwise, creates a new jrm (join reducible member) state in
  /// xhost and attaches this to it.
  ///
  virtual void new_jrm_state(poset_state_handle* xhost,
                             const scoped_index* xexpansion,
                             int xexpansion_ct,
                             const tern& xnew_jem,
                             bool xauto_access = true)
  {
    not_implemented();
  };

  using abstract_poset_member::new_jem_state;

  ///
  /// Creates a new jrm state in xhost which is join equivalent to xother
  /// and attaches this to it.
  ///
  virtual void new_jem_state(abstract_poset_member* xother,
			     bool xgreatest,
                             bool xauto_access)
  {
    not_implemented();
  };

  ///
  /// Creates a new jrm state in xhost which is join equivalent to xother
  /// and attaches this to it.
  ///
  virtual void new_jem_state(poset_state_handle* xhost,
                             pod_index_type xhub_id,
			     bool xgreatest,
                             bool xauto_access)
  {
    not_implemented();
  };

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
  /// The fiber space for section spaces on this schema,
  /// downcast to fiber space type F.
  ///
  template<typename F>
  F& fiber_space();

  ///
  /// The fiber space for section spaces on this schema,
  /// downcast to fiber space type F, const version.
  ///
  template<typename F>
  const F& fiber_space() const;

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
  /// Switch that tells the user if the multivalued subposet exists
  ///
  bool is_multivalued() const;

  ///
  /// The multivalued subposet for section spaces on this schema (mutable version).
  ///
  subposet& multivalued();

  ///
  /// The multivalued subposet for section spaces on this schema (const version).
  ///
  const subposet& multivalued() const;

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
  /// A postorder iterator over the components defined by this.
  ///
  virtual section_component_iterator* component_iterator() const;

  ///
  /// The name of the evaluator family for section spaces on schemae hosted by this.
  ///
  string evaluator_family_name() const;

  ///
  /// The name of the id space for intersection of xsp
  /// with the down set of the member with hub id xhub_id.
  ///
  static string intersection_id_space_name(const subposet& xsp, const pod_index_type xhub_id);

  ///
  /// The name of the id space for intersection of xsp
  /// with the down set of the member with id xid.
  ///
  static string intersection_id_space_name(const subposet& xsp, const scoped_index& xid);

  ///
  /// The number of bytes in this dof
  ///
  virtual size_t size() const = 0;

  ///
  /// The alignment for this dof
  ///
  virtual size_t alignment() const = 0;

  ///
  /// The primitive type index of the dof defined by this.
  ///
  virtual sheaf::primitive_type type() const = 0;

  ///
  /// A postorder iterator over the table (xis_table_dofs == true)
  /// or row (xis_table_dofs == false) dofs defined by this.
  ///
  virtual section_dof_iterator* dof_iterator(bool xis_table_dofs,
					     int xversion = CURRENT_MEMBER_VERSION) const;

  ///
  /// A postorder iterator over the table dofs defined by this.
  /// Synonym for dof_iterator(true).
  ///
  inline section_dof_iterator* table_dof_iterator(int xversion = CURRENT_MEMBER_VERSION) const
  {
    return dof_iterator(true, xversion);
  };

  ///
  /// A postorder iterator over the row dofs defined by this.
  ///
  inline section_dof_iterator* row_dof_iterator(int xversion = CURRENT_MEMBER_VERSION) const
  {
    return dof_iterator(false, xversion);
  };

  ///
  /// True if this schema contains all the table dofs (xis_table_dofs true)
  /// or row dofs (xis_is_table_dofs false) contained in xother.
  /// (This schema may contain additional dofs as well.)
  ///
  virtual bool conforms_to(const schema_poset_member& xother, bool xis_table_dofs) const;

  ///
  /// True if the fiber schema associated with xpath
  /// conforms to xfiber_schema_path.
  ///
  static bool fiber_schema_conforms_to(const namespace_poset& xns,
                                       const poset_path& xpath,
                                       const poset_path& xfiber_schema_path,
                                       bool xauto_access = true);

protected:

  ///
  /// Default constructor; creates a new,
  /// unattached section_space_schema_member handle.
  /// Intended for use only by descendants.
  ///
  section_space_schema_member();

  ///
  /// Makes the table or row dof subposets, client id maps,
  /// and other schema info for this.
  //// @error host is immutable; remove this member.
  ////
  virtual void make_schema_info(bool xis_table_dof);

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
  /// The base space componewnt of this.
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

  ///
  /// Updates row cache using existing _discretization_id_space.
  ///
  void update_row_cache_without_disc_id_space() const;

  ///
  /// Updates row cache including _discretization_id_space.
  ///
  void update_row_cache_with_disc_id_space() const;

  ///
  /// Updates _row_dof_id_space.
  ///
  void update_row_dof_id_space() const;  

private:

  //@}


  // ===========================================================
  /// @name SCHEMA_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// The type of table dofs (xis_table_dof == true) or
  /// row dofs (xis_table_dof == false) defined by this schema.
  /// Returns NOT_A_PRIMITIVE_TYPE if the dofs are
  /// not all the same type.
  ///
  virtual primitive_type dof_tuple_type(bool xis_table_dof) const = 0;

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

  ///
  /// True if this is in the table dofs part (xin_table_dofs == true)
  /// or in the row dofs part (xin_table_dofs == false) of some schema.
  ///
  virtual bool is_dof(bool xin_table_dofs) const = 0;

protected:

  ///
  /// Updates cached table properties.
  ///
  virtual void update_table_cache() const;

  ///
  /// Updates cached row properties.
  ///
  virtual void update_row_cache(bool xupdate_id_space = false) const;

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
  virtual size_type size(pod_index_type xdof_id, bool xis_table_dof) const;
 
  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  /// 
  /// @issue This signature is redundant for xis_table_dof true, but without
  /// the xis_table_dof argument this signature creates an overload ambiguity
  /// with size(pod_index_type, bool). Similar problem occurs with alignment,
  /// type, and offset.
  ///
  size_type size(pod_index_type xdisc_id, 
		 pod_index_type xfiber_dof_id, 
		 bool xis_table_dof) const;

  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  size_type size(const scoped_index& xdisc_id,
		 const scoped_index& xfiber_dof_id,
		 bool xis_table_dof,
		 bool xauto_access) const;

  using schema_poset_member::alignment;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type alignment(pod_index_type xdof_id, bool xis_table_dof) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  size_type alignment(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  size_type alignment(const scoped_index& xdisc_id,
		      const scoped_index& xfiber_dof_id,
		      bool xis_table_dof,
		      bool xauto_access) const;

  using schema_poset_member::type;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual primitive_type type(pod_index_type xdof_id, bool xis_table_dof) const;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  primitive_type type(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const;


  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  primitive_type type(const scoped_index& xdisc_id,
		      const scoped_index& xfiber_dof_id,
		      bool xis_table_dof, 
		      bool xauto_access) const;

  using schema_poset_member::offset;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type offset(pod_index_type xdof_id, bool xis_table_dof) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  size_type offset(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  size_type offset(const scoped_index& xdisc_id,
		   const scoped_index& xfiber_dof_id,
		   bool xis_table_dof, 
		   bool xauto_access) const;

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
  virtual pod_index_type get_ext_id(const string& xid_space_name) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

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
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Insert a link from lesser to this (i.e. lesser <= greater).
  //// @error host is immutable; remove this member.
  ////
  virtual void create_cover_link(abstract_poset_member* xlesser)
  {
    not_implemented();
  };

  ///
  /// Delete a link from lesser to this (i.e. lesser <= greater).
  //// @error host is immutable; remove this member.
  ////
  virtual void delete_cover_link(abstract_poset_member* lesser)
  {
    not_implemented();
  };

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline section_space_schema_member* greatest_jem() const
  {
    return static_cast<section_space_schema_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline section_space_schema_member* least_jem() const
  {
    return static_cast<section_space_schema_member*>(abstract_poset_member::least_jem());
  };

  ///
  /// Merge the join-equivalence class of xjem under
  /// the join equivalence class of this
  //// @error host is immutable; remove this member.
  ////
  virtual void merge_jem(const abstract_poset_member* xjem)
  {
    not_implemented();
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name DOWN SET FACET
  // ===========================================================
  //@{

public:

  using abstract_poset_member::down_ct;

  ///
  /// The number of members in the down set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  virtual int down_ct(pod_index_type xfilter_index) const;

  ///
  /// The down set of this member, auto- and pre-allocated versions
  ///
  virtual subposet* down() const;

  ///
  /// The down set of this member, auto- and pre-allocated versions
  ///
  virtual void down_pa(subposet* result) const;

  using abstract_poset_member::up_ct;

  ///
  /// The number of members in the up set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  virtual int up_ct(pod_index_type xfilter_index) const;

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

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// Poset join of this with other, auto-aloocated version.
  /// The poset join is the least upper bound in the poset.
  ///
  inline section_space_schema_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<section_space_schema_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// Poset join of this with other, pre-allocated.
  /// The poset join is the least upper bound in the poset.
  ///
  virtual void p_join_pa(abstract_poset_member* other, abstract_poset_member* result) const;

  ///
  /// Poset meet of this with other, auto-allocated version.
  /// The poset meet is the greatest lower bound in the poset.
  ///
  inline section_space_schema_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<section_space_schema_member*>(abstract_poset_member::p_meet(other));
  };

  ///
  /// Poset meet of this with other, pre-allocated version.
  /// The poset meet is the greatest lower bound in the poset.
  ///
  virtual void p_meet_pa(abstract_poset_member* other, abstract_poset_member* result);

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public:

  /// @error host is immutable; does not support lattice algebra; remove this facet.

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  inline section_space_schema_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    not_implemented();
    return this;
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline section_space_schema_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    not_implemented();
    return this;
  }

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline section_space_schema_member* l_not(bool xnew_jem = true) const
  {
    not_implemented();
    section_space_schema_member* cthis = const_cast<section_space_schema_member*>(this);
    return cthis;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name COMPONENT INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Sets version to (possibly aliased) xversion. If unalias == true,
  /// set version to the actual version alias refers to.
  ///
  virtual void put_version(int xversion, bool xunalias = false);

protected:

private:

  //@}


  // ===========================================================
  /// @name COMPONENT NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// Sets the name of this member to a standard name; if xunique,
  /// make xname the only name.
  ///
  void put_standard_name(bool xunique, bool xauto_access);

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
                               pod_index_type xfiber_schema_id) = 0;

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
                               pod_index_type xfiber_schema_id) = 0;

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
                               const poset_path& xfiber_schema_path) = 0;

  ///
  /// Detach this handle from its state, if any.
  ///
  virtual void detach_from_state();

  ///
  /// Detach this from its state and delete the state.
  //// @todo host is immutable; remove this function
  ////
  virtual void delete_state(bool xauto_access = false)
  {
    not_implemented();
  };

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
  virtual void to_stream(ostream& xos = cout) const;

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
SHEAF_DLL_SPEC ostream& operator << (ostream &os, section_space_schema_member& p);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle

#endif // SECTION_SPACE_SCHEMA_MEMBER_H
