// $RCSfile: interval_set.cc,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:46 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class interval_set

#include "interval_set.h"
#include "assert_contract.h"
#include "deep_size.h"
#include "interval_set_iterator.h"

// =============================================================
// INTERVAL_SET FACET
// =============================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::interval_set::
interval_set()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::interval_set::
interval_set(const interval_set& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(*this == xother);
  
  // Exit:

  return;
}

sheaf::interval_set::
~interval_set()
{
  // Preconditions:

  // Body:

  // nothing to do.

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::interval_set::
operator==(const interval_set& xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_interval_map == xother._interval_map);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::interval_set::
insert_interval(pod_type xbegin, pod_type xend)
{
  // Preconditions:

  // Body:

  put_interval(xbegin, xend, true);

  // Postconditions:

  ensure(invariant());
  ensure(interval_is_full(xbegin, xend));

  // Exit:

  return;
}

void
sheaf::interval_set::
insert_member(pod_type xmbr)
{
  // Preconditions:

  // Body:

  put_interval(xmbr, xmbr, true);

  // Preconditions:

  ensure(invariant());
  ensure(contains_member(xmbr));

  // Exit:

  return;
}  

void
sheaf::interval_set::
remove_interval(pod_type xbegin, pod_type xend)
{
  // Preconditions:

  // Body:

  put_interval(xbegin, xend, false);

  // Postconditions:

  ensure(invariant());
  ensure(interval_is_empty(xbegin, xend));

  // Exit:

  return;
}

void
sheaf::interval_set::
remove_member(pod_type xmbr)
{
  // Preconditions:

  // Body:

  put_interval(xmbr, xmbr, false);

  // Preconditions:

  ensure(invariant());
  ensure(!contains_member(xmbr));

  // Exit:

  return;
}  

bool
sheaf::interval_set::
contains_member(pod_type xmbr) const
{
  bool result;

  // Preconditions:

  // Body:

  map_type::const_iterator litr = _interval_map.lower_bound(xmbr);
  
  result = (litr != _interval_map.end());
  if(result)
    result = litr->second;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::interval_set::
member_ct(pod_type xbegin, pod_type xend) const
{
  // Preconditions:

  // Body:

  size_type result = 0;

  // Postconditions:

  map_type::const_iterator litr = _interval_map.lower_bound(xbegin);

  pod_type lbegin = xbegin;

  while((litr != _interval_map.end()) && (lbegin <= xend))
  {
    pod_type lend = litr->first;

    if(litr->second)
    {
      // The interval is full, add members.

      if(xend <= lend)
      {
	// Only part of the interval is greater than the input interval,
	// add the part and exit the loop.

	result += (xend - lbegin) + 1;
	break;
      }
      else
      {
	// The entire interval is in the input interval, add it and continue.

	result += (lend - lbegin) + 1;
      }
    }

    // Set the begin of the next interval and increment the iterator.

    lbegin = lend+1;
    litr++;
  }

  // Exit:

  return result;
}

bool
sheaf::interval_set::
interval_is_empty(pod_type xbegin, pod_type xend) const
{
  bool result;

  // Preconditions:

  // Body:

  map_type::const_iterator litr = _interval_map.lower_bound(xbegin);

  result =
    (litr == _interval_map.end()) ||
    (!litr->second && (litr->first >= xend));
  
  // Postcondtions:

  // Exit:

  return result;
}

bool
sheaf::interval_set::
interval_is_full(pod_type xbegin, pod_type xend) const
{
  bool result;

  // Preconditions:

  // Body:

  map_type::const_iterator litr = _interval_map.lower_bound(xbegin);

  result =
    (litr != _interval_map.end()) &&
    litr->second && (litr->first >= xend);

  // Postcondtions:

  // Exit:

  return result;
}

sheaf::interval_set::pod_type
sheaf::interval_set::
begin() const
{
  // Preconditions:

  // Body:

  pod_type result;

  if(is_empty())
  {
    result = invalid_pod_index();
  }
  else
  {
    result = _interval_map.begin()->first+1;
  }
  
  // Postconditions:

  ensure(is_empty() ? !is_valid(result) : true);

  // Exit:

  return result;
}

sheaf::interval_set::pod_type
sheaf::interval_set::
end() const
{
  // Preconditions:

  // Body:

  pod_type result;

  if(is_empty())
  {
    result = invalid_pod_index();
  }
  else
  {
    map_iterator_type litr = _interval_map.end();
    --litr;

    result = litr->first;
  }
  
  // Postconditions:

  ensure(is_empty() ? !is_valid(result) : true);

  // Exit:

  return result;
}

void
sheaf::interval_set::
clear()
{
  // Preconditions:

  // Body:

  _interval_map.clear();
  
  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return;
}

bool
sheaf::interval_set::
is_empty() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _interval_map.empty();
  
  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return result;
}

sheaf::interval_set_iterator*
sheaf::interval_set::
iterator(bool xis_full_iterator) const
{
  interval_set_iterator* result;
  
  // Preconditions:

  // Body:

  result = new interval_set_iterator(*this, xis_full_iterator);
  
  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

void
sheaf::interval_set::
put_interval(pod_type xbegin, pod_type xend, bool xvalue)
{
  // Preconditions:

  // Body:

  // The map contains n entries {e(i) = (end, value), 0 <= i < n}
  // and two implicit entries e(-1) = (before_end, false) and
  // e(n) = (max_pod_index, false).
  // These entries partition the src id space into n+1 intervals:
  //
  // r(-1) = [min_pod_index, e(-1)],
  // r(0) = [e(-1)+1, e(0)],
  // ... ,
  // r(i) = [r(i-1)+1, e(i)],
  // ... ,
  // r(n) = [e(n-1)+1, e(n)].
  //
  // The value of the map at an index p is equal to lower_bound(p).mapped_value.
  //
  // The interval defined by [xbegin, xend] we will refer to as
  // the "new interval". The interval r(l) = [e(l-1), e(l)) that satisfies
  // e(l-1) < xbegin <= e(l) will be referred to as the "left interval".
  // Similarly, the interval r(r) = [e(r-1), e(r)) that satisfies e(r-1) <
  // xend <= e(r) will be referred to as the "right interval".
  //
  // The policy is that the new interval takes precedence over any existing
  // intervals, so typically the left interval is truncated on the right
  // by inserting a new entry (xbegin-1, old contains_member(xbegin)) and the
  // right interval is truncated on the left inserting a new entry
  // (xend, xvalue). Any existing entries that lie completely with the new
  // interval are erased.
  //
  // Two special conditions complicate this typical case:
  // (1) either xbegin or xend fall on an existing entry, and/or
  // (2) the new interval extends an existing interval.
  // Condition (1) requires dealing with the existing record and
  // changes how to detect condition (2). Condition (2) requires merging
  // intervals by either not inserting records or erasing them.
  //
  // If xbegin != e(i).key+1 for any i, then the new interval "right extends"
  // the left interval if xvalue == old contains_member(xbegin) and we don't
  // want to insert an entry for xbegin because it doesn't terminate
  // the left interval or begin the new interval.
  //
  // If xbegin == e(i).key+1 for some i, then the new interval right extends the
  // left interval if xvalue == e(i).value. Not only do we not want to insert
  // a new entry, we want to erase the existing record because it no longer
  // terminates the left interval or begins a new interval..
  //
  // Simlarly, if xend != e(i).key for any i, the new interval "left extends"
  // the right interval if xvalue == e(r).value and we don't want
  // to insert an entry for xend because it doesn't terminate the new
  // interval or begin the right interval.
  //
  // If xend == e(i) for some i, then the new interval left extends the
  // right interval if xvalue != e(i).value.  Not only do we not want to
  // insert a new entry, we want to erase the existing record because it
  // no longer begins the right interval or terminates a new interval.

  // Put the beginning of the interval.

  map_type::iterator litr = _interval_map.find(xbegin-1);
  if(litr != _interval_map.end())
  {
    // Begin == end of left interval.

    bool lold_begin = litr->second;
    if(lold_begin == xvalue)
    {
      // New interval right extends left interval;
      // remove the end of the existing interval.

      _interval_map.erase(litr);
    }
    else
    {
      // New interval terminates the left interval,
      // but it's already terminated properly; 
      // do nothing.
    }
  }
  else
  {
    // Begin is not the end of an existing interval.

    bool lold_begin = contains_member(xbegin);
    if(lold_begin == xvalue)
    {
      // New interval right extends left interval; 
      // do nothing.
    }
    else
    {
      // New interval right truncates left interval.

      _interval_map[xbegin-1] = lold_begin;
    }
  }

  // Put the end of the interval.

  bool lold_end = contains_member(xend);

  litr = _interval_map.find(xend);
  if(litr != _interval_map.end())
  {
    // End == begin of right interval.

    if(lold_end == xvalue)
    {
      // Make entry to terminate new interval;
      // nothing to do.
    }
    else
    {
      // New interval left extends right interval;
      // remove the begin of the existing interval.

      _interval_map.erase(litr);
    }
  }
  else
  {
    // End is not beginning of right interval.

    if(lold_end == xvalue)
    {
      // New interval left extends right interval; 
      // do nothing.
    }
    else
    {
      // Make entry to terminate new interval;
      // truncates right interval.

      _interval_map[xend] = xvalue;
    }
  }    
  
  // Clear any existing entries within the interval.

  litr = _interval_map.lower_bound(xbegin);
  while(litr != _interval_map.end() && litr->first < xend)
  {
    _interval_map.erase(litr);
    litr = _interval_map.lower_bound(xbegin);
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


// =============================================================
// INTERVAL MAP FACET
// =============================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::interval_set::map_type&
sheaf::interval_set::
interval_map() const
{
  return _interval_map;
}

bool
sheaf::interval_set::
first_map_entry() const
{
  // Preconditions:

  require(!is_empty());

  // Body:

  bool result = _interval_map.begin()->second;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::interval_set::
last_map_entry() const
{
  // Preconditions:

  require(!is_empty());

  // Body:

  bool result = (--_interval_map.end())->second;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================
// ANY FACET
// =============================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::interval_set::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const interval_set*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::interval_set*
sheaf::interval_set::
clone() const
{
  // Preconditions:

  // Body:

  interval_set* result = new interval_set();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_empty());

  // Exit:

  return result;
}

sheaf::interval_set&
sheaf::interval_set::
operator=(const interval_set& xother)
{
  // Preconditions:

  // Body:

  _interval_map = xother._interval_map;
  
  // Postconditions:

  ensure(*this == xother);
  
  // Exit:

  return *this;
}

bool
sheaf::interval_set::
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

    invariance(is_empty() || !first_map_entry());
    invariance_for_range(map_iterator_type itr = interval_map().begin(); pod_type i=0,
			 itr != interval_map().end(), ++itr; ++i,
			 itr->second == (i%2 == 1));
    invariance(is_empty() || last_map_entry());
    
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
ostream&
sheaf::operator << (ostream& xos, const interval_set& xset)
{
  // Preconditions:

  // Body:

  xos << endl << "begin: " << xset.begin()
      << endl << "end:   " << xset.end() << endl;

  xos << endl << "members:" << endl;
  interval_set_iterator* litr = xset.iterator(true);
  while(!litr->is_done())
  {
    interval_set::pod_type litem = litr->item();
    xos << litem << " ";

    litr->next();
  }
  delete litr;
  
  xos << endl << endl << "non-members:" << endl;
  litr = xset.iterator(false);
  while(!litr->is_done())
  {
    interval_set::pod_type litem = litr->item();
    xos << litem << " ";

    litr->next();
  }
  delete litr;

  xos << endl;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
sheaf::deep_size(const interval_set& xset, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xset) : 0;

  // Add the member allocated in member _interval_map.

  typedef interval_set::pod_type pod_type;
  typedef no_deep_size_policy<map<pod_type, bool> > map_policy_type;
  result += deep_size<pod_type, bool, map_policy_type>(xset._interval_map, false);

  // Preconditions:

  // Exit:

  return result;
}
