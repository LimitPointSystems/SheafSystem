
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class binary_index_space

#include "binary_index_space.h"

#include "assert_contract.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BINARY_INDEX_SPACE FACET
// ===========================================================

///
sheaf::ragged_array<unary_index>*
fiber_bundle::binary_index_space::
neighbor_list() const
{
  // Preconditions:

  // Body:

  // Create the block neighborhoods.

  binary_index lblock_id, lnbr_id;
  ragged_array<unary_index>* result = new ragged_array<unary_index>(9*size);

  for(lblock_id.i=0; lblock_id.i<i_size; lblock_id.i++)
  {
    for(lblock_id.j=0; lblock_id.j<j_size; lblock_id.j++)
    {

      // Make a list of the members in the neighborhood of
      // the current member, including the current member itself.

      binary_index ldelta;
      for(ldelta.i=-1; ldelta.i<2; ldelta.i++)
      {
        for(ldelta.j=-1; ldelta.j<2; ldelta.j++)
        {
          lnbr_id = lblock_id + ldelta;
          if(contains(lnbr_id))
          {
            result->push_back(to_row_major_offset(lnbr_id));
          }
        }
      }

      if(result->row_ct() < size)
      {
        // Move the the next row.

        result->new_back_row();
      }
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

ostream&
fiber_bundle::
operator<<(ostream& os, const fiber_bundle::binary_index_space& xbis)
{
  os << "i_size: " << xbis.i_size
  << " j_size: " << xbis.j_size
  << " size: " << xbis.size;
  return os;
}


