
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class quad_connectivity

#include "assert_contract.h"
#include "quad_connectivity.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// ===========================================================
// QUAD_CONNECTIVITY FACET
// ===========================================================

fiber_bundle::quad_connectivity::
quad_connectivity()
    : block_connectivity(0)
{

  // Preconditions:

  // Body:

  _nodes_per_element = NODES_PER_ELEMENT;
  
  // Postconditions:

  ensure(element_ct() == 0);
  ensure(node_ct() == 0);
  ensure(node_id_ct() == 0);
  ensure(node_ids() == 0);
  ensure(!delete_node_ids());
  ensure(nodes_per_element() == NODES_PER_ELEMENT);
  ensure(start_id() == 0);
}

fiber_bundle::quad_connectivity::
quad_connectivity(const quad_connectivity& xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(postcondition_of(block_connectivity(xother)));
}

fiber_bundle::quad_connectivity::
quad_connectivity(const pod_index_type* xnode_ids,
                  size_type xnode_id_ct, 
                  size_type xnode_ct)
  : block_connectivity(xnode_ids, xnode_id_ct, NODES_PER_ELEMENT, xnode_ct)
{

  // Preconditions:

  require(xnode_id_ct > 0);
  require((xnode_id_ct % NODES_PER_ELEMENT) == 0);

  // Body:


  // Postconditions:

  ensure(element_ct() == xnode_id_ct/NODES_PER_ELEMENT);
  ensure(xnode_ct > 0 ? node_ct() == xnode_ct : node_ct() > 0);
  ensure(node_id_ct() == xnode_id_ct);
  ensure(node_ids() == xnode_ids);
  ensure(!delete_node_ids());
  ensure(nodes_per_element() == NODES_PER_ELEMENT);

  // Exit:
}

fiber_bundle::quad_connectivity::
quad_connectivity(size_type xi_size, size_type xj_size, pod_index_type xstart_id)
    : block_connectivity(xstart_id)
{

  // Preconditions:

  // Body:

  create_connectivity(xi_size, xj_size, xstart_id);

  // Postconditions:

  ensure(element_ct() == xi_size*xj_size);
  ensure(node_ct() == (xi_size+1)*(xj_size+1));
  ensure(node_id_ct() == element_ct() * NODES_PER_ELEMENT);
  ensure(node_ids() != 0);
  ensure(delete_node_ids());
  ensure(nodes_per_element() == NODES_PER_ELEMENT);
  ensure(start_id() == xstart_id);
  ensure(node_ids()[0] == xstart_id);
}

fiber_bundle::quad_connectivity::
~quad_connectivity()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

void
fiber_bundle::quad_connectivity::
create_connectivity(size_type xi_size, 
		    size_type xj_size,
		    pod_index_type xstart_id)
{
  
  // Preconditions:

  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  _element_ct = xi_size*xj_size;
  _node_ct = (xi_size+1)*(xj_size+1);
  _node_id_ct = _element_ct * NODES_PER_ELEMENT;
  _node_ids = new pod_index_type[_node_id_ct];
  _delete_node_ids = true;
  _nodes_per_element = NODES_PER_ELEMENT;
  _start_id = xstart_id;


  size_type vertex_ct_j = xj_size+1;

  size_type index = 0;

  for(size_type i=0; i<xi_size; ++i)
  {
    size_type ladd = i*vertex_ct_j + _start_id;

    for(size_type j=0; j<xj_size; ++j)
    {
      pod_index_type n0 = j + ladd;
      pod_index_type n1 = n0 + vertex_ct_j;
      pod_index_type n2 = n1 + 1;
      pod_index_type n3 = n0 + 1;

      _node_ids[index++] = n0;
      _node_ids[index++] = n1;
      _node_ids[index++] = n2;
      _node_ids[index++] = n3;
    }
  }

  // Postconditions:

  ensure(element_ct() == xi_size*xj_size);
  ensure(node_ct() == (xi_size+1)*(xj_size+1));
  ensure(node_id_ct() == element_ct() * NODES_PER_ELEMENT);
  ensure(node_ids() != 0);
  ensure(delete_node_ids());
  ensure(nodes_per_element() == NODES_PER_ELEMENT);
  ensure(start_id() == xstart_id);
  ensure(node_ids()[0] == xstart_id);

}

// ===========================================================
// BLOCK_RELATION FACET
// ===========================================================

fiber_bundle::block_connectivity::cell_type
fiber_bundle::quad_connectivity::
element_type() const
{
  return QUAD;
}

// ===========================================================
// ANY FACET
// ===========================================================

fiber_bundle::quad_connectivity*
fiber_bundle::quad_connectivity::
clone() const
{
  quad_connectivity* result;

  // Preconditions:

  // Body:

  result = new quad_connectivity();

  // Postconditions:

  ensure(result->is_same_type(this));

  // Exit:

  return result;
}

bool
fiber_bundle::quad_connectivity::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(block_connectivity::invariant());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::quad_connectivity::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const quad_connectivity*>(other) != 0;

  // Postconditions:

  return result;
}



