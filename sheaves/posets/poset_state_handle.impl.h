
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
/// Implementation for member function templates in class poset_state_handle.

#ifndef POSET_STATE_HANDLE_IMPL_H
#define POSET_STATE_HANDLE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef INDEX_SPACE_ITERATOR_H
#include "index_space_iterator.h"
#endif

// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

template<typename handle_type>
handle_type&
sheaf::poset_state_handle::
get_cover_id_space(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(unexecutable("handle type conforms to state or is mutable"));

  // Body:

  handle_type& result = crg().get_cover_id_space<handle_type>(xlower, xmbr_index);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

template<typename filter_type>
void
sheaf::poset_state_handle::
remove_cover_members(const filter_type& xfilter, bool xlower, pod_index_type xmbr_hub_id)
{
  // Preconditions:

  require(contains_member(xmbr_hub_id));

  // Body:

  crg().remove_cover_members(xfilter, xlower, xmbr_hub_id);

  // Postconditions:

  ensure_for_iterator(index_space_iterator& i=get_cover_id_space_iterator(xlower, xmbr_hub_id),
		      !i.is_done(),
		      i.next(),
		      !xfilter(i.hub_pod()),
		      release_cover_id_space_iterator(i));
  
  // Exit:

  return;
}

template<typename filter_type>
void
sheaf::poset_state_handle::
remove_cover_members(const filter_type& xfilter, bool xlower, const scoped_index& xmbr_id)
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  remove_cover_members(xfilter, xlower, xmbr_id.hub_pod());

  // Postconditions:

  ensure_for_iterator(index_space_iterator& i=get_cover_id_space_iterator(xlower, xmbr_id),
		      !i.is_done(),
		      i.next(),
		      !xfilter(i.hub_pod()),
		      release_cover_id_space_iterator(i));
  
  // Exit:

  return;
}

#endif // ifndef POSET_STATE_HANDLE_IMPL_H
