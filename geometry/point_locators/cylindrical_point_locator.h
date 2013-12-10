
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
/// Interface for class cylindrical_point_locator

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

#ifndef CYLINDRICAL_POINT_LOCATOR_H
#define CYLINDRICAL_POINT_LOCATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POINT_LOCATOR_H
#include "point_locator.h"
#endif

#ifndef D_BOUNDING_BOX_H
#include "d_bounding_box.h"
#endif

#ifndef EVAL_ITERATOR_H
#include "eval_iterator.h"
#endif



#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_SLIST_H
#include "std_slist.h"
#endif

#ifndef STL_SCOPED_INDEX_H
#include "stl_scoped_index.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

template <int DC, int DB>
class d_bin_coordinates;

///
/// An abstract point location query in domains with
/// global coordinate dimension dc and local coordinate dimension db
/// using a search structure based on sorting bounding boxes into
/// a set of bins.
///
class SHEAF_DLL_SPEC cylindrical_point_locator : public point_locator
{

  // ===========================================================
  /// @name CYLINDRICAL_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Dimension of coordinate space.
  ///
  //  static const int DC = 3;

  ///
  /// Dimension of base space.
  ///
  //  static const int DB = 2;

  enum space_dimensions
    {
      DC = 3, DB = 2
    };

  ///
  /// The type of box list.
  ///
  typedef slist<const d_bounding_box<2, 2>*> box_list_type;

  ///
  /// Destructor.
  ///
  virtual ~cylindrical_point_locator();

  ///
  /// The upper bound for the bin index.
  ///
  const block<size_type>& bin_ub() const;

  ///
  /// The dimensions of the smallest bins.
  ///
  const block<sec_vd_value_type>& bin_size() const;

  ///
  /// The number of bounding boxes stored in the search structure.
  ///
  size_type box_ct() const;

  ///
  /// True if this contains no bounding boxes.
  ///
  bool is_empty() const;

  ///
  /// The position of xpt relative to the lower bound,
  /// in integer coordinates; auto-allocated version
  ///
  d_bin_coordinates<2, 2>* relative_position(sec_vd_value_type* xpt, size_type xpt_ub) const;

  ///
  /// The position of xpt relative to the lower bound,
  /// in integer coordinates; pre-allocated version
  ///
  void relative_position_pa(sec_vd_value_type* xpt,
                            size_type xpt_ub,
                            d_bin_coordinates<2, 2>& xresult) const;

  ///
  /// Insert xbox into the search structure.
  ///
  virtual void insert_box(d_bounding_box<2, 2>* xbox) = 0;

  ///
  ///  Remove xbox from the search structure.
  ///
  virtual void remove_box(d_bounding_box<2, 2>* xbox) = 0;

  ///
  /// The list of bounding boxes which may contain xpt.
  ///
  virtual const box_list_type& box_list(sec_vd_value_type* xpt, size_type xpt_ub) const = 0;

  ///
  /// True if xbox is in the box list of some bin.
  ///
  virtual bool contains_box(d_bounding_box<2, 2>* xbox) const = 0;

  ///
  ///  Clear the search structure of all bounding boxes.
  ///
  virtual void clear() = 0;

protected:

  ///
  /// Creates an instance for coordinate section xcoords.
  ///
  cylindrical_point_locator(sec_ed& xcoords);

  ///
  /// Default constructor; disabled.
  ///
  cylindrical_point_locator() {};

  ///
  /// Copy constructor; disabled
  ///
  cylindrical_point_locator(const cylindrical_point_locator& xother) {};

  ///
  /// Assignment operator
  ///
  virtual cylindrical_point_locator& operator=(const point_locator& xother);

  ///
  /// Assignment operator; disabled.
  ///
  cylindrical_point_locator& operator=(const cylindrical_point_locator& xother);

  ///
  /// The upper bound for the bin index.
  ///
  block<size_type> _bin_ub;

  ///
  /// A sec_vd_value_type that truncates to the maximum index for bin 0.
  ///
  sec_vd_value_type _bin_0_max;

  ///
  /// The dimensions of the smallest bins.
  ///
  block<sec_vd_value_type> _bin_size;

  ///
  /// Reciprocal of the dimensions of the smallest bins.
  ///
  block<sec_vd_value_type> _one_over_min_bin_size;

  ///
  /// Updates the bin parameters.
  ///
  virtual void update_bins() = 0;

  ///
  /// The number of bounding boxes stored in the search structure.
  ///
  size_type _box_ct;

  ///
  /// Bounding boxes for the evaluation members.
  ///
  block< d_bounding_box<2, 2> > _boxes;

  ///
  /// The dofs of gathered by evaluation member.
  ///
  block<sec_vd_dof_type> _gathered_dofs;

  ///
  /// The evaluator iterator used to populate the search structure;
  /// must have same life time as the search structure because it owns
  /// the eval_family which owns the section evaluators.
  ///
  eval_iterator _eval_itr;

  ///
  /// The branches for which a point has already been found
  /// for the current evaluation member. Used in all_points_at_value,
  /// allocated her to avoid reallocation for each query.
  ///
  std::set< stl_scoped_index<> > _branches;

  ///
  /// Creates the bounding box or boxes for the quad defined by
  /// the dofs starting at xdofs and inserts them in the search structure.
  ///
  void insert_quad(block<sec_vd_dof_type>& xdofs,
                   const scoped_index& xbranch_id,
                   const scoped_index& xeval_id);

  ///
  /// Creates the bounding box or boxes for the triangle defined by
  /// the dofs starting at xdofs and inserts them in the search structure.
  ///
  void insert_triangle(block<sec_vd_dof_type>& xdofs,
                       const scoped_index& xbranch_id,
                       const scoped_index& xeval_id);


  ///
  /// Converts cartesian coordinates xcartesian
  /// to (longitude, latitude) xresult.
  ///
  void xyz_to_lat_lon(const sec_vd_dof_type xcartesian[3], sec_vd_dof_type xresult[2]);

  ///
  /// Makes a bounding box for a quad.
  ///
  void make_quad_bounding_box(block<sec_vd_dof_type>& xlat_lon_dofs,
                              const scoped_index& xbranch_id,
                              const scoped_index& xeval_id);

  ///
  /// Makes a bounding box for a triangle.
  ///
  void make_triangle_bounding_box(block<sec_vd_dof_type>& xlat_lon_dofs,
                                  const scoped_index& xbranch_id,
                                  const scoped_index& xeval_id);

  //@}


  // ===========================================================
  /// @name POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Updates the search structure to the current values of coordinates().
  ///
  virtual void update();

  ///
  /// Finds a chart point at which coordinates() has value xvalue.
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
  ///
  virtual void branch_points_at_value(const sec_vd_value_type* xvalue,
                                      size_type xvalue_ub,
                                      block<branch_point_pair>& xresult);


  //@}

};
 
} // namespace geometry

#endif // CYLINDRICAL_POINT_LOCATOR_H
