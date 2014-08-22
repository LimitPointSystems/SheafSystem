
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
/// Interface for class filtered_depth_first_itr

#ifndef COM_LIMITPOINT_SHEAF_FILTERED_DEPTH_FIRST_ITR_H
#define COM_LIMITPOINT_SHEAF_FILTERED_DEPTH_FIRST_ITR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DEPTH_FIRST_ITR_H
#include "ComLimitPoint/sheaf/depth_first_itr.h"
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

/// @todo factor common features of filtered_depth_first_itr and postorder_itr
/// into common base class directional_iterator

///
/// The general depth-first iterator over the intersection of a subposet filter
/// with a directional (up or down) set of a poset member anchor. Implemented
/// as a finite state machine with a client selectable state transition function
/// that can be chosen to provide various iteration orders.<br>
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
/// This iterator visits every link in the cover relation graph above/below the anchor
/// of the iteration, maintaining a path to the current member. Conceptually, the path
/// is a list of pointers to lower cover iterators. The current member
/// of each iterator is a node in the path. Physically, the path is stored
/// in two parts. _index is the head of the list. The tail of the list is
/// stored in the variable _path. The current link in the graph is
/// the link between the front of _path and _index, with _index being the
/// lesser member of the link.
///

template <typename T>
class SHEAF_DLL_SPEC filtered_depth_first_itr : public depth_first_itr<T>
{
  // ===========================================================
  /// @name FILTERED_DEPTH_FIRST_ITR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  filtered_depth_first_itr();

  ///
  /// Copy constructor
  ///
  filtered_depth_first_itr(const filtered_depth_first_itr& xother);

  ///
  /// Assignment operator
  ///
  filtered_depth_first_itr& operator=(const filtered_depth_first_itr& xother);

  ///
  /// Destructor
  ///
  ~filtered_depth_first_itr();

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor, with no filter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  filtered_depth_first_itr(const abstract_poset_member& xanchor,
                           bool xdown,
                           bool xstrict,
                           typename depth_first_itr<T>::order_type xorder = depth_first_itr<T>::TRIORDER);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  filtered_depth_first_itr(const abstract_poset_member& xanchor,
                           const subposet& xfilter,
                           bool xdown,
                           bool xstrict,
                           typename depth_first_itr<T>::order_type xorder = depth_first_itr<T>::TRIORDER);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  filtered_depth_first_itr(const abstract_poset_member& xanchor,
                           pod_index_type xfilter_index,
                           bool xdown,
                           bool xstrict,
                           typename depth_first_itr<T>::order_type xorder = depth_first_itr<T>::TRIORDER);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  filtered_depth_first_itr(const abstract_poset_member& xanchor,
                           const scoped_index& xfilter_index,
                           bool xdown,
                           bool xstrict,
                           typename depth_first_itr<T>::order_type xorder = depth_first_itr<T>::TRIORDER);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_name.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  filtered_depth_first_itr(const abstract_poset_member& xanchor,
                           const std::string& xfilter_name,
                           bool xdown,
                           bool xstrict,
                           typename depth_first_itr<T>::order_type xorder = depth_first_itr<T>::TRIORDER);

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Set anchor() to xanchor.
  ///
  virtual void put_anchor(const abstract_poset_member* xanchor);

  ///
  /// Set anchor() to member identified by xanchor_index.
  ///
  virtual void put_anchor(pod_index_type xanchor_index);

  ///
  /// Set anchor() to member identified by xanchor_index.
  ///
  void put_anchor(const scoped_index& xanchor_index);

  ///
  /// Set descending() to xdescending.
  ///
  void put_descending(bool xdescending);

  ///
  /// Set strict() to xstrict.
  ///
  void put_strict(bool xstrict);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(const subposet& xfilter);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(const std::string& xfilter_name);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(pod_index_type xfilter_index);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(const scoped_index& xfilter_index);

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual filtered_depth_first_itr* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}
};
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_FILTERED_DEPTH_FIRST_ITR_H
