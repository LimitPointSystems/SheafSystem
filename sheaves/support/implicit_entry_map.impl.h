
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

/// @file
/// Implementation for class template implicit_entry_map.

#ifndef IMPLICIT_ENTRY_MAP_IMPL_H
#define IMPLICIT_ENTRY_MAP_IMPL_H

#ifndef IMPLICIT_ENTRY_MAP_H
#include "implicit_entry_map.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef DEEP_SIZE_H
#include "deep_size.h"
#endif

#ifndef IMPLICIT_ENTRY_MAP_ITERATOR_H
#include "implicit_entry_map_iterator.h"
#endif

#ifndef RC_PTR_H
#include "rc_ptr.h"
#endif

namespace sheaf
{
  
// =============================================================================
// IMPLICIT_ENTRY_MAP FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename E, typename I>
implicit_entry_map<E, I>::
implicit_entry_map()
  : _ct(0),
    _begin(invalid_pod_index()),
    _end(invalid_pod_index())
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}; 

template <typename E, typename I>
implicit_entry_map<E, I>::
~implicit_entry_map()
{
  // Preconditions:

  // Body:

  // Delete the explicit value reference counted pointers.

  typename explicit_value_map_type::iterator lexplicit_value_itr =
    _explicit_value_map.begin();
  while(lexplicit_value_itr != _explicit_value_map.end())
  {
    // Delete reference counted pointer.

    if(lexplicit_value_itr->second != 0)
    {
      delete lexplicit_value_itr->second;
    }

    // Move to the next entry.
   
    lexplicit_value_itr++;
  }

  // Delete the implicit interval reference counted pointers.

  typename interval_map_type::iterator linterval_itr = _interval_map.begin();
  while(linterval_itr != _interval_map.end())
  {
    // Delete reference counted pointer.

    if(linterval_itr->second != 0)
    {
      delete linterval_itr->second;
    }
    
    // Move to the next entry.

    linterval_itr++;
  }

  // Postconditions:

  // Exit:

  return;
};

template <typename E, typename I>
bool
implicit_entry_map<E, I>::
contains_explicit_entry(pod_type xid) const
{
  // Preconditions:

  // Body:

  typename explicit_value_map_type::const_iterator litr =
    _explicit_value_map.find(xid);

  bool result = (litr != _explicit_value_map.end());

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
bool
implicit_entry_map<E, I>::
contains_implicit_entry(pod_type xid) const
{
  // Preconditions:

  // Body:

  typename interval_map_type::const_iterator litr =
    _interval_map.upper_bound(xid);

  bool result = (litr != _interval_map.end()) && (litr->second != 0);

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
bool
implicit_entry_map<E, I>::
contains_entry(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = (contains_explicit_entry(xid) ||
		 contains_implicit_entry(xid));

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
E&
implicit_entry_map<E, I>::
value(pod_type xid) const
{
  // Preconditions:

  require(contains_entry(xid));

  // Body:

  E* result;

  const explicit_value_type& lexplicit_value = explicit_value(xid);

  if(!lexplicit_value)
  {
    // No explicit value found, get the value from the implicit interval.

    result = &implicit_interval(xid)->value(xid);
  }
  else
  {
    // Explicit value found, get the value from the reference
    // counted pointer.

    result = &*lexplicit_value;
  }
  
  // Postconditions:

  // Exit:

  return *result;
};

template <typename E, typename I>
E&
implicit_entry_map<E, I>::
operator [] (pod_type xid) const
{
  // Preconditions:

  require(contains_entry(xid));

  // Body:

  E& result = value(xid);

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
void
implicit_entry_map<E, I>::
insert_explicit_entry(pod_type xid, E& xvalue)
{
  // Preconditions:

  require(!contains_explicit_entry(xid));

  // Body:

  define_old_variable(size_type old_ct = ct());

  _explicit_value_map[xid] = new explicit_value_type(&xvalue);

  // Update count.

  _ct++;

  // Update extrema.

  update_extrema_for_insert(xid, xid+1);

  // Postconditions:

  ensure(contains_explicit_entry(xid));
  ensure(ct() == old_ct+1);
  ensure(begin() <= xid);
  ensure(end() >= xid+1);

  // Exit:

  return;
};

template <typename E, typename I>
void
implicit_entry_map<E, I>::
insert_implicit_interval(I& xinterval)
{
  // Preconditions:

  /// @todo Make precondition executable.
  require(unexecutable("interval is empty"));
 
  // Body:

  define_old_variable(size_type old_ct = ct());

  pod_type lbegin = xinterval.begin();
  pod_type lend = xinterval.end();

  _interval_map[lend] = new interval_type(&xinterval);

  if(_interval_map.find(lbegin) == _interval_map.end())
  {
    // The beginning of the interval is not the end of some other
    // interval.

    _interval_map[lbegin] = 0;
  }

  // Update count.

  _ct += xinterval.ct();

  // Update extrema.

  update_extrema_for_insert(lbegin, lend);

  // Postconditions:

  /// @todo Make postcondition executable.
  ensure(unexecutable("interval is full"));
  ensure(ct() == old_ct + xinterval.ct());
  ensure(begin() <= xinterval.begin());
  ensure(end() >= xinterval.end());

  // Exit:

  return;
};

template <typename E, typename I>
void
implicit_entry_map<E, I>::
remove_explicit_entry(pod_type xid)
{
  // Preconditions:

  require(contains_explicit_entry(xid));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  explicit_value_type* lrc_ptr = _explicit_value_map.find(xid)->second;

  // Erase from data structure.

  _explicit_value_map.erase(xid);

  // Delete the reference counted pointer.

  delete lrc_ptr;

  // Update the count.

  _ct--;

  // Update the extrema.

  update_extrema_for_remove(xid, xid+1);

  // Postconditions:

  ensure(!contains_explicit_entry(xid));
  ensure(ct() == old_ct - 1);
  ensure((ct() == 0) ? !is_valid(begin()) : true);
  ensure((ct() == 0) ? !is_valid(end()) : true);
  ensure(((ct() > 0) && (xid == old_begin)) ? begin() > xid : true);
  ensure(((ct() > 0) && ((xid + 1) == old_end)) ? end() <= xid : true);

  // Exit:

  return;
};

template <typename E, typename I>
void
implicit_entry_map<E, I>::
remove_implicit_interval(pod_type xid)
{
  // Preconditions:

  require(contains_implicit_entry(xid));

  // Body:

  typename interval_map_type::iterator litr = _interval_map.upper_bound(xid);
  pod_type lend = litr->first;

  typename interval_map_type::iterator lprevious = litr;
  lprevious--;
  pod_type lbegin = lprevious->first;

  typename interval_map_type::iterator lnext = litr;
  lnext++;

  if(lprevious->second == 0)
  {
    if((lnext == _interval_map.end()) || (lnext->second == 0))
    {
      // Remove previous so that no void value is at the end or
      // back-to-back void values.

      _interval_map.erase(litr);
      if(litr->second != 0)
	delete litr->second;

      _interval_map.erase(lprevious);
    }
    else
    {
      // Adjust the void value to be the beginning of the next.

      _interval_map[lend] = 0;
      _interval_map.erase(lprevious);
    }
  }
  else
  {
    if((lnext == _interval_map.end()) || (lnext->second == 0))
    {
      // The void value is in the correct spot, erase current entry.

      _interval_map.erase(litr);
      if(litr->second != 0)
	delete litr->second;
    }
    else
    {
      // A void value needs inserted at the current entry.

      _interval_map[lend] = 0;
    }
  }

  // Update the count.

  _ct -= (lend-lbegin);

  // Update the extrema.

  update_extrema_for_remove(lbegin, lend);

  // Postconditions:

  ensure(!contains_implicit_entry(xid));

  /// @todo Implement a set of functions which allow the postconditions
  ///       for the count and extrema to be properly represented.
  ///       Ex: interval_ct(xid), interval_begin(xid), interval_end(xid).

  // Exit:

  return;
};

template <typename E, typename I>
void
implicit_entry_map<E, I>::
remove_entry(pod_type xid, bool xremove_interval)
{
  // Preconditions:

  // Body:

  /// @issue This can be more efficient.  The calls to contains_* can
  ///        be replaced with access to the data structures which can
  ///        be used for the removal.

  if(contains_explicit_entry(xid))
  {
    // Remove the explicit entry.

    remove_explicit_entry(xid);
  }

  if(contains_implicit_entry(xid))
  {
    // Remove the implicit entry.

    if(xremove_interval)
    {
      // Remove the entire implicit interval.

      remove_implicit_interval(xid);
    }
    else
    {
      // Remove the implicit entry.

      typename interval_map_type::iterator litr = _interval_map.upper_bound(xid);
      pod_type lend = litr->first;

      typename interval_map_type::iterator lprevious = litr;
      lprevious--;
      pod_type lbegin = lprevious->first;

      interval_type* linterval = litr->second;

      if(lbegin == lend-1)
      {
	// Removing the only entry in the interval; remove the entire interval.

	/// @issue This could be done more efficiently since we already
	/// found the previous and next pointers (see the implementation
	/// of remove_implicit_interval).

	remove_implicit_interval(xid);
      }
      else if(xid == lbegin)
      {
	// Removing the first entry.

	if(lprevious->second == 0)
	{
	  // The previous interval is void, remove it.

	  _interval_map.erase(lprevious);
	}

	// Add a void interval.

	_interval_map[xid+1] = 0;

	// Update the count.

	_ct--;

	// Update the extrema; the beginning extrema may have increased by one.

	if(xid == _begin)
	  _begin++;
      }
      else if(xid == lend-1)
      {
	// Removing the last entry.

	typename interval_map_type::iterator lnext = litr;
	lnext++;

	// Adjust the current interval.

	_interval_map.erase(litr);
	_interval_map[xid] = linterval;

	if((lnext != _interval_map.end()) && (lnext->second != 0))
	{
	  // The next interval is not void, add void interval.

	  _interval_map[lend] = 0;
	}

	// Update the count.

	_ct--;

	// Update the extrema; the ending extrema may have decreased by one.

	if(xid == _end-1)
	  _end--;
      }
      else
      {
	// Removing an entry in the middle of the interval.

	_interval_map[xid] = new interval_type(*linterval);
	_interval_map[xid+1] = 0;

	// Update the count.

	_ct--;

	// No need to update the extrema.
      }
    }
  }

  // Postconditions:

  ensure(!contains_entry(xid));

  // Exit:

  return;
};

template <typename E, typename I>
implicit_entry_map_iterator<E, I>*
implicit_entry_map<E, I>::
iterator() const
{
  // Preconditions:

  // Body:

  iterator_type* result = new iterator_type(*this);

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
};

template <typename E, typename I>
pod_index_type
implicit_entry_map<E, I>::
begin() const
{
  return _begin;
};

template <typename E, typename I>
pod_index_type
implicit_entry_map<E, I>::
end() const
{
  return _end;
};

template <typename E, typename I>
size_type
implicit_entry_map<E, I>::
ct() const
{
  return _ct;
};

// PROTECTED MEMBER FUNCTIONS

template <typename E, typename I>
const typename implicit_entry_map<E, I>::explicit_value_type&
implicit_entry_map<E, I>::
null_explicit_value()
{
  static const explicit_value_type result;
  return result;
}

template <typename E, typename I>
const typename implicit_entry_map<E, I>::interval_type&
implicit_entry_map<E, I>::
null_interval()
{
  static const interval_type result;
  return result;
}

template <typename E, typename I>
const typename implicit_entry_map<E, I>::explicit_value_type&
implicit_entry_map<E, I>::
explicit_value(pod_type xid) const
{
  // Preconditions:

  // Body:

  typename explicit_value_map_type::const_iterator litr =
    _explicit_value_map.find(xid);

  const explicit_value_type& result =
    ((litr != _explicit_value_map.end()) ? *litr->second : null_explicit_value());

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
const typename implicit_entry_map<E, I>::interval_type&
implicit_entry_map<E, I>::
implicit_interval(pod_type xid) const
{
  // Preconditions:

  // Body:

  typename interval_map_type::const_iterator litr =
    _interval_map.upper_bound(xid);

  const interval_type& result =
    (((litr != _interval_map.end()) && (litr->second != 0)) ?
     *litr->second : null_interval());

  // Postconditions:

  // Exit:

  return result;
};

// PRIVATE MEMBER FUNCTIONS

template <typename E, typename I>
void
implicit_entry_map<E, I>::
update_extrema_for_insert(pod_type xbegin, pod_type xend)
{
  // Preconditions:

  // Body:

  // Update the begin.

  if(!is_valid(_begin) || (xbegin < _begin))
  {
    _begin = xbegin;
  }

  // Update the end.
  
  if(!is_valid(_end) || (xend > _end))
  {
    _end = xend;
  }
  
  // Postconditions:

  ensure(begin() <= xbegin);
  ensure(end() >= xend);

  // Exit:

  return;
};

template <typename E, typename I>
void
implicit_entry_map<E, I>::
update_extrema_for_remove(pod_type xbegin, pod_type xend)
{
  // Preconditions:

  require(unexecutable("containers have been updated."));
  require(unexecutable("ct() has been updated."));

  // Body:

  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  if(_ct == 0)
  {
    // No more entries, invalid the extrema.

    _begin = invalid_pod_index();
    _end = invalid_pod_index();
  }
  else if(xbegin == _begin)
  {
    // The id is the beginning, find new beginning.

    for(pod_type i = _begin; i < _end; i++)
    {
      if(contains_entry(i))
      {
	_begin = i;
	break;
      }
    }
  }
  else if(xend == _end)
  {
    // The id is the end, find new end.

    for(pod_type i = xend - 1; i >= _begin; i--)
    {
      if(contains_entry(i))
      {
	_end = i+1;
	break;
      }
    }
  }

  // Postconditions:

  ensure((ct() == 0) ? !is_valid(begin()) : true);
  ensure((ct() == 0) ? !is_valid(end()) : true);
  ensure(((ct() > 0) && (xbegin == old_begin)) ? begin() > xbegin : true);
  ensure(((ct() > 0) && (xend == old_end)) ? end() < xend : true);

  // Exit:

  return;
};

// =============================================================================
// IMPLICIT_ENTRY_MAP FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename E, typename I>
bool
implicit_entry_map<E, I>::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  bool result = dynamic_cast< const implicit_entry_map<E, I>* >(other) != 0;

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
implicit_entry_map<E, I>*
implicit_entry_map<E, I>::
clone() const
{
  // Preconditions:

  // Body:

  implicit_entry_map<E, I>* result = new implicit_entry_map<E, I>();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
};

template <typename E, typename I>
bool
implicit_entry_map<E, I>::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(any::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariances for this class:

    ensure((ct() > 0) == is_valid(begin()));
    ensure((ct() > 0) == is_valid(end()));
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
};

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

template <typename E, typename I>
size_t
deep_size(const implicit_entry_map<E, I>& xmap, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xmap) : 0;

  /// @issue Since the deletion will be handled by this map should
  ///        the deep_size?

  /// @todo Implement deep_size for rc_ptr.

//   // Add contribution from member _explicit_value_map.

//   typedef no_deep_size_policy<typename implicit_entry_map<E, I>::explicit_value_map_type> explicit_policy_type;
//   result += deep_size<pod_index_type, E*, explicit_policy_type>(xmap._explicit_value_map, false);

//   // Add contribution from member _interval_map.

//   typedef no_deep_size_policy<typename implicit_entry_map<E, I>::interval_map_type> interval_policy_type;
//   result += deep_size<pod_index_type, I*, interval_policy_type>(xmap._interval_map, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
};

} // namespace sheaf

#endif // ifndef IMPLICIT_ENTRY_MAP_IMPL_H






