
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

// Implementation for class unary_index_space

#include "ComLimitPoint/fiber_bundle/unary_index_space.h"
#include "ComLimitPoint/sheaf/assert_contract.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// UNARY_INDEX_SPACE FACET
// ===========================================================

///
sheaf::ragged_array<unary_index>*
fiber_bundle::unary_index_space::
neighbor_list() const
{
  // Preconditions:

  // Body:

  // Create the block neighborhoods.

  unary_index lblock_id, lnbr_id;
  ragged_array<unary_index>* result = new ragged_array<unary_index>(3*size);

  for(lblock_id=0; lblock_id<i_size; lblock_id++)
  {
    // Make a list of the members in the neighborhood of
    // the current member, including the current member itself.

    unary_index ldelta;
    for(ldelta=-1; ldelta<2; ldelta++)
    {
      lnbr_id = lblock_id + ldelta;
      if(contains(lnbr_id))
      {
        result->push_back(lnbr_id);
      }
    }

    if(result->row_ct() < size)
    {
      // Move the the next row.

      result->new_back_row();
    }
  }

  // Postconditions:

  ensure(result != 0);
  ensure(result->row_ct() == size);

  // Exit:

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream&
fiber_bundle::
operator<<(std::ostream& os, const fiber_bundle::unary_index_space& xbis)
{
  os << "i_size: " << xbis.i_size
  << " size: " << xbis.size;
  return os;
}


