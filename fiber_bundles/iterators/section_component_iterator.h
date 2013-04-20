
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class section_component_iterator

#ifndef SECTION_COMPONENT_ITERATOR_H
#define SECTION_COMPONENT_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef POSTORDER_ITERATOR_H
#include "postorder_iterator.h"
#endif

namespace sheaf
{
class subposet;
class zn_to_bool;
}

namespace fiber_bundle
{

using namespace sheaf;

class section_space_schema_member;

///
/// Iterates in postorder over components of a section_space_schema_member anchor.
/// The components of a section_space_schema_member m are those members m' <= m
/// such that m'.base_space().is_same_state(m.base_space()) and m'.fiber_schema().is_component().
/// Attaches an a handle of type section_space_schema_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC section_component_iterator : public any
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  section_component_iterator();

  ///
  /// Copy constructor
  ///
  section_component_iterator(const section_component_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual section_component_iterator& operator=(const section_component_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~section_component_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual section_component_iterator* clone() const = 0;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor.
  ///
  explicit section_component_iterator(const section_space_schema_member& xanchor);
  // Explicit above prevents interpretation as conversion from section_space_schema_meber

  // ITERATOR FACET

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  bool is_initialized() const;

  // Anchor is not virtual; descendant redefinitions
  // with covariant signature hide this version.

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  section_space_schema_member& anchor();

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  const section_space_schema_member& anchor() const;

  ///
  /// Sets anchor to member xanchor.
  ///
  void put_anchor(const section_space_schema_member* xanchor);

  ///
  /// True if iteration finished
  ///
  bool is_done() const;

  ///
  /// Makes this the next member of the subset.
  ///
  virtual void next();

  ///
  /// Restarts the iteration over the down set of anchor()
  /// If xreset_markers, set !has_visited for all members.
  ///
  virtual void reset(bool xreset_markers = RESET);

  ///
  /// The number of members of the iteration set, from the current member to
  /// the end, inclusive. If xreset, reset before computing the count.
  ///
  virtual int ct(bool xreset = false);

  ///
  /// True if this has already visited hub id xhub_id.
  ///
  virtual bool has_visited(pod_index_type xhub_id) const;

  ///
  /// True if this has already visited id xid.
  ///
  bool has_visited(const scoped_index& xid) const;

  ///
  /// True if this has already visited xmbr.
  ///
  virtual bool has_visited(const section_space_schema_member& xmbr) const;

  ///
  /// Set the visited marker for hub id xhub_id to xvalue.
  /// Intended for use reseting iterator without having
  /// to reset entire collection of markers.
  ///
  virtual void put_has_visited(pod_index_type xhub_id, bool xvalue);

  ///
  /// Set the visisted marker for id xid to xvalue.
  /// Intended for use reseting iterator without having
  /// to reset entire collection of markers.
  ///
  void put_has_visited(const scoped_index& xid, bool xvalue);

  // DOF ITERATOR FACET

  // Item is not virtual; descendant redefinitions
  // with covariant signature hide this version.

  ///
  /// The the current member of the iteration (mutable version).
  ///
  section_space_schema_member& item();

  ///
  /// The the current member of the iteration (const version).
  ///
  const section_space_schema_member& item() const;

  ///
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool item_is_ancestor_of(const section_space_schema_member& xmbr) const;

  ///
  /// The index of the current member of the iteration.
  ///
  virtual const scoped_index& index() const;

protected:

  ///
  /// Creates anchor if needed and attaches it to xanchor.
  /// Abstract in this class; intended to be redefined in descendants.
  ///
  virtual void reset_anchor(const section_space_schema_member& xanchor);

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration.
  ///
  section_space_schema_member* _anchor;

  ///
  /// Creates item if needed and attaches it to the current index.
  ///
  virtual void reset_item() = 0;

  ///
  /// Attaches the item handle to the current index,
  /// or detaches the item handle if is_done.
  ///
  virtual void update_item();

  ///
  /// The member handle for the current item in the iteration.
  ///
  section_space_schema_member* _item;

  ///
  /// The index iterator used to implement the iteration.
  ///
  postorder_iterator _itr;

};

} // namespace fiber_bundle

#endif // ifndef SECTION_COMPONENT_ITERATOR_H
