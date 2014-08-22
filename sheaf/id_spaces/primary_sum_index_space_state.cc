
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
/// Implementation for class primary_sum_index_space_state

#include "ComLimitPoint/sheaf/primary_sum_index_space_state.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/deep_size.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/interval_index_space_state.h"
#include "ComLimitPoint/sheaf/poset_path.h"
#include "ComLimitPoint/sheaf/primary_index_space_handle.h"
#include "ComLimitPoint/sheaf/primitive_value.h"
#include "ComLimitPoint/sheaf/hub_index_space_iterator.h"
#include "ComLimitPoint/sheaf/reserved_primary_index_space_state.h"
#include "std_sstream.h"

using namespace std;

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::hub_index_space_handle
sheaf::primary_sum_index_space_state::
new_space(index_space_family& xid_spaces,
	  const std::string& xname)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  primary_sum_index_space_state* lstate = new primary_sum_index_space_state();
  lstate->new_state(xid_spaces, xname, false);

  hub_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  // Exit:

  return result;
}

sheaf::hub_index_space_handle
sheaf::primary_sum_index_space_state::
new_space(index_space_family& xid_spaces,
	  pod_index_type xid,
	  const std::string& xname)
{
  // Preconditions:

  require(!xid_spaces.contains(xid));
  require(xid_spaces.is_explicit_interval(xid));
  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  primary_sum_index_space_state* lstate = new primary_sum_index_space_state();
  lstate->new_state(xid_spaces, xid, xname, false);

  hub_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.index() == xid);
  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRIMARY_SUM_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::primary_sum_index_space_state::
primary_sum_index_space_state()
  : sum_index_space_state(),
    _standard_id_end(0),
    _term_id_begin(0),
    _term_id_end(0),
    _next_id(0)
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return; 
}

sheaf::primary_sum_index_space_state::
~primary_sum_index_space_state()
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
// PRIMARY SUM INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
new_id()
{
  // Preconditions:

  // Body:

  if(!_reserved_term.is_attached() || !_reserved_term.is_next_id_available())
  {
    // Current reserved term is full or has not been created;
    // need to allocated a new term.

    new_reserved_term();
  }

  pod_index_type result = _reserved_term.new_id();

  // Insert member.

  _members.insert_member(result);

  // Update count and extrema.

  _ct++;

  update_extrema();

  // Postconditions:

  ensure(contains(result));
  ensure(term_of(result).contains_hub(result));

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
new_id(pod_type xid)
{
  // Preconditions:

  require(is_valid_reserved_id(xid));

  // Body:

  pod_type lterm_id = term_id(xid);

  if(!is_valid(lterm_id))
  {
    // xid is not contained in any term; allocate a new term that includes it.

    // The allocated reserved term will be at term end.

    lterm_id = _term_id_end;

    // Create the reserved term.

    new_reserved_term(xid);
  }

  // Insert the id into the reserved term.

  reinterpret_cast<reserved_primary_index_space_handle*>(_terms[lterm_id])->new_hub_id(xid);

  // Insert member.

  _members.insert_member(xid);

  // Update count and extrema.

  _ct++;

  update_extrema();

  // Postconditions:

  ensure(contains(xid));
  ensure(term_of(xid).contains_hub(xid));

  // Exit:

  return xid;
}

void
sheaf::primary_sum_index_space_state::
delete_id(pod_type xid)
{
  // Preconditions:

  // Body:

  if(_members.contains_member(xid))
  {
    _members.remove_member(xid);
    _ct--;
    update_extrema();
  }

  // Postconditions:

  ensure(!contains(xid));

  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
is_valid_reserved_id(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result;

  pod_type lterm_id = term_id(xid);
  if(is_valid(lterm_id))
  {
    // There is a term, make sure it is a reserved term.

    index_space_handle* lterm = _terms[lterm_id];
    if(dynamic_cast<reserved_primary_index_space_handle*>(lterm) != 0)
    {
      // The term is a reserved term, make sure the id is available.

      result = reinterpret_cast<reserved_primary_index_space_handle*>(lterm)->is_hub_id_available(xid);
    }
    else
    {
      // Not a reserved term, id is not valid.

      result = false;
    }
  }
  else
  {
    // There is no term, is if the reserved interval is available.

    result = reserved_interval_is_available(xid);
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
next_id() const
{
  // Preconditions:

  // Body:

  pod_type result = _next_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
new_primary_term(size_type xct)
{
  // Preconditions:

  require(interval_is_available(next_id(), next_id()+xct));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());
  define_old_variable(pod_type old_next_id = next_id());

  pod_type result = new_primary_term(_next_id, xct);

  // Postconditions:

  ensure(invariant());
  ensure(term_id_end() == old_term_id_end + 1);
  ensure(id_spaces().contains(result));
  ensure(interval_is_full(old_next_id, old_next_id+xct));
  ensure(ct() == old_ct + xct);
  ensure(next_id() == old_next_id + xct);

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
new_primary_term(pod_type xid, size_type xct)
{
  // Preconditions:

  require(interval_is_available(xid, xid+xct));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());

  // Create the term.

  pod_type result =
    primary_index_space_state::new_space(id_spaces(),
					 next_term_name(),
					 xid, xct).index();

  // Add the term to this space.

  add_term(result, xid, xid+xct);

  // Add the members to the domain.

  _members.insert_interval(xid, xid+xct-1);

  // Increment the count.

  _ct += xct;

  // Update the extrema.

  update_extrema();

  // Postconditions:

  ensure(invariant());
  ensure(term_id_end() == old_term_id_end + 1);
  ensure(id_spaces().contains(result));
  ensure(interval_is_full(xid, xid+xct));
  ensure(ct() == old_ct + xct);

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
remove_term(pod_type xi)
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  define_old_variable(pod_type old_term_ct = term(xi).ct());
  define_old_variable(pod_type old_begin = _term_begin[xi]);
  define_old_variable(pod_type old_end = _term_end[xi]);
  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_begin = term_id_begin());
  define_old_variable(pod_type old_term_id_end = term_id_end());

  // Remove the term from the sum id space.

  pod_type lbegin = _term_begin[xi];
  pod_type lend = _term_end[xi];

  id_spaces().release_id_space(*_terms[xi]);
  _terms[xi] = 0;
  _term_begin[xi] = invalid_pod_index();
  _term_end[xi] = invalid_pod_index();
  _sum_to_term_map[lend] = invalid_pod_index();
  if(!is_valid(_sum_to_term_map.find(lbegin)->second))
    _sum_to_term_map.erase(lbegin);

  // Set the term id extrema.

  if((xi == _term_id_begin) && (xi == _term_id_end-1))
  {
    // All the terms have been erased, set _term_id_begin to _term_id_end
    // so that the next time the user inserts a term _term_id_begin will be
    // correct.

    _term_id_begin = _term_id_end;
  }
  else if(xi == _term_id_begin)
  {
    for(pod_type i=xi+1; i < _term_id_end; ++i)
    {
      if(_terms[i] != 0)
      {
	// Found a term, that is the new term begin.

	_term_id_begin = i;
	break;
      }  
    }
  }
  else if(xi == _term_id_end-1)
  {
    for(pod_type i=xi-1; i >= _term_id_begin; --i)
    {
      if(_terms[i] != 0)
      {
	// Found a term, that is the new term end.

	_term_id_end = i+1;
	break;
      } 
    }
  }

  // Decrement the count.

  pod_type lmember_end = lend - 1;

  _ct -= _members.member_ct(lbegin, lmember_end);

  // Remove the term's sum id interval.

  _members.remove_interval(lbegin, lmember_end);

  // Update the extrema.

  update_extrema();

  // Postconditions:

  ensure(invariant());
  ensure(ct() <= old_ct);
  ensure(term_id_begin() >= old_term_id_begin);
  ensure(term_id_end() <= old_term_id_end);
  ensure(interval_is_empty(old_begin, old_end - 1));

  // Exit:

  return;
}

void
sheaf::primary_sum_index_space_state::
extend_last_term(size_type xct)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());

  // Get the last term

  pod_type last_term_id = _term_id_end - 1;

  primary_index_space_handle* last_term =
    reinterpret_cast<primary_index_space_handle*>(_terms[last_term_id]);
  size_type old_last_term_ct    = last_term->ct();

  pod_type old_last_term_begin = _term_begin[last_term_id];
  pod_type new_last_term_end = old_last_term_begin + xct;

  // Update the term map.

  last_term->extend(xct);
  
  // Update term ends buffer.

  _term_end[last_term_id] = new_last_term_end;

  // Increment the count.

  _ct += (xct - old_last_term_ct);

  // Update the term's sum id interval.

  _members.insert_interval(old_last_term_begin, new_last_term_end - 1);

  // Update the extrema.

  update_extrema();

  // Postconditions:

  ensure(invariant());
  ensure(ct() == (old_ct - old_last_term_ct + xct));
  ensure(term_id_end() == old_term_id_end);
  ensure(interval_is_full(old_last_term_begin, old_last_term_begin + xct));

  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
interval_is_full(pod_type xbegin, pod_type xend) const
{
  // Preconditions:

  require(xbegin < xend);

  // Body:

  bool result = _members.interval_is_full(xbegin, xend - 1);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::primary_sum_index_space_state::
interval_is_empty(pod_type xbegin, pod_type xend) const
{
  // Preconditions:

  require(xbegin < xend);

  // Body:

  bool result = _members.interval_is_empty(xbegin, xend - 1);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::primary_sum_index_space_state::
interval_is_available(pod_type xbegin, pod_type xend) const
{
  // Preconditons:

  require(xbegin < xend);

  // Body:

  bool result = true;

  for(pod_type i = _term_id_begin; result && (i < _term_id_end); ++i)
  {
    // Make sure no part of the interval does not overlap term.

    result = (_term_end[i] <= xbegin) || (_term_begin[i] >= xend);
  }
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

const std::string&
sheaf::primary_sum_index_space_state::
term_prefix()
{
  // Preconditions:

  // Body:

  static const std::string result("__hub_term_");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

std::string
sheaf::primary_sum_index_space_state::
next_term_name()
{
  std::string result;
  
  // Preconditions:

  // Body:

  std::stringstream lstr;
  lstr << term_prefix() << term_id_end();
  lstr >> result;

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
new_reserved_term()
{
  // Preconditions:

  // Body:

  define_old_variable(pod_type old_next_id = _next_id);
  define_old_variable(pod_type old_term_id_end = _term_id_end);

  pod_type result = new_reserved_term(_next_id + RESERVED_TERM_SIZE - 1);

  // Postconditions:

  ensure(_reserved_term.offset() >= old_next_id);
  ensure(term_id_end() == old_term_id_end+1);
  ensure(next_id() >= term_end(old_term_id_end));

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
new_reserved_term(pod_type xid)
{
  // Preconditions:
  
  // Body:

  define_old_variable(pod_type old_term_id_end = _term_id_end);

  // Term must begin at 0 mod RESERVED_TERM_SIZE and include xid;
  // compute beginning of term.

  pod_type lterm_begin = (xid/RESERVED_TERM_SIZE)*RESERVED_TERM_SIZE;

  // Create the term.

  pod_type result =
    reserved_primary_index_space_state::new_space(id_spaces(),
						  next_term_name(),
						  lterm_begin,
						  RESERVED_TERM_SIZE).index();

  // Add the term to this id space.

  add_term(result, lterm_begin, lterm_begin+RESERVED_TERM_SIZE);

  // Update reserved term id.

  _reserved_term.attach_to(id_spaces(), result);

  // Postconditions:

  ensure(result == _reserved_term.index());
  ensure(term_id_end() == old_term_id_end+1);
  ensure(next_id() >= term_end(old_term_id_end));

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
add_term(pod_type xterm_id, pod_type xbegin, pod_type xend)
{
  // Preconditions:

  require(id_spaces().contains(xterm_id));
  require(interval_is_available(xbegin, xend));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());

   // Add term handle.

  primary_index_space_handle& lterm =
    id_spaces().get_id_space<primary_index_space_handle>(xterm_id);

  _terms.force_item(_term_id_end, &lterm);
  _term_begin.force_item(_term_id_end, xbegin);
  _term_end.force_item(_term_id_end, xend);

  lterm.put_hub_term_id(_term_id_end);

  // Add an entry for the upper bound of the term.

  _sum_to_term_map[xend] = _term_id_end;

  // The interval below this term may be empty.
  // Make sure ids in that interval don't map to this term.

  if(_sum_to_term_map.find(xbegin) == _sum_to_term_map.end())
  {
    _sum_to_term_map[xbegin] = invalid_pod_index();
  }

  // Update the next available id.

  if(xend > _next_id)
  {
    _next_id = xend;
  }
  
  // Increment the term end.

  _term_id_end++;

  // Postconditions:

  ensure(invariant());
  ensure(term_id_end() == old_term_id_end + 1);
  ensure(interval_is_empty(xbegin, xend));
  
  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
reserved_interval_is_available(pod_type xid) const
{
  // Preconditions:

  // Body:

  size_type lsize = RESERVED_TERM_SIZE;
  pod_type lbegin = (xid/lsize)*lsize;
  pod_type lend = lbegin + lsize;
  
  bool result = interval_is_available(lbegin, lend);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
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
    // Extract the extrema from the members set.

    _begin = _members.begin();
    _end = _members.end() + 1;
  }
  
  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// GLUING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::primary_sum_index_space_state::
glue(pod_type xid, pod_type xrep)
{
  // Preconditions:

  require(contains_unique_rep(xid)); // Can't already be glued.
  require(contains_rep(xrep));
  require(term_id(xid) > term_id(xrep));
  
  // Body:

  _rem[xid] = xrep;
  _rem_inv.insert(rem_inv_type::value_type(xrep, xid));

  /// @todo Modify the term maps?

  // Postconditions:

  ensure(invariant());
  ensure(!contains_rep(xid));
  ensure(glued_hub_pod(xid) == xrep);
  
  // Exit:

  return;
}

void
sheaf::primary_sum_index_space_state::
unglue(pod_type xid)
{
  // Preconditions:

  require(contains(xid));
  require(!contains_rep(xid)); 
  
  // Body:

  // Get the representative member.

  pod_type lrep_id = hub_pod(xid);

  // Erase the entry in the rem map.
  
  _rem.erase(xid);

  // Find and erase the entry in the inverse rem map.

  typedef rem_inv_type::iterator itr_type;
  pair<itr_type, itr_type> lrange = _rem_inv.equal_range(lrep_id);

  for(itr_type litr = lrange.first; litr != lrange.second; ++litr)
  {
    if(litr->second == xid)
    {
      _rem_inv.erase(litr);
      break;
    }
  }

  /// @todo Modify the term maps?

  // Postconditions:

  ensure(invariant());
  ensure(contains_unique_rep(xid));
  
  // Exit:

  return;
}

void
sheaf::primary_sum_index_space_state::
unglue_all(pod_type xrep_id)
{
  // Preconditions:

  require(contains_rep(xrep_id)); 
  
  // Body:

  // Find and erase the entry in the rem map 
  // for each member of the equivalence class.

  typedef rem_inv_type::iterator itr_type;
  pair<itr_type, itr_type> lrange = _rem_inv.equal_range(xrep_id);

  for(itr_type litr = lrange.first; litr != lrange.second; ++litr)
  {
    _rem.erase(litr->second);
  }

  // Erase all the entries in the inverse rem map.

  _rem_inv.erase(xrep_id);

  /// @todo Modify the term maps.

  // Postconditions:

  ensure(invariant());
  ensure(contains_unique_rep(xrep_id));
  
  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
has_gluing() const
{
  // Preconditions:

  // Body:

  bool result = !_rem.empty();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// GATHERED ID SPACE FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_handle&
sheaf::primary_sum_index_space_state::
new_gathered_id_space(bool xexclude_bottom)
{
  // Preconditions:

  require(!has_gathered_id_space());

  // Body:

  _gathered_id_space =
    interval_index_space_state::new_space(id_spaces(),
					  gathered_hub_id_space_name(),
					  false, false);

  update_gathered_id_space(xexclude_bottom);

  // Postconditions:

  ensure(has_gathered_id_space());
  ensure(gathered_id_space().is_gathered());
  ensure(xexclude_bottom == gathered_id_space_excludes_bottom());

  // Exit:

  return _gathered_id_space;
}

void
sheaf::primary_sum_index_space_state::
update_gathered_id_space()
{
  // Preconditions:

  require(has_gathered_id_space());

  // Body:

  update_gathered_id_space(gathered_id_space_excludes_bottom());

  // Postconditions:

  ensure(gathered_id_space().is_gathered());

  // Exit:

  return;
}

const sheaf::index_space_handle&
sheaf::primary_sum_index_space_state::
gathered_id_space() const
{
  // Preconditions:

  require(has_gathered_id_space());

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _gathered_id_space;
}

bool
sheaf::primary_sum_index_space_state::
has_gathered_id_space() const
{
  // Preconditions:

  // Body:

  bool result = _gathered_id_space.is_attached();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::primary_sum_index_space_state::
gathered_id_space_excludes_bottom() const
{
  // Preconditions:

  // Body:

  bool result = !_gathered_id_space.contains_hub(BOTTOM_INDEX);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const std::string&
sheaf::primary_sum_index_space_state::
gathered_hub_id_space_name()
{
  // Preconditions:

  // Body:

  static const std::string result(poset_path::reserved_prefix() + "gathered_hub");

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::primary_sum_index_space_state::
update_gathered_id_space(bool xexclude_bottom)
{
  // Preconditions:

  require(has_gathered_id_space());

  // Body:

  // Clear gathered id space if required.

  if(!_gathered_id_space.is_empty())
  {
    _gathered_id_space.clear();
  }

  // Populate the gathered id space.

  pod_type lhub_begin = invalid_pod_index();
  pod_type lhub_end;

  interval_set::map_iterator_type litr = _members.interval_map().begin();

  while(litr != _members.interval_map().end())
  {
    if(litr->second)
    {
      // Interval is full, insert it.

      assertion(is_valid(lhub_begin)); // The first interval should have been empty.
      
      lhub_end = litr->first;

      if(!xexclude_bottom || lhub_begin > BOTTOM_INDEX || lhub_end < BOTTOM_INDEX)
      {
	_gathered_id_space.push_interval(lhub_begin, lhub_end);
      }
      else if(lhub_begin == BOTTOM_INDEX)
      {
	_gathered_id_space.push_interval(lhub_begin+1, lhub_end);
      }
      else if(lhub_end == BOTTOM_INDEX)
      {
	_gathered_id_space.push_interval(lhub_begin, lhub_end-1);
      }
      else
      {
	_gathered_id_space.push_interval(lhub_begin, BOTTOM_INDEX-1);
	_gathered_id_space.push_interval(BOTTOM_INDEX+1, lhub_end);
      }
    }

    // Update the hub begin.

    lhub_begin = litr->first + 1;

    // Increment to next interval.

    ++litr;
  }

  // Postconditions:

  ensure(gathered_id_space().is_gathered());
  ensure(xexclude_bottom == gathered_id_space_excludes_bottom());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STANDARD IDS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::primary_sum_index_space_state::
update_standard_ids()
{
  // Preconditions:

  // Body:

  _standard_id_end = end();

  // Postconditions:

  ensure(has_only_standard_ids());

  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
has_only_standard_ids() const
{
  // Preconditions:

  // Body:

  bool result = (_standard_id_end == end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
clear_ids()
{
  // Preconditions:

  // Body:

  if(!has_only_standard_ids())
  {
    // Determine the number of members to remove.

    size_type lmember_ct = _members.member_ct(_standard_id_end, _end);

    if(lmember_ct > 0)
    {
      // There are members to remove, remove them.

      _members.remove_interval(_standard_id_end, _end);

      // Update count and extrema.

      _ct -= lmember_ct;
      update_extrema();
    }

    // Update standard id end.

    _standard_id_end = end();
  }
  
  // Postconditions:

  ensure(has_only_standard_ids());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUM INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::primary_sum_index_space_state::
contains_rep(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  // _rem contains the reflexive reduction of the rem function,
  // that is, it contains an entry for sum id s if and only if
  // s is not its own representative. So s is a representative
  // if it is a hub id and is not contained in _rem.

  bool result =
    contains_hub(xhub_id) && 
    (_rem.find(xhub_id) == _rem.end());

  // Postconditions:

  ensure(result ? contains_hub(xhub_id) : true);

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
rep(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));
  
  // Body:
  
  pod_type result;
  
  rem_type::const_iterator litr = _rem.find(xhub_id);
  if(litr != _rem.end())
  {
    // Xhub_id is not its own representative;
    
    result = litr->second;
  }
  else
  {
    // Xhub_id is its own representative.

    result = xhub_id;
  }
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
host_rep(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));
  
  // Body:

  // Host id of rep is same as rep.

  pod_type result = rep(xhub_id);
  
  // Postconditions:

  ensure(contains(result));
  
  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
term_id_begin() const
{
  // Preconditions:

  // Body:

  pod_type result = _term_id_begin;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::primary_sum_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
term_id_end() const
{
  // Preconditions:

  // Body:

  pod_type result = _term_id_end;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::primary_sum_index_space_state::
contains_term_id(pod_type xi) const
{
  // Preconditions:

  // Body:

  bool result = ((_term_id_begin <= xi) &&
		 (xi < _term_id_end) &&
		 (_terms[xi] != 0));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
clear()
{
  // Preconditions:

  // Body:

  sum_index_space_state::clear();

  _rem.clear();
  _members.clear();
  _term_id_begin = 0;
  _term_id_end = 0;

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::primary_sum_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const primary_sum_index_space_state& lother =
    dynamic_cast<const primary_sum_index_space_state&>(xother);

  bool result = sum_index_space_state::operator==(xother);
  result = result && (_members == lother._members);
  result = result && (_next_id == lother._next_id);
  result = result && (_reserved_term == lother._reserved_term);
  result = result && (_standard_id_end == lother._standard_id_end);
  /// @error Since we still support tr1 unordered_maps the comparison
  ///        operator may not be supported.  See COM-374.
//   result = result && (_rem == lother._rem);
  result = result && (_term_id_begin == lother._term_id_begin);
  result = result && (_term_id_end == lother._term_id_end);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::primary_sum_index_space_state::
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

sheaf::primary_sum_index_space_state&
sheaf::primary_sum_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const primary_sum_index_space_state& lother =
    dynamic_cast<const primary_sum_index_space_state&>(xother);

  _members           = lother._members;
  _next_id           = lother._next_id;
  _reserved_term     = lother._reserved_term;
  _standard_id_end   = lother._standard_id_end;
  _rem               = lother._rem;
  _term_id_begin     = lother._term_id_begin;
  _term_id_end       = lother._term_id_end;

  (void) sum_index_space_state::operator=(xother);

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
sheaf::primary_sum_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = _members.contains_member(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::primary_sum_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = _members.contains_member(xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::primary_sum_index_space_state::
contains_glued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  // The glued hub id space is the subset of the unglued hub id space
  // that contains only the representative members of the equivalence classes.
  // _rem contains an entry for xhub_id if and only if xhub_id is not a 
  // representative member. So xhub_id is contained in the glued hub id space
  // if and only if it is in the primary sum id space and _rem does not contain an entry for it.

  bool result =
    _members.contains_member(xhub_id) &&
    (_rem.find(xhub_id) == _rem.end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  // The hub to primary sum direction of the map is identical to the inverse rem map.
  // The image of a hub id is thus a set of primary sum ids, the equivalence class
  // of the hub id. For consisentency with the base class, pod() 
  // returns just one of the members of the equivalence class. The obvious 
  // choice is the representative member, that is, xhub_id itself.

  pod_type result =
    contains_hub(xhub_id) ? xhub_id : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = contains(xid) ? xid : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::primary_sum_index_space_state::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  // The sum to host map is identical to the rem function, it's value is the
  // representative member of the equivalence class of xid.

  pod_type result;

  if(contains(xid))
  {
    // xid is in the sum id space.

    rem_type::const_iterator litr = _rem.find(xid);
    if(litr != _rem.end())
    {
      // xid is not its own representative;
    
      result = litr->second;
    }
    else
    {
      // xid is its own representative.

      result = xid;
    }
  }
  else
  {
    // xid is not in the sum id space;
    // result is invalid.

    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(result));

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
sheaf::primary_sum_index_space_state::
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
sheaf::primary_sum_index_space_state::
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
sheaf::primary_sum_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  hub_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<hub_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const hub_index_space_handle* lid_space =
    dynamic_cast<const hub_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::hub_index_space_handle>&
sheaf::primary_sum_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<hub_index_space_handle> result;

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
sheaf::primary_sum_index_space_state::
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
sheaf::primary_sum_index_space_state::
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
sheaf::primary_sum_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  hub_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::primary_sum_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<hub_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::primary_sum_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const hub_index_space_iterator* litr =
    dynamic_cast<const hub_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::hub_index_space_iterator>&
sheaf::primary_sum_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<hub_index_space_iterator> result;

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
sheaf::primary_sum_index_space_state::
class_name() const
{
  static const std::string result("primary_sum_index_space_state");
  return result;
}

sheaf::primary_sum_index_space_state*
sheaf::primary_sum_index_space_state::
clone() const
{
  // Preconditions:

  // Body:

  primary_sum_index_space_state* result =
    new primary_sum_index_space_state();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::primary_sum_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  primary_sum_index_space_state* lproto = new primary_sum_index_space_state();

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
sheaf::primary_sum_index_space_state::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const primary_sum_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::primary_sum_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(sum_index_space_state::invariant());

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
deep_size(const primary_sum_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

   // Add any contributions from the parent class.

  const sum_index_space_state& ixn = static_cast<const sum_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Add the memory allocated in member _rem.

  typedef no_deep_size_policy<primary_sum_index_space_state::rem_type> rem_policy_type;
  result += deep_size<pod_index_type, pod_index_type, rem_policy_type>(xn._rem, false);
 
  // Add the memory allocated in member _members.

  result += deep_size(xn._members, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
