
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
/// Implementation for class mutable_index_space_state

#include "mutable_index_space_state.h"
#include "assert_contract.h"
#include "index_space_iterator.h"
#include "mutable_index_space_handle.h"
#include "scoped_index.h"

// ===========================================================
// MUTABLE_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::mutable_index_space_state::
mutable_index_space_state()
  : explicit_index_space_state()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return; 
}

sheaf::mutable_index_space_state::
mutable_index_space_state(const arg_list& xargs)
  : explicit_index_space_state(xargs)
{
  // Preconditions:
    
  require(precondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));

  // Body:
  
  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));

  // Exit:

  return; 
}

sheaf::mutable_index_space_state::
~mutable_index_space_state()
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
sheaf::mutable_index_space_state::
insert(pod_type xid, const scoped_index& xhub_id)
{
  // Preconditions:

  require(xhub_id.in_scope());
  require(precondition_of(insert_entry(xid, xhub_id.hub_pod())));

  // Body:

  insert(xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(insert_entry(xid, xhub_id.hub_pod())));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
insert(pod_type xid, pod_type xhub_id)
{
  // Preconditions:

  require(is_valid(xid));
  require(is_valid(xhub_id));
  require(!contains(xid));
  require(!contains_hub(xhub_id));
  require(hub_id_space().contains(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);

  // Insert the entery in the map representation.

  map_rep_insert_entry(xid, xhub_id);

  // Update the count.

  ++_ct;

  // Update the extrema.

  update_extrema(xid);

  // Postconditions:

  ensure(invariant());
  ensure(contains(xid, xhub_id));
  ensure(ct() == old_ct + 1);
  ensure(ct() > 1 ? begin() <= old_begin : true);
  ensure(begin() <= xid);
  ensure(ct() > 1 ? end() >= old_end : true);
  ensure(end() > xid);

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
push_back(const scoped_index& xhub_id)
{
  // Preconditions:

  require(xhub_id.in_scope());
  require(precondition_of(push_back(xhub_id.hub_pod())));

  // Body:

  push_back(xhub_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(push_back(xhub_id.hub_pod())));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
push_back(pod_type xhub_id)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);

  pod_type old_next_id = next_id();

  // Insert the entry in the map representation.

  map_rep_push_back(xhub_id);

  // Update the count.

  ++_ct;

  // Update the extrema.

  update_extrema(old_next_id);

  // Postconditions:

  ensure(invariant());
  ensure(contains(old_next_id, xhub_id));
  ensure(ct() == old_ct + 1);
  ensure(ct() > 1 ? begin() <= old_begin : true);
  ensure(end() == old_next_id+1);

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
push(index_space_iterator& xitr, const scoped_index& xhub_id)
{
  // Preconditions:

  require(xhub_id.is_scoped());
  require(precondition_of(push(xitr, xhub_id.pod())));

  // Body:

  push(xitr, xhub_id.pod());
  
  // Postconditions:

  ensure(postcondition_of(push(xitr, xhub_id.pod())));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
push(index_space_iterator& xitr, pod_type xhub_id)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!xitr.is_done());
  require(is_valid(xhub_id));
  require(!contains_hub(xhub_id));
  require(hub_id_space().contains(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());

  pod_type old_itr_id = xitr.pod();

  // Insert the entry in the map representation.

  map_rep_push(xitr, xhub_id);

  // Update the count.

  ++_ct;

  // Update the extrema.

  if(_ct > 1)
  {
    ++_end;
  }
  else
  {
    // First entry, set extrema.

    _begin = old_itr_id;
    _end = old_itr_id + 1;
  }

  // Postconditions:

  ensure(invariant());
  ensure(contains(old_itr_id, xhub_id));
  ensure(ct() == old_ct + 1);
  ensure(ct() > 1 ? begin() == old_begin : true);
  ensure(ct() > 1 ? end() == old_end + 1 : true);
  ensure(xitr.pod() == old_itr_id+1);
  ensure(xitr.hub_pod() == old_itr_hub_id);

  // Exit:

  return;
}

sheaf::mutable_index_space_state::pod_type
sheaf::mutable_index_space_state::
next_id() const
{
  // Preconditions:

  // Body:

  pod_type result = (is_empty() ? 0 : end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::mutable_index_space_state::
remove(const scoped_index& xid, bool xupdate_extrema)
{
  // Preconditions:

  require(xid.in_scope());
  require(precondition_of(remove_hub(xid.hub_pod(), xupdate_extrema)));

  // Body:

  size_type result = remove_hub(xid.hub_pod(), xupdate_extrema);
  
  // Postconditions:

  ensure(postcondition_of(remove_hub(xid.hub_pod(), xupdate_extrema)));

  // Exit

  return result;
}

sheaf::size_type
sheaf::mutable_index_space_state::
remove(pod_type xid, bool xupdate_extrema)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);

  // Remove the entry from the map representation.

  size_type result = map_rep_remove_entry(xid, false);

  if(result != 0)
  {
    // Update the count.

    --_ct;

    if(xupdate_extrema)
    {
      // Update the extrema.

      update_extrema();
    }
  }
  
  // Postconditions:

  ensure(!contains(xid));
  ensure((result != 0) ? ct() == old_ct - 1 : ct() == old_ct);
  ensure((result == 0) || xupdate_extrema || begin() == old_begin);
  ensure((result == 0) || xupdate_extrema || end() == old_end);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(begin()) : true);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(end()) : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? begin() >= old_begin : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? end() <= old_end : true);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::mutable_index_space_state::
remove_hub(pod_type xhub_id, bool xupdate_extrema)
{
  // Preconditions:

  // Body:

  define_old_variable(pod_type old_id = pod(xhub_id));
  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);

  // Remove the entry from the map representation.

  size_type result = map_rep_remove_entry(xhub_id, true);

  if(result != 0)
  {
    // Update the count.

    --_ct;

    if(xupdate_extrema)
    {
      // Update the extrema.

      update_extrema();
    }
  }
  
  // Postconditions:

  ensure(!contains_hub(xhub_id));
  ensure((result != 0) ? ct() == old_ct - 1 : ct() == old_ct);
  ensure((result == 0) || xupdate_extrema || begin() == old_begin);
  ensure((result == 0) || xupdate_extrema || end() == old_end);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(begin()) : true);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(end()) : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? begin() >= old_begin : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? end() <= old_end : true);

  // Exit:

  return result;
}

void
sheaf::mutable_index_space_state::
remove(index_space_iterator& xitr, bool xupdate_extrema)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!xitr.is_done());
  require(contains(xitr.pod()));

  // Body:

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(pod_type old_begin = _begin);
  define_old_variable(pod_type old_end = _end);
  define_old_variable(pod_type old_itr_id = xitr.pod());
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());

  map_rep_remove_entry(xitr);

  // Update the count.

  --_ct;

  if(xupdate_extrema)
  {
    // Update the extrema.

    update_extrema();
  }

  // Postconditions:

  //  ensure(!contains(old_itr_id)); Not true for list_cover_set_iterator
  ensure(!contains_hub(old_itr_hub_id));
  ensure(ct() == old_ct - 1);
  ensure(xupdate_extrema || begin() == old_begin);
  ensure(xupdate_extrema || end() == old_end);
  ensure(xupdate_extrema && is_empty() ? !is_valid(begin()) : true);
  ensure(xupdate_extrema && is_empty() ? !is_valid(end()) : true);
  ensure(xupdate_extrema && !is_empty() ? begin() >= old_begin : true);
  ensure(xupdate_extrema && !is_empty() ? end() <= old_end : true);
  // ensure(xitr.is_done() || xitr.pod() > old_itr_pod); Not true for list_index_space.
  ensure(unexecutable("xitr.is_done() || xitr.hub_pod() == old_next_itr_hub_pod"));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
gather()
{
  // Preconditions:

  // Body:

  // Gather the ids.

  map_rep_gather();
  
  // Set the extrema to reflect the gather.

  if(_ct > 0)
  {
    _begin = 0;
    _end   = _ct;
  }
  else
  {
    invalidate_extrema();
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_gathered());

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
update_extrema()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit

  return;
}

void
sheaf::mutable_index_space_state::
clear()
{
  // Preconditions:

  // Body:

  map_rep_clear();

  _ct = 0;
  invalidate_extrema();
  
  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  
  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
reserve(size_type xcapacity)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure(capacity() >= xcapacity);

  // Exit:

  return;
}

sheaf::size_type
sheaf::mutable_index_space_state::
capacity() const
{
  // Preconditions:

  // Body:

  size_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::mutable_index_space_state::
update_extrema(pod_type xid)
{
  // Preconditions:

  // Body:

  if(_ct > 1)
  {
    // Check to see if xid changes the extrema.

    if(xid < _begin)
    {
      _begin = xid;
    }

    if(xid >= _end)
    {
      _end = xid + 1;
    }
  }
  else if(_ct == 1)
  {
    // First id added.

    _begin  = xid;
    _end    = xid + 1;
  }
  else
  {
    // The map is empty, invalid the extrema.

    assertion(is_empty());
    
    _begin  = invalid_pod_index();
    _end    = invalid_pod_index();
  }

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MAP REPRESENTATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
sheaf::mutable_index_space_state::
map_rep_insert_entry(pod_type xdomain_id, pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));
  require(!contains(xdomain_id));

  // Body:

  is_abstract();
  
  // Postconditions:

  // Not finished inserting entry; do not ensure invariant.

  ensure(contains(xdomain_id, xrange_id));
  
  // Exit

  return;
}

void
sheaf::mutable_index_space_state::
map_rep_push_back(pod_type xrange_id)
{
  // Preconditions:

  require(!contains_hub(xrange_id));

  // Body:

  define_old_variable(pod_type old_next_id = next_id());

  is_abstract();

  // Postconditions:

  // Not finished pushing back; do not ensure invariant.

  ensure(contains(old_next_id, xrange_id));

  // Exit

  return;
}

void
sheaf::mutable_index_space_state::
map_rep_push(index_space_iterator& xitr, pod_type xrange_id)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!contains_hub(xrange_id));

  // Body:

  define_old_variable(pod_type old_itr_pod = xitr.pod());
  define_old_variable(pod_type old_itr_hub_pod = xitr.hub_pod());

  is_abstract();

  // Postconditions:

  // Not finished inserting entry, do not ensure invariant.

  ensure(contains(old_itr_pod, xrange_id));
  ensure(xitr.pod() == old_itr_pod+1);
  ensure(xitr.hub_pod() == old_itr_hub_pod);

  // Exit:

  return;
}

sheaf::size_type
sheaf::mutable_index_space_state::
map_rep_remove_entry(pod_type xid, bool xis_range_id)
{
  // Preconditions:

  // Body:

  size_type result = 0;

  is_abstract();
  
  // Postconditions:

  // Not finished removing entry; do not ensure invariant.

  ensure(xis_range_id ? !contains_hub(xid) : !contains(xid));  

  // Exit

  return result;
}

void
sheaf::mutable_index_space_state::
map_rep_remove_entry(index_space_iterator& xitr)
{
  // Preconditions:

  require(allocated_iterator(xitr));
  require(!xitr.is_done());
  require(contains(xitr.pod()));

  // Body:

  define_old_variable(pod_type old_itr_id = xitr.pod());
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());

  is_abstract();

  // Postconditions:

  ensure(!contains(old_itr_id));
  ensure(!contains(old_itr_hub_id));
  ensure(xitr.is_done() || xitr.pod() > old_itr_id);

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
map_rep_clear()
{
  // Preconditions:

  // Body:

  is_abstract();
  
  // Postconditions:

  // Not finished clearing; do not ensure invariant.
  // Map rep is empty, but _ct not reset, so can't ensure is_empty.

  ensure(unexecutable("map rep is empty"));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_state::
map_rep_gather()
{
  // Preconditions:

  // Body:

  is_abstract();
  
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
sheaf::mutable_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const mutable_index_space_state& lother =
    dynamic_cast<const mutable_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::mutable_index_space_state&
sheaf::mutable_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  (void) explicit_index_space_state::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::mutable_index_space_state::
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
sheaf::mutable_index_space_state::
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
sheaf::mutable_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  mutable_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::mutable_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<mutable_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::mutable_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const mutable_index_space_handle* lid_space =
    dynamic_cast<const mutable_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::mutable_index_space_handle>&
sheaf::mutable_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<mutable_index_space_handle> result;

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
sheaf::mutable_index_space_state::
class_name() const
{
  static const string result("mutable_index_space_state");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::mutable_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const mutable_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::mutable_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(explicit_index_space_state::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
size_t
sheaf::
deep_size(const mutable_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const explicit_index_space_state& ixn = static_cast<const explicit_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
