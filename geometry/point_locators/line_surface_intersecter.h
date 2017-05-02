
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
/// Interface for class line_surface_intersecter

#ifndef LINE_SURFACE_INTERSECTER_H
#define LINE_SURFACE_INTERSECTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "SheafSystem/any.h"
#endif

#ifndef CHART_POINT_1D_H
#include "SheafSystem/chart_point_1d.h"
#endif

#ifndef D_ARRAY_POINT_LOCATOR_H
#include "SheafSystem/d_array_point_locator.h"
#endif
 
#ifndef E3_H
#include "SheafSystem/e3.h"
#endif

#ifndef GEOMETRY_H
#include "SheafSystem/geometry.h"
#endif
 
#ifndef LINEAR_2D_H
#include "SheafSystem/linear_2d.h"
#endif  

#ifndef STD_IOSTREAM_H
#include "SheafSystem/std_iostream.h"
#endif

#ifndef STD_MAP_H
#include "SheafSystem/std_map.h"
#endif
  
namespace sheaf
{
  class subposet;
}

namespace fiber_bundle
{
  class sec_e3;
  class base_space_poset;
}

namespace geometry
{
  
///
/// A line-surface intersection query.
/// @hack Currently implemented only for lines aligned with
/// the z axis and for triangle meshes.
///
class SHEAF_DLL_SPEC line_surface_intersecter : public any
{

  friend SHEAF_DLL_SPEC std::ostream & operator << (std::ostream &os, const line_surface_intersecter& xp);

  // ===========================================================
  /// @name LINE_SURFACE_INTERSECTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an intersector with surfaces defined by 
  /// coordinate section xcoords. Allocates a
  /// search structure with bin index upper bounds xbin_ubs.
  ///
  line_surface_intersecter(sec_e3& xcoords, const block<size_type>& xbin_ubs);

  ///
  /// Copy constructor
  ///
  line_surface_intersecter(const line_surface_intersecter& xother);

  ///
  /// Destructor
  ///
  virtual ~line_surface_intersecter();

  ///
  /// The section space containing the surfaces.
  ///
  const sec_e3& coords() const;  

  ///
  /// Compare functor makes sure surface values are really different.
  ///
  struct really_less_than
  {
    bool operator()(sec_vd_value_type x1, sec_vd_value_type x2) const
    {
      return (x2 - x1) > (std::abs(x1) + std::abs(x2))*1.0e-6;
    }
  };

  ///
  /// The type of intersetion set, a 
  /// map from z coordinate to surface id;
  /// sorted by z coordinate.
  ///
  typedef std::map<sec_vd_value_type, pod_index_type, really_less_than> intersection_set_type;

  ///
  /// The type of search structure box
  ///
  typedef d_bounding_box<3,2> box_type;
  
  ///
  /// Computes the intersections of the line passing 
  /// through points xp0 and xp1 with the surfaces defined by coords().
  ///
  void intersect(const e3_lite& xp0, const e3_lite& xp1, intersection_set_type& xresult) const;

protected:

  ///
  /// Default constructor; disabled.
  ///
  line_surface_intersecter();

  ///
  /// The coordinate section for lines.
  ///
  sec_e3* _coords;

  ///
  /// The base space.
  ///
  base_space_poset* _host;

  ///
  /// The surface id space.
  ///
  index_space_handle* _surface_id_space;

  ///
  /// The id space for surface evaluators.
  ///
  index_space_handle* _eval_id_space;

  /// @hack Only z-axis aligned lines and triangles

  ///
  /// The evaluator for surface sections; temporarily assumes triangle.
  ///
  linear_2d _evaluator;

  ///
  /// The type of collision search structure.
  ///
  typedef d_array_point_locator<3, 2> search_structure_type;
  
  ///
  /// The type of search structure box set
  ///
  typedef search_structure_type::box_set_type box_set_type;

  ///
  /// The intersection search structure.
  ///
  search_structure_type* _locator;

  ///
  /// Computes the intersection xr of the line passing 
  /// through points xp0 and xp1 with the surface
  /// evaluator contained in xbox.
  ///
  bool intersect(const e3_lite& xp0, const e3_lite& xp1, const d_bounding_box<3, 2>& xbox, e3_lite& xr) const;

private:

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
  virtual line_surface_intersecter* clone() const;

  ///
  /// Assignment operator
  ///
  line_surface_intersecter& operator=(const line_surface_intersecter& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert line_surface_intersecter xp in ostream xos.
///
SHEAF_DLL_SPEC
std::ostream&
operator<< (std::ostream &os, const line_surface_intersecter& xp);
  
} // end namespace geometry

#endif // ifndef LINE_SURFACE_INTERSECTER_H
