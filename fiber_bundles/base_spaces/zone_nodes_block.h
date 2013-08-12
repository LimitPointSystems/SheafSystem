

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class zone_nodes_block

#ifndef ZONE_NODES_BLOCK_H
#define ZONE_NODES_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_H
#include "homogeneous_block.h"
#endif

#ifndef ZONE_NODES_BLOCK_CRG_INTERVAL_H
#include "zone_nodes_block_crg_interval.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

class base_space_member_prototype;
class block_connectivity;

///
/// A homogeneous collection of zones with nodal connectivity.
///
class SHEAF_DLL_SPEC zone_nodes_block : public homogeneous_block
{

  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The path of the schema required by this.
  ///
  virtual const poset_path& schema_path() const;

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// The path of the prototype required by this class.
  ///
  static const poset_path& static_prototype_path();

  ///
  /// Manual, shallow factory method; creates a new host poset for members of this type.
  /// The poset is created in namespace xns with path xpath and schema specified by xschema_path.
  ///
  static void new_host(namespace_type& xns, 
                       const poset_path& xpath, 
                       const poset_path& xschema_path, 
		       int xmax_db,
                       bool xauto_access);

  ///
  /// Auto, deep factory method; creates a new host poset and any prerequisite posets
  /// for members of this type. The poset is created in namespace xns with path xpath
  /// and schema specified by standard_schema_path().
  ///
  static void new_host(namespace_type& xns,
		       const poset_path& xpath,
		       int xmax_db,
		       bool xauto_access);
  

protected:

private:

  //@}


  // ===========================================================
  /// @name ZONE_NODES_BLOCK FACET
  // ===========================================================
  //@{

public:

  ///
  /// The dimension of this block; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DB = -1};  

  ///
  /// Default constructor; creates a new, unattached handle.
  ///
  zone_nodes_block();

  ///
  /// Copy constructor; creates a new handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit zone_nodes_block(const abstract_poset_member& xother,
                            bool xnew_jem = false);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~zone_nodes_block();

  // ===========================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  // ===========================================================

  ///
  /// Creates a new handle attached to a new member state in xhost,
  /// with connectivity given by xconn.
  ///
  zone_nodes_block(base_space_poset& xhost, const block_connectivity& xconn, bool xauto_access);


  // ===========================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  // ===========================================================

  ///
  /// Creates a new zone_nodes_block handle attached to the member state
  /// with hub id xhub_id in xhost.
  ///
  zone_nodes_block(const base_space_poset& xhost, pod_index_type xhub_id);

  ///
  /// Creates a new zone_nodes_block handle attached to the member state
  /// with id xid in xhost
  ///
  zone_nodes_block(const base_space_poset& xhost, const scoped_index& xid);

  ///
  /// Creates a new zone_nodes_block handle attached to the member state
  /// with name xname in xhost
  ///
  zone_nodes_block(const base_space_poset& xhost, const string& xname);

  ///
  /// Creates a new zone_nodes_block handle attached to the member state
  /// specifiec by path xpath in namespace xnamespace.
  ///
  zone_nodes_block(const namespace_poset* xnamespace,
                   const poset_path& xpath,
                   bool xauto_access = true);

  ///
  /// Creates a new zone_nodes_block handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  zone_nodes_block(const namespace_poset* xnamespace,
                   pod_index_type xposet_id,
                   pod_index_type xmember_id);

  ///
  /// Creates a new zone_nodes_block handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  zone_nodes_block(const namespace_poset* xnamespace,
                   const scoped_index& xposet_id,
                   const scoped_index& xmember_id);

  // ===========================================================
  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"
  // ===========================================================

  ///
  /// Creates a new unstructured block state in host() and attaches this to it.
  ///
  void new_state(const block_connectivity& xconn, bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  void new_state(base_space_poset& xhost, const block_connectivity& xconn, bool xauto_access);

protected:

private:

  //@}


  // ===========================================================
  /// @name VERTEX CLIENT ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if this block contains a vertex client id space.
  ///
  bool contains_vertex_client_id_space(bool xauto_access) const;

  ///
  /// Allocates a vertex client id space handle from the pool of handles.
  ///
  index_space_handle& get_vertex_client_id_space(bool xauto_access) const;

  ///
  /// Returns the vertex client id space handle xid_space to the pool of handles.
  ///
  void release_vertex_client_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates a vertex client id space iterator from the pool of iterators.
  ///
  index_space_iterator& get_vertex_client_id_space_iterator(bool xauto_access) const;

  ///
  /// Returns the vertex client id space iterator xitr to the pool of iterators.
  ///
  void release_vertex_client_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK FACET
  // ===========================================================
  //@{

public:

  ///
  /// The implicit interval member for this block.
  ///
  virtual const zone_nodes_block_crg_interval& interval() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

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
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual zone_nodes_block& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  zone_nodes_block& operator=(const zone_nodes_block& xother);

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
  inline zone_nodes_block* greatest_jem() const
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline zone_nodes_block* least_jem() const
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::least_jem());
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
  inline zone_nodes_block* p_join(abstract_poset_member* other) const
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline zone_nodes_block* p_meet(abstract_poset_member* other)
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::p_meet(other));
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
  inline zone_nodes_block* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline zone_nodes_block* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline zone_nodes_block* l_not(bool xnew_jem = true) const
  {
    return static_cast<zone_nodes_block*>(homogeneous_block::l_not(xnew_jem));
  };

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
  virtual zone_nodes_block* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  zone_nodes_block* clone(bool xnew_state, bool xauto_access = true) const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};
 
} // namespace fiber_bundle

#endif // ZONE_NODES_BLOCK_H
