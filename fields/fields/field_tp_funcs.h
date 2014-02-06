
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

#ifndef FIELD_TP_FUNCS_H
#define FIELD_TP_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

namespace fields
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF TP FACET
//==============================================================================
//@{

class SHEAF_DLL_SPEC field_atp;
class SHEAF_DLL_SPEC field_stp;

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_tp.
///
namespace field_tp_algebra
{

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC alt(const field_tp& x0, field_atp& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC sym(const field_tp& x0, field_stp& xresult, bool xauto_access);

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated version).
///
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xq.
///
void SHEAF_DLL_SPEC contract(const field_tp& x0, int xp, int xq, field_tp& xresult,
              bool xauto_access);

///
/// Tensor product of x0 and x1 (pre-allocated version).
///
void SHEAF_DLL_SPEC tensor(const field_tp& x0, const field_tp& x1, field_tp& xresult,
            bool xauto_access);

//@}

} // namespace field_tp_algebra

} // namespace fields

#endif // ifndef FIELD_TP_FUNCS_H
