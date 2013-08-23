
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
/// Implementation for class sum_index_space_handle

#include "sum_index_space_handle.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "scoped_index.h"
#include "sum_index_space_state.h"

// ===========================================================
// SUM_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::sum_index_space_handle::
sum_index_space_handle()
  : explicit_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::sum_index_space_handle::
sum_index_space_handle(const sum_index_space_handle& xother)
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

sheaf::sum_index_space_handle::
sum_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::sum_index_space_handle::
sum_index_space_handle(const index_space_family& xid_spaces,
		       const string& xname)
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

sheaf::sum_index_space_handle&
sheaf::sum_index_space_handle::
operator=(const sum_index_space_handle& xother)
{
  // Preconditions:
    
  // Body:
  
  (void) explicit_index_space_handle::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

sheaf::sum_index_space_handle::
~sum_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::sum_index_space_state&
sheaf::sum_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  sum_index_space_state& result =
    reinterpret_cast<sum_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::sum_index_space_state&
sheaf::sum_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const sum_index_space_state& result =
    reinterpret_cast<const sum_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUM INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::sum_index_space_handle::
equivalence_class(pod_type xhub_id, equivalence_class_type& result) const
{
  // Preconditions:

  require(contains_hub(xhub_id));

  // Body:

  state().equivalence_class(xhub_id, result);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return;
}

sheaf::size_type
sheaf::sum_index_space_handle::
equivalence_ct(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));

  // Body:

  size_type result = state().equivalence_ct(xhub_id);

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

bool
sheaf::sum_index_space_handle::
contains_rep(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = state().contains_rep(xhub_id);

  // Postconditions:

  ensure(result ? contains_hub(xhub_id) : true);
  
  // Exit:

  return result;
}

bool
sheaf::sum_index_space_handle::
contains_unique_rep(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = state().contains_unique_rep(xhub_id);

  // Postconditions:

  ensure(result ? contains_hub(xhub_id) : true);  
  ensure(result ? contains_rep(xhub_id) : true);

  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
rep(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));
  
  // Body:
  
  pod_type result = state().rep(xhub_id);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return true;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
host_rep(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));
  
  // Body:

  pod_type result = state().host_rep(xhub_id);

  // Postconditions:

  ensure(contains(result));
  
  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_id_begin() const
{
  // Preconditions:

  // Body:

  pod_type result = state().term_id_begin();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_id_end() const
{
  // Preconditions:

  // Body:

  pod_type result = state().term_id_end();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::sum_index_space_handle::
contains_term_id(pod_type xi) const
{
  // Preconditions:

  // Body:

  bool result = state().contains_term_id(xi);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_handle::
term(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  const index_space_handle& result = state().term(xi);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_handle::
term_of(pod_type xid) const
{
  // Preconditions:

  require(contains(xid));

  // Body:

  const index_space_handle& result = state().term_of(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_handle::
term_of(const scoped_index& xid) const
{
  // Preconditions:

  require(xid.in_scope());
  require(contains(xid));

  // Body:

  const index_space_handle& result = state().term_of(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_handle::
last_term() const
{
  // Preconditions:

  require(!is_empty());

  // Body:

  const index_space_handle& result = state().last_term();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_begin(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = state().term_begin(xi);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_end(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = state().term_end(xi);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_hub_begin(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = state().term_hub_begin(xi);  

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_hub_end(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = state().term_hub_end(xi);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::sum_index_space_handle::pod_type
sheaf::sum_index_space_handle::
term_id(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = state().term_id(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_term_id(result));

  // Exit:

  return result;
}

void
sheaf::sum_index_space_handle::
binary(pod_type xindex, pod_type& xterm_id, pod_type& xlocal_id) const
{
  // Preconditions:

  require(contains_hub(xindex));
  
  // Body:

  state().binary(xindex, xterm_id, xlocal_id);
  
  // Postconditions:

  ensure(contains_term_id(xterm_id));
  ensure(term(xterm_id).contains(xlocal_id));

  // Exit:

  return;
}

void
sheaf::sum_index_space_handle::
simple(pod_type xterm_id, pod_type xlocal_id, pod_type& xindex) const
{
  // Preconditions:

  require(contains_term_id(xterm_id));
  require(term(xterm_id).contains(xlocal_id));
  
  // Body:

  state().simple(xterm_id, xlocal_id, xindex);
  
  // Postconditions:

  ensure(contains_hub(xindex));

  // Exit:

  return;
}

void
sheaf::sum_index_space_handle::
clear()
{
  // Preconditions:

  // Body:

  state().clear();

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return;
}

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

sheaf::sum_index_space_handle*
sheaf::sum_index_space_handle::
clone() const
{
  sum_index_space_handle* result;
  
  // Preconditions:

  // Body:
  
  result = new sum_index_space_handle(*this);

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
sheaf::sum_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<sum_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::sum_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const sum_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::sum_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(explicit_index_space_handle::invariant());

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



