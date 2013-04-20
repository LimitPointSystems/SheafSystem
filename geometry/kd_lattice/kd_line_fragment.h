

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_line_fragment

#ifndef KD_LINE_FRAGMENT_H
#define KD_LINE_FRAGMENT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

namespace geometry
{
  
///
/// A fragment of a line within a single surface,
/// represented as a list of of point ids.
///
class SHEAF_DLL_SPEC kd_line_fragment
{

  // ===========================================================
  /// @name KD_LINE_FRAGMENT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  kd_line_fragment();

  ///
  /// Creates an instance with an empty point id list
  /// and container_id == xcontainer_id.
  ///
  kd_line_fragment(const scoped_index& xcontainer_id);
  

  // Copy constructor; default memberwise will do.

  // Copy assignment operator; default memberwise will do.

  ///
  /// Destructor; not virtual, can not be a base class.
  ///
  ~kd_line_fragment();

protected:

private:

  //@}

  // ===========================================================
  /// @name POINT IDS FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// List of ids of points in this fragment.
  ///
  id_list pt_ids;

  ///
  /// Shorthand for pt_ids.front().
  ///
  const scoped_index& front() const
  {
    require(!pt_ids.empty());

    return pt_ids.front();
  }

  ///
  /// Shorthand for the element after pt_ids.front().
  ///
  const scoped_index& after_front() const
  {
    require(!pt_ids.empty() && (++pt_ids.begin() != pt_ids.end()));
    
    return *(++pt_ids.begin());
  }

  ///
  /// Shorthand for pt_ids.back().
  ///
  const scoped_index& back() const
  {
    require(!pt_ids.empty());

    return pt_ids.back();
  }

  ///
  /// Shorthand for the element before pt_ids.back().
  ///
  const scoped_index& before_back() const
  {
    require(!pt_ids.empty() && (++pt_ids.begin() != pt_ids.end()));
    
    return *(--(--pt_ids.end()));
  }

  ///
  /// @deprecated Use fromt().pod().
  /// Shorthand for pt_ids.front().pod().
  ///
  pod_index_type front_pod() const
  {
    require(!pt_ids.empty());

    return pt_ids.front().pod();
  }

  ///
  /// @deprecated Use back().pod().
  /// Shorthand for pt_ids.back().pod().
  ///
  pod_index_type back_pod() const
  {
    require(!pt_ids.empty());

    return pt_ids.back().pod();
  }

  ///
  /// True if and only if the last point in this 
  /// fragment is the same as the first.
  ///
  bool is_closed() const;

  ///
  /// True if and only if this is the reverse of xother.
  ///
  bool is_reverse_of(const kd_line_fragment& xother) const;

  ///
  /// True if this fragment spans a truncation, that is,
  /// if the front and back of this fragment are truncation points
  /// between the same two surfaces.
  ///
  bool spans_truncation(const kd_lattice& xhost, 
                        map<scoped_index, kd_truncation>& xid2t_map, 
                        bool& xis_reversal, 
                        bool& xis_truncated) const;

  ///
  /// Inserts xother_frag (xfwd true) or the reverse 
  /// of xother_frag (xfwd false) at front of this fragment.
  /// 
  void insert_front(const kd_line_fragment& xother_frag, bool xfwd);

  ///
  /// Inserts xother_frag (xfwd true) or the reverse 
  /// of xother_frag (xfwd false) at back of this fragment.
  /// 
  void insert_back(const kd_line_fragment& xother_frag, bool xfwd);

  ///
  /// Splices xother_frag at front of this fragment.
  /// 
  void splice_front(kd_line_fragment& xother_frag);

  ///
  /// Splices xother_frag at back of this fragment.
  /// 
  void splice_back(kd_line_fragment& xother_frag);
  
  ///
  /// The segment formed by the point referenced by xpt_id_itr
  /// and its successor.
  ///
  void segment(const kd_lattice& xhost, id_list::const_iterator xpt_id_itr, e3_lite& xresult) const;
  
protected:

private:

  //@}

  // ===========================================================
  /// @name COORDINATES FACET
  // ===========================================================
  //@{

public:

  ///
  /// The coordinates of the points in this fragment.
  ///
  void coords(const kd_lattice& xhost, pt_list& xresult) const;

  ///
  /// The coordinates of the points in this fragment,
  /// projected into the xu, xv plane.
  ///
  void coords(const kd_lattice& xhost, int xu, int xv, list<e2_lite>& xresult) const;

  ///
  /// Normal defined by the three points starting with *xpt_itr.
  ///
  void normal(const kd_lattice& xhost, id_list::const_iterator xpt_itr, e3_lite& xresult) const;
  

protected:

private:

  //@}
 
  // ===========================================================
  /// @name CONTAINER ID FACET
  // ===========================================================
  //@{

public:
   
  ///
  /// Id of the tree node containing 
  /// segments of this fragment.
  ///
  scoped_index container_id;

  ///
  /// Updates container_id with xcontainer_id.
  ///
  void update_container_id(const scoped_index& xcontainer_id);
  
  ///
  /// True if and only if this fragment spans
  /// multiple tree nodes.
  ///
  bool spans_multiple_faces() const;

protected:

private:

  //@}

  // ===========================================================
  /// @name SURFACE ID FACET
  // ===========================================================
  //@{

public:
   
  ///
  /// Id of the surface containing 
  /// segments of this fragment.
  ///
  scoped_index surface_id;

  ///
  /// True if the polygon defined by this is star-shaped.
  ///
  bool is_star_shaped(kd_lattice& xhost, int xu, int xv) const;

  ///
  /// True if the polygon defined by this is convex.
  ///
  bool is_convex(kd_lattice& xhost, int xu, int xv) const;

  ///
  /// Triangulates this fragment and links the triangles 
  /// to the frangemnt's surface and container; tests for
  /// convextity and uses triangulate_centroid is possible,
  /// otherwise uses triangulate_ear_clip.
  ///
  void triangulate(kd_lattice& xhost, int xu, int xv) const;

  ///
  /// Triangulates this fragment and links the triangles 
  /// to the frangemnt's surface and container.
  ///
  void triangulate_centroid(kd_lattice& xhost) const;

  ///
  /// Triangulates this fragment and links the triangles 
  /// to the frangemnt's surface and container.
  ///
  void triangulate_ear_clip(kd_lattice& xhost, int xu, int xv) const;

protected:

private:

  //@}
 
  // ===========================================================
  /// @name FRAG_LIST FACET
  // ===========================================================
  //@{

public:

  ///
  /// Appends the segment defined by xpt0_id and xpt1_id, 
  /// which lie in the surface with id xsurface_id and the 
  /// container with id xcontainer_id, in frag_list xfrags.
  ///
  static void append(const scoped_index& xv0_id, 
                     const scoped_index& xv1_id, 
                     const scoped_index& xsurface_id, 
                     const scoped_index& xcontainer_id,
                     frag_list& xfrags);
   
  ///
  /// Assembles the fragment in xfrags into closed lines by analyzing truncations;
  /// additional fragments are created as necessaary using prototype xfrag_prototype.
  ///
  static void assemble(kd_lattice& xhost, const kd_line_fragment& xfrag_prototype, frag_list& xifrags, frag_list& xofrags);
   
  ///
  /// Assembles the fragments in xifrags into lines; using rules for implicit lines.
  ///
  static void assemble(kd_lattice& xhost, frag_list& xifrags, frag_list& xofrags);
   
  ///
  /// Assembles the fragments in xefrags and xcfrags into lines; using rules for face fragments.
  ///
  static void assemble(kd_lattice& xhost, frag_list& xefrags, frag_list& xcfrags, frag_list& xofrags);

  ///
  /// Triangulates the convex polygons in the fragments in xfrags and links them to the frangemnt's container_id.
  ///
  static void triangulate(kd_lattice& xhost, const frag_list& xfrags, const scoped_index& xcontainer_id);

  ///
  /// Triangles the possibly non-convex fragments in xfrags and links them to the frangemnt's container_id.
  ///
  static void triangulate_non_convex(kd_lattice& xhost, 
                                     const frag_list& xfrags, 
                                     const scoped_index& xcontainer_id, 
                                     int xu, 
                                     int xv);
  
  
protected:

private:

  //@}
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert kd_line_fragment& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_line_fragment& xn);  

  ///
  /// Insert frag_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const frag_list& xn);

} // end namespace geometry

#endif // ifndef KD_LINE_FRAGMENT_H
