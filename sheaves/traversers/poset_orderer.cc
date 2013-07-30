

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
/// Implementation for class poset_orderer.

#include "poset_orderer.h"
#include "assert_contract.h"
#include "poset_state_handle.h"
#include "poset_member.h"
#include "index_space_iterator.h"
#include "subposet.h"

// ===========================================================
// POSET_ORDERER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_orderer::
poset_orderer(poset_state_handle* xhost)
    : poset_dft(xhost)
{
  // Preconditions:

  require(precondition_of(poset_dft::poset_dft));

  // Body:

  // create the post-visited marker

  _post_visited = new zn_to_bool(member_index_ub().pod());

  // Postconditions:

  ensure(invariant());
}

sheaf::poset_orderer::
~poset_orderer()
{
  // Preconditions:

  // Body:

  delete _post_visited;

  // Postconditions:
}

void
sheaf::poset_orderer::
restore_order(subposet* xlower_bound)
{
  // Preconditions:

  require(xlower_bound != 0 ? has_same_host(xlower_bound) : true);
  require(unexecutable(xlower_bound != 0 ? jrm order is independent of anything below xlower_bound : true));
  require(unexecutable(only bottom has an empty lower cover));
  // ensured in ensure_lattice_invariant before calling this routine

  // Body:

  _lower_bound = xlower_bound;

  // restore the order

  traverse(&(host()->top()), true);

  // Postconditions:

  ensure(unexecutable(jrm order consistent with jim order));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_DFT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
sheaf::poset_orderer::
previsit_action(abstract_poset_member* xmbr)
{
  // Preconditions:

  // Body:

  if((_lower_bound != 0) && _lower_bound->contains_member(xmbr))
  {
    // no need to go deeper

    _descend = false;
  }

  // Postconditions:

  // Exit

  return;
}

void
sheaf::poset_orderer::
postvisit_action(abstract_poset_member* xmbr)
{
  // Preconditions:

  require(has_same_host(xmbr));
  require(has_been_visited(xmbr));

  // Body:

  // Note 1: order relation for jims is defined by links,
  // so we only need to restore order for the jrms
  //
  // Note 2: because it ignores members with empty lower covers,
  // the restore_order routine requires that there are no
  // members with empty lower covers except bottom.

  if(!xmbr->is_jim())
  {
    // xmbr is a jrm

    // If any of the members in the upper cover of xmbr's lower cover
    // have exactly the same lower cover, then they are join equivalent
    // and need to be merged into the join equivalence class of xmbr

    if(!xmbr->cover_is_empty(LOWER))
    {
      // Xmbr's lower cover is not empty.
      // Check all the members of the upper cover of the first member of xmbr's lower cover.
      // Note that every member that has the same lower cover as xmbr has to appear
      // in the upper cover of the first (and every) member of xmbr's lower cover.

      pod_index_type lfirst_lower = xmbr->first_cover_member(LOWER);
      index_space_iterator& uc_itr = host()->get_cover_id_space_iterator(UPPER, lfirst_lower);

      while(!uc_itr.is_done())
      {
        // The upper cover of the first member is not empty.
        // Check for lower cover equivalance with xmbr,
        // but only if the traversal has completely finished with
        // the other member. This condition prevents the merge below
        // from messing up the traversal and keeps the order within the
        // equivalence class compatible with the original order.

        pod_index_type other_mbr_index = uc_itr.hub_pod();

        if( has_been_post_visited(other_mbr_index) &&
            xmbr->cover_is_equal(LOWER, other_mbr_index) )
        {
          // Current member of upper cover has same lower cover as xmbr.

          if(host()->is_jim(other_mbr_index))
          {
            // Other member is a jim.
            // A jrm is never join-equivalent to a jim;
            // if they have the same lower cover, then the jrm < the jim.
            // The jim should cover the top of xmbr's eqv class.
            // Note that the jim has already been post-visited,
            // so the new link can not affect the traversal.

            pod_index_type xmbr_gjem = _host->greatest_jem(xmbr->index().pod());

            _host->new_link(other_mbr_index, xmbr_gjem);
          }
          else
          {
            // If two jrms have the same lower cover,
            // they are join-equivalent.
            // Merge their equivalence classes.

            host()->merge_jems(xmbr->index().pod(), other_mbr_index);

            // Merge stacks xmbr eqv class on top of other eqv class
            // so other now has the correct lower cover.

            host()->copy_cover(LOWER, other_mbr_index, xmbr->index().pod());
          }
        }

        // Move to next member of upper cover.

        uc_itr.next();
      }

      host()->release_cover_id_space_iterator(uc_itr);
    }
  }

  // Postconditions:

  ensure(unexecutable(g has the proper lower cover links w.r.t.xmbr));
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_TRAVERSER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_orderer::
invariant() const
{
  bool result = true;

  result = result && poset_traverser::invariant();
  result = result && (_post_visited != 0);


  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


