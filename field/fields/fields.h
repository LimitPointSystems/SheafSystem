
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
/// Interface for class fields

#ifndef FIELDS_H
#define FIELDS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif

namespace sheaf
{
template <class T>
class block;
}

namespace fiber_bundle
{
class chart_point_3d;
}

///
/// Namespace for fields component of sheaf system.
///
namespace fields
{

// Fields name space includes fiber_bundle name space.

using namespace sheaf;
using namespace fiber_bundle;
using namespace geometry;

///
/// The type of the function for computing
/// the property dofs at given global coordinates.
///
typedef void (*property_dof_function_type)
(block<sec_vd_value_type>& xglobal_coords,
 block<sec_vd_dof_type>& xproperty_dofs);


// ///
// /// A point in base space paired with a branch in section space.
// ///
// typedef pair<scoped_index, chart_point_3d> branch_point_pair;

} // namespace fields

#endif // ifndef FIELDS_H
