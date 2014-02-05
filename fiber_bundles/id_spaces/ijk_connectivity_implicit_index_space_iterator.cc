
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
/// Implementation for class ijk_connectivity_implicit_index_space_iterator

#include "ijk_connectivity_implicit_index_space_iterator.h"

#include "assert_contract.h"
#include "ijk_connectivity_index_space_interval.h"
#include "index_space_family.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// IJK_CONNECTIVITY_IMPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
ijk_connectivity_implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
ijk_connectivity_implicit_index_space_iterator(const ijk_connectivity_implicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
ijk_connectivity_implicit_index_space_iterator(const index_space_family& xid_spaces,
					       pod_type xindex)
{
  // Preconditions:

  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  attach_to(xid_spaces, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
ijk_connectivity_implicit_index_space_iterator(const index_space_family& xid_spaces,
					       const std::string& xname)
{
  // Preconditions:

  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xname);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator&
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
operator=(const ijk_connectivity_implicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _hub_begin = xother._hub_begin;
    _k_vertex_size = xother._k_vertex_size;
    _jk_vertex_size = xother._jk_vertex_size;

    (void) implicit_index_space_iterator::operator=(xother);
  }
  else
  {
    detach();
  }

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
~ijk_connectivity_implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator::pod_type
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
hub_begin() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _hub_begin;
}

sheaf::size_type
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
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
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
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

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IMPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::ijk_connectivity_implicit_index_space_iterator&
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ijk_connectivity_implicit_index_space_iterator& lother =
    dynamic_cast<const ijk_connectivity_implicit_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = implicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const ijk_connectivity_implicit_index_space_iterator& lother =
      dynamic_cast<const ijk_connectivity_implicit_index_space_iterator&>(xother);

    result = result && (_hub_begin == lother._hub_begin);
    result = result && (_k_vertex_size == lother._k_vertex_size);
    result = result && (_jk_vertex_size == lother._jk_vertex_size);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

fiber_bundle::ijk_connectivity_implicit_index_space_iterator*
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
clone() const
{
  ijk_connectivity_implicit_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new ijk_connectivity_implicit_index_space_iterator(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  switch(_pod)
  {
    case 0:
    {
      // Increment to vertex (i+1, j, k) = _hub_pod + _jk_vertex_size

      _pod++;
      _hub_pod += _jk_vertex_size;
      break;
    }
    case 1:
    {
      // Increment to vertex (i+1, j+1, k) = _hub_pod + _k_vertex_size

      _pod++;
      _hub_pod += _k_vertex_size;
      break;
    }
    case 2:
    {
      // Increment to vertex (i, j+1, k) = _hub_pod - _jk_vertex_size

      _pod++;
      _hub_pod -= _jk_vertex_size;
      break;
    }
    case 3:
    {
      // Increment to vertex (i, j, k+1) = _hub_begin + 1

      _pod++;
      _hub_pod = _hub_begin + 1;
      break;
    }
    case 4:
    {
      // Increment to vertex (i+1, j, k+1) = _hub_pod + _jk_vertex_size

      _pod++;
      _hub_pod += _jk_vertex_size;
      break;
    }
    case 5:
    {
      // Increment to vertex (i+1, j+1, k+1) = _hub_pod + _k_vertex_size

      _pod++;
      _hub_pod += _k_vertex_size;
      break;
    }
    case 6:
    {
      // Increment to vertex (i, j+1, k+1) = _hub_pod - _jk_vertex_size

      _pod++;
      _hub_pod -= _jk_vertex_size;
      break;
    }
    default:
    {
      // The iteration is done.

      assertion(pod() == 7);

      invalidate_ids();
      break;
    }
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() != old_pod);
  ensure(is_done() || hub_pod() != old_hub_pod);

  // Exit:

  return;
}

void
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_done = false;

  // Reset to vertex (i, j, k)

  _pod = 0;
  _hub_pod = _hub_begin;
    
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  // Assign the state information.

  _host     = &xhost;
  _local_id = xlocal_id;

  // Find the section of the ijk_connectivity that represents this id space.

  const ijk_connectivity_index_space_interval* lhost =
    reinterpret_cast<const ijk_connectivity_index_space_interval*>(_host);

  _hub_begin = lhost->vertex_hub_begin(xlocal_id);
  _k_vertex_size = lhost->k_vertex_size();
  _jk_vertex_size = lhost->jk_vertex_size();

  // Reset the iterator.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

bool
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<const ijk_connectivity_index_space_interval*>(&xhost) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const ijk_connectivity_implicit_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::ijk_connectivity_implicit_index_space_iterator::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(implicit_index_space_iterator::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

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

