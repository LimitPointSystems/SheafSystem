

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_plane

#ifndef KD_PLANE_H
#define KD_PLANE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif
 

#ifndef KD_ENUMS_H
#include "kd_enums.h"
#endif 

namespace sheaf
{
  class namespace_poset;
}


namespace fiber_bundle
{
  class e3_lite;
}

  
namespace geometry
{
 
  class kd_lattice;
 

///
/// The type of row dof tuple for kd_member.
///
class SHEAF_DLL_SPEC kd_plane_row_dofs_type
{
public:

  ///
  /// The alignment.
  ///
  int alignment;

  ///
  /// The signed "distance" of the plane from the origin;
  /// the coordinate value at which the plane intersects
  /// the coordinate axis specified by the alignment.
  ///
  vd_value_type distance;
};
 
///
/// Anb axis-aligned splitting plane in a kd_lattice.
///
class SHEAF_DLL_SPEC kd_plane : public any
{

  // ===========================================================
  /// @name KD_PLANE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The row dof tuple type.
  ///
  typedef kd_plane_row_dofs_type row_dofs_type;

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The path of the schema required by this.
  ///
  virtual const poset_path& schema_path() const;

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);
  
  ///
  /// Default constructor.
  ///
  kd_plane();
  
  ///
  /// Creates a new plane with alignment xalign
  /// at distance xdist from the origin.
  ///
  kd_plane(kd_alignment xalign, vd_value_type xdist);

  ///
  /// Copy constructor
  ///
  kd_plane(const kd_plane& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_plane();

  ///
  /// Sets alignment() to xalign and distance() to xdist.
  ///
  void put(int xalign, vd_value_type xdist);

  ///
  /// The aligment of this.
  ///
  kd_alignment alignment() const;

  ///
  /// Sets alignment() to xalign.
  ///
  void put_alignment(int xalign);

  ///
  /// The aligment of this; int version;
  /// faster than enum version.
  ///
  int int_alignment() const;

  ///
  /// The signed distance of this from the origin.
  ///
  vd_value_type distance() const;

  ///
  /// Sets distance() to xdist.
  ///
  void put_distance(vd_value_type xdist);
  
  ///
  /// The row dof tuple.
  ///
  const row_dofs_type& row_dofs() const;

  ///
  /// Lexicographic comparison.
  ///
  bool operator<(const kd_plane& xother) const;

  ///
  /// True if this plane is a valid, axis-aligned plane.
  ///
  bool is_valid() const;

  ///
  /// True if and only if every point in xline
  /// lies precisely in this plane.
  ///
  bool contains_line(const list<e3_lite>& xline) const;

  ///
  /// The component indices for the local u and v axes in this plane;
  /// right-handed if xright_hand, otherwise left-handed..
  ///
  void local_axes(int& xu_id, int& xv_id, bool xright_hand) const;

  ///
  /// The component indices for the local u and v axes in a plane with alignment xalignment;
  /// right-handed if xright_hand, otherwise left-handed..
  ///
  static void local_axes(int xalignment, int& xu_id, int& xv_id, bool xright_hand);

  ///
  /// The alignment of the intersection of this with xother.
  ///
  kd_alignment intersection_alignment(const kd_plane& xother) const;

  ///
  /// The alignment of the intersection of this with xother, integer version.
  ///
  inline int intersection_int_alignment(const kd_plane& xother) const
  {
    return 3 - (_row_dofs.alignment + xother._row_dofs.alignment);  
  };

  ///
  /// The alignment of the intersection of this with xother_alignment, integer version.
  ///
  inline int intersection_int_alignment(int xother_alignment) const
  {
    return 3 - (_row_dofs.alignment + xother_alignment);  
  };

  enum on_code_type {ON = 1, BACK = 2, FRONT = 4, ON_BACK = 3, ON_FRONT = 5, CROSS = 6, NOT_AN_ON_CODE = 8};
  
  ///  
  /// Compares point xpt to the plane with id xid in kd_lattice xhost with tolerance xtolerance.
  ///
  on_code_type on_code(const e3_lite& xpt, const e3_lite& xtolerance) const;

  ///
  /// Converts int xi to on_code.
  ///
  static on_code_type on_code(int xi);

protected:

  ///
  /// The row dofs (data members).
  ///
  row_dofs_type _row_dofs;
  

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
  virtual kd_plane* clone() const;

  ///
  /// Equality comparison operator
  ///
  bool operator==(const kd_plane& xother) const;

  ///
  /// Assignment operator
  ///
  kd_plane& operator=(const kd_plane& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_plane& operator=(const any& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// ///
// /// Comparison functor for kd_plane;
// /// intended for use with stl set.
// ///
// class kd_plane_compare
// {
// public:

//   ///
//   /// Strict weak ordering.
//   ///
//   bool operator()(const kd_plane& x0, const kd_plane& x1) const
//   {
//     const kd_plane::row_dofs_type& lx0 = x0.row_dofs();
//     const kd_plane::row_dofs_type& lx1 = x1.row_dofs();
    
//     bool result = 
//       (lx0.alignment < lx1.alignment) ||
//       ((lx0.alignment == lx1.alignment) && 
//        !sheaf::a_eql(lx0.distance, lx1.distance, tolerance[lx0.alignment]) &&
//        (lx0.distance < lx1.distance));
    
//     return result;
//   };
  
//   ///
//   /// Comparison tolerance.
//   ///
//   e3_lite tolerance;

//   ///
//   /// Create an instance with tolerance == xtolerance.
//   ///
//   kd_plane_compare(const e3_lite& xtolerance)
//   {
//     tolerance = xtolerance;
//   };
// };

      

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
///
/// Insert kd_plane& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_plane& xn);
  
///
/// Insert kd_plane& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_plane::on_code_type& xn);

///
/// The deep size of kd_plane& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_plane& xn, bool xinclude_shallow = true);
  
///
/// Absolute equality comparison of plane xp0 to plane xp1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC 
bool a_eql(const kd_plane& xp0, const kd_plane& xp1, const e3_lite& xtolerance);
  
///
/// Relative equality comparison of plane xp0 to plane xp1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC inline bool r_eql(const kd_plane& xp0, const kd_plane& xp1, const e3_lite& xtolerance);

///
/// Combined comparison of plane xp0 to plane xp1.
///
SHEAF_DLL_SPEC
bool c_eql(const kd_plane& xp0, const kd_plane& xp1, const e3_lite& xtolerance);
  
///
/// Absolute equality comparison of point xp0 to plane xp1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC 
bool a_eql(const e3_lite& xp0, const kd_plane& xp1, const e3_lite& xtolerance);
  
///
/// Relative equality comparison of point xp0 to plane xp1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC inline bool r_eql(const e3_lite& xp0, const kd_plane& xp1, const e3_lite& xtolerance);

///
/// Combined comparison of point xp0 to plane xp1.
///
SHEAF_DLL_SPEC
bool c_eql(const e3_lite& xp0, const kd_plane& xp1, const e3_lite& xtolerance);

  
} // end namespace geometry

#endif // ifndef KD_PLANE_H
