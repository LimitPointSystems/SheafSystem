
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
/// Implementation for member function templates in class poset_crg_state.

#ifndef POSET_CRG_STATE_IMPL_H
#define POSET_CRG_STATE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef POSET_CRG_STATE_H
#include "SheafSystem/poset_crg_state.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef CRG_INTERVAL_H
#include "SheafSystem/crg_interval.h"
#endif

#ifndef INDEX_SPACE_ITERATOR_H
#include "SheafSystem/index_space_iterator.h"
#endif
   
using namespace std;


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
  require(cover_id_space_handle_conforms_to<handle_type>(xlower, xmbr_index));
  
  // Body:

  pod_index_type lid_space_id = cover_id_space_id(xlower, xmbr_index);
  handle_type& result = _id_spaces.get_id_space<handle_type>(lid_space_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

template<typename handle_type>
bool
sheaf::poset_crg_state::
cover_id_space_handle_conforms_to(bool xlower, pod_index_type xmbr_index) const
{
  // cout << endl << "Entering poset_crg_state::cover_id_space_handle_conforms_to." << endl;

  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lid_space_id = cover_id_space_id(xlower, xmbr_index);
  bool result = _id_spaces.handle_conforms_to_state<handle_type>(lid_space_id);

  // Postconditions:


  // Exit:

  // cout << "Leaving poset_crg_state::cover_id_space_handle_conforms_to." << endl;
  return result;
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
  ///       move this functionality to scattered_insertion_index_space_state and allow
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

     scattered_insertion_index_space_handle& lcover =
       _id_spaces.get_id_space<scattered_insertion_index_space_handle>(lspace_id);

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
