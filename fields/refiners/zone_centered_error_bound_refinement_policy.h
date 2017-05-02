
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
/// Interface for class zone_centered_error_bound_refinement_policy

#ifndef ZONE_CENTERED_ERROR_BOUND_REFINEMENT_POLICY_H
#define ZONE_CENTERED_ERROR_BOUND_REFINEMENT_POLICY_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FIELD_REFINEMENT_POLICY_H
#include "SheafSystem/field_refinement_policy.h"
#endif

namespace fields
{

using namespace fiber_bundle;

///
/// A policy that determines a zone should be refined if the
/// error with respect to the source field at the zone center
/// exceeds a given upper bound.
///
class SHEAF_DLL_SPEC zone_centered_error_bound_refinement_policy : public field_refinement_policy
{

  // ===========================================================
  /// @name ZONE_CENTERED_ERROR_BOUND_REFINEMENT_POLICY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with refinement bound xrefinement_ub
  /// and error bound xerror_ub.
  ///
  zone_centered_error_bound_refinement_policy(size_type xrefinement_depth_ub = 2,
      sec_vd_value_type xerror_ub = 0.01);

  ///
  /// Copy constructor
  ///
  zone_centered_error_bound_refinement_policy(const zone_centered_error_bound_refinement_policy& xother);

  ///
  /// Destructor
  ///
  virtual ~zone_centered_error_bound_refinement_policy();

  ///
  /// The upper bound on the error at the center of a cell.
  ///
  sec_vd_value_type error_ub() const;

  ///
  /// Sets error_ub to xub.
  ///
  void put_error_ub(sec_vd_value_type xub);


protected:

  ///
  /// The upper bound on the error.
  ///
  sec_vd_value_type _error_ub;

private:

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
  /// @name FIELD_REFINEMENT_POLICY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the zone specified by xzone_id should be refined.
  ///
  virtual bool should_refine(field_refinement_buffer& xbuffer,
                             size_type xrefinement_depth) const;

  ///
  /// The class name of this.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The class name of this class.
  ///
  static const std::string& static_class_name();

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual zone_centered_error_bound_refinement_policy* clone() const;

  ///
  /// Assignment operator
  ///
  virtual zone_centered_error_bound_refinement_policy& operator=(const field_refinement_policy& xother);

  ///
  /// Assignment operator
  ///
  zone_centered_error_bound_refinement_policy& operator=(const zone_centered_error_bound_refinement_policy& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace fields

#endif // ifndef ZONE_CENTERED_ERROR_BOUND_REFINEMENT_POLICY_H
