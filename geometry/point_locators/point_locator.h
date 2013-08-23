
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
/// Interface for class point_locator

#ifndef POINT_LOCATOR_H
#define POINT_LOCATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

namespace fiber_bundle
{
class chart_point;
class sec_ed;
}

namespace geometry
{

using namespace sheaf;
using namespace fiber_bundle;  

///
/// An abstract point location query in domains with
/// global coordinate dimension dc and local coordinate dimension db.
///
class SHEAF_DLL_SPEC point_locator
{

  // ===========================================================
  /// @name CANONICAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Destructor.
  ///
  virtual ~point_locator();

  //@}


  // ===========================================================
  /// @name POINT_LOCATOR FACET
  // ===========================================================
  //@{

  ///
  /// The coordinate section this inverts.
  ///
  sec_ed& coordinates() const;

  ///
  ///  The lower bound of the domain defined by coordinates().
  ///
  const block<sec_vd_value_type>& lb() const;

  ///
  ///  The upper bound of the domain defined by coordinates().
  ///
  const block<sec_vd_value_type>& ub() const;

  ///
  /// The spatial dimension of the domain;
  /// the dimension of the global coordinates.
  ///
  int dc() const;

  ///
  /// The intrinsic dimension of the domain;
  /// the dimension of the local coordinates.
  ///
  int db() const;

  ///
  /// True if the domain contains xpt.
  ///
  bool domain_contains(sec_vd_value_type* xpt, size_type xpt_ub) const;

  ///
  /// Updates the search structure to the current values of coordinates().
  ///
  virtual void update() = 0;

  ///
  /// Finds a chart point at which coordinates() has value xvalue.
  ///
  virtual void point_at_value(const sec_vd_value_type* xvalue,
                              size_type xvalue_ub,
                              chart_point& xresult) = 0;

  ///
  /// Finds all chart points at which coordinates() has value xvalue
  /// and appends them to xresult.
  /// Note that charts overlap at their boundaries and hence if xvalue
  /// lies on a boundary it is contained in more than one chart.
  ///
  virtual void all_points_at_value(const sec_vd_value_type* xvalue,
                                   size_type xvalue_ub,
                                   block<chart_point_3d>& xresult) = 0;

  ///
  /// Finds one chart point in each branch at which coordinates()
  /// has value xvalue and appends them to xresult.
  ///
  virtual void branch_points_at_value(const sec_vd_value_type* xvalue,
                                      size_type xvalue_ub,
                                      block<branch_point_pair>& xresult) = 0;

protected:

  ///
  /// Default constructor.
  ///
  point_locator();

  ///
  ///  Create an instance for coordinate section xcoords.
  ///
  point_locator(sec_ed& xcoords);

  ///
  /// A value slightly greater then x.
  ///
  static sec_vd_value_type slightly_greater_than(sec_vd_value_type x);

  ///
  /// A value slightly less then x.
  ///
  static sec_vd_value_type slightly_less_than(sec_vd_value_type x);


  ///
  ///  The lower bound of the domain.
  ///
  block<sec_vd_value_type> _lb;

  ///
  ///  The upper bound of the domain.
  ///
  block<sec_vd_value_type> _ub;

  ///
  /// The spatial dimension of the domain;
  /// the dimension of the global coordinates.
  ///
  int _dc;

  ///
  /// The intrinsic dimension of the domain;
  /// the dimension of the local coordinates.
  ///
  int _db;

  ///
  /// Initializes the domain bounds and dimension.
  ///
  void update_domain();


private:

  ///
  /// Copy constructor; disabled.
  ///
  point_locator(const point_locator& xother);

  ///
  /// Assignment operator; disabled.
  ///
  virtual point_locator& operator=(const point_locator& xother);

  ///
  /// The coordinates section this inverts.
  ///
  sec_ed& _coordinates;

  //@}
};


///
/// Inserts point_locator& xpl in stream xos.
///
SHEAF_DLL_SPEC 
ostream&
operator<<(ostream& xos, const point_locator& xpl);
 
} // namespace geometry

#endif // POINT_LOCATOR_H
