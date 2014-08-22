
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
/// Implementation for class cylindrical_point_locator

#include "cylindrical_point_locator.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/bilinear_2d.h"
#include "ComLimitPoint/fiber_bundle/chart_point_3d.h"
#include "d_bin_coordinates.h"
#include "ComLimitPoint/fiber_bundle/eval_iterator.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/linear_2d.h"
#include "ComLimitPoint/sheaf/preorder_iterator.h"
#include "sec_at1_space.h"
#include "sec_ed.h"
#include "std_bitset.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT



// ===========================================================
// CYLINDRICAL_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

//const int geometry::cylindrical_point_locator::DC;
//const int geometry::cylindrical_point_locator::DB;

geometry::cylindrical_point_locator::
cylindrical_point_locator(sec_ed& xcoords) : point_locator(xcoords),_eval_itr(xcoords.schema(), false)
			 //point_locator::point_locator(xcoords),_eval_itr(xcoords.schema(), false)
{
  // Preconditions:

  require(precondition_of(point_locator(xcoords)));

  // Body:

  _bin_ub.reserve(DB);
  _bin_ub.set_ct(DB);

  _bin_size.reserve(DB);
  _bin_size.set_ct(DB);

  _one_over_min_bin_size.reserve(DB);
  _one_over_min_bin_size.set_ct(DB);

  _box_ct = 0;

  // The eval_itr owns the evaluator_family which owns the section_evaluators.
  // The bounding boxes in _boxes keep pointers to these section evaluators.
  // So the lifetime of the eval_family must be as long as _boxes.

  /// @hack a new eval_family is created every time put_schema_anchor(schema)
  /// is called in eval_itr, including initially from the eval_itr constructor.
  /// But we have to reanchor the eval_itr to each branch of a multisection
  /// in update(). We can do this only with put_schema_anchor(index),
  /// which does not recreate the eval family, if we initialize eval_itr here
  /// using its constructor, then force it to be done, ready for reanchoring.

  _eval_itr.force_is_done();

  // Postconditions:


  // Exit:

  return;
}

geometry::cylindrical_point_locator::
~cylindrical_point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

const sheaf::block<sheaf::size_type>&
geometry::cylindrical_point_locator::
bin_ub() const
{
  // Preconditions:


  // Body:

  const block<size_type>& result = _bin_ub;

  // Postconditions:

  ensure_for_all(i, 0, db(), result[i] > 0);

  // Exit:

  return result;
}

const sheaf::block<fiber_bundle::sec_vd_value_type>&
geometry::cylindrical_point_locator::
bin_size() const
{

  // Preconditions:


  // Body:

  const block<sec_vd_value_type>& result  = _bin_size;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
geometry::cylindrical_point_locator::
box_ct() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _box_ct;

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::cylindrical_point_locator::
is_empty() const
{
  bool result;

  // Preconditions:


  // Body:

  result = (box_ct() == 0);

  // Postconditions:

  ensure(result == (box_ct() == 0));

  // Exit:

  return result;
}

geometry::d_bin_coordinates<2, 2>*
geometry::cylindrical_point_locator::
relative_position(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  d_bin_coordinates<2, 2>* result;

  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= db());

  // Body:

  result = new d_bin_coordinates<2, 2>();
  relative_position_pa(xpt, xpt_ub, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(relative_position_pa(xpt, xpt_ub, result)));

  // Exit:

  return result;
}

void
geometry::cylindrical_point_locator::
relative_position_pa(sec_vd_value_type* xpt,
                     size_type xpt_ub,
                     d_bin_coordinates<2, 2>& xresult) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= db());
  require((-90.0 < xpt[1]) && (xpt[1] < 90.0));


  // Body:

  sec_vd_value_type lrel_pos[DB];

  lrel_pos[0] = (xpt[0] + 180.0)*_one_over_min_bin_size[0]; // - (-180)

  // Put lon values outside (-180, 180) into the min or max bins.

  if(lrel_pos[0] < 0.0)
  {
    lrel_pos[0] = 0.01; // Truncates to 0
  }
  else if(lrel_pos[0] >= _bin_ub[0])
  {
    lrel_pos[0] = _bin_0_max; // Truncates to _bin_ub[0] - 1
  }

  lrel_pos[1] = (xpt[1] + 90.0)*_one_over_min_bin_size[1]; // - (-90)

#ifdef DIAGNOSTIC_OUTPUT

  cout << "rel pos: " << setw(12) << lrel_pos[0] << setw(12) << lrel_pos[1] << endl;
#endif

  xresult = lrel_pos;

  // Postconditions:

  // Exit:

  return;
}


void
geometry::cylindrical_point_locator::
insert_box(d_bounding_box<2, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  is_abstract();

  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

void
geometry::cylindrical_point_locator::
remove_box(d_bounding_box<2, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  is_abstract();

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

const geometry::cylindrical_point_locator::box_list_type&
geometry::cylindrical_point_locator::
box_list(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= db());

  // Body:


  is_abstract();

  static box_list_type result; // just to avoid compiler warnings

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::cylindrical_point_locator::
contains_box(d_bounding_box<2, 2>* xbox) const
{
  bool result = true;

  // Preconditions:

  require(xbox != 0);

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

void
geometry::cylindrical_point_locator::
clear()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

void
geometry::cylindrical_point_locator::
update_bins()
{
  // Preconditions:

  require(is_empty());

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

void
geometry::cylindrical_point_locator::
insert_quad(block<sec_vd_dof_type>& xdofs,
            const scoped_index& xbranch_id,
            const scoped_index& xeval_id)
{
  // Preconditions:


  // Body:

  // Vertex 0:

  bitset<4> neg_x, neg_y;
  block<sec_vd_dof_type> lat_lon(8);
  lat_lon.set_ct(8);

  for(int i=0, j=0, k=0; i<4; i++, j+=2, k+=3)
  {
    neg_x[i] = (xdofs[k] < 0.0);
    neg_y[i] = (xdofs[k+1] < 0.0);
    xyz_to_lat_lon(&xdofs[k], &lat_lon[j]);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "xdofs " << xdofs << endl;
  cout << "neg_x " << neg_x << endl;
  cout << "neg_y " << neg_y << endl << endl;
#endif

  int neg_x_ct = neg_x.count();
  int neg_y_ct = neg_y.count();
  bool on_dateline = (neg_x_ct == 4) && (neg_y_ct != 4) && (neg_y_ct != 0);

  if(on_dateline)
  {
    // Create 2 bounding boxes, one at -180, one at +180.

    // Create the box at 180:

    for(int i=0; i<4; ++i)
    {
      if(neg_y[i])
      {
        lat_lon[i*2] += 360.0;
      }
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << "creating bbox at 180" << endl;
#endif

    make_quad_bounding_box(lat_lon, xbranch_id, xeval_id);

    // Create the box at -180:

    for(int i=0; i<4; ++i)
    {
      lat_lon[i*2] -= 360.0;
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << "creating bbox at -180" << endl;
#endif

    make_quad_bounding_box(lat_lon, xbranch_id, xeval_id);

  }
  else
  {
    // Create a single bounding box.

    make_quad_bounding_box(lat_lon, xbranch_id, xeval_id);
  }

  // Postconditions:


  // Exit:

  return;
}

void
geometry::cylindrical_point_locator::
insert_triangle(block<sec_vd_dof_type>& xdofs,
                const scoped_index& xbranch_id,
                const scoped_index& xeval_id)
{
  // Preconditions:


  // Body:

  // Vertex 0:

  bitset<3> neg_x, neg_y;
  block<sec_vd_dof_type> lat_lon(6);
  lat_lon.set_ct(6);

  for(int i=0, j=0, k=0; i<3; i++, j+=2, k+=3)
  {
    neg_x[i] = (xdofs[k] < 0.0);
    neg_y[i] = (xdofs[k+1] < 0.0);
    xyz_to_lat_lon(&xdofs[k], &lat_lon[j]);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "xdofs " << xdofs << endl;
  cout << "neg_x " << neg_x << endl;
  cout << "neg_y " << neg_y << endl << endl;
#endif

  int neg_x_ct = neg_x.count();
  int neg_y_ct = neg_y.count();
  bool on_dateline = (neg_x_ct == 3) && (neg_y_ct != 3) && (neg_y_ct != 0);

  if(on_dateline)
  {
    // Create 2 bounding boxes, one at -180, one at +180.

    // Create the box at 180:

    for(int i=0; i<3; ++i)
    {
      if(neg_y[i])
      {
        lat_lon[i*2] += 360.0;
      }
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << "creating bbox at 180" << endl;
#endif

    make_triangle_bounding_box(lat_lon, xbranch_id, xeval_id);

    // Create the box at -180:

    for(int i=0; i<3; ++i)
    {
      lat_lon[i*2] -= 360.0;
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << "creating bbox at -180" << endl;
#endif

    make_triangle_bounding_box(lat_lon, xbranch_id, xeval_id);

  }
  else
  {
    // Create a single bounding box.

    make_triangle_bounding_box(lat_lon, xbranch_id, xeval_id);
  }

  // Postconditions:


  // Exit:

  return;
}

void
geometry::cylindrical_point_locator::
xyz_to_lat_lon(const sec_vd_dof_type xcartesian[3], sec_vd_dof_type xresult[2])
{
  // Preconditions:

  // Body:

  static const double RAD2DEG = 180.0/M_PI;

  double x = xcartesian[0];
  double y = xcartesian[1];
  double z = xcartesian[2];

  // Convert (x,y,z) to phi and theta in radians.

  double radius = sqrt(x*x + y*y + z*z);
  double theta  = atan2(y, x);
  double phi    = acos(z/radius);

  double longitude = RAD2DEG*theta;
  double latitude  = 90.0 - RAD2DEG*phi;

  // Note that we have longitude before latitude.

  xresult[0] = longitude;
  xresult[1] = latitude;

  // Postconditions:

  // Exit:

}

void
geometry::cylindrical_point_locator::
make_quad_bounding_box(block<sec_vd_dof_type>& xlat_lon_dofs,
                       const scoped_index& xbranch_id,
                       const scoped_index& xeval_id)
{
  // Preconditions:


  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "lat lon dofs: " << xlat_lon_dofs << endl;
#endif

  static bilinear_2d levaluator;

  // Get a bounding box.

  _boxes.set_ct(_boxes.ct() + 1);
  d_bounding_box<2, 2>& bbox = _boxes.back();

  // Store the dofs.

  bbox.put_dofs_index(_gathered_dofs.ct());
  _gathered_dofs.push_back(xlat_lon_dofs);

  // Get the bounds for this eval member.

  sec_vd_value_type lat_lon_min[2];
  levaluator.min(xlat_lon_dofs.base(), xlat_lon_dofs.ct(), lat_lon_min, 2);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "lat_lon_min: " << setw(12) << lat_lon_min[0] << setw(12) << lat_lon_min[1] << endl;
#endif

  sec_vd_value_type lat_lon_max[2];
  levaluator.max(xlat_lon_dofs.base(), xlat_lon_dofs.ct(), lat_lon_max, 2);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "lat_lon_max: " << setw(12) << lat_lon_max[0] << setw(12) << lat_lon_max[1] << endl;
#endif

  // Put the bounds in the bounding box.

  d_bin_coordinates<2, 2> rel_pos;
  relative_position_pa(lat_lon_min, DB, rel_pos);
  bbox.put_lb(rel_pos);

  relative_position_pa(lat_lon_max, DB, rel_pos);
  bbox.put_ub(rel_pos);

  // Set the other attributes of the bounding box.

  bbox.put_member_id(xeval_id);
  bbox.put_branch_id(xbranch_id);
  bbox.put_evaluator(&levaluator);
  bbox.put_dof_ct(xlat_lon_dofs.ct());

#ifdef DIAGNOSTIC_OUTPUT

  cout << "bounding box: " << bbox << endl;
#endif

  // Insert the bounding box into the search structure.

  insert_box(&bbox);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::cylindrical_point_locator::
make_triangle_bounding_box(block<sec_vd_dof_type>& xlat_lon_dofs,
                           const scoped_index& xbranch_id,
                           const scoped_index& xeval_id)
{
  // Preconditions:


  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "lat lon dofs: " << xlat_lon_dofs << endl;
#endif

  static linear_2d levaluator;

  // Get a bounding box.

  _boxes.set_ct(_boxes.ct() + 1);
  d_bounding_box<2, 2>& bbox = _boxes.back();

  // Store the dofs.

  bbox.put_dofs_index(_gathered_dofs.ct());
  _gathered_dofs.push_back(xlat_lon_dofs);

  // Get the bounds for this eval member.

  sec_vd_value_type lat_lon_min[2];
  levaluator.min(xlat_lon_dofs.base(), xlat_lon_dofs.ct(), lat_lon_min, 2);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "lat_lon_min: " << setw(12) << lat_lon_min[0] << setw(12) << lat_lon_min[1] << endl;
#endif

  sec_vd_value_type lat_lon_max[2];
  levaluator.max(xlat_lon_dofs.base(), xlat_lon_dofs.ct(), lat_lon_max, 2);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "lat_lon_max: " << setw(12) << lat_lon_max[0] << setw(12) << lat_lon_max[1] << endl;
#endif

  // Put the bounds in the bounding box.

  d_bin_coordinates<2, 2> rel_pos;
  relative_position_pa(lat_lon_min, DB, rel_pos);
  bbox.put_lb(rel_pos);

  relative_position_pa(lat_lon_max, DB, rel_pos);
  bbox.put_ub(rel_pos);

  // Set the other attributes of the bounding box.

  bbox.put_member_id(xeval_id);
  bbox.put_branch_id(xbranch_id);
  bbox.put_evaluator(&levaluator);
  bbox.put_dof_ct(xlat_lon_dofs.ct());

#ifdef DIAGNOSTIC_OUTPUT

  cout << "bounding box: " << bbox << endl;
#endif

  // Insert the bounding box into the search structure.

  insert_box(&bbox);

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

///
geometry::cylindrical_point_locator&
geometry::cylindrical_point_locator::
operator=(const point_locator& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

///
geometry::cylindrical_point_locator&
geometry::cylindrical_point_locator::
operator=(const cylindrical_point_locator& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

bool
geometry::cylindrical_point_locator::
invariant() const
{
  bool result = true;

  invariance(coordinates().schema().df() == DC);

  return result;
}

void
geometry::cylindrical_point_locator::
update()
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering update");
#endif

  // Preconditions:

  require(coordinates().state_is_read_accessible());

  // Body:

  update_domain();
  update_bins();

  // For each coordinate field evaluator, we need to
  // create a bounding box and insert the bounding box into the search structure.
  // It's more efficient if we allocate all the bounding boxes at once.
  // It's also more efficient if we gather all the dofs for each evaluator
  // in advance. So find out how many evaluators we have:

  size_type leval_ct = coordinates().schema().evaluation_ct();

  // We need at least one bounding box for each evaluation_member,
  // two for any that straddle the dateline.

  _boxes.reserve(2*leval_ct);
  _boxes.set_ct(0);

  // Start the dof buffer off at a reasonable size.
  // We don't know how many dofs there are for each element,
  // but the buffer will resize as necessary.

  _gathered_dofs.reserve(leval_ct*8);
  _gathered_dofs.set_ct(0);

  block<sec_vd_dof_type> xyz_dofs(12);

  // Iterate over the branches.
  /// @hack the multisection hack.

  sec_vd lbranch;
  preorder_iterator lbranch_itr(coordinates(), "jims", DOWN, NOT_STRICT);
  while(!lbranch_itr.is_done())
  {
    // Get a handle to this branch.

    const scoped_index& lbranch_id = lbranch_itr.index();
    lbranch.attach_to_state(coordinates().host(), lbranch_id);

    // Re-anchor the eval itr to this branch.

    _eval_itr.put_schema_anchor(lbranch.schema().index());
    _eval_itr.reset(false);

    while(!_eval_itr.is_done())
    {
      // Gather the dofs for this eval member.

      xyz_dofs.set_ct(0);
      _eval_itr.gather_dofs(lbranch, xyz_dofs);

      // Insert this eval member into the search structure.

      size_type ldisc_ct = _eval_itr.discretization_members().ct();

      if(ldisc_ct == 4)
      {
        insert_quad(xyz_dofs, lbranch_id, _eval_itr.index());
      }
      else if(ldisc_ct == 3)
      {
        insert_triangle(xyz_dofs, lbranch_id, _eval_itr.index());
      }
      else
      {
        post_warning_message("Not a bilinear quad or linear triangle.");
      }

      // Move on to the next evaluator.

      _eval_itr.next();
    }

    // Move on to the next branch.

    lbranch_itr.truncate();
  }

  // Clean up.

  lbranch.detach_from_state();

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving update");
#endif

  return;
}

void
geometry::cylindrical_point_locator::
point_at_value(const sec_vd_value_type* xvalue,
               size_type xvalue_ub,
               chart_point& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= dc());
  require(xresult.db() >= db());

  // Body:

  sec_vd_value_type global_coords[DB];
  xyz_to_lat_lon(xvalue, global_coords);

  // Initialize the chart id to invalid.
  // If the inversion succeeds, it will be set to valid.

  xresult.invalidate();

  // Find the bounding boxes that may contain the value.

  d_bin_coordinates<DB, DB> lrel_pos;
  relative_position_pa(global_coords, DB, lrel_pos);

  const box_list_type& blist = box_list(global_coords, DB);

  // Iterate over the bounding boxes.

  box_list_type::const_iterator iter;

  for(iter = blist.begin(); !xresult.is_valid() && (iter != blist.end()); ++iter)
  {
    const d_bounding_box<DB, DB>* bbox = *iter;

    if(bbox->contains_point(lrel_pos))
    {
      // Found a cell with a bounding box that contains the value;
      // try inverting the value.

      section_evaluator* levaluator = bbox->evaluator();

      size_type dof_ct = bbox->dof_ct();
      sec_vd_dof_type* dofs = _gathered_dofs.base() + bbox->dofs_index();

      levaluator->coord_at_value(dofs,
                                 dof_ct,
                                 global_coords,
                                 DB,
                                 xresult.local_coords(),
                                 xresult.db());

      if(levaluator->in_standard_domain(xresult.local_coords(), xresult.db()))
      {
        // Inversion succeeded.
        // The coordinates are already stored in xresult_coords;
        // so just set the chart id.

        xresult.put_chart_id(bbox->member_id());
      }
      else
      {
        // Inversion failed.

        xresult.invalidate();
      }
    }
  }


  // Postconditions:

  ensure(unexecutable(xresult.is_valid() ?
                      xresult.chart() contains xvalue at xresult.local_coord() :
                      no chart contains xvalue));


  // Exit:

  return;
}

void
geometry::cylindrical_point_locator::
all_points_at_value(const sec_vd_value_type* xvalue,
                    size_type xvalue_ub,
                    block<chart_point_3d>& xresult)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering all_points_at_value");
#endif

  require(xvalue != 0);
  require(xvalue_ub >= dc());
  require(db() <= 3);

  // Body:

  sec_vd_value_type global_coords[DB];
  xyz_to_lat_lon(xvalue, global_coords);

  define_old_variable(int old_xresult_ct = xresult.ct());

  chart_point_3d lchart_pt(invalid_pod_index(), 0.0, 0.0, 0.0);

  // Find the bounding boxes that may contain the value.

  d_bin_coordinates<DB, DB> lrel_pos;
  relative_position_pa(global_coords, DB, lrel_pos);

  const box_list_type& blist = box_list(global_coords, DB);

  // Iterate over the bounding boxes.

  box_list_type::const_iterator iter;

  for(iter = blist.begin(); iter != blist.end(); ++iter)
  {
    const d_bounding_box<DB, DB>* bbox = *iter;

    if(bbox->contains_point(lrel_pos))
    {
      // Found a cell with a bounding box that contains the value;
      // try inverting the value.

      section_evaluator* levaluator = bbox->evaluator();

      size_type dof_ct = bbox->dof_ct();
      sec_vd_dof_type* dofs = _gathered_dofs.base() + bbox->dofs_index();

      levaluator->coord_at_value(dofs,
                                 dof_ct,
                                 global_coords,
                                 DB,
                                 lchart_pt.local_coords(),
                                 lchart_pt.db());

      if(levaluator->in_standard_domain(lchart_pt.local_coords(), lchart_pt.db()))
      {
        // Inversion succeeded.
        // The coordinates are already stored in lchart_pt coords;
        // so just set the chart id.

        lchart_pt.put_chart_id(bbox->member_id());
        xresult.push_back(lchart_pt);
      }
      else
      {
        // Inversion failed; do nothing.
      }
    }
  }


#ifdef DIAGNOSTIC_OUTPUT
  cout << "result: " << xresult << endl;
#endif

  // Postconditions:

  ensure_for_all(i, 0, xresult.ct(), xresult[i].is_valid());


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving all_points_at_value");
#endif

  return;
}

void
geometry::cylindrical_point_locator::
branch_points_at_value(const sec_vd_value_type* xvalue,
                       size_type xvalue_ub,
                       block<branch_point_pair>& xresult)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering branch_points_at_value");
#endif

  require(xvalue != 0);
  require(xvalue_ub >= dc());
  require(dc() <= 3);

  // Body:

  define_old_variable(int old_xresult_ct = xresult.ct());

  sec_vd_value_type global_coords[DB];
  xyz_to_lat_lon(xvalue, global_coords);

  branch_point_pair lbranch_pt;
  scoped_index& lbranch_id = lbranch_pt.first;
  chart_point_3d& lchart_pt = lbranch_pt.second;

  // Find the bounding boxes that may contain the value.

  d_bin_coordinates<DB, DB> lrel_pos;
  relative_position_pa(global_coords, DB, lrel_pos);

  const box_list_type& blist = box_list(global_coords, DB);

  // Iterate over the bounding boxes.

  box_list_type::const_iterator iter;

  for(iter = blist.begin(); iter != blist.end(); ++iter)
  {
    const d_bounding_box<DB, DB>* bbox = *iter;

#ifdef DIAGNOSTIC_OUTPUT

    cout << "considering " << *bbox << endl;
#endif

    lbranch_id = bbox->branch_id();
    if((_branches.find(lbranch_id) == _branches.end()) &&
        (bbox->contains_point(lrel_pos)))
    {

#ifdef DIAGNOSTIC_OUTPUT
      cout << "Inverting it ... ";
#endif
      // Haven't found a point for this branch yet and we've
      // found a cell with a bounding box that contains the value;
      // try inverting the value.

      section_evaluator* levaluator = bbox->evaluator();


      size_type dof_ct = bbox->dof_ct();
      sec_vd_dof_type* dofs = _gathered_dofs.base() + bbox->dofs_index();

      levaluator->coord_at_value(dofs,
                                 dof_ct,
                                 global_coords,
                                 DB,
                                 lchart_pt.local_coords(),
                                 lchart_pt.db());

      if(levaluator->in_standard_domain(lchart_pt.local_coords(), lchart_pt.db()))
      {
        // Inversion succeeded.
        // The coordinates are already stored in lchart_pt coords;
        // so just set the chart id.

#ifdef DIAGNOSTIC_OUTPUT
        cout << "valid" << endl;
#endif

        lchart_pt.put_chart_id(bbox->member_id());
        xresult.push_back(lbranch_pt);

        // We've found a point for this branch.

        _branches.insert(lbranch_id);
      }
      else
      {
        // Inversion failed; do nothing.

#ifdef DIAGNOSTIC_OUTPUT
        cout << "invalid" << endl;
#endif

      }
    }
    else
    {
#ifdef DIAGNOSTIC_OUTPUT
      cout << "Ignoring it" << endl;
#endif

    }

  }

  // Clean up.

  _branches.clear();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "result: " << xresult << endl;
#endif

  // Postconditions:

  ensure(xresult.ct() >= old_xresult_ct);
  ensure_for_all(i, old_xresult_ct, xresult.ct(),
                 coordinates().host()->contains_member(xresult[i].first, false));
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].second.is_valid());


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving branch_points_at_value");
#endif

  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
