
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
/// Implementation for class index_space_collection

#include "abstract_product_structure.h"
#include "index_space_collection.h"
#include "assert_contract.h"
#include "explicit_index_space_state.h"
#include "factory_2.h"
#include "hub_index_space_handle.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "scoped_index.h"

// ===========================================================
// INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_collection::
~index_space_collection()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

bool
sheaf::index_space_collection::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::index_space_collection::
contains(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains_family(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
local_scope(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
family_scope(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains_family(result));

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_collection::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = 0; // To silence the compiler

  is_abstract();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_collection::
index_space_collection()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::index_space_collection&
sheaf::index_space_collection::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
sheaf::index_space_collection::
explicit_state(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  explicit_index_space_state* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::index_space_collection::
id_spaces() const
{
  // Preconditions:

  // Body:

  const index_space_family* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

sheaf::index_space_family&
sheaf::index_space_collection::
id_spaces()
{
  // Preconditions:

  // Body:

  index_space_family* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

const sheaf::hub_index_space_handle&
sheaf::index_space_collection::
hub_id_space() const
{
  // Preconditions:

  // Body:

  const hub_index_space_handle& result = id_spaces().hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_collection::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
is_empty(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (ct(xlocal_id) == 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
begin(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
is_gathered(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (begin(xlocal_id) == 0) && (end(xlocal_id) == ct(xlocal_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains(pod_type xlocal_id, const scoped_index& xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = contains_hub(xlocal_id, xid.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = contains_unglued_hub(xlocal_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains_glued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result =
    contains_unglued_hub(xlocal_id, hub_id_space().unglued_hub_pod(xid));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains(pod_type xlocal_id, pod_type xid, const scoped_index& xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = contains(xlocal_id, xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
pod(pod_type xlocal_id, const scoped_index& xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = pod(xlocal_id, xid.hub_pod());

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = unglued_hub_pod(xlocal_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_collection::
glued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result =
    hub_id_space().glued_hub_pod(unglued_hub_pod(xlocal_id, xid));

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
sheaf::index_space_collection::
is_persistent(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::index_space_collection::
new_product_structure(pod_type xlocal_id,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(has_product_structure(xlocal_id));

  // Exit:

  return;
}

void
sheaf::index_space_collection::
delete_product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  is_abstract();
  
  // Postconditions:

  ensure(!has_product_structure(xlocal_id));

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::index_space_collection::
product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  const abstract_product_structure* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

sheaf::abstract_product_structure&
sheaf::index_space_collection::
product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  abstract_product_structure* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

bool
sheaf::index_space_collection::
has_product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

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
sheaf::index_space_collection::
get_id_space(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_handle* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

void
sheaf::index_space_collection::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_collection::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

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

sheaf::index_space_iterator&
sheaf::index_space_collection::
get_id_space_iterator(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));

  // Body:

  index_space_iterator* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

void
sheaf::index_space_collection::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_collection::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

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
sheaf::index_space_collection::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_collection*>(other) != 0;

  // Postconditions:

  // Exut:

  return result;
}

bool
sheaf::index_space_collection::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

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
 
