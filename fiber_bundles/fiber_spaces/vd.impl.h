
// $RCSfile: vd.impl.h,v $ $Revision: 1.12 $ $Date: 2013/03/13 00:58:45 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for vd facet function templates.

#ifndef VD_IMPL_H
#define VD_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef VD_H
#include "vd.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS VD_ROW_DOFS_TYPE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
const string&
vd_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("vd_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
T&
vd_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  require(xindex >= 0);

  // Body:

  T& result = reinterpret_cast<T*>(this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const T&
vd_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  require(xindex >= 0);

  // Body:

  const T& result = reinterpret_cast<const T*>(this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
vd_row_dofs_type<T>* 
vd_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  vd_row_dofs_type<T>* result = new vd_row_dofs_type<T>();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

// ===========================================================
// VECTOR ALGEBRA
// ===========================================================

namespace vd_algebra
{

// ===========================================================
// VECTOR ALGEBRA: ADDITION
// ===========================================================

// Instantiates for persisent and volatile types.

template <typename T>
T* add(const T& x0, const T& x1)
{
  // Preconditions:

  require(precondition_of(x0.clone()));
  require(precondition_of(add(x0, x1, *result)));

  // Body:

  T* result = x0.clone();

  add(x0, x1, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(x0.clone()));
  ensure(postcondition_of(add(x0, x1, *result)));

  // Exit:

  return result;
}

template <typename T>
void add_equal(T& xresult, const T& xother)
{
  // Preconditions:

  require(precondition_of(add(xresult, xother, xresult)));

  // Body:

  add(xresult, xother, xresult);

  // Postconditions:

  ensure(postcondition_of(add(xresult, xother, xresult)));

  // Exit:

  return;
}

#ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

template <typename T>
T* operator+(const T& x0, const T& x1)
{
  // Preconditions:

  require(precondition_of(result = add(x0, x1)));

  // Body:

  T* result = add(x0, x1);

  // Postconditions:

  ensure(postcondition_of(result = add(x0, x1)));

  // Exit:

  return result;
}

template <typename T>
T& operator+=(T& xresult, const T& xother)
{
  // Preconditions:

  require(precondition_of(add_equal(xresult, xother)));

  // Body:

  add_equal(xresult, xother);

  // Postconditions:

  ensure(postcondition_of(add_equal(xresult, xother)));

  // Exit:

  return xresult;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

// ===========================================================
// VECTOR ALGEBRA: SUBTRACTION
// ===========================================================

// Instantiates for any volatile type.

template <typename T>
T* subtract(const T& x0, const T& x1)
{
  // Preconditions:

  require(precondition_of(x0.clone()));
  require(precondition_of(subtract(x0, x1, *result)));

  // Body:

  T* result = x0.clone();

  subtract(x0, x1, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(x0.clone()));
  ensure(postcondition_of(subtract(x0, x1, *result)));

  // Exit:

  return result;
}

template <typename T>
void subtract_equal(T& xresult, const T& xother)
{
  // Preconditions:

  require(precondition_of(subtract(xresult, xother, xresult)));

  // Body:

  subtract(xresult, xother, xresult);

  // Postconditions:

  ensure(postcondition_of(subtract(xresult, xother, xresult)));

  // Exit:

  return;
}

#ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

template <typename T>
T* operator-(const T& x0, const T& x1)
{
  // Preconditions:

  require(precondition_of(result = subtract(x0, x1)));

  // Body:

  T* result = subtract(x0, x1);

  // Postconditions:

  ensure(postcondition_of(result = subtract(x0, x1)));

  // Exit:

  return result;
}

template <typename T>
T& operator-=(T& xresult, const T& xother)
{
  // Preconditions:

  require(precondition_of(subtract_equal(xresult, xother)));

  // Body:

  subtract_equal(xresult, xother);

  // Postconditions:

  ensure(postcondition_of(subtract_equal(xresult, xother)));

  // Exit:

  return xresult;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS


// ===========================================================
// VECTOR ALGEBRA: SCALAR MULTIPLICATION
// ===========================================================

// $$SCRIBBLE kabuch: This makes no sense. doxygen does not complain about
//		      divide() and it has the same template structure and
//		      arguments.
#ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

template <typename T>
T* multiply(const T& x0, const vd_value_type& x1)
{
  // Preconditions:

  require(precondition_of(multiply(x0, x1, result)));

  // Body:

  T* result = x0.clone();

  multiply(x0, x1, *result);

  // Postconditions:

  ensure(postcondition_of(multiply(x0, x1, *result)));

  // Exit:

  return result;
}

template <typename T>
void multiply_equal(T& xresult, const vd_value_type& x1)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, x1, xresult)));

  // Body:

  multiply(xresult, x1, xresult);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, x1, xresult)));

  // Exit:

  return;
}

template <typename T>
T* operator*(const T& x0, const vd_value_type& x1)
{
  // Preconditions:

  // Body:

  T* result = multiply(x0, x1);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
T& operator*=(T& x0, const vd_value_type& x1)
{
  // Preconditions:

  // Body:

  multiply_equal(x0, x1);

  // Postconditions:

  // Exit:

  return x0;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS


// ===========================================================
// VECTOR ALGEBRA: SCALAR DIVISION
// ===========================================================

template <typename T>
T* divide(const T& x0, const vd_value_type& x1)
{
  // Preconditions:

  require(precondition_of(divide(x0, x1, result)));

  // Body:

  T* result = x0.clone();

  divide(x0, x1, *result);

  // Postconditions:

  ensure(postcondition_of(divide(x0, x1, *result)));

  // Exit:

  return result;
}

template <typename T>
void divide_equal(T& xresult, const vd_value_type& x1)
{
  // Preconditions:

  require(precondition_of(divide(xresult, x1, xresult)));

  // Body:

  divide(xresult, x1, xresult);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, x1, xresult)));

  // Exit:

  return;
}

template <typename T>
T* operator/(const T& x0, const vd_value_type& x1)
{
  // Preconditions:

  // Body:

  T* result = divide(x0, x1);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
T& operator/=(T& x0, const vd_value_type& x1)
{
  // Preconditions:

  // Body:

  divide_equal(x0, x1);

  // Postconditions:

  // Exit:

  return x0;
}
  
} // namespace vd_algebra

} // namespace fiber_bundle

#endif // ifndef VD_IMPL_H
