
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
/// Implementation for class explicit_index_space_interval

#include "ComLimitPoint/sheaf/explicit_index_space_interval.h"

#include "ComLimitPoint/sheaf/abstract_product_structure.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/explicit_index_space_state.h"
#include "ComLimitPoint/sheaf/hub_index_space_handle.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/index_space_iterator.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::explicit_index_space_interval&
sheaf::explicit_index_space_interval::
new_space(index_space_family& xid_spaces,
	  size_type xub)
{
  // Preconditions:

  require(xub > 0);

  // Body:

  define_old_variable(size_type old_id_spaces_end = xid_spaces.end());

  explicit_index_space_interval* result_ptr = new explicit_index_space_interval();
  result_ptr->new_state(xid_spaces, xub);

  result_ptr->_states.reserve(xub);
  
  const explicit_index_space_interval& result = *result_ptr;

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(result.begin() == old_id_spaces_end);
  ensure(result.end() == xid_spaces.end());
  ensure(result.end() == result.begin() + xub);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_index_space_interval::
~explicit_index_space_interval()
{  
  // Preconditions:
    
  // Body:
  
  // Delete the explicit states.

  for(pod_type i = 0; i < _states.ub(); ++i)
  {
    if(_states[i] != 0)
    {
      delete _states[i];
    }
  }

  // Postconditions:

  // Exit:

  return; 
}

void
sheaf::explicit_index_space_interval::
insert(explicit_index_space_state& xid_space)
{
  // Preconditions:

  require(!contains(local_scope(xid_space.index())));
  require(in_bounds(xid_space.index()));

  // Body:

  _states.set_item(xid_space.index() - _begin, &xid_space);

  // Postconditions:

  ensure(contains(local_scope(xid_space.index())));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_interval::
explicit_index_space_interval()
  : index_space_interval()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

bool
sheaf::explicit_index_space_interval::
supports_persistent_id_spaces() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return true;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::explicit_index_space_interval::
class_name() const
{
  static const std::string result("explicit_index_space_interval");
  return result;
}

sheaf::explicit_index_space_interval*
sheaf::explicit_index_space_interval::
clone() const
{
  // Preconditions:

  // Body:

  explicit_index_space_interval* result =
    new explicit_index_space_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::explicit_index_space_interval::
make_prototype()
{
  // Preconditions:

  // Body:

  explicit_index_space_interval* lproto = new explicit_index_space_interval();

  id_space_interval_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::explicit_index_space_interval::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const explicit_index_space_interval& lother =
    dynamic_cast<const explicit_index_space_interval&>(xother);

  bool result = index_space_interval::operator==(xother);

  result = result && (_states == lother._states);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::explicit_index_space_interval::
contains(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  pod_type lspace_id = xlocal_id + _begin;

  bool result =
    (_begin <= lspace_id) &&
    (lspace_id < _end) &&
    (_states[xlocal_id] != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
contains_family(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  bool result =
    (_begin <= xspace_id) &&
    (xspace_id < _end) &&
    (_states[xspace_id - _begin] != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::explicit_index_space_interval::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_interval&
sheaf::explicit_index_space_interval::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const explicit_index_space_interval& lother =
    dynamic_cast<const explicit_index_space_interval&>(xother);

  _states = lother._states;

  index_space_interval::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_interval::
explicit_state(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  explicit_index_space_state* result =
    contains(xlocal_id) ? _states[xlocal_id] : 0;

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

void
sheaf::explicit_index_space_interval::
remove(pod_type xlocal_id)
{
  // Preconditions:

  // Body:

  _states[xlocal_id] = 0;
  
  // Postconditions:

  ensure(!contains(xlocal_id));

  // Exit:

  return;
}

sheaf::size_type
sheaf::explicit_index_space_interval::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = _states[xlocal_id]->ct();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_interval::
begin(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states[xlocal_id]->begin();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_interval::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states[xlocal_id]->end();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states[xlocal_id]->contains(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states[xlocal_id]->contains_unglued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states[xlocal_id]->contains(xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_interval::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states[xlocal_id]->pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::explicit_index_space_interval::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _states[xlocal_id]->unglued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
is_persistent(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states[xlocal_id]->is_persistent();

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
sheaf::explicit_index_space_interval::
new_product_structure(pod_type xlocal_id,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  _states[xlocal_id]->new_product_structure(xproduct);

  // Postconditions:

  ensure(has_product_structure(xlocal_id));

  // Exit:

  return;
}

void
sheaf::explicit_index_space_interval::
delete_product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  _states[xlocal_id]->delete_product_structure();
  
  // Postconditions:

  ensure(!has_product_structure(xlocal_id));

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::explicit_index_space_interval::
product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  const abstract_product_structure& result =
    _states[xlocal_id]->product_structure();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::explicit_index_space_interval::
product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  abstract_product_structure& result = 
    _states[xlocal_id]->product_structure();
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
has_product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = _states[xlocal_id]->has_product_structure();

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
sheaf::explicit_index_space_interval::
get_id_space(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_handle& result = _states[xlocal_id]->get_id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_interval::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  _states[local_scope(xid_space.index())]->release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_interval::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  pod_type local_id = local_scope(xid_space.index());

  bool result =
    contains(local_id) && _states[local_id]->allocated_id_space(xid_space);

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
sheaf::explicit_index_space_interval::
get_id_space_iterator(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_iterator& result = _states[xlocal_id]->get_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_interval::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  _states[local_scope(xitr.index())]->release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_interval::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  pod_type local_id = local_scope(xitr.index());

  bool result =
    contains(local_id) && _states[local_id]->allocated_iterator(xitr);

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
sheaf::explicit_index_space_interval::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const explicit_index_space_interval*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_interval::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_interval::invariant());

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
 
#include "ComLimitPoint/sheaf/index_space_family.h"

size_t
sheaf::
deep_size(const explicit_index_space_interval& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add memory associated with member _states.

  /// @hack Since block calls the namespace level function, we must
  /// call deep size on all the states in the block directly.

//   result += deep_size(xn._states, false);

  for(pod_index_type i = 0; i < xn._states.ub(); ++i)
  {
    if(xn._states[i] != 0)
    {
      result += xn._states[i]->deep_size(true);
    }
  }
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
