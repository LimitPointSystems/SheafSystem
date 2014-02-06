
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

// Implementation for class variable_length_record

#include "variable_length_record.h"

#include "record_index.h"
#include "assert_contract.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// Copy constructor
///
sheaf::variable_length_record::
variable_length_record(const variable_length_record& xother)
    : record(xother),
    _buf(xother._buf),
    _buf_ub(xother._buf_ub),
    _delete_buffer(xother._delete_buffer)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



// Virtual constructor
///
sheaf::variable_length_record*
sheaf::variable_length_record::
clone() const
{
  variable_length_record* result;

  // Preconditions:

  // Body:

  result = new variable_length_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::variable_length_record::
~variable_length_record()
{

  // Preconditions:

  // Body:

  if(_delete_buffer)
  {
    delete[] static_cast<char*>(_buf);
  }


  // Postconditions:

  // Exit:

  return;
}


// Class invariant
///
bool
sheaf::variable_length_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && record::invariant();

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

// Conformance test
///
bool
sheaf::variable_length_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const variable_length_record*>(other) != 0;

  // Postconditions:

  return result;

}



// VARIABLE_LENGTH_RECORD INTERFACE



///
sheaf::variable_length_record::
variable_length_record(const poset_scaffold& xscaffold)
    : record(xscaffold)
{
  // Preconditions:

  // Body:

  _buf = 0;
  _buf_ub = 0;
  _delete_buffer = false;
  _is_internal = false;
  _is_external = false;

  // Postconditions:

  ensure(invariant());

  ensure(!external_index().is_valid());
  ensure(&(scaffold()) == &xscaffold);
  ensure(buf() == 0);
  ensure(buf_ub() == 0);
  ensure(!delete_buffer());
  ensure(!is_internal());
  ensure(!is_external());

  // Exit

  return;
}



///
void*
sheaf::variable_length_record::
buf() const
{
  void* result;

  // Preconditions:

  // Body:

  result = _buf;

  // Postconditions:

  // Exit:

  return result;
}



///
size_t
sheaf::variable_length_record::
buf_ub() const
{
  size_t result;

  // Preconditions:

  // Body:

  result = _buf_ub;

  // Postconditions:

  // Exit:

  return result;
}

///
void
sheaf::variable_length_record::
put_buf(const void* xbuf, size_t xbuf_ub)
{
  // Preconditions:

  require((xbuf == 0) == (xbuf_ub == 0));
  require(unexecutable(xuf_ub == allocated size of xbuf));

  // Body:

  _buf = const_cast<void *>(xbuf);
  _buf_ub = xbuf_ub;

  // Postconditions:

  ensure(buf() == xbuf);
  ensure(buf_ub() == xbuf_ub);

  // Exit

  return;
}

