
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Implementation for class forwarding_index_space_handle

#include "abstract_product_structure.h"
#include "forwarding_index_space_handle.h"
#include "assert_contract.h"
#include "hub_index_space_handle.h"
#include "index_space_family.h"
#include "index_space_iterator.h"

// ===========================================================
// FORWARDING_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::forwarding_index_space_handle::
forwarding_index_space_handle()
  : _host(0),
    _local_id(invalid_pod_index())
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::forwarding_index_space_handle::
forwarding_index_space_handle(const forwarding_index_space_handle& xother)
  : _host(0),
    _local_id(invalid_pod_index())
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

sheaf::forwarding_index_space_handle::
forwarding_index_space_handle(const index_space_family& xid_spaces,
			      pod_type xindex)
{
  // Preconditions:

  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  attach_to(xid_spaces, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

sheaf::forwarding_index_space_handle::
forwarding_index_space_handle(const index_space_family& xid_spaces,
			      const std::string& xname)
{
  // Preconditions:

  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xname);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

sheaf::forwarding_index_space_handle&
sheaf::forwarding_index_space_handle::
operator=(const forwarding_index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  attach_to(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::forwarding_index_space_handle::
~forwarding_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::forwarding_index_space_handle&
sheaf::forwarding_index_space_handle::
operator=(const index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  attach_to(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::forwarding_index_space_handle*
sheaf::forwarding_index_space_handle::
clone() const
{
  forwarding_index_space_handle* result;
  
  // Preconditions:

  // Body:
  
  result = new forwarding_index_space_handle(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::forwarding_index_space_handle::
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
sheaf::forwarding_index_space_handle::
id_spaces()
{
  // Preconditions:

  require(is_attached());

  // Body:

  /// @hack The host should be const but a mutable interface for
  /// the family is required by put_name().  Do a const cast for now
  /// and review in the future.

  index_space_family& result =
    const_cast<index_space_collection*>(_host)->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::forwarding_index_space_handle::
ct() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  size_type result = _host->ct(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::forwarding_index_space_handle::
begin() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->begin(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::forwarding_index_space_handle::
end() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->end(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
contains(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _host->contains(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
contains_unglued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _host->contains_unglued_hub(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
contains_glued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _host->contains_glued_hub(_local_id, xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _host->contains(_local_id, xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::forwarding_index_space_handle::
pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->pod(_local_id, xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::forwarding_index_space_handle::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->unglued_hub_pod(_local_id, xid);

  // Postconditions:

  ensure(is_valid(result) || hub_id_space().contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::forwarding_index_space_handle::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->glued_hub_pod(_local_id, xid);

  // Postconditions:

  ensure(is_valid(result) || hub_id_space().contains(result));

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
is_persistent() const
{
  // Preconditions:

  require(is_attached());

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
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::forwarding_index_space_handle::
new_product_structure(const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(is_attached());

  // Body:

  /// @issue _host needs to const because the attach_to interface
  ///        passes a const host.  This is only necessary because
  ///        the attach_to interface is public.  The interval classes
  ///        want to use this interface and we don't want to make
  ///        every interval a friend.  The interval calls it from
  ///        get_id_space which is const.

  const_cast<index_space_collection*>(_host)->
    new_product_structure(_local_id, xproduct);

  // Postconditions:

  ensure(has_product_structure());

  // Exit:

  return;
}

void
sheaf::forwarding_index_space_handle::
delete_product_structure()
{
  // Preconditions:

  require(is_attached());

  // Body:

  const_cast<index_space_collection*>(_host)->
    delete_product_structure(_local_id);
  
  // Postconditions:

  ensure(!has_product_structure());

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::forwarding_index_space_handle::
product_structure() const
{
  // Preconditions:

  require(is_attached());
  require(has_product_structure());

  // Body:

  const abstract_product_structure& result = _host->product_structure(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::forwarding_index_space_handle::
product_structure()
{
  // Preconditions:

  require(is_attached());
  require(has_product_structure());

  // Body:

  abstract_product_structure& result =
    const_cast<index_space_collection*>(_host)->product_structure(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
has_product_structure() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _host->has_product_structure(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_collection&
sheaf::forwarding_index_space_handle::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_collection& result = *_host;

  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::forwarding_index_space_handle::
index() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->family_scope(_local_id);

  // Postconditions:

  ensure(id_spaces().contains(result));

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
is_attached() const
{
  // Preconditions:

  // Body:

  bool result = is_valid(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::forwarding_index_space_handle::
attach_to(pod_type xindex)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));
  require(conforms_to_state(xindex));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  _host = id_spaces().collection(xindex);
  _local_id = _host->local_scope(xindex);
  
  // Postconditions:

  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::forwarding_index_space_handle::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  _host = &xhost;
  _local_id = xlocal_id;
  
  // Postconditions:

  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

void
sheaf::forwarding_index_space_handle::
detach()
{
  // Preconditions:

  // Body:

  _local_id = invalid_pod_index();

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

bool
sheaf::forwarding_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result = true; // The precondition guarantees this to be true.
  
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
sheaf::forwarding_index_space_handle::
get_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_handle& result = _host->get_id_space(_local_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::forwarding_index_space_handle::
release_id_space() const
{
  // Preconditions:

  require(is_attached());
  require(allocated_id_space());

  // Body:

  _host->release_id_space(const_cast<forwarding_index_space_handle&>(*this));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::forwarding_index_space_handle::
allocated_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = _host->allocated_id_space(*this);

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
sheaf::forwarding_index_space_handle::
get_iterator() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_iterator& result = _host->get_id_space_iterator(_local_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::forwarding_index_space_handle::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());
  require(allocated_iterator(xitr));

  // Body:

  _host->release_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::forwarding_index_space_handle::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());

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
sheaf::forwarding_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const forwarding_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::forwarding_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_handle::invariant());

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


