
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

// Implementation for symmetric_matrix_2x2.


#ifndef SYMMETRIC_MATRIX_2X2_IMPL_H
#define SYMMETRIC_MATRIX_2X2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
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

#ifndef SYMMETRIC_MATRIX_2X2_H
#include "symmetric_matrix_2x2.h"
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
symmetric_matrix_2x2<T>::
operator met_e2_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  met_e2_row_dofs_type<T>& result =
    reinterpret_cast<met_e2_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
symmetric_matrix_2x2<T>::
operator st2_e2_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  st2_e2_row_dofs_type<T>& result =
    reinterpret_cast<st2_e2_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
int
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 3;
}

///
template <typename T>
T*
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  //cout << "### symmetric_matrix_2x2<T>::operator T* () " << std::endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
symmetric_matrix_2x2<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  //cout << "### symmetric_matrix_2x2<T>::operator const T* () const " << std::endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
symmetric_matrix_2x2<T>::
row_index(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  int nrows = number_of_rows();
  int result = (xrow*(2*nrows-1-xrow))/2;

  //int result = (xrow*(3-xrow))/2;

  // Postconditions:

  ensure(result == (xrow*(2*number_of_rows()-1-xrow))/2);

  // Exit:

  return result;
}

///
template <typename T>
symmetric_matrix_2x2<T>::
operator general_matrix_2x2<T> () const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;

  const symmetric_matrix_2x2<T>& lm = *this;

  result[0][0] = lm[0][0];
  result[0][1] = lm[0][1];
  result[1][0] = lm[0][1];
  result[1][1] = lm[1][1];

  // Postconditions:

  ensure(unexecutable("result == *this"));

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x2<T>
symmetric_matrix_2x2<T>::
row(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  general_matrix_1x2<T> result;

  // Just brute force it for the 3x3 case.

  if(xrow == 0)
  {
    result.components[0] = components[0]; // lm[0][0]
    result.components[1] = components[1]; // lm[0][1]
  }
  else // xrow == 1
  {
    result.components[0] = components[1]; // lm[0][1] 
    result.components[1] = components[2]; // lm[1][1]
  }

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
general_matrix_2x1<T>
symmetric_matrix_2x2<T>::
column(int xcolumn) const
{
  // Preconditions:

  require(xcolumn >= 0 && xcolumn < number_of_columns());

  // Body:

  general_matrix_2x1<T> result;

  if(xcolumn == 0)
  {
    result.components[0] = components[0]; // lm[0][0]
    result.components[1] = components[1]; // lm[0][1]
  }
  else // xcolumn == 1
  {
    result.components[0] = components[1]; // lm[0][1] 
    result.components[1] = components[2]; // lm[1][1]
  }

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
void
symmetric_matrix_2x2<T>::
adjoint(symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  //T a10 = a01;
  T a11 = lm[1][1];

  // Return the transpose of the cofactors.

  xresult[0][0] =  a11;
  xresult[0][1] = -a01;
  //xresult[1][0] = -a10;
  xresult[1][1] =  a00;

  // Postconditions:

  // Exit:
}

///
template <typename T>
symmetric_matrix_2x2<T>
symmetric_matrix_2x2<T>::
adjoint() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
  adjoint(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
symmetric_matrix_2x2<T>::
assign(const T& xvalue)
{
  // Preconditions:

  // Body:

  // Unroll the loop in this case.

  components[0] = xvalue;
  components[1] = xvalue;
  components[2] = xvalue;

  // Postconditions:

  ensure_for_all(i, 0, d(), components[i] == xvalue);

  // Exit:

}

///
template <typename T>
void 
symmetric_matrix_2x2<T>::
determinant(T& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  xresult = a00*a11 - a01*a10;

  // Postconditions:

  // Exit:

}

///
template <typename T>
T
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
diagonalization(symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Calculate the eigenvalues of the matrix.

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  // For a 2x2 matrix just solve the quadratic equation.

  //T a = 1.0;
  T b = -(a00 + a11);
  T c = a00*a11 - a01*a10;

  //T discriminant = b*b - 4.0*a*c;
  //T sqrt_discriminant = sqrt(discriminant);

  //T lambda_0 = (-b-sqrt_discriminant)/(2.0*a);
  //T lambda_1 = (-b+sqrt_discriminant)/(2.0*a);

  T discriminant = b*b - 4.0*c;

  if(discriminant < 0.0)
  {
    post_fatal_error_message("Matrix has 2 complex roots.");
  }

  T sqrt_discriminant = sqrt(discriminant);

  T lambda_0 = 0.5*(-b-sqrt_discriminant);
  T lambda_1 = 0.5*(-b+sqrt_discriminant);

  // Assign the diagonals of the result matrix to the
  // eigenvalues and zero to the rest of the elements.

  // Sort into accending order.

  xresult[0][0] = (lambda_0 < lambda_1) ? lambda_0 : lambda_1;
  xresult[0][1] =  0;
  //xresult[1][0] =  0;
  xresult[1][1] = (lambda_1 < lambda_0) ? lambda_0 : lambda_1;

  // Postconditions:

  ensure(xresult.is_diagonal());
  ensure(unexecutable("for_all i, 0, 2, xresult[i][i] == real number"));

  // Exit:

}

///
template <typename T>
symmetric_matrix_2x2<T>
symmetric_matrix_2x2<T>::
diagonalization() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
  diagonalization(result);

  // Postconditions:

  ensure(result.is_diagonal());
  ensure(unexecutable("for_all i, 0, 2, result[i][i] == real number"));

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_2x2<T>::
identity(symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:
 
  const T one = T(1);
  const T zero = T(0);

  xresult[0][0] =  one;
  xresult[0][1] =  zero;
  xresult[1][1] =  one;

  // Postconditions:

  ensure(xresult.is_identity());

  // Exit:
}

///
template <typename T>
symmetric_matrix_2x2<T>
symmetric_matrix_2x2<T>::
identity() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
  identity(result);

  // Postconditions:

  ensure(result.is_identity());

  // Exit:

  return result;
}


///
template <typename T>
void 
symmetric_matrix_2x2<T>::
inverse(symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  // Get the determinant.

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  T determinant = a00*a11 - a01*a10;

  if(determinant == 0.0)
  {
    post_fatal_error_message("No inverse; determinant is zero.");
  }

  xresult[0][0] =  a11/determinant;
  xresult[0][1] = -a01/determinant;
  xresult[1][0] = -a10/determinant;
  xresult[1][1] =  a00/determinant;

  // Postconditions:

  // Exit:
}

///
template <typename T>
symmetric_matrix_2x2<T>
symmetric_matrix_2x2<T>::
inverse() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
  inverse(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
symmetric_matrix_2x2<T>::
is_diagonal() const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  bool result = (lm[0][1]==0.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
symmetric_matrix_2x2<T>::
is_identity() const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  bool result = is_diagonal() && (lm[0][0]==1.0) && (lm[1][1]==1.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
symmetric_matrix_2x2<T>::
is_positive_definite() const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  // For a 2x2 symmetric matrix (n even), the test for positive definiteness
  // is simple (the diagonal terms and the determinant must be positive).

  T a00 = lm[0][0];
  T a11 = lm[1][1];
  T ldet = determinant();

  bool result = (a00 > 0) && (a11 > 0) && (ldet > 0);

  // Postconditions:

  // Exit:

  return result;
}


///
template <typename T>
void 
symmetric_matrix_2x2<T>::
multiply(const T& xscalar, symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Unroll the loop in this case.

  xresult.components[0] = xscalar*components[0];
  xresult.components[1] = xscalar*components[1];
  xresult.components[2] = xscalar*components[2];

  // Postconditions:

  //@issue $$ISSUE: We can't make the following comparison because of
  //                floating point roundoff.
  //ensure_for_all(i, 0, d(), xresult.components[i] == xscalar*components[i]);

  // Exit:

}

///
template <typename T>
symmetric_matrix_2x2<T>
symmetric_matrix_2x2<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}


///
template <typename T>
void 
symmetric_matrix_2x2<T>::
multiply(const general_matrix_2x1<T>& xother,
         general_matrix_2x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  T b00 = xother[0][0];
  T b10 = xother[1][0];

  xresult[0][0] = a00*b00 + a01*b10;
  xresult[1][0] = a10*b00 + a11*b10;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x1<T>
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
multiply(const symmetric_matrix_2x2<T>& xother,
         general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b10 = b01;
  T b11 = xother[1][1];

  xresult[0][0] = a00*b00 + a01*b10;
  xresult[0][1] = a00*b01 + a01*b11;
  xresult[1][0] = a10*b00 + a11*b10;
  xresult[1][1] = a10*b01 + a11*b11;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x2<T>
symmetric_matrix_2x2<T>::
multiply(const symmetric_matrix_2x2<T>& xother) const
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
symmetric_matrix_2x2<T>::
multiply(const general_matrix_2x2<T>& xother,
         general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b10 = xother[1][0];
  T b11 = xother[1][1];

  xresult[0][0] = a00*b00 + a01*b10;
  xresult[0][1] = a00*b01 + a01*b11;
  xresult[1][0] = a10*b00 + a11*b10;
  xresult[1][1] = a10*b01 + a11*b11;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x2<T>
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
multiply(const general_matrix_2x3<T>& xother,
         general_matrix_2x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = a01;
  T a11 = lm[1][1];

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b02 = xother[0][2];

  T b10 = xother[1][0];
  T b11 = xother[1][1];
  T b12 = xother[1][2];

  xresult[0][0] = a00*b00 + a01*b10;
  xresult[0][1] = a00*b01 + a01*b11;
  xresult[0][2] = a00*b02 + a01*b12;

  xresult[1][0] = a10*b00 + a11*b10;
  xresult[1][1] = a10*b01 + a11*b11;
  xresult[1][2] = a10*b02 + a11*b12;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x3<T>
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
trace(T& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_2x2<T>& lm = *this;

  // Unroll the loop for efficiency.

  xresult = lm[0][0] + lm[1][1];

  // Postconditions:

  // Exit:
}

///
template <typename T>
T
symmetric_matrix_2x2<T>::
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
symmetric_matrix_2x2<T>::
transpose(symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // The transpose of a symmetric matrix is the same as the
  // original matrix. But, we'll return it if you really want
  // it.

  //const symmetric_matrix_2x2<T>& lm = *this;

  //xresult[0][0] = lm[0][0];
  //xresult[0][1] = lm[0][1];
  //xresult[1][1] = lm[1][1];

  int ld = d();

  for(int i=0; i<ld; ++i)
  {
      xresult.components[i] = components[i];
  }

  // Postconditions:

  // Exit:

}

///
template <typename T>
symmetric_matrix_2x2<T>
symmetric_matrix_2x2<T>::
transpose() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
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
std::ostream& operator<<(std::ostream& xos, const symmetric_matrix_2x2<T>& xm)
{
  // Preconditions:

  // Body:

  // Here we will actually print the elements below the diagonal
  // even though we don't store them.

  xos << "  " << xm[0][0] << "  " << xm[0][1] << std::endl;
  xos << "  " << xm[0][1] << "  " << xm[1][1] << std::endl;

  // Postconditions:

  // Exit:

  return xos;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

//==============================================================================
//==============================================================================

} // namespace fiber_bundle

#endif // SYMMETRIC_MATRIX_2X2_IMPL_H

