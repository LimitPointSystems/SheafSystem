
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
/// Interface for class d_array_point_locator

#ifndef D_ARRAY_POINT_LOCATOR_H
#define D_ARRAY_POINT_LOCATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_BIN_POINT_LOCATOR_H
#include "d_bin_point_locator.h"
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
template <int DC, int DB>
class SHEAF_DLL_SPEC d_array_point_locator : public d_bin_point_locator<DC, DB>
{

  // ===========================================================
  /// @name D_BIN_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of box list.
  ///
  typedef std::forward_list<const d_bounding_box<DC, DB>*> box_list_type;

  ///
  /// The type of box set.
  ///
  typedef std::set<const d_bounding_box<DC, DB>*> box_set_type;
  
  ///
  /// Insert xbox into this.
  ///
  virtual void insert_box(d_bounding_box<DC, DB>* xbox);

  ///
  ///  Remove xbox from this.
  ///
  virtual void remove_box(d_bounding_box<DC, DB>* xbox);

  using d_bin_point_locator<DC, DB>::box_list;
  
  ///
  /// The list of bounding boxes which may contain xpt.
  ///
  virtual const box_list_type& box_list(sec_vd_value_type* xpt,
                                        size_type xpt_ub) const;

  ///
  /// The list of bounding boxes which may intersect the cell described by xeval, xdofs.
  ///
  virtual void box_list(const section_evaluator& xeval,
			sec_vd_value_type* xdofs, 
			size_type xdofs_ub,
			box_list_type& xresult) const;

  ///
  /// The list of bounding boxes which may intersect the bounding box xbox.
  ///
  virtual void box_list(d_bounding_box<DC, DB>* xbox, box_set_type& xresult) const;

  ///
  /// True if xbox is in this.
  ///
  virtual bool contains_box(d_bounding_box<DC, DB>* xbox) const;

  ///
  ///  Clear this of all bounding boxes.
  ///
  virtual void clear();

  //@}


  // ===========================================================
  /// @name D_ARRAY_POINT_LOCATOR FACET
  // ===========================================================
  //@{

  ///
  /// Create an instance for coordinates xcoords with bin ub xbin_ub.
  /// If xpopulate, enter the eval members of xcoords in the search structure.
  ///
  d_array_point_locator(sec_ed& xcoords, 
			const block<size_type>& xbin_ub, 
			bool xpopulate = true, 
			size_type xeval_capacity = 256);

  ///
  /// Create an instance for coordinates xcoords with bin ub
  /// computed from the size of the mesh.
  /// If xpopulate, enter the eval members of xcoords in the search structure.
  ///
  d_array_point_locator(sec_ed& xcoords, 
			bool xpopulate = true, 
			size_type xeval_capacity = 256);

  ///
  /// Destructor.
  ///
  virtual ~d_array_point_locator();

  ///
  /// The number of bins used by the search structure.
  ///
  size_type size() const;

  ///
  /// The number of bins allocated for use by the search structure.
  ///
  size_type capacity() const;

  ///
  /// Inserts this in ostream xos.
  ///
  void to_stream(std::ostream& xos) const;

protected:

  ///
  /// Default constructor; disabled.
  ///
  d_array_point_locator() {};

  ///
  /// Copy constructor; disabled.
  ///
  d_array_point_locator(const d_array_point_locator& xother) {};

  ///
  /// Assignment operator; disabled.
  ///
  virtual d_array_point_locator& operator=(const point_locator& xother) {return *this;};

  ///
  /// Assignment operator; disabled.
  ///
  d_array_point_locator& operator=(const d_array_point_locator& xother) {return *this;};

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
  size_type bin_id(const d_bin_coordinates<DC, DB>& xcoord) const;

  ///
  /// The single index (offset) associated with xid.
  ///
  size_type bin_id(const block<size_type>& xid) const;

  ///
  /// The single index (offset) associated with xi, xj.
  ///
  size_type bin_id(size_type xi, size_type xj) const;

  ///
  /// The single index (offset) associated with xi, xj, xk.
  ///
  size_type bin_id(size_type xi, size_type xj, size_type xk) const;

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
/// Insert d_array_point_locator<DC, DB> xpl into ostream xos.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
std::ostream&
operator << (std::ostream& xos, const d_array_point_locator<DC, DB>& xpl);

///
/// Insert d_array_point_locator<DC, DB>::box_list_type xbl into ostream xos.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
std::ostream&
operator << (std::ostream& xos, const std::forward_list<const d_bounding_box<DC, DB>*>& xbl);


// ============================================================================
// SPECIALIZATIONS
// ============================================================================

//
// Insert xbox into this; 
// DC = 1, DB = 1 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<1, 1>::
insert_box(d_bounding_box<1, 1>* xbox);

//
// Insert xbox into this; 
// DC = 2, DB = 2 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<2, 2>::
insert_box(d_bounding_box<2, 2>* xbox);

//
// Insert xbox into this;
// DC = 3, DB = 1 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 1>::
insert_box(d_bounding_box<3, 1>* xbox);

//
// Insert xbox into this;
// DC = 3, DB = 2 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 2>::
insert_box(d_bounding_box<3, 2>* xbox);

//
// Insert xbox into this;
// DC = 3, DB = 3 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 3>::
insert_box(d_bounding_box<3, 3>* xbox);
 
//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 1, DB = 1 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<1, 1>::
box_list(const section_evaluator& xeval, sec_vd_value_type* xdofs, size_type xdofs_ub, box_list_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 2, DB = 2 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<2, 2>::
box_list(const section_evaluator& xeval, sec_vd_value_type* xdofs, size_type xdofs_ub, box_list_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 3, DB = 1 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 1>::
box_list(const section_evaluator& xeval, sec_vd_value_type* xdofs, size_type xdofs_ub, box_list_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 3, DB = 2 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 2>::
box_list(const section_evaluator& xeval, sec_vd_value_type* xdofs, size_type xdofs_ub, box_list_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 3, DB = 3 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 3>::
box_list(const section_evaluator& xeval, sec_vd_value_type* xdofs, size_type xdofs_ub, box_list_type& xresult) const;
 
//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 1, DB = 1 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<1, 1>::
box_list(d_bounding_box<1, 1>* xbox, box_set_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 2, DB = 2 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<2, 2>::
box_list(d_bounding_box<2, 2>* xbox, box_set_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 3, DB = 1 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 1>::
box_list(d_bounding_box<3, 1>* xbox, box_set_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 3, DB = 2 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 2>::
box_list(d_bounding_box<3, 2>* xbox, box_set_type& xresult) const;

//
// Get list of boxes possibly overlapping the cell described by xeval, xdofs;
// DC = 3, DB = 3 specialization.
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 3>::
box_list(d_bounding_box<3, 3>* xbox, box_set_type& xresult) const;

//
// Remove xbox from this;
// DC = 1, DB = 1 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<1, 1>::
remove_box(d_bounding_box<1, 1>* xbox);

//
// Remove xbox from this;
// DC = 2, DB = 2 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<2, 2>::
remove_box(d_bounding_box<2, 2>* xbox);

//
// Remove xbox from this;
// DC = 3, DB = 1 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 1>::
remove_box(d_bounding_box<3, 1>* xbox);

//
// Remove xbox from this;
// DC = 3, DB = 2 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 2>::
remove_box(d_bounding_box<3, 2>* xbox);

//
// Remove xbox from this;
// DC = 3, DB = 3 specialization
//
template <>
SHEAF_DLL_SPEC
void
d_array_point_locator<3, 3>::
remove_box(d_bounding_box<3, 3>* xbox);

///
/// The single index (offset) associated with tree coordinates xcoord
/// specialized for d_bin_coordinates<1, 1>.
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<1, 1>::
bin_id(const d_bin_coordinates<1, 1>& xcoord) const;

///
/// The single index (offset) associated with tree coordinates xcoord
/// specialized for d_bin_coordinates<2, 2>.
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<2, 2>::
bin_id(const d_bin_coordinates<2, 2>& xcoord) const;

///
/// The single index (offset) associated with tree coordinates xcoord
/// specialized for d_bin_coordinates<3, 1>.
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<3, 1>::
bin_id(const d_bin_coordinates<3, 1>& xcoord) const;

///
/// The single index (offset) associated with tree coordinates xcoord
/// specialized for d_bin_coordinates<3, 2>.
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<3, 2>::
bin_id(const d_bin_coordinates<3, 2>& xcoord) const;

///
/// The single index (offset) associated with tree coordinates xcoord
/// specialized for d_bin_coordinates<3, 3>.
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<3, 3>::
bin_id(const d_bin_coordinates<3, 3>& xcoord) const;

///
/// The single index (offset) associated with xid
/// specialized for <1, 1>
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<1, 1>::
bin_id(const block<size_type>& xid) const;

///
/// The single index (offset) associated with xid
/// specialized for <2, 2>
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<2, 2>::
bin_id(const block<size_type>& xid) const;

///
/// The single index (offset) associated with xid
/// specialized for <3, 1>
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<3, 1>::
bin_id(const block<size_type>& xid) const;

///
/// The single index (offset) associated with xid
/// specialized for <3, 2>
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<3, 2>::
bin_id(const block<size_type>& xid) const;

///
/// The single index (offset) associated with xid
/// specialized for <3, 3>
///
template <>
SHEAF_DLL_SPEC
size_type
d_array_point_locator<3, 3>::
bin_id(const block<size_type>& xid) const;


}

// namespace geometry/

#endif // D_ARRAY_POINT_LOCATOR_H
