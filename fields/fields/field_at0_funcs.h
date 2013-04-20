

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIELD_AT0_FUNCS_H
#define FIELD_AT0_FUNCS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

namespace fields
{

///
/// Namespace containing the algrebra functions for a field 
/// with a property section of type sec_at0.
///
namespace field_at0_algebra
{

//==============================================================================
/// @name NON-MEMBER FUNCTIONS OF AT0 FACET
//==============================================================================
//@{

///
/// Compute acos of x0 (acos(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC acos(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute asin of x0 (asin(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC asin(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute atan of x0 (atan(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC atan(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute atan2 of x0/x1 (atan2(x0, x1)) (pre-allocated version).
///
void SHEAF_DLL_SPEC atan2(const field_at0& x0, const field_at0& x1, field_at0& xresult,
           bool xauto_access);

///
/// Compute ceil of x0 (ceil(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC ceil(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute cos of x0 (cos(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC cos(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute cosh of x0 (cosh(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC cosh(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute exp of x0 (exp(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC exp(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute fabs of x0 (fabs(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC fabs(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute floor of x0 (floor(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC floor(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute xsignificand = fmod(x0, xexp) (pre-allocated version).
///
void SHEAF_DLL_SPEC fmod(const field_at0& x0, const field_at0& x1, field_at0& xresult,
          bool xauto_access);

///
/// Compute frexp of x0 (frexp(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC frexp(const field_at0& x0, field_at0& xsignificand, field_at0& xexp,
           bool xauto_access);

///
/// Compute ldexp of x0 (ldexp(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC ldexp(const field_at0& x0, int xexp, field_at0& xresult,
           bool xauto_access);

///
/// Compute log of x0 (log(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC log(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute log10 of x0 (log10(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC log10(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute modf of x0 (modf(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC modf(const field_at0& x0, field_at0& xintpart, field_at0& xfractpart,
          bool xauto_access);

///
/// Compute x0 to power xexponent (pow(x0, xexponent)) (pre-allocated version).
///
void SHEAF_DLL_SPEC pow(const field_at0& x0, const vd_value_type& xexponent,
         field_at0& xresult, bool xauto_access);

///
/// Compute sin of x0 (sin(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC sin(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute sinh of x0 (sinh(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC sinh(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute sqrt of x0 (sqrt(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC sqrt(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute tan of x0 (tan(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC tan(const field_at0& x0, field_at0& xresult, bool xauto_access);

///
/// Compute tanh of x0 (tanh(x0)) (pre-allocated version).
///
void SHEAF_DLL_SPEC tanh(const field_at0& x0, field_at0& xresult, bool xauto_access);

//@}
  
} // namespace field_at0_algebra

} // namespace fields

#endif // ifndef FIELD_AT0_FUNCS_H
