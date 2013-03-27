// $RCSfile: poset_dof_iterator.cc,v $ $Revision: 1.28 $ $Date: 2013/03/13 00:59:01 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class poset_dof_iterator

 

#include "poset_dof_iterator.h"

#include "assert_contract.h"
#include "poset_state_handle.h"
#include "schema_poset_member.h"


sheaf::poset_dof_iterator::
poset_dof_iterator()
{

  // Preconditions:


  // Body:

  _anchor = 0;
  _item = 0;
  _is_table_dof = false;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}


sheaf::poset_dof_iterator::
poset_dof_iterator(const sheaf::poset_dof_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  poset_dof_iterator& lother = const_cast<poset_dof_iterator&>(xother);

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
  _is_table_dof = lother._is_table_dof;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(is_table_dof() == xother.is_table_dof());

  // Exit

  return;
}


sheaf::poset_dof_iterator&
sheaf::poset_dof_iterator::
operator=(const sheaf::poset_dof_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));
  require(xother.is_done());

  // Body:

  poset_dof_iterator& lother = const_cast<poset_dof_iterator&>(xother);

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
  _is_table_dof = lother._is_table_dof;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(is_table_dof() == xother.is_table_dof());

  // Exit

  return *this;
}


sheaf::poset_dof_iterator::
~poset_dof_iterator()
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
sheaf::poset_dof_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_dof_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


sheaf::poset_dof_iterator*
sheaf::poset_dof_iterator::
clone() const
{
  sheaf::poset_dof_iterator* result;

  // Preconditions:

  // Body:

  result = new poset_dof_iterator;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::poset_dof_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance( any::invariant() );

  if(invariant_check())
  {
    disable_invariant_check();

    invariance( is_initialized() == (_anchor != 0) );
    invariance( is_initialized() == (_item != 0) );
    invariance( is_initialized() == (_itr.is_initialized()) );

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}



sheaf::poset_dof_iterator::
poset_dof_iterator(const sheaf::schema_poset_member& xanchor, bool xis_table_dof, int xversion)
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.has_version(xversion));


  // Body:

  // Make sure !is_initialized, then set the anchor and reset.

  _anchor = 0;
  _item = 0;
  _is_table_dof = xis_table_dof;
  put_anchor(&xanchor, xversion);
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(unexecutable(postorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());
  ensure(is_table_dof() == xis_table_dof);
  ensure(anchor().version() == xanchor.unaliased_version(xversion));

  return;
}




// ITERATOR FACET

 

bool
sheaf::poset_dof_iterator::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_anchor != 0);
  result = result && (_item != 0);
  result = result && _itr.is_initialized();

  // Postconditions:

  // Exit

  return result;
}

 

sheaf::schema_poset_member&
sheaf::poset_dof_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  schema_poset_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}



const sheaf::schema_poset_member&
sheaf::poset_dof_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  schema_poset_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}



void
sheaf::poset_dof_iterator::
put_anchor(const sheaf::schema_poset_member* xanchor, int xversion)
{
  // Preconditions:

  require(xanchor != 0);
  require(item_is_ancestor_of(*xanchor));
  require(xanchor->state_is_read_accessible());
  require(xanchor->host()->is_schematized(false));
  require(xanchor->has_version(xversion));


  // Body:

  if(_anchor == 0)
  {
    // Create the anchor handle

    _anchor = xanchor->clone();
  }

  // Attach the handle to the same state and
  // (possibly aliased) version as xanchor.

  _anchor->attach_to_state(xanchor);

  // Set the version, making sure it is unaliased.

  _anchor->put_version(xversion, true);

  // Reset the index iterator.

  string ldof_sp_name = schema_poset_member::dof_subposet_name("top", _is_table_dof);
  _itr.put_anchor(_anchor);
  _itr.put_filter(ldof_sp_name);

  // Reset the item

  reset_item();

  // Force the iterator to be done.

  force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().is_same_state(xanchor));
  ensure(anchor().is_same_type(xanchor));
  ensure(anchor().version() == xanchor->unaliased_version(xversion));

  // Exit:

}

void
sheaf::poset_dof_iterator::
put_anchor(pod_index_type xhub_id)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  define_old_variable(int old_anchor_version = anchor().version());

  // Attach the handle to the state with index xhub_id.

  _anchor->attach_to_state(xhub_id);

  // Reset the index iterator anchor

  _itr.put_anchor(xhub_id);

  // Reset the item

  reset_item();

  // Force the iterator to be done.

  force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() == xhub_id);
  ensure(anchor().version() == old_anchor_version);

  // Exit:

}

void
sheaf::poset_dof_iterator::
put_anchor(const scoped_index& xid)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().host()->contains_member(xid));

  // Body:

  define_old_variable(int old_anchor_version = anchor().version());

  put_anchor(xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() ==~ xid);
  ensure(anchor().version() == old_anchor_version);

  // Exit:

} 

bool
sheaf::poset_dof_iterator::
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
sheaf::poset_dof_iterator::
force_is_done()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  _itr.force_is_done();
  _item->detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit:
}

void
sheaf::poset_dof_iterator::
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
sheaf::poset_dof_iterator::
reset(bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  // Body:

  define_old_variable(int old_anchor_version = anchor().version());

  _itr.reset(xreset_markers);
  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(item().is_attached() == !is_done());
  ensure(anchor().version() == old_anchor_version);

  // Exit

  return;
}

int
sheaf::poset_dof_iterator::
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
sheaf::poset_dof_iterator::
has_visited(pod_index_type xhub_id) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  result = _itr.has_visited(xhub_id);

  // Postconditions:

  // Exit:

  return result;
}


bool
sheaf::poset_dof_iterator::
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
sheaf::poset_dof_iterator::
has_visited(const sheaf::schema_poset_member& xmbr) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(item_is_ancestor_of(xmbr));
  require(xmbr.is_attached());
  require(anchor().host()->is_same_state(xmbr.host()));

  // Body:

  result = _itr.has_visited(&xmbr);

  // Postconditions:

  // Exit:

  return result;
}


void
sheaf::poset_dof_iterator::
put_has_visited(pod_index_type xhub_id, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  _itr.put_has_visited(xhub_id, xvalue);

  // Postconditions:

  ensure(has_visited(xhub_id) == xvalue);

  // Exit:

  return;
}

void
sheaf::poset_dof_iterator::
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

// MEMBER ITERATOR FACET

sheaf::schema_poset_member&
sheaf::poset_dof_iterator::
item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  schema_poset_member& result = *_item;

  // Postconditions:

  // Exit

  return result;
}



const sheaf::schema_poset_member&
sheaf::poset_dof_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  schema_poset_member& result = *_item;

  // Postconditions:

  // Exit

  return result;
}

 



bool
sheaf::poset_dof_iterator::
item_is_ancestor_of(const sheaf::schema_poset_member& xmbr) const
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
sheaf::poset_dof_iterator::
index()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  define_old_variable(scoped_index result(_item->index()));

  // Postconditions:

  ensure(result == item().index());

  // Exit

  return _item->index();
}

bool
sheaf::poset_dof_iterator::
is_table_dof() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _is_table_dof;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::poset_dof_iterator::
reset_item()
{
  // Preconditions:

  // Body:

  if(_item == 0)
  {
    // Create the item handle

    _item = new schema_poset_member;
  }

  // Attach the handle.

  update_item();

  // Postconditions:

  ensure(item().is_attached() == !is_done());

  // Exit

  return;
}

void
sheaf::poset_dof_iterator::
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
    _item->attach_to_state(_itr.anchor().host(), _itr.index());
  }

  // Postconditions:

  ensure(item().is_attached() == !is_done());

  // Exit

  return;
}

