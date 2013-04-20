

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_triangle

#include "kd_triangle.h"

#include "assert_contract.h"
#include "cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_lattice.h"
#include "kd_line.h"
#include "kd_line_fragment.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_region.h"
#include "kd_zone_cohort.h"
#include "sec_e3.h"
#include "std_algorithm.h"
#include "subcohort.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;
using namespace fiber_bundle::ed_algebra;
using namespace fiber_bundle::e3_algebra;

// namespace
// {

//
// True if the three points in xpts are collinear, or nearly so.
//
bool is_collinear(const e3_lite xpts[])
{
  return c_eql(xpts[0], xpts[1]) || c_eql(xpts[1], xpts[2]) || c_eql(xpts[2], xpts[0]);
}
  

//
// Finds or creates the intersection point associated with the triangle vertex xv_id.
//
void get_vertex_intersection(kd_lattice& xhost,
                             const scoped_index& xv_id, 
                             const e3_lite& xv, 
                             scoped_index& xresult)
{
  // cout << "Entering kd_triangle.cc:get_vertex_intersection." << endl;
  // cout << "vertex: " << setw(6) << xv_id.pod() << " (" << xv << ")" << endl;
  
  // Find or create the intersection point.
      
  pod_pair ledge;
  kd_lattice::iline_map_type& lmap = xhost.iline_map();
  kd_lattice::iline_map_type::iterator ledge_itr;

  ledge.first = xv_id.pod();
  ledge.second = xv_id.pod();
  ledge_itr = lmap.find(ledge);

  if(ledge_itr != lmap.end())
  {
    // Intersection with edge already exists.

    xresult = ledge_itr->second;

    // cout << "Found existing vertex: " << setw(6) << xresult.pod() << " (" << xv << ")" << endl;
  }
  else
  {
    // Allocate a new point.

    xresult.put_pod(xhost.iline_pts().ct());
    xhost.iline_pts().push_back(xv);

    // Insert the intersection in the map.

    lmap[ledge] = xresult;

    // cout << "Allocated new vertex: " << setw(6) << xresult.pod() << " (" << xv << ")" << endl;
  }

  // cout << "Leaving kd_triangle.cc:get_vertex_intersection." << endl;
  return;
}

//
// Finds or creates the intersection associated with the entire triangle edge defined by pts xv0_id and xv1_id.
//
bool get_edge_intersection(kd_lattice& xhost,
                           const kd_plane& xp,
                           const scoped_index& xv0_id, 
                           const e3_lite& xv0, 
                           const scoped_index& xv1_id, 
                           const e3_lite& xv1,
                           scoped_index& xpta_id,
                           scoped_index& xptb_id)
{
  // cout << "Entering kd_triangle.cc:get_edge_intersection." << endl;
  // cout << "edge: " << setw(6) << xv0_id.pod() << " " << xv0 << setw(6) << xv1_id.pod() << " " << xv1 << endl;
      
  pod_pair ledge;
  kd_lattice::iline_map_type& lmap = xhost.iline_map();
  kd_lattice::iline_map_type::iterator ledge_itr;

  // Check if we've seen this edge before.

  ledge.first = xv0_id.pod();
  ledge.second = xv1_id.pod();
  ledge_itr = lmap.find(ledge);

  bool result;
  if(ledge_itr != lmap.end())
  {
    // We've seen the edge before

    // cout << "Found existing edge" << endl;
    result = false;
  }
  else
  {
    // Insert the edge in the map
    // so we'll know the next time we see it.
    // Actual value of map is irrelevant

    scoped_index linvalid;
    lmap[ledge] = linvalid;
    pod_pair ledge_rev(ledge.second, ledge.first);
    lmap[ledge_rev] = linvalid;
  
    // cout << "Allocated new edge: " << endl;

    // Find or create intersection point a.

    ledge.first = xv0_id.pod();
    ledge.second = xv0_id.pod();
    ledge_itr = lmap.find(ledge);

    if(ledge_itr != lmap.end())
    {
      // Point a already exists

      xpta_id = ledge_itr->second;
    }
    else
    {
      // Allocate a new point.

      xpta_id.put_pod(xhost.iline_pts().ct());
      xhost.iline_pts().push_back(xv0);

      // Insert the intersection in the map.

      lmap[ledge] = xpta_id;
    }
  
    // Find or create intersection point b.

    ledge.first = xv1_id.pod();
    ledge.second = xv1_id.pod();
    ledge_itr = lmap.find(ledge);

    if(ledge_itr != lmap.end())
    {
      // Point b already exists

      xptb_id = ledge_itr->second;
    }
    else
    {
      // Allocate a new point.

      xptb_id.put_pod(xhost.iline_pts().ct());
      xhost.iline_pts().push_back(xv1);

      // Insert the intersection in the map.

      lmap[ledge] = xptb_id;
    }

    result = true;
  }
  
  

  // cout << "Leaving kd_triangle.cc:get_edge_intersection." << endl;
 return result;
}

//
// Finds or creates the intersection point contained in the triangle edge defined by pts xv0_id and xv1_id.
//
void get_point_intersection(kd_lattice& xhost,
                            const kd_plane& xp,
                            const scoped_index& xv0_id, 
                            const e3_lite& xv0, 
                            const scoped_index& xv1_id, 
                            const e3_lite& xv1,
                            scoped_index& xresult)
{ 
  // cout << "Entering kd_triangle.cc:get_point_intersection." << endl;
  // cout << "edge: " << setw(6) << xv0_id.pod() << " " << xv0 << setw(6) << xv1_id.pod() << " " << xv1 << endl;
  // cout << "plane: " << xp << endl;
  
  // Find or create intersection point a.
      
  pod_pair ledge;
  kd_lattice::iline_map_type& lmap = xhost.iline_map();
  kd_lattice::iline_map_type::iterator ledge_itr;

  ledge.first = xv0_id.pod();
  ledge.second = xv1_id.pod();
  ledge_itr = lmap.find(ledge);

  if(ledge_itr != lmap.end())
  {
    // Intersection with edge already exists.

    xresult = ledge_itr->second;

    // cout << "Found existing point: " << setw(6) << xresult.pod() << " (" << xhost.iline_pts()[xresult.pod()] << ")" << endl;
  }
  else
  {
    // Compute the intersection coordinates.

    int lp_axis = xp.int_alignment();
    vd_value_type lu = (xp.distance() - xv0[lp_axis]) / (xv1[lp_axis] - xv0[lp_axis]);
    e3_lite lpt;
    add(xv0, xv1, lu, lpt);

    // Allocate a new point.

    xresult.put(xhost.base_space().member_hub_id_space(false), xhost.iline_pts().ct());
    xhost.iline_pts().push_back(lpt);

    // Insert the intersection in the map.

    lmap[ledge] = xresult;
    pod_pair ledge_rev(ledge.second, ledge.first);
    lmap[ledge_rev] = xresult;

    // cout << "Allocated new point: " << setw(6) << xresult.pod() << " (" << xhost.iline_pts()[xresult.pod()] << ")"  << endl;
  }

  // cout << "Leaving kd_triangle.cc:get_point_intersection." << endl;
  return;
}

  
    

// }

  
  
// } // end unnamed namespace.

// ===========================================================
// KD_TRIANGLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_triangle::
prototype_name()
{
  // cout << endl << "Entering kd_triangle::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("triangle");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_triangle::prototype_name." << endl;
  return result;
}

geometry::kd_triangle::
kd_triangle(kd_lattice& xhost, const scoped_index xv_ids[])
  :kd_member(xhost)
{
  // cout << endl << "Entering kd_triangle::kd_triangle." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, POINT_CT, xhost.base_space().vertices().contains_member(xv_ids[i]));
    
  define_old_variable(size_type old_triangles_ct = xhost.triangles().ct());
  define_old_variable(size_type old_points_ct = xhost.points().ct());

  // Body:

  _id = new_triangle(xhost, xv_ids);
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().triangles().contains(id()));
  ensure(host().triangles().ct() == old_triangles_ct + 1);
  ensure(host().points().ct() == old_points_ct);
  ensure(point(0) == xv_ids[0]);
  ensure(point(1) == xv_ids[1]);

  // Exit:

  // cout << "Leavinging kd_triangle::kd_triangle." << endl;
  return; 
}

geometry::scoped_index
geometry::kd_triangle::
new_triangle(kd_lattice& xhost, const scoped_index xv_ids[])
{
  // cout << endl << "Entering kd_triangle::new_triangle." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, POINT_CT, xhost.base_space().vertices().contains_member(xv_ids[i]));
  //  require(xhost.centroids().contains(xv_ids[2]));

  define_old_variable(size_type old_triangles_ct = xhost.triangles().ct());
  define_old_variable(size_type old_points_ct = xhost.points().ct());
    
  // Body:

  base_space_poset& lbase = xhost.base_space();  

  // Create the triangle.

  scoped_index result = xhost.triangles().new_member();

  // The triangle covers the points.

  lbase.new_link(result, xv_ids[0]);
  lbase.new_link(result, xv_ids[1]);
  lbase.new_link(result, xv_ids[2]);

  // Postconditions:

  ensure(xhost.triangles().contains(result));
  ensure(xhost.triangles().ct() == old_triangles_ct + 1);
  ensure(xhost.points().ct() == old_points_ct);
  ensure(point(xhost, result, 0) == xv_ids[0]);
  ensure(point(xhost, result, 1) == xv_ids[1]);
  ensure(point(xhost, result, 2) == xv_ids[2]);

  // Exit:

  // cout << "Leaving kd_triangle::new_triangle." << endl;
  return result; 
}

geometry::scoped_index
geometry::kd_triangle::
new_triangle(kd_lattice& xhost, const scoped_index& xpt0_id, const scoped_index& xpt1_id, const scoped_index& xpt2_id)
{
  // cout << endl << "Entering kd_triangle::new_triangle." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.base_space().vertices().contains_member(xpt0_id));
  require(xhost.base_space().vertices().contains_member(xpt1_id));
  require(xhost.base_space().vertices().contains_member(xpt2_id));
  //  require(xhost.centroids().contains(xpt2_id));

  define_old_variable(size_type old_triangles_ct = xhost.triangles().ct());
  define_old_variable(size_type old_points_ct = xhost.points().ct());
    
  // Body:

  base_space_poset& lbase = xhost.base_space();  

  // Create the triangle.

  scoped_index result = xhost.triangles().new_member();

  // cout << "tri: " << result << "  " << name(xhost, result);
  // cout << "  v0: " << xpt0_id;
  // cout << "  v1: " << xpt1_id;
  // cout << "  v2: " << xpt2_id;
  // cout << endl;

  // The triangle covers the points.

  lbase.new_link(result, xpt0_id);
  lbase.new_link(result, xpt1_id);
  lbase.new_link(result, xpt2_id);

  // Postconditions:

  ensure(xhost.triangles().contains(result));
  ensure(xhost.triangles().ct() == old_triangles_ct + 1);
  ensure(xhost.points().ct() == old_points_ct);
  ensure(point(xhost, result, 0) == xpt0_id);
  ensure(point(xhost, result, 1) == xpt1_id);
  ensure(point(xhost, result, 2) == xpt2_id);

  // Exit:

  // cout << "Leaving kd_triangle::new_triangle." << endl;
  return result; 
}

geometry::kd_triangle::
kd_triangle(kd_lattice& xhost, const scoped_index& xid)
  : kd_member(xhost, xid)
{
  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(id() == xid);

  // Exit:

  return; 
}

geometry::kd_triangle::
kd_triangle(const kd_triangle& xother)
  : kd_member(xother)
{
  
  // Preconditions:

    
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_triangle::
~kd_triangle()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_triangle::
members(id_list& xmbrs, bool xterminate) const
{
  // Preconditions:

  require(precondition_of(members(host(),id(), xmbrs)));
  
  // Body:

  members(*_host, _id, xmbrs, xterminate);
  
  // Postconditions:

  ensure(postcondition_of(members(host(),id(), xmbrs)));

  // Exit:

  return;
}

void
geometry::kd_triangle::
members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs, bool xterminate)
{
  // cout << endl << "Entering kd_triangle::members." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));

  define_old_variable(size_type old_xmbrs_size = xmbrs.size());
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  assertion(is_valid(litr.hub_pod()));

  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    xmbrs.push_back(lid);
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);

  if(xterminate)
  {
    // Add the terminator.

    scoped_index linvalid;
    xmbrs.push_back(linvalid);
  }  

  // Postconditions:

  ensure(xmbrs.size() >= old_xmbrs_size);
  ensure(xterminate ? !xmbrs.back().is_valid() : true);

  // Exit:

  // cout << "Leaving kd_triangle::members." << endl;
  return;
}

void
geometry::kd_triangle::
members(id_list& xmbrs, list<e3_lite>& xcoords, bool xterminate) const
{
  // Preconditions:

  require(precondition_of(members(host(), id(), xmbrs, xcoords)));
  
  // Body:

  members(*_host, _id, xmbrs, xcoords, xterminate);
  
  // Postconditions:

  ensure(postcondition_of(members(host(), id(), xmbrs, xcoords)));

  // Exit:

  return;
}

void
geometry::kd_triangle::
members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs, list<e3_lite>& xcoords, bool xterminate)
{
  // cout << endl << "Entering kd_triangle::members." << endl;
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  define_old_variable(size_type old_xmbrs_size = xmbrs.size());
  define_old_variable(size_type old_xcoords_size = xcoords.size());

  // Body:

  e3_lite lpt;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  assertion(is_valid(litr.hub_pod()));

  scoped_index linvalid_id;
  e3_lite linvalid_coords;

  scoped_index lid(xhost.base_space().member_id(false));

  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    xmbrs.push_back(lid);
    litr.next();
    xhost.coords().get_fiber(lid, lpt, false);
    xcoords.push_back(lpt);
  }

  xhost.base_space().release_cover_id_space_iterator(litr);

  if(xterminate)
  {
    xmbrs.push_back(linvalid_id);
    xcoords.push_back(linvalid_coords);
  }  

  // Postconditions:

  ensure(xmbrs.size() >= old_xmbrs_size);
  ensure(xcoords.size() >= old_xcoords_size);
  ensure(xterminate ? !xmbrs.back().is_valid() : true);

  // Exit:

  // cout << "Leaving kd_triangle::members." << endl;
  return;
}

void
geometry::kd_triangle::
points(scoped_index xresult[]) const
{
  // Preconditions:

  require(precondition_of(points(host(), id(), xresult)));  
  
  // Body:

  points(*_host, _id, xresult);
  
  // Postconditions:

  ensure(postcondition_of(points(host(), id(), xresult)));

  // Exit:

  return;
}

void
geometry::kd_triangle::
points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_triangle::points." << endl;
  // Preconditions:

  require(unexecutable("xresult is an array with at least POINT_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  xresult[0] = xhost.base_space().member_id(litr.hub_pod(), false);
  litr.next();
  xresult[1] = xhost.base_space().member_id(litr.hub_pod(), false);
  litr.next();
  xresult[2] = xhost.base_space().member_id(litr.hub_pod(), false);
  litr.next();

  assertion(litr.is_done());
  
  xhost.base_space().release_cover_id_space_iterator(litr);

  // cout << "result[0]: " << xresult[0].internal_pod() << endl;
  // cout << "result[1]: " << xresult[1].internal_pod() << endl;


  // Postconditions:

  ensure_for_all(i, 0, POINT_CT, xhost.base_space().vertices().contains_member(xresult[i]));
  //  ensure(xhost.centroids().contains(xresult[2]));
  
  // Exit:

  // cout << "Leaving kd_triangle::points." << endl;
  return;
}

void
geometry::kd_triangle::
points(scoped_index xresult[], e3_lite xcoords[]) const
{
  // Preconditions:

  require(precondition_of(points(host(), id(), xresult, xcoords)));
  
  // Body:

  points(*_host, _id, xresult, xcoords);
  
  // Postconditions:

  ensure(postcondition_of(points(host(), id(), xresult, xcoords)));

  // Exit:

  return;
}

void
geometry::kd_triangle::
points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[], e3_lite xcoords[])
{
  // cout << endl << "Entering kd_triangle::points." << endl;
  // Preconditions:

  require(unexecutable("xresult is an array with at least POINT_CT entries"));
  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  // Body:

  points(xhost, xid, xresult);
  xhost.coords().get_fiber(xresult[0], xcoords[0], false);
  xhost.coords().get_fiber(xresult[1], xcoords[1], false);
  xhost.coords().get_fiber(xresult[2], xcoords[2], false);

  // Postconditions:

  ensure_for_all(i, 0, POINT_CT, xhost.base_space().vertices().contains_member(xresult[i]));
  //  ensure(xhost.centroids().contains(xresult[2]));
  ensure_for_all(i, 0, POINT_CT, xcoords[i] == kd_point::coords(xhost, xresult[i]));

  // Exit:

  // cout << "Leaving kd_triangle::points." << endl;
  return;
}


sheaf::scoped_index
geometry::kd_triangle::
point(int xi) const
{
  // cout << endl << "Entering kd_triangle::point." << endl;

  // Preconditions:

  require(precondition_of(point(host(), id(), xi)));

  // Body:

  scoped_index result = point(*_host, _id, xi);

  // Postconditions:

  ensure(postcondition_of(point(host(), id(), xi)));

  // Exit:

  // cout << "Leaving kd_triangle::point." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_triangle::
point(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_triangle::point." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  require((0 <= xi) && (xi < POINT_CT));

  // Body:  

  int li = 0;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  while(li < xi)
  {
    litr.next();
    ++li;
  }
  
  assertion(li == xi);
  
  scoped_index result = xhost.base_space().member_id(litr.hub_pod(), false);

  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xhost.base_space().vertices().contains_member(result));
  //  ensure(xi == 2 ? xhost.centroids().contains(result) : true);
  
  // Exit:

  // cout << "Leaving kd_triangle::point." << endl;
  return result;
}

void
geometry::kd_triangle::
coord_bounds(e3_lite& xlb, e3_lite& xub) const
{
  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().coords().state_is_read_accessible());

  // Body:

  coord_bounds(*_host, _id, xlb, xub);
  
  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_triangle::
coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub)
{
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));

  // Body:

  // Get the point ids.

  scoped_index lv_ids[POINT_CT];
  e3_lite lv_coords[POINT_CT];
  points(xhost, xid, lv_ids, lv_coords);

  xlb = lv_coords[0];
  xub = lv_coords[0];
  
  xlb[0] = lv_coords[1][0] < xlb[0] ? lv_coords[1][0] : xlb[0];
  xlb[1] = lv_coords[1][1] < xlb[1] ? lv_coords[1][1] : xlb[1];
  xlb[2] = lv_coords[1][2] < xlb[2] ? lv_coords[1][2] : xlb[2];
  
  xlb[0] = lv_coords[2][0] < xlb[0] ? lv_coords[2][0] : xlb[0];
  xlb[1] = lv_coords[2][1] < xlb[1] ? lv_coords[2][1] : xlb[1];
  xlb[2] = lv_coords[2][2] < xlb[2] ? lv_coords[2][2] : xlb[2];
  
  xub[0] = lv_coords[1][0] < xub[0] ? lv_coords[1][0] : xub[0];
  xub[1] = lv_coords[1][1] < xub[1] ? lv_coords[1][1] : xub[1];
  xub[2] = lv_coords[1][2] < xub[2] ? lv_coords[1][2] : xub[2];
  
  xub[0] = lv_coords[2][0] < xub[0] ? lv_coords[2][0] : xub[0];
  xub[1] = lv_coords[2][1] < xub[1] ? lv_coords[2][1] : xub[1];
  xub[2] = lv_coords[2][2] < xub[2] ? lv_coords[2][2] : xub[2];
  
  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::e3_lite
geometry::kd_triangle::
coord_lower_bound() const
{
  // cout << endl << "Entering kd_triangle::coord_lower_bound." << endl;

  // Preconditions:

  require(precondition_of(coord_lower_bound(host(), id())));

  // Body:

  e3_lite result = coord_lower_bound(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(coord_lower_bound(host(), id())));

  // Exit:

  // cout << "Leaving kd_triangle::coord_lower_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_triangle::
coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_triangle::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));

  // Body:

  e3_lite result, lub;
  coord_bounds(xhost, xid, result, lub);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_triangle::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_triangle::
coord_upper_bound() const
{
  // cout << endl << "Entering kd_triangle::coord_upper_bound." << endl;

  // Preconditions:

  require(precondition_of(coord_upper_bound(host(), id())));

  // Body:

  e3_lite result = coord_upper_bound(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(coord_upper_bound(host(), id())));

  // Exit:

  // cout << "Leaving kd_triangle::coord_upper_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_triangle::
coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_triangle::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.triangles().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  e3_lite llb, result;
  coord_bounds(xhost, xid, llb, result);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_triangle::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_triangle::
surface()
{
  // cout << endl << "Entering kd_triangle::surface." << endl;

  // Preconditions:

  require(precondition_of(surface(host(), id())));

  // Body:

  scoped_index result = surface(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(surface(host(), id())));

  // Exit:

  // cout << "Leaving kd_triangle::surface." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_triangle::
surface(const kd_lattice& xhost, const scoped_index xid)
{
  // cout << endl << "Entering kd_triangle::surface." << endl;

  // Preconditions:

  require(precondition_of(surface(xhost, xid, result)));

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  // Body:

  scoped_index result;
  surface(xhost, xid, result);
  
  // Postconditions:

  ensure(postcondition_of(surface(xhost, xid, result)));
  
  // Exit:

  // cout << "Leaving kd_triangle::surface." << endl;
  return result;
}

void
geometry::kd_triangle::
surface(scoped_index& xresult)
{
  // cout << endl << "Entering kd_triangle::surface." << endl;

  // Preconditions:

  require(precondition_of(surface(host(), id(), xresult)));

  // Body:

  surface(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(surface(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_triangle::surface." << endl;
  return;
}

void
geometry::kd_triangle::
surface(const kd_lattice& xhost, const scoped_index xid, scoped_index& xresult)
{
  // cout << endl << "Entering kd_triangle::surface." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  // Body:

  xresult = xhost.base_space().member_id(false);
  xresult.invalidate();

  // $$SCRIBBLE: is the surface always the second member of the upper cover?
  
  const subposet& lsurfaces = xhost.surfaces().sp();
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  while(!litr.is_done())
  {
    if(lsurfaces.contains_member(litr.hub_pod()))
    {
      xresult = litr.hub_pod();
      break;
    }
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xresult.is_valid() ? xhost.surfaces().contains(xresult) : true);
  
  // Exit:

  // cout << "Leaving kd_triangle::surface." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_triangle::
zone()
{
  // cout << endl << "Entering kd_triangle::zone." << endl;

  // Preconditions:

  require(precondition_of(zone(host(), id())));

  // Body:

  scoped_index result = zone(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(zone(host(), id())));

  // Exit:

  // cout << "Leaving kd_triangle::zone." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_triangle::
zone(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_triangle::zone." << endl;

  // Preconditions:

  require(precondition_of(zone(xhost, xid, result)));

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  // Body:

  scoped_index result;
  zone(xhost, xid, result);
  
  // Postconditions:

  ensure(postcondition_of(zone(xhost, xid, result)));
  
  // Exit:

  // cout << "Leaving kd_triangle::zone." << endl;
  return result;
}

void
geometry::kd_triangle::
zone(scoped_index& xresult)
{
  // cout << endl << "Entering kd_triangle::zone." << endl;

  // Preconditions:

  require(precondition_of(zone(host(), id(), xresult)));

  // Body:

  zone(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(zone(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_triangle::zone." << endl;
  return;
}

void
geometry::kd_triangle::
zone(const kd_lattice& xhost, const scoped_index& xid, scoped_index& xresult)
{
  // cout << endl << "Entering kd_triangle::zone." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  
  // Body:

  xresult = xhost.base_space().member_id(false);
  xresult.invalidate();

  // $$SCRIBBLE: is the zone always the first member of the upper cover?
  
  const subposet& lzones = xhost.zones().sp();
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  while(!litr.is_done())
  {
    if(lzones.contains_member(litr.hub_pod()))
    {
      xresult = litr.hub_pod();
      break;
    }
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.is_valid() ? xhost.zones().contains(xresult) : true);
  
  // Exit:

  // cout << "Leaving kd_triangle::zone." << endl;
  return;
}

void
geometry::kd_triangle::
clear(scoped_index xpoints[])
{
  // cout << endl << "Entering kd_triangle::clear." << endl;

  // Preconditions:

  require(precondition_of(clear(host(), id(), xpoints)));

  // Body:

  clear(*_host, _id, xpoints);

  // Postconditions:

  ensure(postcondition_of(clear(host(), id(), xpoints)));

  // Exit:

  // cout << "Leaving kd_triangle::clear." << endl;
  return;
}

void
geometry::kd_triangle::
clear(kd_lattice& xhost, const scoped_index& xid, scoped_index xpoints[])
{
  // cout << endl << "Entering kd_triangle::clear." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.triangles().contains(xid));
  require(unexecutable("xpoints is an array of size at least POINT_CT"));

  define_old_variable(scoped_index old_point_0 = point(xhost, xid, 0));
  define_old_variable(scoped_index old_point_1 = point(xhost, xid, 1));
  define_old_variable(scoped_index old_point_2 = point(xhost, xid, 2));
  define_old_variable(bool old_centroids_contains_old_point_2 = xhost.centroids().contains(old_point_2));
  

  // Body:

  base_space_poset& lbase = xhost.base_space();
  
  lbase.clear_cover(UPPER, xid);

  scoped_index lid;
  
  for(int i=0; i<POINT_CT; ++i)
  {
    lbase.first_cover_member(LOWER, xid, lid);
    xpoints[i] = lid;

    // cout << "i: " << i << "  pt_id: " << lid.pod() << "  upper_cover: " << lbase.cover_iterator(UPPER, lid) << endl;
    
    lbase.delete_link(xid, lid);
  }

  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, xid));
  ensure(xhost.base_space().cover_is_empty(LOWER, xid));
  ensure(xpoints[0] == old_point_0);
  ensure(xpoints[1] == old_point_1);
  ensure(xpoints[2] == old_point_2);
  ensure(xhost.centroids().contains(xpoints[2]) == old_centroids_contains_old_point_2);
  
  // Exit:

  // cout << "Leaving kd_triangle::clear." << endl;
  return;
}

void
geometry::kd_triangle::
deactivate()
{
  // cout << endl << "Entering kd_triangle::deactivate." << endl;

  // Preconditions:

  require(precondition_of(deactivate(host(), id())));

  // Body:

  deactivate(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(deactivate(host(), id())));

  // Exit:

  // cout << "Leaving kd_triangle::deactivate." << endl;
  return;
}

void
geometry::kd_triangle::
deactivate(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_triangle::deactivate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.triangles().contains(xid));
  require(xhost.base_space().cover_is_empty(LOWER, xid));
  require(xhost.base_space().cover_is_empty(UPPER, xid));
  

  // Body:

  xhost.triangles().delete_member(xid);
  
  // Postconditions:

  ensure(!xhost.triangles().is_active(xid));
  
  // Exit:

  // cout << "Leaving kd_triangle::deactivate." << endl;
  return;
}

// void
// geometry::kd_triangle::
// refine(const kd_plane& xp, id_list& xback_tris, id_list& xfront_tris, id_list& xsegs)
// {
//   // cout << endl << "Entering kd_triangle::refine." << endl;

//   // Preconditions:

//   require(precondition_of(refine(host(), id(), xback_tris, xfront_tris, xsegs)));

//   // Body:

//   refine(*_host, _id, xback_tris, xfront_tris, xsegs);

//   // Postconditions:

//   ensure(postcondition_of(refine(host(), id(), xback_tris, xfront_tris, xsegs)));

//   // Exit:

//   // cout << "Leaving kd_triangle::refine." << endl;
//   return;
// }

// void
// geometry::kd_triangle::
// intersect(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, frag_list& xfrags)
// {
//   // cout << endl << "Entering kd_triangle::refine." << endl;

//   // Preconditions:

//   require(xhost.base_space().in_jim_edit_mode());
//   require(xhost.coords().state_is_read_write_accessible());
//   require(xhost.triangles().contains(xid));
  

//   // Body:

//   int lp_axis = xp.int_alignment();
//   vd_value_type lp_dist = xp.distance();

//   vd_value_type lpt_dist;
//   int lpt_code[3];
  

//   scoped_index lpt_ids[POINT_CT];
//   e3_lite lpts[POINT_CT];
  
//   points(xhost, xid, lpt_ids, lpts);

//   int lpt_code_sum = 0;
//   int lpt_code_0_ct = 0;
//   for(int p = 0; p < 3; ++p)
//   {
//     lpt_dist = lpt[i][lp_axis];
//     lpt_code[i] = c_eql(lpt_dist, lp_dist) ? 0 : (lpt_dist < lp_dist ? -1 : 1);
//     lpt_code_sum += lpt_code[i];
//     if(lpt_code[i] == 0)
//     {
//       lpt_code_0_ct++;
//     }
//   }

//   //  pt0   pt1   pt2   sum   0ct  Interpretation

//   //  +-1   +-1   +-1   +-3   0    no intersection, +front, -back
//   //
//   //  -+1   +-1   +-1   +-1   0    intersection opposite pt0
//   //  +-1   -+1   +-1   +-1   0    intersection opposite pt1
//   //  +-1   +-1   -+1   +-1   0    intersection opposite pt2

//   //    0   +-1   -+1     0   1    intersection through pt0  
//   //  +-1     0   -+1     0   1    intersection through pt1
//   //  +-1   -+1     0     0   1    intersection through pt2

//   //    0   +-1   +-1   +-2   1    pt0 touches plane, no intersection, +front, -back
//   //  +-1     0   +-1   +-2   1    pt1 vertex touches plane, no intersection, +front, -back
//   //  +-1   +-1     0   +-2   1    pt2 vertex touches plane, no intersection, +front, -back
  
//   //  +-1     0     0   +-1   2    edge 12 is intersection
//   //    0   +-1     0   +-1   2    edge 02 is intersection
//   //    0     0   +-1   +-1   2    edge 01 is intersection

//   //    0     0     0     0   3    triangle is in plane; no intersection, front

//   int labs_pt_code_sum = abs(lpt_code_sum);
  
//   if(labs_pt_code_sum == 3)
//   {
//     // No intersection

//     if(lpt_code_sum < 0)
//     {
//       xback_tris.push_back(xid);
//     }
//     else
//     {
//       xfront_tris.push_back(xid);
//     }
//   }
//   else if((labs_pt_code_sum == 1) && (lpt_code_0_ct == 0))
//   {
//     // Intersection opposite a point.

//     refine_opposite_vertex(xhost, xid, xp, lpt_ids, lpts, lpt_code, lpt_code_sum, xsegs); 
//   }
  
    


//   // Postconditions:

//   ensure(!xhost.triangles().is_active(xid));
  
//   // Exit:

//   // cout << "Leaving kd_triangle::refine." << endl;
//   return;
// }


void
geometry::kd_triangle::
intersect_plane(const kd_plane& xp, const scoped_index& xzone_id, frag_list& xfrags)
{
  // cout << endl << "Entering kd_triangle::intersect_plane." << endl;

  // Preconditions:

  require(precondition_of(intersect_plane(host(), id(), xp, xzone_id, xfrags)));

  // Body:

  intersect_plane(*_host, _id, xp, xzone_id, xfrags);

  // Postconditions:

  ensure(postcondition_of(intersect_plane(host(), id(), xp, xzone_id, xfrags)));

  // Exit:

  // cout << "Leaving kd_triangle::intersect_plane." << endl;
  return;
}


void
geometry::kd_triangle::
intersect_plane(kd_lattice& xhost, 
                const scoped_index& xid, 
                const kd_plane& xp, 
                const scoped_index& xzone_id, 
                frag_list& xfrags)
{
  // cout << endl << "Entering kd_triangle::intersect_plane." << endl;
  // cout << "triangle: " << xid.pod() << endl;
  // cout << "zone: " << xzone_id.pod() << endl;
  
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  require(unexecutable("xfrags.pt_ids.back() is contained in the boundary of this triangle"));

  // Body:

  int lp_axis = xp.int_alignment();
  vd_value_type lp_dist = xp.distance();

  vd_value_type lpt_dist;
  int lpt_code[POINT_CT];
  

  scoped_index lpt_ids[POINT_CT];
  e3_lite lpts[POINT_CT];
  
  points(xhost, xid, lpt_ids, lpts);

  int lpt_code_sum = 0;
  int lpt_code_0_ct = 0;
  for(int p = 0; p < POINT_CT; ++p)
  {
    lpt_dist = lpts[p][lp_axis];
    lpt_code[p] = sheaf::c_eql(lpt_dist, lp_dist) ? 0 : (lpt_dist < lp_dist ? -1 : 1);
    lpt_code_sum += lpt_code[p];
    if(lpt_code[p] == 0)
    {
      lpt_code_0_ct++;
    }
  }

  // Point code cases enumerated:
    
  //   pt0   pt1   pt2   sum   0ct  interpreation
  //    -1    -1    -1    -3     0  all points behind plane, no intersection
  //    -1    -1     0    -2     1  pt2 touches plane, no intersection
  //    -1    -1    +1    -1     0  plane intersects edge 12 and 20
  //    -1     0    -1    -2     1  pt1 touches plane, no intersection
  //    -1     0     0    -1     2  plane intersects at edge 12
  //    -1     0    +1     0     1  plane intersects pt1 and edge 20
  //    -1    +1    -1    -1     0  plane intersects edges 01 and 12
  //    -1    +1     0     0     1  plane intersects pt2 and edge 01
  //    -1    +1    +1    -1     0  plane intersects edges 01 and 20
  //     0    -1    -1    -2     1  pt0 touches plane, no intersection
  //     0    -1     0    -1     2  plane intersects edge 20
  //     0    -1    +1     0     1  plane intersects at pt0 and edge 12
  //     0     0    -1    -1     2  plane intersects edge 01
  //     0     0     0     0     3  the entire triangle lies in the plane
  //     0     0    +1    +1     2  plane intersects edge 01
  //     0    +1    -1     0     1  plane intersects pt0 and edge 12
  //     0    +1     0    +1     2  plane intersects edge 20
  //     0    +1    +1    +2     1  plane touches pt0, no intersection
  //    +1    -1    -1    -1     0  plane intersects edge 01 and 20
  //    +1    -1     0     0     1  plane intersects pt2 and edge 01
  //    +1    -1    +1    -1     0  plane intersects edge 01 and 12
  //    +1     0    -1     0     1  plane intersects pt1 and edge 20
  //    +1     0     0    +1     2  plane intersects edge 12
  //    +1     0    +1    +2     1  plane touches pt1, no intersection
  //    +1    +1    -1    -1     0  plane intersects edges 20 and 12
  //    +1    +1     0    +2     1  plane touches pt2, no intersection
  //    +1    +1    +1    +3     0  all points in front of plane, no intersection

  // Point code cases enumerated, sorted on abs(sum) and 0 ct, with distinguishing condition
    
  //   pt0   pt1   pt2   sum   0ct  interpreation
  //    -1    -1    -1    -3     0  all points behind plane, no intersection
  //    +1    +1    +1    +3     0  all points in front of plane, no intersection

  //    -1    -1     0    -2     1  pt2 touches plane, no intersection
  //    -1     0    -1    -2     1  pt1 touches plane, no intersection
  //     0    -1    -1    -2     1  pt0 touches plane, no intersection
  //     0    +1    +1    +2     1  plane touches pt0, no intersection
  //    +1     0    +1    +2     1  plane touches pt1, no intersection
  //    +1    +1     0    +2     1  plane touches pt2, no intersection
  // abs(sum >= 2)

  //     0     0     0     0     3  the entire triangle lies in the plane
  // abs(sum) < 2 && 0ct == 3

  //    -1     0     0    -1     2  plane intersects at edge 12
  //    +1     0     0    +1     2  plane intersects at edge 12
  // abs(sum) < 2 && 0ct == 2 && pt_code[0] != 0

  //     0    -1     0    -1     2  plane intersects at edge 20
  //     0    +1     0    +1     2  plane intersects at edge 20
  // abs(sum) < 2 && 0ct == 2 && pt_code[1] != 0

  //     0     0    -1    -1     2  plane intersects at edge 01
  //     0     0    +1    +1     2  plane intersects at edge 01
  // abs(sum) < 2 && 0ct == 2 && pt_code[2] != 0

  //     0    -1    +1     0     1  plane intersects pt0 and edge 12
  //     0    +1    -1     0     1  plane intersects pt0 and edge 12
  // abs(sum) < 2 && 0ct == 1 && pt_code[0] == 0

  //    +1     0    -1     0     1  plane intersects pt1 and edge 20
  //    -1     0    +1     0     1  plane intersects pt1 and edge 20
  // abs(sum) < 2 && 0ct == 1 && pt_code[1] == 0

  //    -1    +1     0     0     1  plane intersects pt2 and edge 01
  //    +1    -1     0     0     1  plane intersects pt2 and edge 01
  // abs(sum) < 2 && 0ct == 1 && pt_code[2] == 0

  //    -1    +1    -1    -1     0  plane intersects edges 01 and 12
  //    +1    -1    +1    -1     0  plane intersects edges 01 and 12
  // abs(sum) < 2 && 0ct == 0 && pt_code[0] == pt_code[2]

  //    -1    -1    +1    -1     0  plane intersects edges 12 and 20
  //    +1    +1    -1    -1     0  plane intersects edges 12 and 20
  // abs(sum) < 2 && 0ct == 0 && pt_code[0] == pt_code[1]

  //    -1    +1    +1    -1     0  plane intersects edges 20 and 01
  //    +1    -1    -1    -1     0  plane intersects edges 20 and 01
  // abs(sum) < 2 && 0ct == 0 && pt_code[1] == pt_code[2]

  // Intersection points and edges.

  scoped_index lpta_id, *ledgea0_id, *ledgea1_id;
  e3_lite lpta, *ledgea0, *ledgea1;

  scoped_index lptb_id, *ledgeb0_id, *ledgeb1_id;
  e3_lite lptb, *ledgeb0, *ledgeb1;

  vd_value_type lu;

  scoped_index ls_id;
  
  
  int labs_pt_code_sum = abs(lpt_code_sum);
  
  if(labs_pt_code_sum < 2)
  {
    if(lpt_code_0_ct == 0)
    {
      // Plane intersects two edges.
      
      if(lpt_code[0] == lpt_code[2])
      {
        // Plane intersects  edges 01 and 12.

        // cout << "Plane intersects  edges 01 and 12" << endl;

        // edgea ==  01

        ledgea0_id = lpt_ids;
        ledgea1_id = lpt_ids + 1;
        ledgea0 = lpts;
        ledgea1 = lpts + 1;    

        // edgeb == 12

        ledgeb0_id = lpt_ids + 1;
        ledgeb1_id = lpt_ids + 2;
        ledgeb0 = lpts + 1;
        ledgeb1 = lpts + 2;
      }
      else if(lpt_code[0] == lpt_code[1])
      {
        // Plane intersects  edges 12 and 20.

        // cout << "Plane intersects  edges 12 and 20" << endl;

        // edgea = 12

        ledgea0_id = lpt_ids + 1;
        ledgea1_id = lpt_ids + 2;
        ledgea0 = lpts + 1;
        ledgea1 = lpts + 2;

        // edgeb == 20

        ledgeb0_id = lpt_ids + 2;
        ledgeb1_id = lpt_ids;
        ledgeb0 = lpts + 2;
        ledgeb1 = lpts;
      }
      else
      {
        assertion(lpt_code[1] == lpt_code[2]);
        
        // Plane intersects  edges 20 and 01.

        // cout << "Plane intersects  edges 20 and 01" << endl;

        // edgea == 20

        ledgea0_id = lpt_ids + 2;
        ledgea1_id = lpt_ids;
        ledgea0 = lpts + 2;
        ledgea1 = lpts;

        // edgeb == 01

        ledgeb0_id = lpt_ids;
        ledgeb1_id = lpt_ids + 1;
        ledgeb0 = lpts;
        ledgeb1 = lpts + 1;
      }

      // Find or create the intersection points

      get_point_intersection(xhost, xp, *ledgea0_id, *ledgea0, *ledgea1_id, *ledgea1, lpta_id);
      get_point_intersection(xhost, xp, *ledgeb0_id, *ledgeb0, *ledgeb1_id, *ledgeb1, lptb_id);

      // $$SCRIBBLE: Vertex welding. If the segment computed is shorted than some tolerance,
      // we should weld the vertices together. We if one vertex is in a face or edge, we
      // should move the other to it. Not clear what to do if both are. One reason to do
      // the welding here is bacuase we still have the triangle edge info and can tell if
      // an intersection is in a tree face or edge. Unfortunately, it's not clear how
      // to handle a single point in the frag list. An alternative would be to somehow
      // carry the edge info along with the frag list until we get to kd_lattice::implicit_lines
      // where combining points is simple.

      // Append the intersection to the fraglist.

      surface(xhost, xid, ls_id);
      kd_line_fragment::append(lpta_id, lptb_id, ls_id, xzone_id, xfrags);
    }
    else if(lpt_code_0_ct == 1)
    {
      // Plane intersects one vertex and one edge.
      // Need to create one intersection point.
      // $$SCRIBBLE: make sure vertex is no longer a centroid.
      
      lptb_id = xhost.points().new_member();

      if(lpt_code[0] == 0)
      {
        // Plane intersects pt0 and edge 12.

        // cout << "Plane intersects pt0 and edge 12" << endl;

        // edgea ==  00

        ledgea0_id = lpt_ids;
        ledgea0 = lpts;

        // edgeb == 12

        ledgeb0_id = lpt_ids + 1;
        ledgeb1_id = lpt_ids + 2;
        ledgeb0 = lpts + 1;
        ledgeb1 = lpts + 2;
      }
      else if(lpt_code[1] == 0)
      {
        // Plane intersects pt1 and edge 20.

        // cout << "Plane intersects pt1 and edge 20" << endl;

        // edgea ==  11

        ledgea0_id = lpt_ids + 1;
        ledgea0 = lpts + 1;

        // edgeb == 20

        ledgeb0_id = lpt_ids + 2;
        ledgeb1_id = lpt_ids;
        ledgeb0 = lpts + 2;
        ledgeb1 = lpts;
      }
      else
      {
        assertion(lpt_code[2] == 0);

        // Plane intersects pt2 and edge 01.

        // cout << "Plane intersects pt2 and edge 01" << endl;

        // edgea ==  22

        ledgea0_id = lpt_ids + 2;
        ledgea0 = lpts + 2;

        // edgeb == 01

        ledgeb0_id = lpt_ids;
        ledgeb1_id = lpt_ids + 1;
        ledgeb0 = lpts;
        ledgeb1 = lpts + 1;
      }

      // Find or create the intersection points.

      get_vertex_intersection(xhost, *ledgea0_id, *ledgea0, lpta_id);
      get_point_intersection(xhost, xp, *ledgeb0_id, *ledgeb0, *ledgeb1_id, *ledgeb1, lptb_id);

      // Append the intersection to the fraglist.

      surface(xhost, xid, ls_id);
      kd_line_fragment::append(lpta_id, lptb_id, ls_id, xzone_id, xfrags);
    }
    else if(lpt_code_0_ct == 2)
    {
      if(lpt_code[0] != 0)
      {
        // Plane intersects at edge 12.

        // cout << "Plane intersects edge 12" << endl;

        // edgea ==  12

        ledgea0_id = lpt_ids + 1;
        ledgea1_id = lpt_ids + 2;
        ledgea0 = lpts + 1;
        ledgea1 = lpts + 2;    
      }
      else if(lpt_code[1] != 0)
      {
        // Plane intersects at edge 20.

        // cout << "Plane intersects edge 20" << endl;

        // edgea ==  20

        ledgea0_id = lpt_ids + 2;
        ledgea1_id = lpt_ids;
        ledgea0 = lpts + 2;
        ledgea1 = lpts;    
      }
      else
      {
        // Plane intersects at edge 01

        // cout << "Plane intersects edge 01" << endl;

        assertion(lpt_code[2] != 0);

        ledgea0_id = lpt_ids;
        ledgea1_id = lpt_ids + 1;
        ledgea0 = lpts;
        ledgea1 = lpts + 1;    
      }

      // Find or create the intersection points.

      if(get_edge_intersection(xhost, xp, *ledgea0_id, *ledgea0, *ledgea1_id, *ledgea1, lpta_id, lptb_id))
      {
        // Append the intersection to the fraglist.

        surface(xhost, xid, ls_id);
        kd_line_fragment::append(lpta_id, lptb_id, ls_id, xzone_id, xfrags);
      }
      
    }
    else
    {
      assertion(lpt_code_0_ct == 3);
      
      // Plane intersects entire triangle.

      // Not sure what to do about this one;
      // post a warning and do nothing.

      post_warning_message("Case triangle lies entirely in plane not supported.");
    }    
  }
  else
  {
    // No intersection; do nothing

    // cout << "Plane does not intersect triangle" << endl;
  }

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_triangle::intersect_plane." << endl;
  return;
}


void
geometry::kd_triangle::
edge_neighbor(const kd_lattice& xhost, 
              const scoped_index& xid, 
              bool xorientation,
              const scoped_index xpt_ids[], 
              int xedge_id, 
              ot& xresult)
{
  // cout << endl << "Entering kd_triangle::edge_neighbor." << endl;
  // cout << "triangle: " << xid.pod() << " " << name(xhost, xid) << endl;
  // cout << "orientation: " << boolalpha << xorientation << noboolalpha << endl;
  // cout << "edge: " << xedge_id << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));
  require_for_all(i, 0, POINT_CT, xhost.base_space().contains_link(xid, xpt_ids[i]));
  require((0 <= xedge_id) && (xedge_id < POINT_CT));
  
  // Body:

  // Get the vertices in local numbering.

  int li0 = xedge_id;
  int li1 = (xedge_id + 1) % POINT_CT;
  int li2 = other_local_point_id(li0, li1);

  // cout << "local vertices:" << setw(3) << li0 << setw(3) << li1 << setw(3) << li2 << endl;  

  const scoped_index& lpt0_id = xpt_ids[li0];
  const scoped_index& lpt1_id = xpt_ids[li1];
  const scoped_index& lpt2_id = xpt_ids[li2];

  // cout << "scoped vertices: " << lpt0_id << "  " << lpt1_id << "  " << lpt2_id << endl;
  
  // Get the other triangles for each point as sets.

  id_list lpt0_list;
  kd_point::triangles(xhost, lpt0_id, lpt0_list);
  id_set lpt0_set(lpt0_list.begin(), lpt0_list.end());

  // cout << "triangles for pt 0: " << lpt0_set << endl;
  
  id_list lpt1_list;
  kd_point::triangles(xhost, lpt1_id, lpt1_list);
  id_set lpt1_set(lpt1_list.begin(), lpt1_list.end());  
  
  // cout << "triangles for pt 1: " << lpt1_set << endl;

  // Triangles connected through the edge are the triangles
  // that appear in both sets of triangles; compute the intersection.
  
  id_list lnbrs;
  back_insert_iterator<id_list> lnbr_itr(lnbrs);
  
  set_intersection(lpt0_set.begin(), lpt0_set.end(), lpt1_set.begin(), lpt1_set.end(), lnbr_itr);

  // cout << "triangles in both: " << lnbrs << endl;

  // The current triangle has to be in the nbrs list; remove it.

  for(id_list::iterator ln=lnbrs.begin(); ln!=lnbrs.end(); )
  {
    if(*ln == xid)
    {
      lnbrs.erase(ln++);
      break;
    }
    else
    {
      ++ln;
    }
  }  

  size_type lnbrs_size = lnbrs.size();

  scoped_index lnbr_pt_ids[POINT_CT];
  scoped_index lroi_id = xhost.region_of_interest().id();

  // Assume we can't find an acceptable neighbor.

  xresult.first.invalidate();
  xresult.second = true; // Just so we know what dbg output means.
  
  if(lnbrs_size == 1)
  {
    // There's only one neighbor, just set the orientation

    // cout << "There's only one neighbor, just set the orientation" << endl;

    e3_lite lnbr_pts[POINT_CT];
    
    // Get the points for the connected triangle.

    points(xhost, lnbrs.front(), lnbr_pt_ids, lnbr_pts);

    // Compute which edge it is in the neighbor.

    int lnbr_i0, lnbr_i1, lnbr_i2;
        
    for(int i=0; i<POINT_CT; ++i)
    {
      if(lpt0_id == lnbr_pt_ids[i])
      {
        lnbr_i0 = i;
      }
      if(lpt1_id == lnbr_pt_ids[i])
      {
        lnbr_i1 = i;
      }
    }

    lnbr_i2 = other_local_point_id(lnbr_i0, lnbr_i1);

    // Determine whether the points in the nbr edge are stored
    // int the same order as the points in the currect edge are
    // stored.

    bool lsame_order = ((lnbr_i0 + 1) % POINT_CT) == lnbr_i1;

    // The stored orientation of the neighbor is the same as 
    // the stored orientation of the current triangle if the 
    // points are stored in the opposite order. If the current
    // orientation of the current triangle is reversed, then
    // the orientation of the nbr is the same if the points
    // are in the same order.

    bool lorientation = xorientation ? !lsame_order : lsame_order;

    // We never accept the false oreintation of an roi triangle
    // or any exterior triangle.

    bool lis_roi_surface = (kd_triangle::surface(xhost, lnbrs.front()) == lroi_id);
    bool lis_roi_interior = xhost.interior_triangles().contains(lnbrs.front());
    bool lis_exterior = !lis_roi_surface && !lis_roi_interior;
    bool lis_roi_false = lis_roi_surface && !lorientation;
    
    if(lis_roi_false)
    {
      // cout << "rejecting roi_false: " << lnbrs.front().pod() << endl;
    }
    else if(lis_exterior)
    {
      // cout << "rejecting exterior: " << lnbrs.front().pod() << endl;
    }
    else
    {
      xresult.first = lnbrs.front();
      xresult.second = lorientation;
    }
  }
  else if(lnbrs_size > 1)
  {
    // There's multiple neighbors,
    // we'll have to compute which is on the in side.

    // cout << "There's multiple neighbors," << endl;

    // Get points for current triangle.

    e3_lite lpts[POINT_CT];
    for(int i=0; i<POINT_CT;++i)
    {
      xhost.coords().get_fiber(xpt_ids[i], lpts[i], false);
    }

    // Debugging: check for degenerate triangles.

    //     bool lis_collinear = is_collinear(lpts);
    //     if(lis_collinear)
    //     {
    //       cout << "coliinear triangle:" << endl;
    //       cout << "pt ids: " << setw(6) << xpt_ids[0].pod() << setw(6) << xpt_ids[1].pod() << setw(6) << xpt_ids[2].pod() << endl;
    //       cout << "points: " << lpts[0] << lpts[1] << lpts[2] << endl;
    //     }

    ot_list::iterator linside_nbr;
    vd_value_type ltheta, ltheta_min = numeric_limits<vd_value_type>::max();

    e3_lite lnbr_pts[POINT_CT];

    for(id_list::iterator ln=lnbrs.begin(); ln!=lnbrs.end(); ++ln)
    {
      // Get the points for the connected triangle.

      // cout << "connected triangle: " << ln->pod() << "  " << name(xhost, *ln) << endl;

      points(xhost, *ln, lnbr_pt_ids, lnbr_pts);

      // Compute which edge it is in the neighbor.

      int lnbr_i0, lnbr_i1, lnbr_i2;
        
      for(int i=0; i<POINT_CT; ++i)
      {
        if(lpt0_id == lnbr_pt_ids[i])
        {
          lnbr_i0 = i;
        }
        if(lpt1_id == lnbr_pt_ids[i])
        {
          lnbr_i1 = i;
        }
      }

      lnbr_i2 = other_local_point_id(lnbr_i0, lnbr_i1);

      // Determine whether the points in the nbr edge are stored
      // int the same order as the points in the currect edge are
      // stored.

      bool lsame_order = ((lnbr_i0 + 1) % POINT_CT) == lnbr_i1;

      // The stored orientation of the neighbor is the same as 
      // the stored orientation of the current triangle if the 
      // points are stored in the opposite order. If the current
      // orientation of the current triangle is reversed, then
      // the orientation of the nbr is the same if the points
      // are in the same order.

      bool lorientation = xorientation ? !lsame_order : lsame_order;

      // We never accept the false oreintation of an roi triangle
      // or any exterior triangle.

      bool lis_roi_surface = (kd_triangle::surface(xhost, *ln) == lroi_id);
      bool lis_roi_interior = xhost.interior_triangles().contains(*ln);
      bool lis_exterior = !lis_roi_surface && !lis_roi_interior;
      bool lis_roi_false = lis_roi_surface && !lorientation;
    
      if(lis_roi_false)
      {
        // cout << "rejecting roi_false: " << ln->pod() << endl;
        continue;
      }
      else if(lis_exterior)
      {
        // cout << "rejecting exterior: " << ln->pod() << endl;
        continue;
      }

      // Compute inside angle:
      
      // Set up a ortho-normal frame (li_hat, lj_hat, lk_hat)
      // with 
      // li_hat = in plane of current triangle, pointing from shared edge 
      //          into interior of current triangle
      // lj_hat = normal to current triangle in stored orientation
      // lk_hat = shared edge in stored direction of current triangle

      // k-hat in the direction of the shared edge.

      e3_lite lk_hat(lpts[li1]);
      lk_hat -= lpts[li0];
      normalize(lk_hat);

      // li_hat temporarily other edge containing pt0.
      // Note that since the vertices are ordered 0, 1, 2
      // in the stored orientation, this edge is directed
      // from pt2 to pt0.

        
      e3_lite li_hat(lpts[li0]);
      li_hat -= lpts[li2];
      normalize(li_hat);

      // Compute the normal to the triangle in the 
      // stored orientation, given by the cross product
      // of 2 successive  edges in the stored order.
      // Edge20 and edge 01 will do. If the orientation
      // is not the stored orientation, reverse the order
      // of the cross product for the normal. This will
      // result in the subsequent cross product for
      // ihat pointing out of the triangle, not into it,
      // so reverse it as well.

      // $$SCRIBBLE: the normal calculation may fail
      // numerically for triangles that are slivers.
      // Not clear what we can do about this.

      // $$TODO: replace this ad-hoc algorithm with a
      // robust implementation of orient3d, e.g. as 
      // available from Shewchuk. Use orient3d to
      // evaluate the in-sde-of relation for all neighbors,
      // orders neighbors around edge. The min is the
      // one we want.

      e3_lite lj_hat;
      if(xorientation)
      {
        // Compute normal for forward orientation.
 
        cross(li_hat, lk_hat, lj_hat);

        // Now make x-axis normal to y and z
        // and pointing into the triangle

        cross(lj_hat, lk_hat, li_hat);
      }
      else
      {
        // Compute normal for reverse orientation.

        cross(lk_hat, li_hat, lj_hat);

        // Now make x-axis normal to y and z
        // and pointing into the triangle

        cross(lk_hat, lj_hat, li_hat);

        // This produces a left-handed coordinate system.
      }
        
      // Vector in plane of mbr triangle:
      // other edge containing pt0.
        
      e3_lite lnbr_edge(lnbr_pts[lnbr_i2]);
      lnbr_edge -= lnbr_pts[lnbr_i0];

      // Compute the angle in the xy plane of the frame.
      // Note that atan2 returns -pi < result <= pi, 
      // while we want 0 < ltheta <= 2*pi so min
      // correctly identifes triangle on in side.
      // So if theta < 0, add 2*PI.

      // $$SCRIBBLE We can identify the min without
      // actually computing the angle, but its 
      // much simpler this way.

      vd_value_type lx = dot(lnbr_edge, li_hat);
      vd_value_type ly = dot(lnbr_edge, lj_hat);
      const vd_value_type TWO_PI = 8.0*atan(1.0);
      ltheta = atan2(ly, lx);
      if(ltheta < 0.0)
      {
        ltheta += TWO_PI;
      }

      // If we follow a path from the current triangle
      // on the side the normal points to, rotating
      // around the shared edge as an axis, the first
      // triangle we come is the one one the same side.
      // So the nbr with the smallest angle is the
      // one the same side.

      // cout << "theta: " << ltheta << " theta_min: " << ltheta_min << endl;
      
      if(ltheta < ltheta_min)
      {
        ltheta_min = ltheta;
        xresult.first = *ln;
        xresult.second = lorientation;
      }
      // cout << "theta: " << ltheta << " theta_min: " << ltheta_min << endl;
    }
  }
  else
  {
    // No neighbors, nothing to do.

    // cout << "No neighbors, nothing to do." << endl;
  }
  
  // Postconditions:

  // Exit:

  // cout << "result: " << xresult.first.pod();
  // cout << "  " << boolalpha << xresult.second << noboolalpha << endl;
  // cout << "Leaving kd_triangle::edge_neighbor." << endl;
  return;
}


void
geometry::kd_triangle::
normal(e3_lite& xresult) const
{
  // cout << endl << "Entering kd_triangle::normal." << endl;

  // Preconditions:

  require(precondition_of(normal(host(), id(), xresult)));

  // Body:

  normal(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(normal(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_triangle::normal." << endl;
  return;
}

void
geometry::kd_triangle::
normal(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xresult)
{
  // cout << endl << "Entering kd_triangle::normal." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.triangles().contains(xid));

  // Body:

  scoped_index lpt_ids[POINT_CT];
  e3_lite lpts[POINT_CT];
  points(xhost, xid, lpt_ids, lpts);
  
  e3_lite le01(lpts[1]);
  le01 -= lpts[0];
  
  e3_lite le20(lpts[0]);
  le20 -= lpts[2];
  
  cross(le20, le01, xresult);
  normalize(xresult);

  // Postconditions:

  ensure(a_eql_1(length(xresult)));
  
  // Exit:

  // cout << "Leaving kd_triangle::normal." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_triangle::
kd_triangle()
{
  
  // Preconditions:

    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_triangle::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_triangle*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_triangle*
geometry::kd_triangle::
clone() const
{
  kd_triangle* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_triangle();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_triangle&
geometry::kd_triangle::
operator=(const kd_triangle& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_triangle&
geometry::kd_triangle::
operator=(const any& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));
    
  // Body:
  
  kd_member::operator=(xother);

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

bool
geometry::kd_triangle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(kd_member::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, const kd_triangle& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  xos << "triangle " << xn.host().triangles().id_space().pod(xn.id());
  xos << "  top id: " << xn.id();
  xos << "  name: " << xn.name();
  xos << "  type: " << xn.type_name();
  xos << boolalpha;
  xos << "  is_jim: " << xn.is_jim();
  xos << "  is_leaf: " << xn.is_leaf();
  xos << noboolalpha;
  xos << "  lb: " << xn.coord_lower_bound();
  xos << "  ub: " << xn.coord_upper_bound();
  xos << endl;
  
  xos << "\tlower cover:";
  const base_space_poset& lbase = xn.host().base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xn.id());
  while(!litr.is_done())
  {
    xos << "   " << lbase.member_name(litr.hub_pod());
    litr.next();
  }
  xos << endl << endl;

  lbase.release_cover_id_space_iterator(litr);

  scoped_index lids[kd_triangle::POINT_CT];

  xos << "\tpoints:";
  xn.points(lids);
  for(int i=0; i<kd_triangle::POINT_CT; ++i)
  {
    xos << "   " << lbase.member_name(lids[i]);
  }
  xos << endl << endl;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_triangle& xn, bool xinclude_shallow)
{
  size_t result = 0;

  // Preconditions:

  // Body:

  not_implemented();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
