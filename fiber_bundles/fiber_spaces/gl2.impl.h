
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
/// Implementation for class gl2.

#ifndef GL2_IMPL_H
#define GL2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef GL2_H
#include "SheafSystem/gl2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS GL2_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
gl2_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("gl2_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
gl2_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 8;

  // Postconditions:

  ensure(result == 8);

  // Exit:

  return result;
}

template <typename T>
T&
gl2_row_dofs_type<T>::
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
gl2_row_dofs_type<T>::
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
gl2_row_dofs_type<T>::
operator typename gl2_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = basis_matrix();

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
gl2_row_dofs_type<T>::
operator const typename gl2_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = basis_matrix();

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
typename gl2_row_dofs_type<T>::matrix_type& 
gl2_row_dofs_type<T>::
basis_matrix()
{
  // Preconditions:

  // Body:

  T& comp0 = components[0];
  matrix_type& result = reinterpret_cast<matrix_type&>(comp0);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const typename gl2_row_dofs_type<T>::matrix_type& 
gl2_row_dofs_type<T>::
basis_matrix() const
{
  // Preconditions:

  // Body:

  T& comp0 = const_cast<T&>(components[0]);
  const matrix_type& result = reinterpret_cast<matrix_type&>(comp0);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
typename gl2_row_dofs_type<T>::matrix_type& 
gl2_row_dofs_type<T>::
component_matrix()
{
  // Preconditions:

  // Body:

  // Component part states at element 4.

  T& comp4 = components[4];
  matrix_type& result = reinterpret_cast<matrix_type&>(comp4);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const typename gl2_row_dofs_type<T>::matrix_type& 
gl2_row_dofs_type<T>::
component_matrix() const
{
  // Preconditions:

  // Body:

  // Component part states at element 4.

  T& comp4 = const_cast<T&>(components[4]);
  const matrix_type& result = reinterpret_cast<matrix_type&>(comp4);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
gl2_row_dofs_type<T>* 
gl2_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  gl2_row_dofs_type<T>* result = new gl2_row_dofs_type<T>();

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
std::ostream& operator<<(std::ostream& xos, const gl2_row_dofs_type<T>& xrdt)
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

#endif // ifndef GL2_IMPL_H
