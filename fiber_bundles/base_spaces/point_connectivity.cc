
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

// Implementation for class point_connectivity

#include "assert_contract.h"
#include "point_connectivity.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// ===========================================================
// POINT_CONNECTIVITY FACET
// ===========================================================

fiber_bundle::point_connectivity::
point_connectivity()
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

fiber_bundle::point_connectivity::
point_connectivity(const point_connectivity& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(postcondition_of(block_connectivity(xother)));
}

fiber_bundle::point_connectivity::
point_connectivity(size_type xi_size, pod_index_type xstart_id)
    : block_connectivity(xstart_id)
{

  // Preconditions:

  // Body:

  create_connectivity(xi_size, xstart_id);

  // Postconditions:

  ensure(element_ct() == xi_size);
  ensure(node_ct() == xi_size);
  ensure(node_id_ct() == element_ct() * NODES_PER_ELEMENT);
  ensure(node_ids() != 0);
  ensure(delete_node_ids());
  ensure(nodes_per_element() == NODES_PER_ELEMENT);
  ensure(start_id() == xstart_id);
  ensure(node_ids()[0] == xstart_id);
}

fiber_bundle::point_connectivity::
~point_connectivity()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

void
fiber_bundle::point_connectivity::
create_connectivity(size_type xi_size, pod_index_type xstart_id)
{
  // Preconditions:

  require(xi_size > 0);

  // Body:

  _element_ct = xi_size;
  _node_ct = xi_size;
  _node_id_ct = _element_ct * NODES_PER_ELEMENT;
  _node_ids = new pod_index_type[_node_id_ct];
  _delete_node_ids = true;
  _nodes_per_element = NODES_PER_ELEMENT;
  _start_id = xstart_id;

  size_type index = 0;

  for(size_type i=0; i<xi_size; ++i)
  {
    _node_ids[i] = i + _start_id;
  }

  // Postconditions:
  ensure(element_ct() == xi_size);
  ensure(node_ct() == xi_size);
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
fiber_bundle::point_connectivity::
element_type() const
{
  return POINT;
}


// ===========================================================
// ANY FACET
// ===========================================================

fiber_bundle::point_connectivity*
fiber_bundle::point_connectivity::
clone() const
{
  point_connectivity* result;

  // Preconditions:


  // Body:

  result = new point_connectivity();

  // Postconditions:

  ensure(result->is_same_type(this));

  // Exit:

  return result;
}

bool
fiber_bundle::point_connectivity::
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
fiber_bundle::point_connectivity::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const point_connectivity*>(other) != 0;

  // Postconditions:

  return result;
}
