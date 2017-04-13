
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class barycentric_refiner_family

#ifndef BARYCENTRIC_REFINER_FAMILY_H
#define BARYCENTRIC_REFINER_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FIELD_REFINER_FAMILY_H
#include "SheafSystem/field_refiner_family.h"
#endif

namespace fields
{

///
/// A family of field refiners that introduce a new vertex in
/// in the barycenter of each cell (zone, face, edge, vertex)
/// in the down set of a zone.
///
class SHEAF_DLL_SPEC barycentric_refiner_family : public field_refiner_family
{

  // ===========================================================
  /// @name BARYCENTRIC_REFINER_FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance containing members for refining base space
  /// xbase_space and using policy xpolicy.
  ///
  barycentric_refiner_family(const base_space_poset& xbase_space,
                             const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor
  ///
  ///
  barycentric_refiner_family(const barycentric_refiner_family& xother);

  ///
  /// Destructor
  ///
  virtual ~barycentric_refiner_family();

  ///
  /// The name of this family.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class of families.
  ///
  static const std::string& static_class_name();

private:

  ///
  /// Default constructor; disabled.
  ///
  ///
  barycentric_refiner_family();

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
  virtual barycentric_refiner_family* clone() const;

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

#endif // ifndef BARYCENTRIC_REFINER_FAMILY_H






