
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
/// Interface for class depth_bound_refinement_policy

#ifndef DEPTH_BOUND_REFINEMENT_POLICY_H
#define DEPTH_BOUND_REFINEMENT_POLICY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_REFINEMENT_POLICY_H
#include "field_refinement_policy.h"
#endif

namespace fields
{

///
/// A policy that determines a zone should be refined if the
/// refinement depth is less than a given upper bound.
/// Intended mostly for use debugging the refinement machinery.
///
class SHEAF_DLL_SPEC depth_bound_refinement_policy : public field_refinement_policy
{

  // ===========================================================
  /// @name DEPTH_BOUND_REFINEMENT_POLICY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with refinement upper bound xrefinement_ub
  ///
  depth_bound_refinement_policy(size_type xrefinement_level_ub = 2);

  ///
  /// Copy constructor
  ///
  ///
  depth_bound_refinement_policy(const depth_bound_refinement_policy& xother);

  ///
  /// Destructor
  ///
  virtual ~depth_bound_refinement_policy();

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
  virtual const string& class_name() const;

  ///
  /// The class name of this class.
  ///
  static const string& static_class_name();

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
  virtual depth_bound_refinement_policy* clone() const;

  ///
  /// Assignment operator
  ///
  virtual depth_bound_refinement_policy& operator=(const field_refinement_policy& xother);

  ///
  /// Assignment operator
  ///
  ///
  depth_bound_refinement_policy& operator=(const depth_bound_refinement_policy& xother);

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

#endif // ifndef DEPTH_BOUND_REFINEMENT_POLICY_H
