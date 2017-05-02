
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

// Implementation for class section_dof_iterator

#include "SheafSystem/section_dof_iterator.h"

#include "SheafSystem/poset_state_handle.h"
#include "SheafSystem/section_space_schema_member.h"
#include "SheafSystem/section_space_schema_poset.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/discretization_iterator.h"
#include "SheafSystem/postorder_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

fiber_bundle::section_dof_iterator&
fiber_bundle::section_dof_iterator::
operator=(const poset_dof_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  (void) poset_dof_iterator::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));
  // Exit

  return *this;
}

fiber_bundle::section_dof_iterator&
fiber_bundle::section_dof_iterator::
operator=(const section_dof_iterator& xother)
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


fiber_bundle::section_dof_iterator::
~section_dof_iterator()
{

  // Preconditions:

  // Body:

  // nothing to do

  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::section_dof_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_dof_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_dof_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance( poset_dof_iterator::invariant() );

  if(invariant_check())
  {
    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// ITERATOR FACET

fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

// MEMBER ITERATOR FACET

fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_dof_iterator::
item_is_ancestor_of(const schema_poset_member& xmbr) const
{
  bool result;

  // Preconditions:

  // Body:

  // Always true in this class;
  // intended to be redefined in descendants.

  result = dynamic_cast<const section_space_schema_member*>(&xmbr) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_dof_iterator::
section_dof_iterator()
    : poset_dof_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

fiber_bundle::section_dof_iterator::
section_dof_iterator(const section_dof_iterator& xother)
    : poset_dof_iterator(xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(is_table_dof() == xother.is_table_dof());

  // Exit:

  return;
}

fiber_bundle::section_dof_iterator::
section_dof_iterator(const section_space_schema_member& xanchor,
		     bool xis_table_dof,
		     int xversion)
  : poset_dof_iterator(xanchor, xis_table_dof, xversion)
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->is_schematized(false));
  require(xanchor.has_version(xversion));

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.unaliased_version(xversion));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}

