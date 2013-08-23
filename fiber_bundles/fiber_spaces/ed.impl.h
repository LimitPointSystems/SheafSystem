
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Implementation for ed facet function templates.

#ifndef ED_IMPL_H
#define ED_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ED_H
#include "ed.h"
#endif

namespace fiber_bundle
{

namespace ed_algebra
{

template <typename T>
vd_value_type operator*(const T& x0, const T& x1)
{
  // Preconditions:

  require(precondition_of(dot(x0, x1)));

  // Body:
 
  vd_value_type result = dot(x0, x1);

  // Postconditions:

  ensure(postcondition_of(dot(x0, x1)));

  // Exit:

  return result;
}

template <typename T>
void normalize(T& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(normalize(x0, x0, xauto_access)));

  // Body:

  normalize(x0, x0, xauto_access);

  // Postconditions:

  ensure(postcondition_of(normalize(x0, x0, xauto_access)));

  // Exit:
}

template <typename T>
void normalize(T& x0)
{
  // Preconditions:

  require(precondition_of(normalize(x0, x0)));

  // Body:

  normalize(x0, x0);

  // Postconditions:

  ensure(postcondition_of(normalize(x0, x0)));

  // Exit:
}
  
} // namespace ed_algebra

} // namespace fiber_bundle

#endif // ifndef ED_IMPL_H
