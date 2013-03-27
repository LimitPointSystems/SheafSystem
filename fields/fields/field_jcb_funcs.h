
// $RCSfile: field_jcb_funcs.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:58:55 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIELD_JCB_FUNCS_H
#define FIELD_JCB_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

namespace fields
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF JCB FACET
//==============================================================================
//@{

class SHEAF_DLL_SPEC field_at1;

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_jcb.
///
namespace field_jcb_algebra
{

///
/// Push vector forward (pre-allocated version).
///
void SHEAF_DLL_SPEC push(const field_jcb& xjcb, const field_at1& xvector, field_at1& xresult,
         bool xauto_access);


///
/// Pull covector back (pre-allocated version).
///
void SHEAF_DLL_SPEC pull(const field_jcb& xjcb, const field_at1& xcovector, field_at1& xresult,
          bool xauto_access);

//@}

} // namespace field_jcb_algebra

} // namespace fields

#endif // ifndef FIELD_JCB_H
