
// $RCSfile: general_matrix_2x2.impl.h,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:17:09 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for general_matrix_2x2.


#ifndef GENERAL_MATRIX_2X2_IMPL_H
#define GENERAL_MATRIX_2X2_IMPL_H

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

#ifndef SYMMETRIC_MATRIX_2X2_H
#include "symmetric_matrix_2x2.h"
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
general_matrix_2x2<T>::
operator gl2_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  gl2_row_dofs_type<T>& result =
    reinterpret_cast<gl2_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_2x2<T>::
operator t02_e2_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  t02_e2_row_dofs_type<T>& result =
    reinterpret_cast<t02_e2_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_2x2<T>::
operator t11_e2_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  t11_e2_row_dofs_type<T>& result =
    reinterpret_cast<t11_e2_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}


///
template <typename T>
int
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 4;
}

///
template <typename T>
T*
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  cout << "general_matrix_2x2<T>::operator T* () " << endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_2x2<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  cout << "general_matrix_2x2<T>::operator const T* () const " << endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
general_matrix_2x2<T>::
row_index(int xrow) const
{

  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  int result = number_of_columns()*xrow;

  // Postconditions:

  ensure(result == number_of_columns()*xrow);

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x2<T>
general_matrix_2x2<T>::
row(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  general_matrix_1x2<T> result;

  int lindex = row_index(xrow);
  result.components[0] = components[lindex++];
  result.components[1] = components[lindex];

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
general_matrix_2x1<T>
general_matrix_2x2<T>::
column(int xcolumn) const
{
  // Preconditions:

  require(xcolumn >= 0 && xcolumn < number_of_columns());

  // Body:

  general_matrix_2x1<T> result;

  int lindex = xcolumn;
  result.components[0] = components[lindex];
  lindex += 2; // += number_of_columns();
  result.components[1] = components[lindex];

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
general_matrix_2x2<T>
general_matrix_2x2<T>::
adjoint() const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  adjoint(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
determinant(T& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = lm[1][0];
  T a11 = lm[1][1];

  xresult = a00*a11 - a01*a10;

  // Postconditions:

  // Exit:

}

///
template <typename T>
T
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
diagonalization(general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Calculate the eigenvalues of the matrix.

  const general_matrix_2x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = lm[1][0];
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
  xresult[1][0] =  0;
  xresult[1][1] = (lambda_1 < lambda_0) ? lambda_0 : lambda_1;

  // Postconditions:

  ensure(xresult.is_diagonal());
  ensure(unexecutable("for_all i, 0, 2, xresult[i][i] == real number"));

  // Exit:

}

///
template <typename T>
general_matrix_2x2<T>
general_matrix_2x2<T>::
diagonalization() const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
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
general_matrix_2x2<T>::
identity(general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:
 
  const T one = T(1);
  const T zero = T(0);

  xresult[0][0] =  one;
  xresult[0][1] =  zero;
  xresult[1][0] =  zero;
  xresult[1][1] =  one;

  // Postconditions:

  ensure(xresult.is_identity());

  // Exit:
}

///
template <typename T>
general_matrix_2x2<T>
general_matrix_2x2<T>::
identity() const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  identity(result);

  // Postconditions:

  ensure(result.is_identity());

  // Exit:

  return result;
}


///
template <typename T>
void 
general_matrix_2x2<T>::
inverse(general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  // Get the determinant.

  T a00 = lm[0][0];
  T a01 = lm[0][1];
  T a10 = lm[1][0];
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
general_matrix_2x2<T>
general_matrix_2x2<T>::
inverse() const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  inverse(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
general_matrix_2x2<T>::
is_antisymmetric() const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  bool result = (lm[0][0]==0.0) && (lm[1][1]==0.0) && (lm[1][0]==-lm[0][1]);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
general_matrix_2x2<T>::
is_diagonal() const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  bool result = (lm[0][1]==0.0) && (lm[1][0]==0.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
general_matrix_2x2<T>::
is_identity() const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  bool result = is_diagonal() && (lm[0][0]==1.0) && (lm[1][1]==1.0);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
bool
general_matrix_2x2<T>::
is_positive_definite() const
{
  // Preconditions:

  // Body:

  //$ISSUE: Does this test mean anything for the general case?  Maybe.
  //        See http://mathworld.wolfram.com/PositiveDefiniteMatrix.html.

  // Get the symmetric part and test it.

  symmetric_matrix_2x2<T> lsym = symmetric_part();
  bool result = lsym.is_positive_definite();

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
general_matrix_2x2<T>::
is_symmetric() const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  bool result = (lm[1][0]==lm[0][1]);

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
void 
general_matrix_2x2<T>::
multiply(const T& xscalar, general_matrix_2x2<T>& xresult) const
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
general_matrix_2x2<T>
general_matrix_2x2<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
general_matrix_2x2<T>::
multiply(const general_matrix_2x1<T>& xother,
         general_matrix_2x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_2x2<T>& lm = *this;

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
general_matrix_2x1<T>
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
multiply(const general_matrix_2x2<T>& xother,
         general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_2x2<T>& lm = *this;

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
general_matrix_2x2<T>
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
multiply(const general_matrix_2x3<T>& xother,
         general_matrix_2x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_2x2<T>& lm = *this;

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
general_matrix_2x3<T>
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
trace(T& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  // Unroll the loop for efficiency.

  xresult = lm[0][0] + lm[1][1];

  // Postconditions:

  // Exit:
}

///
template <typename T>
T
general_matrix_2x2<T>::
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
general_matrix_2x2<T>::
transpose(general_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_2x2<T>& lm = *this;

  xresult[0][0] = lm[0][0];
  xresult[0][1] = lm[1][0];
  xresult[1][0] = lm[0][1];
  xresult[1][1] = lm[1][1];

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x2<T>
general_matrix_2x2<T>::
transpose() const
{
  // Preconditions:

  // Body:

  general_matrix_2x2<T> result;
  transpose(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
general_matrix_2x2<T>::
antisymmetric_part(antisymmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // A - A(transpose) is the antisymmetric part.

  const general_matrix_2x2<T>& lm = *this;

  xresult[0][1] = 2.0*lm[0][1];

  // Postconditions:

  // Exit:
}

///
template <typename T>
antisymmetric_matrix_2x2<T>
general_matrix_2x2<T>::
antisymmetric_part() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_2x2<T> result;
  antisymmetric_part(result);

  // Postconditions:

  // Exit:

  return result;
}


///
template <typename T>
void
general_matrix_2x2<T>::
symmetric_part(symmetric_matrix_2x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // A + A(transpose) is the antisymmetric part.

  const general_matrix_2x2<T>& lm = *this;

  xresult[0][0] = 2.0*lm[0][0];
  xresult[0][1] = lm[0][1] + lm[1][0];
  xresult[1][1] = 2.0*lm[1][1];

  // Postconditions:

  // Exit:
}

///
template <typename T>
symmetric_matrix_2x2<T>
general_matrix_2x2<T>::
symmetric_part() const
{
  // Preconditions:

  // Body:

  symmetric_matrix_2x2<T> result;
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
ostream& operator<<(ostream& xos, const general_matrix_2x2<T>& xm)
{
  // Preconditions:

  // Body:

  xos << "  " << xm[0][0] << "  " << xm[0][1] << endl;
  xos << "  " << xm[1][0] << "  " << xm[1][1] << endl;

  // Postconditions:

  // Exit:

  return xos;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

//==============================================================================
//==============================================================================
 
} // namespace fiber_bundle

#endif // GENERAL_MATRIX_2X2_IMPL_H

