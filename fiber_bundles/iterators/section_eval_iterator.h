
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class section_eval_iterator

#ifndef SECTION_EVAL_ITERATOR_H
#define SECTION_EVAL_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EVAL_ITERATOR_H
#include "eval_iterator.h"
#endif

#ifndef POSET_DOF_ITERATOR_H
#include "poset_dof_iterator.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h" // just to get typedefs
#endif

namespace sheaf
{
template <typename T>
class block;
}

namespace fiber_bundle
{

using namespace sheaf;


class section_evaluator;
class section_space_schema_member;

///
/// Iterates over the evaluation members of a section space schema anchor;
/// gathers the dof ids for each evaluation member.
///
class SHEAF_DLL_SPEC section_eval_iterator : public any
{

public:

  // CANONICAL MEMBERS

  ///
  /// Creates a new instance anchored at xanchor.
  ///
  section_eval_iterator(const section_space_schema_member& xanchor);

  ///
  /// Assignment operator
  ///
  virtual section_eval_iterator&
  operator=(const section_eval_iterator& xother);

  ///
  /// Copy constructor; attaches this to the same anchor as xother.
  ///
  section_eval_iterator(const section_eval_iterator& xother);

  ///
  /// Default constructor; creates an unattached iterator.
  ///
  section_eval_iterator();

  ///
  /// Destructor
  ///
  virtual ~section_eval_iterator();

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this.
  ///
  virtual section_eval_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

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
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool anchor_is_ancestor_of(const section_space_schema_member& xmbr) const;

  ///
  /// Restarts the iteration over the down set of anchor()
  /// If xreset_markers, set !has_visited for all members.
  ///
  virtual void reset(bool xreset_markers = RESET);

  ///
  /// Sets anchor to member with hub id xhub_id and restarts the iteration
  /// If xreset_markers, set !has_visited for all members.
  ///
  virtual void reset(pod_index_type xhub_id, bool xreset_markers = RESET);

  ///
  /// Sets anchor to member with id xid and restarts the iteration
  /// If xreset_markers, set !has_visited for all members.
  ///
  void reset(const scoped_index& xid, bool xreset_markers = RESET);

  ///
  /// Restarts iteration in schema xanchor.
  ///
  virtual void reset(const section_space_schema_member& xanchor);

  ///
  /// Restarts iteration at first component of current evaluator.
  ///
  virtual void reset_components();

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
  /// Set the visited marker for id xid to xvalue.
  /// Intended for use reseting iterator without having
  /// to reset entire collection of markers.
  ///
  void put_has_visited(const scoped_index& xid, bool xvalue);

  // SECTION_EVAL_ITERATOR FACET

  ///
  /// The id of the current evaluation member.
  ///
  const scoped_index& evaluator_id() const;

  ///
  /// The evaluator (local section) associated with the
  /// current evaluation member (mutable version).
  ///
  section_evaluator& evaluator();

  ///
  /// The evaluator (local section) associated with the
  /// current evaluation member (const version).
  ///
  const section_evaluator& evaluator() const;

  ///
  /// True if iteration over the evaluation set is finished.
  ///
  bool evaluators_done() const;

  ///
  /// Makes the next member of the evaluation set
  /// the current evaluation member.
  ///
  virtual void next_evaluator();

  ///
  /// True if iteration over fiber components is finished
  ///
  bool components_done() const;
  
  ///
  /// Makes the next fiber component
  /// the current fiber component.
  ///
  virtual void next_component();

  ///
  /// The ids of the discretization members in the down set of
  /// the current evaluation member (mutable version).
  ///
  block<scoped_index>& discretization_members();

  ///
  /// The ids of the discretization members in the down set of
  /// the current evaluation member (const version).
  ///
  const block<scoped_index>& discretization_members() const;

  ///
  /// The id of the fiber schema member associated with the current component.
  ///
  const scoped_index& fiber_id() const;
  
  ///
  /// Gathers the dofs for the current evalaution member from section xsec
  /// and appends them to the back of xdofs.
  ///
  void gather_dofs(const sec_vd& xsec, block<sec_vd::dof_type>& xdofs);

  ///
  /// Scatters the dofs for the current evalaution member from the
  /// location xindex and following of xdofs into section xsec.
  ///
  void scatter_dofs(sec_vd& xsec, const block<sec_vd::dof_type>& xdofs, size_type xindex);


protected:

  ///
  /// Creates anchor if needed and attaches it to xanchor.
  ///
  void reset_anchor(const section_space_schema_member& xanchor);

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration.
  ///
  section_space_schema_member* _anchor;

  ///
  /// The iterator for the fiber schema component.
  ///
  postorder_iterator _fiber_schema_itr;

  ///
  /// The iterator for the base space component.
  ///
  eval_iterator _evaluation_itr;

  //   ///
  ///   /// The ids of the fiber schema member corresponding to the current component.
  //   ///
  //   scoped_index _fiber_id;
};

} // namespace fiber_bundle

#endif // ifndef SECTION_EVAL_ITERATOR_H
