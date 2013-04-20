
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class zone_centered_refiner_family

#ifndef ZONE_CENTERED_REFINER_FAMILY_H
#define ZONE_CENTERED_REFINER_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_REFINER_FAMILY_H
#include "field_refiner_family.h"
#endif

namespace fields
{

///
/// A family of field refiners that introduce a new vertex in
/// the center of a zone, but not in the boundary of a zone.
///
class SHEAF_DLL_SPEC zone_centered_refiner_family : public field_refiner_family
{

  // ===========================================================
  /// @name ZONE_CENTERED_REFINER_FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance containing members for refining base space
  /// xbase_space and using policy xpolicy.
  ///
  zone_centered_refiner_family(const base_space_poset& xbase_space,
                               const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor
  ///
  ///
  zone_centered_refiner_family(const zone_centered_refiner_family& xother);

  ///
  /// Destructor
  ///
  virtual ~zone_centered_refiner_family();

  ///
  /// The name of this family.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class of families.
  ///
  static const string& static_class_name();

private:

  ///
  /// Default constructor; disabled.
  ///
  ///
  zone_centered_refiner_family();

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name FIELD_REFINER_FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Initializes this to contain members for base space
  /// xbase_space and using policy xpolicy.
  ///
  virtual void initialize(const base_space_poset& xbase_space,
                          const field_refinement_policy& xpolicy);

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
  virtual zone_centered_refiner_family* clone() const;

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
  
} // namespace fields

#endif // ifndef ZONE_CENTERED_REFINER_FAMILY_H






