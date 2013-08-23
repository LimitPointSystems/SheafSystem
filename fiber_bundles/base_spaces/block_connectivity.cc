
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

// Implementation for class block_connectivity

#include "assert_contract.h"
#include "block_connectivity.h"
#include "std_limits.h"
#include "std_set.h"

using namespace fiber_bundle;

// ===========================================================
// BLOCK_CONNECTIVITY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::block_connectivity::
~block_connectivity()
{
  // Preconditions:

  // Body:

  if(_delete_node_ids)
  {
    delete [] _node_ids;
  }

  // Postconditions:
}

size_type
fiber_bundle::block_connectivity::
element_ct() const
{
  return _element_ct;
}

size_type
fiber_bundle::block_connectivity::
node_ct() const
{
  return _node_ct;
}

sheaf::pod_index_type*
fiber_bundle::block_connectivity::
node_ids()
{
  return _node_ids;
}

const sheaf::pod_index_type*
fiber_bundle::block_connectivity::
node_ids() const
{
  return _node_ids;
}

bool
fiber_bundle::block_connectivity::
delete_node_ids() const
{
  return _delete_node_ids;
}

sheaf::size_type
fiber_bundle::block_connectivity::
node_id_ct() const
{
  return _node_id_ct;
}

size_type
fiber_bundle::block_connectivity::
nodes_per_element() const
{
  return _nodes_per_element;
}

sheaf::pod_index_type
fiber_bundle::block_connectivity::
start_id() const
{
  return _start_id;
}

void
fiber_bundle::block_connectivity::
to_stream(ostream& os) const
{
  size_type npe = nodes_per_element();
  size_type nid_ct = node_id_ct();
  const pod_index_type* nids = node_ids();

  os << endl;
  for(size_type i=0; i<nid_ct; i+=npe)
  {
    for(size_type j=0; j<npe; ++j)
    {
      os << " " << nids[i+j];
    }

    os << endl;
  }
}

fiber_bundle::block_connectivity&
fiber_bundle::block_connectivity::
operator=(const block_connectivity& xother)
{
  // Preconditions:

  // Body:

  _element_ct = xother._element_ct;
  _node_ct = xother._node_ct;
  _node_id_ct = xother._node_id_ct;  

  if(_delete_node_ids)
  {
    delete [] _node_ids;
  }

  _node_ids = new pod_index_type[xother._node_id_ct];  

  for(pod_index_type i=0; i<_node_id_ct; ++i)
  {
    _node_ids[i] = xother._node_ids[i];
  }

  _delete_node_ids = true;

  _nodes_per_element = xother._nodes_per_element;
  _start_id = xother._start_id;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);
  ensure(node_ids() != xother.node_ids());
  ensure(delete_node_ids());
  

  // Exit:

  return *this;
}



bool
fiber_bundle::block_connectivity::
operator==(const block_connectivity& xother) const
{
  // Preconditions:

  // Body:

  bool result;

  result = (_element_ct == xother._element_ct);
  result = result && (_node_ct == xother._node_ct);
  result = result && (_node_id_ct == xother._node_id_ct);  
  for(pod_index_type i=0; result && (i<_node_id_ct); ++i)
  {
    result = result && (_node_ids[i] == xother._node_ids[i]);
  }

  result = result && (_nodes_per_element == xother._nodes_per_element);
  result = result && (_start_id == xother._start_id);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS


fiber_bundle::block_connectivity::
block_connectivity()
{

  // Preconditions:

  // Body:

  _element_ct = 0;
  _node_ct = 0;
  _node_ids = 0;
  _delete_node_ids = false;
  _node_id_ct = 0;
  _nodes_per_element = 0;
  _start_id = 0;

  // Postconditions:

  ensure(element_ct() == 0);
  ensure(node_ct() == 0);
  ensure(node_ids() == 0);
  ensure(!delete_node_ids());
  ensure(node_id_ct() == 0);
  ensure(nodes_per_element() == 0);
  ensure(start_id() == 0);



}

fiber_bundle::block_connectivity::
block_connectivity(const block_connectivity& xother)
{

  // Preconditions:

  // Body:

  _element_ct = 0;
  _node_ct = 0;
  _node_ids = 0;
  _delete_node_ids = false;
  _node_id_ct = 0;
  _nodes_per_element = 0;
  _start_id = 0;

  (*this) == xother;
  
  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return;
}

fiber_bundle::block_connectivity::
block_connectivity(const pod_index_type* xnode_ids, 
		   size_type xnode_id_ct, 
		   size_type xnodes_per_element, 
		   size_type xnode_ct)
{

  // Preconditions:

  require(xnode_ids != 0);
  require(xnode_id_ct > 0);
  require(xnodes_per_element > 0);

  // Body:

  _element_ct = xnode_id_ct/xnodes_per_element;

  pod_index_type lstart_id = numeric_limits<pod_index_type>::max();
  if(xnode_ct > 0)
  {
    for(size_type i=0; i<xnode_id_ct; ++i)
    {
      pod_index_type lnode_id = xnode_ids[i];
      lstart_id = (lnode_id < lstart_id) ? lnode_id : lstart_id;
    }
    _node_ct = xnode_ct;
  }
  else
  {
    set<pod_index_type> lnodes;
    for(size_type i=0; i<xnode_id_ct; ++i)
    {
      pod_index_type lnode_id = xnode_ids[i];
      lstart_id = (lnode_id < lstart_id) ? lnode_id : lstart_id;
      lnodes.insert(lnode_id);
    }
    _node_ct = lnodes.size();
  }
  
  _node_ids = const_cast<pod_index_type*>(xnode_ids);
  _delete_node_ids = false;
  _node_id_ct = xnode_id_ct;
  _nodes_per_element = xnodes_per_element;
  _start_id = lstart_id;
  
  // Postconditions:

  ensure(element_ct() == xnode_id_ct/xnodes_per_element);
  ensure(xnode_ct > 0 ? node_ct() == xnode_ct : node_ct() > 0);
  ensure(node_ids() == xnode_ids);
  ensure(!delete_node_ids());
  ensure(node_id_ct() == xnode_id_ct);
  ensure(nodes_per_element() == xnodes_per_element);

}

fiber_bundle::block_connectivity::
block_connectivity(pod_index_type xstart_id)
{

  // Preconditions:

  // Body:

  _element_ct = 0;
  _node_ct = 0;
  _node_ids = 0;
  _delete_node_ids = false;
  _node_id_ct = 0;
  _nodes_per_element = 0;
  _start_id = xstart_id;

  // Postconditions:

  ensure(node_ids() == 0);
  ensure(!delete_node_ids());
  ensure(node_id_ct() == 0);
  ensure(start_id() == xstart_id);

}

// ===========================================================
// ANY FACET
// ===========================================================

bool
fiber_bundle::block_connectivity::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(block_relation::invariant());

    // Can't delete node ids if they haven't been allocated.

    invariance(delete_node_ids() ? node_ids() != 0 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::block_connectivity::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const block_connectivity*>(other) != 0;

  // Postconditions:

  return result;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================


ostream&
fiber_bundle::
operator << (ostream& xos, const fiber_bundle::block_connectivity& xconn)
{

  xconn.to_stream(xos);

  return xos;
}
