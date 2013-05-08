

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class interval_index_space_state

#include "interval_index_space_state.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "interval_index_space_handle.h"
#include "interval_index_space_iterator.h"
#include "deep_size.h"
#include "hub_index_space_handle.h"
#include "scoped_index.h"

// ===========================================================
// INTERVAL_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
sheaf::interval_index_space_state::
make_arg_list(bool xmerge_mode)
{
  // Preconditions:

  // Body:

  arg_list result = mutable_index_space_state::make_arg_list();
  result << "merge_mode" << xmerge_mode;

  // Postconditions:

  ensure(result.contains_arg("merge_mode"));
  ensure(result.value("merge_mode") == xmerge_mode);

  // Exit:

  return result;
} 

// PROTECTED MEMBER FUNCTIONS

void
sheaf::interval_index_space_state::
insert_map_interval(pod_type xdomain_begin, 
		    pod_type xdomain_end, 
		    pod_type xrange_begin, 
		    pod_type xrange_end,
		    map<pod_type, pod_type>& xmap,
		    bool xmerge_mode)
{
  // Preconditions:

  // Body:

  // The map contains n entries {e(i) = (domain, range), 0 <= i < n}
  // and two implicit  entries e(-1) = (min_pod_index, invalid) and 
  // e(n) = (max_pod_index, invalid).
  // These entries partition the domain id space into n+1 intervals:
  //
  // I(0) = [e(-1), e(0)-1], 
  // I(1) = [e(0), e(1)-1], 
  // ... , 
  // I(i) = [e(i-1), e(i)-1],
  // ... , 
  // I(n) = [e(n-1), e(n)].
  //
  // An interval I(i) contains a domain id d if and only if e(i-1) <= d < e(i).
  //
  // The value of the map at an index p is calculated by finding
  // e(i) = lower_bound(p) and interpolating back from e(i).domain to p;
  // see function map_value for the details.
  //
  // We will refer to the interval defined by [xdomain_begin, xdomain_end] 
  // as the "new interval". The existing interval that contains xdomain_begin
  // will be referred to as the "left interval". Similarly, the existing interval 
  // that contains xdomain_end will be referred to as the "right interval". 
  //
  // The policy is that the new interval takes precedence over any existing
  // intervals, so typically the left interval is truncated on the right by inserting
  // a new entry (xdomain_begin, old map_value(xdomain_begin)) and the right
  // interval is truncated on the left inserting a new entry (xdomain_end, xrange_end).
  // Any existing entries that lie completely with the new interval are erased.
  //
  // Two special conditions complicate this typical case:
  // (1) either xdomain_begin or xdomain_end falls on an existing entry, and/or
  // (2) the new interval extends an existing interval.
  // Condition (1) requires dealing with the existing record and
  // changes how to detect condition (2). Condition (2) requires merging
  // intervals by either not inserting records or erasing them.
  //
  // If xdomain_begin-1 != e(i) for any i, then the new interval "right extends" 
  // the left interval if xrange_begin == old map_value(xdomain_begin-1)+1 and we don't
  // want to insert an entry for xdomain_begin because it doesn't terminate
  // the left interval or begin the new interval.
  //
  // If xdomain_begin-1 == e(i) for some i, then the new interval right extends the 
  // left interval if xrange_begin-1 == e(i).range. Not only do we not want to insert
  // a new entry, we want to erase the existing record because it no longer
  // terminates the left interval or begins a new interval.
  //
  // Simlarly, if xdomain_end != e(i) for any i, the new interval "left extends" 
  // the right interval if xrange_end == map_value(xdomain_end) and we don't want
  // to insert an entry for xdomain_end because it doesn't terminate the new
  // interval or begin the right interval.
  //
  // If xdomain_end == e(i) for some i, then the condition that the new interval 
  // left extends the right interval is xrange_end == e(i).range. But since
  // xdomain_end then just duplicates the existing entry, we don't need to do anything.

  // Put the beginning of the interval.

  pod_type left_of_xrange_begin = 
    is_valid(xrange_begin) ? xrange_begin - 1 : xrange_begin;
    
  map_type::iterator litr = xmap.find(xdomain_begin - 1);
  if(litr != xmap.end())
  {
    // Begin-1 == end of left interval.

    pod_type lold_range_end = litr->second;

    if(xmerge_mode && (lold_range_end == left_of_xrange_begin))
    {
      // New interval right extends left interval;
      // remove the end of the existing interval.

      xmap.erase(litr);
    }
    else
    {
      // New interval right truncates the left interval.
      // do nothing.
    }
  }
  else
  {
    // Begin is not the end of an existing interval.

    pod_type lold_range_begin = map_value(xdomain_begin, xmap);
    if(xmerge_mode && (lold_range_begin == xrange_begin))
    {
      // New interval right extends left interval; 
      // do nothing.
    }
    else
    {
      // New interval right truncates left interval.

      xmap[xdomain_begin-1] =
	is_valid(lold_range_begin) ? lold_range_begin - 1 : lold_range_begin;
    }
  }

  // Put the end of the interval.
  
  pod_type lold_range_end = map_value(xdomain_end, xmap);

  litr = xmap.find(xdomain_end);
  if(litr != xmap.end())
  {
    // End == end of left interval.

    if(xmerge_mode && (xrange_end == litr->second))
    {
      // New entry duplicates existing entry;
      // do nothing.
    }
    else
    {
      // Make entry to terminate new interval;
      // erase existing entry.

      xmap.erase(litr);

      lold_range_end = map_value(xdomain_end, xmap);
      if(xmerge_mode && (xrange_end == lold_range_end))
      {
	// New entry left extends right interval;
	// do nothing.
      }
      else
      {
	// New entry left truncates right interval.

	xmap[xdomain_end] = xrange_end;
      }
    }
  }
  else
  {
    // End is not beginning of right interval.

    if(xmerge_mode && (xrange_end == lold_range_end))
    {
      // New interval left extends right interval; 
      // do nothing.
    }
    else
    {
      // Make entry to terminate new interval;
      // truncates right interval.

      xmap[xdomain_end] = xrange_end;
    }
  }

  // Clear any existing entries within the interval. 

  litr = xmap.lower_bound(xdomain_begin);
  while(litr != xmap.end() && litr->first < xdomain_end)
  {
    xmap.erase(litr);
    litr = xmap.lower_bound(xdomain_begin);
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::interval_index_space_state::pod_type
sheaf::interval_index_space_state::
map_value(pod_type xid, const map<pod_type, pod_type>& xmap)
{
  // Preconditions:

  // Body:

  pod_type result;

  map_type::const_iterator itr = xmap.lower_bound(xid);
  if(itr != xmap.end() && is_valid(itr->second))
  {
    // Xid is in a mapped interval;
    // difference between result and domain end of interval
    // same as difference between xid and range end of interval.

    result = itr->second - (itr->first - xid);
  }
  else
  {
    // Xid is not in a mapped interval;
    // result is invalid.

    result = invalid_pod_index();
  }

  // Postconditions:

  // Exit

  return result;
}

sheaf::interval_index_space_state::
interval_index_space_state()
  : mutable_index_space_state()
{
  // Preconditions:
    
  // Body:
  
  _merge_mode = true;
  _capacity = 0;

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  ensure(merge_mode());
  ensure(capacity() == 0);

  // Exit:

  return; 
}

sheaf::interval_index_space_state::
interval_index_space_state(const arg_list& xargs)
  : mutable_index_space_state(xargs)
{
  // Preconditions:
    
  require(precondition_of(mutable_index_space_state::mutable_index_space_state(xargs)));
  require(xargs.contains_arg("merge_mode"));

  // Body:
  
  _merge_mode = xargs.value("merge_mode");
  _capacity = 0;

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(mutable_index_space_state::mutable_index_space_state(xargs)));
  ensure(merge_mode() == xargs.value("merge_mode"));
  ensure(capacity() == 0);

  // Exit:

  return; 
}

sheaf::interval_index_space_state::
~interval_index_space_state()
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
sheaf::interval_index_space_state::
insert_interval(pod_type xbegin, 
		pod_type xend,
		const scoped_index& xhub_begin, 
		const scoped_index& xhub_end)
{
  // Preconditions:

  require(xhub_begin.in_scope());
  require(xhub_end.in_scope());
  require(precondition_of(insert_interval(xbegin, xend.
					  xhub_begin.hub_pod(),
					  xhub_end.hub_pod())));

  // Body:

  insert_interval(xbegin, xend,
		  xhub_begin.hub_pod(), xhub_end.hub_pod());

  // Postconditions:

  ensure(postcondition_of(insert_interval(xbegin, xend,
					  xhub_begin.hub_pod(),
					  xhub_end.hub_pod())));

  // Exit:

  return;
}  

void
sheaf::interval_index_space_state::
insert_interval(pod_type xbegin, 
		pod_type xend, 
		pod_type xhub_begin, 
		pod_type xhub_end)
{
  // Preconditions:

  require(xhub_begin <= xhub_end);
  require(xbegin <= xend);
  require((xhub_end - xhub_begin) == (xend - xbegin));
  
  // Body:

  // Define old variables.

  define_old_variable(pod_type old_ct = ct());

  pod_type old_invalid_entry_ct = invalid_entry_ct(xhub_begin, xhub_end);

  // Insert the interval.

  map_rep_insert_interval(xbegin, xend, xhub_begin, xhub_end);

  // If this is the first interval, initialize the extrema.

  if(_ct == 0)
  {
    // First interval, initialize the extrema.

    _begin = xbegin;
    _end = xend + 1;
  }
  else
  {
    // Not the first interval, update the extrema.

    if(xbegin < _begin)
    {
      _begin = xbegin;
    }

    if(xend >= _end)
    {
      _end = xend + 1;
    }
  }
  
  // Update the count.

  _ct += old_invalid_entry_ct;  

  // Postconditions:

  ensure(ct() >= old_ct);
  ensure_for_range(pod_type i=xhub_begin, i<=xhub_end, ++i, pod(i) == xbegin+(i-xhub_begin));
  ensure_for_range(pod_type i=xbegin, i<=xend, ++i, hub_pod(i) == xhub_begin+(i-xbegin));

  // Exit:

  return;
}

void
sheaf::interval_index_space_state::
push_interval(const scoped_index& xhub_begin, const scoped_index& xhub_end)
{
  // Preconditions:

  require(xhub_begin.in_scope());
  require(xhub_end.in_scope());
  require(precondition_of(push_interval(xhub_begin.hub_pod(),
					xhub_end.hub_pod())));

  // Body:

  push_interval(xhub_begin.hub_pod(), xhub_end.hub_pod());

  // Postconditions:

  ensure(postcondition_of(push_interval(xhub_begin.hub_pod(),
					xhub_end.hub_pod())));

  // Exit:

  return;
}

void
sheaf::interval_index_space_state::
push_interval(pod_type xhub_begin, pod_type xhub_end)
{
  // Preconditions:

  require(xhub_begin <= xhub_end);
 
  // Body:

  // Define old variables.

  define_old_variable(pod_type old_ct = ct());

  pod_type old_next_id = next_id();

  insert_interval(old_next_id, old_next_id + (xhub_end - xhub_begin),
		  xhub_begin, xhub_end);

  // Postconditions:

  ensure(ct() == old_ct + (xhub_end - xhub_begin + 1));
  ensure(next_id() == old_next_id + (xhub_end - xhub_begin + 1));
  ensure_for_range(pod_type i=xhub_begin, i<=xhub_end, ++i, pod(i) == old_next_id+(i-xhub_begin));

  // Exit:

  return;
}

sheaf::size_type
sheaf::interval_index_space_state::
remove_interval(const scoped_index& xhub_begin,
		const scoped_index& xhub_end)
{
  // Preconditions:

  require(xhub_begin.in_scope());
  require(xhub_end.in_scope());
  require(precondition_of(remove_hub_interval(xhub_begin.hub_pod(),
					      xhub_end.hub_pod())));

  // Body:

  size_type result = remove_hub_interval(xhub_begin.hub_pod(),
					 xhub_end.hub_pod());

  // Postconditions:

  ensure(postcondition_of(remove_hub_interval(xhub_begin.hub_pod(),
					      xhub_end.hub_pod())));
  
  // Exit:

  return result;
}

sheaf::size_type
sheaf::interval_index_space_state::
remove_hub_interval(pod_type xhub_begin, pod_type xhub_end)
{
  // Preconditions:

  require(xhub_begin <= xhub_end);

  // Body:

  // Remove the interval.

  size_type result = map_rep_remove_interval(xhub_begin, xhub_end, true);

  // Update the count.

  _ct -= result;

  // Update the extrema.

  update_extrema();

  // Postconditions:

  ensure_for_range(pod_type i=xhub_begin, i<=xhub_end, ++i, !contains_hub(i));  

  // Exit

  return result;
}

sheaf::size_type
sheaf::interval_index_space_state::
remove_interval(pod_type xbegin, pod_type xend)
{
  // Preconditions:

  require(xbegin <= xend);

  // Body:

  // Remove the interval.

  size_type result = map_rep_remove_interval(xbegin, xend, false);

  // Update the count.

  _ct -= result;

  // Update the extrema.

  update_extrema();

  // Postconditions:

  ensure_for_range(pod_type i=xbegin, i<=xend, ++i, !contains(i));

  // Exit

  return result;
}

sheaf::interval_index_space_state::pod_type
sheaf::interval_index_space_state::
interval_begin(const scoped_index& xid) const
{
  // Preconditions:

  require(xid.in_scope());
  require(precondition_of(interval_begin(xid.hub_pod())));

  // Body:

  pod_type result = interval_begin(xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(interval_begin(xid.hub_pod())));

  // Exit:

  return result;
}

sheaf::interval_index_space_state::pod_type
sheaf::interval_index_space_state::
interval_begin(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result;

  to_domain_type::const_iterator itr = _to_domain.lower_bound(xhub_id);
  if(itr != _to_domain.end() && is_valid(itr->second))
  {
    // Xhub_id is in a mapped interval; begin of the interval 
    // is the preceeding entry in the map + 1.

    --itr;
    result = itr->first + 1;
  }
  else
  {
    // Xhub_id is not in a mapped interval;
    // result is invalid.

    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));
  
  // Exit:

  return result;
}

sheaf::interval_index_space_state::pod_type
sheaf::interval_index_space_state::
interval_end(const scoped_index& xid) const
{
  // Preconditions:

  require(xid.in_scope());
  require(precondition_of(interval_end(xid.hub_pod())));

  // Body:

  pod_type result = interval_end(xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(interval_end(xid.hub_pod())));

  // Exit:

  return result;
}

sheaf::interval_index_space_state::pod_type
sheaf::interval_index_space_state::
interval_end(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result;

  to_domain_type::const_iterator itr = _to_domain.lower_bound(xhub_id);
  if(itr != _to_domain.end() && is_valid(itr->second))
  {
    // Xhub_id is in a mapped interval;

    result = itr->first;
  }
  else
  {
    // Xhub_id is not in a mapped interval;
    // result is invalid.

    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));

  // Exit:

  return result;
}

bool
sheaf::interval_index_space_state::
merge_mode() const
{
  // Preconditions:

  // Body:

  bool result = _merge_mode;

  // Postcondtions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::interval_index_space_state::
put_merge_mode(bool xvalue)
{
  // Preconditions:

  // Body:

  _merge_mode = xvalue;

  // Postconditions:

  ensure(merge_mode() == xvalue);
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::size_type
sheaf::interval_index_space_state::
invalid_entry_ct(pod_type xhub_begin, pod_type xhub_end) const
{
  // Preconditions:

  // Body:

  size_type result = xhub_end - xhub_begin + 1;

  pod_type lold_range_id = xhub_begin - 1;

  to_domain_type::const_iterator itr = _to_domain.lower_bound(xhub_begin);

  while(itr != _to_domain.end() && itr->first <= xhub_end)
  {
    if(is_valid(itr->second))
    {
      // The existing interval is populated, calculate the number of entries
      // in the input interval.

      if(itr->first < xhub_end)
      {
	// The existing interval is completely in the input interval;
	// Add the entire existing interval.

	result -= (itr->first - lold_range_id);
      }
      else
      {
	// The existing interval is only partly in the input interval;
	// Add the remaining input interval.

	result -= (xhub_end - lold_range_id);
	break;
      }
    }

    // Advance the iterator.

    lold_range_id = itr->first;
    ++itr;
  }
  
  // Preconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}      

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MUTABLE INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::interval_index_space_state::
update_extrema()
{
  // Preconditions:

  // Body:

  if(_ct == 0)
  {
    // The map is empty; invalidate the extrema.

    invalidate_extrema();
  }
  else
  {
    // Extract the extrema from the map.

    // Begin is the entry in _to_range 
    // before the first entry with a valid domain.

    to_range_type::const_iterator itr = _to_range.begin();
    while(itr != _to_range.end())
    {
      if(is_valid(itr->second))
      {
	--itr;
	_begin = itr->first + 1;
	break;
      }
      ++itr;
    }

    // End is last entry in _to_range with valid range.

    to_range_type::reverse_iterator ritr = _to_range.rbegin();
    while(ritr != _to_range.rend())
    {
      if(is_valid(ritr->second))
      {
	_end = ritr->first + 1;
	break;
      }
      ++ritr;
    }
  }

  // Postconditions:

  // Exit

  return;
}

void
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
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

void
sheaf::interval_index_space_state::
print_map_rep(ostream& xos) const
{
  // Preconditions:

  // Body:

  xos << "_to_range: " << endl;
  
  for(map_type::const_iterator litr=_to_range.begin(); litr!=_to_range.end(); ++litr)
  {
    xos << "  (" << litr->first << ", " << litr->second << ")";
  }
  xos << endl;  

  xos << "_to_domain: " << endl;
  
  for(map_type::const_iterator litr=_to_domain.begin(); litr!=_to_domain.end(); ++litr)
  {
    xos << "  (" << litr->first << ", " << litr->second << ")";
  }  
  xos << endl;  

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::interval_index_space_state::
map_rep_insert_interval(pod_type xdomain_begin,
			pod_type xdomain_end, 
			pod_type xrange_begin, 
			pod_type xrange_end)
{
  // Preconditions:

  require(xrange_begin <= xrange_end);
  require(xdomain_begin <= xdomain_end);
  require((xrange_end - xrange_begin) == (xdomain_end - xdomain_begin));
  
  // Body:

  insert_map_interval(xdomain_begin, xdomain_end,
		      xrange_begin, xrange_end,
		      _to_range, _merge_mode);

  insert_map_interval(xrange_begin, xrange_end,
		      xdomain_begin, xdomain_end,
		      _to_domain, _merge_mode);

  // Postconditions:

  ensure_for_range(pod_type i=0, i<xrange_end-xrange_begin+1, ++i, pod(xrange_begin+i) == xdomain_begin+i);
  ensure_for_range(pod_type i=0, i<xdomain_end-xdomain_begin+1, ++i, hub_pod(xdomain_begin+i) == xrange_begin+i);

  // Exit:

  return;
}

sheaf::size_type
sheaf::interval_index_space_state::
map_rep_remove_interval(pod_type xbegin, pod_type xend, bool xis_range_id)
{
  // Preconditions:

  require(xbegin <= xend);

  // Body:

  pod_type lbegin = xis_range_id ? xbegin : map_value(xbegin, _to_range);
  pod_type lend = xis_range_id ? xend : map_value(xend, _to_range);

  size_type result = 0;

  // Remove any mapped intervals included in [lbegin, lend)
  // from the _to_range direction.

  const pod_type linvalid = invalid_pod_index();

  pod_type lrange_begin = lbegin;
  pod_type lmapped_range_end = map_value(lend, _to_domain);

  to_domain_type::iterator litr = _to_domain.lower_bound(lrange_begin);
  while((lrange_begin <= lend) && (litr != _to_domain.end()))
  {
    pod_type lrange_end;
    pod_type ldomain_end;
    
    if(litr->first <= lend)
    {
      // Found interval completely contained 
      // in [lbegin, lend].

      lrange_end = litr->first;
      ldomain_end = litr->second;
    }
    else
    {
      // Found interval only partly contained
      // in [lbegin, lend].

      lrange_end = lend;
      ldomain_end = lmapped_range_end;
    }
    
    if(is_valid(ldomain_end))
    {
      // Found an included mapped interval; 
      // remove it from the _to_range map.

      pod_type ldomain_begin = ldomain_end - (lrange_end - lrange_begin);

      insert_map_interval(ldomain_begin, ldomain_end, linvalid, linvalid, _to_range, _merge_mode);

      // Add the number of ids removed from this mapped interval.

      result += lrange_end - lrange_begin + 1;
    }

    lrange_begin = lrange_end + 1;
    litr = _to_domain.lower_bound(lrange_begin);
  }

  // Remove [lbegin, lend] from the _to_domain direction.

  insert_map_interval(lbegin, lend, linvalid, linvalid, _to_domain, _merge_mode);

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::interval_index_space_state::
map_rep_insert_entry(pod_type xdomain_id, pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));
  require(!contains(xdomain_id));

  // Body:

  map_rep_insert_interval(xdomain_id, xdomain_id, xrange_id, xrange_id);

  // Not finished inserting entry; do not ensure invariant.

  ensure(contains(xdomain_id, xrange_id));
  
  // Exit

  return;
}

void
sheaf::interval_index_space_state::
map_rep_push_back(pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));

  // Body:

  pod_type old_next_id = next_id();

  map_rep_insert_interval(old_next_id, old_next_id, xrange_id, xrange_id);

  // Postconditions:

  // Not finished pushing back; do not ensure invariant.

  ensure(contains(old_next_id, xrange_id));

  // Exit

  return;
}

void
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
map_rep_remove_entry(pod_type xid, bool xis_range_id)
{
  // Preconditions:

  // Body:

  pod_type lid = xis_range_id ? xid : map_value(xid, _to_range);

  size_type result = map_rep_remove_interval(lid, lid, true);
  
  // Postconditions:

  // Not finished removing entry; do not ensure invariant.

  ensure(xis_range_id ? !contains_hub(xid) : !contains(xid));  

  // Exit

  return result;
}

void
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
map_rep_gather()
{
  // Preconditions:

  // Body:

  ///
  /// @todo Need to alter this algorthim to take into account ids deleted
  ///       from the hub id space.  This includes adjusting the interval,
  ///       adjusting _ct and updating the range extrema.
  ///

  // Clear the domain map.

  _to_domain.clear();

  // Get the first entry.

  to_range_type::iterator litr = _to_range.begin();
  assertion(!is_valid(litr->second));

  // Add the first entry.

  pod_type ldomain_end = -1;
  pod_type lrange_end = litr->second;

  _to_domain[lrange_end] = invalid_pod_index();
  _to_range[ldomain_end] = invalid_pod_index();

  // Start the iteration.

  pod_type lold_domain_end;
  pod_type lct;
  pod_type lrange_begin;

  while(litr != _to_range.end())
  {
    lrange_end = litr->second;

    if(is_valid(lrange_end))
    {
      lct = (litr->first - lold_domain_end);
      ldomain_end += lct;

      _to_domain[lrange_end] = ldomain_end;
      _to_range[ldomain_end] = lrange_end;

      lrange_begin = (lrange_end - lct);

      if(_to_domain.find(lrange_begin) == _to_domain.end())
      {
	// There is no entry at range begin, add an invalid entry.

	_to_domain[lrange_begin] = invalid_pod_index();
      }
    }

    lold_domain_end = litr->first;
    
    // Copy the iterator.

    to_range_type::iterator lerase_itr = litr;

    // Advance the iterator.

    litr++;

    // Erase the old entry.

    if(ldomain_end != lold_domain_end)
      _to_range.erase(lerase_itr);
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
sheaf::interval_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const interval_index_space_state& lother =
    dynamic_cast<const interval_index_space_state&>(xother);

  bool result = mutable_index_space_state::operator==(xother);
  result = result && (_to_range == lother._to_range);
  result = result && (_to_domain == lother._to_domain);
  result = result && (_merge_mode == lother._merge_mode);
  result = result && (_capacity == lother._capacity);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::interval_index_space_state::
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

sheaf::interval_index_space_state&
sheaf::interval_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const interval_index_space_state& lother =
    dynamic_cast<const interval_index_space_state&>(xother);

  _to_domain   = lother._to_domain;
  _to_range  = lother._to_range;
  _merge_mode = lother._merge_mode;
  _capacity   = lother._capacity;

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
sheaf::interval_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  to_range_type::const_iterator itr = _to_range.lower_bound(xid);

  bool result = (itr != _to_range.end()) && is_valid(itr->second);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::interval_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  to_domain_type::const_iterator itr = _to_domain.lower_bound(xhub_id);
  
  bool result = (itr != _to_domain.end()) && is_valid(itr->second);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::interval_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result = map_value(xhub_id, _to_domain);

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::interval_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = map_value(xid, _to_range);

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
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  interval_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::interval_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<interval_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::interval_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const interval_index_space_handle* lid_space =
    dynamic_cast<const interval_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::interval_index_space_handle>&
sheaf::interval_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<interval_index_space_handle> result;

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
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
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
sheaf::interval_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  interval_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::interval_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<interval_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::interval_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const interval_index_space_iterator* litr =
    dynamic_cast<const interval_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::interval_index_space_iterator>&
sheaf::interval_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<interval_index_space_iterator> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
sheaf::interval_index_space_state::
class_name() const
{
  static const string result("interval_index_space_state");
  return result;
}

sheaf::interval_index_space_state*
sheaf::interval_index_space_state::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  interval_index_space_state* result = new interval_index_space_state(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::interval_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  interval_index_space_state* lproto = new interval_index_space_state();

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
sheaf::interval_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const interval_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::interval_index_space_state::
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
deep_size(const interval_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const mutable_index_space_state& ixn = static_cast<const mutable_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Add the memory allocated in member _to_domain.

  typedef interval_index_space_state::pod_type pod_type;
  typedef interval_index_space_state::map_type map_type;
  typedef no_deep_size_policy<map_type> map_policy_type;
  result += deep_size<pod_type, pod_type, map_policy_type>(xn._to_domain,
							   false);

  // Add the memory allocated in member _to_range.

  result += deep_size<pod_type, pod_type, map_policy_type>(xn._to_range,
							   false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
