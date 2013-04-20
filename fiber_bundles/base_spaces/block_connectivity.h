
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class block_connectivity

#ifndef BLOCK_CONNECTIVITY_H
#define BLOCK_CONNECTIVITY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_RELATION_H
#include "block_relation.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// Zone to node connectivity relation for zone_nodes block.
///
class SHEAF_DLL_SPEC block_connectivity  : public block_relation
{
public:

  // ===========================================================
  /// @name BLOCK_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

  ///
  ///  Destructor.
  ///
  virtual ~block_connectivity();

  ///
  /// The number of elements.
  ///
  size_type element_ct() const;

  ///
  /// The number of distinct nodes.
  ///
  size_type node_ct() const;

  ///
  ///  The nodal connectivity array.
  ///
  pod_index_type* node_ids();

  ///
  ///  The nodal connectivity array.
  ///
  const pod_index_type* node_ids() const;

  ///
  /// True if destructor of this should delete _node_ids.
  ///
  bool delete_node_ids() const;

  ///
  ///  The number of entries in node_ids().
  ///
  size_type node_id_ct() const;

  ///
  ///  The number of nodes per element.
  ///
  size_type nodes_per_element() const;

  ///
  /// The id given to the first node id generated.
  ///
  pod_index_type start_id() const;

  ///
  ///  Print to stream xos.
  ///
  virtual void to_stream(ostream& xos) const;

  ///
  /// Assignment operator
  ///
  block_connectivity& operator=(const block_connectivity& xother);

  ///
  /// Equality operator.
  ///
  virtual bool operator==(const block_connectivity& xother) const;

protected:

  ///
  /// Default constructor.
  ///
  block_connectivity();

  ///
  /// Copy constructor.
  ///
  block_connectivity(const block_connectivity& xother);

  ///
  /// Creates an instance with node_ids() == xnode_ids,
  /// node_id_ct() == xnode_id_ct, and start_id() == xstart_id.
  /// If xnode_ct == 0, the number of distinct nodes will
  /// be computed, otherwise node_ct() == xnode_ct.
  ///
  block_connectivity(const pod_index_type* xnode_ids, 
		     size_type xnode_id_ct,
		     size_type xnodes_per_element,
		     size_type xnode_ct);

  ///
  /// Parameter xstart_id is the id given to the first node id generated.
  /// Mostly only useful for creating 1 (vs 0) based node numbering.
  ///
  //*/
  block_connectivity(pod_index_type xstart_id);

  ///
  /// The number of elements.
  ///
  size_type _element_ct;

  ///
  /// The number of distinct nodes.
  ///
  size_type _node_ct;

  ///
  /// the number of entyries in _node_ids.
  ///
  size_type _node_id_ct;

  ///
  ///  The nodal connectivity array.
  ///
  pod_index_type* _node_ids;

  ///
  /// True if destructor of this should delete _node_ids.
  ///
  bool _delete_node_ids;

  ///
  ///  The number of nodes per element.
  ///
  size_type _nodes_per_element;

  ///
  /// The id given to the first node id generated.
  /// Mostly only useful for creating 1 (vs 0) based node numbering.
  ///
  pod_index_type _start_id;

private:

  //@}

  // ===========================================================
  /// @name BLOCK_RELATION FACET
  // ===========================================================
  //@{

public:

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
  virtual block_connectivity* clone() const = 0;

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


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
///  Print block_connectivity instance xconn to stream xos.
///
SHEAF_DLL_SPEC 
ostream& operator << (ostream& xos, const block_connectivity& xconn);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle

#endif // ifndef BLOCK_CONNECTIVITY_H
