
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
/// Interface for class d_uniform_point_locator

#ifndef D_UNIFORM_POINT_LOCATOR_H
#define D_UNIFORM_POINT_LOCATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef POINT_LOCATOR_H
#include "SheafSystem/point_locator.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace fiber_bundle
{
class section_evaluator;
class structured_block;
}

namespace geometry
{

///
/// A point location query in domains with uniform
/// global coordinates of dimension dc and local coordinate dimension db.
///
template <int DC, int DB>
class SHEAF_DLL_SPEC d_uniform_point_locator : public point_locator
{

  // ===========================================================
  /// @name D_UNIFORM_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for coordinate section xcoords.
  ///
  d_uniform_point_locator(sec_ed& xcoords);

  ///
  /// Destructor.
  ///
  virtual ~d_uniform_point_locator();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;


protected:

  ///
  /// Default constructor; disabled.
  ///
  d_uniform_point_locator() {};

  ///
  /// Copy constructor; disabled
  ///
  d_uniform_point_locator(const d_uniform_point_locator<DC, DB>& xother) {};

  ///
  /// Assignment operator; disabled.
  ///
    virtual d_uniform_point_locator& operator=(const point_locator& xother) {return *this;};

  ///
  /// Assignment operator; disabled.
  ///
      d_uniform_point_locator& operator=(const d_uniform_point_locator<DC, DB>& xother) {return *this;};

  ///
  /// Buffer for clipped value.
  ///
  sec_vd_value_type _clipped_value[DC];

  ///
  /// Base space of coordinates.
  ///
  structured_block* _block;

  ///
  /// Point in local coordinates of block.
  ///
  chart_point* _block_pt;

  ///
  /// The dof tuple of coordinates().
  ///
  sec_vd_dof_type* _dofs;

  ///
  /// The number of dofs in the dof tuple of coordinates().
  ///
  size_type _dof_ct;

  ///
  /// Evaluator for coordinates.
  ///
  section_evaluator* _evaluator;

  ///
  /// Ensures that xcomp is strictly less than xupper_bound.
  ///
  sec_vd_value_type clip_component(sec_vd_value_type xcomp,
                                   sec_vd_value_type xupper_bound);

  //@}


  // ===========================================================
  /// @name POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Updates the search structure to the current values of coordinates().
  ///
  virtual void update();

  ///
  /// Finds the chart point at which coordinates() has value xvalue.
  ///
  virtual void point_at_value(const sec_vd_value_type* xvalue,
                              size_type xvalue_ub,
                              chart_point& xresult);

  ///
  /// Finds all chart points at which coordinates() has value xvalue
  /// and appends them to xresult.
  /// Note that charts overlap at their boundaries and hence if xvalue
  /// lies on a boundary it is contained in more than one chart.
  ///
  virtual void all_points_at_value(const sec_vd_value_type* xvalue,
                                   size_type xvalue_ub,
                                   block<chart_point_3d>& xresult);

  ///
  /// Finds one chart point in each branch at which coordinates()
  /// has value xvalue and appends them to xresult.
  /// Note that uniform sections can't really have branches,
  /// so this is just a synonym for point_at_value.
  ///
  virtual void branch_points_at_value(const sec_vd_value_type* xvalue,
                                      size_type xvalue_ub,
                                      block<branch_point_pair>& xresult);

  //@}

};


// ============================================================================
// SPECIALIZATIONS
// ============================================================================

template <>
SHEAF_DLL_SPEC
d_uniform_point_locator<1, 1>::
d_uniform_point_locator(sec_ed& xcoords);

template <>
SHEAF_DLL_SPEC
d_uniform_point_locator<2, 2>::
d_uniform_point_locator(sec_ed& xcoords);

template <>
SHEAF_DLL_SPEC
d_uniform_point_locator<3, 3>::
d_uniform_point_locator(sec_ed& xcoords);

} // namespace geometry

#endif // D_UNIFORM_POINT_LOCATOR_H
