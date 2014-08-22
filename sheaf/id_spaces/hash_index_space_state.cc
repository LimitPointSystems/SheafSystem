
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
/// Implementation for class hash_index_space_state

#include "ComLimitPoint/sheaf/hash_index_space_state.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/hash_index_space_handle.h"
#include "ComLimitPoint/sheaf/hash_index_space_iterator.h"
#include "ComLimitPoint/sheaf/deep_size.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/hub_index_space_handle.h"

using namespace std;
using namespace unordered;

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::hash_index_space_handle
sheaf::hash_index_space_state::
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

  hash_index_space_state* lstate = new hash_index_space_state();
  lstate->new_state(xid_spaces, xname, xis_persistent);

  lstate->reserve(xcapacity);

  hash_index_space_handle result(*lstate);

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

sheaf::hash_index_space_handle
sheaf::hash_index_space_state::
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

  hash_index_space_state* lstate = new hash_index_space_state();
  lstate->new_state(xid_spaces, xid, xname, xis_persistent);

  lstate->reserve(xcapacity);

  hash_index_space_handle result(*lstate);

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
// HASH_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::hash_index_space_state::
hash_index_space_state()
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

sheaf::hash_index_space_state::
~hash_index_space_state()
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
sheaf::hash_index_space_state::
update_extrema()
{
  // Preconditions:

  // Body:

  _begin = max_pod_index();
  _end = min_pod_index();

  for(to_range_type::const_iterator itr = _to_range.begin();
      itr != _to_range.end();
      ++itr)
  {
    update_extrema(itr->first);
  }

  // Postconditions:

  // Exit

  return;
}

void
sheaf::hash_index_space_state::
reserve(size_type xcapacity)
{
  // Preconditions:

  // Body:

  if(xcapacity > capacity())
  {  
    size_type lbucket_ct = (xcapacity / 2) + (xcapacity % 2);

    _to_domain.rehash(lbucket_ct);
    _to_range.rehash(lbucket_ct);
  }

  // Postconditions:

  ensure(invariant());
  ensure(capacity() >= xcapacity);

  // Exit:

  return;
}

sheaf::size_type
sheaf::hash_index_space_state::
capacity() const
{
  // Preconditions:

  // Body:

  size_type result = (2 * _to_range.bucket_count());

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
sheaf::hash_index_space_state::
map_rep_insert_entry(pod_type xdomain_id, pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));
  require(!contains(xdomain_id));

  // Body:

  // Assign mapping.

  _to_range[xdomain_id] = xrange_id;
  _to_domain[xrange_id] = xdomain_id;
  
  // Postconditions:

  // Not finished inserting entry; do not ensure invariant.

  ensure(contains(xdomain_id, xrange_id));
  
  // Exit

  return;
}

void
sheaf::hash_index_space_state::
map_rep_push_back(pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));

  // Body:

  pod_type old_next_id = next_id();

  _to_domain[xrange_id] = old_next_id;
  _to_range[old_next_id] = xrange_id;

  // Postconditions:

  // Not finished pushing back; do not ensure invariant.

  ensure(contains(old_next_id, xrange_id));

  // Exit

  return;
}

void
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
map_rep_remove_entry(pod_type xid, bool xis_range_id)
{
  // Preconditions:

  // Body:

  size_type result = 0;

  if(xis_range_id)
  {
    // Find the domain id for xid, if there is one.

    to_domain_type::iterator itr = _to_domain.find(xid);
    if(itr != _to_domain.end())
    {
      // Erase the entry in the _to_range map.

      _to_range.erase(itr->second);

      // Erase the entry in the _to_domain map.

      _to_domain.erase(itr);

      // Removed 1 entry.

      result = 1;
    }
  }
  else
  {
    // Find the range id for xid, if there is one.

    to_range_type::iterator itr = _to_range.find(xid);
    if(itr != _to_range.end())
    {
      // Erase the entry in the _to_domain map.

      _to_domain.erase(itr->second);

      // Erase the entry in the _to_range map.

      _to_range.erase(itr);

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
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
map_rep_gather()
{
  // Preconditions:

  // Body:

  // Build the gathered _to_domain map.

  _to_domain.clear();
  _ct = 0;
  
  pod_type ldomain_id = 0;
  pod_type lrange_id;
  
  to_range_type::iterator lto_range_itr = _to_range.begin();
  while(lto_range_itr != _to_range.end())
  {
    lrange_id = lto_range_itr->second;

    if(hub_id_space().contains(lrange_id))
    {
      // The range id has not been delete.
      // Add it to the map.

      _to_domain[lrange_id] = ldomain_id;

      // Increment the domain id.

      ++ldomain_id;

      // Increment the id space count.

      ++_ct;
    }

    // Increment to the next entry in the _to_range map.

    ++lto_range_itr;
  }

  // Build the gathered _to_range map.

  _to_range.clear();

  to_domain_type::iterator lto_domain_itr = _to_domain.begin();
  while(lto_domain_itr != _to_domain.end())
  {
    // Insert the entry into the map.

    _to_range[lto_domain_itr->second] = lto_domain_itr->first;

    // Increment the iterator.

    ++lto_domain_itr;
  }
  
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
sheaf::hash_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const hash_index_space_state& lother =
    dynamic_cast<const hash_index_space_state&>(xother);

  bool result = mutable_index_space_state::operator==(xother);
  /// @error Since we still support tr1 unordered_maps the comparison
  ///        operator may not be supported.  See COM-374.
//   result = result && (_to_range == lother._to_range);
//   result = result && (_to_domain == lother._to_domain);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::hash_index_space_state::
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

sheaf::hash_index_space_state&
sheaf::hash_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const hash_index_space_state& lother =
    dynamic_cast<const hash_index_space_state&>(xother);

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
sheaf::hash_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = (_to_range.find(xid) != _to_range.end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  to_range_type::const_iterator itr = _to_range.find(xid);

  bool result = (itr != _to_range.end()) && (itr->second == xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  to_range_type::const_iterator itr = _to_range.find(xid);

  pod_type result =
    (itr == _to_range.end()) ? invalid_pod_index() : itr->second;

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
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  hash_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::hash_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<hash_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::hash_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const hash_index_space_handle* lid_space =
    dynamic_cast<const hash_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::hash_index_space_handle>&
sheaf::hash_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<hash_index_space_handle> result;

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
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
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
sheaf::hash_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  hash_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::hash_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<hash_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::hash_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const hash_index_space_iterator* litr =
    dynamic_cast<const hash_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::hash_index_space_iterator>&
sheaf::hash_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<hash_index_space_iterator> result;

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
sheaf::hash_index_space_state::
class_name() const
{
  static const std::string result("hash_index_space_state");
  return result;
}

sheaf::hash_index_space_state*
sheaf::hash_index_space_state::
clone() const
{
  // Preconditions:

  // Body:

  hash_index_space_state* result = new hash_index_space_state();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::hash_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  hash_index_space_state* lproto = new hash_index_space_state();

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
sheaf::hash_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const hash_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::hash_index_space_state::
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
deep_size(const hash_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const mutable_index_space_state& ixn = static_cast<const mutable_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Add contribution from unordered_map<pod_type, pod_type> to_domain.

  typedef hash_index_space_state::pod_type pod_type;
  typedef no_deep_size_policy<unordered_map<pod_type, pod_type> > to_domain_policy_type;
  result += deep_size<pod_type, pod_type, to_domain_policy_type>(xn._to_domain, false);

  // Add contribution from unordered_map<pod_type, pod_type> _to_range.

  typedef no_deep_size_policy<unordered_map<pod_type, pod_type> > to_range_policy_type;
  result += deep_size<pod_type, pod_type, to_range_policy_type>(xn._to_range, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
