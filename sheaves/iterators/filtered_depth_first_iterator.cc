// $RCSfile: filtered_depth_first_iterator.cc,v $ $Revision: 1.29 $ $Date: 2013/01/12 17:17:38 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class filtered_depth_first_iterator

#include "filtered_depth_first_iterator.h"
#include "poset_state_handle.h"
#include "assert_contract.h"
#include "subposet.h"
#include "zn_to_bool.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator()
    : depth_first_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(order() == NOT_AN_ORDER);
  ensure(!is_initialized());
  ensure(descending());
  ensure(!strict());
  ensure(visit_once());

  // Exit

  return;
}

sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator(const filtered_depth_first_iterator& xother)
    : depth_first_iterator(xother)
{

  // Preconditions:

  // Body:

  // Nothing left to do; base ctor does it all.

  // Postconditions:

  ensure(invariant());
  ensure(order() == xother.order());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? filter().is_same_state(&(const_cast<filtered_depth_first_iterator&>(xother).filter())) : true);
  ensure(is_initialized() ? descending() == xother.descending() : true);
  ensure(is_initialized() ? strict() == xother.strict() : true);
  ensure(visit_once() == xother.visit_once());
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}

sheaf::filtered_depth_first_iterator&
sheaf::filtered_depth_first_iterator::
operator=(const filtered_depth_first_iterator& xother)
{

  // Preconditions:

  // Body:

  depth_first_iterator::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure(order() == xother.order());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? filter().is_same_state(&(const_cast<filtered_depth_first_iterator&>(xother).filter())) : true);
  ensure(is_initialized() ? descending() == xother.descending() : true);
  ensure(is_initialized() ? strict() == xother.strict() : true);
  ensure(visit_once() == xother.visit_once());
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return *this;
}


sheaf::filtered_depth_first_iterator::
~filtered_depth_first_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::filtered_depth_first_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const filtered_depth_first_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::filtered_depth_first_iterator*
sheaf::filtered_depth_first_iterator::
clone() const
{
  filtered_depth_first_iterator* result;

  // Preconditions:

  // Body:

  result = new filtered_depth_first_iterator;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
sheaf::filtered_depth_first_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(depth_first_iterator::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    /// @todo finish filtered_iterator::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// OTHER CONSTRUCTORS




sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator(const abstract_poset_member& xanchor,
                              bool xdown,
                              bool xstrict,
                              order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xorder != NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  initialize_order(xorder);
  _descending = xdown;
  _strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  _anchor = 0;
  _new_filter = false;
  put_anchor(&xanchor);
  put_filter(xanchor.version_index());
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.version());
  ensure(filter().is_attached());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? index() !=~ anchor().index() : true);
  ensure(visit_once());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}

sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator(const abstract_poset_member& xanchor,
                              const subposet& xfilter,
                              bool xdown,
                              bool xstrict,
                              order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(&xfilter));
  require(xorder != NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  initialize_order(xorder);
  _descending = xdown;
  _strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  _anchor = 0;
  _new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter);
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.version());
  ensure(filter().is_attached());
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? index() !=~ anchor().index() : true);
  ensure(visit_once());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}

sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator(const abstract_poset_member& xanchor,
                              pod_index_type xfilter_index,
                              bool xdown,
                              bool xstrict,
                              order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(xfilter_index));
  require(xorder != NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  initialize_order(xorder);
  _descending = xdown;
  _strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  _anchor = 0;
  _new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter_index);
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.version());
  ensure(filter().is_attached());
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? index() !=~ anchor().index() : true);
  ensure(visit_once());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}

sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator(const abstract_poset_member& xanchor,
                              const scoped_index& xfilter_index,
                              bool xdown,
                              bool xstrict,
                              order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(xfilter_index));
  require(xorder != NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  initialize_order(xorder);
  _descending = xdown;
  _strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  _anchor = 0;
  _new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter_index.hub_pod());
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.version());
  ensure(filter().is_attached());
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? index() !=~ anchor().index() : true);
  ensure(visit_once());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


sheaf::filtered_depth_first_iterator::
filtered_depth_first_iterator(const abstract_poset_member& xanchor,
                              const string& xfilter_name,
                              bool xdown,
                              bool xstrict,
                              order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(!xfilter_name.empty() ? xanchor.host()->includes_subposet(xfilter_name) : true);
  require(xorder != NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  initialize_order(xorder);
  _descending = xdown;
  _strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  _anchor = 0;
  _new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter_name);
  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.version());
  ensure(filter().is_attached());
  // If _client_filter has multiple names, ensure that at least
  // one of them matches.
  ensure(!xfilter_name.empty() ?
         _client_filter.has_name(xfilter_name) :
         _client_filter.has_name(anchor().version_name()));
  ensure(descending() == xdown);
  ensure(strict() == xstrict);
  ensure(strict() && !is_done() ? index() !=~ anchor().index() : true);
  ensure(visit_once());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


// ITERATOR FACET



void
sheaf::filtered_depth_first_iterator::
put_anchor(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(xanchor != 0);
  require(anchor_is_ancestor_of(*xanchor));
  require(xanchor->state_is_read_accessible());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now (re)initialize.

  initialize_traversal(*xanchor);

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
sheaf::filtered_depth_first_iterator::
put_anchor(pod_index_type xanchor_index)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xanchor_index));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now reinitialize.

  initialize_traversal(xanchor_index);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() == xanchor_index);
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().index() == old_filter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit:

}

void
sheaf::filtered_depth_first_iterator::
put_anchor(const scoped_index& xanchor_index)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xanchor_index));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());

  put_anchor(xanchor_index.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() ==~ xanchor_index);
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().index() == old_filter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit:

}

void
sheaf::filtered_depth_first_iterator::
put_descending(bool xdescending)
{
  // Preconditions:

  // Body:

  _descending = xdescending;

  // Postconditions:

  ensure(descending() == xdescending);

  // Exit

  return;
}

void
sheaf::filtered_depth_first_iterator::
put_strict(bool xstrict)
{
  // Preconditions:

  // Body:

  _strict = xstrict;

  // Postconditions:

  ensure(strict() == xstrict);

  // Exit

  return;
}

void
sheaf::filtered_depth_first_iterator::
put_filter(const subposet& xfilter)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->includes_subposet(&xfilter));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now reinitialize.

  initialize_filter(xfilter);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(filter().is_same_state(&xfilter));
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(is_done());

  return;
}

void
sheaf::filtered_depth_first_iterator::
put_filter(const string& xfilter_name)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(!xfilter_name.empty() ? anchor().host()->includes_subposet(xfilter_name) : true);

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now reinitialize.

  initialize_filter(xfilter_name);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());

  // If _client_filter has multiple names, ensure that at least
  // one of them matches.
  ensure(!xfilter_name.empty() ?
         _client_filter.has_name(xfilter_name) :
         _client_filter.has_name(anchor().version_name()));
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
}

void
sheaf::filtered_depth_first_iterator::
put_filter(pod_index_type xfilter_index)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->includes_subposet(xfilter_index));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now reinitialize.

  initialize_filter(xfilter_index);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(filter().index() == xfilter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
}

void
sheaf::filtered_depth_first_iterator::
put_filter(const scoped_index& xfilter_index)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->includes_subposet(xfilter_index));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  put_filter(xfilter_index.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(filter().index() ==~ xfilter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  return;
}
