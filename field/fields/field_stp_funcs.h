
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


#ifndef FIELD_STP_FUNCS_H
#define FIELD_STP_FUNCS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

namespace fields
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF STP FACET
//==============================================================================
//@{

//$$SCRIBBLE: Currently all symmetric_product functions are
//            "not_implemented()" because the only meaningful
//            results would be like Sym(st2 (X) st2) = st4.
//            But we have not yet implemented any st4 classes.

///
/// The symmetric product of two general tensors (pre-allocated version).
///
void SHEAF_DLL_SPEC symmetric_product(const field_stp& x0, const field_stp& x1,
                       field_stp& xresult, bool xauto_access);

//@}

} // namespace fields

#endif // ifndef FIELD_STP_FUNCS_H
