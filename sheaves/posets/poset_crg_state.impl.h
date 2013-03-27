// $RCSfile: poset_crg_state.impl.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:59:06 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for member function templates in class poset_crg_state.

#ifndef POSET_CRG_STATE_IMPL_H
#define POSET_CRG_STATE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_CRG_STATE_H
#include "poset_crg_state.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef CRG_INTERVAL_H
#include "crg_interval.h"
#endif

#ifndef INDEX_SPACE_ITERATOR_H
#include "index_space_iterator.h"
#endif
   

// ===========================================================
// POSET_CRG_STATE FACET
// ===========================================================

template<typename handle_type>
handle_type&
sheaf::poset_crg_state::
get_cover_id_space(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  /// @todo Need a precondition that enforces that handle_type conforms the
  ///       the state or is a mutable handle type.

  // Body:

  crg_interval& linterval = interval(xmbr_index);
  pod_index_type lid = linterval.cover_id_space_id(xlower, xmbr_index);

  handle_type* result = 0;

  if(_id_spaces.handle_conforms_to_state<handle_type>(lid))
  {
    result = &_id_spaces.get_id_space<handle_type>(lid);
  }
  else
  {
    /// @todo Implement conversion from implicit id space the mutable handle
    ///       type.

    not_implemented();
  }

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

template<typename filter_type>
void
sheaf::poset_crg_state::
remove_cover_members(const filter_type& xfilter, bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  /// @todo Review.  Is this the most efficient way to do this?  Probably should
  ///       move this functionality to mutable_index_space_state and allow
  ///       the given implementations to do as efficiently as possible.

  // Gather members that need removed for the cover into a set.

  set<pod_index_type> lmbrs_to_remove;
  index_space_iterator& litr = get_cover_id_space_iterator(xlower, xmbr_index);
   while(!litr.is_done())
   {
     if(xfilter(litr.hub_pod()))
     {
       // Remove the current item from the cover.

       lmbrs_to_remove.insert(litr.hub_pod());
     }

     litr.next();
   }
   release_cover_id_space_iterator(litr);

   if(!lmbrs_to_remove.empty())
   {
     // There are members to be removed.  Force the cover to be explicit
     // and remove the members.

     pod_index_type lspace_id = force_explicit_cover(xlower, xmbr_index, true);

     mutable_index_space_handle& lcover =
       _id_spaces.get_id_space<mutable_index_space_handle>(lspace_id);

     set<pod_index_type>::iterator lmbr_itr;
     for(lmbr_itr = lmbrs_to_remove.begin();
	 lmbr_itr != lmbrs_to_remove.end();
	 ++lmbr_itr)
     {
       lcover.remove_hub(*lmbr_itr, false);
     }

     lcover.update_extrema();

     lcover.release_id_space();
   }
  // Postconditions:

  ensure_for_iterator(index_space_iterator& i=get_cover_id_space_iterator(xlower, xmbr_index),
		      !i.is_done(),
		      i.next(),
		      !xfilter(i.hub_pod()),
		      release_cover_id_space_iterator(i));

  // Exit:

  return;
}

#endif // ifndef POSET_CRG_STATE_IMPL_H
