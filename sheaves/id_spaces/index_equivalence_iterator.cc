
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
/// Implementation for class index_equivalence_iterator

#include "index_equivalence_iterator.h"

#include "assert_contract.h"
#include "index_space_family.h"

// ===========================================================
// INDEX_EQUIVALENCE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_equivalence_iterator::
index_equivalence_iterator(const index_space_family& xid_spaces,
			   pod_index_type xrep_id,
			   bool xonly_persistent,
			   bool xsort_ids)
  : _equivalence_class(xid_spaces, xonly_persistent, xsort_ids)
{
  // Preconditions:

  require(is_valid(xrep_id) ? xid_spaces.hub_id_space().contains(xrep_id) : true);

  // Body:

  _id_spaces = &xid_spaces;
  _only_persistent = xonly_persistent;
  _is_sorted = xsort_ids;
  _rep_id = xrep_id;

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(&id_spaces() == &xid_spaces);
  ensure(rep_id() == xrep_id);
  ensure(only_persistent() == xonly_persistent);
  ensure(is_sorted() == xsort_ids);

  // Exit:

  return;
}

sheaf::index_equivalence_iterator::
index_equivalence_iterator(const index_space_family& xid_spaces,
			   const scoped_index& xrep_id,
			   bool xonly_persistent,
			   bool xsort_ids)
  : _equivalence_class(xid_spaces, xonly_persistent, xsort_ids)
{
  // Preconditions:

  require(xrep_id.is_valid() ? xid_spaces.hub_id_space().contains(xrep_id.hub_pod()) : true);

  // Body:

  _id_spaces = &xid_spaces;
  _only_persistent = xonly_persistent;
  _is_sorted = xsort_ids;
  _rep_id = xrep_id.hub_pod();

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(&id_spaces() == &xid_spaces);
  ensure(rep_id() == xrep_id.hub_pod());
  ensure(only_persistent() == xonly_persistent);
  ensure(is_sorted() == xsort_ids);

  // Exit:

  return;
}

sheaf::index_equivalence_iterator::
index_equivalence_iterator(const index_space_family& xid_spaces,
			   bool xonly_persistent,
			   bool xsort_ids)
  : _equivalence_class(xid_spaces, xonly_persistent, xsort_ids)
{
  // Preconditions:

  // Body:

  _id_spaces = &xid_spaces;
  _only_persistent = xonly_persistent;
  _is_sorted = xsort_ids;
  _rep_id = invalid_pod_index();

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(&id_spaces() == &xid_spaces);
  ensure(only_persistent() == xonly_persistent);
  ensure(is_sorted() == xsort_ids);

  // Exit:

  return;
}

sheaf::index_equivalence_iterator::
~index_equivalence_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

const sheaf::index_space_family&
sheaf::index_equivalence_iterator::
id_spaces() const
{
  return *_id_spaces;
}

sheaf::pod_index_type
sheaf::index_equivalence_iterator::
rep_id() const
{
  return _rep_id;
}

void
sheaf::index_equivalence_iterator::
rep_id(scoped_index& result) const
{
  result.put(_id_spaces->hub_id_space(), _rep_id);
}

bool
sheaf::index_equivalence_iterator::
only_persistent() const
{
  return _only_persistent;
}

bool
sheaf::index_equivalence_iterator::
is_sorted() const
{
  return _is_sorted;
}

void
sheaf::index_equivalence_iterator::
put_rep_id(pod_index_type xrep_id)
{
  // Preconditions:

  // Body:

  _rep_id = xrep_id;

  // Postconditions:

  ensure(invariant());
  ensure(rep_id() == xrep_id);

  // Exit:

  return;
}

void
sheaf::index_equivalence_iterator::
put_rep_id(const scoped_index& xrep_id)
{
  // Preconditions:

  require(xrep_id.is_valid() ? id_spaces().hub_id_space().contains(xrep_id.hub_pod()) : true);
  // Body:

  _rep_id = xrep_id.hub_pod();

  // Postconditions:

  ensure(invariant());
  ensure(rep_id() == xrep_id.hub_pod());

  // Exit:

  return;
}

const sheaf::index_equivalence_iterator::member_type&
sheaf::index_equivalence_iterator::
item() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const member_type& result = _item;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_equivalence_iterator::
is_done() const
{
  // Preconditions:

  // Body:

  bool result = _is_done;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_equivalence_iterator::
ct() const
{
  // Preconditions:

  // Body:

  size_type result =
    is_valid(_rep_id) ?
    _equivalence_class.equivalence_ct(_rep_id) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}   

void
sheaf::index_equivalence_iterator::
next()
{
  // Preconditions:

  require(!is_done());

  // Body:

  define_old_variable(pod_index_type old_space_index = item().first);

  // Increment the list iterator.

  _itr++;

  // Assign the item.

  if(_itr == _end)
  {
    _is_done = true;
  }
  else
  {
    _item = *_itr;
  }

  // Postconditions:

  ensure(invariant());
  //ensure(!is_done() ? item().first > old_space_index : true);
  // @error equivalence class not sorted by id space;
  // underlying hash map not ordered.
  ensure(!is_done() ? item().first != old_space_index : true);

  // Exit:

  return;
}

void
sheaf::index_equivalence_iterator::
reset()
{
  // Preconditions:

  // Body:

  _is_done = false;

  if(is_valid(_rep_id))
  {
    // Initialize the iterator to the beginning of the list and
    // initialize the end of the iterator.

    const index_equivalence_class::list_type& lequivalence_list =
      _equivalence_class.equivalence_list(_rep_id);

    _itr = lequivalence_list.begin();
    _end = lequivalence_list.end();

    // Assign the item.

    if(_itr == _end)
    {
      _is_done = true;
    }
    else
    {
      _item = *_itr;
    }
  }
  else
  {
    // The rep id is not valid, iteration is finished.

    _is_done = true;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::index_equivalence_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_equivalence_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::index_equivalence_iterator*
sheaf::index_equivalence_iterator::
clone() const
{
  index_equivalence_iterator* result;

  // Preconditions:

  // Body:

  result = new index_equivalence_iterator(*_id_spaces, _rep_id,
					  _only_persistent,
					  _is_sorted);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(&result->id_spaces() == &id_spaces());
  ensure(result->rep_id() == rep_id());
  ensure(result->only_persistent() == only_persistent());
  ensure(result->is_sorted() == is_sorted());

  // Exit:

  return result;
}

sheaf::index_equivalence_iterator&
sheaf::index_equivalence_iterator::
operator=(const index_equivalence_iterator& xother)
{
  // Preconditions:

  // Body:

  _id_spaces = xother._id_spaces;
  _rep_id = xother._rep_id;
  _only_persistent = xother._only_persistent;
  _is_sorted = xother._is_sorted;
  _equivalence_class = xother._equivalence_class;
  _itr = xother._itr;
  _end = xother._end;
  _item = xother._item;
  _is_done = xother._is_done;

  // Postconditions:

  ensure(invariant());
  
  // Exit:

  return *this;
}

bool
sheaf::index_equivalence_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(any::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    /// @hack section_space_schema_poset internal_id hack.  !rep_id().is_scoped
    /// should go away once the section_space_schema_poset has a scoped
    /// internal_id.

    invariance(is_valid(rep_id()) ? id_spaces().hub_id_space().contains(rep_id()) : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

