
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

#ifndef FIELD_ST2_FUNCS_H
#define FIELD_ST2_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

namespace fields
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF ST2 FACET
//==============================================================================
//@{

class SHEAF_DLL_SPEC field_at0;

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_st2.
///
namespace field_st2_algebra
{

///
/// The trace of x0.
///
void SHEAF_DLL_SPEC trace(const field_st2& x0, field_at0& xresult, bool xauto_access);

///
/// The determinant of x0.
///
void SHEAF_DLL_SPEC determinant(const field_st2& x0, field_at0& xresult, bool xauto_access);

//@}

} // namespace field_st2_algebra

} // namespace fields

#endif // ifndef FIELD_ST2_FUNCS_H
