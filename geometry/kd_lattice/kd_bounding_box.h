// $RCSfile: kd_bounding_box.h,v $ $Revision: 1.4 $ $Date: 2012/07/04 16:42:16 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_bounding_box

#ifndef KD_BOUNDING_BOX_H
#define KD_BOUNDING_BOX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef E3_H
#include "e3.h"
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
  
namespace geometry
{
 
  class kd_lattice;
  
///
/// An axis-aligned bounding box.
///
class SHEAF_DLL_SPEC kd_bounding_box
{

  // ===========================================================
  /// @name KD_BOUNDING_BOX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  kd_bounding_box();

  ///
  /// Creates an instance with lb() == xlb and ub() == xub.
  ///
  kd_bounding_box(const e3_lite& xlb, const e3_lite& xub);

  /// Copy constructor; default memberwise initialization will do.

  ///
  /// Destructor; not virtual, can not be a base class.
  ///
  ~kd_bounding_box();

  ///
  /// The lower bound.
  ///
  e3_lite& lb();

  ///
  /// The lower bound, const version.
  ///
  const e3_lite& lb() const;
 
  ///
  /// The upper bound.
  ///
  e3_lite& ub();
 
  ///
  /// The upper bound, const version.
  ///
  const e3_lite& ub() const;

  ///
  /// The size of this box; the length of the edges
  /// in the x,y, and z directions; ub() - lb().
  ///
  e3_lite size() const;

  ///
  /// Assignment operator.
  ///
  kd_bounding_box& operator=(const kd_bounding_box& xother);

  ///
  /// Equality comparision.
  ///
  bool operator==(const kd_bounding_box& xother) const;

  ///
  /// True if and only if this contains bounding box xbox.
  ///
  bool contains(const kd_bounding_box& xbox) const;

  ///
  /// True if and only if this contains point xpt.
  ///
  bool contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if the interior of this contains point xpt.
  ///
  bool interior_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if the boundary of this contains point xpt.
  ///
  bool boundary_contains_point(const e3_lite& xpt) const;

  ///
  /// True if and only if this contains all the points xline.
  ///
  bool contains_line(const pt_list& xline) const;

  ///
  /// The Cohen-Sutherland out code type.
  ///
  enum out_code_2d_type {INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8, CLIPPED = 16, NOT_AN_OUT_CODE_2D = 32};
 
  ///
  /// Converts an int to an out_code_2d.
  ///
  static out_code_2d_type out_code_2d_from_int(int xcode);

  ///
  /// The Cohen-Sutherland out code for point with coordinates xpu, 
  /// xpv along axes xu, xv, respectively;.history independent
  ///
  int out_code_2d(const e3_lite& xpt, int xu, int xv) const;

  ///
  /// The Cohen-Sutherland out code for point with coordinates xpu, 
  /// xpv along axes xu, xv, respectively; history dependent
  ///
  int out_code_2d(double xpu, double xpv, int xu, int xv, int xhistory) const;
  
  ///
  /// Clips the line segment specified by points xp0 amd xp1
  /// against the rectangle specified by components xi and xj.
  /// Result can be bit-wise ored againt out code to determine
  /// which edges xpt is in.
  ///
  int clip_2d(const e3_lite& xp0, e3_lite& xp1, int xi, int xj) const;

  ///
  /// A 3D out code type.
  ///
  enum out_code_3d_type 
  {
    INSIDE_3D = 0, 
    OUTSIDE_FACE2 = 1, 
    OUTSIDE_FACE3 = 2, 
    OUTSIDE_FACE4 = 4, 
    OUTSIDE_FACE5 = 8, 
    OUTSIDE_FACE0 = 16, 
    OUTSIDE_FACE1 = 32, 
    NOT_AN_OUT_CODE_3D = 64
  };

  ///
  /// Out code for point xpt.
  ///
  int out_code_3d(const e3_lite& xpt) const;

  ///
  /// A code for testing whether points are strictly inside or are on the boundary.
  ///
  enum in_code_3d_type 
  {
    STRICT_INSIDE_3D = 0, 
    FACE2 = 1, 
    FACE3 = 2, 
    FACE4 = 4, 
    FACE5 = 8, 
    FACE0 = 16, 
    FACE1 = 32, 

    EDGE0  = int(FACE4) | int(FACE0),
    EDGE1  = int(FACE3) | int(FACE0),
    EDGE2  = int(FACE5) | int(FACE0),
    EDGE3  = int(FACE2) | int(FACE0),
    EDGE4  = int(FACE4) | int(FACE1),
    EDGE5  = int(FACE3) | int(FACE1),
    EDGE6  = int(FACE5) | int(FACE1),
    EDGE7  = int(FACE2) | int(FACE1),
    EDGE8  = int(FACE5) | int(FACE2),
    EDGE9  = int(FACE5) | int(FACE3),
    EDGE10 = int(FACE4) | int(FACE3),
    EDGE11 = int(FACE4) | int(FACE2),

    VERTEX0 = int(FACE2) | int(FACE4) | int(FACE0),
    VERTEX1 = int(FACE3) | int(FACE4) | int(FACE0),
    VERTEX2 = int(FACE3) | int(FACE5) | int(FACE0),
    VERTEX3 = int(FACE2) | int(FACE5) | int(FACE0),
    VERTEX4 = int(FACE2) | int(FACE4) | int(FACE1),
    VERTEX5 = int(FACE3) | int(FACE4) | int(FACE1),
    VERTEX6 = int(FACE3) | int(FACE5) | int(FACE1),
    VERTEX7 = int(FACE2) | int(FACE5) | int(FACE1)
  };

  ///
  /// In code for point xpt.
  ///
  int in_code_3d(const e3_lite& xpt) const;
  
  ///
  /// Converts in_code_3d to local vertex id.
  ///
  static int local_vertex_id(int xin_code_3d);
  
  ///
  /// Converts in_code_3d to local edge id.
  ///
  static int local_edge_id(int xin_code_3d);
  
  ///
  /// Converts in_code_3d to local face id.
  ///
  static int local_face_id(int xin_code_3d);
  
  ///
  /// Converts in_code_3d to local cell id of dimension xd.
  ///
  static void local_cell_id(int xin_code_3d, int& xlocal_cell_id, int& xd);
  
protected:

  ///
  /// The lower bound.
  ///
  e3_lite _lb;

  ///
  /// The upper bound.
  ///
  e3_lite _ub;


private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
///
/// Insert kd_bounding_box& xn into ostream& xos.
///
SHEAF_DLL_SPEC ostream & operator << (ostream &xos, const kd_bounding_box& xn);
  
///
/// Insert kd_bounding_box::out_code_2d_type xn into ostream& xos.
///
SHEAF_DLL_SPEC ostream & operator << (ostream &xos, const kd_bounding_box::out_code_2d_type& xn); 

///
/// Extracts individual out_cde_2d bits  from xcode.
///
SHEAF_DLL_SPEC list<kd_bounding_box::out_code_2d_type> parse_out_code_2d(int xcode);
  
///
/// Insert kd_bounding_box::out_code_2d_type xn into ostream& xos.
///
SHEAF_DLL_SPEC ostream & operator << (ostream &xos, const list<kd_bounding_box::out_code_2d_type>& xn); 

///
/// The deep size of kd_bounding_box& xn.
///
SHEAF_DLL_SPEC size_t deep_size(const kd_bounding_box& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_BOUNDING_BOX_H
