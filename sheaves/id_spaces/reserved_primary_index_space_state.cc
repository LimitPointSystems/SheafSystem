
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
/// Implementation for class reserved_primary_index_space_state

#include "SheafSystem/reserved_primary_index_space_state.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/deep_size.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/reserved_primary_index_space_handle.h"
#include "SheafSystem/reserved_primary_index_space_iterator.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_handle
sheaf::reserved_primary_index_space_state::
new_space(index_space_family& xid_spaces,
	  const std::string& xname,
	  pod_type xoffset,
	  size_type xct)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));
  require(xoffset >= 0);
  require(xct > 0);

  // Body:

  reserved_primary_index_space_state* lstate = new reserved_primary_index_space_state();
  lstate->new_state(xid_spaces, xname, false);

  lstate->_offset = xoffset;
  lstate->_ct = xct;
  lstate->_begin = 0;
  lstate->_end = xct;

  lstate->_next_hub_id = xoffset;

  reserved_primary_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  ensure(result.offset() == xoffset);
  ensure(result.ct() == xct);
  ensure(result.next_hub_id() == xoffset);

  // Exit:

  return result;
}

sheaf::reserved_primary_index_space_handle
sheaf::reserved_primary_index_space_state::
new_space(index_space_family& xid_spaces,
	  pod_index_type xid,
	  const std::string& xname,
	  pod_type xoffset,
	  size_type xct)
{
  // Preconditions:

  require(!xid_spaces.contains(xid));
  require(xid_spaces.is_explicit_interval(xid));
  require(!xname.empty());
  require(!xid_spaces.contains(xname));
  require(xoffset >= 0);
  require(xct > 0);

  // Body:

  reserved_primary_index_space_state* lstate = new reserved_primary_index_space_state();
  lstate->new_state(xid_spaces, xid, xname, false);

  lstate->_offset = xoffset;
  lstate->_ct = xct;
  lstate->_begin = 0;
  lstate->_end = xct;

  lstate->_next_hub_id = xoffset;

  reserved_primary_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.index() == xid);
  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  ensure(result.offset() == xoffset);
  ensure(result.ct() == xct);
  ensure(result.next_hub_id() == xoffset);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RESERVED_PRIMARY_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_state::
reserved_primary_index_space_state()
  : primary_index_space_state()
{
  // Preconditions:
    
  // Body:

  _next_hub_id = invalid_pod_index();

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  ensure(!is_valid(next_hub_id()));

  // Exit:

  return; 
}

sheaf::reserved_primary_index_space_state::
~reserved_primary_index_space_state()
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
// OFFSET INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_state::pod_type
sheaf::reserved_primary_index_space_state::
new_id()
{
  // Preconditions:

  require(is_next_id_available());

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_next_hub_id = next_hub_id());

  pod_type result = _next_hub_id;

  new_hub_id(_next_hub_id);

  // Postconditions:

  ensure(invariant());
  ensure(next_hub_id() == old_next_hub_id + 1);

  // Exit:

  return result;
}

sheaf::reserved_primary_index_space_state::pod_type
sheaf::reserved_primary_index_space_state::
new_hub_id(pod_type xhub_id)
{
  // Preconditions:

  require(is_hub_id_available(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_next_hub_id = next_hub_id());

  if(_next_hub_id <= xhub_id)
  {
    _next_hub_id = xhub_id+1;
  }

  // Postconditions:

  ensure(invariant());
  ensure(next_hub_id() >= old_next_hub_id);

  // Exit:

  return xhub_id;
}

sheaf::reserved_primary_index_space_state::pod_type
sheaf::reserved_primary_index_space_state::
next_hub_id() const
{
  // Preconditions:

  // Body:

  pod_type result = _next_hub_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_state::
is_next_id_available() const
{
  // Preconditions:

  // Body:

  bool result = (_next_hub_id < (_offset + _end));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_state::
is_hub_id_available(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result =
    (xhub_id >= _offset) && (xhub_id < (_offset + _end)) && !hub_id_space().contains(xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRIMARY INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::reserved_primary_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const reserved_primary_index_space_state& lother =
    dynamic_cast<const reserved_primary_index_space_state&>(xother);

  bool result = primary_index_space_state::operator==(xother);
  result = result && (_next_hub_id == lother._next_hub_id);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::reserved_primary_index_space_state::
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

sheaf::reserved_primary_index_space_state&
sheaf::reserved_primary_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const reserved_primary_index_space_state& lother =
    dynamic_cast<const reserved_primary_index_space_state&>(xother);

  _next_hub_id = lother._next_hub_id;

  (void) primary_index_space_state::operator=(xother);

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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::reserved_primary_index_space_state::
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
sheaf::reserved_primary_index_space_state::
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
sheaf::reserved_primary_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  reserved_primary_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::reserved_primary_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<reserved_primary_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::reserved_primary_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const reserved_primary_index_space_handle* lid_space =
    dynamic_cast<const reserved_primary_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::reserved_primary_index_space_handle>&
sheaf::reserved_primary_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<reserved_primary_index_space_handle> result;

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
sheaf::reserved_primary_index_space_state::
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
sheaf::reserved_primary_index_space_state::
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
sheaf::reserved_primary_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  reserved_primary_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::reserved_primary_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<reserved_primary_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::reserved_primary_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const reserved_primary_index_space_iterator* litr =
    dynamic_cast<const reserved_primary_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::reserved_primary_index_space_iterator>&
sheaf::reserved_primary_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<reserved_primary_index_space_iterator> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::reserved_primary_index_space_state::
class_name() const
{
  static const std::string result("reserved_primary_index_space_state");
  return result;
}

sheaf::reserved_primary_index_space_state*
sheaf::reserved_primary_index_space_state::
clone() const
{
  // Preconditions:

  // Body:

  reserved_primary_index_space_state* result = new reserved_primary_index_space_state();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::reserved_primary_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  reserved_primary_index_space_state* lproto = new reserved_primary_index_space_state();

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
sheaf::reserved_primary_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const reserved_primary_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(primary_index_space_state::invariant());

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
deep_size(const reserved_primary_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const primary_index_space_state& ixn = static_cast<const primary_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
