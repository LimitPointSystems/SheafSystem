
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

// Implementation for class block_relation

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block_relation.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BLOCK_RELATION FACET
// ===========================================================

///
fiber_bundle::block_relation::
block_relation()
{
  // Nothing to do.
}

///
fiber_bundle::block_relation::
~block_relation()
{
  // Nothing to do.
}


// ===========================================================
// ANY FACET
// ===========================================================

///
bool
fiber_bundle::block_relation::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(any::invariant());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
fiber_bundle::block_relation::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const block_relation*>(other) != 0;

  // Postconditions:

  return result;
}



