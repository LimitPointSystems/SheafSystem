
// $RCSfile: field_st2_funcs.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:58:56 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIELD_ST2_FUNCS_H
#define FIELD_ST2_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
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
