//

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Implementation for class block_adjacency

#include "block_adjacency.h"

#include "assert_contract.h"
#include "block_connectivity.h"
#include "std_iomanip.h"

using namespace fiber_bundle;

// ===========================================================
// BLOCK_ADJACENCY FACET
// ===========================================================

///
fiber_bundle::block_adjacency::
block_adjacency()
{

  // Preconditions:


  // Body:

  _node_ct = 0;
  _zone_ct = 0;

  _element_type = CELL_TYPE_END;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
fiber_bundle::block_adjacency::
block_adjacency(const block_adjacency& xother)
{

  // Preconditions:


  // Body:

  _adj = xother._adj;
  _node_ct = xother._node_ct;
  _zone_ct = xother._zone_ct;
  _element_type = xother._element_type;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::block_adjacency::
block_adjacency(const block_connectivity& xconn)
{
  // Preconditions:


  // Body:

  put_connectivity(xconn);

  // Postconditions:


  // Exit:

  return;
}

#ifndef DOXYGEN_SKIP_TYPEDEF_MAPPING
///
fiber_bundle::block_adjacency::
block_adjacency(size_type xzone_ct,
                size_type xnodes_per_zone,
                size_type xnode_ids_ct,
                const pod_index_type* xnode_ids,
                cell_type xelement_type)
{
  // Preconditions:

  require(xnode_ids_ct == xzone_ct*xnodes_per_zone);

  // Body:

  _element_type = xelement_type;
  put_connectivity(xzone_ct, xnodes_per_zone, xnode_ids_ct, xnode_ids);

  // Postconditions:

  ensure(element_type() == xelement_type);
  ensure(zone_ct() == xzone_ct);

  // Exit:

  return;
}
#endif // ifndef DOXYGEN_SKIP_TYPEDEF_MAPPING

///
fiber_bundle::block_adjacency::
~block_adjacency()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::block_adjacency::
put_connectivity(const block_connectivity& xconn)
{
  // Preconditions:


  // Body:

  _element_type = xconn.element_type();

  size_type lzone_ct = xconn.element_ct();
  size_type lnodes_per_zone = xconn.nodes_per_element();
  size_type lnode_ids_ct = xconn.node_id_ct();
  const pod_index_type* lnode_ids = xconn.node_ids();

  put_connectivity(lzone_ct, lnodes_per_zone, lnode_ids_ct, lnode_ids);

  // Postconditions:

  ensure(element_type() == xconn.element_type());
  ensure(zone_ct() == xconn.element_ct());

  // Exit:

  return;
}

///
void
fiber_bundle::block_adjacency::
put_connectivity(size_type xzone_ct,
                 size_type xnodes_per_zone,
                 size_type xnode_ids_ct,
                 const pod_index_type* xnode_ids)
{
  // Preconditions:

  require(xnode_ids_ct == xzone_ct*xnodes_per_zone);

  // Body:

  _zone_ct = xzone_ct;

  // Transpose the connectivity to form the adjacency.

  _adj.clear();
  size_type k = 0;

  for(size_type i=0; i<xzone_ct; ++i)
  {
    for(size_type j=0; j<xnodes_per_zone; ++j)
    {
      assertion(k < xnode_ids_ct);
      pod_index_type lvertex = xnode_ids[k++];

      _adj[lvertex].push_front(i);
    }
  }

  // Store node ct directly because
  // STL only ensures size() performance O(n).

  _node_ct = _adj.size();


#ifdef DIAGNOSTIC_OUTPUT

  cout << *this << endl;
#endif


  // Postconditions:

  ensure(zone_ct() == xzone_ct);

  // Exit:

  return;
}

///
fiber_bundle::block_adjacency&
fiber_bundle::block_adjacency::
operator=(const block_connectivity& xconn)
{
  // Preconditions:


  // Body:

  put_connectivity(xconn);

  // Postconditions:


  // Exit:

  return *this;
}

///
fiber_bundle::block_adjacency::node_iterator_type
fiber_bundle::block_adjacency::
begin()
{
  return _adj.begin();
}

///
fiber_bundle::block_adjacency::const_node_iterator_type
fiber_bundle::block_adjacency::
begin() const
{
  return _adj.begin();
}

///
fiber_bundle::block_adjacency::node_iterator_type
fiber_bundle::block_adjacency::
end()
{
  return _adj.end();
}

///
fiber_bundle::block_adjacency::const_node_iterator_type
fiber_bundle::block_adjacency::
end() const
{
  return _adj.end();
}

///
sheaf::size_type
fiber_bundle::block_adjacency::
node_ct() const
{
  return _node_ct;
}

///
sheaf::size_type
fiber_bundle::block_adjacency::
zone_ct() const
{
  return _zone_ct;
}


// ===========================================================
// BLOCK_RELATION FACET
// ===========================================================

///
fiber_bundle::block_relation::cell_type
fiber_bundle::block_adjacency::
element_type() const
{
  return _element_type;
}

// ===========================================================
// ANY FACET
// ===========================================================


///
bool
fiber_bundle::block_adjacency::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const block_adjacency*>(other) != 0;

  // Postconditions:

  return result;
}

///
fiber_bundle::block_adjacency*
fiber_bundle::block_adjacency::
clone() const
{
  block_adjacency* result;

  // Preconditions:

  // Body:

  result = new block_adjacency();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::block_adjacency&
fiber_bundle::block_adjacency::
operator=(const block_adjacency& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fiber_bundle::block_adjacency::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(block_relation::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

///
ostream&
fiber_bundle::
operator<<(ostream& xos, const fiber_bundle::block_adjacency& xadj)
{
  // Preconditions:


  // Body:

  typedef fiber_bundle::block_adjacency::const_node_iterator_type node_itr_type;
  typedef fiber_bundle::block_adjacency::const_zone_iterator_type zone_itr_type;

  for(node_itr_type v = xadj.begin(); v != xadj.end(); ++v)
  {
    cout << " node: " << setw(4) << v->first << "  zones: ";
    for(zone_itr_type z = v->second.begin(); z != v->second.end(); ++z)
    {
      cout << setw(4) << *z;
    }
  }
  cout << endl;

  // Postconditions:


  // Exit:

  return xos;
}
