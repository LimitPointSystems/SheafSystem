
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

/// @file
/// Implementation for class ij_adjacency_implicit_index_space_iterator

#include "ij_adjacency_implicit_index_space_iterator.h"

#include "assert_contract.h"
#include "ij_adjacency_index_space_interval.h"
#include "index_space_family.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// IJ_ADJACENCY_IMPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::ij_adjacency_implicit_index_space_iterator::
ij_adjacency_implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

fiber_bundle::ij_adjacency_implicit_index_space_iterator::
ij_adjacency_implicit_index_space_iterator(const ij_adjacency_implicit_index_space_iterator& xother)
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

fiber_bundle::ij_adjacency_implicit_index_space_iterator::
ij_adjacency_implicit_index_space_iterator(const index_space_family& xid_spaces,
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

fiber_bundle::ij_adjacency_implicit_index_space_iterator::
ij_adjacency_implicit_index_space_iterator(const index_space_family& xid_spaces,
					   const string& xname)
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

fiber_bundle::ij_adjacency_implicit_index_space_iterator&
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
operator=(const ij_adjacency_implicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _hub_begin = xother._hub_begin;
    _j_size = xother._j_size;
    _i_ct = xother._i_ct;
    _j_ct = xother._j_ct;
    _i = xother._i;
    _j = xother._j;

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

fiber_bundle::ij_adjacency_implicit_index_space_iterator::
~ij_adjacency_implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::ij_adjacency_implicit_index_space_iterator::pod_type
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
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
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
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
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
i_ct() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _i_ct;
}

sheaf::size_type
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
j_ct() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _j_ct;
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

fiber_bundle::ij_adjacency_implicit_index_space_iterator&
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ij_adjacency_implicit_index_space_iterator& lother =
    dynamic_cast<const ij_adjacency_implicit_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = implicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const ij_adjacency_implicit_index_space_iterator& lother =
      dynamic_cast<const ij_adjacency_implicit_index_space_iterator&>(xother);

    result = result && (_hub_begin == lother._hub_begin);
    result = result && (_j_size == lother._j_size);
    result = result && (_i_ct == lother._i_ct);
    result = result && (_j_ct == lother._j_ct);
    result = result && (_i == lother._i);
    result = result && (_j == lother._j);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

fiber_bundle::ij_adjacency_implicit_index_space_iterator*
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
clone() const
{
  ij_adjacency_implicit_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new ij_adjacency_implicit_index_space_iterator(*this);

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
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Increment to the next id.

  _j++;
  if(_j == _j_ct)
  {
    // Done with the j-iteration, try incrementing in the i-direction.

    _j = 0;
    _i++;

    if(_i == _i_ct)
    {
      // The iteration is done.

      invalidate_ids();
    }
    else
    {
      // The iteration is not done, increment the ids in the i-direction.

      ++_pod;
      _hub_pod = (_i * _j_size) + _hub_begin;
    }
  }
  else
  {
    // The iteration is not done, increment the ids in the j-direction.

    ++_pod;
    ++_hub_pod;
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() != old_pod);
  ensure(is_done() || hub_pod() != old_hub_pod);

  // Exit:

  return;
}

void
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_done = false;

  // Reset to first adjacent zone.

  _pod = 0;
  _hub_pod = _hub_begin;
    
  _i = 0;
  _j = 0;

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
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  // Assign the state information.

  _host     = &xhost;
  _local_id = xlocal_id;

  // Find the section of the ij_adjacency that represents this id space.

  const ij_adjacency_index_space_interval* lhost =
    reinterpret_cast<const ij_adjacency_index_space_interval*>(_host);

  lhost->adjacent_zones(xlocal_id, _hub_begin, _i_ct, _j_ct);
  _j_size = lhost->j_size();

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
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<const ij_adjacency_index_space_interval*>(&xhost) != 0);

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
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const ij_adjacency_implicit_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::ij_adjacency_implicit_index_space_iterator::
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


