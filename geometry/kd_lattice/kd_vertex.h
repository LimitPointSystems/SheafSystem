

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_vertex

#ifndef KD_VERTEX_H
#define KD_VERTEX_H

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
/// Vertex in the kd-tree part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_vertex : public kd_member
{

  // ===========================================================
  /// @name KD_VERTEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{DB = 0};

  ///
  /// The name of the base space member prototype for zones.
  ///
  static const string& prototype_name();
  
  ///
  /// Creates a new vertex in xhost.
  ///
  kd_vertex(kd_lattice& xhost);
  
  ///
  /// Creates a new vertex in xhost.
  ///
  static scoped_index new_vertex(kd_lattice& xhost);
  
  ///
  /// Creates a new vertex in xhost with coordinates xcoords.
  ///
  kd_vertex(kd_lattice& xhost, const e3_lite& xcoords);
  
  ///
  /// Creates a new vertex in xhost with coordinates xcoords.
  ///
  static scoped_index new_vertex(kd_lattice& xhost, const e3_lite& xcoords);
  
  ///
  /// Creates an instance attached to the zone with id xid in xhost.
  ///
  kd_vertex(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_vertex(const kd_vertex& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_vertex();

  ///
  /// The coordinates of this vertex, auto-allocated.
  ///
  e3_lite coords() const;

  ///
  /// The coordinates of the vertex with id xid in kd_lattice xhost, auto-allocated.
  ///
  static e3_lite coords(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The coordinates of this vertex, preallocated.
  ///
  void coords(e3_lite& xcoords) const;

  ///
  /// The coordinates of the vertex with id xid in kd_lattice xhost, preallocated.
  ///
  static void coords(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xcoords);

  ///
  /// Sets the coordinates of this vertex to xoccords.
  ///
  void put_coords(const e3_lite& xcoords);

  ///
  /// Sets the coordinates of the vertex with id xid in kd_lattice xhost to xcoords.
  ///
  static void put_coords(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xcoords);

  ///
  /// True if and only if xpt has the same coordinates as this vertex..
  ///
  bool contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if xpt has the same coordinates as
  /// the vertex with id xid in kd_lattice xhost.
  ///
  static bool contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt);

  ///
  /// Replaces the point with id xpt_id with this vertex
  /// in all memebers of the upper and lower cover of the point;
  /// then deletes the point.
  ///
  void replace_point(const scoped_index& xpt_id);

  ///
  /// Replaces the point with id xpt_id with the vertex
  /// withg id xid in kd_lattice xhost in all memebers 
  /// of the upper and lower cover of the point;
  /// then deletes the point.
  ///
  static void replace_point(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id);
  
  
protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_vertex();
  

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
  virtual kd_vertex* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_vertex& operator=(const kd_vertex& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_vertex& operator=(const any& xother);

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
/// Insert kd_vertex& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_vertex& xn);

///
/// The deep size of kd_vertex& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_vertex& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_VERTEX_H
