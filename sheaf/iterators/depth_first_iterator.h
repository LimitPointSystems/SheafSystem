
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

// Interface for class depth_first_iterator


#ifndef COM_LIMITPOINT_SHEAF_DEPTH_FIRST_ITERATOR_H
#define COM_LIMITPOINT_SHEAF_DEPTH_FIRST_ITERATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_STATE_HANDLE_H
#include "ComLimitPoint/sheaf/poset_state_handle.h"
#endif

#ifndef STD_STACK_H
#include "std_stack.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SUBPOSET_H
#include "ComLimitPoint/sheaf/subposet.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_TOTAL_POSET_MEMBER_H
#include "ComLimitPoint/sheaf/total_poset_member.h"
#endif

namespace sheaf
{

class zn_to_bool;  

///
/// @deprecated Use depth_first_tr
/// The general depth-first iterator over the intersection of a poset member anchor's
/// whole with its down set. Implemented as a finite state machine with a client
/// selectable state transition function that can be chosen to provide various iteration
/// orders.<br>
/// <br>
/// The iterator returns control to the client so that the it can perform client-defined
/// actions. There are three action types, the PREVISIT_ACTION, the POSTVISIT_ACTION, and
/// the LINK_ACTION, each associated with specific positions in the iteration.
/// The previsit position is immediately before iteration over the cover of the current
/// member begins. The postvisit position is immediately after iteration over the cover
/// ends. The link position is on the current link, immediately after the lesser end of the
/// link has been visited and context has ascended to the current link. The link action
/// thus immediately follows the postvisit action of the lesser member, but the context
/// is different.<br>
/// <br>
/// This iterator visits every link in the cover relation graph below the anchor
/// of the iteration, maintaining a path to the current member. Conceptually, the path
/// is a list of pointers to lower cover iterators. The current member
/// of each iterator is a node in the path. Physically, the path is stored
/// in two parts. _index is the head of the list. The tail of the list is
/// stored in the variable _path. The current link in the graph is
/// the link between the front of _path and _index, with _index being the
/// lesser member of the link.
///
class SHEAF_DLL_SPEC depth_first_iterator : public any
{


public:

  // CANONICAL MEMBERS

  ///
  /// Assignment operator
  ///
  depth_first_iterator& operator=(const depth_first_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~depth_first_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual depth_first_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // SOME USEFUL CONSTANTS

  ///
  /// Placeholder for null filter
  ///
  static const char* NULL_FILTER;

/*   /// */
/*   /// Iteration directions */
/*   /// */
/*   static const bool DOWN; */

/*   /// */
/*   /// Iteration directions */
/*   /// */
/*   static const bool UP; */

/*   /// */
/*   /// Iteration marker reset control */
/*   /// */
/*   static const bool RESET; */

/*   /// */
/*   /// Iteration marker reset control */
/*   /// */
/*   static const bool NO_RESET; */

/*   /// */
/*   /// Iteration strictness control */
/*   /// */
/*   static const bool STRICT; */

/*   /// */
/*   /// Iteration strictness control */
/*   /// */
/*   static const bool NOT_STRICT; */

  ///
  /// The types of order in which the iterator will visit
  /// the members of the poset. Determines which
  /// actions are exported to the client.
  ///
  enum order_type
  {
    PREORDER,  // Member is visited before its inferiors, exports PREVISIT_ACTION.
    POSTORDER, // Member is visited after its inferiors, exports POSTVISIT_ACTION.
    LINKORDER, // Visits links; exports LINK_ACTION.
    BIORDER,  // Exports PREVISIT_ACTION and POSTVISIT_ACTION.
    TRIORDER,  // Exports PREVISIT_ACTION, POSTVISIT_ACTION, and LINK_ACTION.
    NOT_AN_ORDER
  };

  ///
  /// The types of action a client should take when
  /// the iterator returns control to the client.
  ///
  enum action_type
  {
    PREVISIT_ACTION,
    LINK_ACTION,
    POSTVISIT_ACTION,
    NOT_AN_ACTION
  };

  // ITERATOR FACET

  ///
  /// The order of the iteration. Determines which
  /// actions are exported to the client.
  ///
  order_type order() const;

  //$$SCRIBBLE jebutler const correctness

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  virtual bool is_initialized() const;

  ///
  /// The poset member whose downset is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  virtual abstract_poset_member& anchor();

  ///
  /// The poset member whose downset is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  virtual const abstract_poset_member& anchor() const;

  ///
  /// True if xmbr conforms to the type of anchor of this.
  ///
  virtual bool anchor_is_ancestor_of(const abstract_poset_member& xmbr) const;

  ///
  /// True if iterating over down set of anchor
  ///
  bool descending() const;

  ///
  /// True if iterating over xstrict up/down set of anchor
  ///
  bool strict() const;

  ///
  /// The subposet which is the filter;
  /// Defines what is passed, not what is blocked.
  ///
  subposet& filter();

  ///
  /// True if iteration finished
  ///
  bool is_done() const;

  ///
  /// Force the iterator to be done.
  ///
  virtual void force_is_done();

  ///
  /// Makes this the next member of the subset.
  ///
  inline void next()
  {
    next(false);
  };

  ///
  /// Makes this the next member of the subset
  /// which is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  ///
  inline void truncate()
  {
    next(true);
  };

  ///
  /// Makes this the next member of the subset.
  /// If action() == PREVISIT_ACTION and xtruncate,
  /// new this is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  /// If action() != PREVISIT_ACTION, xtruncate is ignored.
  ///
  virtual void next(bool xtruncate);

  ///
  /// Restarts the iteration over the down set of anchor().
  ///
  virtual void reset(bool xreset_markers = true);

  ///
  /// The number of members of the iteration set, from the current member to
  /// the end, inclusive. If xreset, reset before computing the count.
  ///
  int ct(bool xreset = false);

  ///
  /// True if this has already visited member with hub id xhub_id.
  ///
  bool has_visited(pod_index_type xhub_id) const;

  ///
  /// True if this has already visited member with id xid
  ///
  bool has_visited(const scoped_index& xid) const;

  ///
  /// True if this has already visited member xmbr
  ///
  bool has_visited(const abstract_poset_member* xmbr) const;

  ///
  /// Set the visited marker for hub id xhub_id to xvalue.
  /// Intended for use reseting iterator without having
  /// to reset entire collection of markers.
  ///
  void put_has_visited(pod_index_type xhub_id, bool xvalue);

  ///
  /// Set the visisted marker for id xid to xvalue.
  /// Intended for use reseting iterator without having
  /// to reset entire collection of markers.
  ///
  void put_has_visited(const scoped_index& xid, bool xvalue);

  ///
  /// True if traversal should only visit a member once;
  /// that is, it should not revisit members it has already visited.
  ///
  bool visit_once() const;

  ///
  /// Set visit_once() to xvisit_once.
  ///
  void put_visit_once(bool xvisit_once);

  ///
  /// True if the current member has no greater member
  /// within the subposet visited by this iterator.
  ///
  bool is_maximal() const;

  ///
  /// The index of the greater member of the current link
  ///
  const scoped_index& greater_index() const;

  ///
  /// The index of the lesser member of the current link.
  ///
  const scoped_index& lesser_index() const;

  ///
  /// The type of action the client should take
  /// when the iterator returns control to the client.
  ///
  action_type action() const;

  ///
  /// Schedules the lesser member entry in the cover of
  /// the greater member of the current link for deletion
  /// on the next call to next().
  /// Warning: this function can change the state of the
  /// the cover relation graph in unpredictable ways.
  /// Use only if you know what you are doing.
  ///
  void erase_cover();

  // INDEX ITERATOR FACET

  ///
  /// The index of the current member of the iteration.
  ///
  const scoped_index& index() const;

  ///
  /// The length of the path from anchor() to the current member.
  ///
  size_t depth() const;

protected:

  ///
  /// Default constructor; creates an unattached iterator,
  ///
  depth_first_iterator();

  ///
  /// Copy constructor
  ///
  depth_first_iterator(const depth_first_iterator& xother);

  ///
  /// Moves this to the first member of the iteration.
  ///
  void first();

  ///
  /// Mark xmbr as visited.
  /// Warning: this function can change the
  /// state of the iteration in unpredictable ways.
  /// Use only if you know what you are doing.
  ///
  void mark_visited(abstract_poset_member* xmbr);

  ///
  /// Mark xmbr as not visited.
  /// Warning: this function can change the
  /// state of the iteration in unpredictable ways.
  /// Use only if you know what you are doing.
  ///
  void mark_not_visited(abstract_poset_member* xmbr);

  ///
  /// Attaches the item handle to the current index.
  /// Empty in this class; intended for redefinition in descendants.
  ///
  virtual void attach_item();

  ///
  /// Detaches the item handle to the current index.
  /// Empty in this class; intended for redefinition in descendants.
  ///
  virtual void detach_item();

  ///
  /// Initializes _order and _transition_fcn
  ///
  void initialize_order(order_type xorder);

  ///
  /// Initializes the anchor, has_visited markers and filter.
  ///
  void initialize_traversal(const abstract_poset_member& xanchor);

  ///
  /// Initializes the anchor, has_visited markers and filter.
  ///
  void initialize_traversal(pod_index_type xanchor_hub_id);

  ///
  /// Initializes the anchor, has_visited markers and filter.
  ///
  void initialize_traversal(const scoped_index& xanchor_id);

  ///
  /// Initializes the anchor.
  ///
  void initialize_anchor(const abstract_poset_member& xanchor);

  ///
  /// Initializes the has_visited markers.
  ///
  virtual void initialize_has_visited(const abstract_poset_member& xanchor);

  ///
  /// The marker bit vector.
  //// @hack temporary support for obsolete "multivalued" 
  //// feature of discretization_iterator; will be removed when
  //// discretization_iterator updated.
  ////
  zn_to_bool* has_visited() const;

  ///
  /// Sets _has_visited to xhas_visited.
  //// @hack temporary support for obsolete "multivalued" 
  //// feature of discretization_iterator; will be removed when
  //// discretization_iterator updated.
  ////
  void put_has_visited(zn_to_bool* xhas_visited);
  

  ///
  /// The value of the filter at hub id xhub_id.
  ///
  bool filter(pod_index_type xhub_id) const
  {
    return (*_filter)[xhub_id];
  };

  ///
  /// The value of the filter at id xid.
  ///
  bool filter(const scoped_index& xid) const
  {
    return (*_filter)[xid.hub_pod()];
  };

  ///
  /// Initializes the filter subposet from the client filter.
  ///
  void initialize_filter();

  ///
  /// Initializes the client filter to xfilter then
  /// initializes the filter from the client filter.
  ///
  void initialize_filter(const subposet& xfilter);

  ///
  /// Initializes the client filter to the subposet with hub id
  /// xfilter_hub_id then initializes the filter from the client filter.
  ///
  void initialize_filter(pod_index_type xfilter_hub_id);

  ///
  /// Initializes the client filter to the subposet with id
  /// xfilter_id then initializes the filter from the client filter.
  ///
  void initialize_filter(const scoped_index& xfilter_id);

  ///
  /// Initializes the client filter to the subposet with name
  /// xfilter_name then initializes the filter from the client filter.
  ///
  void initialize_filter(const std::string& xfilter_name);

  ///
  /// Release the cover iterators back to the pool of iterators.
  ///
  void release_cover_id_space_iterators();

  ///
  /// The top member of the down set being iterated over
  ///
  abstract_poset_member* _anchor;

  ///
  /// The type of action the client should take;
  /// the state of the iterator.
  ///
  action_type _action;

  ///
  /// The index of the lesser end of the current link;
  /// the current item in the iteration.
  ///
  scoped_index _index;

  ///
  /// The index of the greater member of the current link
  ///
  mutable scoped_index _greater_index;

  ///
  /// The index of the lesser member of the current link.
  ///
  mutable scoped_index _lesser_index;

  ///
  /// The filter specified by the client.
  ///
  subposet _client_filter;

  ///
  /// True if this allocated a new filter;
  ///
  bool _new_filter;

  ///
  /// True if iterating over the up/down set of anchor.
  ///
  bool _descending;

  ///
  /// True if iterating over the strict up/down set of anchor
  ///
  bool _strict;

  ///
  /// The order of the iteration.
  ///
  order_type _order;

  ///
  /// The states for the finite state machine that controls iteration.
  ///
  enum iterator_state
  {
    FIRST,
    INIT_COVER_ITERATOR,
    TEST_HAS_VISITED,
    INC_COVER_ITERATOR,
    ERASE_COVER_ITERATOR,
    DESCEND,
    TEST_PATH_TAIL,
    ASCEND,
    EXECUTE_PREVISIT_ACTION,
    EXECUTE_LINK_ACTION,
    EXECUTE_POSTVISIT_ACTION,
    FINISH,
    NOT_A_STATE // Must be last; used for array bounds.
  };

  ///
  /// The input tokens for the finite state machine.
  ///
  enum iterator_token
  {
    PASS,
    FAIL
  };

  ///
  /// The names of the iterator states, convenient for debugging.
  ///
  static const char* iterator_state_names[NOT_A_STATE+1];

  ///
  /// The current state transition function for the iterator finite state machine.
  /// Points to one of the predefined transition functions.
  ///
  const iterator_state (*_transition_fcn)[FAIL+1];

  ///
  /// The predefined transition function for postorder iteration.
  /// Defines the next state for each combination of state and input token,
  /// except for state FINISH, which is always a terminal state.
  ///
  static const iterator_state PREORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1];

  ///
  /// The predefined transition function for postorder iteration.
  /// Defines the next state for each combination of state and input token,
  /// except for state FINISH, which is always a terminal state.
  ///
  static const iterator_state POSTORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1];

  ///
  /// The predefined transition function for linkorder iteration.
  /// Defines the next state for each combination of state and input token,
  /// except for state FINISH, which is always a terminal state.
  ///
  static const iterator_state LINKORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1];

  ///
  /// The predefined transition function for biorder iteration.
  /// Defines the next state for each combination of state and input token,
  /// except for state FINISH, which is always a terminal state.
  ///
  static const iterator_state BIORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1];

  ///
  /// The predefined transition function for triorder iteration.
  /// Defines the next state for each combination of state and input token,
  /// except for state FINISH, which is always a terminal state.
  ///
  static const iterator_state TRIORDER_TRANSITION_FCN[NOT_A_STATE-1][FAIL+1];

  typedef const iterator_state (*transition_fcn_type)[FAIL+1];

  ///
  /// The set of predefined transition functions.
  ///
  static const transition_fcn_type STD_TRANSITION_FCNS[NOT_AN_ORDER+1];

  ///
  /// The current state of iteration.
  ///
  iterator_state _state;

  ///
  /// The lower cover iterator for the head of the path
  /// to the current member of the iteration
  ///
  index_space_iterator* _path_head_lc;

  ///
  /// The head of the path to the current member of the iteration
  /// lesser_index() == this->index() == **_path_head == lesser member of current link
  ///
  index_space_iterator* _path_head;

  ///
  /// The tail of the path to the current member of the iteration
  /// greater_index() == **(_path_tail.top()) == greater member of current link
  ///	
  std::stack<index_space_iterator*> _path_tail;

  ///
  /// The tail of the filtered path to the current member of the iteration.
  /// Contains only members which pass the filter; equivalent to the path
  /// in the subposet selected by the filter.
  ///
  std::stack<pod_index_type> _filtered_path_tail;

  ///
  /// True if traversal should only visit a member once;
  /// that is, it should not revisit members it has already visited.
  ///
  bool _visit_once;

private:

  ///
  /// True if this has visited member in current iteration.
  /// Note that this object must be allocated on the heap because otherwise
  /// we would have to initialize it using the member initialization list,
  /// which would bypass the preconditions in the constructor.
  ///
  zn_to_bool* _has_visited;

  ///
  /// The filter; defined by what it passes, not what it blocks,
  /// i.e. the iterator will only return members of the down set of
  /// _anchor which are also members of _filter.
  /// For refined posets, the actual filter may not be identical
  /// to the client filter, see initialize_filter.
  ///
  zn_to_bool* _filter;

};

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_DEPTH_FIRST_ITERATOR_H
