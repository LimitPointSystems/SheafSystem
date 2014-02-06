
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

// Implementation for antisymmetric_matrix_3x3.


#ifndef ANTISYMMETRIC_MATRIX_3X3_IMPL_H
#define ANTISYMMETRIC_MATRIX_3X3_IMPL_H

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

#ifndef GENERAL_MATRIX_3X2_H
#include "general_matrix_3x2.h"
#endif

#ifndef GENERAL_MATRIX_3X1_H
#include "general_matrix_3x1.h"
#endif

#ifndef GENERAL_MATRIX_3X3_H
#include "general_matrix_3x3.h"
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
antisymmetric_matrix_3x3<T>::
operator at2_e3_row_dofs_type<T>& () const
{
  // Preconditions:

  // Body:

  T* lcomps = const_cast<T*>(components);

  at2_e3_row_dofs_type<T>& result =
    reinterpret_cast<at2_e3_row_dofs_type<T>&>(*lcomps);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
int
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  //cout << "antisymmetric_matrix_3x3<T>::operator T* () " << std::endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
antisymmetric_matrix_3x3<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  //cout << "antisymmetric_matrix_3x3<T>::operator const T* () const " << std::endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
antisymmetric_matrix_3x3<T>::
row_index(int xrow) const
{

  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows()-1);

  // Body:

  int nrows = number_of_rows();
  int result = (xrow*(2*nrows-1-xrow))/2 - 1 - xrow;

  //int result = (xrow*(5-xrow))/2 - 1 - xrow;

  // Postconditions:

  ensure(result == (xrow*(2*number_of_rows()-1-xrow))/2 - 1 - xrow);

  // Exit:

  return result;
}

///
template <typename T>
antisymmetric_matrix_3x3<T>::
operator general_matrix_3x3<T> () const
{
  // Preconditions:

  // Body:

  general_matrix_3x3<T> result;

  const antisymmetric_matrix_3x3<T>& lm = *this;

  result[0][0] =  0.0;
  result[0][1] =  lm[0][1];
  result[0][2] =  lm[0][2];

  result[1][0] = -lm[0][1];
  result[1][1] =  0.0;
  result[1][2] =  lm[1][2];

  result[2][0] = -lm[0][2];
  result[2][1] = -lm[1][2];
  result[2][2] =  0.0;

  // Postconditions:

  ensure(unexecutable("result == *this"));

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x3<T>
antisymmetric_matrix_3x3<T>::
row(int xrow) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  general_matrix_1x3<T> result;

  // Just brute force it for the 3x3 case.

  if(xrow == 0)
  {
    result.components[0] =  0.0;           // [0][0];
    result.components[1] =  components[0]; // [0][1];
    result.components[2] =  components[1]; // [0][2];
  }
  else if(xrow == 1)
  {
    result.components[0] = -components[0]; // [1][0];
    result.components[1] =  0.0;           // [1][1];
    result.components[2] =  components[2]; // [1][2];
  }
  else // xrow == 2
  {
    result.components[0] = -components[1]; // [2][0];
    result.components[1] = -components[2]; // [1][2];
    result.components[2] =  0.0;           // [2][2];
  }

  // Postconditions:

  // Exit:

  return result;

}

///
template <typename T>
general_matrix_3x1<T>
antisymmetric_matrix_3x3<T>::
column(int xcolumn) const
{
  // Preconditions:

  require(xcolumn >= 0 && xcolumn < number_of_columns());

  // Body:

  general_matrix_3x1<T> result;

  // Just brute force it for the 3x3 case.

  if(xcolumn == 0)
  {
    result.components[0] =  0.0;           // [0][0];
    result.components[1] = -components[0]; // [1][0];
    result.components[2] = -components[1]; // [2][0];
  }
  else if(xcolumn == 1)
  {
    result.components[0] =  components[0]; // [0][1];
    result.components[1] =  0.0;           // [1][1];
    result.components[2] = -components[2]; // [2][1];
  }
  else // xcolumn == 2
  {
    result.components[0] =  components[1]; // [0][2];
    result.components[1] =  components[2]; // [1][2];
    result.components[2] =  0.0;           // [2][2];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
antisymmetric_matrix_3x3<T>::
adjoint(general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Get the cofactors.

  const antisymmetric_matrix_3x3<T>& lm = *this;

  //T a00 =  0;
  T a01 =  lm[0][1];
  T a02 =  lm[0][2];
  T a10 = -a01;
  //T a11 =  0;
  T a12 =  lm[1][2];
  T a20 = -a02;
  T a21 = -a12;
  //T a22 =  0;

  //T c00 = a11*a22 - a12*a21;
  //T c01 = a12*a20 - a10*a22;
  //T c02 = a10*a21 - a11*a20;

  //T c10 = a02*a21 - a01*a22;
  //T c11 = a00*a22 - a02*a20;
  //T c12 = a01*a20 - a00*a21;

  //T c20 = a01*a12 - a02*a11;
  //T c21 = a02*a10 - a00*a12;
  //T c22 = a00*a11 - a01*a10;

  T c00 = -a12*a21;
  T c01 =  a12*a20;
  T c02 =  a10*a21;

  T c10 =  a02*a21;
  T c11 = -a02*a20;
  T c12 =  a01*a20;

  T c20 =  a01*a12;
  T c21 =  a02*a10;
  T c22 = -a01*a10;

  // The adjoint matrix is the transpose of the cofactor matrix.

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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
assign(const T& xvalue)
{
  // Preconditions:

  // Body:

  // Unroll the loop in this case.

  components[0] = xvalue;
  components[1] = xvalue;
  components[2] = xvalue;

  // Postconditions:

  // Exit:
}

///
template <typename T>
void 
antisymmetric_matrix_3x3<T>::
determinant(T& xresult) const
{
  // Preconditions:

  // Body:

  // For an antisymmetric matrix, the determinant is zero
  // for all odd n (ie; n = 1, 3 5, ...).

  xresult = T(0);

  // Postconditions:

  // Exit:

}

///
template <typename T>
T
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
inverse(antisymmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  post_fatal_error_message("No inverse; determinant is zero.");

  // Postconditions:

  // Exit:
}

///
template <typename T>
antisymmetric_matrix_3x3<T>
antisymmetric_matrix_3x3<T>::
inverse() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_3x3<T> result;
  inverse(result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
bool
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
multiply(const T& xscalar, antisymmetric_matrix_3x3<T>& xresult) const
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
antisymmetric_matrix_3x3<T>
antisymmetric_matrix_3x3<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_3x3<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
antisymmetric_matrix_3x3<T>::
multiply(const general_matrix_3x1<T>& xother,
         general_matrix_3x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_3x3<T>& lm = *this;

  T a00 = 0.0;
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = -a01;
  T a11 = 0.0;
  T a12 = lm[1][2];
  T a20 = -a02;
  T a21 = -a12;
  T a22 = 0.0;

  T b00 = xother[0][0];
  T b10 = xother[1][0];;
  T b20 = xother[2][0];

  //xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  //xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  //xresult[2][0] = a20*b00 + a21*b10 + a22*b20;

  xresult[0][0] = a01*b10 + a02*b20;
  xresult[1][0] = a10*b00 + a12*b20;
  xresult[2][0] = a20*b00 + a21*b10;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x1<T>
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
multiply(const general_matrix_3x2<T>& xother,
         general_matrix_3x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_3x3<T>& lm = *this;

  T a00 = 0.0;
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = -a01;
  T a11 = 0.0;
  T a12 = lm[1][2];
  T a20 = -a02;
  T a21 = -a12;
  T a22 = 0.0;

  T b00 = xother[0][0];
  T b01 = xother[0][1];

  T b10 = xother[1][0];;
  T b11 = xother[1][1];

  T b20 = xother[2][0];
  T b21 = xother[2][1];

  //xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  //xresult[0][1] = a00*b01 + a01*b11 + a02*b21;

  //xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  //xresult[1][1] = a10*b01 + a11*b11 + a12*b21;

  //xresult[2][0] = a20*b00 + a21*b10 + a22*b20;
  //xresult[2][1] = a20*b01 + a21*b11 + a22*b21;

  xresult[0][0] = a01*b10 + a02*b20;
  xresult[0][1] = a01*b11 + a02*b21;

  xresult[1][0] = a10*b00 + a12*b20;
  xresult[1][1] = a10*b01 + a12*b21;

  xresult[2][0] = a20*b00 + a21*b10;
  xresult[2][1] = a20*b01 + a21*b11;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x2<T>
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
multiply(const general_matrix_3x3<T>& xother,
         general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_3x3<T>& lm = *this;

  T a00 = 0.0;
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = -a01;
  T a11 = 0.0;
  T a12 = lm[1][2];
  T a20 = -a02;
  T a21 = -a12;
  T a22 = 0.0;

  T b00 = xother[0][0];
  T b01 = xother[0][1];
  T b02 = xother[0][2];

  T b10 = xother[1][0];;
  T b11 = xother[1][1];
  T b12 = xother[1][2];

  T b20 = xother[2][0];
  T b21 = xother[2][1];
  T b22 = xother[2][2];

  //xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  //xresult[0][1] = a00*b01 + a01*b11 + a02*b21;
  //xresult[0][2] = a00*b02 + a01*b12 + a02*b22;

  //xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  //xresult[1][1] = a10*b01 + a11*b11 + a12*b21;
  //xresult[1][2] = a10*b02 + a11*b12 + a12*b22;

  //xresult[2][0] = a20*b00 + a21*b10 + a22*b20;
  //xresult[2][1] = a20*b01 + a21*b11 + a22*b21;
  //xresult[2][2] = a20*b02 + a21*b12 + a22*b22;

  xresult[0][0] = a01*b10 + a02*b20;
  xresult[0][1] = a01*b11 + a02*b21;
  xresult[0][2] = a01*b12 + a02*b22;

  xresult[1][0] = a10*b00 + a12*b20;
  xresult[1][1] = a10*b01 + a12*b21;
  xresult[1][2] = a10*b02 + a12*b22;

  xresult[2][0] = a20*b00 + a21*b10;
  xresult[2][1] = a20*b01 + a21*b11;
  xresult[2][2] = a20*b02 + a21*b12;


  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x3<T>
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
multiply(const antisymmetric_matrix_3x3<T>& xother,
         general_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const antisymmetric_matrix_3x3<T>& lm = *this;

  T a00 = 0.0;
  T a01 = lm[0][1];
  T a02 = lm[0][2];
  T a10 = -a01;
  T a11 = 0.0;
  T a12 = lm[1][2];
  T a20 = -a02;
  T a21 = -a12;
  T a22 = 0.0;

  T b00 = 0.0;
  T b01 = xother[0][1];
  T b02 = xother[0][2];
  T b10 = -b01;
  T b11 = 0.0;
  T b12 = xother[1][2];
  T b20 = -b02;
  T b21 = -b12;
  T b22 = 0.0;

  //xresult[0][0] = a00*b00 + a01*b10 + a02*b20;
  //xresult[0][1] = a00*b01 + a01*b11 + a02*b21;
  //xresult[0][2] = a00*b02 + a01*b12 + a02*b22;

  //xresult[1][0] = a10*b00 + a11*b10 + a12*b20;
  //xresult[1][1] = a10*b01 + a11*b11 + a12*b21;
  //xresult[1][2] = a10*b02 + a11*b12 + a12*b22;

  //xresult[2][0] = a20*b00 + a21*b10 + a22*b20;
  //xresult[2][1] = a20*b01 + a21*b11 + a22*b21;
  //xresult[2][2] = a20*b02 + a21*b12 + a22*b22;

  xresult[0][0] = a01*b10 + a02*b20;
  xresult[0][1] = a02*b21;
  xresult[0][2] = a01*b12;

  xresult[1][0] = a12*b20;
  xresult[1][1] = a10*b01 + a12*b21;
  xresult[1][2] = a10*b02;

  xresult[2][0] = a21*b10;
  xresult[2][1] = a20*b01;
  xresult[2][2] = a20*b02 + a21*b12;

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_3x3<T>
antisymmetric_matrix_3x3<T>::
multiply(const antisymmetric_matrix_3x3<T>& xother) const
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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
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
antisymmetric_matrix_3x3<T>::
transpose(antisymmetric_matrix_3x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Just unroll the loop here.

  const antisymmetric_matrix_3x3<T>& lm = *this;

  xresult[0][1] = -lm[0][1];
  xresult[0][2] = -lm[0][2];
  xresult[1][2] = -lm[1][2];

  // Postconditions:

  // Exit:

}

///
template <typename T>
antisymmetric_matrix_3x3<T>
antisymmetric_matrix_3x3<T>::
transpose() const
{
  // Preconditions:

  // Body:

  antisymmetric_matrix_3x3<T> result;
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
std::ostream& operator<<(std::ostream& xos, const antisymmetric_matrix_3x3<T>& xm)
{
  // Preconditions:

  // Body:

  // Here we will actually print the elements on and below the diagonal
  // even though we don't store them.

  int nrows = xm.number_of_rows();
  int ncols = xm.number_of_columns();

  for(int i=0; i<nrows; ++i)
  {
    for(int j=0; j<ncols; ++j)
    {
      T v;
      if(i == j)
        v = T(0);
      else if(i < j)
        v =  xm[i][j];
      else
        v = -xm[j][i];
   
      xos << "  " << v;
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

#endif // ANTISYMMETRIC_MATRIX_3X3_IMPL

