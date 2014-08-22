
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
/// Implementation for class section_space_schema_crg_range

#include "ComLimitPoint/fiber_bundle/section_space_schema_crg_range.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"

// ===========================================================
// SECTION_SPACE_SCHEMA_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_crg_range::
section_space_schema_crg_range()
  : _base_space(0),
    _fiber_schema(0)
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

fiber_bundle::section_space_schema_crg_range::
~section_space_schema_crg_range()
{  
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  // Exit:

  return; 
}

fiber_bundle::base_space_poset&
fiber_bundle::section_space_schema_crg_range::
base_space()
{
  // Preconditions:

  require(base_space_initialized());

  // Body:

  base_space_poset& result = *_base_space;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const fiber_bundle::base_space_poset&
fiber_bundle::section_space_schema_crg_range::
base_space() const
{
  // Preconditions:

  require(base_space_initialized());

  // Body:

  const base_space_poset& result = *_base_space;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_crg_range::
base_space_initialized() const
{
  // Preconditions:

  // Body:

  bool result = (_base_space != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::poset_state_handle&
fiber_bundle::section_space_schema_crg_range::
fiber_schema()
{
  // Preconditions:

  require(fiber_schema_initialized());

  // Body:

  poset_state_handle& result = *_fiber_schema;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::poset_state_handle&
fiber_bundle::section_space_schema_crg_range::
fiber_schema() const
{
  // Preconditions:

  require(fiber_schema_initialized());

  // Body:

  const poset_state_handle& result = *_fiber_schema;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_crg_range::
fiber_schema_initialized() const
{
  // Preconditions:

  // Body:

  bool result = (_fiber_schema != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_crg_range::
contains_member(pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_crg_range::
tuple(pod_index_type xindex,
      pod_index_type& xbase_space_id,
      pod_index_type& xfiber_schema_id) const
{
  // Preconditions:

  require(local_id_space().contains_hub(xindex));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(contains_member(xbase_space_id, xfiber_schema_id));

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_crg_range::
ordinal(pod_index_type xbase_space_id,
	pod_index_type xfiber_schema_id,
	pod_index_type& xindex) const
{
  // Preconditions:

  require(contains_member(xbase_space_id, xfiber_schema_id));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(local_id_space().contains_hub(xindex));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_crg_range::
initialize_base_space(base_space_poset& xbase_space)
{
  // Preconditions:

  require(!base_space_initialized());

  // Body:

  _base_space = &xbase_space;

  // Postconditions:

  ensure(base_space_initialized());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_crg_range::
initialize_fiber_schema(poset_state_handle& xfiber_schema)
{
  // Preconditions:

  require(!fiber_schema_initialized());

  // Body:

  _fiber_schema = &xfiber_schema;

  // Postconditions:

  ensure(fiber_schema_initialized());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IMPLICIT_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_crg_range::
implicit_cover_contains_iterator(bool xlower,
				 pod_index_type xmbr_index,
				 const cover_set_iterator& xitr) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return false;
}

bool
fiber_bundle::section_space_schema_crg_range::
implicit_cover_is_singleton(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  bool result = (cover_size(xlower, xmbr_index) == 1);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::section_space_schema_crg_range::
class_name() const
{
  // Preconditions:

  // Body:

  static const string result("section_space_schema_crg_range");

  // Postconditions:

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
fiber_bundle::section_space_schema_crg_range::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_space_schema_crg_range*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::section_space_schema_crg_range*
fiber_bundle::section_space_schema_crg_range::
clone() const
{
  // Preconditions:

  // Body:
  
  section_space_schema_crg_range* result = 0;

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
fiber_bundle::section_space_schema_crg_range::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(implicit_crg_range::invariant());

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
 
