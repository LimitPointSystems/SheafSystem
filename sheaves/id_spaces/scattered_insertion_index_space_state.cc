
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
/// Implementation for class scattered_insertion_index_space_state

#include "scattered_insertion_index_space_state.h"
#include "assert_contract.h"
#include "index_space_iterator.h"
#include "scattered_insertion_index_space_handle.h"
#include "scoped_index.h"

// ===========================================================
// SCATTERED_INSERTION_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::scattered_insertion_index_space_state::
scattered_insertion_index_space_state()
  : gathered_insertion_index_space_state()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return; 
}

sheaf::scattered_insertion_index_space_state::
~scattered_insertion_index_space_state()
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
sheaf::scattered_insertion_index_space_state::
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
sheaf::scattered_insertion_index_space_state::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// GATHER_INSERTION_INDEX_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// MAP REPRESENTATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
sheaf::scattered_insertion_index_space_state::
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

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::scattered_insertion_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const scattered_insertion_index_space_state& lother =
    dynamic_cast<const scattered_insertion_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::scattered_insertion_index_space_state&
sheaf::scattered_insertion_index_space_state::
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
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::scattered_insertion_index_space_state::
class_name() const
{
  static const std::string result("scattered_insertion_index_space_state");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::scattered_insertion_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const scattered_insertion_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::scattered_insertion_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(gathered_insertion_index_space_state::invariant());

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
deep_size(const scattered_insertion_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const gathered_insertion_index_space_state& ixn = static_cast<const gathered_insertion_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
