
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

// Implementation for class member_member_poset_bounds

#include "ComLimitPoint/sheaf/member_member_poset_bounds.h"

#include "ComLimitPoint/sheaf/index_iterator.h"
#include "ComLimitPoint/sheaf/poset_bounds_descriptor.h"
#include "ComLimitPoint/sheaf/poset_state_handle.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/zn_to_bool.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
sheaf::member_member_poset_bounds::
member_member_poset_bounds()
{
  // Preconditions:

  // Body:

  _lb_is_singleton = true;
  _lb_id = BOTTOM_INDEX;
  _bounded_below = false;
  _lb = 0;

  _ub_is_singleton = true;
  _ub_id = TOP_INDEX;
  _bounded_above = false;
  _ub = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

///
sheaf::member_member_poset_bounds::
member_member_poset_bounds(const member_member_poset_bounds& xother)
    : poset_bounds(xother)
{

  // Preconditions:

  // Body:

  member_member_poset_bounds& lother =
    const_cast<member_member_poset_bounds&>(xother);

  _lb = lother._lb != 0 ? new zn_to_bool(*(lother._lb)) : 0;
  _ub = lother._ub != 0 ? new zn_to_bool(*(lother._ub)) : 0;

  // Postconditions:

  ensure(invariant());
}

///
sheaf::member_member_poset_bounds*
sheaf::member_member_poset_bounds::
clone() const
{
  member_member_poset_bounds* result;

  // Preconditions:

  // Body:

  result = new member_member_poset_bounds(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  /// @todo make following executable when is_attached() const.
  ensure(unexecutable("result->is_attached() == is_attached()"));

  // Exit:

  return result;
}

///
sheaf::member_member_poset_bounds::
~member_member_poset_bounds()
{

  // Preconditions:

  // Body:

  detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

///
bool
sheaf::member_member_poset_bounds::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && poset_bounds::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(is_attached() == !(_lb == 0));
    invariance((_lb == 0) == (_ub == 0));
    invariance(lb_is_singleton());
    invariance(ub_is_singleton());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::member_member_poset_bounds::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const member_member_poset_bounds*>(other) != 0;

  // Postconditions:

  return result;

}

// POSET_BOUNDS FACET

///
bool
sheaf::member_member_poset_bounds::
lb_contains_member(const scoped_index& xindex)
{
  bool result;

  // Preconditions:

  require(is_attached());

  // Body:

  result = (xindex == lb_id());

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::index_iterator
sheaf::member_member_poset_bounds::
lb_iterator()
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_iterator result(_lb);

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::member_member_poset_bounds::
ub_contains_member(const scoped_index& xindex)
{
  bool result;

  // Preconditions:

  require(is_attached());

  // Body:

  result = (xindex == ub_id());

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::index_iterator
sheaf::member_member_poset_bounds::
ub_iterator()
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_iterator result(_ub);

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::member_member_poset_bounds::
is_attached()
{
  bool result;

  // Preconditions:

  // Body:

  result = _lb != 0;

  // Postconditions:

  // Exit

  return result;
}

///
void
sheaf::member_member_poset_bounds::
attach_to_state(poset_state_handle* xhost)
{
  // Preconditions:

  require(!is_attached());
  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(lb_id()));
  require(xhost->contains_member(ub_id()));

  // Body:

  /// @issue using zn_to_bool here wastes space.

  _lb = new zn_to_bool(lb_id() + 1);
  _lb->put(_lb_id, true);

  _ub = new zn_to_bool(ub_id()+ 1);
  _ub->put(_ub_id, true);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());

  // Exit

  return;
}

///
void
sheaf::member_member_poset_bounds::
detach_from_state()
{
  // Preconditions:

  // Body:

  if(_lb != 0)
  {
    delete _lb;
    _lb = 0;
  }

  if(_ub != 0)
  {
    delete _ub;
    _ub = 0;
  }

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit

  return;
}

///
sheaf::poset_bounds_descriptor
sheaf::member_member_poset_bounds::
descriptor()
{
  // Preconditions:

  // Body:

  poset_bounds_descriptor
  result(poset_bounds_descriptor::MEMBER_MEMBER, lb_id(), ub_id());

  // Postconditions:

  ensure(result.mode() == poset_bounds_descriptor::MEMBER_MEMBER);
  ensure(result.lb_id() == lb_id());
  ensure(result.ub_id() == ub_id());

  // Exit

  return result;
}

// MEMBER_MEMBER_POSET_BOUNDS FACET

///
sheaf::member_member_poset_bounds::
member_member_poset_bounds(int xlb_id, int xub_id)
{
  // Preconditions:

  // Body:

  _lb = 0;
  _lb_id = xlb_id;
  _lb_is_singleton = true;
  _bounded_below = _lb_id != BOTTOM_INDEX;

  _ub = 0;
  _ub_id = xub_id;
  _ub_is_singleton = true;
  _bounded_above = _ub_id != TOP_INDEX;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit

  return;
}


// PRIVATE MEMBER FUNCTIONS


