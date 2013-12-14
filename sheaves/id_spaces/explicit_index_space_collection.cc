
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
/// Implementation for class explicit_index_space_collection

#include "abstract_product_structure.h"
#include "explicit_index_space_collection.h"
#include "assert_contract.h"
#include "explicit_index_space_state.h"
#include "hub_index_space_handle.h"
#include "index_space_iterator.h"

// ===========================================================
// EXPLICIT_INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_index_space_collection::
~explicit_index_space_collection()
{  
  // Preconditions:
    
  // Body:

  map_type::iterator itr = _states.begin();
  while(itr != _states.end())
  {
    explicit_index_space_state* lstate = itr->second;
    ++itr;
    delete lstate;
  }
  
  // Postconditions:

  // Exit:

  return; 
}

sheaf::size_type
sheaf::explicit_index_space_collection::
capacity() const
{
  // Preconditions:

  // Body:

  size_type result = (2 * _states.bucket_count());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_collection::
insert(explicit_index_space_state& xid_space)
{
  // Preconditions:

  require(!contains(local_scope(xid_space.index())));

  // Body:

  // Local scope is the same is family scope,
  // no need to convert.

  _states[xid_space.index()] = &xid_space;

  // Postconditions:

  ensure(contains(local_scope(xid_space.index())));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_collection::
explicit_index_space_collection()
  : index_space_collection()
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
// INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::explicit_index_space_collection::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const explicit_index_space_collection& lother =
    dynamic_cast<const explicit_index_space_collection&>(xother);

  /// @error Since we still support tr1 unordered_maps the comparison
  ///        operator may not be supported.  See COM-374.
//   bool result = (_states == lother._states);
//   result = result && (_id_spaces == lother._id_spaces);

  bool result = (_id_spaces == lother._id_spaces);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::explicit_index_space_collection::
contains(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  // Local scope is the same is family scope,
  // no need to convert.

  map_type::const_iterator itr = _states.find(xlocal_id);

  bool result = (itr != _states.end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_collection::
contains_family(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  // Local scope is the same is family scope,
  // no need to convert.

  map_type::const_iterator itr = _states.find(xspace_id);

  bool result = (itr != _states.end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_collection::
local_scope(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  // Local scope is the same is family scope,
  // no need to convert.

  pod_type result = contains(xspace_id) ? xspace_id : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_collection::
family_scope(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  // Local scope is the same is family scope,
  // no need to convert.

  pod_type result = contains(xlocal_id) ? xlocal_id : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains_family(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_collection&
sheaf::explicit_index_space_collection::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const explicit_index_space_collection& lother =
    dynamic_cast<const explicit_index_space_collection&>(xother);

  _states    = lother._states;
  _id_spaces = lother._id_spaces;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_collection::
explicit_state(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  explicit_index_space_state* result =
    contains(xlocal_id) ? _states.find(xlocal_id)->second : 0;

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

const sheaf::index_space_family&
sheaf::explicit_index_space_collection::
id_spaces() const
{
  // Preconditions:

  // Body:

  const index_space_family& result = *_id_spaces;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::explicit_index_space_collection::
id_spaces()
{
  // Preconditions:

  // Body:

  index_space_family& result = *_id_spaces;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_collection::
remove(pod_type xlocal_id)
{
  // Preconditions:

  // Body:

  if(contains(xlocal_id))
  {
    _states.erase(xlocal_id);
  }
  
  // Postconditions:

  ensure(!contains(xlocal_id));

  // Exit:

  return;
}

sheaf::size_type
sheaf::explicit_index_space_collection::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = _states.find(xlocal_id)->second->ct();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_collection::
begin(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states.find(xlocal_id)->second->begin();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_collection::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states.find(xlocal_id)->second->end();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_collection::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states.find(xlocal_id)->second->contains(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_collection::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states.find(xlocal_id)->second->contains_unglued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_collection::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states.find(xlocal_id)->second->contains(xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_collection::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states.find(xlocal_id)->second->pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_collection::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states.find(xlocal_id)->second->unglued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_collection::
is_persistent(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states.find(xlocal_id)->second->is_persistent();

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
sheaf::explicit_index_space_collection::
new_product_structure(pod_type xlocal_id,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  _states.find(xlocal_id)->second->new_product_structure(xproduct);

  // Postconditions:

  ensure(has_product_structure(xlocal_id));

  // Exit:

  return;
}

void
sheaf::explicit_index_space_collection::
delete_product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  _states.find(xlocal_id)->second->delete_product_structure();
  
  // Postconditions:

  ensure(!has_product_structure(xlocal_id));

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::explicit_index_space_collection::
product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  const abstract_product_structure& result =
    _states.find(xlocal_id)->second->product_structure();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::explicit_index_space_collection::
product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  abstract_product_structure& result = 
    _states.find(xlocal_id)->second->product_structure();
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_collection::
has_product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states.find(xlocal_id)->second->has_product_structure();

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
sheaf::explicit_index_space_collection::
get_id_space(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_handle& result =
    _states.find(xlocal_id)->second->get_id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_collection::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  _states.find(local_scope(xid_space.index()))->
    second->release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_collection::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  map_type::const_iterator itr = _states.find(local_scope(xid_space.index()));

  bool result =
    (itr != _states.end()) && itr->second->allocated_id_space(xid_space);

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
sheaf::explicit_index_space_collection::
get_id_space_iterator(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_iterator& result =
    _states.find(xlocal_id)->second->get_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_collection::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  _states.find(local_scope(xitr.index()))->second->release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_collection::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  map_type::const_iterator itr = _states.find(local_scope(xitr.index()));

  bool result =
    (itr != _states.end()) && itr->second->allocated_iterator(xitr);

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
sheaf::explicit_index_space_collection::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const explicit_index_space_collection*>(other) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::explicit_index_space_collection::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_collection::invariant());

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
sheaf::
deep_size(const explicit_index_space_collection& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  /// @todo Add deep size of _states.
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
