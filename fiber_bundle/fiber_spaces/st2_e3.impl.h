
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

/// @file
/// Implementation for class st2_e3.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_ST2_E3_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_ST2_E3_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_ST2_E3_H
#include "ComLimitPoint/fiber_bundle/st2_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_GL3_H
#include "ComLimitPoint/fiber_bundle/gl3.h"
#endif

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST2_E3_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
st2_e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("st2_e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
st2_e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 6;
}

template <typename T>
T&
st2_e3_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  ensure(xindex>=0 && xindex<d());

  // Body:

  T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const T&
st2_e3_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  ensure(xindex>=0 && xindex<d());

  // Body:

  const T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
st2_e3_row_dofs_type<T>::
operator typename st2_e3_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return reinterpret_cast<matrix_type&>(*this);
}

template <typename T>
st2_e3_row_dofs_type<T>::
operator const typename st2_e3_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  st2_e3_row_dofs_type<T>& lthis = const_cast<st2_e3_row_dofs_type<T>&>(*this);

  return reinterpret_cast<matrix_type&>(lthis);
}

template <typename T>
st2_e3_row_dofs_type<T>* 
st2_e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  st2_e3_row_dofs_type<T>* result = new st2_e3_row_dofs_type<T>();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

template <typename T>
std::ostream& operator<<(std::ostream& xos, const st2_e3_row_dofs_type<T>& xrdt)
{
  int ld = xrdt.d();
  for(int i=0; i<ld; ++i)
  {
    xos << " " << xrdt.components[i];
  }

  return xos;
}

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_ST2_E3_IMPL_H