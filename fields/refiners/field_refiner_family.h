
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_refiner_family

#ifndef FIELD_REFINER_FAMILY_H
#define FIELD_REFINER_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
template <class T>
class factory;
class index_space_handle;
class namespace_poset;
}

namespace fiber_bundle
{
class base_space_poset;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;

class field_refinement_policy;
class local_field_refiner;
class field_refiner_family_factory;


///
/// A family of compatible local_field_refiners, one for
/// each member of some family of cell types;
/// a map from cell type to field_type.
///
class SHEAF_DLL_SPEC field_refiner_family : public any
{

  // ===========================================================
  /// @name FIELD_REFINER_FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance of the refiner family associated with
  /// name xname.
  ///
  static field_refiner_family* new_family(const string& xname);

  ///
  /// Copy constructor
  ///
  ///
  field_refiner_family(const field_refiner_family& xother);

  ///
  /// Destructor
  ///
  virtual ~field_refiner_family();

  ///
  /// The name of this family.
  ///
  virtual const string& class_name() const = 0;

  ///
  /// The evaluator associated with cell type xtype_id.
  /// Note that the result may be void.
  ///
  local_field_refiner* member(pod_index_type xtype_id) const;

  ///
  /// The number of members of this family.
  ///
  size_type size() const;

  ///
  /// The refinement policy for this family.
  ///
  field_refinement_policy& policy() const;

  ///
  /// A factory for making field_refiner_family objects.
  ///
  static factory<field_refiner_family>& family_factory();

  ///
  /// Initializes this to contain members for base space
  /// xbase_space and using policy xpolicy.
  ///
  virtual void initialize(const base_space_poset& xbase_space,
                          const field_refinement_policy& xpolicy) = 0;

  ///
  /// True if this has been populated with members.
  ///
  bool is_initialized() const;

protected:

  ///
  /// Default constructor.
  ///
  field_refiner_family();

  ///
  /// The members of the family.
  ///
  block<local_field_refiner*> _members;

  ///
  /// The refinement policy for this family.
  ///
  field_refinement_policy* _policy;

  ///
  /// The id space for base space cell type ids.
  ///
  index_space_handle* _cell_type_id_space;

  ///
  /// True if this has been populated with members.
  ///
  bool _is_initialized;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual field_refiner_family* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef FIELD_REFINER_FAMILY_H






