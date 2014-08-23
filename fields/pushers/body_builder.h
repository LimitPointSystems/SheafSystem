
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
/// Interface for class body_builder

#ifndef COM_LIMITPOINT_FIELDS_BODY_BUILDER_H
#define COM_LIMITPOINT_FIELDS_BODY_BUILDER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELDS_H
#include "ComLimitPoint/fields/fields.h"
#endif

namespace sheaf
{
template <class T>
class block;
class subposet;
}

namespace fiber_bundle
{
class base_space_poset;
class section_evaluator;
}

namespace fields
{

class field_vd;

///
/// A simple body builder; creates base space members equivalent to
/// subsets defined by a field classification criterion.
///
class SHEAF_DLL_SPEC body_builder : public any
{

  // ===========================================================
  /// @name BODY_BUILDER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of local coordinate;
  /// the scalar type for the local coordinate vector space.
  ///
  typedef chart_point_coord_type coord_type;

  ///
  /// The type of component in the value;
  /// the scalar type in the fiber space.
  ///
  typedef sec_vd_value_type value_type;

  ///
  /// The type of degree of freedom.
  ///
  typedef sec_vd_dof_type dof_type;

  ///
  /// Default constructor.
  ///
  ///
  body_builder();

  // Copy constructor not implemented;
  // default memberwise copy will do.

  ///
  /// Destructor
  ///
  virtual ~body_builder();

  ///
  /// Builds the bodies defined by threshholds
  /// xlower and xupper in field xfield; auto_allocated.
  ///
  block<scoped_index>* build(field_vd& xfield,
			     value_type xlower,
			     value_type xupper);

  ///
  /// Builds the bodies defined by threshholds
  /// xlower and xupper in field xfield; pre_allocated.
  ///
  void build_pa(field_vd& xfield,
                value_type xlower,
                value_type xupper,
                block<scoped_index>& xresult);


private:

  ///
  /// Select the members of the evaluation subposet that
  /// satisfy the threshhold criterion.
  ///
  void select_evaluation_members(const field_vd& xfield,
                                 value_type xlower,
                                 value_type xupper,
                                 subposet& xselected);

  ///
  /// True if the field defined by xeval and xdofs falls
  /// within the interval defined by threshholds xlower and xupper.
  ///
  bool interval_contains_field(const section_evaluator& xeval,
                               const block<dof_type>& xdofs,
                               value_type xlower,
                               value_type xupper) const;

  ///
  /// Find the members of subposet xselected which form a
  /// contiguous neighborhood of the member with index xindex.
  ///
  void find_contiguous_neighborhood(const base_space_poset& xbase_space,
                                    subposet& xselected,
                                    const scoped_index& xindex,
                                    block<scoped_index>& xresult);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual body_builder* clone() const;

  // Assignment operator not implemented;
  // default memberwise assignment will do.

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

#endif // ifndef COM_LIMITPOINT_FIELDS_BODY_BUILDER_H
