

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Enums shared by kd_lattice cluster.

#ifndef KD_ENUMS_H
#define KD_ENUMS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace geometry
{
  ///
  /// Type of axis alignment. 
  /// Alignment is parallel to the indicated axis for edges and
  /// perpendicular to the indicated axis for faces.
  ///
  enum kd_alignment
  {
    X_AXIS_ALIGNED = 0, 
    Y_AXIS_ALIGNED = 1, 
    Z_AXIS_ALIGNED = 2, 
    NOT_AXIS_ALIGNED // Must be last.
  };

  ///
  /// Converts int xi to kd_alignment.
  ///
  SHEAF_DLL_SPEC kd_alignment alignment(int xi);

  ///
  /// @deprecated Use kd_plane::intersection_alignment.
  /// The alignment that is not xa0 or xa1.
  ///
  SHEAF_DLL_SPEC kd_alignment other_alignment(kd_alignment xa0, kd_alignment xa1);

  ///
  /// @deprecated Use kd_plane::intersection_int_alignment.
  /// The alignment that is not xa0 or xa1; int version
  ///
  SHEAF_DLL_SPEC inline int other_int_alignment(int xa0, int xa1)
  {
    return 3 - (xa0 + xa1);
  };
  
  ///
  /// Insert kd_alignment& xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC ostream & operator << (ostream &xos, const kd_alignment& xn);
  
} // end namespace geometry

#endif // ifndef KD_ENUMS_H
