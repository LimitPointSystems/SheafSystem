

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class poset_crg_state 

#include "poset_crg_state.impl.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "deep_size.h"
#include "explicit_crg_interval.h"
#include "factory.h"
#include "implicit_crg_interval.h"
#include "interval_index_space_handle.h"
#include "interval_index_space_state.h"
#include "list_index_space_state.h"
#include "primary_index_space_handle.h"
#include "poset_path.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "std_set.h"
#include "std_string.h"
#include "std_strstream.h"

// ===========================================================
// POSET_CRG_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_crg_state::
poset_crg_state()
{
  // Preconditions:

  // Body:

  // Set _begin to 0 in the hub id space.

  _begin.put(hub_id_space(), 0);

  // Set _end to 0 in the hub id space.

  _end.put(hub_id_space(), 0);

  // Set counts to 0.

  _member_ct = 0;
  _standard_member_ct = 0;
  _jim_edit_depth = 0;

  // Postconditions:

  ensure(begin().is_hub_scope());
  ensure(begin() == 0);
  ensure(end().is_hub_scope());
  ensure(standard_member_ct() == 0);
  ensure(member_ct() == 0);
  ensure(jim_edit_depth() == 0);
}

sheaf::poset_crg_state::
~poset_crg_state()
{
  // Preconditions:

  // Body:

  // Delete the intervals.

  interval_map_type::iterator li_itr;

  for(li_itr = _interval_map.begin();
      li_itr != _interval_map.end();
      ++li_itr)
  {
    if(li_itr->second != 0)
    {
      delete li_itr->second;
    }
  }

  // Dof tuple ids will be deleted automatically.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MEMBERSHIP (NODES) FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
sheaf::poset_crg_state::
new_member()
{
  // Preconditions:

  // Body:

  define_old_variable(scoped_index old_end = _end);
  define_old_variable(size_type old_member_ct = _member_ct);

  pod_index_type result = _id_spaces.new_id();

  // Update the upper bound on the member index.

  _end = hub_id_space().end();

  // Increment the member counter.

  ++_member_ct;

  // Initialize the upper and lower cover of the member.

  initialize_member_covers(result);

  // No entry in dof tuple map or name map to start with.

  // Postconditions:

  ensure(end() >= old_end);
  ensure(member_ct() == old_member_ct + 1);
  ensure(contains_explicit_member(result));
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // Exit:

  return result;
}

void
sheaf::poset_crg_state::
new_member(pod_index_type xid)
{
  // Preconditions:

  require(!contains_member(xid));
  require(id_spaces().is_valid_reserved_id(xid));

  // Body:

  define_old_variable(scoped_index old_end = end());
  define_old_variable(size_type old_member_ct = _member_ct);

  _id_spaces.new_id(xid);

  // Update the upper bound on the member index.

  _end = hub_id_space().end();

  // Increment the member counter.

  ++_member_ct;

  // Initialize the upper and lower cover of the member.

  initialize_member_covers(xid);

  // No entry in dof tuple map or name map to start with.

  // Postconditions:

  ensure(end() >= old_end);
  ensure(member_ct() == old_member_ct + 1);
  ensure(contains_explicit_member(xid));
  ensure(cover_is_empty(LOWER, xid));
  ensure(cover_is_empty(UPPER, xid));

  return;
}


void
sheaf::poset_crg_state::
new_standard_member_hack(standard_member_index xid)
{
  // Preconditions:

  require((xid == BOTTOM_INDEX) || (xid == TOP_INDEX));

  // Body:

  define_old_variable(size_type old_member_ct = _member_ct);

  // Update the upper bound on the member index.

  _end = xid + 1;

  // Increment the member counter.

  ++_member_ct;

  // Initialize the upper and lower cover of the member.

  initialize_member_covers(xid, true);

  // No entry in dof tuple map or name map to start with.

  // Postconditions:

  ensure(end() >= xid + 1);
  ensure(member_ct() == old_member_ct + 1);
  ensure(contains_explicit_member(xid));
  ensure(cover_is_empty(LOWER, xid));
  ensure(cover_is_empty(UPPER, xid));

  return;
}

sheaf::pod_index_type
sheaf::poset_crg_state::
new_member_interval(const string& xinterval_type, size_type xsize)
{
  // Preconditions:

  require(crg_interval::interval_factory().contains_prototype(xinterval_type));
  require(xsize > 0);

  // Body:

  define_old_variable(scoped_index old_end = end());
  define_old_variable(size_type old_member_ct = _member_ct);

  // Allocate a interval of ids.

  pod_index_type lspace_id = _id_spaces.new_primary_state(xsize);
  primary_index_space_handle lid_space(_id_spaces, lspace_id);

  pod_index_type result = lid_space.offset();

  // Update the upper bound on the member index.

  _end = hub_id_space().end();

  // Increment the member counter.

  _member_ct += xsize;

  // Create the interval emulator and set its size and local id map.
  // The local id map for the interval is the term id map from the hub id space.

  crg_interval* linterval = crg_interval::new_interval(xinterval_type);

  linterval->initialize_id_spaces(_id_spaces);
  linterval->initialize_local_id_space(lid_space);

  // Put the emulator in the implicit member map.

  // The entire index interval of the emulator is mapped to the emulator
  // by making a single entry for the end of the interval and using the
  // upper_bound query on the map. See member function interval().
  // Maps use internal (poset) id space.

  _interval_map[hub_id_space().end()] = linterval;

  // Make sure that ids below begin() do not map to this member by making sure
  // there's an entry at the end of the preceeding interval == begin of this interval.

  if(_interval_map.find(result) == _interval_map.end())
  {
    _interval_map[result] = 0;
  }

  interval_map_type::const_iterator itr = _interval_map.begin();
  while(itr != _interval_map.end())
  {
    ++itr;
  }

  // Postconditions:

  ensure(end() >= old_end + xsize);
  ensure(member_ct() == old_member_ct + xsize);
  ensure(interval(result).id_spaces_initialized());
  ensure(interval(result).local_id_space_initialized());
  ensure_for_range(pod_index_type i = result, i < end().pod(), ++i, contains_member(i));
  ensure(unexecutable("atoms not in upper cover of bottom"));

  return result;
}

void
sheaf::poset_crg_state::
new_member_interval(pod_index_type xid, const string& xinterval_type, size_type xsize)
{
  // Preconditions:

  require(is_valid(xid));
  require_for_range(pod_index_type i=0, i<xsize, ++i, !contains_member(xid + i));
  require(crg_interval::interval_factory().contains_prototype(xinterval_type));
  require(xsize > 0);

  // Body:

  define_old_variable(scoped_index old_end = end());
  define_old_variable(size_type old_member_ct = _member_ct);

  // Allocate a interval of ids, if needed.

  _id_spaces.new_primary_state(xid, xsize);

  // Update the upper bound on the member index.

  _end = hub_id_space().end();

  // Increment the member counter.

  _member_ct  += xsize;

  // Create the interval emulator and set its size and local id map.
  // The local id map for the interval is the term id map from the hub id space.

  crg_interval* linterval = crg_interval::new_interval(xinterval_type);
  linterval->initialize_id_spaces(_id_spaces);
  linterval->initialize_local_id_space(_id_spaces.term_of(xid));

  // Put the emulator in the implicit member map.

  // The entire index interval of the emulator is mapped to the emulator
  // by making a single entry for the end of the interval and using the
  // upper_bound query on the map. See member function interval().
  // Maps use internal (poset) id space.

  _interval_map[xid + xsize] = linterval;

  // Make sure that ids below begin() do not map to this member by making sure
  // there's an entry at the end of the preceeding interval == begin of this interval.

  if(_interval_map.find(xid) == _interval_map.end())
  {
    _interval_map[xid] = 0;
  }

  // Postconditions:

  ensure(end() >= old_end);
  ensure(member_ct() == old_member_ct + xsize);
  ensure(interval(xid).id_spaces_initialized());
  ensure(interval(xid).local_id_space_initialized());
  ensure_for_range(pod_index_type i=0, i<xsize, ++i, contains_member(xid + i));
  ensure(unexecutable("atoms not in upper cover of bottom"));

  return;
}

void
sheaf::poset_crg_state::
delete_member(pod_index_type xid)
{
  // Preconditions:

  require(contains_member(xid)); // equivalent to hub_id_space().contains(xid);

  // Body:

  define_old_variable(size_type old_member_ct = _member_ct); 

  // Delete cover id spaces.

  crg_interval& linterval = interval(xid);

  if(linterval.cover_is_explicit(LOWER, xid))
  {
    _id_spaces.delete_secondary_state(linterval.cover_id_space_id(LOWER, xid));
  }
  
  if(linterval.cover_is_explicit(UPPER, xid))
  {
    _id_spaces.delete_secondary_state(linterval.cover_id_space_id(UPPER, xid));
  }
  
  // Remove from dof tuple map.

  _explicit_dof_tuple_map.erase(xid);

  // Remove from name map.

  _member_name_map.delete_index(xid);

  // Remove member from the id space family.

  _id_spaces.delete_id(xid);

  // Update the upper bound on the member index.

  _end = !hub_id_space().is_empty() ? hub_id_space().end() : 0;

  --_member_ct;

  // $$SCRIBBLE: what about links to member?
  // Review abstract_poset_member::delete_state().

  // Postconditions:

  ensure(member_ct() == old_member_ct - 1);
  ensure(!contains_member(xid));

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
delete_interval(pod_index_type xid)
{
  // Preconditions:

  require(contains_member(xid));

  // Body:

  define_old_variable(size_type old_member_ct = _member_ct);

  // Get interval emulator.

  crg_interval& linterval = interval(xid);

  pod_index_type linterval_begin = linterval.begin();
  pod_index_type linterval_end   = linterval.end();

  pod_index_type llower_cover_begin = linterval.cover_id_space_id(LOWER, linterval_begin);
  pod_index_type lupper_cover_begin = linterval.cover_id_space_id(UPPER, linterval_begin);

  define_old_variable(size_type old_interval_size = linterval.size());
  define_old_variable(pod_index_type old_interval_begin = linterval.begin());
  define_old_variable(pod_index_type old_interval_end = linterval.end());

  // Delete the primary id space for the id interval being deleted.

  _id_spaces.delete_primary_state(hub_id_space().term_id(xid));

  // Update the upper bound on the member index.

  _end = !hub_id_space().is_empty() ? hub_id_space().end() : 0;

  // Decrement the member count.

  _member_ct -= linterval.size();

  // Remove the emulator from the map and delete it.

  _interval_map.erase(linterval_end);
  delete &linterval;

  // Postconditions:

  ensure(member_ct() == old_member_ct - old_interval_size);
  ensure_for_range(pod_index_type i = old_interval_begin, i < old_interval_end, ++i, !contains_member(i));

  // Exit:

  return;
}

sheaf::size_type
sheaf::poset_crg_state::
member_ct() const
{
  return _member_ct;
}

sheaf::size_type
sheaf::poset_crg_state::
standard_member_ct()
{
  return _standard_member_ct;
}

sheaf::size_type
sheaf::poset_crg_state::
standard_member_ct() const
{
  return _standard_member_ct;
}

void
sheaf::poset_crg_state::
put_standard_member_ct(size_type xct)
{
  // Preconditions:

  // Body:

  _standard_member_ct = xct;

  // Postconditions:

  ensure(standard_member_ct() == xct);

  // Exit:

  return;
}

const sheaf::scoped_index&
sheaf::poset_crg_state::
begin() const
{
  return _begin;
}

const sheaf::scoped_index&
sheaf::poset_crg_state::
end() const
{
  return _end;
}

bool
sheaf::poset_crg_state::
contains_member(pod_index_type xid) const
{
  // Preconditions:

  // Body:

  bool result = hub_id_space().contains(xid);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
contains_implicit_member(pod_index_type xid) const
{
  return contains_member(xid) && (implicit_member(xid) != 0);
}

bool
sheaf::poset_crg_state::
contains_explicit_member(pod_index_type xid) const
{
  // A member is fully explicit if it exists and is not implicit.

  return contains_member(xid) && (implicit_member(xid) == 0);
}

const sheaf::crg_interval&
sheaf::poset_crg_state::
interval(pod_index_type xid) const
{
  // Preconditions:

  require(contains_member(xid));

  // Body:

  // All the member ids in the interval of an implicit member emulator
  // map to the emulator by maintaining a single entry for the
  // end (upper bound) of the interval.
  // Map uses hub id space.

  return *_interval_map.upper_bound(xid)->second;
}

sheaf::crg_interval&
sheaf::poset_crg_state::
interval(pod_index_type xid)
{
  // Preconditions:

  require(contains_member(xid));

  // Body:

  // All the member ids in the interval of an implicit member emulator
  // map to the emulator by maintaining a single entry for the
  // end (upper bound) of the interval.
  // Map uses hub id space.

  return *_interval_map.upper_bound(xid)->second;
}

sheaf::implicit_crg_interval*
sheaf::poset_crg_state::
implicit_member(pod_index_type xid) const
{
  // Preconditions:

  require(contains_member(xid));

  // Body:

  implicit_crg_interval* result = 0;

  crg_interval* linterval = _interval_map.upper_bound(xid)->second;
  if(dynamic_cast<implicit_crg_interval*>(linterval) != 0)
  {
    result = reinterpret_cast<implicit_crg_interval*>(linterval);
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::poset_crg_state::
initialize_member_covers(pod_index_type xid, bool xstandard_member_hack)
{
  // Preconditions:

  require(contains_member(xid));

  // Body:

  // Find the explicit cover interval.

  explicit_crg_interval* linterval;

  interval_map_type::iterator litr = _interval_map.upper_bound(xid);

  if((litr == _interval_map.end()) || (litr->second == 0))
  {
    /// @hack Cartesian product subspace hack;
    /// xstandard_member_hack argument is intended only for use by
    /// section_space_schema_poset constructor.

    string lclass_name = xstandard_member_hack ?
      "standard_member_hack_crg_interval" : "explicit_crg_interval";

    // No cover interval found, create one.

    linterval =
      reinterpret_cast<explicit_crg_interval*>
      (crg_interval::new_interval(lclass_name));

    linterval->initialize_id_spaces(_id_spaces);
    linterval->initialize_local_id_space(_id_spaces.term_of(xid));
    linterval->initialize_covers();

    // The entire index interval of the emulator is mapped to the emulator
    // by making a single entry for the end of the interval and using the
    // upper_bound query on the map. See member function interval().
    // Maps use internal (poset) id space.

    _interval_map[linterval->end()] = linterval;

    // Make sure that ids below begin() do not map to this member by making sure
    // there's an entry at the end of the preceeding interval == begin of this interval.

    if(_interval_map.find(linterval->begin()) == _interval_map.end())
    {
      _interval_map[xid] = 0;
    }
  }
  else
  {
    // Cpver interval was found, cast it to an explicit cover interval.

    assertion(dynamic_cast<explicit_crg_interval*>(litr->second));

    linterval = reinterpret_cast<explicit_crg_interval*>(litr->second);
  }

  // Create explicit lower cover id space.

  pod_index_type llower_cover_id = linterval->cover_id_space_id(LOWER, xid);
  _id_spaces.new_secondary_state(llower_cover_id,
				 crg_interval::explicit_cover_name(LOWER, xid),
				 "list_index_space_state",
				 list_index_space_state::make_arg_list(),
				 false);

  // Create explicit upper cover id space.

  pod_index_type lupper_cover_id = linterval->cover_id_space_id(UPPER, xid);
  _id_spaces.new_secondary_state(lupper_cover_id,
				 crg_interval::explicit_cover_name(UPPER, xid),
				 "list_index_space_state",
				 list_index_space_state::make_arg_list(),
				 false);

  // Postconditions:

  ensure(cover_is_empty(LOWER, xid));
  ensure(cover_is_empty(UPPER, xid));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ID SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::poset_crg_state::
id_spaces() const
{
  return _id_spaces;
}

const sheaf::hub_index_space_handle&
sheaf::poset_crg_state::
hub_id_space() const
{
  return _id_spaces.hub_id_space();
}

const sheaf::scoped_index&
sheaf::poset_crg_state::
hub_id() const
{
  // Preconditions:

  // Body:

  const scoped_index& result = begin();

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_crg_state::
hub_id(pod_index_type xid) const
{
  // Preconditions:

  // Body:

  scoped_index result(hub_id());
  result = xid;

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

const sheaf:: index_space_handle&
sheaf::poset_crg_state::
new_gathered_hub_id_space(bool xexclude_bottom)
{
  // Preconditions:

  require(!has_gathered_hub_id_space());

  // Body:

  const index_space_handle& result =
    _id_spaces.new_gathered_hub_id_space(xexclude_bottom);

  // Postconditions:

  ensure(has_gathered_hub_id_space());
  ensure(gathered_hub_id_space().is_gathered());
  ensure(xexclude_bottom == gathered_hub_id_space_excludes_bottom());

  // Exit:

  return result;
}

void
sheaf::poset_crg_state::
update_gathered_hub_id_space()
{
  // Preconditions:

  require(has_gathered_hub_id_space());

  // Body:

  _id_spaces.update_gathered_hub_id_space();

  // Postconditions:

  ensure(gathered_hub_id_space().is_gathered());

  // Exit:

  return;
}

const sheaf::index_space_handle&
sheaf::poset_crg_state::
gathered_hub_id_space() const
{
  // Preconditions:

  require(has_gathered_hub_id_space());

  // Body:

  const index_space_handle& result = _id_spaces.gathered_hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
has_gathered_hub_id_space() const
{
  // Preconditions:

  // Body:

  bool result = _id_spaces.has_gathered_hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
gathered_hub_id_space_excludes_bottom() const
{
  // Preconditions:

  // Body:

  bool result = _id_spaces.gathered_hub_id_space_excludes_bottom();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MEMBER NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_crg_state::member_name_map_type&
sheaf::poset_crg_state::
member_name_map()
{
  return _member_name_map;
}

const sheaf::poset_crg_state::member_name_map_type&
sheaf::poset_crg_state::
member_name_map() const
{
  return _member_name_map;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EDIT MODE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_crg_state::
jim_edit_mode() const
{
  return _jim_edit_depth > 0;
}

void
sheaf::poset_crg_state::
request_jim_edit_mode()
{
  // Preconditions:


  // Body:

  define_old_variable(int old_jim_edit_depth = _jim_edit_depth);

  _jim_edit_depth++;

  // Postconditions:

  ensure(jim_edit_depth() == old_jim_edit_depth + 1);

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
release_jim_edit_mode()
{
  // Preconditions:

  require(jim_edit_mode());

  // Body:

  define_old_variable(int old_jim_edit_depth = _jim_edit_depth);

  _jim_edit_depth--;

  // Postconditions:

  ensure(jim_edit_depth() == old_jim_edit_depth - 1);
  ensure(jim_edit_depth() >= 0);

  // Exit:

  return;
}

 

int
sheaf::poset_crg_state::
jim_edit_depth() const
{
  return _jim_edit_depth;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER SET (LINKS) FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_crg_state::
cover_is_explicit(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  return interval(xmbr_index).cover_is_explicit(xlower, xmbr_index);
}

bool
sheaf::poset_crg_state::
cover_is_implicit(bool xlower, pod_index_type xmbr_index) const
{
  // A cover set for a member is implicit if the member is implicit.
  // Note that a cover set can be both implict and explicit at the same time.

  return contains_implicit_member(xmbr_index);
}

sheaf::index_space_handle&
sheaf::poset_crg_state::
get_cover_id_space(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid =  interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  index_space_handle& result = _id_spaces.get_id_space(lid);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::poset_crg_state::
release_cover_id_space(index_space_handle& xcover_id_space) const
{
  // Preconditions:

  // Body:

  _id_spaces.release_id_space(xcover_id_space);

  // Postconditions:

  ensure(!xcover_id_space.is_attached());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::poset_crg_state::
cover_id_space_id(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type result = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  // Postconditions:

  ensure(is_valid(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
sheaf::poset_crg_state::
get_cover_id_space_iterator(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);
  index_space_iterator& result = _id_spaces.get_id_space_iterator(lid);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::poset_crg_state::
release_cover_id_space_iterator(index_space_iterator& xcover_itr) const
{
  // Preconditions:

  // Body:

  _id_spaces.release_id_space_iterator(xcover_itr);

  // Postconditions:

  ensure(!xcover_itr.is_attached());

  // Exit:

  return;
} 

bool
sheaf::poset_crg_state::
cover_contains_iterator(bool xlower,
                        pod_index_type xmbr_index,
                        const index_space_iterator& xitr) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  index_space_handle& lcover = get_cover_id_space(xlower, xmbr_index);

  bool result = lcover.allocated_iterator(xitr);

  release_cover_id_space(lcover);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
cover_is_empty(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  bool result = _id_spaces.is_empty(lid);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
cover_is_singleton(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  bool result = (_id_spaces.ct(lid) == 1);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::poset_crg_state::
cover_ct(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  size_type result = _id_spaces.ct(lid);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
cover_contains_member(bool xlower,
                      pod_index_type xmbr_index,
                      pod_index_type xother_mbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  bool result = _id_spaces.contains_hub(lid, xother_mbr_index);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_crg_state::
cover_is_equal(bool xlower,
               pod_index_type xmbr_index,
               pod_index_type xother_mbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(contains_member(xother_mbr_index));

  // Body:

  // Gather the cover of xmbr_index into a set.

  index_space_iterator& litr = get_cover_id_space_iterator(xlower, xmbr_index);

  set< pod_index_type > lmbr_set;
  while(!litr.is_done())
  {
    lmbr_set.insert(litr.hub_pod());
    litr.next();
  }

  release_cover_id_space_iterator(litr);

  // Gather the cover of xother_member_index into a set.

  index_space_iterator& lother_itr = get_cover_id_space_iterator(xlower, xother_mbr_index);

  set< pod_index_type > lother_set;
  while(!lother_itr.is_done())
  {
    lother_set.insert(lother_itr.hub_pod());
    lother_itr.next();
  }

  release_cover_id_space_iterator(lother_itr);

  // Compare the sets.

  bool result = (lmbr_set == lother_set);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_crg_state::
first_cover_member(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_is_empty(xlower, xmbr_index));

  // Body:

  pod_index_type lid = interval(xmbr_index).cover_id_space_id(xlower, xmbr_index);

  pod_index_type result = _id_spaces.hub_begin(lid);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::poset_crg_state::
insert_cover_member(pod_index_type xother_mbr_index,
                    bool xlower,
                    pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_contains_member(xlower, xmbr_index, xother_mbr_index));

  // Body:

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  lcover.push_back(xother_mbr_index);

  _id_spaces.release_id_space(lcover);

  // Postconditions:

  ensure(cover_contains_member(xlower, xmbr_index, xother_mbr_index));

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
insert_cover_member(pod_index_type xother_mbr_index,
                    bool xlower,
                    pod_index_type xmbr_index,
                    index_space_iterator& xitr)
{
  // Preconditions:

  require(!xitr.is_done());
  require(contains_member(xmbr_index));
  require(!cover_contains_member(xlower, xmbr_index, xother_mbr_index));

  // Body:

  define_old_variable(pod_index_type old_itr_pod = xitr.pod());
  define_old_variable(pod_index_type old_itr_hub_pod = xitr.hub_pod());

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  lcover.push(xitr, xother_mbr_index);

  _id_spaces.release_id_space(lcover);

  // Postconditions:

  ensure(cover_contains_member(xlower, xmbr_index, xother_mbr_index));
  ensure(xitr.pod() == old_itr_pod + 1);
  ensure(xitr.hub_pod() == old_itr_hub_pod);

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
remove_cover_member(pod_index_type xother_mbr_index,
                    bool xlower,
                    pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  lcover.remove_hub(xother_mbr_index, true);

  _id_spaces.release_id_space(lcover);

  // Postconditions:

  ensure(!cover_contains_member(xlower, xmbr_index, xother_mbr_index));

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
remove_cover_member(index_space_iterator& xitr,
                    bool xlower,
                    pod_index_type xmbr_index)
{
  // Preconditions:

  require(!xitr.is_done());
  require(contains_member(xmbr_index));

  // Body:

  define_old_variable(pod_index_type old_itr_pod = xitr.pod());
  define_old_variable(pod_index_type old_itr_hub_pod = xitr.hub_pod());

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  lcover.remove(xitr, true);

  _id_spaces.release_id_space(lcover);

  // Postconditions:

  ensure(!cover_contains_member(xlower, xmbr_index, old_itr_hub_pod));
  ensure(xitr.is_done() || xitr.pod() > old_itr_pod);

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
replace_cover_member(pod_index_type xold_other_mbr_index,
		     pod_index_type xnew_other_mbr_index,
		     bool xlower,
		     pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  define_old_variable(bool old_cover_contains_old_other_mbr_index = cover_contains_member(xlower, xmbr_index, xold_other_mbr_index));

  // Body:

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  pod_index_type lold_pod = lcover.pod(xold_other_mbr_index);

  /// @todo Add a replace function to mutable id space or loosen the
  /// preconditions allowing for the pod value to exist.

  lcover.remove(lold_pod, true);
  lcover.insert(lold_pod, xnew_other_mbr_index);

  _id_spaces.release_id_space(lcover);

  // Postconditions:

  ensure(!cover_contains_member(xlower, xmbr_index, xold_other_mbr_index));
  ensure(old_cover_contains_old_other_mbr_index ? cover_contains_member(xlower, xmbr_index, xnew_other_mbr_index) : true);

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
clear_cover(bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:+

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  lcover.clear();

  _id_spaces.release_id_space(lcover);

  // Postconditions:

  ensure(cover_is_empty(xlower, xmbr_index));

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
copy_cover(bool xlower, pod_index_type xmbr_index, pod_index_type xother_mbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(contains_member(xother_mbr_index));

  // Body:

  pod_index_type lid = force_explicit_cover(xlower, xmbr_index);
  mutable_index_space_handle& lcover =
    _id_spaces.get_id_space<mutable_index_space_handle>(lid);

  lcover.clear();

  index_space_iterator& litr = get_cover_id_space_iterator(xlower, xother_mbr_index);
  while(!litr.is_done())
  {
    lcover.push_back(litr.hub_pod());

    litr.next();
  }
  release_cover_id_space_iterator(litr);

  _id_spaces.release_id_space(lcover);

  // Postconditions

  ensure(cover_is_equal(xlower, xmbr_index, xother_mbr_index));

  return;
}

void
sheaf::poset_crg_state::
append_upper_cover_of_bottom(pod_index_type xmbr_begin,
			     pod_index_type xmbr_end)
{
  // Preconditions:

  require(xmbr_end > xmbr_begin);
  require(cover_is_empty(UPPER, BOTTOM_INDEX) || id_spaces().handle_conforms_to_state<interval_index_space_handle>(cover_id_space_id(UPPER, BOTTOM_INDEX)));
  require_for_range(pod_index_type i=xmbr_begin, i<xmbr_end, ++i, contains_member(i));

  // Body:

  pod_index_type lspace_id = cover_id_space_id(UPPER, BOTTOM_INDEX);

  if(cover_is_empty(UPPER, BOTTOM_INDEX))
  {
    // This is the first time this function has been called.  The cover id 
    // space was initialized to a list id space.  It needs to be replaced
    // with an interval id space so that the block can efficiently store
    // the upper cover of bottom.

    ///
    /// @hack This function is only a temporary fix to avoid a problem size
    /// id space for the upper cover of bottom and will be replaced by a
    /// templatized get_cover_id_space in the future.
    ///

    // Delete the current id space state.

    _id_spaces.delete_secondary_state(lspace_id);

    // Make a new interval id space state.

    arg_list largs = interval_index_space_state::make_arg_list(true);

    _id_spaces.new_secondary_state(lspace_id,
				   crg_interval::explicit_cover_name(UPPER, BOTTOM_INDEX),
				   "interval_index_space_state",
				   largs,
				   false);
  }

  // Add the interval to the cover.  Since the interval id space takes a
  // closed interval but this function takes a half open interval, one
  // needs subtracted from xmbr_end.

  assertion(id_spaces().handle_conforms_to_state<interval_index_space_handle>(lspace_id));

  interval_index_space_handle& lcover = id_spaces().get_id_space<interval_index_space_handle>(lspace_id);
  lcover.push_interval(xmbr_begin, xmbr_end-1);
  id_spaces().release_id_space(lcover);

  // Postconditions:

  ensure(id_spaces().handle_conforms_to_state<interval_index_space_handle>(cover_id_space_id(UPPER, BOTTOM_INDEX)));
  ensure_for_range(pod_index_type i=xmbr_begin, i<xmbr_end, ++i, cover_contains_member(UPPER, BOTTOM_INDEX, i));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::pod_index_type
sheaf::poset_crg_state::
force_explicit_cover(bool xlower, pod_index_type xmbr_index, bool xinitialize)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type result =
    interval(xmbr_index).force_explicit_cover(xlower, xmbr_index, xinitialize);

  // Postconditions:

  ensure(id_spaces().contains(result));
  ensure(id_spaces().handle_conforms_to_state<mutable_index_space_handle>(result));

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
sheaf::poset_crg_state::
member_dof_tuple_id(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  explicit_dof_tuple_map_type::const_iterator le_itr =
    _explicit_dof_tuple_map.find(xmbr_index);
  if(le_itr != _explicit_dof_tuple_map.end())
  {
    return le_itr->second;
  }
  else
  {
    implicit_crg_interval* lmbr = implicit_member(xmbr_index);

    if(lmbr != 0)
    {
      return lmbr->dof_tuple_id(xmbr_index);
    }
    else
    {
      return invalid_pod_index();
    }
  }
}

void
sheaf::poset_crg_state::
put_member_dof_tuple_id(pod_index_type xmbr_index,
                        pod_index_type xdof_tuple_id)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  _explicit_dof_tuple_map[xmbr_index] = xdof_tuple_id;

  // Postconditions:

  ensure(member_dof_tuple_id(xmbr_index) == xdof_tuple_id);
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
sheaf::poset_crg_state::
clean_cover(bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  /// @todo Reimplement or design out of the io system.

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::poset_crg_state::
explicit_down_set_members(const implicit_crg_interval& xinterval,
			  set<pod_index_type>& result) const
{
  // Preconditions:

  // Body:

  const crg_interval::explicit_cover_map_type& lcover_map = xinterval.explicit_cover_map(LOWER);
  crg_interval::explicit_cover_map_type::const_iterator lcover_map_itr;
  for(lcover_map_itr = lcover_map.begin();
      lcover_map_itr != lcover_map.end();
      ++lcover_map_itr)
  {
    index_space_iterator& lcover_itr =
      _id_spaces.get_id_space_iterator(lcover_map_itr->second);

     while(!lcover_itr.is_done())
    {
      pod_index_type lmbr_id = lcover_itr.hub_pod();
      
      const crg_interval& linterval = interval(lmbr_id);

      if(linterval.cover_is_explicit(LOWER, lmbr_id))
      {
	// Member is explicit, insert it into the result.

	result.insert(lmbr_id);

	// Insert the explicit members in the down set.

	explicit_down_set_members(lmbr_id, result);
      }

      lcover_itr.next();
    }

     _id_spaces.release_id_space_iterator(lcover_itr);
  }
  
  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

void
sheaf::poset_crg_state::
explicit_down_set_members(pod_index_type xmbr_index,
			  set<pod_index_type>& result) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  index_space_iterator& itr = get_cover_id_space_iterator(LOWER, xmbr_index);
  while(!itr.is_done())
  {
    pod_index_type lmbr_id = itr.hub_pod();

    const crg_interval& linterval = interval(lmbr_id);

    if(linterval.cover_is_explicit(LOWER, lmbr_id))
    {
      // Member is explicit, insert it into the result.

      result.insert(lmbr_id);

      // Insert the explicit members in the down set.

      explicit_down_set_members(lmbr_id, result);
    }

    itr.next();
  }
  release_cover_id_space_iterator(itr);

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_crg_state::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_crg_state*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_crg_state*
sheaf::poset_crg_state::
clone() const
{
  poset_crg_state* result = 0;

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::poset_crg_state::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    disable_invariant_check();

    invariance(begin().is_hub_scope());
    invariance(begin() == BOTTOM_INDEX);
    invariance(end().is_hub_scope());

    invariance(member_ct() >= standard_member_ct());
    invariance(standard_member_ct() >= 0);
    invariance(jim_edit_depth() >= 0);

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON MEMBER FUNCTIONS
// ===========================================================

ostream & 
sheaf::
operator<<(ostream &os, const poset_crg_state& p)
{

  // Preconditions:

  // Body:

  os << endl
     << "ROW GRAPH" << endl
     << "---------" << endl
     << endl;

  os << "Members and Covering Relation" << endl
     << "-----------------------------" << endl
     << endl;

  os << " member_ct = "
     << p.member_ct()
     << endl
     << endl;

  for(scoped_index i = p.begin(); i < p.end(); ++i)
  {
    if(p.contains_member(i.hub_pod()))
    {
      os << "index: " << setw(5) << i.hub_pod();

      typedef poset_crg_state::member_name_map_type name_map_type;
      typedef name_map_type::name_list_type name_list_type;
      typedef name_map_type::const_name_iterator name_itr_type;

      const name_list_type lname_list = 
	p.member_name_map().all_names(i.hub_pod());
      name_itr_type lname_itr = lname_list.begin();

      string lfirst_name;
      if(lname_itr != lname_list.end())
      {
        lfirst_name = *lname_itr;
        ++lname_itr;
      }

      os << "    " << setw(36) << left << lfirst_name << right;

      os << "dof_map: "
	 << setw(2*sizeof(int)+3)
	 << p.member_dof_tuple_id(i.hub_pod());

      os << "    upper_cover:";
      index_space_iterator& uc_itr = p.get_cover_id_space_iterator(UPPER, i.hub_pod());
      while(!uc_itr.is_done())
      {
        os << " " << uc_itr.hub_pod();
        uc_itr.next();
      }
      p.release_cover_id_space_iterator(uc_itr);

      // Note set::size() returns an unsigned integer.

      int ltab_ct = 3 - (3*static_cast<int>(p.cover_ct(UPPER, i.hub_pod())))/8;

      for(int ltab = 0; ltab < ltab_ct; ltab++)
      {
        os << "\t";
      }

      os << "lower_cover:";
      index_space_iterator& lc_itr = p.get_cover_id_space_iterator(LOWER, i.hub_pod());
      while(!lc_itr.is_done())
      {
        os << " " << lc_itr.hub_pod();
        lc_itr.next();
      }
      p.release_cover_id_space_iterator(lc_itr);

      os << endl;

      while(lname_itr != lname_list.end())
      {
        os << "            ";
        os << "    " << setw(36) << left << *lname_itr << right << endl;
        ++lname_itr;
      }
    } // end if contains_member

  } // end for all members

  // Memeber id space family.

  os << endl
     << "Member Id Space Family" << endl
     << "----------------------" << endl
     << endl;

  os << p.id_spaces() << endl;

  // Postconditions:

  // Exit

  return os;
}
  
size_t
sheaf::
deep_size(const poset_crg_state& xp, bool xinclude_shallow, size_t xresults[2])
{
  size_t result;
  size_t crg_result;
  size_t id_space_result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  typedef hash_map<pod_index_type, pod_index_type> implicit_member_map_type;
  typedef no_deep_size_policy<implicit_member_map_type> implicit_member_map_policy_type;

  typedef map<pod_index_type, crg_interval*> crg_interval_map_type;
  typedef value_ptr_deep_size_policy<crg_interval_map_type> crg_interval_map_policy_type;

  // Add the deep size of the data members.

  id_space_result = deep_size(xp._id_spaces, false);

  crg_result = deep_size<pod_index_type, pod_index_type, implicit_member_map_policy_type>(xp._explicit_dof_tuple_map, false);
  crg_result += deep_size<pod_index_type, crg_interval*, crg_interval_map_policy_type>(xp._interval_map, false);
  crg_result += deep_size(xp._member_name_map, false);

  xresults[0] = crg_result;
  xresults[1] = id_space_result;
  result = id_space_result + crg_result;  

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
