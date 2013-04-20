

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for general_matrix_1x2.


#ifndef GENERAL_MATRIX_1X2_IMPL_H
#define GENERAL_MATRIX_1X2_IMPL_H

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

#ifndef GENERAL_MATRIX_1X3_H
#include "general_matrix_1x3.h"
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
int
general_matrix_1x2<T>::
number_of_rows()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 1;
}

///
template <typename T>
int
general_matrix_1x2<T>::
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
general_matrix_1x2<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 2;
}

///
template <typename T>
T*
general_matrix_1x2<T>::
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
general_matrix_1x2<T>::
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
general_matrix_1x2<T>::
operator T* ()
{
  // Preconditions:

  // Body:

  cout << "general_matrix_1x2<T>::operator T* () " << endl;

  T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
general_matrix_1x2<T>::
operator const T* () const
{
  // Preconditions:

  // Body:

  cout << "general_matrix_1x2<T>::operator const T* () const " << endl;

  const T* result = components;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

///
template <typename T>
int
general_matrix_1x2<T>::
row_index(int xrow) const
{

  // Preconditions:

  require(xrow >= 0 && xrow < number_of_rows());

  // Body:

  //int result = number_of_columns()*nrow;
  //int result = 1*xrow;
  int result = xrow;

  // Postconditions:

  ensure(result == number_of_columns()*xrow);

  // Exit:

  return result;
}

///
template <typename T>
void
general_matrix_1x2<T>::
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
general_matrix_1x2<T>::
multiply(const T& xscalar, general_matrix_1x2<T>& xresult) const
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
general_matrix_1x2<T>
general_matrix_1x2<T>::
multiply(const T& xscalar) const
{
  // Preconditions:

  // Body:

  general_matrix_1x2<T> result;
  multiply(xscalar, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
general_matrix_1x2<T>::
multiply(const general_matrix_2x1<T>& xother, T& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_1x2<T>& lm = *this;

  T a00 = lm[0][0];
  T a01 = lm[0][1];

  T b00 = xother[0][0];
  T b10 = xother[1][0];

  xresult = a00*b00 + a01*b10;

  // Postconditions:

  // Exit:

}

///
template <typename T>
T
general_matrix_1x2<T>::
multiply(const general_matrix_2x1<T>& xother) const
{
  // Preconditions:

  // Body:

  T result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
general_matrix_1x2<T>::
multiply(const general_matrix_2x2<T>& xother,
         general_matrix_1x2<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_1x2<T>& lm = *this;

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
general_matrix_1x2<T>
general_matrix_1x2<T>::
multiply(const general_matrix_2x2<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_1x2<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void 
general_matrix_1x2<T>::
multiply(const general_matrix_2x3<T>& xother,
         general_matrix_1x3<T>& xresult) const
{
  // Preconditions:

  // Body:

  // Multiply [A][B] where [A] = *this & [B] = xother.

  const general_matrix_1x2<T>& lm = *this;

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
general_matrix_1x3<T>
general_matrix_1x2<T>::
multiply(const general_matrix_2x3<T>& xother) const
{
  // Preconditions:

  // Body:

  general_matrix_1x3<T> result;
  multiply(xother, result);

  // Postconditions:

  // Exit:

  return result;
}

///
template <typename T>
void
general_matrix_1x2<T>::
transpose(general_matrix_2x1<T>& xresult) const
{
  // Preconditions:

  // Body:

  const general_matrix_1x2<T>& lm = *this;

  xresult[0][0] = lm[0][0];
  xresult[1][0] = lm[0][1];

  // Postconditions:

  // Exit:

}

///
template <typename T>
general_matrix_2x1<T>
general_matrix_1x2<T>::
transpose() const
{
  // Preconditions:

  // Body:

  general_matrix_2x1<T> result;
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
ostream& operator<<(ostream& xos, const general_matrix_1x2<T>& xm)
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
    xos << endl;
  }

  // Postconditions:

  // Exit:

  return xos;
}

#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

//==============================================================================
//==============================================================================
 
} // namespace fiber_bundle

#endif // GENERAL_MATRIX_1X2_IMPL_H
