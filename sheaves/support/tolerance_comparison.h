// $RCSfile: tolerance_comparison.h,v $ $Revision: 1.4 $ $Date: 2012/07/04 16:42:28 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class tolerance_comparison

#ifndef TOLERANCE_COMPARISON_H
#define TOLERANCE_COMPARISON_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_LIMITS_H
#include "std_limits.h"
#endif
 
#ifndef STD_MATH_H
#include "std_cmath.h"
#endif
 
namespace sheaf
{

  // ===========================================================
  // FLOAT COMPARISION
  // ===========================================================

  ///
  /// Tolerance for float comparisons.
  ///
  const float float_tolerance = sqrt(numeric_limits<float>::epsilon());
  
  ///
  /// Absolute equality comparison of float xf0 to 0.0f using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(float xf0)
  {
    return abs(xf0) <= float_tolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to 0.0f using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(float xf0, float xtolerance)
  {
    return abs(xf0) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to 1.0f using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(float xf0)
  {
    return abs(xf0 - 1.0f) <= float_tolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to 1.0f using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(float xf0, float xtolerance)
  {
    return abs(xf0 - 1.0f) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to float xf1 using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(float xf0, float xf1)
  {
    return abs(xf0 - xf1) <= float_tolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to float xf1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(float xf0, float xf1, float xtolerance)
  {
    return abs(xf0 - xf1) <= xtolerance;
  };

  ///
  /// Relative equality comparison of float xf0 to float xf1 using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(float xf0, float xf1)
  {
    return abs(xf0 - xf1) <= float_tolerance*(abs(xf0) + abs(xf1));
  };
  
  ///
  /// Relative equality comparison of float xf0 to float xf1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(float xf0, float xf1, float xtolerance)
  {
    return abs(xf0 - xf1) <= xtolerance*(abs(xf0) + abs(xf1));
  };
  
  ///
  /// Combined equality comparison of float xf0 to float xf1 using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(float xf0, float xf1)
  {
    return abs(xf0 - xf1) <= float_tolerance*(abs(xf0) + abs(xf1) + 1.0f);
  };
  
  ///
  /// Combined equality comparison of float xf0 to float xf1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(float xf0, float xf1, float xtolerance)
  {
    return abs(xf0 - xf1) <= xtolerance*(abs(xf0) + abs(xf1) + 1.0f);
  };
  

  // ===========================================================
  // DOUBLE EQUALITY COMPARISION
  // ===========================================================

  ///
  /// Tolerance for double comparisons.
  ///
  const double double_tolerance = sqrt(numeric_limits<double>::epsilon());
  
  ///
  /// Absolute equality comparison of double xd0 to 0.0 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(double xd0)
  {
    return abs(xd0) <= double_tolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to 0.0 using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(double xd0, double xtolerance)
  {
    return abs(xd0) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to 1.0 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(double xd0)
  {
    return abs(xd0 - 1.0) <= double_tolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to 1.0 using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(double xd0, double xtolerance)
  {
    return abs(xd0 - 1.0) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(double xd0, double xd1)
  {
    return abs(xd0 - xd1) <= double_tolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(double xd0, double xd1, double xtolerance)
  {
    return abs(xd0 - xd1) <= xtolerance;
  };

  ///
  /// Relative equality comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(double xd0, double xd1)
  {
    return abs(xd0 - xd1) <= double_tolerance*(abs(xd0) + abs(xd1));
  };
  
  ///
  /// Relative equality comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(double xd0, double xd1, double xtolerance)
  {
    return abs(xd0 - xd1) <= xtolerance*(abs(xd0) + abs(xd1));
  };
  
  ///
  /// Combined equality equality comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(double xd0, double xd1)
  {
    return abs(xd0 - xd1) <= double_tolerance*(abs(xd0) + abs(xd1) + 1.0);
  };
  
  ///
  /// Combined equality equality comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(double xd0, double xd1, double xtolerance)
  {
    return abs(xd0 - xd1) <= xtolerance*(abs(xd0) + abs(xd1) + 1.0);
  };
  

  // ===========================================================
  // DOUBLE LESS THAN OR EQUAL COMPARISION
  // ===========================================================
  
  ///
  /// Combined less than or equal comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lte(double xd0, double xd1)
  {
    return xd0 <= (xd1 + double_tolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  
  ///
  /// Combined less than or equal comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lte(double xd0, double xd1, double xtolerance)
  {
    return xd0 <= (xd1 + xtolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  

  // ===========================================================
  // DOUBLE LESS THAN COMPARISION
  // ===========================================================
  
  ///
  /// Combined less than comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lt(double xd0, double xd1)
  {
    return xd0 < (xd1 - double_tolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  
  ///
  /// Combined less than comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lt(double xd0, double xd1, double xtolerance)
  {
    return xd0 < (xd1 - xtolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  

  // ===========================================================
  // DOUBLE GREATER THAN OR EQUAL COMPARISION
  // ===========================================================
  
  ///
  /// Combined greater than or equal comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gte(double xd0, double xd1)
  {
    return xd0 >= (xd1 - double_tolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  
  ///
  /// Combined greater than or equal comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gte(double xd0, double xd1, double xtolerance)
  {
    return xd0 >= (xd1 - xtolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  

  // ===========================================================
  // DOUBLE GREATER THAN COMPARISION
  // ===========================================================
  
  ///
  /// Combined greater than comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gt(double xd0, double xd1)
  {
    return xd0 > (xd1 + double_tolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  
  ///
  /// Combined greater than comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gt(double xd0, double xd1, double xtolerance)
  {
    return xd0 > (xd1 + xtolerance*(abs(xd0) + abs(xd1) + 1.0));
  };
  

  
  
} // end namespace sheaf

#endif // ifndef TOLERANCE_COMPARISON_H
