// $RCSfile: kd_surface.h,v $ $Revision: 1.3 $ $Date: 2012/07/04 16:42:17 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_surface

#ifndef KD_SURFACE_H
#define KD_SURFACE_H

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
/// Surface in the contents part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_surface : public kd_member
{

  // ===========================================================
  /// @name KD_SURFACE FACET
  // ===========================================================
  //@{

public:
  
//   ///
//   /// Static const ints; hack to make MSC++ happy.
//   ///
//  enum static_const_int{};

  ///
  /// The name of the base space member prototype for surfaces.
  ///
  static const string& prototype_name();

  ///
  /// Creates a new surface in xhost.
  ///
  kd_surface(kd_lattice& xhost);
  
  ///
  /// Creates a new surface in xhost.
  ///
  static void new_surface(kd_lattice& xhost, scoped_index& xresult);
  
  ///
  /// Creates an instance attached to the surface with id xid in xhost.
  ///
  kd_surface(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_surface(const kd_surface& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_surface();

  ///
  /// The members of this surface.
  ///
  void members(id_list& xmbrs) const;

  ///
  /// The members of the surface with id xid in ld_lattice xhost.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs);

  ///
  /// The lines contained in this surface.
  ///
  void lines(id_list& xlines) const;

  ///
  /// The lines contained in the surface with id xid in kd_lattice xhost.
  ///
  static void lines(const kd_lattice& xhost, const scoped_index& xid, id_list& xlines);

  ///
  /// The triangles contained in this surface.
  ///
  void triangles(id_list& xtriangles) const;

  ///
  /// The triangles contained in the surface with id xid in kd_lattice xhost.
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangles);

  ///
  /// The  boundary of this surface as a list of line fragments.
  ///
  void boundary(id_list_list& xfrags) const;

  ///
  /// The boundary of the surface with id xid in 
  /// kd_lattice xhost as a list of line fragments.
  ///
  static void boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xfrags);

  ///
  /// The  boundary of this surface sorted into truncation and non-truncation parts.
  ///
  void boundary(id_list_list& xtrunc, id_list_list& xnon_trunc) const;

  ///
  /// The boundary of the surface with id xid in 
  /// kd_lattice xhost sorted into truncation and non-truncation parts..
  ///
  static void boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xtrunc, id_list_list& xnon_trunc);

  ///
  /// The truncation part of the boundary of this surface as a list of line_fragments.
  ///
  void truncation_boundary(id_list_list& xpts) const;

  ///
  /// The truncation part of the boundary of the surface with id xid in 
  /// kd_lattice xhost as a list of line fragments.
  ///
  static void truncation_boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xpts);

  ///
  /// The non-truncation part of the boundary of this surface as a list of line fragments.
  ///
  void non_truncation_boundary(id_list_list& xpts) const;

  ///
  /// The non-truncation part of the boundary of the surface with id xid in 
  /// kd_lattice xhost as a list of line fragments.
  ///
  static void non_truncation_boundary(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xpts);

  ///
  /// The truncation_points contained in this surface.
  ///
  void truncation_points(id_list& xpts) const;

  ///
  /// The truncation_points contained in the surface with id xid in kd_lattice xhost.
  ///
  static void truncation_points(const kd_lattice& xhost, const scoped_index& xid, id_list& xpts);

  ///
  /// The intersection_points contained in this surface.
  ///
  void intersection_points(id_list& xpts) const;

  ///
  /// The intersection_points contained in the surface with id xid in kd_lattice xhost.
  ///
  static void intersection_points(const kd_lattice& xhost, const scoped_index& xid, id_list& xpts);
  
  ///
  /// Inserts the line with id xnew_line_id in this surface.
  ///
  void insert_line(const scoped_index& xnew_line_id);
  
  ///
  /// Inserts the line with id xline_id in the surface 
  /// with id xid in kd_lattice xhost.
  ///
  static void insert_line(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xline_id);

  ///
  /// Merge the surfaces with ids in xsurfaces in kd_lattice xhost
  /// into a single surface with id xsurfaces.begin().
  ///
  static void merge(kd_lattice& xhost, id_set& xsurfaces);

  ///
  /// Clears the upper and lower cover of this surface;
  /// returns the ids of the deactivated members of the lower cover in xdeleted.
  ///
  void clear(pod_id_hash_set& xdeleted);  

  ///
  /// Clears the upper and lower cover of the surface with id xid in kd_lattice xhost;
  /// returns the ids of the deactivated members of the lower cover in xdeleted.
  ///
  static void clear(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted);  
  
  ///
  /// Deactivates this surface.
  ///
  void deactivate();
  
  ///
  /// Deactivates the surface with id xid in kd_lattice xhost.
  ///
  static void deactivate(kd_lattice& xhost, const scoped_index& xid);
  
  ///
  /// True if this surface has no contents (triangles or lines).
  ///
  bool is_empty() const;
  
  ///
  /// True if the surface with id xid in kd_lattice xhost has no contents (triangles or lines).
  ///
  static bool is_empty(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Decomposes this surface into its connected components.
  ///
  void decompose(id_list& xnew_surfaces);

  ///
  /// Decomposes the surface with id xid in kd_lattice xhost
  /// into its connected components.
  ///
  static void decompose(kd_lattice& xhost, const scoped_index& xid, id_list& xnew_surfaces);
  

protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_surface();

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
  virtual kd_surface* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_surface& operator=(const kd_surface& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_surface& operator=(const any& xother);

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
/// Insert kd_surface& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_surface& xn);

///
/// The deep size of kd_surface& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_surface& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_SURFACE_H
