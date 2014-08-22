
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
/// Interface for class homogeneous_block.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_HOMOGENEOUS_BLOCK_H
#define COM_LIMITPOINT_FIBER_BUNDLE_HOMOGENEOUS_BLOCK_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BASE_SPACE_MEMBER_H
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#endif

namespace sheaf
{
class index_space_handle;
class index_space_iterator;
class hub_index_space_handle;
  
}

namespace fiber_bundle
{

using namespace sheaf;

class homogeneous_block_crg_interval;
  
///
/// A client handle for a base space member which represents
/// a homgeneous collection of local cells, aka "zones" or "elements".
///
class SHEAF_DLL_SPEC homogeneous_block : public base_space_member
{
  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new host poset for members of this type.
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
  /// @name HOMOGENEOUS_BLOCK FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~homogeneous_block();

  ///
  /// The hub id space of this block.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// The id space for the members of this block, including the block itself.
  ///
  const index_space_handle& local_id_space() const;

  ///
  /// The type id of the prototype for the local cell;
  /// the id of the local cell prototype in the id space "cell_types"
  /// in the prototypes poset.
  ///
  const pod_index_type& local_cell_type_id() const;

  ///
  /// The type name of the prototype for the local cell.
  ///
  const char* local_cell_type_name() const;

  ///
  /// The number of local cell instances in this block.
  ///
  virtual const size_type& size() const;

  using base_space_member::new_row_dof_map;

  ///
  /// OBSOLETE: use scoped_index new_row_dof_map(poset_state_handle& ...)
  /// Creates a new row dof map and initializes it
  /// from the prototypes with names xprototype_name
  /// and xlocal_cell_name.
  ///
  array_poset_dof_map* new_row_dof_map(const poset* xhost,
                                       const std::string& xprototype_name,
                                       const std::string& xlocal_cell_name,
                                       size_type xsize);

  ///
  /// Creates a new row dof map and initializes it
  /// from the prototypes with names xprototype_name
  /// and xlocal_cell_name, and size xsize.
  ///
  static const scoped_index& new_row_dof_map(poset_state_handle& xhost,
					     const std::string& xprototype_name,
					     const std::string& xlocal_cell_name,
					     size_type xsize,
					     bool xauto_access);

protected:

  ///
  /// Default constructor; creates a new, unattached homogeneous_block handle.
  ///
  homogeneous_block();

  ///
  /// Initializes handle data members when attaching
  /// to a different member of the same host;
  /// intended to be redefined in derived classes.
  ///
  virtual void attach_handle_data_members();

  ///
  /// The implicit interval member for this block.
  ///
  virtual const homogeneous_block_crg_interval& interval() const;

  ///
  /// Sets the number of local cell instances in this block.
  ///
  void put_size(const size_type& xsize);

//   ///
//   /// The type of row dof tuple for this.
//   ///
//   struct SHEAF_DLL_SPEC row_dof_tuple_type
//   {
//     ///
//     /// The base space dimension.
//     ///
//     int db;

//     ///
//     /// The cell type id.
//     ///
//     int type_id;

//     ///
//     /// The cell type name.
//     ///
//     const char* type_name;

//     ///
//     /// The refinement depth.
//     ///
//     int refinement_depth;

//     ///
//     /// The local cell type id.
//     ///
//     int local_cell_type_id;

//     ///
//     /// The local cell type name.
//     ///
//     const char * local_cell_type_name;

//     ///
//     /// The number of local cell instances in this block.
//     ///
//     size_type size;
//   };


//   ///
//   /// The row dof tuple for this.
//   ///
//   inline row_dof_tuple_type* row_dof_tuple()
//   {
//     return reinterpret_cast<row_dof_tuple_type*>(dof_map().dof_tuple());
//   }

  ///
  /// The implicit interval posetmember for this block.
  ///
  homogeneous_block_crg_interval* _interval;

private:

  //@}


  // ===========================================================
  /// @name ZONE ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if this block contains a zone id space.
  ///
  bool contains_zone_id_space(bool xauto_access) const;

  ///
  /// Allocates a handle from the pool of handles for the id space of zones in this block.
  ///
  index_space_handle& get_zone_id_space(bool xauto_access) const;

  ///
  /// Returns the zone id space xid_space to the pool of handles.
  ///
  void release_zone_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates a zone id space iterator from the pool of iterators.
  ///
  index_space_iterator& get_zone_id_space_iterator(bool xauto_access) const;

  ///
  /// Returns the zone id space iterator xitr to the pool of iterators.
  ///
  void release_zone_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name VERTEX ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if this block contains a vertex id space.
  ///
  bool contains_vertex_id_space(bool xauto_access) const;

  ///
  /// Allocates a handle from the pool of handles for the id space of vertices in this block.
  ///
  index_space_handle& get_vertex_id_space(bool xauto_access) const;

  ///
  /// Returns the vertex id space handle xid_space to the pool of handles.
  ///
  void release_vertex_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates a vertex id space iterator from the pool of iterators.
  ///
  index_space_iterator& get_vertex_id_space_iterator(bool xauto_access) const;

  ///
  /// Returns the vertex id space iterator xitr to the pool of iterators.
  ///
  void release_vertex_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

private:

  //@}


  // ==========================================================
  /// @name CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this block contains the connectivity for a zone with id xzone_id.
  ///
  bool contains_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const;

  ///
  /// True if this block contains the connectivity for a zone with id xzone_id.
  /// synonym for contains_connectivity(xzone_id.hub_pod(), xauto_access).
  ///
  bool contains_connectivity_id_space(const scoped_index& xzone_id, bool xauto_access) const;

  ///
  /// Allocates an id space handle from the connectivity handle pool attached
  /// to the connectivity id space state for zone with id xzone_id.
  ///
  index_space_handle& get_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const;

  ///
  /// Allocates an id space handle from the connectivity handle pool attached
  /// to the connectivity id space state for zone with id xzone_id.
  /// synonym for get_connectivity_id_space(zone_id_space().pod(xzone_id)).
  ///
  index_space_handle& get_connectivity_id_space(const scoped_index& xzone_id, bool xauto_access) const;

  ///
  /// Returns the id space handle xid_space to the connectivity handle pool.
  ///
  void release_connectivity_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates an id space iterator from the connectivity iterator pool attached
  /// to the connectivity id space state for zone with id xzone_id.
  ///
  index_space_iterator& get_connectivity_id_space_iterator(pod_index_type xzone_id, bool xauto_access) const;

  ///
  /// Allocates an id space iterator from the connectivity iterator pool attached
  /// to the connectivity id space state for zone with id xzone_id.
  /// synonym for get_connecitivity_iterator(zone_id_space().pod(xzone_id)).
  ///
  index_space_iterator& get_connectivity_id_space_iterator(const scoped_index& xzone_id, bool xauto_access) const;

  ///
  /// Returns the id space iterator xid_space to the connectivity iterator pool.
  ///
  void release_connectivity_id_space_iterator(index_space_iterator& xid_space, bool xauto_access) const;

protected:

private:

  //@}


  // ==========================================================
  /// @name ADJACENCY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this block contains the adjacency for a vertex with id xvertex_id.
  ///
  bool contains_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const;

  ///
  /// True if this block contains the adjacency for a vertex with id xvertex_id.
  /// synonym for contains_adjacency(xvertex_id.hub_pod(), xauto_access).
  ///
  bool contains_adjacency_id_space(const scoped_index& xvertex_id, bool xauto_access) const;

  ///
  /// Allocates an id space handle from the adjacency handle pool attached
  /// to the adjacency id space state for vertex with id xvertex_id.
  ///
  index_space_handle& get_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const;

  ///
  /// Allocates an id space handle from the adjacency handle pool attached
  /// to the adjacency id space state for vertex with id xvertex_id.
  /// synonym for get_adjacency_id_space(vertex_id_space().pod(xvertex_id)).
  ///
  index_space_handle& get_adjacency_id_space(const scoped_index& xvertex_id, bool xauto_access) const;

  ///
  /// Returns the id space handle xid_space to the adjacency handle pool.
  ///
  void release_adjacency_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates an id space iterator from the adjacency iterator pool attached
  /// to the adjacency id space state for vertex with id xvertex_id.
  ///
  index_space_iterator& get_adjacency_id_space_iterator(pod_index_type xvertex_id, bool xauto_access) const;

  ///
  /// Allocates an id space iterator from the adjacency iterator pool attached
  /// to the adjacency id space state for vertex with id xvertex_id.
  /// synonym for get_connecitivity_iterator(vertex_id_space().pod(xvertex_id)).
  ///
  index_space_iterator& get_adjacency_id_space_iterator(const scoped_index& xvertex_id, bool xauto_access) const;

  ///
  /// Returns the id space iterator xid_space to the adjacency iterator pool.
  ///
  void release_adjacency_id_space_iterator(index_space_iterator& xid_space, bool xauto_access) const;

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
  /// Make a new handle, no state instance of current
  ///
  virtual homogeneous_block* clone() const = 0;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline homogeneous_block* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<homogeneous_block*>(base_space_member::clone(xnew_state, xauto_access));
  }

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
  inline homogeneous_block* greatest_jem() const
  {
    return static_cast<homogeneous_block*>(base_space_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline homogeneous_block* least_jem() const
  {
    return static_cast<homogeneous_block*>(base_space_member::least_jem());
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
  inline homogeneous_block* p_join(abstract_poset_member* other) const
  {
    return static_cast<homogeneous_block*>(base_space_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline homogeneous_block* p_meet(abstract_poset_member* other)
  {
    return static_cast<homogeneous_block*>(base_space_member::p_meet(other));
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
  inline homogeneous_block* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<homogeneous_block*>(base_space_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of thisposet with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline homogeneous_block* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<homogeneous_block*>(base_space_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline homogeneous_block* l_not(bool xnew_jem = true) const
  {
    return static_cast<homogeneous_block*>(base_space_member::l_not(xnew_jem));
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
  /// Class invariant
  ///
  virtual bool invariant() const;

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual homogeneous_block& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  homogeneous_block& operator=(const homogeneous_block& xother);

protected:

private:

  //@}
};
  
} // namespace fiber_bundle

#endif // COM_LIMITPOINT_FIBER_BUNDLE_HOMOGENEOUS_BLOCK_H
