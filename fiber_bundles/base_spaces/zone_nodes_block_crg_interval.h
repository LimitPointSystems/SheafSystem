
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
//

/// @file
/// Interface for class zone_nodes_block_crg_interval.

#ifndef ZONE_NODES_BLOCK_CRG_INTERVAL_H
#define ZONE_NODES_BLOCK_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_CRG_INTERVAL_H
#include "homogeneous_block_crg_interval.h"
#endif

#ifndef BLOCK_ADJACENCY_H
#include "block_adjacency.h"
#endif

#ifndef SCATTERED_INSERTION_INDEX_SPACE_HANDLE_H
#include "scattered_insertion_index_space_handle.h"
#endif

#ifndef RAGGED_ARRAY_H
#include "ragged_array.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef SINGLY_LINKED_LIST_H
#include "singly_linked_list.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

class block_connectivity;

///
/// Emulator for a interval of implicit base space members
/// representing an unstructured block, that is,
/// a homogeneous collection of zones of a given type
/// with nodal connectivity.
///
class SHEAF_DLL_SPEC zone_nodes_block_crg_interval : public homogeneous_block_crg_interval
{

  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name ZONE_NODE_BLOCK_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  zone_nodes_block_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~zone_nodes_block_crg_interval();

private:

  ///
  /// The name of the prototype for
  /// the zone type of connectivity xconn.
  ///
  static const std::string& zone_prototype_name(const block_connectivity& xconn);

  ///
  /// The dimension of the zone type of connectivity xconn.
  ///
  static int zone_db(const block_connectivity& xconn);

  ///
  /// Connectivity size for each zone
  ///
  size_type _nodes_per_zone;

  ///
  /// The hub id of the beginning of the zones.
  ///
  pod_index_type _zone_begin;

  ///
  /// The number of zones.
  ///
  size_type _zone_size;

  ///
  /// The hub id of the beginning of the vertices.
  ///
  pod_index_type _vertex_begin;

  ///
  /// The number of vertices.
  ///
  size_type _vertex_size;

  ///
  /// The connectivity for this block in hub ids.
  ///
  block<pod_index_type> _connectivity;

  ///
  /// The adjacency for this block.
  ///
  ragged_array<pod_index_type> _adjacency;

  //@}


  // ===========================================================
  /// @name VERTEX CLIENT ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the vertex client id space has been initialized.
  ///
  bool vertex_client_id_space_initialized() const;

  ///
  /// The index of the vertex client id space.
  ///
  pod_index_type vertex_client_space_id() const;

protected:

  ///
  /// The reserved name for the vertex client id space of this interval.
  ///
  std::string vertex_client_id_space_name();

  ///
  /// Initializes the vertex client id space.
  ///
  void initialize_vertex_client_id_space(block_adjacency& xadjacency);

  ///
  /// The index of the vertex client id space.
  ///
  pod_index_type _vertex_client_space_id;

  ///
  /// True, if and only if the client id space has been initialized.
  ///
  bool _vertex_client_id_space_initialized;

private:

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ZONES FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the zones id space.
  ///
  void initialize_zones(base_space_poset& xhost);

private:

  //@}


  // ===========================================================
  /// @name VERTICES FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the vertex id space.
  ///
  void initialize_vertices(base_space_poset& xhost);

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  using base_space_crg_interval::db;

  ///
  /// The dimension of the member with id xmbr_id.
  /// Does not require access to dof tuple.
  ///
  virtual int db(pod_index_type xmbr_id) const;

  ///
  /// The id space index for the cells of dimension xd.
  /// Returns invalid_pod_index() if there is no id space for dimension xd.
  ///
  virtual pod_index_type d_cells_space_id(int xd) const;

protected:

  ///
  /// The dimension of a zone.
  ///
  int _zone_db;

private:

  //@}


  // ===========================================================
  /// @name BLOCK VERTICES FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the block vertices id space.
  ///
  void initialize_block_vertices();

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The size of the interval for block connectivity xconn.
  ///
  static void get_size(const block_connectivity& xconn, size_type& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

public:

protected:

  ///
  /// Initialize the lower covers for this interval.
  ///
  virtual void initialize_lower_covers();

  ///
  /// Initialize the upper cover for this interval.
  ///
  virtual void initialize_upper_covers();

private:

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  ///
  /// The dof tuple ids for an instance
  /// created with parameter xi_size.
  ///
  static void get_dof_tuple_ids(poset_state_handle& xhost,
                                const block_connectivity& xconn,
                                block<pod_index_type>& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The private data for an instance with connectivity xconn.
  ///
  static void get_private_data(const block_connectivity& xconn,
                               block<pod_index_type>& result);

protected:

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void get_implicit_private_data(block<pod_index_type>& xdata) const;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void put_implicit_private_data(const block<pod_index_type>& xdata);

private:

  //@}


  // ===========================================================
  /// @name FINIALIZE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Finialize the initialization of this crg interval in the host xhost.
  ///
  virtual void finalize(poset_state_handle& xhost);

protected:

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const std::string& class_name() const;

  ///
  /// True if fully initialized.
  ///
  virtual bool is_initialized() const;

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual zone_nodes_block_crg_interval* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fiber_bundle

#endif // ifndef ZONE_NODES_BLOCK_CRG_INTERVAL_H
