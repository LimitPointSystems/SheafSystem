
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
/// Implementation for class index_equivalence_class

#include "ComLimitPoint/sheaf/index_equivalence_class.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/hub_index_space_handle.h"
#include "ComLimitPoint/sheaf/index_space_family_iterator.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/index_space_iterator.h"

#include "ComLimitPoint/sheaf/block.impl.h"

// ===========================================================
// INDEX_EQUIVALENCE_CLASS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_equivalence_class::
index_equivalence_class(const index_space_family& xid_spaces,
			bool xonly_persistent,
			bool xsort_ids)
{  
  // Preconditions:
    
  // Body:

  const hub_index_space_handle& lhub_id_space = xid_spaces.hub_id_space();

  size_type lct = is_valid(lhub_id_space.end()) ? lhub_id_space.end() : 0;
  _equivalence_lists.reserve(lct);
  _equivalence_lists.set_ct(lct);
  
  index_space_family_iterator lid_space_itr(xid_spaces, xonly_persistent);

  // The first id space should be the hub id space.  This assumption will
  // ensure the the first id in the equivalence lists is the hub id.

  assertion(lid_space_itr.only_persistent() || !lid_space_itr.is_done());
  assertion(lid_space_itr.only_persistent() || lid_space_itr.index() == xid_spaces.hub_id_space().index());

  member_type litem;

  while(!lid_space_itr.is_done())
  {
    index_space_iterator& lid_itr = lid_space_itr.get_id_space_iterator();

    // Set the id space index.

    litem.first = lid_itr.index();

    while(!lid_itr.is_done())
    {
      // Add the current id to the end of the equivalence list for
      // the representive id.

      pod_type lhub_id = lid_itr.hub_pod();
      if(lhub_id_space.contains(lhub_id))
      {
	// Only insert ids that are in the hub id space for storage
	// efficiency and to avoid an array out-of-bounds problem when
	// the last term of the hub id space is a reserved term that
	// is not full.

	litem.second = lid_itr.pod();
	_equivalence_lists[lhub_id].push_back(litem);
      }

      // Increment to the next id.

      lid_itr.next();
    }

    lid_space_itr.release_id_space_iterator(lid_itr);
    lid_space_itr.next();
  }

  // The equivalence lists are built, sort them if requested by the user.

  if(xsort_ids)
  {
    for(pod_type i = 0; i < lct; i++)
    {
      _equivalence_lists[i].sort(id_space_less_than);
    }
  }

  // Postconditions:

  // Exit:

  return; 
}

sheaf::index_equivalence_class::
~index_equivalence_class()
{  
  // Preconditions:
    
  // Body:

  // nothing to do.
  
  // Postconditions:

  // Exit:

  return; 
}

sheaf::index_equivalence_class&
sheaf::index_equivalence_class::
operator=(const index_equivalence_class& xother)
{
  // Preconditions:

  // Body:

  size_type lct = xother._equivalence_lists.ct();

  _equivalence_lists.reserve(xother._equivalence_lists.ub());
  _equivalence_lists.set_ct(lct);

  for(pod_type i = 0; i < lct; i++)
  {
    list_type& lother_list = xother._equivalence_lists[i];

    list_type::const_iterator litr;
    for(litr = lother_list.begin(); litr != lother_list.end(); ++litr)
    {
      _equivalence_lists[i].push_back(*litr);
    }
  }

  // Postconditions:

  // Exit:

  return *this;
}

const sheaf::index_equivalence_class::list_type&
sheaf::index_equivalence_class::
equivalence_list(pod_index_type xrep_id) const
{
  // Preconditions:

  require(contains_rep_id(xrep_id));

  // Body:

  const list_type& result = _equivalence_lists[xrep_id];

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::index_equivalence_class::list_type&
sheaf::index_equivalence_class::
equivalence_list(const scoped_index& xrep_id) const
{
  // Preconditions:

  require(contains_rep_id(xrep_id));

  // Body:

  return equivalence_list(xrep_id.hub_pod());
}

sheaf::size_type
sheaf::index_equivalence_class::
equivalence_ct(pod_index_type xrep_id) const
{
  // Preconditions:

  require(contains_rep_id(xrep_id));

  // Body:

  size_type result = _equivalence_lists[xrep_id].size();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_equivalence_class::
equivalence_ct(const scoped_index& xrep_id) const
{
  // Preconditions:

  require(contains_rep_id(xrep_id));

  // Body:

  return equivalence_ct(xrep_id.hub_pod());
}

bool
sheaf::index_equivalence_class::
contains_rep_id(pod_index_type xrep_id) const
{
  // Preconditions:

  // Body:

  bool result = (xrep_id >= 0) && (xrep_id < _equivalence_lists.ct());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_equivalence_class::
contains_rep_id(const scoped_index& xrep_id) const
{
  // Preconditions:

  // Body:

  return contains_rep_id(xrep_id.hub_pod());
}

bool
sheaf::index_equivalence_class::
id_space_less_than(const member_type& xitem1, const member_type& xitem2)
{
  // Preconditions:

  // Body:

  bool result = (xitem1.first < xitem2.first);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
