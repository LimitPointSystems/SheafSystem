

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class base_space_member_prototype.

#ifndef BASE_SPACE_MEMBER_PROTOTYPE_H
#define BASE_SPACE_MEMBER_PROTOTYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP_H
#include "array_poset_dof_map.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

namespace sheaf
{
class tern;
class poset;
}


namespace fiber_bundle
{

using namespace sheaf;

class base_space_poset;

///
/// A client handle for a base space member prototype.
///
class SHEAF_DLL_SPEC base_space_member_prototype : public total_poset_member
{
  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of host poset for this type of member.
  ///
  typedef base_space_poset host_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The name of the standard schema member for this class.
  ///
  static const string& standard_schema_member_name();

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The path of the schema required by this.
  ///
  virtual const poset_path& schema_path() const;

  ///
  /// The name of the prototypes poset.
  ///
  static const string& prototypes_poset_name();

  ///
  /// Manual, shallow factory method; creates a new host poset for members of this type.
  /// The poset is created in namespace xns with path xhost_path and schema specified by xschema_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path, 
			     int xmax_db,
			     bool xauto_access);

  ///
  /// Auto, deep factory method; creates a new host poset and any prerequisite posets
  /// for members of this type. The poset is created in namespace xns with path xhost_path
  /// and schema specified by standard_schema_path().
  ///
  static host_type& new_host(namespace_type& xns,
			     const poset_path& xhost_path,
			     int xmax_db,
			     bool xauto_access);
  

protected:

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_MEMBER_PROTOTYPE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached base_space_member_prototype handle.
  ///
  base_space_member_prototype();

  ///
  /// Copy constructor; creates a new base_space_member_prototype handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit base_space_member_prototype(const abstract_poset_member& xother,
                                       bool xnew_jem = false);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~base_space_member_prototype();

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a prototype with name xname, dimension xdb, and
  /// local cell prototype xlocal_cell_name.
  ///
  base_space_member_prototype(poset* xhost,
                              const string& xname,
                              int xdb,
                              const string& xlocal_cell_name,
                              bool xauto_access);

  ///
  /// Creates a new handle attached to a new jim (join-irreducible member)
  /// state in xhost using the existing dof tuple with index xdof_tuple_id.
  ///
  base_space_member_prototype(poset* xhost,
                              const scoped_index& xdof_tuple_id,
                              bool xauto_access);

  ///
  /// Creates a new handle attached to a new jim (join-irreducible member)
  /// state in xhost using the existing dof tuple with index xdof_tuple_id.
  ///
  base_space_member_prototype(poset* xhost,
                              pod_index_type xdof_tuple_id,
                              bool xauto_access);

  ///
  /// creates a new jrm (join reducible member) attached to a new member state
  /// in xhost The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  base_space_member_prototype(poset* xhost,
                              scoped_index* xexpansion,
                              int xexpansion_ct,
                              const tern& xnew_jem,
                              bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  /// @issue Why is xhost below of type poset* rather than the more general
  /// poset_state_handle* or the moe specific base_space_poset*?

  ///
  /// Creates a new base_space_member_prototype handle attached to the member state
  /// with hub id xhub_id in xhost
  ///
  base_space_member_prototype(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new base_space_member_prototype handle attached to the member state
  /// with id xid in xhost
  ///
  base_space_member_prototype(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new base_space_member_prototype handle attached to the member state
  /// with name xname in xhost
  ///
  base_space_member_prototype(const poset* xhost, const string& xname);

  ///
  /// Creates a new base_space_member_prototype handle attached to the member state
  /// with specified by xpath in namespace xnamespace.
  ///
  base_space_member_prototype(const namespace_poset* xnamespace,
                              const poset_path& xpath,
                              bool xauto_access);

  ///
  /// Creates a new base_space_member_prototype handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  base_space_member_prototype(const namespace_poset* xnamespace,
                              pod_index_type xposet_id,
                              pod_index_type xmember_id,
                              bool xauto_access);

  ///
  /// Creates a new base_space_member_prototype handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  base_space_member_prototype(const namespace_poset* xnamespace,
                              const scoped_index& xposet_id,
                              const scoped_index& xmember_id,
                              bool xauto_access);

  // FEATURES

  /// The dimension of this block; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DB = -1};

protected:

  ///
  /// Creates a new row dof map and initializes it.
  ///
  void init_row_dof_tuple(int xdb, const string& xlocal_cell_name);

private:

  //@}


  // ===========================================================
  /// @name ROW DOFS
  // ===========================================================
  //@{

public:

  ///
  /// The base space dimension.
  ///
  int db() const;

  ///
  /// The cell type id of this.
  /// The id of the prototype of this in the
  /// "cell_types" id space of the prototypes poset.
  ///
  const pod_index_type& type_id() const;

  ///
  /// The cell type name.
  ///
  const char* type_name() const;

  ///
  /// The refinement depth.
  ///
  int refinement_depth() const;

  ///
  /// The local cell type id.
  ///
  pod_index_type local_cell_type_id() const;

  ///
  /// The local cell type name.
  ///
  const char* local_cell_type_name() const;

  ///
  /// The type of row dof tuple for this.
  ///
  struct SHEAF_DLL_SPEC row_dof_tuple_type
  {
    ///
    /// The base space dimension.
    ///
    int db;

    ///
    /// The cell type id.
    ///
    int type_id;

    ///
    /// The cell type name.
    ///
    const char* type_name;

    ///
    /// The refinement depth.
    ///
    int refinement_depth;

    ///
    /// The local cell type id.
    ///
    int local_cell_type_id;

    ///
    /// The local cell type name.
    ///
    const char* local_cell_type_name;

    ///
    /// The number of local cells.
    ///
    size_type size;

    ///
    /// The upper bound on the x direction index for structured blocks
    ///
    size_type i_size;

    ///
    /// The upper bound on the y direction index for structured blocks
    ///
    size_type j_size;

    ///
    /// The upper bound on the z direction index for structured blocks
    ///
    size_type k_size;
  };

  ///
  /// The row dof tuple for this.
  ///
  row_dof_tuple_type* row_dof_tuple(bool xrequire_write_access = false);

protected:

private:

  //@}


  // ===========================================================
  /// @name TOTAL_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ABSTRACT_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline base_space_member_prototype* clone(bool xnew_state, bool xauto_access = true) const
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

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
  inline base_space_member_prototype* greatest_jem() const
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline base_space_member_prototype* least_jem() const
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::least_jem());
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
  inline base_space_member_prototype* p_join(abstract_poset_member* other) const
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline base_space_member_prototype* p_meet(abstract_poset_member* other)
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::p_meet(other));
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
  /// the lattice join is the least upper bound in the lattice generated by the
  /// jims in the poset
  ///
  inline base_space_member_prototype* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline base_space_member_prototype* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline base_space_member_prototype* l_not(bool xnew_jem = true) const
  {
    return reinterpret_cast<base_space_member_prototype*>(total_poset_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

  /// @todo implement the following. Requires support in the io subsystem.

  //   ///
  //   /// The namespace of host()
  //   ///
  //   virtual fiber_bundles_namespace* name_space();

  //   ///
  //   /// True if other conforms to name_space().
  //   ///
  //   virtual bool namespace_is_ancestor_of(namespace_poset* other);

  //   ///
  //   /// The poset which this is a handle to a member of.
  //   ///
  //   virtual base_space_poset* host();

  ///
  /// The poset which this is a handle to a member of.
  ///
  poset* host() const;

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

public:

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual base_space_member_prototype* clone() const;

  ///
  /// Assignment operator; attaches this to the same state as xother.
  ///
  virtual base_space_member_prototype& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother.
  ///
  base_space_member_prototype& operator=(const base_space_member_prototype& xother);

protected:

private:

  //@}
};

} // namespace fiber_bundle

#endif // BASE_SPACE_MEMBER_PROTOTYPE_H
