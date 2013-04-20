

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Iimplementation for templates of kd_lattice

#ifndef KD_LATTICE_IMPL_H
#define KD_LATTICE_IMPL_H

#ifndef KD_LATTICE_H
#include "kd_lattice.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef INDEX_SPACE_ITERATOR_H
#include "index_space_iterator.h"
#endif

#ifndef COHORT_H
#include "cohort.h"
#endif
 
#ifndef SUBPOSET_H
#include "subposet.h"
#endif
 
template <typename M, typename A>
void
geometry::kd_lattice::
search(const sheaf::scoped_index& xid, A& xaction)
{
  // cout << endl << "Entering kd_lattice::search." << endl;

  // Preconditions:

  require(base_space().state_is_read_accessible());

  // Body:

  // Execute the previsit action.

  xaction.previsit(*this, xid);

  if(!this->leaves().contains(xid))
  {
    int lct = 0;
    index_space_iterator& litr = this->base_space().get_cover_id_space_iterator(LOWER, xid);
    while(!litr.is_done() && (lct < 2))
    {
      if(this->member_filter<M>().contains_member(litr.hub_pod()))
      {
	this->search<M, A>(litr.hub_pod(), xaction);
	lct++;
      }
      litr.next();
    }
    this->base_space().release_cover_id_space_iterator(litr);
  }
  
  xaction.postvisit(*this, xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::search." << endl;
  return;
}
 
template <typename A>
void
geometry::kd_lattice::
search2(const sheaf::scoped_index& xid, A& xaction)
{
  // cout << endl << "Entering kd_lattice::search2." << endl;

  // Preconditions:

  require(base_space().state_is_read_accessible());

  // Body:

  // Execute the previsit action.

  xaction.previsit(*this, xid);

  if(!xaction.truncate(*this, xid))
  {
    // Search the lower cover.

    index_space_iterator& litr = this->base_space().get_cover_id_space_iterator(LOWER, xid);
    while(!litr.is_done())
    {
      this->search2<A>(litr.hub_pod(), xaction);
      litr.next();
    }
    this->base_space().release_cover_id_space_iterator(litr);
  }

  // Execute the postvisit action.
  
  xaction.postvisit(*this, xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::search2." << endl;
  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#endif // KD_LATTICE_IMPL_H
