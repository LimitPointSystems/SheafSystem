
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

#ifndef FIELD_ED_FUNCS_H
#define FIELD_ED_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

namespace fields
{

//=============================================================================
/// @name NON-MEMBER FUNCTIONS OF ED FACET
//=============================================================================
//@{

class SHEAF_DLL_SPEC field_at0;

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_ed.
///
namespace field_ed_algebra
{

///
/// The Euclidean "dot" product of x0 with x2.
///
void SHEAF_DLL_SPEC dot(const field_ed& x0, const field_ed& x1, field_at0& xresult,
         bool xauto_access);

///
/// The Euclidean length (magnitude) of x0.
///
void SHEAF_DLL_SPEC length(const field_ed& x0, field_at0& xresult,
            bool xauto_access);

///
/// Set the Euclidean length (magnitude) of x0 to xlength.
///
void SHEAF_DLL_SPEC put_length(field_ed& x0, const vd_value_type& xlength,
                bool xauto_access);

///
/// Normalize x0 (convert to a unit vector).
///
void SHEAF_DLL_SPEC normalize(const field_ed& x0, field_ed& xresult,
               bool xauto_access);

///
/// Normalize x0 (convert to a unit vector) in place;
/// synonym for normalize(x0, x0, xauto_access).
///
void SHEAF_DLL_SPEC normalize(field_ed& x0, bool xauto_access);

//@}

} // namespace field_ed_algebra

} // namespace fields

#endif // ifndef FIELD_ED_FUNCS_H
