
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
/// Implementation for class ragged_array_index_space_interval

#include "SheafSystem/abstract_product_structure.h"
#include "SheafSystem/ragged_array_index_space_interval.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/ragged_array_implicit_index_space_iterator.h"
#include "SheafSystem/forwarding_index_space_handle.h"
#include "SheafSystem/explicit_index_space_state.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/index_space_family.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::ragged_array_index_space_interval&
sheaf::ragged_array_index_space_interval::
new_space(index_space_family& xid_spaces,
	  size_type xub,
	  ragged_array<pod_type>& xhub_ids,
	  bool xowns_hub_ids)
{
  // Preconditions:

  require(xub > 0);
  require(xhub_ids.row_ct() >= xub);

  // Body:

  define_old_variable(size_type old_id_spaces_end = xid_spaces.end());

  ragged_array_index_space_interval* result_ptr = new ragged_array_index_space_interval();
  result_ptr->new_state(xid_spaces, xub);

  result_ptr->_owns_hub_ids = xowns_hub_ids;

  if(xowns_hub_ids)
  {
    // Use the assignment operator of block to copy the contents of the
    // user input into the hub ids array.

    result_ptr->_hub_ids = new ragged_array<pod_type>();

    *(result_ptr->_hub_ids) = xhub_ids;
  }
  else
  {
    // The user is responsible for the memory management, copy the point
    // to the user input.

    result_ptr->_hub_ids = &xhub_ids;
  }

  const ragged_array_index_space_interval& result = *result_ptr;

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(result.begin() == old_id_spaces_end);
  ensure(result.end() == xid_spaces.end());
  ensure(result.end() == result.begin() + xub);

  ensure(result.hub_ids() == xhub_ids);
  ensure(result.owns_hub_ids() == xowns_hub_ids);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RAGGED_ARRAY_INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::ragged_array_index_space_interval::
~ragged_array_index_space_interval()
{  
  // Preconditions:
    
  // Body:

  if(_owns_hub_ids)
  {
    delete _hub_ids;
  }
  
  // Postconditions:

  // Exit:

  return; 
}

const sheaf::ragged_array<sheaf::ragged_array_index_space_interval::pod_type>&
sheaf::ragged_array_index_space_interval::
hub_ids() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_hub_ids;
}

bool
sheaf::ragged_array_index_space_interval::
owns_hub_ids() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _owns_hub_ids;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::ragged_array_index_space_interval::
ragged_array_index_space_interval()
  : index_space_interval()
{
  // Preconditions:
    
  // Body:

  _owns_hub_ids = false;
  _hub_ids = 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::ragged_array_index_space_interval::
class_name() const
{
  static const std::string result("ragged_array_index_space_interval");
  return result;
}

sheaf::ragged_array_index_space_interval*
sheaf::ragged_array_index_space_interval::
clone() const
{
  // Preconditions:

  // Body:

  ragged_array_index_space_interval* result =
    new ragged_array_index_space_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::ragged_array_index_space_interval::
make_prototype()
{
  // Preconditions:

  // Body:

  ragged_array_index_space_interval* lproto = new ragged_array_index_space_interval();

  id_space_interval_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::ragged_array_index_space_interval::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ragged_array_index_space_interval& lother =
    dynamic_cast<const ragged_array_index_space_interval&>(xother);

  bool result = index_space_interval::operator==(xother);

  result = result && (_owns_hub_ids == _owns_hub_ids);
  result = result && (_owns_hub_ids ? (*_hub_ids == *lother._hub_ids) : (_hub_ids == lother._hub_ids));

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::ragged_array_index_space_interval::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::ragged_array_index_space_interval&
sheaf::ragged_array_index_space_interval::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ragged_array_index_space_interval& lother =
    dynamic_cast<const ragged_array_index_space_interval&>(xother);

  _owns_hub_ids = lother._owns_hub_ids;

  if(_owns_hub_ids)
  {
    _hub_ids = new ragged_array<pod_type>();
    *_hub_ids = *lother._hub_ids;
  }
  else
  {
    _hub_ids = lother._hub_ids;
  }

  index_space_interval::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
sheaf::ragged_array_index_space_interval::
explicit_state(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  /// @todo Check to see if there is an override.

  explicit_index_space_state* result = 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::ragged_array_index_space_interval::
remove(pod_type xlocal_id)
{
  // Preconditions:

  // Body:

  /// @todo Remove or implement.

  not_implemented();
  
  // Postconditions:

  ensure(!contains(xlocal_id));

  // Exit:

  return;
}

sheaf::size_type
sheaf::ragged_array_index_space_interval::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = _hub_ids->col_ct(xlocal_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::ragged_array_index_space_interval::
begin(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 0;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::ragged_array_index_space_interval::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = _hub_ids->col_ct(xlocal_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::ragged_array_index_space_interval::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (0 <= xid) && (xid < _hub_ids->col_ct(xlocal_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::ragged_array_index_space_interval::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false;

  /// @issue Using a linear search to minimize storage.  For ids per space,
  /// of 4 and under a linear search is as efficient as hashing.  For 8 ids
  /// per space it is probably slightly slower.  However, no extra storage
  /// is needed for the linear search.  This function is probably not used
  /// enough by the user to justify the extra storage.  If we find hashing
  /// necessary, we should use lazy instantiation to create maps from
  /// hub ids per id space.

  pod_type lct = _hub_ids->col_ct(xlocal_id);
  pod_type* lids = _hub_ids->row(xlocal_id);

  for(pod_type i = 0; i < lct; ++i)
  {
    if(lids[i] == xid)
    {
      result = true;
      break;
    }
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::ragged_array_index_space_interval::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result =
    (0 <= xid) && (xid < _hub_ids->col_ct(xlocal_id)) &&
    ((*_hub_ids)[xlocal_id][xid] == xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::ragged_array_index_space_interval::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = invalid_pod_index();

  /// @issue Using a linear search to minimize storage.  For _ids_per_space,
  /// of 4 and under a linear search is as efficient as hashing.  For 8 ids
  /// per space it is probably slightly slower.  However, no extra storage
  /// is needed for the linear search.  This function is probably not used
  /// enough by the user to justify the extra storage.  If we find hashing
  /// necessary, we should use lazy instantiation to create maps from
  /// hub ids per id space.

  pod_type lct = _hub_ids->col_ct(xlocal_id);
  pod_type* lids = _hub_ids->row(xlocal_id);

  for(pod_type i = 0; i < lct; ++i)
  {
    if(lids[i] == xid)
    {
      result = i;
      break;
    }
  }

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::ragged_array_index_space_interval::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result =
    ((0 <= xid) && (xid < _hub_ids->col_ct(xlocal_id))) ?
    (*_hub_ids)[xlocal_id][xid] :
    invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
sheaf::ragged_array_index_space_interval::
is_persistent(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = false;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::ragged_array_index_space_interval::
new_product_structure(pod_type xlocal_id,
		      const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  /// @todo Implement.

  not_implemented();

  // Postconditions:

  ensure(has_product_structure(xlocal_id));

  // Exit:

  return;
}

void
sheaf::ragged_array_index_space_interval::
delete_product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  /// @todo Implement.

  not_implemented();
  
  // Postconditions:

  ensure(!has_product_structure(xlocal_id));

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::ragged_array_index_space_interval::
product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  /// @todo Implement.

  const abstract_product_structure* result = 0; // Just to silence compiler warnings.

  not_implemented();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

sheaf::abstract_product_structure&
sheaf::ragged_array_index_space_interval::
product_structure(pod_type xlocal_id)
{
  // Preconditions:

  require(contains(xlocal_id));
  require(has_product_structure(xlocal_id));

  // Body:

  /// @todo Implement.

  abstract_product_structure* result = 0; // Just to silence compiler warnings.

  not_implemented();
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

bool
sheaf::ragged_array_index_space_interval::
has_product_structure(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  /// @todo Implement.

  bool result = false; // Just to silence compiler warnings.

  not_implemented();
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_handle&
sheaf::ragged_array_index_space_interval::
get_id_space(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_handle& result = _handles.get();
  result.attach_to(*this, xlocal_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::ragged_array_index_space_interval::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  _handles.release(reinterpret_cast<forwarding_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::ragged_array_index_space_interval::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const forwarding_index_space_handle* lid_space =
    dynamic_cast<const forwarding_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && _handles.allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator&
sheaf::ragged_array_index_space_interval::
get_id_space_iterator(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  index_space_iterator& result = _iterators.get();
  result.attach_to(*this, xlocal_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::ragged_array_index_space_interval::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  _iterators.release(reinterpret_cast<ragged_array_implicit_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::ragged_array_index_space_interval::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const ragged_array_implicit_index_space_iterator* litr =
    dynamic_cast<const ragged_array_implicit_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && _iterators.allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::ragged_array_index_space_interval::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const ragged_array_index_space_interval*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::ragged_array_index_space_interval::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_interval::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
size_t
sheaf::
deep_size(const ragged_array_index_space_interval& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add contributions from _hub_ids.

  // Add contributions from _hub_ids.

  /// @hack The hub ids should only be added if the interval owns the data.
  /// Since this class is only used by zone_nodes_block_crg_interval we
  /// add the contributions of the hub id array here so we do not have to
  /// specialize deep_size functions for crg_interval.

//   if(xn.owns_hub_ids())
//   {
//     result += deep_size(xn.hub_ids(), false);
//   }

  result += deep_size(xn.hub_ids(), false);
  
  // Add contributions for _handles.

  result += deep_size(xn._handles, false);
  
  // Add contributions for _iterators.

  result += deep_size(xn._iterators, false);
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
