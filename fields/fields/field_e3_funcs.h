
// $RCSfile: field_e3_funcs.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:58:55 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIELD_E3_FUNCS_H
#define FIELD_E3_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
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
