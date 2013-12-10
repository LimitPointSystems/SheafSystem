
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Interface for class block_adjacency

#ifndef BLOCK_ADJACENCY_H
#define BLOCK_ADJACENCY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_RELATION_H
#include "block_relation.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_SLIST_H
#include "std_slist.h"
#endif

namespace fiber_bundle
{

  class block_connectivity;
  using namespace sheaf;

///
/// Node to zone adjacency relation for a block of zones of a given type.
///
class SHEAF_DLL_SPEC block_adjacency : public block_relation
{

  // ===========================================================
  // BLOCK_ADJACENCY FACET
  // ===========================================================

public:

  ///
  /// The type of the adjacency relation.
  ///
  typedef std::map< pod_index_type, slist<pod_index_type> > adj_type;

  ///
  /// Type of iterator for nodes.
  ///
  typedef adj_type::iterator node_iterator_type;

  ///
  /// Type of const iterator for nodes.
  ///
  typedef adj_type::const_iterator const_node_iterator_type;

  ///
  /// Type of iterator for zones.
  ///
  typedef adj_type::mapped_type::iterator zone_iterator_type;

  ///
  /// Type of const iterator for zones.
  ///
  typedef adj_type::mapped_type::const_iterator const_zone_iterator_type;


  ///
  /// Default constructor
  ///
  ///
  block_adjacency();

  ///
  /// Copy constructor
  ///
  ///
  block_adjacency(const block_adjacency& xother);

  ///
  /// Creates an instance which is the transpose of connectivty xconn.
  ///
  block_adjacency(const block_connectivity& xconn);

  ///
  /// Creates an instance which is transpose of the connectivity
  /// in xnode_ids, wit element_type() == xelement_type.
  ///
  block_adjacency(size_type xzone_ct,
                  size_type xnodes_per_zone,
                  size_type xnode_ids_ct,
                  const pod_index_type* xnode_ids,
                  cell_type xelement_type = CELL_TYPE_END);

  ///
  /// Destructor
  ///
  virtual ~block_adjacency();

  ///
  /// Makes this the transpose of connectivity xconn.
  ///
  void put_connectivity(const block_connectivity& xconn);

  ///
  /// Makes this the transpose of connectivity xconn.
  ///
  void put_connectivity(size_type xzone_ct,
                        size_type xnodes_per_zone,
                        size_type xnode_ids_ct,
                        const pod_index_type* xnode_ids);

  ///
  /// Makes this the transpose of connectivity xconn;
  /// synonym for put_connectivity(xconn).
  ///
  block_adjacency& operator=(const block_connectivity& xconn);

  ///
  /// Beginning of adjacency relation.
  ///
  node_iterator_type begin();

  ///
  /// Beginning of adjacency relation; const version.
  ///
  const_node_iterator_type begin() const;

  ///
  /// End of adjacency relation.
  ///
  node_iterator_type end();

  ///
  /// End of adjacency relation; const version.
  ///
  const_node_iterator_type end() const;

  ///
  /// The number of distinct nodes.
  ///
  size_type node_ct() const;

  ///
  /// The number of distinct zones.
  ///
  size_type zone_ct() const;


protected:

  ///
  /// Storage for the adjcency relation.
  ///
  adj_type _adj;

  ///
  /// The number of distinct nodes.
  ///
  size_type _node_ct;

  ///
  /// The number of distinct zones.
  ///
  size_type _zone_ct;


private:

  // ===========================================================
  // BLOCK_RELATION FACET
  // ===========================================================

public:

  ///
  /// The element type.
  ///
  virtual cell_type element_type() const;

protected:

  ///
  /// The element type.
  ///
  cell_type _element_type;

private:


  // ===========================================================
  // ANY FACET
  // ===========================================================

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual block_adjacency* clone() const;

  ///
  /// Assignment operator
  ///
  ///
  block_adjacency& operator=(const block_adjacency& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
///  Print block_adjacency& xconn to stream xos.
///
SHEAF_DLL_SPEC 
std::ostream& operator<<(std::ostream& xos, const block_adjacency& xconn);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle
 

#endif // ifndef BLOCK_ADJACENCY_H
