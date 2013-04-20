

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class fields

#ifndef FIELDS_H
#define FIELDS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
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
