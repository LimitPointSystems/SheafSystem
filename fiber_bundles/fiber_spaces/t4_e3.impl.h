
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
/// Implementation for class t4_e3

#ifndef T4_E3_IMPL_H
#define T4_E3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef T4_E3_H
#include "SheafSystem/t4_e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T4_E3_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
t4_e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("t4_e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
t4_e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 81;

  // Postconditions:

  ensure(result == 81);

  // Exit:

  return result;
}

template <typename T>
T&
t4_e3_row_dofs_type<T>::
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
t4_e3_row_dofs_type<T>::
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
t4_e3_row_dofs_type<T>* 
t4_e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  t4_e3_row_dofs_type<T>* result = new t4_e3_row_dofs_type<T>();

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
std::ostream& operator<<(std::ostream& xos, const t4_e3_row_dofs_type<T>& xrdt)
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

#endif // ifndef T4_E3_IMPL_H
