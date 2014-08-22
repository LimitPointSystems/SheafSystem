
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
/// Interface for class property_disc_iterator_1_2


#ifndef PROPERTY_DISC_ITERATOR_1_2_H
#define PROPERTY_DISC_ITERATOR_1_2_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef PROPERTY_DISC_ITERATOR_H
#include "ComLimitPoint/fields/property_disc_iterator.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BASE_SPACE_POSET_H
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_3D_H
#include "ComLimitPoint/fiber_bundle/chart_point_3d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_H
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_H
#include "ComLimitPoint/sheaf/zn_to_bool.h"
#endif

namespace fiber_bundle
{
class eval_family;
class section_space_schema_member;
class section_evaluator;
class sec_rep_descriptor;
class structured_block;
}

namespace fields
{

///
/// A property discretization iterator for a proerty section with
/// the same evaluation subposet as the coordinates section and with
/// the property evaluation strictly above the property discretization.
///
class SHEAF_DLL_SPEC property_disc_iterator_1_2 : public property_disc_iterator
{

  // ===========================================================
  /// @name PROPERTY_DISC_ITERATOR_1_2 FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an iterator over the schema of xfield.
  ///
  property_disc_iterator_1_2(const field_vd& xfield);

  ///
  /// Creates an iterator anchored at xcoordinate_schema.base_space().
  ///
  property_disc_iterator_1_2(
    const section_space_schema_member& xcoordinate_schema,
    const section_space_schema_member& xproperty_schema);

  ///
  /// Destructor.
  ///
  ~property_disc_iterator_1_2();

private:

  ///
  /// Default constructor; disabled.
  ///
  property_disc_iterator_1_2() {};

  ///
  /// Copy constructor; disabled.
  ///
  property_disc_iterator_1_2(const property_disc_iterator_1_2& xother) {};

  ///
  /// Coord eval previsit action.
  ///
  void coord_eval_previsit_action();

  ///
  /// Prop disc previsit action.
  ///
  void prop_disc_previsit_action();

  ///
  /// Coord disc previsit action.
  ///
  void coord_disc_previsit_action();

  ///
  /// Coord eval postvisit action.
  ///
  void coord_eval_postvisit_action();

  //@}


  // ===========================================================
  /// @name PROPERTY_DISC_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The gets the values of xsec at the property discretization points.
  ///
  virtual void get_prop_disc_values(const sec_vd& xsec);

  //@}


  // ===========================================================
  /// @name DEPTH_FIRST_ITERATOR FACET
  // ===========================================================
  //@{

public:

  using property_disc_iterator::next;

  ///
  /// Makes this the next member of the subset.
  /// If xtruncate, new this is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  ///
  virtual void next(bool xtruncate);

  ///
  /// Restarts the iteration.
  ///
  virtual void reset(bool xreset_markers = true);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual property_disc_iterator_1_2* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  //@}

};
  
} // namespace fields

#endif // ifndef PROPERTY_DISC_ITERATOR_1_2_H
