
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

// Implementation for symmetric_matrix_3x3.


#ifndef SYMMETRIC_MATRIX_3X3_IMPL_H
#define SYMMETRIC_MATRIX_3X3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef GENERAL_MATRIX_1x3_H
#include "general_matrix_1x3.h"
#endif

#ifndef GENERAL_MATRIX_3X1_H
#include "general_matrix_3x1.h"
#endif

#ifndef GENERAL_MATRIX_3X2_H
#include "general_matrix_3x2.h"
#endif

#ifndef GENERAL_MATRIX_3X3_H
#include "general_matrix_3x3.h"
#endif

#ifndef SYMMETRIC_MATRIX_3X3_H
#include "symmetric_matrix_3x3.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

#ifndef STD_ALGORITHM_H
#include "std_algorithm.h"
#endif


namespace fiber_bundle
{

using namespace sheaf;

//==============================================================================
// MEMBER FUNCTIONS
//==============================================================================

///
template <typename T>
symmetric_matrix_3x3<T>::
operator met_e3_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  met_e3_row_dofs_type<T>& result =
    reinterpret_cast<met_e3_row_dofs_type<T>&>(*lcomps);


  return result;
}


///
template <typename T>
symmetric_matrix_3x3<T>::
operator st2_e3_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  st2_e3_row_dofs_type<T>& result =
    reinterpret_cast<st2_e3_row_dofs_type<T>&>(*lcomps);


  return result;
}

///
template <typename T>
int
symmetric_matrix_3x3<T>::
number_of_rows()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 3;
}

///
template <typename T>
int
symmetric_matrix_3x3<T>::
number_of_columns()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 3;
}

///
template <typename T>
int
symmetric_matrix_3x3<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 6;
}

///
template <typename T>
T*
symmetric_matrix_3x3<T>::
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
symmetric_matrix_3x3<T>::
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
symmetric_matrix_3x3<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  //cout << "symmetric_matrix_3x3<T>::operator T* () " << std::endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
symmetric_matrix_3x3<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  //cout << "symmetric_matrix_3x3<T>::operator const T* () const " << std::endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
symmetric_matrix_3x3<T>::
row_index(int xrow) const
{

  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  int nrows = number_of_rows();
  int result = (xrow*(2*nrows-1-xrow))/2;

  //int result = (xrow*(5-xrow))/2;

  // Postconditions:

  ensure(result == (xrow*(2*number_of_rows()-1-xrow))/2);

  // Exit:

  return result;
}

///
template <typename T>
symmetric_matrix_3x3<T>::
operator general_matrix_3x3<T> () const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;

  const symmetric_matrix_3x3<T>& lm = *this;

  result[0][0] = lm[0][0];
  result[0][1] = lm[0][1];
  result[0][2] = lm[0][2];

  result[1][0] = lm[0][1];
  result[1][1] = lm[1][1];
  result[1][2] = lm[1][2];

  result[2][0] = lm[0][2];
  result[2][1] = lm[1][2];
  result[2][2] = lm[2][2];

  // Postconditions:

  ensure(unexecutable("result == *this"));

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x3<T>
symmetric_matrix_3x3<T>::
row(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  general_matrix_1x3<T> result;

  // Just brute force it for the 3x3 case.

  if(xrow == 0)
  {
    result.components[0] = components[0]; // lm[0][0];
    result.components[1] = components[1]; // lm[0][1];
    result.components[2] = components[2]; // lm[0][2];
  }
  else if(xrow == 1)
  {
    result.components[0] = components[1]; // lm[0][1];
    result.components[1] = components[3]; // lm[1][1];
    result.components[2] = components[4]; // lm[1][2];
  }
  else // xrow == 2
  {
    result.components[0] = components[2]; // lm[0][2];
    result.components[1] = components[4]; // lm[1][2];
    result.components[2] = components[5]; // lm[2][2];
  }

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
general_matrix_3x1<T>
symmetric_matrix_3x3<T>::
column(int xcolumn) const
{
  // Preconditions:

  require(xcolumn >= 0 && xcolumn < number_of_columns());

  // Body:

  general_matrix_3x1<T> result;

  // Just brute force it for the 3x3 case.

  if(xcolumn == 0)
  {
    result.components[0] = components[0]; // lm[0][0];
    result.components[1] = components[1]; // lm[1][0];
    result.components[2] = components[2]; // lm[2][0];
  }
  else if(xcolumn == 1)
  {
    result.components[0] = components[1]; // lm[0][1];
    result.components[1] = components[3]; // lm[1][1];
    result.components[2] = components[4]; // lm[2][1];
  }
  else // xcolumn == 2
  {
    result.components[0] = components[2]; // lm[0][2];
    result.components[1] = components[4]; // lm[1][2];
    result.components[2] = components[5]; // lm[2][2];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
symmetric_matrix_3x3<T>::
adjoint(symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Get the cofactors.

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T c00 = a11*a22 - a12*a21;
  //T c01 = a12*a20 - a10*a22;
  //T c02 = a10*a21 - a11*a20;

  T c10 = a02*a21 - a01*a22;
  T c11 = a00*a22 - a02*a20;
  //T c12 = a01*a20 - a00*a21;

  T c20 = a01*a12 - a02*a11;
  T c21 = a02*a10 - a00*a12;
  T c22 = a00*a11 - a01*a10;

  // The adjoint matrix is the transpose of the cofactor matrix.

  xresult[0][0] = c00;
  xresult[0][1] = c10;
  xresult[0][2] = c20;

  //xresult[1][0] = c01;
  xresult[1][1] = c11;
  xresult[1][2] = c21;

  //xresult[2][0] = c02;
  //xresult[2][1] = c12;
  xresult[2][2] = c22;


  // Postconditions:

  // Exit:
}

///
template <typename T>
symmetric_matrix_3x3<T>
symmetric_matrix_3x3<T>::
adjoint() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
  adjoint(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
symmetric_matrix_3x3<T>::
assign(const T& xvalue)
{
  // Preconditions:

  // Body:

  for(int i=0; i<d(); ++i)
  {
    components[i] = xvalue;
  }

  // Postconditions:

  ensure_for_all(i, 0, d(), components[i] == xvalue);

  // Exit:

}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
determinant(T& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T c00 = a11*a22 - a12*a21;
  T c01 = a12*a20 - a10*a22;
  T c02 = a10*a21 - a11*a20;

  xresult = a00*c00 + a01*c01 + a02*c02;

  // Postconditions:

  // Exit:

}

///
template <typename T>
T
symmetric_matrix_3x3<T>::
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
symmetric_matrix_3x3<T>::
diagonalization(symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Calculate the eigenvalues of the matrix.

  // For 3x3 matrices the eigenvalues can be determined
  // by solving a cubic equation, ie;
  //    a*x*x*x = b*x*x +c*x +d = 0.

  //@todo $$TODO: We need a templated cubic equation solver function.
  //              For example:
  //                 template <typename T> cubic_solver(T a, T b, T c, T d,
  //                                                    T result[3]);

  T lambda_0;
  T lambda_1;
  T lambda_2;

  const T zero = T(0);

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T d = -determinant();
  T c = a00*(a11 + a22) + a11*a22 - a01*a10 - a02*a20 - a12*a21;
  T b = -(a00 + a11 + a22);
  T a = 1.0;

  // If the determanant (-d) == 0.0, one eigenvalue is 0 and we can factor
  // to get a quadratic to solve (a*x*x = b*x +c = 0).

  if(d == 0)
  {
    T discriminant = b*b - 4.0*c;

    if(discriminant < 0.0)
    {
      post_fatal_error_message("Matrix has 2 complex roots.");
    }

    T sqrt_discriminant = sqrt(discriminant);

    lambda_0 = zero;
    lambda_1 = 0.5*(-b+sqrt_discriminant);;
    lambda_2 = 0.5*(-b-sqrt_discriminant);
  }
  else
  {
    T q = (3.0*c - b*b)/9.0;
    T r = (b*(9.0*c - 2.0*b*b) - 27.0*d) / 54.0;

    T discriminant = q*q*q + r*r;
    T b3 = b/3.0;

    if(discriminant > 0.0)
    {
      // There is one real root and 2 complex conjugate roots.

      post_fatal_error_message("Matrix has 2 complex roots.");
    }
    else if(discriminant == 0.0)
    {
      // There are 3 real roots and 2 are equal.

      T powr = (r < 0) ? -pow(-r, 1.0/3.0) : pow(r, 1.0/3.0);
      lambda_0 = (2.0*powr) - b3;
      lambda_1 = (-powr) - b3;
      lambda_2 = lambda_1;
    }
    else // discriminant < 0.0
    {
      // There are 3 real unequal roots.

     // Need pi but M_PI is not part of the standard; so compute it.

      static const T L_PI = acos(T(-1.0));
      q = -q;
      T t1 = acos(r/sqrt(q*q*q));
      T t2 = 2.0*sqrt(q);

      lambda_0 = t2*cos(t1/3.0) - b3;
      lambda_1 = t2*cos((t1 + 2.0*L_PI)/3.0) - b3;
      lambda_2 = t2*cos((t1 + 4.0*L_PI)/3.0) - b3;
    }

    // Assign the diagonals of the result matrix to the
    // eigenvalues and zero to the rest of the elements.

    xresult.assign(zero);

    // Sort into accending order.

    T tmp[3] = {lambda_0, lambda_1, lambda_2};

    sort(&tmp[0], &tmp[3]);
    
    xresult[0][0] =  tmp[0];
    xresult[1][1] =  tmp[1];
    xresult[2][2] =  tmp[2];
  }

  // Postconditions:

  ensure(xresult.is_diagonal());
  ensure(unexecutable("for_all i, 0, 2, xresult[i][i] == real number"));

  // Exit:

}

///
template <typename T>
symmetric_matrix_3x3<T>
symmetric_matrix_3x3<T>::
diagonalization() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
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
symmetric_matrix_3x3<T>::
identity(symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:
 
  const T one = T(1);
  const T zero = T(0);

  xresult.assign(zero);

  xresult[0][0] =  one;
  xresult[1][1] =  one;
  xresult[2][2] =  one;

  // Postconditions:

  ensure(xresult.is_identity());

  // Exit:
}

///
template <typename T>
symmetric_matrix_3x3<T>
symmetric_matrix_3x3<T>::
identity() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
  identity(result);

  // Postconditions:

  ensure(result.is_identity());

  // Exit:

  return result;
}


///
template <typename T>
void 
symmetric_matrix_3x3<T>::
inverse(symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  // Cofactors:

  T c00 = a11*a22 - a12*a21;
  T c01 = a12*a20 - a10*a22;
  T c02 = a10*a21 - a11*a20;

  T determinant = a00*c00 + a01*c01 + a02*c02;

  if(determinant == 0.0)
  {
    post_fatal_error_message("No inverse; determinant is zero.");
  }

  T c10 = a02*a21 - a01*a22;
  T c11 = a00*a22 - a02*a20;
  //T c12 = a01*a20 - a00*a21;

  T c20 = a01*a12 - a02*a11;
  T c21 = a02*a10 - a00*a12;
  T c22 = a00*a11 - a01*a10;

  xresult[0][0] = c00/determinant;
  xresult[0][1] = c10/determinant;
  xresult[0][2] = c20/determinant;

  //xresult[1][0] = c01/determinant;
  xresult[1][1] = c11/determinant;
  xresult[1][2] = c21/determinant;

  //xresult[2][0] = c02/determinant;
  //xresult[2][1] = c12/determinant;
  xresult[2][2] = c22/determinant;

  // Postconditions:

  // Exit:
}

///
template <typename T>
symmetric_matrix_3x3<T>
symmetric_matrix_3x3<T>::
inverse() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
  inverse(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
symmetric_matrix_3x3<T>::
is_diagonal() const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_3x3<T>& lm = *this;

  bool result = (lm[0][1]==0.0) && (lm[0][2]==0.0) && (lm[1][2]==0.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
symmetric_matrix_3x3<T>::
is_identity() const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_3x3<T>& lm = *this;

  bool result = is_diagonal() &&
                (lm[0][0]==1.0) && (lm[1][1]==1.0) && (lm[2][2]==1.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
symmetric_matrix_3x3<T>::
is_positive_definite() const
{
  // Preconditions:

  // Body:

  ///@issue This is NOT the most efficient way to do this.
  ///         But it gets the job done.
  ///@todo Optimize this function.

  // Since the eigenvalues must all be positive.
  // So, create the diagonalization and compare all of
  // to eigenvalues (diagonals) to zero.

  symmetric_matrix_3x3<T> ldiag = diagonalization();

  bool result = true;
  for(int i=0; i<number_of_rows(); ++i)
  {
    if(ldiag[i][i] <= 0)
    {
      result = false;
      break;
    }
  }
  
  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
multiply(const T& xscalar, symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  for(int i=0; i<d(); ++i)
  {
      xresult.components[i] = xscalar*components[i];
  }

  // Postconditions:

  //@issue $$ISSUE: We can't make the following comparison because of
  //                floating point roundoff.
  //ensure_for_all(i, 0, d(), xresult.components[i] == xscalar*components[i]);

  // Exit:

}

///
template <typename T>
symmetric_matrix_3x3<T>
symmetric_matrix_3x3<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
multiply(const general_matrix_3x1<T>& xother,
         general_matrix_3x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T b00 = xother[0][0];
  T b10 = xother[1][0];
  T b20 = xother[2][0];

  xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  xresult[2][0] = a20*b00 + a21*b10 + a22*b20;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x1<T>
symmetric_matrix_3x3<T>::
multiply(const general_matrix_3x1<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_3x1<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
multiply(const general_matrix_3x2<T>& xother,
         general_matrix_3x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T b00 = xother[0][0];
  T b01 = xother[0][1];

  T b10 = xother[1][0];
  T b11 = xother[1][1];

  T b20 = xother[2][0];
  T b21 = xother[1][1];

  xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  xresult[0][1] = a00*b01 + a01*b11 + a02*b21;

  xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  xresult[1][1] = a10*b01 + a11*b11 + a12*b21;

  xresult[2][0] = a20*b00 + a21*b10 + a22*b20;
  xresult[2][1] = a20*b01 + a21*b11 + a22*b21;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x2<T>
symmetric_matrix_3x3<T>::
multiply(const general_matrix_3x2<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_3x2<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
multiply(const general_matrix_3x3<T>& xother,
         general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b02 = xother[0][2];

  T b10 = xother[1][0];
  T b11 = xother[1][1];
  T b12 = xother[1][2];

  T b20 = xother[2][0];
  T b21 = xother[2][1];
  T b22 = xother[2][2];

  xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  xresult[0][1] = a00*b01 + a01*b11 + a02*b21;
  xresult[0][2] = a00*b02 + a01*b12 + a02*b22;

  xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  xresult[1][1] = a10*b01 + a11*b11 + a12*b21;
  xresult[1][2] = a10*b02 + a11*b12 + a12*b22;

  xresult[2][0] = a20*b00 + a21*b10 + a22*b20;
  xresult[2][1] = a20*b01 + a21*b11 + a22*b21;
  xresult[2][2] = a20*b02 + a21*b12 + a22*b22;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x3<T>
symmetric_matrix_3x3<T>::
multiply(const general_matrix_3x3<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
multiply(const symmetric_matrix_3x3<T>& xother,
         general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const symmetric_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = a01;
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = a02;
  T a21 = a12;
  T a22 = lm[2][2];

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b02 = xother[0][2];
  T b10 = b01;
  T b11 = xother[1][1];
  T b12 = xother[1][2];
  T b20 = b02;
  T b21 = b12;
  T b22 = xother[2][2];

  xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  xresult[0][1] = a00*b01 + a01*b11 + a02*b21;
  xresult[0][2] = a00*b02 + a01*b12 + a02*b22;

  xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  xresult[1][1] = a10*b01 + a11*b11 + a12*b21;
  xresult[1][2] = a10*b02 + a11*b12 + a12*b22;

  xresult[2][0] = a20*b00 + a21*b10 + a22*b20;
  xresult[2][1] = a20*b01 + a21*b11 + a22*b21;
  xresult[2][2] = a20*b02 + a21*b12 + a22*b22;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x3<T>
symmetric_matrix_3x3<T>::
multiply(const symmetric_matrix_3x3<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
symmetric_matrix_3x3<T>::
trace(T& xresult) const
{
  // Preconditions:

  // Body:

  const symmetric_matrix_3x3<T>& lm = *this;

  // Unroll the loop for efficiency.

  xresult = lm[0][0] + lm[1][1] + lm[2][2];

  // Postconditions:

  // Exit:
}

///
template <typename T>
T
symmetric_matrix_3x3<T>::
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
symmetric_matrix_3x3<T>::
transpose(symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // The transpose of a symmetric matrix is the same as the
  // original matrix. But, we'll return it if you really want
  // it.

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
symmetric_matrix_3x3<T>
symmetric_matrix_3x3<T>::
transpose() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
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
std::ostream& operator<<(std::ostream& xos, const symmetric_matrix_3x3<T>& xm)
{
  // Preconditions:

  // Body:

  // Here we will actually print the below the diagonal
  // even though we don't store them.

  int nrows = xm.number_of_rows();
  int ncols = xm.number_of_columns();

  for(int i=0; i<nrows; ++i)
  {
    for(int j=0; j<ncols; ++j)
    {
      double v;
      if(i <= j)
        v = xm[i][j];
      else
        v = xm[j][i];
   
      xos << "  " << v;
    }
    xos << std::endl;
  }

  // Postconditions:

  // Exit:

  return xos;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

///
template <typename T>
void
jacobi_transformation(const symmetric_matrix_3x3<T>& xm,
                      general_matrix_3x3<T>& xeigenvectors,
                      symmetric_matrix_3x3<T>& xdiagonal)
{
  //$$TODO: Provide a better explanation.

  // Determine the eigenvalues and eigenvectors of a real 3x3 symmetric matrix.
  // Uses the cyclic Jacobi method.
 
  // Preconditions:

  // Body:

  T eigenvalues[3];
  jacobi_transformation(xm, xeigenvectors, eigenvalues);

  for(int i=0; i<3; ++i)
  {
    xdiagonal[i][i] = eigenvalues[i]; 
  } 

  // Postconditions:

  // Body:

}

///
template <typename T>
void
jacobi_transformation(const symmetric_matrix_3x3<T>& xm,
                      general_matrix_3x3<T>& xeigenvectors,
                      T xeigenvalues[3])
{
  //$$TODO: Provide a better explanation.

  // Determine the eigenvalues and eigenvectors of a real 3x3 symmetric matrix.
  // Uses the cyclic Jacobi method.  This code is basically a templatized version
  // of the code in "Numerical Recipes, 11.1".
 
  // Preconditions:

  // Body:

  static const int n = 3;

  static const int max_iterations = 50;
  static const T zero = 0.0;

  // Copy the original symmetric matrix into a second matrix
  // to be used for working storage.

  symmetric_matrix_3x3<T> lm = xm;

  //cout << "lm:" << std::endl << lm << std::endl;

  //int number_of_rotations = 0;

  // Initialize xeigenvectors to the identity matrix.

  xeigenvectors = xeigenvectors.identity();

  //cout << "xeigenvectors:" << std::endl << xeigenvectors << std::endl;

  // Initialize b and xeigenvalues to the diagonal of lm;

  T b[3];
  T z[3];
  for(int i=0; i<n; ++i)
  {
    T lmii = lm[i][i];
    xeigenvalues[i] = lmii;
    b[i]  = lmii;
    z[i]  = 0.0;
  }

  int i;
  for(i=0; i<max_iterations; ++i)
  {
    // Sum the off diagonals.

    T sum = fabs(lm[0][1]) + fabs(lm[0][2]) + fabs(lm[1][2]);

    //cout << "number_of_rotations = " << number_of_rotations;
    //cout << "  sum = " << sum << std::endl;

    // Test for convergence.

    if(sum == zero)
    {
      // The iteration has converged; so break out of the loop;

      break;
    }

    T tresh = (i>=3) ? 0.0 : (0.2*sum/(n*n));

    for(int ip=0; ip<n-1; ++ip)
    {
      for(int iq=ip+1; iq<n; ++iq)
      {
        T g = 100.0*fabs(lm[ip][iq]);

        // After 4 sweeps, skip the rotation if the off-diagonal element is small.

        if(i > 3
           && (fabs(xeigenvalues[ip])+g) == fabs(xeigenvalues[ip])
           && (fabs(xeigenvalues[iq])+g) == fabs(xeigenvalues[iq]))
        {
          lm[ip][iq] = 0.0;
        }
        else if(fabs(lm[ip][iq]) > tresh)
        {
          T t;
          T h = xeigenvalues[iq] - xeigenvalues[ip];
          if((fabs(h)+g) == fabs(h))
          {
            t = lm[ip][iq]/h;
          }
          else
          {
            T theta = 0.5*h/(lm[ip][iq]);
            t = 1.0/(fabs(theta) + sqrt(1.0+theta*theta));
            if(theta < 0.0) t = -t;
          }

          T cos = 1.0/sqrt(1.0 + t*t);
          T sin = t*cos;
          T tau = sin/(1.0 + cos);
          h = t*lm[ip][iq];

          z[ip] -= h;
          z[iq] += h;
          xeigenvalues[ip] -= h;
          xeigenvalues[iq] += h;

          lm[ip][iq] = 0.0;

          for(int j=0; j<ip; ++j)
          {
            g = lm[j][ip];
            h = lm[j][iq];
            lm[j][ip] = g - (sin * (h + (g * tau)));
            lm[j][iq] = h + (sin * (g - (h * tau)));
          }

          for(int j=ip+1; j<iq; ++j)
          {
            g = lm[ip][j];
            h = lm[j][iq];
            lm[ip][j] = g - (sin * (h + (g * tau)));
            lm[j][iq] = h + (sin * (g - (h * tau)));
          }

          for(int j=iq+1; j<n; ++j)
          {
            g = lm[ip][j];
            h = lm[iq][j];
            lm[ip][j] = g - (sin * (h + (g * tau)));
            lm[iq][j] = h + (sin * (g - (h * tau)));
           }

          for(int j=0; j<n; ++j)
          {
            g = xeigenvectors[j][ip];
            h = xeigenvectors[j][iq];
            xeigenvectors[j][ip] = g - (sin * (h + (g * tau)));
            xeigenvectors[j][iq] = h + (sin * (g - (h * tau)));
          }

          //++number_of_rotations;  
        }
      }
    }

    // Update the eigenvalues and reinitialize z.

    for(int ip=0; ip<3; ++ip)
    {
      b[ip] += z[ip];
      xeigenvalues[ip] = b[ip];
      z[ip] = 0.0;
    }

  }

  if(i >= max_iterations)
  {
    post_fatal_error_message("Too many Jacobi iterations");
  }

  // Sort in ascending value of eigenvalues.

  sort_eigenvalues(xeigenvectors, xeigenvalues);

  //$$TODO: Transpose so eigenvectors are the rows?.

  // Postconditions:

  // Exit:



}

///
template <typename T>
void
sort_eigenvalues(general_matrix_3x3<T>& xeigenvectors,
                 T xeigenvalues[3])
{
  // Sort the eigenvalues and eigenvectors into ascending order.
  // At this point the eigenvectors are stored by columns.

  // Preconditions:

  // Body;

  static const int n = 3;

  for(int i=0; i<n; ++i)
  {
    T ev_min = xeigenvalues[i];
    int k = i;

    int j;
    for(j=i+1; j<n; ++j)
    {
      if(ev_min > xeigenvalues[j])
      {
        ev_min = xeigenvalues[j];
        k = j;
      }
    }

    if(k != j)
    {
      // Swap the eigenvalues.

      xeigenvalues[k] = xeigenvalues[i];
      xeigenvalues[i] = ev_min;

      // Swap the eigenvectors.

      for(int j=0; j<n; ++j)
      {
        T temp = xeigenvectors[j][i];
        xeigenvectors[j][i] = xeigenvectors[j][k];
        xeigenvectors[j][k] = temp;
      }
    }
  } 

  // Postconditions:

  // Exit:

}

//==============================================================================
//==============================================================================

} // namespace fiber_bundle

#endif // SYMMETRIC_MATRIX_3X3_IMPL_H

