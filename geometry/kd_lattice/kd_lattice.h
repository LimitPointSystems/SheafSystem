// $RCSfile: kd_lattice.h,v $ $Revision: 1.7 $ $Date: 2013/01/20 19:40:46 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_lattice

#ifndef KD_LATTICE_H
#define KD_LATTICE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif
  
#ifndef GEOMETRY_H
#include "geometry.h"
#endif

#ifndef KD_BOUNDING_BOX_H
#include "kd_bounding_box.h"
#endif

#ifdef USE_VTK

#ifndef KD_DISPLAY_H
#include "kd_display.h"
#endif

#endif

#ifndef KD_ENUMS_H
#include "kd_enums.h"
#endif
 
namespace sheaf
{
  class subposet;
}

namespace fiber_bundle
{
  class array_section_dof_map;
  class base_space_poset;
  class base_space_member;
  class e3_lite;
  class sec_e3;
  class sec_tuple;
}

namespace geometry
{

  
///
/// A kd-tree embedded in a lattice-ordered cell complex.
///
class SHEAF_DLL_SPEC kd_lattice : public any
{

  // ===========================================================
  /// @name KD_LATTICE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance in namespace xns with name xname for the volume bounded by xlb and xub.
  ///
  kd_lattice(geometry_namespace& xns, const string& xname, const e3_lite& xlb, const e3_lite& xub);

  ///
  /// Destructor
  ///
  virtual ~kd_lattice();

  ///
  /// The namespace.
  ///
  geometry_namespace& name_space();

  ///
  /// The namespace, const version.
  ///
  const geometry_namespace& name_space() const;

  ///
  /// The base space.
  ///
  base_space_poset& base_space();

  ///
  /// The base space; const version
  ///
  const base_space_poset& base_space() const;

  ///
  /// The active part of the base space.
  /// Everthing in the base space except the
  /// cohort inactivation structure is below
  /// this member.
  ///
  base_space_member& active_part();

  ///
  /// The active part of the base space; const version.
  /// Everthing in the base space except the
  /// cohort inactivation structure is below
  /// this member.
  ///
  const base_space_member& active_part() const;  

  ///
  /// The coordinate section.
  ///
  sec_e3& coords();

  ///
  /// The coordinate section, const version.
  ///
  const sec_e3& coords() const;

  ///
  /// Creates the restriction of the coordinates to the active part
  /// as a separate section.
  /// @hack Workaround for restriction bug in SheafScope.
  ///
  void create_active_sections();
  
  ///
  /// Write this lattice to a graphvis .dot file with name xname.
  ///
  void write_dot(const string& xname) const;

  ///
  /// Depth first search of members of type M beneath the member with id xid.
  /// Actions provided by xaction, which must have member functions 
  /// previsit(kd_lattice&, const scoped_index&)and postvisit(kd_lattice&, const scoped_index&).
  ///
  template <typename M, typename A> 
  SHEAF_DLL_SPEC 
  void search(const scoped_index& xid, A& xaction);

  ///
  /// Depth first search of members beneath the member with id xid.
  /// Actions provided by xaction, which must have member functions
  ///   void previsit(kd_lattice&, const scoped_index&), and 
  ///   void postvisit(kd_lattice&, const scoped_index&)
  ///   bool truncate(kd_lattice&, const scoped_index&), 
  /// If truncate returns true, the lower cover of member xid is not searched.
  ///
  template <typename A> 
  SHEAF_DLL_SPEC 
  void search2(const scoped_index& xid, A& xaction);

  ///
  /// Filter for members of type M.
  ///
  template <typename M> 
  SHEAF_DLL_SPEC 
  const subposet& member_filter();

  ///
  /// Updates the several section space schema to 
  /// the current state of the base space.
  ///
  void update_section_space_schema();

protected:

  ///
  /// Default constructor
  ///
  kd_lattice();

  ///
  /// Copy constructor
  ///
  kd_lattice(const kd_lattice& xother);

private:

  ///
  /// The namespace.
  ///
  geometry_namespace* _name_space;

  ///
  /// The base space.
  ///
  base_space_poset* _base_space;

  ///
  /// The active part of the base space.
  /// Everthing in the base space except the
  /// cohort inactivation structure is below
  /// this member.
  ///
  base_space_member* _active_part;
  
  ///
  /// The coordinate section.
  ///
  sec_e3* _coords;

  ///
  /// The dof map for the coordinates.
  ///
  array_section_dof_map* _coords_dof_map;

  ///
  /// The lower bound for the coordinates.
  ///
  e3_lite _coord_lb;

  ///
  /// The upper bound for the coordinates.
  ///
  e3_lite _coord_ub;

#ifdef USE_VTK

  ///
  /// The VTK display.
  ///
  kd_display _display;

#endif

  ///
  /// Create the base space.
  ///
  void create_base_space(const string& xname);

  ///
  /// Create the various base space member cohorts.
  ///
  void create_cohorts();
  
  ///
  /// Create the coordinates and splitting plane section spaces and sections.
  ///
  void create_sections();
  

  //@}

  // ===========================================================
  /// @name DISPLAY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Expansion factor factor to use in exploded lattice display.
  ///
  static double& display_expansion_factor();

  ///
  /// If true, update display after each insert_plane call.
  ///
  static bool& display_insert_plane();

  ///
  /// If true, update display after each insert_line call.
  ///
  static bool& display_insert_line();

  ///
  /// If true, update display after each insert_line call
  /// but before retriangulation..
  ///
  static bool& display_untriangulated_insert_line();

  ///
  /// If true, update display after each remove_line call.
  ///
  static bool& display_remove_line();

  ///
  /// Displays this using vtk.
  ///
  void display(bool xexploded, bool xpt_labels);

  ///
  /// Displays the subvolumes in this using vtk.
  ///
  void display_subvolumes(bool xexploded, bool xpt_labels);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name NOTIFICATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Clears all the notification sets.
  ///
  void clear_notify_sets();

  ///
  /// If true, notify sets are automatically cleared
  /// before any insert or remove operation.
  ///
  bool auto_clear_notify_sets() const;

  ///
  /// Sets auto_clear_notify_sets to xval.
  ///
  void put_auto_clear_notify_sets(bool xval);
  
  
protected:

  ///
  /// If true, notify sets are automatically cleared
  /// before any insert or remove operation.
  ///
  bool _auto_clear_notify_sets;

private:

  //@}
 

  // ===========================================================
  /// @name KD_VERTEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Vertices.
  ///
  vertex_cohort& vertices();

  ///
  /// Vertices, const verion.
  ///
  const vertex_cohort& vertices() const;

protected:

  ///
  /// Vertices.
  ///
  vertex_cohort* _vertices;

private:

  //@}

 
  // ===========================================================
  /// @name KD_EDGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// All edges of the zones in the kd-tree.
  ///
  cohort& edges();

  ///
  /// All edges of the zones in the kd-tree.
  ///
  const cohort& edges() const;

  ///
  /// X-aligned edges of the zones in the kd-tree.
  ///
  kd_edge_cohort& x_edges();

  ///
  /// X-aligned edges of the zones in the kd-tree, const version.
  ///
  const kd_edge_cohort& x_edges() const;

  ///
  /// Y-aligned edges of the zones in the kd-tree.
  ///
  kd_edge_cohort& y_edges();

  ///
  /// Y-aligned edges of the zones in the kd-tree, const version.
  ///
  const kd_edge_cohort& y_edges() const;

  ///
  /// Z-aligned edges of the zones in the kd-tree.
  ///
  kd_edge_cohort& z_edges();

  ///
  /// Z-aligned edges of the zones in the kd-tree, const version.
  ///
  const kd_edge_cohort& z_edges() const;

protected:

  ///
  /// All edges of the zones in the kd-tree.
  ///
  cohort* _edges;

  ///
  /// X-aligned ddges of the zones in the kd-tree.
  ///
  kd_edge_cohort* _x_edges;

  ///
  /// Y-aligned ddges of the zones in the kd-tree.
  ///
  kd_edge_cohort* _y_edges;

  ///
  /// Z-aligned ddges of the zones in the kd-tree.
  ///
  kd_edge_cohort* _z_edges;

private:

  //@}

 
  // ===========================================================
  /// @name KD_FACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// All faces of the zones in the kd-tree.
  ///
  cohort& faces();

  ///
  /// All faces of the zones in the kd-tree.
  ///
  const cohort& faces() const;

  ///
  /// X-aligned faces of the zones in the kd-tree.
  ///
  kd_face_cohort& x_faces();

  ///
  /// X-aligned faces of the zones in the kd-tree, const version.
  ///
  const kd_face_cohort& x_faces() const;

  ///
  /// Y-aligned faces of the zones in the kd-tree.
  ///
  kd_face_cohort& y_faces();

  ///
  /// Y-aligned faces of the zones in the kd-tree, const version.
  ///
  const kd_face_cohort& y_faces() const;

  ///
  /// Z-aligned faces of the zones in the kd-tree.
  ///
  kd_face_cohort& z_faces();

  ///
  /// Z-aligned faces of the zones in the kd-tree, const version.
  ///
  const kd_face_cohort& z_faces() const;

protected:

  ///
  /// All faces of the zones in the kd-tree.
  ///
  cohort* _faces;

  ///
  /// X-aligned faces of the zones in the kd-tree.
  ///
  kd_face_cohort* _x_faces;

  ///
  /// Y-aligned faces of the zones in the kd-tree.
  ///
  kd_face_cohort* _y_faces;

  ///
  /// Z-aligned faces of the zones in the kd-tree.
  ///
  kd_face_cohort* _z_faces;

private:

  //@}


  // ===========================================================
  /// @name KD_ZONE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Zones in the kd-tree.
  ///
  kd_zone_cohort& zones();

  ///
  ///  Zones in the kd-tree, const verion.
  ///
  const kd_zone_cohort& zones() const;

  ///
  /// The largest zone; the domain of the lattice.
  ///
  kd_zone& top_zone();

  ///
  /// The largest zone; the domain of the lattice, const version.
  ///
  const kd_zone& top_zone() const;

  ///
  /// The set of zones cleared since the last triangulation update.
  ///
  pod_id_hash_set& cleared_zones();

  ///
  /// The set of zones cleared since the last triangulation update, const version.
  ///
  const pod_id_hash_set& cleared_zones() const;  

protected:

  ///
  /// Zones in the kd-tree.
  ///
  kd_zone_cohort* _zones;

  ///
  /// The largest zone; the domain of the lattice.
  ///
  kd_zone* _top_zone;

  ///
  /// The set of zones cleared since the last triangulation update.
  ///
  pod_id_hash_set _cleared_zones;

private:

  //@} 

  // ===========================================================
  /// @name LEAF FACET
  // ===========================================================
  //@{

public:

  ///
  /// All leaves in the kd-tree.
  ///
  cohort& leaves();

  ///
  ///  All leaves in the kd-tree, const verion.
  ///
  const cohort& leaves() const;

  ///
  /// Zones that are leaves in the kd-tree.
  ///
  cohort& zone_leaves();

  ///
  /// Zones that are leaves in the kd-tree, const version.
  ///
  const cohort& zone_leaves() const;
  

protected:

  ///
  /// Leaves in the kd-tree.
  ///
  cohort* _leaves;

  ///
  /// Zones that are leaves in the kd-tree.
  ///
  cohort* _zone_leaves;

private:

  //@} 


  // ===========================================================
  /// @name KD_PLANE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this contains a plane equal to xp.
  ///
  bool contains_plane(const kd_plane& xp) const;

  ///
  /// True if this contains a plane with the same alignment as xp
  /// and distance within plane_tolerance() of xp.
  ///
  bool contains_equivalent_plane(const kd_plane& xp) const;  

  ///
  /// A plane with the same alignment as xp
  /// and distance within plane_tolerance() of xp.
  ///
  kd_plane equivalent_plane(const kd_plane& xp) const;  

  ///
  /// Finds an exsiting plane with alignment and distance 
  /// equivalent to xalign and xdist, respectively, or
  /// creats a plane with those values.
  ///
  kd_plane get_equivalent_plane(kd_alignment xalign, vd_value_type xdist) const;  

  ///
  /// The splitting plane for the cell with id xid.
  ///
  const kd_plane& plane(const scoped_index& xid) const;

  ///
  /// Sets the splitting plane for the cell with id xid to plane xp.
  ///
  void put_plane(const scoped_index& xid, const kd_plane& xp);

  ///
  /// Insert plane xp.
  ///
  void insert_plane(const kd_plane& xp);

  ///
  /// Remove the plane with id xid.
  ///
  void remove_plane(const scoped_index& xid);

  ///
  /// The absolute tolerance for equality comparison of one plane to another.
  /// If a new plane and an existing plane both have the alignment A and 
  /// the new plane is within plane_tolerance()[A] of the existing plane, 
  /// the new plane "snaps" to the existing plane.
  ///
  const e3_lite& plane_tolerance() const;

  ///
  /// Sets plane_tolerance() to xtolerance.
  ///
  void put_plane_tolerance(const e3_lite& xtolerance);

protected:

  ///
  /// The set of splitting planes.
  ///
  set<kd_plane> _planes;

  ///
  /// Map from cell id to splitting plane.
  ///
  block<kd_plane> _cells_to_planes_map;

  ///
  /// The absolute tolerance for equality comparison of one plane to another.
  ///
  e3_lite _plane_tolerance;

private:

  //@}

  // ===========================================================
  /// @name KD_BOUNDING_BOX FACET
  // ===========================================================
  //@{

public:

  ///
  /// The bounding box for the enitre domain.
  ///
  const kd_bounding_box& bounding_box() const;

  ///
  /// The bounding box for the cell with id xid.
  ///
  kd_bounding_box& bounding_box(const scoped_index& xid);

  ///
  /// The bounding box for the cell with id xid, const version.
  ///
  const kd_bounding_box& bounding_box(const scoped_index& xid) const;
  
  ///
  /// Sets the bounding box for the cell with id xid to xb;
  /// may force reallocation of bounding box store and 
  /// invalidate any client-held references returned by
  /// accessor bounding_box(const scoped_index&)..
  ///
  void put_bounding_box(const scoped_index& xid, const kd_bounding_box& xb);
  

protected:

  ///
  /// Map from cell id to bounding box.
  ///
  block<kd_bounding_box> _cells_to_bounding_boxes_map;

private:

  //@}
 
  // ===========================================================
  /// @name POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Points.
  ///
  vertex_cohort& points();

  ///
  /// Points, const verion.
  ///
  const vertex_cohort& points() const;
  
  ///
  /// The points contained in the tree cell with id xid.
  ///
  void points(const scoped_index& xid, id_list& xpoints) const;

  ///
  /// Point location query; returns the id of the minimal tree cell
  /// of dimension at least xd containing point xpt.
  ///
  scoped_index locate_point(const e3_lite& xpt, int xd);

  ///
  /// Find the face leaf in plane xp that contains the beginning of line xline.
  ///
  void find_face_leaf(const kd_plane& xp, const pt_list& xline, scoped_index& xresult) const;

  ///
  /// Find the face leaves in plane xp.
  ///
  void find_face_leaves(const kd_plane& xp, id_list& xresult) const;

  ///
  /// Find the face leaves in plane xp contained in bounding box xb.
  ///
  void find_face_leaves(const kd_bounding_box& xb, const kd_plane& xp, id_list& xresult) const;

  ///
  /// The absolute tolerance for equality comparison of points.
  ///
  const e3_lite& point_tolerance() const;

  ///
  /// Sets point_tolerance() to xtolerance.
  ///
  void put_point_tolerance(const e3_lite& xtolerance);

  ///
  /// True if and only if point xpt is contained in the domain of this.
  ///
  bool contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if point xpt is contained in the interior of this.
  ///
  bool interior_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if point xpt is contained in the boundary of this.
  ///
  bool boundary_contains_point(const e3_lite& xpt) const;

  ///
  /// True if the tree cell with id xid contains point xpt.
  ///
  bool cell_contains_point(const scoped_index& xid, const e3_lite& xpt) const;
 
  ///
  /// Set of ids of new points.
  ///
  id_set& new_points();
 
  ///
  /// Set of ids of new points, const version.
  ///
  const id_set& new_points() const;
 
  ///
  /// Set of ids of modified points.
  ///
  id_set& modified_points();
 
  ///
  /// Set of ids of modified points, const version.
  ///
  const id_set& modified_points() const;
 
  ///
  /// Set of ids of deleted points.
  ///
  id_set& deleted_points();  
 
  ///
  /// Set of ids of deleted points, const version.
  ///
  const id_set& deleted_points() const;  

protected:

  ///
  /// Points.
  ///
  vertex_cohort* _points;

  ///
  /// The absolute tolerance for equality comparison of points.
  ///
  e3_lite _point_tolerance;
 
  ///
  /// Set of ids of new points.
  ///
  id_set _new_points;
 
  ///
  /// Set of ids of modified points.
  ///
  id_set _modified_points;
 
  ///
  /// Set of ids of deleted points.
  ///
  id_set _deleted_points;

private:

  //@}
  

  // ===========================================================
  /// @name TRUNCATION_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Truncation points.
  ///
  cohort& truncation_points();

  ///
  /// Truncation points, const verion.
  ///
  const cohort& truncation_points() const;

  ///
  /// The absolute tolerance for detection of truncations.
  ///
  const e3_lite& truncation_tolerance() const;

  ///
  /// Sets truncation_tolerance() to xtolerance.
  ///
  void put_truncation_tolerance(const e3_lite& xtolerance);

protected:

  ///
  /// Truncation points.
  ///
  cohort* _truncation_points;

  ///
  /// The absolute tolerance for detection of truncations.
  ///
  e3_lite _truncation_tolerance;

private:  

  //@}
  

  // ===========================================================
  /// @name TRUNCATION_MID_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Truncation_mid points.
  ///
  subcohort& truncation_mid_points();

  ///
  /// Truncation_mid points, const verion.
  ///
  const subcohort& truncation_mid_points() const;

protected:

  ///
  /// Truncation_mid points.
  ///
  subcohort* _truncation_mid_points;

private:  

  //@}

  // ===========================================================
  /// @name TRUNCATION_REVERSAL_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Truncation_reversal points.
  ///
  cohort& truncation_reversal_points();

  ///
  /// Truncation_reversal points, const verion.
  ///
  const cohort& truncation_reversal_points() const;

protected:

  ///
  /// Truncation_reversal points.
  ///
  cohort* _truncation_reversal_points;

private:  

  //@}
 

  // ===========================================================
  /// @name INTERSECTION_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Intersection points.
  ///
  cohort& intersection_points();

  ///
  /// Intersection points, const verion.
  ///
  const cohort& intersection_points() const;

  ///
  /// The absolute tolerance for detection of intersections.
  ///
  const e3_lite& intersection_tolerance() const;

  ///
  /// Sets intersection_tolerance() to xtolerance.
  ///
  void put_intersection_tolerance(const e3_lite& xtolerance);

protected:

  ///
  /// Intersection points.
  ///
  cohort* _intersection_points;

  ///
  /// The absolute tolerance for detection of intersections.
  ///
  e3_lite _intersection_tolerance;

private:  

  //@}

  // ===========================================================
  /// @name EDGE_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Points contained in kd_edges.
  ///
  cohort& edge_points();

  ///
  /// Points contained in kd_edges, const version.
  ///
  const cohort& edge_points() const;
  

protected:

  ///
  /// Points contained in kd_edges.
  ///
  cohort* _edge_points;

private:

  //@}

  // ===========================================================
  /// @name CENTROID FACET
  // ===========================================================
  //@{

public:

  ///
  /// Centroid points.
  ///
  subcohort& centroids();

  ///
  /// Centroid points, const verion.
  ///
  const subcohort& centroids() const;

protected:

  ///
  /// Centroid points.
  ///
  subcohort* _centroids;

private:  

  //@}

  // ===========================================================
  /// @name SEGMENT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Segments.
  ///
  d_cells_cohort& segments();

  ///
  /// Segments, const version.
  ///
  const d_cells_cohort& segments() const;

protected:

  ///
  /// Segments.
  ///
  d_cells_cohort* _segments;

private:

  //@}
 
  // ===========================================================
  /// @name LINE_SEGMENTS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Line segments.
  ///
  subcohort& line_segments();

  ///
  ///  Line segments, const verion.
  ///
  const subcohort& line_segments() const;

protected:

  ///
  ///  Line segments.
  ///
  subcohort* _line_segments;

private:

  //@}
 
  // ===========================================================
  /// @name FIRST_SEGMENTS FACET
  // ===========================================================
  //@{

public:

  ///
  /// First segments.
  ///
  cohort& first_segments();

  ///
  ///  First segments, const verion.
  ///
  const cohort& first_segments() const;

protected:

  ///
  ///  First segments.
  ///
  cohort* _first_segments;

private:

  //@}

 
  // ===========================================================
  /// @name LAST_SEGMENTS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Last segments.
  ///
  cohort& last_segments();

  ///
  ///  Last segments, const verion.
  ///
  const cohort& last_segments() const;

protected:

  ///
  ///  Last segments.
  ///
  cohort* _last_segments;

private:

  //@}

 
  // ===========================================================
  /// @name BOUNDARY_SEGMENTS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Boundary segments.
  ///
  subcohort& boundary_segments();

  ///
  ///  Boundary segments, const verion.
  ///
  const subcohort& boundary_segments() const;

protected:

  ///
  ///  Boundary segments.
  ///
  subcohort* _boundary_segments;

private:

  //@}

 
  // ===========================================================
  /// @name DIAGONAL_SEGMENTS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Diagonal segments.
  ///
  subcohort& diagonal_segments();

  ///
  ///  Diagonal segments, const verion.
  ///
  const subcohort& diagonal_segments() const;

protected:

  ///
  ///  Diagonal segments.
  ///
  subcohort* _diagonal_segments;

private:

  //@}

 
  // ===========================================================
  /// @name TRUNCATION_SEGMENTS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Truncation segments.
  ///
  subcohort& truncation_segments();

  ///
  ///  Truncation segments, const verion.
  ///
  const subcohort& truncation_segments() const;

protected:

  ///
  ///  Truncation segments.
  ///
  subcohort* _truncation_segments;

private:

  //@}

 
 
  // ===========================================================
  /// @name LINE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Lines.
  ///
  jim_cohort& lines();

  ///
  ///  Lines, const verion.
  ///
  const jim_cohort& lines() const;

  ///
  /// Forces the line given by the points in xline
  /// into the plane xp.
  ///
  void force_line(pt_list& xline, const kd_plane& xp);
  
  ///
  /// Insert the line given by the points in xline 
  /// and lying in the plane xp. If auto_triangulate(),
  /// retriangulate the affected zones,
  /// otherwise leave them untriangulated.
  ///
  scoped_index insert_line(pt_list& xline, const kd_plane& xp);

  ///
  /// Remove the line with id xid;
  /// if auto_triangulate(), retriangulate the affected zones,
  /// otherwise leave them untriangulated.
  ///
  void remove_line(const scoped_index& xid);
  
  ///
  /// Computes the lines implied by the intersection of plane xp with existing surfaces.
  ///
  void implicit_lines(const kd_plane& xp, pt_list_list& xresult);

  ///
  /// Points in implicit lines defined
  /// by plane-surface intersections.
  ///
  block<e3_lite>& iline_pts();  

  ///
  /// Points in implicit lines defined
  /// by plane-surface intersections, const version.
  ///
  const block<e3_lite>& iline_pts() const;  

  ///
  /// The type of map from triangle edge to implicit line point id.
  ///
  typedef map<pod_pair, scoped_index> iline_map_type;

  ///
  /// Map from triangle edge to implicit line point id.
  ///
  iline_map_type& iline_map();

  ///
  /// Map from triangle edge to implicit line point id, const version.
  ///
  const iline_map_type& iline_map() const;
 
  ///
  /// Set of ids of new lines.
  ///
  id_set& new_lines();
 
  ///
  /// Set of ids of new lines, const version.
  ///
  const id_set& new_lines() const;
 
  ///
  /// Set of ids of modified lines.
  ///
  id_set& modified_lines();
 
  ///
  /// Set of ids of modified lines, const version.
  ///
  const id_set& modified_lines() const;
 
  ///
  /// Set of ids of deleted lines.
  ///
  id_set& deleted_lines();  
 
  ///
  /// Set of ids of deleted lines, const version.
  ///
  const id_set& deleted_lines() const;  
  

protected:

  ///
  ///  Lines.
  ///
  jim_cohort* _lines;

  ///
  /// Points in implicit lines defined
  /// by plane-surface intersections.
  ///
  block<e3_lite> _iline_pts;  

  ///
  /// Map from triangle edge to implicit line point id.
  ///
  iline_map_type _iline_map;
 
  ///
  /// Set of ids of new lines.
  ///
  id_set _new_lines;
 
  ///
  /// Set of ids of modified lines.
  ///
  id_set _modified_lines;
 
  ///
  /// Set of ids of deleted lines.
  ///
  id_set _deleted_lines;
  
private:

  //@}


  // ===========================================================
  /// @name LINE WEB FACET
  // ===========================================================
  //@{

public:

  ///
  /// Line_webs.
  ///
  jim_cohort& line_webs();

  ///
  ///  Line_webs, const verion.
  ///
  const jim_cohort& line_webs() const;

protected:

  ///
  ///  Line_webs.
  ///
  jim_cohort* _line_webs;

private:

  //@}

 
  // ===========================================================
  /// @name TRIANGLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Triangles.
  ///
  d_cells_cohort& triangles();

  ///
  ///  Triangles, const verion.
  ///
  const d_cells_cohort& triangles() const;

  ///
  /// If true, triangulate after every change to this lattice.
  ///
  bool auto_triangulate() const;

  ///
  /// Set auto_triangulate() to xvalue.
  ///
  void put_auto_triangulate(bool xvalue);

  ///
  /// Retriangulates the entire lattice.
  ///
  void retriangulate();

  ///
  /// Retriangulates the cleared zones.
  ///
  void retriangulate_cleared_zones();
  
protected:

  ///
  ///  Triangles.
  ///
  d_cells_cohort* _triangles;

  ///
  /// If true, triangulate after every change to this lattice.
  ///
  bool _auto_triangulate;
  

private:

  //@} 
 
 
 
  // ===========================================================
  /// @name POLYGON FACET
  // ===========================================================
  //@{

public:

  ///
  /// Polygons.
  ///
  d_cells_cohort& polygons();

  ///
  ///  Polygons, const verion.
  ///
  const d_cells_cohort& polygons() const;

protected:

  ///
  ///  Polygons.
  ///
  d_cells_cohort* _polygons;

private:

  //@} 

 

  // ===========================================================
  /// @name SURFACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Surfaces.
  ///
  jim_cohort& surfaces();

  ///
  ///  Surfaces, const verion.
  ///
  const jim_cohort& surfaces() const;
 
  ///
  /// Set of ids of new surfaces.
  ///
  id_set& new_surfaces();
 
  ///
  /// Set of ids of new surfaces, const version.
  ///
  const id_set& new_surfaces() const;
 
  ///
  /// Set of ids of modified surfaces.
  ///
  id_set& modified_surfaces();
 
  ///
  /// Set of ids of modified surfaces, const version.
  ///
  const id_set& modified_surfaces() const;
 
  ///
  /// Set of ids of deleted surfaces.
  ///
  id_set& deleted_surfaces();  
 
  ///
  /// Set of ids of deleted surfaces, const version.
  ///
  const id_set& deleted_surfaces() const;  

protected:

  ///
  ///  Surfaces.
  ///
  jim_cohort* _surfaces;
 
  ///
  /// Set of ids of new surfaces.
  ///
  id_set _new_surfaces;
 
  ///
  /// Set of ids of modified surfaces.
  ///
  id_set _modified_surfaces;
 
  ///
  /// Set of ids of deleted surfaces.
  ///
  id_set _deleted_surfaces;

private:

  //@}

  // ===========================================================
  /// @name SUBVOLUME FACET
  // ===========================================================
  //@{

public:

  ///
  /// Surfaces bounding subvolumes.
  ///
  subcohort& subvolume_surfaces();

  ///
  /// Surfaces bounding subvolumes, const version.
  ///
  const subcohort& subvolume_surfaces() const;  

  ///
  /// The region of interest for subvolume extraction and meshing.
  ///
  kd_region& region_of_interest();

  ///
  /// The region of interest for subvolume extraction and meshing, const version.
  ///
  const kd_region& region_of_interest() const;

  ///
  /// The triangles contained in the volumes bounded by the region of interest.
  ///
  cohort& interior_triangles();

  ///
  /// The triangles contained in the volumes bounded by the region of interest, const version.
  ///
  const cohort& interior_triangles() const;

  ///
  /// Creates a new region of intersect surface
  /// with bounds xlb, xub.
  ///
  void insert_region(const e3_lite& xlb, const e3_lite& xub);

  ///
  /// Extract the subvolume surfaces within the region of interest.
  ///
  void extract_subvolume_surfaces();
  

protected:

  ///
  /// Surfaces bounding subvolumes.
  ///
  subcohort* _subvolume_surfaces;

  ///
  /// The region of interest.
  ///
  kd_region*  _region_of_interest;

  ///
  /// The triangles contained in the volumes bounded by the region of interest.
  ///
  cohort* _interior_triangles;
  
  
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
  virtual kd_lattice* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

  ///
  /// Assignment operator; disabled.
  ///
  kd_lattice& operator=(const kd_lattice& xother);

  ///
  /// Assignment operator; disabled.
  ///
  virtual kd_lattice& operator=(const any& xother);

private:

  //@}
 
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert kd_lattice& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_lattice& xn);

///
/// The deep size of kd_lattice& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_lattice& xn, bool xinclude_shallow = true);


// ===========================================================
// SPECIALIZATIONS
// ===========================================================

//
// Filter for members of type kd_zone.
//
template<> SHEAF_DLL_SPEC const subposet& kd_lattice::member_filter<kd_zone>();

//
// Filter for members of type kd_face.
//
template<> SHEAF_DLL_SPEC const subposet& kd_lattice::member_filter<kd_face>();

//
// Filter for members of type kd_edge.
//
template<> SHEAF_DLL_SPEC const subposet& kd_lattice::member_filter<kd_edge>();

//
// Filter for members of type kd_vertex.
//
template<> SHEAF_DLL_SPEC const subposet& kd_lattice::member_filter<kd_vertex>();
 
  
} // end namespace geometry

#endif // ifndef KD_LATTICE_H
