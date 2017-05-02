
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

// Interface for class hex_connectivity

#ifndef HEX_CONNECTIVITY_H
#define HEX_CONNECTIVITY_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef BLOCK_CONNECTIVITY_H
#include "SheafSystem/block_connectivity.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// Nodal connectivity for a block containing zones of type hex.
///
class SHEAF_DLL_SPEC hex_connectivity : public block_connectivity
{

public:

  // ===========================================================
  /// @name HEX_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:
  ///
  /// Default constructor.
  /// Equivalent to hex_connectivity(1, 1, 1)
  ///
  hex_connectivity();

  ///
  /// Copy constructor
  ///
  hex_connectivity(const hex_connectivity& xother);
 
  ///
  /// Creates an instance corresponding to the general arrangement
  /// of vertices given by node_ids() == xnode_ids
  /// and node_id_ct() == xnode_id_ct. If xnode_ct == 0,
  /// node_ct() will be computed from node_ids(), otherwise,
  /// node_ct() == xnode_ct.
  ///
  hex_connectivity(const pod_index_type* xnode_ids,
                   size_type xnode_id_ct, 
                   size_type xnode_ct);

  ///
  /// Creates an instance corresponding to a cubical array of
  /// vertices (xi_size + 1)*(x_jsize + 1)*(xk_size + 1), 
  /// that is, xi_size, xj_size and xk_size
  /// are the number of edges in the i, j, and k direction, respectively.
  /// Xstart_id is the id of the first vertex, that is, i=0, j=0.
  ///
  hex_connectivity(size_type xi_size,
                   size_type xj_size,
                   size_type xk_size,
                   pod_index_type xstart_id = 0);
  ///
  /// Destructor.
  ///
  virtual ~hex_connectivity();

  ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 8}; 

protected:
  ///
  /// Allocates and initializes the connectivity array.
  ///
  void create_connectivity(size_type xi_size,
                   size_type xj_size,
                   size_type xk_size,
                   pod_index_type xstart_id = 0);

  ///
  /// The number of vertices in the i-direction.
  ///
  size_type _i_vertex_size;

  ///
  /// The number of vertices in the j-direction.
  ///
  size_type _j_vertex_size;

  ///
  /// The number of vertices in the k-direction.
  ///
  size_type _k_vertex_size;

  ///
  /// The node id associated with (xi,xj,xk).
  ///
  size_type node_id(size_type xi, size_type xj, size_type xk) const;

private:

  //@}

// ===========================================================
  /// @name BLOCK_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}

  // ===========================================================
  /// @name BLOCK_RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The element type.
  ///
  virtual cell_type element_type() const;

protected:

private:

  //@}

// ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:
  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual hex_connectivity* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:

private:

  //@}

};
  
} //namespace fiber_bundle

#endif // ifndef HEX_CONNECTIVITY_H
