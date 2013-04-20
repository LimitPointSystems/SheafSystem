

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class singleton_index_space_state

#include "singleton_index_space_state.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "deep_size.h"
#include "hub_index_space_handle.h"
#include "singleton_index_space_handle.h"
#include "singleton_index_space_iterator.h"

// ===========================================================
// SINGLETON_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
sheaf::singleton_index_space_state::
make_arg_list(pod_type xhub_id)
{
  // Preconditions:

  // Body:

  arg_list result;
  result << "hub_id" << xhub_id;

  // Postconditions:

  ensure(result.contains_arg("hub_id"));
  ensure(result.value("hub_id") == xhub_id);

  // Exit:

  return result;
} 

// PROTECTED MEMBER FUNCTIONS

sheaf::singleton_index_space_state::
singleton_index_space_state()
  : explicit_index_space_state(),
    _hub_id(invalid_pod_index())
{
  // Preconditions:
    
  // Body:

  _ct = 0;
  _begin = 0;
  _end = 0;

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  ensure(!is_valid(hub_id()));
  ensure(ct() == 0);
  ensure(begin() == 0);
  ensure(end() == 0);

  // Exit:

  return; 
}

sheaf::singleton_index_space_state::
singleton_index_space_state(const arg_list& xargs)
  : explicit_index_space_state(xargs)
{
  // Preconditions:
    
  require(precondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));
  require(xargs.contains_arg("hub_id"));

  // Body:
  
  _hub_id = xargs.value("hub_id");
  _ct     = 1;
  _begin  = 0;
  _end    = 1;

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));
  ensure(hub_id() == (pod_type) xargs.value("hub_id"));

  // Exit:

  return; 
}

sheaf::singleton_index_space_state::
~singleton_index_space_state()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SINGLETON INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::singleton_index_space_state::pod_type
sheaf::singleton_index_space_state::
hub_id() const
{
  // Preconditions:

  // Body:

  pod_type result = _hub_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::singleton_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const singleton_index_space_state& lother =
    dynamic_cast<const singleton_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);
  result = result && (_hub_id == lother._hub_id);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::singleton_index_space_state::
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

sheaf::singleton_index_space_state&
sheaf::singleton_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const singleton_index_space_state& lother =
    dynamic_cast<const singleton_index_space_state&>(xother);

  _hub_id = lother._hub_id;

  (void) explicit_index_space_state::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::singleton_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = (xid == 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::singleton_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = (xhub_id == _hub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::singleton_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result =
    contains_hub(xhub_id) ? 0 : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::singleton_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = contains(xid) ? _hub_id : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::singleton_index_space_state::
handle_pool_ct()
{
  // Preconditions:

  // Body:

  size_type result = handles().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::singleton_index_space_state::
handle_pool_deep_size()
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(handles(), true);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::index_space_handle&
sheaf::singleton_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  singleton_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::singleton_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<singleton_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::singleton_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const singleton_index_space_handle* lid_space =
    dynamic_cast<const singleton_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::singleton_index_space_handle>&
sheaf::singleton_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<singleton_index_space_handle> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::singleton_index_space_state::
iterator_pool_ct()
{
  // Preconditions:

  // Body:

  size_type result = iterators().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::singleton_index_space_state::
iterator_pool_deep_size()
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(iterators(), true);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
sheaf::singleton_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  singleton_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::singleton_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<singleton_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::singleton_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const singleton_index_space_iterator* litr =
    dynamic_cast<const singleton_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::singleton_index_space_iterator>&
sheaf::singleton_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<singleton_index_space_iterator> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
sheaf::singleton_index_space_state::
class_name() const
{
  static const string result("singleton_index_space_state");
  return result;
}

sheaf::singleton_index_space_state*
sheaf::singleton_index_space_state::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  singleton_index_space_state* result = new singleton_index_space_state(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::singleton_index_space_state::
_has_prototype = make_prototype();

bool
sheaf::singleton_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  singleton_index_space_state* lproto = new singleton_index_space_state();

  id_space_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::singleton_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const singleton_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(explicit_index_space_state::invariant());

    // Invariances for this class:

    invariance(is_gathered());
      
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
deep_size(const singleton_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const explicit_index_space_state& ixn = static_cast<const explicit_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}