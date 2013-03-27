
// $RCSfile: field_met_funcs.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:58:56 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIELD_MET_FUNCS_H
#define FIELD_MET_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
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
