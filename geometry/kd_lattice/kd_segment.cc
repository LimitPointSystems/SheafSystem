

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_segment

#include "kd_segment.h"

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
#include "kd_triangle.h"
#include "std_algorithm.h"
#include "std_limits.h"
#include "sec_e3.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.

// namespace
// {

  
  
// } // end unnamed namespace.

// ===========================================================
// KD_SEGMENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_segment::
prototype_name()
{
  // cout << endl << "Entering kd_segment::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("segment");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_segment::prototype_name." << endl;
  return result;
}

geometry::kd_segment::
kd_segment(kd_lattice& xhost, const scoped_index xv_ids[])
  :kd_member(xhost)
{
  // cout << endl << "Entering kd_segment::kd_segment." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, POINT_CT, xhost.points().d_cells_contains(xv_ids[i]));
    
  define_old_variable(size_type old_segments_ct = xhost.segments().ct());
  define_old_variable(size_type old_points_ct = xhost.points().ct());

  // Body:

  _id = new_segment(xhost, xv_ids);
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().segments().contains(id()));
  ensure(host().segments().ct() == old_segments_ct + 1);
  ensure(host().points().ct() == old_points_ct);
  ensure(point(0) == xv_ids[0]);
  ensure(point(1) == xv_ids[1]);

  // Exit:

  // cout << "Leavinging kd_segment::kd_segment." << endl;
  return; 
}

geometry::scoped_index
geometry::kd_segment::
new_segment(kd_lattice& xhost, const scoped_index xv_ids[])
{
  // cout << endl << "Entering kd_segment::new_segment." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, POINT_CT, xhost.points().d_cells_contains(xv_ids[i]));

  define_old_variable(size_type old_segments_ct = xhost.segments().ct());
  define_old_variable(size_type old_points_ct = xhost.points().ct());
    
  // Body:

  base_space_poset& lbase = xhost.base_space();  

  // Create the segment.

  scoped_index result = xhost.segments().new_member();

  // The segment covers the points.

  lbase.new_link(result, xv_ids[0]);
  lbase.new_link(result, xv_ids[1]);

  // Postconditions:

  ensure(xhost.segments().contains(result));
  ensure(xhost.segments().ct() == old_segments_ct + 1);
  ensure(xhost.points().ct() == old_points_ct);
  ensure(point(xhost, result, 0) == xv_ids[0]);
  ensure(point(xhost, result, 1) == xv_ids[1]);

  // Exit:

  // cout << "Leaving kd_segment::new_segment." << endl;
  return result; 
}

geometry::scoped_index
geometry::kd_segment::
new_segment(kd_lattice& xhost, const scoped_index& xpt0_id, const scoped_index& xpt1_id)
{
  // cout << endl << "Entering kd_segment::new_segment." << endl;

  // Preconditions:

  // cout << "  pt0: " << xpt0_id << "  " << xhost.base_space().member_name(xpt0_id) << endl;
  // cout << "  pt1: " << xpt1_id << "  " << xhost.base_space().member_name(xpt1_id) << endl;

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.points().d_cells_contains(xpt0_id));
  require(xhost.points().d_cells_contains(xpt1_id));

  define_old_variable(size_type old_segments_ct = xhost.segments().ct());
  define_old_variable(size_type old_points_ct = xhost.points().ct());
    
  // Body:

  base_space_poset& lbase = xhost.base_space();  

  // Create the segment.

  scoped_index result = xhost.segments().new_member();

  // The segment covers the points.

  lbase.new_link(result, xpt0_id);
  lbase.new_link(result, xpt1_id);

  // Postconditions:

  ensure(xhost.segments().contains(result));
  ensure(xhost.segments().ct() == old_segments_ct + 1);
  ensure(xhost.points().ct() == old_points_ct);
  ensure(point(xhost, result, 0) == xpt0_id);
  ensure(point(xhost, result, 1) == xpt1_id);

  // Exit:

  // cout << "Leaving kd_segment::new_segment." << endl;
  return result; 
}

geometry::kd_segment::
kd_segment(kd_lattice& xhost, const scoped_index& xid)
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

geometry::kd_segment::
kd_segment(const kd_segment& xother)
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

geometry::kd_segment::
~kd_segment()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_segment::
line_fragments(id_list_list& xfrags) const
{
  // Preconditions:

  require(precondition_of(line_fragments(host(),id(), xfrags)));
  
  // Body:

  line_fragments(*_host, _id, xfrags);
  
  // Postconditions:

  ensure(postcondition_of(line_fragments(host(),id(), xfrags)));

  // Exit:

  return;
}

void
geometry::kd_segment::
line_fragments(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xfrags)
{
  // cout << endl << "Entering kd_segment::line_fragments." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  assertion(!litr.is_done());
  assertion(is_valid(litr.hub_pod()));

  scoped_index lcur_pt0 = xhost.base_space().member_id(litr.hub_pod(), false);
  
  litr.next();

  assertion(!litr.is_done());
  assertion(is_valid(litr.hub_pod()));

  scoped_index lcur_pt1 = xhost.base_space().member_id(litr.hub_pod(), false);  

  xhost.base_space().release_cover_id_space_iterator(litr);

  if(xfrags.empty() || xfrags.back().back() != lcur_pt0)
  {
    // No previous aegment or first point of this segment 
    // is not the same as second point of previous segment. 
    // This is the beginning of a line fragment.

    id_list lfrag;
    xfrags.push_back(lfrag);
    
    // Add the first point in the segment.

    xfrags.back().push_back(lcur_pt0);
  }
  else if(xhost.truncation_points().contains(lcur_pt0))
  {
    // xfrags.back().back() and lcur_pt0 are the same point,
    // but it is a truncation point. Start a new fragment if 
    // this segment and the previous segment aren't in the same
    // surface. The two segments are in different surfaces if
    // the intersection of the surfaces containing the first point
    // of the previous segment and the surfaces containing the
    // second point of this segment is empty.

    // Get the surfaces of the first pt of the previous segment.

    id_list::iterator lprev_pt0 = xfrags.back().end();
    --lprev_pt0; // Second pt of previous segment.
    --lprev_pt0; // First pt of previous segment.

    id_list lprev_surfs;
    kd_point::surfaces(xhost, *lprev_pt0, lprev_surfs);
    
    // Get surfaces of the second pt of the current segment

    id_list lcur_surfs;
    kd_point::surfaces(xhost, lcur_pt1, lcur_surfs);
    
    // Compute the intersection

    intersect(lprev_surfs, lcur_surfs);
    if(lcur_surfs.empty())
    {
      id_list lfrag;
      xfrags.push_back(lfrag);
    
      // Add the first point in the segment.

      xfrags.back().push_back(lcur_pt0);
    }  
  }  

  // Add the second point.
  
  xfrags.back().push_back(lcur_pt1);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_segment::line_fragments." << endl;
  return;
}

void
geometry::kd_segment::
line_fragments(const kd_line_fragment& xfrag_prototype, frag_list& xfrags) const
{
  // Preconditions:

  require(precondition_of(line_fragments(host(),id(), xfrag_prototype, xfrags)));
  
  // Body:

  line_fragments(*_host, _id, xfrag_prototype, xfrags);
  
  // Postconditions:

  ensure(postcondition_of(line_fragments(host(),id(), xfrag_prototype, xfrags)));

  // Exit:

  return;
}

void
geometry::kd_segment::
line_fragments(const kd_lattice& xhost, const scoped_index& xid, const kd_line_fragment& xfrag_prototype, frag_list& xfrags)
{
  // cout << endl << "Entering kd_segment::line_fragments." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  assertion(!litr.is_done());
  assertion(is_valid(litr.hub_pod()));

  scoped_index lcur_pt0 = xhost.base_space().member_id(litr.hub_pod(), false);
  
  litr.next();

  assertion(!litr.is_done());
  assertion(is_valid(litr.hub_pod()));

  scoped_index lcur_pt1 = xhost.base_space().member_id(litr.hub_pod(), false);  

  xhost.base_space().release_cover_id_space_iterator(litr);

  if(xfrags.empty() || xfrags.back().pt_ids.back() != lcur_pt0)
  {
    // No previous aegment or first point of this segment 
    // is not the same as second point of previous segment. 
    // This is the beginning of a line fragment.

    xfrags.push_back(xfrag_prototype);

    // Set the surface for the fragment.

    surface(xhost, xid, xfrags.back().surface_id);
    
    // Add the first point in the segment.

    xfrags.back().pt_ids.push_back(lcur_pt0);
  }
  //   else if(xhost.truncation_points().contains(lcur_pt0))
  //   {
  //     // xfrags.back().back() and lcur_pt0 are the same point,
  //     // but it is a truncation point. Start a new fragment if 
  //     // this segment and the previous segment aren't in the same
  //     // surface. 

  //     scoped_index lsurf_id;
  //     surface(xhost, xid, lsurf_id);
    
  //     if(lsurf_id != xfrags.back().surface_id)
  //     {
  //       kd_line_fragment lfrag;
  //       xfrags.push_back(lfrag);
    
  //       // Add the first point in the segment.

  //       xfrags.back().pt_ids.push_back(lcur_pt0);

  //       // Set the surface for the fragment.

  //       surface(xhost, xid, xfrags.back().surface_id);
  //     }  
  //   }  
  else if(xhost.truncation_points().contains(lcur_pt0))
  {
    // xfrags.back().back() and lcur_pt0 are the same point,
    // but it is a truncation point; start a new fragment.

    xfrags.push_back(xfrag_prototype);

    // Set the surface for the fragment.

    surface(xhost, xid, xfrags.back().surface_id);
    
    // Add the first point in the segment.

    xfrags.back().pt_ids.push_back(lcur_pt0);
  }  

  // Update the container id in the frag, if necessary.

  xfrags.back().update_container_id(xfrag_prototype.container_id);

  // Add the second point.
  
  xfrags.back().pt_ids.push_back(lcur_pt1);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_segment::line_fragments." << endl;
  return;
}

void
geometry::kd_segment::
members(id_list_list& xmbrs, bool xinclude_segments) const
{
  // Preconditions:

  require(precondition_of(members(host(),id(), xmbrs, xinclude_segments)));
  
  // Body:

  members(*_host, _id, xmbrs, xinclude_segments);
  
  // Postconditions:

  ensure(postcondition_of(members(host(),id(), xmbrs, xinclude_segments)));

  // Exit:

  return;
}

void
geometry::kd_segment::
members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, bool xinclude_segments)
{
  // cout << endl << "Entering kd_segment::members." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  assertion(is_valid(litr.hub_pod()));

  if(xmbrs.empty() || xmbrs.back().back() != litr.hub_pod())
  {
    // No previous aegment or first point of this segment 
    // is not the same as second point of previous segment. 
    // This is the beginning of a line fragment.

    id_list lfrag;
    xmbrs.push_back(lfrag);
    
    // Add the first point in the segment.

    xmbrs.back().push_back(xhost.base_space().member_id(litr.hub_pod(), false));
  } 

  if(xinclude_segments)
  {
    // Add the segment itself.

    xmbrs.back().push_back(xid);
  }  

  // Add the second point.
  
  litr.next();
  xmbrs.back().push_back(xhost.base_space().member_id(litr.hub_pod(), false));

  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_segment::members." << endl;
  return;
}

void
geometry::kd_segment::
members(id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments) const
{
  // Preconditions:

  require(precondition_of(members(host(),id(), xmbrs, xcoords, xinclude_segments)));
  
  // Body:

  members(*_host, _id, xmbrs, xcoords, xinclude_segments);
  
  // Postconditions:

  ensure(postcondition_of(members(host(),id(), xmbrs, xcoords, xinclude_segments)));

  // Exit:

  return;
}

void
geometry::kd_segment::
members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments)
{
  // cout << endl << "Entering kd_segment::members." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  e3_lite lpt;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  assertion(is_valid(litr.hub_pod()));

  if(xmbrs.empty() || xmbrs.back().back().hub_pod() != litr.hub_pod())
  {
    // No previous aegment or first point of this segment 
    // is not the same as second point of previous segment. 
    // This is the beginning of a line fragment.

    id_list lfrag;
    xmbrs.push_back(lfrag);

    pt_list lpt_frag;
    xcoords.push_back(lpt_frag);
    
    // Add the first point in the segment and its coordinates.

    scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);

    xmbrs.back().push_back(lid);

    kd_point::coords(xhost, lid, lpt);
    xcoords.back().push_back(lpt);
  }

  if(xinclude_segments)
  {
    // Add the segment itself and place holder coordinates.

    xmbrs.back().push_back(xid);

    lpt = numeric_limits<vd_value_type>::max();
    xcoords.back().push_back(lpt);
  }  

  // Add the second point and coordinates.
  
  litr.next();
  scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);
  xmbrs.back().push_back(lid);

  kd_point::coords(xhost, lid, lpt);
  xcoords.back().push_back(lpt);

  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_segment::members." << endl;
  return;
}

void
geometry::kd_segment::
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
geometry::kd_segment::
points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_segment::points." << endl;
  // Preconditions:

  require(unexecutable("xresult is an array with at least POINT_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  xresult[0] = xhost.base_space().member_id(litr.hub_pod(), false);
  litr.next();
  xresult[1] = xhost.base_space().member_id(litr.hub_pod(), false);
  
  // cout << "result[0]: " << xresult[0].internal_pod() << endl;
  // cout << "result[1]: " << xresult[1].internal_pod() << endl;

  xhost.base_space().release_cover_id_space_iterator(litr);


  // Postconditions:

  ensure_for_all(i, 0, POINT_CT, xhost.base_space().vertices().contains_member(xresult[i]));

  // Exit:

  // cout << "Leaving kd_segment::points." << endl;
  return;
}

void
geometry::kd_segment::
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
geometry::kd_segment::
points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[], e3_lite xcoords[])
{
  // cout << endl << "Entering kd_segment::points." << endl;
  // Preconditions:

  require(unexecutable("xresult is an array with at least POINT_CT entries"));
  require(xhost.coords().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  points(xhost, xid, xresult);
  xhost.coords().get_fiber(xresult[0], xcoords[0], false);
  xhost.coords().get_fiber(xresult[1], xcoords[1], false);

  // Postconditions:

  ensure_for_all(i, 0, POINT_CT, xhost.base_space().vertices().contains_member(xresult[i]));
  ensure_for_all(i, 0, POINT_CT, xcoords[i] == kd_point::coords(xhost, xresult[i]));

  // Exit:

  // cout << "Leaving kd_segment::points." << endl;
  return;
}


sheaf::scoped_index
geometry::kd_segment::
point(int xi) const
{
  // cout << endl << "Entering kd_segment::point." << endl;

  // Preconditions:

  require(precondition_of(point(host(), id(), xi)));

  // Body:

  scoped_index result = point(*_host, _id, xi);

  // Postconditions:

  ensure(postcondition_of(point(host(), id(), xi)));

  // Exit:

  // cout << "Leaving kd_segment::point." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_segment::
point(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_segment::point." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  require((0 <= xi) && (xi < POINT_CT));

  // Body:  
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  if(xi > 0)
  {
    litr.next();
  }
  
  scoped_index result = xhost.base_space().member_id(litr.hub_pod(), false);

  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xhost.base_space().vertices().contains_member(result));
  
  // Exit:

  // cout << "Leaving kd_segment::point." << endl;
  return result;
}

void
geometry::kd_segment::
refine(const scoped_index& xpt_id, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::refine." << endl;

  // Preconditions:

  require(precondition_of(refine(host(), id(), xresult)));

  // Body:

  refine(*_host, _id, xpt_id, xresult);

  // Postconditions:

  ensure(postcondition_of(refine(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_segment::refine." << endl;
  return;
}

void
geometry::kd_segment::
refine(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::refine." << endl;

  // Preconditions:

  require(xhost.segments().contains(xid));
  require(xhost.points().d_cells_contains(xpt_id));
  require(xhost.base_space().in_jim_edit_mode());

  define_old_variable(scoped_index old_xid_point_1 = point(xhost, xid, 1));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();

  // Create the new segment.

  xresult = xhost.segments().new_member();

  // Get the second point of the old segment.

  scoped_index lpt1_id = point(xhost, xid, 1);

  // Insert the old segment in the upper cover of the new point.
  // If the "new" point was not previously contained in something else,
  // this is the first member of the upper cover.

  lbase.insert_cover_member(xid, UPPER, xpt_id);

  // The new point replaces the second point
  // in the lower cover of the old segment.

  lbase.replace_cover_member(lpt1_id, xpt_id, LOWER, xid);

  // Link the new segment to the new point.
  // If the "new" point was not previously contained in something else,
  // this is the second member of its upper cover.

  lbase.new_link(xresult, xpt_id);

  // Insert the second point in the lower cover of the new segment

  lbase.insert_cover_member(lpt1_id, LOWER, xresult);
  
  // The new segment replaces the old segment
  // in the upper cover of the second point.

  lbase.replace_cover_member(xid, xresult, UPPER, lpt1_id);

  // Insert the new segment in the face containing xid.

  scoped_index lface_id;
  face(xhost, xid, lface_id);
  lbase.new_link(lface_id, xresult);

  // Insert the new segment in the line containing xid.

  scoped_index lline_id;
  line(xhost, xid, lline_id);
  kd_line::insert_segment(xhost, lline_id, xresult, xid, true); 

  // Update the lst segments subposet.

  if(xhost.last_segments().contains(xid))
  {
    xhost.last_segments().remove_member(xid);
    xhost.last_segments().insert_member(xresult);
  }
  
  // Postconditions:

  ensure(xhost.segments().contains(xresult));
  ensure(point(xhost, xid, 1) == xpt_id);
  ensure(point(xhost, xresult, 0) == xpt_id);
  ensure(point(xhost, xresult, 1) == old_xid_point_1);
  ensure(line(xhost, xresult) == line(xhost, xid));
  ensure(face(xhost, xresult) == face(xhost, xid));
  
  // Exit:

  // cout << "Leaving kd_segment::refine." << endl;
  return;
}

void
geometry::kd_segment::
refine(const scoped_index& xpt_id, const scoped_index& xface0_id, const scoped_index& xface1_id, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::refine." << endl;

  // Preconditions:

  require(precondition_of(refine(host(), id(), xresult, xface0_id, xface1_id)));

  // Body:

  refine(*_host, _id, xpt_id, xface0_id, xface1_id, xresult);

  // Postconditions:

  ensure(postcondition_of(refine(host(), id(), xresult, xface0_id, xface1_id)));

  // Exit:

  // cout << "Leaving kd_segment::refine." << endl;
  return;
}

void
geometry::kd_segment::
refine(kd_lattice& xhost, 
       const scoped_index& xid, 
       const scoped_index& xpt_id, 
       const scoped_index& xface0_id, 
       const scoped_index& xface1_id, 
       scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::refine." << endl;

  // Preconditions:

  require(xhost.segments().contains(xid));
  require(xhost.points().d_cells_contains(xpt_id));
  require(xhost.base_space().in_jim_edit_mode());
  require(face(xhost, xid).is_valid());

  define_old_variable(scoped_index old_xid_point_1 = point(xhost, xid, 1));
  
  // Body:

  // Refine the segment.

  refine(xhost, xid, xpt_id, xresult);
  
  // Replace the existing face of the old segment with xface0_id
  // and the face of the new segment with xface1_id.

  base_space_poset& lbase = xhost.base_space();

  scoped_index lold_face_id;
  face(xhost, xid, lold_face_id);

  lbase.remove_cover_member(xid, LOWER, lold_face_id);
  lbase.insert_cover_member(xid, LOWER, xface0_id);
  lbase.replace_cover_member(lold_face_id, xface0_id, UPPER, xid);

  lbase.remove_cover_member(xresult, LOWER, lold_face_id);
  lbase.insert_cover_member(xresult, LOWER, xface1_id);
  lbase.replace_cover_member(lold_face_id, xface1_id, UPPER, xresult);
  
  // Postconditions:

  ensure(xhost.segments().contains(xresult));
  ensure(point(xhost, xid, 1) == xpt_id);
  ensure(point(xhost, xresult, 0) == xpt_id);
  ensure(point(xhost, xresult, 1) == old_xid_point_1);
  ensure(line(xhost, xresult) == line(xhost, xid));
  ensure(face(xhost, xid) == xface0_id);
  ensure(face(xhost, xresult) == xface1_id);
  
  // Exit:

  // cout << "Leaving kd_segment::refine." << endl;
  return;
}

void
geometry::kd_segment::
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
geometry::kd_segment::
coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub)
{
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.segments().contains(xid));

  // Body:

  // Get the point ids.

  scoped_index lv_ids[POINT_CT];
  points(xhost, xid, lv_ids);

  coord_bounds(xhost, lv_ids[0], lv_ids[1], xlb, xub);
  
  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::e3_lite
geometry::kd_segment::
coord_lower_bound() const
{
  // cout << endl << "Entering kd_segment::coord_lower_bound." << endl;

  // Preconditions:

  require(precondition_of(coord_lower_bound(host(), id())));

  // Body:

  e3_lite result = coord_lower_bound(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(coord_lower_bound(host(), id())));

  // Exit:

  // cout << "Leaving kd_segment::coord_lower_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_segment::
coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_segment::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.segments().contains(xid));

  // Body:

  e3_lite result, lub;
  coord_bounds(xhost, xid, result, lub);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_segment::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_segment::
coord_upper_bound() const
{
  // cout << endl << "Entering kd_segment::coord_upper_bound." << endl;

  // Preconditions:

  require(precondition_of(coord_upper_bound(host(), id())));

  // Body:

  e3_lite result = coord_upper_bound(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(coord_upper_bound(host(), id())));

  // Exit:

  // cout << "Leaving kd_segment::coord_upper_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_segment::
coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_segment::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.segments().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  e3_lite llb, result;
  coord_bounds(xhost, xid, llb, result);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_segment::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

void
geometry::kd_segment::
put_coord_bounds(const e3_lite& xlb, const e3_lite& xub, bool xforward)
{
  // cout << endl << "Entering kd_segment::put_coord_bounds(const e3_lite&, const e3_lite&b, bool)." << endl;
  // Preconditions:

  require(host().coords().state_is_read_write_accessible());
  
  // Body:

  put_coord_bounds(*_host, _id, xlb, xub, xforward);
  
  // Postconditions:

  ensure(coord_lower_bound() == xlb);
  ensure(coord_upper_bound() == xub);

  // Exit:

  // cout << "Leaving kd_segment::put_coord_bounds(const e3_lite&, const e3_lite&, bool)." << endl;
  return;
}

void
geometry::kd_segment::
put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub, bool xforward)
{
  // cout << endl << "Entering kd_segment::put_coord_bounds(kd_lattice&, const scoped_index&, const e3_lite&, const e3_lite&, bool)." << endl;

  // Preconditions:

  require(xhost.segments().contains(xid));
  require(xhost.coords().state_is_read_write_accessible());
  
  // Body:

  // Get the point ids.

  scoped_index lv_ids[POINT_CT];
  points(xhost, xid, lv_ids);

  // Set the coordinates for the points.

  sec_e3& lcoords = xhost.coords();
  if(xforward)
  {
    lcoords.put_fiber(lv_ids[0], xlb, false);
    lcoords.put_fiber(lv_ids[1], xub, false);
  }
  else
  {
    lcoords.put_fiber(lv_ids[0], xub, false);
    lcoords.put_fiber(lv_ids[1], xlb, false);
  }

  // Postconditions:

  ensure(coord_lower_bound(xhost, xid) == xlb);
  ensure(coord_upper_bound(xhost, xid) == xub);
  
  // Exit:

  // cout << "Leaving kd_segment::put_coord_bounds(kd_lattice&, const scoped_index&, const e3_lite&, const e3_lite&, bool)." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_segment::
line()
{
  // cout << endl << "Entering kd_segment::line." << endl;

  // Preconditions:

  require(precondition_of(line(host(), id())));

  // Body:

  scoped_index result = line(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(line(host(), id())));

  // Exit:

  // cout << "Leaving kd_segment::line." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_segment::
line(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_segment::line." << endl;

  // Preconditions:

  require(precondition_of(line(xhost, xid, result)));

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  scoped_index result;
  line(xhost, xid, result);
  
  // Postconditions:

  ensure(postcondition_of(line(xhost, xid, result)));
  
  // Exit:

  // cout << "Leaving kd_segment::line." << endl;
  return result;
}

void
geometry::kd_segment::
line(scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::line." << endl;

  // Preconditions:

  require(precondition_of(line(host(), id(), xresult)));

  // Body:

  line(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(line(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_segment::line." << endl;
  return;
}

void
geometry::kd_segment::
line(const kd_lattice& xhost, const scoped_index xid, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::line." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  xresult = xhost.base_space().member_id(false);
  xresult.invalidate();

  // $$SCRIBBLE: is the line always the second member of the upper cover?
  
  const subposet& llines = xhost.lines().sp();
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  while(!litr.is_done())
  {
    if(llines.contains_member(litr.hub_pod()))
    {
      xresult = litr.hub_pod();
      break;
    }
    litr.next();
  }
  
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.is_valid() ? xhost.lines().contains(xresult) : true);
  
  // Exit:

  // cout << "Leaving kd_segment::line." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_segment::
face()
{
  // cout << endl << "Entering kd_segment::face." << endl;

  // Preconditions:

  require(precondition_of(face(host(), id())));

  // Body:

  scoped_index result = face(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(face(host(), id())));

  // Exit:

  // cout << "Leaving kd_segment::face." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_segment::
face(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_segment::face." << endl;

  // Preconditions:

  require(precondition_of(face(xhost, xid, result)));

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // Body:

  scoped_index result(xhost.base_space().member_id(false));
  face(xhost, xid, result);
  
  // Postconditions:

  ensure(postcondition_of(face(xhost, xid, result)));
  
  // Exit:

  // cout << "Leaving kd_segment::face." << endl;
  return result;
}

void
geometry::kd_segment::
face(scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::face." << endl;

  // Preconditions:

  require(precondition_of(face(host(), id(), xresult)));

  // Body:

  face(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(face(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_segment::face." << endl;
  return;
}

void
geometry::kd_segment::
face(const kd_lattice& xhost, scoped_index xid, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::face." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().contains(xid));
  
  // xid passed by value to avoid &xid == &xresult.

  // Body:

  xresult = xhost.base_space().member_id(false);
  xresult.invalidate();

  // $$SCRIBBLE: is the face always the first member of the upper cover?
  
  const subposet& lfaces = xhost.faces().sp();
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  while(!litr.is_done())
  {
    if(lfaces.contains_member(litr.hub_pod()))
    {
      xresult = litr.hub_pod();
      break;
    }
    litr.next();
  }
  
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.is_valid() ? xhost.faces().contains(xresult) : true);
  
  // Exit:

  // cout << "Leaving kd_segment::face." << endl;
  return;
}

void
geometry::kd_segment::
surfaces(id_list& xresult) const
{
  // cout << endl << "Entering kd_segment::surfaces." << endl;

  // Preconditions:

  require(precondition_of(surfaces(host(), id(), xresult)));
  
  // Body:

  surfaces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(surfaces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_segment::surfaces." << endl;
  return;
}

void
geometry::kd_segment::
surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_segment::surfaces." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // We've implemented triangles without edges, so segments aren't
  // directly connected to surfaces. The defining condition becomes
  // a segment is in a surface if both its points are in the surface.

  // Get the points.

  scoped_index lpt_ids[POINT_CT];
  points(xhost, xid, lpt_ids);
  
  // Get the surfaces for the first point.

  id_list lsurfs0;
  kd_point::surfaces(xhost, lpt_ids[0], lsurfs0);
  
  // Get the surfaces for the second point.

  id_list lsurfs1;
  kd_point::surfaces(xhost, lpt_ids[1], lsurfs1);
  
  // Intersect the lists.

  for(id_list::iterator i0=lsurfs0.begin(); i0!=lsurfs0.end(); ++i0)
  {
    for(id_list::iterator i1=lsurfs1.begin(); i1!=lsurfs1.end(); ++i1)
    {
      if(*i1 == *i0)
      {
        xresult.push_back(*i1);
      }
    }
  }

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_segment::surfaces." << endl;
  return;
}

void
geometry::kd_segment::
surface(scoped_index& xresult) const
{
  // cout << endl << "Entering kd_segment::surface." << endl;

  // Preconditions:

  require(precondition_of(surface(host(), id(), xresult)));
  
  // Body:

  surface(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(surface(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_segment::surface." << endl;
  return;
}

void
geometry::kd_segment::
surface(const kd_lattice& xhost, const scoped_index& xid, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::surface." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().is_active(xid));
  require(line(xhost, xid).is_valid()); // Line insertion complete.  

  // Body:

  // Each segment is in exactly one line and 
  // (once the line is fully inserted) each line 
  // is in exactly one surface.

  scoped_index lline_id;
  line(xhost, xid, lline_id);
  
  kd_line::surface(xhost, lline_id, xresult);

  // Postconditions:

  ensure(xhost.surfaces().contains(xresult));  
  
  // Exit:

  // cout << "Leaving kd_segment::surface." << endl;
  return;
}

void
geometry::kd_segment::
triangles(id_list& xresult) const
{
  // cout << endl << "Entering kd_segment::triangles." << endl;

  // Preconditions:

  require(precondition_of(triangles(host(), id(), xresult)));
  
  // Body:

  triangles(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(triangles(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_segment::triangles." << endl;
  return;
}

void
geometry::kd_segment::
triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_segment::triangles." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // We've implemented triangles without edges, so segments aren't
  // directly connected to triangles. The defining condition becomes
  // a segment is in a triangle if both its points are in the triangle.

  // Get the points.

  scoped_index lpt_ids[POINT_CT];
  points(xhost, xid, lpt_ids);

  // $$SCRIBBLE: replace the following with triangles(xhost, lpt_ids[0], lpt_ids[1], id_set);
  
  // Get the triangles for the first point.

  id_list ltris0;
  kd_point::triangles(xhost, lpt_ids[0], ltris0);
  
  // Get the triangles for the second point.

  id_list ltris1;
  kd_point::triangles(xhost, lpt_ids[1], ltris1);
  
  // Merge the lists.

  // $$SCRIBBLE: there may be an efficiency problem here.
  // Each point is in ~4 triangles, so there are ~16
  // iterations in the loop.

  for(id_list::iterator i0=ltris0.begin(); i0!=ltris0.end(); ++i0)
  {
    for(id_list::iterator i1=ltris1.begin(); i1!=ltris1.end(); ++i1)
    {
      if(*i1 == *i0)
      {
        xresult.push_back(*i1);
      }
    }
  }

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_segment::triangles." << endl;
  return;
}

void
geometry::kd_segment::
triangles(const kd_lattice& xhost, const scoped_index& xv0_id, const scoped_index& xv1_id, id_set& xresult)
{
  // cout << endl << "Entering kd_segment::triangles." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xv0_id));
  require(xhost.points().is_active(xv1_id));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // Get the triangles that contain xv0_id.

  id_list lids;
  kd_point::triangles(xhost, xv0_id, lids);
    
  id_set lv0_tris(lids.begin(), lids.end());
    
  // Get the triangles that contain xv1_id.

  lids.clear();
  kd_point::triangles(xhost, xv1_id, lids);
    
  id_set lv1_tris(lids.begin(), lids.end());
    
  // Find the triangles that contain both points.
  
  insert_iterator<id_set> litr(xresult, xresult.end());
  
  set_intersection(lv0_tris.begin(), lv0_tris.end(), lv1_tris.begin(), lv1_tris.end(), litr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_segment::triangles." << endl;
  return;
}

bool
geometry::kd_segment::
is_boundary() const
{
  // cout << endl << "Entering kd_segment::is_boundary." << endl;

  // Preconditions:

  require(precondition_of(is_boundary(host(), id())));
  
  // Body:

  bool result = is_boundary(host(), id());
  
  // Postconditions:

  ensure(postcondition_of(is_boundary(host(), id())));

  // Exit:

  // cout << "Leaving kd_segment::is_boundary." << endl;
  return result;
}

bool
geometry::kd_segment::
is_boundary(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_segment::is_boundary." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.segments().is_active(xid));

  // Body:

  // A segment is on the boundary of a surface
  // if each triangle it is contained in is in
  // a different surface.

  // Note that this condition is correct only
  // for instantiated segments. Truncation segments
  // containing a truncation midpoint are not
  // instantiaed as segments but are considered
  // part of the boundary even if they are
  // contained in 2 triangles.

  id_list ltri_ids;
  kd_segment::triangles(xhost, xid, ltri_ids);
  
  
  int ltri_ct = ltri_ids.size();

  bool result = false;
  if(ltri_ct == 1)
  {
    // Segment is in only one triangle,
    // has to be on the boundary.

    result =  true;
  }
  else if(ltri_ct == 2)
  {
    // Segment is on the boundary if the two triangles
    // are in different surfaces.

    scoped_index lsurf_id0, lsurf_id1;
    kd_triangle::surface(xhost, ltri_ids.front(), lsurf_id0);
    kd_triangle::surface(xhost, ltri_ids.back(), lsurf_id1);
    
    result = lsurf_id0 != lsurf_id1;
  }
  else if(ltri_ct > 2)
  {
    // The triangles can't all be in the same surface.

    result = true;
  }
  
  // Postconditions:

  // Exit:

  // cout << "Leaving kd_segment::is_boundary." << endl;
  return result;
}

void
geometry::kd_segment::
clear(scoped_index xpoints[])
{
  // cout << endl << "Entering kd_segment::clear." << endl;

  // Preconditions:

  require(precondition_of(clear(host(), id(), xpoints)));

  // Body:

  clear(*_host, _id, xpoints);

  // Postconditions:

  ensure(postcondition_of(clear(host(), id(), xpoints)));

  // Exit:

  // cout << "Leaving kd_segment::clear." << endl;
  return;
}

void
geometry::kd_segment::
clear(kd_lattice& xhost, const scoped_index& xid, scoped_index xpoints[])
{
  // cout << endl << "Entering kd_segment::deactivate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.segments().contains(xid));
  require(unexecutable("xpoints is an array of size at least POINT_CT"));

  define_old_variable(scoped_index old_point_0 = point(xhost, xid, 0));
  define_old_variable(scoped_index old_point_1 = point(xhost, xid, 1));

  // Body:

  base_space_poset& lbase = xhost.base_space();
  
  lbase.clear_cover(UPPER, xid);

  scoped_index lid;
  
  for(int i=0; i<POINT_CT; ++i)
  {
    lbase.first_cover_member(LOWER, xid, lid);
    xpoints[i] = lid;
    lbase.delete_link(xid, lid);
  }

  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, xid));
  ensure(xhost.base_space().cover_is_empty(LOWER, xid));
  ensure(xpoints[0] == old_point_0);
  ensure(xpoints[1] == old_point_1);
  
  // Exit:

  // cout << "Leaving kd_segment::deactivate." << endl;
  return;
}

void
geometry::kd_segment::
deactivate()
{
  // cout << endl << "Entering kd_segment::deactivate." << endl;

  // Preconditions:

  require(precondition_of(deactivate(host(), id())));

  // Body:

  deactivate(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(deactivate(host(), id())));

  // Exit:

  // cout << "Leaving kd_segment::deactivate." << endl;
  return;
}

void
geometry::kd_segment::
deactivate(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_segment::deactivate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.segments().contains(xid));
  require(xhost.base_space().cover_is_empty(UPPER, xid));
  require(xhost.base_space().cover_is_empty(LOWER, xid));
  

  // Body:

  xhost.first_segments().remove_member(xid);
  xhost.last_segments().remove_member(xid);
  xhost.segments().delete_member(xid);
  
  // Postconditions:

  ensure(!xhost.first_segments().contains(xid));
  ensure(!xhost.last_segments().contains(xid));
  ensure(!xhost.segments().is_active(xid));
  
  // Exit:

  // cout << "Leaving kd_segment::deactivate." << endl;
  return;
}
void
geometry::kd_segment::
find(const kd_lattice& xhost, const scoped_index& xid0, const scoped_index& xid1, scoped_index& xresult)
{
  // cout << endl << "Entering kd_segment::find." << endl;

  // Preconditions:


  // Body:

  xresult = xhost.base_space().member_id(false);
  xresult.invalidate();

  // Get the segments for the first point.

  id_list lsegs0;
  kd_point::segments(xhost, xid0, lsegs0);
  
  // Get the segments for the second point.

  id_list lsegs1;
  kd_point::segments(xhost, xid1, lsegs1);
  
  // Merge the lists.

  // $$SCRIBBLE: there may be an efficiency problem here.
  // Each point is in ~2 segments, so there are ~4
  // iterations in the loop.

  for(id_list::iterator i0=lsegs0.begin(); i0!=lsegs0.end(); ++i0)
  {
    for(id_list::iterator i1=lsegs1.begin(); i1!=lsegs1.end(); ++i1)
    {
      if(*i1 == *i0)
      {
        // Found a segment containing both points.
        xresult = *i1;

        // One is enough.

        break;
      }
    }

    if(xresult.is_valid())
    {
      break;
    }
  }

  // Postconditions:

  ensure(!xresult.is_valid() || xhost.base_space().contains_link(xresult, xid0));
  ensure(!xresult.is_valid() || xhost.base_space().contains_link(xresult, xid1));
  
  // Exit:

  // cout << "Leaving kd_segment::find." << endl;
  return;
}

// void
// geometry::kd_segment::
// next_polygon_segment(const id_set& xfaces, scoped_index& xresult)
// {
//   // cout << endl << "Entering kd_segment::next_polygon_segment." << endl;

//   // Preconditions:

//   require(precondition_of(next_polygon_segment(host(), id(), xfaces, xresult)));

//   // Body:

//   next_polygon_segment(*_host, _id, xfaces, xresult);

//   // Postconditions:

//   ensure(postcondition_of(next_polygon_segment(host(), id(), xfaces, xresult)));

//   // Exit:

//   // cout << "Leaving kd_segment::next_polygon_segment." << endl;
//   return;
// }

// void
// geometry::kd_segment::
// next_polygon_segment(const kd_lattice& xhost, const scoped_index xid, int xi, const id_set& xfaces, scoped_index& xresult)
// {
//   // cout << endl << "Entering kd_segment::next_polygon_segment." << endl;

//   // Preconditions:

//   require(xhost.base_space().state_is_read_accessible());
//   require(xhost.segments().contains(xid));
//   require(xhost.leaves().contains(xid));
//   require((0 <= xi) && (xi < POINT_CT));
//   require(unexecutable("xfaces contains the faces of the current zone."));
  
//   // Body:

//   xresult.invalidate();

//   const base_space_poset& lbase = xhost.base_space();

//   scoped_index lface_id;
//   face(xhost, xid, lface_id);

//   scoped_index lpt_id = point(xhost, xid, xi);
  
//   if(xhost.edge_points().contains(lpt_id))
//   {
//     // The point is on an edge of the current face.

//     if(xhost.intersection_points().contains(lpt_id))
//     {
//       // The point is an intersection point;
//       // search its up-set for a segment in a different
//       // face of the same zone.

//       index_space_iterator& litr0 = lbase.cover_iterator(UPPER, lpt_id);
//       while(!litr0.is_done() && !xresult.is_valid())
//       {
//         if(xhost.segments().contains(litr0.item()) && (litr0.item() != xid))
//         {
//           index_space_iterator& litr1 = lbase.cover_iterator(UPPER, litr0.item());
//           while(!litr1.is_done() && !xresult.is_valid())
//           {
//             if(xfaces.find(litr1.item()) != xfaces.end())
//             {
//               if(litr1.item() != lface_id)
//               {
//                 // The current segment is in a 
//                 // different face of the same zone.
//                 // We've found the next polygon segment.

//                 xresult = litr0.item();
//               }
//               else
//               {
//                 // Found a different segment in the same face;
//                 // lpt must be both an intersection point and
//                 // a trruncation point; ignore this segment.

//                 assertion(xhost.truncation_points().contains(lpt_id));
//               }
//             }
//             else
//             {
//               // Litr1.item() is not a face in the current zone;
//               // ignore it.
//             }
          
//             litr1.next();
//           } // end while(!litr1.is_done())
//         }
//         else
//         {
//           // Litr0.item() is either not a segment or is xid;
//           // either way, ignore it.
//         }
      
//         litr0.next();
//       } // while(!litr0.is_done())
//     } // end if(intersection point)
//     else
//     {
//       // The point is an edge point, but not an intersection point,
//       // ignore it.
//     }
//   } // end if(edge_point)
//   else if(xhost.truncation_points().contains(lpt_id))
//   {
//     // The point is in interior of the current face
//     // and is a truncation point; look for a segment 
//     // in the same line as xid.

//     scoped_index lthis_line_id;
//     line(xhost, xid, lthis_line_id);

//     index_space_iterator& litr0 = lbase.cover_iterator(UPPER, lpt_id);
//     while(!litr0.is_done() && !xresult.is_valid())
//     {
//       if(xhost.segments().contains(litr0.item()) && (litr0.item() != xid))
//       {
//         scoped_index lother_line_id;
//         line(xhost, litr0.item(), lother_line_id);
//         if(lother_line_id == line_id)
//         {
//           // Current segment is in the same line;
//           // we've found the next polygon segment.

//           xresult = litr0.item();
//         }
//         else
//         {
//           // Current segment is in a different line,
//           // ignore it.
//         }
//       }
//       litr0.next();
//     }
//   } // end else if(truncation point).
//   else
//   {
//     // The point is in the interior of the face and
//     // is not a truncation point; any connected
//     // segment is in the same line.

//     index_space_iterator& litr0 = lbase.cover_iterator(UPPER, lpt_id);
//     while(!litr0.is_done() && !xresult.is_valid())
//     {
//       if(xhost.segments().contains(litr0.item()) && (litr0.item() != xid))
//       {
//         xresult = litr0.item();
//       }
//       litr0.next();
//     }
//   } // end else not a truncation point.    
  
//   // Postconditions:

//   ensure(!xresult.is_valid() || xhost.segments().contains(xresult));

//   // Exit:

//   // cout << "Leaving kd_segment::next_polygon_segment." << endl;
//   return;
// }



// PROTECTED MEMBER FUNCTIONS

geometry::kd_segment::
kd_segment()
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
geometry::kd_segment::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_segment*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_segment*
geometry::kd_segment::
clone() const
{
  kd_segment* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_segment();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_segment&
geometry::kd_segment::
operator=(const kd_segment& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_segment&
geometry::kd_segment::
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
geometry::kd_segment::
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
operator << (ostream& xos, const kd_segment& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  xos << "segment " << xn.host().segments().id_space().pod(xn.id());
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

  scoped_index lids[kd_segment::POINT_CT];

  xos << "\tpoints:";
  xn.points(lids);
  for(int i=0; i<kd_segment::POINT_CT; ++i)
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
deep_size(const kd_segment& xn, bool xinclude_shallow)
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
