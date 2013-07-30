
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

// Implementation for class poset_bounds_descriptor

 

#include "poset_bounds_descriptor.h"
#include "assert_contract.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

sheaf::poset_bounds_descriptor::
poset_bounds_descriptor()
{
  // Preconditions:

  // Body:

  _mode  = NOT_A_MODE;
  _lb_id = invalid_pod_index();
  _ub_id = invalid_pod_index();

  // Postconditions:

  ensure(invariant());
  ensure(mode() == NOT_A_MODE);
  ensure(!is_valid(lb_id()));
  ensure(!is_valid(ub_id()));

  // Exit

  return;
}

sheaf::poset_bounds_descriptor::
poset_bounds_descriptor(const poset_bounds_descriptor& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);
}

sheaf::poset_bounds_descriptor&
sheaf::poset_bounds_descriptor::
operator=(const poset_bounds_descriptor& xother)
{

  // Preconditions:

  // Body:

  _mode  = xother._mode;
  _lb_id = xother._lb_id;
  _ub_id = xother._ub_id;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

  // Exit:

  return *this;
}

bool
sheaf::poset_bounds_descriptor::
operator==(const poset_bounds_descriptor& xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (_mode  == xother._mode) &&
    (_lb_id == xother._lb_id) &&
    (_ub_id == xother._ub_id);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

sheaf::poset_bounds_descriptor*
sheaf::poset_bounds_descriptor::
clone() const
{
  poset_bounds_descriptor* result;

  // Preconditions:

  // Body:

  result = new poset_bounds_descriptor(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

sheaf::poset_bounds_descriptor::
~poset_bounds_descriptor()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


bool
sheaf::poset_bounds_descriptor::
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

    /// @issue are there any clauses in this invariant?
    /// @todo finish poset_bounds_descriptor::invariant.

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_bounds_descriptor::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const poset_bounds_descriptor*>(other) != 0;

  // Postconditions:

  return result;

}

// POSET_BOUNDS_DESCRIPTOR FACET

int
sheaf::poset_bounds_descriptor::
mode_to_int(specification_mode xmode)
{
  int result;

  // Preconditions:

  // Body:

  /// @issue The C++ standard says this map is unnecessary.
  /// But we've implemented anyway, just in case not all
  /// compilers follow the standard.

  switch(xmode)
  {
  case MEMBER_MEMBER:
    result = 0;
    break;
  case MEMBER_SUBPOSET:
    result = 1;
    break;
  case SUBPOSET_MEMBER:
    result = 2;
    break;
  case SUBPOSET_SUBPOSET:
    result = 3;
    break;
  default:
    post_fatal_error_message("unrecognized specification mode");
    break;
  }

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_bounds_descriptor::specification_mode
sheaf::poset_bounds_descriptor::
int_to_mode(int xmode)
{
  specification_mode result;

  // Preconditions:

  require((0 <= xmode) && (xmode <= 3));

  // Body:

  switch(xmode)
  {
  case 0:
    result = MEMBER_MEMBER;
    break;
  case 1:
    result = MEMBER_SUBPOSET;
    break;
  case 2:
    result = SUBPOSET_MEMBER;
    break;
  case 3:
    result = SUBPOSET_SUBPOSET;
    break;
  }

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_bounds_descriptor::
poset_bounds_descriptor(specification_mode xmode,
                        pod_index_type xlb_id,
                        pod_index_type xub_id)
    : _mode(xmode),
      _lb_id(xlb_id),
      _ub_id(xub_id)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(mode()  == xmode);
  ensure(lb_id() == xlb_id);
  ensure(ub_id() == xub_id);

  // Exit

  return;
}

sheaf::poset_bounds_descriptor::
poset_bounds_descriptor(specification_mode xmode,
                        const scoped_index& xlb_id,
                        const scoped_index& xub_id)
    : _mode(xmode),
      _lb_id(xlb_id.hub_pod()),
      _ub_id(xub_id.hub_pod())
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(mode()  == xmode);
  ensure(lb_id() == xlb_id.hub_pod());
  ensure(ub_id() == xub_id.hub_pod());

  // Exit

  return;
}

sheaf::poset_bounds_descriptor::specification_mode
sheaf::poset_bounds_descriptor::
mode() const
{
  specification_mode result;

  // Preconditions:

  // Body:

  result = _mode;

  // Postconditions:

  // Can't call invariant because it's not const
  // ensure(invariant());

  // Exit

  return result;
}

bool
sheaf::poset_bounds_descriptor::
lb_is_member() const
{
  bool result;

  // Preconditions:

  // Body:

  result = ((mode() == MEMBER_MEMBER) || (mode() == MEMBER_SUBPOSET));

  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());
  ensure(result == ((mode() == MEMBER_MEMBER) || (mode() == MEMBER_SUBPOSET)));

  // Exit

  return result;
}

bool
sheaf::poset_bounds_descriptor::
ub_is_member() const
{
  bool result;

  // Preconditions:

  // Body:

  result = ((mode() == MEMBER_MEMBER) || (mode() == SUBPOSET_MEMBER));

  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());
  ensure(result == ((mode() == MEMBER_MEMBER) || (mode() == SUBPOSET_MEMBER)));

  // Exit

  return result;
}

sheaf::pod_index_type
sheaf::poset_bounds_descriptor::
lb_id() const
{
  return _lb_id;
}

void
sheaf::poset_bounds_descriptor::
put_lb_id(pod_index_type xlb_id)
{
  // Preconditions:

  // Body:

  _lb_id = xlb_id;

  // Postconditions:

  ensure(lb_id() == xlb_id);

  // Exit:

  return;
}

void
sheaf::poset_bounds_descriptor::
put_lb_id(const scoped_index& xlb_id)
{
  // Preconditions:

  // Body:

  _lb_id = xlb_id.hub_pod();

  // Postconditions:

  ensure(lb_id() == xlb_id.hub_pod());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::poset_bounds_descriptor::
ub_id() const
{
  return _ub_id;
}

void
sheaf::poset_bounds_descriptor::
put_ub_id(pod_index_type xub_id)
{
  // Preconditions:

  // Body:

  _ub_id = xub_id;

  // Postconditions:

  ensure(ub_id() == xub_id);

  // Exit:

  return;
}

void
sheaf::poset_bounds_descriptor::
put_ub_id(const scoped_index& xub_id)
{
  // Preconditions:

  // Body:

  _ub_id = xub_id.hub_pod();

  // Postconditions:

  ensure(ub_id() == xub_id.hub_pod());

  // Exit:

  return;
}

bool
sheaf::poset_bounds_descriptor::
lb_is_valid_for(const poset_state_handle& xposet) const
{
  bool result = true;

  // Preconditions:

  require(xposet.state_is_read_accessible());

  // Body:

  if(lb_is_member())
  {
    result = xposet.contains_member(lb_id());
  }
  else
  {
    result =
      lb_id() == TOC_INDEX || xposet.includes_subposet(lb_id());
  }


  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());
  ensure(lb_is_member() ? xposet.contains_member(lb_id()) : true);

  ensure(!lb_is_member() ?
         (lb_id() == TOC_INDEX) || xposet.includes_subposet(lb_id()) :
         true);

  // Exit

  return result;
}

bool
sheaf::poset_bounds_descriptor::
ub_is_valid_for(const poset_state_handle& xposet) const
{
  bool result = true;

  // Preconditions:

  require(xposet.state_is_read_accessible());

  // Body:

  result = (ub_is_member() ?
            xposet.contains_member(ub_id()) :
            xposet.includes_subposet(ub_id()));

  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());
  ensure(result == (ub_is_member() ?
                    xposet.contains_member(ub_id()) :
                    xposet.includes_subposet(ub_id())));

  // Exit

  return result;
}

bool
sheaf::poset_bounds_descriptor::
is_valid_for(const poset_state_handle& xposet) const
{
  bool result = true;

  // Preconditions:

  require(xposet.state_is_read_accessible());

  // Body:

  result = (lb_is_valid_for(xposet) && ub_is_valid_for(xposet));

  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());
  ensure(result == (lb_is_valid_for(xposet) && ub_is_valid_for(xposet)));

  // Exit

  return result;
}


bool
sheaf::poset_bounds_descriptor::
lb_member_is_bottom() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (lb_is_member() && (lb_id() == BOTTOM_INDEX));

  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());

  ensure(result == (lb_is_member() && (lb_id() == BOTTOM_INDEX)));

  // Exit

  return result;
}

bool
sheaf::poset_bounds_descriptor::
ub_member_is_not_top() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = (ub_is_member() && (ub_id() != TOP_INDEX));

  // Postconditions:

  // Can't call invariant because it's not const
  //  ensure(invariant());

  ensure(result == (ub_is_member() && (ub_id() != TOP_INDEX)));

  // Exit

  return result;
}

const sheaf::poset_bounds_descriptor&
sheaf::poset_bounds_descriptor::
BOTTOM_TOP = *(new poset_bounds_descriptor(MEMBER_MEMBER, BOTTOM_INDEX, TOP_INDEX));

const sheaf::poset_bounds_descriptor&
sheaf::poset_bounds_descriptor::
BOTTOM_BOTTOM = *(new poset_bounds_descriptor(MEMBER_MEMBER, BOTTOM_INDEX, BOTTOM_INDEX));

