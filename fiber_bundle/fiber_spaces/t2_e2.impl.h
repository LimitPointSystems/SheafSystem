
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
/// Implementation for t2_e2 facet function templates.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_T2_E2_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_T2_E2_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_T2_E2_H
#include "ComLimitPoint/fiber_bundle/t2_e2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T2_E2_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
t2_e2_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("t2_e2_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
t2_e2_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 4;

  // Postconditions:

  ensure(result == 4);

  // Exit:

  return result;

}

template <typename T>
T&
t2_e2_row_dofs_type<T>::
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
t2_e2_row_dofs_type<T>::
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
t2_e2_row_dofs_type<T>::
operator typename t2_e2_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = reinterpret_cast<matrix_type&>(*this);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
t2_e2_row_dofs_type<T>::
operator const typename t2_e2_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  t2_e2_row_dofs_type<T>& lthis = const_cast<t2_e2_row_dofs_type<T>&>(*this);
  const matrix_type& result = reinterpret_cast<matrix_type&>(lthis);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
t2_e2_row_dofs_type<T>* 
t2_e2_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  t2_e2_row_dofs_type<T>* result = new t2_e2_row_dofs_type<T>();

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
std::ostream& operator<<(std::ostream& xos, const t2_e2_row_dofs_type<T>& xrdt)
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

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_T2_E2_IMPL_H