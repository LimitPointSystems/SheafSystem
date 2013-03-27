// $RCSfile: preorder_member_iterator.cc,v $ $Revision: 1.23 $ $Date: 2013/01/12 17:17:39 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class preorder_member_iterator

#include "preorder_member_iterator.h"

#include "poset_state_handle.h"
#include "preorder_iterator.h"
#include "assert_contract.h"
#include "total_poset_member.h"


sheaf::preorder_member_iterator::
preorder_member_iterator()
    : filtered_depth_first_member_iterator(new preorder_iterator,
                                           new total_poset_member)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}


sheaf::preorder_member_iterator::
preorder_member_iterator(const preorder_member_iterator& xother)
    : filtered_depth_first_member_iterator(xother)
{

  // Preconditions:

  // Body:

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


sheaf::preorder_member_iterator&
sheaf::preorder_member_iterator::
operator=(const filtered_depth_first_member_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  filtered_depth_first_member_iterator::operator=(xother);

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

sheaf::preorder_member_iterator&
sheaf::preorder_member_iterator::
operator=(const preorder_member_iterator& xother)
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


sheaf::preorder_member_iterator::
~preorder_member_iterator()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}



bool
sheaf::preorder_member_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const preorder_member_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


sheaf::preorder_member_iterator*
sheaf::preorder_member_iterator::
clone() const
{
  preorder_member_iterator* result;

  // Preconditions:

  // Body:

  result = new preorder_member_iterator;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::preorder_member_iterator::
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

sheaf::preorder_member_iterator::
preorder_member_iterator(const abstract_poset_member& xanchor,
                         bool xdown,
                         bool xstrict)
    :filtered_depth_first_member_iterator(new preorder_iterator(xanchor,
                                          xdown,
                                          xstrict),
                                          xanchor.clone())
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(filter().index() == anchor().version_index());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(unexecutable(preorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}

sheaf::preorder_member_iterator::
preorder_member_iterator(const abstract_poset_member& xanchor,
                         const subposet& xfilter,
                         bool xdown,
                         bool xstrict)
    :filtered_depth_first_member_iterator(new preorder_iterator(xanchor,
                                          xfilter,
                                          xdown,
                                          xstrict),
                                          xanchor.clone())
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require( xanchor.host()->includes_subposet(&xfilter));


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(filter().is_same_state(&xfilter));
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(unexecutable(preorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}


sheaf::preorder_member_iterator::
preorder_member_iterator(const abstract_poset_member& xanchor,
                         pod_index_type xfilter_index,
                         bool xdown,
                         bool xstrict)
    :filtered_depth_first_member_iterator(new preorder_iterator(xanchor,
                                          xfilter_index,
                                          xdown,
                                          xstrict),
                                          xanchor.clone())
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(xfilter_index));


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(filter().is_attached());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(unexecutable(preorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}

sheaf::preorder_member_iterator::
preorder_member_iterator(const abstract_poset_member& xanchor,
                         const scoped_index& xfilter_index,
                         bool xdown,
                         bool xstrict)
    :filtered_depth_first_member_iterator(new preorder_iterator(xanchor,
                                          xfilter_index,
                                          xdown,
                                          xstrict),
                                          xanchor.clone())
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(xfilter_index));


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(filter().is_attached());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(unexecutable(preorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}


sheaf::preorder_member_iterator::
preorder_member_iterator(const abstract_poset_member& xanchor,
                         const string& xfilter_name,
                         bool xdown,
                         bool xstrict)
    :filtered_depth_first_member_iterator(new preorder_iterator(xanchor,
                                          xfilter_name,
                                          xdown,
                                          xstrict),
                                          xanchor.clone())
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(!xfilter_name.empty() ? xanchor.host()->includes_subposet(xfilter_name) : true);


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(!xfilter_name.empty() ?
         filter().name() == xfilter_name :
         filter().name() == anchor().version_name());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? item().index() !=~ anchor().index() : true);
  ensure(unexecutable(preorder - have visited all children of this));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}

void
sheaf::preorder_member_iterator::
truncate()
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  _iterator->truncate();
  update_item();

  // Postconditions:

  // Exit

  return;
}


