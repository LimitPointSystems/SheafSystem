// $RCSfile: block_decomposition_iterator.cc,v $ $Revision: 1.23 $ $Date: 2013/01/12 17:17:38 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class block_decomposition_iterator

#include "block_decomposition_iterator.h"

#include "poset_state_handle.h"
#include "biorder_iterator.h"
#include "preorder_iterator.h"
#include "assert_contract.h"
#include "total_poset_member.h"

//#define DIAGNOSTIC_OUTPUT

///
sheaf::block_decomposition_iterator::
block_decomposition_iterator()
    : filtered_depth_first_member_iterator(new biorder_iterator,
                                           new total_poset_member)
{

  // Preconditions:


  // Body:

  _action = NOT_AN_ACTION;
  _below_neighborhood = false;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());
  ensure(action() == NOT_AN_ACTION);

  // Exit

  return;
}


///
sheaf::block_decomposition_iterator::
block_decomposition_iterator(const block_decomposition_iterator& xother)
    : filtered_depth_first_member_iterator(xother)
{

  // Preconditions:

  // Body:

  _action = NOT_AN_ACTION;
  _below_neighborhood = false;
  if(is_initialized())
  {
    _blocks.attach_to_state(anchor().host(), "__blocks");
    _neighborhoods.attach_to_state(anchor().host(), "__neighborhoods");
    first();
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

  return;
}


///
sheaf::block_decomposition_iterator&
sheaf::block_decomposition_iterator::
operator=(const filtered_depth_first_member_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  filtered_depth_first_member_iterator::operator=(xother);
  _action = NOT_AN_ACTION;
  _below_neighborhood = false;
  if(is_initialized())
  {
    _blocks.attach_to_state(anchor().host(), "__blocks");
    _neighborhoods.attach_to_state(anchor().host(), "__neighborhoods");
    first();
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

///
sheaf::block_decomposition_iterator&
sheaf::block_decomposition_iterator::
operator=(const block_decomposition_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}


///
sheaf::block_decomposition_iterator::
~block_decomposition_iterator()
{

  // Preconditions:

  // Body:

  _blocks.detach_from_state();
  _neighborhoods.detach_from_state();
  _center_member.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}


///

///
bool
sheaf::block_decomposition_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const block_decomposition_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::block_decomposition_iterator*
sheaf::block_decomposition_iterator::
clone() const
{
  block_decomposition_iterator* result;

  // Preconditions:

  // Body:

  result = new block_decomposition_iterator;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::block_decomposition_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && filtered_depth_first_member_iterator::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::block_decomposition_iterator::
block_decomposition_iterator(const abstract_poset_member& xanchor,
                             bool xdown,
                             bool xstrict)
    :filtered_depth_first_member_iterator(new biorder_iterator(xanchor,
                                          xdown,
                                          xstrict),
                                          new total_poset_member)
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet("__blocks"));
  require(xanchor.host()->includes_subposet("__neighborhoods"));

  // Body:

  _action = NOT_AN_ACTION;
  _below_neighborhood = false;
  _blocks.attach_to_state(anchor().host(), "__blocks");
  _neighborhoods.attach_to_state(anchor().host(), "__neighborhoods");
  first();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(filter().index() == anchor().version_index());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(strict() ? !has_visited(anchor()): true );
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}




///
sheaf::block_decomposition_iterator::
block_decomposition_iterator(filtered_depth_first_iterator* xitr,
                             abstract_poset_member* xitem)
    : filtered_depth_first_member_iterator(xitr, xitem)
{
  // Preconditions:

  // Body:

  _action = NOT_AN_ACTION;
  _below_neighborhood = false;

  // Postconditions:

  // Exit

  return;
}

 

///
sheaf::block_decomposition_iterator::action_type
sheaf::block_decomposition_iterator::
action() const
{
  action_type result;

  // Preconditions:

  // Body:

  result = _action;

  // Postconditions:

  // Exit

  return result;
}



///
void
sheaf::block_decomposition_iterator::
next()
{

  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  next(false);

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() == item().is_attached());
  ensure(is_done() == (action() == NOT_AN_ACTION));

  // Exit

  return;
}




///
void
sheaf::block_decomposition_iterator::
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
  first();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().is_attached());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(strict() ? !has_visited(anchor()): true );
  ensure(item().is_attached() == !is_done());

  // Exit

  return;
}


///
sheaf::subposet&
sheaf::block_decomposition_iterator::
blocks()
{
  // Preconditions:


  // Body:

  subposet& result = _blocks;

  // Postconditions:


  // Exit:

  return result;
}


///
sheaf::subposet&
sheaf::block_decomposition_iterator::
neighborhoods()
{
  // Preconditions:


  // Body:

  subposet& result = _neighborhoods;

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::abstract_poset_member&
sheaf::block_decomposition_iterator::
center_member()
{
  // Preconditions:


  // Body:

  abstract_poset_member& result = _center_member;

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::block_decomposition_iterator::neighbor_list_type*
sheaf::block_decomposition_iterator::
neighbor_list()
{
  neighbor_list_type* result;

  // Preconditions:

  require(!is_done());

  // Body:

  // Note: some neighborhoods may be <= other neighborhoods.
  // As a result, we will not get all the neighbor links if
  // we just do a single depth first traversal from the top.

  result = new neighbor_list_type;

  // Initialize a preorder iterator without
  // really iterating over anything.

  preorder_iterator lblock_itr(anchor().host()->top(), DOWN, NOT_STRICT);

  list<scoped_index> ldown_set;

  poset_state_handle* lhost = anchor().host();
  index_iterator lnbrhd_itr = _neighborhoods.indexed_member_iterator();
  while(!lnbrhd_itr.is_done())
  {
    // Get the id of the center member of the neighborhood.

    string lnbrhd_name = lhost->member_name(lnbrhd_itr.index());

    string lctr_name(poset_path::block_name(lnbrhd_name));
    pod_index_type lctr_id = lhost->member_id(lctr_name, false);

    // Get the list of neighbors for the center.

    list<scoped_index>& lnbr_list = (*result)[lctr_id];

    // Load the neighbor list for the center.

    lblock_itr.put_anchor(lnbrhd_itr.index());

    lblock_itr.reset(false);
    while(!lblock_itr.is_done())
    {
      const scoped_index& lblock_id = lblock_itr.index();

      // Store this member in the down set list.

      ldown_set.push_back(lblock_id);

      // Examine this member.

      if(_blocks.contains_member(lblock_id))
      {
        // This member of the down set
        // of the neighborhood is a block.

        if((lblock_id.hub_pod() != lctr_id))
        {
          // This block is a neighbor of the center member.

          lnbr_list.push_back(lblock_itr.index());
        }

        // Don't want to go any deeper.

        lblock_itr.truncate();
      }
      else
      {
        // This member is not a block; go deeper.

        lblock_itr.next();
      }
    }

    // Explicitly clear the visited flags on the
    // down set iterator; avoids problem size reset.

    while(!ldown_set.empty())
    {
      lblock_itr.put_has_visited(ldown_set.front(), false);
      ldown_set.pop_front();
    }

    // Move on to the next neighborhood.

    lnbrhd_itr.next();
  }


#ifdef DIAGNOSTIC_OUTPUT
  neighbor_list_type::iterator itr = result->begin();
  while(itr != result->end())
  {
    cout << "block " << itr->first << " nbrs:";
    list<scoped_index>::iterator litr = itr->second.begin();
    while(litr != itr->second.end())
    {
      cout << " " << *litr++;
    }
    cout << endl;
    itr++;
  }
#endif

  // Postconditions:


  // Exit:

  return result;
}

///
void
sheaf::block_decomposition_iterator::
next(bool xtruncate)
{

  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  _action = NOT_AN_ACTION;

  while((_action == NOT_AN_ACTION) && !_iterator->is_done())
  {
    _iterator->next(xtruncate);
    update_item();

    if(_iterator->action() == biorder_iterator::PREVISIT_ACTION)
    {
      // In previsit position.

      if(_neighborhoods.contains_member(_item))
      {
        _below_neighborhood = true;
        string lnbrhd_name = item().name();
        string lctr_name(poset_path::block_name(lnbrhd_name));
        _center_member.attach_to_state(item().host(), lctr_name);
      }

      // Keep going, but don't go deeper
      // than the block members.

      _action = NOT_AN_ACTION;
      xtruncate = _blocks.contains_member(_item);
    }
    else if(_iterator->action() == biorder_iterator::POSTVISIT_ACTION)
    {
      // In postvisit position.

      if(_blocks.contains_member(_item))
      {
        _action = BLOCK_ACTION;
      }
      else if(_neighborhoods.contains_member(_item))
      {
        _action = NEIGHBORHOOD_ACTION;
        _below_neighborhood = false;
      }
      else
      {
        if(!_below_neighborhood)
        {
          _center_member.detach_from_state();
        }
        _action = NOT_AN_ACTION;
      }

      // Truncation argument is ignored if not previsit action.
    }
  }

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() == item().is_attached());
  ensure(is_done() == (action() == NOT_AN_ACTION));

  // Exit

  return;
}

///
void
sheaf::block_decomposition_iterator::
first()
{
  // Preconditions:

  require(_iterator->is_done() ||
          (_iterator->action() == biorder_iterator::PREVISIT_ACTION));

  // Body:

  // _iterator is either in previsit position or done.

  if(!_iterator->is_done())
  {
    // Must be in previsit position.
    // Keep going, but don't go deeper
    // than the block members.

    next(_blocks.contains_member(_item));
  }

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() == item().is_attached());
  ensure(is_done() == (action() == NOT_AN_ACTION));

  // Exit:

  return;
}

