
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

#ifndef FIELD_VD_FUNCS_H
#define FIELD_VD_FUNCS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

namespace fields
{

//=============================================================================
/// @name NON-MEMBER FUNCTIONS OF VD FACET
//=============================================================================
//@{

class SHEAF_DLL_SPEC field_at0;

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_vd.
///
namespace field_vd_algebra
{

///
/// x0 add x1 (pre-allocated version).
///
SHEAF_DLL_SPEC
void add(const field_vd& x0, const field_vd& x1, field_vd& xresult,
         bool xauto_access);

///
/// x0 add_equal x1 (self-allocated version);
/// synonym for add(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC
void add_equal(field_vd& xresult, const field_vd& xother, bool xauto_access);

///
/// x0 subtract x1 (pre-allocated version).
///
SHEAF_DLL_SPEC
void subtract(const field_vd& x0, const field_vd& x1, field_vd& xresult,
              bool xauto_access);

///
/// x0 subtract_equal x1 (self-allocated version);
/// synonym for subtract(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC
void subtract_equal(field_vd& xresult, const field_vd& xother,
                    bool xauto_access);

///
/// x0 multiplied by x1 (pre-allocated version).
///
SHEAF_DLL_SPEC
void multiply(const field_vd& x0, const sec_at0& x1, field_vd& xresult,
              bool xauto_access);

///
/// xresult multiply_equal xresult (pre-allocated version);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC
void multiply_equal(field_vd& xresult, const sec_at0& xother,
                    bool xauto_access);

///
/// x0 multiplied by x1 (a constant) (pre-allocated version).
///
SHEAF_DLL_SPEC
void multiply(const field_vd& x0, const vd_value_type& x1, field_vd& xresult,
              bool xauto_access);

///
/// xresult multiply_equal xother (pre-allocated version);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC
void multiply_equal(field_vd& xresult, const vd_value_type& xother,
                    bool xauto_access);

///
/// x0 divided by x1 (pre-allocated version).
///
SHEAF_DLL_SPEC
void divide(const field_vd& x0, const sec_at0& x1, field_vd& xresult,
            bool xauto_access);

///
/// xresult divide_equal xother (pre-allocated version);
/// synonym for divide(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC
void divide_equal(field_vd& xresult, const sec_at0& xother,
                  bool xauto_access);

///
/// x0 divided by x1 (a constant) (pre-allocated version).
///
SHEAF_DLL_SPEC
void divide(const field_vd& x0, const vd_value_type& x1, field_vd& xresult,
            bool xauto_access);

///
/// xresult divide_equal xother (pre-allocated version);
/// synonym for divide(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC
void divide_equal(field_vd& xresult, const vd_value_type& xother,
                  bool xauto_access);

///
/// Contraction of vector xvector on covector xcovector
/// (pre-allocated version).
///
SHEAF_DLL_SPEC
void contract(const field_vd& xvector, const field_vd& xcovector,
              field_at0& xresult, bool xauto_access);

//@}

} // namespace field_vd_algebra

} // namespace fields

#endif // ifndef FIELD_VD_FUNCS_H
