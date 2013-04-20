

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class TERNARY_SECTION_SPACE_SCHEMA_MEMBER

#ifndef TERNARY_SECTION_SPACE_SCHEMA_MEMBER_H
#define TERNARY_SECTION_SPACE_SCHEMA_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CLIENT_INDEX_H
#include "client_index.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#include "section_space_schema_member.h"
#endif

// #ifndef TERNARY_SECTION_SPACE_SCHEMA_POSET_H
// #include "ternary_section_space_schema_poset.h"
// #endif

namespace fiber_bundle
{

class sec_rep_descriptor;
  class ternary_section_space_schema_poset;
  
///
/// A client handle for a poset member which has been
/// prepared for use as a schema for a section space.
///
class SHEAF_DLL_SPEC ternary_section_space_schema_member : public section_space_schema_member
{
  friend class section_space_schema_poset; // For access to get_ext_ids.

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();
  

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates a new, unattached ternary_section_space_schema_member handle.
  ///
  ternary_section_space_schema_member();

  ///
  /// Copy constructor; creates a new ternary_section_space_schema_member handle
  /// attached to the same state as xother.
  ///
  explicit ternary_section_space_schema_member(const ternary_section_space_schema_member& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  ternary_section_space_schema_member& operator=(const abstract_poset_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~ternary_section_space_schema_member();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// True if other conforms to host
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual ternary_section_space_schema_member* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline ternary_section_space_schema_member* clone(bool xnew_state,
      bool xauto_access = true) const
  {
    return static_cast<ternary_section_space_schema_member*>
           (section_space_schema_member::clone(xnew_state, xauto_access));
  }

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

  // HOST POSET INTERFACE

  ///
  /// The poset which this is a handle to a component of.
  ///

  inline ternary_section_space_schema_poset* host() const
  {
    return static_cast<ternary_section_space_schema_poset*>(section_space_schema_member::host());
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  // None - section_space_schema_poset is immutable.

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new ternary_section_space_schema_member handle attached to the member state
  /// with index xindex in xhost
  ///
  ternary_section_space_schema_member(ternary_section_space_schema_poset* xhost,
                                      const scoped_index& xindex);


  ///
  /// Creates a new ternary_section_space_schema_member handle attached to the member state
  /// with name xname in xhost
  ///
  ternary_section_space_schema_member(ternary_section_space_schema_poset* xhost,
                                      const string& xname);

  ///
  /// Creates a new ternary_section_space_schema_member handle attached to
  /// the member state with path xpath in the namespace xnamespace.
  ///
  ternary_section_space_schema_member(namespace_poset* xnamespace,
                                      const poset_path& xpath,
                                      bool xauto_access = true);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  // None - section_space_schema_member is immutable


  // ===========================================================
  // COMPONENT NAME FACET
  // ===========================================================

  ///
  /// Get name for this poset member
  ///
  virtual string name() const;

  // ===========================================================
  // STATE FACET
  // ===========================================================

  using section_space_schema_member::attach_to_state;

  ///
  /// Attach to the state in host() with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  virtual void attach_to_state(const scoped_index& xbase_space_id,
                               const scoped_index& xfiber_schema_id);

  ///
  /// Attach to the state in xhost with
  /// component ids xbase_id and xfiber_schema_id.
  ///
  virtual void attach_to_state(section_space_schema_poset* xhost,
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
  /// Attach to the state in the current host with component
  /// ids xbase_space_id, xfiber_schema_id, and xlocal_schema_id.
  ///
  void attach_to_state(ternary_section_space_schema_poset* xhost,
                       const scoped_index& xbase_space_id,
                       const scoped_index& xfiber_schema_id,
                       const scoped_index& xlocal_schema_id);


  ///
  /// Detach this handle from its state, if any.
  ///
  virtual void detach_from_state();



  // ===========================================================
  // MEMBER ATTRIBUTE FACET
  // ===========================================================

  ///
  /// True if this member is join irreducible
  ///
  virtual bool is_jim(bool xin_current_version = true) const;

  ///
  /// True if this member covers the bottom
  ///
  virtual bool is_atom() const;



  // ===========================================================
  // DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member
  ///
  virtual primitives_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  // ===========================================================
  // ORDERING RELATION FACET
  // ===========================================================

  

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline ternary_section_space_schema_member* greatest_jem() const
  {
    return static_cast<ternary_section_space_schema_member*>(abstract_poset_member::greatest_jem());
  };

  

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline ternary_section_space_schema_member* least_jem() const
  {
    return static_cast<ternary_section_space_schema_member*>(abstract_poset_member::least_jem());
  };



  // ===========================================================
  // DOWN SET FACET
  // ===========================================================

  ///
  /// The number of members in the down set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  int down_ct(const scoped_index& xfilter_index = WHOLE_INDEX) const;

  ///
  /// The down set of this member, auto- and pre-allocated versions
  ///
  subposet* down();

  ///
  /// The down set of this member, auto- and pre-allocated versions
  ///
  void down_pa(subposet* result);

  ///
  /// The number of members in the up set of this member,
  /// filtered by the subposet in host() with index xfilter_index.
  ///
  int up_ct(const scoped_index& xfilter_index = WHOLE_INDEX) const;

  ///
  /// The up set of this member, auto- and pre-allocated versions
  ///
  subposet* up() const;

  ///
  /// The up set of this member, auto- and pre-allocated versions
  ///
  void up_pa(subposet* result);

  ///
  /// The number of members in the set of jims contained in the down set of
  /// this member.
  ///
  int jim_ct() const;

  ///
  /// The set of jims contained in the down set of this member, auto-allocated
  ///
  subposet* jims();

  ///
  /// The set of jims contained in the down set of this member, pre-allocated
  ///
  void jims_pa(subposet* result);

  ///
  /// The number of maximal members in the set of jims contained in the down
  /// set of this member.
  ///
  int maximal_jim_ct();

  ///
  /// The maximal members of the set of jims contained in this member,
  /// auto-allocated
  ///
  subposet* maximal_jims();

  ///
  /// The maximal members of the set of jims contained in this member,
  /// pre-allocated
  ///
  void maximal_jims_pa(subposet* result);




  // ===========================================================
  // POSET ALGEBRA FACET
  // ===========================================================

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline ternary_section_space_schema_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<ternary_section_space_schema_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// Poset join of this with other, pre-allocated.
  /// The poset join is the least upper bound in the poset.
  ///
  virtual void p_join_pa(abstract_poset_member* other, abstract_poset_member* result) const;

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline ternary_section_space_schema_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<ternary_section_space_schema_member*>(abstract_poset_member::p_meet(other));
  };

  ///
  /// Poset meet of this with other, pre-allocated version.
  /// The poset meet is the greatest lower bound in the poset.
  ///
  virtual void p_meet_pa(abstract_poset_member* other, abstract_poset_member* result);


  // ===========================================================
  // LATTICE ALGEBRA FACET
  // ===========================================================

  /// @error host is immutable; does not support lattice algebra; remove this facet

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  inline ternary_section_space_schema_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    not_implemented();
    return this;
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline ternary_section_space_schema_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    not_implemented();
    return this;
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline ternary_section_space_schema_member* l_not(bool xnew_jem = true) const
  {
    not_implemented();
    return this;
  };


  // ===========================================================
  // SCHEMA POSET MEMBER FACET
  // ===========================================================

  ///
  /// The type of table dofs (xis_table_dof == true) or
  /// row dofs (xis_table_dof == false) defined by this schema.
  /// Returns NOT_A_PRIMITIVE_TYPE if the dofs are
  /// not all the same type.
  ///
  virtual primitive_type dof_tuple_type(bool xis_table_dof);

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
  /// The client id map for the table dofs of this schema.
  /// Not implemented for xis_table_dof false.
  ///
  ///
  virtual id_space_map& dof_client_id_map(bool xis_table_dof) const;

  ///
  /// True if this is in the table dofs part (xin_table_dofs == true)
  /// or in the row dofs part (xin_table_dofs == false) of some schema.
  ///
  virtual bool is_dof(bool xin_table_dofs) const;

  ///
  /// The number of bytes in this dof
  ///
  virtual size_t size() const;

  ///
  /// The alignment for this dof
  ///
  virtual size_t alignment() const;

  ///
  /// The primitive type index of the dof defined by this.
  ///
  virtual sheaf::primitive_type type() const;

  ///
  /// The client id of this in the client id map of xother_schema.
  ///
  virtual client_index client_id(schema_poset_member& xschema, bool xin_table_dofs) const;

  ///
  /// The maximum client id for the table dofs (xis_table_dofs == true) or
  /// row dofs (xis_table_dofs == false) defined by this.
  ///
  virtual client_index max_client_id(bool xis_table_dofs) const;

  /// @todo implement ternary_section_dof_iterator,
  /// then implement the following functions:

  //   ///
  ///   /// A postorder iterator over the table (xis_table_dofs == true)
  ///   /// or row (xis_table_dofs == false) dofs defined by this.
  //   ///
  //   virtual ternary_section_dof_iterator* dof_iterator(bool xis_table_dofs);

  //   ///
  ///   /// A postorder iterator over the table dofs defined by this.
  ///   /// Synonym for dof_iterator(true).
  //   ///
  //   inline ternary_section_dof_itr* table_dof_iterator()
  //   {
  //     return dof_iterator(true);
  //   };

  //   ///
  ///   /// A postorder iterator over the row dofs defined by this.
  //   ///
  //   inline ternary_section_dof_itr* row_dof_iterator()
  //   {
  //     return dof_iterator(false);
  //   };

  // ===========================================================
  // SECTION_SPACE_SCHEMA_POSET_MEMBER FACET
  // ===========================================================

  ///
  /// The member id of the local schema component of this.
  ///
  inline scoped_index local_schema_id()
  {
    return _local_schema_id;
  };

  ///
  /// The local schema component of this.
  ///
  inline schema_poset_member& local_schema()
  {
    return _local_schema;
  };

  // ===========================================================
  // I/O SUPPORT FACET
  // ===========================================================

  ///
  /// An iterator over the members of the decomposition identified by xindex.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual index_iterator* get_decomposition(const scoped_index& xindex);

  ///
  /// Gets the internal id corresponding to xext_id in the id space
  /// with name xid_space_name.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual scoped_index get_int_id(pod_index_type xext_id,
				  const string& xid_space_name) const;


  ///
  /// Gets the external ids of this in
  /// the id space with namexid_space_name
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
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

  ///
  /// Initializes the handle data members when
  /// this handle is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// The member id of the local schema component of this.
  ///
  scoped_index _local_schema_id;

  ///
  /// The local schema component of this.
  ///
  schema_poset_member _local_schema;

  ///
  /// Updates cached row properties.
  ///
  virtual void update_row_cache();

};

} // namespace fiber_bundle

#endif // TERNARY_SECTION_SPACE_SCHEMA_MEMBER_H
