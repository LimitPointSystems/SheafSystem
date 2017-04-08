
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

// Implementation for general_matrix_3x3.


#ifndef GENERAL_MATRIX_3X3_IMPL_H
#define GENERAL_MATRIX_3X3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef ANTISYMMETRIC_MATRIX_3X3_H
#include "antisymmetric_matrix_3x3.h"
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
general_matrix_3x3<T>::
operator gl3_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  gl3_row_dofs_type<T>& result =
    reinterpret_cast<gl3_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_3x3<T>::
operator jcb_e33_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  jcb_e33_row_dofs_type<T>& result =
    reinterpret_cast<jcb_e33_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_3x3<T>::
operator t02_e3_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  t02_e3_row_dofs_type<T>& result =
    reinterpret_cast<t02_e3_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
int
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 9;
}

///
template <typename T>
T*
general_matrix_3x3<T>::
operator[](int xrow)
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  T* result = &components[row_index(xrow)];

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

template <typename T>
const T*
general_matrix_3x3<T>::
operator[](int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  const T* result = &components[row_index(xrow)];

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x3<T>
general_matrix_3x3<T>::
row(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  general_matrix_1x3<T> result;

  int lindex = row_index(xrow);
  result.components[0] = components[lindex++];
  result.components[1] = components[lindex++];
  result.components[2] = components[lindex];

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
general_matrix_3x1<T>
general_matrix_3x3<T>::
column(int xcolumn) const
{
  // Preconditions:

  require(xcolumn >= 0 && xcolumn < number_of_columns());

  // Body:

  general_matrix_3x1<T> result;

  int lindex = xcolumn;
  result.components[0] = components[lindex];
  lindex += 3; // += number_of_columns();
  result.components[1] = components[lindex];
  lindex += 3; // += number_of_columns();
  result.components[2] = components[lindex];

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_3x3<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  //cout << "general_matrix_3x3<T>::operator T* () " << std::endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_3x3<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  //cout << "general_matrix_3x3<T>::operator const T* () const " << std::endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
general_matrix_3x3<T>::
row_index(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  //int result = number_of_columns()*xrow;
  int result = 3*xrow;

  // Postconditions:

  ensure(result == number_of_columns()*xrow);

  // Exit:

  return result;
}


///
template <typename T>
void
general_matrix_3x3<T>::
adjoint(general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Get the cofactors.

  const general_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = lm[1][0];
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = lm[2][0];
  T a21 = lm[2][1];
  T a22 = lm[2][2];

  T c00 = a11*a22 - a12*a21;
  T c01 = a12*a20 - a10*a22;
  T c02 = a10*a21 - a11*a20;

  T c10 = a02*a21 - a01*a22;
  T c11 = a00*a22 - a02*a20;
  T c12 = a01*a20 - a00*a21;

  T c20 = a01*a12 - a02*a11;
  T c21 = a02*a10 - a00*a12;
  T c22 = a00*a11 - a01*a10;

  // Adjoint is the transpose of the cofactor matrix.

  xresult[0][0] = c00;
  xresult[0][1] = c10;
  xresult[0][2] = c20;

  xresult[1][0] = c01;
  xresult[1][1] = c11;
  xresult[1][2] = c21;

  xresult[2][0] = c02;
  xresult[2][1] = c12;
  xresult[2][2] = c22;

  // Postconditions:

  // Exit:
}

///
template <typename T>
general_matrix_3x3<T>
general_matrix_3x3<T>::
adjoint() const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  adjoint(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
determinant(T& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = lm[1][0];
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = lm[2][0];
  T a21 = lm[2][1];
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
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
diagonalization(general_matrix_3x3<T>& xresult) const
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

  const general_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = lm[1][0];
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = lm[2][0];
  T a21 = lm[2][1];
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
      // There is 1 real root and 2 complex conjugate roots.

      post_fatal_error_message("Matrix has 2 complex roots.");
    }
    else if(discriminant== 0.0)
    {
      // There are 3 real roots and 2 are equal.

      T powr = (r < 0) ? -pow(-r, 1.0/3.0) : pow(r, 1.0/3.0);
      lambda_0 = (2.0*powr) - b3;
      lambda_1 = (-powr) - b3;
      lambda_2 = lambda_1;
    }
    else
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

    std::sort(&tmp[0], &tmp[3]);
    
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
general_matrix_3x3<T>
general_matrix_3x3<T>::
diagonalization() const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
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
general_matrix_3x3<T>::
identity(general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:
 
  const T one  = T(1);
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
general_matrix_3x3<T>
general_matrix_3x3<T>::
identity() const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  identity(result);

  // Postconditions:

  ensure(result.is_identity());

  // Exit:

  return result;
}


///
template <typename T>
void 
general_matrix_3x3<T>::
inverse(general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = lm[1][0];
  T a11 = lm[1][1];
  T a12 = lm[1][2];
  T a20 = lm[2][0];
  T a21 = lm[2][1];
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
  T c12 = a01*a20 - a00*a21;

  T c20 = a01*a12 - a02*a11;
  T c21 = a02*a10 - a00*a12;
  T c22 = a00*a11 - a01*a10;

  xresult[0][0] = c00/determinant;
  xresult[0][1] = c10/determinant;
  xresult[0][2] = c20/determinant;

  xresult[1][0] = c01/determinant;
  xresult[1][1] = c11/determinant;
  xresult[1][2] = c21/determinant;

  xresult[2][0] = c02/determinant;
  xresult[2][1] = c12/determinant;
  xresult[2][2] = c22/determinant;

  // Postconditions:

  // Exit:
}

///
template <typename T>
general_matrix_3x3<T>
general_matrix_3x3<T>::
inverse() const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  inverse(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
general_matrix_3x3<T>::
is_antisymmetric() const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  bool result = (lm[0][0]==0.0) && (lm[1][1]==0.0) && (lm[2][2]==0.0) &&
                (lm[1][0]==-lm[0][1]) &&
                (lm[2][0]==-lm[0][2]) &&
                (lm[2][1]==-lm[1][2]);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
general_matrix_3x3<T>::
is_diagonal() const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  bool result =
    (lm[0][1]==0.0) && (lm[0][2]==0.0) && (lm[1][0]==0.0) &&
    (lm[1][2]==0.0) && (lm[2][0]==0.0) && (lm[2][1]==0.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
general_matrix_3x3<T>::
is_identity() const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  bool result = is_diagonal() &&
                (lm[0][0]==1.0) && (lm[1][1]==1.0) && (lm[2][2]==1.0);

  // Postconditions:

  // Exit:

  return result;

}


///
template <typename T>
bool
general_matrix_3x3<T>::
is_positive_definite() const
{
  // Preconditions:

  // Body:

  //$ISSUE: Does this test mean anything for the general case?  Maybe.
  //        See http://mathworld.wolfram.com/PositiveDefiniteMatrix.html.

  // Get the symmetric part and test it.

  symmetric_matrix_3x3<T> lsym = symmetric_part();
  bool result = lsym.is_positive_definite();

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
general_matrix_3x3<T>::
is_symmetric() const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  bool result = (lm[1][0]==lm[0][1]) &&
                (lm[2][0]==lm[0][2]) &&
                (lm[2][1]==lm[1][2]);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
void 
general_matrix_3x3<T>::
multiply(const T& xscalar, general_matrix_3x3<T>& xresult) const
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
general_matrix_3x3<T>
general_matrix_3x3<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
general_matrix_3x3<T>::
multiply(const general_matrix_3x3<T>& xother,
         general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_3x3<T>& lm = *this;

  int nra = number_of_rows();
  int nca = number_of_columns();
  int ncb = xother.number_of_columns();

  for(int i=0; i<nra; ++i)
  {
    for(int j=0; j<ncb; ++j)
    {
      T sum = T(0);

      for(int k=0; k<nca; ++k)
      {
        sum += lm[i][k]*xother[k][j];
      }

      xresult[i][j] = sum;
    }
  }

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x3<T>
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
multiply(const general_matrix_3x2<T>& xother,
         general_matrix_3x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_3x3<T>& lm = *this;

  int nra = number_of_rows();
  int nca = number_of_columns();
  int ncb = xother.number_of_columns();

  for(int i=0; i<nra; ++i)
  {
    for(int j=0; j<ncb; ++j)
    {
      T sum = T(0);

      for(int k=0; k<nca; ++k)
      {
        sum += lm[i][k]*xother[k][j];
      }

      xresult[i][j] = sum;
    }
  }

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x2<T>
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
multiply(const general_matrix_3x1<T>& xother,
         general_matrix_3x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_3x3<T>& lm = *this;

  int nra = number_of_rows();
  int nca = number_of_columns();
  int ncb = xother.number_of_columns();

  for(int i=0; i<nra; ++i)
  {
    for(int j=0; j<ncb; ++j)
    {
      T sum = T(0);

      for(int k=0; k<nca; ++k)
      {
        sum += lm[i][k]*xother[k][j];
      }

      xresult[i][j] = sum;
    }
  }

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x1<T>
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
trace(T& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  // Unroll the loop for efficiency.

  xresult = lm[0][0] + lm[1][1] + lm[2][2];

  // Postconditions:

  ensure(xresult == lm[0][0] + lm[1][1] + lm[2][2]);

  // Exit:
}

///
template <typename T>
T
general_matrix_3x3<T>::
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
general_matrix_3x3<T>::
transpose(general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_3x3<T>& lm = *this;

  int nrows = number_of_rows();
  int ncols = number_of_columns();

  for(int i=0; i<nrows; ++i)
  {
    for(int j=0; j<ncols; ++j)
    {
      xresult[i][j] = lm[j][i];
    }
  }

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x3<T>
general_matrix_3x3<T>::
transpose() const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;
  transpose(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
general_matrix_3x3<T>::
antisymmetric_part(antisymmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // A - A(transpose) is the antisymmetric part.

  const general_matrix_3x3<T>& lm = *this;

  int n = number_of_rows();

  for(int i=0; i<n-1; ++i)
  {
    for(int j=i+1; j<n; ++j)
    {
      xresult[i][j] = lm[i][j] - lm[j][i];
    }
  }

  // Postconditions:

  // Exit:
}

///
template <typename T>
antisymmetric_matrix_3x3<T>
general_matrix_3x3<T>::
antisymmetric_part() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_3x3<T> result;
  antisymmetric_part(result);

  // Postconditions:

  // Exit:

  return result;
}


///
template <typename T>
void
general_matrix_3x3<T>::
symmetric_part(symmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // A + A(transpose) is the antisymmetric part.

  const general_matrix_3x3<T>& lm = *this;

  int n = number_of_rows();

  for(int i=0; i<n; ++i)
  {
    for(int j=i; j<n; ++j)
    {
      xresult[i][j] = lm[i][j] + lm[j][i];
    }
  }

  // Postconditions:

  // Exit:
}

///
template <typename T>
symmetric_matrix_3x3<T>
general_matrix_3x3<T>::
symmetric_part() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_3x3<T> result;
  symmetric_part(result);

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
std::ostream& operator<<(std::ostream& xos, const general_matrix_3x3<T>& xm)
{
  // Preconditions:

  // Body:

  int nrows = xm.number_of_rows();
  int ncols = xm.number_of_columns();

  for(int i=0; i<nrows; ++i)
  {
    for(int j=0; j<ncols; ++j)
    {
      xos << "  " << xm[i][j];
    }
    xos << std::endl;
  }

  // Postconditions:

  // Exit:

  return xos;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

//==============================================================================
//==============================================================================

} // namespace fiber_bundle

#endif // GENERAL_MATRIX_3X3_IMPL_H

