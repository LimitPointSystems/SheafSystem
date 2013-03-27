// $RCSfile: kd_face.h,v $ $Revision: 1.5 $ $Date: 2013/01/10 13:54:43 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_face

#ifndef KD_FACE_H
#define KD_FACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef LIST_INDEX_SPACE_ITERATOR_H
#include "list_index_space_iterator.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

#ifndef KD_MEMBER_H
#include "kd_member.h"
#endif

namespace geometry
{
 
///
/// Axis-aligned rectangular face in the kd-tree part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_face : public kd_member
{

  // ===========================================================
  /// @name KD_FACE FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{DB = 2, VERTEX_CT = 4, EDGE_CT = 4, SUBFACE_CT = 2, ZONE_CT = 2};

  //
  // Conveninent representation for a point in a polyline.
  //
  struct line_pt
  {
    ///
    /// The coordinates of the point.
    ///
    e3_lite pt;

    ///
    /// The id of the point.
    ///
    scoped_index pt_id;

    ///
    /// The bounding box clipping code for the point.
    ///
    int clip_code;

    ///
    /// The first item in the face contents
    /// that the segment beginning at this point
    /// has not been tested against.
    ///
    list_index_space_iterator contents_itr;

    ///
    /// Creates an instance with pt == xpt.
    ///
    line_pt(const e3_lite& xpt);

    ///
    /// True if and only if this point
    /// has the same value for all members
    /// as xother.
    ///
    bool operator==(const line_pt& xother) const;
  };

  //
  // Convenient representation for line.
  //
  typedef list<line_pt> line_list;

  ///
  /// The name of the base space member prototype
  /// for faces with alignment xalignment.
  ///
  static const string& prototype_name(kd_alignment xlignment);

  ///
  /// Creates a new face in xhost with with edges in xedge_ids.
  ///
  kd_face(kd_lattice& xhost, const scoped_index xedges[], kd_alignment xalignment);
  
  ///
  /// Creates a new face in xhost with with edges in xedge_ids.
  ///
  static scoped_index new_face(kd_lattice& xhost, const scoped_index xedges[], kd_alignment xalignment);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_face(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_face(const kd_face& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_face();

  ///
  /// The subfaces of this face.
  ///
  void subfaces(scoped_index xresult[]) const;

  ///
  /// The subfaces of the face with id xid in kd_lattice xhost.
  ///
  static void subfaces(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The xi-th subface of this face.
  ///
  scoped_index subface(int xi) const;

  ///
  /// The xi-th subface of the face with id xid in kd_lattice xhost.
  ///
  static scoped_index subface(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The edges of this face.
  ///
  void edges(scoped_index xresult[]) const;

  ///
  /// The edges of the face with id xid in kd_lattice xhost.
  ///
  static void edges(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The xi-th edge of this face.
  ///
  scoped_index edge(int xi) const;

  ///
  /// The xi-th edge of the face with id xid in kd_lattice xhost.
  ///
  static scoped_index edge(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The edge that splits this face into two subfaces..
  ///
  scoped_index splitting_edge() const;

  ///
  /// The edge that splits the face with id xid in kd_lattice xhost into two subfaces..
  ///
  static scoped_index splitting_edge(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The vertices of this zone.
  ///
  void vertices(scoped_index xresult[]) const;

  ///
  /// The vertices of the edge with id xid in ld_lattice xhost.
  ///
  static void vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The id of the xi-th vertex.
  ///
  scoped_index vertex(int xi) const;

  ///
  /// The id of the xi-th vertex in the edge with id xid in kd_lattice xhost.
  ///
  static scoped_index vertex(const kd_lattice& xhost, const scoped_index& xid, int xi);

  using kd_member::alignment;
  
  ///
  /// The alignment for a face with coordinates bounds xlb, xub.
  ///
  static kd_alignment alignment(const e3_lite& xlb, const e3_lite& xub);

  ///
  /// True if coordinates bounds xlb, xub correspond to a non-degenerate axis-aligned face.
  ///
  static bool is_axis_aligned(const e3_lite& xlb, const e3_lite& xub);

  using kd_member::coord_bounds;

  ///
  /// The upper bound for the xi-th coordinate.
  ///
  void coord_bounds(e3_lite& xlb, e3_lite& xub) const;

  ///
  /// The coordinate bounds for the edge with id xid in kd_lattice xhost.
  ///
  static void coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub);

  ///
  /// The lower bound on the coordinates for this face.
  ///
  e3_lite coord_lower_bound() const;

  ///
  /// The lower bound on the coordinates for the face with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The upper bound on the coordinates for this face.
  ///
  e3_lite coord_upper_bound() const;

  ///
  /// The upper bound on the coordinates for the face with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Set the vertex coordinates to the box defined by xlb, xub.
  ///
  void put_coord_bounds(const e3_lite& xlb, const e3_lite& xub);

  ///
  /// Set the vertex coordinates to the box defined by xlb, xub.
  ///
  static void put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub);

  ///
  /// True if and only if xpt lies within the coordinate bounds of this face.
  ///
  bool contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies within the coordinate bounds
  /// of the face with id xid in kd_lattice xhost.
  ///
  static bool contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// True if and only if xpt lies strictly within the coordinate bounds of this face.
  ///
  bool interior_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies strictly within the coordinate bounds
  /// of the face with id xid in kd_lattice xhost.
  ///
  static bool interior_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// True if and only if xpt lies on the coordinate bounds of this face.
  ///
  bool boundary_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies on the coordinate bounds
  /// of the face with id xid in kd_lattice xhost.
  ///
  static bool boundary_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// Point location query; searches the down-set of this face
  /// for the minimal cell of dimension at least xd containing point xpt. 
  /// Returns the id of the cell..
  ///
  scoped_index locate_point(const e3_lite& xpt, int xd) const;

  ///
  /// Point location query; searches the down-set of the face
  /// with id xid in kd_lattice xhost for the minimal cell 
  /// of dimension at least xd containing point xpt. 
  /// Returns the id of the cell..
  ///
  static scoped_index locate_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt, int xd);

  ///
  /// The leaf in the down-set of this face that contains
  /// the beginning of line xline.
  ///
  void leaf(const pt_list& xline, scoped_index& xresult) const;

  ///
  /// The leaf in the down-set of the face with id xid
  /// in kd_lattice xhost that contains the beginning of line xline.
  ///
  static void leaf(const kd_lattice& xhost, const scoped_index& xid, const pt_list& xline, scoped_index& xresult);

  ///
  /// The leaves in the down-set of this face.
  ///
  void leaves(id_list& xresult) const;

  ///
  /// The leaves in the down-set of the face with id xid in kd_lattice xhost.
  ///
  static void leaves(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// Inserts point xpt in the face with id xid 
  /// in kd_lattice xhost; returns the id of the point.
  ///
  static scoped_index insert_point(kd_lattice& xhost, const scoped_index& xid,  e3_lite& xpt);

  ///
  /// Inserts point xpt, with clipping code xcode,
  /// in the face with id xid in kd_lattice xhost; returns the id of the point.
  ///
  static scoped_index insert_point(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt, int xcode);

  ///
  /// True if plane xp intersects this face.
  ///
  bool in_bounds(const kd_plane& xp) const;

  ///
  /// True if plane xp intersects the face with id xid in kd_lattice xhost.
  ///
  static bool in_bounds(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp);

  ///
  /// True if plane xp contains this face.
  ///
  bool in_plane(const kd_plane& xp) const;

  ///
  /// True if plane xp contains the face with id xid in kd_lattice xhost.
  ///
  static bool in_plane(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp);

  //  using kd_member::refine;

  ///
  /// Splits this face in two at the intersection with plane xp;
  /// puts the ids of the new edge and the two new faces in xnew_ids.
  ///
  void refine(const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Splits the face with id xid in kd_lattice xhost in two at the intersection with plane xp;
  /// puts the ids of the new edge and the two new faces in xnew_ids.
  ///
  static void refine(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Inserts the polyline xline into this face.
  ///
  void insert_line(line_list& xline, id_list& xline_mbrs);

  ///
  /// Inserts the polyline xline into the face with id xid in kd_lattice xhost.
  ///
  static scoped_index insert_line(kd_lattice& xhost, const scoped_index& xid, line_list& xline, id_list& xline_mbrs);

  ///
  /// The line fragments contained in this face.
  ///
  void line_fragments(frag_list& xline_mbrs) const;
  
  ///
  /// The line fragments contained in the face with id xid in kd_lattice xhost.
  ///
  static void line_fragments(const kd_lattice& xhost, const scoped_index& xid, frag_list& xline_mbrs);
  
  ///
  /// The zones containing this face.
  ///
  void zones(id_list& xzones) const;
  
  ///
  /// The zones containing the face with id xid in kd_lattice xhost.
  ///
  static void zones(const kd_lattice& xhost, const scoped_index& xid, id_list& xzones);

  ///
  /// The segments contained in this face.
  ///
  void segments(id_list& xsegments) const;
  
  ///
  /// The segments contained in the face with id xid in kd_lattice xhost.
  ///
  static void segments(const kd_lattice& xhost, const scoped_index& xid, id_list& xlines);
  
  ///
  /// True if this face has no contents (line segments).
  ///
  bool is_empty() const;
  
  ///
  /// True if the face with id xid in kd_lattice xhost has no contents (line segments).
  ///
  static bool is_empty(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Creates a surface to close subvolumes bounded by this face.
  /// If xedge_fwd use the stored edge order, otherwise reverse the order.
  /// If xpolygon_fwd use the generated polygon order, otherwise reverse the order.
  ///
  void triangulate(const scoped_index& xsurface_id, bool xedge_fwd, bool xpolygon_fwd);

  ///
  /// Triangulates the polygons contained in
  /// the face with id xid in kd_lattice xhost
  /// links them to the surface with id xsurface_id.
  /// If xedge_fwd use the stored edge order, otherwise reverse the order.
  /// If xpolygon_fwd use the generated polygon order, otherwise reverse the order.
  ///
  static void triangulate(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xsurface_id, bool xedge_fwd, bool xpolygon_fwd);
  
  // $$SCRIBBLE: replace with id_list_list signature.

  ///
  /// The triangles contained in this zone.
  ///
  void triangles(id_list& xresult) const;
  
  ///
  /// The triangles contained in the zone with id xid in kd_lattice xhost.
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The vertex connectivity for the triangles contained in this face.
  ///
  void triangle_members(id_list& xtriangle_mbrs) const;
  
  ///
  /// The vertex connectivity for the triangles contained in the face with id xid in kd_lattice xhost.
  ///
  static void triangle_members(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangle_mbrs);
  
  ///
  /// Local 2D coordinate system for the face with id xid in kd_lattice xhost.
  /// If xfwd , the axes are oriented so u x v points to increasing alignment 
  /// coordinate, otherwise to decreasing alignment coordinate.
  ///
  static void local_axes(kd_lattice& xhost, const scoped_index& xid, int& xu, int& xv, bool xfwd = true);
  

protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_face();

  ///
  /// Removes the lower cover of the face with id xid 
  /// in kd_lattice xhost and returns 
  /// the first EDGE_CT members in xedges and the 
  /// contents of the face (the remaining members
  /// of the lower cover) in xcontents.
  ///
  static void remove_lower_cover(kd_lattice& xhost, scoped_index xid, scoped_index xedges[], list<scoped_index>& xcontents);

  ///
  /// Creates a new subface of the face with id xold_face_id in kd_lattice xhost
  /// with edges xedge_ids; the new face replaces xold_face_id in the upper cover
  /// of the xi-th edge.
  ///
  static scoped_index new_subface(kd_lattice& xhost, 
                                  const scoped_index& xold_face_id, 
                                  const scoped_index xedge_ids[], 
                                  int xi);  

  ///
  /// Splits the face with id xid in kd_lattice xhost in two 
  /// at the intersection with plane xp by refining edges 0 and 2.
  /// If xnew_edge_forward, the new edge is directed from edge 0
  /// to edge 2, otherwise the reverse. Puts the ids of the two 
  /// new faces and the new edge in xnew_ids.
  /// $$SCRIBBLE: xnew_edge_forward appears to be unnecessary; remove it.
  ///
  static void refine_edges_0_and_2(kd_lattice& xhost,
                                   scoped_index xid,
                                   const kd_plane& xp,
                                   scoped_index xnew_ids[]);

  ///
  /// Splits the face with id xid in kd_lattice xhost in two 
  /// at the intersection with plane xp by refining edges 1 and 3.
  /// If xnew_edge_forward, the new edge is directed from edge 1
  /// to edge 3, otherwise the reverse. Puts the ids of the two 
  /// new faces and the new edge in xnew_ids.
  /// $$SCRIBBLE: xnew_edge_forward appears to be unnecessary; remove it.
  ///
  static void refine_edges_1_and_3(kd_lattice& xhost,
                                   scoped_index xid,
                                   const kd_plane& xp,
                                   scoped_index xnew_ids[]);


  ///
  /// Sorts the segments in xcontents into the two subfaces and splitting edge in xnew_ids;
  /// spltting any segments that cross the splitting plane xp.
  /// 
  static void split_contents(kd_lattice& xhost, 
                             const scoped_index& xold_face_id, 
                             const scoped_index xnew_ids[], 
                             const kd_plane& xp, 
                             list<scoped_index>& xcontents);

//   ///
//   /// Finds the face adjacent to the face with id xid in kd_lattice xhost
//   /// through the edge or vertex specified by out code xcode.
//   ///
//   static scoped_index adjacent_face(kd_lattice& xhost, const scoped_index& xid, int xcode);

  ///
  /// Finds the face adjacent to the face with id xid in kd_lattice xhost
  /// along line xline..
  ///
  static scoped_index adjacent_face(kd_lattice& xhost, const scoped_index& xid, line_list& xline);
  
  ///
  /// Local 2D coordinate system for the face with id xid in kd_lattice xhost
  /// with orientation assigned consistent with use in kd_bounding_box::clip_2d,
  /// called from insert_point and kd_face::adjacent face
  ///
  static void local_axes_clip_2d(kd_lattice& xhost, const scoped_index& xid, int& xu, int& xv);
  

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
  virtual kd_face* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_face& operator=(const kd_face& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_face& operator=(const any& xother);

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
/// Insert kd_face& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_face& xn);
 
///
/// Insert kd_face::line_pt& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_face::line_pt& xn);
 
///
/// Insert kd_face::line_kist& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_face::line_list& xn);

///
/// The deep size of kd_face& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_face& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_FACE_H
