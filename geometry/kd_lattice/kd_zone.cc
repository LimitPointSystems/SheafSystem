// $RCSfile: kd_zone.cc,v $ $Revision: 1.7 $ $Date: 2013/03/13 00:59:00 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_zone

#include "kd_zone.h"
#include "assert_contract.h"
#include "cohort.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "hash_set_filter.h"
#include "kd_bounding_box.h"
#include "kd_edge.h"
#include "kd_face.h"
#include "kd_lattice.h"
#include "kd_line_fragment.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_segment.h"
#include "kd_triangle.h"
#include "kd_vertex.h"
#include "kd_zone_cohort.h"
#include "sec_e3.h"
#include "subcohort.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

// namespace
// {

  
//}    

// ===========================================================
// KD_ZONE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_zone::
prototype_name()
{
  // cout << endl << "Entering kd_zone::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("kd_zone");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_zone::prototype_name." << endl;
  return result;
}

geometry::kd_zone::
kd_zone(kd_lattice& xhost)
  : kd_member(xhost)
{
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  
  define_old_variable(size_type old_zones_ct = xhost.zones().ct());
  define_old_variable(size_type old_faces_ct = xhost.faces().ct());
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());
    
  // Body:

  _id = new_zone(xhost);

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().base_space().cover_is_empty(UPPER, id()));
  ensure(host().zones().contains(id()));
  ensure(host().zones().ct() == old_zones_ct + 1);
  ensure(host().faces().ct() == old_faces_ct + FACE_CT);
  ensure(host().edges().ct() == old_edges_ct + EDGE_CT);
  ensure(host().vertices().ct() == old_vertices_ct + VERTEX_CT);

  // Exit:

  return; 
}

sheaf::scoped_index
geometry::kd_zone::
new_zone(kd_lattice& xhost)
{
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());

  define_old_variable(size_type old_zones_ct = xhost.zones().ct());
  define_old_variable(size_type old_faces_ct = xhost.faces().ct());
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());
    
  // Body:

  // Create the vertices; linked to bottom by new_vertex().

  scoped_index lzv_ids[VERTEX_CT];
  for(int i=0; i< VERTEX_CT; ++i)
  {
    lzv_ids[i] = kd_vertex::new_vertex(xhost);
  }

  // Create the edges and link them to the vertices;
  // edges always oriented in direction of increasing coordinate.

  static const int ledge_vertex_ids[EDGE_CT][kd_edge::VERTEX_CT] = 
    {
      0, 1, // edge 0
      1, 2, // edge 1
      3, 2, // edge 2
      0, 3, // edge 3
      4, 5, // edge 4
      5, 6, // edge 5
      7, 6, // edge 6
      4, 7, // edge 7
      3, 7, // edge 8
      2, 6, // edge 9
      1, 5, // edge 10
      0, 4  // edge 11
    };
  
  static const kd_alignment ledge_alignment[EDGE_CT] =
    {
      X_AXIS_ALIGNED, // edge 0
      Y_AXIS_ALIGNED, // edge 1
      X_AXIS_ALIGNED, // edge 2
      Y_AXIS_ALIGNED, // edge 3
      X_AXIS_ALIGNED, // edge 4
      Y_AXIS_ALIGNED, // edge 5
      X_AXIS_ALIGNED, // edge 6
      Y_AXIS_ALIGNED, // edge 7
      Z_AXIS_ALIGNED, // edge 8
      Z_AXIS_ALIGNED, // edge 9
      Z_AXIS_ALIGNED, // edge 10
      Z_AXIS_ALIGNED  // edge 11
    };

  scoped_index lev_ids[kd_edge::VERTEX_CT];
  scoped_index lze_ids[EDGE_CT];
  for(int i=0; i< EDGE_CT; ++i)
  {
    for(int j= 0; j<kd_edge::VERTEX_CT; ++j)
    {
      lev_ids[j] = lzv_ids[ledge_vertex_ids[i][j]];
    }

    lze_ids[i] = kd_edge::new_edge(xhost, lev_ids, ledge_alignment[i]);
  }

  // Create the faces and link them to the edges.
  // Faces 0, 1 are z-aligned with z(0) < z(1).
  // Faces 2, 3 are x-aligned with x(2) < x(3).
  // Faces 4, 5 are y-aligned with y(4) < y(5).

  /// @issue Our chioce for orientation of the x aligned faces
  /// is left-handed while the other faces are right-handed.
  /// We should change the x aligned faces to right-handed
  /// to be consistent. See also kd_face::clip_line. 

  int lface_edge_ids[FACE_CT][kd_face::EDGE_CT] = 
    {
      0, 1, 2, 3,   // face 0
      4, 5, 6, 7,   // face 1
      11, 7, 8, 3,  // face 2
      10, 5, 9, 1,  // face 3
      0, 10, 4, 11, // face 4
      2, 9, 6, 8    // face 5
    };

  static const kd_alignment lface_alignment[FACE_CT] =
    {
      Z_AXIS_ALIGNED, // face 0
      Z_AXIS_ALIGNED, // face 1
      X_AXIS_ALIGNED, // face 2
      X_AXIS_ALIGNED, // face 3
      Y_AXIS_ALIGNED, // face 4
      Y_AXIS_ALIGNED  // face 5
    };
  

  scoped_index lfe_ids[kd_face::EDGE_CT];
  scoped_index lzf_ids[FACE_CT];

  for(int i=0; i< FACE_CT; ++i)
  {
    for(int j= 0; j<kd_face::EDGE_CT; ++j)
    {
      lfe_ids[j] = lze_ids[lface_edge_ids[i][j]];
    }

    lzf_ids[i] = kd_face::new_face(xhost, lfe_ids, lface_alignment[i]);
  }

  // Create the zone.

  scoped_index result = xhost.zones().new_member();

  // The zone covers the faces.

  for(int i=0; i<FACE_CT; ++i)
  {  
    xhost.base_space().new_link(result, lzf_ids[i]);
  }
  

  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, result));
  ensure(xhost.zones().contains(result));
  ensure(xhost.zones().ct() == old_zones_ct + 1);
  ensure(xhost.faces().ct() == old_faces_ct + FACE_CT);
  ensure(xhost.edges().ct() == old_edges_ct + EDGE_CT);
  ensure(xhost.vertices().ct() == old_vertices_ct + VERTEX_CT);

  // Exit:

  return result; 
}

geometry::kd_zone::
kd_zone(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub)
  : kd_member(xhost)
{
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(is_axis_aligned(xlb, xub));
  
  define_old_variable(size_type old_zones_ct = xhost.zones().ct());
  define_old_variable(size_type old_faces_ct = xhost.faces().ct());
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  // Body:

  _id = new_zone(xhost, xlb, xub);
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().base_space().cover_is_empty(UPPER, id()));
  ensure(host().zones().contains(id()));
  ensure(host().zones().ct() == old_zones_ct + 1);
  ensure(xhost.faces().ct() == old_faces_ct + FACE_CT);
  ensure(xhost.edges().ct() == old_edges_ct + EDGE_CT);
  ensure(xhost.vertices().ct() == old_vertices_ct + VERTEX_CT);
  ensure(coord_lower_bound() == xlb);
  ensure(coord_upper_bound() == xub);

  // Exit:

  return; 
}

sheaf::scoped_index
geometry::kd_zone::
new_zone(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_zone::new_zone." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(is_axis_aligned(xlb, xub));

  define_old_variable(size_type old_zones_ct = xhost.zones().ct());
  define_old_variable(size_type old_faces_ct = xhost.faces().ct());
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  // Body:

  scoped_index result = new_zone(xhost);
  put_coord_bounds(xhost, result, xlb, xub);  

  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, result));
  ensure(xhost.zones().contains(result));
  ensure(xhost.zones().ct() == old_zones_ct + 1);
  ensure(xhost.faces().ct() == old_faces_ct + FACE_CT);
  ensure(xhost.edges().ct() == old_edges_ct + EDGE_CT);
  ensure(xhost.vertices().ct() == old_vertices_ct + VERTEX_CT);
  ensure(coord_lower_bound(xhost, result) == xlb);
  ensure(coord_upper_bound(xhost, result) == xub);

  // Exit:

  // cout << "Leaving kd_zone::new_zone." << endl;
  return result;
}


geometry::kd_zone::
kd_zone(kd_lattice& xhost, const scoped_index& xid)
  : kd_member(xhost, xid)
{
  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_zone::
kd_zone(const kd_zone& xother)
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

geometry::kd_zone::
~kd_zone()
{
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_zone::
subzones(scoped_index xresult[]) const
{
  // Preconditions:

  require(unexecutable("xresult is an array with at least SUBZONE_CT entries"));
  require(host().base_space().state_is_read_accessible());
  require(!host().leaves().contains(id()));
  
  // Body:

  subzones(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, SUBZONE_CT, host().zones().contains(xresult[i]));

  // Exit:

  return;
}

void
geometry::kd_zone::
subzones(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_zone::subzones(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least SUBZONE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  require(!xhost.leaves().contains(xid));
  
  // Body:

  const kd_zone_cohort& lzones = xhost.zones();

  int lsz = 0;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done() && (lsz < SUBZONE_CT))
  {
    lid = litr.hub_pod();

    if(lzones.contains(lid))
    {
      xresult[lsz++] = lid;
    }    
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure_for_all(i, 0, SUBZONE_CT, xhost.zones().contains(xresult[i]));
  
  // Exit:

  // cout << "Leaving kd_zone::subzones(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_zone::
subzone(int xi) const
{
  // cout << endl << "Entering kd_zone::subzone(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < SUBZONE_CT));

  // Body:

  scoped_index result = subzone(*_host, _id, xi);

  // Postconditions:

  ensure(host().zones().contains(result));

  // Exit:

  // cout << "Leaving kd_zone::subzone(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_zone::
subzone(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_zone::subzone(const kd_lattice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  require((0 <= xi) && (xi < SUBZONE_CT));

  // Body:

  const kd_zone_cohort& lzones = xhost.zones();

  int lsz = 0;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(lzones.contains(lid))
    {
      if(lsz == xi)
      {
        break;
      }
      else
      {
        lsz++;
      }
    } 
    litr.next();
  }

  scoped_index result = xhost.base_space().member_id(litr.hub_pod(), false);
  
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xhost.zones().contains(result));
  
  // Exit:

  // cout << "Leaving kd_zone::subzone(const kd_lattice&, const scoped_index&, int)." << endl;
  return result;
}

void
geometry::kd_zone::
faces(scoped_index xresult[]) const
{
  // Preconditions:

  require(unexecutable("xresult is an array with at least FACE_CT entries"));
  require(host().base_space().state_is_read_accessible());
  
  // Body:

  faces(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, FACE_CT, host().faces().contains(xresult[i]));

  // Exit:

  return;
}

void
geometry::kd_zone::
faces(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_zone::faces(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least FACE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  const cohort& lfaces = xhost.faces();

  scoped_index lid = lbase.member_id(false);
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  for(int i=0; i<FACE_CT; ++i)
  {
    lid = litr.hub_pod();
    while(!lfaces.contains(lid))
    {
      index_space_iterator& lc_itr = lbase.get_cover_id_space_iterator(LOWER, lid);
      for(int j=0; j<i; ++j)
      {
        lc_itr.next();
      }
      lid = lc_itr.hub_pod();
      lbase.release_cover_id_space_iterator(lc_itr);
    }
    xresult[i] = lid;
    
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure_for_all(i, 0, FACE_CT, xhost.faces().contains(xresult[i]));
  
  // Exit:

  // cout << "Leaving kd_zone::faces(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_zone::
face(int xi) const
{
  // cout << endl << "Entering kd_zone::face(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < FACE_CT));

  // Body:

  scoped_index result = face(*_host, _id, xi);

  // Postconditions:

  ensure(host().faces().contains(result));

  // Exit:

  // cout << "Leaving kd_zone::face(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_zone::
face(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_zone::face(const kd_lattice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  require((0 <= xi) && (xi < FACE_CT));

  // Body:

  const base_space_poset& lbase = xhost.base_space();
  const cohort& lfaces = xhost.faces();

  scoped_index result = xid;
  while(!lfaces.contains(result))
  {
    index_space_iterator& lc_itr = lbase.get_cover_id_space_iterator(LOWER, result);
    for(int i=0; i<xi; ++i)
    {
      lc_itr.next();
    }
    result = lc_itr.hub_pod();
    lbase.release_cover_id_space_iterator(lc_itr);
  }

  // Postconditions:

  ensure(xhost.faces().contains(result));
  
  // Exit:

  // cout << "Leaving kd_zone::face(const kd_lattice&, const scoped_index&, int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_zone::
splitting_face() const
{
  // cout << endl << "Entering kd_zone::splitting_face()." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());

  // Body:

  scoped_index result = splitting_face(*_host, _id);

  // Postconditions:

  ensure(host().faces().contains(result));

  // Exit:

  // cout << "Leaving kd_zone::splitting_face(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_zone::
splitting_face(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone::splitting_face(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));

  // Body:

  scoped_index result = subzone(xhost, xid, 0);

  switch(xhost.plane(xid).alignment())
  {
    case X_AXIS_ALIGNED:
      result = face(xhost, result, 3);
      break;
    case Y_AXIS_ALIGNED:
      result = face(xhost, result, 5);
      break;
    case Z_AXIS_ALIGNED:
      result = face(xhost, result, 1);
      break;
    default:
      post_fatal_error_message("Unrecognized alignment.");
  }
      

  // Postconditions:

  ensure(xhost.faces().contains(result));
  
  // Exit:

  // cout << "Leaving kd_zone::splitting_face(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

void
geometry::kd_zone::
edges(scoped_index xresult[]) const
{
  // cout << endl << "Entering kd_zone::edges(scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least FACE_CT entries"));
  require(host().base_space().state_is_read_accessible());
  
  // Body:

  edges(*_host, _id, xresult);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::edges(scoped_index[])." << endl;
  return;
}

void
geometry::kd_zone::
edges(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_zone::edges(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least EDGE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  
  // Body:

  // Get the faces.

  scoped_index lface_ids[FACE_CT];
  faces(xhost, xid, lface_ids);

  // First face contains edges 0 through 3

  scoped_index* lresult = xresult;
  kd_face::edges(xhost, lface_ids[0], lresult);

  // Second face contains faces 4 through 7.  

  lresult += 4;
  kd_face::edges(xhost, lface_ids[1], lresult);

  // Third face contains edges 11, 7, 8, 3 (in that order).
  
  scoped_index lface_edges[kd_face::EDGE_CT];
  kd_face::edges(xhost, lface_ids[2], lface_edges);

  xresult[8]  = lface_edges[2];
  xresult[11] = lface_edges[0];

  // Fourth face contains edges 10, 5, 9, 1 (in that order).
  
  kd_face::edges(xhost, lface_ids[3], lface_edges);

  xresult[9]  = lface_edges[2];
  xresult[10] = lface_edges[0];
  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::edges(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_zone::
edge(int xi) const
{
  // cout << endl << "Entering kd_zone::edge(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < EDGE_CT));

  // Body:

  scoped_index result = edge(*_host, _id, xi);

  // Postconditions:

  ensure(host().edges().contains(result));

  // Exit:

  // cout << "Leaving kd_zone::edge(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_zone::
edge(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_zone::edge(const kd_lattice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  require((0 <= xi) && (xi < EDGE_CT));

  // Body:

  static const int lface_ids[EDGE_CT] = 
    {
      0, 0, 0, 0, 1, 1, 1, 1, 2, 3, 3, 2
    };
  
  static const int llocal_edge_ids[EDGE_CT] = 
    {
      0, 1, 2, 3, 0, 1, 2, 3, 2, 2, 0, 0
    };

  scoped_index lface_id(face(xhost, xid, lface_ids[xi]));
  scoped_index result = kd_face::edge(xhost, lface_id, llocal_edge_ids[xi]);

  // Postconditions:

  ensure(xhost.edges().contains(result));
  
  // Exit:

  // cout << "Leaving kd_zone::edge(const kd_lattice&, const scoped_index&, int)." << endl;
  return result;
}

void
geometry::kd_zone::
vertices(scoped_index xresult[]) const
{
  // cout << endl << "Entering kd_zone::vertices(scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(host().base_space().state_is_read_accessible());
  
  // Body:

  vertices(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, host().vertices().contains(xresult[i]));

  // Exit:

  // cout << "Leaving kd_zone::vertices(scoped_index[])." << endl;
  return;
}

void
geometry::kd_zone::
vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_zone::vertices(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  
  // The vertices of the zone are the vertices of face 0
  // followed by the vertices of face 1, in that order.

  scoped_index lf_id = face(xhost, xid, 0);
  scoped_index* lresult = xresult;
  kd_face::vertices(xhost, lf_id, lresult);
  
  lf_id = face(xhost, xid, 1);
  lresult += kd_face::VERTEX_CT;
  kd_face::vertices(xhost, lf_id, lresult);

  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, xhost.vertices().contains(xresult[i]));  

  // Exit:

  // cout << "Leaving kd_zone::vertices(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_zone::
vertex(int xi) const
{
  // cout << endl << "Entering kd_zone::vertex(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < VERTEX_CT));

  // Body:

  scoped_index result = vertex(*_host, _id, xi);

  // Postconditions:

  ensure(host().vertices().contains(result));

  // Exit:

  // cout << "Leaving kd_zone::vertex(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_zone::
vertex(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_zone::vertex(kd_lsttice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  require((0 <= xi) && (xi < VERTEX_CT));

  // Body:


  scoped_index lf_id;
  scoped_index result;
  
  if(xi < 4)
  {
    lf_id = face(xhost, xid, 0);
    result = kd_face::vertex(xhost, lf_id, xi);
  }
  else
  {
    lf_id = face(xhost, xid, 1);
    result = kd_face::vertex(xhost, lf_id, xi-4);
  }

  // Postconditions:

  ensure(xhost.vertices().contains(result));
  
  // Exit:

  // cout << "Leaving kd_zone::vertex(kd_lsttice&, const scoped_index&, int)." << endl;
  return result;
}

bool
geometry::kd_zone::
is_axis_aligned(const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_zone::is_axis_aligned." << endl;

  // Preconditions:


  // Body:

  bool result = !( (xlb[0] == xub[0]) ||(xlb[1] == xub[1]) ||(xlb[2] == xub[2]) );


  // Postconditions:

  ensure(result == !( (xlb[0] == xub[0]) ||(xlb[1] == xub[1]) ||(xlb[2] == xub[2]) ));

  // Exit:

  // cout << "Leaving kd_zone::is_axis_aligned." << endl;
  return result;
}

void
geometry::kd_zone::
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
geometry::kd_zone::
coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());
  require(xhost.zones().contains(xid));

  // Body:

  // Get the vertex ids.

  scoped_index lv_ids[VERTEX_CT];
  vertices(xhost, xid, lv_ids);

  // Need to use two vertices on a diagonal; 0 and 6 will do.

  coord_bounds(xhost, lv_ids[0], lv_ids[6], xlb, xub);
  
  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::e3_lite
geometry::kd_zone::
coord_lower_bound() const
{
  // cout << endl << "Entering kd_zone::coord_lower_bound." << endl;

  // Preconditions:


  // Body:

  e3_lite result = coord_lower_bound(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::coord_lower_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_zone::
coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite result, lub;
  coord_bounds(xhost, xid, result, lub);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_zone::
coord_upper_bound() const
{
  // cout << endl << "Entering kd_zone::coord_upper_bound." << endl;

  // Preconditions:


  // Body:

  e3_lite result = coord_upper_bound(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::coord_upper_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_zone::
coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite llb, result;
  coord_bounds(xhost, xid, llb, result);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

void
geometry::kd_zone::
put_coord_bounds(const e3_lite& xlb, const e3_lite& xub)
{
  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().coords().state_is_read_write_accessible());
  require(is_axis_aligned(xlb, xub));
  
  // Body:

  put_coord_bounds(*_host, _id, xlb, xub);
  
  // Postconditions:

  ensure(coord_lower_bound() == xlb);
  ensure(coord_upper_bound() == xub);

  // Exit:

  return;
}

void
geometry::kd_zone::
put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.zones().contains(xid));
  require(is_axis_aligned(xlb, xub));
  
  // Body:

  // Get the vertex ids.

  scoped_index lv_ids[VERTEX_CT];
  vertices(xhost, xid, lv_ids);  

  //   cout << "vertices: ";
  //   for(int i=0; i<VERTEX_CT; ++i)
  //   {
  //     cout << setw(6) << lv_ids[i].hub_pod();
  //   }
  //   cout << endl;
  

  // Set the coordinates for the vertices.

  sec_e3& lcoords = xhost.coords();
  
  e3_lite lfiber;
  
  // xmin, ymin, zmin; vertex 0.

  lfiber[0] = xlb[0];
  lfiber[1] = xlb[1];
  lfiber[2] = xlb[2];
  lcoords.put_fiber(lv_ids[0], lfiber, false);

  // xmax, ymin, zmin; vertex 1:

  lfiber[0] = xub[0];
  lfiber[1] = xlb[1];
  lfiber[2] = xlb[2];
  lcoords.put_fiber(lv_ids[1], lfiber, false);

  // xmax, ymax, zmin; vertex 2.

  lfiber[0] = xub[0];
  lfiber[1] = xub[1];
  lfiber[2] = xlb[2];
  lcoords.put_fiber(lv_ids[2], lfiber, false);

  // xmin, ymax, zmin; vertex 3.

  lfiber[0] = xlb[0];
  lfiber[1] = xub[1];
  lfiber[2] = xlb[2];
  lcoords.put_fiber(lv_ids[3], lfiber, false);

  // xmin, ymin, zmax; vertex 4.

  lfiber[0] = xlb[0];
  lfiber[1] = xlb[1];
  lfiber[2] = xub[2];
  lcoords.put_fiber(lv_ids[4], lfiber, false);

  // xmax, ymin, zmax; vertex 5:

  lfiber[0] = xub[0];
  lfiber[1] = xlb[1];
  lfiber[2] = xub[2];
  lcoords.put_fiber(lv_ids[5], lfiber, false);

  // xmax, ymax, zmax; vertex 6.

  lfiber[0] = xub[0];
  lfiber[1] = xub[1];
  lfiber[2] = xub[2];
  lcoords.put_fiber(lv_ids[6], lfiber, false);

  // xmin, ymax, zmax; vertex 7.

  lfiber[0] = xlb[0];
  lfiber[1] = xub[1];
  lfiber[2] = xub[2];
  lcoords.put_fiber(lv_ids[7], lfiber, false);

  // Postconditions:

  ensure(coord_lower_bound(xhost, xid) == xlb);
  ensure(coord_upper_bound(xhost, xid) == xub);

  // Exit:

  return;
}

fiber_bundle::e3_lite
geometry::kd_zone::
center() const
{
  // cout << endl << "Entering kd_zone::center." << endl;

  // Preconditions:


  // Body:

  e3_lite result = center(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::center." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_zone::
center(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone::center(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite llb, result;
  coord_bounds(xhost, xid, llb, result);
  
  result += llb;
  multiply(result, 0.5, result);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::center(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

bool
geometry::kd_zone::
contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_zone::contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::contains_point." << endl;
  return result;
}

bool
geometry::kd_zone::
contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_zone::contains_point." << endl;

  // Preconditions:

  require(xhost.zones().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  bool result = xhost.bounding_box(xid).contains_point(xpt);
  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::contains_point." << endl;
  return result;
}

bool
geometry::kd_zone::
interior_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_zone::interior_contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = interior_contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_zone::
interior_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_zone::interior_contains_point." << endl;

  // Preconditions:

  require(xhost.zones().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  bool result = xhost.bounding_box(xid).interior_contains_point(xpt);

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_zone::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_zone::
boundary_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_zone::boundary_contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = boundary_contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::boundary_contains_point." << endl;
  return result;
}

bool
geometry::kd_zone::
boundary_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_zone::boundary_contains_point." << endl;

  // Preconditions:

  require(xhost.zones().contains(xid));

  // Body:

  bool result = xhost.bounding_box(xid).boundary_contains_point(xpt);

  // Postconditions:

  ensure(result == xhost.bounding_box(xid).boundary_contains_point(xpt));

  // Exit:

  // cout << "Leaving kd_zone::boundary_contains_point." << endl;
  return result;
}

scoped_index
geometry::kd_zone::
locate_point(const e3_lite& xpt, int xd) const
{
  // cout << endl << "Entering kd_zone::locate_point." << endl;

  // Preconditions:

  require(precondition_of(locate_point(host(), id(), xpt, xd)));

  // Body:

  scoped_index result = locate_point(*_host, _id, xpt, xd);

  // Postconditions:

  ensure(postcondition_of(locate_point(host(), id(), xpt, xd)));

  // Exit:

  // cout << "Leaving kd_zone::locate_point." << endl;
  return result;
}

scoped_index
geometry::kd_zone::
locate_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt, int xd)
{
  // cout << endl << "Entering kd_zone::locate_point." << endl;

  // Preconditions:

  require(xhost.zones().contains(xid));
  require(interior_contains_point(xhost, xid, xpt));

  // Body:

  scoped_index result(xid);

  while(!xhost.leaves().contains(result))
  {      
    // xpt is not on the boundary of the zone,
    // so it must either in the splitting face or 
    // in one of the subzones.

    const kd_plane& lp = xhost.plane(result);
    int lalignment = lp.int_alignment();
    double lp_dist = lp.distance();
    double lpt_dist = xpt[lalignment];
    
    if((xd < DB) && (lpt_dist == lp_dist))
    {
      // Point is located on the face between the subzones.

      result = kd_zone::splitting_face(xhost, result);
      result = kd_face::locate_point(xhost, result, xpt, xd);
    }
    else if( lpt_dist < lp_dist)
    {
      // Point is located in back side subzone.

      result = kd_zone::subzone(xhost, result, 0);
    }
    else
    {
      // Point is located in front side subzone.

      result = kd_zone::subzone(xhost, result, 1);
    }
  }
  
  // Postconditions:

  ensure(xhost.leaves().contains(result));
  ensure(xhost.cell_contains_point(result, xpt));

  // Exit:

  // cout << "Leaving kd_zone::locate_point." << endl;
  return result;
}

void
geometry::kd_zone::
find_face_leaf(const kd_plane& xp, const pt_list& xline, scoped_index& xresult) const
{
  // cout << endl << "Entering kd_zone::find_face_leaf." << endl;

  // Preconditions:

  require(precondition_of(find_face_leaf(host(), id(), xp, xline, xresult)));
  
  // Body:

  find_face_leaf(host(), id(), xp, xline, xresult);
  
  // Postconditions:

  ensure(postcondition_of(find_face_leaf(host(), id(), xp, xline, xresult)));

  // Exit:

  // cout << "Leaving kd_zone::find_face_leaf." << endl;
  return;
}

void
geometry::kd_zone::
find_face_leaf(const kd_lattice& xhost, 
               const scoped_index& xid, 
               const kd_plane& xp, 
               const pt_list& xline, 
               scoped_index& xresult)
{
  // cout << endl << "Entering kd_zone::find_face_leaf." << endl;
  // cout << "First point: " << xline.front() << "  second point: " << (*(++xline.begin())) << endl;
  // cout << "bounding box: " << xhost.bounding_box(xid) << endl;

  // Preconditions:

  require(xhost.zones().contains(xid));
  require(interior_contains_point(xhost, xid, xline.front()));
  // require(xline.front()[xp.alignment()] == xp.distance());
  require(xp.contains_line(xline));
  require(!xline.empty());
  require(++xline.begin() != xline.end()); // At least 2 points.
  
  // Body:

  xresult = xid;
  
  int lxp_alignment = xp.alignment();
  vd_value_type lxp_dist = xp.distance();

  while(!xhost.leaves().contains(xresult))
  {      
    // xpt0 is not on the boundary of the zone,
    // so it must either in the splitting face or 
    // in one of the subzones.

    const kd_plane& lp = xhost.plane(xresult);
    double lp_dist = lp.distance();
    int lp_alignment = lp.int_alignment();
    double lpt_dist = xline.front()[lp_alignment];

    // cout << "inspecting zone: " << xresult << endl;
    // cout << "bounding box: " << xhost.bounding_box(xresult) << endl;
    // cout << "splitting plane:" << lp << endl;
    // cout << "lpt_dist: " << lpt_dist << "  lp_dist: " << lp_dist << endl;
    
    if(lpt_dist < lp_dist)
    {
      // Point is located in back side subzone.

      // cout << "Point is located in back side subzone." << endl;

      xresult = kd_zone::subzone(xhost, xresult, 0);
    }
    else if(lpt_dist > lp_dist)
    {
      // Point is located in front side subzone.

      // cout << "Point is located in front side subzone." << endl;

      xresult = kd_zone::subzone(xhost, xresult, 1);
    }
    else
    {
      // Point is located on the face between the subzones.

      assertion(lpt_dist == lp_dist);

      // cout << "Point is located on the face between the subzones" << endl;

      if(lp_alignment == lxp_alignment)
      {
        // Line is (partially) contained in splitting face

        // cout << "Line is (partially) contained in splitting face" << endl;
        
        assertion(lpt_dist == lxp_dist);

        xresult = kd_zone::splitting_face(xhost, xresult);
        kd_face::leaf(xhost, xresult, xline, xresult);
      }
      else
      {
        // Line crosses splitting plane.

        // cout << "Line crosses splitting plane, look at second point." << endl;

        pt_list::const_iterator lpt1 = ++xline.begin();
        lpt_dist = (*lpt1)[lp_alignment];
        
        if(lpt_dist < lp_dist)
        {
          // Point is located in back side subzone.

          // cout << "Second point is located in back side subzone." << endl;

          xresult = kd_zone::subzone(xhost, xresult, 0);
        }
        else if(lpt_dist > lp_dist)
        {
          // Second point is located in front side subzone.

          // cout << "Point is located in front side subzone." << endl;

          xresult = kd_zone::subzone(xhost, xresult, 1);
        }
        else
        {
          // Second point is located on the face between the subzones.

          assertion(lpt_dist == lp_dist);

          // cout << "Second point is located on the face between the subzones" << endl;

          // Doesn't matter which subzone we take; 
          // line insertion algorithm will work either way.
          // Take the front subzone.

          xresult = kd_zone::subzone(xhost, xresult, 1);
        }
      }
    }
  }
  
  // cout << "result: " << xresult << "  " << name(xhost, xresult) << endl;
  // cout << "bounding box: " << xhost.bounding_box(xresult) << endl;

  // Postconditions:

  ensure(xhost.leaves().contains(xresult));
  ensure(xhost.cell_contains_point(xresult, xline.front()));

  // Exit:

  // cout << "Leaving kd_zone::find_face_leaf." << endl;
  return;
}

void
geometry::kd_zone::
find_face_leaves(const kd_plane& xp, id_list& xresult) const
{
  // cout << endl << "Entering kd_zone::find_face_leaves." << endl;

  // Preconditions:

  require(precondition_of(find_face_leaves(host(), id(), xp, xresult)));
  
  // Body:

  find_face_leaves(host(), id(), xp, xresult);
  
  // Postconditions:

  ensure(postcondition_of(find_face_leaves(host(), id(), xp, xresult)));

  // Exit:

  // cout << "Leaving kd_zone::find_face_leaves." << endl;
  return;
}

void
geometry::kd_zone::
find_face_leaves(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, id_list& xresult)
{
  // cout << endl << "Entering kd_zone::find_face_leaves." << endl;
  // cout << "bounding box: " << xhost.bounding_box(xid) << endl;

  // Preconditions:

  require(xhost.zones().contains(xid));
  require(xhost.contains_plane(xp));
  
  // Body:

  int lxp_alignment = xp.alignment();
  vd_value_type lxp_dist = xp.distance();

  if(xhost.leaves().contains(xid))
  {
    // Didn't find a face leaf; do nothing.
  }
  else
  {
    // This zone is not a leaf.
    // Get the splitting plane.

    const kd_plane& lp = xhost.plane(xid);
    
    // Get the subzones.

    scoped_index lsubzone_ids[2];
    kd_zone::subzones(xhost, xid, lsubzone_ids);

    // Look in the appropriate subzones.

    if(lp.alignment() == xp.alignment())
    {
      // The plane is parallel to the splitting plane.

      if(xp.distance() < lp.distance())
      {
        // The plane lies on the back side of the splitting plane;
        // find it in the subzone in back of the splitting plane.

        find_face_leaves(xhost, lsubzone_ids[0], xp, xresult);
      }
      else if(xp.distance() > lp.distance())
      {
        // The plane lies on the front side of the splitting plane;
        // find it in the subzone in front of the splitting plane.

        find_face_leaves(xhost, lsubzone_ids[1], xp, xresult);
      }
      else
      {
        // The plane is the splitting plane;
        // find the leaves in the spltting face

        kd_face::leaves(xhost, splitting_face(xhost, xid), xresult);
      }
    }    
    else
    {
      // The plane crosses the splitting plane;
      // find the plane in both subzones.

      find_face_leaves(xhost, lsubzone_ids[0], xp, xresult);
      find_face_leaves(xhost, lsubzone_ids[1], xp, xresult);
    }
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::find_face_leaves." << endl;
  return;
}

bool
geometry::kd_zone::
in_bounds(const kd_plane& xp) const
{
  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().coords().state_is_read_accessible());

  // Body:

  bool result = in_bounds(*_host, _id, xp);

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::kd_zone::
in_bounds(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());
  require(xhost.zones().contains(xid));

  // Body:


  e3_lite llb, lub;
  coord_bounds(xhost, xid, llb, lub);
  
  int i = xp.alignment();
  bool result = (llb[i] < xp.distance()) && (xp.distance() < lub[i]);

  // Postconditions:


  // Exit:

  return result;
}


void
geometry::kd_zone::
refine(const kd_plane& xp, scoped_index xnew_ids[])
{
  // Preconditions:

  require(host().base_space().in_jim_edit_mode());
  require(host().coords().state_is_read_write_accessible());
  require(in_bounds(xp));
  
  // Body:

  refine(*_host, _id, xp, xnew_ids);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_zone::
refine(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[])
{
  // cout << endl << "Entering kd_zone::refine." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(in_bounds(xhost, xid, xp));
  require(xhost.zones().contains(xid));

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));  
  
  // Body:

  // Set the splitting plane.

  xhost.put_plane(xid, xp);

  // Refine the zone.

  switch(xp.alignment())
  {
    case X_AXIS_ALIGNED:
      refine_x_axis_aligned(xhost, xid, xp, xnew_ids);
      break;
    case Y_AXIS_ALIGNED:
      refine_y_axis_aligned(xhost, xid, xp, xnew_ids);
      break;
    case Z_AXIS_ALIGNED:
      refine_z_axis_aligned(xhost, xid, xp, xnew_ids);
      break;
    default:
      post_fatal_error_message("Unrecognized plane alignment.");
      break;
  }

  // Updated the cleared zones set.

  pod_id_hash_set& lcleared_zones = xhost.cleared_zones();
  pod_id_hash_set::iterator z;

  if((z = lcleared_zones.find(xid.hub_pod())) != lcleared_zones.end())
  {
    lcleared_zones.erase(z);
    lcleared_zones.insert(xnew_ids[0].hub_pod());
    lcleared_zones.insert(xnew_ids[1].hub_pod());
  }  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::refine." << endl;
  return;
}

void
geometry::kd_zone::
insert_plane(const kd_plane& xp)
{
  // cout << endl << "Entering kd_zone::insert_plane." << endl;

  // Preconditions:

  require(xp.is_valid());
  require((!host().contains_equivalent_plane(xp)));
  
  // Body:

  insert_plane(*_host, _id, xp);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::insert_plane." << endl;
  return;
}

void
geometry::kd_zone::
insert_plane(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp)
{
  // cout << endl << "Entering kd_zone::insert_plane." << endl;

  // Preconditions:

  require(xp.is_valid());
  require((!xhost.contains_equivalent_plane(xp)));

  // Body:

  if(xhost.leaves().contains(xid))
  {
      // The new plane splits the zone; refine the zone.

      scoped_index lnew_ids[3];
      refine(xhost, xid, xp, lnew_ids);
  }
  else
  {
    // This zone is not a leaf.
    // Get the splitting plane.

    const kd_plane& lp = xhost.plane(xid);
    
    // Get the subzones.

    scoped_index lsubzone_ids[2];
    kd_zone::subzones(xhost, xid, lsubzone_ids);

    // Insert the plane in the appropraite subzones.

    if(lp.alignment() == xp.alignment())
    {
      // The new plane is parallel to the splitting plane.

      if(xp.distance() < lp.distance())
      {
        // The new plane lies on the back side of the splitting plane;
        // insert it in the subzone in back of the splitting plane.

        insert_plane(xhost, lsubzone_ids[0], xp);
      }
      else
      {
        // The new plane lies on the front side of the splitting plane;
        // insert it in the subzone in front of the splitting plane.

        insert_plane(xhost, lsubzone_ids[1], xp);
      }      
    }    
    else
    {
      // The plane crosses the splitting plane;
      // insert the plane in both subzones.

      insert_plane(xhost, lsubzone_ids[0], xp);
      insert_plane(xhost, lsubzone_ids[1], xp);
    }
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::insert_plane." << endl;
  return;
}

void
geometry::kd_zone::
line_fragments(frag_list& xfrags) const
{
  // cout << endl << "Entering kd_zone::line_fragments." << endl;

  // Preconditions:

  require(precondition_of(line_fragments(host(), id(), xfrags)));

  // Body:

  line_fragments(*_host, _id, xfrags);

  // Postconditions:

  ensure(postcondition_of(line_fragments(host(), id(), xfrags)));

  // Exit:

  // cout << "Leaving kd_zone::line_fragments." << endl;
  return;
}

void
geometry::kd_zone::
line_fragments(const kd_lattice& xhost, const scoped_index& xid, frag_list& xfrags)
{
  // cout << endl << "Entering kd_zone::line_fragments." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  // Body:

  scoped_index lf_ids[FACE_CT];
  faces(xhost, xid, lf_ids);
  
  for(int i=0; i<FACE_CT; ++i)
  {
    kd_face::line_fragments(xhost, lf_ids[i], xfrags);
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::line_fragments." << endl;
  return;
}

void
geometry::kd_zone::
triangulate() const
{
  // cout << endl << "Entering kd_zone::triangulate." << endl;

  // Preconditions:

  require(precondition_of(triangulate(host(), id())));
  
  // Body:

  triangulate(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(triangulate(host(), id())));

  // Exit:

  // cout << "Leaving kd_zone::triangulate." << endl;
  return;
}

void
geometry::kd_zone::
triangulate(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone::triangulate." << endl;
  // cout << "  zone_id: " << xid.hub_pod() << "  name: " << xhost.base_space().member_name(xid, false) << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  // Body:
  
  // Get the faces.

  // Get the line members from the contents of all the faces.

  // $$SCRIBBLE: in triangulate polygons below, we'll need to know what 
  // surfaces contain the points extracted here. We can get that directly
  // from the points, but it would be more efficient to also extract what line
  // each fragment belongs to here and pass that info to triangulate polygons.

  frag_list lifrags, lofrags;  
  line_fragments(xhost, xid, lifrags);  
  
  // cout << "line fragments: " << endl << lifrags << endl;
  
  // Assemble them into continuous lines ("polygons") around
  // the boundary of the zone.

  //  assemble_line_fragments(lifrags);

  kd_line_fragment lprototype(xid);
  kd_line_fragment::assemble(xhost, lprototype, lifrags, lofrags);

  // cout << "lofrags: " << endl << lofrags << endl;
  

  // lofrags now contains the polygons.

  // Triangulate the polygons and enter the triangles
  // in the lower cover of the zone and corresponding surfaces.

  kd_line_fragment::triangulate(xhost, lofrags, xid);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::triangulate."  << endl << endl;
  return;
}

void
geometry::kd_zone::
triangles(id_list& xresult) const
{
  // cout << endl << "Entering kd_zone::triangles." << endl;

  // Preconditions:

  require(precondition_of(triangles(host(), id(), xresult)));

  // Body:

  triangles(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(triangles(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_zone::triangles." << endl;
  return;
}

void
geometry::kd_zone::
triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_zone::triangles." << endl;
  // cout << "zone: " << xid.pod() << "  " << name(xhost, xid) << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  
  // Skip past the faces.

  for(int i=0; i<FACE_CT; ++i)
  {
    lid = litr.hub_pod();

    kd_face::triangles(xhost, lid, xresult);
    litr.next();
  }

  // Get the triangles.

  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.triangles().contains(lid))
    {
      xresult.push_back(lid);
    }
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::triangles." << endl;
  return;
}

void
geometry::kd_zone::
triangle_members(id_list& xtriangle_mbrs) const
{
  // cout << endl << "Entering kd_zone::triangle_members." << endl;

  // Preconditions:

  require(precondition_of(triangle_members(host(), id(), xtriangle_mbrs)));

  // Body:

  triangle_members(*_host, _id, xtriangle_mbrs);

  // Postconditions:

  ensure(postcondition_of(triangle_members(host(), id(), xtriangle_mbrs)));

  // Exit:

  // cout << "Leaving kd_zone::triangle_members." << endl;
  return;
}

void
geometry::kd_zone::
triangle_members(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangle_mbrs)
{
  // cout << endl << "Entering kd_zone::triangle_members." << endl;
  // cout << "zone: " << xid.pod() << "  " << name(xhost, xid) << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(xhost.base_space().member_id(false));

  // Skip past the faces.

  for(int i=0; i<FACE_CT; ++i)
  {
    lid = litr.hub_pod();

    kd_face::triangle_members(xhost, lid, xtriangle_mbrs);
    litr.next();
  }

  // Get the triangles.

  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.triangles().contains(lid))
    {
      kd_triangle::members(xhost, lid, xtriangle_mbrs, true);
    }
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::triangle_members." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::kd_zone::
kd_zone()
{
  
  // Preconditions:
    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

void
geometry::kd_zone::
remove_lower_cover(kd_lattice& xhost, scoped_index xid, scoped_index xfaces[], id_list& xcontents)
{
  // Preconditions:

  require(unexecutable("xfaces is an array with at least FACE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));
  require(xhost.base_space().is_jim(xid));

  // xid passed by value to ensure the following:
  //  require((&xid != &result[0]) && (&xid != &result[1]) && (&xid != &result[2]));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();

  int i=0;
  xcontents.clear();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid(lbase.member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(i < FACE_CT)
    {
      // Faces are the first FACE_CT members of the lower cover.

      xfaces[i] = lid;
    }
    else
    {
      // The contents of the zone are any remaining members.

      xcontents.push_back(lid);
    }
    litr.next();
    ++i;
  }
  lbase.release_cover_id_space_iterator(litr);
  
  lbase.clear_cover(LOWER, xid);

  // Postconditions:


  // Exit:

  return;
}

sheaf::scoped_index
geometry::kd_zone::
new_subzone(kd_lattice& xhost, const scoped_index& xold_zone_id, const scoped_index xface_ids[], int xi)
{
  // cout << endl << "Entering kd_zone::new_subzone." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.zones().contains(xold_zone_id));

  // Body:

  // Create the new subzone.

  scoped_index result = xhost.zones().new_member();

  // Link the subzone to its faces.

  base_space_poset& lbase = xhost.base_space();  
  for(int i=0; i<FACE_CT; ++i)
  {
    const scoped_index& lface_id = xface_ids[i];
    if(i == xi)
    {
      // The current face was a face in the old zone,
      // replace the old zone in the upper cover of the face.

      lbase.replace_cover_member(xold_zone_id, result, UPPER, lface_id);
    }
    else
    {
      // The current face is a new face; 
      // just insert the new zone in its upper cover.

      lbase.insert_cover_member(result, UPPER, lface_id);
    }

    // Insert the face in the lower cover of the zone.

    lbase.insert_cover_member(lface_id, LOWER, result);
  }  

  // Set the splitting plane to default value.

  kd_plane lp;
  xhost.put_plane(result, lp);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::new_subzone." << endl;
  return result;
}

void
geometry::kd_zone::
refine_x_axis_aligned(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[])
{
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(in_bounds(xhost, xid, xp));
  require(xhost.zones().contains(xid));
  require(xp.alignment() == X_AXIS_ALIGNED);

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  scoped_index& lnew_zone_0_id = xnew_ids[0];
  scoped_index& lnew_zone_1_id = xnew_ids[1];
  scoped_index& lnew_face_id = xnew_ids[2];
  const scoped_index& lold_zone_id = xid;

  base_space_poset& lbase = xhost.base_space();

  if(lbase.is_jim(xid))
  {
    // This zone has not been refined previously refined.

    // Get the existing faces while removing them from lower cover;
    // this leaves old zone in upper cover of faces.

    scoped_index lold_face_ids[FACE_CT];
    id_list lcontents;
    remove_lower_cover(xhost, xid, lold_face_ids, lcontents);

    // Refine face 0.

    scoped_index lface_0_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[0], xp, lface_0_new_ids);

    // Refine face 4.

    scoped_index lface_4_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[4], xp, lface_4_new_ids);

    // Refine face 1.

    scoped_index lface_1_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[1], xp, lface_1_new_ids);

    // Refine face 5.

    scoped_index lface_5_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[5], xp, lface_5_new_ids);
    
    // Create the new face from the new edges of the refined faces,

    scoped_index le_ids[kd_face::EDGE_CT];
    le_ids[0] = lface_4_new_ids[2];
    le_ids[1] = lface_1_new_ids[2];
    le_ids[2] = lface_5_new_ids[2];
    le_ids[3] = lface_0_new_ids[2];
    lnew_face_id = kd_face::new_face(xhost, le_ids, X_AXIS_ALIGNED);

    // Set the bounding box for the new face.
    // Note that we copy the old box here rather than
    // keeping a reference because the calls to 
    // put_bounding_box may force reallocation.

    kd_bounding_box lold_box = xhost.bounding_box(lold_zone_id);
    kd_bounding_box lbox;

    lbox = lold_box;
    lbox.lb()[X_AXIS_ALIGNED] = xp.distance();
    lbox.ub()[X_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_face_id, lbox);

    // Create the first subzone.

    scoped_index lf_ids[FACE_CT];
    lf_ids[0] = lface_0_new_ids[0];
    lf_ids[1] = lface_1_new_ids[0];
    lf_ids[2] = lold_face_ids[2];
    lf_ids[3] = lnew_face_id;
    lf_ids[4] = lface_4_new_ids[0];
    lf_ids[5] = lface_5_new_ids[0];
    lnew_zone_0_id = new_subzone(xhost, lold_zone_id, lf_ids, 2);

    // Set the bounding box for the first subzone.

    lbox = lold_box;
    lbox.ub()[X_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_zone_0_id, lbox);
    
    // Create the second subzone.

    lf_ids[0] = lface_0_new_ids[1];
    lf_ids[1] = lface_1_new_ids[1];
    lf_ids[2] = lnew_face_id;
    lf_ids[3] = lold_face_ids[3];
    lf_ids[4] = lface_4_new_ids[1];
    lf_ids[5] = lface_5_new_ids[1];
    lnew_zone_1_id = new_subzone(xhost, lold_zone_id, lf_ids, 3);

    // Set the bounding box for the second subzone.

    lbox = lold_box;
    lbox.lb()[X_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_zone_1_id, lbox);

    // Sort the contents into the new subzones and splitting face.

    if(!lcontents.empty())
    {
      split_contents(xhost, lold_zone_id, xnew_ids, xp, lcontents);
    }
    
    // Restore the original lower cover, but with faces 2, 3 replaced
    // by first and second subzones, respectively.

    // $$SCRIBBLE: assumes lower cover is empty.

    lbase.insert_cover_member(lold_face_ids[0], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[1], LOWER, lold_zone_id);
    lbase.new_link(lold_zone_id, lnew_zone_0_id);
    lbase.new_link(lold_zone_id, lnew_zone_1_id);
    lbase.insert_cover_member(lold_face_ids[4], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[5], LOWER, lold_zone_id);

    // Existing zone is no longer a leaf.

    xhost.zones().unleaf(lold_zone_id);
  }
  else
  {
    // This zone is already refined.
    // Get the ids of the two subzones and the face between them.
    // Subzones 0, 1 are 3th and 4rd items in lower cover, respectively.

    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid); 
    assertion(!litr.is_done());

    litr.next(); // 2nd item.
    assertion(!litr.is_done());

    litr.next(); // 3rd item.
    assertion(!litr.is_done());
    
    xnew_ids[0] = lbase.member_id(litr.hub_pod(), false);

    litr.next(); // 4th item.
    assertion(!litr.is_done());    

    xnew_ids[1] = lbase.member_id(litr.hub_pod(), false);

    // The face between is the 4th face of the first subzone.

    xnew_ids[2] = face(xhost, xnew_ids[0], 3);

    lbase.release_cover_id_space_iterator(litr);
  }

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_zone::
refine_y_axis_aligned(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[])
{
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(in_bounds(xhost, xid, xp));
  require(xhost.zones().contains(xid));
  require(xp.alignment() == Y_AXIS_ALIGNED);

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  scoped_index& lnew_zone_0_id = xnew_ids[0];
  scoped_index& lnew_zone_1_id = xnew_ids[1];
  scoped_index& lnew_face_id = xnew_ids[2];
  const scoped_index& lold_zone_id = xid;

  base_space_poset& lbase = xhost.base_space();

  if(lbase.is_jim(xid))
  {
    // This zone has not been refined previously refined.

    // Get the existing faces while removing them from lower cover;
    // this leaves old zone in upper cover of faces.

    scoped_index lold_face_ids[FACE_CT];
    id_list lcontents;
    remove_lower_cover(xhost, xid, lold_face_ids, lcontents);

    // Refine face 0.

    scoped_index lface_0_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[0], xp, lface_0_new_ids);

    // Refine face 3.

    scoped_index lface_3_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[3], xp, lface_3_new_ids);

    // Refine face 1.

    scoped_index lface_1_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[1], xp, lface_1_new_ids);

    // Refine face 2.

    scoped_index lface_2_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[2], xp, lface_2_new_ids);
    
    // Create the new face from the new edges of the refined faces,

    scoped_index le_ids[kd_face::EDGE_CT];
    le_ids[0] = lface_0_new_ids[2];
    le_ids[1] = lface_3_new_ids[2];
    le_ids[2] = lface_1_new_ids[2];
    le_ids[3] = lface_2_new_ids[2];
    lnew_face_id = kd_face::new_face(xhost, le_ids, Y_AXIS_ALIGNED);

    // Set the bounding box for the new face.
    // Note that we copy the old box here rather than
    // keeping a reference because the calls to 
    // put_bounding_box may force reallocation.

    kd_bounding_box lold_box = xhost.bounding_box(lold_zone_id);
    kd_bounding_box lbox;

    lbox = lold_box;
    lbox.lb()[Y_AXIS_ALIGNED] = xp.distance();
    lbox.ub()[Y_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_face_id, lbox);

    // Create the first subzone.

    scoped_index lf_ids[FACE_CT];
    lf_ids[0] = lface_0_new_ids[0];
    lf_ids[1] = lface_1_new_ids[0];
    lf_ids[2] = lface_2_new_ids[0];
    lf_ids[3] = lface_3_new_ids[0];
    lf_ids[4] = lold_face_ids[4];
    lf_ids[5] = lnew_face_id;
    lnew_zone_0_id = new_subzone(xhost, lold_zone_id, lf_ids, 4);

    // Set the bounding box for the first subzone.

    lbox = lold_box;
    lbox.ub()[Y_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_zone_0_id, lbox);

    // Create the second subzone.

    lf_ids[0] = lface_0_new_ids[1];
    lf_ids[1] = lface_1_new_ids[1];
    lf_ids[2] = lface_2_new_ids[1];
    lf_ids[3] = lface_3_new_ids[1];
    lf_ids[4] = lnew_face_id;
    lf_ids[5] = lold_face_ids[5];
    lnew_zone_1_id = new_subzone(xhost, lold_zone_id, lf_ids, 5);

    // Set the bounding box for the second subzone.

    lbox = lold_box;
    lbox.lb()[Y_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_zone_1_id, lbox);

    // Sort the contents into the new subzones and splitting face.

    if(!lcontents.empty())
    {
      split_contents(xhost, lold_zone_id, xnew_ids, xp, lcontents);
    }

    // Restore the original lower cover, but with faces 4, 5 replaced by
    // the first and second subzone, respectively.

    // $$SCRIBBLE: assumes lower cover is empty.

    lbase.insert_cover_member(lold_face_ids[0], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[1], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[2], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[3], LOWER, lold_zone_id);
    lbase.new_link(lold_zone_id, lnew_zone_0_id);
    lbase.new_link(lold_zone_id, lnew_zone_1_id);

    // Existing zone is no longer a leaf or a jim.

    xhost.zones().unleaf(lold_zone_id);
  }
  else
  {
    // This zone is already refined.
    // Get the ids of the two subzones and the face between them.
    // Subzones 0, 1 are 5th and 6th items in lower cover, resepctively.

    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);    
    assertion(!litr.is_done());    
    
    litr.next(); // 2nd item.
    assertion(!litr.is_done());
    
    litr.next(); // 3rd item.
    assertion(!litr.is_done());
    
    litr.next(); // 4th item.
    assertion(!litr.is_done());
    
    litr.next(); // 5th item.
    assertion(!litr.is_done());
    
    xnew_ids[0] = litr.hub_pod();
    
    litr.next(); // 6th item.
    assertion(!litr.is_done());
    
    xnew_ids[1] = litr.hub_pod();

    // The face between is the fifth face of the second subzone.

    xnew_ids[2] = face(xhost, xnew_ids[1], 4);

    lbase.release_cover_id_space_iterator(litr);
  }

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_zone::
refine_z_axis_aligned(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[])
{
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(in_bounds(xhost, xid, xp));
  require(xhost.zones().contains(xid));
  require(xp.alignment() == Z_AXIS_ALIGNED);

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  scoped_index& lnew_zone_0_id = xnew_ids[0];
  scoped_index& lnew_zone_1_id = xnew_ids[1];
  scoped_index& lnew_face_id = xnew_ids[2];
  const scoped_index& lold_zone_id = xid;

  base_space_poset& lbase = xhost.base_space();

  if(lbase.is_jim(xid))
  {
    // This zone has not been refined previously refined.

    // Get the existing faces and other members while removing 
    // them from lower cover; this leaves old zone in upper cover of faces.

    scoped_index lold_face_ids[FACE_CT];
    id_list lcontents;
    remove_lower_cover(xhost, xid, lold_face_ids, lcontents);

    assertion(lcontents.empty());
    
    // Refine face 4.

    scoped_index lface_4_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[4], xp, lface_4_new_ids);

    // Refine face 3.

    scoped_index lface_3_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[3], xp, lface_3_new_ids);

    // Refine face 5.

    scoped_index lface_5_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[5], xp, lface_5_new_ids);

    // Refine face 2.

    scoped_index lface_2_new_ids[3];
    kd_face::refine(xhost, lold_face_ids[2], xp, lface_2_new_ids);
    
    // Create the new face from the new edges of the refined faces,

    scoped_index le_ids[kd_face::EDGE_CT];
    le_ids[0] = lface_4_new_ids[2];
    le_ids[1] = lface_3_new_ids[2];
    le_ids[2] = lface_5_new_ids[2];
    le_ids[3] = lface_2_new_ids[2];
    lnew_face_id = kd_face::new_face(xhost, le_ids, Z_AXIS_ALIGNED);

    // Set the bounding box for the new face.

    kd_bounding_box lold_box = xhost.bounding_box(lold_zone_id);
    kd_bounding_box lbox;

    lbox = lold_box;
    lbox.lb()[Z_AXIS_ALIGNED] = xp.distance();
    lbox.ub()[Z_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_face_id, lbox);

    // Create the first subzone.

    scoped_index lf_ids[FACE_CT];
    lf_ids[0] = lold_face_ids[0];
    lf_ids[1] = lnew_face_id;
    lf_ids[2] = lface_2_new_ids[0];
    lf_ids[3] = lface_3_new_ids[0];
    lf_ids[4] = lface_4_new_ids[0];
    lf_ids[5] = lface_5_new_ids[0];
    lnew_zone_0_id = new_subzone(xhost, lold_zone_id, lf_ids, 0);

    // Set the bounding box for the first subzone.

    lbox = lold_box;
    lbox.ub()[Z_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_zone_0_id, lbox);

    // Create the second subzone.

    lf_ids[0] = lnew_face_id;
    lf_ids[1] = lold_face_ids[1];
    lf_ids[2] = lface_2_new_ids[1];
    lf_ids[3] = lface_3_new_ids[1];
    lf_ids[4] = lface_4_new_ids[1];
    lf_ids[5] = lface_5_new_ids[1];
    lnew_zone_1_id = new_subzone(xhost, lold_zone_id, lf_ids, 1);

    // Sort the contents into the new subzones and splitting face.

    if(!lcontents.empty())
    {
      split_contents(xhost, lold_zone_id, xnew_ids, xp, lcontents);
    }

    // Set the bounding box for the second subzone.

    lbox = lold_box;
    lbox.lb()[Z_AXIS_ALIGNED] = xp.distance();
    xhost.put_bounding_box(lnew_zone_1_id, lbox);

    // Restore original lower cover with faces 0, 1 replaced
    // by subzones 0, 1, respectively.

    // $$SCRIBBLE: assumes lower cover is empty.

    lbase.new_link(lold_zone_id, lnew_zone_0_id);
    lbase.new_link(lold_zone_id, lnew_zone_1_id);
    lbase.insert_cover_member(lold_face_ids[2], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[3], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[4], LOWER, lold_zone_id);
    lbase.insert_cover_member(lold_face_ids[5], LOWER, lold_zone_id);


    // Existing zone is no longer a leaf or a jim.

    xhost.zones().unleaf(lold_zone_id);
  }
  else
  {
    // This zone is already refined.
    // Get the ids of the two subzones and the face between them.
    // Subzones 0, 1 are 1st and 2nd items in lower cover, respectively.

    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);    
    assertion(!litr.is_done());    
    
    xnew_ids[0] = litr.hub_pod();
    
    litr.next();
    assertion(!litr.is_done());
    
    xnew_ids[1] = litr.hub_pod();

    // The face between is the first face of the second subzone.

    xnew_ids[2] = face(xhost, xnew_ids[1], 0);

    lbase.release_cover_id_space_iterator(litr);
  }

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_zone::
split_contents(kd_lattice& xhost,
               const scoped_index& xold_zone_id,
               const scoped_index xnew_ids[], 
               const kd_plane& xp, 
               id_list& xcontents)
{
  // cout << endl << "Entering kd_zone::split_contents." << endl;

  // Preconditions:


  // Body:

  //   base_space_poset& lbase = xhost.base_space();
  //   scoped_index& lback_zone_id = xnew_ids[0];
  //   scoped_index& lfront_zone_id = xnew_ids[1];
  //   scoped_index& lsplitting_face_id = xnew_ids[2];

  //   // Split the triangles into back and front parts.

  //   id_list lback_tris, lfront_tris, lsegs;  
  //   for(id_list::iterator lt = xcontents.begin(); i != xcontents.end(); ++lt)
  //   {
  //     assertion(xhost.triangles().contains(*lt));

  //     kd_triangle::refine(xhost, litr.hub_pod(), xp, lback_tris, lfront_tris, lsegs);
  //   }

  //   // Insert back triangles in back zone.

  //   for(id_list::iterator lt = lback_tris.begin(); i != llback_tris.end(); ++lt)
  //   {
  //     if(lbase.cover_is_empty(UPPER, *lt))
  //     {
  //       // This is a new triangle, just link to it.

  //       lbase.new_link(lback_zone_id, *lt);
  //     }
  //     else
  //     {
  //       // This is one of the existing triangles,
  //       // replace the old zone in its upper cover.

  //       lbase.insert_cover_member(*lt, LOWER, lback_zone_id);
  //       lbase.replace_cover_member(xold_zone_id, UPPER, *lt);
  //     }
  //   }

  //   // Insert front triangles in front zone.

  //   for(id_list::iterator lt = lfront_tris.begin(); i != llfront_tris.end(); ++lt)
  //   {
  //     if(lbase.cover_is_empty(UPPER, *lt))
  //     {
  //       // This is a new triangle, just link to it.

  //       lbase.new_link(lfront_zone_id, *lt);
  //     }
  //     else
  //     {
  //       // This is one of the existing triangles,
  //       // replace the old zone in its upper cover.

  //       lbase.insert_cover_member(*lt, LOWER, lfront_zone_id);
  //       lbase.replace_cover_member(xold_zone_id, UPPER, *lt);
  //     }
  //   }

  //   // Insert line segments into the splitting face.
  //   // $$SCRIBBLE: where to we sort the segments into a line?

  //   for(id_list::iterator ls = lsegs.begin(); i != lsegs.end(); ++lt)
  //   {
  //     lbase.new_link(lsplitting_face_id, *ls);
  //   }
      
  // Postconditions:

  //  ensure(xcontents.empty());
  
  // Exit:

  // cout << "Leaving kd_zone::split_contents." << endl;
  return;
}


void
geometry::kd_zone::
clear_contents(pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_zone::clear_contents." << endl;

  // Preconditions:

  require(precondition_of(clear_contents(host(), id(), xdeleted)));
  
  // Body:

  clear_contents(*_host, _id, xdeleted);

  // Postconditions:

  ensure(postcondition_of(clear_contents(host(), id(), xdeleted)));

  // Exit:

  // cout << "Leaving kd_zone::clear_contents." << endl;
  return;
}

void
geometry::kd_zone::
clear_contents(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_zone::clear_contents." << endl;
  // cout << "zone: " << xid.pod() << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.zone_leaves().contains(xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  
  // Skip the faces.

  for(int i=0; i<FACE_CT; ++i)
  {
    litr.next();
  }
  
  // The remaining members should be triangles.
  // Disconnect and inactivate them.

  scoped_index lsurf_id;
  scoped_index lpt_ids[kd_triangle::POINT_CT];
  scoped_index& lpt0_id = lpt_ids[0];
  scoped_index& lpt1_id = lpt_ids[1];
  scoped_index& lpt2_id = lpt_ids[2];

  scoped_index lid(lbase.member_id(false));

  while(!litr.is_done())
  {
    // Enter the triangle in the deleted set.

    xdeleted.insert(litr.hub_pod());

    // Mark the surface containing the triangle as modified.

    // $$SCRIBBLE: this process and the subsequent update
    // of the surfaces in kd_lattice::insert_line and insert_plane
    // can be made more efficeint by grouping the triangles 
    // by surface in the lower cover of the zone and inserting 
    // the jrm in the lower cover of the surface.

    lid = litr.hub_pod();

    kd_triangle::surface(xhost, lid, lsurf_id);
    xhost.modified_surfaces().insert(lsurf_id);

    // Remove the triangle.
    
    kd_triangle::clear(xhost, lid, lpt_ids);
    kd_triangle::deactivate(xhost, lid);

    // Truncation reversal points are identified during triangulation,
    // so remove them when we remove the triangulation.
    // Centroid can never a a reversal point.

    xhost.truncation_reversal_points().remove_member(lpt0_id);
    xhost.truncation_reversal_points().remove_member(lpt1_id);
    
    // Remove truncation mid points and centroid.

    if(lbase.cover_is_empty(UPPER, lpt0_id))
    {
      // This vertex is a mid point
      // and is no longer in any triangles.
      // Deactivate it.

      xhost.truncation_mid_points().delete_member(lpt0_id);
    }
    if(lbase.cover_is_empty(UPPER, lpt1_id))
    {
      // This vertex is a mid point
      // and is no longer in any triangles.
      // Deactivate it.

      xhost.truncation_mid_points().delete_member(lpt1_id);
    }
    if(lbase.cover_is_empty(UPPER, lpt2_id))
    {
      // This vertex is a centroid
      // and is no longer in any triangles.
      // Deactivate it.

      xhost.centroids().delete_member(lpt2_id);
    }
    
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);
  
  lbase.remove_cover_members(hash_set_filter(xdeleted), LOWER, xid);

  // Insert this zone in the cleared zones list.

  xhost.cleared_zones().insert(xid.hub_pod());

  // Postconditions:

  ensure(is_empty(xhost, xid));
  
  // Exit:

  // cout << "Leaving kd_zone::clear_contents." << endl;
  return;
}


void
geometry::kd_zone::
clear_contents(const kd_plane& xp, pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_zone::clear_contents." << endl;

  // Preconditions:

  require(xp.is_valid());
  require((!host().contains_equivalent_plane(xp)));
  
  // Body:

  clear_contents(*_host, _id, xp, xdeleted);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::clear_contents." << endl;
  return;
}

void
geometry::kd_zone::
clear_contents(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_zone::clear_contents." << endl;

  // Preconditions:

  require(xp.is_valid());
  require((!xhost.contains_equivalent_plane(xp)));

  // Body:

  if(xhost.leaves().contains(xid))
  {
    // The new plane splits the zone; 
    // clear the contents of the zone.

    clear_contents(xhost, xid, xdeleted);
  }
  else
  {
    // This zone is not a leaf.
    // Get the splitting plane.

    const kd_plane& lp = xhost.plane(xid);
    
    // Get the subzones.

    scoped_index lsubzone_ids[2];
    kd_zone::subzones(xhost, xid, lsubzone_ids);

    // Clear the appropriate subzones.

    if(lp.alignment() == xp.alignment())
    {
      // The new plane is parallel to the splitting plane.

      if(xp.distance() < lp.distance())
      {
        // The new plane lies on the back side of the splitting plane;
        // clear the subzone in back of the splitting plane.

        clear_contents(xhost, lsubzone_ids[0], xp, xdeleted);
      }
      else
      {
        // The new plane lies on the front side of the splitting plane;
        // clear the subzone in front of the splitting plane.

        clear_contents(xhost, lsubzone_ids[1], xp, xdeleted);
      }      
    }    
    else
    {
      // The plane crosses the splitting plane;
      // clear both subzones.

      clear_contents(xhost, lsubzone_ids[0], xp, xdeleted);
      clear_contents(xhost, lsubzone_ids[1], xp, xdeleted);
    }
  }

  // Postconditions:

  ensure(is_empty(xhost, xid));

  // Exit:

  // cout << "Leaving kd_zone::clear_contents." << endl;
  return;
}


void
geometry::kd_zone::
intersect_plane(const kd_plane& xp, frag_list& xfrags)
{
  // cout << endl << "Entering kd_zone::intersect_plane." << endl;

  // Preconditions:

  require(xp.is_valid());
  require((!host().contains_equivalent_plane(xp)));
  
  // Body:

  intersect_plane(*_host, _id, xp, xfrags);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::intersect_plane." << endl;
  return;
}

void
geometry::kd_zone::
intersect_plane(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, frag_list& xfrags)
{
  // cout << endl << "Entering kd_zone::intersect_plane." << endl;

  // Preconditions:

  require(xp.is_valid());
  require((!xhost.contains_equivalent_plane(xp)));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  if(xhost.leaves().contains(xid))
  {
    // The new plane splits the zone; 
    // intersect the contents of the zone.

    index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
    scoped_index lid(xhost.base_space().member_id(false));
    while(!litr.is_done())
    {
      lid = litr.hub_pod();

      if(xhost.triangles().contains(lid))
      {
        kd_triangle::intersect_plane(xhost, lid, xp, xid, xfrags);
      }
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }
  else
  {
    // This zone is not a leaf.
    // Get the splitting plane.

    const kd_plane& lp = xhost.plane(xid);
    
    // Get the subzones.

    scoped_index lsubzone_ids[2];
    kd_zone::subzones(xhost, xid, lsubzone_ids);

    // Intersect the appropriate subzones.

    if(lp.alignment() == xp.alignment())
    {
      // The new plane is parallel to the splitting plane.

      if(xp.distance() < lp.distance())
      {
        // The new plane lies on the back side of the splitting plane;
        // intersect the subzone in back of the splitting plane.

        intersect_plane(xhost, lsubzone_ids[0], xp, xfrags);
      }
      else
      {
        // The new plane lies on the front side of the splitting plane;
        // intersect the subzone in front of the splitting plane.

        intersect_plane(xhost, lsubzone_ids[1], xp, xfrags);
      }      
    }    
    else
    {
      // The plane crosses the splitting plane;
      // intersect both subzones.

      intersect_plane(xhost, lsubzone_ids[0], xp, xfrags);
      intersect_plane(xhost, lsubzone_ids[1], xp, xfrags);
    }
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::intersect_plane." << endl;
  return;
}

bool
geometry::kd_zone::
is_empty() const
{
  // cout << endl << "Entering kd_zone::is_empty." << endl;

  // Preconditions:

  require(precondition_of(is_empty(host(), id())));

  // Body:

  bool result = is_empty(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_empty(host(), id())));

  // Exit:

  // cout << "Leaving kd_zone::is_empty." << endl;
  return result;
}

bool
geometry::kd_zone::
is_empty(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone::is_empty." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.zones().contains(xid));

  // Body:

  bool result = xhost.base_space().cover_ct(LOWER, xid) <= FACE_CT;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_zone::is_empty." << endl;
  return result;
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_zone::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_zone*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_zone*
geometry::kd_zone::
clone() const
{
  kd_zone* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_zone();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_zone&
geometry::kd_zone::
operator=(const kd_zone& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_zone&
geometry::kd_zone::
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
geometry::kd_zone::
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
operator << (ostream& xos, const kd_zone& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  const kd_lattice& lkdl = xn.host();
  const base_space_poset& lbase = xn.host().base_space();

  xos << "zone " << xn.host().zones().id_space().pod(xn.id());
  xos << "  top id: " << xn.id();
  xos << "  name: " << xn.name();
  xos << "  type: " << xn.type_name();
  xos << boolalpha;
  xos << "  is_jim: " << xn.is_jim();
  xos << "  is_leaf: " << xn.is_leaf();
  xos << noboolalpha;
  xos << "  lb: " << xn.coord_lower_bound();
  xos << "  ub: " << xn.coord_upper_bound();
  xos << "  bounding box: " << xn.host().bounding_box(xn.id());
  
  xos << endl;
  xos << endl;
  
  xos << "\tlower cover:";
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xn.id());
  while(!litr.is_done())
  {
    xos << "   " << lbase.member_name(litr.hub_pod());
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  xos << endl << endl;

  scoped_index lids[kd_zone::EDGE_CT];

  xos << "\tfaces:";
  xn.faces(lids);
  for(int i=0; i<kd_zone::FACE_CT; ++i)
  {
    xos << "   " << lbase.member_name(lids[i]);
    xos << "   " << lkdl.faces().id_space().pod(lids[i]);
  }
  xos << endl << endl;

  xos << "\tedges:";
  xn.edges(lids);
  for(int i=0; i<kd_zone::EDGE_CT; ++i)
  {
    xos << "   " << lbase.member_name(lids[i]);
    xos << "   " << lkdl.edges().id_space().pod(lids[i]);
  }
  xos << endl << endl;

  xos << "\tvertices:";
  xn.vertices(lids);
  for(int i=0; i<kd_zone::VERTEX_CT; ++i)
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
deep_size(const kd_zone& xn, bool xinclude_shallow)
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
