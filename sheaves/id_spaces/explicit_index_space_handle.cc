
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
/// Implementation for class explicit_index_space_handle

#include "abstract_product_structure.h"
#include "explicit_index_space_handle.h"
#include "assert_contract.h"
#include "explicit_index_space_state.h"
#include "hub_index_space_handle.h"
#include "index_space_family.h"
#include "index_space_iterator.h"

// ===========================================================
// EXPLICIT_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_index_space_handle::
explicit_index_space_handle()
  : _state(0)
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::explicit_index_space_handle::
explicit_index_space_handle(const explicit_index_space_handle& xother)
  : _state(0)
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

sheaf::explicit_index_space_handle::
explicit_index_space_handle(const index_space_family& xid_spaces,
			    pod_type xindex)
{
  // Preconditions:

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

sheaf::explicit_index_space_handle::
explicit_index_space_handle(const index_space_family& xid_spaces,
			    const std::string& xname)
{
  // Preconditions:

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

sheaf::explicit_index_space_handle::
~explicit_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

sheaf::explicit_index_space_handle&
sheaf::explicit_index_space_handle::
operator=(const explicit_index_space_handle& xother)
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

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_state&
sheaf::explicit_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  explicit_index_space_state& result = *_state;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::explicit_index_space_state&
sheaf::explicit_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const explicit_index_space_state& result = *_state;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_index_space_handle&
sheaf::explicit_index_space_handle::
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

sheaf::explicit_index_space_handle*
sheaf::explicit_index_space_handle::
clone() const
{
  explicit_index_space_handle* result;
  
  // Preconditions:

  // Body:
  
  result = new explicit_index_space_handle(*this);

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
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::explicit_index_space_handle::
id_spaces() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_family& result = _state->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::explicit_index_space_handle::
id_spaces()
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_family& result = _state->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::explicit_index_space_handle::
ct() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  size_type result = _state->ct();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::explicit_index_space_handle::
begin() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->begin();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::explicit_index_space_handle::
end() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->end();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
contains(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->contains(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
contains_unglued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->contains_unglued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
contains_glued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->contains_glued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->contains(xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::explicit_index_space_handle::
pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::explicit_index_space_handle::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->unglued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::explicit_index_space_handle::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->glued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
is_persistent() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->is_persistent();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_collection&
sheaf::explicit_index_space_handle::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_collection& result = _state->host();

  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::explicit_index_space_handle::
index() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->index();

  // Postconditions:

  ensure(id_spaces().contains(result));

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
is_attached() const
{
  // Preconditions:

  // Body:

  bool result = (_state != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_handle::
attach_to(pod_type xindex)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));
  require(conforms_to_state(xindex));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  _state = state(xindex);
  
  // Postconditions:

  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::explicit_index_space_handle::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  _state = state(xhost, xlocal_id);
  
  // Postconditions:

  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

void
sheaf::explicit_index_space_handle::
detach()
{
  // Preconditions:

  // Body:

  _state = 0;

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result = (state(xhost, xlocal_id) != 0);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::explicit_index_space_handle::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  _state  = xstate;

  // Postconditions:

  ensure(is_attached());
  ensure(&state() == xstate);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_handle::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (xstate != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_handle::
state(pod_type xindex) const
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));

  // Body:

  const index_space_collection& lhost =
    host().contains(xindex) ? host() : *id_spaces().collection(xindex);

  explicit_index_space_state* result =
    lhost.explicit_state(lhost.local_scope(xindex));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_handle::
state(const index_space_collection& xhost, pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  explicit_index_space_state* result = xhost.explicit_state(xlocal_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::explicit_index_space_handle::
new_product_structure(const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(is_attached());

  // Body:

  _state->new_product_structure(xproduct);

  // Postconditions:

  ensure(has_product_structure());

  // Exit:

  return;
}

void
sheaf::explicit_index_space_handle::
delete_product_structure()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _state->delete_product_structure();
  
  // Postconditions:

  ensure(!has_product_structure());

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::explicit_index_space_handle::
product_structure() const
{
  // Preconditions:

  require(is_attached());
  require(has_product_structure());

  // Body:

  const abstract_product_structure& result = _state->product_structure();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::explicit_index_space_handle::
product_structure()
{
  // Preconditions:

  require(is_attached());
  require(has_product_structure());

  // Body:

  abstract_product_structure& result = _state->product_structure();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
has_product_structure() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->has_product_structure();

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
sheaf::explicit_index_space_handle::
get_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_handle& result = _state->get_id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_handle::
release_id_space() const
{
  // Preconditions:

  require(is_attached());
  require(allocated_id_space());

  // Body:

  _state->release_id_space(const_cast<explicit_index_space_handle&>(*this));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_handle::
allocated_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->allocated_id_space(*this);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator&
sheaf::explicit_index_space_handle::
get_iterator() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_iterator& result = _state->get_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_handle::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());
  require(allocated_iterator(xitr));

  // Body:

  _state->release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_handle::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _state->allocated_iterator(xitr);

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
sheaf::explicit_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const explicit_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_handle::invariant());

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



