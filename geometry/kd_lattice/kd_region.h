// $RCSfile: kd_region.h,v $ $Revision: 1.3 $ $Date: 2012/07/04 16:42:17 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_region

#ifndef KD_REGION_H
#define KD_REGION_H

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
/// A surface bounding a region of interest in a kd_lattice;
/// a domain for 3D mesh generation
///
class SHEAF_DLL_SPEC kd_region : public kd_member
{

  // ===========================================================
  /// @name KD_REGION FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{ FACE_CT = 6 };

  ///
  /// The name of the base space member prototype for regions.
  ///
  static const string& prototype_name();

  ///
  /// Creates a new region in xhost.
  ///
  kd_region(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub);
  
  ///
  /// Creates a new region in xhost.
  ///
  static void new_region(kd_lattice& xhost, const e3_lite& xlb, const e3_lite& xub, scoped_index& xresult);
  
  ///
  /// Creates an unattached instance with host() == xhost.
  ///
  kd_region(kd_lattice& xhost);
  
  ///
  /// Creates an instance attached to the region with id xid in xhost.
  ///
  kd_region(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_region(const kd_region& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_region();

  ///
  /// The members of this region.
  ///
  void members(id_list& xmbrs) const;

  ///
  /// The members of the region with id xid in ld_lattice xhost.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list& xmbrs);

  ///
  /// The triangles contained in this region.
  ///
  void triangles(id_list& xtriangles) const;

  ///
  /// The triangles contained in the region with id xid in kd_lattice xhost.
  ///
  static void triangles(const kd_lattice& xhost, const scoped_index& xid, id_list& xtriangles);

  ///
  /// Clears the upper and lower cover of this region;
  /// returns the ids of the deactivated members of the lower cover in xdeleted.
  ///
  void clear(pod_id_hash_set& xdeleted);  

  ///
  /// Clears the upper and lower cover of the region with id xid in kd_lattice xhost;
  /// returns the ids of the deactivated members of the lower cover in xdeleted.
  ///
  static void clear(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted);  

  ///
  /// True if this region has no contents (triangles).
  ///
  bool is_empty() const;
  
  ///
  /// True if the region with id xid in kd_lattice xhost has no contents (triangles).
  ///
  static bool is_empty(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Extract the Subvolume boundaries in this region.
  ///
  void subvolumes(id_list& xresult);

  ///
  /// Extract the subvolumes in the region with id xid in kd_lattice xhost.
  ///
  static void subvolumes(kd_lattice& xhost, const scoped_index& xid, id_list& xresult);
  

protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_region();

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
  virtual kd_region* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_region& operator=(const kd_region& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_region& operator=(const any& xother);

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
/// Insert kd_region& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_region& xn);

///
/// The deep size of kd_region& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_region& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_REGION_H
