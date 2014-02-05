
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
/// Implementation for class singleton_index_space_handle

#include "singleton_index_space_handle.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "singleton_index_space_state.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::singleton_index_space_handle
sheaf::singleton_index_space_handle::
new_space(index_space_family& xid_spaces,
	  const std::string& xname,
	  pod_type xhub_id)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));
  require(xid_spaces.hub_id_space().contains(xhub_id));

  // Body:

  singleton_index_space_handle result =
    singleton_index_space_state::new_space(xid_spaces,
					   xname,
					   xhub_id);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  ensure(result.hub_id() == xhub_id);
  ensure(result.ct() == 1);
  ensure(result.is_gathered());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SINGLETON_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::singleton_index_space_handle::
singleton_index_space_handle()
  : explicit_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::singleton_index_space_handle::
singleton_index_space_handle(const singleton_index_space_handle& xother)
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

sheaf::singleton_index_space_handle::
singleton_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::singleton_index_space_handle::
singleton_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::singleton_index_space_handle&
sheaf::singleton_index_space_handle::
operator=(const singleton_index_space_handle& xother)
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

sheaf::singleton_index_space_handle::
~singleton_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::singleton_index_space_handle::
singleton_index_space_handle(singleton_index_space_state& xstate)
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

sheaf::singleton_index_space_state&
sheaf::singleton_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  singleton_index_space_state& result =
    reinterpret_cast<singleton_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::singleton_index_space_state&
sheaf::singleton_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const singleton_index_space_state& result =
    reinterpret_cast<const singleton_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SINGLETON INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::singleton_index_space_handle::pod_type
sheaf::singleton_index_space_handle::
hub_id() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = state().hub_id();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
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

sheaf::singleton_index_space_handle&
sheaf::singleton_index_space_handle::
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

sheaf::singleton_index_space_handle*
sheaf::singleton_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  singleton_index_space_handle* result = new singleton_index_space_handle(*this);

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
sheaf::singleton_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<singleton_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::singleton_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const singleton_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_handle::
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


 

