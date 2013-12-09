
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
  const float float_tolerance = sqrt(std::numeric_limits<float>::epsilon());
  
  ///
  /// Absolute equality comparison of float xf0 to 0.0f using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(float xf0)
  {
    return std::abs(xf0) <= float_tolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to 0.0f using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(float xf0, float xtolerance)
  {
    return std::abs(xf0) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to 1.0f using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(float xf0)
  {
    return std::abs(xf0 - 1.0f) <= float_tolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to 1.0f using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(float xf0, float xtolerance)
  {
    return std::abs(xf0 - 1.0f) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to float xf1 using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(float xf0, float xf1)
  {
    return std::abs(xf0 - xf1) <= float_tolerance;
  };
  
  ///
  /// Absolute equality comparison of float xf0 to float xf1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(float xf0, float xf1, float xtolerance)
  {
    return std::abs(xf0 - xf1) <= xtolerance;
  };

  ///
  /// Relative equality comparison of float xf0 to float xf1 using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(float xf0, float xf1)
  {
    return std::abs(xf0 - xf1) <= float_tolerance*(std::abs(xf0) + std::abs(xf1));
  };
  
  ///
  /// Relative equality comparison of float xf0 to float xf1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(float xf0, float xf1, float xtolerance)
  {
    return std::abs(xf0 - xf1) <= xtolerance*(std::abs(xf0) + std::abs(xf1));
  };
  
  ///
  /// Combined equality comparison of float xf0 to float xf1 using tolerance float_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(float xf0, float xf1)
  {
    return std::abs(xf0 - xf1) <= float_tolerance*(std::abs(xf0) + std::abs(xf1) + 1.0f);
  };
  
  ///
  /// Combined equality comparison of float xf0 to float xf1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(float xf0, float xf1, float xtolerance)
  {
    return std::abs(xf0 - xf1) <= xtolerance*(std::abs(xf0) + std::abs(xf1) + 1.0f);
  };
  

  // ===========================================================
  // DOUBLE EQUALITY COMPARISION
  // ===========================================================

  ///
  /// Tolerance for double comparisons.
  ///
  const double double_tolerance = sqrt(std::numeric_limits<double>::epsilon());
  
  ///
  /// Absolute equality comparison of double xd0 to 0.0 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(double xd0)
  {
    return std::abs(xd0) <= double_tolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to 0.0 using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_0(double xd0, double xtolerance)
  {
    return std::abs(xd0) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to 1.0 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(double xd0)
  {
    return std::abs(xd0 - 1.0) <= double_tolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to 1.0 using tolerance xtolerance
  ///
  SHEAF_DLL_SPEC inline bool a_eql_1(double xd0, double xtolerance)
  {
    return std::abs(xd0 - 1.0) <= xtolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(double xd0, double xd1)
  {
    return std::abs(xd0 - xd1) <= double_tolerance;
  };
  
  ///
  /// Absolute equality comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool a_eql(double xd0, double xd1, double xtolerance)
  {
    return std::abs(xd0 - xd1) <= xtolerance;
  };

  ///
  /// Relative equality comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(double xd0, double xd1)
  {
    return std::abs(xd0 - xd1) <= double_tolerance*(std::abs(xd0) + std::abs(xd1));
  };
  
  ///
  /// Relative equality comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool r_eql(double xd0, double xd1, double xtolerance)
  {
    return std::abs(xd0 - xd1) <= xtolerance*(std::abs(xd0) + std::abs(xd1));
  };
  
  ///
  /// Combined equality equality comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(double xd0, double xd1)
  {
    return std::abs(xd0 - xd1) <= double_tolerance*(std::abs(xd0) + std::abs(xd1) + 1.0);
  };
  
  ///
  /// Combined equality equality comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_eql(double xd0, double xd1, double xtolerance)
  {
    return std::abs(xd0 - xd1) <= xtolerance*(std::abs(xd0) + std::abs(xd1) + 1.0);
  };
  

  // ===========================================================
  // DOUBLE LESS THAN OR EQUAL COMPARISION
  // ===========================================================
  
  ///
  /// Combined less than or equal comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lte(double xd0, double xd1)
  {
    return xd0 <= (xd1 + double_tolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  
  ///
  /// Combined less than or equal comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lte(double xd0, double xd1, double xtolerance)
  {
    return xd0 <= (xd1 + xtolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  

  // ===========================================================
  // DOUBLE LESS THAN COMPARISION
  // ===========================================================
  
  ///
  /// Combined less than comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lt(double xd0, double xd1)
  {
    return xd0 < (xd1 - double_tolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  
  ///
  /// Combined less than comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_lt(double xd0, double xd1, double xtolerance)
  {
    return xd0 < (xd1 - xtolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  

  // ===========================================================
  // DOUBLE GREATER THAN OR EQUAL COMPARISION
  // ===========================================================
  
  ///
  /// Combined greater than or equal comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gte(double xd0, double xd1)
  {
    return xd0 >= (xd1 - double_tolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  
  ///
  /// Combined greater than or equal comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gte(double xd0, double xd1, double xtolerance)
  {
    return xd0 >= (xd1 - xtolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  

  // ===========================================================
  // DOUBLE GREATER THAN COMPARISION
  // ===========================================================
  
  ///
  /// Combined greater than comparison of double xd0 to double xd1 using tolerance double_tolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gt(double xd0, double xd1)
  {
    return xd0 > (xd1 + double_tolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  
  ///
  /// Combined greater than comparison of double xd0 to double xd1 using tolerance xtolerance.
  ///
  SHEAF_DLL_SPEC inline bool c_gt(double xd0, double xd1, double xtolerance)
  {
    return xd0 > (xd1 + xtolerance*(std::abs(xd0) + std::abs(xd1) + 1.0));
  };
  

  
  
} // end namespace sheaf

#endif // ifndef TOLERANCE_COMPARISON_H
