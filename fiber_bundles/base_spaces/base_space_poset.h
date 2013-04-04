// $RCSfile: base_space_poset.h,v $ $Revision: 1.43 $ $Date: 2013/03/20 21:56:04 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

///
/// The lattice of closed cells of a cellular space;
/// a lattice representation of a computational mesh.
///
class SHEAF_DLL_SPEC base_space_poset : public refinable_poset
{

  friend class sheaf::namespace_poset;
  friend class unstructured_block_builder;
  friend class fiber_bundles_namespace;
  friend SHEAF_DLL_SPEC size_t deep_size(const base_space_poset& xp, bool xinclude_shallow, size_t xresults[4]);
  
  // ===========================================================
  /// @name BASE_SPACE_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Makes a constructor arg_list for an instance
  /// with maximum intrinsic dimension xmax_db.
  /// Intended for use with fiber_bundles_namespace::new_base_space.
  ///
  static arg_list make_args(int xmax_db);

protected:

  ///
  /// Default constructor; creates a new base_space_poset handle not attached to any state.
  ///
  base_space_poset();

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  base_space_poset(const base_space_poset& xother);

  ///
  /// Copy constructor; attaches this to the same state as xother.
  //// @hack needed only because base_space_member::host() is type poset.
  //// @todo remove when finished refactoring sheaves and fiber_bundles.
  ////
  base_space_poset(const poset& xother);

  ///
  /// Destructor
  ///
  virtual ~base_space_poset();

  ///
  /// Creates a new base_space_poset in namespace xhost with schema
  /// specified by xschema_path, name xname, and maximum dimension xmax_db.
  ///
  base_space_poset(namespace_poset* xhost,
                   const poset_path& xschema_path,
                   const string& xname,
                   int xmax_db,
                   bool xauto_access = true);

  ///
  /// Creates a new base_space_poset with schema xschema,
  /// name xname and maximum dimension xmax_db.
  ///
  base_space_poset(namespace_poset* xhost,
                   schema_poset_member* xschema,
                   const string& xname,
                   int xmax_db,
                   bool xauto_access = true);

  ///
  /// Creates a new handle attached to the base_space_poset with
  /// index xindex in namespace xhost.
  ///
  base_space_poset(const namespace_poset* xhost, pod_index_type xindex);

  ///
  /// Creates a new handle attached to the base_space_poset with
  /// index xindex in namespace xhost.
  ///
  base_space_poset(const namespace_poset* xhost, const scoped_index& xindex);

  ///
  /// Creates a new handle attached to the base_space_poset with
  /// name xname in namespace xhost.
  ///
  base_space_poset(const namespace_poset* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the base_space_poset associated
  /// with namespace member xmbr
  ///
  base_space_poset(const abstract_poset_member* xmbr);

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

protected:

  using refinable_poset::new_state;

  // Following definitions hide the inherited new_state routines.

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// maximum dimension xmax_db.
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 int xmax_db,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema xschema,  name xname, and maximum dimension xmax_db.
  ///
  void new_state(namespace_poset* xname_space,
                 schema_poset_member* xschema,
                 const string& xname,
                 int xmax_db,
                 bool xauto_access = true);

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

protected:

private:

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


  // ===========================================================
  /// @name STANDARD SUBPOSETS FACET
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
  static string blocks_name();

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
  static string block_vertices_name();

  ///
  /// The subposet containing all the vertices (mutable version).
  ///
  subposet& vertices();

  ///
  /// The subposet containing all the vertices (const version).
  ///
  const subposet& vertices() const;

  ///
  /// The subposet containing the elements or zones.
  ///
  subposet& elements();

  ///
  /// The subposet containing the elements or zones.
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
  mutable_index_space_handle& d_cells_id_space(int xd);

  ///
  /// The id space for the subposet containing the cells of dimension xd (const version).
  ///
  const mutable_index_space_handle& d_cells_id_space(int xd) const;

  ///
  /// The name of the xdb-cell subposet.
  ///
  static string d_cells_name(int xdb, int xmax_db);

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
  static string cells_name();

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
  block<mutable_index_space_handle*> _d_cells_id_spaces;

  //########################################################################
  //$$MASON

  ///
  /// The subposet containing all the cells.
  ///
  subposet _cells;

  //########################################################################

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
  string type_name(pod_index_type xmbr_hub_id) const;

  ///
  /// The type id of the member with id xmbr_id.
  ///
  string type_name(const scoped_index& xmbr_id) const;

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

protected:

private:

  //@}


  // ===========================================================
  /// @name OTHER FEATURES FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of the prototypes poset;
  /// a synonym for bsae_space_member::prototypes_poset_name().
  ///
  static const string& prototypes_poset_name();

  ///
  /// The type id of the base space member prototype with name xname.
  ///
  pod_index_type prototype_type_id(const string& xname, bool xauto_access = true) const;

  ///
  /// The dof tuple id in this of the base space member prototype
  /// with name xname and refinememnt_depth xdepth. If xcreate,
  /// create the dof tuple if it doesn't already exist.
  ///
  scoped_index prototype_dof_tuple_id(const string& xname,
				      int xdepth,
				      bool xcreate,
				      bool xauto_access) const;

  ///
  /// The type of table dof tuple for this.
  ///
  struct SHEAF_DLL_SPEC table_dof_tuple_type
  {
    ///
    /// The maximum dimension of the members of this base space.
    ///
    int max_db;
  };

  ///
  /// The table dof tuple for this (const version).
  ///
  const table_dof_tuple_type* table_dof_tuple() const;

  ///
  /// The table dof tuple for this (mutable version).
  ///
  table_dof_tuple_type* table_dof_tuple();

  /// @issue why do we define row_dof_tuple_type
  /// both here and in base_space_member?

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
    const char * type_name;

    ///
    /// The refinement depth.
    ///
    int refinement_depth;
  };

  ///
  /// The row dof tuple for the member with hub id xmbr_hub_id.
  ///
  row_dof_tuple_type* member_dof_tuple(pod_index_type xmbr_hub_id,
                                       bool xrequire_write_access = false) const;

  ///
  /// The row dof tuple for the member with id xmbr_id.
  ///
  row_dof_tuple_type* member_dof_tuple(const scoped_index& xmbr_id,
                                       bool xrequire_write_access = false) const;

  ///
  /// The row dof tuple with hub id xmbr_hub_id.
  ///
  row_dof_tuple_type* row_dof_tuple(pod_index_type xmbr_hub_id,
                                    bool xrequire_write_access = false) const;

  ///
  /// The row dof tuple with id xmbr_id.
  ///
  row_dof_tuple_type* row_dof_tuple(const scoped_index& xmbr_id,
                                    bool xrequire_write_access = false) const;

protected:

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

private:

  //@}


  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
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

  using refinable_poset::new_row_dof_map;

  ///
  /// Creates a new dof map with dofs equal to those of
  /// the prototype with name xprototype_name.
  ///
  const scoped_index& new_row_dof_map(const string& xprototype_name);

protected:

  ///
  /// Creates the subposets common to every poset (i.e._whole and _jims).
  ///
  virtual void initialize_standard_subposets(const string& xname);

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

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
  /// Assignment operator; attaches this to the same state as xother
  ///
  base_space_poset& operator=(const poset_state_handle& xother);

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

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

} // namespace fiber_bundle


#endif // BASE_SPACE_POSET_H
