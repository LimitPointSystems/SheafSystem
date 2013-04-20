
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class binary_section_dof_iterator

#ifndef BINARY_SECTION_DOF_ITERATOR_H
#define BINARY_SECTION_DOF_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_DOF_ITERATOR_H
#include "section_dof_iterator.h"
#endif

namespace fiber_bundle
{

class binary_section_space_schema_member;

///
/// Iterates in postorder over dofs of a schema member anchor.
/// Attaches an a handle of type section_space_schema_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC binary_section_dof_iterator : public section_dof_iterator
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator.
  /// Protected because this class is abstract.
  ///
  binary_section_dof_iterator();

  ///
  /// Copy constructor; attaches this to the same anchor as xother.
  /// Protected because this class is abstract.
  ///
  binary_section_dof_iterator(const binary_section_dof_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual binary_section_dof_iterator& operator=(const poset_dof_iterator& xother);

  ///
  /// Assignment operator
  ///
  binary_section_dof_iterator& operator=(const binary_section_dof_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~binary_section_dof_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual binary_section_dof_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator over the table dofs (xis_table_dof == true)
  /// or rows dofs (xis_table_dof = false) of refinemement level xversion
  /// of schema xanchor.
  /// "Explicit" prevents interpretation as conversion from binary_section_space_schema_member
  ///
  explicit binary_section_dof_iterator(const binary_section_space_schema_member& xanchor,
                                       bool xis_table_dof = false,
                                       int xversion = ANCHOR_VERSION);

  // ITERATOR FACET

  // Anchor is not virtual; covariant signature hides
  // inherited version.

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  binary_section_space_schema_member& anchor();

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  const binary_section_space_schema_member& anchor() const;

  // DOF ITERATOR FACET

  // Item is not virtual; covariant signature hides
  // inherited version.

  ///
  /// The the current member of the iteration (mutable version).
  ///
  binary_section_space_schema_member& item();

  ///
  /// The the current member of the iteration (const version).
  ///
  const binary_section_space_schema_member& item() const;

  ///
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool item_is_ancestor_of(const schema_poset_member& xmbr) const;

protected:

  ///
  /// Creates item if needed and attaches it to the current index.
  /// Abstract in this class; intended to be redefined in descendants.
  ///
  virtual void reset_item();

  ///
  /// Attaches the item handle to the current index,
  /// or detaches the item handle if is_done.
  ///
  virtual void update_item();

  ///
  /// Initializes the iteration.
  ///
  void initialize(const binary_section_space_schema_member& xanchor,
                  bool xis_table_dof,
                  int xversion);

};

} // namespace fiber_bundle

#endif // ifndef BINARY_SECTION_DOF_ITERATOR_H
