
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

// Implementation for antisymmetric_matrix_2x2.


#ifndef ANTISYMMETRIC_MATRIX_2X2_IMPL_H
#define ANTISYMMETRIC_MATRIX_2X2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef ANTISYMMETRIC_MATRIX_2X2_H
#include "antisymmetric_matrix_2x2.h"
#endif

#ifndef GENERAL_MATRIX_1X2_H
#include "general_matrix_1x2.h"
#endif

#ifndef GENERAL_MATRIX_2X1_H
#include "general_matrix_2x1.h"
#endif

#ifndef GENERAL_MATRIX_2X2_H
#include "general_matrix_2x2.h"
#endif

#ifndef GENERAL_MATRIX_2X3_H
#include "general_matrix_2x3.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

//==============================================================================
// MEMBER FUNCTIONS
//==============================================================================

///
template <typename T>
antisymmetric_matrix_2x2<T>::
operator at2_e2_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  at2_e2_row_dofs_type<T>& result =
    reinterpret_cast<at2_e2_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
int
antisymmetric_matrix_2x2<T>::
number_of_rows()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 2;
}

///
template <typename T>
int
antisymmetric_matrix_2x2<T>::
number_of_columns()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 2;
}

///
template <typename T>
int
antisymmetric_matrix_2x2<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 1;
}

///
template <typename T>
T*
antisymmetric_matrix_2x2<T>::
operator[](int nrow)
{
  // Preconditions:

  require(nrow >= 0 && nrow < number_of_rows());

  // Body:

  T* result = &components[row_index(nrow)];

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

template <typename T>
const T*
antisymmetric_matrix_2x2<T>::
operator[](int nrow) const
{
  // Preconditions:

  require(nrow >= 0 && nrow < number_of_rows());

  // Body:

  const T* result = &components[row_index(nrow)];

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
antisymmetric_matrix_2x2<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  //cout << "antisymmetric_matrix_2x2<T>::operator T* () " << std::endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
antisymmetric_matrix_2x2<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  //cout << "antisymmetric_matrix_2x2<T>::operator const T* () const " << std::endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
antisymmetric_matrix_2x2<T>::
row_index(int xrow) const
{

  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows()-1);

  // Body:

  int nrows = number_of_rows();
  int result = (xrow*(2*nrows-1-xrow))/2 - 1 - xrow;

  //int result = (xrow*(3-xrow))/2 - 1 - xrow;

  // Postconditions:

  ensure(result == (xrow*(2*number_of_rows()-1-xrow))/2 - 1 - xrow);

  // Exit:

  return result;
}

///
template <typename T>
antisymmetric_matrix_2x2<T>::
operator general_matrix_2x2<T> () const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;

  const antisymmetric_matrix_2x2<T>& lm = *this;

  result[0][0] =  0.0;
  result[0][1] =  lm[0][1];
  result[1][0] = -lm[0][1];
  result[1][1] =  0.0;

  // Postconditions:

  ensure(unexecutable("result == *this"));

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x2<T>
antisymmetric_matrix_2x2<T>::
row(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  general_matrix_1x2<T> result;

  // Just brute force it for the 2x2 case.

  if(xrow == 0)
  {
    result.components[0] =  0.0;           // [0][0];
    result.components[1] =  components[0]; // [0][1];
  }
  else // xrow == 1
  {
    result.components[0] = -components[0]; // [1][0];
    result.components[1] =  0.0;           // [1][1];
  }

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
general_matrix_2x1<T>
antisymmetric_matrix_2x2<T>::
column(int xcolumn) const
{
  // Preconditions:

  require(xcolumn >= 0 && xcolumn < number_of_columns());

  // Body:

  general_matrix_2x1<T> result;

  // Just brute force it for the 2x2 case.

  if(xcolumn == 0)
  {
    result.components[0] =  0.0;           // [0][0];
    result.components[1] = -components[0]; // [1][0];
  }
  else // xcolumn == 1
  {
    result.components[0] =  components[0]; // [0][1];
    result.components[1] =  0.0;           // [1][1];
  }

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
void
general_matrix_2x2<T>::
adjoint(general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = lm[1][0];
  T a11 = lm[1][1];

  // Adjoint is the transpose of the cofactor matrix.

  xresult[0][0] =  a11;
  xresult[0][1] = -a01;
  xresult[1][0] = -a10;
  xresult[1][1] =  a00;

  // Postconditions:

  // Exit:
}


///
template <typename T>
void
antisymmetric_matrix_2x2<T>::
adjoint(antisymmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Get the cofactor.

  // Note that the result for a 2x2 is also
  // an antisymmetric matrix.

  //xresult[0][0] =  0.0;
  xresult[0][1] = -components[0];
  //xresult[1][0] =  components[0];
  //xresult[1][1] =  0.0;

  // Postconditions:

  // Exit:
}

///
template <typename T>
antisymmetric_matrix_2x2<T>
antisymmetric_matrix_2x2<T>::
adjoint() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_2x2<T> result;
  adjoint(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
antisymmetric_matrix_2x2<T>::
assign(const T& xvalue)
{
  // Preconditions:

  // Body:

  components[0] = xvalue;

  // Postconditions:

  // Exit:

  //return result;
}

///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
determinant(T& xresult) const
{
  // Preconditions:

  // Body:

  T a01 = components[0];

  xresult = a01*a01;

  // Postconditions:

  // Exit:

}

///
template <typename T>
T
antisymmetric_matrix_2x2<T>::
determinant() const
{
  // Preconditions:

  // Body:

  T result;

  determinant(result);

  // Postconditions:

  // Exit:

  return result;
}


///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
inverse(antisymmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  const antisymmetric_matrix_2x2<T>& lm = *this;

  //double a00 = 0.0;
  double a01 = lm[0][1];
  //double a10 = -a01;
  //double a11 = 0.0;

  //double determinant = a01*a01;
  //double determinant = a00*a11 - a01*a10;;

  //if(determinant == 0.0)
  if(a01 == 0.0)
  {
    post_fatal_error_message("No inverse; determinant is zero.");
  }

  //xresult[0][0] =  a11/determinant;
  //xresult[0][1] = -a01/determinant;
  //xresult[1][0] = -a10/determinant;
  //xresult[1][1] =  a00/determinant;

  xresult[0][1] = -1.0/a01;

  // Postconditions:

  // Exit:
}

///
template <typename T>
antisymmetric_matrix_2x2<T>
antisymmetric_matrix_2x2<T>::
inverse() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_2x2<T> result;
  inverse(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
antisymmetric_matrix_2x2<T>::
is_positive_definite() const
{
  // Preconditions:

  // Body:

  bool result = false;

  // Postconditions:

  ensure(result == false);

  // Exit:

  return result;
}


///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
multiply(const T& xscalar, antisymmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  xresult.components[0] = xscalar*components[0];

  // Postconditions:

  //@issue $$ISSUE: We can't make the following comparison because of
  //                floating point roundoff.
  //ensure_for_all(i, 0, d(), xresult.components[i] == xscalar*components[i]);

  // Exit:

}

///
template <typename T>
antisymmetric_matrix_2x2<T>
antisymmetric_matrix_2x2<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_2x2<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}
///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
multiply(const general_matrix_2x1<T>& xother,
         general_matrix_2x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_2x2<T>& lm = *this;

  //T a00 = 0.0;
  T a01 = lm[0][1];
  T a10 = -a01;
  //T a11 = 0.0;

  T b00 = xother[0][0];
  T b10 = xother[1][0];

  //   xresult[0][0] = a00*b00 + a01*b10;
  //   xresult[1][0] = a10*b00 + a11*b10;

  xresult[0][0] = a01*b10;
  xresult[1][0] = a10*b00;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x1<T>
antisymmetric_matrix_2x2<T>::
multiply(const general_matrix_2x1<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_2x1<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
multiply(const general_matrix_2x2<T>& xother,
         general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_2x2<T>& lm = *this;

  //T a00 = 0.0;
  T a01 = lm[0][1];
  T a10 = -a01;
  //T a11 = 0.0;

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b10 = xother[1][0];
  T b11 = xother[1][1];

  //   xresult[0][0] = a00*b00 + a01*b10;
  //   xresult[0][1] = a00*b01 + a01*b11;
  //   xresult[1][0] = a10*b00 + a11*b10;
  //   xresult[1][1] = a10*b01 + a11*b11;

  xresult[0][0] = a01*b10;
  xresult[0][1] = a01*b11;

  xresult[1][0] = a10*b00;
  xresult[1][1] = a10*b01;


  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x2<T>
antisymmetric_matrix_2x2<T>::
multiply(const general_matrix_2x2<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
multiply(const general_matrix_2x3<T>& xother,
         general_matrix_2x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_2x2<T>& lm = *this;

  //T a00 = 0.0;
  T a01 = lm[0][1];
  T a10 = -a01;
  //T a11 = 0.0;

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b02 = xother[0][2];

  T b10 = xother[1][0];
  T b11 = xother[1][1];
  T b12 = xother[1][2];

  //   xresult[0][0] = a00*b00 + a01*b10;
  //   xresult[0][1] = a00*b01 + a01*b11;
  //   xresult[0][2] = a00*b02 + a01*b12;

  //   xresult[1][0] = a10*b00 + a11*b10;
  //   xresult[1][1] = a10*b01 + a11*b11;
  //   xresult[1][2] = a10*b02 + a11*b12;

  xresult[0][0] = a01*b10;
  xresult[0][1] = a01*b11;
  xresult[0][2] = a01*b12;

  xresult[1][0] = a10*b00;
  xresult[1][1] = a10*b01;
  xresult[1][2] = a10*b02;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x3<T>
antisymmetric_matrix_2x2<T>::
multiply(const general_matrix_2x3<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_2x3<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
multiply(const antisymmetric_matrix_2x2<T>& xother,
         general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_2x2<T>& lm = *this;

  //T a00 = 0.0;
  T a01 = lm[0][1];
  //T a10 = -a01;
  //T a11 = 0.0;

  //T b00 = 0.0;
  T b01 = xother[0][1];
  //T b10 = -b01;
  //T b11 = 0.0;

  //   xresult[0][0] = a00*b00 + a01*b10;
  //   xresult[0][1] = a00*b01 + a01*b11;
  //   xresult[1][0] = a10*b00 + a11*b10;
  //   xresult[1][1] = a10*b01 + a11*b11;

  // In the 2x2 case the result is a diagonal matrix
  // with identical elements.

  xresult[0][0] = -a01*b01;
  xresult[0][1] = 0.0;
  xresult[1][0] = 0.0;
  xresult[1][1] = xresult[0][0];

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x2<T>
antisymmetric_matrix_2x2<T>::
multiply(const antisymmetric_matrix_2x2<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
antisymmetric_matrix_2x2<T>::
trace(T& xresult) const
{
  // Preconditions:

  // Body:

  xresult = T(0);

  // Postconditions:

  ensure(xresult == 0);

  // Exit:
}

///
template <typename T>
T
antisymmetric_matrix_2x2<T>::
trace() const
{
  // Preconditions:

  // Body:

  T result;

  trace(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
antisymmetric_matrix_2x2<T>::
transpose(antisymmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  //const antisymmetric_matrix_2x2<T>& lm = *this;
  //xresult[0][1] = -lm[0][1];

  xresult[0][1] = -components[0];

  // Postconditions:

  // Exit:

}

///
template <typename T>
antisymmetric_matrix_2x2<T>
antisymmetric_matrix_2x2<T>::
transpose() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_2x2<T> result;
  transpose(result);

  // Postconditions:

  // Exit:

  return result;
}

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

#ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const antisymmetric_matrix_2x2<T>& xm)
{
  // Preconditions:

  // Body:

  // Here we will actually print the elements on and below the diagonal
  // even though we don't store them.

  xos << "  " <<       0.0 << "  " << xm[0][1] << std::endl;
  xos << "  " << -xm[0][1] << "  " <<      0.0 << std::endl;

  // Postconditions:

  // Exit:

  return xos;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

//==============================================================================
//==============================================================================

} // namespace fiber_bundle

#endif // ANTISYMMETRIC_MATRIX_2X2_IMPL_H
 
