
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class section_dof_iterator

#ifndef SECTION_DOF_ITERATOR_H
#define SECTION_DOF_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_DOF_ITERATOR_H
#include "poset_dof_iterator.h"
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
/// Iterates in postorder over dofs of a schema member anchor.
/// Attaches an a handle of type section_space_schema_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC section_dof_iterator : public poset_dof_iterator
{

public:

  // CANONICAL MEMBERS

  ///
  /// Assignment operator
  ///
  virtual section_dof_iterator& operator=(const poset_dof_iterator& xother);

  ///
  /// Assignment operator
  ///
  section_dof_iterator& operator=(const section_dof_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~section_dof_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual section_dof_iterator* clone() const = 0;

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // OTHER CONSTRUCTORS

  // ITERATOR FACET

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  virtual bool is_initialized() const;

  // Anchor is not virtual; covariant signature hides
  // inherited version.

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

  using poset_dof_iterator::put_anchor;
  ///
  /// Set anchor() to xversion of *xanchor.
  ///
  virtual void put_anchor(const schema_poset_member* xanchor, int xversion);

  ///
  /// True if iteration finished
  ///
  virtual bool is_done() const;

  ///
  /// Force the iterator to be done.
  ///
  virtual void force_is_done();

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

  using poset_dof_iterator::has_visited;

  ///
  /// True if this has already visited hub id xhub_id.
  ///
  virtual bool has_visited(pod_index_type xhub_id) const;

  ///
  /// True if this has already visited xmbr.
  ///
  virtual bool has_visited(const schema_poset_member& xmbr) const;

  using poset_dof_iterator::put_has_visited;

  ///
  /// Set the visisted marker for hub id xhub_id to xvalue.
  /// Intended for use reseting iterator without having
  /// to reset entire collection of markers.
  ///
  virtual void put_has_visited(pod_index_type xhub_id, bool xvalue);

  // DOF ITERATOR FACET

  // Item is not virtual; descendant redefinitions
  // with covariant signature hide this version.

  ///
  /// The current member of the iteration (mutable version).
  ///
  section_space_schema_member& item();

  ///
  /// The current member of the iteration (const version).
  ///
  const section_space_schema_member& item() const;

  ///
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool item_is_ancestor_of(const schema_poset_member& xmbr) const;

protected:

  ///
  /// Default constructor; creates an unattached iterator.
  /// Protected because this class is abstract.
  ///
  section_dof_iterator();

  ///
  /// Copy constructor; attaches this to the same anchor as xother.
  /// Protected because this class is abstract.
  ///
  section_dof_iterator(const section_dof_iterator& xother);

  ///
  /// Creates item if needed and attaches it to the current index.
  /// Abstract in this class; intended to be redefined in descendants.
  ///
  virtual void reset_item() = 0;

  ///
  /// Attaches the item handle to the current index,
  /// or detaches the item handle if is_done.
  ///
  virtual void update_item() = 0;

  ///
  /// The discretization iterator
  ///
  depth_first_iterator* _discretization_itr;

};
 
} // namespace fiber_bundle

#endif // ifndef SECTION_DOF_ITERATOR_H
