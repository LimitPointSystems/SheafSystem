
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

// Implementation for class subposet_member_iterator

#include "subposet_member_iterator.h"
#include "assert_contract.h"

#include "poset_state_handle.h"
#include "subposet.h"

///
sheaf::subposet_member_iterator::
subposet_member_iterator(const subposet& xdomain)
{

  // Preconditions:

  require(xdomain.state_is_read_accessible());

  // Body:

  _filter = 0;
  _new_filter = false;

  reset(&xdomain);

  // Postconditions:

  ensure(invariant());
}


///
bool
sheaf::subposet_member_iterator::
invariant() const
{
  bool result = true;

  // Body:

  invariance(domain() != 0);
  invariance(!is_done() ? domain()->contains_member(this) : true);

  // Exit:

  return result;

}


///
sheaf::subposet_member_iterator::
~subposet_member_iterator()
{
  // Preconditions:

  // Body:

  if ((_filter != 0) && _new_filter)
  {
    delete _filter;
  }

  // Necessary to prevent poset_member::~poset_member from deleting state

  detach_from_state();

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}




///
bool
sheaf::subposet_member_iterator::
is_done() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _itr.is_done();
}




///
bool
sheaf::subposet_member_iterator::
is_last() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _itr.is_last();
}


///
void
sheaf::subposet_member_iterator::
next()
{
  // Preconditions:

  require(!is_done());
  require(state_is_read_accessible());


  // Body:

  _itr.next();

  if (!_itr.is_done())
  {
    //attach_to_state(_domain->host(), _itr.item());
    attach_to_state(_domain->host(), _itr.index());
  }
  else
  {
    detach_from_state();
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}


///
void
sheaf::subposet_member_iterator::
reset()
{
  // Preconditions:

  require(domain() != 0);
  require(domain()->state_is_read_accessible());


  // Body:

  _itr.reset();

  if (!_itr.is_done())
  {
    //attach_to_state(_domain->host(), _itr.item());
    attach_to_state(_domain->host(), _itr.index());
  }
  else
  {
    detach_from_state();
  }


  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}


///
void
sheaf::subposet_member_iterator::
reset(const subposet* xdomain)
{

  // Preconditions:

  require(xdomain != 0);
  require(xdomain->state_is_read_accessible());

  // Body:

  _domain = const_cast<subposet*>(xdomain);

  initialize_filter();

  _itr.reset(_filter, _domain->host()->member_hub_id_space(false));

  if (!_itr.is_done())
  {
    attach_to_state(_domain->host(), _itr.index());
  }
  else
  {
    detach_from_state();
  }

  // Postconditions:

  ensure(domain() == xdomain);
  ensure(invariant());
}



///
sheaf::subposet*
sheaf::subposet_member_iterator::
domain() const
{
  subposet* result;

  // Preconditions:

  // Body:

  result = _domain;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

void
sheaf::subposet_member_iterator::
initialize_filter()
{
  // Preconditions:

  require(domain() != 0);
  require(domain()->state_is_read_accessible());

  // Body:


  // First clean up any existing filter.

  if ((_filter != 0) && _new_filter)
  {
    // `this' allocated filter, delete it.
    delete _filter;
    _new_filter = false;
  }

  // Initialize the new filter.

  if (_domain->host()->is_version())
  {
    // filter is intersection of whole() and _domain.

    _filter = new zn_to_bool(*(_domain->members()));
    _new_filter = true;
    _filter->b_and_sa(_domain->host()->whole().members());
  }
  else
  {
    // use _domain itself as the filter.

    _filter = _domain->members();
    _new_filter = false;
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
sheaf::subposet_member_iterator&
sheaf::subposet_member_iterator::
operator=(const abstract_poset_member& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  //Exit:

  return *this;
}

///
sheaf::subposet_member_iterator&
sheaf::subposet_member_iterator::
operator=(const subposet_member_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  //Exit:

  return *this;
}

