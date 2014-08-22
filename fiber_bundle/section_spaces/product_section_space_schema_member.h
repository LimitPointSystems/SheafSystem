
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
/// Interface for class product_section_space_schema_member.

#ifndef PRODUCT_SECTION_SPACE_SCHEMA_MEMBER_H
#define PRODUCT_SECTION_SPACE_SCHEMA_MEMBER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#include "ComLimitPoint/fiber_bundle/section_space_schema_member.h"
#endif

namespace fiber_bundle
{

class product_section_space_schema_poset;
class sec_rep_descriptor;

///
/// A client handle for a poset member which has been
/// prepared for use as a schema for a section space.
/// See class product_section_space_schema_poset for a
/// description of the schema represented by this class.
///
///
///
class SHEAF_DLL_SPEC product_section_space_schema_member : public section_space_schema_member
{
  // ===========================================================
  /// @name PRODUCT_SECTION_SPACE_SCHEMA_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached product_section_space_schema_member handle.
  ///
  product_section_space_schema_member();

  ///
  /// Copy constructor; creates a new product_section_space_schema_member handle
  /// attached to the same state as xother.
  ///
  explicit product_section_space_schema_member(const product_section_space_schema_member& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual product_section_space_schema_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  product_section_space_schema_member& operator=(const product_section_space_schema_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~product_section_space_schema_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline product_section_space_schema_member* clone(bool xnew_state,
      bool xauto_access = true) const
  {
    return static_cast<product_section_space_schema_member*>
           (section_space_schema_member::clone(xnew_state, xauto_access));
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to a new jim (join-irreducible member)
  /// state in xhost. ("explicit"  prevents interpretation as implicit
  /// conversion from poset* to product_section_space_schema_member&)
  ///
  explicit product_section_space_schema_member(poset* xhost,
					       array_poset_dof_map* xdof_map = 0,
					       bool xcopy_dof_map = false,
					       bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim (join-irreducible member)
  /// state in xhost using the existing dof tuple with index xdof_tuple_id.
  ///
  product_section_space_schema_member(poset* xhost,
				      const scoped_index& xdof_tuple_id,
				      bool xauto_access);

  ///
  /// creates a new jrm (join reducible member) attached to a new member state
  /// in xhost The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  product_section_space_schema_member(poset* xhost,
				      scoped_index* xexpansion,
				      int xexpansion_ct,
				      const tern& xnew_jem,
				      bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new product_section_space_schema_member handle
  /// attached to the member state with hub id xhub_id in xhost
  ///
  product_section_space_schema_member(const product_section_space_schema_poset* xhost,
				      pod_index_type xhub_id);

  ///
  /// Creates a new product_section_space_schema_member handle
  /// attached to the member state with id xid in xhost
  ///
  product_section_space_schema_member(const product_section_space_schema_poset* xhost,
				      const scoped_index& xid);

  ///
  /// Creates a new product_section_space_schema_member handle
  /// attached to the member state with name xname in xhost
  ///
  product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                     const std::string& xname);

  ///
  /// Create a new handle attached to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                     pod_index_type xbase_space_id,
                                     pod_index_type xfiber_schema_id);


  ///
  /// Create a new handle attached to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                     const scoped_index& xbase_space_id,
                                     const scoped_index& xfiber_schema_id);


  ///
  /// Create a new handle attached to the state in xhost specified by
  /// paths xbase_path and xfiber_schema_path.
  ///
  product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                     const poset_path& xbase_path,
                                     const poset_path& xfiber_schema_path);

  ///
  /// Creates a new product_section_space_schema_member handle
  /// attached to the member state specified by xpath in the namespace xns.
  ///
  product_section_space_schema_member(const namespace_poset& xns,
                                     const poset_path& xpath,
                                     bool xauto_access = true);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  // None - section_space_schema_member is immutable

protected:

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
  /// @name SECTION_SPACE_SCHEMA_MEMBER FACET
  // ===========================================================
  //@{

public:

protected:

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
//   virtual primitive_type dof_tuple_type(bool xis_table_dof) const;

//   ///
//   /// The number of bytes in this dof
//   ///
//   virtual size_t size() const;

//   ///
//   /// The alignment for this dof
//   ///
//   virtual size_t alignment() const;

//   ///
//   /// The primitive type index of the dof defined by this.
//   ///
//   virtual sheaf::primitive_type type() const;

//   ///
//   /// True if this is in the table dofs part (xin_table_dofs == true)
//   /// or in the row dofs part (xin_table_dofs == false) of some schema.
//   ///
//   virtual bool is_dof(bool xin_table_dofs) const;

  ///
  /// A postorder iterator over the table (xis_table_dofs == true)
  /// or row (xis_table_dofs == false) dofs defined by version
  /// version of this.
  ///
  virtual poset_dof_iterator* dof_iterator(bool xis_table_dofs,
					   int xversion = CURRENT_MEMBER_VERSION) const;

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
  virtual dof_descriptor_array* dof_descriptors(bool xis_table_dof) const;

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
 
  using schema_poset_member::size;
  
  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type size(pod_index_type xdof_id,
			 bool xis_table_dof) const;
 
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
			 bool xis_table_dof) const;

  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type size(const scoped_index& xdisc_id,
			 const scoped_index& xfiber_dof_id,
			 bool xis_table_dof,
			 bool xauto_access) const;

  using schema_poset_member::alignment;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type alignment(pod_index_type xdof_id,
			      bool xis_table_dof) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type alignment(pod_index_type xdisc_id,
			      pod_index_type xfiber_dof_id,
			      bool xis_table_dof) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type alignment(const scoped_index& xdisc_id,
			      const scoped_index& xfiber_dof_id,
			      bool xis_table_dof,
			      bool xauto_access) const;

  using schema_poset_member::type;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual primitive_type type(pod_index_type xdof_id,
			      bool xis_table_dof) const;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual primitive_type type(pod_index_type xdisc_id,
			      pod_index_type xfiber_dof_id,
			      bool xis_table_dof) const;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual primitive_type type(const scoped_index& xdisc_id,
			      const scoped_index& xfiber_dof_id,
			      bool xis_table_dof, 
			      bool xauto_access) const;

  using schema_poset_member::offset;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type offset(pod_index_type xdof_id,
			   bool xis_table_dof) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type offset(pod_index_type xdisc_id,
			   pod_index_type xfiber_dof_id,
			   bool xis_table_dof) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdisc_id, xfiber_dof_id in the schema defined by this.
  ///
  virtual size_type offset(const scoped_index& xdisc_id,
			   const scoped_index& xfiber_dof_id,
			   bool xis_table_dof, 
			   bool xauto_access) const;

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
  ///
  virtual index_iterator* get_decomposition(pod_index_type xindex) const;

  /// @todo Remove.
  /// @todo Review.

//   ///
//   /// Gets the internal id corresponding to xext_id in the id space
//   /// with name xid_space_name.
//   /// @hack the product subposet hack, version 2.
//   /// This member exists only to encapsulate the hack.
//   ///
//   virtual pod_index_type get_int_id(pod_index_type xext_id,
// 				    const std::string& xid_space_name) const;

  ///
  /// Gets the external ids of this in
  /// the id space with namexid_space_name
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  virtual void get_ext_ids(const std::string& xid_space_name,
                           pod_index_type& xschema_poset_ext_id,
                           pod_index_type& xschema_member_ext_id,
                           pod_index_type& xbase_space_ext_id,
                           pod_index_type& xfiber_schema_ext_id,
                           pod_index_type& xlocal_schema_ext_id) const;


  ///
  /// The schema for the external data type associated with this schema.
  ///
  virtual schema_poset_member& ext_data_type_schema();

  ///
  /// The number of instances of the external data type needed to
  /// represent this schema.
  ///
  virtual size_t ext_data_type_ct(bool xis_table_schema) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member (mutable version)
  ///
  virtual primitives_poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member (const version)
  ///
  virtual const primitives_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline product_section_space_schema_member* greatest_jem() const
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline product_section_space_schema_member* least_jem() const
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::least_jem());
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline product_section_space_schema_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline product_section_space_schema_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::p_meet(other));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  inline product_section_space_schema_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline product_section_space_schema_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline product_section_space_schema_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<product_section_space_schema_member*>(abstract_poset_member::l_not(xnew_jem));
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
  inline product_section_space_schema_poset* host() const
  {
    return reinterpret_cast<product_section_space_schema_poset*>(section_space_schema_member::host());
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
  virtual product_section_space_schema_member* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

} // namespace fiber_bundle

#endif // PRODUCT_SECTION_SPACE_SCHEMA_MEMBER_H
