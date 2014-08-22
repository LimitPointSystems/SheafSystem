
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
/// Implementation for class hub_index_space_handle

#include "ComLimitPoint/sheaf/hub_index_space_handle.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/primary_sum_index_space_state.h"

// ===========================================================
// HUB_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::hub_index_space_handle::
hub_index_space_handle()
  : sum_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::hub_index_space_handle::
hub_index_space_handle(const hub_index_space_handle& xother)
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

sheaf::hub_index_space_handle::
hub_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::hub_index_space_handle::
hub_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::hub_index_space_handle&
sheaf::hub_index_space_handle::
operator=(const hub_index_space_handle& xother)
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

sheaf::hub_index_space_handle::
~hub_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::hub_index_space_handle::
hub_index_space_handle(primary_sum_index_space_state& xstate)
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

sheaf::primary_sum_index_space_state&
sheaf::hub_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  primary_sum_index_space_state& result =
    reinterpret_cast<primary_sum_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::primary_sum_index_space_state&
sheaf::hub_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const primary_sum_index_space_state& result =
    reinterpret_cast<const primary_sum_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRIMARY SUM INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::hub_index_space_handle::pod_type
sheaf::hub_index_space_handle::
new_id()
{
  // Preconditions:

  // Body:

  pod_index_type result = state().new_id();

  // Postconditions:

  ensure(contains(result));

  // Exit:

  return result;
}

sheaf::hub_index_space_handle::pod_type
sheaf::hub_index_space_handle::
new_id(pod_type xid)
{
  // Preconditions:

  require(is_valid_reserved_id(xid));

  // Body:

  state().new_id(xid);

  // Postconditions:

  ensure(contains(xid));

  // Exit:

  return xid;
}

void
sheaf::hub_index_space_handle::
delete_id(pod_type xid)
{
  // Preconditions:

  // Body:

  state().delete_id(xid);

  // Postconditions:

  ensure(!contains(xid));

  // Exit:

  return;
}

bool
sheaf::hub_index_space_handle::
is_valid_reserved_id(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = state().is_valid_reserved_id(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::hub_index_space_handle::pod_type
sheaf::hub_index_space_handle::
next_id() const
{
  // Preconditions:

  // Body:

  pod_type result = state().next_id();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::hub_index_space_handle::pod_type
sheaf::hub_index_space_handle::
new_primary_term(size_type xct)
{
  // Preconditions:

  require(interval_is_available(next_id(), next_id()+xct));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());
  define_old_variable(pod_type old_next_id = next_id());

  pod_type result = state().new_primary_term(xct);

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

sheaf::hub_index_space_handle::pod_type
sheaf::hub_index_space_handle::
new_primary_term(pod_type xid, size_type xct)
{
  // Preconditions:

  require(interval_is_available(xid, xid+xct));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());

  pod_type result = state().new_primary_term(xid, xct);

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
sheaf::hub_index_space_handle::
remove_term(pod_type xi)
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  define_old_variable(pod_type old_term_ct = term(xi).ct());
  define_old_variable(pod_type old_begin = term_begin(xi));
  define_old_variable(pod_type old_end = term_end(xi));
  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_begin = term_id_begin());
  define_old_variable(pod_type old_term_id_end = term_id_end());

  state().remove_term(xi);

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
sheaf::hub_index_space_handle::
extend_last_term(size_type xct)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_term_id_end = term_id_end());
  define_old_variable(pod_type old_last_term_begin = term_begin(term_id_end() - 1));
  define_old_variable(pod_type old_last_term_ct = last_term().ct());

  state().extend_last_term(xct);

  // Postconditions:

  ensure(invariant());
  ensure(ct() == (old_ct - old_last_term_ct + xct));
  ensure(term_id_end() == old_term_id_end);
  ensure(interval_is_full(old_last_term_begin, old_last_term_begin + xct));

  // Exit:

  return;
}

bool
sheaf::hub_index_space_handle::
interval_is_full(pod_type xbegin, pod_type xend) const
{
  // Preconditions:

  require(xbegin < xend);

  // Body:

  bool result = state().interval_is_full(xbegin, xend);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::hub_index_space_handle::
interval_is_empty(pod_type xbegin, pod_type xend) const
{
  // Preconditions:

  require(xbegin < xend);

  // Body:

  bool result = state().interval_is_empty(xbegin, xend);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::hub_index_space_handle::
interval_is_available(pod_type xbegin, pod_type xend) const
{
  // Preconditons:

  require(xbegin < xend);

  // Body:

  bool result = state().interval_is_available(xbegin, xend);
  
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
sheaf::hub_index_space_handle::
glue(pod_type xid, pod_type xrep)
{
  // Preconditions:

  require(contains_unique_rep(xid)); // Can't already be glued.
  require(contains_rep(xrep));
  require(term_id(xid) > term_id(xrep));
  
  // Body:

  state().glue(xid, xrep);

  // Postconditions:

  ensure(invariant());
  ensure(!contains_rep(xid));
  ensure(glued_hub_pod(xid) == xrep);
  
  // Exit:

  return;
}

void
sheaf::hub_index_space_handle::
unglue(pod_type xid)
{
  // Preconditions:

  require(contains(xid));
  require(!contains_rep(xid)); 
  
  // Body:

  state().unglue(xid);

  // Postconditions:

  ensure(invariant());
  ensure(contains_unique_rep(xid));
  
  // Exit:

  return;
}

void
sheaf::hub_index_space_handle::
unglue_all(pod_type xrep_id)
{
  // Preconditions:

  require(contains_rep(xrep_id)); 
  
  // Body:

  state().unglue_all(xrep_id);

  // Postconditions:

  ensure(invariant());
  ensure(contains_unique_rep(xrep_id));
  
  // Exit:

  return;
}

bool
sheaf::hub_index_space_handle::
has_gluing() const
{
  // Preconditions:

  // Body:

  bool result = state().has_gluing();

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
sheaf::hub_index_space_handle::
new_gathered_id_space(bool xexclude_bottom)
{
  // Preconditions:

  require(!has_gathered_id_space());

  // Body:

  const index_space_handle& result =
    state().new_gathered_id_space(xexclude_bottom);

  // Postconditions:

  ensure(has_gathered_id_space());
  ensure(gathered_id_space().is_gathered());
  ensure(xexclude_bottom == gathered_id_space_excludes_bottom());

  // Exit:

  return result;
}

void
sheaf::hub_index_space_handle::
update_gathered_id_space()
{
  // Preconditions:

  require(has_gathered_id_space());

  // Body:

  state().update_gathered_id_space();

  // Postconditions:

  ensure(gathered_id_space().is_gathered());

  // Exit:

  return;
}

const sheaf::index_space_handle&
sheaf::hub_index_space_handle::
gathered_id_space() const
{
  // Preconditions:

  require(has_gathered_id_space());

  // Body:

  const index_space_handle& result = state().gathered_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::hub_index_space_handle::
gathered_id_space_excludes_bottom() const
{
  // Preconditions:

  // Body:

  bool result = state().gathered_id_space_excludes_bottom();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::hub_index_space_handle::
has_gathered_id_space() const
{
  // Preconditions:

  // Body:

  bool result = state().has_gathered_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STANDARD IDS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::hub_index_space_handle::
update_standard_ids()
{
  // Preconditions:

  // Body:

  state().update_standard_ids();

  // Postconditions:

  ensure(has_only_standard_ids());

  // Exit:

  return;
}

bool
sheaf::hub_index_space_handle::
has_only_standard_ids() const
{
  // Preconditions:

  // Body:

  bool result = state().has_only_standard_ids();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::hub_index_space_handle::
clear_ids()
{
  // Preconditions:

  // Body:

  state().clear_ids();
  
  // Postconditions:

  ensure(has_only_standard_ids());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUM_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::hub_index_space_handle&
sheaf::hub_index_space_handle::
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

sheaf::hub_index_space_handle*
sheaf::hub_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  hub_index_space_handle* result =
    new hub_index_space_handle(*this);

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
sheaf::hub_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<primary_sum_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::hub_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result =
    dynamic_cast<const hub_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::hub_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(sum_index_space_handle::invariant());

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


