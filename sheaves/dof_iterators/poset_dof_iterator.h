
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//

// Interface for class poset_dof_iterator

#ifndef POSET_DOF_ITERATOR_H
#define POSET_DOF_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POSTORDER_ITERATOR_H
#include "postorder_iterator.h"
#endif

namespace sheaf
{

class subposet;
class schema_poset_member;
class zn_to_bool;
  
///
/// Iterates in postorder over dofs of a schema member anchor.
/// Attaches a handle of type schema_poset_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC poset_dof_iterator : public any
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  poset_dof_iterator();

  ///
  /// Copy constructor
  ///
  poset_dof_iterator(const poset_dof_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual poset_dof_iterator& operator=(const poset_dof_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~poset_dof_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual poset_dof_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // SOME USEFUL CONSTANTS


  ///
  /// Identifiers for anchor version.
  ///
  enum anchor_version_index
  {
    ANCHOR_VERSION = CURRENT_MEMBER_VERSION,
    ANCHOR_HOST_VERSION = CURRENT_HOST_VERSION
  };

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator over the table dofs (is_table_dof true) or
  /// row dofs (xis_table_dof false) of version xversion
  /// in schema xanchor.
  /// "Explicit" prevents interpretation as conversion from schema_poset_member.
  ///
  explicit poset_dof_iterator(const schema_poset_member& xanchor,
                              bool xis_table_dof = false,
                              int xversion = ANCHOR_VERSION);

  // ITERATOR FACET

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  virtual bool is_initialized() const;

  // Anchor is not virtual; descendant redefinitions
  // with covariant signature hide this version.

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  schema_poset_member& anchor();

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  const schema_poset_member& anchor() const;

  ///
  /// Set anchor() to xversion of *xanchor.
  /// Forces reset of markers, since the host may be different.
  ///
  virtual void put_anchor(const schema_poset_member* xanchor, int xversion);

  ///
  /// Set anchor() to the member with hub id xhub_id in host().
  /// Does not change version; does not force reset of markers.
  ///
  virtual void put_anchor(pod_index_type xindex);

  ///
  /// Set anchor() to the member with id xid in host().
  /// Does not change version; does not force reset of markers.
  ///
  void put_anchor(const scoped_index& xid);

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

  ///
  /// True if this has already visited hub id xhub_id.
  ///
  virtual bool has_visited(pod_index_type xhub_id) const;

  ///
  /// True if this has already visited id xid.
  ///
  bool has_visited(const scoped_index& xindex) const;

  ///
  /// True if this has already visited xmbr.
  ///
  virtual bool has_visited(const schema_poset_member& xmbr) const;

  ///
  /// Set the visisted marker for hub id xhub_id to xvalue.
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
  /// The current member of the iteration (mutable version).
  ///
  schema_poset_member& item();

  ///
  /// The current member of the iteration (const version).
  ///
  const schema_poset_member& item() const;

  ///
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool item_is_ancestor_of(const schema_poset_member& xmbr) const;

  ///
  /// The index of the current member of the iteration.
  ///
  virtual const scoped_index& index();

  ///
  /// True if iterating over table dofs.
  ///
  bool is_table_dof() const;

protected:

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration.
  ///
  schema_poset_member* _anchor;

  ///
  /// Creates item if needed and attaches it to the current index.
  ///
  virtual void reset_item();

  ///
  /// Attaches the item handle to the current index,
  /// or detaches the item handle if is_done.
  ///
  virtual void update_item();

  ///
  /// The member handle for the current item in the iteration.
  ///
  schema_poset_member* _item;

  ///
  /// The index iterator used to implement the iteration.
  ///
  postorder_iterator _itr;

  ///
  /// True if iterating over table dofs.
  ///
  bool _is_table_dof;
};

} // namespace sheaf

#endif // ifndef POSET_DOF_ITERATOR_H
