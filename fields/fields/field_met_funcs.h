
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

#ifndef FIELD_MET_FUNCS_H
#define FIELD_MET_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

namespace fields
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF MET FACET
//==============================================================================
//@{

class SHEAF_DLL_SPEC field_ed;

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_met.
///
namespace field_met_algebra
{

///
/// Lower vector (pre-allocated version).
///
void SHEAF_DLL_SPEC lower(const field_met& xmetric, const field_ed& xvector,
           field_ed& xresult, bool xauto_access);

///
/// Raise covector (pre-allocated version).
///
void SHEAF_DLL_SPEC raise(const field_met& xmetric, const field_ed& xcovector,
           field_ed& xresult, bool xauto_access);

//@}

} // namespace field_met_algebra

} // namespace fields

#endif // ifndef FIELD_MET_FUNCS_H
