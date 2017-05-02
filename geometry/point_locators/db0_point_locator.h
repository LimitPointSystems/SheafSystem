
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
/// Interface for class db0_point_locator

#ifndef DB0_POINT_LOCATOR_H
#define DB0_POINT_LOCATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef POINT_LOCATOR_H
#include "SheafSystem/point_locator.h"
#endif

#ifndef SINGLY_LINKED_LIST_H
#include "SheafSystem/singly_linked_list.h"
#endif

#ifndef STD_QUEUE_H
#include "SheafSystem/std_queue.h"
#endif

#ifndef SECTION_EVAL_ITERATOR_H
#include "SheafSystem/section_eval_iterator.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

///
/// An abstract point location query in domains with
/// global coordinate dimension DC and local coordinate dimension 0
/// using a search structure based on sorting bounding boxes into
/// a regular array of bins.
///
template<int DC>
class SHEAF_DLL_SPEC db0_point_locator : public point_locator
{

  // ===========================================================
  /// @name DB0_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create an instance for coordinates xcoords with bin ub xbin_ub.
  ///
  db0_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub);

  ///
  /// Creates an instance for coordinate section xcoords
  /// with average bin occupancy = xavg_occupancy
  ///
  db0_point_locator(sec_ed& xcoords, int xavg_occupancy = 2);

  ///
  /// The type of the bin coordinates.
  ///
  typedef int bin_coord_type;

  ///
  /// Destructor.
  ///
  virtual ~db0_point_locator();

  ///
  /// The upper bound for the bin index.
  ///
  const block<size_type>& bin_ub() const;

  ///
  /// The dimensions of the smallest bins.
  ///
  const block<sec_vd_value_type>& bin_size() const;

  ///
  /// True if the search structure contains no vertices.
  ///
  bool is_empty() const;

  ///
  /// The position of xpt relative to the lower bound in integer coordinates.
  ///
  void relative_position(const sec_vd_value_type xpt[],
                         bin_coord_type xresult[]) const;

  ///
  ///  Clear the search structure of all bounding boxes.
  ///
  virtual void clear();

protected:

  ///
  /// Default constructor; disabled.
  ///
  db0_point_locator() {};

  ///
  /// Copy constructor; disabled
  ///
  db0_point_locator(const db0_point_locator& xother) {};

  ///
  /// Assignment operator; disabled.
  ///
  virtual db0_point_locator& operator=(const point_locator& xother) {return *this;};

  ///
  /// Assignment operator; disabled.
  ///
  db0_point_locator& operator=(const db0_point_locator& xother) {return *this;};

  ///
  /// The upper bound for the bin index.
  ///
  block<size_type> _bin_ub;

  ///
  /// The dimensions of the smallest bins.
  ///
  block<sec_vd_value_type> _bin_size;

  ///
  /// The diagonal length of the smallest bins.
  ///
  sec_vd_value_type _bin_diag;

  ///
  /// Reciprocal of the dimensions of the smallest bins.
  ///
  block<sec_vd_value_type> _one_over_min_bin_size;

  ///
  /// Updates the bin parameters.
  ///
  virtual void update_bins();

  ///
  /// The information stored in the search structure for each vertex.
  ///
  struct SHEAF_DLL_SPEC vertex_type
  {
    // The id of the  vertex.

    scoped_index disc_id;

    // The branch containing the vertex

    scoped_index branch_id;

    // The coordinates of the vertex in the branch.

    sec_vd_dof_type coords[DC];
  };

  ///
  /// The type of vertex list.
  ///
  typedef singly_linked_list<vertex_type> vertex_list_type;

  ///
  /// The search structure; a d-dimensional array of bins.
  ///
  block<vertex_list_type> _bins;

  ///
  /// The bins scheduled to be searched for the current query point.
  ///
  std::queue<int> _search_q;

  ///
  /// Set xbin_pos the bin closest to xpt_pos.
  ///
  void find_closest_bin(const bin_coord_type xpt_pos[],
                        bin_coord_type xbin_pos[]);

  ///
  /// The radius of a sphere centered on the query point
  /// that will be searched for vertices.
  ///
  sec_vd_value_type _search_radius;

  ///
  /// The lower bound of the search region.
  ///
  bin_coord_type _search_region_lb[DC];

  ///
  /// The upper bound of the search region.
  ///
  bin_coord_type _search_region_ub[DC];

  ///
  /// Initialize the search radius and the search region.
  ///
  void initialize_search_region(const sec_vd_value_type xvalue[]);

  ///
  /// Increase the search radius and expand the search region to match.
  ///
  void expand_search_region(const sec_vd_value_type xvalue[]);

  ///
  /// Compute the intersection of the domain with the search box
  /// enclosing the search sphere.
  ///
  void compute_search_region(const sec_vd_value_type xvalue[]);

  ///
  /// Puts all the bins from
  /// the search region onto the search queue.
  ///
  void initialize_search_q();

  ///
  /// Puts previous unsearched bins from
  /// the search region onto the search queue.
  ///
  void update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);

  ///
  /// The squared distance from the point with coordinates xglobal_coords
  /// to the vertex associated with xvertex_id.
  ///
  sec_vd_value_type
  vertex_distance_sq(const sec_vd_value_type xglobal_coords[],
                     const vertex_type& xvertex_entry);


  ///
  /// Sets xresult.chart() to the vertex in _bins that is both closest
  /// to the point with value xvalue and closer than _search_radius.
  ///
  void find_closest_vertex(const sec_vd_value_type* xvalue,
                           sec_vd_value_type& xclosest_dist_sq,
                           chart_point& xresult);

  ///
  /// Sets xresult.chart() to the vertex, if any  in bin xbin_id that is both
  //  closest to the point with value xvalue and closer than _search_radius.
  /// Sets xclost_dist to the distance to the vertex.
  ///
  void find_closest_vertex_in_bin(int xbin_id,
                                  const sec_vd_value_type* xvalue,
                                  chart_point& xresult,
                                  sec_vd_value_type& xclosest_dist);


  ///
  /// The id of the bin with bin coords xcoord.
  ///
  int bin_id(const bin_coord_type xcoord[]) const;

  ///
  /// Prints the contents of the bins on xos; intended for debugging.
  ///
  void print_bins(std::ostream& xos, const std::string& xmsg) const;

  ///
  /// Prints the contents of the search queue on xos; intended for debugging.
  ///
  void print_queue(std::ostream& xos, const std::string& xmsg) const;

  ///
  /// Prints xvlaue on xos; intended for debugging.
  ///
  void print_value(std::ostream& xos,
                   const sec_vd_value_type xvalue[],
                   const std::string& xmsg) const;


  ///
  /// Prints xcoords on xos; intended for debugging.
  ///
  void print_coords(std::ostream& xos,
                    const bin_coord_type xcoords[],
                    const std::string& xmsg) const;


  ///
  /// The maximum distance from the query point xpt
  /// to any point in the bin with coordinates xbin_pos.
  ///
  sec_vd_value_type max_bin_distance(const sec_vd_value_type xpt[],
                                     const bin_coord_type xbin_pos[]) const;

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
  /// Finds a chart point at which coordinates() has value xvalue;
  /// for sections over db = 0 base spaces, this means the point
  /// with value closest to xvalue.
  ///
  virtual void point_at_value(const sec_vd_value_type* xvalue,
                              size_type xvalue_ub,
                              chart_point& xresult);

  ///
  /// Finds all chart points at which coordinates() has value xvalue;
  /// for sections over db = 0 base spaces, this means the single point
  /// with value closest to xvalue.
  ///
  virtual void all_points_at_value(const sec_vd_value_type* xvalue,
                                   size_type xvalue_ub,
                                   block<chart_point_3d>& xresult);


  ///
  /// Finds one chart point in each branch at which coordinates()
  /// has value xvalue and appends them to xresult;
  /// for sections over db = 0 base spaces, this means the single point
  /// with value closest to xvalue.
  ///
  virtual void branch_points_at_value(const sec_vd_value_type* xvalue,
                                      size_type xvalue_ub,
                                      block<branch_point_pair>& xresult);

  //@}

};

// ============================================================================
// SPECIALIZATIONS
// ============================================================================

//
// Puts all the bins from/ the search region
// onto the search queue; DC = 1 specialization
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<1>::
initialize_search_q();

//
// Puts all the bins from the search region
// onto the search queue; DC = 2 specialization
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<2>::
initialize_search_q();

//
// Puts all the bins from the search region
//onto the search queue; DC = 3 specialization
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<3>::
initialize_search_q();

//
// Puts previous unsearched bins from the search region
// onto the search queue; DC = 1 specialization
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<1>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);

//
// Puts previous unsearched bins from the search region
// onto the search queue; DC = 2 specialization
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<2>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);

//
// Puts previous unsearched bins from the search region
// onto the search queue; DC = 3 specialization
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<3>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);

//
// The id of the bin with bin coords xcoord; DC = 1 specialization.
//
template<>
SHEAF_DLL_SPEC
int
db0_point_locator<1>::
bin_id(const bin_coord_type xcoord[]) const;


//
// The id of the bin with bin coords xcoord; DC = 2 specialization.
//
template<>
SHEAF_DLL_SPEC
int
db0_point_locator<2>::
bin_id(const bin_coord_type xcoord[]) const;


//
// The id of the bin with bin coords xcoord; DC = 3 specialization.
//
template<>
SHEAF_DLL_SPEC
int
db0_point_locator<3>::
bin_id(const bin_coord_type xcoord[]) const;

//
// The maximum distance from the query point xpt
// to any point in the bin with coordinates xbin_pos; DC=1 specialization.
//
template<>
SHEAF_DLL_SPEC
sec_vd_value_type
db0_point_locator<1>::
max_bin_distance(const sec_vd_value_type xpt[], const bin_coord_type xbin_pos[]) const;

//
// The maximum distance from the query point xpt
// to any point in the bin with coordinates xbin_pos; DC=2 specialization.
//
template<>
SHEAF_DLL_SPEC
sec_vd_value_type
db0_point_locator<2>::
max_bin_distance(const sec_vd_value_type xpt[], const bin_coord_type xbin_pos[]) const;

//
// The maximum distance from the query point xpt
// to any point in the bin with coordinates xbin_pos; DC=3 specialization.
//
template<>
SHEAF_DLL_SPEC
sec_vd_value_type
db0_point_locator<3>::
max_bin_distance(const sec_vd_value_type xpt[], const bin_coord_type xbin_pos[]) const;

//
// Prints the contents of the bins on xos; DC=3 specialization.
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<3>::
print_bins(std::ostream& xos, const std::string& xmsg) const;

///
/// Puts all the bins from the search region onto the search queue
/// specialized for DC=1
///
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<1>::
initialize_search_q();


///
/// Puts all the bins from the search region onto the search queue
/// specialized for DC=2
///
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<2>::
initialize_search_q();


///
/// Puts all the bins from the search region onto the search queue
/// specialized for DC=3
///
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<3>::
initialize_search_q();

///
/// Puts previous unsearched bins from the search region onto the search queue
/// specialized for DC=1.
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<1>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);

///
/// Puts previous unsearched bins from the search region onto the search queue
/// specialized for DC=2.
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<2>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);

///
/// Puts previous unsearched bins from the search region onto the search queue
/// specialized for DC=3.
//
template<>
SHEAF_DLL_SPEC
void
db0_point_locator<3>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[]);



} // namespace geometry

#endif // DB0_POINT_LOCATOR_H
