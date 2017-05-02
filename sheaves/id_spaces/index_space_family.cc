
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
/// Implementation for class index_space_family

#include "SheafSystem/index_space_family.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/explicit_index_space_interval.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/index_equivalence_iterator.h"
#include "SheafSystem/index_space_family_iterator.h"
#include "SheafSystem/index_space_interval_iterator.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/interval_index_space_state.h"
#include "SheafSystem/scattered_insertion_index_space_handle.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/primary_index_space_handle.h"
#include "SheafSystem/primary_sum_index_space_state.h"
#include "SheafSystem/scoped_index.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_set.h"

using namespace std;

// ===========================================================
// INDEX_SPACE_FAMILY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_family::
index_space_family()
  : _end(0),
    _standard_end(0),
    _explicit_interval(0),
    _next_explicit_id(0)
{
  // Preconditions:
    
  // Body:

  // Create the primary sum id space state.

  _hub_id_space =
    primary_sum_index_space_state::new_space(const_cast<index_space_family&>(*this),
					     hub_id_space_name());

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::index_space_family::
~index_space_family()
{  
  // Preconditions:
    
  // Body:

  // Delete the intervals.

  interval_map_type::iterator litr = _intervals.begin();
  
  while(litr != _intervals.end())
  {
    index_space_interval* linterval = litr->second;
    ++litr;

    if(linterval != 0)
    {
      delete linterval;
    }
  }

  // Postconditions:

  // Exit:

  return;
}

std::string
sheaf::index_space_family::
name(pod_type xid) const
{
  // Preconditions:

  // Body:

  string result = _name_to_index.name(xid);

  // Postconditions:

  ensure(result.empty() || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
index(const std::string& xname) const
{
  // Preconditions:

  require(!xname.empty());

  // Body:

  pod_type result = _name_to_index.index(xname);

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

void
sheaf::index_space_family::
put_name(pod_type xid, const std::string& xname)
{
  // Preconditions:

  require(contains(xid));
  require(!contains(xname));

  // Body:

  _name_to_index.put_entry(xid, xname, false);

  // Postconditions:

  ensure(contains(xname));

  // Exit:

  return;
}

bool
sheaf::index_space_family::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  const index_space_collection* lcollection = collection(xid);

  bool result = (lcollection != 0) && lcollection->contains_family(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(const std::string& xname) const
{
  // Preconditions:

  // Body:

  pod_type lid = _name_to_index.index(xname);

  bool result = is_valid(lid) ? contains(lid) : false;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
begin() const
{
  // Preconditions:

  // Body:

  pod_type result = 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
end() const
{
  // Preconditions:

  // Body:

  pod_type result = _end;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
has_only_standard_id_spaces() const
{
  // Preconditions:

  // Body:

  bool result = (_standard_end == _end);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_family::
update_standard_id_spaces()
{
  // Preconditions:

  // Body:

  _standard_end = _end;
  _hub_id_space.update_standard_ids();

  // Postconditions:

  ensure(has_only_standard_id_spaces());
  ensure(hub_id_space().has_only_standard_ids());

  // Exit:

  return;
}

void
sheaf::index_space_family::
clear_id_spaces()
{
  // Preconditions:

  // Body:

  // Remove non-standard id spaces.

  interval_map_type::iterator itr = _intervals.begin();
  while(itr != _intervals.end())
  {
    index_space_interval* linterval = itr->second;
	interval_map_type::iterator old_itr = itr;

    // Increment to next interval.

    itr++;

    if(linterval != 0)
    {
      // Check the interval.

      if(linterval->begin() >= _standard_end)
      {
	// Interval is completely outside the standard id spaces, delete it.

	_intervals.erase(old_itr);
	delete linterval;
      }
      else if((linterval->begin() < _standard_end) &&
	      (linterval->end() > _standard_end))
      {
	// Interval is partly outside the standard id spaces.

	assertion(dynamic_cast<explicit_index_space_interval*>(linterval) != 0);

	for(pod_type i=_standard_end; i<linterval->end(); ++i)
	{
	  linterval->remove(linterval->local_scope(i));
	}
      }
      else
      {
	// Interval complete inside the standard id spaces, do nothing.
      }
    }
  }

  // Update the end id space.

  _end = _standard_end;

  // Remove non-standard ids from primary sum id space.

  _hub_id_space.clear_ids();

  // Postconditions:

  ensure(invariant());
  ensure(has_only_standard_id_spaces());
  ensure(hub_id_space().has_only_standard_ids());

  // Exit:

  return;
}

sheaf::size_type&
sheaf::index_space_family::
max_rep_ids()
{
  // Preconditions:

  // Body:

  static size_type result = 300;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::index_space_family::
delete_space(pod_type xid)
{
  // Preconditions:

  require(xid != hub_id_space().index());
  require(contains(xid) ? !handle_conforms_to_state<primary_index_space_handle>(xid) : true);

  // Body:

  if(contains(xid))
  {
    if(is_explicit_interval(xid))
    {
      // The id space is explicit; delete the state object.

      delete_state(xid);
    }
    else
    {
      // The id space is implicit; delete the interval.

      delete_interval(xid);
    }
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(!contains(xid));

  // Exit:

  return;
}

void
sheaf::index_space_family::
delete_space(const std::string& xname)
{
  // Preconditions:

  require(xname != hub_id_space_name());
  require(contains(xname) ? !handle_conforms_to_state<primary_index_space_handle>(xname) : true);

  // Body:

  if(_name_to_index.contains_name(xname))
  {
    delete_space(_name_to_index.index(xname));
  }

  // Postconditions:

  ensure(invariant());
  ensure(!contains(xname));

  // Exit:

  return;
}

bool
sheaf::index_space_family::
is_explicit_interval(pod_type xid)
{
  // Preconditions:

  // Body:

  bool result =
    (dynamic_cast<explicit_index_space_interval*>(collection(xid)) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_family::pod_type
sheaf::index_space_family::
new_primary_state(size_type xct)
{
  // Preconditions:

  // Body:

  pod_type result = _hub_id_space.new_primary_term(xct);

  // Postconditions:

  ensure(invariant());
  ensure(contains(result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
new_primary_state(pod_type xid, size_type xct)
{
  // Preconditions:

  // Body:

  pod_type result = _hub_id_space.new_primary_term(xid, xct);

  // Postconditions:

  ensure(invariant());
  ensure(contains(result));

  // Exit:

  return result;
}

void
sheaf::index_space_family::
delete_primary_state(pod_type xid)
{
  // Preconditions:

  require(xid != hub_id_space().index());
  require(contains(xid));
  require(handle_conforms_to_state<primary_index_space_handle>(xid));

  // Body:

  // Remove the term from the hub id space..

  primary_index_space_handle& lterm =
    get_id_space<primary_index_space_handle>(xid);

  _hub_id_space.remove_term(lterm.hub_term_id());

  // Delete the state.

  delete_state(xid);
  
  // Postconditions:

  ensure(invariant());
  ensure(!contains(xid));

  // Exit:

  return;
}

void
sheaf::index_space_family::
new_state(const std::string& xname,
	  const std::string& xstate_class_name)
{
  // Preconditions:

  require(!xname.empty());
  require(!contains(xname));
  require(!xstate_class_name.empty());
  require(explicit_index_space_state::id_space_factory().contains_prototype(xstate_class_name));

  /// @hack See COM-475.  Remove this precondition once COM-475 is fixed.
  require(unexecutable("xstate_class_name is a mutable id space state"));

  // Body:

  explicit_index_space_state* lstate =
    explicit_index_space_state::id_space_factory().new_instance(xstate_class_name);

  lstate->new_state(const_cast<index_space_family&>(*this), xname, true);

  // Postconditions:

  ensure(invariant());
  ensure(contains(xname));

  /// @hack See COM-475.  Remove this postcondition once COM-475 is fixed.
  ensure(handle_conforms_to_state<scattered_insertion_index_space_handle>(xname));

  // Exit:

  return;
}

void
sheaf::index_space_family::
delete_state(pod_type xid)
{
  // Preconditions:

  // Body:

  index_space_collection* lcollection = collection(xid);

  if(lcollection != 0)
  {
    pod_type local_id = lcollection->local_scope(xid);

    // Get the explicit state.

    explicit_index_space_state* lstate = lcollection->explicit_state(local_id);

    // Remove the state from the collection.

    lcollection->remove(local_id);

    // Delete the explicit state, if there is one.

    if(lstate != 0)
    {
      delete lstate;
    }
  }

  // Delete the names.

  if(_name_to_index.contains_index(xid))
  {
    _name_to_index.delete_index(xid);
  }

  // Postconditions:

  ensure(invariant());
  ensure(!contains(xid));

  // Exit:

  return;
}

void
sheaf::index_space_family::
insert_interval(index_space_interval& xinterval)
{
  // Preconditions:

  require(xinterval.begin() == end());

  // Body:

  // Insert interval into the map.

  _intervals[xinterval.end()] = &xinterval;

  if(_intervals.find(xinterval.begin()) == _intervals.end())
  {
    // The beginning of the interval is not the end of some other
    // interval.

    _intervals[xinterval.begin()] = 0;
  }

  // Update the end of ths family.

  _end = xinterval.end();
  
  // Postconditions:

  // Exit:

  return;
}

void
sheaf::index_space_family::
delete_interval(pod_type xid)
{
  // Preconditions:

  require(xid != hub_id_space().index());
  require(!contains(xid) || !handle_conforms_to_state<primary_index_space_handle>(xid));

  // Body:

  if(contains(xid))
  {
    interval_iterator_type litr = _intervals.upper_bound(xid);
    pod_type lend = litr->first;

    index_space_interval* linterval = litr->second;

    interval_iterator_type lprevious = litr;
    lprevious--;
    pod_type lbegin = lprevious->first;

    interval_iterator_type lnext = litr;
    lnext++;

    if(!lprevious->second)
    {
      if((lnext == _intervals.end()) || (!lnext->second))
      {
	// Remove previous so that no void value is at the end or
	// back-to-back void values.

	_intervals.erase(litr);
	_intervals.erase(lprevious);
      }
      else
      {
	// Adjust the void value to be the beginning of the next.

	_intervals[lend] = 0;
	_intervals.erase(lprevious);
      }
    }
    else
    {
      if((lnext == _intervals.end()) || (!lnext->second))
      {
	// The void value is in the correct spot, erase current entry.

	_intervals.erase(litr);
      }
      else
      {
	// A void value needs inserted at the current entry.

	_intervals[lend] = 0;
      }
    }

    // Update the end.

    if(lend == _end)
    {
      // There should always be an interval.

      assertion(_intervals.begin() != _intervals.end());

      _end = (--_intervals.end())->first;
    }

    // Delete the interval.

    if(linterval != 0)
    {
      delete linterval;
    }
  }
     
  // Postconditions:

  ensure(invariant());
  ensure(!contains(xid));

  // Exit:

  return;
}

const sheaf::index_space_collection*
sheaf::index_space_family::
collection(pod_type xid) const
{
  // Preconditions:

  // Body:

  const_interval_iterator_type litr = _intervals.upper_bound(xid);

  const index_space_collection* result =
    (litr != _intervals.end()) ? litr->second : 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection*
sheaf::index_space_family::
collection(pod_type xid)
{
  // Preconditions:

  // Body:

  const_interval_iterator_type litr = _intervals.upper_bound(xid);

  index_space_collection* result =
    (litr != _intervals.end()) ? litr->second : 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
reserve_next_explicit_id()
{
  // Preconditions:

  // Body:

  define_old_variable(pod_type old_next_explicit_id = _next_explicit_id);

  // Find the explicit id space interval.

  if((_explicit_interval == 0) ||
     (_next_explicit_id == _explicit_interval->end()))
  {
    // Construct a new explicit id space interval.

    _explicit_interval =
      const_cast<explicit_index_space_interval*>(&explicit_index_space_interval::new_space(*this, explicit_interval_size()));

    _next_explicit_id = _explicit_interval->begin();
  }

  pod_type result = _next_explicit_id;

  // Increment the next explicit id.

  _next_explicit_id++;

  // Postconditions:

  ensure(is_explicit_interval(result));

  // Exit:

  return result;
}  

sheaf::size_type
sheaf::index_space_family::
explicit_interval_size()
{
  return EXPLICIT_INTERVAL_SIZE;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HUB ID SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_family::pod_type
sheaf::index_space_family::
new_id()
{
  // Preconditions:

  // Body:

  pod_index_type result = _hub_id_space.new_id();

  // Postconditions:

  ensure(hub_id_space().contains(result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
new_id(pod_type xid)
{
  // Preconditions:

  require(is_valid_reserved_id(xid));

  // Body:

  _hub_id_space.new_id(xid);

  // Postconditions:

  ensure(hub_id_space().contains(xid));

  // Exit:

  return xid;
}

void
sheaf::index_space_family::
delete_id(pod_type xid)
{
  // Preconditions:

  // Body:

  _hub_id_space.delete_id(xid);

  // Postconditions:

  ensure(!hub_id_space().contains(xid));

  // Exit:

  return;
}

const sheaf::hub_index_space_handle&
sheaf::index_space_family::
hub_id_space() const
{
  // Preconditions:

  // Body:

  const hub_index_space_handle& result = _hub_id_space;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf:: index_space_handle&
sheaf::index_space_family::
new_gathered_hub_id_space(bool xexclude_bottom)
{
  // Preconditions:

  require(!has_gathered_hub_id_space());

  // Body:

  const index_space_handle& result =
    _hub_id_space.new_gathered_id_space(xexclude_bottom);

  // Postconditions:

  ensure(has_gathered_hub_id_space());
  ensure(gathered_hub_id_space().is_gathered());
  ensure(xexclude_bottom == gathered_hub_id_space_excludes_bottom());

  // Exit:

  return result;
}

void
sheaf::index_space_family::
update_gathered_hub_id_space()
{
  // Preconditions:

  require(has_gathered_hub_id_space());

  // Body:

  _hub_id_space.update_gathered_id_space();

  // Postconditions:

  ensure(gathered_hub_id_space().is_gathered());

  // Exit:

  return;
}

const sheaf::index_space_handle&
sheaf::index_space_family::
gathered_hub_id_space() const
{
  // Preconditions:

  require(has_gathered_hub_id_space());

  // Body:

  const index_space_handle& result =
    _hub_id_space.gathered_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
has_gathered_hub_id_space() const
{
  // Preconditions:

  // Body:

  bool result = _hub_id_space.has_gathered_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
gathered_hub_id_space_excludes_bottom() const
{
  // Preconditions:

  // Body:

  bool result = _hub_id_space.gathered_id_space_excludes_bottom();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const std::string&
sheaf::index_space_family::
hub_id_space_name()
{
  // Preconditions:

  // Body:

  static const std::string result(poset_path::reserved_prefix() + "hub");

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_valid_reserved_id(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = _hub_id_space.is_valid_reserved_id(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::index_space_family::
term_of(pod_type xid) const
{
  // Preconditions:

  // Body:

  const index_space_handle& result = _hub_id_space.term_of(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::index_space_family::
term_of(const scoped_index& xid) const
{
  // Preconditions:

  // Body:

  const index_space_handle& result = _hub_id_space.term_of(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::index_space_family::
last_term() const
{
  // Preconditions:

  require(!hub_id_space().is_empty());

  // Body:

  const index_space_handle& result = _hub_id_space.last_term();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_family::
extend_last_term(size_type xct)
{
  // Preconditions:

  require(!hub_id_space().is_empty());

  // Body:

  define_old_variable(scoped_index old_last_term_begin(last_term(), last_term().begin()));

  // Extend the last term.

  _hub_id_space.extend_last_term(xct);

  // Postconditions:

  ensure_for_range(scoped_index i=old_last_term_begin, i<old_last_term_begin+xct, ++i, i.in_scope());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::index_space_family::
ct(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  size_type result = ct(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_family::
ct(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  size_type result = lcollection->ct(local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_empty(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = is_empty(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_empty(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  bool result = (ct(xspace_id) == 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
begin(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = begin(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
begin(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  pod_type result = lcollection->begin(local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
end(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = end(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
end(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  pod_type result = lcollection->end(local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
hub_begin(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = hub_begin(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
hub_begin(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  pod_type result = lcollection->hub_pod(local_id, lcollection->begin(local_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_gathered(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = is_gathered(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_gathered(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  bool result = (begin(xspace_id) == 0) && (end(xspace_id) == ct(xspace_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains(_name_to_index.index(xname), xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  bool result = lcollection->contains(local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(const std::string& xname, const scoped_index& xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains_hub(_name_to_index.index(xname), xid.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(pod_type xspace_id, const scoped_index& xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  bool result = contains_hub(xspace_id, xid.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains_hub(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains_unglued_hub(xname, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains_hub(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  bool result = contains_unglued_hub(xspace_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains_unglued_hub(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains_unglued_hub(_name_to_index.index(xname), xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains_unglued_hub(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  bool result = lcollection->contains_unglued_hub(local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains_glued_hub(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains_glued_hub(_name_to_index.index(xname), xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains_glued_hub(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  bool result =
    contains_unglued_hub(xspace_id, hub_id_space().unglued_hub_pod(xid));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(const std::string& xname, pod_type xid, const scoped_index& xhub_id) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains(_name_to_index.index(xname), xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(pod_type xspace_id, pod_type xid, const scoped_index& xhub_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  bool result = contains(xspace_id, xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(const std::string& xname, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = contains(_name_to_index.index(xname), xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
contains(pod_type xspace_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  bool result = lcollection->contains(local_id, xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
pod(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = pod(_name_to_index.index(xname), xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(xname, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
pod(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  pod_type result = lcollection->pod(local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(xspace_id, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
pod(const std::string& xname, const scoped_index& xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = pod(_name_to_index.index(xname), xid.hub_pod());

  // Postconditions:

  ensure(!is_valid(result) || contains(xname, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
pod(pod_type xspace_id, const scoped_index& xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  pod_type result = pod(xspace_id, xid.hub_pod());

  // Postconditions:

  ensure(!is_valid(result) || contains(xspace_id, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
hub_pod(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = unglued_hub_pod(xname, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(xname, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
hub_pod(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  pod_type result = unglued_hub_pod(xspace_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(xspace_id, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
unglued_hub_pod(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = unglued_hub_pod(_name_to_index.index(xname), xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xname, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
unglued_hub_pod(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  pod_type result = lcollection->hub_pod(local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xspace_id, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
glued_hub_pod(const std::string& xname, pod_type xid) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  pod_type result = glued_hub_pod(_name_to_index.index(xname), xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(xname, result));

  // Exit:

  return result;
}

sheaf::index_space_family::pod_type
sheaf::index_space_family::
glued_hub_pod(pod_type xspace_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  pod_type result =
    hub_id_space().glued_hub_pod(unglued_hub_pod(xspace_id, xid));

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(xspace_id, result));

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_persistent(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = is_persistent(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
is_persistent(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  bool result = lcollection->is_persistent(local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// GLUING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::index_space_family::
glue(pod_type xid, pod_type xrep)
{
  // Preconditions:

  require(hub_id_space().contains_unique_rep(xid)); // Can't already be glued.
  require(hub_id_space().contains_rep(xrep));
  require(hub_id_space().term_id(xid) > hub_id_space().term_id(xrep));
  
  // Body:

  _hub_id_space.glue(xid, xrep);

  // Postconditions:

  ensure(invariant());
  ensure(!hub_id_space().contains_rep(xid));
  ensure(hub_id_space().glued_hub_pod(xid) == xrep);
  
  // Exit:

  return;
}

void
sheaf::index_space_family::
unglue(pod_type xid)
{
  // Preconditions:

  require(hub_id_space().contains(xid));
  require(!hub_id_space().contains_rep(xid)); 
  
  // Body:

  _hub_id_space.unglue(xid);

  // Postconditions:

  ensure(invariant());
  ensure(hub_id_space().contains_unique_rep(xid));
  
  // Exit:

  return;
}

void
sheaf::index_space_family::
unglue_all(pod_type xrep_id)
{
  // Preconditions:

  require(hub_id_space().contains_rep(xrep_id)); 
  
  // Body:

  _hub_id_space.unglue_all(xrep_id);

  // Postconditions:

  ensure(invariant());
  ensure(hub_id_space().contains_unique_rep(xrep_id));
  
  // Exit:

  return;
}

bool
sheaf::index_space_family::
has_gluing() const
{
  // Preconditions:

  // Body:

  bool result = _hub_id_space.has_gluing();

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
sheaf::index_space_family::
new_product_structure(const std::string& xname,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xname));

  // Body:

 new_product_structure(_name_to_index.index(xname), xproduct);

  // Postconditions:

  ensure(has_product_structure(xname));

  // Exit:

  return;
}

void
sheaf::index_space_family::
new_product_structure(pod_type xspace_id,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  lcollection->new_product_structure(local_id, xproduct);

  // Postconditions:

  ensure(has_product_structure(xspace_id));

  // Exit:

  return;
}

void
sheaf::index_space_family::
delete_product_structure(const std::string& xname)
{
  // Preconditions:

  require(contains(xname));

  // Body:

  delete_product_structure(_name_to_index.index(xname));
  
  // Postconditions:

  ensure(!has_product_structure(xname));

  // Exit:

  return;
}

void
sheaf::index_space_family::
delete_product_structure(pod_type xspace_id)
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  lcollection->delete_product_structure(local_id);
  
  // Postconditions:

  ensure(!has_product_structure(xspace_id));

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::index_space_family::
product_structure(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));
  require(has_product_structure(xname));

  // Body:

  const abstract_product_structure& result =
    product_structure(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::abstract_product_structure&
sheaf::index_space_family::
product_structure(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));
  require(has_product_structure(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  const abstract_product_structure& result =
    lcollection->product_structure(local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::index_space_family::
product_structure(const std::string& xname)
{
  // Preconditions:

  require(contains(xname));
  require(has_product_structure(xname));

  // Body:

  abstract_product_structure& result =
    product_structure(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::index_space_family::
product_structure(pod_type xspace_id)
{
  // Preconditions:

  require(contains(xspace_id));
  require(has_product_structure(xspace_id));

  // Body:

  index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  abstract_product_structure& result =
    lcollection->product_structure(local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
has_product_structure(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  bool result = has_product_structure(_name_to_index.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
has_product_structure(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  bool result = lcollection->has_product_structure(local_id);

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
sheaf::index_space_family::
get_id_space(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  index_space_handle& result = get_id_space(_name_to_index.index(xname));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::index_space_handle&
sheaf::index_space_family::
get_id_space(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  index_space_handle& result = lcollection->get_id_space(local_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::index_space_family::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  collection(xid_space.index())->release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_family::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  bool result = collection(xid_space.index())->allocated_id_space(xid_space);

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

sheaf::index_space_iterator&
sheaf::index_space_family::
get_id_space_iterator(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  index_space_iterator& result = get_id_space_iterator(_name_to_index.index(xname));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

sheaf::index_space_iterator&
sheaf::index_space_family::
get_id_space_iterator(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  const index_space_collection* lcollection = collection(xspace_id);
  pod_type local_id = lcollection->local_scope(xspace_id);

  index_space_iterator& result = lcollection->get_id_space_iterator(local_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::index_space_family::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  collection(xitr.index())->release_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_family::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  bool result = collection(xitr.index())->allocated_id_space_iterator(xitr);

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
sheaf::index_space_family::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_family*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_space_family::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(begin() == 0);
    invariance(contains(hub_id_space_name()));
      
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
 
std::ostream& 
sheaf::
operator<<(std::ostream& xos, const index_space_family& xfamily)
{
  // Preconditions:

  // Body:

  // Collect the id spaces into two sets (primary and secondary).

  set<pod_index_type> lprimary;
  set<pod_index_type> lsecondary;

  index_space_family_iterator litr(xfamily, false);
  while(!litr.is_done())
  {
    if(litr.name().substr(0, 5) == "__hub")
    {
      // This is a primary id space.

      lprimary.insert(litr.index());
    }
    else
    {
      // This is a secondary id space.

      lsecondary.insert(litr.index());
    }

    litr.next();
  }

  xos << "id spaces" << endl;
  xos << "---------" << endl;
  xos << endl;
  
  xos << " begin = " << xfamily.begin() << endl;
  xos << " end   = " << xfamily.end() << endl << endl;

  xos << setw(10) << "index"
      << setw(32) << "name" 
      << setw(10) << "ct"
      << setw(10) << "begin"
      << setw(10) << "end"
      << setw(12) << "persistent"
      << endl;

  xos << setw(10)  << "---------"
      << setw(32)  << "-------------------------------" 
      << setw(10)  << "---------"
      << setw(10)  << "---------"
      << setw(10)  << "---------"
      << setw(12)  << "-----------"
      << endl;

  set<pod_index_type>::const_iterator lprimary_itr = lprimary.begin();

  // There's always a top id space and it must be first; print it out.

  size_type lct = xfamily.ct(*lprimary_itr);

  xos << setw(10) << *lprimary_itr
      << setw(32) << xfamily.name(*lprimary_itr)
      << setw(10) << lct;

  if(lct > 0)
  {
    xos << setw(10) << xfamily.begin(*lprimary_itr)
	<< setw(10) << xfamily.end(*lprimary_itr);
  }
  
  xos << endl;
  lprimary_itr++;

  // Print out any primary id spaces.

  xos << " primary:" << endl;  

  while(lprimary_itr != lprimary.end())
  {
    lct = xfamily.ct(*lprimary_itr);

    xos << setw(10) << *lprimary_itr
	<< setw(32) << xfamily.name(*lprimary_itr)
	<< setw(10) << lct;

    if(lct > 0)
    {
      xos << setw(10) << xfamily.begin(*lprimary_itr)
	  << setw(10) << xfamily.end(*lprimary_itr);
    }
  
    xos << endl;
    
    lprimary_itr++;
  }
  
  // Print out the secondary id spaces.

  xos << " secondary:" << endl;

  set<pod_index_type>::const_iterator lsecondary_itr = lsecondary.begin();

  while(lsecondary_itr != lsecondary.end())
  {
    lct = xfamily.ct(*lsecondary_itr);

    xos << setw(10) << *lsecondary_itr
	<< setw(32) << xfamily.name(*lsecondary_itr)
	<< setw(10) << lct;

    if(lct > 0)
    {
      xos << setw(10) << xfamily.begin(*lsecondary_itr)
	  << setw(10) << xfamily.end(*lsecondary_itr)
          << setw(12) << boolalpha << xfamily.is_persistent(*lsecondary_itr) << noboolalpha;
    }
  
    xos << endl;
    
    lsecondary_itr++;
  }
  

  xos << endl;
  xos << "equivalence classes" << endl;
  xos << "-------------------" << endl;
  xos << endl;

  const hub_index_space_handle& lhub_space = xfamily.hub_id_space();

  if(lhub_space.ct() <= index_space_family::max_rep_ids())
  {
    index_space_iterator& lid_itr = lhub_space.get_iterator();

    scoped_index lid(lhub_space);
    index_equivalence_iterator leqv_itr(xfamily, lid, false, true);

    while(!lid_itr.is_done())
    {
      lid = lid_itr.pod();
      leqv_itr.put_rep_id(lid);
      leqv_itr.reset();

      if(!leqv_itr.is_done())
      {
	// There are equivelence classes for lid, output them.

        xos << "(" 
            << setw(4) << lid.scope_id()
            << ", "
            << setw(4) << lid.pod() 
            << "):";

	while(!leqv_itr.is_done())
	{
	  xos << "    (" 
              << setw(4) << leqv_itr.item().first 
              << ", "
	      << setw(4) << leqv_itr.item().second 
              << ")";

	  leqv_itr.next();
	}

	xos << endl;
      }

      lid_itr.next();
    }

    lhub_space.release_iterator(lid_itr);
  }
  else
  {
    xos << "  ... " << endl
	<< "  Equivalence class output terminated because the " << endl
	<< "  size of the hub id space exceeded "
	<< index_space_family::max_rep_ids() << " ids," << endl
	<< "  use index_space_family::max_rep_ids() to change default." << endl;
    
  }

  // Postconditions:

  // Exit:

  return xos;
}

size_t
sheaf::
deep_size(const index_space_family& xfamily, bool xinclude_shallow)
{
  size_t result = 0;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xfamily) : 0;

  // Add the contributation from member _intervals.

  index_space_family::const_interval_iterator_type itr;
  for(itr = xfamily._intervals.begin(); itr != xfamily._intervals.end(); ++itr)
  {
    if(itr->second != 0)
    {
      result += itr->second->deep_size(true);
    }
  }

  // Add contributions from member _name_to_index.

  result += deep_size(xfamily._name_to_index, false);
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
