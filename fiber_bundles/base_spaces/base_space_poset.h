
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
/// Interface for class base_space_poset.

#ifndef BASE_SPACE_POSET_H
#define BASE_SPACE_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef REFINABLE_POSET_H
#include "refinable_poset.h"
#endif

namespace sheaf
{
class namespace_poset;
}

namespace fiber_bundle
{

using namespace sheaf;  
  
class base_space_crg_interval;
class base_space_member_row_dof_tuple_type;
class base_space_poset;

// Following functions must be forward declared before friend statement.

///
/// The deep size of the referenced object of type poset_state_handle.
/// if xinclude_shallow, add the sizeof xp to the result.
/// if xresults is not null, the deep size of the poset_state parts returned;
/// xresults[0] is the deep_size of poset_crg_state,
/// xresults[1] is the deep_size of index_space_family,
/// xresults[2] is the deep_size of poset_powerset_state,
/// xresults[3] is the deep_size of poset_table_state.
///
SHEAF_DLL_SPEC
size_t deep_size(const base_space_poset& xp,
		 bool xinclude_shallow = true,
		 size_t xresults[4] = 0);

///
/// The type of table dof tuple for base_space_poset.
///
class SHEAF_DLL_SPEC base_space_poset_table_dof_tuple_type
{
public:

  ///
  /// The maximum dimension of the members of this base space.
  ///
  int max_db;

protected:

private:

};  

///
/// The lattice of closed cells of a cellular space;
/// a lattice representation of a computational mesh.
///
class SHEAF_DLL_SPEC base_space_poset : public refinable_poset
{

  friend class sheaf::namespace_poset;
  friend class unstructured_block_builder;
  friend class fiber_bundles_namespace;
  friend SHEAF_DLL_SPEC size_t fiber_bundle::deep_size(const base_space_poset& xp, bool xinclude_shallow, size_t xresults[4]);
  
  // ===========================================================
  /// @name BASE_SPACE_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of table dof tuple for this.
  ///
  typedef base_space_poset_table_dof_tuple_type table_dof_tuple_type;

  ///
  /// The type of row dof tuple for this.
  ///
  typedef base_space_member_row_dof_tuple_type row_dof_tuple_type;

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates a new base_space_poset in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attribute max_db
  /// specified by xmax_db..
  ///
  static base_space_poset& new_table(namespace_type& xhost, 
				     const poset_path& xpath, 
				     const poset_path& xschema_path,
				     int xmax_db,
				     bool xauto_access);
  
protected:

  ///
  /// Default constructor; creates a new base_space_poset handle not attached to any state.
  ///
  base_space_poset();

  ///
  /// Copy constructor; disabled.
  ///
  base_space_poset(const base_space_poset& xother) { };

  ///
  /// Destructor
  ///
  virtual ~base_space_poset();

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}



  // ===========================================================
  /// @name ZONE ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True, if and only if the block containing the member with index
  /// xmbr_id has a zone id space.
  ///
  bool contains_zone_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// True, if and only if the block containing the member with index
  /// xmbr_id has a zone id space.
  /// synonym for contains_zone_id_space(xmbr_id.hub_pod()).
  ///
  bool contains_zone_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an zone id space handle for the block containing
  /// the member with index xmbr_id from the pool of handles.
  ///
  index_space_handle& get_zone_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an zone id space handle for the block containing
  /// the member with index xmbr_id from the pool of handles.
  /// synonym for get_zone_id_space(xmbr_id.hub_pod()).
  ///

  index_space_handle& get_zone_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Returns the handle to the zone id space, xid_space to the
  /// pool of id space handles.
  ///
  void release_zone_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates an zone id space iterator for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  ///
  index_space_iterator& get_zone_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an zone id space iterator for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  /// synonym for get_zone_id_space_iterator(xmbr_id.hub_pod()).
  ///
  index_space_iterator& get_zone_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Returns the iterator to the zone id space, xitr to the
  /// pool of id space iterators.
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
  /// True, if and only if the block containing the member with index
  /// xmbr_id has a vertex id space.
  ///
  bool contains_vertex_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// True, if and only if the block containing the member with index
  /// xmbr_id has a vertex id space.
  /// synonym for contains_vertex_id_space(xmbr_id.hub_pod()).
  ///
  bool contains_vertex_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an vertex id space handle for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  ///
  index_space_handle& get_vertex_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an vertex id space handle for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  /// synonym for get_vertex_id_space(xmbr_id.hub_pod()).
  ///
  index_space_handle& get_vertex_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Returns the handle to the vertex id space, xid_space to the
  /// pool of id space handles.
  ///
  void release_vertex_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates an vertex id space iterator for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  ///
  index_space_iterator& get_vertex_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an vertex id space iterator for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  /// synonym for get_vertex_id_space_iterator(xmbr_id.hub_pod()).
  ///
  index_space_iterator& get_vertex_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Returns the iterator to the vertex id space, xitr to the
  /// pool of id space iterators.
  ///
  void release_vertex_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name VERTEX CLIENT ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True, if and only if the block containing the member with index
  /// xmbr_id has a vertex client id space.
  ///
  bool contains_vertex_client_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// True, if and only if the block containing the member with index
  /// xmbr_id has a vertex client id space.
  /// synonym for contains_vertex_client_id_space(xmbr_id.hub_pod()).
  ///
  bool contains_vertex_client_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an vertex client id space handle for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  ///
  index_space_handle& get_vertex_client_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an vertex client id space handle for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  /// synonym for get_vertex_client_id_space(xmbr_id.hub_pod()).
  ///
  index_space_handle& get_vertex_client_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Returns the handle to the vertex client id space, xid_space to the
  /// pool of id space handles.
  ///
  void release_vertex_client_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates an vertex client id space iterator for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  ///
  index_space_iterator& get_vertex_client_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// Allocates an vertex client id space iterator for the block containing
  /// the member with index xmbr_id for the pool of id spaces.
  /// synonym for get_vertex_client_id_space_iterator(xmbr_id.hub_pod()).
  ///
  index_space_iterator& get_vertex_client_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Returns the iterator to the vertex client id space, xitr to the
  /// pool of id space iterators.
  ///
  void release_vertex_client_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

private:

  //@}


  // ==========================================================
  /// @name CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this poset contains the connectivity for a zone with id xzone_id.
  ///
  bool contains_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const;

  ///
  /// True if this poset contains the connectivity for a zone with id xzone_id.
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
  /// True if this poset contains the adjacency for a vertex with id xvertex_id.
  ///
  bool contains_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const;

  ///
  /// True if this poset contains the adjacency for a vertex with id xvertex_id.
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
  /// @name MEMBER PROTOTYPES FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of the prototypes poset;
  /// a synonym for bsae_space_member::prototypes_poset_name().
  ///
  static const std::string& prototypes_poset_name();

  ///
  /// The type id of the base space member prototype with name xname.
  ///
  pod_index_type prototype_type_id(const std::string& xname, bool xauto_access = true) const;

  ///
  /// The dof tuple id in this of the base space member prototype
  /// with name xname and refinememnt_depth xdepth. If xcreate,
  /// create the dof tuple if it doesn't already exist.
  ///
  scoped_index prototype_dof_tuple_id(const std::string& xname,
				      int xdepth,
				      bool xcreate,
				      bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

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
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

private:

  //@}

  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  using refinable_poset::new_member;
  
  ///
  /// Creates a disconnected jim using the prototype with name xprototype_name.
  /// If xcopy_dof_map or if xhost does not already contain a copy 
  /// of the prototype dof map, create a copy of the dof map,
  /// otherwise just refer to an existing copy.
  ///
  pod_index_type new_member(const std::string& xprototype_name, bool xcopy_dof_map);
  
  ///
  /// Synonym for new_member(const std::string& xprototype_name, bool xcopy_dof_map),
  /// provided only to eliminate ambiguity with refinable_poset::new_member(bool, pod_index_type)
  /// when xprototype_name is provided as a string literal.
  ///
  pod_index_type new_member(const char* xprototype_name, bool xcopy_dof_map);

  ///
  /// Creates a new jim and initializes it for use as a prototype with 
  /// type name xtype_name, dimension xdb, and local cell prototype xlocal_cell_name.
  ///
  pod_index_type new_member(const std::string& xtype_name, int xdb, const std::string& xlocal_cell_name);
  
protected:

private:

  //@}

  // ===========================================================
  /// @name SUBPOSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The subposet containing all the blocks, const ver (mutable version).
  ///
  subposet& blocks();

  ///
  /// The subposet containing all the blocks, const ver (const version).
  ///
  const subposet& blocks() const;

  ///
  /// The name of the blocks subposet.
  ///
  static std::string blocks_name();

  ///
  /// The subposet containing the vertices associated with blocks (mutable version).
  ///
  subposet& block_vertices();

  ///
  /// The subposet containing the vertices associated with blocks (const version).
  ///
  const subposet& block_vertices() const;

  ///
  /// The name of the block vertices subposet.
  ///
  static std::string block_vertices_name();

  ///
  /// The subposet containing all the vertices, that is, the cells of dimension 0 (mutable version).
  ///
  subposet& vertices();

  ///
  /// The subposet containing all the vertices, that is, the cells of dimension 0 (const version).
  ///
  const subposet& vertices() const;

  ///
  /// The subposet containing the elements or zones, that is, the cells of maximal dimension.
  ///
  subposet& elements();

  ///
  /// The subposet containing the elements or zones, that is, the cells of maximal dimension.
  ///
  const subposet& elements() const;

  ///
  /// The subposet containing the cells of dimension xd (mutable version).
  ///
  subposet& d_cells(int xd);

  ///
  /// The subposet containing the cells of dimension xd (const version).
  ///
  const subposet& d_cells(int xd) const;

  ///
  /// The id space for the subposet containing the cells of dimension xd (mutable version).
  ///
  scattered_insertion_index_space_handle& d_cells_id_space(int xd);

  ///
  /// The id space for the subposet containing the cells of dimension xd (const version).
  ///
  const scattered_insertion_index_space_handle& d_cells_id_space(int xd) const;

  ///
  /// The name of the xdb-cell subposet.
  ///
  static std::string d_cells_name(int xdb, int xmax_db);

  ///
  /// The subposet containing all the cells, of any dimension.
  ///
  subposet& cells();

  ///
  /// The subposet containing all the cells, of any dimension.
  ///
  const subposet& cells() const;

  ///
  /// The name of the cells subposet.
  ///
  static std::string cells_name();

  ///
  /// Inserts interval xinterval into the standard subposets.
  ///
  void insert_interval_in_standard_subposets(base_space_crg_interval& xinterval);

protected:

  ///
  /// The subposet containing all the blocks.
  ///
  subposet _blocks;

  ///
  /// The subposet containing the vertices associated with blocks.
  ///
  subposet _block_vertices;

  ///
  /// The subposets containing the cells of dimension 0 <= d <= db().
  ///
  block<subposet> _d_cells;

  ///
  /// The id spaces for the subposets containing the cells of dimension 0 <= d <= db().
  ///
  block<scattered_insertion_index_space_handle*> _d_cells_id_spaces;

  ///
  /// The subposet containing all the cells.
  ///
  subposet _cells;

  ///
  /// Creates the subposets common to every poset (i.e._whole and _jims).
  ///
  virtual void initialize_standard_subposets(const std::string& xname);

private:

  //@}
 
 
  // ===========================================================
  /// @name TABLE DOFS FACET
  // ===========================================================
  //@{

public:

  ///
  /// The maximum dimension of the members of this base space.
  ///
  int max_db() const;

  ///
  /// Sets max_db() to xmax_db.
  ///
  void put_max_db(int xmax_db);

  ///
  /// Sets max_db() to the larger of old max_db() and xmax_db.
  ///
  void update_max_db(int xmax_db);

  ///
  /// The table dof tuple for this (const version).
  ///
  const table_dof_tuple_type* table_dof_tuple() const;

  ///
  /// The table dof tuple for this (mutable version).
  ///
  table_dof_tuple_type* table_dof_tuple();

protected:

private:

  //@}

  // ===========================================================
  /// @name ROW DOFS FACET
  // ===========================================================
  //@{

public:

  ///
  /// The base space dimension of the member with hub id xmbr_hub_id.
  ///
  int db(pod_index_type xmbr_hub_id) const;

  ///
  /// The base space dimension of the member with id xmbr_id.
  ///
  int db(const scoped_index& xmbr_id) const;

  ///
  /// The type id of the member with hub id xmbr_hub_id.
  ///
  pod_index_type type_id(pod_index_type xmbr_hub_id) const;

  ///
  /// The type id of the member with id xmbr_id.
  ///
  pod_index_type type_id(const scoped_index& xmbr_id) const;

  ///
  /// The type id of the member with hub id xmbr_hub_id.
  ///
  std::string type_name(pod_index_type xmbr_hub_id) const;

  ///
  /// The type id of the member with id xmbr_id.
  ///
  std::string type_name(const scoped_index& xmbr_id) const;

  ///
  /// The refinement depth of the member with hub id xmbr_hub_id.
  ///
  int refinement_depth(pod_index_type xmbr_hub_id) const;

  ///
  /// The refinement depth of the member with id xmbr_id.
  ///
  int refinement_depth(const scoped_index& xmbr_id) const;

  ///
  /// Sets the refinement depth of the member with hub id xmbr_hub_id to xdepth.
  ///
  void put_refinement_depth(pod_index_type xmbr_hub_id, int xdepth);

  ///
  /// Sets the refinement depth of the member with id xmbr_id to xdepth.
  ///
  void put_refinement_depth(const scoped_index& xmbr_id, int xdepth);

  using refinable_poset::member_dof_tuple;
  
  ///
  /// The row dof tuple for the member with member hub id xmbr_hub_id.
  ///
  row_dof_tuple_type* member_dof_tuple(pod_index_type xmbr_hub_id,
                                       bool xrequire_write_access = false) const;

  ///
  /// The row dof tuple for the member with member id xmbr_id.
  ///
  row_dof_tuple_type* member_dof_tuple(const scoped_index& xmbr_id,
                                       bool xrequire_write_access = false) const;

  ///
  /// The row dof tuple with tuple hub id xtuple_hub_id.
  ///
  row_dof_tuple_type* row_dof_tuple(pod_index_type xtuple_hub_id,
                                    bool xrequire_write_access = false) const;

  ///
  /// The row dof tuple with tuple id xtuple_id.
  ///
  row_dof_tuple_type* row_dof_tuple(const scoped_index& xtuple_id,
                                    bool xrequire_write_access = false) const;

  using refinable_poset::new_row_dof_map;

  ///
  /// Creates a new dof map with dofs equal to those of
  /// the prototype with name xprototype_name.
  ///
  const scoped_index& new_row_dof_map(const std::string& xprototype_name);

protected:

private:

  //@}

  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the member with hub id xmbr_id is an explicit member.
  ///
  /// @hack product subposet hack, ver 2.
  /// Needed to enforce that a section space schema member with an implicit
  /// base space schema member is not supported by the i/o system.
  ///
  bool is_explicit_member(pod_index_type xmbr_id) const;
  
  ///
  /// True if the member with hub id xmbr_id is a block member.
  ///
  /// @hack product subposet hack, ver 2.
  /// Needed to enforce that a section space schema member with an implicit
  /// base space schema member is not supported by the i/o system.
  ///
  bool is_block_member(pod_index_type xmbr_id) const;
  
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
  virtual base_space_poset* clone() const;

  ///
  /// Assignment operator; disabled.
  ///
  base_space_poset& operator=(const poset_state_handle& xother)
  {
    return const_cast<base_space_poset&>(*this);
  };

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================



} // namespace fiber_bundle


#endif // BASE_SPACE_POSET_H
