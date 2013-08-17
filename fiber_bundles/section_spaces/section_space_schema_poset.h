


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class section_space_schema_poset.

#ifndef SECTION_SPACE_SCHEMA_POSET_H
#define SECTION_SPACE_SCHEMA_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP_H
#include "array_poset_dof_map.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "namespace_relative_member_index.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H
#include "section_space_schema_table_dofs_type.h"
#endif

#ifndef SEC_REP_DESCRIPTOR_H
#include "sec_rep_descriptor.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

namespace sheaf
{
class ij_product_structure;
class namespace_poset;
class namespace_poset_member;
}

namespace fiber_bundle
{

using namespace sheaf;


class section_space_schema_member;

///
/// An abstract schema poset for a section space. A Cartesian
/// product subspace of the tensor product of a base space
/// lattice, a fiber schema lattice, and possibly a local schema lattice.
///
class SHEAF_DLL_SPEC section_space_schema_poset : public poset_state_handle
{
  friend class namespace_poset;

  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef section_space_schema_member member_type;
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef section_space_schema_table_dofs_type table_dofs_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// The representation for section spaces on this schema.
  ///
  sec_rep_descriptor& rep();

  ///
  /// The representation for section spaces on this schema; const version.
  ///
  const sec_rep_descriptor& rep() const;

  ///
  /// True if the discretization and evaluation subposets named 
  /// in xrep are included in xbase_space and the discretization 
  /// subposet has a non-empty id space.
  ///
  static bool rep_is_valid(const sec_rep_descriptor& xrep, const poset_state_handle& xbase_space);

  ///
  /// True if and only if the section representation specified in xargs 
  /// is valid in the base space specified in xargs; that is, if the 
  /// discretization and evaluation subposets named in xrep are included
  ///  in xbase_space and the discretization subposet has a non-empty id space.
  ///
  bool rep_is_valid(const namespace_poset& xns, const arg_list& xaregs, bool xauto_access) const;

  ///
  /// The upper bound of the member id of the base space
  /// for section spaces on this schema.
  ///
  pod_index_type base_space_member_id_ub() const;

  ///
  /// Computes the base space member id associated with hub id xmbr_hub_id.
  ///
  virtual pod_index_type get_base_space_id_from_index(pod_index_type xmbr_hub_id) const;

  ///
  /// Computes the base space member id associated with xindex.
  ///
  void get_base_space_id_from_index(const scoped_index& xmbr_id,
				    scoped_index& result) const;

  ///
  /// The increment in the member id when the id of the
  /// base space component is increased by one.
  ///
  int base_space_stride() const;

  ///
  /// The dimension of the base space.
  ///
  int db() const;

  ///
  /// The base space for section spaces on this schema.
  ///
  base_space_poset& base_space();

  ///
  /// The base space for section spaces on this schema, const version.
  ///
  const base_space_poset& base_space() const;

  ///
  /// The upper bound on the member id of the fiber schema
  /// for section spaces on this schema.
  ///
  pod_index_type fiber_schema_member_id_ub() const;

  ///
  /// Computes the fiber schema member id associated with hub id xmbr_hub_id.
  ///
  virtual pod_index_type get_fiber_schema_id_from_index(pod_index_type xmbr_hub_id) const;

  ///
  /// Computes the fiber schema member id associated with xindex.
  ///
  void get_fiber_schema_id_from_index(const scoped_index& xmbr_id,
				      scoped_index& result) const;

  ///
  /// The increment in the member id when the id of the
  /// fiber schema component is increased by one.
  ///
  int fiber_schema_stride() const;

  ///
  /// The dimension of the fiber space.
  ///
  int df() const;

  ///
  /// The fiber schema for section spaces on this schema (mutable version).
  ///
  poset_state_handle& fiber_schema();

  ///
  /// The fiber schema for section spaces on this schema (const version).
  ///
  const poset_state_handle& fiber_schema() const;

  ///
  /// The fiber space for section spaces on this schema.
  ///
  poset& fiber_space();

  ///
  /// The fiber space for section spaces on this schema, const version.
  ///
  const poset& fiber_space() const;
  
  ///
  /// The discretization subposet for section spaces on this schema.
  ///
  subposet& discretization();

  ///
  /// The discretization subposet for section spaces on this schema, const version.
  ///
  const subposet& discretization() const;

  ///
  /// Switch that tells the user if the multivalued subposet exists
  ///
  bool is_multivalued() const;

  ///
  /// The multivalued subposet for section spaces on this schema.
  ///
  subposet& multivalued();

  ///
  /// The multivalued subposet for section spaces on this schemam const ver.
  ///
  const subposet& multivalued() const;

  ///
  /// The evaluation subposet for section spaces on this schema.
  ///
  subposet& evaluation();

  ///
  /// The evaluation subposet for section spaces on this schema, const ver.
  ///
  const subposet& evaluation() const;

  ///
  /// The name of the evaluator family for section spaces on this schema.
  ///
  string evaluator_family_name() const;

  ///
  /// The product structure of this schema.
  ///
  const ij_product_structure& product_structure() const;

  ///
  /// Computes the index associated with component ids
  /// xbase_space_id and xfiber_schema_id.
  ///
  virtual pod_index_type
  get_index_from_components(pod_index_type xbase_space_id,
                            pod_index_type xfiber_schema_id) const = 0;

  ///
  /// Computes the index associated with component ids
  /// xbase_space_id and xfiber_schema_id.
  ///
  void get_index_from_components(const scoped_index& xbase_space_id,
				 const scoped_index& xfiber_schema_id,
				 scoped_index& result) const;

  ///
  /// Extends the hub id space to match extension of the base space.
  ///
  void update_hub_id_space(bool xauto_access);

protected:

  ///
  /// The representation for section spaces on this schema.
  ///
  sec_rep_descriptor _rep;

  ///
  /// The base space for section spaces on this schema.
  ///
  base_space_poset* _base_space;

//   ///
//   /// The fiber schema for section spaces on this schema.
//   ///
//   poset_state_handle _fiber_schema;

  /// @hack the "fiber space hack", the schema poset should not own the
  /// fiber space. The fiber space is instantiated on a specific fiber
  /// schema member and hence should belong either to that member or
  /// to a section space instantiated on that member. But we have no
  /// way currently to implement either of these associations.

  ///
  /// The fiber space for section spaces on this schema.
  ///
  poset* _fiber_space;

  ///
  /// The discretization subposet for section spaces on this schema.
  ///
  subposet  _discretization;

  ///
  /// The multivalued subposet for section spaces on this schema.
  ///
  subposet  _multivalued;

  ///
  /// The evaluation subposet for section spaces on this schema.
  ///
  subposet _evaluation;

  ///
  /// The Cartisian product subspace structure.
  ///
  ij_product_structure* _product;

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_poset();

  ///
  /// Covariant constructor
  ///
  section_space_schema_poset(section_space_schema_member* xtop, section_space_schema_member* xbottom);

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// Get read access to the state associated with this.
  ///
  virtual void get_read_access() const;

  ///
  /// Get read write access to the state associated with this.  If
  /// release_read_only_access is requested, read only access will be
  /// released then read_write_access will be requested, finally the
  /// same level of read_access as before will be requested.
  ///
  virtual void get_read_write_access(bool xrelease_read_only_access = false);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  virtual void release_access(bool xall = false) const;

protected:

  ///
  /// Initializes the handle data members that depend on the
  /// table dofs and are required to get access when this handle
  /// is used to create a new state. Intended to be called only
  /// from new_state.
  ///
  virtual void initialize_handle_data_members(const namespace_poset& xns);

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Release all access to posets this depends on,
  /// then detach and delete the state.
  ///
  virtual void terminate_access();  

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// OBSOLETE: use table_dofs().
  /// Pointer to the storage for the table dofs.
  ///
  inline table_dofs_type* table_dof_tuple_ptr()
  {
    return reinterpret_cast<table_dofs_type*>(table_dof_map().dof_tuple());
  };

  ///
  /// OBSOLETE: use table_dofs().
  /// Pointer to the storage for the table dofs.
  ///
  inline const table_dofs_type* table_dof_tuple_ptr() const
  {
    return reinterpret_cast<const table_dofs_type*>(table_dof_map().dof_tuple());
  };

private:

  //@}

  // ===========================================================
  /// @name SCHEMATIZATION FACET
  // ===========================================================
  //@{

public:

  using poset_state_handle::is_schematized;

  ///
  /// True if this poset has been prepared for use as a schema,
  /// that is, if the top member has been schematized.
  ///
  virtual bool is_schematized(bool xauto_access) const;

  ///
  /// Prepare this poset and its top member for use as a schema.
  /// If xall_members = true, schematize all other members as well.
  ///
  virtual void schematize(subposet* xtable_dof_subposet,
                          subposet* xrow_dof_subposet,
                          bool xall_members = false);

protected:

private:

  //@}


  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The top of member of the lattice (mutable version)
  ///
  section_space_schema_member& top();

  ///
  /// The top of member of the lattice (const version) 
  ///
  const section_space_schema_member& top() const;

  ///
  /// The bottom of member of the lattice (mutable version)
  ///
  section_space_schema_member& bottom();

  ///
  /// The bottom of member of the lattice (const version)
  ///
  const section_space_schema_member& bottom() const;

  ///
  /// The number of members of this poset
  ///
  virtual int member_ct() const;

  ///
  /// The number of standard members automatically
  /// allocated by the constructor.
  ///
  virtual int standard_member_ct() const;

  ///
  /// The upper bound on the member_index;
  ///
  virtual scoped_index member_index_ub() const;

  ///
  /// An iterator for members of this poset
  ///
  index_iterator member_iterator() const;

  using poset_state_handle::contains_member;

  ///
  /// True if some version of this poset contains poset member
  /// with hub id xmbr_hub_id
  ///
  virtual bool contains_member(pod_index_type xmbr_hub_id, bool xauto_access = true) const;

  ///
  /// True if version xversion of this poset contains poset member
  /// with hub id xmbr_hub_id
  ///
  virtual bool contains_member(pod_index_type xmbr_hub_id, int xversion, bool xauto_access = true) const;

  using poset_state_handle::is_jim;

  ///
  /// True if the member with hub id xmbr_hub_id is a jim.
  ///
  virtual bool is_jim(pod_index_type xmbr_hub_id, bool xin_current_version = true) const;

  using poset_state_handle::is_atom;

  ///
  /// True if the member with hub id xmbr_hub_id covers the bottom.
  ///
  virtual bool is_atom(pod_index_type xmbr_hub_id) const;

  using poset_state_handle::member_name;

  ///
  /// The name of the member with hub id xmbr_hub_id
  ///
  virtual string member_name(pod_index_type xmbr_hub_id, bool xauto_access = false) const;

protected:

  ///
  /// Creates the members common to every poset (i.e. _top and _bottom).
  ///
  virtual void initialize_standard_members();

  ///
  /// Create a new bottom or top member.
  /// @hack Cartesian product subspace hack;
  /// intended only for use by section_space_schema_poset 
  /// constructor.
  ///
  void new_standard_member_hack(standard_member_index xindex);

  using poset_state_handle::new_member;

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// Redefined here only to trap attempts to make a new member,
  /// as an aid to debugging.
  ///
  virtual pod_index_type new_member(bool xis_jim, pod_index_type xdof_tuple_id);

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// Redefined here only to trap attempts to make a new member,
  /// as an aid to debugging.
  ///
  virtual pod_index_type new_member(bool xis_jim, poset_dof_map* xdof_map = 0, bool xcopy_dof_map = false);

  using poset_state_handle::delete_member;

  ///
  /// Delete the member with hub id xmbr_hub_id.
  /// Redefined here only to trap attempts to make a new member,
  /// as an aid to debugging.
  ///
  virtual void delete_member(pod_index_type xmbr_hub_id);

private:

  //@}


  // ===========================================================
  /// @name COVER RELATION FACET
  // ===========================================================
  //@{

public:

  using poset_state_handle::new_link;

  ///
  /// Insert a link from lesser to greater (i.e. lesser <= greater).
  /// Redefined here only to trap attempts to make a new link,
  /// as an aid to debugging.
  ///
  virtual void new_link(pod_index_type xgreater, pod_index_type xlesser);

  using poset_state_handle::delete_link;

  ///
  /// Delete the link with between xgreater and xlesser
  /// Redefined here only to trap attempts to delete a link,
  /// as an aid to debugging.
  ///
  virtual void delete_link(pod_index_type xgreater, pod_index_type xlesser);

protected:

private:

  //@}

  // ===========================================================
  /// @name POWERSET FACET
  // ===========================================================
  //@{

public:

  using poset_state_handle::new_subposet;

  ///
  ///
  /// Creates a new subposet. If xinitialize, set the membership
  /// to include the members with indices in xmambers; otherwise,
  /// leave the subposet empty.
  ///
  virtual pod_index_type new_subposet(const block<pod_index_type>& xmembers);

  using poset_state_handle::delete_subposet;

  ///
  /// Deletes the subposet with hub id xsubposet_hub_id
  ///
  virtual void delete_subposet(pod_index_type xsubposet_hub_id);

  ///
  /// The number of versions.
  ///
  virtual int version_ct() const;

  ///
  /// The current version
  ///
  virtual int version() const;

  using poset_state_handle::version_index;

  ///
  /// The subposet index of the whole() subposet for version xversion.
  ///
  virtual pod_index_type version_index(int xversion) const;

  using poset_state_handle::version_jims_index;

  ///
  /// The subposet index of the jims() subposet for version xversion.
  ///
  virtual pod_index_type version_jims_index(int xversion) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// An iterator over the members of the decomposition identified by xindex.
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  /// Row decomposition i/o is not supported for section
  /// space schema in PSH2; this routine is not implemented
  /// and will issue a fatal error if called.
  ///
  virtual index_iterator* get_decomposition(pod_index_type xindex) const;

  using poset_state_handle::is_valid_int_id;

  ///
  /// True if xint_id can be translated to an external id using
  /// the equivalence map with name xid_space_name.
  ///
  virtual bool is_valid_int_id(pod_index_type xint_id,
			       const string& xid_space_name,
			       bool xauto_access) const;

  using poset_state_handle::get_ext_id;

  ///
  /// Translates xint_id to an external id using
  /// the equivalence map with name xid_space_name.
  ///
  virtual pod_index_type get_ext_id(pod_index_type xint_id,
				    const string& xid_space_name,
				    bool xauto_access) const;

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;


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
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual section_space_schema_poset* clone() const = 0;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  section_space_schema_poset& operator=(const poset_state_handle& xother);

private:

  //@}
};

} // namespace fiber_bundle

#endif // SECTION_SPACE_SCHEMA_POSET_H
