// $RCSfile: kd_face.cc,v $ $Revision: 1.7 $ $Date: 2013/03/13 00:58:59 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_face

#include "kd_face.h"

#include "assert_contract.h"
#include "cohort.h"
#include "e3.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_bounding_box.h"
#include "kd_edge.h"
#include "kd_face_cohort.h"
#include "kd_lattice.h"
#include "kd_line.h"
#include "kd_line_fragment.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_segment.h"
#include "kd_triangle.h"
#include "kd_zone_cohort.h"
#include "sec_e3.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;
using namespace fiber_bundle::ed_algebra;

// namespace
// {

typedef kd_face::line_pt line_pt;
typedef kd_face::line_list line_list;

//
// The action to be taken for an intersection.
//
enum intersection_action 
{
  EXTEND0, SNAP0, REFINE, SNAP1, EXTEND1, IGNORE
};

 
ostream& operator << (ostream& xos, const intersection_action& xn)
{
  // Preconditions:

  // Body:

  static const string laction[] =
    {
      "EXTEND0", "SNAP0", "REFINE", "SNAP1", "EXTEND1", "IGNORE"
    };

  xos << laction[xn];

  // Postconditions:

  // Exit:

  return xos;
}




//
// Computes action to be taken for an intersection at local coordinate xu
// and with local coordinate snapping tolerance xtolerance for a segment.
// The segment is treated as the first segment is a line if xis_first
// and the last segment is xis_last. The first point in the segment
// is treated as constrained by a previous intersection if xis_truncation0
// is true and similarly for the second point and xis_truncation1.
//
intersection_action compute_intersection_action(vd_value_type xu, 
                                                vd_value_type xtolerance, 
                                                bool xis_first, 
                                                bool xis_last, 
                                                bool xis_constrained0, 
                                                bool xis_constrained1)
{
  // cout << endl << "Entering kd_face:compute_intersection_action" << endl;
  
  // Preconditions:

  // Body:

  // $$SCRIBBLE: ERROR: insersect_segment is computing and passing [0.0, 1.0] for
  // s, t but this routine expects [-1.0, 1.0].
  
  //   const double lfirst_vertex = -1.0;
  //   const double lsecond_vertex = 1.0;
  //   const double lmid_pt = 0.0;
  const double lfirst_vertex = 0.0;
  const double lsecond_vertex = 1.0;
  const double lmid_pt = 0.5;
  intersection_action result;
  

  // Snapping logic:
  //
  // The basic idea is that if the intersection is closer to an
  // existing vertex than some threshhold, the snapping distance, then
  // creating a new vertex at the intersection will creating a line
  // segment that is too short and subsequently create long narrow
  // triangles. To avoid this case, instead of creating a new vertex,
  // we can move (snap) an existing vertex to the intersection. At
  // first glance, the condition for snapping should be:
  //
  // | intersection position - vertex position | < snap distance
  //
  // Since there are two vertices, the above condition is actually
  // two conditions:
  // 
  // (lfirst_vertex - lsnap) < xu < (lfirst_vertex + lsnap) or 
  // (second_vertex - lsnap) < xu < (lsecond_vertex + lsnap)
  //
  // However, we have to account for the possibility that these two
  // intervals overlap; i.e. if lsnap > llen/2.0.  Even worse is the
  // case in which lsnap > llen, in which case the intervals overlap
  // entirely. In either case we have to make sure the vertex that is
  // closest to the intersection is the one that snaps. This is ensured
  // by the conditions:
  // 
  // (lfirst_vertex - lsnap) < xu < min(lfirst_vertex + lsnap, lmid_pt) and 
  // max(second_vertex - lsnap, lmid_pt) < xu < (lsecond_vertex + lsnap)
  //
  // These conditions need to be further modified to account for
  // the asymmetry between the first and second vertex and between
  // first, last, and other line segments. Since the second vertex
  // on one segment may be the first vertex of the next segment,
  // we have to decide which segment the intersection will be
  // associated with. We use the convention that the intersection is
  // always associated with the second segment. So for a first segment
  // the conditions become:
  // 
  // (lfirst_vertex - lsnap) < xu < min(lfirst_vertex + lsnap, lmid_pt) or 
  // max(second_vertex - lsnap, lmid_pt) <= xu
  //
  // For a last segment:
  // 
  // xu < min(lfirst_vertex + lsnap, lmid_pt) or 
  // max(second_vertex - lsnap, lmid_pt) < xu <= (lsecond_vertex + lsnap)
  // 
  // and for an other (internal) segment:
  // 
  // xu < min(lfirst_vertex + lsnap, lmid_pt) or 
  // max(second_vertex - lsnap, lmid_pt) <= xu
  //
  // In this version of compute_intersection_action,
  // we force snap distance == xtolerance.

  
  /// @issue Snapping a vertex which is already an intersection.
  /// In determining the action to be taken with a new intersection,
  /// we are always free to refine or extend the current segment,
  /// doing so does not violate the constraints associated with the
  /// existing vertices, but may introduce arbitrarily short segemnts.
  /// Hence we may wish to merge (snap) the intersection with an existing vertex.
  ///
  /// If the existing vertex is already an intersection, then it is constrained
  /// to lie in the meet of at least 2 planes, call them plane A and B.
  /// If the current intersection is a truncation, then it is only
  /// constrained to lie in one of these planes, say plane A.
  /// In this case, we can not snap the vertex to the intersection,
  /// but we can snap the intersection to the vertex, or we can
  /// move both the intersection and the vertex within A meet B.
  /// If the current intersection is not a truncation, then it 
  /// is constrained to lie in the meet of A or B with a third
  /// plane C, the only thing we can do is snap both the intersection
  /// and the vertex to A meet B meet C.
  ///
  /// If the existing vertex was already constrained to lie in 
  /// the intersection of 3 planes, it can not be moved at all.
  /// If the current intersection is a truncation, we can only snap
  /// the intersecton to the vertex. If the current intersection 
  /// is not a truncation, we can not snap at all, we must refine.
  ///
  /// For the time being, we treat every existing vertex as being
  /// either dimension 2 (not an intersection, constrained only
  /// to its original input plane) or dimension 0 (an intersection
  /// and fully constrained). If it turns out to be important in
  /// practice, we can add the machinery to deal with the dimension
  /// of the contraint correctly.
  
  if(xis_first)
  {
    // First segment in line.

    // (ignore] u0 (snap0 | extend0) u1 [snap0 or refine) u2 [refine] u3 (snap1] u4 (ignore)
    // u0 = lfirst_vertex - xtolerance
    // u1 = lfirst_vertex
    // u2 = min(lfirst_vertex + xtolerance, lmid_pt)
    // u3 = max(lsecond_vertex - xtolerance, lmid_pt)
    // u4 = lsecond_vertex

    if((xu <= lfirst_vertex - xtolerance) || (xu > lsecond_vertex))
    {
      // Intersection is not in (lfirst_vertex - xtolerance, lsecond_vertex]
      // intersection is exterior, not a truncation.

      result = IGNORE;
    }
    else 
    {
      // Intersection is in (lfirst_vertex - xtolerance, lsecond_vertex]
      // we can't ignore it.

      if(xu < lfirst_vertex)
      {
        // Intersection in (lfirst_vertex - xtolerance, lfirst_vertex);
        // first vertex snaps to intersection unless it is already
        // an intersection, in which case it extends.
        // This segment truncates.

        result = xis_constrained0 ? EXTEND0 : SNAP0;
      }
      if(xu < min(lfirst_vertex + xtolerance, lmid_pt))
      {
        // Intersection in (lfirst_vertex, min(lfirst_vertex + xtolerance, lmid_pt);
        // first vertex snaps to intersection unless it is already
        // an intersection, in which case it refines.
        // This segment truncates.

        result = xis_constrained0 ? REFINE : SNAP0;
      }
      else if(xu <= max(lsecond_vertex - xtolerance, lmid_pt))
      {
        // Intersection in [min(lfirst_vertex + xtolerance, lmid_pt), max(lsecond_vertex - xtolerance, lmid_pt)];
        // this segment refines; other segment truncates

        result = REFINE;
      }
      else
      {
         // Intersection in (max(lsecond_vertex - xtolerance, lmid_pt), lsecond_vertex];
        // second vertex snaps to intersection unless it is already
        // an intersection, in which case it refines; other segment truncates.
        // Note that if intersection precisely matches a vertex,
        // it matches the second vertex of the incoming segment, 
        // not the first vertex of the outgoing segment.

        result = xis_constrained1 ? REFINE : SNAP1;
      }
    }       
  }
  else if(xis_last)
  {
    // Last segment in line.
    
    // (ignore] u0  (snap0 or refine) u1 [refine] u2 (snap1 or refine) u3 [snap1 or extend] u4 (ignore)
    // u0 = lfirst_vertex
    // u1 = min(lfirst_vertex + xtolerance, lmid_pt)
    // u2 = max(lsecond_vertex - xtolerance, lmid_pt)
    // u3 = lsecond_vertex
    // u4 = lsecond_vertex + xtolerance

    if((xu <= lfirst_vertex) || (xu > lsecond_vertex + xtolerance))
    {
      // Intersection is not in (lfirst_vertex, lsecond_vertex + xtolerance]
      // intersection is exterior, not a truncation.
      // Note that if intersection precisely matches a vertex,
      // it matches the second vertex of the incoming segment, 
      // not the first vertex of the outgoing segment.

      result = IGNORE;
    }
    else 
    {
      // Intersection is in (lfirst_vertex, lsecond_vertex + xtolerance],
      // we can't ignore it.

      if(xu < min(lfirst_vertex + xtolerance, lmid_pt))
      {
        // Intersection in (lfirst_vertex, min(lfirst_vertex + xtolerance, lmid_pt));
        // first vertex snaps to intersection unless it is already
        // an intersection, in which case it refines; other segment truncates.

        result = xis_constrained0 ? REFINE : SNAP0;
      }
      else if(xu <= max(lsecond_vertex - xtolerance, lmid_pt))
      {
        // Intersection in [min(lfirst_vertex + xtolerance, lmid_pt), max(lsecond_vertex - xtolerance, lmid_pt)];
        // this segment refines; other segment truncates

        result = REFINE;
      }
      else if(xu < lsecond_vertex)
      {
        // Intersection in (max(lsecond_vertex - xtolerance, lmid_pt), lsecond_vertex);
        // second vertex snaps to intersection unless it is already
        // an intersection, in which case it refines; other segment truncates.

        result = xis_constrained1 ? REFINE : SNAP1;
      }
      else
      {
        // Intersection in [lsecond_vertex, lsecond_vertex + xtolerance]
        // second vertex snaps to intersection unless it is already
        // an intersection, in which case it extends; other segment truncates.

        result = xis_constrained1 ? EXTEND1 : SNAP1;
      }
    }
  }
  else
  {
    // Neither first nor last segment in line.
    
    // (ignore] u0  (snap0 or refine) u1 [refine] u2 (snap1 or refine] u3 (ignore)
    // u0 = lfirst_vertex
    // u1 = lfirst_vertex + intersect
    // u2 = lsecond_vertex - intersect
    // u3 = lsecond_vertex

    if((xu <= lfirst_vertex) || (xu > lsecond_vertex))
    {
      // Intersection not in (lfirst_vertex, lsecond_vertex];
      // intersection is exterior, not a truncation.
      // Note that if intersection precisely matches a vertex,
      // it matches the second vertex of the incoming segment, 
      // not the first vertex of the outgoing segment.

      result = IGNORE;
    }
    else 
    {
      // Intersection in (lfirst_vertex, lsecond_vertex];
      // we can't ignore it.

      if(xu < min(lfirst_vertex + xtolerance, lmid_pt))
      {
        // Intersection in (lfirst_vertex, min(lfirst_vertex + xtolerance, lmid_pt));
        // first vertex snaps to intersection unless it is already
        // an intersection, in which case it refines; other segment truncates.

        // cout << "refine or snap0" << endl;
        

        result = xis_constrained0 ? REFINE : SNAP0;
      }
      else if(xu <= max(lsecond_vertex - xtolerance, lmid_pt))
      {
        // Intersection in [min(lsecond_vertex + xtolerance, lmid_pt), max(lsecond_vertex - xtolerance, lmid_pt)];
        // this segment refines; other segment truncates

        // cout << "refine" << endl;
        result = REFINE;
      }
      else
      {
         // Intersection in (lsecond_vertex - lsnap, lsecond_vertex];
        // second vertex snaps to intersection unless it is already
        // an intersection, in which case it refines; other segment truncates.
        // Note that if intersection precisely matches a vertex,
        // it matches the second vertex of the incoming segment, 
        // not the first vertex of the outgoing segment.

        // cout << "refine or snap1" << endl;
        result = xis_constrained1 ? REFINE : SNAP1;
      }
    }
    
  }  

  // cout << "result: " << result;
  // cout << boolalpha;
  // cout << " is_first: " << xis_first;
  // cout << " is_last: " << xis_last;
  // cout << " is_trunc0: " << xis_constrained0;
  // cout << " is_trunc1: " << xis_constrained1;
  // cout << noboolalpha;
  // cout << " xu: " << xu;
  // cout << " xtolerance: " << xtolerance;
  // cout << endl;
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face:compute_intersection_action" << endl << endl;
  return result;
}

//
// Creates the segment specified by xline_mbrs.back() and xline.front()
// and inserts it in xline_mbrs..
//
void create_segment(kd_lattice& xhost, id_list& xline_mbrs, line_list& xline)
{
  // cout << endl << "Entering kd_face.cc::create_segment." << endl;
  // cout << "line mbrs: " << xline_mbrs << endl;
  // cout << "line_list: " << endl << xline << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());

  require(!xline_mbrs.empty());
  require(xline_mbrs.back().is_valid());
  require(xhost.base_space().vertices().contains_member(xline_mbrs.back()));

  require(!xline.empty());
  require(xline.front().pt_id.is_valid());
  require(xhost.base_space().vertices().contains_member(xline.front().pt_id));
  
  require(xline_mbrs.back() != xline.front().pt_id);

  // Body::

  // Create the segment.

  scoped_index lseg_id = kd_segment::new_segment(xhost, xline_mbrs.back(), xline.front().pt_id);

  // cout << "create segment: " << lseg_id.internal_pod();
  // cout << " vertices ";
  // cout << xline_mbrs.back().internal_pod();
  // cout << " " << xline.front().pt_id.internal_pod();
  // cout << endl;

  if((++xline_mbrs.begin()) == xline_mbrs.end())
  {
    xhost.first_segments().insert_member(lseg_id);
  }
  
  if((++xline.begin()) == xline.end())
  {
    xhost.last_segments().insert_member(lseg_id);
  }
    
  // Update the line members list.

  xline_mbrs.push_back(lseg_id);
  xline_mbrs.push_back(xline.front().pt_id);

  // Postconditions::

  ensure(xline_mbrs.back() == xline.front().pt_id);

  // Exit:

  // cout << "Leaving kd_face.cc::create_segment." << endl << endl;
  return;
}

//
// Executes the intersection actions specified by xAB_action and 
// xCD_action to create the intersection at xpt between the new segment
// CD specified by xpt0 and xline.front() and the existing segment
// AB with id xAB_id in in the face with id xid in kd_lattice xhost.
//
void create_intersection(kd_lattice& xhost,
                         const scoped_index& xid,
                         const index_space_iterator& xitr,
                         scoped_index xAB_pt_ids[],
                         intersection_action xAB_action,
                         line_pt& xptC,
                         line_list& xline,
                         intersection_action xCD_action,
                         line_pt& xpt)
{
  // cout << endl << "Entering kd_face.cc:create_intersection" << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.segments().contains(xitr.hub_pod()));  

  require(xhost.base_space().vertices().contains_member(xAB_pt_ids[0]));
  require(xhost.base_space().vertices().contains_member(xAB_pt_ids[1]));


  require(xptC.pt == kd_point::coords(xhost, xptC.pt_id));

  require(!xline.empty());
  require(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));

  define_old_variable(int old_xline_size = xline.size());
  
  // Body:

  // We have to determine when to create
  // a new point for the intersection and when to use
  // an existing point. If any of the 4 points
  // A, B, C, D which have already been created snap to
  // the intersection, then we don't need to create
  // a point. Furthermore, if two points snap, i.e. A or B
  // and C or D, then we have to replace C or D with A or B.

  const scoped_index& lAB_id = xhost.base_space().member_id(xitr.hub_pod(), false);

  // Segment CD is defined by
  // xptC and  lptD = xline.front().

  line_pt& lptD = xline.front();

  assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
  assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));

  // Handle the double snap and replacemnt cases first.

  if((xAB_action == SNAP0) && (xCD_action == SNAP0))
  {
    // ptA snaps to intersection.
    
    kd_point::snap(xhost, xAB_pt_ids[0], xpt.pt);

    xpt.pt_id = xAB_pt_ids[0];
    
    // ptC also snaps to intersection,
    // so ptC is replaced by ptA.

    if(xptC.pt_id != xpt.pt_id)
    {
      if(kd_point::merge(xhost, xptC.pt_id, xpt.pt_id))
      {
        // ptC merged into the intersection.

        xptC.pt = xpt.pt;
      }
      else
      {
        // The intersection merged into ptC.

        xpt.pt = xptC.pt;
      }
    }
    

    assertion(xptC.pt == xpt.pt);
    assertion(xptC.pt_id == xpt.pt_id);
    assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
    assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
    assertion(xpt.pt  == kd_point::coords(xhost, xpt.pt_id));
  }
  else if((xAB_action == SNAP0) && (xCD_action == SNAP1))
  {
    // ptA snaps to intersection.
    
    kd_point::snap(xhost, xAB_pt_ids[0], xpt.pt);
 
    xpt.pt_id = xAB_pt_ids[0];
    
    // ptD also snaps to intersection,
    // so ptD is replaced by ptA.

    if(lptD.pt_id != xpt.pt_id)
    {
      if(kd_point::merge(xhost, lptD.pt_id, xpt.pt_id))
      {
        // ptD merged into the intersection.

        lptD.pt = xpt.pt;
      }
      else
      {
        // The intersection merged into ptD.

        xpt.pt = lptD.pt;
      }
    }    

    assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
    assertion(lptD.pt == xpt.pt);
    assertion(lptD.pt_id == xpt.pt_id);
    assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
    assertion(xpt.pt == kd_point::coords(xhost, xpt.pt_id));
  }
  else if((xAB_action == SNAP1) && (xCD_action == SNAP0))
  {
    // ptB snaps to intersection.
    
    kd_point::snap(xhost, xAB_pt_ids[1], xpt.pt);

    xpt.pt_id = xAB_pt_ids[1];
    
    // ptC also snaps to intersection,
    // so ptC is replaced by ptA.

    if(xptC.pt_id != xpt.pt_id)
    {
      if(kd_point::merge(xhost, xptC.pt_id, xpt.pt_id))
      {
        // ptC merged into the intersection.

        xptC.pt = xpt.pt;
      }
      else
      {
        // The intersection merged into ptC.

        xpt.pt = xptC.pt;
      }    
    }
    
    assertion(xptC.pt == xpt.pt);
    assertion(xptC.pt_id == xpt.pt_id);
    assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
    assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
    assertion(xpt.pt == kd_point::coords(xhost, xpt.pt_id));
  }
  else if((xAB_action == SNAP1) && (xCD_action == SNAP1))
  {
    // ptB snaps to intersection.
    
    kd_point::snap(xhost, xAB_pt_ids[1], xpt.pt);

    xpt.pt_id = xAB_pt_ids[1];
    
    // ptD also snaps to intersection,
    // so ptD is replaced by ptA.

    if(lptD.pt_id != xpt.pt_id)
    {
      if(kd_point::merge(xhost, lptD.pt_id, xpt.pt_id))
      {
        // ptD merged into the intersection.

        lptD.pt = xpt.pt;
      }
      else
      {
        // The intersection merged into ptD.

        xpt.pt = lptD.pt;
      }
    }
    
    assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
    assertion(lptD.pt == xpt.pt);
    assertion(lptD.pt_id == xpt.pt_id);
    assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
    assertion(xpt.pt == kd_point::coords(xhost, xpt.pt_id));
  }
  else
  {
    // No double snap and replacement; check for single snap.
    // Since we've already dealt with the double snap
    // cases and SNAP0 and SNAP1 are mutally exclusive
    // for the same segment, only one snap is possible.

    if(xAB_action == SNAP0)
    {
      // ptA snaps to intersection.
    
      kd_point::snap(xhost, xAB_pt_ids[0], xpt.pt);

      xpt.pt_id = xAB_pt_ids[0];
    }
    else if(xAB_action == SNAP1)
    {
      // ptB snaps to intersection.
    
      kd_point::snap(xhost, xAB_pt_ids[1], xpt.pt);

      xpt.pt_id = xAB_pt_ids[1];
    }
    else if(xCD_action == SNAP0)
    {
      // ptC snaps to the intersection.

      kd_point::snap(xhost, xptC.pt_id, xpt.pt);

      xpt.pt_id = xptC.pt_id;

      xptC.pt = xpt.pt;

      assertion(xptC.pt == xpt.pt);
      assertion(xptC.pt_id == xpt.pt_id);
      assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
      assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
      assertion(xpt.pt == kd_point::coords(xhost, xpt.pt_id));
    }
    else if(xCD_action == SNAP1)
    {
      // ptD snaps to the intersection.

      kd_point::snap(xhost, lptD.pt_id, xpt.pt);

      xpt.pt_id = lptD.pt_id;

      lptD.pt = xpt.pt;

      assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
      assertion(lptD.pt == xpt.pt);
      assertion(lptD.pt_id == xpt.pt_id);
      assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
      assertion(xpt.pt == kd_point::coords(xhost, xpt.pt_id));
    }
    else
    {
      // No snapping; have to create the intersection point.

      xpt.pt_id = kd_point::new_point(xhost, xpt.pt);

      assertion(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
      assertion(lptD.pt == kd_point::coords(xhost, lptD.pt_id));
      assertion(xpt.pt == kd_point::coords(xhost, xpt.pt_id));
    }
    
    
    // Deal with the remaining cases.

    if(xAB_action == EXTEND0)
    {        
      // Segment AB extends by adding a segmemt before ptA.

      scoped_index lline_id = kd_segment::line(xhost, lAB_id);
      kd_line::push_front(xhost, lline_id, xpt.pt_id);
    }
    else if(xAB_action == REFINE)
    {
      // Segment AB refines by inserting the intersection point.

      scoped_index lnew_seg_id;
      kd_segment::refine(xhost, lAB_id, xpt.pt_id, lnew_seg_id);
    }
    else if(xAB_action == EXTEND1)
    {
      // Segment AB extends by adding a segmemt after ptB.

      scoped_index lline_id = kd_segment::line(xhost, lAB_id);
      kd_line::push_back(xhost, lline_id, xpt.pt_id);
    }

    if(xCD_action == EXTEND0)
    {
      // Segment CD extends by adding a segment before ptC,
      // giving xpt -> ptC -> ptD.
      // xpt, ptC will become the current segment,
      // ptC, ptD will be the next segment.

      // CD has to be the first segment in the new line,
      // so ptC has to be first point in new line.

      // $$SCRIBBLE how do we test this condition?

      // When we test ptC-ptD again, we don't want
      // to repeat all the tests we've already done,
      // we want to start with the next contents mbr.

      xptC.contents_itr = xitr;
      xptC.contents_itr.next();

      // Push ptC back onto xline.

      xline.push_front(xptC);
      
      // Now current segment is xpt -> ptC,
      // so xpt is the new ptC and old C is new D

      // cout << "setting " << xptC.pt_id.pod() << " to " << xpt.pt_id.pod() << endl;

      xptC.pt = xpt.pt;
      xptC.pt_id = xpt.pt_id;

      // Note that lptD, lptD.pt, and lptD.pt_id
      // still refer to old D, which now the second
      // member of xline, but it doesn't matteer,
      // we're finished.
    }
    else if(xCD_action == REFINE)
    {
      // Segment CD refines to ptC - xpt - ptD,

      // When we test xpt-ptD again, we don't want
      // to repeat all the tests we've already done,
      // we want to start with the next contents mbr.

      xpt.contents_itr = xitr;
      xpt.contents_itr.next();

      // Push xpt onto xline.

      xline.push_front(xpt);

      // Now current segment is ptC -> xpt.
    }
    else if(xCD_action == EXTEND1)
    {
      // Segment CD extends by adding a segment after ptD.
      // giving ptC -> ptD -> xpt.

      // CD has to be the last segment in the new line, so
      // ptD has to be the last point in new line.

      assertion(&xline.front() == &xline.back());
      
      // Put xpt on the back of the line.

      // xpt is the last point in the line,
      // so there's no segment following
      // it, force cover iterator is_done().

      xpt.contents_itr.force_is_done();
      xline.push_back(xpt);

      // ptD is unchanged, but set cover iterator
      // to start at the next contents member.

      lptD.contents_itr = xitr;
      lptD.contents_itr.next();
    }  
  } // end else no replacement

  // Postconditions:

  ensure(xptC.pt == kd_point::coords(xhost, xptC.pt_id));
  ensure(xline.size() >= old_xline_size);
  ensure(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));
  ensure(xpt.pt == kd_point::coords(xhost, xpt.pt_id));

  // Exit:

  // cout << "Leaving kd_face.cc:create_intersection" << endl << endl;
  return;
};

//
// Computes the intersection (truncation), if any, 
// between the new segment specified by xpt0 and xline.front() 
// and the existing segment with id xid, which lies in the face with id xid 
// in the plane with local coordinates xu_id, xv_id in kd_latice xhost.
// Returns true if found intersection, false otherwise.
//
bool intersect_segment(kd_lattice& xhost, 
                       const scoped_index& xid,
                       const index_space_iterator& xitr, 
                       int xu_id, 
                       int xv_id, 
                       line_pt& xpt0, 
                       line_list& xline,
                       bool xCD_is_first)
{
  // cout << endl << "Entering kd_face.cc:intersect_segment." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.segments().contains(xitr.hub_pod()));  

  require(xpt0.pt == kd_point::coords(xhost, xpt0.pt_id));
  require(unexecutable("out code of xpt0 == INSIDE"));

  require(!xline.empty());
  require(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));

  define_old_variable(int old_xline_size = xline.size());

  // Body:
  
  // Existing segment, AB

  scoped_index lAB_pt_ids[kd_segment::POINT_CT];
  e3_lite lAB_pts[kd_segment::POINT_CT];
  e3_lite& lptA = lAB_pts[0];
  e3_lite& lptB = lAB_pts[1];

  const scoped_index& lAB_id = xhost.base_space().member_id(xitr.hub_pod(), false);
  kd_segment::points(xhost, lAB_id, lAB_pt_ids, lAB_pts);  

  // cout << "AB: " << lAB_id.internal_pod();
  // cout << " vertices: " << lAB_pt_ids[0].internal_pod();
  // cout << "  " << lptA;
  // cout << " "  << lAB_pt_ids[1].internal_pod();
  // cout << " " << lptB;
  // cout << endl;

  // New segment, CD

  e3_lite& lptC = xpt0.pt;
  scoped_index& lptC_id = xpt0.pt_id;
  e3_lite& lptD = xline.front().pt;
  scoped_index& lptD_id = xline.front().pt_id;

  // cout << "CD: ";
  // cout << " vertices: " << lptC_id.internal_pod();
  // cout << "  " << lptC;
  // cout << "  " << lptD_id.internal_pod();
  // cout << "  " << lptD;
  // cout << endl;

  bool result = false;

  if((++xline.begin() == xline.end()) && (lptD_id == lAB_pt_ids[0]))
  {
    // PtD is the last point in the line,
    // which for closed lines is the same as
    // the first point, see kd_lattice::insert_line.
    // PtA is equal to ptD, so ptA has to be the
    // first point in the line; this is a closed
    // line, not an intersection. Do nothing.

    // cout << "Found line closure, no intersection." << endl;
  }
  else
  {
    // Check for intersection.

    // Equation for intersection:
    //
    // lptA + s*(lptB - lptA) = lptC + t*(lptD - lptC)
    //
    // rearrange:
    //
    // (lptB - lptA)*s + (lptC - lptD)*t = (lptC - lptA)
    //
    // xu_id component: a*s + b*t = e 
    // xv_id component: c*s + d*t = f
    //
    // Solve with Cramer's rule:
    //
    //  det = a*d - c*b
    //  s   = (e*d-f*b)/cdet;
    //  t   = (a*f-c*e)/cdet;
    //

    double a = lptB[xu_id] - lptA[xu_id];
    double b = lptC[xu_id] - lptD[xu_id];

    double c = lptB[xv_id] - lptA[xv_id];
    double d = lptC[xv_id] - lptD[xv_id];

    double ad = a*d;
    double cb = c*b;
  
    if(c_eql(ad, cb))
    {
      // Segments are parallel; they do not intersect.

      // cout << "Segments are parallel; no intersection." << endl;
    }
    else
    {
      // Segments are not parallel.

      // cout << "Segments are not parallel; compute intersection " << endl;

      // Compute the intersection in the local coordinate for CD.

      double cdet = ad - cb;

      double e = lptC[xu_id] - lptA[xu_id];
      double f = lptC[xv_id] - lptA[xv_id];

      double lt = (a*f-c*e)/cdet;

      // Compute the tolerance in local coordinates of CD.

      e3_lite lCD(lptD);
      lCD -= lptC;
      vd_value_type lCD_len = length(lCD);
      const e3_lite& ltrunc_tolerance = xhost.truncation_tolerance();
      vd_value_type ltolerance = max(ltrunc_tolerance[xu_id], ltrunc_tolerance[xv_id]);
      vd_value_type lCD_tol = lCD_len > 0.0 ? ltolerance/lCD_len : 0.0;

      // Compute the intersection action for the intersection in CD.

      bool lCD_is_last = (&xline.front() == &xline.back());
      bool lCD_is_constrained0 = 
        xhost.truncation_points().contains(lptC_id) || xhost.edge_points().contains(lptC_id);
      bool lCD_is_constrained1 = 
        lptD_id.is_valid() && (xhost.truncation_points().contains(lptD_id) || xhost.edge_points().contains(lptD_id));

      // cout << "lCD_action: ";
    
      intersection_action lCD_action = 
        compute_intersection_action(lt, lCD_tol, xCD_is_first, lCD_is_last, lCD_is_constrained0, lCD_is_constrained1);

      if(lCD_action != IGNORE)
      {  
        // Compute the intersection in the local coordinate for AB.

        double ls = (e*d-f*b)/cdet;

        // Compute the tolerance in local coordinates of AB.

        e3_lite lAB(lptB);
        lAB -= lptA;
        vd_value_type lAB_len = length(lAB);
        vd_value_type lAB_tol = lAB_len > 0.0 ? ltolerance/lAB_len : 0.0;

        // Compute the intersection action for the intersection in AB.

        bool lAB_is_first = xhost.first_segments().contains(lAB_id);
        bool lAB_is_last = xhost.last_segments().contains(lAB_id);
        bool lAB_is_constrained0 = 
          xhost.truncation_points().contains(lAB_pt_ids[0]) || xhost.edge_points().contains(lAB_pt_ids[0]);
        bool lAB_is_constrained1 = 
          xhost.truncation_points().contains(lAB_pt_ids[1]) || xhost.edge_points().contains(lAB_pt_ids[1]);

        // cout << "lAB_action: ";

        intersection_action lAB_action = 
          compute_intersection_action(ls, lAB_tol, lAB_is_first, lAB_is_last, lAB_is_constrained0, lAB_is_constrained1);
  

        if(lAB_action != IGNORE)
        {
          // Compute the intersection point in global coordinates;
          // lpt = lptA + ls*(lptB - lptA).

          line_pt lpt(lAB);
          lpt.pt *= ls;
          lpt.pt += lptA;

          // cout << "lptx: " << lpt << endl;

          // Create the intersection.

          create_intersection(xhost, xid, xitr, lAB_pt_ids, lAB_action, xpt0, xline, lCD_action, lpt);

          // We just created an intersection between
          // the current segment and an existing segment.
          // An intersection in a plane is a truncation
          // point, unless it is the self intersection
          // that closes a line.
          // The current line has not yet been created,
          // so if the existing segment is in any line,
          // it is a different line and we have a truncation.
        
          scoped_index lline_id;
	  scoped_index lAB_id = xhost.base_space().member_id(xitr.hub_pod(), false);
          kd_segment::line(xhost, lAB_id, lline_id);
          if(lline_id.is_valid())
          {
            // cout << "found truncation point: " << lpt.pt_id << endl;
            
            xhost.truncation_points().insert_member(lpt.pt_id);
          }

          result = true;
        } // end lAB_action != ignore
      } // end lCD_action != ignore  
    } // end segments not parallel.
  } // end closed line else

  // Postconditions:

  ensure(xpt0.pt == kd_point::coords(xhost, xpt0.pt_id));
  ensure(xline.size() >= old_xline_size);
  ensure(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));

  // Exit:

  // cout << "Leaving kd_face.cc:intersect_segment." << endl << endl;
  return result;
}

//
// Computes intersections and truncations, if any, between the new line segment 
// specified by xpt0 and xline.front() and the contents of the face 
// with id xid in kd_lattice xhost, which has local coordinates
// xu_id, xv_id.
//
bool intersect_contents(kd_lattice& xhost, 
                        const scoped_index& xid, 
                        int xu_id, 
                        int xv_id, 
                        line_pt& xpt0, 
                        line_list& xline,
                        bool xCD_is_first)
{
  // cout << endl << "Entering kd_face.cc::intersect_contents." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());

  require(xpt0.pt == kd_point::coords(xhost, xpt0.pt_id));
  require(unexecutable("out code of xpt0 == INSIDE"));

  require(!xline.empty());
  require(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));  

  define_old_variable(int old_xline_size = xline.size());

  // Body:
  
  bool result = false;

  list_index_space_iterator litr;
  if(!xline.front().contents_itr.is_done())
  {
    // This segment was created by an intersection
    // and hence has already been checked agoainst
    // some of the contents; just check it against
    // the rest.

    litr = xline.front().contents_itr;

    //     cout << "using stored iterator:";
    //     if(litr.is_done())
    //     {
    //       cout << " is done" << endl;
    //     }
    //     else
    //     {
    //       cout << setw(6) << litr.item().pod() << endl;
    //     }
  }
  else
  {
    // This segment needs to be checked against the entire contents.

    litr.attach_to(xhost.base_space().member_id_spaces(false),
		   xhost.base_space().cover_id_space_id(LOWER, xid));

    // Skip past the edges.
  
    litr.next();
    litr.next();
    litr.next();
    litr.next();

    //     cout << "using new iterator:";
    //     if(litr.is_done())
    //     {
    //       cout << " is done" << endl;
    //     }
    //     else
    //     {
    //       cout << setw(6) << litr.item().pod() << endl;
    //     }
  }

  // $$SCRIBBLE ERROR only do this when itr is initialized.  
  //   // Skip past the edges.
  
  //   litr.next();
  //   litr.next();
  //   litr.next();
  //   litr.next();

  // Test for intersection with the contents of the face.
  // Intersect current segment with remaining
  // members of the current contents. 
  // If an intersection is found, it
  // may or may not add segments to the
  // line but current segment is
  // always defined by xpt0 and xline.front().

  while(!litr.is_done())
  {

    intersect_segment(xhost, xid, litr, xu_id, xv_id, xpt0, xline, xCD_is_first);
    litr.next();
  }

  // Postconditions:

  ensure(xpt0.pt == kd_point::coords(xhost, xpt0.pt_id));
  ensure(unexecutable("out code of xpt0 == INSIDE"));

  ensure(xline.size() >= old_xline_size);
  ensure(!xline.empty());
  ensure(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));  
  
  // Exit:

  // cout << "Leaving kd_face.cc::intersect_contents." << endl << endl;
  return result;
}

//
// Clips the segment specified by xpt0 and xline.front()
// against the bounding box xbox of the face with id xid
// in kd_lattice xhost, which has local coordinates
// xu_id, xv_id. Returns clipping code.
//
int clip_segment(kd_lattice& xhost, 
                  const scoped_index& xid,
                  const kd_bounding_box& xbox,
                  int xu_id, 
                  int xv_id, 
                  const line_pt& xpt0, 
                  line_list& xline)
{
  // cout << endl << "Entering kd_face.cc::clip_segment." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());

  require(!xline.empty());
  require(unexecutable("out code of xline.front() == INSIDE"));

  require(!(xpt0 == xline.front()));
  

  define_old_variable(int old_xline_size = xline.size());

  // Body:

  // Get the second point of the segment.

  line_pt lpt1(xline.front());

  // If pt1 falls just inside the boundary of
  // the face, the next segment will clip, leaving
  // a very short segment inside the face and leading
  // degenerate triangles that cause the subvolume 
  // extraction to fail. To avoid this, extend
  // the segment a small amount  before clipping.

  const double EXTEND_FACTOR = 1.0 + sheaf::double_tolerance;
  e3_lite lseg(lpt1.pt);
  lseg -= xpt0.pt;
  lseg *= EXTEND_FACTOR;
  add(xpt0.pt, lseg, lpt1.pt);
  
  // Clip the segment against the bounding box;
  // will change lpt1.pt if segment clips.

  int result = xbox.clip_2d(xpt0.pt, lpt1.pt, xu_id, xv_id);

  if(result)
  {
    // Extended segment has been clipped. If the clipped point
    // is close to the original, unextended front pt, then
    // the front pt is either slightly inside or slightly
    // outside the boundary. Either way, the next segment 
    // will be short, which we don't want. Have to check for 
    // this condition before we insert the point in the edge,
    // because that may move the point.

    bool lshort_segment = c_eql(lpt1.pt, xline.front().pt);

    // Short segment or not, the new point lies
    // in an edge and may be an intersection. Find or create 
    // the point member. Note that if we find an intersection,
    // we move the point to the intersection, so this may change lpt1.

    lpt1.pt_id = kd_face::insert_point(xhost, xid, lpt1.pt, result);

    lpt1.clip_code = result;

    assertion(lpt1.pt == kd_point::coords(xhost, lpt1.pt_id));

    //    if((result & kd_bounding_box::CLIPPED) && !c_eql(lpt1.pt, xline.front().pt))
    if(lshort_segment)
    {
      // The front point either was close to the boundary
      // and we don't want to produce any short segments,
      // so move the front pt to the new point. 
      // Note that this not only changes the position
      // of the point but also sets its id and clip code.

      // cout << "new point replaces front" << endl;

      xline.front() = lpt1;
    }
    else
    {
      // Point was significiantly outside the boundary and was clipped,
      // which created a new point, which implies an additional segment
      // Push the new point onto xline.

      // cout << "new segment created; push new point onto line" << endl;
    
      xline.push_front(lpt1);
    }
  }
  else
  {
    // Segment was strictly in the interior.

    xline.front().clip_code = result;
  }

  // cout << "result: " << kd_bounding_box::out_code_2d_from_int(result) << endl;

  // Postconditions:

  ensure(xline.size() >= old_xline_size);
  ensure(xpt0.pt == kd_point::coords(xhost, xpt0.pt_id));
  ensure(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));
  ensure(xline.front().clip_code == result);  
  
  // Exit:

  // cout << "Leaving kd_face.cc::clip_segment." << endl << endl;
  return result;
}

//} // end unnamed namespace.


// ===========================================================
// KD_FACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_face::line_pt::
line_pt(const e3_lite& xpt)
  : pt(xpt), clip_code(kd_bounding_box::INSIDE)
{
  // Preconditions:


  // Body:

  // Nothing else to do.

  // Postconditions:
  
  ensure(pt == xpt);
  ensure(!pt_id.is_valid());
  ensure(clip_code == kd_bounding_box::INSIDE);
  ensure(contents_itr.is_done());

  // Exit:

  return;
}


bool
geometry::kd_face::line_pt::
operator==(const kd_face::line_pt& xother) const
{
  // cout << endl << "Entering kd_face::operator==." << endl;

  // Preconditions:


  // Body:

  bool result;
  result = (pt == xother.pt);
  result = result && (pt_id == xother.pt_id);
  result = result && (clip_code == xother.clip_code);
  bool lboth_done = (contents_itr.is_done() && xother.contents_itr.is_done());
  result = result && ( lboth_done || (contents_itr.hub_pod() == xother.contents_itr.hub_pod()));
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::operator==." << endl;
  return result;
}


const string&
geometry::kd_face::
prototype_name(kd_alignment xalignment)
{
  // cout << endl << "Entering kd_face::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string lproto_name[4] = 
    {
      "kd_x_axis_aligned_face",
      "kd_y_axis_aligned_face",
      "kd_z_axis_aligned_face",
      "kd_not_axis_aligned_face"
    };

  const string& result = lproto_name[xalignment];

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_face::prototype_name." << endl;
  return result;
}

geometry::kd_face::
kd_face(kd_lattice& xhost, const scoped_index xedges[], kd_alignment xalignment)
{
  // cout << endl << "Entering kd_face::new_face(kd_lattice&, const scoped_index[])." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, EDGE_CT, xhost.edges().contains(xedges[i]));
  require(xalignment != NOT_AXIS_ALIGNED);

  define_old_variable(size_type old_faces_ct = xhost.faces().ct());
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());
  
  // Body:

  _id = new_face(xhost, xedges, xalignment);

  // Postconditions:

  ensure(alignment() == xalignment);
  ensure(host().faces().ct() == old_faces_ct + 1);
  ensure(host().edges().ct() == old_edges_ct);
  ensure(host().vertices().ct() == old_vertices_ct);
  ensure_for_all(i, 0, EDGE_CT, edge(i) == xedges[i]);
  
  // Exit:

  // cout << "Leaving kd_face::new_face(kd_lattice&, const scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_face::
new_face(kd_lattice& xhost, const scoped_index xedges[], kd_alignment xalignment)
{
  // cout << endl << "Entering kd_face::new_face(kd_lattice&, const scoped_index[])." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require_for_all(i, 0, EDGE_CT, xhost.edges().contains(xedges[i]));
  require(xalignment != NOT_AXIS_ALIGNED);
  
  define_old_variable(size_type old_faces_ct = xhost.faces().ct());
  define_old_variable(size_type old_edges_ct = xhost.edges().ct());
  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  // Body:

  base_space_poset& lbase = xhost.base_space();

  // Create the face with alignment xalignment.
  
  scoped_index result;

  switch(xalignment)
  {
    case X_AXIS_ALIGNED:
      result = xhost.x_faces().new_member();
      break;
    case Y_AXIS_ALIGNED:
      result = xhost.y_faces().new_member();
      break;
    case Z_AXIS_ALIGNED:
      result = xhost.z_faces().new_member();
      break;
    default:
      post_fatal_error_message("Unsupported face alignment.");
  }

  // The face covers the edges.

  for(int i=0; i<EDGE_CT; ++i)
  {
    lbase.new_link(result, xedges[i]);
  }

  // Postconditions:

  ensure(alignment(xhost, result) == xalignment);
  ensure(xhost.faces().ct() == old_faces_ct + 1);
  ensure(xhost.edges().ct() == old_edges_ct);
  ensure(xhost.vertices().ct() == old_vertices_ct);
  ensure_for_all(i, 0, EDGE_CT, edge(xhost, result, i) == xedges[i]);
  
  // Exit:

  // cout << "Leaving kd_face::new_face(kd_lattice&, const scoped_index[])." << endl;
  return result;
}

geometry::kd_face::
kd_face(kd_lattice& xhost, const scoped_index& xid)
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

geometry::kd_face::
kd_face(const kd_face& xother)
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

geometry::kd_face::
~kd_face()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}


void
geometry::kd_face::
subfaces(scoped_index xresult[]) const
{
  // Preconditions:

  require(unexecutable("xresult is an array with at least SUBFACE_CT entries"));
  require(host().base_space().state_is_read_accessible());
  require(!host().leaves().contains(id()));
  
  // Body:

  subfaces(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, SUBFACE_CT, host().faces().contains(xresult[i]));

  // Exit:

  return;
}

void
geometry::kd_face::
subfaces(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_face::subfaces(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least SUBFACE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  require(!xhost.leaves().contains(xid));
  
  // Body:

  const cohort& lfaces = xhost.faces();

  int lsz = 0;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  while(!litr.is_done() && (lsz < SUBFACE_CT))
  {
    if(lfaces.contains(litr.hub_pod()))
    {
      xresult[lsz++] = xhost.base_space().member_id(litr.hub_pod(), false);
    }    
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure_for_all(i, 0, SUBFACE_CT, xhost.faces().contains(xresult[i]));
  
  // Exit:

  // cout << "Leaving kd_face::subfaces(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_face::
subface(int xi) const
{
  // cout << endl << "Entering kd_face::subface(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < SUBFACE_CT));

  // Body:

  scoped_index result = subface(*_host, _id, xi);

  // Postconditions:

  ensure(host().faces().contains(result));

  // Exit:

  // cout << "Leaving kd_face::subface(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_face::
subface(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_face::subface(const kd_lattice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  require(!xhost.leaves().contains(xid));
  require((0 <= xi) && (xi < SUBFACE_CT));

  // Body:

  const cohort& lfaces = xhost.faces();

  scoped_index result;
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid); // link 0

  if(xi == 0)
  {
    // Subface 0 is either link 0 or link 3.

    if(!xhost.faces().contains(xhost.base_space().member_id(litr.hub_pod(), false)))
    {
      litr.next(); // link 1
      litr.next(); // link 2
      litr.next(); // link 3
    }
    result = litr.hub_pod();
  }
  else
  {
    // Subface 1 is either link 1 or 2.

    litr.next(); // link 1
    if(!xhost.faces().contains(xhost.base_space().member_id(litr.hub_pod(), false)))
    {
      litr.next(); // link 2
    }
    result = xhost.base_space().member_id(litr.hub_pod(), false);
  }

  //   litr.reset();
  //   while(!litr.is_done())
  //   {
  //     cout << "litr.item(): " << litr.item() << "  "  << xhost.base_space().member_name(litr.item()) << endl;
  //     litr.next();
  //   }
  
  // cout << "result: " << result << "  "  << xhost.base_space().member_name(result) << endl;

  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xhost.faces().contains(result));
  
  // Exit:

  // cout << "Leaving kd_face::subface(const kd_lattice&, const scoped_index&, int)." << endl;
  return result;
}


void
geometry::kd_face::
edges(scoped_index xresult[]) const
{
  // cout << endl << "Entering kd_face::edges(scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least FACE_CT entries"));
  require(host().base_space().state_is_read_accessible());
  
  // Body:

  edges(*_host, _id, xresult);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::edges(scoped_index[])." << endl;
  return;
}

void
geometry::kd_face::
edges(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_face::edges(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least FACE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  const cohort& ledges = xhost.edges();

  scoped_index lid;
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  for(int i=0; i<EDGE_CT; ++i)
  {
    lid = xhost.base_space().member_id(litr.hub_pod(), false);
    while(!ledges.contains(lid))
    {
      index_space_iterator& lc_itr = lbase.get_cover_id_space_iterator(LOWER, lid);
      for(int j=0; j<i; ++j)
      {
        lc_itr.next();
      }
      lid = xhost.base_space().member_id(lc_itr.hub_pod(), false);
      lbase.release_cover_id_space_iterator(lc_itr);
    }
    xresult[i] = lid;
    
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  // Postconditions:

  ensure_for_all(i, 0, EDGE_CT, xhost.edges().contains(xresult[i]));
  
  // Exit:

  // cout << "Leaving kd_face::edges(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_face::
edge(int xi) const
{
  // cout << endl << "Entering kd_face::edge." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < EDGE_CT));

  // Body:

  scoped_index result = edge(*_host, _id, xi);

  // Postconditions:

  ensure(host().edges().contains(result));

  // Exit:

  // cout << "Leaving kd_face::edge." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_face::
edge(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_face::edge." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  require((0 <= xi) && (xi < EDGE_CT));

  // Body:

  const base_space_poset& lbase = xhost.base_space();
  const cohort& ledges = xhost.edges();

  scoped_index result = xid;
  while(!ledges.contains(result))
  {
    index_space_iterator& lc_itr = lbase.get_cover_id_space_iterator(LOWER, result);
    for(int i=0; i<xi; ++i)
    {
      lc_itr.next();
    }
    result = xhost.base_space().member_id(lc_itr.hub_pod(), false);
    lbase.release_cover_id_space_iterator(lc_itr);
  }

  // Postconditions:

  ensure(xhost.edges().contains(result));
  
  // Exit:

  // cout << "Leaving kd_face::edge." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_face::
splitting_edge() const
{
  // cout << endl << "Entering kd_face::splitting_edge()." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());

  // Body:

  scoped_index result = splitting_edge(*_host, _id);

  // Postconditions:

  ensure(host().edges().contains(result));

  // Exit:

  // cout << "Leaving kd_face::splitting_edge(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_face::
splitting_edge(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_face::splitting_edge(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));

  // Body:

  kd_alignment lface_alignment = alignment(xhost, xid);
  kd_alignment lplane_alignment = xhost.plane(xid).alignment();

  scoped_index result = subface(xhost, xid, 0);
  
  switch(lface_alignment)
  {
    case X_AXIS_ALIGNED:
      switch(lplane_alignment)
      {
        case X_AXIS_ALIGNED:
          post_fatal_error_message("Attempt to refine x const face by x const plane.");
          break;
        case Y_AXIS_ALIGNED:
          result = edge(xhost, result, 2);
          break;
        case Z_AXIS_ALIGNED:
          result = edge(xhost, result, 1);
          break;
        default:
          post_fatal_error_message("Unrecognized plane alignment.");
          break;
      }      
      break;
    case Y_AXIS_ALIGNED:
      switch(lplane_alignment)
      {
        case X_AXIS_ALIGNED:
          result = edge(xhost, result, 1);
          break;
        case Y_AXIS_ALIGNED:
          post_fatal_error_message("Attempt to refine y const face by y const plane.");
          break;
        case Z_AXIS_ALIGNED:
          result = edge(xhost, result, 2);
          break;
        default:
          post_fatal_error_message("Unrecognized plane alignment.");
          break;
      }
      break;
    case Z_AXIS_ALIGNED:
      switch(lplane_alignment)
      {
        case X_AXIS_ALIGNED:
          result = edge(xhost, result, 1);
          break;
        case Y_AXIS_ALIGNED:
          result = edge(xhost, result, 2);
          break;
        case Z_AXIS_ALIGNED:
          post_fatal_error_message("Attempt to refine z const face by z const plane.");
          break;
        default:
          post_fatal_error_message("Unrecognized plane alignment.");
          break;
      }
      break;
    default:
      post_fatal_error_message("Unrecognized face alignment.");
      break;
  }


  // Postconditions:

  ensure(xhost.edges().contains(result));
  
  // Exit:

  // cout << "Leaving kd_face::splitting_edge(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

void
geometry::kd_face::
vertices(scoped_index xresult[]) const
{
  // cout << endl << "Entering kd_face::vertices(scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(host().base_space().state_is_read_accessible());
  
  // Body:

  vertices(*_host, _id, xresult);
  
  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, host().vertices().contains(xresult[i]));

  // Exit:

  // cout << "Leaving kd_face::vertices(scoped_index[])." << endl;
  return;
}

void
geometry::kd_face::
vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[])
{
  // cout << endl << "Entering kd_face::vertices(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;

  // Preconditions:

  require(unexecutable("xresult is an array with at least VERTEX_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();
  
  // Get the edges.

  edges(xhost, xid, xresult);

  // Get the vertices from the edges,
  // paying attention to the orientation of the edge.

  xresult[0] = kd_edge::vertex(xhost, xresult[0], 0);
  xresult[1] = kd_edge::vertex(xhost, xresult[1], 0);
  xresult[2] = kd_edge::vertex(xhost, xresult[2], 1);
  xresult[3] = kd_edge::vertex(xhost, xresult[3], 1);

  // Postconditions:

  ensure_for_all(i, 0, VERTEX_CT, xhost.vertices().contains(xresult[i]));

  // Exit:

  // cout << "Leaving kd_face::vertices(kd_lsttice&, const scoped_index&, scoped_index[])." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_face::
vertex(int xi) const
{
  // cout << endl << "Entering kd_face::vertex(int)." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require((0 <= xi) && (xi < VERTEX_CT));

  // Body:

  scoped_index result = vertex(*_host, _id, xi);

  // Postconditions:

  ensure(host().vertices().contains(result));

  // Exit:

  // cout << "Leaving kd_face::vertex(int)." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_face::
vertex(const kd_lattice& xhost, const scoped_index& xid, int xi)
{
  // cout << endl << "Entering kd_face::vertex(kd_lsttice&, const scoped_index&, int)." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.edges().contains(xid));
  require((0 <= xi) && (xi < VERTEX_CT));

  // Body:

  scoped_index result = edge(xhost, xid, xi);
  if(xi < 2)
  {
    result = kd_edge::vertex(xhost, result, 0);  
  } 
  else
  {
    result = kd_edge::vertex(xhost, result, 1);  
  }
 

  // Postconditions:

  ensure(xhost.vertices().contains(result));
  
  // Exit:

  // cout << "Leaving kd_face::vertex(kd_lsttice&, const scoped_index&, int)." << endl;
  return result;
}

geometry::kd_alignment
geometry::kd_face::
alignment(const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_face::alignment(const e3_lite&, const e3_lite&)." << endl;

  // Preconditions:


  // Body:

  kd_alignment result;
  if((xlb[0] == xub[0]) && (xlb[1] != xub[1]) && (xlb[2] != xub[2]))
  {
    result = X_AXIS_ALIGNED;
  }
  else if((xlb[0] != xub[0]) && (xlb[1] == xub[1]) && (xlb[2] != xub[2]))
  {
    result = Y_AXIS_ALIGNED;
  }
  else if((xlb[0] != xub[0]) && (xlb[1] != xub[1]) && (xlb[2] == xub[2]))
  {
    result = Z_AXIS_ALIGNED;
  }
  else
  {
    result = NOT_AXIS_ALIGNED;
  }    


  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::alignment(const e3_lite&, const e3_lite&)." << endl;
  return result;
}

bool
geometry::kd_face::
is_axis_aligned(const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_face::is_axis_aligned." << endl;

  // Preconditions:


  // Body:

  bool result = (alignment(xlb, xub) != NOT_AXIS_ALIGNED);


  // Postconditions:

  ensure(result == (alignment(xlb, xub) != NOT_AXIS_ALIGNED));

  // Exit:

  // cout << "Leaving kd_face::is_axis_aligned." << endl;
  return result;
}

void
geometry::kd_face::
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
geometry::kd_face::
coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());

  // Body:

  // Get the vertex ids.

  scoped_index lv_ids[VERTEX_CT];
  vertices(xhost, xid, lv_ids);

  // Need to use two vertices on a diagonal; 0 and 2 will do.

  coord_bounds(xhost, lv_ids[0], lv_ids[2], xlb, xub);
  
  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::e3_lite
geometry::kd_face::
coord_lower_bound() const
{
  // cout << endl << "Entering kd_face::coord_lower_bound." << endl;

  // Preconditions:


  // Body:

  e3_lite result = coord_lower_bound(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::coord_lower_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_face::
coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_face::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite result, lub;
  coord_bounds(xhost, xid, result, lub);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::coord_lower_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_face::
coord_upper_bound() const
{
  // cout << endl << "Entering kd_face::coord_upper_bound." << endl;

  // Preconditions:


  // Body:

  e3_lite result = coord_upper_bound(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::coord_upper_bound." << endl;
  return result;
}

fiber_bundle::e3_lite
geometry::kd_face::
coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_face::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;

  // Preconditions:


  // Body:

  e3_lite llb, result;
  coord_bounds(xhost, xid, llb, result);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::coord_upper_bound(const kd_lattice&, const scoped_index&)." << endl;
  return result;
}

void
geometry::kd_face::
put_coord_bounds(const e3_lite& xlb, const e3_lite& xub)
{
  // Preconditions:

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
geometry::kd_face::
put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub)
{
  // Preconditions:

  require(xhost.coords().state_is_read_write_accessible());
  require(is_axis_aligned(xlb, xub));
  
  // Body:

  // Get the vertex ids.

  scoped_index lv_ids[VERTEX_CT];
  vertices(xhost, xid, lv_ids);

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

  // Postconditions:

  ensure(coord_lower_bound(xhost, xid) == xlb);
  ensure(coord_upper_bound(xhost, xid) == xub);

  // Exit:

  return;
}

sheaf::scoped_index
geometry::kd_face::
insert_point(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt)
{
  // cout << endl << "Entering kd_face::insert_point." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.base_space().in_jim_edit_mode());
  require(contains_point(xhost, xid, xpt));
  
  // Body:

  // Get the bounding box for the face.

  kd_bounding_box& lbox = xhost.bounding_box(xid);
 
  // Get local a local coordinate system for use with
  // bounding box clipping routine.

  int lu, lv;
  local_axes_clip_2d(xhost, xid, lu, lv);

  // This face contains xpt so xpt is either on an edge
  // or in the interior; determine which it is.

  int lcode = lbox.out_code_2d(xpt[lu], xpt[lv], lu, lv, 0);

  // Insert the point as directed by the out code.

  scoped_index result = insert_point(xhost, xid, xpt, lcode);

  
  // Postconditions:

  ensure(xhost.base_space().vertices().contains_member(result));

  // Exit:

  // cout << "Leaving kd_face::insert_point." << endl << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_face::
insert_point(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt, int xcode)
{
  // cout << endl << "Entering kd_face::insert_point." << endl;
  // cout <<"face: " << xid << endl;
  // cout << "pt: " << xpt << endl;
  // cout << "out code: " << kd_bounding_box::out_code_2d_from_int(xcode) << endl;
  

  // Preconditions:

  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.base_space().in_jim_edit_mode());
  
  // Body:

  scoped_index result, ledge_id;
  
  if(xcode & kd_bounding_box::LEFT)
  {
    // The point is on the left edge, which is always edge 3

    ledge_id = edge(xhost, xid, 3);

    // Insert the point in the edge.

    kd_edge::insert_point(xhost, ledge_id, xpt, result);
  }
  else if(xcode & kd_bounding_box::RIGHT)
  {
    // The point is on the right edge, which is always edge 1

    ledge_id = edge(xhost, xid, 1);

    // Insert the point in the edge.

    kd_edge::insert_point(xhost, ledge_id, xpt, result);
  }
  else if(xcode & kd_bounding_box::BOTTOM)
  {
    // The point is on the bottom edge, which is always edge 0.

    ledge_id = edge(xhost, xid, 0);

    // Insert the point in the edge.

    kd_edge::insert_point(xhost, ledge_id, xpt, result);
  }
  else if(xcode & kd_bounding_box::TOP)
  {
    // The point is on the top edge, which is always edge 2

    ledge_id = edge(xhost, xid, 2);

    // Insert the point in the edge.

    kd_edge::insert_point(xhost, ledge_id, xpt, result);
  }
  else
  {
    // The point is in the interior,

    // Create the point.

    result = kd_point::new_point(xhost, xpt);

    // cout << "created new point:"  << result << endl;
  }
  
  // Postconditions:

  ensure(xhost.base_space().vertices().contains_member(result));
  ensure(xpt == kd_point::coords(xhost, result));

  // Exit:

  // cout << "Leaving kd_face::insert_point." << endl << endl;
  return result;
}

bool
geometry::kd_face::
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
geometry::kd_face::
in_bounds(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());

  // Body:


  e3_lite llb, lub;
  coord_bounds(xhost, xid, llb, lub);
  
  int i = xp.alignment();
  bool result = (llb[i] < xp.distance()) && (xp.distance() < lub[i]);

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::kd_face::
in_plane(const kd_plane& xp) const
{
  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().coords().state_is_read_accessible());

  // Body:

  bool result = in_plane(*_host, _id, xp);

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::kd_face::
in_plane(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());

  // Body:


  e3_lite llb, lub;
  coord_bounds(xhost, xid, llb, lub);
  
  int i = xp.alignment();
  bool result = (alignment(xhost, xid) == xp.alignment()) && (llb[i] == xp.distance());

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::kd_face::
contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_face::contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::contains_point." << endl;
  return result;
}

bool
geometry::kd_face::
contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_face::contains_point." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
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
      result = (xpt[0] == llb[0]) && (llb[1] <= xpt[1]) && (xpt[1] <= lub[1]) && (llb[2] <= xpt[2]) && (xpt[2] <= lub[2]);
      break;
    case Y_AXIS_ALIGNED:
      result = (xpt[1] == llb[1]) && (llb[0] <= xpt[0]) && (xpt[0] <= lub[0]) && (llb[2] <= xpt[2]) && (xpt[2] <= lub[2]);
      break;
    case Z_AXIS_ALIGNED:
      result = (xpt[2] == llb[2]) && (llb[0] <= xpt[0]) && (xpt[0] <= lub[0]) && (llb[1] <= xpt[1]) && (xpt[1] <= lub[1]);
      break;
    default:
      post_fatal_error_message("Unsupported alignment type.");
      break;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::contains_point." << endl;
  return result;
}

bool
geometry::kd_face::
interior_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_face::interior_contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = interior_contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_face::
interior_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_face::interior_contains_point." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
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
      result = (xpt[0] == llb[0]) && (llb[1] < xpt[1]) && (xpt[1] < lub[1]) && (llb[2] < xpt[2]) && (xpt[2] < lub[2]);
      break;
    case Y_AXIS_ALIGNED:
      result = (xpt[1] == llb[1]) && (llb[0] < xpt[0]) && (xpt[0] < lub[0]) && (llb[2] < xpt[2]) && (xpt[2] < lub[2]);
      break;
    case Z_AXIS_ALIGNED:
      result = (xpt[2] == llb[2]) && (llb[0] < xpt[0]) && (xpt[0] < lub[0]) && (llb[1] < xpt[1]) && (xpt[1] < lub[1]);
      break;
    default:
      post_fatal_error_message("Unsupported alignment type.");
      break;
  }

  // Postconditions:

  ensure(unexecutable("result == (xpt[i] == bnd[i] for some i and bnd"));

  // Exit:

  // cout << "Leaving kd_face::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_face::
boundary_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_face::boundary_contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = boundary_contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::boundary_contains_point." << endl;
  return result;
}

bool
geometry::kd_face::
boundary_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_face::boundary_contains_point." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
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
      result = (xpt[0] == llb[0]) && ((xpt[1] == llb[1])  || (xpt[1] == lub[1]) ||  (xpt[2] == llb[2]) || (xpt[2] == lub[2]));
      break;
    case Y_AXIS_ALIGNED:
      result = (xpt[1] == llb[1]) && ((xpt[0] == llb[0]) || (xpt[0] == lub[0]) || (xpt[2] == llb[2]) || (xpt[2] == lub[2]));
      break;
    case Z_AXIS_ALIGNED:
      result = (xpt[2] == llb[2]) && ((xpt[0] == llb[0]) || (xpt[0] == lub[0]) || (xpt[1] == llb[1]) || (xpt[1] == lub[1]));
      break;
    default:
      post_fatal_error_message("Unsupported alignment type.");
      break;
  }

  // Postconditions:

  ensure(unexecutable("result == (xpt[i] == bnd[i]  for some i and bnd"));

  // Exit:

  // cout << "Leaving kd_face::boundary_contains_point." << endl;
  return result;
}

scoped_index
geometry::kd_face::
locate_point(const e3_lite& xpt, int xd) const
{
  // cout << endl << "Entering kd_face::locate_point." << endl;

  // Preconditions:

  require(precondition_of(locate_point(host(), id(), xpt, xd)));

  // Body:

  scoped_index result = locate_point(*_host, _id, xpt, xd);

  // Postconditions:

  ensure(postcondition_of(locate_point(host(), id(), xpt, xd)));

  // Exit:

  // cout << "Leaving kd_face::locate_point." << endl;
  return result;
}

scoped_index
geometry::kd_face::
locate_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt, int xd)
{
  // cout << endl << "Entering kd_face::locate_point." << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
  require(interior_contains_point(xhost, xid, xpt));

  // Body:

  const e3_lite& ltolerance = xhost.point_tolerance();

  scoped_index result(xid);

  while(!xhost.leaves().contains(result))
  {      
    // xpt is not on the boundary of the face,
    // so it must either in the splitting edge or 
    // in one of the subfaces.

    const kd_plane& lp = xhost.plane(result);
    int lalignment = lp.int_alignment();
    double lp_dist = lp.distance();
    double lpt_dist = xpt[lalignment];
    
    if((xd < DB) && (lpt_dist == lp_dist))
    {
      // Point is located on the edge between the subfaces.

      result = kd_face::splitting_edge(xhost, result);
      result = kd_edge::locate_point(xhost, result, xpt, xd);
    }
    else if( lpt_dist < lp_dist)
    {
      // Point is located in back side subface.

      result = kd_face::subface(xhost, result, 0);
    }
    else
    {
      // Point is located in front side subface.

      result = kd_face::subface(xhost, result, 1);
    }
  }
  
  // Postconditions:

  ensure(xhost.leaves().contains(result));
  ensure(xhost.cell_contains_point(result, xpt));

  // Exit:

  // cout << "Leaving kd_face::locate_point." << endl;
  return result;
}

void
geometry::kd_face::
leaf(const pt_list& xline, scoped_index& xresult) const
{
  // cout << endl << "Entering kd_face::leaf." << endl;

  // Preconditions:

  require(precondition_of(leaf(host(), id(), xline, xresult)));
  
  // Body:

  leaf(host(), id(), xline, xresult);
  
  // Postconditions:

  ensure(postcondition_of(leaf(host(), id(), xline, xresult)));

  // Exit:

  // cout << "Leaving kd_face::leaf." << endl;
  return;
}

void
geometry::kd_face::
leaf(const kd_lattice& xhost, const scoped_index& xid, const pt_list& xline, scoped_index& xresult)
{
  // cout << endl << "Entering kd_face::leaf." << endl;
  // cout << "First point: " << xline.front() << "  second point: " << (*(++xline.begin())) << endl;
  // cout << "bounding box: " << xhost.bounding_box(xid) << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
  require(!xline.empty());
  require(++xline.begin() != xline.end()); // At least 2 points.
  require(contains_point(xhost, xid, xline.front()));
  
  // Body:

  xresult = xid;

  pt_list::const_iterator lpt0 = xline.begin();

  while(!xhost.leaves().contains(xresult))
  {      
    // xpt is in the face, and the face is not a leaf,
    // so it must either in one of the subfaces.
    
    const kd_plane& lp = xhost.plane(xresult);
    int lp_alignment = lp.int_alignment();
    vd_value_type lp_dist = lp.distance();
    vd_value_type lpt_dist = (*lpt0)[lp_alignment];

    // cout << "inspecting face: " << xresult << endl;
    // cout << "bounding box: " << xhost.bounding_box(xresult) << endl;
    // cout << "splitting plane:" << lp << endl;
    // cout << "lpt_dist: " << lpt_dist << "  lp_dist: " << lp_dist << endl;
    
    if(lpt_dist < lp_dist)
    {
      // First point is located in back side subface.

      // cout << " First point is located in back side subface" << endl;      

      xresult = kd_face::subface(xhost, xresult, 0);
    }
    else if(lpt_dist > lp_dist)
    {
      // First point is located in front side subface.

      // cout << " First point is located in front side subface" << endl;      

      xresult = kd_face::subface(xhost, xresult, 1);
    }
    else
    {
      // First point is located on the spitting edge.
      // Look at the second point to determine which subface.

      // cout << "First point is located on the spitting edge." << endl;

      pt_list::const_iterator lpt1 = ++xline.begin();
      lpt_dist = (*lpt1)[lp_alignment];

      // cout << "second point: " << *lpt1 << endl;
      // cout << "lpt_dist: " << lpt_dist << "  lp_dist: " << lp_dist << endl;

      if(lpt_dist < lp_dist)
      {
        // Second point is located in back side subface.

        // cout << "Second point is located in back side subface" << endl;

        xresult = kd_face::subface(xhost, xresult, 0);
      }
      else if(lpt_dist > lp_dist)
      {
        // Second point is located in front side subface.

        // cout << "Second point is located in front side subface" << endl;

        xresult = kd_face::subface(xhost, xresult, 1);
      }
      else
      {
        // Second point is located on the spitting edge;
        // doesn't matter which subface we choose.

        // cout << "Second point is located on splitting edge" << endl;

        xresult = kd_face::subface(xhost, xresult, 1);
      }
    }
  }
  
  // cout << "result: " << xresult << "  " << name(xhost, xresult) << endl;
  // cout << "bounding box: " << xhost.bounding_box(xresult) << endl;
  
  // Postconditions:

  ensure(xhost.leaves().contains(xresult));
  ensure(xhost.cell_contains_point(xresult, xline.front()));

  // Exit:

  // cout << "Leaving kd_face::leaf." << endl;
  return;
}

void
geometry::kd_face::
leaves(id_list& xresult) const
{
  // cout << endl << "Entering kd_face::find_face_leaves." << endl;

  // Preconditions:

  require(precondition_of(find_face_leaves(host(), id(), xresult)));
  
  // Body:

  leaves(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(leaves(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_face::find_face_leaves." << endl;
  return;
}

void
geometry::kd_face::
leaves(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_face::leaves." << endl;
  // cout << "bounding box: " << xhost.bounding_box(xid) << endl;

  // Preconditions:

  require(xhost.faces().contains(xid));
  
  
  // Body:

  if(xhost.leaves().contains(xid))
  {
    // Found a leaf.

    xresult.push_back(xid);
  }
  else
  {
    // This face is not a leaf; 
    // look in its subfaces.

    const cohort& lfaces = xhost.faces();

    int lsz = 0;
    index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
    while(!litr.is_done() && (lsz < SUBFACE_CT))
    {
      scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);
      if(lfaces.contains(lid))
      {
        leaves(xhost, lid, xresult);
      }    
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::leaves." << endl;
  return;
}

void
geometry::kd_face::
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
geometry::kd_face::
refine(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[])
{
  // cout << endl << "Entering kd_face::refine." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.faces().contains(xid));
  require(in_bounds(xhost, xid, xp));

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  // Set the splitting plane.

  xhost.put_plane(xid, xp);

  // Determine the orientation and use the corresponding refinement.

  kd_alignment lface_alignment = alignment(xhost, xid);
  kd_alignment lplane_alignment = xp.alignment();

  switch(lface_alignment)
  {
    case X_AXIS_ALIGNED:
      switch(lplane_alignment)
      {
        case X_AXIS_ALIGNED:
          post_fatal_error_message("Attempt to refine x const face by x const plane.");
          break;
        case Y_AXIS_ALIGNED:
          refine_edges_1_and_3(xhost, xid, xp, xnew_ids);
          break;
        case Z_AXIS_ALIGNED:
          refine_edges_0_and_2(xhost, xid, xp, xnew_ids);
          break;
        default:
          post_fatal_error_message("Unrecognized plane alignment.");
          break;
      }      
      break;
    case Y_AXIS_ALIGNED:
      switch(lplane_alignment)
      {
        case X_AXIS_ALIGNED:
          refine_edges_0_and_2(xhost, xid, xp, xnew_ids);
          break;
        case Y_AXIS_ALIGNED:
          post_fatal_error_message("Attempt to refine y const face by y const plane.");
          break;
        case Z_AXIS_ALIGNED:
          refine_edges_1_and_3(xhost, xid, xp, xnew_ids);
          break;
        default:
          post_fatal_error_message("Unrecognized plane alignment.");
          break;
      }
      break;
    case Z_AXIS_ALIGNED:
      switch(lplane_alignment)
      {
        case X_AXIS_ALIGNED:
          refine_edges_0_and_2(xhost, xid, xp, xnew_ids);
          break;
        case Y_AXIS_ALIGNED:
          refine_edges_1_and_3(xhost, xid, xp, xnew_ids);
          break;
        case Z_AXIS_ALIGNED:
          post_fatal_error_message("Attempt to refine z const face by z const plane.");
          break;
        default:
          post_fatal_error_message("Unrecognized plane alignment.");
          break;
      }
      break;
    default:
      post_fatal_error_message("Unrecognized face alignment.");
      break;
  }

  //   cout << "splitting plane: " << xp << endl;
  //   cout << "back subface: " << xnew_ids[0] << " bounds: " << xhost.bounding_box(xnew_ids[0]) << endl;
  //   cout << "front subface: " << xnew_ids[1] << " bounds: " << xhost.bounding_box(xnew_ids[1]) << endl;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::refine." << endl << endl;
  return;
}

void
geometry::kd_face::
insert_line(line_list& xline, id_list& xline_mbrs)
{
  // cout << endl << "Entering kd_face::insert_line." << endl;

  // Preconditions:


  // Body:

  insert_line(*_host, _id, xline, xline_mbrs);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::insert_line." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_face::
insert_line(kd_lattice& xhost, const scoped_index& xid, line_list& xline, id_list& xline_mbrs)
{
  // cout << endl << "Entering kd_face::insert_line for face: " << xid.internal_pod() << endl;
  // cout << "bounding box: " << xhost.bounding_box(xid) << endl;
  // cout << "line mbrs: " << xline_mbrs << endl;
  // cout << "line_list: " << endl << xline << endl;
  
  // Preconditions:

  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());

  require(!xline.empty());
  require(++xline.begin() != xline.end()); // At least 2 points.
  require(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));

  require(!xline_mbrs.empty());
  require(xhost.points().d_cells_contains(xline_mbrs.back()));

  require(xline.front().pt_id == xline_mbrs.back());  
  
  // Body:

  // Get the bounding box for the face.

  kd_bounding_box& lbox = xhost.bounding_box(xid);
 
  // Get local a local coordinate system for use with
  // bounding box clipping routine.

  int lu, lv;
  local_axes_clip_2d(xhost, xid, lu, lv);

  // Save an iterator pointing to the last line member previously inserted.

  id_list::iterator lmbr_itr = --xline_mbrs.end();
  
  scoped_index result; // Invalid by default.
  int lcode = kd_bounding_box::INSIDE;

  // Initially, the current segment is defined by 
  // xline.front() == xline_mbrs.back()
  // and the second member of xline.

  line_pt lpt0 = xline.front();
  xline.pop_front();

  while(!xline.empty())
  {
    // The current segment is defined by
    // lpt0 == xline_mbrs.back() and xline.front(),
    // with the following invariant:

    assertion(lpt0.pt_id == xline_mbrs.back());    
    assertion(lpt0.pt == kd_point::coords(xhost, lpt0.pt_id));

    // Ensure the second point has been created.

    if(xline.front().pt_id.is_valid())
    {
      // The second point has already been created;
      // make sure pt is consistent with pt_id.

      xline.front().pt = kd_point::coords(xhost, xline.front().pt_id);
    }
    else
    {
      // The second point has not been created yet.
      // Create it now, even though we may replace it
      // with an existing point later.

      xline.front().pt_id = kd_point::new_point(xhost, xline.front().pt);
    }

    assertion(xline.front().pt == kd_point::coords(xhost, xline.front().pt_id));

    // cout << "lpt0: " << lpt0;
    // cout << "  front: " << xline.front();
    // cout << "  back: " << xline_mbrs.back().internal_pod();
    // cout << endl;
    

    // Clip the segment against the edges of the face.

    clip_segment(xhost, xid, lbox, lu, lv, lpt0, xline);


    // cout << "lpt0: " << lpt0;
    // cout << "  front: " << xline.front();
    // cout << "  back: " << xline_mbrs.back().internal_pod();
    // cout << endl;

    // Check for intersection with contents; this change
    // either lpt0 or xline.front().

    bool lCD_is_first = (&xline_mbrs.front() == &xline_mbrs.back());
    intersect_contents(xhost, xid, lu, lv, lpt0, xline, lCD_is_first);

    // cout << "lpt0: " << lpt0;
    // cout << "  front: " << xline.front();
    // cout << "  back: " << xline_mbrs.back().internal_pod();
    // cout << "  size: " << xline_mbrs.size();
    // cout << endl;

    // The current segment is still lpt0 to xline.front().

    // lpt0 is usually the second point in the preceding
    // segment and hence the same as xline_mbrs.back(),
    // with two execeptions:
    // 1) When the first segment has extended to an intersection "before the beginning".
    // 2) When lpt0 has benn merged into another point.
    // Hence we have the following assertion:

    assertion( (lpt0.pt_id == xline_mbrs.back()) || (xline_mbrs.size() == 1) || !xhost.points().is_active(xline_mbrs.back()));
  
    if(lpt0.pt_id != xline_mbrs.back())
    {
      // The first segment has extended;
      // there is only one member in xline_mbrs,
      // but it is still the original first point;
      // the previous point has merged with another.
      // Either way replace it with the new first point.

      xline_mbrs.back() = lpt0.pt_id;
    }

    assertion((lpt0.pt_id == xline_mbrs.back()));

    // cout << "lpt0: " << lpt0;
    // cout << "  front: " << xline.front();
    // cout << "  back: " << xline_mbrs.back();
    // cout << endl;

    // The current segment has no further 
    // intersections; make it a line member
  
    create_segment(xhost, xline_mbrs, xline);  
    
    // We're finished with the current segment, Move on.

    if(xline.front().clip_code)
    {
      // Found intersection with edge.
      // We're finished with this face;
      // get the adjoining face on the 
      // other side of the exit edge.

      // cout << "Found an edge intersection; finished with this face." << endl;

      if(++xline.begin() == xline.end())
      {
        // The front of xline is the last point; 
        // we're fished with this line.

        xline.pop_front();
        result.invalidate();
      }
      else
      {
        // We're finished with this face but
        // there's at least two points (one segment) left.
        // Move to the next face.

        result = kd_face::adjacent_face(xhost, xid, xline);
      }
      
      break;
    }
    else
    {
      // Move to the next segment.

      // cout << "Moving to next segment." << endl;

      lpt0 = xline.front();
      xline.pop_front();      
    }
  }

  // Link the segments contained in this face.

  // cout << "Linking face to segments: ";
  
  base_space_poset& lbase = xhost.base_space();
  while(lmbr_itr != xline_mbrs.end())
  {
    if(xhost.segments().contains(*lmbr_itr))
    {
      lbase.new_link(xid, *lmbr_itr);
      // cout << "  " << lmbr_itr->internal_pod();
    }
    ++lmbr_itr;
  }

  // cout << "  done." << endl;

  // cout << endl << "Number of points left: " << xline.size() << endl;

  // Postconditions:

  ensure(result.is_valid() == !xline.empty());
  ensure(result.is_valid() ? xhost.faces().contains(result) : true);

  ensure(!xline_mbrs.empty());
  require(xhost.points().d_cells_contains(xline_mbrs.back()));

  ensure(xline.empty() || (++xline.begin() != xline.end())); // empty or at least two points
  ensure(xline.empty() || (xline.front().pt == kd_point::coords(xhost, xline.front().pt_id)));
  ensure(xline.empty() || (xline.front().pt_id == xline_mbrs.back()));  

  // Exit:

  // cout << "Leaving kd_face::insert_line." << endl;
  return result;
}

void
geometry::kd_face::
line_fragments(frag_list& xfrags) const
{
  // cout << endl << "Entering kd_face::line_fragments." << endl;

  // Preconditions:


  // Body:

  line_fragments(*_host, _id, xfrags);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::line_fragments." << endl;
  return;
}

void
geometry::kd_face::
line_fragments(const kd_lattice& xhost, const scoped_index& xid, frag_list& xfrags)
{
  // cout << endl << "Entering kd_face::line_fragments." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));

  // Body:

  scoped_index linvalid_id; // Invalid by default.
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  
  // Skip past the edges.

  for(int i=0; i<EDGE_CT; ++i)
  {
    litr.next();
  }  

  kd_line_fragment lfrag_prototype(xid);
  
  while(!litr.is_done())
  {
    // cout << litr.item() << "  " << xhost.base_space().member_name(litr.item()) << endl;
    
    scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);
    if(xhost.segments().contains(lid))
    {
      kd_segment::line_fragments(xhost, lid, lfrag_prototype, xfrags);
    }
    
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:
  
  // Exit:

  // cout << "Leaving kd_face::line_fragments." << endl << endl;
  return;
}

void
geometry::kd_face::
zones(id_list& xzones) const
{
  // cout << endl << "Entering kd_face::zones." << endl;

  // Preconditions:


  // Body:

  zones(*_host, _id, xzones);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::zones." << endl;
  return;
}

void
geometry::kd_face::
zones(const kd_lattice& xhost, const scoped_index& xid, id_list& xzones)
{
  // cout << endl << "Entering kd_face::zones." << endl;
  // cout << "id: " << xid << "  name: " << name(xhost, xid) << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());

  define_old_variable(size_type old_xzones_size = xzones.size());

  // Body:

  scoped_index linvalid_id; // Invalid by default.
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  
  // Skip past the edges.

  while(!litr.is_done())
  {
    scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);
    if(xhost.zones().contains(lid))
    {
      xzones.push_back(lid);
    }
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xzones.size() >= old_xzones_size);
  ensure(xzones.size() <= old_xzones_size + ZONE_CT);
  
  // Exit:

  // cout << "Leaving kd_face::zones." << endl;
  return;
}

void
geometry::kd_face::
segments(id_list& xsegments) const
{
  // cout << endl << "Entering kd_face::segments." << endl;

  // Preconditions:


  // Body:

  segments(*_host, _id, xsegments);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::segments." << endl;
  return;
}

void
geometry::kd_face::
segments(const kd_lattice& xhost, const scoped_index& xid, id_list& xsegments)
{
  // cout << endl << "Entering kd_face::segments." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  define_old_variable(size_type old_xsegments_size = xsegments.size());

  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  
  // Skip past the edges.

  for(int i=0; i<EDGE_CT; ++i)
  {
    litr.next();
  }

  while(!litr.is_done())
  {
    xsegments.push_back(xhost.base_space().member_id(litr.hub_pod(), false));
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xsegments.size() >= old_xsegments_size);
  
  // Exit:

  // cout << "Leaving kd_face::segments." << endl;
  return;
}

bool
geometry::kd_face::
is_empty() const
{
  // cout << endl << "Entering kd_face::is_empty." << endl;

  // Preconditions:

  require(precondition_of(is_empty(host(), id())));

  // Body:

  bool result = is_empty(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_empty(host(), id())));

  // Exit:

  // cout << "Leaving kd_face::is_empty." << endl;
  return result;
}

bool
geometry::kd_face::
is_empty(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_face::is_empty." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));

  // Body:

  bool result = xhost.base_space().cover_ct(LOWER, xid) <= EDGE_CT;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::is_empty." << endl;
  return result;
}

void
geometry::kd_face::
triangulate(const scoped_index& xsurface_id, bool xedge_fwd, bool xpolygon_fwd)
{
  // cout << endl << "Entering kd_face::triangulate." << endl;

  // Preconditions:

  require(precondition_of(triangulate(host(), id(), xsurface_id, xedge_fwd, xpolygon_fwd)));

  // Body:

  triangulate(*_host, _id, xsurface_id, xedge_fwd, xpolygon_fwd);

  // Postconditions:

  ensure(postcondition_of(triangulate(host(), id(), xsurface_id, xedge_fwd, xpolygon_fwd)));

  // Exit:

  // cout << "Leaving kd_face::triangulate." << endl;
  return;
}

void
geometry::kd_face::
triangulate(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xsurface_id, bool xedge_fwd, bool xpolygon_fwd)
{
  // cout << endl << "Entering kd_face::triangulate." << endl;
  // cout << "face: " << xid.pod() << "  " << name(xhost, xid) << endl;


  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.faces().contains(xid));
  require(xhost.leaves().contains(xid));
  require(xhost.surfaces().contains(xsurface_id));

  // Body:

  // Collect all the line fragments, from 
  // both the edges and the contents of the face.

  // Get the line fragments contained in the edges.
  // Mark the edges with invalid surface ids, see
  // use kd_line_fragment::assemble.

  kd_line_fragment lprototype(xid);
  lprototype.surface_id.invalidate();  

  scoped_index ledges[EDGE_CT];
  edges(xhost, xid, ledges);

//   for(int i=0; i<EDGE_CT; ++i)
//   {
//     cout << "edge " << i << " lower cover: " << xhost.base_space().cover_iterator(LOWER, ledges[i]) << endl;
//   }
  
  frag_list lefrags;
  kd_edge::line_fragments(xhost, ledges[0], lprototype, true, lefrags);
  kd_edge::line_fragments(xhost, ledges[1], lprototype, true, lefrags);
  kd_edge::line_fragments(xhost, ledges[2], lprototype, false, lefrags);
  kd_edge::line_fragments(xhost, ledges[3], lprototype, false, lefrags);


  // cout << "edge frags before reversal: " << endl << lefrags << endl;

  if(!xedge_fwd)
  {
    // Reverse the order of the fragments.

    for(frag_list::iterator lf=lefrags.begin(); lf!=lefrags.end(); ++lf)
    {
      lf->pt_ids.reverse();
    }
    
    lefrags.reverse();
  }

  // cout << "edge frags after reversal: " << endl << lefrags << endl;

  // Get the line fragments contained in the contents.

  frag_list lcfrags;
  line_fragments(xhost, xid, lcfrags);
  
  // cout << "contents frags: " << endl << lcfrags << endl;
  
  // Now assemble the fragments into closed loops,
  // each of which is the boundary of a surface
  // which is part of the boundary of a subvolume.

  // There are two kinds of fragments: fragments
  // from the edges of the face and fragments from
  // the lines in the contents of the face. The
  // assembly rules are:
  // 1) edge fragments are directional, they can 
  //    not be reversed
  // 2) contents fragments are bidirectional, they
  //    cn be reversed, and in fact should be used
  //    once in each direction.

  frag_list lofrags;
  kd_line_fragment::assemble(xhost, lefrags, lcfrags, lofrags);

  // cout << "output frags:" << endl << lofrags << endl;

  if(!xpolygon_fwd)
  {
    // Reverse the order of the fragments.

    for(frag_list::iterator lf=lofrags.begin(); lf!=lofrags.end(); ++lf)
    {
      lf->pt_ids.reverse();
    }
  }

  // cout << "output frags after reversal:" << endl << lofrags << endl;

  //   // Set the surface id.

  //   for(frag_list::iterator lf = lofrags.begin(); lf != lofrags.end(); ++lf)
  //   {
  //     lf->surface_id = xsurface_id;
  //   }
  
  //   // Triangulate the fragments.

  //   int lu, lv;
  //   local_axes(xhost, xid, lu, lv, xpolygon_fwd);
  //   kd_line_fragment::triangulate_non_convex(xhost, lofrags, xid, lu, lv);


  int lu, lv;
  local_axes(xhost, xid, lu, lv, xpolygon_fwd);

  // Set the surface id.

  for(frag_list::iterator lf = lofrags.begin(); lf != lofrags.end(); ++lf)
  {
    lf->surface_id = xsurface_id;
    lf->container_id = xid;
    lf->triangulate(xhost, lu, lv);
  }
      
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::triangulate." << endl;
  return;
}


void
geometry::kd_face::
triangles(id_list& xresult) const
{
  // cout << endl << "Entering kd_face::triangles." << endl;

  // Preconditions:

  require(precondition_of(triangles(host(), id(), xresult)));

  // Body:

  triangles(*_host, _id, xresult);

  // Postconditions:

  ensure(postcondition_of(triangles(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_face::triangles." << endl;
  return;
}

void
geometry::kd_face::
triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_face::triangles." << endl;
  // cout << "face: " << xid.pod() << "  " << name(xhost, xid) << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  
  // Skip past the edges.

  for(int i=0; i<EDGE_CT; ++i)
  {
    litr.next();
  }

  // Get the triangles.

  while(!litr.is_done())
  {
    scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);
    if(xhost.triangles().contains(lid))
    {
      xresult.push_back(lid);
    }
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::triangles." << endl;
  return;
}

void
geometry::kd_face::
triangle_members(id_list& xtriangle_mbrs) const
{
  // cout << endl << "Entering kd_face::triangle_members." << endl;

  // Preconditions:

  require(precondition_of(triangle_members(host(), id(), xtriangle_mbrs)));

  // Body:

  triangle_members(*_host, _id, xtriangle_mbrs);

  // Postconditions:

  ensure(postcondition_of(triangle_members(host(), id(), xtriangle_mbrs)));

  // Exit:

  // cout << "Leaving kd_face::triangle_members." << endl;
  return;
}

void
geometry::kd_face::
triangle_members(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangle_mbrs)
{
  // cout << endl << "Entering kd_face::triangle_members." << endl;
  // cout << "face: " << xid.pod() << "  " << name(xhost, xid) << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.leaves().contains(xid));

  // Body:

  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  
  // Skip past the edges.

  for(int i=0; i<EDGE_CT; ++i)
  {
    litr.next();
  }

  // Get the triangles.

  while(!litr.is_done())
  {
    scoped_index lid = xhost.base_space().member_id(litr.hub_pod(), false);
    if(xhost.triangles().contains(lid))
    {
      kd_triangle::members(xhost, lid, xtriangle_mbrs, true);
    }
    litr.next();
  }

  xhost.base_space().release_cover_id_space_iterator(litr);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::triangle_members." << endl;
  return;
}

void
geometry::kd_face::
local_axes(kd_lattice& xhost, const scoped_index& xid, int& xu, int& xv, bool xfwd)
{
  // cout << endl << "Entering kd_face::local_axes." << endl;

  // Preconditions:

  require(alignment(xhost, xid) != NOT_AXIS_ALIGNED);
  
  // Body:

  int lalignment = int_alignment(xhost, xid);
  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      xu = 1;
      xv = 2;
      break;
    case Y_AXIS_ALIGNED:
      xu = 2;
      xv = 0;
      break;
    case Z_AXIS_ALIGNED:
      xu = 0;
      xv = 1;
      break;
    default:
      break;
  }

  if(!xfwd)
  {
    int ltmp = xu;
    xu = xv;
    xv = ltmp;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::local_axes." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::kd_face::
kd_face()
{
  
  // Preconditions:

    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

void
geometry::kd_face::
remove_lower_cover(kd_lattice& xhost, scoped_index xid, scoped_index xedges[], id_list& xcontents)
{
  // Preconditions:

  require(unexecutable("xedges is an array with at least EDGE_CT entries"));
  require(xhost.base_space().state_is_read_accessible());
  require(xhost.faces().contains(xid));
  require(xhost.base_space().is_jim(xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();

  int i=0;
  xcontents.clear();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  while(!litr.is_done())
  {
    if(i < EDGE_CT)
    {
      // Edges are the first EDGE_CT members of the lower cover.

      xedges[i] = xhost.base_space().member_id(litr.hub_pod(), false);
    }
    else
    {
      // The contents of the face are any remaining members.

      xcontents.push_back(xhost.base_space().member_id(litr.hub_pod(), false));
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
geometry::kd_face::
new_subface(kd_lattice& xhost, 
            const scoped_index& xold_face_id, 
            const scoped_index xedge_ids[], 
            int xi)
{
  // cout << endl << "Entering kd_face::new_subface." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.faces().contains(xold_face_id));

  // Body:

  // Create the new subface.

  kd_alignment lalignment = alignment(xhost, xold_face_id);
  scoped_index result;

  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      result = xhost.x_faces().new_member();
      break;
    case Y_AXIS_ALIGNED:
      result = xhost.y_faces().new_member();
      break;
    case Z_AXIS_ALIGNED:
      result = xhost.z_faces().new_member();
      break;
    default:
      post_fatal_error_message("Unsupported face alignment.");
  }      

  // Link the subface to its edges.

  base_space_poset& lbase = xhost.base_space();  
  for(int i=0; i<EDGE_CT; ++i)
  {
    const scoped_index& ledge_id = xedge_ids[i];
    if(i == xi)
    {
      // The current edge was an edge in the old face,
      // replace the old face in the upper cover of the edge.

      lbase.replace_cover_member(xold_face_id, result, UPPER, ledge_id);
    }
    else
    {
      // The current edge is a new edge; 
      // just insert the new face in its upper cover.

      lbase.insert_cover_member(result, UPPER, ledge_id);
    }

    // Insert the edge in the lower cover of the face.

    lbase.insert_cover_member(ledge_id, LOWER, result);
  }  

  // Set the splitting plane to default value.

  kd_plane lp;
  xhost.put_plane(result, lp);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::new_subface." << endl;
  return result;
}

void
geometry::kd_face::
refine_edges_0_and_2(kd_lattice& xhost, 
                     scoped_index xid, 
                     const kd_plane& xp, 
                     scoped_index xnew_ids[])
{
  // cout << endl << "Entering kd_face::refine_x_const_by_z_const." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.faces().contains(xid));
  require(in_bounds(xhost, xid, xp));

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  scoped_index& lnew_face_0_id = xnew_ids[0];
  scoped_index& lnew_face_1_id = xnew_ids[1];
  scoped_index& lnew_edge_id = xnew_ids[2];
  const scoped_index& lold_face_id = xid;

  base_space_poset& lbase = xhost.base_space();

  if(lbase.is_jim(xid))
  {
    // This face has not been refined previously refined.

    // Get the existing edges while removing them from lower cover;
    // this leaves old face in upper cover of edges.

    scoped_index lold_edge_ids[EDGE_CT];
    id_list lcontents;
    remove_lower_cover(xhost, xid, lold_edge_ids, lcontents);

    // Refine edge 0.

    scoped_index ledge_0_new_ids[3];
    kd_edge::refine(xhost, lold_edge_ids[0], xp, ledge_0_new_ids);

    // Refine edge 2.

    scoped_index ledge_2_new_ids[3];
    kd_edge::refine(xhost, lold_edge_ids[2], xp, ledge_2_new_ids);

    // Create the new edge from the two new vertices
    // which were created by refining the edges.

    scoped_index lv_ids[kd_edge::VERTEX_CT];
    lv_ids[0] = ledge_0_new_ids[2];
    lv_ids[1] = ledge_2_new_ids[2];

    // Alignment for new edge; same as edges 1, 3.

    static const kd_alignment lnew_edge_alignment[NOT_AXIS_ALIGNED] =
      {
        Y_AXIS_ALIGNED, // X aligned face
        Z_AXIS_ALIGNED, // Y aligned face
        Y_AXIS_ALIGNED  // Z aligned face
      };
    
    // $$SCRIBBLE: replace these calculations with kd_plane::intersection_alignment calls.

    kd_alignment lface_alignment = alignment(xhost, xid);
    assertion(lface_alignment != NOT_AXIS_ALIGNED);
    kd_alignment ledge_alignment = lnew_edge_alignment[lface_alignment];    
    int lother_alignment = other_int_alignment(lface_alignment, ledge_alignment);
    
    lnew_edge_id = kd_edge::new_edge(xhost, lv_ids, ledge_alignment);

    // Set the bounding box for the new edge.
    // Note that we copy the old box here rather than
    // keeping a reference because the calls to 
    // put_bounding_box may force reallocation.

    kd_bounding_box lold_box = xhost.bounding_box(lold_face_id);
    kd_bounding_box lbox;

    lbox = lold_box;
    lbox.lb()[lother_alignment] = xp.distance();
    lbox.ub()[lother_alignment] = xp.distance();
    xhost.put_bounding_box(lnew_edge_id, lbox);
  
    // Create the first new face

    scoped_index le_ids[kd_face::EDGE_CT];
    le_ids[0] = ledge_0_new_ids[0];
    le_ids[1] = lnew_edge_id;
    le_ids[2] = ledge_2_new_ids[0];
    le_ids[3] = lold_edge_ids[3];
    lnew_face_0_id = kd_face::new_subface(xhost, lold_face_id, le_ids, 3);
 
    // Set the bounding box for the first subface.

    lbox = lold_box;
    lbox.ub()[lother_alignment] = xp.distance();
    xhost.put_bounding_box(lnew_face_0_id, lbox);
  
    // Create the second new face

    le_ids[0] = ledge_0_new_ids[1];
    le_ids[1] = lold_edge_ids[1];
    le_ids[2] = ledge_2_new_ids[1];
    le_ids[3] = lnew_edge_id;
    lnew_face_1_id = kd_face::new_subface(xhost, lold_face_id, le_ids, 1);

    // Set the bounding box for the second subface.

    lbox = lold_box;
    lbox.lb()[lother_alignment] = xp.distance();
    xhost.put_bounding_box(lnew_face_1_id, lbox);

    // Sort the contents into the two subfaces and the splitting edge.

    if(!lcontents.empty())
    {
      split_contents(xhost, lold_face_id, xnew_ids, xp, lcontents);
    }
    
    // Restore original lower cover, but with subfaces 0, 1 
    // replacing edges 3, 1, respectively.
    // With this order, the i-th member of the lower cover
    // is either the i-th edge, or the subface that contains the i-th edge.
    // $$SCRIBBLE: assumes lower cover is empty.

    lbase.insert_cover_member(lold_edge_ids[0], LOWER, lold_face_id);
    lbase.new_link(lold_face_id, lnew_face_1_id);
    lbase.insert_cover_member(lold_edge_ids[2], LOWER, lold_face_id);
    lbase.new_link(lold_face_id, lnew_face_0_id);

    // Existing face is no longer a leaf or a jim.

    xhost.leaves().remove_member(lold_face_id, false);
    lbase.jims().remove_member(lold_face_id);
  }
  else
  {
    // This face is already refined.
    // Get the ids of the two subfaces and the edge between them.

    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid); // 0
    litr.next(); // 1
    
    xnew_ids[1] = xhost.base_space().member_id(litr.hub_pod(), false);
    
    litr.next(); // 2
    litr.next(); // 3

    xnew_ids[0] = xhost.base_space().member_id(litr.hub_pod(), false);

    // The edge between is edge 1 of the first subface.

    xnew_ids[2] = edge(xhost, xnew_ids[0], 1);

    lbase.release_cover_id_space_iterator(litr);
  }

  // Postconditions:


  ensure(xhost.faces().contains(xnew_ids[0]));
  ensure(xhost.faces().contains(xnew_ids[1]));
  ensure(xhost.edges().contains(xnew_ids[2]));
  ensure(xnew_ids[2] == edge(xhost, xnew_ids[0], 1));
  ensure(xnew_ids[2] == edge(xhost, xnew_ids[1], 3));

  // Exit:

  // cout << "Leaving kd_face::refine_x_const_by_y_const." << endl;
  return;
}

void
geometry::kd_face::
refine_edges_1_and_3(kd_lattice& xhost, 
                     scoped_index xid, 
                     const kd_plane& xp, 
                     scoped_index xnew_ids[])
{
  // cout << endl << "Entering kd_face::refine_x_const_by_y_const." << endl;
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.faces().contains(xid));
  require(in_bounds(xhost, xid, xp));

  // xid passed by value to ensure the following:
  //  require((&xid != &xnew_ids[0]) && (&xid != &xnew_ids[1]) && (&xid != &xnew_ids[2]));
  
  // Body:

  scoped_index& lnew_face_0_id = xnew_ids[0];
  scoped_index& lnew_face_1_id = xnew_ids[1];
  scoped_index& lnew_edge_id = xnew_ids[2];
  const scoped_index& lold_face_id = xid;

  base_space_poset& lbase = xhost.base_space();

  if(lbase.is_jim(xid))
  {
    // This face has not been refined previously refined.

    // Get the existing edges while removing them from lower cover;
    // this leaves old face in upper cover of edges.

    scoped_index lold_edge_ids[EDGE_CT];
    id_list lcontents;
    remove_lower_cover(xhost, xid, lold_edge_ids, lcontents);

    // Refine edge 1.

    scoped_index ledge_1_new_ids[3];
    kd_edge::refine(xhost, lold_edge_ids[1], xp, ledge_1_new_ids);

    // Refine edge 3.

    scoped_index ledge_3_new_ids[3];
    kd_edge::refine(xhost, lold_edge_ids[3], xp, ledge_3_new_ids);

    // Create the new edge from the two new vertices
    // which were created by refining the edges.

    scoped_index lv_ids[kd_edge::VERTEX_CT];
    lv_ids[0] = ledge_3_new_ids[2];
    lv_ids[1] = ledge_1_new_ids[2];

    static const kd_alignment lnew_edge_alignment[NOT_AXIS_ALIGNED] =
      {
        Z_AXIS_ALIGNED, // X aligned face
        X_AXIS_ALIGNED, // Y aligned face
        X_AXIS_ALIGNED  // Z aligned face
      };
    
    kd_alignment lface_alignment = alignment(xhost, xid);
    assertion(lface_alignment != NOT_AXIS_ALIGNED);
    kd_alignment ledge_alignment = lnew_edge_alignment[lface_alignment];
    int lother_alignment = other_int_alignment(lface_alignment, ledge_alignment);


    lnew_edge_id = kd_edge::new_edge(xhost, lv_ids, ledge_alignment);

    // Set the bounding box for the new edge.
    // Note that we copy the old box here rather than
    // keeping a reference because the calls to 
    // put_bounding_box may force reallocation.

    kd_bounding_box lold_box = xhost.bounding_box(lold_face_id);
    kd_bounding_box lbox;

    lbox = lold_box;
    lbox.lb()[lother_alignment] = xp.distance();
    lbox.ub()[lother_alignment] = xp.distance();
    xhost.put_bounding_box(lnew_edge_id, lbox);
  
    // Create the first new face

    scoped_index le_ids[kd_face::EDGE_CT];
    le_ids[0] = lold_edge_ids[0];
    le_ids[1] = ledge_1_new_ids[0];
    le_ids[2] = lnew_edge_id;
    le_ids[3] = ledge_3_new_ids[0];
    lnew_face_0_id = kd_face::new_subface(xhost, lold_face_id, le_ids, 0);

    // Set the bounding box for the first subface.

    lbox = lold_box;
    lbox.ub()[lother_alignment] = xp.distance();
    xhost.put_bounding_box(lnew_face_0_id, lbox);
  
    // Create the second new face

    le_ids[0] = lnew_edge_id;
    le_ids[1] = ledge_1_new_ids[1];
    le_ids[2] = lold_edge_ids[2];
    le_ids[3] = ledge_3_new_ids[1];
    lnew_face_1_id = kd_face::new_subface(xhost, lold_face_id, le_ids, 2);

    // Set the bounding box for the second subface.

    lbox = lold_box;
    lbox.lb()[lother_alignment] = xp.distance();
    xhost.put_bounding_box(lnew_face_1_id, lbox);

    // Sort the contents into the two subfaces and the splitting edge.

    if(!lcontents.empty())
    {
      split_contents(xhost, lold_face_id, xnew_ids, xp, lcontents);
    }

    // Restore original lower cover, but with subface 0, 1
    // replacing edges 0, 2, respectively.
    // With this order, the i-th member of the lower cover
    // is either the i-th edge, or the subface that contains the i-th edge.

    lbase.new_link(lold_face_id, lnew_face_0_id);
    lbase.insert_cover_member(lold_edge_ids[1], LOWER, lold_face_id);
    lbase.new_link(lold_face_id, lnew_face_1_id);
    lbase.insert_cover_member(lold_edge_ids[3], LOWER, lold_face_id);

    // Existing face is no longer a leaf or a jim.

    xhost.leaves().remove_member(lold_face_id, false);
    lbase.jims().remove_member(lold_face_id);
  }
  else
  {
    // This face is already refined.
    // Get the ids of the two subfaces and the edge between them.

    index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid); // 0
    
    xnew_ids[0] = xhost.base_space().member_id(litr.hub_pod(), false);
    
    litr.next(); // 1
    litr.next(); // 2

    xnew_ids[1] = xhost.base_space().member_id(litr.hub_pod(), false);

    // The edge between is edge 0 of the second subface.

    xnew_ids[2] = edge(xhost, xnew_ids[1], 0);

    lbase.release_cover_id_space_iterator(litr);
  }

  // Postconditions:

  ensure(xhost.faces().contains(xnew_ids[0]));
  ensure(xhost.faces().contains(xnew_ids[1]));
  ensure(xhost.edges().contains(xnew_ids[2]));
  ensure(xnew_ids[2] == edge(xhost, xnew_ids[0], 2));
  ensure(xnew_ids[2] == edge(xhost, xnew_ids[1], 0));

  // Exit:

  // cout << "Leaving kd_face::refine_x_const_by_y_const." << endl;
  return;
}

void
geometry::kd_face::
split_contents(kd_lattice& xhost, 
               const scoped_index& xold_face_id, 
               const scoped_index xnew_ids[], 
               const kd_plane& xp, 
               id_list& xcontents)
{
  // cout << endl << "Entering kd_face::split_contents." << endl;

  // cout << "face: " << xold_face_id.internal_pod();
  // cout << "  contents:" << xcontents << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.faces().contains(xnew_ids[0]));
  require(xhost.faces().contains(xnew_ids[1]));
  require(xhost.edges().contains(xnew_ids[2]));

  // Body:

  base_space_poset& lbase = xhost.base_space();

  // Get ids of coordinate components for face alignment,
  // plane alignment, and edge alignment.

  int lf_id = int_alignment(xhost, xnew_ids[0]);
  int lp_id = xp.int_alignment();
  int le_id = xp.intersection_int_alignment(lf_id);
  
  scoped_index lseg_id;
  scoped_index lpt_ids[kd_segment::POINT_CT];
  scoped_index& lpt0_id = lpt_ids[0];
  scoped_index& lpt1_id = lpt_ids[1];

  e3_lite lpts[kd_segment::POINT_CT];
  e3_lite& lpt0 = lpts[0];
  e3_lite& lpt1 = lpts[1];  


  while(!xcontents.empty())
  {
    lseg_id = xcontents.front();
    kd_segment::points(xhost, lseg_id, lpt_ids, lpts);

    // cout << "processing segment: " << lseg_id.internal_pod();
    // cout << "  " << lbase.member_name(lseg_id);
    // cout << "  lpt0: " << lpt0;
    // cout << "  lpt1: " << lpt1;
    // cout << "  splitting plane: " << xp << endl;

    // $$SCRIBBLE: what if both points are on the splitting plane>

    int lcode0 = xp.on_code(lpt0, xhost.point_tolerance());
    // cout << "lcode0: " << kd_plane::on_code(lcode0) << endl;

    if(lcode0 == kd_plane::ON)
    {
      // The first point is on the splitting plane;
      // link the splitting edge to it.

      // cout << "inserting pt0: " << lpt0_id.internal_pod() << "  in splitting edge " << xnew_ids[2].internal_pod() << endl;

      kd_edge::insert_point_no_intersection(xhost, xnew_ids[2], lpt0_id);
    }

    int lcode1 = xp.on_code(lpt1, xhost.point_tolerance());
    // cout << "lcode1: " << kd_plane::on_code(lcode1) << endl;

    if(lcode1 == kd_plane::ON)
    {
      // The second point is on the splitting plane;
      // link the splitting edge to it.
      // We don't want inserting the edge to induce 
      // intersections between existing segments, 
      // so use insert_point_no_intersection.

      // cout << "inserting pt1: " << lpt1_id.internal_pod() << "  in splitting edge " << xnew_ids[2].internal_pod() << endl;

      kd_edge::insert_point_no_intersection(xhost, xnew_ids[2], lpt1_id);
    }
    
    int lcode = lcode0 | lcode1;

    // cout << "lcode: " << kd_plane::on_code(lcode ) << endl;    
    
    if((lcode == kd_plane::BACK) || (lcode == kd_plane::ON_BACK))
    {
      // Both points are behind the plane, or one point 
      // is behind and one point is on the plane; 
      // insert the segment in the first subface.

      // cout << "inserting segment: " << lseg_id << " in back subface " << xnew_ids[0].internal_pod() << endl;

      // cout << "upper cover: ";
      // cover_set_iterator ldbg_itr = lbase.cover_iterator(UPPER, lseg_id);
      // while(!ldbg_itr.is_done())
      // {
      //  cout << "  " << ldbg_itr.item().internal_pod();
      //  ldbg_itr.next();
      // }
      // cout << endl;
      
      lbase.insert_cover_member(lseg_id, LOWER, xnew_ids[0]);

      assertion(lbase.cover_contains_member(UPPER, lseg_id, xold_face_id));

      lbase.replace_cover_member(xold_face_id, xnew_ids[0], UPPER, lseg_id);

      assertion(!lbase.cover_contains_member(LOWER, xold_face_id, lseg_id));
      
    }
    else if((lcode == kd_plane::FRONT) || (lcode == kd_plane::ON_FRONT))
    {
      // Both points are in front of the plane, or one point 
      // is in front and one point is on the plane; 
      // insert the segment in the second subface.

      // cout << "inserting segment: " << lseg_id << " in front subface " << xnew_ids[1].internal_pod() << endl;

      // cout << "upper cover: ";
      //       cover_set_iterator ldbg_itr = lbase.cover_iterator(UPPER, lseg_id);
      //       while(!ldbg_itr.is_done())
      //       {
      //         cout << "  " << ldbg_itr.item().internal_pod();
      //         ldbg_itr.next();
      //       }
      // cout << endl;

      lbase.insert_cover_member(lseg_id, LOWER, xnew_ids[1]);

      assertion(lbase.cover_contains_member(UPPER, lseg_id, xold_face_id));

      lbase.replace_cover_member(xold_face_id, xnew_ids[1], UPPER, lseg_id);

      assertion(!lbase.cover_contains_member(LOWER, xold_face_id, lseg_id));

    }
    else if( lcode == kd_plane::ON)
    {
      // Both points lie on the edge.
      // $$SCRIBBLE: this one is a problem because
      // we can't currently deal with segments contained in edges,
      // if a segment covers one of the vertices in the edge we
      // lose the connectivity of the edge. Perhaps we can deal with
      // his case using the link-to-vertex-or-segment-contain-vertex
      // policy that we use with subedges, if we require the segment
      // contain only 1 vertex, i.e. it is not identical to the edge.
      // We can enforce this policy by subdividing the segment if it
      // identical to the edge.

      post_warning_message("kd_face::split_contents: segment contained in edge.");
    }
    else
    {
      // The segment crosses the plane; compute the intersection.

      assertion(lcode == kd_plane::CROSS);

      // cout << "splitting  segment: " << lseg_id << " across subfaces" << endl;

      e3_lite lpt;
      vd_value_type lp_dist = xp.distance();

      lpt[le_id] = lpt0[le_id] + (lpt1[le_id] - lpt0[le_id])*(lp_dist - lpt0[lp_id])/(lpt1[lp_id] - lpt0[lp_id]);
      lpt[lp_id] = lp_dist;
      lpt[lf_id] = lpt0[lf_id];

      // $$SCRIBBLE: deal with point tolerance here.

      // If intersection is within tolerance of first point,
      // move first point to intersection

      // If intersection is within tolerance of second point,
      // move second point to intersection.

      // What if intersection is within tolerance of both points?

      // Insert the point in the splitting edge.
      // We don't want inserting the edge to induce 
      // intersections between existing segments, 
      // so use insert_point_no_intersection.

      scoped_index lpt_id;
      kd_edge::insert_point_no_intersection(xhost, xnew_ids[2], lpt, lpt_id);
      // kd_edge::insert_point(xhost, xnew_ids[2], lpt, lpt_id);
      
      // New point refines the segment.

      scoped_index lnew_seg_id;        
     
      // cout << "back box: " << xhost.bounding_box(xnew_ids[0]) << endl;
      // cout << "front box: " << xhost.bounding_box(xnew_ids[1]) << endl;
        
      // cout << " pt0: " << lpt0 << endl;
      // cout << " pt: " << lpt << endl;
      // cout << " pt1: " << lpt1 << endl;

      if(lcode0 == kd_plane::BACK)
      {
        // The segment crosses the plane from back to front

        // cout << "splitting back to front" << endl;
        
        // Put the first segment in the back subface and
        // the second segment in the front subface.

        kd_segment::refine(xhost, lseg_id, lpt_id, xnew_ids[0], xnew_ids[1], lnew_seg_id);

        // cout << "inserted segment " << lseg_id.internal_pod() << " in face " << xnew_ids[0].internal_pod() << endl;
        // cout << "inserted segment " << lnew_seg_id.internal_pod() << " in face " << xnew_ids[1].internal_pod() << endl;
      }
      else
      {
        // The segment crosses the plane from front to back
        
        // Put the first segment in the front subface and
        // the second segment in the back subface.

        // cout << "splitting front to back" << endl;        

        kd_segment::refine(xhost, lseg_id, lpt_id, xnew_ids[1], xnew_ids[0], lnew_seg_id);

        // cout << "inserted segment " << lseg_id.internal_pod() << " in face " << xnew_ids[1].internal_pod() << endl;
        // cout << "inserted segment " << lnew_seg_id.internal_pod() << " in face " << xnew_ids[0].internal_pod() << endl;
      }
    } // end if(lcode) .. else
    
    // Move to the next segment.

    xcontents.pop_front();
    
  } // end while
  

  // Postconditions:

  ensure(xcontents.empty());
  
  // Exit:

  // cout << "Leaving kd_face::split_contents." << endl << endl;
  return;
}

#define POINT_TO_VERTEX_WELDING
#ifdef POINT_TO_VERTEX_WELDING

sheaf::scoped_index
geometry::kd_face::
adjacent_face(kd_lattice& xhost, const scoped_index& xid, line_list& xline)
{
  // cout << endl << "Entering kd_face::adjacent_face." << endl;
  // cout << "face: " << xid.pod() << "  " << name(xhost, xid) << endl;
  // cout << "line: " << endl << xline << endl;
  
  // Preconditions:

  require(!xline.empty());
  require(++xline.begin() != xline.end()); // At least two points.
  
  // Body:

  // Get the bounding box for the face.

  kd_bounding_box& lbox = xhost.bounding_box(xid);
 
  // Get local a local coordinate system for use with
  // bounding box clipping routine.

  int lu, lv;
  local_axes_clip_2d(xhost, xid, lu, lv);

  // We need to re-evaluate the clipping code so we can detect
  // vertex versus edge adjacency.

  int lcode = lbox.out_code_2d(xline.front().pt, lu, lv);

  e3_lite& lnext_pt = (++xline.begin())->pt;
  bool lnext_left  = lnext_pt[lu] < lbox.lb()[lu];
  bool lnext_right = lnext_pt[lu] > lbox.ub()[lu];
  bool lnext_bot   = lnext_pt[lv] < lbox.lb()[lv];
  bool lnext_top   = lnext_pt[lv] > lbox.ub()[lv];

  scoped_index result, ledge, lface;

  if(lcode & kd_bounding_box::LEFT)
  {
    if(lcode & kd_bounding_box::TOP)
    {
      // Line exits through left top;
      // need to look at next point.

      if(lnext_left && lnext_top)
      {
        // cout << "left and top" << endl;
        
        // Left ...

        ledge = edge(xhost, xid, 3);
        result = kd_edge::other_face(xhost, ledge, xid);

        // ... and top

        ledge = edge(xhost, result, 2);
        result = kd_edge::other_face(xhost, ledge, result);
      }
      else if(lnext_left)
      {
        // Just left

        // cout << "Just left" << endl;

        ledge = edge(xhost, xid, 3);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else if(lnext_top)
      {
        // Just top

        // cout << "Just top" << endl;

        ledge = edge(xhost, xid, 2);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else
      {
        // Line returns through current face.

        // cout << "Line returns through current face." << endl;

        result = xid;
      }
    }
    else if(lcode & kd_bounding_box::BOTTOM)
    {
      // Line exits through left bottom;
      // need to look at next point.

      if(lnext_left && lnext_bot)
      {
        // cout << "left and bottom" << endl;
        
        // Left ...
    
        ledge = edge(xhost, xid, 3);
        result = kd_edge::other_face(xhost, ledge, xid);

        // ... and bottom        

        ledge = edge(xhost, result, 0);
        result = kd_edge::other_face(xhost, ledge, result);
      }
      else if(lnext_left)
      {
        // Just left

        // cout << "Just left" << endl;

        ledge = edge(xhost, xid, 3);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else if(lnext_bot)
      {
        // Just bottom.

        // cout << "just bottom" << endl;
    
        ledge = edge(xhost, xid, 0);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else
      {
        // Line returns through current face.

        result = xid;

        // cout << "Line returns through current face." << endl;
      }
    }
    else
    {
      // Just left, but still have to look at next pt.

      // cout << "Just left" << endl;

      if(lnext_left)
      {
        ledge = edge(xhost, xid, 3);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else
      {
        // Line returns thorugh current face.

        result = xid;

        // cout << "Line returns through current face." << endl;
      }
    }    
  } // end if left
  else if(lcode & kd_bounding_box::RIGHT)
  {
    if(lcode & kd_bounding_box::TOP)
    {
      // Line exits through right top.

      if(lnext_right && lnext_top)
      {
        // cout << "right and top" << endl;
        
        // Right ...

        ledge = edge(xhost, xid, 1);
        result = kd_edge::other_face(xhost, ledge, xid);

        // ... and top

        ledge = edge(xhost, result, 2);
        result = kd_edge::other_face(xhost, ledge, result);
      }
      else if(lnext_right)
      {
        // Just right.

        // cout << "Just right" << endl;

        ledge = edge(xhost, xid, 1);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else if(lnext_top)
      {
        // Just top

        // cout << "just top" << endl;

        ledge = edge(xhost, xid, 2);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else
      {
        // Line returns through current face.

        // cout << "Line returns through current face." << endl;

        result = xid;
      }
    }
    else if(lcode & kd_bounding_box::BOTTOM)
    {
      // Line exits through right bottom;
      // need to look at next point.

      if(lnext_right && lnext_bot)
      {
        // cout << "right and bottom" << endl;
        
        // Right ...
    
        ledge = edge(xhost, xid, 1);
        result = kd_edge::other_face(xhost, ledge, xid);

        // ... and bottom        

        ledge = edge(xhost, result, 0);
        result = kd_edge::other_face(xhost, ledge, result);
      }
      else if(lnext_right)
      {
        // Just right.

        // cout << "Just right" << endl;

        ledge = edge(xhost, xid, 1);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else if(lnext_bot)
      {
        // Just bottom.

        // cout << "just bottom" << endl;
    
        ledge = edge(xhost, xid, 0);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else
      {
        // Line returns through current face.

        result = xid;

        // cout << "Line returns through current face." << endl;
      }
    }
    else
    {
      // Just right.

      // cout << "Just right" << endl;
    
      if(lnext_right)
      {
        ledge = edge(xhost, xid, 1);
        result = kd_edge::other_face(xhost, ledge, xid);
      }
      else
      {
        // Line returns through current face.

        result = xid;

        // cout << "Line returns through current face." << endl;
      }      
    }
  } // end if right
  else if(lcode & kd_bounding_box::TOP)
  {
    // cout << "Just top" << endl;

    if(lnext_top)
    {
      ledge = edge(xhost, xid, 2);
      result = kd_edge::other_face(xhost, ledge, xid);
    }
    else
    {
      // Line returns through current face.

      result = xid;

      // cout << "Line returns through current face." << endl;
    }    
  }
  else
  {
    assertion(lcode & kd_bounding_box::BOTTOM);
    
    // cout << "Just bottom" << endl;
    
    if(lnext_bot)
    {
      ledge = edge(xhost, xid, 0);
      result = kd_edge::other_face(xhost, ledge, xid);
    }
    else
    {
      // Line returns through current face.

      result = xid;

      // cout << "Line returns through current face." << endl;
    }    
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::adjacent_face." << endl;
  return result;
}

#else

// sheaf::scoped_index
// geometry::kd_face::
// adjacent_face(kd_lattice& xhost, const scoped_index& xid, int xcode)
// {
//   cout << endl << "Entering kd_face::adjacent_face." << endl;
//   cout << "face: " << xid.pod() << "  " << name(xhost, xid) << endl;
//   cout << "clip codes: " << parse_out_code_2d(xcode) << endl;

//   // Preconditions:


//   // Body:

//   // $$SCRIBBLE: ERROR if point represented by xcode is
//   // at a vertex, we have to look at the next point
//   // in the line to decide where to go.

//   scoped_index result, ledge, lface;

//   if(xcode & kd_bounding_box::LEFT)
//   {
//     cout << "left ";
    
//     ledge = edge(xhost, xid, 3);
//     result = kd_edge::other_face(xhost, ledge, xid);

//     if(xcode & kd_bounding_box::TOP)
//     {
//       cout << " and top";
      
//       ledge = edge(xhost, result, 2);
//       result = kd_edge::other_face(xhost, ledge, result);
//     }
//     else if(xcode & kd_bounding_box::BOTTOM)
//     {
//       cout << " and bottom";
      
//       ledge = edge(xhost, result, 0);
//       result = kd_edge::other_face(xhost, ledge, result);
//     }
//     cout << endl;
//   }
//   else if(xcode & kd_bounding_box::RIGHT)
//   {
//     ledge = edge(xhost, xid, 1);
//     result = kd_edge::other_face(xhost, ledge, xid);
//     cout << "right";
    
//     if(xcode & kd_bounding_box::TOP)
//     {
//       cout << " and top";
      
//       ledge = edge(xhost, result, 2);
//       result = kd_edge::other_face(xhost, ledge, result);
//     }
//     else if(xcode & kd_bounding_box::BOTTOM)
//     {
//       cout << " and bottom";
      
//       ledge = edge(xhost, result, 0);
//       result = kd_edge::other_face(xhost, ledge, result);
//     }
//     cout << endl;
//   }
//   else if(xcode & kd_bounding_box::TOP)
//   {
//     cout << "top" << endl;
    
//     ledge = edge(xhost, xid, 2);
//     result = kd_edge::other_face(xhost, ledge, xid);
//   }
//   else
//   {
//     assertion(xcode & kd_bounding_box::BOTTOM);
    
//     cout << "bottom" << endl;
    
//     ledge = edge(xhost, xid, 0);
//     result = kd_edge::other_face(xhost, ledge, xid);
//   }
    

//   // Postconditions:


//   // Exit:

//   cout << "Leaving kd_face::adjacent_face." << endl;
//   return result;
// }

#endif

void
geometry::kd_face::
local_axes_clip_2d(kd_lattice& xhost, const scoped_index& xid, int& xu, int& xv)
{
  // cout << endl << "Entering kd_face::local_axes_clip_2d." << endl;

  // Preconditions:

  require(alignment(xhost, xid) != NOT_AXIS_ALIGNED);
  
  // Body:  
  
  // We have to choose local coordinates
  // for the face such that the edge
  // codes LEFT, RIGHT, TOP, BOTTOM
  // in kd_bounding_box::clip_2d are
  // consistent with the edge assignments
  // in kd_face::adjacent_face. This in turn
  // requires consistency with the order
  // edges are labeled in each of our face
  // alignments. In particular, our choice 
  // for orientation of the x aligned faces 
  // is left-handed, so we have to choose 
  // left-handed u,v here. We also have to
  // a left-handed orientation for the y
  // aligned faces, even though the orientation
  // of the y aligned faces is right handed.
  // This works, but it is tricky and it would
  // be good to have some simpler more consistent
  // treatment.

  int lalignment = int_alignment(xhost, xid);
  switch(lalignment)
  {
    case X_AXIS_ALIGNED:
      xu = 2; // left-handed.
      xv = 1;
      break;
    case Y_AXIS_ALIGNED:
      xu = 0; // left-handed.
      xv = 2;
      break;
    case Z_AXIS_ALIGNED:
      xu = 0;
      xv = 1;
      break;
    default:
      break;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_face::local_axes_clip_2d." << endl;
  return;
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_face::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_face*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_face*
geometry::kd_face::
clone() const
{
  kd_face* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_face();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_face&
geometry::kd_face::
operator=(const kd_face& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_face&
geometry::kd_face::
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
geometry::kd_face::
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
operator << (ostream& xos, const kd_face& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  const kd_lattice& lkdl = xn.host();
  const base_space_poset& lbase = xn.host().base_space();
  

  xos << "face " << xn.host().faces().id_space().pod(xn.id());
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
    xos << "   " << lbase.member_name(xn.host().base_space().member_id(litr.hub_pod(), false));
    litr.next();
  }
  xos << endl << endl;
  lbase.release_cover_id_space_iterator(litr);

  scoped_index lids[kd_face::EDGE_CT];

  xos << "\tedges:";
  xn.edges(lids);
  for(int i=0; i<kd_face::EDGE_CT; ++i)
  {
    xos << "   " << lbase.member_name(lids[i]);
    xos << "   " << lkdl.edges().id_space().pod(lids[i]);
  }
  xos << endl << endl;

  xos << "\tvertices:";
  xn.vertices(lids);
  for(int i=0; i<kd_face::VERTEX_CT; ++i)
  {
    xos << "   " << lbase.member_name(lids[i]);
  }
  xos << endl << endl;

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const kd_face::line_pt& xn)
{
  // Preconditions:

  // Body:

  xos << " pt:" << xn.pt;
  xos << " pt_id: " << xn.pt_id;
  xos << " clip_code: " << xn.clip_code;
  xos << " itr:";
  if(!xn.contents_itr.is_done())
  {
    xos << " " << xn.contents_itr.hub_pod();
  }
  
  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const kd_face::line_list& xn)
{
  // Preconditions:

  // Body:

  for(line_list::const_iterator i = xn.begin(); i != xn.end(); ++i)
  {
    xos << *i << endl;
  }
  
  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_face& xn, bool xinclude_shallow)
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
