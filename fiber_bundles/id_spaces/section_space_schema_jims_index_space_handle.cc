
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
/// Implementation for class section_space_schema_jims_index_space_handle

#include "section_space_schema_jims_index_space_handle.h"
#include "assert_contract.h"
#include "ij_product_structure.h"
#include "index_space_family.h"
#include "section_space_schema_jims_index_space_state.h"
#include "scoped_index.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_handle::
section_space_schema_jims_index_space_handle()
  : explicit_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

fiber_bundle::section_space_schema_jims_index_space_handle::
section_space_schema_jims_index_space_handle(const section_space_schema_jims_index_space_handle& xother)
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

fiber_bundle::section_space_schema_jims_index_space_handle::
section_space_schema_jims_index_space_handle(const index_space_family& xid_spaces,
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

fiber_bundle::section_space_schema_jims_index_space_handle::
section_space_schema_jims_index_space_handle(const index_space_family& xid_spaces,
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

fiber_bundle::section_space_schema_jims_index_space_handle&
fiber_bundle::section_space_schema_jims_index_space_handle::
operator=(const section_space_schema_jims_index_space_handle& xother)
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

fiber_bundle::section_space_schema_jims_index_space_handle::
~section_space_schema_jims_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_state&
fiber_bundle::section_space_schema_jims_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  section_space_schema_jims_index_space_state& result =
    reinterpret_cast<section_space_schema_jims_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const fiber_bundle::section_space_schema_jims_index_space_state&
fiber_bundle::section_space_schema_jims_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const section_space_schema_jims_index_space_state& result =
    reinterpret_cast<const section_space_schema_jims_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SPACE SCHEMA JIMS INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_jims_index_space_handle::
put_factors(const index_space_handle& xbase_space_id_space,
	    const index_space_handle& xfiber_schema_id_space,
	    const ij_product_structure& xsection_space_schema_product)
{
  // Preconditions:
    
  // Body:

  state().put_factors(xbase_space_id_space,
		      xfiber_schema_id_space,
		      xsection_space_schema_product);

  // Postconditions:

  ensure(invariant());
  ensure(is_consistent());

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_jims_index_space_handle::
is_consistent() const
{
  // Preconditions:

  // Body:

  bool result = state().is_consistent();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_jims_index_space_handle::
update()
{
  // Preconditions:

  // Body:

  state().update();

  // Postconditions:

  ensure(is_consistent());

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

fiber_bundle::section_space_schema_jims_index_space_handle*
fiber_bundle::section_space_schema_jims_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  section_space_schema_jims_index_space_handle* result = new section_space_schema_jims_index_space_handle(*this);

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
fiber_bundle::section_space_schema_jims_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<section_space_schema_jims_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
fiber_bundle::section_space_schema_jims_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_space_schema_jims_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_jims_index_space_handle::
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


