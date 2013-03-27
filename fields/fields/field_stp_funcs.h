
// $RCSfile: field_stp_funcs.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:22 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//


#ifndef FIELD_STP_FUNCS_H
#define FIELD_STP_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
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
