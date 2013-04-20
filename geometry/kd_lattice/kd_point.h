

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_point

#ifndef KD_POINT_H
#define KD_POINT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef KD_MEMBER_H
#include "kd_member.h"
#endif

#ifndef STD_ITERATOR_H
#include "std_iterator.h"
#endif

namespace fiber_bundle
{
  class e3_lite;
}
  
namespace geometry
{
 
  class kd_lattice;
  
///
/// Point in the contents part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_point : public kd_member
{

  // ===========================================================
  /// @name KD_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of the base space member prototype for zones.
  ///
  static const string& prototype_name();
  
  ///
  /// Creates a new point in xhost.
  ///
  kd_point(kd_lattice& xhost);
  
  ///
  /// Creates a new point in xhost.
  ///
  static scoped_index new_point(kd_lattice& xhost);
  
  ///
  /// Creates a new point in xhost with coordinates xcoords.
  ///
  kd_point(kd_lattice& xhost, const e3_lite& xcoords);
  
  ///
  /// Creates a new point in xhost with coordinates xcoords.
  ///
  static scoped_index new_point(kd_lattice& xhost, const e3_lite& xcoords);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_point(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_point(const kd_point& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_point();

  ///
  /// The coordinates of this point, auto-allocated.
  ///
  e3_lite coords() const;

  ///
  /// The coordinates of the point with id xid in kd_lattice xhost, auto-allocated.
  ///
  static e3_lite coords(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The coordinates of this point, preallocated.
  ///
  void coords(e3_lite& xcoords) const;

  ///
  /// The coordinates of the point with id xid in kd_lattice xhost, preallocated.
  ///
  static void coords(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xcoords);

  ///
  /// Sets the coordinates of this point to xoccords.
  ///
  void put_coords(const e3_lite& xcoords);

  ///
  /// Sets the coordinates of the point with id xid in kd_lattice xhost to xcoords.
  ///
  static void put_coords(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xcoords);

  ///
  /// True if and only if xpt has the same coordinates as this point within tolerance xhost.point_tolerance().
  ///
  bool a_eql(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt has the same coordinates as
  /// the point with id xid in kd_lattice xhost within tolerance xhost.point_tolerance().
  ///
  static bool a_eql(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// Moves this point to position xpt and updates modified lists.
  ///
  void snap(const e3_lite& xpt);

  ///
  /// Moves the point with id xid in kd_lattice xhost 
  /// to position xpt and updates modified lists.
  ///
  static void snap(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// Merges this point with the point with id xother_id.
  /// If this pointis not a tree vertex,
  /// then it is the source of the merge and xother_id is the
  /// destination of the merge, otherwise xother_id is the source
  /// and this the destination. In either case, the source
  /// is replaced by the destination in the lower covers of
  /// every member of the upper cover of the source and the
  /// source is deactivated. The result is true if this is 
  /// the source and false otherwise.
  ///
  bool merge(scoped_index& xother_id);

  ///
  /// Merges the point with id xid with the point
  /// with id xother_id in kd_lattice xhost.
  /// If the point referred to by xid is not a tree vertex,
  /// then xid is the source of the merge and xother_id is the
  /// destination of the merge, otherwise xother_id is the source
  /// and xid the destination. In either case, the source
  /// is replaced by the destination in the lower covers of
  /// every member of the upper cover of the source and
  /// the source is deactivated. The result is true if xid 
  /// is the source and false otherwise.
  ///
  static bool merge(kd_lattice& xhost, scoped_index& xid, scoped_index& xother_id);
  
  ///
  /// Deactivates this point.
  ///
  void deactivate();
  
  ///
  /// Deactivates the point with id xid in kd_lattice xhost.
  ///
  static void deactivate(kd_lattice& xhost, scoped_index& xid);

  ///
  /// True if and only if this point is the first point in a line.
  ///
  bool is_first() const;

  ///
  /// True if and only if the point with id xid in 
  /// kd_lattice xhost is the first point in a line.
  ///
  static bool is_first(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if and only if this point is the last point in a line.
  ///
  bool is_last() const;

  ///
  /// True if and only if the point with id xid in 
  /// kd_lattice xhost is the last point in a line.
  ///
  static bool is_last(const kd_lattice& xhost, const scoped_index& xid);
  
  ///
  /// Updates the intersection_points and truncation_points 
  /// cohort membership of this point.
  ///
  void update_cohorts();
  
  ///
  /// Updates the intersection_points and truncation_points 
  /// cohort membership of the point with id xid in kd_lattice xhost.
  ///
  static void update_cohorts(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if and only if this point is contained in more than one line.
  ///
  bool is_intersection() const;

  ///
  /// True if and only if the point with id xid in 
  /// kd_lattice xhost is contained in more than one line.
  ///
  static bool is_intersection(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if and only if this point is contained in more than one surface.
  ///
  bool is_truncation() const;

  ///
  /// True if and only if the point with id xid in 
  /// kd_lattice xhost is contained in more than one surface.
  ///
  static bool is_truncation(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if and only if this point 
  /// is contained in more than one surface
  /// and the truncation relationship between the surfaces
  /// reverses at this point.
  ///
  bool is_truncation_reversal() const;

  ///
  /// True if and only if the point with id xid in 
  /// kd_lattice xhost is contained in more than one surface
  /// and the truncation relationship between the surfaces
  /// reverses at the point.
  ///
  static bool is_truncation_reversal(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The lines containing this point..
  ///
  void lines(id_list& xresult) const;

  ///
  /// The lines containing the point with id xid in kd_lattice xhost.
  ///
  static void lines(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The surfaces containing this point..
  ///
  void surfaces(id_list& xresult) const;

  ///
  /// The surfaces containing the point with id xid in kd_lattice xhost.
  ///
  static void surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The triangles containing this point..
  ///
  void triangles(id_list& xresult) const;

  ///
  /// The triangles containing the point with id xid in kd_lattice xhost.
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The segments containing this point..
  ///
  void segments(id_list& xresult) const;

  ///
  /// The segments containing the point with id xid in kd_lattice xhost.
  ///
  static void segments(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The faces containing this point..
  ///
  void faces(id_set& xresult) const;

  ///
  /// The faces containing the point with id xid in kd_lattice xhost.
  ///
  static void faces(const kd_lattice& xhost, const scoped_index& xid, id_set& xresult);

  ///
  /// True if this point is in the same face as the point with id xother_id.
  ///
  bool same_face(const scoped_index& xother_id) const;

  ///
  /// True if the point with id xid in kd_lattice xhost
  ///  is in the same face as the point with id xother_id.
  ///
  static bool same_face(const kd_lattice& xhost, const scoped_index& xid, const scoped_index& xother_id);  

//   ///
//   /// Computes the intersection of the plane xp with the surfaces containing
//   /// the point with id xid in kd_lattice xhost.
//   ///
//   static void intersect_surfaces(kd_lattice& xhost, const scoped_index& xid, const kd_plane& xp, frag_list& xfrags);



protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_point();
  

private:

  ///
  /// @deprecated
  /// The surfaces which are truncated at this point..
  ///
  void truncated_surfaces(id_list& xresult) const;

  ///
  /// @deprecated
  /// The surfaces which are truncated at the point with id xid in kd_lattice xhost.
  ///
  static void truncated_surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// @deprecated
  /// The surfaces which do the truncating at this point..
  ///
  void truncating_surfaces(id_list& xresult) const;

  ///
  /// @deprecated
  /// The surfaces which do the truncating at the point with id xid in kd_lattice xhost.
  ///
  static void truncating_surfaces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

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
  virtual kd_point* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_point& operator=(const kd_point& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_point& operator=(const any& xother);

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
/// Insert kd_point& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_point& xn);

///
/// The deep size of kd_point& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_point& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_POINT_H
