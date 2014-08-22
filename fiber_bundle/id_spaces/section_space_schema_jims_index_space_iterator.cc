
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
/// Implementation for class section_space_schema_jims_index_space_iterator

#include "ComLimitPoint/fiber_bundle/section_space_schema_jims_index_space_iterator.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/explicit_index_space_handle.h"
#include "ComLimitPoint/sheaf/ij_product_structure.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_jims_index_space_state.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_iterator::
section_space_schema_jims_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

fiber_bundle::section_space_schema_jims_index_space_iterator::
section_space_schema_jims_index_space_iterator(const section_space_schema_jims_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return;
}

fiber_bundle::section_space_schema_jims_index_space_iterator::
section_space_schema_jims_index_space_iterator(const index_space_family& xid_spaces,
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

fiber_bundle::section_space_schema_jims_index_space_iterator::
section_space_schema_jims_index_space_iterator(const index_space_family& xid_spaces,
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

fiber_bundle::section_space_schema_jims_index_space_iterator&
fiber_bundle::section_space_schema_jims_index_space_iterator::
operator=(const section_space_schema_jims_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _base_space_itr = &xother.state().base_space().get_iterator();
    *_base_space_itr = *xother._base_space_itr;
  
    _fiber_schema_itr = &xother.state().fiber_schema().get_iterator();
    *_fiber_schema_itr = *xother._fiber_schema_itr;
  
    _section_space_schema_jims_product = new ij_product_structure(*xother._section_space_schema_jims_product);
    _section_space_schema_product = new ij_product_structure(*xother._section_space_schema_product);

    (void) explicit_index_space_iterator::operator=(xother);
  }
  else
  {
    detach();
  }

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

fiber_bundle::section_space_schema_jims_index_space_iterator::
~section_space_schema_jims_index_space_iterator()
{
  // Preconditions:

  // Body:

  // nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_state&
fiber_bundle::section_space_schema_jims_index_space_iterator::
state()
{
  // Preconditions:

  // Body:

  section_space_schema_jims_index_space_state& result =
    reinterpret_cast<section_space_schema_jims_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const fiber_bundle::section_space_schema_jims_index_space_state&
fiber_bundle::section_space_schema_jims_index_space_iterator::
state() const
{
  // Preconditions:

  // Body:

  const section_space_schema_jims_index_space_state& result =
    reinterpret_cast<const section_space_schema_jims_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_iterator&
fiber_bundle::section_space_schema_jims_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const section_space_schema_jims_index_space_iterator& lother =
    dynamic_cast<const section_space_schema_jims_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
fiber_bundle::section_space_schema_jims_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = explicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const section_space_schema_jims_index_space_iterator& lother =
      dynamic_cast<const section_space_schema_jims_index_space_iterator&>(xother);

    result = result && (*_base_space_itr == *lother._base_space_itr);
    result = result && (*_fiber_schema_itr == *lother._fiber_schema_itr);
    result = result && (*_section_space_schema_jims_product == *lother._section_space_schema_jims_product);
    result = result && (*_section_space_schema_product == *lother._section_space_schema_product);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

fiber_bundle::section_space_schema_jims_index_space_iterator*
fiber_bundle::section_space_schema_jims_index_space_iterator::
clone() const
{
  section_space_schema_jims_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new section_space_schema_jims_index_space_iterator(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_iterator&
fiber_bundle::section_space_schema_jims_index_space_iterator::
base_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_base_space_itr;
}

sheaf::index_space_iterator&
fiber_bundle::section_space_schema_jims_index_space_iterator::
fiber_schema_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_fiber_schema_itr;
}

void
fiber_bundle::section_space_schema_jims_index_space_iterator::
update_ids()
{
  // Preconditions:

  require(!base_space_iterator().is_done());
  require(!fiber_schema_iterator().is_done());

  // Body:

  _section_space_schema_jims_product->ordinal(_base_space_itr->pod(),
					      _fiber_schema_itr->pod(),
					      _pod);

  _section_space_schema_product->ordinal(_base_space_itr->hub_pod(),
					 _fiber_schema_itr->hub_pod(),
					 _hub_pod);

  // Postconditions:

  ensure(!is_done());

  // Exit:

  return;
}

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_jims_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Increment fiber schema iterator.

  _fiber_schema_itr->next();

  if(_fiber_schema_itr->is_done())
  {
    // Fiber schema iteration is done,
    // increment base space iterator.

    _base_space_itr->next();

    if(_base_space_itr->is_done())
    {
      // Base space iterator is done,
      // the iteration is finished.

      invalidate_ids();
    }
    else
    {
      // Base space iterator is not done.
      // Reset fiber schema iterator and update the ids.

      _fiber_schema_itr->reset();
      update_ids();
    }
  }
  else
  {
    // Fiber schema iterator is not done, update the ids.

    update_ids();
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() != old_pod);
  ensure(is_done() || hub_pod() != old_hub_pod);

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_jims_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_done = false;

  _base_space_itr->reset();
  _fiber_schema_itr->reset();

  if(_base_space_itr->is_done() || _fiber_schema_itr->is_done())
  {
    // Nothing to iterator over, iteration is done.

    invalidate_ids();
  }
  else
  {
    // Update the ids.

    update_ids();
  }
    
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_jims_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  // Assign the state information.

  _state  = xstate;
  _base_space_itr = &state().base_space().get_iterator();
  _fiber_schema_itr = &state().fiber_schema().get_iterator();
  _section_space_schema_jims_product = state().product_structure().clone();
  _section_space_schema_product = state().section_space_schema_product_structure().clone();

  // Reset the iterator.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == xstate);
  ensure(!is_done() ? pod() >= 0 : true);
  ensure(!is_done() ? is_valid(hub_pod()) : true);

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_jims_index_space_iterator::
detach()
{
  // Preconditions:

  // Body:

  state().base_space().release_iterator(*_base_space_itr);
  state().fiber_schema().release_iterator(*_fiber_schema_itr);
  delete _section_space_schema_jims_product;
  delete _section_space_schema_product;

  _state = 0;

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_jims_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<section_space_schema_jims_index_space_state*>(xstate) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_jims_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_space_schema_jims_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_jims_index_space_iterator::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(explicit_index_space_iterator::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

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
