

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class singleton_index_space_interval

#include "abstract_product_structure.h"
#include "singleton_index_space_interval.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "singleton_implicit_index_space_iterator.h"
#include "forwarding_index_space_handle.h"
#include "explicit_index_space_state.h"
#include "hub_index_space_handle.h"

// ===========================================================
// SINGLETON_INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
sheaf::singleton_index_space_interval::
make_arg_list(pod_type xhub_offset)
{
  // Preconditions:

  require(xhub_offset >= 0);

  // Body:

  arg_list result = index_space_interval::make_arg_list();
  result << "hub_offset" << xhub_offset;

  // Postconditions

  ensure(result.contains_arg("hub_offset"));
  ensure(result.value("hub_offset") == xhub_offset);

  // Exit:

  return result;
}

sheaf::singleton_index_space_interval::
~singleton_index_space_interval()
{  
  // Preconditions:
    
  // Body:

  // Nothing to do.
  
  // Postconditions:

  // Exit:

  return; 
}

sheaf::singleton_index_space_interval::pod_type
sheaf::singleton_index_space_interval::
hub_offset() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _hub_offset;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::singleton_index_space_interval::
singleton_index_space_interval()
  : index_space_interval()
{
  // Preconditions:
    
  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::singleton_index_space_interval::
singleton_index_space_interval(const arg_list& xargs)
  : index_space_interval(xargs)
{
  // Preconditions:

  require(precondition_of(index_space_interval::index_space_interval(xargs)));

  // Body:

  _hub_offset = xargs.value("hub_offset");
  
  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(index_space_interval::index_space_interval(xargs)));
  ensure(hub_offset() == xargs.value("hub_offset"));

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

const string&
sheaf::singleton_index_space_interval::
class_name() const
{
  static const string result("singleton_index_space_interval");
  return result;
}

sheaf::singleton_index_space_interval*
sheaf::singleton_index_space_interval::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  singleton_index_space_interval* result =
    new singleton_index_space_interval(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::singleton_index_space_interval::
_has_prototype = make_prototype();

bool
sheaf::singleton_index_space_interval::
make_prototype()
{
  // Preconditions:

  // Body:

  singleton_index_space_interval* lproto = new singleton_index_space_interval();

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
sheaf::singleton_index_space_interval::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const singleton_index_space_interval& lother =
    dynamic_cast<const singleton_index_space_interval&>(xother);

  bool result = index_space_interval::operator==(xother);

  result = result && (_hub_offset == lother._hub_offset);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::singleton_index_space_interval::
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

sheaf::singleton_index_space_interval&
sheaf::singleton_index_space_interval::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const singleton_index_space_interval& lother =
    dynamic_cast<const singleton_index_space_interval&>(xother);

  _hub_offset = lother._hub_offset;

  index_space_interval::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = 1;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 1;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_interval::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (xid == 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_interval::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (xid == (_hub_offset + xlocal_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_interval::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result =
    (xid == 0) &&
    ((xlocal_id + _hub_offset) == xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::singleton_index_space_interval::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = contains_hub(xlocal_id, xid) ? 0 : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::singleton_index_space_interval::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result =
    (xid == 0) ? xlocal_id + _hub_offset : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
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
sheaf::singleton_index_space_interval::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  _iterators.release(reinterpret_cast<singleton_implicit_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::singleton_index_space_interval::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const singleton_implicit_index_space_iterator* litr =
    dynamic_cast<const singleton_implicit_index_space_iterator*>(&xitr);

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
sheaf::singleton_index_space_interval::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const singleton_index_space_interval*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_interval::
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
deep_size(const singleton_index_space_interval& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add contributions for _handles.

  result += deep_size(xn._handles, false);
  
  // Add contributions for _iterators.

  result += deep_size(xn._iterators, false);
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
