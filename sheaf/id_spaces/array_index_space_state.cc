
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
/// Implementation for class array_index_space_state

#include "ComLimitPoint/sheaf/array_index_space_state.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/array_index_space_handle.h"
#include "ComLimitPoint/sheaf/array_index_space_iterator.h"
#include "ComLimitPoint/sheaf/deep_size.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/hub_index_space_handle.h"

using namespace std;
using namespace unordered;

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::array_index_space_handle
sheaf::array_index_space_state::
new_space(index_space_family& xid_spaces,
	  const std::string& xname,
	  bool xis_persistent,
	  size_type xcapacity)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));
  require(xcapacity >= 0);

  // Body:

  array_index_space_state* lstate = new array_index_space_state();
  lstate->new_state(xid_spaces, xname, xis_persistent);

  lstate->reserve(xcapacity);

  array_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.is_persistent() == xis_persistent);
  ensure(result.name() == xname);

  ensure(result.capacity() >= xcapacity);

  // Exit:

  return result;
}

sheaf::array_index_space_handle
sheaf::array_index_space_state::
new_space(index_space_family& xid_spaces,
	  pod_index_type xid,
	  const std::string& xname,
	  bool xis_persistent,
	  size_type xcapacity)
{
  // Preconditions:

  require(!xid_spaces.contains(xid));
  require(xid_spaces.is_explicit_interval(xid));
  require(!xname.empty());
  require(!xid_spaces.contains(xname));
  require(xcapacity >= 0);

  // Body:

  array_index_space_state* lstate = new array_index_space_state();
  lstate->new_state(xid_spaces, xid, xname, xis_persistent);

  lstate->reserve(xcapacity);

  array_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.index() == xid);
  ensure(result.is_persistent() == xis_persistent);
  ensure(result.name() == xname);

  ensure(result.capacity() >= xcapacity);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ARRAY_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::array_index_space_state::
array_index_space_state()
  : mutable_index_space_state()
{
  // Preconditions:
    
  // Body:
  
  reserve(0);

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  ensure(capacity() >= 0);

  // Exit:

  return; 
}

sheaf::array_index_space_state::
~array_index_space_state()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MUTABLE INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::array_index_space_state::
update_extrema()
{
  // Preconditions:

  // Body:

  if(_ct >= 1)
  {
    to_domain_type::const_iterator itr = _to_domain.begin();

    // Initialize values to the first entry.

    _begin = itr->second;
    _end = itr->second + 1;

    ++itr; // Increment iterator to the second entry.

    while(itr != _to_domain.end())
    {
      update_extrema(itr->second);
      
      ++itr;
    }
  }
  else
  {
    assertion(is_empty());

    invalidate_extrema();
  }

  // Postconditions:

  // Exit

  return;
}

void
sheaf::array_index_space_state::
reserve(size_type xcapacity)
{
  // Preconditions:

  // Body:

  if(xcapacity > capacity())
  {
    _to_range.reserve(xcapacity);
    _to_domain.rehash(xcapacity / 2);
  }

  // Postconditions:

  ensure(invariant());
  ensure(capacity() >= xcapacity);

  // Exit:

  return;
}

sheaf::size_type
sheaf::array_index_space_state::
capacity() const
{
  // Preconditions:

  // Body:

  size_type result = _to_range.ub();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MAP REPRESENTATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
sheaf::array_index_space_state::
map_rep_insert_entry(pod_type xdomain_id, pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));
  require(!contains(xdomain_id));

  // Body:

  // Assign mapping.

  _to_domain[xrange_id] = xdomain_id;
  _to_range.force_item(xdomain_id, xrange_id);
  
  // Postconditions:

  // Not finished inserting entry; do not ensure invariant.

  ensure(contains(xdomain_id, xrange_id));
  
  // Exit

  return;
}

void
sheaf::array_index_space_state::
map_rep_push_back(pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));

  // Body:

  pod_type old_next_id = next_id();

  _to_domain[xrange_id] = old_next_id;
  _to_range.force_item(old_next_id, xrange_id);

  // Postconditions:

  // Not finished pushing back; do not ensure invariant.

  ensure(contains(old_next_id, xrange_id));

  // Exit

  return;
}

void
sheaf::array_index_space_state::
map_rep_push(index_space_iterator& xitr, pod_type xrange_id)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!contains_hub(xrange_id));

  // Body:

  define_old_variable(pod_type old_itr_pod = xitr.pod());
  define_old_variable(pod_type old_itr_hub_pod = xitr.hub_pod());

  /// @todo Implement.

  not_implemented();

  // Postconditions:

  // Not finished inserting entry, do not ensure invariant.

  ensure(contains(old_itr_pod, xrange_id));
  ensure(xitr.pod() == old_itr_pod+1);
  ensure(xitr.hub_pod() == old_itr_hub_pod);

  // Exit:

  return;
}

sheaf::size_type
sheaf::array_index_space_state::
map_rep_remove_entry(pod_type xid, bool xis_range_id)
{
  // Preconditions:

  // Body:

  size_type result = 0;

  if(xis_range_id)
  {
    // Xid is a range id.
    // Check if it is in the map.

    to_domain_type::iterator itr = _to_domain.find(xid);
    if(itr != _to_domain.end())
    {
      // "Erase" the entry in the _to_range map
      // by initializing it to invalid.

      _to_range.initialize(itr->second);

      // Erase the entry in the _to_domain map.

      _to_domain.erase(itr);

      // Removed 1 entry.

      result = 1;
    }
  }
  else
  {
    // Xid is a domain id
    // Check if it is in the map.

    if(contains(xid))
    {
      // Erase the entry in the _to_domain map.

      pod_type lrange_id = _to_range[xid];
      _to_domain.erase(lrange_id);
      
      // "Erase" the entry in the _to_range map
      // by initializing it to invalid.

      _to_range.initialize(xid);

      // Removed 1 entry.

      result = 1;
    }
  }
  
  // Postconditions:

  // Not finished removing entry; do not ensure invariant.

  ensure(xis_range_id ? !contains_hub(xid) : !contains(xid));  

  // Exit

  return result;
}

void
sheaf::array_index_space_state::
map_rep_remove_entry(index_space_iterator& xitr)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!xitr.is_done());
  require(contains(xitr.pod()));

  // Body:

  define_old_variable(pod_type old_itr_id = xitr.pod());
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());

  /// @todo Implement.

  not_implemented();

  // Postconditions:

  ensure(!contains(old_itr_id));
  ensure(!contains(old_itr_hub_id));
  ensure(xitr.is_done() || xitr.pod() > old_itr_id);

  // Exit:

  return;
}

void
sheaf::array_index_space_state::
map_rep_clear()
{
  // Preconditions:

  // Body:

  _to_range.clear();
  _to_domain.clear();
  
  // Postconditions:

  // Not finished clearing; do not ensure invariant.
  // Map rep is empty, but _ct not reset, so can't ensure is_empty.

  ensure(unexecutable("map rep is empty"));

  // Exit:

  return;
}

void
sheaf::array_index_space_state::
map_rep_gather()
{
  // Preconditions:

  // Body:

  // Initialize map members.

  _to_domain.clear();
  _ct = 0;

  // Rebuild the to_domain map while gathering the to_range map.

  pod_type ldomain_id = 0;
  pod_type lrange_id;

  for(pod_type i = 0; i < _end; i++)
  {
    lrange_id = _to_range[i];

    if(is_valid(lrange_id) && hub_id_space().contains(lrange_id))
    {
      _to_range[ldomain_id] = lrange_id;
      _to_domain[lrange_id] = ldomain_id;

      ldomain_id++;

      // Update the count.

      _ct++;
    }
  }

  // ldomain_id should now be the same as _ct.

  assertion(ldomain_id == _ct);

  // The valid part of the to_range map is now gathered
  // into the first part of the array. Initialize the
  // remainder of the array to invalid.

  _to_range.initialize(ldomain_id, _to_range.ub());
  
  // Postconditions:

  ensure(unexecutable("map rep is gathered"));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::array_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const array_index_space_state& lother =
    dynamic_cast<const array_index_space_state&>(xother);

  bool result = mutable_index_space_state::operator==(xother);
  result = result && (_to_range.ub() == lother._to_range.ub());
  pod_type lindex(0);
  while(result && lindex < _to_range.ub())
  {
    result = (_to_range[lindex] == lother._to_range[lindex]);
    ++lindex;
  }
  /// @error Since we still support tr1 unordered_maps the comparison
  ///        operator may not be supported.  See COM-374.
  //result = result && (_to_domain == lother._to_domain);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::array_index_space_state::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::array_index_space_state&
sheaf::array_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const array_index_space_state& lother =
    dynamic_cast<const array_index_space_state&>(xother);

  _to_domain = lother._to_domain;
  _to_range  = lother._to_range;

  (void) mutable_index_space_state::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::array_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result =
    (0 <= xid) && (xid < _to_range.ub()) && is_valid(_to_range[xid]);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::array_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = (_to_domain.find(xhub_id) != _to_domain.end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::array_index_space_state::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = 
    is_valid(xid) && (0 <= xid) &&
    (xid < _to_range.ub()) && (xhub_id == _to_range[xid]);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::array_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  to_domain_type::const_iterator itr = _to_domain.find(xhub_id);

  pod_type result =
    (itr == _to_domain.end()) ? invalid_pod_index() : itr->second;

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::array_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result;
  if((0 <= xid) && (xid < _to_range.ub()))
  {
    result = _to_range[xid];
  }
  else
  {
    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::array_index_space_state::
handle_pool_ct()
{
  // Preconditions:

  // Body:

  size_type result = handles().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::array_index_space_state::
handle_pool_deep_size()
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(handles(), true);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::index_space_handle&
sheaf::array_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  array_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::array_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<array_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::array_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const array_index_space_handle* lid_space =
    dynamic_cast<const array_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::array_index_space_handle>&
sheaf::array_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<array_index_space_handle> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::array_index_space_state::
iterator_pool_ct()
{
  // Preconditions:

  // Body:

  size_type result = iterators().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::array_index_space_state::
iterator_pool_deep_size()
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(iterators(), true);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
sheaf::array_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  array_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::array_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<array_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::array_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const array_index_space_iterator* litr =
    dynamic_cast<const array_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::array_index_space_iterator>&
sheaf::array_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<array_index_space_iterator> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::array_index_space_state::
class_name() const
{
  static const std::string result("array_index_space_state");
  return result;
}

sheaf::array_index_space_state*
sheaf::array_index_space_state::
clone() const
{
  // Preconditions:

  // Body:

  array_index_space_state* result = new array_index_space_state();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::array_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  array_index_space_state* lproto = new array_index_space_state();

  id_space_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::array_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const array_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::array_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(mutable_index_space_state::invariant());

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
deep_size(const array_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const mutable_index_space_state& ixn = static_cast<const mutable_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Add contribution from unordered_map<pod_type, pod_type> to_domain_type.

  typedef array_index_space_state::pod_type pod_type;
  typedef no_deep_size_policy<unordered_map<pod_type, pod_type> > to_domain_policy_type;
  result += deep_size<pod_type, pod_type, to_domain_policy_type>(xn._to_domain, false);

  // Add contribution from auto_block _to_range.

  result += deep_size(xn._to_range, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
