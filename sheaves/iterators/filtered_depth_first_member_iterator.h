
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

// Interface for class filtered_depth_first_member_iterator

#ifndef FILTERED_DEPTH_FIRST_MEMBER_ITERATOR_H
#define FILTERED_DEPTH_FIRST_MEMBER_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_ITERATOR_H
#include "filtered_depth_first_iterator.h"
#endif

namespace sheaf
{

class subposet;
class zn_to_bool;  

///
/// @deprecated No replacement.
/// Iterates in postorder over the intersection of a subposet filter
/// with a directional (up or down) set of a poset member anchor.
/// Attaches an a handle of type abstract_poset_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC filtered_depth_first_member_iterator : public any
{

public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  filtered_depth_first_member_iterator(const filtered_depth_first_member_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual filtered_depth_first_member_iterator& operator=(const filtered_depth_first_member_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~filtered_depth_first_member_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual filtered_depth_first_member_iterator* clone() const = 0;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // SOME USEFUL CONSTANTS

  ///
  /// Iteration directions
  ///
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


  // ITERATOR FACET

  ///
  /// The order of the iteration. Determines which
  /// actions are exported to the client.
  ///
  depth_first_iterator::order_type order();

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  bool is_initialized() const;

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
  /// Set anchor() to *xanchor.
  ///
  virtual void put_anchor(const abstract_poset_member* xanchor);

  ///
  /// Set anchor() to member at xanchor_hub_id.
  ///
  virtual void put_anchor(pod_index_type xanchor_hub_id);

  ///
  /// Set anchor() to member at xanchor_id.
  ///
  void put_anchor(const scoped_index& xanchor_id);

  ///
  /// The subposet which is the filter;
  /// Defines what is passed, not what is blocked.
  ///
  const subposet& filter() const;

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(const subposet& filter);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(const std::string& xfilter_name);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(pod_index_type xfilter_hub_id);

  ///
  /// Sets the subposet which is the filter.
  ///
  void put_filter(const scoped_index& xfilter_id);

  ///
  /// True if iterating over down set of anchor
  ///
  bool descending() const;

  ///
  /// Set descending() to xdescending.
  ///
  void put_descending(bool xdescending);

  ///
  /// True if iterating over xstrict up/down set of anchor
  ///
  bool strict() const;

  ///
  /// Set strict() to xstrict.
  ///
  void put_strict(bool xstrict);

  ///
  /// True if iteration finished
  ///
  bool is_done() const;

  ///
  /// Makes this the next member of the iteration.
  ///
  virtual void next();

  ///
  /// Restarts the iteration.
  ///
  virtual void reset(bool xreset_markers = RESET);

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
  bool has_visited(const abstract_poset_member& xmbr) const;

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
  /// The index of the greater member of the current link
  ///
  const scoped_index& greater_index() const;

  ///
  /// The index of the lesser member of the current link
  /// lesser_index() == index()
  ///
  const scoped_index& lesser_index() const;

  // MEMBER ITERATOR FACET

  // Item is not virtual; descendant redefinitions
  // with covariant signature hide this version.

  ///
  /// The the current member of the iteration (mutable version).
  ///
  abstract_poset_member& item();

  ///
  /// The the current member of the iteration (const version).
  ///
  const abstract_poset_member& item() const;

  ///
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool item_is_ancestor_of(const abstract_poset_member& xmbr) const;

  ///
  /// True if xmbr conforms to the type of anchor of this.
  ///
  virtual bool anchor_is_ancestor_of(const abstract_poset_member& xmbr) const;


protected:

  ///
  /// Covariant constructor; supports virtual construction of data members.
  ///
  filtered_depth_first_member_iterator(filtered_depth_first_iterator* xitr,
                                       abstract_poset_member* xitem);

  ///
  /// Attaches the item handle to the current index,
  /// or detaches the item handle if is_done.
  ///
  virtual void update_item();

  ///
  /// The member handle for the current item in the iteration.
  ///
  abstract_poset_member* _item;

  ///
  /// The index iterator used to implement the iteration.
  ///
  filtered_depth_first_iterator* _iterator;

private:

  ///
  /// Default constructor; private to prevent default construction
  ///
  filtered_depth_first_member_iterator();

};

} // namespace sheaf

#endif // ifndef FILTERED_DEPTH_FIRST_MEMBER_ITERATOR_H
