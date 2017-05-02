
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

// Implementation for class section_component_iterator

#include "SheafSystem/section_component_iterator.h"

#include "SheafSystem/poset_state_handle.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/section_space_schema_member.h"
#include "SheafSystem/section_space_schema_poset.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

fiber_bundle::section_component_iterator::
section_component_iterator()
{

  // Preconditions:


  // Body:

  _anchor = 0;
  _item = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}


fiber_bundle::section_component_iterator::
section_component_iterator(const section_component_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  section_component_iterator& lother = const_cast<section_component_iterator&>(xother);

  if(lother.is_initialized())
  {
    _item = lother._item->clone();
    _anchor = lother._anchor->clone();
  }
  else
  {
    _item = 0;
    _anchor = 0;
  }
  _itr = lother._itr;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}


fiber_bundle::section_component_iterator&
fiber_bundle::section_component_iterator::
operator=(const section_component_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  section_component_iterator& lother = const_cast<section_component_iterator&>(xother);

  if(is_initialized())
  {
    _item->detach_from_state();
    delete _item;
    _item = 0;

    _anchor->detach_from_state();
    delete _anchor;
    _anchor = 0;
  }

  if(lother._anchor != 0)
  {
    _item = lother._item->clone();

    _anchor = lother._anchor->clone();
    _anchor->attach_to_state(lother._anchor);
  }

  _itr = lother._itr;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return *this;
}


fiber_bundle::section_component_iterator::
~section_component_iterator()
{

  // Preconditions:

  // Body:

  if(_anchor != 0)
  {
    _anchor->detach_from_state();
    delete _anchor;
  }

  if(_item != 0)
  {
    _item->detach_from_state();
    delete _item;
  }

  // Postconditions:

  // Exit:

  return;
}



bool
fiber_bundle::section_component_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_component_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


bool
fiber_bundle::section_component_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && any::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    result = result && ( is_initialized() == (_anchor != 0) );
    result = result && ( is_initialized() == (_item != 0) );
    result = result && ( is_initialized() == (_itr.is_initialized()) );

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}



fiber_bundle::section_component_iterator::
section_component_iterator(const section_space_schema_member& xanchor)
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());


  // Body:

  // Make sure !is_initialized, then just reset.

  _anchor = 0;
  _item = 0;
  put_anchor(&xanchor);
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(unexecutable(postorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}




// ITERATOR FACET



bool
fiber_bundle::section_component_iterator::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _item != 0;

  // Postconditions:

  // Exit

  return result;
}



fiber_bundle::section_space_schema_member&
fiber_bundle::section_component_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_component_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}



bool
fiber_bundle::section_component_iterator::
is_done() const
{
  bool result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _itr.is_done();

  // Postconditions:

  // Exit

  return result;
}


void
fiber_bundle::section_component_iterator::
next()
{

  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  _itr.next();
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() == item().is_attached());
  ensure(unexecutable(postorder - have visited all of the members of the strict down set
                        of item()));

  // Exit

  return;
}


void
fiber_bundle::section_component_iterator::
reset(bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  // Body:

  _itr.reset(xreset_markers);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(item().is_attached() == !is_done());

  // Exit

  return;
}

void
fiber_bundle::section_component_iterator::
put_anchor(const section_space_schema_member* xanchor)
{

  // Preconditions:

  require(item_is_ancestor_of(*xanchor));
  require(xanchor->state_is_read_accessible());
  require(xanchor->host()->is_schematized(false));

  // Body:

  // Reset the anchor.

  reset_anchor(*xanchor);

  // Set the anchor and filter of the iterator.

  string ldof_sp_name = schema_poset_member::dof_subposet_name("top", false);
  _itr.put_anchor(&(xanchor->fiber_schema()));
  _itr.put_filter(ldof_sp_name);
  reset_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(xanchor));
  ensure(anchor().is_same_type(xanchor));
  ensure(item().is_attached() == !is_done());

  return;
}

int
fiber_bundle::section_component_iterator::
ct(bool xreset)
{
  int result = 0;

  // Preconditions:

  require(is_initialized());
  require(xreset ? anchor().state_is_read_accessible(): true);

  // Body:

  result = _itr.ct(xreset);
  update_item();

  // Postconditions:

  ensure(result >= 0);
  ensure(is_done());

  // Exit

  return result;
}

bool
fiber_bundle::section_component_iterator::
has_visited(pod_index_type xhub_id) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  pod_index_type lbase_space_id   = anchor().host()->get_base_space_id_from_index(xhub_id);
  pod_index_type lfiber_schema_id = anchor().host()->get_fiber_schema_id_from_index(xhub_id);

  result = (anchor().base_space_id() == lbase_space_id) && _itr.has_visited(lfiber_schema_id);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_component_iterator::
has_visited(const scoped_index& xid) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xid));

  // Body:

  return has_visited(xid.hub_pod());
}


bool
fiber_bundle::section_component_iterator::
has_visited(const section_space_schema_member& xmbr) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(item_is_ancestor_of(xmbr));
  require(xmbr.is_attached());
  require(anchor().host()->is_same_state(xmbr.host()));

  // Body:

  result = (anchor().base_space_id() ==~ xmbr.base_space_id()) &&
           _itr.has_visited(&(xmbr.fiber_schema()));

  // Postconditions:

  // Exit:

  return result;
}


void
fiber_bundle::section_component_iterator::
put_has_visited(pod_index_type xhub_id, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));
  require(anchor().base_space_id() == anchor().host()->get_base_space_id_from_index(xhub_id));

  // Body:

  _itr.put_has_visited(_anchor->host()->get_fiber_schema_id_from_index(xhub_id), xvalue);

  // Postconditions:

  ensure(has_visited(xhub_id) == xvalue);

  // Exit:

  return;
}

void
fiber_bundle::section_component_iterator::
put_has_visited(const scoped_index& xid, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xid));
  require(anchor().base_space_id() == anchor().host()->get_base_space_id_from_index(xid.hub_pod()));

  // Body:

  put_has_visited(xid.hub_pod(), xvalue);
  
  // Postconditions:

  ensure(has_visited(xid) == xvalue);

  // Exit:

  return;
}

// MEMBER ITERATOR FACET

fiber_bundle::section_space_schema_member&
fiber_bundle::section_component_iterator::
item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_item;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_component_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_item;

  // Postconditions:

  // Exit

  return result;
}



bool
fiber_bundle::section_component_iterator::
item_is_ancestor_of(const section_space_schema_member& xmbr) const
{
  bool result;

  // Preconditions:

  // Body:

  // Always true in this class;
  // intended to be redefined in descendants.

  result = true;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::scoped_index&
fiber_bundle::section_component_iterator::
index() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  const scoped_index& result = _item->index();

  // Postconditions:

  ensure(result == item().index());

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::section_component_iterator::
reset_anchor(const section_space_schema_member& xanchor)
{
  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());

  // Body:

  if(_anchor == 0)
  {
    // Create the anchor handle

    _anchor = xanchor.clone();
  }

  // Attach the handle.

  _anchor->attach_to_state(&xanchor);

  // Postconditions:

  // Can't use anchor() in postconditions because
  // can't satisfy is_initialized() precondition yet.

  ensure(_anchor != 0);
  ensure(_anchor->is_attached());
  ensure(_anchor->is_same_state(&xanchor));
  ensure(_anchor->is_same_type(&xanchor));

  // Exit

  return;
}

void
fiber_bundle::section_component_iterator::
update_item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  if(_itr.is_done())
  {
    _item->detach_from_state();
  }
  else
  {
    /// @issue resets host, which is unnecessary except when called from
    /// reset_item. Would be more efficient to just reset indices; avoids
    /// call to _item.init_handle_data_members

    _item->attach_to_state(_anchor->host(), _anchor->base_space_id(), _itr.index().pod());
  }

  // Postconditions:

  ensure(item().is_attached() == !is_done());

  // Exit

  return;
}

