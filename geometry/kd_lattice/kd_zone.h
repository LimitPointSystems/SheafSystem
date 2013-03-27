// $RCSfile: kd_zone.h,v $ $Revision: 1.4 $ $Date: 2012/07/04 16:42:17 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_zone

#ifndef KD_ZONE_H
#define KD_ZONE_H

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
 
///
/// Axis-aligned rectangular cuboid zone in the kd-tree part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_zone : public kd_member
{

  // ===========================================================
  /// @name KD_ZONE FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{DB = 3, VERTEX_CT = 8, EDGE_CT = 12, FACE_CT = 6, SUBZONE_CT = 2};

  ///
  /// The name of the base space member prototype for zones.
  ///
  static const string& prototype_name();
  
  ///
  /// Creates a new zone with new face, edges, and vertices in xhost, without coordinates
  ///
  kd_zone(kd_lattice& xhost);
  
  ///
  /// Creates a new zone with new face, edges, and vertices in xhost, without coordinates
  ///
  static scoped_index new_zone(kd_lattice& xhost);
  
  ///
  /// Creates a new zone with new face, edges, and vertices in xhost, with coordinate bounds xlb, xub.
  ///
  kd_zone(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub);
  
  ///
  /// Creates a new zone with new face, edges, and vertices in xhost, with coordinate bounds xlb, xub.
  ///
  static scoped_index new_zone(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_zone(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_zone(const kd_zone& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_zone();

  ///
  /// The subzones of this zone.
  ///
  void subzones(scoped_index xresult[]) const;

  ///
  /// The subzones of the zone with id xid in kd_lattice xhost.
  ///
  static void subzones(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The xi-th subzone of this zone.
  ///
  scoped_index subzone(int xi) const;

  ///
  /// The xi-th subzone of the zone with id xid in kd_lattice xhost.
  ///
  static scoped_index subzone(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The faces of this zone.
  ///
  void faces(scoped_index xresult[]) const;

  ///
  /// The faces of the zone with id xid in kd_lattice xhost.
  ///
  static void faces(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The xi-th face of this zone.
  ///
  scoped_index face(int xi) const;

  ///
  /// The xi-th face of the zone with id xid in kd_lattice xhost.
  ///
  static scoped_index face(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The face that splits this zone into two subzones..
  ///
  scoped_index splitting_face() const;

  ///
  /// The face that splits the zone with id xid in kd_lattice xhost into two subzones..
  ///
  static scoped_index splitting_face(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The edges of this zone.
  ///
  void edges(scoped_index xresult[]) const;

  ///
  /// The edges of the zone with id xid in kd_lattice xhost.
  ///
  static void edges(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The xi-th edge of this zone.
  ///
  scoped_index edge(int xi) const;

  ///
  /// The xi-th edge of the zone with id xid in kd_lattice xhost.
  ///
  static scoped_index edge(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// The vertices of this zone.
  ///
  void vertices(scoped_index xresult[]) const;

  ///
  /// The vertices of the zone with id xid in kd_lattice xhost.
  ///
  static void vertices(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The id of the xi-th vertex.
  ///
  scoped_index vertex(int xi) const;

  ///
  /// The id of the xi-th vertex in the zone with id xid in kd_lattice xhost.
  ///
  static scoped_index vertex(const kd_lattice& xhost, const scoped_index& xid, int xi);

  ///
  /// True if coordinates bounds xlb, xub correspond to a non-degenerate axis-aligned zone.
  ///
  static bool is_axis_aligned(const e3_lite& xlb, const e3_lite& xub);

  using kd_member::coord_bounds;

  ///
  /// The coordinate bounds for this zone.
  ///
  void coord_bounds(e3_lite& xlb, e3_lite& xub) const;

  ///
  /// The coordinate bounds for the zone with id xid in kd_lattice xhost.
  ///
  static void coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub);

  ///
  /// The lower bound on the coordinates for this zone.
  ///
  e3_lite coord_lower_bound() const;

  ///
  /// The lower bound on the coordinates for the zone with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The upper bound on the coordinates for this zone.
  ///
  e3_lite coord_upper_bound() const;

  ///
  /// The upper bound on the coordinates for the zone with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Set the vertex coordinates of this zone to the box defined by xlb, xub.
  ///
  void put_coord_bounds(const e3_lite& xlb, const e3_lite& xub);

  ///
  /// Set the vertex coordinates of the zone with id xid in kd_lattice xhost to the box defined by xlb, xub.
  ///
  static void put_coord_bounds(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xlb, const e3_lite& xub);

  ///
  /// The center of the bounding box for this zone.
  ///
  e3_lite center() const;
  
  ///
  /// The center of the bounding box of the zone with id xid in kd-lattice xhost.
  ///
  static e3_lite center(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if and only if xpt lies within the coordinate bounds of this zone.
  ///
  bool contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies within the coordinate bounds
  /// of the zone with id xid in kd_lattice xhost.
  ///
  static bool contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// True if and only if xpt lies strictly within the coordinate bounds of this zone.
  ///
  bool interior_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies strictly within the coordinate bounds
  /// of the zone with id xid in kd_lattice xhost.
  ///
  static bool interior_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// True if and only if xpt lies on the coordinate bounds of this zone.
  ///
  bool boundary_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt lies on the coordinate bounds
  /// of the zone with id xid in kd_lattice xhost.
  ///
  static bool boundary_contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// Point location query; searches the down-set of this zone
  /// for the minimal cell of dimension at least xd containing point xpt. 
  /// Returns the id of the cell..
  ///
  scoped_index locate_point(const e3_lite& xpt, int xd) const;

  ///
  /// Point location query; searches the down-set of the zone
  /// with id xid in kd_lattice xhost for the minimal cell 
  /// of dimension at least xd containing point xpt. 
  /// Returns the id of the cell..
  ///
  static scoped_index locate_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt, int xd);

  ///
  /// Find the face leaf in plane xp in the down-set of this zone that 
  /// contains the beginning of line xline.
  ///
  void find_face_leaf(const kd_plane& xp, const pt_list& xline, scoped_index& xresult) const;

  ///
  /// Find the face leaf in plane xp in the down-set of the zone with id xid in kd_lattice xhost 
  /// that contains the beginning of line xline.
  ///
  static void find_face_leaf(const kd_lattice& xhost, 
                             const scoped_index& xid, 
                             const kd_plane& xp, 
                             const pt_list& xline, 
                             scoped_index& xresult);

  ///
  /// Find the face leaves contained in plane xp and 
  /// in the down-set of this zone.
  ///
  void find_face_leaves(const kd_plane& xp, id_list& xresult) const;

  ///
  /// Find the face leaves contained in plane xp and 
  /// in the down-set of the zone with id xid in kd_lattice xhost.
  ///
  static void find_face_leaves(const kd_lattice& xhost, 
                               const scoped_index& xid, 
                               const kd_plane& xp,
                               id_list& xresult);

  ///
  /// True if plane xp intersects this zone.
  ///
  bool in_bounds(const kd_plane& xp) const;

  ///
  /// True if plane xp intersects the edge with id xid in kd_lattice xhost.
  ///
  static bool in_bounds(const kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp);

  ///
  /// Splits this zone in two at the intersection with plane xp.
  ///
  void refine(const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Splits the face with id xid in kd_lattice xhost in two at the intersection with plane xp;
  /// puts the ids of the new edge and the two new faces in xnew_ids.
  ///
  static void refine(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Inserts plane xp into the zone with id xid in kd_lattice xhost.
  ///
  static bool insert_plane(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, kd_plane& xactual_plane);

  ///
  /// Inserts plane xp into this zone.
  ///
  void insert_plane(const kd_plane& xp);

  ///
  /// Inserts plane xp into the zone with id xid in kd_lattice xhost.
  ///
  static void insert_plane(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp);

  ///
  /// Intersects plane xp with the triangles in this zone.
  ///
  void intersect_plane(const kd_plane& xp, frag_list& xfrags);

  ///
  /// Intersects plane xp with the triangles in the zone with id xid in kd_lattice xhost.
  ///
  static void intersect_plane(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, frag_list& xfrags);
  
  ///
  /// The line fragments contained in the faces of this zone.
  ///
  void line_fragments(frag_list& xfrags) const;
  
  ///
  /// The lines contained in the faces of the zone with id xid in kd_lattice xhost.
  ///
  static void line_fragments(const kd_lattice& xhost, const scoped_index& xid, frag_list& xfrags);

  ///
  /// (Re-) Triangulates surfaces contained in this zone.;
  ///
  void triangulate() const;

  ///
  /// (Re-) Triangulates surfaces contained in the zone with id xid in kd_lattice xhost.
  ///
  static void triangulate(kd_lattice& xhost, const scoped_index& xid);
  
  ///
  /// The triangles contained in this zone.
  ///
  void triangles(id_list& xresult) const;
  
  ///
  /// The triangles contained in the zone with id xid in kd_lattice xhost.
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);
  
  ///
  /// The vertex connectivity for the triangles contained in this zone.
  ///
  void triangle_members(id_list& xtriangle_mbrs) const;
  
  ///
  /// The vertex connectivity for the triangles contained in the zone with id xid in kd_lattice xhost.
  ///
  static void triangle_members(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangle_mbrs);

  ///
  /// Deletes the contents of this zone;
  /// populates xdeleted with ids of deleted contents.
  ///
  void clear_contents(pod_id_hash_set& xdeleted);  

  ///
  /// Deletes the contents of the zone with id xid in kd_lattice xhost;
  /// populates xdeleted with ids of deleted contents.
  ///
  static void clear_contents(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted);  

  ///
  /// Deletes the contents of leaf zones beneath this zone which intersect plane xp.
  /// Populates xdeleted with ids of deleted contents.
  ///
  void clear_contents(const kd_plane& xp, pod_id_hash_set& xdeleted);  

  ///
  /// Deletes the contents of the leaf zones beneath the zone with id xid in kd_lattice xhost
  /// which intersect plane xp; populates xdeleted with ids of deleted contents.
  ///
  static void clear_contents(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, pod_id_hash_set& xdeleted);  
  
  ///
  /// True if this zone has no contents (triangles).
  ///
  bool is_empty() const;
  
  ///
  /// True if the zone with id xid in kd_lattice xhost has no contents (triangles).
  ///
  static bool is_empty(const kd_lattice& xhost, const scoped_index& xid);
  
protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_zone();

  ///
  /// Removes the lower cover of the zone with id xid 
  /// in kd_lattice xhost and returns 
  /// the first FACE_CT members in xfaces and the 
  /// contents of the zone (the remaining members
  /// of the lower cover) in xcontents.
  ///
  static void remove_lower_cover(kd_lattice& xhost, scoped_index xid, scoped_index xfaces[], id_list& xcontents);

  ///
  /// Creates a new subzone of the zone with id xold_zone_id in kd_lattice xhost
  /// with faces xface_ids; the new zone replaces xold_zone_id in the upper cover
  /// of the xi-th face.
  ///
  static scoped_index new_subzone(kd_lattice& xhost, 
                                  const scoped_index& xold_zone_id, 
                                  const scoped_index xface_ids[], 
                                  int xi);  

  ///
  /// Splits the face with id xid in kd_lattice xhost in two at the intersection with X_AXIS_ALIGNED plane xp;
  /// puts the ids of the new edge and the two new faces in xnew_ids.
  ///
  static void refine_x_axis_aligned(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Splits the face with id xid in kd_lattice xhost in two at the intersection with Y_AXIS_ALIGNED plane xp;
  /// puts the ids of the new edge and the two new faces in xnew_ids.
  ///
  static void refine_y_axis_aligned(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Splits the face with id xid in kd_lattice xhost in two at the intersection with Z_AXIS_ALIGNED plane xp;
  /// puts the ids of the new edge and the two new faces in xnew_ids.
  ///
  static void refine_z_axis_aligned(kd_lattice& xhost, scoped_index xid, const kd_plane& xp, scoped_index xnew_ids[]);

  ///
  /// Sorts the members in xcontents into the two subzones and splitting face in xnew_ids;
  /// spltting any members that cross the splitting plane xp.
  /// 
  static void split_contents(kd_lattice& xhost, 
                             const scoped_index& xold_zone_id,
                             const scoped_index xnew_ids[],
                             const kd_plane& xp, 
                             id_list& xcontents);
  

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
  virtual kd_zone* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_zone& operator=(const kd_zone& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_zone& operator=(const any& xother);

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
/// Insert kd_zone& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_zone& xn);

///
/// The deep size of kd_zone& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_zone& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_ZONE_H
