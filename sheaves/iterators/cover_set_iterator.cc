

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

/// @file
/// Explicit instantiations for class cover_set_iterator

#include "cover_set_iterator.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "index_space_handle.h"
#include "index_space_iterator.h"
#include "std_iomanip.h"

// ===========================================================
// COVER_SET_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::cover_set_iterator::
cover_set_iterator()
  : _itr(0), _item(invalid_pod_index()), _is_done(true)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_done());

  // Exit:

  return;
}

sheaf::cover_set_iterator::
cover_set_iterator(const index_space_handle& xcover)
{
  // Preconditions:

  // Body:

  reset(xcover);

  // Postconditions:

  ensure(is_done() == (xcover.is_empty()));
  ensure(!is_done() ? item() == xcover.begin() : true);

  // Exit:

  return;
}

sheaf::cover_set_iterator::
cover_set_iterator(pod_index_type xmbr_index)
{
  // Preconditions:

  require(is_valid(xmbr_index));

  // Body:

  reset(xmbr_index);

  // Postconditions:

  ensure(!is_done());
  ensure(item() == xmbr_index);

  // Exit:

  return;
}

sheaf::cover_set_iterator::
cover_set_iterator(const cover_set_iterator& xother)
{
  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure((*this) == xother);

  // Exit:

  return;
}

sheaf::cover_set_iterator& 
sheaf::cover_set_iterator::
operator=(const cover_set_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother._itr == 0)
  {
    _itr = 0;
  }
  else
  {
    /// @issue This causes a look-up for the state for explicit id spaces.
    /// This an inefficiency that should be optimized away.

    _itr = &xother._itr->host().get_iterator(_itr->index());
  }

  _item = xother._item;
  _is_done = xother._is_done;

  // Postconditions:

  /// @issue Postconditions may not be true.  This contructor gets a handle
  /// to a new iterator that is set to the begining of the id space.  The
  /// iterator passed in may have a different state.

  //ensure((*this) == xother);

  // Exit:

  return (*this);
}

sheaf::cover_set_iterator::
~cover_set_iterator()
{
  // Preconditions:

  // Body:

  if(_itr != 0)
  {
    /// @issue This causes a look-up for the state for explicit id spaces.
    /// This an inefficiency that should be optimized away.

    _itr->host().release_iterator(*_itr);
  }
  
  // Postconditions:

  // Exit:

  return;
}

bool 
sheaf::cover_set_iterator::
operator==(const cover_set_iterator& xother) const
{
  // Preconditions:

  // Body:

  bool result =
    (_itr == xother._itr) &&
    (_item == xother._item) &&
    (_is_done == xother._is_done);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::cover_set_iterator::
item() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  // Postconditions:

  // Exit:

  return _item;
}

bool
sheaf::cover_set_iterator::
is_done() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _is_done;
}

void
sheaf::cover_set_iterator::
next()
{
  // Preconditions:

  require(!is_done());

  // Body:

  if(_itr != 0)
  {
    _itr->next();
    _is_done = _itr->is_done();
    _item = _is_done ? invalid_pod_index() : _itr->hub_pod();
  }
  else
  {
    _is_done = true;
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::cover_set_iterator& 
sheaf::cover_set_iterator::
operator++()
{
  // Preconditions:

  require(!is_done());

  // Body:

  next();

  // Postconditions:

  // Exit:

  return *this;
}

sheaf::cover_set_iterator 
sheaf::cover_set_iterator::
operator++(int)
{
  // Preconditions:

  require(!is_done());

  // Body:

  cover_set_iterator result(*this);
  _itr->next();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::cover_set_iterator::
reset()
{
  // Preconditions:

  // Body:

  if(_itr != 0)
  {
    _itr->reset();
    _is_done = _itr->is_done();
    _item = _is_done ? invalid_pod_index() : _itr->hub_pod();
  }
  else
  {
    _is_done = false;
  }

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::cover_set_iterator::
reset(const index_space_handle& xcover)
{
  // Preconditions:

  // Body:

  _itr = &xcover.get_iterator();
  reset();

  // Postconditions:

  ensure(is_done() == (xcover.is_empty()));
  ensure(!is_done() ? item() == xcover.begin() : true);

  // Exit:

  return;
}

void
sheaf::cover_set_iterator::
reset(pod_index_type xmbr_index)
{
  // Preconditions:

  require(is_valid(xmbr_index));

  // Body:

  _itr = 0;
  _item = xmbr_index;
  _is_done = false;

  // Postconditions:

  ensure(!is_done());
  ensure(item() == xmbr_index);

  // Exit:

  return;
}

void
sheaf::cover_set_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  _is_done = true;

  // Postconditions:

  ensure(is_done());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
ostream&
sheaf::
operator<<(ostream& xos, const cover_set_iterator& xi)
{
  cover_set_iterator li(xi);
  li.reset();
  while(!li.is_done())
  {
    xos << setw(10) << li.item();
    li.next();
  }
  
  return xos;
}
