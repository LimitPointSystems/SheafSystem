

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_edge

#include "kd_edge.h"

#include "assert_contract.h"
#include "cohort.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "kd_bounding_box.h"
#include "kd_edge_cohort.h"
#include "kd_lattice.h"
#include "kd_line_fragment.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_vertex.h"
#include "sec_e3.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.


// ===========================================================
// KD_EDGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_edge::
prototype_name(kd_alignment xalignment)
{
  // cout << endl << "Entering kd_edge::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string lproto_name[4] = 
    {
      "kd_x_axis_aligned_edge",
      "kd_y_axis_aligned_edge",
      "kd_z_axis_aligned_edge",
      "kd_not_axis_aligned_edge"
    };

  const string& result = lproto_name[xalignment];

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_edge::prototype_name." << endl;
  return result;
}

geometry::kd_edge::
kd_edge(kd_lattice& xhost, const scoped_index xv_ids[], kd_alignment xalignment)
  :kd_member(xhost)
{
  // cout << endl << "Entering kd_edge::new_edge." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, VERTEX_CT, xhost.vertices().contains(xv_ids[i]));
  require(xalignment != NOT_AXIS_ALIGNED);
    
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  // Body:

  _id = new_edge(xhost, xv_ids, xalignment);
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(alignment() == xalignment);
  ensure(host().edges().contains(id()));
  ensure(host().edges().ct() == old_edges_ct + 1);
  ensure(host().vertices().ct() == old_vertices_ct);
  ensure(vertex(0) == xv_ids[0]);
  ensure(vertex(1) == xv_ids[1]);

  // Exit:

  // cout << "Leavinging kd_edge::kd_edge." << endl;
  return; 
}

geometry::scoped_index
geometry::kd_edge::
new_edge(kd_lattice& xhost, const scoped_index xv_ids[], kd_alignment xalignment)
{
  // cout << endl << "Entering kd_edge::new_edge." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, VERTEX_CT, xhost.vertices().contains(xv_ids[i]));
  require(xalignment != NOT_AXIS_ALIGNED);

  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());
    
  // Body:

  base_space_poset& lbase = xhost.base_space();  

  // Create the edge with alignment xalignment.

  scoped_index result;

  switch(xalignment)
  {
    case X_AXIS_ALIGNED:
      result = xhost.x_edges().new_member();
      break;
    case Y_AXIS_ALIGNED:
      result = xhost.y_edges().new_member();
      break;
    case Z_AXIS_ALIGNED:
      result = xhost.z_edges().new_member();
      break;
    default:
      post_fatal_error_message("Unsupported edge alignment.");
  }      

  // The edge covers the vertices.

  lbase.new_link(result, xv_ids[0]);
  lbase.new_link(result, xv_ids[1]);

  // Postconditions:

  ensure(alignment(xhost, result) == xalignment);
  ensure(xhost.edges().contains(result));
  ensure(xhost.edges().ct() == old_edges_ct + 1);
  ensure(xhost.vertices().ct() == old_vertices_ct);
  ensure(vertex(xhost, result, 0) == xv_ids[0]);
  ensure(vertex(xhost, result, 1) == xv_ids[1]);

  // Exit:

  // cout << "Leaving kd_edge::new_edge." << endl;
  return result; 
}

geometry::kd_edge::
kd_edge(kd_lattice& xhost, const scoped_index& xid)
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

geometry::kd_edge::
kd_edge(const kd_edge& xother)
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

geometry::kd_edge::
~kd_edge()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_edge::
subedges(scoped_index xresult[]) const
{
  // Preconditions:

  require(unexecutable("xresult is an array with at least SUBEDGE_CT entries"));
  require(host().base_space().state_is_read_accessible());
  require(!host().leaves().contains(id()));
  
  // Body:

  subedges(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, SUBEDGE_CT, host().edges().contains(xresult[i]));

  // Exit:

  return;
}

void
geometry::kd_edge::
subedges(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_edge::subedges(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least SUBEDGE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require(!xhost.leaves().contains(xid));
  
  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  xresult[0] = litr.hub_pod();
  litr.next();
  xresult[1] = litr.hub_pod();
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure_for_all(i, 0, SUBEDGE_CT, xhost.edges().contains(xresult[i]));
  
  // Exit:

  // cout << "Leaving kd_edge::subedges(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_edge::
subedge(int xi) const
{
  // cout << endl << "Entering kd_edge::subedge(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < SUBEDGE_CT));

  // Body:

  scoped_index result = subedge(*_host, _id, xi);

  // Postconditions:

  ensure(host().edges().contains(result));

  // Exit:

  // cout << "Leaving kd_edge::subedge(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_edge::
subedge(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_edge::subedge(const kd_lattice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require((0 <= xi) && (xi < SUBEDGE_CT));

  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  if(xi = 1)
  {
    litr.next();
  }
  
  scoped_index result = xhost.base_space().member_id(litr.hub_pod(), false);

  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xhost.edges().contains(result));
  
  // Exit:

  // cout << "Leaving kd_edge::subedge(const kd_lattice&, const scoped_index&, int)." << endl;
  return result;
}

void
geometry::kd_edge::
vertices(scoped_index xresult[]) const
{
  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(host().base_space().state_is_read_accessible());
  
  // Body:

  vertices(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, host().vertices().contains(xresult[i]));

  // Exit:

  return;
}

void
geometry::kd_edge::
vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_edge::vertices." << endl;
  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  const vertex_cohort& lvertices = xhost.vertices();

  scoped_index lid(xid);
  // cout << "lid: " << lid.internal_pod() << endl;
  
  index_space_iterator& litr0 = lbase.get_cover_id_space_iterator(LOWER, lid);
  for(int i=0; i<VERTEX_CT; ++i)
  {
    lid = litr0.hub_pod();
    // cout << "lid: " << lid.internal_pod() << endl;
    while(!lvertices.contains(lid))
    {
      index_space_iterator& litr1 = lbase.get_cover_id_space_iterator(LOWER, lid);
      for(int j=0; j<i; ++j)
      {
        litr1.next();
      }
      lid = litr1.hub_pod();
      // cout << "lid: " << lid.internal_pod() << endl;
      lbase.release_cover_id_space_iterator(litr1);
    }

    xresult[i] = lid;
    litr0.next();
  }
  lbase.release_cover_id_space_iterator(litr0);

  // cout << "result[0]: " << xresult[0].internal_pod() << endl;
  // cout << "result[1]: " << xresult[1].internal_pod() << endl;


  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, xhost.vertices().contains(xresult[i]));

  // Exit:

  // cout << "Leaving kd_edge::vertices." << endl;
  return;
}

void
geometry::kd_edge::
vertices(scoped_index xresult[], e3_lite xcoords[]) const
{
  // Preconditions:

  require(precondition_of(vertices(host(), id(), xresult, xcoords)));
  
  // Body:

  vertices(*_host, _id, xresult, xcoords);
  
  // Postconditions:

  ensure(postcondition_of(vertices(host(), id(), xresult, xcoords)));

  // Exit:

  return;
}

void
geometry::kd_edge::
vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[], e3_lite xcoords[])
{
  // cout << endl << "Entering kd_edge::vertices." << endl;
  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(xhost.coords().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  
  // Body:

  vertices(xhost, xid, xresult);
  xhost.coords().get_fiber(xresult[0], xcoords[0], false);
  xhost.coords().get_fiber(xresult[1], xcoords[1], false);

  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, xhost.base_space().vertices().contains_member(xresult[i]));
  ensure_for_all(i, 0, VERTEX_CT, xcoords[i] == kd_vertex::coords(xhost, xresult[i]));

  // Exit:

  // cout << "Leaving kd_edge::vertices." << endl;
  return;
}


sheaf::scoped_index
geometry::kd_edge::
vertex(int xi) const
{
  // cout << endl << "Entering kd_edge::vertex." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < VERTEX_CT));

  // Body:

  scoped_index result = vertex(*_host, _id, xi);

  // Postconditions:

  ensure(host().vertices().contains(result));

  // Exit:

  // cout << "Leaving kd_edge::vertex." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_edge::
vertex(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_edge::vertex." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require((0 <= xi) && (xi < VERTEX_CT));

  // Body:

  const base_space_poset& lbase = xhost.base_space();
  const vertex_cohort& lvertices = xhost.vertices();

  scoped_index lid = xid;
  while(!lvertices.contains(lid))
  {
    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, lid);
    for(int i=0; i<xi; ++i)
    {
      litr.next();
    }
    lid = litr.hub_pod();
    lbase.release_cover_id_space_iterator(litr);
  }
  
  scoped_index result = lid;

  // Postconditions:

  ensure(xhost.vertices().contains(result));
  
  // Exit:

  // cout << "Leaving kd_edge::vertex." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_edge::
splitting_vertex() const
{
  // cout << endl << "Entering kd_edge::splitting_vertex()." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());

  // Body:

  scoped_index result = splitting_vertex(*_host, _id);

  // Postconditions:

  ensure(host().vertices().contains(result));

  // Exit:

  // cout << "Leaving kd_edge::splitting_vertex(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_edge::
splitting_vertex(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_edge::splitting_vertex(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));

  // Body:

  scoped_index result = subedge(xhost, xid, 0);
  result = vertex(xhost, result, 1);

  // Postconditions:

  ensure(xhost.vertices().contains(result));
  
  // Exit:

  // cout << "Leaving kd_edge::splitting_vertex(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

geometry::kd_alignment
geometry::kd_edge::
alignment(const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_edge::alignment(const e3_lite&, const e3_lite&)." << endl;

  // Preconditions:


  // Body:

  kd_alignment result;
  if((xlb[1] == xub[1]) && (xlb[2] == xub[2]) && (xlb[0] != xub[0]))
  {
    result = X_AXIS_ALIGNED;
  }
  else if((xlb[0] == xub[0]) && (xlb[2] == xub[2]) && (xlb[1] != xub[1]))
  {
    result = Y_AXIS_ALIGNED;
  }
  else if((xlb[0] == xub[0]) && (xlb[1] == xub[1]) && (xlb[2] != xub[2]))
  {
    result = Z_AXIS_ALIGNED;
  }
  else
  {
    result = NOT_AXIS_ALIGNED;
  }    


  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::alignment(const e3_lite&, const e3_lite&)." << endl;
  return result;
}

bool
geometry::kd_edge::
is_axis_aligned(const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_edge::is_axis_aligned." << endl;

  // Preconditions:


  // Body:

  bool result = (alignment(xlb, xub) != NOT_AXIS_ALIGNED);


  // Postconditions:

  ensure(result == (alignment(xlb, xub) != NOT_AXIS_ALIGNED));

  // Exit:

  // cout << "Leaving kd_edge::is_axis_aligned." << endl;
  return result;
}

void
geometry::kd_edge::
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
geometry::kd_edge::
coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());
  require(xhost.edges().contains(xid));

  // Body:

  // Get the vertex ids.

  scoped_index lv_ids[VERTEX_CT];
  vertices(xhost, xid, lv_ids);

  coord_bounds(xhost, lv_ids[0], lv_ids[1], xlb, xub);
  
  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::e3_lite
geometry::kd_edge::
coord_lower_bound() const
{
  // cout << endl << "Entering kd_edge::coord_lower_bound." << endl;

  // Preconditions:


  // Body:

  e3_lite result = coord_lower_bound(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::coord_lower_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_edge::
coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_edge::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite result, lub;
  coord_bounds(xhost, xid, result, lub);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_edge::
coord_upper_bound() const
{
  // cout << endl << "Entering kd_edge::coord_upper_bound." << endl;

  // Preconditions:


  // Body:

  e3_lite result = coord_upper_bound(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::coord_upper_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_edge::
coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_edge::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite llb, result;
  coord_bounds(xhost, xid, llb, result);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

void
geometry::kd_edge::
put_coord_bounds(const e3_lite& xlb, const e3_lite& xub, bool xforward)
{
  // cout << endl << "Entering kd_edge::put_coord_bounds(const e3_lite&, const e3_lite&b, bool)." << endl;
  // Preconditions:

  require(host().coords().state_is_read_write_accessible());
  require(is_axis_aligned(xlb, xub));
  
  // Body:

  put_coord_bounds(*_host, _id, xlb, xub, xforward);
  
  // Postconditions:

  ensure(coord_lower_bound() == xlb);
  ensure(coord_upper_bound() == xub);

  // Exit:

  // cout << "Leaving kd_edge::put_coord_bounds(const e3_lite&, const e3_lite&, bool)." << endl;
  return;
}

void
geometry::kd_edge::
put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub, bool xforward)
{
  // cout << endl << "Entering kd_edge::put_coord_bounds(kd_lattice&, const scoped_index&, const e3_lite&, const e3_lite&, bool)." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_write_accessible());
  require(is_axis_aligned(xlb, xub));
  
  // Body:

  // Get the vertex ids.

  scoped_index lv_ids[VERTEX_CT];
  vertices(xhost, xid, lv_ids);

  // Set the coordinates for the vertices.

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

  // cout << "Leaving kd_edge::put_coord_bounds(kd_lattice&, const scoped_index&, const e3_lite&, const e3_lite&, bool)." << endl;
  return;
}

bool
geometry::kd_edge::
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
geometry::kd_edge::
in_bounds(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());
  require(xhost.edges().contains(xid));

  // Body:


  e3_lite llb, lub;
  coord_bounds(xhost, xid, llb, lub);
  
  int i = xp.alignment();
  bool result = (llb[i] < xp.distance()) && (xp.distance() < lub[i]);

  //  cout << "llb: " << llb << " lub: " << lub << " alignment: " << i << " distance: " << xp.distance() << endl;
  

  // Postconditions:


  // Exit:

  return result;
}


bool
geometry::kd_edge::
contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_edge::contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::contains_point." << endl;
  return result;
}

bool
geometry::kd_edge::
contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_edge::contains_point." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  const kd_bounding_box& lbox = xhost.bounding_box(xid);
  const e3_lite& llb = lbox.lb();
  const e3_lite& lub = lbox.ub();

  bool result;
  
  kd_alignment lalignment = alignment(xhost, xid);
  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      result = (xpt[1] == llb[1]) && (xpt[2] == llb[2]) && (llb[0] <= xpt[0]) && (xpt[0] <= lub[0]);
      break;
    case Y_AXIS_ALIGNED:
      result = (xpt[0] == llb[0]) && (xpt[2] == llb[2]) && (llb[1] <= xpt[1]) && (xpt[1] <= lub[1]);
      break;
    case Z_AXIS_ALIGNED:
      result = (xpt[0] == llb[0]) && (xpt[1] == llb[1]) && (llb[2] <= xpt[2]) && (xpt[2] <= lub[2]);
      break;
    default:
      post_fatal_error_message("Unsupported alignment type.");
      break;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::contains_point." << endl;
  return result;
}

bool
geometry::kd_edge::
interior_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_edge::interior_contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = interior_contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_edge::
interior_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_edge::interior_contains_point." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  const kd_bounding_box& lbox = xhost.bounding_box(xid);
  const e3_lite& llb = lbox.lb();
  const e3_lite& lub = lbox.ub();

  bool result;
  
  kd_alignment lalignment = alignment(xhost, xid);  
  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      result = (xpt[1] == llb[1]) && (xpt[2] == llb[2]) && (llb[0] < xpt[0]) && (xpt[0] < lub[0]);
      break;
    case Y_AXIS_ALIGNED:
      result = (xpt[0] == llb[0]) && (xpt[2] == llb[2]) && (llb[1] < xpt[1]) && (xpt[1] < lub[1]);
      break;
    case Z_AXIS_ALIGNED:
      result = (xpt[0] == llb[0]) && (xpt[1] == llb[1]) && (llb[2] < xpt[2]) && (xpt[2] < lub[2]);
      break;
    default:
      post_fatal_error_message("Unsupported alignment type.");
      break;
  }

  // Postconditions:

  ensure(unexecutable("result == (xpt[i] == bnd[i] for some i and bnd"));

  // Exit:

  // cout << "Leaving kd_edge::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_edge::
boundary_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_edge::boundary_contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = boundary_contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::boundary_contains_point." << endl;
  return result;
}

bool
geometry::kd_edge::
boundary_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_edge::boundary_contains_point." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  const kd_bounding_box& lbox = xhost.bounding_box(xid);
  const e3_lite& llb = lbox.lb();
  const e3_lite& lub = lbox.ub();

  bool result;  
  
  kd_alignment lalignment = alignment(xhost, xid);
  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      result = (xpt[1] == llb[1]) && (xpt[2] == llb[2]) && ((llb[0] == xpt[0]) || (xpt[0] == lub[0]));
      break;
    case Y_AXIS_ALIGNED:
      result = (xpt[0] == llb[0]) && (xpt[2] == llb[2]) && ((llb[1] == xpt[1]) || (xpt[1] == lub[1]));
      break;
    case Z_AXIS_ALIGNED:
      result = (xpt[0] == llb[0]) && (xpt[1] == llb[1]) && ((llb[2] == xpt[2]) || (xpt[2] == lub[2]));
      break;
    default:
      post_fatal_error_message("Unsupported alignment type.");
      break;
  }

  // Postconditions:

  ensure(unexecutable("result == (xpt[i] == bnd[i] for some i and bnd"));

  // Exit:

  // cout << "Leaving kd_edge::boundary_contains_point." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_edge::
locate_point(const e3_lite& xpt, int xd) const
{
  // cout << endl << "Entering kd_edge::locate_point." << endl;

  // Preconditions:

  require(precondition_of(locate_point(host(), id(), xpt, xd)));

  // Body:

  scoped_index result = locate_point(*_host, _id, xpt, xd);

  // Postconditions:

  ensure(postcondition_of(locate_point(host(), id(), xpt, xd)));

  // Exit:

  // cout << "Leaving kd_edge::locate_point." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_edge::
locate_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt, int xd)
{
  // cout << endl << "Entering kd_edge::locate_point." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(interior_contains_point(xhost, xid, xpt));

  // Body:

  scoped_index result(xid);

  while(!xhost.leaves().contains(result))
  {      
    // xpt is not on the boundary of the edge,
    // so it must either in the splitting point or 
    // in one of the subedges.

    const kd_plane& lp = xhost.plane(result);
    int lalignment = lp.int_alignment();
    double lp_dist = lp.distance();
    double lpt_dist = xpt[lalignment];
    
    if((xd < DB) && (lpt_dist == lp_dist))
    {
      // Point is located on the vertex between the subedges.

      result = kd_edge::splitting_vertex(xhost, result);
    }
    else if(lpt_dist < lp_dist)
    {
      // Point is located in back side subedge.

      result = kd_edge::subedge(xhost, result, 0);
    }
    else
    {
      // Point is located in front side subedge.

      result = kd_edge::subedge(xhost, result, 1);
    }
  }
  
  // Postconditions:

  ensure(xhost.leaves().contains(result));
  ensure(xhost.cell_contains_point(result, xpt));

  // Exit:

  // cout << "Leaving kd_edge::locate_point." << endl;
  return result;
}


void
geometry::kd_edge::
refine(const kd_plane& xp, scoped_index xnew_ids[])
{
  // Preconditions:

  require(host().base_space().in_jim_edit_mode());
  require(host().coords().state_is_read_write_accessible());
  require(alignment() == xp.alignment());
  require(in_bounds(xp));
  
  // Body:

  refine(*_host, _id, xp, xnew_ids);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_edge::
refine(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[])
{
  // cout << endl << "Entering kd_edge::refine." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.edges().contains(xid));
  require(alignment(xhost, xid) == xp.alignment());
  require(in_bounds(xhost, xid, xp));

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  // Set the splitting plane.

  xhost.put_plane(xid, xp);

  scoped_index& lnew_edge_0_id = xnew_ids[0];
  scoped_index& lnew_edge_1_id = xnew_ids[1];
  scoped_index& lnew_vertex_id = xnew_ids[2];
  const scoped_index& lold_edge_id = xid;
  
  base_space_poset& lbase = xhost.base_space();

  if(lbase.is_jim(xid))
  {
    // This edge has not been refined; refine it now.

    // Get the existing vertices while removing them from lower cover;
    // this leaves old edge in upper cover of vertices..
  
    scoped_index lold_vertex_ids[VERTEX_CT];
    list<scoped_index> lcontents;
    kd_edge::remove_lower_cover(xhost, xid, lold_vertex_ids, lcontents);

    // Compute the coordinates for the new vertex;
    // new vertex has same comnponents as old vertices,
    // except in the direction the edge is aligned.

    e3_lite lfiber;
    xhost.coords().get_fiber(lold_vertex_ids[0], lfiber, false);
    int i = xp.alignment();
    lfiber[i] = xp.distance();

    // Create the new vertex.

    lnew_vertex_id = kd_vertex::new_vertex(xhost, lfiber);
    
    // Create the first new subedge.

    scoped_index lv_ids[VERTEX_CT];
    lv_ids[0] = lold_vertex_ids[0];
    lv_ids[1] = lnew_vertex_id;
    lnew_edge_0_id = kd_edge::new_subedge(xhost, lold_edge_id, lv_ids, 0);

    // Set the bounding box for the first subedge.
    // Note that we copy the old box here rather than
    // keeping a reference because the calls to 
    // put_bounding_box may force reallocation.

    kd_bounding_box lold_box = xhost.bounding_box(lold_edge_id);
    kd_bounding_box lbox;

    lbox = lold_box;
    lbox.ub()[i] = xp.distance();
    xhost.put_bounding_box(lnew_edge_0_id, lbox);

    // Create the second new subedge.

    lv_ids[0] = lnew_vertex_id;
    lv_ids[1] = lold_vertex_ids[1];
    lnew_edge_1_id = kd_edge::new_subedge(xhost, lold_edge_id, lv_ids, 1);

    // Set the bounding box for the second subedge.

    lbox = lold_box;
    lbox.lb()[i] = xp.distance();
    xhost.put_bounding_box(lnew_edge_1_id, lbox);

    // Sort the contents into the new subedges and vertex.

    if(!lcontents.empty())
    {
      split_contents(xhost, lold_edge_id, xnew_ids, xp, lcontents);
    }    
    
    // Existing edge covers the two new subedges.
    // $$SCRIBBLE: assumes lower cover is empty.

    lbase.new_link(lold_edge_id, lnew_edge_0_id);
    lbase.new_link(lold_edge_id, lnew_edge_1_id); 

    // Existing edge is no longer a leaf or a jim.

    xhost.leaves().remove_member(lold_edge_id);
    lbase.jims().remove_member(lold_edge_id);
  }
  else
  {
    // This edge has already been refined, 
    // get the two sub-edges and the vertex
    // between them.

    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);    
    assertion(!litr.is_done());
    
    xnew_ids[0] = lbase.member_id(litr.hub_pod(), false);
    
    litr.next();
    assertion(!litr.is_done());
    
    xnew_ids[1] = lbase.member_id(litr.hub_pod(), false);
    xnew_ids[2] = lbase.member_id(lbase.first_cover_member(LOWER, litr.hub_pod()), false);

    lbase.release_cover_id_space_iterator(litr);
  } 

  // Postconditions:

  ensure(xhost.edges().contains(xnew_ids[0]));
  ensure(xhost.edges().contains(xnew_ids[1]));
  ensure(xhost.vertices().contains(xnew_ids[2]));
  ensure(vertex(xhost, xnew_ids[0], 1) == xnew_ids[2]);
  ensure(vertex(xhost, xnew_ids[1], 0) == xnew_ids[2]);

  // Exit:

  // cout << "Leaving kd_edge::refine." << endl;
  return;
}

void
geometry::kd_edge::
insert_point(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt, scoped_index& xresult)
{
  // cout << endl << "Entering kd_edge::insert_point." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.base_space().in_jim_edit_mode());
  require(contains_point(xhost, xid, xpt));
  
  // Body:

  // cout << "inserting point: " << xpt << "  in edge: " << xid.internal_pod() << endl;
  

  base_space_poset& lbase = xhost.base_space();
  sec_e3& lcoords = xhost.coords();

  int lalignment = int_alignment(xhost, xid);
  vd_value_type lpt_align = xpt[lalignment];
  vd_value_type ltolerance = xhost.intersection_tolerance()[lalignment];

  e3_lite lcur_pt, lv0_pt, lv1_pt;
  vd_value_type lprev_align, lcur_align, lv0_align, lv1_align;
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);

  // Get the coordinates of the first vertex.

  scoped_index lv0_pt_id = lbase.member_id(litr.hub_pod(), false);
  lcoords.get_fiber(lv0_pt_id, lv0_pt, true);
  lv0_align = lv0_pt[lalignment];
  
  lcur_pt = lv0_pt;
  lcur_align = lv0_align;

  // Skip the tree vertices.
  // We define points to be distinct from vertices,
  // even if they numerically have the same coordinates.


  // Get the coordinates of the second vertex.

  litr.next();
  scoped_index lv1_pt_id = lbase.member_id(litr.hub_pod(), false);
  lcoords.get_fiber(lv1_pt_id, lv1_pt, true);
  lv1_align = lv1_pt[lalignment];

  litr.next();

  // Insert xpt in contents, keeping the contents
  // ordered by increasing coordinate.
  
  scoped_index lid = lbase.member_id(false);

  while(!litr.is_done())
  {
    assertion(xhost.coords().schema().discretization().contains_member(litr.hub_pod()));

    lprev_align = lcur_align;
    lid = litr.hub_pod();
    lcoords.get_fiber(lid, lcur_pt, true);
    lcur_align = lcur_pt[lalignment];

    // cout << "comparing to pt: " << litr.item().internal_pod();  
    // cout << "  " << name(xhost, litr.item());
    // cout << "  coords: " << lcur_pt << endl;

    if(sheaf::a_eql(lpt_align, lcur_align, ltolerance))
    {
      // New point is equivalent to existing point;
      // this may an intersection or truncation point

      // $$SCRIBBLE: fix this problem.
      /// @issue Truncation in edge. This coincidence is an
      /// intersection, only if the coincident point is in a 
      /// line in another plane. If the coincident point is
      /// a line in the same plane as xpt, we have a truncation. 

      xresult = lid;
      xpt =  lcur_pt;
      xhost.intersection_points().insert_member(xresult);
      
      // cout << "found intersection point " << xresult.internal_pod() << endl;

      break;
    }
    else if(lcur_align > lpt_align)
    {
      // This is the first item in the iteration
      // with coordinate greater than xpt,
      // insert xpt before the current item.

      // Create a new point

      xresult = kd_point::new_point(xhost, xpt);

      // Insert the point in the lower_cover.
      // Insertion will invalidate the iterator,
      // but we're going to break out of the loop anyway.

      lbase.insert_cover_member(xresult, LOWER, xid, litr);
      lbase.insert_cover_member(xid, UPPER, xresult);

      // cout << "inserted new point: " << xresult.internal_pod() << endl;

      // Result is contained in a kd_edge; put it in edge_points.

      xhost.edge_points().insert_member(xresult);

      break;
    }
    else
    {
      // cout << "not an intersection" << endl;

      litr.next();
    }    
  }
  
  if(litr.is_done())
  {
    // If the edge contained any points,
    // then lcur_align is strictly < lpt_align,
    // but if the edge was empty, we may have
    // the point may be equal to the vertex.

    assertion(lcur_align <= lpt_align);

    if(sheaf::c_eql(lpt_align, lv0_align))
    {
      // Point is within sheaf::double_tolerance of first vertex.
      // Place it precisely at the first vertex to avoid numerical instabilities
      // in kd_face::adjacent_face and elsewhere associated with
      // crossing corner of face close to vertex.
    
      xpt = lv0_pt;
      xresult = lv0_pt_id;
      // cout << "weld to first vertex: " << lv0_pt_id.pod() << "  " << xpt << endl;
    }
    else if(sheaf::c_eql(lpt_align, lv1_align))
    {
      // Point is within sheaf::double_tolerance of second vertex.
      // Place it precisely at the second vertex to avoid numerical instabilities
      // in kd_face::adjacent_face and elsewhere associated with
      // crossing corner of face close to vertex.
    
      xpt = lv1_pt;
      xresult = lv1_pt_id;
      // cout << "weld to second vertex: " << lv1_pt_id.pod() << "  " << xpt << endl;
    }
    else
    {
      // Insert xpt at the end of the contents.

      // Create a new point.

      xresult = kd_point::new_point(xhost, xpt);

      // Insert the point at end of the lower cover

      xhost.base_space().new_link(xid, xresult);

      // cout << "inserted new point: " << xresult.internal_pod() << " at end of contents" << endl;
    }  

    // Result is contained in a kd_edge; put it in edge_points.

    xhost.edge_points().insert_member(xresult);
  }

  lbase.release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xhost.base_space().vertices().contains_member(xresult));
  ensure(xhost.edge_points().contains(xresult));
  ensure(xpt == kd_point::coords(xhost, xresult));
  
  // Exit:

  // cout << "Leaving kd_edge::insert_point." << endl << endl;
  return;
}

void
geometry::kd_edge::
insert_point_no_intersection(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_edge::insert_point_no_intersection." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.base_space().in_jim_edit_mode());
  
  // Body:

  // cout << "inserting point: " << xpt_id.internal_pod() << "  in edge: " << xid.internal_pod() << endl;

  base_space_poset& lbase = xhost.base_space();
  
  if(!lbase.cover_contains_member(LOWER, xid, xpt_id))
  {
    lbase.new_link(xid, xpt_id);
    xhost.edge_points().insert_member(xpt_id);
  }
  
  // $$SCRIBBLE: what about vertex welding?

  // Postconditions:

  ensure(xhost.base_space().contains_link(xid, xpt_id));
  ensure(xhost.edge_points().contains(xpt_id));
  
  // Exit:

  // cout << "Leaving kd_edge::insert_point_no_intersection." << endl << endl;
  return;
}

void
geometry::kd_edge::
insert_point_no_intersection(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt, scoped_index& xresult)
{
  // cout << endl << "Entering kd_edge::insert_point_no_intersection." << endl;

  // Preconditions:

  require(xhost.edges().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.base_space().in_jim_edit_mode());
  require(contains_point(xhost, xid, xpt));
  
  // Body:

  // cout << "inserting point: " << xpt << "  in edge: " << xid.internal_pod() << endl;
  

  base_space_poset& lbase = xhost.base_space();
  sec_e3& lcoords = xhost.coords();

  int lalignment = int_alignment(xhost, xid);
  vd_value_type lpt_align = xpt[lalignment];
  vd_value_type ltolerance = xhost.intersection_tolerance()[lalignment];

  e3_lite lcur_pt, lv0_pt, lv1_pt;
  vd_value_type lprev_align, lcur_align, lv0_align, lv1_align;
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);

  // Get the coordinates of the first vertex.

  scoped_index lv0_pt_id = lbase.member_id(litr.hub_pod(), false);
  lcoords.get_fiber(lv0_pt_id, lv0_pt, true);
  lv0_align = lv0_pt[lalignment];
  
  lcur_pt = lv0_pt;
  lcur_align = lv0_align;

  // Skip the tree vertices.
  // We define points to be distinct from vertices,
  // even if they numerically have the same coordinates.


  // Get the coordinates of the second vertex.

  litr.next();
  scoped_index lv1_pt_id = lbase.member_id(litr.hub_pod(), false);
  lcoords.get_fiber(lv1_pt_id, lv1_pt, true);
  lv1_align = lv1_pt[lalignment];

  litr.next();

  // Insert xpt in contents, keeping the contents
  // ordered by increasing coordinate.
  
  scoped_index lid = lbase.member_id(false);

  while(!litr.is_done())
  {
    assertion(xhost.coords().schema().discretization().contains_member(litr.hub_pod()));

    lprev_align = lcur_align;
    lid = litr.hub_pod();
    lcoords.get_fiber(lid, lcur_pt, true);
    lcur_align = lcur_pt[lalignment];

    // cout << "comparing to pt: " << litr.item().internal_pod();  
    // cout << "  " << name(xhost, litr.item());
    // cout << "  coords: " << lcur_pt << endl;

    if(lcur_align > lpt_align)
    {
      // This is the first item in the iteration
      // with coordinate greater than xpt,
      // insert xpt before the current item.

      // Create a new point

      xresult = kd_point::new_point(xhost, xpt);

      // Insert the point in the lower_cover.
      // Insertion will invalidate the iterator,
      // but we're going to break out of the loop anyway.

      lbase.insert_cover_member(xresult, LOWER, xid, litr);
      lbase.insert_cover_member(xid, UPPER, xresult);

      // cout << "inserted new point: " << xresult.internal_pod() << endl;

      // Result is contained in a kd_edge; put it in edge_points.

      xhost.edge_points().insert_member(xresult);

      break;
    }
    else
    {
      // cout << "not an intersection" << endl;

      litr.next();
    }    
  }
  
  if(litr.is_done())
  {
    // If the edge contained any points,
    // then lcur_align is strictly < lpt_align,
    // but if the edge was empty, we may have
    // the point may be equal to the vertex.

    assertion(lcur_align <= lpt_align);

    if(sheaf::c_eql(lpt_align, lv0_align))
    {
      // Point is within sheaf::double_tolerance of first vertex.
      // Place it precisely at the first vertex to avoid numerical instabilities
      // in kd_face::adjacent_face and elsewhere associated with
      // crossing corner of face close to vertex.
    
      xpt = lv0_pt;
      xresult = lv0_pt_id;
      // cout << "weld to first vertex: " << lv0_pt_id.pod() << "  " << xpt << endl;
    }
    else if(sheaf::c_eql(lpt_align, lv1_align))
    {
      // Point is within sheaf::double_tolerance of second vertex.
      // Place it precisely at the second vertex to avoid numerical instabilities
      // in kd_face::adjacent_face and elsewhere associated with
      // crossing corner of face close to vertex.
    
      xpt = lv1_pt;
      xresult = lv1_pt_id;
      // cout << "weld to second vertex: " << lv1_pt_id.pod() << "  " << xpt << endl;
    }
    else
    {
      // Insert xpt at the end of the contents.

      // Create a new point.

      xresult = kd_point::new_point(xhost, xpt);

      // Insert the point at end of the lower cover

      xhost.base_space().new_link(xid, xresult);

      // cout << "inserted new point: " << xresult.internal_pod() << " at end of contents" << endl;
    }  

    // Result is contained in a kd_edge; put it in edge_points.

    xhost.edge_points().insert_member(xresult);
  }

  lbase.release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xhost.base_space().vertices().contains_member(xresult));
  ensure(xhost.edge_points().contains(xresult));
  ensure(xpt == kd_point::coords(xhost, xresult));
  
  // Exit:

  // cout << "Leaving kd_edge::insert_point_no_intersection." << endl << endl;
  return;
}

sheaf::scoped_index
geometry::kd_edge::
other_face(const kd_lattice& xhost, const scoped_index& xid, const scoped_index& xface_id)
{
  // cout << endl << "Entering kd_edge::other_face." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.faces().contains(xface_id));

  // Body:

  // cout << "face: " << xhost.bounding_box(xface_id) << endl;
  // cout << "edge: " << xhost.bounding_box(xid) << endl;

  scoped_index result;
  int lface_alignment = row_dofs(xhost, xface_id).alignment;

  // cout << "face_alignment: " << alignment(xhost, xface_id) << endl;
  // cout << "edge_alignment: " << alignment(xhost, xid) << endl;
  
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  scoped_index litr_id(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    litr_id = litr.hub_pod();

    // cout << litr.item() << "  " << kd_member::name(xhost, litr.item()) << endl;
    
    if(litr_id != xface_id)
    {
      int litr_alignment = row_dofs(xhost, litr_id).alignment;

      // cout << "itr alignment: " << litr_alignment << endl;
      
      if(litr_alignment == lface_alignment)
      {
        result = litr_id;
        break;
      }
    }

    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);

  // cout << "result: " << result;
  // cout << "  " << name(xhost, result) << endl;
  // cout << "bounding box: " << xhost.bounding_box(result) << endl;

  // Postconditions:

  ensure(xhost.faces().contains(result));
  ensure(alignment(xhost, result) == alignment(xhost, xface_id));
  ensure(xhost.base_space().contains_link(result, xid));
  
  // Exit:

  // cout << "Leaving kd_edge::other_face." << endl;
  return result;
}

bool
geometry::kd_edge::
is_empty() const
{
  // cout << endl << "Entering kd_edge::is_empty." << endl;

  // Preconditions:

  require(precondition_of(is_empty(host(), id())));

  // Body:

  bool result = is_empty(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_empty(host(), id())));

  // Exit:

  // cout << "Leaving kd_edge::is_empty." << endl;
  return result;
}

bool
geometry::kd_edge::
is_empty(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_edge::is_empty." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));

  // Body:

  bool result = xhost.base_space().cover_ct(LOWER, xid) <= VERTEX_CT;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::is_empty." << endl;
  return result;
}

void
geometry::kd_edge::
line_fragments(const kd_line_fragment& xfrag_prototype, bool xfwd, frag_list& xresult) const
{
  // Preconditions:

  require(precondition_of(line_fragments(host(),id(), xfrag_prototype, xfwd, xresult)));
  
  // Body:

  line_fragments(*_host, _id, xfrag_prototype, xfwd, xresult);
  
  // Postconditions:

  ensure(postcondition_of(line_fragments(host(),id(), xfrag_prototype, xfwd, xresult)));

  // Exit:

  return;
}

void
geometry::kd_edge::
line_fragments(const kd_lattice& xhost, const scoped_index& xid, const kd_line_fragment& xfrag_prototype, bool xfwd, frag_list& xresult)
{
  // cout << endl << "Entering kd_edge::line_fragments." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require(xhost.leaves().contains(xid));
  
  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  scoped_index lprev_pt = xhost.base_space().member_id(false);
  scoped_index llast_pt = xhost.base_space().member_id(false);
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);

  // First tree vertex is first point.

  lprev_pt = litr.hub_pod();
  litr.next();

  // Second tree vertex is last point

  llast_pt = litr.hub_pod();
  litr.next();
  
  while(!litr.is_done())
  {
    // Make every pair of tree verices or points defined a fragment;
    // let the assembly process sort them out.

    xresult.push_back(xfrag_prototype);

    // Leave surface and container id as set in prototype.

    if(xfwd)
    {
      // Insert the segment in the forward order.

      xresult.back().pt_ids.push_back(lprev_pt);
      xresult.back().pt_ids.push_back(xhost.base_space().member_id(litr.hub_pod(), false));
    }
    else
    {
      // Insert the segment in the reverse order.
      // Note tht although the points in the segment
      // will be in the reverse order, the order
      // of the segments in the list is not reversed.

      xresult.back().pt_ids.push_back(xhost.base_space().member_id(litr.hub_pod(), false));
      xresult.back().pt_ids.push_back(lprev_pt);
    }
    
    lprev_pt = litr.hub_pod();
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);

  // Last segment

  xresult.push_back(xfrag_prototype);

  if(xfwd)
  {
    xresult.back().pt_ids.push_back(lprev_pt);
    xresult.back().pt_ids.push_back(llast_pt);
  }
  else
  {
    xresult.back().pt_ids.push_back(llast_pt);
    xresult.back().pt_ids.push_back(lprev_pt);
  }
  
  // cout << "alignment: " << alignment(xhost, xid) << endl;
  // cout << "result: " << endl << xresult << endl;

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_edge::line_fragments." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_edge::
kd_edge()
{
  
  // Preconditions:

    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

void
geometry::kd_edge::
remove_lower_cover(kd_lattice& xhost, scoped_index xid, scoped_index xvertices[], list<scoped_index>& xcontents)
{
  // Preconditions:

  require(unexecutable("xvertices is an array with at least VERTEX_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require(xhost.base_space().is_jim(xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();
  
  int i=0;
  xcontents.clear();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  while(!litr.is_done())
  {
    if(i < VERTEX_CT)
    {
      // Faces are the first FACE_CT members of the lower cover.

      xvertices[i] = lbase.member_id(litr.hub_pod(), false);
    }
    else
    {
      // The contents of the zone are any remaining members.

      xcontents.push_back(lbase.member_id(litr.hub_pod(), false));
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
geometry::kd_edge::
new_subedge(kd_lattice& xhost, 
	    const scoped_index& xold_edge_id, 
	    const scoped_index xvertex_ids[], 
	    int xi)
{
  // cout << endl << "Entering kd_edge::new_subedge." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.edges().contains(xold_edge_id));

  // Body:

  // Body:

  // Create the new subedge.

  kd_alignment lalignment = alignment(xhost, xold_edge_id);
  scoped_index result;

  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      result = xhost.x_edges().new_member();
      break;
    case Y_AXIS_ALIGNED:
      result = xhost.y_edges().new_member();
      break;
    case Z_AXIS_ALIGNED:
      result = xhost.z_edges().new_member();
      break;
    default:
      post_fatal_error_message("Unsupported edge alignment.");
  }

  // Link the subedge to its vertices.

  base_space_poset& lbase = xhost.base_space();  
  for(int i=0; i<VERTEX_CT; ++i)
  {
    const scoped_index& lvertex_id = xvertex_ids[i];
    if(i == xi)
    {
      // The current vertex was an vertex in the old edge,
      // replace the old edge in the upper cover of the vertex.

      lbase.replace_cover_member(xold_edge_id, result, UPPER, lvertex_id);
    }
    else
    {
      // The current vertex is a new vertex; 
      // just insert the new vertex in its upper cover.

      lbase.insert_cover_member(result, UPPER, lvertex_id);
    }

    // Insert the vertex in the lower cover of the edge.

    lbase.insert_cover_member(lvertex_id, LOWER, result);
  }  

  // Set the splitting plane to default value.

  kd_plane lp;
  xhost.put_plane(result, lp);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_edge::new_subedge." << endl;
  return result;
}


void
geometry::kd_edge::
split_contents(kd_lattice& xhost,
	       const scoped_index& xold_edge_id,
	       const scoped_index xnew_ids[],
	       const kd_plane& xp,
	       list<scoped_index>& xcontents)
{
  // cout << endl << "Entering kd_edge::split_contents." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.edges().contains(xnew_ids[0]));
  require(xhost.edges().contains(xnew_ids[1]));
  require(xhost.vertices().contains(xnew_ids[2]));

  // Body:

  base_space_poset& lbase = xhost.base_space();

  // cout << "  old edge: " << xold_edge_id;
  // cout << "  lower cover: " << lbase.cover_iterator(LOWER, xold_edge_id);
  // cout << endl;

  //   cout << "  contents:";
  //   for(list<scoped_index>::iterator i= xcontents.begin(); i != xcontents.end(); ++i)
  //   {
  //     cout << "  " << i->internal_pod();
  //   }
  //   cout << endl;
  

  // Get id of coordinate component for edge alignment
  // same as splitting plane alignment.

  int le_id = xp.int_alignment();

  // Get the coordinate of the splitting plane
  
  vd_value_type lp_dist = xp.distance();

  scoped_index lpt_id;
  e3_lite lpt;

  while(!xcontents.empty())
  {
    lpt_id = xcontents.front();

    // cout << "lpt_id: " << lpt_id << endl;
    
    xhost.coords().get_fiber(lpt_id, lpt, false);
    
    vd_value_type lpt_dist = lpt[le_id];
    
    if(lpt_dist < lp_dist)
    {
      // Point is behind the splitting plane, 
      // insert the segment in the first subzone.

      lbase.insert_cover_member(lpt_id, LOWER, xnew_ids[0]);
      lbase.replace_cover_member(xold_edge_id, xnew_ids[0], UPPER, lpt_id);
    }
    else if(lpt_dist > lp_dist)
    {
      // Point is behind the splitting plane, 
      // insert the segment in the first subzone.

      lbase.insert_cover_member(lpt_id, LOWER, xnew_ids[1]);

      // cout << "  old edge: " << xold_edge_id;
      // cout << "  new edge: " << xnew_ids[1];
      // cout << "  lpt: " << lpt_id;
      // cout << "  upper cover: " << lbase.cover_iterator(UPPER, lpt_id);
      // cout << endl;
      
      lbase.replace_cover_member(xold_edge_id, xnew_ids[1], UPPER, lpt_id);
    }
    else
    {
      // Point is on the splitting plane.

      lbase.remove_cover_member(xold_edge_id, UPPER, lpt_id);
      kd_vertex::replace_point(xhost, xnew_ids[2], lpt_id);
    }
    
    // Move to the next point.

    xcontents.pop_front();
    
  } // end while
  

  // Postconditions:

  ensure(xcontents.empty());
  
  // Exit:

  // cout << "Leaving kd_edge::split_contents." << endl;
  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_edge::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_edge*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_edge*
geometry::kd_edge::
clone() const
{
  kd_edge* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_edge();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_edge&
geometry::kd_edge::
operator=(const kd_edge& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_edge&
geometry::kd_edge::
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
geometry::kd_edge::
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
operator << (ostream& xos, const kd_edge& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  xos << "edge " << xn.host().edges().id_space().pod(xn.id());
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
  const base_space_poset& lbase = xn.host().base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xn.id());
  while(!litr.is_done())
  {
    xos << "   " << lbase.member_name(litr.hub_pod());
    litr.next();
  }
  xos << endl << endl;
  lbase.release_cover_id_space_iterator(litr);

  scoped_index lids[kd_edge::VERTEX_CT];

  xos << "\tvertices:";
  xn.vertices(lids);
  for(int i=0; i<kd_edge::VERTEX_CT; ++i)
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
deep_size(const kd_edge& xn, bool xinclude_shallow)
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
