

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_segment

#ifndef KD_SEGMENT_H
#define KD_SEGMENT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef KD_MEMBER_H
#include "kd_member.h"
#endif
 

namespace fiber_bundle
{
  class e3_lite;
}
  
namespace geometry
{
 
  class kd_lattice;
  
///
/// Linear segment in the contents part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_segment : public kd_member
{

  // ===========================================================
  /// @name KD_SEGMENT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{POINT_CT = 2, SUBSEGMENT_CT = 2};

  ///
  /// The name of the base space member prototype for segments.
  ///
  static const string& prototype_name();

  ///
  /// Creates a new segment in xhost with points specified by xv_ids.
  ///
  kd_segment(kd_lattice& xhost, const scoped_index xv_ids[]);
  
  ///
  /// Creates a new segment in xhost with points specified by xv_ids.
  ///
  static scoped_index new_segment(kd_lattice& xhost, const scoped_index xv_ids[]);
  
  ///
  /// Creates a new segment in xhost with points specified by xv_ids.
  ///
  static scoped_index new_segment(kd_lattice& xhost, const scoped_index& xpt0_id, const scoped_index& xpt1_id);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_segment(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_segment(const kd_segment& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_segment();

  ///
  /// The line fragments contained in this segment.
  ///
  void line_fragments(id_list_list& xfrags) const;
  
  ///
  /// The line fragments contained in the segment with id xid in kd_lattice xhost.
  ///
  static void line_fragments(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xfrags);

  ///
  /// The line fragments contained in this segment.
  ///
  void line_fragments(const kd_line_fragment& xfrag_prototype, frag_list& xfrags) const;
  
  ///
  /// The line fragments contained in the segment with id xid in kd_lattice xhost.
  ///
  static void line_fragments(const kd_lattice& xhost, const scoped_index& xid, const kd_line_fragment& xfrag_prototype, frag_list& xfrags);

  ///
  /// The members of this segment;
  /// if xinclude_segments, xmbrs includes segment ids, otherwise
  /// the result contains only points.
  ///
  void members(id_list_list& xmbrs, bool xinclude_segments) const;

  ///
  /// The members of the segment with id xid in ld_lattice xhost;
  /// if xinclude_segments, xmbrs includes segment ids, otherwise
  /// the result contains only points.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, bool xinclude_segments);

  ///
  /// The members of this segment and their coordinates;
  /// if xinclude_segments, xmbrs includes segment ids and xcoords
  /// includes placeholder coordinates for the segments, otherwise
  /// the results contains only points.
  ///
  void members(id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments) const;

  ///
  /// The members of the segment with id xid in ld_lattice xhost and their coordinates;
  /// if xinclude_segments, xmbrs includes segment ids and xcoords
  /// includes placeholder coordinates for the segments, otherwise
  /// the results contains only points.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments);

  ///
  /// The points of this segment.
  ///
  void points(scoped_index xresult[]) const;

  ///
  /// The points of the segment with id xid in ld_lattice xhost.
  ///
  static void points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The points of this segment and their coordinates.
  ///
  void points(scoped_index xresult[], e3_lite xcoords[]) const;

  ///
  /// The points of the segment with id xid in ld_lattice xhost and their coordinates.
  ///
  static void points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[], e3_lite xcoords[]);

  ///
  /// The id of the xi-th point.
  ///
  scoped_index point(int xi) const;

  ///
  /// The id of the xi-th point in the segment with id xid in kd_lattice xhost.
  ///
  static scoped_index point(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// Splits this segment in two by inserting the point with id xpt_id;
  /// xresult is set to the id of the new segment.
  ///
  void refine(const scoped_index& xpt_id, scoped_index& xresult);

  ///
  /// Splits the segment with id xid in kd_lattice xhost
  /// in two by inserting the point with id xpt_id;
  /// xresult is set to the id of the new segment.
  ///
  static void refine(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id, scoped_index& xresult);

  ///
  /// Splits this segment in two by inserting the point with id xpt_id;
  /// xresult is set to the id of the new segment. The old segment
  /// is moved to the face with id xface0_id and the new segment
  /// is inserted in the face with id xface1_id.
  ///
  void refine(const scoped_index& xpt_id, const scoped_index& xface0_id, const scoped_index& xface01_id, scoped_index& xresult);

  ///
  /// Splits the segment with id xid in kd_lattice xhost
  /// in two by inserting the point with id xpt_id;
  /// xresult is set to the id of the new segment. The old segment
  /// is moved to the face with id xface0_id and the new segment
  /// is inserted in the face with id xface1_id.
  ///
  static void refine(kd_lattice& xhost, 
                     const scoped_index& xid, 
                     const scoped_index& xpt_id,
                     const scoped_index& xface0_id, 
                     const scoped_index& xface1_id,
                     scoped_index& xresult);
  

  using kd_member::coord_bounds;

  ///
  /// The coordinate bounds for this segment..
  ///
  void coord_bounds(e3_lite& xlb, e3_lite& xub) const;

  ///
  /// The coordinate bounds for the segment with id xid in kd_lattice xhost.
  ///
  static void coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub);

  ///
  /// The lower bound on the coordinates for this segment.
  ///
  e3_lite coord_lower_bound() const;

  ///
  /// The lower bound on the coordinates for the segment with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The upper bound on the coordinates for this segment.
  ///
  e3_lite coord_upper_bound() const;

  ///
  /// The upper bound on the coordinates for the segment with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Set the point coordinates of this segment. 
  /// If xforward, point 0 is at xlb and 
  /// vertx 1 is at xub, otherwise the reverse.
  ///
  void put_coord_bounds(const e3_lite& xlb, const e3_lite& xub, bool xforward);

  ///
  /// Set the point coordinates of the segment with id xid in kd_lattice xhost. 
  /// If xforward, point 0 is at xlb and vertx 1 is at xub, otherwise the reverse.
  ///
  static void put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub, bool xforward);

  ///
  /// The line containing this segment.
  ///
  scoped_index line();
  
  ///
  /// The line containing the segment with id xid in kd_attice xhost.
  ///
  static scoped_index line(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The line containing this segment.
  ///
  void line(scoped_index& xresult);
  
  ///
  /// The line containing the segment with id xid in kd_attice xhost.
  ///
  static void line(const kd_lattice& xhost, const scoped_index xid, scoped_index& xresult);

  ///
  /// The face containing this segment.
  ///
  scoped_index face();
  
  ///
  /// The face containing the segment with id xid in kd_attice xhost.
  ///
  static scoped_index face(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The face containing this segment.
  ///
  void face(scoped_index& xresult);
  
  ///
  /// The face containing the segment with id xid in kd_lattice xhost.
  ///
  static void face(const kd_lattice& xhost, scoped_index xid, scoped_index& xresult);

  ///
  /// The surfaces containing this segment.
  /// $$SCRIBBLE: since a segment is always in exactly one line
  /// and a line is always in exactly one surface, how can a
  /// segment be in more than one surface?
  ///
  void surfaces(id_list& xresult) const;

  ///
  /// The surfaces containing the segment with id xid in kd_lattice xhost.
  ///
  static void surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The surface containing this segment..
  ///
  void surface(scoped_index& xresult) const;

  ///
  /// The surface containing the segment with id xid in kd_lattice xhost.
  ///
  static void surface(const kd_lattice& xhost, const scoped_index& xid, scoped_index& xresult);

  ///
  /// The triangles containing this segment..
  ///
  void triangles(id_list& xresult) const;

  ///
  /// The triangles containing the segment with id xid in kd_lattice xhost.
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The triangles containing the two vertices with 
  /// ids xv0_id and xv1_id in kd_lattice xhost..
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xv0_id, const scoped_index& xv1_id, id_set& xresult);

  ///
  /// True if this segment is on the boundary of a surface.
  ///
  bool is_boundary() const;

  ///
  /// True if the segment with id xid in kd_lattice xhost
  /// is on the boundary of a surface.
  ///
  static bool is_boundary(const kd_lattice& xhost, const scoped_index& xid);
  

  ///
  /// Clears the upper and lower cover of this segment;
  /// returns the ids of the points in the lower cover in xpoints.
  ///
  void clear(scoped_index xpoints[]);

  ///
  /// Clears the upper and lower cover of the segment with id xid in kd_lattice xhost;
  /// returns the ids of the points in the lower cover in xpoints.
  ///
  static void clear(kd_lattice& xhost, const scoped_index& xid, scoped_index xpoints[]);
  
  ///
  /// Deactivates this segment.
  ///
  void deactivate();
  
  ///
  /// Deactivates the segment with id xid in kd_lattice xhost.
  ///
  static void deactivate(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Finds the segment, if any, with points xid0 and xid1, ither either order.
  ///
  static void find(const kd_lattice& xhost, const scoped_index& xid0, const scoped_index& xid1, scoped_index& xresult);
  
//   ///
//   /// Searches segments connected to the xi-th
//   /// point of this segment 
//   /// for a segment in a face contained in xfaces.
//   ///
//   void next_polygon_segment(int xi, const id_set& xfaces, scoped_index& xresult) const;
  
//   ///
//   /// Searches segments connected to the xi-th
//   /// point of the segment with id xid in kd_lattice xhost 
//   /// for a segment in a face contained in xfaces.
//   ///
//   static void next_polygon_segment(const kd_lattice& xhost, 
//                                    const scoped_index& xid, 
//                                    int xi,
//                                    const id_set& xfaces,
//                                    scoped_index& xresult);
  
  

protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_segment();

private:

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual kd_segment* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_segment& operator=(const kd_segment& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_segment& operator=(const any& xother);

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
/// Insert kd_segment& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_segment& xn);

///
/// The deep size of kd_segment& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_segment& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_SEGMENT_H
