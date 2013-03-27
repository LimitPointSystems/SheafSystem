// $RCSfile: kd_point.cc,v $ $Revision: 1.7 $ $Date: 2013/03/13 00:59:00 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_point

#include "kd_point.h"
#include "array_section_dof_map.h"
#include "assert_contract.h"
#include "base_space_member.h"
#include "cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_edge.h"
#include "kd_lattice.h"
#include "kd_line.h"
#include "kd_segment.h"
#include "kd_truncation_pair.h"
#include "kd_truncation.h"
#include "postorder_itr.h"
#include "preorder_itr.h"
#include "std_algorithm.h"
#include "sec_e3.h"
#include "subcohort.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// KD_POINT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_point::
prototype_name()
{
  // cout << endl << "Entering kd_zone::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("kd_point");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_zone::prototype_name." << endl;
  return result;
}

geometry::kd_point::
kd_point(kd_lattice& xhost)
  : kd_member(xhost)
{
  // cout << "Entering kd_point(kd_lattice& xhost)." << endl;
  
  // Preconditions:

  require(host().base_space().in_jim_edit_mode());
    
  // Body:

  define_old_variable(size_type old_points_ct = xhost.points().ct());

  _id = new_point(xhost);

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().points().contains(id()));
  ensure(host().points().ct() == old_points_ct + 1);

  // Exit:

  // cout << "Leaving kd_point(kd_lattice& xhost)." << endl;
  return; 
}

sheaf::scoped_index
geometry::kd_point::
new_point(kd_lattice& xhost)
{
  // cout << "Entering kd_point::new_point(kd_lattice& xhost)." << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
    
  // Body:

  // Activate or create a point.

  scoped_index result = xhost.points().new_member();

  // Set the alignment dof.
  // $$SCRIBBLE: dof should be set once, in kd_lattice
  // when cohort is created, not once for each member.

  row_dofs(xhost, result).alignment = NOT_AXIS_ALIGNED;

  // Postconditions:

  ensure(xhost.points().contains(result));

  // Exit:

  // cout << "Leaving kd_point::new_point(kd_lattice& xhost)." << endl;
  return result; 
}

geometry::kd_point::
kd_point(kd_lattice& xhost, const e3_lite& xcoords)
  : kd_member(xhost)
{
  // cout << endl << "Entering kd_point(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  
  // Preconditions:

  require(host().base_space().in_jim_edit_mode());
  require(host().coords().state_is_read_write_accessible());
    
  // Body:

  define_old_variable(size_type old_points_ct = xhost.points().ct());

  _id = new_point(xhost, xcoords);

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().points().contains(id()));
  ensure(host().points().ct() == old_points_ct + 1);
  ensure(coords() == xcoords);
  
  // Exit:

  // cout << "Leaving kd_point(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  return; 
}

sheaf::scoped_index
geometry::kd_point::
new_point(kd_lattice& xhost, const e3_lite& xcoords)
{
  // cout << endl << "Entering kd_point::new_point(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
    
  // Body:

  // Create the point.

  scoped_index result = new_point(xhost);

  // Set the coordinates for the point.

  kd_point::put_coords(xhost, result, xcoords);

  // Postconditions:

  ensure(xhost.points().contains(result));
  ensure(coords(xhost, result) == xcoords);
  

  // Exit:

  // cout << "Leaving kd_point::new_point(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  return result; 
}

geometry::kd_point::
kd_point(kd_lattice& xhost, const scoped_index& xid)
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

geometry::kd_point::
kd_point(const kd_point& xother)
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

geometry::kd_point::
~kd_point()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

fiber_bundle::e3_lite
geometry::kd_point::
coords() const
{
  // Preconditions:

  require(host().coords().state_is_read_accessible());
  
  // Body:

  e3_lite result(coords(*_host, _id));

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::e3_lite
geometry::kd_point::
coords(const kd_lattice& xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));
  
  // Body:

  e3_lite result;
  xhost.coords().get_fiber(xid, result, false);

  // Postconditions:


  // Exit:

  return result;
}

void
geometry::kd_point::
coords(e3_lite& xcoords) const
{
  // Preconditions:

  require(host().coords().state_is_read_accessible());
  
  // Body:

  coords(*_host, _id, xcoords);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_point::
coords(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xcoords)
{
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));
  
  // Body:

  xhost.coords().get_fiber(xid, xcoords, false);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_point::
put_coords(const e3_lite& xcoords)
{
  // cout << endl << "Entering kd_point::put_coords(const e3_lite&)." << endl;

  // Preconditions:

  require(host().coords().state_is_read_write_accessible());

  // Body:

  put_coords(*_host, _id, xcoords);

  // Postconditions:

  ensure(coords() == xcoords);

  // Exit:

  // cout << "Leaving kd_point::put_coords(const e3_lite&)." << endl;
  return;
}

void
geometry::kd_point::
put_coords(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xcoords)
{
  // cout << endl << "Entering kd_point::put_coords(kd_lattice&, const scoped_index&, const e3_lite&)." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  xhost.coords().force_fiber(xid, xcoords, false);
  
  // Postconditions:

  ensure(coords(xhost, xid) == xcoords);

  // Exit:

  // cout << "Leaving kd_point::put_coords(kd_lattice&, const scoped_index&, const e3_lite&)." << endl;
  return;
}

bool
geometry::kd_point::
a_eql(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_point::a_eql." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = a_eql(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_point::a_eql." << endl;
  return result;
}

bool
geometry::kd_point::
a_eql(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_point::a_eql." << endl;

  // Preconditions:

  require(xhost.points().d_cells_contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  const e3_lite& ltolerance = xhost.point_tolerance();
  
  e3_lite lcoords;
  coords(xhost, xid, lcoords);

  bool result = fiber_bundle::vd_algebra::a_eql(xpt, lcoords, ltolerance);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_point::a_eql." << endl;
  return result;
}

void
geometry::kd_point::
snap(const e3_lite& xpt)
{
  // cout << endl << "Entering kd_point::snap." << endl;

  // Preconditions:

  require(precondition_of(snap(host(), id(), xpt)));

  // Body:

  snap(*_host, _id, xpt);

  // Postconditions:

  ensure(postcondition_of(snap(host(), id(), xpt)));

  // Exit:

  // cout << "Leaving kd_point::snap." << endl;
  return;
}

void
geometry::kd_point::
snap(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_point::snap." << endl;

  // Preconditions:

  require(xhost.base_space().vertices().contains_member(xid));
  require(xhost.coords().state_is_read_write_accessible());
  
  // Body:

  // Snap the point to the intersection location.

  put_coords(xhost, xid, xpt);

  // cout << "moved vertex " << xid.internal_pod();
  // cout << " to coordinates " << xpt << endl;

  // Mark the point as modified.

  xhost.modified_points().insert(xid);

  // Mark any lines or surfaces containing the point as modified.


  const subposet& llines = xhost.lines().sp();
  id_set& lnew_lines = xhost.new_lines();
  id_set& lmodified_lines = xhost.modified_lines();

  const subposet& lsurfaces = xhost.surfaces().sp();
  id_set& lnew_surfaces = xhost.new_surfaces();
  id_set& lmodified_surfaces = xhost.modified_surfaces();  
  
  base_space_member lmbr(&xhost.base_space(), xid);    
  hash_set_postorder_itr litr(lmbr, 0, UP);
  while(!litr.is_done())
  {
    scoped_index lindex = litr.index();
    if(llines.contains_member(lindex))
    {
      if(lnew_lines.find(lindex) == lnew_lines.end())
      {
        // cout << "inserting line " << lindex.internal_pod() << " in modified list" << endl;
        
        lmodified_lines.insert(lindex);
      }      
    }
    else if(lsurfaces.contains_member(litr.index()))
    {
      if(lnew_surfaces.find(lindex) == lnew_surfaces.end())
      {
        // cout << "inserting surface " << lindex.internal_pod() << " in modified list" << endl;

        lmodified_surfaces.insert(lindex);
      }
    }
    litr.next();
  }
  lmbr.detach_from_state();

 // Postconditions:

  ensure(coords(xhost, xid) == xpt);
  ensure(xhost.modified_points().find(xid) != xhost.modified_points().end());
  ensure(unexecutable("lines and surfaces containing xid are in either new or modified notification sets"));

  // Exit:

  // cout << "Leaving kd_point::snap." << endl;
  return;
}

bool
geometry::kd_point::
merge(scoped_index& xother_id)
{
  // cout << endl << "Entering kd_point::merge." << endl;

  // Preconditions:

  require(precondition_of(merge(host(), id(), xother_id)));

  // Body:

  bool result = merge(*_host, _id, xother_id);

  // Postconditions:

  ensure(postcondition_of(merge(host(), id(), xother_id)));

  // Exit:

  // cout << "Leaving kd_point::merge." << endl;
  return result;
}

bool
geometry::kd_point::
merge(kd_lattice& xhost, scoped_index& xid, scoped_index& xother_id)
{
  // cout << endl << "Entering kd_point::merge." << endl;

  // Preconditions:

  require(!(xid ==~ xother_id));
  require(xhost.base_space().in_jim_edit_mode());
  //   require(xhost.base_space().vertices().contains_member(xid));
  //   require(xhost.base_space().vertices().contains_member(xother_id));
  require(xhost.points().d_cells_contains(xid));
  require(xhost.points().d_cells_contains(xother_id));

  // Can't merge two tree vertices.

  require(!(xhost.vertices().contains(xid) && xhost.vertices().contains(xother_id)));

  // Should never merge a centroid or a truncation mid point.

  require(!xhost.centroids().contains(xid));
  require(!xhost.truncation_mid_points().contains(xid));
  require(!xhost.centroids().contains(xother_id));
  require(!xhost.truncation_mid_points().contains(xother_id));
  
  
  define_old_variable(scoped_index old_xother_id = xother_id);
  define_old_variable(scoped_index old_xid = xid);
  
  // Body:

  // Can't merge tree vertices into contents vertices.
  // Pick the tree vertex, if neither is a tree vertex, pick xid.

  scoped_index lsrc_id;
  scoped_index ldst_id;

  bool result = !xhost.vertices().contains(xid);
  
  if(result)
  {
    // xid is not a tree vertex; it is the source..
    
    lsrc_id = xid;
    ldst_id = xother_id;
  }
  else
  {
    // xid is a tree vertex; it is the destination..
    
    lsrc_id = xother_id;
    ldst_id = xid;
  }  

  // cout << "merging " << lsrc_id.pod() << " into " << ldst_id.pod() << endl;

  base_space_poset& lbase = xhost.base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(UPPER, lsrc_id);
  while(!litr.is_done())
  {
    lbase.replace_cover_member(lsrc_id, ldst_id, LOWER, litr.hub_pod());
    lbase.insert_cover_member(litr.hub_pod(), UPPER, ldst_id);
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);
  
  lbase.clear_cover(UPPER, lsrc_id);

  if(xhost.intersection_points().contains(lsrc_id))
  {
    xhost.intersection_points().insert_member(ldst_id);
  }

  if(xhost.truncation_points().contains(lsrc_id))
  {
    xhost.truncation_points().insert_member(ldst_id);
  }

  if(xhost.edge_points().contains(lsrc_id))
  {
    xhost.edge_points().insert_member(ldst_id);
  }

  deactivate(xhost, lsrc_id);

  xid = ldst_id;
  xother_id = ldst_id;
  
  // Postconditions:
  
  ensure(xid == xother_id);
  ensure(result ? (xid == old_xother_id) : (xid == old_xid));
  ensure(unexecutable("postcondition_of(deactivate(xhost, source))"));
  
  
  // Exit:

  // cout << "Leaving kd_point::merge." << endl;
  return result;
}

void
geometry::kd_point::
deactivate()
{
  // cout << endl << "Entering kd_point::deactivate." << endl;

  // Preconditions:

  require(precondition_of(deactivate(host(), id())));

  // Body:

  deactivate(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(deactivate(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::deactivate." << endl;
  return;
}

void
geometry::kd_point::
deactivate(kd_lattice& xhost, scoped_index& xid)
{
  // cout << endl << "Entering kd_point::deactivate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.base_space().vertices().contains_member(xid));
  ensure(xhost.base_space().cover_is_empty(UPPER, xid));

  // Body:

  // @hack This routine would be unnecessary if the various 
  // point and vertex cohorts were properly structured, that is
  // if they were all included in a single vertex cohort.

  xhost.intersection_points().remove_member(xid);
  xhost.truncation_points().remove_member(xid);
  xhost.edge_points().remove_member(xid);

  if(xhost.vertices().contains(xid))
  {
    xhost.vertices().delete_member(xid);
  }

  if(xhost.points().contains(xid))
  {
    xhost.points().delete_member(xid);
  }
  
  // Postconditions:

  ensure(!xhost.vertices().is_active(xid));
  ensure(!xhost.points().is_active(xid));
  ensure(!xhost.intersection_points().contains(xid));
  ensure(!xhost.truncation_points().contains(xid));
  ensure(!xhost.edge_points().contains(xid));
  
  // Exit:

  // cout << "Leaving kd_point::deactivate." << endl;
  return;
}

bool
geometry::kd_point::
is_first() const
{
  // cout << endl << "Entering kd_point::is_first." << endl;

  // Preconditions:

  require(precondition_of(is_first(host(), id())));

  // Body:

  bool result = is_first(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_first(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::is_first." << endl;
  return result;
}

bool
geometry::kd_point::
is_first(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_point::is_first." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  // Search for first segments in the upper cover of the point.

  bool result = false;
  
  const base_space_poset& lbase = xhost.base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(lbase.member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.first_segments().contains(lid))
    {
      if(xid == kd_segment::point(xhost, lid, 0))
      {
        // xid is the first point of a first segment.

        result = true;
        break;
      }
    }
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);
  
  // Postconditions:

  
  // Exit:

  // cout << "Leaving kd_point::is_first." << endl;
  return result;
}

bool
geometry::kd_point::
is_last() const
{
  // cout << endl << "Entering kd_point::is_last." << endl;

  // Preconditions:

  require(precondition_of(is_last(host(), id())));

  // Body:

  bool result = is_last(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_last(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::is_last." << endl;
  return result;
}

bool
geometry::kd_point::
is_last(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_point::is_last." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  // Search for last segments in the upper cover of the point.

  bool result = false;
  
  const base_space_poset& lbase = xhost.base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(lbase.member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.last_segments().contains(lid))
    {
      if(xid == kd_segment::point(xhost, lid, 1))
      {
        // xid is the second point of a last segment.

        result = true;
        break;
      }
    }
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);
  
  // Postconditions:

  
  // Exit:

  // cout << "Leaving kd_point::is_last." << endl;
  return result;
}

bool
geometry::kd_point::
is_intersection() const
{
  // cout << endl << "Entering kd_point::is_intersection." << endl;

  // Preconditions:

  require(precondition_of(is_intersection(host(), id())));

  // Body:

  bool result = is_intersection(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_intersection(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::is_intersection." << endl;
  return result;
}

bool
geometry::kd_point::
is_intersection(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_point::is_intersection." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  id_list llines;
  lines(xhost, xid, llines);
  
  bool result = llines.size() > 1;
  
  // Postconditions:

  
  // Exit:

  // cout << "Leaving kd_point::is_intersection." << endl;
  return result;
}

bool
geometry::kd_point::
is_truncation() const
{
  // cout << endl << "Entering kd_point::is_truncation." << endl;

  // Preconditions:

  require(precondition_of(is_truncation(host(), id())));

  // Body:

  bool result = is_truncation(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_truncation(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::is_truncation." << endl;
  return result;
}

bool
geometry::kd_point::
is_truncation(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_point::is_truncation." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  id_list lsurfs;
  surfaces(xhost, xid, lsurfs);

  /// @error Definition of truncation point. Defining truncation point
  /// by number of containing surfaces > 1 doesn't capture self truncation points.
  
  bool result = lsurfs.size() > 1;
  
  // Postconditions:

  
  // Exit:

  // cout << "Leaving kd_point::is_truncation." << endl;
  return result;
}

bool
geometry::kd_point::
is_truncation_reversal() const
{
  // cout << endl << "Entering kd_point::is_truncation_reversal." << endl;

  // Preconditions:

  require(precondition_of(is_truncation_reversal(host(), id())));

  // Body:

  bool result = is_truncation_reversal(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_truncation_reversal(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::is_truncation_reversal." << endl;
  return result;
}

bool
geometry::kd_point::
is_truncation_reversal(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_point::is_truncation_reversal." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  /// @error pd_point::is_truncation_reversal implemented using
  /// kd_lattice::truncation_reversal_points(), but it is
  /// intended for use updating truncation_reversal_points,
  /// see kd_point::update_cohorts. We can get away with this
  /// only because update_cohrts is call only from kd_line::clear
  /// and lines never contain truncation reversal points.

  bool result = xhost.truncation_reversal_points().contains(xid);    

  // Postconditions:

  
  // Exit:

  // cout << "Leaving kd_point::is_truncation_reversal." << endl;
  return result;
}

void
geometry::kd_point::
update_cohorts()
{
  // cout << endl << "Entering kd_point::update_cohorts." << endl;

  // Preconditions:

  require(precondition_of(update_cohorts(host(), id())));

  // Body:

  update_cohorts(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(update_cohorts(host(), id())));

  // Exit:

  // cout << "Leaving kd_point::update_cohorts." << endl;
  return;
}

void
geometry::kd_point::
update_cohorts(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_point::update_cohorts." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().vertices().contains_member(xid));

  // Body:

  if(xhost.intersection_points().contains(xid))
  {
    if(!kd_point::is_intersection(xhost, xid))
    {
      xhost.intersection_points().remove_member(xid);
    }
  }

  if(xhost.truncation_points().contains(xid))
  {
    if(!kd_point::is_truncation(xhost, xid))
    {
      xhost.truncation_points().remove_member(xid);
    }
  }

  if(xhost.truncation_reversal_points().contains(xid))
  {
    /// @error: see is_truncation_reversal.
    if(!kd_point::is_truncation_reversal(xhost, xid))
    {
      xhost.truncation_reversal_points().remove_member(xid);
    }
  }

  
  // Postconditions:

  
  // Exit:

  // cout << "Leaving kd_point::update_cohorts." << endl;
  return;
}

void
geometry::kd_point::
lines(id_list& xresult) const
{
  // cout << endl << "Entering kd_point::lines." << endl;

  // Preconditions:

  require(precondition_of(lines(host(), id(), xresult)));
  
  // Body:

  lines(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(lines(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::lines." << endl;
  return;
}

void
geometry::kd_point::
lines(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_point::lines." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  scoped_index lid;

  index_space_iterator& ls_itr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  scoped_index ls_id(xhost.base_space().member_id(false));
  while(!ls_itr.is_done())
  {
    ls_id = ls_itr.hub_pod();

    if(xhost.segments().contains(ls_id))
    {
      kd_segment::line(xhost, ls_id, lid);

      bool lnew_line = true;
      for(id_list::iterator i=xresult.begin(); i!=xresult.end(); ++i)
      {
        if(lid == *i)
        {
          lnew_line = false;
          break;
        }
      }
      if(lnew_line)
      {
        xresult.push_back(lid);
      }
    }
    
    ls_itr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(ls_itr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_point::lines." << endl;
  return;
}

void
geometry::kd_point::
surfaces(id_list& xresult) const
{
  // cout << endl << "Entering kd_point::surfaces." << endl;

  // Preconditions:

  require(precondition_of(surfaces(host(), id(), xresult)));
  
  // Body:

  surfaces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(surfaces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::surfaces." << endl;
  return;
}

void
geometry::kd_point::
surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_point::surfaces." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // Search the up set of this point for surfaces.
  // Note that truncation midpoints are only included
  // in trinagles, so we can't assume the upper cover
  // contains segments and look for lines etc.

  
  base_space_member lmbr(&xhost.base_space(), xid);

  set_preorder_itr litr(lmbr, &xhost.surfaces().sp(), UP);
  while(!litr.is_done())
  {
    xresult.push_back(litr.index());
    
    // No need to look higher up the graph.

    litr.truncate();
  }

  lmbr.detach_from_state();
  
  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_point::surfaces." << endl;
  return;
}

void
geometry::kd_point::
triangles(id_list& xresult) const
{
  // cout << endl << "Entering kd_point::triangles." << endl;

  // Preconditions:

  require(precondition_of(triangles(host(), id(), xresult)));
  
  // Body:

  triangles(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(triangles(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::triangles." << endl;
  return;
}

void
geometry::kd_point::
triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_point::triangles." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().d_cells_is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(lbase.member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.triangles().contains(lid))
    {
      xresult.push_back(lid);
    }
    
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_point::triangles." << endl;
  return;
}

void
geometry::kd_point::
segments(id_list& xresult) const
{
  // cout << endl << "Entering kd_point::segments." << endl;

  // Preconditions:

  require(precondition_of(segments(host(), id(), xresult)));
  
  // Body:

  segments(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(segments(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::segments." << endl;
  return;
}

void
geometry::kd_point::
segments(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_point::segments." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(lbase.member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.segments().contains(lid))
    {
      xresult.push_back(lid);
    }
    
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_point::segments." << endl;
  return;
}

void
geometry::kd_point::
faces(id_set& xresult) const
{
  // cout << endl << "Entering kd_point::faces." << endl;

  // Preconditions:

  require(precondition_of(faces(host(), id(), xresult)));
  
  // Body:

  faces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(faces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::faces." << endl;
  return;
}

void
geometry::kd_point::
faces(const kd_lattice& xhost, const scoped_index& xid, id_set& xresult)
{
  // cout << endl << "Entering kd_point::faces." << endl;
  // cout << xid << "  " << name(xhost, xid) << endl;
  // cout << "xresult: " << xresult << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  scoped_index lface_id;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    if(xhost.segments().contains(lid))
    {
      kd_segment::face(xhost, lid, lface_id);

      xresult.insert(lface_id);
    }
    
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // cout << "xresult: " << xresult << endl;

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  
  // Exit:

  // cout << "Leaving kd_point::faces." << endl;
  return;
}

bool
geometry::kd_point::
same_face(const scoped_index& xother_id) const
{
  // cout << endl << "Entering kd_point::same_face." << endl;

  // Preconditions:

  require(precondition_of(same_face(host(), id(), xother_id)));
  
  // Body:

  bool result = same_face(host(), id(), xother_id);
  
  // Postconditions:

  ensure(postcondition_of(same_face(host(), id(), xother_id)));

  // Exit:

  // cout << "Leaving kd_point::same_face." << endl;
  return result;
}

bool
geometry::kd_point::
same_face(const kd_lattice& xhost, const scoped_index& xid, const scoped_index& xother_id)
{
  // cout << endl << "Entering kd_point::same_face." << endl;
  // cout << xid << "  " << name(xhost, xid) << endl;
  // cout << xother_id  << "  " << name(xhost, xother_id) << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));
  require(xhost.points().is_active(xother_id));

  // Body:

  id_set lfaces;
  faces(xhost, xid, lfaces);
  
  id_set lother_faces;
  faces(xhost, xother_id, lother_faces);
  
  id_set lcommon_faces;
  insert_iterator<id_set> litr(lcommon_faces, lcommon_faces.end());
  
  set_intersection(lfaces.begin(), lfaces.end(), lother_faces.begin(), lother_faces.end(), litr);
  
  bool result = !lcommon_faces.empty();
  
  // Postconditions:

  // Exit:

  // cout << "Leaving kd_point::same_face." << endl;
  return result;
}


// void
// geometry::kd_point::
// intersect_surfaces(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, frag_list& xfrags)
// {
//   // cout << endl << "Entering kd_point::intersect_surfaces." << endl;

//   // Preconditions:

//   require(xhost.base_space().in_jim_edit_mode());
//   require(xhost.points().contains(xid));

//   // Body:

//   base_space_poset& lbase = xhost.base_space();
//   cover_set_iterator lv_itr;

//   // Subtasks:
//   // Find the triangle containing this point.
//   // While triangle found at not a opposite edge of face.
//   //   compute the intersection of the plane with the triangle.
//   //   find the adjacent triangle at the other end of the intersection

//   // $$SCRIBBLE: not clear how much we want to do here.
//   // Much of the intersection algorithm belongs in kd_face.
//   // maybe just find the triangle? Find the opposing intersection pt?

//   // Postconditions:


//   // Exit:

//   // cout << "Leaving kd_point::intersect_surfaces." << endl;
//   return;
// }

// PROTECTED MEMBER FUNCTIONS

geometry::kd_point::
kd_point()
{
  
  // Preconditions:

    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}


// PRIVATE MEMBER FUNCTIONS

void
geometry::kd_point::
truncated_surfaces(id_list& xresult) const
{
  // cout << endl << "Entering kd_point::truncated_surfaces." << endl;

  // Preconditions:

  require(precondition_of(truncated_surfaces(host(), id(), xresult)));
  
  // Body:

  truncated_surfaces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(truncated_surfaces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::truncated_surfaces." << endl;
  return;
}

void
geometry::kd_point::
truncated_surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_point::truncated_surfaces." << endl;
  // cout << "point: " << xid.pod() << "  " << name(xhost, xid) << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));
  require(xhost.truncation_points().contains(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // Search for end segments in the upper cover of the point.

  scoped_index lsurf_id;
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lsurf_id.invalidate();
    lid = litr.hub_pod();
    
    // cout << "examining segment: " << litr.item().pod() << "  " << name(xhost, litr.item()) << endl;

    if(xhost.first_segments().contains(lid))
    {
      // cout << "is a first segment" << endl;
      
      if(xid == kd_segment::point(xhost, lid, 0))
      {
        // Xid is the first point of a first segment;
        // the surface containing this segment is 
        // truncated at this point
        
        // cout << "is first point" << endl;
        
        kd_segment::surface(xhost, lid, lsurf_id);
      }
      else
      {
        // cout << "not first point" << endl;
      }
      
    }
    else if(xhost.last_segments().contains(lid))
    {
      // cout << "is a last segment" << endl;

      if(xid == kd_segment::point(xhost, lid, 1))
      {
        // Xid is the last point of a last segment;
        // the surface containing this segment is 
        // truncated at this point

        // cout << "is last point" << endl;

        kd_segment::surface(xhost, lid, lsurf_id);
      }
      {
        // cout << "not last point" << endl;
      }
    }
    else
    {
      // cout << "not an end segment" << endl;
    }

    if(lsurf_id.is_valid())
    {
      // Make sure no surface gets inserted more than once;
      // there should only be one or two entries,
      // so linear search is efficent enough.

      bool lnew_surf = true;
      for(id_list::iterator i=xresult.begin(); i!=xresult.end(); ++i)
      {
        if(lsurf_id == *i)
        {
          lnew_surf = false;
          break;
        }
      }
      if(lnew_surf)
      {
        // cout << "insert surface in result" << endl;
        
        xresult.push_back(lsurf_id);
      }
    }

    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_point::truncated_surfaces." << endl;
  return;
}

void
geometry::kd_point::
truncating_surfaces(id_list& xresult) const
{
  // cout << endl << "Entering kd_point::truncating_surfaces." << endl;

  // Preconditions:

  require(precondition_of(truncating_surfaces(host(), id(), xresult)));
  
  // Body:

  truncating_surfaces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(truncating_surfaces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_point::truncating_surfaces." << endl;
  return;
}

void
geometry::kd_point::
truncating_surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_point::truncating_surfaces." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.points().is_active(xid));
  require(xhost.truncation_points().contains(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // Search for end segments in the upper cover of the point.

  scoped_index lsurf_id;
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  scoped_index lid(xhost.base_space().member_id(false));
  while(!litr.is_done())
  {
    lsurf_id.invalidate();
    lid = litr.hub_pod();
    
    // cout << "examining segment: " << litr.item().pod() << "  " << name(xhost, litr.item()) << endl;

    if(xhost.first_segments().contains(lid))
    {
      // cout << "is a first segment" << endl;
      
      if(xid == kd_segment::point(xhost, lid, 0))
      {
        // Xid is the first point of a first segment;
        // the surface containing this segment is 
        // truncated at this point
        
        // cout << "is first point" << endl;
      }
      else
      {
        // cout << "not first point" << endl;
        
        kd_segment::surface(xhost, lid, lsurf_id);
      }
      
    }
    else if(xhost.last_segments().contains(lid))
    {
      // cout << "is a last segment" << endl;

      if(xid == kd_segment::point(xhost, lid, 1))
      {
        // Xid is the last point of a last segment;
        // the surface containing this segment is 
        // truncated at this point

        // cout << "is last point" << endl;
      }
      {
        // cout << "not last point" << endl;

        kd_segment::surface(xhost, lid, lsurf_id);
      }
    }
    else if(xhost.segments().contains(lid))
    {
      // cout << "not an end segment" << endl;

      kd_segment::surface(xhost, lid, lsurf_id);
    }
    

    if(lsurf_id.is_valid())
    {
      // Make sure no surface gets inserted more than once;
      // there should only be one or two entries,
      // so linear search is efficent enough.

      bool lnew_surf = true;
      for(id_list::iterator i=xresult.begin(); i!=xresult.end(); ++i)
      {
        if(lsurf_id == *i)
        {
          lnew_surf = false;
          break;
        }
      }
      if(lnew_surf)
      {
        // cout << "insert surface in result" << endl;
        
        xresult.push_back(lsurf_id);
      }
    }

    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_point::truncating_surfaces." << endl;
  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_point::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_point*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_point*
geometry::kd_point::
clone() const
{
  kd_point* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_point();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_point&
geometry::kd_point::
operator=(const kd_point& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_point&
geometry::kd_point::
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
geometry::kd_point::
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
operator << (ostream& xos, const kd_point& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());
  

  // Body:

  xos << "point " << xn.host().points().id_space().pod(xn.id());
  xos << "  top id: " << xn.id();
  xos << "  name: " << xn.name();
  xos << "  type: " << xn.type_name();
  xos << boolalpha;
  xos << "  is_jim: " << xn.is_jim();
  xos << "  is_leaf: " << xn.is_leaf();
  xos << noboolalpha;
  xos << "  coordinates: " << xn.coords();
  xos << endl;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_point& xn, bool xinclude_shallow)
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
