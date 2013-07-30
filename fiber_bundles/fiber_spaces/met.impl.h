

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for met facet function templates.


#ifndef MET_IMPL_H
#define MET_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MET_H
#include "met.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

// template <typename T, typename MT>
// T* raise(const MT& xmetric, const T& xcovector)
// {
//   // Preconditions:

//   require(xmetric.state_is_auto_read_accessible(true));
//   require(xcovector.state_is_auto_read_accessible(true));
//   require(xcovector.d(true) == xmetric.dd(true));
//   require(xmetric.is_contravariant(0, true));
//   require(xcovector.is_covariant(0, true));   //  is_dual;

//   // Body:

//   /// @hack vd heirarchy isn't const correct.

//   T& lxcovector = const_cast<T&>(xcovector);
//   T* result = lxcovector.clone(true, true);

//   // For the raise operation, the result must be contravariant.

//   // Not for volatile type!!!
//   result->put_is_p_vector(true);

//   raise(xmetric, lxcovector, *result);

//   // Postconditions:

//   ensure(result != 0);
//   ensure(postcondition_of(xcovector.clone(true, true)));
//   ensure(postcondition_of(raise(xmetric, xcovector, *result))); 

//   // Exit:

//   return result;
// }

// template <typename T, typename MT>
// T* lower(const MT& xmetric, const T& xvector)
// {
//   // Preconditions:

//   //require(precondition_of(xvector.clone(true, true)));
//   //require(precondition_of(lower(xmetric, xvector, *result)));

//   require(xmetric.state_is_auto_read_accessible(true));
//   require(xvector.state_is_auto_read_accessible(true));
//   require(xvector.d(true) == xmetric.dd(true));
//   require(xmetric.is_covariant(0, true));
//   require(xvector.is_contravariant(0, true)); // !is_dual;


//   // Body:

//   /// @hack vd heirarchy isn't const correct.

//   T& lxvector = const_cast<T&>(xvector);
//   T* result = lxvector.clone(true, true);;

//   // For the lower operation, the result must be covariant.

//   // Not for volatile type!!!
//   result->put_is_p_form(true);

//   lower(xmetric, xvector, *result);

//   // Postconditions:

//   ensure(result != 0);
//   ensure(postcondition_of(xvector.clone(true, true)));
//   ensure(postcondition_of(lower(xmetric, xvector, *result))); 

//   // Exit:

//   return result;
// }

} // namespace fiber_bundle

#endif // ifndef MET_IMPL_H
