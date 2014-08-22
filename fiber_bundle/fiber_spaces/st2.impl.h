
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
/// Implementation for st2 facet function templates.


#ifndef COM_LIMITPOINT_FIBER_BUNDLE_ST2_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_ST2_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_ST2_H
#include "ComLimitPoint/fiber_bundle/st2.h"
#endif

namespace fiber_bundle
{

namespace st2_algebra
{

template <typename T, typename GLN>
T* to_principal_axes(const T& xlite, GLN& xtransform)
{
  // Preconditions:

  // Body:

  T* result = xlite.clone();

  to_principal_axes(xlite, xtransform, *result);

  // Postconditions:

  return result;

  // Exit:
}

template <typename T, typename GLN>
void to_principal_axes(const T& xlite, GLN& xtransform, T& xresult)
{
  // Preconditions:

  // Body:

  not_implemented(); //Specialized for some cases (See st2_e2 & st2_e3). 

  // Postconditions:

  // Exit:
}

template <typename T, typename GLN>
void to_principal_axes(const T& xlite, const T& xpd_lite,
                       GLN& xtransform, T& xresult)
{
  // Preconditions:

  // Body:

  not_implemented(); //Specialized for some cases (See st2_e2 & st2_e3). 

  // Postconditions:

  // Exit:
}
  
} // namespace st2_algebra

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_ST2_IMPL_H
