
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
/// Implementation for class offset_index_space_state

#include "SheafSystem/offset_index_space_state.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/deep_size.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/offset_index_space_handle.h"
#include "SheafSystem/offset_index_space_iterator.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::offset_index_space_handle
sheaf::offset_index_space_state::
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

  offset_index_space_state* lstate = new offset_index_space_state();
  lstate->new_state(xid_spaces, xname, false);

  lstate->_offset = xoffset;
  lstate->_ct = xct;
  lstate->_begin = 0;
  lstate->_end = xct;

  offset_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  ensure(result.offset() == xoffset);
  ensure(result.ct() == xct);
  ensure(result.is_gathered());

  // Exit:

  return result;
}

sheaf::offset_index_space_handle
sheaf::offset_index_space_state::
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

  offset_index_space_state* lstate = new offset_index_space_state();
  lstate->new_state(xid_spaces, xid, xname, false);

  lstate->_offset = xoffset;
  lstate->_ct = xct;
  lstate->_begin = 0;
  lstate->_end = xct;

  offset_index_space_handle result(*lstate);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.index() == xid);
  ensure(result.name() == xname);
  ensure(!result.is_persistent());

  ensure(result.offset() == xoffset);
  ensure(result.ct() == xct);
  ensure(result.is_gathered());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// OFFSET_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::offset_index_space_state::
offset_index_space_state()
  : explicit_index_space_state(),
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

sheaf::offset_index_space_state::
~offset_index_space_state()
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

sheaf::offset_index_space_state::pod_type
sheaf::offset_index_space_state::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::offset_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const offset_index_space_state& lother =
    dynamic_cast<const offset_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);
  result = result && (_offset == lother._offset);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::offset_index_space_state::
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

sheaf::offset_index_space_state&
sheaf::offset_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const offset_index_space_state& lother =
    dynamic_cast<const offset_index_space_state&>(xother);

  _offset = lother._offset;

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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  offset_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::offset_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<offset_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::offset_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const offset_index_space_handle* lid_space =
    dynamic_cast<const offset_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::offset_index_space_handle>&
sheaf::offset_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<offset_index_space_handle> result;

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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
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
sheaf::offset_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  offset_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::offset_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<offset_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::offset_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const offset_index_space_iterator* litr =
    dynamic_cast<const offset_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<sheaf::offset_index_space_iterator>&
sheaf::offset_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<offset_index_space_iterator> result;

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
sheaf::offset_index_space_state::
class_name() const
{
  static const std::string result("offset_index_space_state");
  return result;
}

sheaf::offset_index_space_state*
sheaf::offset_index_space_state::
clone() const
{
  // Preconditions:

  // Body:

  offset_index_space_state* result = new offset_index_space_state();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
sheaf::offset_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  offset_index_space_state* lproto = new offset_index_space_state();

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
sheaf::offset_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const offset_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::offset_index_space_state::
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
deep_size(const offset_index_space_state& xn, bool xinclude_shallow)
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
