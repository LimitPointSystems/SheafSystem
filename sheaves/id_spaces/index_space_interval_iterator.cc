// $RCSfile: index_space_interval_iterator.cc,v $ $Revision: 1.3 $ $Date: 2013/03/13 00:59:02 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class index_space_interval_iterator

#include "index_space_interval_iterator.h"
#include "assert_contract.h"
#include "hub_index_space_handle.h"
#include "index_space_interval.h"
#include "index_space_family.h"
#include "index_space_iterator.h"

// ===========================================================
// INDEX_SPACE_INTERVAL_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_interval_iterator::
~index_space_interval_iterator()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

sheaf::index_space_interval_iterator&
sheaf::index_space_interval_iterator::
operator=(const index_space_interval_iterator& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  _host = xother._host;
  _only_persistent = xother._only_persistent;
  _ub = xother._ub;
  _local_id = xother._local_id;
  
  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

bool
sheaf::index_space_interval_iterator::
operator==(const index_space_interval_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = (_host == xother._host);
  result = result && (_only_persistent == xother._only_persistent);
  result = result && (_ub == xother._ub);
  result = result && (_local_id == xother._local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::index_space_interval_iterator*
sheaf::index_space_interval_iterator::
clone() const
{
  // Preconditions:

  // Body:
  
  index_space_interval_iterator* result =
    new index_space_interval_iterator(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result; 
}

const sheaf::index_space_interval&
sheaf::index_space_interval_iterator::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_interval& result = *_host;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
only_persistent() const
{
  // Preconditions:

  // Body:

  bool result = _only_persistent;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_interval_iterator::
ub() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  size_type result = _ub;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_interval_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_index = index());

  do
  {
    ++_local_id;
    if(_local_id == _ub)
    {
      // Done with the iteration, invalid index and exit.

      _local_id = invalid_pod_index();
      break;
    }
  }
  while(!_host->contains(_local_id) ||
	(_only_persistent && !_host->is_persistent(_local_id)));

  // Postconditions:

  ensure(invariant());
  ensure(is_done() || index() != old_index);

  // Exit:

  return;
}

bool
sheaf::index_space_interval_iterator::
is_done() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = !is_valid(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_interval_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _local_id = 0;

  while(!_host->contains(_local_id))
  {
    ++_local_id;
    if(_local_id == _ub)
    {
      // Done with the iteration, invalid index and exit.

      _local_id = invalid_pod_index();
      break;
    }
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::index_space_interval_iterator::pod_type
sheaf::index_space_interval_iterator::
index() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->family_scope(_local_id);

  // Postconditions:

  ensure(is_valid(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_interval_iterator::
index_space_interval_iterator(const index_space_interval_iterator& xother)
{
  // Preconditions:
    
  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return; 
}

sheaf::index_space_interval_iterator::
index_space_interval_iterator(bool xonly_persistent)
  : _host(0),
    _local_id(invalid_pod_index()),
    _only_persistent(xonly_persistent)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(only_persistent() == xonly_persistent);
  ensure(!is_attached());

  // Exit:

  return;
}

void
sheaf::index_space_interval_iterator::
attach_to(index_space_interval& xhost)
{
  // Preconditions:

  // Body:

  _host = &xhost;
  _ub = _host->end() - _host->begin();

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(ub() == (xhost.end() - xhost.begin()));

  // Exit:

  return;
}

void
sheaf::index_space_interval_iterator::
detach()
{
  // Preconditions:

  // Body:

  _host = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

bool
sheaf::index_space_interval_iterator::
is_attached() const
{
  // Preconditions:

  // Body:

  bool result = (_host != 0);

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

const sheaf::index_space_family&
sheaf::index_space_interval_iterator::
id_spaces() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_family& result = _host->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::index_space_interval_iterator::
id_spaces()
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_family& result = _host->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::index_space_interval_iterator::
hub_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const hub_index_space_handle& result = id_spaces().hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_interval_iterator::
ct() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  size_type result = _host->ct(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_interval_iterator::
begin() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->begin(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_interval_iterator::
end() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->end(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
contains(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->contains(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
contains_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->contains_hub(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
contains_unglued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->contains_unglued_hub(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
contains_glued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->contains_glued_hub(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->contains(_local_id, xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_interval_iterator::
pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->pod(_local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_interval_iterator::
hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->hub_pod(_local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_interval_iterator::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->unglued_hub_pod(_local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_interval_iterator::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = _host->glued_hub_pod(_local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(result));

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
is_persistent() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->is_persistent(_local_id);

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
sheaf::index_space_interval_iterator::
get_id_space() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  index_space_handle& result = _host->get_id_space(_local_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::index_space_interval_iterator::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());
  require(allocated_id_space(xid_space));

  // Body:

  _host->release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_interval_iterator::
allocated_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->allocated_id_space(xid_space);

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
sheaf::index_space_interval_iterator::
get_id_space_iterator() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  index_space_iterator& result = _host->get_id_space_iterator(_local_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::index_space_interval_iterator::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());
  require(allocated_id_space_iterator(xitr));

  // Body:

  _host->release_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_interval_iterator::
allocated_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  bool result = _host->allocated_id_space_iterator(xitr);

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
sheaf::index_space_interval_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_interval_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_space_interval_iterator::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(!is_attached() || is_done() || is_valid(index()));
      
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

