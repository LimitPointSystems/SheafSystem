
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

// Implementation for class filtered_depth_first_member_iterator

 

#include "filtered_depth_first_member_iterator.h"

#include "poset_state_handle.h"
#include "assert_contract.h"
#include "total_poset_member.h"

// const bool sheaf::filtered_depth_first_member_iterator::DOWN = true;
// const bool sheaf::filtered_depth_first_member_iterator::UP = false;
// const bool sheaf::filtered_depth_first_member_iterator::RESET = true;
// const bool sheaf::filtered_depth_first_member_iterator::NO_RESET = false;
// const bool sheaf::filtered_depth_first_member_iterator::STRICT = true;
// const bool sheaf::filtered_depth_first_member_iterator::NOT_STRICT = false;


sheaf::filtered_depth_first_member_iterator::
filtered_depth_first_member_iterator(const filtered_depth_first_member_iterator& xother)
{

  // Preconditions:

  // Body:

  _iterator = xother._iterator->clone();
  (*_iterator) = *(xother._iterator);

  _item = xother._item->clone();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? filter().is_same_state(&xother.filter()) : true);
  ensure(is_initialized() ? descending() == xother.descending() : true);
  ensure(is_initialized() ? strict() == xother.strict() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}


sheaf::filtered_depth_first_member_iterator&
sheaf::filtered_depth_first_member_iterator::
operator=(const filtered_depth_first_member_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  if(this != &(xother))
  {
    filtered_depth_first_member_iterator& lother = const_cast<filtered_depth_first_member_iterator&>(xother);

    delete _iterator;
    _iterator = lother._iterator->clone();
    (*_iterator) = *(lother._iterator);

    _item->detach_from_state();
    delete _item;
    _item = lother._item->clone();
  }


  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? filter().is_same_state(&xother.filter()) : true);
  ensure(is_initialized() ? descending() == xother.descending() : true);
  ensure(is_initialized() ? strict() == xother.strict() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return *this;
}


sheaf::filtered_depth_first_member_iterator::
~filtered_depth_first_member_iterator()
{

  // Preconditions:

  // Body:

  delete _iterator;
  _iterator = 0;

  _item->detach_from_state();
  delete _item;
  _item = 0;

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::filtered_depth_first_member_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const filtered_depth_first_member_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::filtered_depth_first_member_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && any::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    invariance( _item != 0 );
    invariance( _iterator != 0 );
    invariance( is_initialized() == (_iterator->is_initialized()) );

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// ITERATOR FACET

sheaf::depth_first_iterator::order_type
sheaf::filtered_depth_first_member_iterator::
order()
{
  depth_first_iterator::order_type result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _iterator->order();

  // Postconditions:

  // Exit

  return result;
}

 

bool
sheaf::filtered_depth_first_member_iterator::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _iterator->is_initialized();

  // Postconditions:

  // Exit

  return result;
}

 



sheaf::abstract_poset_member&
sheaf::filtered_depth_first_member_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  abstract_poset_member& result = _iterator->anchor();

  // Postconditions:

  // Exit

  return result;
}



const sheaf::abstract_poset_member&
sheaf::filtered_depth_first_member_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  abstract_poset_member& result = _iterator->anchor();

  // Postconditions:

  // Exit

  return result;
}



void
sheaf::filtered_depth_first_member_iterator::
put_anchor(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(xanchor!=0);

  // Body:

  define_old_variable(bool old_descending = descending());
  define_old_variable(bool old_strict = strict());

  // Set the iterator's anchor and update the item.

  _iterator->put_anchor(xanchor);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().is_same_state(xanchor));
  ensure(anchor().is_same_type(xanchor));
  ensure(anchor().version() == xanchor->version());
  ensure(filter().index() == anchor().version_index());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit:

}

void
sheaf::filtered_depth_first_member_iterator::
put_anchor(pod_index_type xanchor_hub_id)
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Set the iterator's anchor and update the item.

  _iterator->put_anchor(xanchor_hub_id);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() == xanchor_hub_id);

  // Exit:

}

void
sheaf::filtered_depth_first_member_iterator::
put_anchor(const scoped_index& xanchor_id)
{
  // Preconditions:

  require(is_initialized());

  // Body:

  put_anchor(xanchor_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() ==~ xanchor_id);

  // Exit:

}

const sheaf::subposet&
sheaf::filtered_depth_first_member_iterator::
filter() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  subposet& result = _iterator->filter();

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::filtered_depth_first_member_iterator::
put_filter(const subposet& xfilter)
{

  // Preconditions:

  require(anchor().host()->includes_subposet(&xfilter));

  // Body:

  define_old_variable(bool old_descending = descending());
  define_old_variable(bool old_strict = strict());

  // Set the iterator's filter and update the item

  _iterator->put_filter(xfilter);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(filter().is_same_state(&xfilter));
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
}

void
sheaf::filtered_depth_first_member_iterator::
put_filter(const std::string& xfilter_name)
{

  // Preconditions:

  require(!xfilter_name.empty() ? anchor().host()->includes_subposet(xfilter_name) : true);

  // Body:

  define_old_variable(bool old_descending = descending());
  define_old_variable(bool old_strict = strict());

  // Set the iterator's filter and update the item

  _iterator->put_filter(xfilter_name);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(!xfilter_name.empty() ?
         filter().name() == xfilter_name :
         filter().name() == anchor().version_name());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
}

void
sheaf::filtered_depth_first_member_iterator::
put_filter(pod_index_type xfilter_hub_id)
{

  // Preconditions:

  require(anchor().host()->includes_subposet(xfilter_hub_id));

  // Body:

  define_old_variable(bool old_descending = descending());
  define_old_variable(bool old_strict = strict());

  // Set the iterator's filter and update the item

  _iterator->put_filter(xfilter_hub_id);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(filter().index() == xfilter_hub_id);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
}

void
sheaf::filtered_depth_first_member_iterator::
put_filter(const scoped_index& xfilter_id)
{

  // Preconditions:

  require(anchor().host()->includes_subposet(xfilter_id));

  // Body:

  define_old_variable(bool old_descending = descending());
  define_old_variable(bool old_strict = strict());

  put_filter(xfilter_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(filter().index() ==~ xfilter_id);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
} 

bool
sheaf::filtered_depth_first_member_iterator::
descending() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _iterator->descending();

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::filtered_depth_first_member_iterator::
put_descending(bool xdescending)
{
  // Preconditions:

  // Body:

  _iterator->put_descending(xdescending);

  // Postconditions:

  ensure(descending() == xdescending);

  // Exit

  return;
}

 

bool
sheaf::filtered_depth_first_member_iterator::
strict() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _iterator->strict();

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::filtered_depth_first_member_iterator::
put_strict(bool xstrict)
{
  // Preconditions:

  // Body:

  _iterator->put_strict(xstrict);

  // Postconditions:

  ensure(strict() == xstrict);

  // Exit

  return;
}

 

bool
sheaf::filtered_depth_first_member_iterator::
is_done() const
{
  bool result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _iterator->is_done();

  // Postconditions:

  // Exit

  return result;
}


void
sheaf::filtered_depth_first_member_iterator::
next()
{

  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  _iterator->next();
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() == item().is_attached());

  // Exit

  return;
}


void
sheaf::filtered_depth_first_member_iterator::
reset(bool xreset_markers)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  // Body:

  define_old_variable(int old_anchor_version = anchor().version());
  define_old_variable(bool old_descending = descending());
  define_old_variable(bool old_strict = strict());

  _iterator->reset(xreset_markers);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().is_attached());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(item().is_attached() == !is_done());

  // Exit

  return;
}

int
sheaf::filtered_depth_first_member_iterator::
ct(bool xreset)
{
  int result = 0;

  // Preconditions:

  require(is_initialized());
  require(xreset ? anchor().state_is_read_accessible(): true);

  // Body:

  result = _iterator->ct();
  update_item();

  // Postconditions:

  ensure(result >= 0);
  ensure(is_done());

  // Exit

  return result;
}

bool
sheaf::filtered_depth_first_member_iterator::
has_visited(pod_index_type xhub_id) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  result = _iterator->has_visited(xhub_id);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::filtered_depth_first_member_iterator::
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
sheaf::filtered_depth_first_member_iterator::
has_visited(const abstract_poset_member& xmbr) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(xmbr.is_attached());
  require(anchor().host()->is_same_state(xmbr.host()));

  // Body:

  result = _iterator->has_visited(&xmbr);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::filtered_depth_first_member_iterator::
put_has_visited(pod_index_type xhub_id, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  _iterator->put_has_visited(xhub_id, xvalue);

  // Postconditions:

  ensure(has_visited(xhub_id) == xvalue);

  // Exit:

  return;
}

void
sheaf::filtered_depth_first_member_iterator::
put_has_visited(const scoped_index& xid, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xid));

  // Body:

  put_has_visited(xid.hub_pod(), xvalue);

  // Postconditions:

  ensure(has_visited(xid) == xvalue);

  // Exit:

  return;
}

const sheaf::scoped_index&
sheaf::filtered_depth_first_member_iterator::
greater_index() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  const scoped_index& result = _iterator->greater_index();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::filtered_depth_first_member_iterator::
lesser_index() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  const scoped_index& result = _iterator->lesser_index();

  // Postconditions:

  ensure(result == item().index());

  // Exit

  return result;
}

// MEMBER ITERATOR FACET

 

sheaf::abstract_poset_member&
sheaf::filtered_depth_first_member_iterator::
item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  abstract_poset_member& result = *_item;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::abstract_poset_member&
sheaf::filtered_depth_first_member_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  abstract_poset_member& result = *_item;

  // Postconditions:

  // Exit

  return result;
}
 



bool
sheaf::filtered_depth_first_member_iterator::
item_is_ancestor_of(const abstract_poset_member& xmbr) const
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

 

bool
sheaf::filtered_depth_first_member_iterator::
anchor_is_ancestor_of(const abstract_poset_member& xmbr) const
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

// PROTECTED MEMBER FUNCTIONS

sheaf::filtered_depth_first_member_iterator::
filtered_depth_first_member_iterator(filtered_depth_first_iterator* xitr,
                                     abstract_poset_member* xitem)
{
  // Preconditions:

  require(xitr != 0);
  require(xitem != 0);

  // Body:

  _iterator = xitr;
  _item = xitem;

  update_item();

  // Postconditions:

  ensure(_iterator == xitr);
  ensure(_item == xitem);
  ensure(!is_done() == item().is_attached());

  // Exit

  return;
}

void
sheaf::filtered_depth_first_member_iterator::
update_item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  if(_iterator->is_done())
  {
    _item->detach_from_state();
  }
  else
  {
    _item->attach_to_state(_iterator->anchor().host(), _iterator->index());
  }

  // Postconditions:

  ensure(!is_done() == item().is_attached());

  // Exit

  return;
}


sheaf::filtered_depth_first_member_iterator::
filtered_depth_first_member_iterator()
{
  // Preconditions:

  // Body:

  // This routine should be unreachable.

  not_implemented();

  // Postconditions:

  // Exit

  return;
}
