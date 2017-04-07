
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
/// Implementation for class list_index_space_state

#include "list_index_space_state.h"
#include "assert_contract.h"
#include "list_index_space_handle.h"
#include "list_index_space_iterator.h"
#include "deep_size.h"
#include "index_space_family.h"
#include "hub_index_space_handle.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_index_space_handle
sheaf::list_index_space_state::
new_space(index_space_family& xid_spaces,
	  const std::string& xname,
	  bool xis_persistent)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  list_index_space_state* lstate = new list_index_space_state();
  lstate->new_state(xid_spaces, xname, xis_persistent);

  list_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.is_persistent() == xis_persistent);
  ensure(result.name() == xname);

  ensure(result.capacity() >= 0);

  // Exit:

  return result;
}

sheaf::list_index_space_handle
sheaf::list_index_space_state::
new_space(index_space_family& xid_spaces,
	  pod_index_type xid,
	  const std::string& xname,
	  bool xis_persistent)
{
  // Preconditions:

  require(!xid_spaces.contains(xid));
  require(xid_spaces.is_explicit_interval(xid));
  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  list_index_space_state* lstate = new list_index_space_state();
  lstate->new_state(xid_spaces, xid, xname, xis_persistent);

  list_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.index() == xid);
  ensure(result.is_persistent() == xis_persistent);
  ensure(result.name() == xname);

  //  ensure(result.capacity() >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// LIST_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::list_index_space_state::
reverse(bool xupdate_extrema)
{
  // Preconditions:

  // Body:

  _to_range.reverse();


  if(xupdate_extrema)
  {
    update_extrema();
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::list_index_space_state::pod_type
sheaf::list_index_space_state::
front() const
{
  return _to_range.front();
}

sheaf::list_index_space_state::pod_type
sheaf::list_index_space_state::
back() const
{
  return _to_range.back();
}

void
sheaf::list_index_space_state::
push_front(pod_type xhub_id)
{
  // cout << endl << "Entering list_index_space_state::push_front." << endl;

  // Preconditions:

  require(!contains_unglued_hub(xhub_id));
  
  // Body:

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);

  // Insert the entry in the list.

  _to_range.push_front(xhub_id);
  
  // Update the count.

  ++_ct;

  // Update the extrema.

  _begin = 0;

  if(_ct > 1)
  {
    ++_end;
  }
  else
  {
    _end = 1;
  }

  // Postconditions:

  ensure(invariant());
  ensure(unglued_hub_pod(0) == xhub_id);
  ensure(ct() == old_ct + 1);
  ensure(begin() == 0);
  ensure(ct() > 1 ? end() == old_end+1 : end() == 1);
  
  // Exit:

  // cout << "Leaving list_index_space_state::push_front." << endl;
  return;
}

void
sheaf::list_index_space_state::
replace_range_id(pod_type xold_range_id, pod_type xnew_range_id)
{
  // cout << endl << "Entering list_index_space_state::replace_range_id." << endl;

  // Preconditions:

  require((xnew_range_id != xold_range_id) ? !contains_unglued_hub(xnew_range_id) : true);
  
  // Body:

  define_old_variable(bool  old_contains_xold_range_id = contains_unglued_hub(xold_range_id));
  define_old_variable(pod_type old_domain_id = pod(xold_range_id));

  to_range_type::iterator litr = to_range_itr(xold_range_id, true);
  if(litr != _to_range.end())
  {
    *litr = xnew_range_id;
  }
  

  // Postconditions:

  ensure(old_contains_xold_range_id ? contains_unglued_hub(xnew_range_id) : true);
  ensure((xnew_range_id != xold_range_id) ? !contains_unglued_hub(xold_range_id) : true);
  ensure(old_contains_xold_range_id ? pod(xnew_range_id) == old_domain_id : true);
  
  // Exit:

  // cout << "Leaving list_index_space_state::replace_range_id." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

sheaf::list_index_space_state::
list_index_space_state()
  : gathered_insertion_index_space_state()
{
  // Preconditions:
    
  // Body:
  
  _capacity = 0;

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  ensure(capacity() == 0);

  // Exit:

  return; 
}

sheaf::list_index_space_state::
~list_index_space_state()
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
// GATHERED_INSERTION INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


void
sheaf::list_index_space_state::
update_extrema()
{
  // Preconditions:

  // Body:

  // List is always gathered by defintion.

  if(_ct == 0)
  {
    // The map is empty.

    _begin = invalid_pod_index();
    _end = invalid_pod_index();
  }
  else
  {
    _begin = 0;
    _end = _ct;
  }

  // Postconditions:s

  // Exit

  return;
}

void
sheaf::list_index_space_state::
reserve(size_type xcapacity)
{
  // Preconditions:

  // Body:

  _capacity = xcapacity;

  // Postconditions:

  ensure(invariant());
  ensure(capacity() >= xcapacity);

  // Exit:

  return;
}

sheaf::size_type
sheaf::list_index_space_state::
capacity() const
{
  // Preconditions:

  // Body:

  size_type result = _capacity;

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

sheaf::list_index_space_state::to_range_type&
sheaf::list_index_space_state::
to_range()
{
  return _to_range;
}

const sheaf::list_index_space_state::to_range_type&
sheaf::list_index_space_state::
to_range() const
{
  return _to_range;
}


// PROTECTED MEMBER FUNCTIONS

void
sheaf::list_index_space_state::
map_rep_push_back(pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));

  // Body:

  define_old_variable(pod_type old_next_id = next_id());

  _to_range.push_back(xrange_id);

  // Postconditions:

  // Not finished pushing back; do not ensure invariant.

  ensure(contains(old_next_id, xrange_id));

  // Exit

  return;
}

void
sheaf::list_index_space_state::
map_rep_push(index_space_iterator& xitr, pod_type xrange_id)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!contains_hub(xrange_id));

  // Body:

  define_old_variable(pod_type old_itr_pod = xitr.pod());
  define_old_variable(pod_type old_itr_hub_pod = xitr.hub_pod());

  list_index_space_iterator& litr =
    reinterpret_cast<list_index_space_iterator&>(xitr);

  // Insert an item before the current position.

  litr._itr = _to_range.insert(litr._itr, xrange_id);

  // Increment to the next position in the iteration
  // (old_itr_pod+1, old_itr_hub_pod).

  ++litr._itr;

  // Update the pod value.

  ++litr._pod;

  // Postconditions:

  // Not finished inserting entry, do not ensure invariant.

  ensure(contains(old_itr_pod, xrange_id));
  ensure(xitr.pod() == old_itr_pod+1);
  ensure(xitr.hub_pod() == old_itr_hub_pod);

  // Exit:

  return;
}

sheaf::size_type
sheaf::list_index_space_state::
map_rep_remove_entry(pod_type xid, bool xis_range_id)
{
  // Preconditions:


  define_old_variable(bool old_contains_entry = xis_range_id ? contains_hub(xid) : contains(xid));
  define_old_variable(pod_type old_pod = xis_range_id ? pod(xid) : xid);
  define_old_variable(pod_type old_hub_pod = xis_range_id ? xid : hub_pod(xid));
  
  // Body:

  // $$SCRIBBLE: need to actually remove the entry

  size_type result = 0;

  to_range_type::iterator litr = to_range_itr(xid, xis_range_id);
  if(litr != _to_range.end())
  {
    _to_range.erase(litr);
    result = 1;
  }

//   size_type result = 0;

//   if(xis_range_id)
//   {
//     to_range_type::iterator litr = _to_range.begin();

//     while(litr != _to_range.end())
//     {
//       if(*litr == xid)
//       {
// 	// Found the id, remove it.

// 	*litr = invalid_pod_index();
// 	result = 1;
// 	break;
//       }
//       else
//       {
// 	// Not the id, iterate to the next item.

// 	++litr;
//       }
//     }
//   }
//   else
//   {
//     pod_type ldomain_id;

//     to_range_type::iterator itr;

//     for(itr = _to_range.begin(), ldomain_id = 0;
// 	itr != _to_range.end();
// 	++itr, ++ldomain_id)
//     {
//       if(ldomain_id == xid)
//       {
// 	// Found the id.

// 	if(!is_valid(*itr))
// 	{
// 	  // Entry does not exist, exit loop.

// 	  break;
// 	}
	
// 	// Entry exists, remove it.

// 	*itr = invalid_pod_index();
// 	result = 1;

// 	break;
//       }
//     }
//   }

//   if(result > 0)
//   {
//     // No invalid ids should be on the tail of the list, prone them.

//     while(!_to_range.empty() && !is_valid(_to_range.back()))
//     {
//       _to_range.pop_back();
//     }  
//   }
  
  // Postconditions:

  // Not finished removing entry; do not ensure invariant.

  //  ensure(xis_range_id ? !contains_hub(xid) : !contains(xid));
  ensure(!old_contains_entry || !contains(old_pod, old_hub_pod));
  ensure((result == 0) || (result == 1));

  // Exit

  return result;
}

void
sheaf::list_index_space_state::
map_rep_remove_entry(index_space_iterator& xitr)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!xitr.is_done());
  require(contains(xitr.pod()));

  // Body:

  define_old_variable(pod_type old_itr_id = xitr.pod());
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());

  list_index_space_iterator& litr =
    reinterpret_cast<list_index_space_iterator&>(xitr);

  // Remove the current position.
  // Note that since the id space is determined by sequentially
  // numbering the items in the list, the pod id
  // associated with the new value of the iterator is unchanged.

  litr._itr = _to_range.erase(litr._itr);

  if(litr._itr == _to_range.end())
  {
    // Erased the last item in the list, the iteration is done.

    litr.invalidate_ids();
  }
  else
  {
    // Update the hub pod.

    litr._hub_pod = *litr._itr;
  }

  // Postconditions:

  ensure(!contains_hub(old_itr_hub_id));
  ensure(xitr.is_done() || xitr.pod() == old_itr_id);
  ensure(unexecutable("xitr.is_done() || xitr.hub_pod() == old_next_itr_hub_pod"));

  // Exit:

  return;
}

void
sheaf::list_index_space_state::
map_rep_clear()
{
  // Preconditions:

  // Body:

  _to_range.clear();
  
  // Postconditions:

  // Not finished clearing; do not ensure invariant.
  // Map rep is empty, but _ct not reset, so can't ensure is_empty.

  ensure(unexecutable("map rep is empty"));

  // Exit:

  return;
}

void
sheaf::list_index_space_state::
map_rep_gather()
{
  // Preconditions:

  // Body:

  // $$SCRIBBLE: no need to do anything. Map is always gatherd.

//   to_range_type::iterator itr;
//   to_range_type::iterator new_itr;

//   for(itr = _to_range.begin(), new_itr = _to_range.begin();
//       itr != _to_range.end();
//       ++itr)
//   {
//     if(is_valid(*itr) && (itr != new_itr))
//     {
//       // The current value is value and the position has changed,
//       // assign value to new position.

//       *new_itr = *itr;
//       ++new_itr;
//     }
//   }

//   if(new_itr != _to_range.end())
//   {
//     // Trim the map to the new size.

//     _to_range.erase(++new_itr, _to_range.end());
//   }
  
  // Postconditions:

  ensure(unexecutable("map rep is gathered"));

  // Exit:

  return;
}

sheaf::list_index_space_state::to_range_type::iterator
sheaf::list_index_space_state::
to_range_itr(pod_type xid, bool xis_range_id)
{
  // cout << endl << "Entering list_index_space_state::to_range_itr." << endl;

  // Preconditions:


  // Body:

  to_range_type::iterator result;
  
  if(xis_range_id)
  {
    for(result = _to_range.begin(); result != _to_range.end(); ++result)
    {
      if(*result == xid)
      {
        break;
      }
    }
  }
  else
  {
    pod_type ldomain_id;
    for(result = _to_range.begin(), ldomain_id = 0; result != _to_range.end(); ++result, ++ldomain_id)
    {
      if(ldomain_id == xid)
      {
        break;
      }
    }
  }
  

  // Postconditions:

  // Exit:

  // cout << "Leaving list_index_space_state::to_range_itr." << endl;
  return result;
}

sheaf::list_index_space_state::to_range_type::const_iterator
sheaf::list_index_space_state::
to_range_const_itr(pod_type xid, bool xis_range_id) const
{
  // cout << endl << "Entering list_index_space_state::to_range_const_itr." << endl;

  // Preconditions:


  // Body:

  to_range_type::const_iterator result;
  
  if(xis_range_id)
  {
    for(result = _to_range.begin(); result != _to_range.end(); ++result)
    {
      if(*result == xid)
      {
        break;
      }
    }
  }
  else
  {
    pod_type ldomain_id;
    for(result = _to_range.begin(), ldomain_id = 0; result != _to_range.end(); ++result, ++ldomain_id)
    {
      if(ldomain_id == xid)
      {
        break;
      }
    }
  }
  

  // Postconditions:

  // Exit:

  // cout << "Leaving list_index_space_state::to_range_const_itr." << endl;
  return result;
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::list_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const list_index_space_state& lother =
    dynamic_cast<const list_index_space_state&>(xother);

  bool result = gathered_insertion_index_space_state::operator==(xother);
  result = result && (_to_range == lother._to_range);
  result = result && (_capacity == lother._capacity);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::list_index_space_state::
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

sheaf::list_index_space_state&
sheaf::list_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const list_index_space_state& lother =
    dynamic_cast<const list_index_space_state&>(xother);

  _to_range = lother._to_range;
  _capacity = lother._capacity;

  (void) gathered_insertion_index_space_state::operator=(xother);

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
sheaf::list_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  // If _ct = 0 then _begin == _end == invalid_pod_index() and 
  // the following expression returns false for any xid. So we don't
  // have to test whether _begin or _end is valid.

  assertion(is_valid(_begin) == is_valid(_end));
  
  bool result = (_begin <= xid) && (xid < _end);

//   bool result = false;

//   pod_index_type ldomain_id;
//   to_range_type::const_iterator itr;

//   for(itr = _to_range.begin(), ldomain_id = 0;
//       itr != _to_range.end();
//       ++itr, ++ldomain_id)
//   {
//     if(ldomain_id == xid)
//     {
//       result = is_valid(*itr);
//       break;
//     }
//   }

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::list_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = to_range_const_itr(xhub_id, true) != _to_range.end();
  

//   bool result = false;

//   to_range_type::const_iterator itr;

//   for(itr = _to_range.begin(); itr != _to_range.end(); ++itr)
//   {
//     if(*itr == xhub_id)
//     {
//       result = true;
//       break;
//     }
//   }

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::list_index_space_state::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  to_range_type::const_iterator litr = to_range_const_itr(xid, false);
  bool result = (litr != _to_range.end()) && (*litr == xhub_id);


//   bool result = false;

//   pod_index_type ldomain_id;
//   to_range_type::const_iterator itr;

//   for(itr = _to_range.begin(), ldomain_id = 0; itr != _to_range.end(); ++itr, ++ldomain_id)
//   {
//     if(ldomain_id == xid)
//     {
//       result = (*itr == xhub_id);
//       break;
//     }
//   }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::list_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result = invalid_pod_index();

  pod_index_type ldomain_id;
  to_range_type::const_iterator itr;

  for(itr = _to_range.begin(), ldomain_id = 0; itr != _to_range.end(); ++itr, ++ldomain_id)
  {
    if(*itr == xhub_id)
    {
      result = ldomain_id;
      break;
    }
  }

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::list_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  to_range_type::const_iterator litr = to_range_const_itr(xid, false);
  pod_type result = (litr != _to_range.end()) ? *litr : invalid_pod_index();

//   pod_type result = invalid_pod_index();

//   pod_index_type ldomain_id;
//   to_range_type::const_iterator itr;

//   for(itr = _to_range.begin(), ldomain_id = 0; itr != _to_range.end(); ++itr, ++ldomain_id)
//   {
//     if(ldomain_id == xid)
//     {
//       result = *itr;
//       break;
//     }
//   }

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
sheaf::list_index_space_state::
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
sheaf::list_index_space_state::
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
sheaf::list_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  list_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::list_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<list_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::list_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const list_index_space_handle* lid_space =
    dynamic_cast<const list_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::list_index_space_handle>&
sheaf::list_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<list_index_space_handle> result;

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
sheaf::list_index_space_state::
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
sheaf::list_index_space_state::
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
sheaf::list_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  list_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::list_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<list_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::list_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const list_index_space_iterator* litr =
    dynamic_cast<const list_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::list_index_space_iterator>&
sheaf::list_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<list_index_space_iterator> result;

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
sheaf::list_index_space_state::
class_name() const
{
  static const std::string result("list_index_space_state");
  return result;
}

sheaf::list_index_space_state*
sheaf::list_index_space_state::
clone() const
{
  // Preconditions:

  // Body:

  list_index_space_state* result = new list_index_space_state();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::list_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  list_index_space_state* lproto = new list_index_space_state();

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
sheaf::list_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const list_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::list_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(gathered_insertion_index_space_state::invariant());

    // Invariances for this class:

    invariance(is_valid(begin()) == is_valid(end()));
    invariance((begin() == 0) || !is_valid(begin()));
      
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
deep_size(const list_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const gathered_insertion_index_space_state& ixn = static_cast<const gathered_insertion_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Add contribution from list<pod_type> _to_range.

  result += deep_size(xn._to_range, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
