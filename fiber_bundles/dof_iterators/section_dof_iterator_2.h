// $RCSfile: section_dof_iterator_2.h,v $ $Revision: 1.2 $ $Date: 2013/01/10 13:54:23 $

//
// Copyright (c) 2011 Limit Point Systems, Inc.
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
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  section_space_schema_member& anchor();

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  const section_space_schema_member& anchor() const;

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
  /// Creates an iterator over the table dofs (xis_table_dof == true)
  /// or rows dofs (xis_table_dof = false) of refinemement level xversion
  /// of schema xanchor.
  /// "Explicit" prevents interpretation as conversion from section_space_schema_member
  ///
  explicit section_dof_iterator(const section_space_schema_member& xanchor,
				bool xis_table_dof = false,
				int xversion = ANCHOR_VERSION);

  ///
  /// Creates item if needed and attaches it to the current index.
  /// Abstract in this class; intended to be redefined in descendants.
  ///
  virtual void reset_item() = 0;

};
 
} // namespace fiber_bundle

#endif // ifndef SECTION_DOF_ITERATOR_H
