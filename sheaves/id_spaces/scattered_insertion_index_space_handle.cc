
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
/// Implementation for class scattered_insertion_index_space_handle

#include "SheafSystem/scattered_insertion_index_space_handle.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/scattered_insertion_index_space_state.h"
#include "SheafSystem/scoped_index.h"

// ===========================================================
// SCATTERED_INSERTION_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::scattered_insertion_index_space_handle::
scattered_insertion_index_space_handle()
  : gathered_insertion_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::scattered_insertion_index_space_handle::
scattered_insertion_index_space_handle(const scattered_insertion_index_space_handle& xother)
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

sheaf::scattered_insertion_index_space_handle::
scattered_insertion_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::scattered_insertion_index_space_handle::
scattered_insertion_index_space_handle(const index_space_family& xid_spaces, const std::string& xname)
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

sheaf::scattered_insertion_index_space_handle&
sheaf::scattered_insertion_index_space_handle::
operator=(const scattered_insertion_index_space_handle& xother)
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

sheaf::scattered_insertion_index_space_handle::
~scattered_insertion_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::scattered_insertion_index_space_state&
sheaf::scattered_insertion_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  scattered_insertion_index_space_state& result =
    reinterpret_cast<scattered_insertion_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::scattered_insertion_index_space_state&
sheaf::scattered_insertion_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const scattered_insertion_index_space_state& result =
    reinterpret_cast<const scattered_insertion_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MUTABLE INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::scattered_insertion_index_space_handle::
insert(pod_type xid, const scoped_index& xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(xhub_id.in_scope());
  require(precondition_of(insert(xid, xhub_id.hub_pod())));

  // Body:

  insert(xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(insert(xid, xhub_id.hub_pod())));

  // Exit:

  return;
}

void
sheaf::scattered_insertion_index_space_handle::
insert(pod_type xid, pod_type xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(is_valid(xid));
  require(is_valid(xhub_id));
  require(!contains(xid));
  require(!contains_hub(xhub_id));
  require(hub_id_space().contains(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  state().insert(xid, xhub_id);

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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// GATHERED_INSERTION_INDEX_SPACE_HANDLE FACET
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

sheaf::scattered_insertion_index_space_handle&
sheaf::scattered_insertion_index_space_handle::
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

sheaf::scattered_insertion_index_space_handle*
sheaf::scattered_insertion_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  scattered_insertion_index_space_handle* result = new scattered_insertion_index_space_handle(*this);

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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::scattered_insertion_index_space_handle::
conforms_to_state(const index_space_collection& xhost, pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<scattered_insertion_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::scattered_insertion_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const scattered_insertion_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::scattered_insertion_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(gathered_insertion_index_space_handle::invariant());

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
deep_size(const scattered_insertion_index_space_handle& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

