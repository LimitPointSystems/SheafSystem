
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
/// Interface for class geometry

#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_FIBER_BUNDLE_H
#include "ComLimitPoint/fiber_bundle/fiber_bundle.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_STL_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/stl_scoped_index.h"
#endif

#ifndef STD_UNORDERED_SET_H
#include "std_unordered_set.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif
 
#ifndef STD_SET_H
#include "std_set.h"
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
/// Namespace for geometry component of sheaf system.
///
namespace geometry
{

  // geometry name space includes fiber_bundle name space.

  using namespace sheaf;
  using namespace fiber_bundle;


  ///
  /// A point in base space paired with a branch in section space.
  ///
  typedef std::pair<scoped_index, chart_point_3d> branch_point_pair;


  // ===========================================================
  // NON-MEMBER FUNCTIONS
  // ===========================================================
 
} // namespace geometry

#endif // ifndef GEOMETRY_H
