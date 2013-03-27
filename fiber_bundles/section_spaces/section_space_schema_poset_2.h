
// $RCSfile: section_space_schema_poset_2.h,v $ $Revision: 1.2 $ $Date: 2013/01/10 13:54:36 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class section_space_schema_poset.

#ifndef SECTION_SPACE_SCHEMA_POSET_H
#define SECTION_SPACE_SCHEMA_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
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
class namespace_poset;
}

namespace fiber_bundle
{

using namespace sheaf;

class section_space_schema_crg_range;
class section_space_schema_member;

///
/// An abstract schema poset for a section space.
///
class SHEAF_DLL_SPEC section_space_schema_poset : public poset
{
  friend class namespace_poset;
  friend class section_space_schema_member;

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
  /// The tuple conversion from section space schema id xindex to the
  /// base space id xbase_space_id and fiber schema id xfiber_schema_id.
  ///
  void tuple(const scoped_index& xindex,
	     scoped_index& xbase_space_id,
	     scoped_index& xfiber_schema_id) const;

  ///
  /// The tuple conversion from section space schema id xindex to the
  /// base space id xbase_space_id and fiber schema id xfiber_schema_id.
  ///
  virtual void tuple(pod_index_type xindex,
		     pod_index_type& xbase_space_id,
		     pod_index_type& xfiber_schema_id) const = 0;

  ///
  /// The ordinal conversion from base space id xbase_space_id and
  /// fiber schema id xfiber_schema_id to section space schema id xindex.
  ///
  void ordinal(const scoped_index& xbase_space_id,
	       const scoped_index& xfiber_schema_id,
	       scoped_index& xindex) const;

  ///
  /// The ordinal conversion from base space id xbase_space_id and
  /// fiber schema id xfiber_schema_id to section space schema id xindex.
  ///
  virtual void ordinal(pod_index_type xbase_space_id,
		       pod_index_type xfiber_schema_id,
		       pod_index_type& xindex) const = 0;

  ///
  /// True if xindex is in the homogeneous member id space.
  ///
  bool is_homogeneous(const scoped_index& xindex) const;

  ///
  /// True if xindex is in the homogeneous member id space.
  ///
  virtual bool is_homogeneous(pod_index_type xindex) const = 0;

  ///
  /// True if this poset contains a member with base space id xbase_space_id
  /// and fiber schema id xfiber_schema_id.
  ///
  bool contains_range_member(const scoped_index& xbase_space_id,
			     const scoped_index& xfiber_schema_id,
			     bool xauto_access) const;

  ///
  /// True if this poset contains a member with base space id xbase_space_id
  /// and fiber schema id xfiber_schema_id.
  ///
  virtual bool contains_range_member(pod_index_type xbase_space_id,
				     pod_index_type xfiber_schema_id,
				     bool xauto_access) const = 0;

  ///
  /// Extends the hub id space to match extension of the base space.
  ///
  virtual void update_hub_id_space(bool xauto_access) = 0;

protected:

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_poset();

  ///
  /// Covariant constructor
  ///
  section_space_schema_poset(section_space_schema_member* xtop, section_space_schema_member* xbottom);

  ///
  /// Create the table dof members with the same ids as the table dofs
  /// in the fiber schema id space and initialize the table dof subposet
  /// to contains the members.
  ///
  void initialize_table_dof_subposet();

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
  /// The evaluation subposet for section spaces on this schema.
  ///
  subposet _evaluation;

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

private:

  //@}


  // ===========================================================
  /// @name SCHEMATIZATION FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  using poset_state_handle::new_member;

  ///
  /// Create a disconnected member with is_jim == xis_jim and
  /// the dof tuple identified by xdof_tuple_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member(bool xis_jim, const scoped_index& xdof_tuple_id);

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member(bool xis_jim, poset_dof_map* xdof_map = 0, bool xcopy_dof_map = false);

  ///
  /// Create a disconnected member range of type xrange_type with size xsize,
  /// dof tuple ids xdof_tuple_ids, and range type specific private data xdata.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member_range(const string& xrange_type,
					  size_type xsize,
					  const block<scoped_index>& xdof_tuple_ids,
					  const block<pod_index_type>& xdata);

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

  using poset_state_handle::member_id;

  ///
  /// The member id for base space member with name xbase_space_namd,
  /// and fiber schema member with name xfiber_schema_name.
  ///
  pod_index_type member_id(const string& xbase_space_name,
			   const string& xfiber_schema_name) const;

  ///
  /// The member id for base space member with name xbase_space_namd,
  /// and fiber schema member with name xfiber_schema_name.
  ///
  void member_id(const string& xbase_space_name,
		 const string& xfiber_schema_name,
		 scoped_index& result) const;

  ///
  /// True if and only if a member can be created.
  /// @hack This function is the precondition for the new_member functions
  /// and only exists because the homogeneous range needs to be dynamic.
  /// The number of members created can not exceed the size of the
  /// reserved id space.
  ///
  bool is_new_member_available() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER RELATION FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}

  /// @todo Remove.
  // $$SCRIBBLE: Remove version hack.

  // ===========================================================
  /// @name POWERSET FACET
  // ===========================================================
  //@{

public:

//   ///
//   /// The number of versions.
//   ///
//   virtual int version_ct() const;

//   ///
//   /// The current version
//   ///
//   virtual int version() const;

//   using poset_state_handle::version_index;

//   ///
//   /// The subposet index of the whole() subposet for version xversion.
//   ///
//   virtual pod_index_type version_index(int xversion) const;

//   using poset_state_handle::version_jims_index;

//   ///
//   /// The subposet index of the jims() subposet for version xversion.
//   ///
//   virtual pod_index_type version_jims_index(int xversion) const;

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
