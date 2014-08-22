
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

// Implementation for class poset_bounds

#include "ComLimitPoint/sheaf/poset_bounds.h"

#include "ComLimitPoint/sheaf/assert_contract.h"

// ===========================================================
// ANY FACET
// ===========================================================

sheaf::poset_bounds*
sheaf::poset_bounds::
clone() const
{
  poset_bounds* result;

  // Preconditions:


  // Body:

  result = new poset_bounds(*this);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_bounds::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_bounds::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const poset_bounds*>(other) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// POSET_BOUNDS FACET
// ===========================================================

sheaf::poset_bounds::
poset_bounds()
{

  // Preconditions:

  // Body:

  _lb = 0;
  _lb_is_singleton = false;
  _bounded_below = false;

  _ub = 0;
  _ub_is_singleton = false;
  _bounded_above = false;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::poset_bounds::
poset_bounds(const poset_bounds& xother)
    : _descriptor(xother._descriptor)
{
  // Preconditions:

  // Body:

  switch(_descriptor.mode())
  {
  case poset_bounds_descriptor::MEMBER_MEMBER:
    _lb = (xother._lb != 0) ? new zn_to_bool(*xother._lb) : 0;
    _lb_is_singleton = true;

    _bounded_below = (lb_id() != BOTTOM_INDEX);

    _ub = (xother._ub != 0) ? new zn_to_bool(*xother._ub) : 0;
    _ub_is_singleton = true;

    _bounded_above = (ub_id() != TOP_INDEX);

    break;

  case poset_bounds_descriptor::MEMBER_SUBPOSET:
    _lb = (xother._lb != 0) ? new zn_to_bool(*xother._lb) : 0;
    _lb_is_singleton = true;

    _bounded_below = (lb_id() != BOTTOM_INDEX);

    _ub = xother._ub;
    _ub_is_singleton = false;
    _bounded_above = true;

    break;

  case poset_bounds_descriptor::SUBPOSET_MEMBER:
    _lb = xother._lb;
    _lb_is_singleton = false;
    _bounded_below = true;

    _ub = (xother._ub != 0) ? new zn_to_bool(*xother._ub) : 0;
    _ub_is_singleton = true;

    _bounded_above = (ub_id() != TOP_INDEX);

    break;

  case poset_bounds_descriptor::SUBPOSET_SUBPOSET:
    _lb = xother._lb;
    _lb_is_singleton = false;
    _bounded_below = true;

    _ub = xother._ub;
    _ub_is_singleton = false;
    _bounded_above = true;

    break;

  default:
    post_fatal_error_message("unrecognized specification mode");
    break;
  }

  // Postconditions:

  ensure(invariant());
}

sheaf::poset_bounds::
poset_bounds(const poset_bounds_descriptor& xdesc)
    : _descriptor(xdesc)
{
  // Preconditions:


  // Body:

  switch(_descriptor.mode())
  {
  case poset_bounds_descriptor::MEMBER_MEMBER:
    _lb = 0;
    _lb_is_singleton = true;

    _bounded_below = (lb_id() != BOTTOM_INDEX);

    _ub = 0;
    _ub_is_singleton = true;

    _bounded_above = (ub_id() != TOP_INDEX);

    break;

  case poset_bounds_descriptor::MEMBER_SUBPOSET:
    _lb = 0;
    _lb_is_singleton = true;

    _bounded_below = (lb_id() != BOTTOM_INDEX);

    _ub = 0;
    _ub_is_singleton = false;
    _bounded_above = true;

    break;

  case poset_bounds_descriptor::SUBPOSET_MEMBER:
    _lb = 0;
    _lb_is_singleton = false;
    _bounded_below = true;

    _ub = 0;
    _ub_is_singleton = true;

    _bounded_above = (ub_id() != TOP_INDEX);

    break;

  case poset_bounds_descriptor::SUBPOSET_SUBPOSET:
    _lb = 0;
    _lb_is_singleton = false;
    _bounded_below = true;

    _ub = 0;
    _ub_is_singleton = false;
    _bounded_above = true;

    break;

  default:
    post_fatal_error_message("unrecognized specification mode");
    break;
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::poset_bounds::
~poset_bounds()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


sheaf::poset_bounds_descriptor
sheaf::poset_bounds::
descriptor() const
{
  return _descriptor;
}

sheaf::poset_bounds_descriptor::specification_mode
sheaf::poset_bounds::
mode() const
{
  return _descriptor.mode();
}


sheaf::pod_index_type
sheaf::poset_bounds::
lb_id() const
{
  return _descriptor.lb_id();
}

void
sheaf::poset_bounds::
put_lb_id(pod_index_type xlb_id)
{
  // Preconditions:

  require(lb_is_singleton());

  // Body:

  _descriptor.put_lb_id(xlb_id);

  // Postconditions:

  ensure(lb_id() == xlb_id);

  // Exit

  return;
}

void
sheaf::poset_bounds::
put_lb_id(const scoped_index& xlb_id)
{
  // Preconditions:

  require(lb_is_singleton());

  // Body:

  _descriptor.put_lb_id(xlb_id.hub_pod());

  // Postconditions:

  ensure(lb_id() == xlb_id.hub_pod());

  // Exit

  return;
}

bool
sheaf::poset_bounds::
lb_is_singleton() const
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _lb_is_singleton;
}

bool
sheaf::poset_bounds::
bounded_below() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _bounded_below;
}

sheaf::pod_index_type
sheaf::poset_bounds::
ub_id() const
{
  return _descriptor.ub_id();
}

void
sheaf::poset_bounds::
put_ub_id(pod_index_type xub_id)
{
  // Preconditions:

  require(ub_is_singleton());

  // Body:

  _descriptor.put_ub_id(xub_id);

  // Postconditions:

  ensure(ub_id() == xub_id);

  // Exit

  return;
}

void
sheaf::poset_bounds::
put_ub_id(const scoped_index& xub_id)
{
  // Preconditions:

  require(ub_is_singleton());

  // Body:

  _descriptor.put_ub_id(xub_id.hub_pod());

  // Postconditions:

  ensure(ub_id() == xub_id.hub_pod());

  // Exit

  return;
}

bool
sheaf::poset_bounds::
ub_is_singleton() const
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _ub_is_singleton;
}

bool
sheaf::poset_bounds::
ub_is_decomposition() const
{
  bool result;

  // Preconditions:

  // Body:

  /// @hack avoid expense of computing join by assuming
  /// if bound is subposet then join is external schema.

  result = !_ub_is_singleton;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_bounds::
bounded_above() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _bounded_above;
}



// PROTECTED MEMBER FUNCTIONS

