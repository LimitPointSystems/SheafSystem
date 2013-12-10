
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
/// Explicit instantiations for class d_array_point_locator.


#include "d_array_point_locator.impl.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<1, 1>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<2, 2>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<3, 1>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<3, 2>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<3, 3>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <1, 1>(ostream& xos,
                            const geometry::d_array_point_locator<1, 1>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <2, 2>(ostream& xos,
                            const geometry::d_array_point_locator<2, 2>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <3, 1>(ostream& xos,
                            const geometry::d_array_point_locator<3, 1>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <3, 2>(ostream& xos,
                            const geometry::d_array_point_locator<3, 2>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <3, 3>(ostream& xos,
                            const geometry::d_array_point_locator<3, 3>& xpl);


#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
