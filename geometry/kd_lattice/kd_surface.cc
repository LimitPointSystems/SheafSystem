

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_surface

#include "kd_surface.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_lattice.h"
#include "kd_line.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_segment.h"
#include "kd_triangle.h"
#include "postorder_itr.h"
#include "sec_e3.h"
#include "set_filter.h"
#include "std_algorithm.h"
#include "std_hash_set.h"
#include "subcohort.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.

namespace
{

  // Type definitions for kd_surface::boundary_points.

  typedef pod_pair seg_type;

  struct seg_equals
  {
    bool operator()(const seg_type& x0, const seg_type& x1) const
    {
      // x0 and x1 the same if vertices are same or reversed.

      bool result = 
        ((x0.first == x1.first) && (x0.second == x1.second)) || 
        ((x0.first == x1.second) && (x0.second == x1.first)) ;
      
      return result;
    };
  };
  
  struct seg_hash
  {
    size_t operator()(const seg_type& x) const
    {
      return x.first <= x.second ? x.first : x.second;
    };
  };

  typedef hash_set<seg_type, seg_hash, seg_equals> seg_set; 

  ostream & operator << (ostream &xos, const seg_set& xn)
  {
    for(seg_set::const_iterator s=xn.begin(); s!=xn.end(); ++s)
    {
      cout << setw(6) << s->first << setw(6) << s->second << endl;
    }
    
    return xos;
  };

  typedef hash_multimap<pod_index_type, pod_index_type> seg_map;
  typedef seg_map::iterator seg_map_itr;
  typedef pair<seg_map_itr, seg_map_itr> seg_range;
  
  ostream & operator << (ostream &xos, const seg_map& xn)
  {
    for(seg_map::const_iterator s=xn.begin(); s!=xn.end(); ++s)
    {
      cout << setw(6) << s->first << setw(6) << s->second << endl;
    }
    
    return xos;
  };
  
  seg_map_itr find_seg(const seg_type& xseg, seg_map& xmap)
  {
    seg_map_itr result = xmap.end();

    seg_range lrange = xmap.equal_range(xseg.first);
    for(seg_map_itr s=lrange.first; s!=lrange.second; ++s)
    {
      if(s->second == xseg.second)
      {
        result = s;
        break;
      }
    }
    
    return result;
  }
  
    
}


// ===========================================================
// KD_SURFACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_surface::
prototype_name()
{
  // cout << endl << "Entering kd_surface::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("surface");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_surface::prototype_name." << endl;
  return result;
}

geometry::kd_surface::
kd_surface(kd_lattice& xhost)
  :kd_member(xhost)
{
  // cout << endl << "Entering kd_surface::kd_surface." << endl;

  // Preconditions:

  require(precondition_of(new_surface(xhost, id())));
  
  // Body:

  new_surface(xhost, _id);
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(postcondition_of(new_surface(xhost, id())));

  // Exit:

  // cout << "Leavinging kd_surface::kd_surface." << endl;
  return; 
}

void
geometry::kd_surface::
new_surface(kd_lattice& xhost, scoped_index& xresult)
{
  // cout << endl << "Entering kd_surface::new_surface." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());

  define_old_variable(size_type old_surfaces_ct = xhost.surfaces().ct());
    
  // Body:


  // Create the surface member.

  xresult = xhost.surfaces().new_member();

  // cout << "activated surface: " << xresult << "  " << name(xhost, xresult) << endl;

  // Mark the surface as new.

  xhost.new_surfaces().insert(xresult);
  xhost.modified_surfaces().erase(xresult);
  xhost.deleted_surfaces().erase(xresult);
  
  // Postconditions:

  ensure(xhost.surfaces().contains(xresult));
  ensure(xhost.surfaces().ct() == old_surfaces_ct + 1);
  ensure(xhost.base_space().cover_is_empty(UPPER, xresult));
  ensure(xhost.base_space().cover_is_empty(LOWER, xresult));
  ensure(xhost.new_surfaces().find(xresult) != xhost.new_surfaces().end());
  ensure(xhost.modified_surfaces().find(xresult) == xhost.modified_surfaces().end());
  ensure(xhost.deleted_surfaces().find(xresult) == xhost.deleted_surfaces().end());
  

  // Exit:

  // cout << "Leaving kd_surface::new_surface." << endl;
  return; 
}

geometry::kd_surface::
kd_surface(kd_lattice& xhost, const scoped_index& xid)
  : kd_member(xhost, xid)
{
  
  // Preconditions:

  require(xhost.surfaces().contains(xid));
  
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(id() == xid);

  // Exit:

  return; 
}

geometry::kd_surface::
kd_surface(const kd_surface& xother)
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

geometry::kd_surface::
~kd_surface()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_surface::
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
geometry::kd_surface::
members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs)
{
  // cout << endl << "Entering kd_surface::members." << endl;
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

  // cout << "Leaving kd_surface::members." << endl;
  return;
}

void
geometry::kd_surface::
centroids(id_list& xcentroids) const
{
  // Preconditions:

  require(precondition_of(centroids(host(),id(), xcentroids)));

  // Body:

  centroids(*_host, _id, xcentroids);

  // Postconditions:

  ensure(postcondition_of(centroids(host(),id(), xcentroids)));

  // Exit:

  return;
}

void
geometry::kd_surface::
centroids(const kd_lattice& xhost, const scoped_index& xid, id_list& xcentroids)
{
  // cout << endl << "Entering kd_surface::centroids." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  // Body:

  base_space_member lsurf(&xhost.base_space(), xid);
  set_postorder_itr litr(lsurf, xhost.centroids().sp(),true, true);
  while(!litr.is_done())
    {
      xcentroids.push_back(litr.index());
      litr.next();
    }

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_surface::centroids." << endl;
  return;
}

void
geometry::kd_surface::
lines(id_list& xlines) const
{
  // Preconditions:

  require(precondition_of(lines(host(),id(), xlines)));
  
  // Body:

  lines(*_host, _id, xlines);
  
  // Postconditions:

  ensure(postcondition_of(lines(host(),id(), xlines)));

  // Exit:

  return;
}

void
geometry::kd_surface::
lines(const kd_lattice& xhost, const scoped_index& xid, id_list& xlines)
{
  // cout << endl << "Entering kd_surface::lines." << endl;
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

      if(xhost.lines().contains(lid))
      {
        xlines.push_back(lid);
      }
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }  

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_surface::lines." << endl;
  return;
}

void
geometry::kd_surface::
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
geometry::kd_surface::
triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangles)
{
  // cout << endl << "Entering kd_surface::triangles." << endl;
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

  // cout << "Leaving kd_surface::triangles." << endl;
  return;
}

void
geometry::kd_surface::
boundary(id_list_list& xfrags) const
{
  // Preconditions:

  require(precondition_of(boundary(host(),id(), xfrags)));
  
  // Body:

  boundary(*_host, _id, xfrags);
  
  // Postconditions:

  ensure(postcondition_of(boundary(host(),id(), xfrags)));

  // Exit:

  return;
}

void
geometry::kd_surface::
boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xfrags)
{
  // cout << endl << "Entering kd_surface::boundary." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));
  
  // Body:

  // Consider the number of triangles within this surface that 
  // a segment can be included in.
  // If a segment is included in only 1 triangle, it is a boundary segment.
  // If a segment is included in 2 triangles, it is an interior segment.
  // If a segment is included in 3 triangles, it is a self trunction segment,
  // which we consider part of the boundary.
  // If a segment is included in 4 or more triangles of the same surface,
  // then the surface passes through itself, which we don't support.
  // So if a segment is included in an odd number of triangles, it is
  // a boundary segment. We can find the set of segments included in an
  // odd number of triangles by iterating over all the triangles in the 
  // surface and for each segment in the triangle inserting it in the set if it  
  // is not present and erasing it if it is present.

  typedef seg_map::value_type map_value;
  typedef seg_map::size_type map_size_t;
  
  seg_map lmap;
  seg_type lseg, lrev_seg;  
  map_size_t lseg_ct;
  map_value lval;
  seg_map_itr ls;

  scoped_index lpt_ids[kd_triangle::POINT_CT];
  
  // cout << "building bounary of surface: " << xid << "  " << name(xhost, xid) << endl;
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.triangles().contains(lid))
    {
      // cout << "item: " << litr.hub_pod() << "  " << name(xhost, litr.hub_pod());
      kd_triangle::points(xhost, lid, lpt_ids);

      // Triangles are constructed so that point 2
      // is the centroid point of the polygon containing
      // the triangle. So only segment 01 can possibly
      // be a boundary segment, ignore the other segments.      
        
      lseg.first = lpt_ids[0].pod();
      lseg.second = lpt_ids[1].pod();

      lrev_seg.first = lseg.second;
      lrev_seg.second = lseg.first;
      
      // cout << "  testing seg" << setw(6) << lseg << endl;

      ls = find_seg(lseg, lmap);
      if(ls != lmap.end())
      {
        // Boundary map already contains this segment.

        // Check for truncation segment.
        // A segment is a truncation segment if one end is
        // a truncation point and the other is a midpoint.

        bool lone_is_midpoint =
          xhost.truncation_mid_points().contains(lpt_ids[0]) ||
          xhost.truncation_mid_points().contains(lpt_ids[1]);

        bool lone_is_trunc =
          xhost.truncation_points().contains(lpt_ids[0]) ||
          xhost.truncation_points().contains(lpt_ids[1]);

        // cout << boolalpha;
        // cout << "one is midpoint: " << lone_is_midpoint;
        // cout << "  one is trunc: " << lone_is_trunc;
        // cout << noboolalpha;
        // cout << endl;
        
        if(lone_is_midpoint && lone_is_trunc)
        {
          // This is a truncation segment;
          // it is considered part of the boundary
          // whether it is included in an odd
          // number of triangles or not. Leave it.
        }
        else
        {
          // This is a non-truncation segment
          // erase it and its reverse.

          lmap.erase(ls);

          // cout << "  erased: " << endl;

          ls = find_seg(lrev_seg, lmap);
        
          assertion(ls != lmap.end());
        
          lmap.erase(ls);
        }        
      }
      else
      {
        // Map does not contain segment;
        // insert both it and its reverse.

        lmap.insert(lseg);
        lmap.insert(lrev_seg);
        
        // cout << "  inserted: " << endl;
      }
      
    }
    litr.next();
  } // end while

  xhost.base_space().release_cover_id_space_iterator(litr);

  lseg_ct = lmap.size();
  assertion((lseg_ct % 2) == 0);
  lseg_ct /= 2;
  
  // cout << "finished building boundary. size: " << lmap.size() << endl;
  using ::operator<<;
  // cout << lmap << endl;
  
  // Now lmap contains the segments in the boundary;
  // we need to sort them into consecutive segments.
  // We can do this by just following the transitive closure of the
  // the first entry in the map. There are two possible orientations
  // to the boundary, which we get is random.
  //
  // One technical difficulty is that the surface may consist of
  // discontiguous pieces, or pieces that connect only at a point.
  // This is why the result is a fragment list..

  // Create and initial fragment.

  id_list lid_list;

  // Start at the beginning and follow the map entries,
  // pushing the points onto the current fragment.
  
  ls = lmap.begin();
  while(ls != lmap.end())
  {
    // Still mor entries;
    // start a new fragment.

    xfrags.push_back(lid_list);

    while(ls != lmap.end())
    {
      // Push the current point onto the fragment.

      lid.put_pod(ls->first);
      xfrags.back().push_back(lid);

      // Erase the current entry and its reverse
      // so we don't traverse them again.

      lrev_seg.first = ls->second;
      lrev_seg.second = ls->first;

      // cout << "erasing: " << setw(6) << ls->first << setw(6) << ls->second << endl;
    
      lmap.erase(ls);

      ls = find_seg(lrev_seg, lmap);

      assertion(ls != lmap.end());
    
      // cout << "erasing: " << setw(6) << ls->first << setw(6) << ls->second << endl;

      lmap.erase(ls);

      // Now follow the second point thru the map.

      ls = lmap.find(lrev_seg.first);
    }
  
    assertion(ls == lmap.end());
  
    // Second point was a dead end;
    // we've reached the end of a fragment.

    lid.put_pod(lrev_seg.first);
    xfrags.back().push_back(lid);

    ls = lmap.begin();
  }
  
  //   // Check for closure.

  //   if(xfrags.empty())
  //   {
  //     // Error, boundary empty.

  //     post_warning_message("Boundary empty.");
  //   }
  //   else if(xfrags.back().front() != xfrags.back().back())
  //   {
  //     // Error, boundary not closed.

  //     post_warning_message("Boundary not closed");
  //   }


  // Postconditions:

  // Exit:

  // cout << "Leaving kd_surface::boundary." << endl;
  return;
}

void
geometry::kd_surface::
boundary(id_list_list& xtrunc, id_list_list& xnon_trunc) const
{
  // Preconditions:

  require(precondition_of(boundary(host(),id(), xtrunc, xnon_trunc)));
  
  // Body:

  boundary(*_host, _id, xtrunc, xnon_trunc);
  
  // Postconditions:

  ensure(postcondition_of(boundary(host(),id(), xtrunc, xnon_trunc)));

  // Exit:

  return;
}

void
geometry::kd_surface::
boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xtrunc, id_list_list& xnon_trunc)
{
  // cout << endl << "Entering kd_surface::boundary." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xtrunc_size = xtrunc.size());
  define_old_variable(size_type old_xnon_trunc_size = xnon_trunc.size());
  
  // Body:

  id_list_list lfrags;
  kd_surface::boundary(xhost, xid, lfrags);

  bool lone_is_midpoint, lone_is_trunc;

  for(id_list_list::iterator f=lfrags.begin(); f!=lfrags.end(); ++f)
  {
    id_list& lpt_ids = *f;
  
    scoped_index lpt0_id, lpt1_id;
  
    id_list::iterator p=lpt_ids.begin();
    lpt1_id = *p;

    ++p;
  
    while(p!=lpt_ids.end())
    {
      lpt0_id = lpt1_id;
      lpt1_id = *p;

      lone_is_midpoint =
        xhost.truncation_mid_points().contains(lpt0_id) ||
        xhost.truncation_mid_points().contains(lpt1_id);

      lone_is_trunc =
        xhost.truncation_points().contains(lpt0_id) ||
        xhost.truncation_points().contains(lpt1_id);

      if(lone_is_midpoint && lone_is_trunc)
      {
        // This is a truncation segment

        // cout << "found truncation segment. " << endl;        

        if(xtrunc.empty() || (lpt0_id != xtrunc.back().back()))
        {
          // First segment or this segment is not contiguous with previous;
          // start a new fragment.

          id_list lfrag;
          xtrunc.push_back(lfrag);
          xtrunc.back().push_back(lpt0_id);
        }
      
        xtrunc.back().push_back(lpt1_id);
      }
      else
      {
        // This is a non-truncation segment.

        // cout << "found non-truncation segment. " << endl;

        if(xnon_trunc.empty() || (lpt0_id != xnon_trunc.back().back()))
        {
          // First segment or this segment is not contiguous with previous;
          // start a new fragment.

          id_list lfrag;
          xnon_trunc.push_back(lfrag);
          xnon_trunc.back().push_back(lpt0_id);
        }
      
        xnon_trunc.back().push_back(lpt1_id);
      }

      // Move on.

      ++p;
    }
  }
  

  // cout << "truncation list: " << endl;
  // cout << xtrunc << endl;

  // cout << "non-truncation list: " << endl;
  // cout << xnon_trunc << endl;

  // Postconditions:

  ensure(xtrunc.size() >= old_xtrunc_size);
  ensure(xnon_trunc.size() >= old_xnon_trunc_size);
  
  // Exit:

  // cout << "Leaving kd_surface::boundary." << endl;
  return;
}

void
geometry::kd_surface::
truncation_boundary(id_list_list& xpts) const
{
  // Preconditions:

  require(precondition_of(truncation_boundary(host(),id(), xpts)));
  
  // Body:

  truncation_boundary(*_host, _id, xpts);
  
  // Postconditions:

  ensure(postcondition_of(truncation_boundary(host(),id(), xpts)));

  // Exit:

  return;
}

void
geometry::kd_surface::
truncation_boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xpts)
{
  // cout << endl << "Entering kd_surface::truncation_boundary." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xpts_size = xpts.size());
  
  // Body:

  id_list_list lnon_trunc;
  kd_surface::boundary(xhost, xid, xpts, lnon_trunc);
  
  // Postconditions:

  ensure(xpts.size() >= old_xpts_size);
  
  // Exit:

  // cout << "Leaving kd_surface::truncation_boundary." << endl;
  return;
}

void
geometry::kd_surface::
non_truncation_boundary(id_list_list& xpts) const
{
  // Preconditions:

  require(precondition_of(non_truncation_boundary(host(),id(), xpts)));
  
  // Body:

  non_truncation_boundary(*_host, _id, xpts);
  
  // Postconditions:

  ensure(postcondition_of(non_truncation_boundary(host(),id(), xpts)));

  // Exit:

  return;
}

void
geometry::kd_surface::
non_truncation_boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xpts)
{
  // cout << endl << "Entering kd_surface::non_truncation_boundary." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xpts_size = xpts.size());
  
  // Body:


  id_list_list ltrunc;
  kd_surface::boundary(xhost, xid, ltrunc, xpts);

  // Postconditions:

  ensure(xpts.size() >= old_xpts_size);
  
  // Exit:

  // cout << "Leaving kd_surface::non_truncation_boundary." << endl;
  return;
}

void
geometry::kd_surface::
truncation_points(id_list& xpts) const
{
  // Preconditions:

  require(precondition_of(truncation_points(host(),id(), xpts)));
  
  // Body:

  truncation_points(*_host, _id, xpts);
  
  // Postconditions:

  ensure(postcondition_of(truncation_points(host(),id(), xpts)));

  // Exit:

  return;
}

void
geometry::kd_surface::
truncation_points(const kd_lattice& xhost, const scoped_index& xid, id_list& xpts)
{
  // cout << endl << "Entering kd_surface::truncation_points." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xpts_size = xpts.size());
  
  // Body:

  base_space_member lsurface(&xhost.base_space(), xid);
  
  hash_set_postorder_itr litr(lsurface, xhost.truncation_points().sp(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xpts.push_back(litr.index());
    litr.next();
  }

  lsurface.detach_from_state();

  // Postconditions:

  ensure(xpts.size() >= old_xpts_size);

  // Exit:

  // cout << "Leaving kd_surface::truncation_points." << endl;
  return;
}

void
geometry::kd_surface::
intersection_points(id_list& xpts) const
{
  // Preconditions:

  require(precondition_of(intersection_points(host(),id(), xpts)));
  
  // Body:

  intersection_points(*_host, _id, xpts);
  
  // Postconditions:

  ensure(postcondition_of(intersection_points(host(),id(), xpts)));

  // Exit:

  return;
}

void
geometry::kd_surface::
intersection_points(const kd_lattice& xhost, const scoped_index& xid, id_list& xpts)
{
  // cout << endl << "Entering kd_surface::intersection_points." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xpts_size = xpts.size());
  
  // Body:

  base_space_member lsurface(&xhost.base_space(), xid);
  
  hash_set_postorder_itr litr(lsurface, xhost.intersection_points().sp(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xpts.push_back(litr.index());
    litr.next();
  }

  lsurface.detach_from_state();
  

  // Postconditions:

  ensure(xpts.size() >= old_xpts_size);

  // Exit:

  // cout << "Leaving kd_surface::intersection_points." << endl;
  return;
}


void
geometry::kd_surface::
insert_line(const scoped_index& xline_id)
{
  // cout << endl << "Entering kd_surface::insert_line." << endl;

  // Preconditions:

  require(precondition_of(insert_line(host(), id(), xline_id)));

  // Body:

  insert_line(*_host, _id, xline_id);

  // Postconditions:

  ensure(postcondition_of(insert_line(host(), id(), xline_id)));

  // Exit:

  // cout << "Leaving kd_surface::insert_line." << endl;
  return;
}

void
geometry::kd_surface::
insert_line(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xline_id)
{
  // cout << endl << "Entering kd_surface::insert_line." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.surfaces().contains(xid));
  require(xhost.lines().contains(xline_id));

  // Body:
  
  xhost.base_space().new_link(xid, xline_id);
  
  // Postconditions:

  ensure(xhost.base_space().contains_link(xid, xline_id));

  // Exit:

  // cout << "Leaving kd_surface::insert_line." << endl;
  return;
}

void
geometry::kd_surface::
merge(kd_lattice& xhost, id_set& xsurfaces)
{
  // cout << endl << "Entering kd_surface::merge." << endl;
  // cout << "surfaces: " << xsurfaces << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(!xsurfaces.empty());
  require_for_range(id_set::iterator i = xsurfaces.begin(), i != xsurfaces.end(), ++i, xhost.surfaces().is_active(*i));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();
  scoped_index lcvr_id(lbase.member_id(false));

  id_set::iterator lsurf_itr = xsurfaces.begin();
  
  scoped_index ldst_id = *lsurf_itr;
  ++lsurf_itr;
  while(lsurf_itr != xsurfaces.end())
  {
    index_space_iterator& lcvr_itr = lbase.get_cover_id_space_iterator(LOWER, *lsurf_itr);
    while(!lcvr_itr.is_done())
    {
      lcvr_id = lcvr_itr.hub_pod();

      lbase.insert_cover_member(lcvr_id, LOWER, ldst_id);
      lbase.replace_cover_member(*lsurf_itr, ldst_id, UPPER, lcvr_id);
      lcvr_itr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(lcvr_itr);

    lbase.clear_cover(LOWER, lsurf_itr->index());
    lbase.delete_link(xhost.active_part().index(), lsurf_itr->index());
    deactivate(xhost, lsurf_itr->index());

    xhost.deleted_surfaces().insert(*lsurf_itr);

    ++lsurf_itr;
  }

  xhost.modified_surfaces().insert(ldst_id);
  
  // Postconditions:

  ensure(xhost.surfaces().is_active(*xsurfaces.begin()));
  ensure_for_range(id_set::iterator i = ++xsurfaces.begin(), i != xsurfaces.end(), ++i, !xhost.surfaces().is_active(*i));
  ensure(unexecutable("contents of all other surfaces merged into xsurfaces.begin()"));

  // Exit:

  // cout << "Leaving kd_surface::merge." << endl;
  return;
}


void
geometry::kd_surface::
clear(pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_surface::clear." << endl;

  // Preconditions:

  require(precondition_of(clear(host(), id(), xdeleted)));
  
  // Body:

  clear(*_host, _id, xdeleted);

  // Postconditions:

  ensure(postcondition_of(clear(host(), id(), xdeleted)));

  // Exit:

  // cout << "Leaving kd_surface::clear." << endl;
  return;
}

void
geometry::kd_surface::
clear(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_surface::clear." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.surfaces().contains(xid));
  require(!is_empty(xhost, xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();

  not_implemented();
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(lbase.member_id(false));
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
  
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, xid));
  ensure(xhost.base_space().cover_is_empty(LOWER, xid));

  // Exit:

  // cout << "Leaving kd_surface::clear." << endl;
  return;
}

void
geometry::kd_surface::
deactivate()
{
  // cout << endl << "Entering kd_surface::deactivate." << endl;

  // Preconditions:

  require(precondition_of(deactivate(host(), id())));

  // Body:

  deactivate(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(deactivate(host(), id())));

  // Exit:

  // cout << "Leaving kd_surface::deactivate." << endl;
  return;
}

void
geometry::kd_surface::
deactivate(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_surface::deactivate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.surfaces().contains(xid));
  require(xhost.base_space().cover_is_empty(UPPER, xid));
  require(xhost.base_space().cover_is_empty(LOWER, xid));

  // Body:

  xhost.surfaces().delete_member(xid);
  xhost.new_surfaces().erase(xid);
  xhost.modified_surfaces().erase(xid);
  xhost.deleted_surfaces().insert(xid);

  // cout << "deactivated surface: " << xid << "  " << name(xhost, xid) << endl;
  
  // Postconditions:

  ensure(!xhost.surfaces().is_active(xid));
  ensure(xhost.new_surfaces().find(xid) == xhost.new_surfaces().end());
  ensure(xhost.modified_surfaces().find(xid) == xhost.modified_surfaces().end());
  ensure(xhost.deleted_surfaces().find(xid) != xhost.deleted_surfaces().end());
  
  // Exit:

  // cout << "Leaving kd_surface::deactivate." << endl;
  return;
}


bool
geometry::kd_surface::
is_empty() const
{
  // cout << endl << "Entering kd_surface::is_empty." << endl;

  // Preconditions:

  require(precondition_of(is_empty(host(), id())));

  // Body:

  bool result = is_empty(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_empty(host(), id())));

  // Exit:

  // cout << "Leaving kd_surface::is_empty." << endl;
  return result;
}

bool
geometry::kd_surface::
is_empty(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_surface::is_empty." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  // Body:

  const base_space_poset& lbase = xhost.base_space();

  bool result = lbase.cover_is_empty(LOWER, xid);  

  if(!result)
  {
    // Lower cover contains only lines and triangles.
    result = 
      !xhost.lines().contains(lbase.first_cover_member(LOWER, xid.hub_pod())) &&
      !xhost.triangles().contains(lbase.first_cover_member(LOWER, xid.hub_pod()));
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_surface::is_empty." << endl;
  return result;
}

void
geometry::kd_surface::
decompose(id_list& xnew_surfaces)
{
  // cout << endl << "Entering kd_surface::decompose." << endl;

  // Preconditions:

  require(precondition_of(decompose(host(), id(), xnew_surfaces)));

  // Body:

  decompose(*_host, _id, xnew_surfaces);

  // Postconditions:

  ensure(postcondition_of(decompose(host(), id(), xnew_surfaces)));

  // Exit:

  // cout << "Leaving kd_surface::decompose." << endl;
  return;
}

void
geometry::kd_surface::
decompose(kd_lattice& xhost, const scoped_index& xid, id_list& xnew_surfaces)
{
  // cout << endl << "Entering kd_surface::decompose." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.surfaces().contains(xid));

  define_old_variable(size_type old_xnew_surfaces_size = xnew_surfaces.size());

  // Body:

  base_space_poset& lbase = xhost.base_space();

  // Get the lines currently in the lower cover as a set.

  id_list llines;
  lines(xhost, xid, llines);
  id_set loriginal_lines(llines.begin(), llines.end());

  id_set lconnected_lines;  
  id_set lconnected_component;
  pod_id_set lmoved;  

  bool lfirst_component = true;

  while(!loriginal_lines.empty())
  {
    // cout << "original lines: " << loriginal_lines << endl;
    
    // Get the lines that are connected to the first line;
    // may include lines in other surfaces connected
    // through truncation points.

    lconnected_lines.clear();
    kd_line::connected_lines(xhost, *loriginal_lines.begin(), lconnected_lines);

    // cout << "connected lines: " << lconnected_lines << endl;

    // Get rid of any lines from other surfaces.

    lconnected_component.clear();
    insert_iterator<id_set> lcc_itr(lconnected_component, lconnected_component.end());
    set_intersection(loriginal_lines.begin(), loriginal_lines.end(), lconnected_lines.begin(), lconnected_lines.end(), lcc_itr);
      
    // cout << "connected component: " << lconnected_component << endl;

    if(lfirst_component)
    {
      // Leave the first connected component 
      // in the original surface.

      for(id_set::iterator l = lconnected_component.begin(); l != lconnected_component.end(); ++l)
      {
        loriginal_lines.erase(*l);
      }
      lfirst_component = false;
    }
    else
    {
      // Move the other connected components
      // to surfaces.

      scoped_index lnew_surf_id;
      new_surface(xhost, lnew_surf_id);
      xnew_surfaces.push_back(lnew_surf_id);
      
      for(id_set::iterator l = lconnected_component.begin(); l != lconnected_component.end(); ++l)
      {
        // Insert the line in the new surface;
        // note that the line is still in the 
        // original surface.

        insert_line(xhost, lnew_surf_id, *l);
        lmoved.insert(l->index().pod());
        loriginal_lines.erase(*l);
      }
    }

  } // end while
  

  // Remove the moved lines from the original surface.

  for(pod_id_set::iterator l = lmoved.begin(); l != lmoved.end(); ++l)
  {
    lbase.remove_cover_member(xid, UPPER, *l);
  }

  set_filter lmoved_filter(lmoved);
  lbase.remove_cover_members(lmoved_filter, LOWER, xid);

  // Postconditions:

  ensure(xnew_surfaces.size() >= old_xnew_surfaces_size);
  
  // Exit:

  // cout << "Leaving kd_surface::decompose." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::kd_surface::
kd_surface()
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
geometry::kd_surface::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_surface*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_surface*
geometry::kd_surface::
clone() const
{
  kd_surface* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_surface();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_surface&
geometry::kd_surface::
operator=(const kd_surface& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_surface&
geometry::kd_surface::
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
geometry::kd_surface::
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
operator << (ostream& xos, const kd_surface& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  xos << "line " << xn.host().lines().id_space().pod(xn.id());
  xos << "  top id: " << xn.id();
  xos << "  name: " << xn.name();
  xos << "  type: " << xn.type_name();
  xos << boolalpha;
  xos << "  is_jim: " << xn.is_jim();
  xos << "  is_leaf: " << xn.is_leaf();
  xos << noboolalpha;
  xos << endl;
  
  xos << "\tlower cover:";
  const base_space_poset& lbase = xn.host().base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xn.id());
  scoped_index lid(lbase.member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();
    
    xos << "   " << lbase.member_name(lid);
    litr.next();
  }
  xos << endl;
  lbase.release_cover_id_space_iterator(litr);

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_surface& xn, bool xinclude_shallow)
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
