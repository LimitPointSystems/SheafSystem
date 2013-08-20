

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class binary_section_space_schema_member.

#ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
#define BINARY_SECTION_SPACE_SCHEMA_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#include "section_space_schema_member.h"
#endif

#ifndef BINARY_SECTION_COMPONENT_ITERATOR_H
#include "binary_section_component_iterator.h"
#endif

#ifndef BINARY_SECTION_DOF_ITERATOR_H
#include "binary_section_dof_iterator.h"
#endif

// #ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
// #include "binary_section_space_schema_poset.h"
// #endif

// #ifndef CLIENT_INDEX_H
// #include "client_index.h"
// #endif

namespace fiber_bundle
{

  class binary_section_space_schema_poset;
  class sec_rep_descriptor;

///
/// A client handle for a poset member which has been
/// prepared for use as a schema for a section space.
/// See class binary_section_space_schema_poset for a
/// description of the schema represented by this class.
///
///
///
class SHEAF_DLL_SPEC binary_section_space_schema_member : public section_space_schema_member
{

  // ===========================================================
  /// @name HOAT FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef binary_section_space_schema_poset host_type;
  
  ///
  /// Creates a new host for members of this type in namespace xns with path xhost_path,
  /// schema specified by xschema_path, and table attributes base_space_path, fiber_space_path,
  /// and rep_path specified by xbase_path, xfiber_path, and xrep_path, respectively.
  ///
  static host_type& new_host(namespace_type& xns, 
                              const poset_path& xhost_path, 
                              const poset_path& xschema_path,
                              const poset_path& xbase_path,
                              const poset_path& xfiber_path,
                              const poset_path& xrep_path,
                              bool xauto_access);
 
//   ///
//   /// The standard path for the host of a schema with base space,
//   /// fiber space, and representation specified by xbase_path, xfiber_path,
//   /// and xrep_path, respectively.
//   ///
//   static poset_path standard_host_path(const poset_path& xbase_path, 
//                                        const poset_path& xfiber_path, 
//                                        const poset_path& xrep_path);
 
//   ///
//   /// The standard path for a schema member with base space,
//   /// fiber space, and representation specified by xbase_path, xfiber_path,
//   /// and xrep_path, respectively.
//   ///
//   static poset_path standard_path(const poset_path& xbase_path, 
//                                   const poset_path& xfiber_path, 
//                                   const poset_path& xrep_path);
  
//   ///
//   /// The host with path standard_host_path(xbase_path, xfiber_path, xrep_path).
//   /// Returns the host if it already exists, otherwise, creates it in namespace xns
//   /// with path specified by standard_host_path and schema specified by standard_schema_path. 
//   ///
//   static host_type& standard_host(namespace_type& xns, 
//                                   const poset_path& xbase_path,
//                                   const poset_path& xfiber_path,
//                                   const poset_path& xrep_path,
//                                   bool xauto_access);

  
//   ///
//   /// The path for standard schema member with base space, fiber space, and representation 
//   /// specified by xbase_path, xfiber_path, and xrep_path, respectively.
//   /// Creates the standard host and member if they do not already exist.
//   ///
//   static poset_path standard_schema(namespace_type& xns, 
//                                     const poset_path& xbase_path,
//                                     const poset_path& xfiber_path,
//                                     const poset_path& xrep_path,
//                                     bool xauto_access);
 
  ///
  /// The standard path for the host of a schema for sections of type S with
  /// base space specified by xbase_path, fiber suffix xfiber_suffix, and 
  /// representation specified by xrep_path.
  ///
  template <typename S>
  static poset_path standard_host_path(const poset_path& xbase_path, 
                                       const poset_path& xrep_path, 
                                       const string& xfiber_suffix);
 
  ///
  /// The standard path for a schema member for sections of type S with
  /// base space sepcified by xbase_path, fiber suffix xfiber_suffix, and 
  /// representation specified by xrep_path.
  ///
  template <typename S>
  static poset_path standard_member_path(const poset_path& xbase_path, 
                                         const poset_path& xrep_path, 
                                         const string& xfiber_suffix);

  ///
  /// True if and only if the host specified by standard_host_path<S>(xbase_path, xrep_path, xfiber_suffix)
  /// does not exist, or it exists and conforms to host_type.
  ///
  template <typename S>
  static poset_path standard_host_is_available(namespace_poset& xns,
                                               const poset_path& xbase_path, 
                                               const poset_path& xrep_path, 
                                               const string& xfiber_suffix,
                                               bool xauto_access);
  
  ///
  /// The standard host of a schema for sections of type S with
  /// base space sepcified by xbase_path, fiber suffix xfiber_suffix, and 
  /// representation specified by xrep_path.
  ///
  template <typename S>
  static host_type& standard_host(namespace_type& xns, 
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

  
  ///
  /// The path for standard schema member for sections of type S with
  /// base space sepcified by xbase_path, fiber suffix xfiber_suffix, and 
  /// representation specified by xrep_path.Creates the standard host and 
  /// member if they do not already exist.
  ///
  template <typename S>
  static poset_path standard_schema(namespace_type& xns, 
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name BINARY_SECTION_SPACE_SCHEMA_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached binary_section_space_schema_member handle.
  ///
  binary_section_space_schema_member();

  ///
  /// Copy constructor; creates a new binary_section_space_schema_member handle
  /// attached to the same state as xother.
  ///
  explicit binary_section_space_schema_member(const binary_section_space_schema_member& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual binary_section_space_schema_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  binary_section_space_schema_member& operator=(const binary_section_space_schema_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~binary_section_space_schema_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline binary_section_space_schema_member* clone(bool xnew_state,
      bool xauto_access = true) const
  {
    return static_cast<binary_section_space_schema_member*>
           (section_space_schema_member::clone(xnew_state, xauto_access));
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  // None - section_space_schema_poset is immutable.

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new binary_section_space_schema_member handle
  /// attached to the member state with hub id xhub_id in xhost
  ///
  binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                     pod_index_type xhub_id);

  ///
  /// Creates a new binary_section_space_schema_member handle
  /// attached to the member state with id xid in xhost
  ///
  binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                     const scoped_index& xid);

  ///
  /// Creates a new binary_section_space_schema_member handle
  /// attached to the member state with name xname in xhost
  ///
  binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                     const string& xname);

  ///
  /// Create a new handle attached to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                     pod_index_type xbase_space_id,
                                     pod_index_type xfiber_schema_id);


  ///
  /// Create a new handle attached to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                     const scoped_index& xbase_space_id,
                                     const scoped_index& xfiber_schema_id);


  ///
  /// Create a new handle attached to the state in xhost specified by
  /// paths xbase_path and xfiber_schema_path.
  ///
  binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                     const poset_path& xbase_path,
                                     const poset_path& xfiber_schema_path);

  ///
  /// Creates a new binary_section_space_schema_member handle
  /// attached to the member state specified by xpath in the namespace xns.
  ///
  binary_section_space_schema_member(const namespace_poset& xns,
                                     const poset_path& xpath,
                                     bool xauto_access = true);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  // None - section_space_schema_member is immutable

protected:

private:

  //@}


  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// A postorder iterator over the components defined by this.
  ///
  virtual binary_section_component_iterator* component_iterator() const;

protected:

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
  virtual primitive_type dof_tuple_type(bool xis_table_dof) const;

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
  /// True if this is in the table dofs part (xin_table_dofs == true)
  /// or in the row dofs part (xin_table_dofs == false) of some schema.
  ///
  virtual bool is_dof(bool xin_table_dofs) const;

  using section_space_schema_member::size;
  
  ///
  /// The number of bytes in this dof
  ///
  virtual size_t size() const;

  using section_space_schema_member::alignment;
  
  ///
  /// The alignment for this dof
  ///
  virtual size_t alignment() const;

  using section_space_schema_member::type;
  
  ///
  /// The primitive type index of the dof defined by this.
  ///
  virtual sheaf::primitive_type type() const;

  ///
  /// A postorder iterator over the table (xis_table_dofs == true)
  /// or row (xis_table_dofs == false) dofs defined by this.
  ///
  virtual binary_section_dof_iterator* dof_iterator(bool xis_table_dofs,
						    int xversion = CURRENT_MEMBER_VERSION) const;

  ///
  /// A postorder iterator over the table dofs defined by this.
  /// Synonym for dof_iterator(true).
  ///
  inline binary_section_dof_iterator* table_dof_iterator(int xversion = CURRENT_MEMBER_VERSION) const
  {
    return dof_iterator(true, xversion);
  };

  ///
  /// A postorder iterator over the row dofs defined by this.
  ///
  inline binary_section_dof_iterator* row_dof_iterator(int xversion = CURRENT_MEMBER_VERSION) const
  {
    return dof_iterator(false, xversion);
  };

protected:

  ///
  /// Updates cached row properties.
  ///
  virtual void update_row_cache(bool xupdate_id_map = false) const;

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

  ///
  /// Gets the internal id corresponding to xext_id in the id space
  /// with name xid_space_name.
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  virtual pod_index_type get_int_id(pod_index_type xext_id,
				    const string& xid_space_name) const;

  ///
  /// Gets the external ids of this in
  /// the id space with namexid_space_name
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  virtual void get_ext_ids(const string& xid_space_name,
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
  inline binary_section_space_schema_member* greatest_jem() const
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline binary_section_space_schema_member* least_jem() const
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::least_jem());
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
  inline binary_section_space_schema_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline binary_section_space_schema_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::p_meet(other));
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
  inline binary_section_space_schema_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline binary_section_space_schema_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline binary_section_space_schema_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<binary_section_space_schema_member*>(abstract_poset_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  using section_space_schema_member::attach_to_state;

  ///
  /// Attach to the state in host() with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  virtual void attach_to_state(pod_index_type xbase_space_id,
                               pod_index_type xfiber_schema_id);

  ///
  /// Attach to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  virtual void attach_to_state(const section_space_schema_poset* xhost,
                               pod_index_type xbase_space_id,
                               pod_index_type xfiber_schema_id);


  ///
  /// Attach to the state in xhost specified by
  /// paths xbase_path and xfiber_schema_path.
  ///
  virtual void attach_to_state(const section_space_schema_poset* xhost,
                               const poset_path& xbase_path,
                               const poset_path& xfiber_schema_path);

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
  inline binary_section_space_schema_poset* host() const
  {
    return reinterpret_cast<binary_section_space_schema_poset*>(section_space_schema_member::host());
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
  virtual binary_section_space_schema_member* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

} // namespace fiber_bundle

#endif // BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
