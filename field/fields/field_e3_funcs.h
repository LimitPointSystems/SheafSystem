
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
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

#ifndef FIELD_E3_FUNCS_H
#define FIELD_E3_FUNCS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

namespace fields
{

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_e3.
///
namespace field_e3_algebra
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF E3 FACET
//==============================================================================
//@{

///
/// The 3D Euclidean vector "cross" product of x0 with x1
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC cross(const field_e3& x0, const field_e3& x1, field_e3& xresult,
           bool xauto_access);

///
/// The 3D Euclidean vector "cross" product of xresult with xother,
/// /// synonym for cross(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC cross_equal(field_e3& xresult, const field_e3& xother,
                 bool xauto_access);

//@}
  
} // namespace field_e3_algebra

} // namespace fields

#endif // ifndef FIELD_E3_FUNCS_H
