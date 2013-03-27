
// $RCSfile: field_atp_funcs.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:58:55 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIELD_ATP_FUNCS_H
#define FIELD_ATP_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

namespace fields
{

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_atp.
///
namespace field_atp_algebra
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF ATP FACET
//==============================================================================
//@{

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC hook(const field_atp& x0, const  field_atp& x1, field_atp& xresult,
          bool xauto_access);

//void star(const atp& x0, atp& xresult, bool xauto_access);
///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC star(const field_atp& x0, field_atp& xresult, bool xauto_access);

//void wedge(const atp& x0, const atp& x1, atp& xresult,
//           bool xauto_access);
///
/// The exterior (wedge) product of two antisymmetric tensors
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC wedge(const field_atp& x0, const field_atp& x1, field_atp& xresult,
           bool xauto_access);

//@}

} // namespace field_atp_algebra

} // namespace fields

#endif // ifndef FIELD_ATP_FUNCS_H
