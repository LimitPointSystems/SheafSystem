
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

// Implementation for class POSET_DFT


#ifndef POSET_DFT_H
#include "poset_dft.h"
#endif

#include "abstract_poset_member.h"
#include "assert_contract.h"
#include "poset.h"
#include "total_poset_member.h"
#include "index_space_iterator.h"
#include "zn_to_bool.h"

///
sheaf::poset_dft::
poset_dft(const poset_state_handle* xhost)
    : poset_traverser(xhost)
{

  // Preconditions

  require(precondition_of(poset_traverser));

  // body:

  _descend = true;

  // postconditions:

  ensure(invariant());
}


///
sheaf::poset_dft::
~poset_dft()
{

  // Delete the poset members on the free members stack

  while(!_free_mbrs.empty())
  {
    delete (_free_mbrs.top());
    _free_mbrs.pop();
  }

}


void
sheaf::poset_dft::
private_traverse()
{

  // Preconditions: (from poset_traverser)

  require(_anchor != 0);

  // Body:

  recursive_dft(_anchor);

  // Postconditions:

  ensure(unexecutable(traversal truncated or all members <= anchor() visited));

  // Exit:

  return;
}


void
sheaf::poset_dft::
recursive_dft(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(xmbr != 0);

  // Body:

  // This is the first time the traversal has visited this member,
  // mark it and execute the previsit action

  mark_visited(xmbr);
  previsit_action(xmbr);
  ensure_visited_ub(); // action may have changed size of poset

  // check to see if previsit_action decided to continue the descent

  if(_descend)
  {
    // continue dft, descend into lower cover

    /// @issue Comments on possible optimization:
    ///
    /// The current implementation explicitly represents all links, including
    /// the links from the minimal jims to the greatest_bootom_jem.
    /// In order to avoid the typically large storage requirements, the link between
    /// the minimal jims and the bottom could be implied, not actually represented.
    /// If xmbr is a jim and has an empty lower cover, there is an implied link
    /// to the greatest join equivalent member of the bottom, and vice versa.

    // Assuming that there are no disconnected members,
    // there are then four cases when the cover of a member can be empty
    // 1) the upper cover of the top
    // 2) the upper cover of the greatest_bottom_jem
    // 3) the lower cover of the bottom
    // 4) the lower cover of a minimal jim
    //
    // Cases 1 and 3 are handled properly by the lack of explicit links.
    // Cases 4 can be dealt with by substituting a single global object
    // _implied_lower_cover of type list_cover_set for xmbr.cover
    // The _implied_lower_cover has one member, the greatest_bottom_jem.
    // Case 2 must be handled specially. Instead of a cover set iterator,
    // we can use the member iterator for host()->jims() and only follow
    // jims with empty lower covers.


    // get an member for the other end of a link

    abstract_poset_member* linked_mbr;
    if(_free_mbrs.empty())
    {
      // No free iterators, have to make one.

      linked_mbr = _anchor->clone();
    }
    else
    {
      // Just get one from the free stack.

      linked_mbr = _free_mbrs.top();
      _free_mbrs.pop();
    }

    // Have to set version to CCR and must be attached
    // to some member to do this, bottom will do.

    linked_mbr->attach_to_state(&(host()->bottom()));
    linked_mbr->put_version(COARSEST_COMMON_REFINEMENT_VERSION);

    // Initialize itr for lower (upper) cover of xmbr.

    index_space_iterator& link_itr =
      host()->get_cover_id_space_iterator(_in_down_set, xmbr->index());

    // Iterate over lower (upper) cover of xmbr

    while(!link_itr.is_done())
    {
      // Attach to the member at the other end of the link.
      // Must use the host, index signature because linked_mbr
      // may have been deleted or otherwise unattached in
      // postvisit or link actions.

      linked_mbr->attach_to_state(host(), link_itr.hub_pod());

      // Increment the iterator directly after attaching to state.
      // This moves the iterator past the current linked member
      // so it can be deleted in the post_visit action.

      link_itr.next();

      if (! has_been_visited(linked_mbr))
      {
        // First time we've seen this member, recur.

        recursive_dft(linked_mbr);
      }

      link_action(xmbr, linked_mbr);
      ensure_visited_ub(); // Action may have changed size of poset.
    }

    host()->release_cover_id_space_iterator(link_itr);

    // Finished with the poset member;
    // detach it and push it onto the stack,
    // so we won't have to create one next time.

    linked_mbr->detach_from_state();
    _free_mbrs.push(linked_mbr);

  } // end if _descend
  else
  {
    // Reset _descend to default (true).

    _descend = true;
  }

  // Finished with the cover of xmbr;
  // execute the postvisit_action.

  postvisit_action(xmbr);
  ensure_visited_ub(); // Action may have changed size of poset.

  // Postconditions:

  ensure(unexecutable(traversal truncated or all members <= xmbr visited));

  // Exit:

  return;
}



