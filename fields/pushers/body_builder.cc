
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

/// @file
/// Implementation for class body_builder

#include "ComLimitPoint/fields/body_builder.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "ComLimitPoint/sheaf/block.impl.h"
#include "ComLimitPoint/sheaf/index_space_iterator.h"
#include "ComLimitPoint/fiber_bundle/section_eval_iterator.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "ComLimitPoint/sheaf/subposet.h"
#include "ComLimitPoint/sheaf/tern.h"
#include "ComLimitPoint/fields/field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// BODY_BUILDER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::body_builder::
body_builder()
{

  // Preconditions:


  // Body:

  // Nothing to do;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


fields::body_builder::
~body_builder()
{

  // Preconditions:


  // Body:

  // Nothing to do.;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::block<sheaf::scoped_index>*
fields::body_builder::
build(field_vd& xfield, value_type xlower, value_type xupper)
{
  block<scoped_index>* result;

  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().state_is_read_write_accessible());
  require(xfield.dp() == 1);
  require(xlower < xupper);

  // Body:

  result = new block<scoped_index>;
  build_pa(xfield, xlower, xupper, *result);

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

void
fields::body_builder::
build_pa(field_vd& xfield,
         value_type xlower,
         value_type xupper,
         block<scoped_index>& xresult)
{
  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().state_is_read_write_accessible());
  require(xfield.dp() == 1);
  require(xlower < xupper);

  // Body:

  /// @todo Remove cast when base_space_member returns a base_space_poset.

  base_space_poset* lbase_space =
    dynamic_cast<base_space_poset*>(xfield.base_space().host());

  base_space_member lbody(xfield.base_space()); // Any member of base space will do.

  // Find the evaluation members that meet the threshhold criterion.

  subposet lselected(lbase_space);
  select_evaluation_members(xfield, xlower, xupper, lselected);

  // Find all contiguous neighborhoods and join them into bodies.

  block<scoped_index> lresult(16);
  block<scoped_index> lnbrhd(1024);

  // Can't use index_iterator because we are modifying the subposet
  // while we are iterating.

  scoped_index i(lbase_space->member_id(0, false));

  for(; i<lbase_space->member_index_ub(); ++i)
  {
    if(lselected.contains_member(i))
    {

      // Find the contiguous neighborhood of xindex.

      find_contiguous_neighborhood(*lbase_space, lselected, i, lnbrhd);

      // Join the neighborhood to form a body (member of the base space).

      lbody.new_jrm_state(lnbrhd.base(), lnbrhd.ct(), tern::NEITHER, false);
      xresult.push_back(lbody.index());
    }
  }


  // Clean up.

  lselected.delete_state();
  lbody.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

void
fields::body_builder::
select_evaluation_members(const field_vd& xfield,
                          value_type xlower,
                          value_type xupper,
                          subposet& xselected)
{
  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xlower < xupper);

  // Body:

  // Make a dof buffer; start with a reasonable amount of space,
  // just to avoid many small reallocations.

  block<dof_type> ldofs(xfield.dp()*32);

  section_eval_iterator litr(xfield.property().schema());
  while(!litr.evaluators_done())
  {
    ldofs.set_ct(0);
    litr.gather_dofs(xfield.property(), ldofs);
    if(interval_contains_field(litr.evaluator(), ldofs, xlower, xupper))
    {
      // The current eval member is selected by the classifier;
      // enter it into the result.

      xselected.insert_member(litr.evaluator_id());
    }

    litr.next_evaluator();
  }

  // Postconditions:


  // Exit:

  return;
}

bool
fields::body_builder::
interval_contains_field(const section_evaluator& xeval,
                        const block<dof_type>& xdofs,
                        value_type xlower,
                        value_type xupper) const
{
  bool result;

  // Preconditions:

  require(xdofs.ct() == xeval.dof_ct());
  require(xlower < xupper);

  // Body:

  result =
    (xlower <= xeval.min(xdofs.base(), xdofs.ct())) &&
    (xeval.max(xdofs.base(), xdofs.ct()) <= xupper);

  // Postconditions:


  // Exit:

  return result;
}

void
fields::body_builder::
find_contiguous_neighborhood(const base_space_poset& xbase_space,
                             subposet& xselected,
                             const scoped_index& xindex,
                             block<scoped_index>& xresult)
{
  // Preconditions:

  require(xbase_space.state_is_read_accessible());
  require(xselected.contains_member(xindex));

  // Body:

  xresult.set_ct(0);
  size_type lnext = 0;

  xselected.remove_member(xindex);
  xresult.push_back(xindex);

  while(lnext < xresult.ct())
  {
    // Get the member at the front of the queue and pop the front.
    // This shortens the queue; eventually we run out of new neighbors
    // to add below, the front of the queue reaches the back of the queue,
    // and we're done.

    scoped_index mbr_id = xresult[lnext++];

    // The definition of neighbor used here is that neighbors
    // meet in an a member of dimension one lower than the neighbors;
    // that is, neighboring zones share faces. We assume there are no jrms
    // in the lower covers of zones. Then all neighbors of a given zone
    // must be in the upper cover of the lower cover of the zone.
    // Neighbors with lower dimensional meets can be also be handled,
    // at the cost of more complicated traversals.

    // Iterate over the lower cover of the current member.

    index_space_iterator& lc_itr = xbase_space.get_cover_id_space_iterator(LOWER, mbr_id);

    scoped_index nbr_id(xbase_space.member_hub_id_space(false));

    while(!lc_itr.is_done())
    {
      // Iterate over the upper cover of the current member of the lower cover.

      index_space_iterator& uc_itr = xbase_space.get_cover_id_space_iterator(UPPER, lc_itr.hub_pod());

      while(!uc_itr.is_done())
      {
        // The current member of the upper cover is a neighbor.

        nbr_id = uc_itr.hub_pod();
        if(xselected.contains_member(nbr_id.pod()))
        {
          // The neighbor also meets the threshhold criterion.
          // Remove it from the selected subposet. This eventually
          // terminates the outer loop over selected members.
          /// @issue better make sure the iterator supports modifying the membership.

          xselected.remove_member(nbr_id.pod());

          // Put it into the result/queue; this lengthens the queue.
          // Eventually we run out of new neighbors to add.

          xresult.push_back(nbr_id);
        }
        uc_itr.next();
      }
      xbase_space.release_cover_id_space_iterator(uc_itr);

      lc_itr.next();
    }
    xbase_space.release_cover_id_space_iterator(lc_itr);
  }

  // Postconditions:

  ensure(xresult.ct() > 0);

  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::body_builder::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this

  bool result = dynamic_cast<const body_builder*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::body_builder*
fields::body_builder::
clone() const
{
  body_builder* result;

  // Preconditions:

  // Body:

  result = new body_builder();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


bool
fields::body_builder::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

