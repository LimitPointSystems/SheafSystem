
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
/// Interface for class structured_block_3d_crg_interval

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_STRUCTURED_BLOCK_3D_CRG_INTERVAL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_STRUCTURED_BLOCK_3D_CRG_INTERVAL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_HOMOGENEOUS_BLOCK_CRG_INTERVAL_H
#include "ComLimitPoint/fiber_bundle/homogeneous_block_crg_interval.h"
#endif

namespace sheaf
{
class ijk_product_structure;
}

namespace fiber_bundle
{

using namespace sheaf;

///
/// Emulator for a interval of implicit base space members
/// representing a 3 dimensional structured block, that is,
/// a homogeneous collection of connected hexahedra
/// arranged in an i_size() x j_size() x k_size() array.
///
class SHEAF_DLL_SPEC structured_block_3d_crg_interval : public homogeneous_block_crg_interval
{

  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name STRUCTURED_BLOCK_3D_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  structured_block_3d_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~structured_block_3d_crg_interval();

  ///
  /// The number of zones in the i direction in this block.
  ///
  size_type i_size() const;

  ///
  /// The number of zones in the j direction in this block.
  ///
  size_type j_size() const;

  ///
  /// The number of zones in the k direction in this block.
  ///
  size_type k_size() const;

protected:

  ///
  /// The index of the vertex identified by tuple (xi, xj, xk).
  ///
  pod_index_type vertex_id(pod_index_type xi, 
			   pod_index_type xj, 
			   pod_index_type xk) const;

private:

  ///
  /// The number of zones in the i direction in this block.
  ///
  size_type _i_size;

  ///
  /// The number of zones in the j direction in this block.
  ///
  size_type _j_size;

  ///
  /// The number of zones in the k direction in this block.
  ///
  size_type _k_size;

  ///
  /// _j_size*_k_size
  ///
  size_type _jk_size;

  ///
  /// The number of vertices in the i direction in this block.
  ///
  size_type _i_vertex_size;

  ///
  /// The number of vertices in the j direction in this block.
  ///
  size_type _j_vertex_size;

  ///
  /// The number of vertices in the k direction in this block.
  ///
  size_type _k_vertex_size;

  ///
  /// _j_vertex_size*_k_vertex_size
  ///
  size_type _jk_vertex_size;

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

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK FACET
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

  ///
  /// The product structure of the zone id space.
  ///
  const ijk_product_structure& zones_product_structure() const;

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

  ///
  /// The product structure of the vertex id space.
  ///
  const ijk_product_structure& vertices_product_structure() const;

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
  /// The size for an instance created with parameter xi_size.
  ///
  static void get_size(size_type xi_size,
                       size_type xj_size,
                       size_type xk_size,
                       size_type& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

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
                                size_type xi_size,
                                size_type xj_size,
                                size_type xk_size,
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
  /// The private data for an instance with parameter xi_size.
  ///
  static void get_private_data(size_type xi_size,
                               size_type xj_size,
                               size_type xk_size,
                               block<pod_index_type>& result);

protected:

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const;

  ///
  /// The private data for this instance.
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
  virtual structured_block_3d_crg_interval* clone() const;

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

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_STRUCTURED_BLOCK_3D_CRG_INTERVAL_H
