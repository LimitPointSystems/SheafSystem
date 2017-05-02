
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

// Implementation for class depth_first_iterator

#include "SheafSystem/depth_first_iterator.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/poset_state_handle.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/subposet.h"
#include "SheafSystem/zn_to_bool.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

// const bool sheaf::depth_first_iterator::DOWN = true;
// const bool sheaf::depth_first_iterator::UP = false;
// const bool sheaf::depth_first_iterator::RESET = true;
// const bool sheaf::depth_first_iterator::NO_RESET = false;
// const bool sheaf::depth_first_iterator::STRICT = true;
// const bool sheaf::depth_first_iterator::NOT_STRICT = false;

sheaf::depth_first_iterator::
~depth_first_iterator()
{
  // Preconditions:

  // Body:

  // Release cover iterators.

  release_cover_id_space_iterators();

  // Delete the anchor;

  if(_anchor != 0)
  {
    // Delete the anchor.

    _anchor->detach_from_state();
    delete _anchor;
  }

  // Detach the client filter.

  _client_filter.detach_from_state();

  // Delete the filter and visited marker

  if(_new_filter)
    delete _filter;
  if(_has_visited != 0)
    delete _has_visited;

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::depth_first_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const depth_first_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::depth_first_iterator*
sheaf::depth_first_iterator::
clone() const
{
  depth_first_iterator* result;

  // Preconditions:

  // Body:

  result = new depth_first_iterator;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
sheaf::depth_first_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(any::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    invariance( is_initialized() ? order() != NOT_AN_ORDER : true);
    invariance( !is_initialized() ? is_done() : true);
    invariance( is_initialized() ? anchor().is_attached() == (_has_visited != 0) : true );
    invariance( is_initialized() == (_has_visited != 0));

    // The following apparent "invariance" is in fact not true when the graph
    // is being modified behind the current position of the iterator.
    // invariance( is_initialized() ? (_has_visited->ub() == anchor().host()->member_index_ub()) : true );

    /// @todo Need to replace with a condition that takes in account when the
    /// _path_head is not initialized.

    //invariance( is_initialized() && !is_done() ? index() == _path_head.item() : true);
    invariance( (action() == NOT_AN_ACTION) == is_done() );
    invariance( (_state == NOT_A_STATE) == is_done() );
    invariance( _new_filter ? _filter != 0 : true );
    invariance( is_initialized() == (_anchor != 0) );
    invariance( !is_initialized() ? !_new_filter : true );


    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// Placeholder for null filter
const char*
sheaf::depth_first_iterator::
NULL_FILTER = "";


// ITERATOR FACET

sheaf::depth_first_iterator::order_type
sheaf::depth_first_iterator::
order() const
{
  order_type result;

  // Preconditions:

  // Body:

  result = _order;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::depth_first_iterator::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_anchor != 0) && (_has_visited != 0) && (_filter != 0);

  // Postconditions:

  // Exit

  return result;
}

sheaf::abstract_poset_member&
sheaf::depth_first_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  abstract_poset_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::abstract_poset_member&
sheaf::depth_first_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  abstract_poset_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::depth_first_iterator::
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

bool
sheaf::depth_first_iterator::
descending() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _descending;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::depth_first_iterator::
strict() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _strict;

  // Postconditions:

  // Exit

  return result;
}

sheaf::subposet&
sheaf::depth_first_iterator::
filter()
{
  // Preconditions:

  // The following precondition is stronger than necessary for
  // this routine alone, but is consistent with the preconditions for
  // anchor() and has_visited() and hence easier for the client to understand.

  require(is_initialized());

  // Body:

  subposet& result = _client_filter;

  // Postconditions:

  ensure(is_initialized() == result.is_attached());

  // Exit

  return result;
}

bool
sheaf::depth_first_iterator::
is_done() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_state == NOT_A_STATE);

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::depth_first_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  _index.invalidate();
  _action = NOT_AN_ACTION;
  _state  = NOT_A_STATE;

  // Clear the path

  release_cover_id_space_iterators();

  // Clear the filtered path

  while(!_filtered_path_tail.empty())
  {
    _filtered_path_tail.pop();
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit:
}

void
sheaf::depth_first_iterator::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_index_type lc_index;

  // The following while/switch construction is a finite state machine.
  // Each case in the switch corresponds to a state. In each state, an
  // action is performed and the result of the action determines the
  // "input token" of the finite state machine. The transition to the
  // next state is determined by the transitition function, implemented
  // as an array indexed by state and token.
  //
  // Control enters the while with _state set to some value. Each iteration
  // of the loop corresponds to a state transition. Iteration continues
  // until a state is reached which returns to the caller.

  /// @todo elaborate the number of states and the state transition functions
  /// so that the tests on _descending and _strict are removed from the iteration.
  /// For instance there should be separate EXECUTE_PREVISIT_ACTION and
  /// EXECUTE_STRICT_PREVISIT_ACTION states and transition functions. The
  /// EXECUTE_PREVISIT_ACTION would not test _strict or _index. The non-strict
  /// transistion function would use EXECUTE_PREVISIT_ACTION while the strict
  /// trnaisition function would use EXECUTE_STRICT_PREVISIT_ACTION.

  while(true)
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "in depth_first_iterator::next: _state = " << iterator_state_names[_state];
    if(is_initialized())
    {
      cout << "\t\t_filtered_path_tail: " << _filtered_path_tail.top();
      cout << "\t _index: " << _index;
    }
    cout << endl;
#endif

    switch(_state)
    {
      case INIT_COVER_ITERATOR:

	// Initialize the cover iterator, depending on truncation and direction.

	if(_path_head_lc != 0)
	{
	  _anchor->host()->release_cover_id_space_iterator(*_path_head_lc);
	}

	_path_head_lc = &_anchor->host()->get_cover_id_space_iterator(_descending, _index);

	if(xtruncate)
	{
	  // Truncation requested; initialize the iterator to end.
	  // Cover of this will be skipped.

	  _path_head_lc->force_is_done();

	  // Client has only requested truncation for the current member.
	  // If we pass thorugh this state again, we don't want to truncate.

	  xtruncate = false;
	}

	// Test the cover iterator to see if there is a current member of the cover.

	if(!_path_head_lc->is_done())
	{
	  // Cover iterator points to the current member of cover;
	  // Now there is a link defined. _index and _path_head refer to
	  // the greater member and _path_head_lc refers to the lesser member.

	  // Check to see if lesser has already been visited.

	  _state = _transition_fcn[INIT_COVER_ITERATOR][PASS];
	}
	else
	{
	  // Cover iterator is finished; we've visited all the cover.
	  // There is no current link, we're in the postvisit action position.

	  // _state = EXECUTE_POSTVISIT_ACTION;

	  _state = _transition_fcn[INIT_COVER_ITERATOR][FAIL];
	}

	break;

      case TEST_HAS_VISITED:

	// Check to see if we've already visited the
	// current member of the cover.

	lc_index = _path_head_lc->hub_pod();

	if(_visit_once && has_visited(lc_index))
	{
	  // Current member of cover has been visited and we're only visiting once;
	  // execute the link action then move on to the next member.

	  _state = _transition_fcn[TEST_HAS_VISITED][PASS];
	}
	else
	{
	  // Current member hasn't been visited or
	  // we're visiting more than once; descend

	  _state = _transition_fcn[TEST_HAS_VISITED][FAIL];
	}
	break;

      case INC_COVER_ITERATOR:

	// Move on to the next member of the cover.

	_path_head_lc->next();

	// Test the cover iterator to see if there is a current member of the cover.

	if(!_path_head_lc->is_done())
	{
	  // Cover iterator points to the current member of cover;
	  // check to see if it has already been visited.

	  _state = _transition_fcn[INC_COVER_ITERATOR][PASS];
	}
	else
	{
	  // Cover iterator is finished; we've visited all the cover;
	  // the iterator is is in the postvisit action position.

	  _state = _transition_fcn[INC_COVER_ITERATOR][FAIL];
	}

	break;

      case ERASE_COVER_ITERATOR:

	// Erase the current member of cover and move on,
	// without trashing the iterator.

	{
	  // Local scope to avoid compiler complaint about
	  // "jump to case label crosses initialization" of ltmp_itr.


#ifdef DIAGNOSTIC_OUTPUT
	  cout << "in depth_first_iterator::next::ERASE_COVER_ITERATOR "
	       << "erasing " << *_path_head_lc
	       << " in cover of " << *_path_head
	       << endl;
#endif

	  pod_index_type litem = _path_head_lc->hub_pod();
	  _path_head_lc->next();
	  _anchor->host()->clear_cover(_descending, litem);
	}

	// Test the cover iterator to see if there is a current member of the cover.

	if(!_path_head_lc->is_done())
	{
	  // Cover iterator points to the current member of cover;
	  // check to see if it has already been visited.

	  _state = _transition_fcn[ERASE_COVER_ITERATOR][PASS];
	}
	else
	{
	  // Cover iterator is finished; we've visited all the cover;
	  // the iterator is is in the postvisit action position.

	  _state = _transition_fcn[ERASE_COVER_ITERATOR][FAIL];
	}

	break;

      case DESCEND:

	// Mark the current member of cover.

	lc_index = _path_head_lc->hub_pod();

	put_has_visited(lc_index, true);

	// Descend.

	if(_index !=~ _anchor->index())
	{
	  assertion(_index.pod() == _path_head->hub_pod());

	  _path_tail.push(_path_head);

	  // Update the greater end of the link.

	  if(filter(_path_head->hub_pod()))
	  {
	    _filtered_path_tail.push(_path_head->hub_pod());
	  }
	}

	_path_head = _path_head_lc;
	_path_head_lc = 0;
	_index = lc_index;

	// This is the first time we've seend this node and we're
	// about to begin iteration over its cover.
	// This is the previsit action position.

	_state = _transition_fcn[DESCEND][PASS];

	break;

      case TEST_PATH_TAIL:

	// Test the path tail to see whether we can ascend or
	// we're done.

	if(_index == _anchor->index())
	{
	  // Tail of path is empty;
	  // _path_head is anchor;
	  // iteration is over.

	  _state = _transition_fcn[TEST_PATH_TAIL][PASS];
	}
	else
	{
	  // Tail of path is not empty; ascend.

	  _state = _transition_fcn[TEST_PATH_TAIL][FAIL];
	}

	break;

      case ASCEND:

	// Release the path head lower cover.

	_anchor->host()->release_cover_id_space_iterator(*_path_head_lc);
	_path_head_lc = 0;

	if(_path_tail.empty())
	{
	  // Assend to the anchor.

	  _path_head_lc = _path_head;
	  _path_head = 0;
	
	  // Attach this to the anchor.

	  _index = _anchor->index();
	}
	else
	{
	  // Ascend to the previous link in the path

	  _path_head_lc = _path_head;

	  // Update the greater end of the link;

	  if(!_filtered_path_tail.empty() &&
	     (_filtered_path_tail.top() == _path_tail.top()->hub_pod()))
	  {
	    // Filtered path can not be empty at this point.

	    _filtered_path_tail.pop();
	  }

	  _path_head = _path_tail.top();
	  _path_tail.pop();

	  // Attach this to the lesser member of the current link

	  _index = _path_head->hub_pod();
	}

	// We have just ascended from visiting
	// the lesser member of the link.
	// This is the link action position;

	// _state  = EXECUTE_LINK_ACTION;

	_state = _transition_fcn[ASCEND][PASS];

	break;

      case EXECUTE_PREVISIT_ACTION:

	// Only execute the action if the current member passes the filter.

	/// @todo can remove test for strictness from the iteration when
	/// _strict is false by implementing a separate state execute_strict_previsit_action,
	/// then defining two different transition functions, one for strict,
	/// one for not strict. Then proper transition function is installed by reset.

#ifdef DIAGNOSTIC_OUTPUT

	cout << "index: " << _index
	     << " filter value: " << boolalpha << filter(_index) << noboolalpha
	     << endl;
#endif

	if(filter(_index) && (!_strict || !(_index == _anchor->index())) )
	{
	  // Current member passes the filter, attach and
	  // return to client for previsit action. When client
	  // returns control, initialize iteration over this members cover.

	  attach_item();

	  _state = _transition_fcn[EXECUTE_PREVISIT_ACTION][PASS];
	  _action = PREVISIT_ACTION;
	  return;
	}
	else
	{
	  // Current member doesn't pass the filter;
	  // skip the previsit action and go directly to
	  // initializing iteration over this members cover.

	  _state = _transition_fcn[EXECUTE_PREVISIT_ACTION][FAIL];
	}

	break;

      case EXECUTE_LINK_ACTION:

#ifdef DIAGNOSTIC_OUTPUT

	cout << "\t\t*_path_head_lc: " << *_path_head_lc << endl;
#endif

	// Only execute the link action if the current member passes the filter.

	if( filter(_index) && (!_strict || !(_index == _anchor->index())) )
	{
	  // Current member passes the filter, attach and
	  // return to client for postvisit action. When client
	  // returns control, increment the cover iterator.

	  attach_item();

	  _state = _transition_fcn[EXECUTE_LINK_ACTION][PASS];
	  _action = LINK_ACTION;
	  return;
	}
	else
	{
	  // Current member doesn't pass the filter;
	  // skip the link action and go directly to
	  // incrementing the cover iterator.

	  _state = _transition_fcn[EXECUTE_LINK_ACTION][FAIL];
	}

	break;

      case EXECUTE_POSTVISIT_ACTION:

	// Only execute the action if the current member passes the filter.

	/// @todo see todo at execute_previsit_action.

	if( filter(_index) && (!_strict || !(_index == _anchor->index())) )
	{
	  // Current member passes the filter, attach and
	  // return to client for postvisit action. When client
	  // returns control, test the path to see if we can ascend.

	  attach_item();

	  _state = _transition_fcn[EXECUTE_POSTVISIT_ACTION][PASS];
	  _action = POSTVISIT_ACTION;
	  return;
	}
	else
	{
	  // Current member doesn't pass the filter;
	  // skip the postvisit action and go directly to
	  // testing the path to see if we can ascend.

	  _state = _transition_fcn[EXECUTE_POSTVISIT_ACTION][FAIL];
	}

	break;

      case FINISH:

	// Iteration is over.

	_index.invalidate();

	detach_item();

	_state = NOT_A_STATE;
	_action = NOT_AN_ACTION;
	return;
    }
  }

  // Postconditions:

  /// @issue Here and beyond is unreachable;
  /// remaining code commented out to avoid compiler warnings.

  // ensure(invariant());

  // Exit

  // return;
}

void
sheaf::depth_first_iterator::
reset(bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force the iteration into a clean state.

  force_is_done();

  // Size of host poset may have changed since last reset.
  // Make sure _has_visited is large enough.

  _has_visited->extend_to(_anchor->host()->member_index_ub().pod());

  // Reset the markers as requested.

  if(xreset_markers)

    /// @todo replace with clear_has_visited

    _has_visited->make_false_sa();

  // Advance to the first item in the iteration

  first();

  // Postconditions:

  ensure(invariant());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  /// @todo add postconditions describing the effect of reset_markers,
  /// descending, and strict. Also add a postcondtion that state is_done
  /// or is first member of iteration. The following might be useful:
  /// ensure(strict() && !is_done() ? index() != anchor().index() : true);
  /// ensure(strict() ? !has_visited(&(anchor())): true );


  // Exit

  return;
}

int
sheaf::depth_first_iterator::
ct(bool xreset)
{
  int result = 0;

  // Preconditions:

  require(is_initialized());
  require(xreset ? anchor().state_is_read_accessible(): true);

  // Body:

  if(xreset)
    reset();

  while(!is_done())
  {
    result++;
    next();
  }

  // Postconditions:

  ensure(result >= 0);
  ensure(is_done());

  // Exit

  return result;
}

bool
sheaf::depth_first_iterator::
has_visited(pod_index_type xhub_id) const
{

  // preconditions:

  require(is_initialized());
  require(anchor().host()->contains_member(xhub_id, true));

  // body:

  bool result = (*_has_visited)[xhub_id];

  return result;
}
 
bool
sheaf::depth_first_iterator::
has_visited(const scoped_index& xid) const
{

  // preconditions:

  require(is_initialized());
  require(anchor().host()->contains_member(xid, true));

  // body:

  bool result = (*_has_visited)[xid.hub_pod()];

  return result;
}
 
bool
sheaf::depth_first_iterator::
has_visited(const abstract_poset_member* xmbr) const
{

  // preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(xmbr != 0);
  require(xmbr->is_attached());
  require(anchor().host()->is_same_state(xmbr->host()));

  // body:

  bool result = (*_has_visited)[xmbr->index().hub_pod()];

  return result;
}

void
sheaf::depth_first_iterator::
put_has_visited(pod_index_type xhub_id, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  _has_visited->put(xhub_id, xvalue);

  // Postconditions:

  ensure(has_visited(xhub_id) == xvalue);

  return;
}

void
sheaf::depth_first_iterator::
put_has_visited(const scoped_index& xid, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xid));

  // Body:

  _has_visited->put(xid.hub_pod(), xvalue);

  // Postconditions:

  ensure(has_visited(xid) == xvalue);

  return;
}

bool
sheaf::depth_first_iterator::
visit_once() const
{
  return _visit_once;
}

void
sheaf::depth_first_iterator::
put_visit_once(bool xvisit_once)
{
  // Preconditions:

  // Body:

  _visit_once = xvisit_once;

  // Postconditions:

  ensure(visit_once() == xvisit_once);

  // Exit:

  return;
}

bool
sheaf::depth_first_iterator::
is_maximal() const
{
  bool result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = !greater_index().is_valid();

  // Postconditions:

  ensure(result == !greater_index().is_valid());

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::depth_first_iterator::
greater_index() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  _greater_index =
    (_action == LINK_ACTION) ? _index.pod() :
    (_filtered_path_tail.empty() ? invalid_pod_index() : _filtered_path_tail.top());

  // Postconditions:

  // Exit

  return _greater_index;
}

const sheaf::scoped_index&
sheaf::depth_first_iterator::
lesser_index() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  /// @issue the preconditions above ensure that the dereference
  /// of _path_head_lc in the following will succeed, as long as
  /// this routine is called from client level. If called internally
  /// from the INC_COVER_ITERATOR state, the dereference could fail.
  /// Such a call is inappropriate, but how do we express this fact
  /// as a precondition?

  _lesser_index = (_action == LINK_ACTION) ? _path_head_lc->hub_pod() : _index.pod();

  // Postconditions:

  // Exit

  return _lesser_index;
}

sheaf::depth_first_iterator::action_type
sheaf::depth_first_iterator::
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

void
sheaf::depth_first_iterator::
erase_cover()
{
  // Preconditions:

  require(action() == LINK_ACTION);

  // Body:

  _state = ERASE_COVER_ITERATOR;

  // Postconditions:

  // Exit:

  return;
}

// INDEX ITERATOR FACET

const sheaf::scoped_index&
sheaf::depth_first_iterator::
index() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const scoped_index& result = _index;

  // Postconditions:

  ensure( (action() == LINK_ACTION) ? (result == greater_index()) : (result == lesser_index()) );

  // Exit

  return result;
}

size_t
sheaf::depth_first_iterator::
depth() const
{
  int result;

  // Preconditions:

  require(!is_done());

  // Body:

  result = _path_tail.size();

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::depth_first_iterator::
depth_first_iterator()
{
  // Preconditions:

  // Body:

  //  Set other members to default values.

  _anchor = 0;
  _filter = 0;
  _new_filter = false;
  _descending = true;
  _strict = false;
  initialize_order(NOT_AN_ORDER);
  _has_visited = 0;
  _visit_once = true;
  _action = NOT_AN_ACTION;
  _state = NOT_A_STATE;
  _path_head_lc = 0;
  _path_head = 0;

  _index.invalidate();

  // Postconditions:

  ensure(invariant());
  ensure(order() == NOT_AN_ORDER);
  ensure(!is_initialized());
  ensure(descending());
  ensure(!strict());
  ensure(visit_once());
  ensure(is_done());

  // Exit

  return;
}

sheaf::depth_first_iterator::
depth_first_iterator(const depth_first_iterator& xother)
{

  // Preconditions:

  // Body:

  // Ensure !is_initialized(), then call assigment operator.

  _anchor = 0;
  _new_filter = false;
  _filter = 0;
  _path_head_lc = 0;
  _path_head = 0;

  (*this) = xother;

  // Assignemnt operator ensures is_done, so must reset,
  // but markers have already been initialized.

  reset(NO_RESET);

  // Postconditions:

  ensure(invariant());
  ensure(order() == xother.order());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? filter().is_same_state(&(const_cast<depth_first_iterator&>(xother).filter())) : true);
  ensure(is_initialized() ? descending() == xother.descending() : true);
  ensure(is_initialized() ? strict() == xother.strict() : true);
  ensure(visit_once() == xother.visit_once());
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}

sheaf::depth_first_iterator&
sheaf::depth_first_iterator::
operator=(const depth_first_iterator& xother)
{

  // Preconditions:

  // Body:

  depth_first_iterator& lother = const_cast<depth_first_iterator&>(xother);

  if(is_initialized())
  {
    // Force this into an uninitialized state.

    force_is_done();

    initialize_order(NOT_AN_ORDER);
    _descending = true;
    _strict = false;

    _anchor->detach_from_state();
    delete _anchor;
    _anchor = 0;

    delete _has_visited;
    _has_visited = 0;
    _visit_once = true;

    if(_new_filter)
    {
      delete _filter;
      _filter = 0;
      _new_filter = false;
    }

    _client_filter.detach_from_state();
  }

  // Now this is not initialized, which implies is_done

  assertion(!is_initialized());
  assertion(is_done());

  if(lother.is_initialized())
  {
    // Initialize this to the same state as xother.

    initialize_order(lother._order);
    _descending = lother._descending;
    _strict = lother._strict;

    initialize_traversal(lother.anchor());
    if(lother.filter().index() != lother.anchor().version_index())
    {
      initialize_filter(lother.filter().index());
    }
  }

  _visit_once = lother._visit_once;

  // Postconditions:

  ensure(invariant());
  ensure(order() == xother.order());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? filter().is_same_state(&(const_cast<depth_first_iterator&>(xother).filter())) : true);
  ensure(is_initialized() ? descending() == xother.descending() : true);
  ensure(is_initialized() ? strict() == xother.strict() : true);
  ensure(visit_once() == xother.visit_once());
  ensure(is_done());

  // Exit

  return *this;
}

void
sheaf::depth_first_iterator::
first()
{
  // Preconditions:

  require(is_initialized());
  require(_path_tail.empty()); // must be looking for first member

  // Body:

  // Initialize_index; needed by call to upper/lower_cover
  // in first pass through state init_cover_iterator.

  _index = _anchor->index();

  // Mark the anchor as visited.

  put_has_visited(_index, true);

  // Now in the previsit position of _path_head, before the previsit action
  // has been taken and before iteration over the cover has begun.

  _state = _transition_fcn[FIRST][PASS];
  next();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
mark_visited(abstract_poset_member* xmbr)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_write_accessible());
  require(xmbr != 0);
  require(xmbr->is_attached());
  require(anchor().host()->contains_member(xmbr));

  // Body:

  //  _has_visited->put(xmbr->index().pod(), true);
  put_has_visited(xmbr->index(), true);

  // Postconditions:

  ensure(has_visited(xmbr));

  // Exit:

  return;
}

void
sheaf::depth_first_iterator::
mark_not_visited(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(is_initialized());
  require(xmbr != 0);
  require(xmbr->is_attached());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xmbr));

  // Body:

  put_has_visited(xmbr->index(), false);

  // Postconditions:

  ensure(!has_visited(xmbr));

  // Exit:

  return;
}

void
sheaf::depth_first_iterator::
attach_item()
{
  // Preconditions:

  // Body:

  // Empty in this class; intended for redefinition in descendants;

  // Postconditions:

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
detach_item()
{
  // Preconditions:

  // Body:

  // Empty in the class; intended for redefinition in descendants;

  // Postconditions:

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_order(order_type xorder)
{
  // Preconditions:

  // Body:

  _order = xorder;
  _transition_fcn = STD_TRANSITION_FCNS[_order];

  // Postconditions:

  ensure(order() == xorder);

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_traversal(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(anchor_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Allocate anchor if needed and attach to
  // the state and version of xanchor.

  initialize_anchor(xanchor);

  // (Re)allocate markers and initialize to false.

  initialize_has_visited(xanchor);

  // Initialize the filter

  initialize_filter(_anchor->version_index());

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in depth_first_iterator::initialize_traversal(xanchor): " << endl
       << "_anchor = " << *_anchor << endl
       << "_filter = " << _filter << endl;
#endif

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.version());
  ensure(filter().index() == anchor().version_index());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_traversal(pod_index_type xanchor_hub_id)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xanchor_hub_id));
  require(is_done());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());

  // Set the anchor

  _anchor->attach_to_state(xanchor_hub_id);

  // Force the iterator to is_done so
  // client must reset before using this.

  force_is_done();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in depth_first_iterator::initialize_traversal(xanchor_hub_id): " << endl
       << "_anchor = " << *_anchor << endl
       << "_filter = " << _filter << endl;
#endif

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() == xanchor_hub_id);
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().index() == old_filter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_traversal(const scoped_index& xanchor_id)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xanchor_id));
  require(is_done());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());

  initialize_traversal(xanchor_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() ==~ xanchor_id);
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().index() == old_filter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_anchor(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(anchor_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  if(_anchor == 0)
  {
    _anchor = xanchor.clone();
  }
  else if(!_anchor->is_same_type(&xanchor))
  {
    release_cover_id_space_iterators();

    _anchor->detach_from_state();
    delete _anchor;
    _anchor = xanchor.clone();
  }

  _anchor->attach_to_state(&xanchor);

  // Set _index to the internal id space of _anchor.

  _index = _anchor->host()->member_id(false);
  _greater_index = _index;
  _lesser_index = _index;

  // Postconditions:

  // Can't use anchor() yet because it requres is_initialized().

  ensure(_anchor != 0);
  ensure(_anchor->is_same_state(&xanchor));
  ensure(_anchor->is_same_type(&xanchor));
  ensure(is_done());

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_has_visited(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  if(_has_visited != 0)
  {
    delete _has_visited;
  }

  // Allocate has visited bit vector to be indexed in internal scope.

  pod_index_type lub = xanchor.host()->member_index_ub().pod();
  _has_visited = new zn_to_bool(lub);


  // Postconditions:

  ensure(_has_visited != 0);
  ensure(is_done());

  // Exit

  return;
}

sheaf::zn_to_bool*
sheaf::depth_first_iterator::
has_visited() const
{
  return _has_visited;
}

void
sheaf::depth_first_iterator::
put_has_visited(zn_to_bool* xhas_visited)
{
  _has_visited = xhas_visited;
  return;
}

void
sheaf::depth_first_iterator::
initialize_filter()
{
  // Preconditions:

  require(_anchor != 0);
  require(_anchor->state_is_read_accessible());
  require(_client_filter.is_attached());
  require(is_done());

  // Body:

  // First clean up any existing filter.

  // If this allocated the existing _filter, delete it.

  if(_new_filter)
    delete _filter;

  _filter = 0;

  // Initialize the new filter using same scope as _client_filter (internal scope).
  // Iterator should traverse downset of the anchor, filtered by
  // the intersection of _client_filter with the version filter associated
  // with _anchor.version(). If _client_filter is the same as the version filter,
  // or if the version filter is the same as the allocated filter (that is,
  // the version is the coarsest common refinement and allocated members
  // pass the filter) then we don't need to compute the intersection nor
  // store the result, we can just use _client_filter._members().

  int lversion = _anchor->version();

  if(lversion == COARSEST_COMMON_REFINEMENT_VERSION)
  {
    // Version is CCR, use the client filter members as the traversal filter.

    _filter = _client_filter.members();
    _new_filter = false;
  }
  else
  {
    poset_state_handle* lhost = _anchor->host();
    pod_index_type lversion_index = lhost->version_index(lversion);
    if(_client_filter.index() == lversion_index)
    {
      // Client filter is same as version filter;
      // use the client filter members as the traversal filter.

      _filter = _client_filter.members();
      _new_filter = false;
    }
    else
    {
      // Have to allocate a new traversal filter.

      _filter = new zn_to_bool(*(_client_filter.members()));
      _new_filter = true;
      _filter->b_and_sa(lhost->powerset().member(lversion_index).members());
    }
  }

  // Postconditions:

  ensure(_filter != 0);
  ensure(is_done());

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_filter(const subposet& xfilter)
{
  // Preconditions:

  require(_anchor != 0);
  require(_anchor->state_is_read_accessible());
  require(_anchor->host()->includes_subposet(&xfilter));
  require(is_done());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  _client_filter.attach_to_state(&xfilter);

  initialize_filter();

  // Postconditions:

  ensure(invariant());
  ensure(_filter != 0);
  ensure(_client_filter.is_same_state(&xfilter));
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(is_done());


  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_filter(pod_index_type xfilter_hub_id)
{
  // Preconditions:

  require(_anchor != 0);
  require(_anchor->state_is_read_accessible());
  require(_anchor->host()->includes_subposet(xfilter_hub_id));
  require(is_done());

  // Body:

  _client_filter.attach_to_state(_anchor->host(), xfilter_hub_id);

  initialize_filter();

  // Postconditions:

  ensure(_filter != 0);
  ensure(_client_filter.index() == xfilter_hub_id);
  ensure(is_done());

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_filter(const scoped_index& xfilter_id)
{
  // Preconditions:

  require(_anchor != 0);
  require(_anchor->state_is_read_accessible());
  require(_anchor->host()->includes_subposet(xfilter_id));
  require(is_done());

  // Body:

  initialize_filter(xfilter_id.hub_pod());

  // Postconditions:

  ensure(_filter != 0);
  ensure(_client_filter.index() ==~ xfilter_id);
  ensure(is_done());

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
initialize_filter(const std::string& xfilter_name)
{
  // Preconditions:

  require(_anchor != 0);
  require(_anchor->state_is_read_accessible());
  require(!xfilter_name.empty() ?
	  _anchor->host()->includes_subposet(xfilter_name) :
	  true);
  require(is_done());

  // Body:

  if(xfilter_name.empty())
  {
    _client_filter.attach_to_state(_anchor->host(), _anchor->version_name());
  }
  else
  {
    _client_filter.attach_to_state(_anchor->host(), xfilter_name);
  }

  initialize_filter();

  // Postconditions:

  ensure(_filter != 0);
  // If _client_filter has multiple names, ensure that at least
  // one of them matches.
  ensure(!xfilter_name.empty() ?
	 _client_filter.has_name(xfilter_name) :
	 _client_filter.has_name(anchor().version_name()));
  ensure(is_done());

  // Exit

  return;
}

void
sheaf::depth_first_iterator::
release_cover_id_space_iterators()
{
  // Preconditions:

  // Body:

  if(_anchor != 0)
  {
    _anchor->host()->get_read_access();

    if(_path_head_lc != 0)
    {
      _anchor->host()->release_cover_id_space_iterator(*_path_head_lc);
      _path_head_lc = 0;
    }

    if(_path_head != 0)
    {
      _anchor->host()->release_cover_id_space_iterator(*_path_head);
      _path_head = 0;
    }

    while(!_path_tail.empty())
    {
      _anchor->host()->release_cover_id_space_iterator(*_path_tail.top());
      _path_tail.pop();
    }

    _anchor->host()->release_access();
  }
  else
  {
    /// @todo These assertions should be documented as preconditions.

    assertion(_path_head_lc == 0);
    assertion(_path_head == 0);
    assertion(_path_tail.empty());
  }
  
  // Postconditions:

  ensure(_path_head_lc == 0);
  ensure(_path_head == 0);
  ensure(_path_tail.empty());

  // Exit:

  return;
} 

const char*
sheaf::depth_first_iterator::
iterator_state_names[NOT_A_STATE+1] =
  {
    "FIRST",
    "INIT_COVER_ITERATOR",
    "TEST_HAS_VISITED",
    "INC_COVER_ITERATOR",
    "ERASE_COVER_ITERATOR",
    "DESCEND",
    "TEST_PATH_TAIL",
    "ASCEND",
    "EXECUTE_PREVISIT_ACTION",
    "EXECUTE_LINK_ACTION",
    "EXECUTE_POSTVISIT_ACTION",
    "FINISH",
    "NOT_A_STATE"
  };

const sheaf::depth_first_iterator::iterator_state
sheaf::depth_first_iterator::
PREORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1] =
  {
    // PASS,   FAIL

    EXECUTE_PREVISIT_ACTION, EXECUTE_PREVISIT_ACTION, // FIRST
    TEST_HAS_VISITED,   TEST_PATH_TAIL,   // INIT_COVER_ITERATOR
    INC_COVER_ITERATOR,  DESCEND,   // TEST_HAS_VISITED
    TEST_HAS_VISITED,  TEST_PATH_TAIL,   // INC_COVER_ITERATOR
    NOT_A_STATE,  NOT_A_STATE,   // ERASE_COVER_ITERATOR
    EXECUTE_PREVISIT_ACTION, EXECUTE_PREVISIT_ACTION, // DESCEND
    FINISH,   ASCEND,    // TEST_PATH_TAIL
    INC_COVER_ITERATOR,  INC_COVER_ITERATOR,  // ASCEND
    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // EXECUTE_PREVISIT_ACTION
    NOT_A_STATE,  NOT_A_STATE,   // EXECUTE_LINK_ACTION,
    NOT_A_STATE,  NOT_A_STATE   // EXECUTE_POSTVISIT_ACTION
  };


const sheaf::depth_first_iterator::iterator_state
sheaf::depth_first_iterator::
POSTORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1] =
  {
    // PASS,   FAIL

    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // FIRST
    TEST_HAS_VISITED,   EXECUTE_POSTVISIT_ACTION, // INIT_COVER_ITERATOR
    INC_COVER_ITERATOR,  DESCEND,   // TEST_HAS_VISITED
    TEST_HAS_VISITED,  EXECUTE_POSTVISIT_ACTION, // INC_COVER_ITERATOR
    NOT_A_STATE,  NOT_A_STATE, // ERASE_COVER_ITERATOR
    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // DESCEND
    FINISH,   ASCEND,    // TEST_PATH_TAIL
    INC_COVER_ITERATOR,  INC_COVER_ITERATOR,  // ASCEND
    NOT_A_STATE,  NOT_A_STATE,   // EXECUTE_PREVISIT_ACTION
    NOT_A_STATE,  NOT_A_STATE,   // EXECUTE_LINK_ACTION,
    TEST_PATH_TAIL,  TEST_PATH_TAIL   // EXECUTE_POSTVISIT_ACTION
  };

const sheaf::depth_first_iterator::iterator_state
sheaf::depth_first_iterator::
LINKORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1] =
  {
    // PASS,   FAIL

    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // FIRST
    TEST_HAS_VISITED,   TEST_PATH_TAIL,   // INIT_COVER_ITERATOR
    EXECUTE_LINK_ACTION, DESCEND,   // TEST_HAS_VISITED
    TEST_HAS_VISITED,  TEST_PATH_TAIL,   // INC_COVER_ITERATOR
    TEST_HAS_VISITED,  TEST_PATH_TAIL,   // ERASE_COVER_ITERATOR
    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // DESCEND
    FINISH,   ASCEND,    // TEST_PATH_TAIL
    EXECUTE_LINK_ACTION, EXECUTE_LINK_ACTION,  // ASCEND
    NOT_A_STATE,  NOT_A_STATE,   // EXECUTE_PREVISIT_ACTION
    INC_COVER_ITERATOR,  INC_COVER_ITERATOR,  // EXECUTE_LINK_ACTION,
    NOT_A_STATE,  NOT_A_STATE   // EXECUTE_POSTVISIT_ACTION
  }
;

const sheaf::depth_first_iterator::iterator_state
sheaf::depth_first_iterator::
BIORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1] =
  {
    // PASS,   FAIL

    EXECUTE_PREVISIT_ACTION, EXECUTE_PREVISIT_ACTION, // FIRST
    TEST_HAS_VISITED,   EXECUTE_POSTVISIT_ACTION, // INIT_COVER_ITERATOR
    INC_COVER_ITERATOR,  DESCEND,   // TEST_HAS_VISITED
    TEST_HAS_VISITED,  EXECUTE_POSTVISIT_ACTION, // INC_COVER_ITERATOR
    NOT_A_STATE,  NOT_A_STATE, // ERASE_COVER_ITERATOR
    EXECUTE_PREVISIT_ACTION, EXECUTE_PREVISIT_ACTION, // DESCEND
    FINISH,   ASCEND,    // TEST_PATH_TAIL
    INC_COVER_ITERATOR,  INC_COVER_ITERATOR,  // ASCEND
    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // EXECUTE_PREVISIT_ACTION
    NOT_A_STATE,  NOT_A_STATE,   // EXECUTE_LINK_ACTION,
    TEST_PATH_TAIL,  TEST_PATH_TAIL   // EXECUTE_POSTVISIT_ACTION
  };

const sheaf::depth_first_iterator::iterator_state
sheaf::depth_first_iterator::
TRIORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1] =
  {
    // PASS,   FAIL

    EXECUTE_PREVISIT_ACTION, EXECUTE_PREVISIT_ACTION, // FIRST
    TEST_HAS_VISITED,   EXECUTE_POSTVISIT_ACTION, // INIT_COVER_ITERATOR
    EXECUTE_LINK_ACTION, DESCEND,   // TEST_HAS_VISITED
    TEST_HAS_VISITED,  EXECUTE_POSTVISIT_ACTION, // INC_COVER_ITERATOR
    TEST_HAS_VISITED,  EXECUTE_POSTVISIT_ACTION, // ERASE_COVER_ITERATOR
    EXECUTE_PREVISIT_ACTION, EXECUTE_PREVISIT_ACTION, // DESCEND
    FINISH,   ASCEND,    // TEST_PATH_TAIL
    EXECUTE_LINK_ACTION, EXECUTE_LINK_ACTION,  // ASCEND
    INIT_COVER_ITERATOR, INIT_COVER_ITERATOR,  // EXECUTE_PREVISIT_ACTION
    INC_COVER_ITERATOR,  INC_COVER_ITERATOR,  // EXECUTE_LINK_ACTION,
    TEST_PATH_TAIL,  TEST_PATH_TAIL   // EXECUTE_POSTVISIT_ACTION
  };

const sheaf::depth_first_iterator::transition_fcn_type
sheaf::depth_first_iterator::
STD_TRANSITION_FCNS[NOT_AN_ORDER+1] =
  {
    PREORDER_TRANSITION_FCN,
    POSTORDER_TRANSITION_FCN,
    LINKORDER_TRANSITION_FCN,
    BIORDER_TRANSITION_FCN,
    TRIORDER_TRANSITION_FCN,
    0
  };


