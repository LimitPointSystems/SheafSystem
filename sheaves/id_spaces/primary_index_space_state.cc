// $RCSfile: primary_index_space_state.cc,v $ $Revision: 1.3 $ $Date: 2013/03/13 00:59:02 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class primary_index_space_state

#include "primary_index_space_state.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "deep_size.h"
#include "hub_index_space_handle.h"
#include "primary_index_space_handle.h"
#include "primary_index_space_iterator.h"

// ===========================================================
// PRIMARY_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
sheaf::primary_index_space_state::
make_arg_list(pod_type xoffset, size_type xct)
{
  // Preconditions:

  // Body:

  arg_list result;
  result << "offset" << xoffset;
  result << "ct" << xct;

  // Postconditions:

  ensure(result.contains_arg("offset"));
  ensure(result.value("offset") == xoffset);
  ensure(result.contains_arg("ct"));
  ensure(result.value("ct") == xct);

  // Exit:

  return result;
} 

// PROTECTED MEMBER FUNCTIONS

sheaf::primary_index_space_state::
primary_index_space_state()
  : explicit_index_space_state(),
    _hub_term_id(invalid_pod_index()),
    _offset(0)
{
  // Preconditions:
    
  // Body:
  
  _ct = 0;
  _begin = 0;
  _end = 0;

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  ensure(offset() == 0);
  ensure(begin() == 0);
  ensure(end() == 0);

  // Exit:

  return; 
}

sheaf::primary_index_space_state::
primary_index_space_state(const arg_list& xargs)
  : explicit_index_space_state(xargs),
    _hub_term_id(invalid_pod_index())
{
  // Preconditions:
    
  require(precondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));
  require(xargs.contains_arg("offset"));
  require(xargs.contains_arg("ct"));

  // Body:
  
  _offset = xargs.value("offset");
  _ct     = xargs.value("ct");
  _begin  = 0;
  _end    = _ct;

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));
  ensure(offset() == (pod_type) xargs.value("offset"));
  ensure(ct() == (size_type) xargs.value("ct"));

  // Exit:

  return; 
}

sheaf::primary_index_space_state::
~primary_index_space_state()
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
// PRIMARY INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primary_index_space_state::pod_type
sheaf::primary_index_space_state::
offset() const
{
  // Preconditions:

  // Body:

  pod_type result = _offset;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::primary_index_space_state::
extend(size_type xct)
{
  // Preconditions:

  require(xct > ct());
  require(hub_id_space().interval_is_available(end(), end() - ct() + xct));

  // Body:

  _ct = xct;
  _end = _ct;

  // Postconditions:

  ensure(invariant());
  ensure(ct() == xct);

  // Exit:

  return;
}

sheaf::primary_index_space_state::pod_type
sheaf::primary_index_space_state::
hub_term_id() const
{
  // Preconditions:

  // Body:

  pod_type result = _hub_term_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::primary_index_space_state::
put_hub_term_id(pod_type xhub_term_id)
{
  // Preconditions:

  // Body:

  _hub_term_id = xhub_term_id;

  // Postconditions:

  ensure(hub_term_id() == xhub_term_id);

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::primary_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const primary_index_space_state& lother =
    dynamic_cast<const primary_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);

  result = result && (_offset == lother._offset);
  result = result && (_hub_term_id == lother._hub_term_id);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::primary_index_space_state::
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

sheaf::primary_index_space_state&
sheaf::primary_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const primary_index_space_state& lother =
    dynamic_cast<const primary_index_space_state&>(xother);

  _offset = lother._offset;
  _hub_term_id = lother._hub_term_id;

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
sheaf::primary_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = (0 <= xid) && (xid < _end);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
sheaf::primary_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = (_offset <= xhub_id) && (xhub_id < _offset + _end);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::primary_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result =
    contains_hub(xhub_id) ? xhub_id - _offset : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::primary_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = contains(xid) ? xid + _offset : invalid_pod_index();

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
sheaf::primary_index_space_state::
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
sheaf::primary_index_space_state::
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
sheaf::primary_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  primary_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::primary_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<primary_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::primary_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const primary_index_space_handle* lid_space =
    dynamic_cast<const primary_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::primary_index_space_handle>&
sheaf::primary_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<primary_index_space_handle> result;

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
sheaf::primary_index_space_state::
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
sheaf::primary_index_space_state::
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
sheaf::primary_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  primary_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::primary_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<primary_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::primary_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const primary_index_space_iterator* litr =
    dynamic_cast<const primary_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::primary_index_space_iterator>&
sheaf::primary_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<primary_index_space_iterator> result;

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
sheaf::primary_index_space_state::
class_name() const
{
  static const string result("primary_index_space_state");
  return result;
}

sheaf::primary_index_space_state*
sheaf::primary_index_space_state::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  primary_index_space_state* result = new primary_index_space_state(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::primary_index_space_state::
_has_prototype = make_prototype();

bool
sheaf::primary_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  primary_index_space_state* lproto = new primary_index_space_state();

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
sheaf::primary_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const primary_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::primary_index_space_state::
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
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
size_t
sheaf::
deep_size(const primary_index_space_state& xn, bool xinclude_shallow)
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
