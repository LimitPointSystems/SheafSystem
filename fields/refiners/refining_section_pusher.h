
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
/// Interface for class refining_section_pusher.

#ifndef REFINING_SECTION_PUSHER_H
#define REFINING_SECTION_PUSHER_H

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
/// A refining section push-forward operator. Moves sections from
/// one sec_rep_space to another using extension by zero to define
/// the target outside the domain of the source. Refines the base
/// of the target as specfied by a given refinement policy.
///
class SHEAF_DLL_SPEC refining_section_pusher : public any
{

  // =============================================================================
  /// @name REFINING_SECTION_PUSHER FACET
  // =============================================================================
  //@{

public:

  ///
  /// Creates an instance for sections over base space xbase_space
  /// using the refiner family with name xrefiner_family_name and
  /// the policy with name xrefinement_policy_name.
  ///
  refining_section_pusher(const poset& xbase_space,
                          const std::string& xrefiner_family_name,
                          const std::string& xrefinement_policy_name,
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
  /// Pushes field xsource to field xtarget, pre-allocated.
  ///
  void push(const field_vd& xsource, field_vd& xtarget, bool xauto_access);

  ///
  /// True if and only if x1 and x2 have the same fiber type and dimension.
  ///
  bool same_fiber(const sec_vd& x1, const sec_vd& x2) const;

protected:

  ///
  /// Default constructor; disabled.
  ///
  refining_section_pusher();

private:

  ///
  /// The family of refiners for the range.
  ///
  field_refiner_family* _refiners;

  //@}


  // =============================================================================
  /// @name ANY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Copy constructor.
  ///
  refining_section_pusher(const refining_section_pusher& xother);

  ///
  /// Destructor.
  ///
  virtual ~refining_section_pusher();

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

#endif // ifndef REFINING_SECTION_PUSHER_H
