
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
/// Implementation for class ijk_connectivity_index_space_interval

#include "ComLimitPoint/fiber_bundle/ijk_connectivity_index_space_interval.h"

#include "ComLimitPoint/sheaf/abstract_product_structure.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/ijk_connectivity_implicit_index_space_iterator.h"
#include "ComLimitPoint/sheaf/ijk_product_structure.h"
#include "ComLimitPoint/sheaf/forwarding_index_space_handle.h"
#include "ComLimitPoint/sheaf/explicit_index_space_state.h"
#include "ComLimitPoint/sheaf/hub_index_space_handle.h"
#include "ComLimitPoint/sheaf/index_space_family.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::ijk_connectivity_index_space_interval&
fiber_bundle::ijk_connectivity_index_space_interval::
new_space(index_space_family& xid_spaces,
	  size_type xub,
	  pod_type xvertex_hub_begin,
	  size_type xj_size,
	  size_type xk_size)
{
  // Preconditions:

  require(xub > 0);
  require(xid_spaces.hub_id_space().contains(xvertex_hub_begin));
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  define_old_variable(size_type old_id_spaces_end = xid_spaces.end());

  ijk_connectivity_index_space_interval* result_ptr = new ijk_connectivity_index_space_interval();
  result_ptr->new_state(xid_spaces, xub);

  result_ptr->_vertex_hub_begin = xvertex_hub_begin;
  result_ptr->_j_size = xj_size;
  result_ptr->_k_size = xk_size;

  result_ptr->_j_vertex_size = result_ptr->_j_size+1;
  result_ptr->_k_vertex_size = result_ptr->_k_size+1;

  result_ptr->_jk_vertex_size = result_ptr->_j_vertex_size * result_ptr->_k_vertex_size;

  const ijk_connectivity_index_space_interval& result = *result_ptr;

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(result.begin() == old_id_spaces_end);
  ensure(result.end() == xid_spaces.end());
  ensure(result.end() == result.begin() + xub);

  ensure(result.vertex_hub_begin() == xvertex_hub_begin);
  ensure(result.j_size() == xj_size);
  ensure(result.k_size() == xk_size);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IJK_CONNECTIVITY_INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::ijk_connectivity_index_space_interval::
~ijk_connectivity_index_space_interval()
{  
  // Preconditions:
    
  // Body:

  // Nothing to do.
  
  // Postconditions:

  // Exit:

  return; 
}

fiber_bundle::ijk_connectivity_index_space_interval::pod_type
fiber_bundle::ijk_connectivity_index_space_interval::
vertex_hub_begin() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _vertex_hub_begin;
}

fiber_bundle::ijk_connectivity_index_space_interval::pod_type
fiber_bundle::ijk_connectivity_index_space_interval::
vertex_hub_begin(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  // xlocal_id is the zone id, compute the i, j, k indices.

  pod_type i, j, k;
  sheaf::tuple(xlocal_id, _j_size, _k_size, i, j, k);

  // Compute the vertex id.

  pod_type result =
    ordinal(i, j, k, _j_vertex_size, _k_vertex_size) + _vertex_hub_begin;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
j_size() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _j_size;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
k_size() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _k_size;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
j_vertex_size() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _j_vertex_size;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
k_vertex_size() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _k_vertex_size;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
jk_vertex_size() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _jk_vertex_size;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::ijk_connectivity_index_space_interval::
ijk_connectivity_index_space_interval()
  : index_space_interval()
{
  // Preconditions:
    
  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::ijk_connectivity_index_space_interval::
class_name() const
{
  static const string result("ijk_connectivity_index_space_interval");
  return result;
}

fiber_bundle::ijk_connectivity_index_space_interval*
fiber_bundle::ijk_connectivity_index_space_interval::
clone() const
{
  // Preconditions:

  // Body:

  ijk_connectivity_index_space_interval* result =
    new ijk_connectivity_index_space_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::ijk_connectivity_index_space_interval::
make_prototype()
{
  // Preconditions:

  // Body:

  ijk_connectivity_index_space_interval* lproto = new ijk_connectivity_index_space_interval();

  id_space_interval_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::ijk_connectivity_index_space_interval::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ijk_connectivity_index_space_interval& lother =
    dynamic_cast<const ijk_connectivity_index_space_interval&>(xother);

  bool result = index_space_interval::operator==(xother);

  result = result && (_vertex_hub_begin == lother._vertex_hub_begin);
  result = result && (_j_size == lother._j_size);
  result = result && (_k_size == lother._k_size);
  result = result && (_j_vertex_size == lother._j_vertex_size);
  result = result && (_k_vertex_size == lother._k_vertex_size);
  result = result && (_jk_vertex_size == lother._jk_vertex_size);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = fiber_bundle::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::ijk_connectivity_index_space_interval&
fiber_bundle::ijk_connectivity_index_space_interval::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ijk_connectivity_index_space_interval& lother =
    dynamic_cast<const ijk_connectivity_index_space_interval&>(xother);

  _vertex_hub_begin = lother._vertex_hub_begin;
  _j_size = lother._j_size;
  _k_size = lother._k_size;
  _j_vertex_size = lother._j_vertex_size;
  _k_vertex_size = lother._k_vertex_size;
  _jk_vertex_size = lother._jk_vertex_size;

  index_space_interval::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
fiber_bundle::ijk_connectivity_index_space_interval::
explicit_state(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  /// @todo Check to see if there is an override.

  explicit_index_space_state* result = 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::ijk_connectivity_index_space_interval::
remove(pod_type xlocal_id)
{
  // Preconditions:

  // Body:

  /// @todo Remove or implement.

  not_implemented();
  
  // Postconditions:

  ensure(!contains(xlocal_id));

  // Exit:

  return;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_index_space_interval::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = 8;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::ijk_connectivity_index_space_interval::
begin(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::ijk_connectivity_index_space_interval::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 8;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (0 <= xid) && (xid < 8);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result;
  pod_type loffset = xid - vertex_hub_begin(xlocal_id);

  if(loffset >= _jk_vertex_size)
  {
    // i+1.

    loffset -= _jk_vertex_size;
    if(loffset >= _k_vertex_size)
    {
      // i+1, j+1.

      loffset -= _k_vertex_size;
      result = ((0 <= loffset) && (loffset < 2));
    }
    else
    {
      // i+1, j.

      result = ((0 <= loffset) && (loffset < 2));
    }
  }
  else
  {
    // i.

    if(loffset >= _k_vertex_size)
    {
      // i, j+1.

      loffset -= _k_vertex_size;
      result = ((0 <= loffset) && (loffset < 2));
    }
    else
    {
      // i, j

      result = ((0 <= loffset) && (loffset < 2));
    }
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = is_valid(xhub_id) && (hub_pod(xlocal_id, xid) == xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::ijk_connectivity_index_space_interval::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result;
  pod_type loffset = xid - vertex_hub_begin(xlocal_id);

  if(loffset >= _jk_vertex_size)
  {
    // i+1.

    loffset -= _jk_vertex_size;
    if(loffset >= _k_vertex_size)
    {
      // i+1, j+1.

      loffset -= _k_vertex_size;
      if(loffset == 0)
      {
	// Vertex (i+1, j+1, k)

	result = 2;
      }
      else if(loffset == 1)
      {
	// Vertex (i+1, j+1, k+1)

	result = 6;
      }
      else
      {
	// Not a valid range id.

	result = invalid_pod_index();
      }
    }
    else
    {
      // i+1, j.

      if(loffset == 0)
      {
	// Vertex (i+1, j, k)

	result = 1;
      }
      else if(loffset == 1)
      {
	// Vertex (i+1, j, k+1)

	result = 5;
      }
      else
      {
	// Not a valid range id.

	result = invalid_pod_index();
      }
    }
  }
  else
  {
    // i.

    if(loffset >= _k_vertex_size)
    {
      // i, j+1.

      loffset -= _k_vertex_size;
      if(loffset == 0)
      {
	// Vertex (i, j+1, k)

	result = 3;
      }
      else if(loffset == 1)
      {
	// Vertex (i, j+1, k+1)

	result = 7;
      }
      else
      {
	// Not a valid range id.
    
	result = invalid_pod_index();
      }
    }
    else
    {
      // i, j

      if(loffset == 0)
      {
	// Vertex (i, j, k)

	result = 0;
      }
      else if(loffset == 1)
      {
	// Vertex (i, j, k+1)

	result = 4;
      }
      else
      {
	// Not a valid range id.

	result = invalid_pod_index();
      }
    }
  }

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::ijk_connectivity_index_space_interval::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = vertex_hub_begin(xlocal_id);

  switch(xid)
  {
    case 0:
    {
      // vertex (0, 0, 0)

      break;
    }
    case 1:
    {
      // vertex (1, 0, 0)

      result += _jk_vertex_size;
      break;
    }
    case 2:
    {
      // vertex(1, 1, 0)

      result += _jk_vertex_size + _k_vertex_size;
      break;
    }
    case 3:
    {
      // vertex(0, 1, 0)

      result += _k_vertex_size;
      break;
    }
    case 4:
    {
      // vertex(0, 0, 1)

      result += 1;
      break;
    }
    case 5:
    {
      // vertex(1, 0, 1)

      result += _jk_vertex_size + 1;
      break;
    }
    case 6:
    {
      // vertex(1, 1, 1)

      result += _jk_vertex_size + _k_vertex_size + 1;
      break;
    }
    case 7:
    {
      // vertex(0, 1, 1)

      result += _k_vertex_size + 1;
      break;
    }
    default:
    {
      result = invalid_pod_index();
      break;
    }
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
is_persistent(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::ijk_connectivity_index_space_interval::
new_product_structure(pod_type xlocal_id,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  /// @todo Implement.

  not_implemented();

  // Postconditions:

  ensure(has_product_structure(xlocal_id));

  // Exit:

  return;
}

void
fiber_bundle::ijk_connectivity_index_space_interval::
delete_product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  /// @todo Implement.

  not_implemented();
  
  // Postconditions:

  ensure(!has_product_structure(xlocal_id));

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
fiber_bundle::ijk_connectivity_index_space_interval::
product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  /// @todo Implement.

  const abstract_product_structure* result = 0; // Just to silence compiler warnings.

  not_implemented();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

sheaf::abstract_product_structure&
fiber_bundle::ijk_connectivity_index_space_interval::
product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  /// @todo Implement.

  abstract_product_structure* result = 0; // Just to silence compiler warnings.

  not_implemented();
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
has_product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  /// @todo Implement.

  bool result = false; // Just to silence compiler warnings.

  not_implemented();
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_handle&
fiber_bundle::ijk_connectivity_index_space_interval::
get_id_space(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_handle& result = _handles.get();
  result.attach_to(*this, xlocal_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::ijk_connectivity_index_space_interval::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  _handles.release(reinterpret_cast<forwarding_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const forwarding_index_space_handle* lid_space =
    dynamic_cast<const forwarding_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && _handles.allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator&
fiber_bundle::ijk_connectivity_index_space_interval::
get_id_space_iterator(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_iterator& result = _iterators.get();
  result.attach_to(*this, xlocal_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::ijk_connectivity_index_space_interval::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  _iterators.release(reinterpret_cast<ijk_connectivity_implicit_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const ijk_connectivity_implicit_index_space_iterator* litr =
    dynamic_cast<const ijk_connectivity_implicit_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && _iterators.allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::ijk_connectivity_index_space_interval::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const ijk_connectivity_index_space_interval*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::ijk_connectivity_index_space_interval::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_interval::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
size_t
fiber_bundle::
deep_size(const ijk_connectivity_index_space_interval& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add contributions for _handles.

  result += deep_size(xn._handles, false);
  
  // Add contributions for _iterators.

  result += deep_size(xn._iterators, false);
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
