// $RCSfile: edge_centered_refiner_family.h,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:28 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class edge_centered_refiner_family

#ifndef EDGE_CENTERED_REFINER_FAMILY_H
#define EDGE_CENTERED_REFINER_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_REFINER_FAMILY_H
#include "field_refiner_family.h"
#endif

namespace fields
{

///
/// A family of field refiners that introduce a new vertex
/// in each edge, but avoid introducing new vertices in the
/// center of the zone whenever possible.
//// @hack basically barycentric_refiner_family with
//// barycentric_triangle_refiner replaced with edge_centered_triangle_refiner.
////
class SHEAF_DLL_SPEC edge_centered_refiner_family : public field_refiner_family
{

  // ===========================================================
  /// @name EDGE_CENTERED_REFINER_FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance containing members for refining base space
  /// xbase_space and using policy xpolicy.
  ///
  edge_centered_refiner_family(const base_space_poset& xbase_space,
                               const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor
  ///
  edge_centered_refiner_family(const edge_centered_refiner_family& xother);

  ///
  /// Destructor
  ///
  virtual ~edge_centered_refiner_family();

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
  edge_centered_refiner_family();

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
  virtual edge_centered_refiner_family* clone() const;

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

#endif // ifndef EDGE_CENTERED_REFINER_FAMILY_H






