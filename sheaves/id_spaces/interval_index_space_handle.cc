
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
/// Implementation for class interval_index_space_handle

#include "interval_index_space_handle.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "interval_index_space_state.h"
#include "scoped_index.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::interval_index_space_handle
sheaf::interval_index_space_handle::
new_space(index_space_family& xid_spaces,
	  const std::string& xname,
	  bool xis_persistent,
	  bool xmerge_mode)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  interval_index_space_handle result =
    interval_index_space_state::new_space(xid_spaces,
					  xname,
					  xis_persistent,
					  xmerge_mode);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.is_persistent() == xis_persistent);
  ensure(result.name() == xname);

  ensure(result.merge_mode() >= xmerge_mode);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INTERVAL_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::interval_index_space_handle::
interval_index_space_handle()
  : mutable_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::interval_index_space_handle::
interval_index_space_handle(const interval_index_space_handle& xother)
{
  // Preconditions:
    
  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return; 
}

sheaf::interval_index_space_handle::
interval_index_space_handle(const index_space_family& xid_spaces,
			   pod_type xindex)
{
  // Preconditions:

  require(xid_spaces.contains(xindex));
  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  attach_to(xid_spaces, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

sheaf::interval_index_space_handle::
interval_index_space_handle(const index_space_family& xid_spaces,
			   const std::string& xname)
{
  // Preconditions:

  require(xid_spaces.contains(xname));
  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xname);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

sheaf::interval_index_space_handle&
sheaf::interval_index_space_handle::
operator=(const interval_index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  attach_to(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::interval_index_space_handle::
~interval_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::interval_index_space_handle::
interval_index_space_handle(interval_index_space_state& xstate)
{
  // Preconditions:

  // Body:

  attach_to(&xstate);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == &xstate);

  // Exit:

  return;
}

sheaf::interval_index_space_state&
sheaf::interval_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  interval_index_space_state& result =
    reinterpret_cast<interval_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::interval_index_space_state&
sheaf::interval_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const interval_index_space_state& result =
    reinterpret_cast<const interval_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INTERVAL INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::interval_index_space_handle::
insert_interval(pod_type xbegin, 
		pod_type xend,
		const scoped_index& xhub_begin, 
		const scoped_index& xhub_end)
{
  // Preconditions:

  require(is_attached());
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
sheaf::interval_index_space_handle::
insert_interval(pod_type xbegin, 
		pod_type xend, 
		pod_type xhub_begin, 
		pod_type xhub_end)
{
  // Preconditions:

  require(is_attached());
  require(xhub_begin <= xhub_end);
  require(xbegin <= xend);
  require((xhub_end - xhub_begin) == (xend - xbegin));
  
  // Body:

  define_old_variable(pod_type old_ct = ct());

  state().insert_interval(xbegin, xend, xhub_begin, xhub_end);

  // Postconditions:

  ensure(ct() >= old_ct);
  ensure_for_range(pod_type i=xhub_begin, i<=xhub_end, ++i, pod(i) == xbegin+(i-xhub_begin));
  ensure_for_range(pod_type i=xbegin, i<=xend, ++i, hub_pod(i) == xhub_begin+(i-xbegin));

  // Exit:

  return;
}

void
sheaf::interval_index_space_handle::
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
sheaf::interval_index_space_handle::
push_interval(pod_type xhub_begin, pod_type xhub_end)
{
  // Preconditions:

  require(xhub_begin <= xhub_end);
 
  // Body:

  // Define old variables.

  define_old_variable(pod_type old_ct = ct());
  define_old_variable(pod_type old_next_id = next_id());

  state().push_interval(xhub_begin, xhub_end);

  // Postconditions:

  ensure(ct() == old_ct + (xhub_end - xhub_begin + 1));
  ensure(next_id() == old_next_id + (xhub_end - xhub_begin + 1));
  ensure_for_range(pod_type i=xhub_begin, i<=xhub_end, ++i, pod(i) == old_next_id+(i-xhub_begin));

  // Exit:

  return;
}

sheaf::size_type
sheaf::interval_index_space_handle::
remove_interval(const scoped_index& xhub_begin,
		const scoped_index& xhub_end)
{
  // Preconditions:

  require(is_attached());
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
sheaf::interval_index_space_handle::
remove_hub_interval(pod_type xhub_begin, pod_type xhub_end)
{
  // Preconditions:

  require(is_attached());
  require(xhub_begin <= xhub_end);

  // Body:

  size_type result = state().remove_hub_interval(xhub_begin, xhub_end);

  // Postconditions:

  ensure_for_range(pod_type i=xhub_begin, i<=xhub_end, ++i, !contains_hub(i));  

  // Exit

  return result;
}

sheaf::size_type
sheaf::interval_index_space_handle::
remove_interval(pod_type xbegin, pod_type xend)
{
  // Preconditions:

  require(is_attached());
  require(xbegin <= xend);

  // Body:

  size_type result = state().remove_interval(xbegin, xend);

  // Postconditions:

  ensure_for_range(pod_type i=xbegin, i<=xend, ++i, !contains(i));

  // Exit

  return result;
}

sheaf::interval_index_space_handle::pod_type
sheaf::interval_index_space_handle::
interval_begin(const scoped_index& xid) const
{
  // Preconditions:

  require(is_attached());
  require(xid.in_scope());
  require(precondition_of(interval_begin(xid.hub_pod())));

  // Body:

  pod_type result = interval_begin(xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(interval_begin(xid.hub_pod())));

  // Exit:

  return result;
}

sheaf::interval_index_space_handle::pod_type
sheaf::interval_index_space_handle::
interval_begin(pod_type xhub_id) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = state().interval_begin(xhub_id);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));
  
  // Exit:

  return result;
}

sheaf::interval_index_space_handle::pod_type
sheaf::interval_index_space_handle::
interval_end(const scoped_index& xid) const
{
  // Preconditions:

  require(is_attached());
  require(xid.in_scope());
  require(precondition_of(interval_end(xid.hub_pod())));

  // Body:

  pod_type result = interval_end(xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(interval_end(xid.hub_pod())));

  // Exit:

  return result;
}

sheaf::interval_index_space_handle::pod_type
sheaf::interval_index_space_handle::
interval_end(pod_type xhub_id) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = state().interval_end(xhub_id);
  
  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));

  // Exit:

  return result;
}

bool
sheaf::interval_index_space_handle::
merge_mode() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = state().merge_mode();

  // Postcondtions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::interval_index_space_handle::
put_merge_mode(bool xvalue)
{
  // Preconditions:

  require(is_attached());

  // Body:

  state().put_merge_mode(xvalue);

  // Postconditions:

  ensure(merge_mode() == xvalue);
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MUTABLE_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MAP REPRESENTATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::interval_index_space_handle::
print_map_rep(std::ostream& xos) const
{
  // Preconditions:

  // Body:

  state().print_map_rep(xos);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::interval_index_space_handle&
sheaf::interval_index_space_handle::
operator=(const index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  attach_to(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::interval_index_space_handle*
sheaf::interval_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  interval_index_space_handle* result = new interval_index_space_handle(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::interval_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<interval_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::interval_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const interval_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::interval_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(mutable_index_space_handle::invariant());

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
 

