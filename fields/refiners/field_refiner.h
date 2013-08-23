
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Interface for class field_refiner.

#ifndef FIELD_REFINER_H
#define FIELD_REFINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace sheaf
{
class poset;
}

namespace fiber_bundle
{
class sec_ed;
class sec_vd;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
 
class field_refinement_policy;
class field_refiner_family;
class field_vd;

///
/// Refines a given field and its base space using a
/// given refinement policy and refiner family.
///
class SHEAF_DLL_SPEC field_refiner : public any
{

  // ===========================================================
  /// @name FIELD_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for sections over base space xbase_space
  /// using the refiner family with name xrefiner_family_name and
  /// the policy with name xrefinement_policy_name.
  ///
  field_refiner(const poset& xbase_space,
                const string& xrefiner_family_name,
                const string& xrefinement_policy_name,
                bool xauto_access);

  ///
  /// The family of refiners for the range.
  ///
  field_refiner_family& refiners();

  ///
  /// The refinement policy of the refiners.
  ///
  field_refinement_policy& policy() const;

  ///
  /// Refines field xtarget.
  ///
  void refine(field_vd& xtarget, bool xauto_access);

  ///
  /// Refines field with coordinates xcoordinates and property xproperty.
  ///
  void refine(const sec_ed& xcoordinates, const sec_vd& xproperty, bool xauto_access);

protected:

  ///
  /// Default constructor; disabled.
  ///
  field_refiner();

private:

  ///
  /// The family of refiners for the range.
  ///
  field_refiner_family* _refiners;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Copy constructor.
  ///
  field_refiner(const field_refiner& xother);

  ///
  /// Destructor.
  ///
  virtual ~field_refiner();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef FIELD_REFINER_H
