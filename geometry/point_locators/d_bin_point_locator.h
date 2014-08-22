
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
/// Interface for class d_bin_point_locator

#ifndef COM_LIMITPOINT_GEOMETRY_D_BIN_POINT_LOCATOR_H
#define COM_LIMITPOINT_GEOMETRY_D_BIN_POINT_LOCATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_GEOMETRY_POINT_LOCATOR_H
#include "ComLimitPoint/geometry/point_locator.h"
#endif

#ifndef COM_LIMITPOINT_GEOMETRY_D_BOUNDING_BOX_H
#include "ComLimitPoint/geometry/d_bounding_box.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_EVAL_ITERATOR_H
#include "ComLimitPoint/fiber_bundle/eval_iterator.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SINGLY_LINKED_LIST_H
#include "ComLimitPoint/sheaf/singly_linked_list.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_STL_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/stl_scoped_index.h"
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
template <int DC, int DB>
class SHEAF_DLL_SPEC d_bin_point_locator : public point_locator
{

  // ===========================================================
  /// @name D_BIN_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of box list.
  ///
  typedef singly_linked_list<const d_bounding_box<DC, DB>*> box_list_type;

  ///
  /// Destructor.
  ///
  virtual ~d_bin_point_locator();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

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
  d_bin_coordinates<DC, DB>* relative_position(sec_vd_value_type* xpt,
                                               size_type xpt_ub) const;

  ///
  /// The position of xpt relative to the lower bound,
  /// in integer coordinates; pre-allocated version
  ///
  void relative_position_pa(sec_vd_value_type* xpt,
                            size_type xpt_ub,
                            d_bin_coordinates<DC, DB>& xresult) const;

  ///
  /// Assigns a box to xmbr_id and initializes it,
  /// but does not insert it in the search structure.
  ///
  d_bounding_box<DC, DB>* assign_box(const scoped_index& xmbr_id, 
				     const scoped_index& xbranch_id, 
				     section_evaluator& xeval, 
				     const sec_vd_dof_type* xdofs, 
				     size_type xdofs_ct);  

  ///
  /// The number of boxes that have been allocated.
  ///
  size_type box_capacity();

  ///
  /// The xi-th bounding box.
  ///
  d_bounding_box<DC, DB>* box(pod_index_type xi);

  ///
  /// Updates the xi-th bounding box with dofs xdofs.
  ///
  void update_box(pod_index_type xi, const sec_vd_dof_type* xdofs, size_type xdofs_ct);  


  ///
  /// Insert xbox into the search structure.
  ///
  virtual void insert_box(d_bounding_box<DC, DB>* xbox) = 0;

  ///
  ///  Remove xbox from the search structure.
  ///
  virtual void remove_box(d_bounding_box<DC, DB>* xbox) = 0;

  ///
  /// The list of bounding boxes which may contain xpt.
  ///
  virtual const box_list_type& box_list(sec_vd_value_type* xpt,
                                        size_type xpt_ub) const = 0;

  ///
  /// True if xbox is in the box list of some bin.
  ///
  virtual bool contains_box(d_bounding_box<DC, DB>* xbox) const = 0;

  ///
  ///  Clear the search structure of all bounding boxes.
  ///
  virtual void clear() = 0;

  ///
  /// The dofs of gathered by evaluation member.
  ///
  const block<sec_vd_dof_type>& gathered_dofs() const;

protected:

  ///
  /// Creates an instance for coordinate section xcoords.
  ///
  d_bin_point_locator(sec_ed& xcoords);

  ///
  /// Default constructor; disabled.
  ///
  d_bin_point_locator() {};

  ///
  /// Copy constructor; disabled
  ///
  d_bin_point_locator(const d_bin_point_locator<DC, DB>& xother) {};

  ///
  /// Assignment operator; disabled.
  ///
  virtual d_bin_point_locator& operator=(const point_locator& xother) {return *this;};

  ///
  /// Assignment operator; disabled.
  ///
  d_bin_point_locator& operator=(const d_bin_point_locator<DC, DB>& xother) {return *this;};

  ///
  /// The upper bound for the bin index.
  ///
  block<size_type> _bin_ub;

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
  block< d_bounding_box<DC, DB> > _boxes;

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

  //@}


  // ===========================================================
  /// @name POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  using point_locator::update;

  ///
  /// Updates the search structure to the current values of coordinates();
  /// synonym for update(true);
  ///
  virtual void update();

  ///
  /// Updates the search structure to the current values of coordinates();
  /// if  xpopulate, populates the search structure with the eval members
  /// coordinates(). Ensures capacity for at least xeval_capacity eval members.
  ///
  virtual void update(bool xpopulate, size_type xeval_capacity);

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

#endif // COM_LIMITPOINT_GEOMETRY_D_BIN_POINT_LOCATOR_H
