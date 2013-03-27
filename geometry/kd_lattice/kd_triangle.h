// $RCSfile: kd_triangle.h,v $ $Revision: 1.4 $ $Date: 2012/07/04 16:42:17 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_triangle

#ifndef KD_TRIANGLE_H
#define KD_TRIANGLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef KD_MEMBER_H
#include "kd_member.h"
#endif

#ifndef STD_BITSET_H
#include "std_bitset.h"
#endif
 

namespace fiber_bundle
{
  class e3_lite;
}
  
namespace geometry
{
 
  class kd_lattice;
  
///
/// Linear triangle in the contents part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_triangle : public kd_member
{

  // ===========================================================
  /// @name KD_TRIANGLE FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{POINT_CT = 3};

  ///
  /// The name of the base space member prototype for triangles.
  ///
  static const string& prototype_name();

  ///
  /// Creates a new triangle in xhost with points specified by xv_ids.
  ///
  kd_triangle(kd_lattice& xhost, const scoped_index xv_ids[]);
  
  ///
  /// Creates a new triangle in xhost with points specified by xv_ids.
  ///
  static scoped_index new_triangle(kd_lattice& xhost, const scoped_index xv_ids[]);
  
  ///
  /// Creates a new triangle in xhost with points specified by xv_ids.
  ///
  static scoped_index new_triangle(kd_lattice& xhost,
                                   const scoped_index& xpt0_id,
                                   const scoped_index& xpt1_id,
                                   const scoped_index& xpt2_id);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_triangle(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_triangle(const kd_triangle& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_triangle();

  ///
  /// The members of this triangle.
  /// If xterminate, xmbrs is terminated with an invalid id.
  ///
  void members(id_list& xmbrs, bool xterminate = true) const;

  ///
  /// The members of the triangle with id xid in ld_lattice xhost.
  /// If xterminate, xmbrs is terminated by an invalid id.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs, bool xterminate = true);

  ///
  /// The members of this triangle and their coordinates.
  /// If xterminate, xmbrs and xcoords are terminated by an invalid member.
  ///
  void members(id_list& xmbrs, list<e3_lite>& xcoords, bool xterminate = true) const;

  ///
  /// The members of the triangle with id xid in ld_lattice xhost and their coordinates.
  /// If xterminate, xmbrs and xcoords are terminated by an invalid member.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs, list<e3_lite>& xcoords, bool xterminate = true);

  ///
  /// The points of this triangle.
  ///
  void points(scoped_index xresult[]) const;

  ///
  /// The points of the triangle with id xid in ld_lattice xhost.
  ///
  static void points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[]);

  ///
  /// The points of this triangle and their coordinates.
  ///
  void points(scoped_index xresult[], e3_lite xcoords[]) const;

  ///
  /// The points of the triangle with id xid in ld_lattice xhost and their coordinates.
  ///
  static void points(const kd_lattice& xhost, scoped_index xid, scoped_index xresult[], e3_lite xcoords[]);

  ///
  /// The id of the xi-th point.
  ///
  scoped_index point(int xi) const;

  ///
  /// The id of the xi-th point in the triangle with id xid in kd_lattice xhost.
  ///
  static scoped_index point(const kd_lattice& xhost, const scoped_index& xid, int xi);

  using kd_member::coord_bounds;

  ///
  /// The coordinate bounds for this triangle..
  ///
  void coord_bounds(e3_lite& xlb, e3_lite& xub) const;

  ///
  /// The coordinate bounds for the triangle with id xid in kd_lattice xhost.
  ///
  static void coord_bounds(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xlb, e3_lite& xub);

  ///
  /// The lower bound on the coordinates for this triangle.
  ///
  e3_lite coord_lower_bound() const;

  ///
  /// The lower bound on the coordinates for the triangle with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_lower_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The upper bound on the coordinates for this triangle.
  ///
  e3_lite coord_upper_bound() const;

  ///
  /// The upper bound on the coordinates for the triangle with id xid in kd_lattice xhost.
  ///
  static e3_lite coord_upper_bound(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The surface containing this triangle.
  ///
  scoped_index surface();
  
  ///
  /// The surface containing the triangle with id xid in kd_attice xhost.
  ///
  static scoped_index surface(const kd_lattice& xhost, const scoped_index xid);

  ///
  /// The surface containing this triangle.
  ///
  void surface(scoped_index& xresult);
  
  ///
  /// The surface containing the triangle with id xid in kd_attice xhost.
  ///
  static void surface(const kd_lattice& xhost, const scoped_index xid, scoped_index& xresult);

  ///
  /// The zone containing this triangle.
  ///
  scoped_index zone();
  
  ///
  /// The zone containing the triangle with id xied in kd_attice xhost.
  ///
  static scoped_index zone(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The zone containing this triangle.
  ///
  void zone(scoped_index& xresult);
  
  ///
  /// The zone containing the triangle with id xid in kd_lattice xhost.
  ///
  static void zone(const kd_lattice& xhost, const scoped_index& xid, scoped_index& xresult);  

  ///
  /// Clears the upper and lower cover of this triangle;
  /// returns the ids of the points in the lower cover in xpoints.
  ///
  void clear(scoped_index xpoints[]);

  ///
  /// Clears the upper and lower cover of the triangle with id xid in kd_lattice xhost;
  /// returns the ids of the points in the lower cover in xpoints.
  ///
  static void clear(kd_lattice& xhost, const scoped_index& xid, scoped_index xpoints[]);
  
  ///
  /// Deactivates this triangle.
  ///
  void deactivate();
  
  ///
  /// Deactivates the triangle with id xid in kd_lattice xhost.
  ///
  static void deactivate(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Computes the intersection, if any, of plane xp with
  /// this triangle, which is in the zone with id xzone_id, 
  /// and appends the result to xfrags and xmap.
  ///
  void intersect_plane(const kd_plane& xp, const scoped_index& xzone_id, frag_list& xfrags);

  ///
  /// Computes the intersection, if any, of plane xp with the
  /// triangle with id xid in kd_attice host, which is in the
  /// zone with id xzone_id, and appends the result to xfrags.
  ///
  static void intersect_plane(kd_lattice& xhost, 
                              const scoped_index& xid, 
                              const kd_plane& xp, 
                              const scoped_index& xzone_id,
                              frag_list& xfrags);
 
  ///
  /// Type of oriented triangle representation.
  ///
  typedef pair<scoped_index, bool> ot;
  
  ///
  /// Type of list of oriented triangles.
  ///
  typedef list<ot> ot_list;
  
  ///
  /// Hash functor for oriented triangles.
  ///
  struct ot_hash
  {
    size_t operator()(const ot& xot) const
    {
      return xot.first.pod();
    };
  };

  ///
  /// Type of set of oriented triangles.
  ///
  typedef hash_set<ot, ot_hash> ot_set;

  ///
  /// The triangle connected to the oriented triangle xot 
  /// in kd_lattice xhost through the edge with local id xedge_id.
  /// The orientation of the result is true if it
  /// is the same as the orientation of xot, false otherwise.
  /// If there are multiple neighbors connected through the
  /// edge, the one in the in-side of xot is returned.
  ///
  static void edge_neighbor(const kd_lattice& xhost, 
                            const scoped_index& xid,
                            bool xorientation,
                            const scoped_index xpt_ids[],
                            int xedge_id,
                            ot& xresult);  

  ///
  /// The local point id that is not xid0 or xid1.
  ///
  inline static int other_local_point_id(int xid0, int xid1)
  {
    require((0 <= xid0) && (xid0 < POINT_CT));
    require((0 <= xid1) && (xid1 < POINT_CT));

    return 3 - (xid0 + xid1);
  };


  ///
  /// The normal to this triangle.
  ///
  void normal(e3_lite& xresult) const;
  
  ///
  /// The normal to the triangle with id xid in kd_lattice xhost.
  ///
  static void normal(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xresult);
  

  
protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_triangle();

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
  virtual kd_triangle* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_triangle& operator=(const kd_triangle& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_triangle& operator=(const any& xother);

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
/// Insert kd_triangle& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_triangle& xn);

///
/// The deep size of kd_triangle& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_triangle& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_TRIANGLE_H
