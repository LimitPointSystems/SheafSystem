
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class property_disc_iterator_1_3


#ifndef PROPERTY_DISC_ITERATOR_1_3_H
#define PROPERTY_DISC_ITERATOR_1_3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PROPERTY_DISC_ITERATOR_H
#include "property_disc_iterator.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
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
/// A property discretization iterator for a property section with
/// the same evaluation subposet as the coordinates section and with
/// the property evaluation at or below the property discretization.
///
/// Since the prop disc is above the prop eval, we need to decide how
/// to associate a point with the prop disc member. We interpret this
/// construction as a method for saving memory when the same dof
/// or set of dofs is to be used for some collection of zones
/// and we let the zones assign the location of the dof, just
/// as for dofs below the eval subposet. Thus, when the disc is above
/// the eval, the disc member gets a location for each eval member.
/// Note that typically the zones are the maximal local members of
/// the base space lattice and hence there is no way to specify a
/// point on any larger objects, since they don't have local coords.
///
class SHEAF_DLL_SPEC property_disc_iterator_1_3 : public property_disc_iterator
{

  // ===========================================================
  /// @name PROPERTY_DISC_ITERATOR_1_3 FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an iterator over the schema of xfield.
  ///
  property_disc_iterator_1_3(const field_vd& xfield);

  ///
  /// Creates an iterator anchored at xcoordinate_schema.base_space().
  ///
  property_disc_iterator_1_3(
    const section_space_schema_member& xcoordinate_schema,
    const section_space_schema_member& xproperty_schema);

  ///
  /// Destructor.
  ///
  ~property_disc_iterator_1_3();

private:

  ///
  /// Default constructor; disabled.
  ///
  property_disc_iterator_1_3() {};

  ///
  /// Copy constructor; disabled.
  ///
  property_disc_iterator_1_3(const property_disc_iterator_1_3& xother) {};

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
  virtual property_disc_iterator_1_3* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  //@}

};

} // namespace fields

#endif // ifndef PROPERTY_DISC_ITERATOR_1_3_H
