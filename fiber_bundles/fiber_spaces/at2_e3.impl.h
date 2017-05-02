
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
/// Implementation for class at2_e3.

#ifndef AT2_E3_IMPL_H
#define AT2_E3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef AT2_E3_H
#include "SheafSystem/at2_e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS AT2_E3_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
at2_e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("at2_e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
at2_e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 3;

  // Postconditions:

  ensure(result == 3);

  // Exit:

  return result;
}

template <typename T>
T&
at2_e3_row_dofs_type<T>::
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
at2_e3_row_dofs_type<T>::
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
at2_e3_row_dofs_type<T>::
operator typename at2_e3_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return reinterpret_cast<matrix_type&>(*this);
}

template <typename T>
at2_e3_row_dofs_type<T>::
operator const typename at2_e3_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  at2_e3_row_dofs_type<T>& lthis = const_cast<at2_e3_row_dofs_type<T>&>(*this);
  const matrix_type& result = reinterpret_cast<matrix_type&>(lthis);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
at2_e3_row_dofs_type<T>* 
at2_e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  at2_e3_row_dofs_type<T>* result = new at2_e3_row_dofs_type<T>();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#ifndef DOXYGEN_SKIP_IMPLEMENTATIONS
template <typename T>
std::ostream& operator<<(std::ostream& xos, const at2_e3_row_dofs_type<T>& xrdt)
{
  int ld = xrdt.d();
  for(int i=0; i<ld; ++i)
  {
    xos << " " << xrdt.components[i];
  }

  return xos;
}
#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

} // namespace fiber_bundle

#endif // ifndef AT2_E3_IMPL_H
