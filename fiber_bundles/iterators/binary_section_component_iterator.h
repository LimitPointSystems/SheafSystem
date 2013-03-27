// $RCSfile: binary_section_component_iterator.h,v $ $Revision: 1.15 $ $Date: 2013/01/12 17:17:08 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class binary_section_component_iterator

#ifndef BINARY_SECTION_COMPONENT_ITERATOR_H
#define BINARY_SECTION_COMPONENT_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_COMPONENT_ITERATOR_H
#include "section_component_iterator.h"
#endif

namespace fiber_bundle
{

class binary_section_space_schema_member;

///
/// Iterates in postorder over dofs of a schema member anchor.
/// Attaches an a handle of type section_space_schema_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC binary_section_component_iterator : public section_component_iterator
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator.
  /// Protected because this class is abstract.
  ///
  binary_section_component_iterator();

  ///
  /// Copy constructor; attaches this to the same anchor as xother.
  /// Protected because this class is abstract.
  ///
  binary_section_component_iterator(const binary_section_component_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual binary_section_component_iterator& operator=(const section_component_iterator& xother);

  ///
  /// Assignment operator
  ///
  binary_section_component_iterator& operator=(const binary_section_component_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~binary_section_component_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual binary_section_component_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor.
  ///
  explicit binary_section_component_iterator(const binary_section_space_schema_member& xanchor);
  // Explicit above prevents interpretation as conversion from abstract_poset_meber

  // ITERATOR FACET

  // Anchor is not virtual; covariant signature hides
  // inherited version.

  ///
  /// The schema member whose downset is being iterated over;
  /// the top member of the domain of iteration.
  ///
  const binary_section_space_schema_member& anchor() const;

  // COMPONENT ITERATOR FACET

  // Item is not virtual; covariant signature hides
  // inherited version.

  ///
  /// The the current member of the iteration.
  ///
  const binary_section_space_schema_member& item() const;

  ///
  /// True if xmbr conforms to the type of item of this.
  ///
  virtual bool item_is_ancestor_of(const section_space_schema_member& xmbr) const;


protected:

  ///
  /// Creates item if needed and attaches it to the current index.
  /// Abstract in this class; intended to be redefined in descendants.
  ///
  virtual void reset_item();

};
 
} // namespace fiber_bundle

#endif // ifndef BINARY_SECTION_COMPONENT_ITERATOR_H
