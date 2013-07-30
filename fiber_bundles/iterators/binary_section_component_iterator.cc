
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class binary_section_component_iterator

#include "binary_section_component_iterator.h"

#include "binary_section_space_schema_member.h"
#include "poset_state_handle.h"
#include "assert_contract.h"

///
fiber_bundle::binary_section_component_iterator::
binary_section_component_iterator()
    : section_component_iterator()
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}


///
fiber_bundle::binary_section_component_iterator::
binary_section_component_iterator(const binary_section_component_iterator& xother)
    : section_component_iterator(xother)
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}

///
fiber_bundle::binary_section_component_iterator&
fiber_bundle::binary_section_component_iterator::
operator=(const section_component_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  (void) section_component_iterator::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return *this;
}

///
fiber_bundle::binary_section_component_iterator&
fiber_bundle::binary_section_component_iterator::
operator=(const binary_section_component_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}


///
fiber_bundle::binary_section_component_iterator::
~binary_section_component_iterator()
{

  // Preconditions:

  // Body:

  // Nothing to do - base class does it all.

  // Postconditions:

  // Exit:

  return;
}


///

///
bool
fiber_bundle::binary_section_component_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const binary_section_component_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

///
fiber_bundle::binary_section_component_iterator*
fiber_bundle::binary_section_component_iterator::
clone() const
{
  binary_section_component_iterator* result;

  // Preconditions:

  // Body:

  result = new binary_section_component_iterator;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


bool
fiber_bundle::binary_section_component_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && section_component_iterator::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    result = result && (dynamic_cast<binary_section_space_schema_member*>(_anchor) != 0);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
fiber_bundle::binary_section_component_iterator::
binary_section_component_iterator(const binary_section_space_schema_member& xanchor)
    : section_component_iterator()
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());


  // Body:

  // Base constructor ensures !is_initialized, so set the anchor and reset.

  put_anchor(&xanchor);
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(unexecutable(postorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}


// ITERATOR FACET

///
const fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_component_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  const binary_section_space_schema_member& result =
    reinterpret_cast<binary_section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

// MEMBER ITERATOR FACET

///
const fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_component_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  const binary_section_space_schema_member& result =
    reinterpret_cast<binary_section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}



///
bool
fiber_bundle::binary_section_component_iterator::
item_is_ancestor_of(const section_space_schema_member& xmbr) const
{
  bool result;

  // Preconditions:

  // Body:

  // Always true in this class;
  // intended to be redefined in descendants.

  result = dynamic_cast<const binary_section_space_schema_member*>(&xmbr) != 0;

  // Postconditions:

  // Exit

  return result;
}



// PROTECTED MEMBER FUNCTIONS


///
void
fiber_bundle::binary_section_component_iterator::
reset_item()
{
  // Preconditions:

  // Body:

  if(_item == 0)
  {
    // Create the item handle.

    _item = new binary_section_space_schema_member;
  }

  assertion(is_initialized());

  // Attach the handle.

  update_item();

  // Postconditions:

  ensure(is_initialized());
  ensure(!is_done() == item().is_attached());

  // Exit

  return;
}

