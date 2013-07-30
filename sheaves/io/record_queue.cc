
// $Name@
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
/// Implementation for class record_queue

#include "record_queue.h"

#include "assert_contract.h"

// ===========================================================
// RECORD_QUEUE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS 

sheaf::record_queue::
record_queue()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return;
}

sheaf::record_queue::
record_queue(const record_queue& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

sheaf::record_queue::
~record_queue()
{

  // Preconditions:

  // Body:


  // Postconditions:

  // Exit:

  return;
}

void
sheaf::record_queue::
enqueue(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  // Insert xindex at the back of the read queue

  /// @todo replace this representation with something
  /// more sophisticated that supports hyperslices

  _record_queue.push(xindex);

  // Postconditions:

  ensure(!is_empty());
  ensure(unexecutable(ct() == old ct() + 1));

  // Exit

  return;
}

sheaf::pod_index_type
sheaf::record_queue::
dequeue()
{
  // Preconditions:

  require(!is_empty());

  // Body:

  pod_index_type result = _record_queue.front();
  _record_queue.pop();

  // Postconditions:

  ensure(unexecutable(ct() == old ct() - 1));
  /// @todo make above assertion executable

  // Exit

  return result;
}

int
sheaf::record_queue::
ct() const
{
  return _record_queue.size();
}

bool
sheaf::record_queue::
is_empty() const
{
  return _record_queue.empty();
}

void
sheaf::record_queue::
clear()
{
  // Preconditions:

  // Body:

  while(!is_empty())
    (void)dequeue();

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RECORD_QUEUE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS 

sheaf::record_queue*
sheaf::record_queue::
clone() const
{
  record_queue* result;

  // Preconditions:

  // Body:

  result = new record_queue();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::record_queue::
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
sheaf::record_queue::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const record_queue*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


