
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
/// Implementation for class reserved_primary_index_space_handle

#include "reserved_primary_index_space_handle.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "reserved_primary_index_space_state.h"

// ===========================================================
// RESERVED_PRIMARY_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_handle::
reserved_primary_index_space_handle()
  : primary_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::reserved_primary_index_space_handle::
reserved_primary_index_space_handle(const reserved_primary_index_space_handle& xother)
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

sheaf::reserved_primary_index_space_handle::
reserved_primary_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::reserved_primary_index_space_handle::
reserved_primary_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::reserved_primary_index_space_handle&
sheaf::reserved_primary_index_space_handle::
operator=(const reserved_primary_index_space_handle& xother)
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

sheaf::reserved_primary_index_space_handle::
~reserved_primary_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_handle::
reserved_primary_index_space_handle(reserved_primary_index_space_state& xstate)
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

sheaf::reserved_primary_index_space_state&
sheaf::reserved_primary_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  reserved_primary_index_space_state& result =
    reinterpret_cast<reserved_primary_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::reserved_primary_index_space_state&
sheaf::reserved_primary_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const reserved_primary_index_space_state& result =
    reinterpret_cast<const reserved_primary_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESERVED PRIMARY INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_handle::pod_type
sheaf::reserved_primary_index_space_handle::
new_id()
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_next_hub_id = next_hub_id());

  pod_type result = state().new_id();

  // Postconditions:

  ensure(invariant());
  ensure(next_hub_id() == old_next_hub_id + 1);

  // Exit:

  return result;
}

sheaf::reserved_primary_index_space_handle::pod_type
sheaf::reserved_primary_index_space_handle::
new_hub_id(pod_type xhub_id)
{
  // Preconditions:

  require(is_hub_id_available(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_next_hub_id = next_hub_id());

  pod_type result = state().new_hub_id(xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(next_hub_id() >= old_next_hub_id);

  // Exit:

  return result;
}

sheaf::reserved_primary_index_space_handle::pod_type
sheaf::reserved_primary_index_space_handle::
next_hub_id() const
{
  // Preconditions:

  // Body:

  pod_type result = state().next_hub_id();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_handle::
is_next_id_available() const
{
  // Preconditions:

  // Body:

  bool result = state().is_next_id_available();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_handle::
is_hub_id_available(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = state().is_hub_id_available(xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRIMARY_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_handle*
sheaf::reserved_primary_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  reserved_primary_index_space_handle* result = new reserved_primary_index_space_handle(*this);

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
sheaf::reserved_primary_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<reserved_primary_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::reserved_primary_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const reserved_primary_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(primary_index_space_handle::invariant());

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

 

