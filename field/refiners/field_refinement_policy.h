
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
/// Interface for class field_refinement_policy

#ifndef FIELD_REFINEMENT_POLICY_H
#define FIELD_REFINEMENT_POLICY_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace sheaf
{
template <class T>
class factory;
}

namespace fields
{

using namespace sheaf;
  
class field_refinement_buffer;

///
/// An abstract policy that determines the conditions under which
/// a zone should be refined.
///
class SHEAF_DLL_SPEC field_refinement_policy : public any
{

  // ===========================================================
  /// @name FIELD_REFINEMENT_POLICY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~field_refinement_policy();

  ///
  /// True if the zone specified by xzone_id should be refined.
  ///
  virtual bool should_refine(field_refinement_buffer& xbuffer,
                             size_type xrefinement_depth) const = 0;

  ///
  /// The upper bound on the refinement depth of a cell.
  /// A cell will not be refined if its refinement depth
  /// is equal to or greater than the upper bound.
  ///
  size_type refinement_depth_ub() const;

  ///
  /// Set the refinement depth upper bound to xub.
  ///
  void put_refinement_depth_ub(size_type xub);

  ///
  /// The class name of this.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The class name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// Creates an instance of the policy with class name xname.
  ///
  static field_refinement_policy* new_policy(const std::string& xname);

  ///
  /// A factory for making policy objects.
  ///
  static factory<field_refinement_policy>& policy_factory();

protected:

  ///
  /// Creates an instance with reinement upper bound xrefinement_ub.
  ///
  ///
  field_refinement_policy(size_type xrefinement_depth_ub);

  ///
  /// Copy constructor
  ///
  ///
  field_refinement_policy(const field_refinement_policy& xother);

  ///
  /// The upper bound and the refinement level of a cell.
  ///
  size_type _refinement_depth_ub;

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
  virtual field_refinement_policy* clone() const = 0;

  ///
  /// Assignment operator
  ///
  ///
  virtual field_refinement_policy& operator=(const field_refinement_policy& xother);

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

#endif // ifndef FIELD_REFINEMENT_POLICY_H
