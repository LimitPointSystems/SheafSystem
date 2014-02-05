
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
/// Implementation for class filtered_depth_first_itr

#ifndef FILTERED_DEPTH_FIRST_ITR_IMPL_H
#define FILTERED_DEPTH_FIRST_ITR_IMPL_H

#ifndef FILTERED_DEPTH_FIRST_ITR_H
#include "filtered_depth_first_itr.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace sheaf
{
  
// ===========================================================
// FILTERED_DEPTH_FIRST_ITR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr()
    : depth_first_itr<T>::depth_first_itr()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(this->order() == depth_first_itr<T>::NOT_AN_ORDER);
  ensure(!this->is_initialized());
  ensure(this->descending());
  ensure(!this->strict());
  ensure(this->visit_once());

  // Exit

  return;
}

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr(const filtered_depth_first_itr& xother)
    : depth_first_itr<T>::depth_first_itr(xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(this->order() == xother.order());
  ensure(this->is_initialized() == xother.is_initialized());
  ensure(this->is_initialized() ? this->anchor().is_same_state(&xother.anchor()) : true);
  ensure(this->is_initialized() ? this->anchor().version() == xother.anchor().version() : true);
  ensure(this->is_initialized() ? this->filter().is_same_state(&(const_cast<filtered_depth_first_itr&>(xother).filter())) : true);
  ensure(this->is_initialized() ? this->descending() == xother.descending() : true);
  ensure(this->is_initialized() ? this->strict() == xother.strict() : true);
  ensure(this->visit_once() == xother.visit_once());
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}

template <typename T>
filtered_depth_first_itr<T>&
filtered_depth_first_itr<T>::
operator=(const filtered_depth_first_itr& xother)
{

  // Preconditions:

  // Body:

  depth_first_itr<T>::depth_first_itr::operator=(xother);

  // Postconditions:
 
  ensure(invariant());
  ensure(this->order() == xother.order());
  ensure(this->is_initialized() == xother.is_initialized());
  ensure(this->is_initialized() ? this->anchor().is_same_state(&xother.anchor()) : true);
  ensure(this->is_initialized() ? this->anchor().version() == xother.anchor().version() : true);
  ensure(this->is_initialized() ? this->filter().is_same_state(&(const_cast<filtered_depth_first_itr&>(xother).filter())) : true);
  ensure(this->is_initialized() ? this->descending() == xother.descending() : true);
  ensure(this->is_initialized() ? this->strict() == xother.strict() : true);
  ensure(this->visit_once() == xother.visit_once());
  ensure(unexecutable(this is first member of iteration or is_done()));


  // Exit

  return *this;
}

template <typename T>
filtered_depth_first_itr<T>::
~filtered_depth_first_itr()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

// OTHER CONSTRUCTORS

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr(const abstract_poset_member& xanchor,
                         bool xdown,
                         bool xstrict,
                         typename depth_first_itr<T>::order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xorder != depth_first_itr<T>::NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  this->initialize_order(xorder);
  this->_descending = xdown;
  this->_strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  this->_anchor = 0;
  this->_new_filter = false;
  put_anchor(&xanchor);
  put_filter(xanchor.version_index());
  this->reset();

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->anchor().is_same_state(&xanchor));
  ensure(this->anchor().is_same_type(&xanchor));
  ensure(this->anchor().version() == xanchor.version());
  ensure(this->filter().is_attached());
  ensure(this->descending() == xdown);
  ensure(this->strict() == xstrict);
  ensure(this->strict() && !this->is_done() ? this->index() !=~ this->anchor().index() : true);
  ensure(this->visit_once());
  ensure(unexecutable(!this->is_done() implies this is first member));

  return;
}

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr(const abstract_poset_member& xanchor,
                         const subposet& xfilter,
                         bool xdown,
                         bool xstrict,
                         typename depth_first_itr<T>::order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(&xfilter));
  require(xorder != depth_first_itr<T>::NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  this->initialize_order(xorder);
  this->_descending = xdown;
  this->_strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  this->_anchor = 0;
  this->_new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter);
  this->reset();

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->anchor().is_same_state(&xanchor));
  ensure(this->anchor().is_same_type(&xanchor));
  ensure(this->anchor().version() == xanchor.version());
  ensure(this->filter().is_attached());
  ensure(this->descending() == xdown);
  ensure(this->strict() == xstrict);
  ensure(this->strict() && !this->is_done() ? this->index() !=~ this->anchor().index() : true);
  ensure(this->visit_once());
  ensure(unexecutable(!this->is_done() implies this is first member));

  return;
}

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr(const abstract_poset_member& xanchor,
                         pod_index_type xfilter_index,
                         bool xdown,
                         bool xstrict,
                         typename depth_first_itr<T>::order_type xorder)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(xfilter_index));
  require(xorder != depth_first_itr<T>::NOT_AN_ORDER);


  // Body:

  // Initialize the order, dir, and strictness

  this->initialize_order(xorder);
  this->_descending = xdown;
  this->_strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  this->_anchor = 0;
  this->_new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter_index);
  this->reset();

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->anchor().is_same_state(&xanchor));
  ensure(this->anchor().is_same_type(&xanchor));
  ensure(this->anchor().version() == xanchor.version());
  ensure(this->filter().is_attached());
  ensure(this->strict() == xstrict);
  ensure(this->strict() && !this->is_done() ? this->index() !=~ this->anchor().index() : true);
  ensure(this->visit_once());
  ensure(unexecutable(!this->is_done() implies this is first member));

  return;
}

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr(const abstract_poset_member& xanchor,
                         const scoped_index& xfilter_index,
                         bool xdown,
                         bool xstrict,
                         typename depth_first_itr<T>::order_type xorder)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->includes_subposet(xfilter_index));
  require(xorder != depth_first_itr<T>::NOT_AN_ORDER);

  // Body:

  // Initialize the order, dir, and strictness

  this->initialize_order(xorder);
  this->_descending = xdown;
  this->_strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  this->_anchor = 0;
  this->_new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter_index.hub_pod());
  this->reset();

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->anchor().is_same_state(&xanchor));
  ensure(this->anchor().is_same_type(&xanchor));
  ensure(this->anchor().version() == xanchor.version());
  ensure(this->filter().is_attached());
  ensure(this->strict() == xstrict);
  ensure(this->strict() && !this->is_done() ? this->index() !=~ this->anchor().index() : true);
  ensure(this->visit_once());
  ensure(unexecutable(!this->is_done() implies this is first member));

  return;
}

template <typename T>
filtered_depth_first_itr<T>::
filtered_depth_first_itr(const abstract_poset_member& xanchor,
                         const std::string& xfilter_name,
                         bool xdown,
                         bool xstrict,
                         typename depth_first_itr<T>::order_type xorder)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(!xfilter_name.empty() ? xanchor.host()->includes_subposet(xfilter_name) : true);
  require(xorder != depth_first_itr<T>::NOT_AN_ORDER);

  // Body:

  // Initialize the order, dir, and strictness

  this->initialize_order(xorder);
  this->_descending = xdown;
  this->_strict = xstrict;

  // Initialize the anchor and filter. Then, reset.

  this->_anchor = 0;
  this->_new_filter = false;
  put_anchor(&xanchor);
  put_filter(xfilter_name);
  this->reset();

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->anchor().is_same_state(&xanchor));
  ensure(this->anchor().is_same_type(&xanchor));
  ensure(this->anchor().version() == xanchor.version());
  ensure(this->filter().is_attached());
  ensure(!xfilter_name.empty() ?
         this->filter().name() == xfilter_name :
         this->filter().name() == this->anchor().version_name());
  ensure(this->descending() == xdown);
  ensure(this->strict() == xstrict);
  ensure(this->strict() && !this->is_done() ? this->index() !=~ this->anchor().index() : true);
  ensure(this->visit_once());
  ensure(unexecutable(!this->is_done() implies this is first member));

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
void
filtered_depth_first_itr<T>::
put_anchor(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(xanchor != 0);
  require(this->anchor_is_ancestor_of(*xanchor));
  require(xanchor->state_is_read_accessible());

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  this->force_is_done();

  // Now (re)initialize.

  this->initialize_traversal(*xanchor);

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->is_done());
  ensure(this->anchor().is_same_state(xanchor));
  ensure(this->anchor().is_same_type(xanchor));
  ensure(this->anchor().version() == xanchor->version());
  ensure(this->filter().index() == this->anchor().version_index());
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);

  // Exit:

}

template <typename T>
void
filtered_depth_first_itr<T>::
put_anchor(pod_index_type xanchor_index)
{
  // Preconditions:

  require(this->is_initialized());
  require(this->anchor().state_is_read_accessible());
  require(this->anchor().host()->contains_member(xanchor_index));

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);
  define_old_variable(scoped_index old_filter_index = this->filter().index());
  define_old_variable(int old_anchor_version = this->anchor().version());

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  this->force_is_done();

  // Now reinitialize.

  this->initialize_traversal(xanchor_index);

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->is_done());
  ensure(this->anchor().index() == xanchor_index);
  ensure(this->anchor().version() == old_anchor_version);
  ensure(this->filter().index() == old_filter_index);
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);

  // Exit:

}

template <typename T>
void
filtered_depth_first_itr<T>::
put_anchor(const scoped_index& xanchor_index)
{
  // Preconditions:

  require(this->is_initialized());
  require(this->anchor().state_is_read_accessible());
  require(this->anchor().host()->contains_member(xanchor_index));

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);
  define_old_variable(scoped_index old_filter_index = this->filter().index());
  define_old_variable(int old_anchor_version = this->anchor().version());

  put_anchor(xanchor_index.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->is_done());
  ensure(this->anchor().index() ==~ xanchor_index);
  ensure(this->anchor().version() == old_anchor_version);
  ensure(this->filter().index() == old_filter_index);
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);

  // Exit:

}

template <typename T>
void
filtered_depth_first_itr<T>::
put_descending(bool xdescending)
{
  // Preconditions:

  // Body:

  this->_descending = xdescending;

  // Postconditions:

  ensure(this->descending() == xdescending);

  // Exit

  return;
}

template <typename T>
void
filtered_depth_first_itr<T>::
put_strict(bool xstrict)
{
  // Preconditions:

  // Body:

  this->_strict = xstrict;

  // Postconditions:

  ensure(this->strict() == xstrict);

  // Exit

  return;
}

template <typename T>
void
filtered_depth_first_itr<T>::
put_filter(const subposet& xfilter)
{

  // Preconditions:

  require(this->is_initialized());
  require(this->anchor().state_is_read_accessible());
  require(this->anchor().host()->includes_subposet(&xfilter));

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  this->force_is_done();

  // Now reinitialize.

  this->initialize_filter(xfilter);

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->filter().is_same_state(&xfilter));
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);
  ensure(this->is_done());

  return;
}

template <typename T>
void
filtered_depth_first_itr<T>::
put_filter(const std::string& xfilter_name)
{

  // Preconditions:

  require(this->is_initialized());
  require(this->anchor().state_is_read_accessible());
  require(!xfilter_name.empty() ? this->anchor().host()->includes_subposet(xfilter_name) : true);

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  this->force_is_done();

  // Now reinitialize.

  this->initialize_filter(xfilter_name);

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->is_done());
  ensure(!xfilter_name.empty() ?
         this->filter().name() == xfilter_name :
         this->filter().name() == this->anchor().version_name());
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);

  return;
}

template <typename T>
void
filtered_depth_first_itr<T>::
put_filter(pod_index_type xfilter_index)
{
  // Preconditions:

  require(this->is_initialized());
  require(this->anchor().state_is_read_accessible());
  require(this->anchor().host()->includes_subposet(xfilter_index));

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  this->force_is_done();

  // Now reinitialize.

  this->initialize_filter(xfilter_index);

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->is_done());
  ensure(this->filter().index() == xfilter_index);
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);

  return;
}

template <typename T>
void
filtered_depth_first_itr<T>::
put_filter(const scoped_index& xfilter_index)
{

  // Preconditions:

  require(this->is_initialized());
  require(this->anchor().state_is_read_accessible());
  require(this->anchor().host()->includes_subposet(xfilter_index));

  // Body:

  define_old_variable(bool old_descending = this->_descending);
  define_old_variable(bool old_strict = this->_strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  this->force_is_done();

  // Now reinitialize.

  this->initialize_filter(xfilter_index.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(this->is_initialized());
  ensure(this->is_done());
  ensure(this->filter().index() ==~ xfilter_index);
  ensure(this->descending() == old_descending);
  ensure(this->strict() == old_strict);

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
bool
filtered_depth_first_itr<T>::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const filtered_depth_first_itr*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

template <typename T>
filtered_depth_first_itr<T>*
filtered_depth_first_itr<T>::
clone() const
{
  filtered_depth_first_itr* result;

  // Preconditions:

  // Body:

  result = new filtered_depth_first_itr;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

template <typename T>
bool
filtered_depth_first_itr<T>::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(depth_first_itr<T>::invariant());

  if(this->invariant_check())
  {
    this->disable_invariant_check();

    /// @todo finish filtered_iterator::invariant()

    // Finished, turn invariant checking back on.

    this->enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


} // namespace sheaf

#endif // ifndef FILTERED_DEPTH_FIRST_ITR_IMPL_H
