
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
/// Interface for class array_cylindrical_point_locator

#ifndef ARRAY_CYLINDRICAL_POINT_LOCATOR_H
#define ARRAY_CYLINDRICAL_POINT_LOCATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef CYLINDRICAL_POINT_LOCATOR_H
#include "cylindrical_point_locator.h"
#endif

namespace geometry
{

template <int DC, int DB>
class d_bounding_box;

///
/// A point location query in domains with
/// global coordinate dimension DC and local coordinate dimension DB
/// implemented using a DC index array search structure. Efficient for
/// for compact (axis-aligned, box-shaped) domains.
///
class SHEAF_DLL_SPEC array_cylindrical_point_locator : public cylindrical_point_locator
{

  // ===========================================================
  /// @name ARRAY_CYLINDRICAL_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create an instance for coordinates xcoords with bin ub xbin_ub.
  ///
  array_cylindrical_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub);

  ///
  /// Create an instance for coordinates xcoords with bin ub
  /// computed from the size of the mesh.
  ///
  array_cylindrical_point_locator(sec_ed& xcoords);

  ///
  /// Destructor.
  ///
  virtual ~array_cylindrical_point_locator();

  ///
  /// The number of bins used by the search structure.
  ///
  size_type size() const;

  ///
  /// The number of bins allocated for use by the search structure.
  ///
  size_type capacity() const;

  ///
  /// True if the base space of xcoords is a block of quads
  /// and the evaluator family id dlinear.
  ///
  bool is_dlinear_quads(const sec_ed& xcoords) const;

  ///
  /// True if the base space of xcoords is a block of triangles
  /// and the evaluator family id dlinear.
  ///
  bool is_dlinear_triangles(const sec_ed& xcoords) const;

protected:

  ///
  /// Default constructor; disabled.
  ///
  array_cylindrical_point_locator()
  {}
  ;

  ///
  /// Copy constructor; disabled.
  ///
  array_cylindrical_point_locator(const array_cylindrical_point_locator& xother)
  {}
  ;

  ///
  /// Assignment operator
  ///
  virtual array_cylindrical_point_locator& operator=(const point_locator& xother);

  ///
  /// Assignment operator; disabled.
  ///
  array_cylindrical_point_locator& operator=(const array_cylindrical_point_locator& xother);

  ///
  /// Resets this with bounds xlb, xub, and xbin_ub.
  /// If xbin_ub == 0; use default_bin_ub().
  ///
  void update_bins();

  ///
  /// The search structure; a d-dimensional array of bins.
  ///
  block<box_list_type> _bins;

  ///
  /// The single index (offset) associated with tree coordinates xcoord.
  ///
  size_type bin_id(const d_bin_coordinates<2, 2>& xcoord) const;

  ///
  /// The single index (offset) associated with xid.
  ///
  size_type bin_id(const block<size_type>& xid) const;

  ///
  /// The single index (offset) associated with xi, xj.
  ///
  size_type bin_id(size_type xi, size_type xj) const;

  //@}


  // ===========================================================
  /// @name CYLINDRICAL_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of box list.
  ///
  typedef singly_linked_list<const d_bounding_box<2, 2>*> box_list_type;

  ///
  /// Insert xbox into this.
  ///
  virtual void insert_box(d_bounding_box<2, 2>* xbox);

  ///
  ///  Remove xbox from this.
  ///
  virtual void remove_box(d_bounding_box<2, 2>* xbox);

  ///
  /// The list of bounding boxes which may contain xpt.
  ///
  virtual const box_list_type& box_list(sec_vd_value_type* xpt, size_type xpt_ub) const;

  ///
  /// True if xbox is in this.
  ///
  virtual bool contains_box(d_bounding_box<2, 2>* xbox) const;

  ///
  ///  Clear this of all bounding boxes.
  ///
  virtual void clear();

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

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert array_cylindrical_point_locator xpl into ostream xos.
///
SHEAF_DLL_SPEC 
std::ostream&
operator << (std::ostream& xos, const array_cylindrical_point_locator& xpl);
 
} // namespace geometry

#endif // ARRAY_CYLINDRICAL_POINT_LOCATOR_H
