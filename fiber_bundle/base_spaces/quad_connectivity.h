
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

// Interface for class quad_connectivity

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_QUAD_CONNECTIVITY_H
#define COM_LIMITPOINT_FIBER_BUNDLE_QUAD_CONNECTIVITY_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BASE_CONNECTIVITY_H
#include "ComLimitPoint/fiber_bundle/block_connectivity.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;


///
/// Nodal connectivity for a block containing zones of type quad.
///
class SHEAF_DLL_SPEC quad_connectivity : public block_connectivity
{

public:
  // ===========================================================
  // @name QUAD_CONNECTIVITY FACET
  // ===========================================================
  //@{

  ///
  /// Default constructor.
  /// Equivalent to quad_connectivity(1, 1)
  ///
  quad_connectivity();

  ///
  /// Copy constructor
  ///
  quad_connectivity(const quad_connectivity& xother);

  ///
  /// Creates an instance corresponding to the general arrangement
  /// of vertices given by node_ids() == xnode_ids,
  /// and node_id_ct() == xnode_id_ct. If xnode_ct == 0,
  /// node_ct() will be computed from node_ids(), otherwise,
  /// node_ct() == xnode_ct.
  ///
  quad_connectivity(const pod_index_type* xnode_ids,
                    size_type xnode_id_ct, 
                    size_type xnode_ct);

  ///
  /// Creates an instance corresponding to a rectangular array of
  /// vertices xi_size + 1 by  x_jsize + 1, that is, xi_size and xj_size
  /// are the number of edges in the i and j direction, respectively.
  /// Xstart_id is the id of the first vertex, that is, i=0, j=0.
  ///
  quad_connectivity(size_type xi_size, size_type xj_size, pod_index_type xstart_id = 0);

  ///
  /// Destructor.
  ///
  virtual ~quad_connectivity();


  ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 4}; 

protected:

  ///
  /// Allocates and initializes the connectivity array.
  ///
  void create_connectivity(size_type xi_size, 
			   size_type xj_size,
			   pod_index_type xstart_id);


private:

 //@}

  // ===========================================================
  /// @name BLOCK_CONNECTIVITY FACET
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
  // ANY FACET
  // ===========================================================

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
   virtual quad_connectivity* clone() const;

//   ///
//   /// Class invariant.
//   ///
   virtual bool invariant() const;

//   ///
//   /// Conformance test; true if other conforms to this
//   ///
   virtual bool is_ancestor_of(const any* other) const;

};
  
} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_QUAD_CONNECTIVITY_H
