
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
/// Implementation for class met_e3.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_MET_E3_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_MET_E3_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_MET_E3_H
#include "ComLimitPoint/fiber_bundle/met_e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS MET_E3_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
met_e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("met_e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
met_e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 6;

  // Postconditions:

  ensure(result == 6);

  // Exit:

  return result;
}

template <typename T>
T&
met_e3_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  require(xindex>=0 && xindex<d());

  // Body:

  T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const T&
met_e3_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  require(xindex>=0 && xindex<d());

  // Body:

  const T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
met_e3_row_dofs_type<T>::
operator typename met_e3_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = reinterpret_cast<matrix_type&>(*this);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
met_e3_row_dofs_type<T>::
operator const typename met_e3_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  met_e3_row_dofs_type<T>& lthis = const_cast<met_e3_row_dofs_type<T>&>(*this);
  const matrix_type& result = reinterpret_cast<matrix_type&>(lthis);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
met_e3_row_dofs_type<T>* 
met_e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  met_e3_row_dofs_type<T>* result = new met_e3_row_dofs_type<T>();

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
std::ostream& operator<<(std::ostream& xos, const met_e3_row_dofs_type<T>& xrdt)
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

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_MET_E3_IMPL_H
