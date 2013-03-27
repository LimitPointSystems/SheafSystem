// $RCSfile: i_connectivity_index_space_interval.cc,v $ $Revision: 1.3 $ $Date: 2013/03/13 00:58:48 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class i_connectivity_index_space_interval

#include "i_connectivity_index_space_interval.h"

#include "abstract_product_structure.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "i_connectivity_implicit_index_space_iterator.h"
#include "forwarding_index_space_handle.h"
#include "explicit_index_space_state.h"
#include "hub_index_space_handle.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// I_CONNECTIVITY_INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::i_connectivity_index_space_interval::
make_arg_list(pod_type xvertex_hub_begin)
{
  // Preconditions:

  require(xvertex_hub_begin >= 0);

  // Body:

  arg_list result = index_space_interval::make_arg_list();
  result << "vertex_hub_begin" << xvertex_hub_begin;

  // Postconditions

  ensure(result.contains_arg("vertex_hub_begin"));
  ensure(result.value("vertex_hub_begin") == xvertex_hub_begin);

  // Exit:

  return result;
}

fiber_bundle::i_connectivity_index_space_interval::
~i_connectivity_index_space_interval()
{  
  // Preconditions:
    
  // Body:

  // Nothing to do.
  
  // Postconditions:

  // Exit:

  return; 
}

fiber_bundle::i_connectivity_index_space_interval::pod_type
fiber_bundle::i_connectivity_index_space_interval::
vertex_hub_begin() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _vertex_hub_begin;
}

fiber_bundle::i_connectivity_index_space_interval::pod_type
fiber_bundle::i_connectivity_index_space_interval::
vertex_hub_begin(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  pod_type result = xlocal_id + _vertex_hub_begin;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::i_connectivity_index_space_interval::
i_connectivity_index_space_interval()
  : index_space_interval()
{
  // Preconditions:
    
  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

fiber_bundle::i_connectivity_index_space_interval::
i_connectivity_index_space_interval(const arg_list& xargs)
  : index_space_interval(xargs)
{
  // Preconditions:

  require(precondition_of(index_space_interval::index_space_interval(xargs)));

  // Body:

  _vertex_hub_begin = xargs.value("vertex_hub_begin");
  
  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(index_space_interval::index_space_interval(xargs)));
  ensure(vertex_hub_begin() == xargs.value("vertex_hub_begin"));

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
fiber_bundle::i_connectivity_index_space_interval::
class_name() const
{
  static const string result("i_connectivity_index_space_interval");
  return result;
}

fiber_bundle::i_connectivity_index_space_interval*
fiber_bundle::i_connectivity_index_space_interval::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  i_connectivity_index_space_interval* result =
    new i_connectivity_index_space_interval(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::i_connectivity_index_space_interval::
_has_prototype = make_prototype();

bool
fiber_bundle::i_connectivity_index_space_interval::
make_prototype()
{
  // Preconditions:

  // Body:

  i_connectivity_index_space_interval* lproto = new i_connectivity_index_space_interval();

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
fiber_bundle::i_connectivity_index_space_interval::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const i_connectivity_index_space_interval& lother =
    dynamic_cast<const i_connectivity_index_space_interval&>(xother);

  bool result = index_space_interval::operator==(xother);

  result = result && (_vertex_hub_begin == lother._vertex_hub_begin);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fiber_bundle::i_connectivity_index_space_interval::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = fiber_bundle::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::i_connectivity_index_space_interval&
fiber_bundle::i_connectivity_index_space_interval::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const i_connectivity_index_space_interval& lother =
    dynamic_cast<const i_connectivity_index_space_interval&>(xother);

  _vertex_hub_begin = lother._vertex_hub_begin;

  index_space_interval::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::explicit_index_space_state*
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
ct(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  size_type result = 2;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
end(pod_type xlocal_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = 2;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::i_connectivity_index_space_interval::
contains(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = (0 <= xid) && (xid < 2);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::i_connectivity_index_space_interval::
contains_unglued_hub(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type loffset = xid - vertex_hub_begin(xlocal_id);
  bool result = result = ((0 <= loffset) && (loffset < 2));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::i_connectivity_index_space_interval::
contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  bool result = is_valid(xhub_id) && (hub_pod(xlocal_id, xid) == xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::i_connectivity_index_space_interval::
pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result = xid - vertex_hub_begin(xlocal_id);

  if((result < 0) || (2 >= result))
  {
    // Not a valid pod.

    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains(xlocal_id, result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
fiber_bundle::i_connectivity_index_space_interval::
unglued_hub_pod(pod_type xlocal_id, pod_type xid) const
{
  // Preconditions:

  require(contains(xlocal_id));

  // Body:

  pod_type result =
    ((0 <= xid) && (xid < 2)) ?
    xid + vertex_hub_begin(xlocal_id) : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(xlocal_id, result));

  // Exit:

  return result;
}

bool
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::i_connectivity_index_space_interval::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_id_space_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  _iterators.release(reinterpret_cast<i_connectivity_implicit_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::i_connectivity_index_space_interval::
allocated_id_space_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const i_connectivity_implicit_index_space_iterator* litr =
    dynamic_cast<const i_connectivity_implicit_index_space_iterator*>(&xitr);

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
fiber_bundle::i_connectivity_index_space_interval::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const i_connectivity_index_space_interval*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::i_connectivity_index_space_interval::
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
fiber_bundle::
deep_size(const i_connectivity_index_space_interval& xn, bool xinclude_shallow)
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
