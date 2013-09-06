

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class binary_section_space_schema_poset.

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#define BINARY_SECTION_SPACE_SCHEMA_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_POSET_H
#include "section_space_schema_poset.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP_H
#include "array_poset_dof_map.h"
#endif

namespace sheaf
{
class namespace_poset;
class namespace_poset_member;
}

namespace fiber_bundle
{

class sec_rep_descriptor;

///
/// A schema poset for a section space. A binary Cartesian
/// product subspace of the binary tensor product of a
/// base space lattice and a fiber schema lattice.
/// The tensor product of two lattices B and F is the
/// finite distributive lattice generated by the poset
/// J(B) x J(F), where J(B) is the poset of jims of B
/// and similarly for J(F). The jims of the tensor product
/// are thus pairs (jB, jF) and the general member of the
/// tensor product lattice is equivalent to a subset (in
/// fact a down set) of J(B) x J(F). This class only
/// represents those members of the tensor product which
/// are equivalent to pairs (pB, pF), where pB and pF are
/// arbitrary members of B and F, respectively. Members of this Cartesian
/// product subspace of the tensor product can be represented
/// more efficiently than the general members, since we do not
/// to store the subset defines the member.
///
class SHEAF_DLL_SPEC binary_section_space_schema_poset : public section_space_schema_poset
{
  friend class fiber_bundles_namespace;
  friend class sheaf::namespace_poset; // Qualification needed by g++ 4.2.2
  
  // ===========================================================
  /// @name BINARY_SECTION_SPACE_SCHEMA_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new binary_section_space_schema_poset in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attributes base_space_path, fiber_space_path,
  /// and rep_path specified by xbase_path, xfiber_path, and xrep_path, respectively.
  ///
  static binary_section_space_schema_poset& new_table(namespace_type& xhost, 
                                                      const poset_path& xpath, 
                                                      const poset_path& xschema_path,
                                                      const poset_path& xbase_path,
                                                      const poset_path& xfiber_path,
                                                      const poset_path& xrep_path,
                                                      bool xauto_access);


protected:

  ///
  /// Default constructor; creates a new binary_section_space_schema_poset handle not attached to any state.
  ///
  binary_section_space_schema_poset();

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  binary_section_space_schema_poset(const binary_section_space_schema_poset& xother);

  ///
  /// Destructor
  ///
  virtual ~binary_section_space_schema_poset();

  ///
  /// Creates prototype for this class and enters in in factory.
  ///
  static bool make_prototype();

private:

  //@}


  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_POSET FACET
  // ===========================================================
  //@{

public:

  using section_space_schema_poset::get_index_from_components;

  ///
  /// Computes the index associated with component ids
  /// xbase_space_id, xfiber_schema_id, and xlocal_schema_id.
  ///
  virtual pod_index_type
  get_index_from_components(pod_index_type xbase_space_id,
                            pod_index_type xfiber_schema_id) const;

protected:

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

protected:

  using section_space_schema_poset::new_state;

  ///
  /// Creates a new poset state with path xpath, schema xschema and table dof map xdof_map,
  /// attaches this to the state.
  ///
  virtual void new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map);

private:

  //@}


  // ===========================================================
  /// @name COVER RELATION FACET
  // ===========================================================
  //@{

public:

  using poset_state_handle::contains_link;

  ///
  /// True if there is a cover link between hub id xlesser and hub id xgreater
  ///
  virtual bool contains_link(pod_index_type xgreater,
			     pod_index_type xlesser) const;

  using poset_state_handle::cover_ct;

  ///
  /// The number of members in the lower cover (xlower true)
  /// or upper cover (xlower false) of the member with hub id xhub_id.
  ///
  virtual size_type cover_ct(bool xlower, pod_index_type xhub_id) const;

  using poset_state_handle::le;

  ///
  /// True if xlesser is less than or equal to hub id xgreater.
  ///
  virtual bool le(pod_index_type xgreater, pod_index_type xlesser) const;

  using poset_state_handle::leqv;

  ///
  /// True if xlesser is less than or equivalent to hub id xgreater.
  ///
  virtual bool leqv(pod_index_type xgreater, pod_index_type xlesser) const;

  using poset_state_handle::is_jem;

  ///
  /// True if xother is join equivalent to hub id xhub_id
  ///
  virtual bool is_jem(pod_index_type xhub_id, pod_index_type xother) const;

  using poset_state_handle::greatest_jem;

  ///
  /// The index of the largest member which is join-equivalent to hub id xhub_id
  ///
  virtual pod_index_type greatest_jem(pod_index_type xhub_id) const;

  using poset_state_handle::least_jem;

  ///
  /// The index of the smallest member which is join-equivalent to hub id xhub_id
  ///
  virtual pod_index_type least_jem(pod_index_type xhub_id) const;

  using poset_state_handle::merge_jems;

  ///
  /// Merge the join-equivalence class of xjem2 under that of xjem1
  ///
  virtual void merge_jems(pod_index_type xjem1, pod_index_type xjem2);

protected:

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a member handle of the type appropriate for members of this
  /// when used as a schema. Intended for use only by the i/o subsystem.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual schema_poset_member*
  new_schema_handle(const string& xid_space_name,
                    pod_index_type xschema_member_ext_id,
                    pod_index_type xbase_space_ext_id,
                    pod_index_type xfiber_schema_ext_id,
                    pod_index_type xlocal_schema_ext_id);

  // Note that we can not covariantly redefine the return type
  // of new_schema_handle without including binary_section_space_schema_member.h,
  // which causes a cyclic dependency between the poset and member classes.

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
  virtual binary_section_space_schema_poset* clone() const;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  binary_section_space_schema_poset& operator=(const poset_state_handle& xother);

private:

  //@}
};

} // namespace fiber_bundle

#endif // BINARY_SECTION_SPACE_SCHEMA_POSET_H
