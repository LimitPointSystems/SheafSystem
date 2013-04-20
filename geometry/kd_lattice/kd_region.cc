

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_region

#include "kd_region.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "index_iterator.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_bounding_box.h"
#include "kd_face.h"
#include "kd_lattice.h"
#include "kd_plane.h"
#include "kd_surface.h"
#include "kd_triangle.h"
#include "kd_zone.h"
#include "sec_e3.h"
#include "subcohort.h"

using namespace geometry; // Workaround for MS C++ bug.

//namespace
//{

typedef kd_triangle::ot ot;
typedef kd_triangle::ot_list ot_list;
typedef kd_triangle::ot_hash ot_hash;
typedef kd_triangle::ot_set ot_set;

  
//}


// ===========================================================
// KD_REGION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_region::
prototype_name()
{
  // cout << endl << "Entering kd_region::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("part");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_region::prototype_name." << endl;
  return result;
}

geometry::kd_region::
kd_region(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub)
  :kd_member(xhost)
{
  // cout << endl << "Entering kd_region::kd_region." << endl;

  // Preconditions:

  require(precondition_of(new_region(xhost, xlb, xub, id())));
  
  // Body:

  new_region(xhost, xlb, xub, _id);
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(postcondition_of(new_region(xhost, xlb, xub, id())));

  // Exit:

  // cout << "Leavinging kd_region::kd_region." << endl;
  return; 
}

void
geometry::kd_region::
new_region(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub, scoped_index& xresult)
{
  // cout << endl << "Entering kd_region::new_region." << endl;

  // Preconditions:

  require(xhost.bounding_box().contains_point(xlb));
  require(xhost.bounding_box().contains_point(xub));
  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());

  define_old_variable(size_type old_surfaces_ct = xhost.surfaces().ct());
    
  // Body:


  // Create the region member;
  // the region *is* its bounding surface.

  kd_surface::new_surface(xhost, xresult);

  // Link under the active part.

  xhost.base_space().new_link(xhost.active_part().index(), xresult);

  // cout << "new region: " << xresult << "  " << name(xhost, xresult) << endl;

//   // Create the bounding box.

//   kd_bounding_box lbox(xlb, xub);
//   xhost.put_bounding_box(xresult, lbox);
 
  // Find or create the planes bounding the region.
  // Planes are same order as faces in zone, namely
  // Planes 0, 1 are z-aligned with z(0) < z(1).
  // Planes 2, 3 are x-aligned with x(2) < x(3).
  // Planes 4, 5 are y-aligned with y(4) < y(5).

  kd_plane lplanes[FACE_CT];
  lplanes[0].put(Z_AXIS_ALIGNED, xlb[2]);
  lplanes[1].put(Z_AXIS_ALIGNED, xub[2]);
  lplanes[2].put(X_AXIS_ALIGNED, xlb[0]);
  lplanes[3].put(X_AXIS_ALIGNED, xub[0]);
  lplanes[4].put(Y_AXIS_ALIGNED, xlb[1]);
  lplanes[5].put(Y_AXIS_ALIGNED, xub[1]);
  
  // Find or create the planes.
  // Note that we have to extract any implicit lines we need
  // for every plane before inserting any plane, because plane
  // insertion will remove triangles.

  pt_list_list lilines[FACE_CT];
  for(int i=0; i<FACE_CT; ++i)
  {
    // cout << "Checking for plane equivalent to: " << lplanes[i] << endl;
    
    if(!xhost.contains_equivalent_plane(lplanes[i]))
    {
      // Extract the implicit lines where the plane intesects surfaces.

      // cout << "No equivalent plane, extracting implicit lines: "  << endl;

      xhost.implicit_lines(lplanes[i], lilines[i]);

      // cout << "Implicit lines: " << endl << lilines[i] << endl;
    }
  }

  bool old_xhost_auto_triangulate = xhost.auto_triangulate();
  xhost.put_auto_triangulate(false);
  
  for(int i=0; i<FACE_CT; ++i)
  {
    // cout << "region face: " << i << endl;
    
    // cout << "Checking for plane equivalent to: " << lplanes[i] << endl;
    
    if(xhost.contains_equivalent_plane(lplanes[i]))
    {
      
      lplanes[i] = xhost.equivalent_plane(lplanes[i]);

      // cout << "Found equivalent plane: " << lplanes[i] << endl;

      // $$SCRIBBLE: we're assuming here that if a plane exists,
      // it has been fully interpreted.
    }
    else
    {
      // Create the plane.

      xhost.insert_plane(lplanes[i]);

      // cout << "Created new plane." << endl;

      if(!lilines[i].empty())
      {
        // Make the implicit lines explicit.

        for(pt_list_list::iterator l=lilines[i].begin(); l!=lilines[i].end(); ++l)
        {
          xhost.insert_line(*l, lplanes[i]);
        }
      }
    }
  }

  // Retriangulate any zones we cleared.

  xhost.retriangulate_cleared_zones();
  xhost.put_auto_triangulate(old_xhost_auto_triangulate);

  // Set the bounding box from the actual planes used.

  e3_lite llb, lub;
  
  llb[2] = lplanes[0].distance();
  lub[2] = lplanes[1].distance();
  llb[0] = lplanes[2].distance();
  lub[0] = lplanes[3].distance();
  llb[1] = lplanes[4].distance();
  lub[1] = lplanes[5].distance();

  kd_bounding_box lbox(llb, lub);
  xhost.put_bounding_box(xresult, lbox);
  
  
  //  xhost.display(false, true);
  
  // Now all the planes and lines are explicit.  
  // Gather the face leaves and triangulate them.

  // Inexplicably, the edges of the faces are ordered so the right-hand normal
  // points to decreasing alignment coordinate for x and y alignment,
  // but increasing alignment coordinate for z alignment. The triangles
  // generated here will inherit inherit that order, in two steps.
  // First, the polygon ordering in kd_line_fragment.c:find_frag_any_surface_no_rev
  // requires the normal to the polygon to point in the local +w direction.
  // Since the local axes are right-handed, this means we want the edges
  // ordered so the normal points in increasing alignment coordinate.
  // Once the polygons are properly ordered, we need to reverse the
  // polygons in the upper bound faces so they point into the region,
  // that is, so the point to decreasing alignment coordinate.

  // To get the edges oriented to increasing alignment coordinate,
  // we want to use the stored order (true) or its reverse (false)
  // as follows:

  static const bool ledge_fwd[FACE_CT] = {true, true, false, false, false, false};   

  // To get the polygons oriented inward, we want to use the 
  // generated order (true) or its reverse (false) as follows:

  static const bool lpolygon_fwd[FACE_CT] = {true, false, true, false, true, false};   

  // $$SBRIBBLE: we need to reorient the faces so they always point to
  // increasing alignment coordinate.

  for(int i=0; i<FACE_CT; ++i)
  {
    // Gather the leaves for this face.

    // cout << endl << "Gather leaves for region face: " << i << "  plane: " << lplanes[i] << endl;

    id_list lface_ids;
    xhost.find_face_leaves(lbox, lplanes[i], lface_ids);

    // Triangulate the leaves; links triangles to face and surface.

    for(id_list::iterator lf=lface_ids.begin(); lf!=lface_ids.end(); ++lf)
    {
      kd_face::triangulate(xhost, *lf, xresult, ledge_fwd[i], lpolygon_fwd[i]);

#ifdef DIAGNOSTIC_OUTPUT

      // Just for debugging: print the triangles.

      cout << "face: " << lf->pod() << "  " << name(xhost, *lf) << endl;
      cout << "triangulate forward: " << boolalpha << lfwd[i] << noboolalpha << endl;

      scoped_index lpt_ids[kd_triangle::POINT_CT];
      e3_lite lpts[kd_triangle::POINT_CT], ln;
      id_list ltris;
      kd_face::triangles(xhost, *lf, ltris);
      for(id_list::iterator lt=ltris.begin(); lt!=ltris.end(); ++lt)
      {
        kd_triangle::points(xhost, *lt, lpt_ids, lpts);
        kd_triangle::normal(xhost, *lt, ln);
        
        cout << "triangle: " << setw(6) << lt->pod();
        cout << setw(16) << name(xhost, *lt);
        cout << "  pt ids: ";
        cout << setw(6) << lpt_ids[0].pod();
        cout << setw(6) << lpt_ids[1].pod();
        cout << setw(6) << lpt_ids[2].pod();
        cout << "  pts: ";
        cout << setw(8) << lpts[0][0] << setw(8) << lpts[0][1] << setw(8) << lpts[0][2];
        cout << setw(8) << lpts[1][0] << setw(8) << lpts[1][1] << setw(8) << lpts[1][2];
        cout << setw(8) << lpts[2][0] << setw(8) << lpts[2][1] << setw(8) << lpts[2][2];
        cout << "  normal";
        cout << setw(8) << ln[0] << setw(8) << ln[1] << setw(8) << ln[2];
        cout << endl;
      }

#endif

    }
  }

  // Mark all the interior triangles.
  // $$SCRIBBLE: reimplement as tree trversal.

  // cout << "find interior triangles:" << endl;
  
  cohort& linterior_tris = xhost.interior_triangles();
  id_list ltris;
  index_iterator lz_itr = xhost.zone_leaves().sp().indexed_member_iterator();
  while(!lz_itr.is_done())
  {
    // cout << "looking in zone: " << lz_itr.index().pod() << " triangles: ";
    
    if(lbox.contains(xhost.bounding_box(lz_itr.index())))
    {
      kd_zone::triangles(xhost, lz_itr.index(), ltris);
      for(id_list::iterator lt = ltris.begin(); lt != ltris.end(); ++lt)
      {
        linterior_tris.insert_member(*lt);
      }
    }
    // cout << ltris << endl;
    ltris.clear();

    lz_itr.next();
  }

  // Mark the surface as new.

  xhost.new_surfaces().insert(xresult);
  xhost.modified_surfaces().erase(xresult);
  xhost.deleted_surfaces().erase(xresult);
  
  // Postconditions:

  // cout << "surfaces.ct: " << xhost.surfaces().ct() << " old surface ct:" << old_surfaces_ct << endl;

  ensure(xhost.surfaces().contains(xresult));
  ensure(xhost.surfaces().ct() == old_surfaces_ct + 1);
  ensure(xhost.new_surfaces().find(xresult) != xhost.new_surfaces().end());
  ensure(xhost.modified_surfaces().find(xresult) == xhost.modified_surfaces().end());
  ensure(xhost.deleted_surfaces().find(xresult) == xhost.deleted_surfaces().end());
  ensure(xhost.auto_triangulate() == old_xhost_auto_triangulate);
  
  // Exit:

  // cout << "Leaving kd_region::new_region." << endl;
  return; 
}

geometry::kd_region::
kd_region(kd_lattice& xhost)
  : kd_member(xhost)
{
  
  // Preconditions:

  
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(&host() == &xhost);
  ensure(!id().is_valid());

  // Exit:

  return; 
}

geometry::kd_region::
kd_region(kd_lattice& xhost, const scoped_index& xid)
  : kd_member(xhost, xid)
{
  
  // Preconditions:

  
  // Body:

  // $$SCRIBBLE: how do we ensure xid refers to a region?
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(id() == xid);

  // Exit:

  return; 
}

geometry::kd_region::
kd_region(const kd_region& xother)
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

geometry::kd_region::
~kd_region()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_region::
members(id_list& xmbrs) const
{
  // Preconditions:

  require(precondition_of(members(host(),id(), xmbrs)));
  
  // Body:

  members(*_host, _id, xmbrs);
  
  // Postconditions:

  ensure(postcondition_of(members(host(),id(), xmbrs)));

  // Exit:

  return;
}

void
geometry::kd_region::
members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs)
{
  // cout << endl << "Entering kd_region::members." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));
  
  // Body:


  if(!is_empty(xhost, xid))
  {
    index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
    scoped_index lid(xhost.base_space().member_id(false));
    while(!litr.is_done())
    {
      lid = litr.hub_pod();

      xmbrs.push_back(lid);
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_region::members." << endl;
  return;
}

void
geometry::kd_region::
triangles(id_list& xtriangles) const
{
  // Preconditions:

  require(precondition_of(triangles(host(),id(), xtriangles)));
  
  // Body:

  triangles(*_host, _id, xtriangles);
  
  // Postconditions:

  ensure(postcondition_of(triangles(host(),id(), xtriangles)));

  // Exit:

  return;
}

void
geometry::kd_region::
triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangles)
{
  // cout << endl << "Entering kd_region::triangles." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));
  
  // Body:

  if(!is_empty(xhost, xid))
  {
    index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
    scoped_index lid(xhost.base_space().member_id(false));
    while(!litr.is_done())
    {
      lid = litr.hub_pod();

      if(xhost.triangles().contains(lid))
      {
        xtriangles.push_back(lid);
      }
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }
  
  // Postconditions:

  // Exit:

  // cout << "Leaving kd_region::triangles." << endl;
  return;
}


void
geometry::kd_region::
clear(pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_region::clear." << endl;

  // Preconditions:

  require(precondition_of(clear(host(), id(), xdeleted)));
  
  // Body:

  clear(*_host, _id, xdeleted);

  // Postconditions:

  ensure(postcondition_of(clear(host(), id(), xdeleted)));

  // Exit:

  // cout << "Leaving kd_region::clear." << endl;
  return;
}

void
geometry::kd_region::
clear(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_region::clear." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.surfaces().contains(xid));
  require(!is_empty(xhost, xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();

  not_implemented();
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    xdeleted.insert(lid);
    if(xhost.triangles().contains(lid))
    {
    }
    else if(xhost.lines().contains(lid))
    {
    }

    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, xid));
  ensure(xhost.base_space().cover_is_empty(LOWER, xid));

  // Exit:

  // cout << "Leaving kd_region::clear." << endl;
  return;
}

bool
geometry::kd_region::
is_empty() const
{
  // cout << endl << "Entering kd_region::is_empty." << endl;

  // Preconditions:

  require(precondition_of(is_empty(host(), id())));

  // Body:

  bool result = is_empty(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_empty(host(), id())));

  // Exit:

  // cout << "Leaving kd_region::is_empty." << endl;
  return result;
}

bool
geometry::kd_region::
is_empty(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_region::is_empty." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  // Body:

  const base_space_poset& lbase = xhost.base_space();

  bool result = lbase.cover_is_empty(LOWER, xid);  

  if(!result)
  {
    // Lower cover contains only triangles.
    result = !xhost.triangles().contains(lbase.first_cover_member(LOWER, xid.hub_pod()));
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_region::is_empty." << endl;
  return result;
}

void
geometry::kd_region::
subvolumes(id_list& xresult)
{
  // cout << endl << "Entering kd_region::subvolumes." << endl;

  // Preconditions:

  require(precondition_of(subvolumes(host(), id(), xresult)));

  // Body:

  subvolumes(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(subvolumes(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_region::subvolumes." << endl;
  return;
}

void
geometry::kd_region::
subvolumes(kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_region::subvolumes." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());

  // $$SCRIBBLE this should be tighter, maybe a std name for roi? or a subcohort?

  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());

  // Body:

  base_space_poset& lbase = xhost.base_space();

  // Extract the transitive closure of the triangle-edge-triangle connectivty,
  // subject to constraints that keep us in the boundary of a given subvolume.
  
  ot_list lot_q;
  ot_set lvisited;
  scoped_index lpt_ids[kd_triangle::POINT_CT];

  // Initialize the queue of triangles to process with
  // the triangles in the roi surface, they all have
  // known, outward facing normals.

  // $$SCRIBBLE: this will only find subvolumes that
  // intersect the roi surface. We need to consider all
  // oriented triangles that remain after following this
  // procedure. Perhaps by removing triangles from an
  // unvisited set rather than inserting them is a visited set.

  id_list lroi;
  kd_surface::triangles(xhost, xid, lroi);

  ot lnbr;

  for(id_list::iterator lrt = lroi.begin(); lrt != lroi.end(); ++lrt)
  {
    // Try to insert roi triangle in visited set.
    // Orientation of roi triangle is always outward == true.

    // cout << "roi triangle: " << *lrt << "  " << name(xhost, *lrt) << endl;

    ot lrtot(*lrt, true);

    if(lvisited.find(lrtot) == lvisited.end())
    {
      // Haven't visited this roi triangle yet.

      // cout << "Not visited before, starting a new subvolume" << endl;

      // Start a new subvolume.

      scoped_index lvol_id(xhost.subvolume_surfaces().new_member());
      lbase.new_link(xhost.active_part().index(), lvol_id);
      xresult.push_back(lvol_id);

      // Only want to link a given triangle to this subvolume
      // once (see call to new_link and associated comments below).
      // Can use contains_cover_member, but default list id space
      // requires O(size of list) time for search.
      // Allocate a hash set to keep track instead.

      pod_id_hash_set llinked;

      // Initialize the oriented triangle queue.

      lot_q.clear();
      lot_q.push_back(lrtot);

      while(!lot_q.empty())
      {
        ot_list::iterator lot = lot_q.begin();

        // cout << "front of q: " << lot->first;
        // cout << "  " << boolalpha << lot->second << noboolalpha << endl;

        if(lvisited.insert(*lot).second)
        {
          // Haven't visited this oriented triangle before.
          // Link it under the subvolume surface.

          // cout << "Haven't visited this oriented triangle before." << endl;          

          // Get the points for this triangle.

          kd_triangle::points(xhost, lot->first, lpt_ids);

          // cout << "triangle: " << setw(6) << lot->first;
          // cout << boolalpha << setw(7) << lot->second << noboolalpha;
          // cout << endl;
          // cout << "   vertices: ";
          // for(int i=0; i<kd_triangle::POINT_CT; ++i)
          // {
            // cout << "  " << lpt_ids[i];
          // }
          // cout << endl;
          
          // cout << "   nbrs:" << endl;
          
          for(int i=0; i<kd_triangle::EDGE_CT; ++i) // edges in triangle
          {
            // Get the inside neighbor through edge i.

            kd_triangle::edge_neighbor(xhost, lot->first, lot->second, lpt_ids, i, lnbr);

            // cout << "   " << lnbr.first;
            // cout << boolalpha << setw(7) << lnbr.second << noboolalpha;
            
            if(lnbr.first.is_valid())
            {
              lot_q.push_back(lnbr);
              // cout << " ... queued: ";
            }
            else
            {
              // No neighbors; do nothing.
            }
            // cout << endl;
          } // end for edges in triangle

          // cout << endl;

          // If we have any internal boundaries, the triangles in
          // the internal boundary will appear twice here, once in each
          // orientation. We currently have no way to distinguish
          // between orientations in the CRG and inserting two links
          // between the same two members is undefined.
          // We can deal with this in 3 ways:
          // 1) Duplicate the triangle in the opposite orientation,
          //    creates a double sided internal boundary.
          // 2) Only insert it once, creates a single sided internal boundary
          // 3) Remove it entirely, no internal boundary.
          //
          // We'll use option 2:

          assertion(lot->first.is_hub_scope());

          if(llinked.insert(lot->first.pod()).second)
          // if(!lbase.cover_contains_member(LOWER, xresult.back(), lot->first))
          {
            // This is the first time we've seen this triangle in
            // this subvolume. Link it.

            lbase.new_link(xresult.back(), lot->first);
          }
          
        } // front of quueue lvisited insert succeeded
        else
        {
          // Front of queue already visited; ignore it.

          // cout << "front of queue already visited; ignore it." << endl;
        }
        
        lot_q.pop_front();

      } // end while queue not empty

      // cout << "queue empty; next roi triangle" << endl;
      
    } // roi lvisit insert succeeded
    else
    {
      // lvisited insert failed, 
      // we've already visited this triangle, 
      // do nothing.

      // cout << "already visited this roi triangle" << endl;
    }
  } // end for triangles in roi.  

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  ensure_for_range(id_list::iterator i=xresult.begin(), i!=xresult.end(), ++i, xhost.subvolume_surfaces().contains(*i));
  
  // Exit:

  // cout << "Leaving kd_region::subvolumes." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::kd_region::
kd_region()
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
geometry::kd_region::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_region*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_region*
geometry::kd_region::
clone() const
{
  kd_region* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_region();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_region&
geometry::kd_region::
operator=(const kd_region& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_region&
geometry::kd_region::
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
geometry::kd_region::
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
operator << (ostream& xos, const kd_region& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  id_list ltris;

  cout << "region of interest surface:" << endl;

  kd_surface::triangles(xn.host(), xn.id(), ltris);
  cout << "triangles: " << endl << ltris << endl;
  
  cout << "subvolumes: " << endl;
  
  index_space_iterator& litr =
    xn.host().subvolume_surfaces().id_space().get_iterator();
  scoped_index lid(xn.host().subvolume_surfaces().id_space());
  while(!litr.is_done())
  {
    lid = litr.pod();

    kd_lattice& lhost = const_cast<kd_lattice&>(xn.host());
    kd_surface lsurf(lhost, lid);
    
    cout << "subvolume: " << lsurf.id().pod() << "  " << lsurf.name() << endl;
    
    ltris.clear();
    lsurf.triangles(ltris);
    cout << "triangles: " << endl << ltris << endl;

    litr.next();
  }
  xn.host().subvolume_surfaces().id_space().release_iterator(litr);

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_region& xn, bool xinclude_shallow)
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
