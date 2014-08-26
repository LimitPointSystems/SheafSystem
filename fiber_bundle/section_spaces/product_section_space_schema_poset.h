
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
/// Interface for class product_section_space_schema_poset.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_PRODUCT_SECTION_SPACE_SCHEMA_POSET_H
#define COM_LIMITPOINT_FIBER_BUNDLE_PRODUCT_SECTION_SPACE_SCHEMA_POSET_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SECTION_SPACE_SCHEMA_POSET_H
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "ComLimitPoint/sheaf/namespace_relative_member_index.h"
#endif

namespace sheaf
{
class ij_product_structure;
}

namespace fiber_bundle
{

using namespace sheaf;

class product_section_space_schema_crg_range;
class product_section_space_schema_member;
class section_space_schema_table_dof_crg_range;

///
/// An schema poset for a section space represented by a Cartesian
/// product subspace of the tensor product of a base space
/// lattice, and a fiber schema lattice.
///
class SHEAF_DLL_SPEC product_section_space_schema_poset : public section_space_schema_poset
{
  friend class fiber_bundle_namespace;
  friend class ij_product_structure;
  friend class product_section_space_schema_member;
  friend class product_section_space_schema_crg_range;
  friend class sec_rep_space;
  friend class section_space_schema_table_dof_crg_range;

  // ===========================================================
  /// @name PRODUCT_SECTION_SPACE_SCHEMA_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(const poset_path& xrep_path, 
				const poset_path& xbase_space_path, 
				const poset_path& xfiber_space_path);

  ///
  /// Creates a new handle attached to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  product_section_space_schema_poset(namespace_poset& xhost,
				     const std::string& xname,
				     const arg_list& xargs,
				     const poset_path& xschema_path,
				     bool xauto_access);

protected:

  ///
  /// Default constructor; creates a new product_section_space_schema_poset handle not attached to any state.
  ///
  product_section_space_schema_poset();

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  product_section_space_schema_poset(const product_section_space_schema_poset& xother);

  ///
  /// Destructor
  ///
  virtual ~product_section_space_schema_poset();

  ///
  /// Initializes xarg to satisfy class invariants.
  ///
  virtual void initialize_arg_list(const namespace_poset& xns,
				   const std::string& xname,
				   arg_list& xargs,
				   const poset_path& xschema_path,
				   bool xauto_access);

  ///
  /// The product structure of this poset.
  ///
  const ij_product_structure& product_structure() const;

  ///
  /// Initialize the row dof subposet to the product of the row dof ids
  /// in the base space and the row dof ids in the fiber schema.
  ///
  void initialize_row_dof_subposet();

  ///
  /// The implicit crg range that represents the table dof members of this poset.
  ///
  section_space_schema_table_dof_crg_range& table_dof_range();

  ///
  /// Set the table dof crg range.
  ///
  void put_table_dof_range(section_space_schema_table_dof_crg_range& xtable_dof_range);

  ///
  /// The implicit crg range that represents the product members of this poset.
  ///
  product_section_space_schema_crg_range& product_range();

  ///
  /// Set the product range.
  ///
  void put_product_range(product_section_space_schema_crg_range& xproduct_range);

  ///
  /// Creates prototype for this class and enters in in factory.
  ///
  static bool make_prototype();

  ///
  /// The implicit crg range that represents the table dof members of this poset.
  ///
  section_space_schema_table_dof_crg_range* _table_dof_range;

  ///
  /// The implicit crg range that represents the product members of this poset.
  ///
  product_section_space_schema_crg_range* _product_range;

private:

  //@}


  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  using section_space_schema_poset::tuple;

  ///
  /// The tuple conversion from section space schema id xindex to the
  /// base space id xbase_space_id and fiber schema id xfiber_schema_id.
  ///
  virtual void tuple(pod_index_type xindex,
		     pod_index_type& xbase_space_id,
		     pod_index_type& xfiber_schema_id) const;

  using section_space_schema_poset::ordinal;

  ///
  /// The ordinal conversion from base space id xbase_space_id and
  /// fiber schema id xfiber_schema_id to section space schema id xindex.
  ///
  virtual void ordinal(pod_index_type xbase_space_id,
		       pod_index_type xfiber_schema_id,
		       pod_index_type& xindex) const;

  using section_space_schema_poset::is_homogeneous;

  ///
  /// True if xindex is in the homogeneous member id space.
  ///
  virtual bool is_homogeneous(pod_index_type xindex) const;

  ///
  /// True if this poset contains a member with base space id xbase_space_id
  /// and fiber schema id xfiber_schema_id.
  ///
  virtual bool contains_range_member(pod_index_type xbase_space_id,
				     pod_index_type xfiber_schema_id,
				     bool xauto_access) const;

  ///
  /// Extends the hub id space to match extension of the base space.
  ///
  virtual void update_hub_id_space(bool xauto_access);

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

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  void new_state(namespace_poset& xhost,
                 const std::string& xname,
                 const arg_list& xargs,
                 const poset_path& xschema_path,
                 bool xauto_access);

  ///
  /// Attaches this external poset to a new poset state with schema
  /// given by xschema and table dofs by xdof_map.
  /// Intended for use by i/o subsystem.
  ///
  virtual void new_state(const schema_poset_member& xschema,
                         array_poset_dof_map& xdof_map);

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


  /// @todo Remove.
//   // ===========================================================
//   /// @name SCHEMATIZATION FACET
//   // ===========================================================
//   //@{

// public:

//   using poset_state_handle::is_schematized;

//   ///
//   /// True if this poset has been prepared for use as a schema,
//   /// that is, if the top member has been schematized.
//   ///
//   virtual bool is_schematized(bool xauto_access) const;

//   ///
//   /// True if the member with index xindex has been prepared for use as a schema.
//   ///
//   virtual bool is_schematized(pod_index_type xindex, bool xauto_access) const;

//   ///
//   /// Prepare this poset and its top member for use as a schema.
//   /// If xall_members = true, schematize all other members as well.
//   ///
//   virtual void schematize(subposet* xtable_dof_subposet,
//                           subposet* xrow_dof_subposet,
//                           bool xall_members = false);

// protected:

// private:

//   //@}


  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The top of member of the lattice (mutable version)
  ///
  product_section_space_schema_member& top();

  ///
  /// The top of member of the lattice (const version) 
  ///
  const product_section_space_schema_member& top() const;

  ///
  /// The bottom of member of the lattice (mutable version)
  ///
  product_section_space_schema_member& bottom();

  ///
  /// The bottom of member of the lattice (const version)
  ///
  const product_section_space_schema_member& bottom() const;

  using poset_state_handle::is_jim;

  ///
  /// True if the member with index xindex is a jim.
  ///
  virtual bool is_jim(pod_index_type xindex, bool xin_current_version = true) const;

  using poset_state_handle::member_name;

  ///
  /// The name of the member with index xindex
  ///
  virtual string member_name(pod_index_type xindex, bool xauto_access = false) const;

protected:

  ///
  /// Creates the members common to every poset (i.e. _top and _bottom).
  ///
  virtual void initialize_standard_members();

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  /// @todo Remove.
//   using poset_state_handle::is_valid_int_id;

//   ///
//   /// True if xint_id can be translated to an external id using
//   /// the equivalence map with name xid_space_name.
//   ///
//   virtual bool is_valid_int_id(pod_index_type xint_id,
// 			       const std::string& xid_space_name,
// 			       bool xauto_access) const;

//   using poset_state_handle::get_ext_id;

//   ///
//   /// Translates xint_id to an external id using
//   /// the equivalence map with name xid_space_name.
//   ///
//   virtual pod_index_type get_ext_id(pod_index_type xint_id,
// 				    const std::string& xid_space_name,
// 				    bool xauto_access) const;

  ///
  /// Creates a member handle of the type appropriate for members of this
  /// when used as a schema. Intended for use only by the i/o subsystem.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual schema_poset_member*
  new_schema_handle(const std::string& xid_space_name,
                    pod_index_type xschema_member_ext_id,
                    pod_index_type xbase_space_ext_id,
                    pod_index_type xfiber_schema_ext_id,
                    pod_index_type xlocal_schema_ext_id);

  // Note that we can not covariantly redefine the return type
  // of new_schema_handle without including product_section_space_schema_member.h,
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
  virtual product_section_space_schema_poset* clone() const;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  product_section_space_schema_poset& operator=(const poset_state_handle& xother);

private:

  //@}
};

} // namespace fiber_bundle

#endif // COM_LIMITPOINT_FIBER_BUNDLE_PRODUCT_SECTION_SPACE_SCHEMA_POSET_H
