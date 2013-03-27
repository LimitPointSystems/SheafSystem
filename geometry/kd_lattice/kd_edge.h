// $RCSfile: kd_edge.h,v $ $Revision: 1.4 $ $Date: 2012/07/04 16:42:16 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_edge

#ifndef KD_EDGE_H
#define KD_EDGE_H

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
/// Axis-aligned linear edge in the kd-tree part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_edge : public kd_member
{

  // ===========================================================
  /// @name KD_EDGE FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{DB = 1, VERTEX_CT = 2, SUBEDGE_CT = 2};

  ///
  /// The name of the base space member prototype
  /// for edges with alignment xalignment.
  ///
  static const string& prototype_name(kd_alignment xlignment);
  
  ///
  /// Creates a new edge in xhost with vertices specified by xv_ids and alignment xalignment.
  ///
  kd_edge(kd_lattice& xhost, const scoped_index xv_ids[], kd_alignment xalignment);
  
  ///
  /// Creates a new edge in xhost with vertices specified by xv_ids and alignment xalignment.
  ///
  static scoped_index new_edge(kd_lattice& xhost, const scoped_index xv_ids[], kd_alignment xalignment);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_edge(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_edge(const kd_edge& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_edge();

  ///
  /// The subedges of this edge.
  ///
  void subedges(scoped_index xresult[]) const;

  ///
  /// The subedges of the edge with id xid in kd_lattice xhost.
  ///
  static void subedges(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The xi-th subedge of this edge.
  ///
  scoped_index subedge(int xi) const;

  ///
  /// The xi-th subedge of the edge with id xid in kd_lattice xhost.
  ///
  static scoped_index subedge(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The vertices of this edge.
  ///
  void vertices(scoped_index xresult[]) const;

  ///
  /// The vertices of the edge with id xid in ld_lattice xhost.
  ///
  static void vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The vertices of this edge and their coordinates.
  ///
  void vertices(scoped_index xresult[], e3_lite xcoords[]) const;

  ///
  /// The vertices of the edge with id xid in ld_lattice xhost and their coordinates.
  ///
  static void vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[], e3_lite xcoords[]);

  ///
  /// The id of the xi-th vertex.
  ///
  scoped_index vertex(int xi) const;

  ///
  /// The id of the xi-th vertex in the edge with id xid in kd_lattice xhost.
  ///
  static scoped_index vertex(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The vertex that splits this edge into two subedges..
  ///
  scoped_index splitting_vertex() const;

  ///
  /// The vertex that splits the edge with id xid in kd_lattice xhost into two subedges..
  ///
  static scoped_index splitting_vertex(const kd_lattice& xhost, const scoped_index& xid);

  using kd_member::alignment;

  ///
  /// The alignment for a edge with coordinates bounds xlb, xub.
  ///
  static kd_alignment alignment(const e3_lite& xlb, const e3_lite& xub);

  ///
  /// True if coordinates bounds xlb, xub correspond to a non-degenerate axis-aligned edge.
  ///
  static bool is_axis_aligned(const e3_lite& xlb, const e3_lite& xub);

  using kd_member::coord_bounds;

  ///
  /// The coordinate bounds for this edge..
  ///
  void coord_bounds(e3_lite& xlb, e3_lite& xub) const;

  ///
  /// The coordinate bounds for the edge with id xid in kd_lattice xhost.
  ///
  static void coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub);

  ///
  /// The lower bound on the coordinates for this edge.
  ///
  e3_lite coord_lower_bound() const;

  ///
  /// The lower bound on the coordinates for the edge with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The upper bound on the coordinates for this edge.
  ///
  e3_lite coord_upper_bound() const;

  ///
  /// The upper bound on the coordinates for the edge with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Set the vertex coordinates of this edge. 
  /// If xforward, vertex 0 is at xlb and 
  /// vertx 1 is at xub, otherwise the reverse.
  ///
  void put_coord_bounds(const e3_lite& xlb, const e3_lite& xub, bool xforward);

  ///
  /// Set the vertex coordinates of the edge with id xid in kd_lattice xhost. 
  /// If xforward, vertex 0 is at xlb and vertx 1 is at xub, otherwise the reverse.
  ///
  static void put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub, bool xforward);
  
  ///
  /// True if plane xp intersects this edge.
  ///
  bool in_bounds(const kd_plane& xp) const;

  ///
  /// True if plane xp intersects the edge with id xid in kd_lattice xhost.
  ///
  static bool in_bounds(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp);

  ///
  /// True if and only if xpt lies within the coordinate bounds of this edge.
  ///
  bool contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies within the coordinate bounds
  /// of the edge with id xid in kd_lattice xhost.
  ///
  static bool contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// True if and only if xpt lies strictly within the coordinate bounds of this edge.
  ///
  bool interior_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies strictly within the coordinate bounds
  /// of the edge with id xid in kd_lattice xhost.
  ///
  static bool interior_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// True if and only if xpt lies on the coordinate bounds of this edge.
  ///
  bool boundary_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies on the coordinate bounds
  /// of the edge with id xid in kd_lattice xhost.
  ///
  static bool boundary_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// Point location query; searches the down-set of this edge
  /// for the minimal cell of dimension at least xd containing 
  /// point xpt. Returns the id of the cell..
  ///
  scoped_index locate_point(const e3_lite& xpt, int xd) const;

  ///
  /// Point location query; searches the down-set of the edge
  /// with id xid in kd_lattice xhost for the minimal cell  of
  /// dimension at least xd containing point xpt. 
  /// Returns the id of the cell..
  ///
  static scoped_index locate_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt, int xd);
  
  ///
  /// Splits this edge in two at the intersection with plane xp.
  ///
  void refine(const kd_plane& xp, scoped_index xnew_ids[]);
  

  ///
  /// Splits the edge with id xid in kd_lattice xhost 
  /// in two at the intersection with plane xp.
  ///
  static void refine(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Inserts point xpt in the edge with id xid in kd_lattice xhost; returns the id of the point.
  ///
  static void insert_point(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt, scoped_index& xresult);

  ///
  /// Inserts the point with id xpt_id in the edge with id xid in kd_lattice xhost
  /// without looking for intersections.
  ///
  static void insert_point_no_intersection(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id);

  ///
  /// Inserts point xpt in the edge with id xid in kd_lattice xhost 
  /// without looking for intersections; returns the id of the point.
  ///
  static void insert_point_no_intersection(kd_lattice& xhost, const scoped_index& xid, e3_lite& xpt, scoped_index& xresult);

  ///
  /// Finds the other face adjacent to the edge with id xid in kd_lattice xhost
  /// that has alignment as the face with id xface_id; returns the id of the face.
  ///
  static scoped_index other_face(const kd_lattice& xhost, const scoped_index& xid, const scoped_index& xface_id);
  
  ///
  /// True if this edge has no contents (points).
  ///
  bool is_empty() const;
  
  ///
  /// True if the edge with id xid in kd_lattice xhost has no contents (points).
  ///
  static bool is_empty(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The line fragments contained in this edge.
  ///
  void line_fragments(const kd_line_fragment& xfrag_prototype, bool xfwd, frag_list& xresult) const;
  
  ///
  /// The line fragments contained in the edge with id xid in kd_lattice xhost.
  ///
  static void line_fragments(const kd_lattice& xhost, 
                             const scoped_index& xid, 
                             const kd_line_fragment& xfrag_prototype, 
                             bool xfwd,
                             frag_list& xresult);
 


protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_edge();

  ///
  /// Removes the vertices of the edge with id xid in kd_lattice xhost 
  // from its lower cover and returns them in xresult.
  ///
  ///
  /// Removes the lower cover of the edge with id xid 
  /// in kd_lattice xhost and returns 
  /// the first VERTEX_CT members in xvertices and the 
  /// contents of the edge (the remaining members
  /// of the lower cover) in xcontents.
  ///
  static void remove_lower_cover(kd_lattice& xhost, scoped_index xid, scoped_index xvertices[], list<scoped_index>& xcontents);

  ///
  /// Creates a new subedge of the edge with id xold_edge_id in kd_lattice xhost
  /// with vertices xvertex_ids; the new edge replaces xold_edge_id in the upper cover
  /// of the xi-th vertex.
  ///
  static scoped_index new_subedge(kd_lattice& xhost, 
                                  const scoped_index& xold_edge_id, 
                                  const scoped_index xvertex_ids[], 
                                  int xi);  

  ///
  /// Sorts the point in xcontents into the two subedges and splitting point in xnew_ids.
  /// 
  static void split_contents(kd_lattice& xhost, 
                             const scoped_index& xold_edge_id,
                             const scoped_index xnew_ids[], 
                             const kd_plane& xp, 
                             list<scoped_index>& xcontents);

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
  virtual kd_edge* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_edge& operator=(const kd_edge& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_edge& operator=(const any& xother);

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
/// Insert kd_edge& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_edge& xn);

///
/// The deep size of kd_edge& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_edge& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_EDGE_H
