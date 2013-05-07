

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class geometry

#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STL_SCOPED_INDEX_H
#include "stl_scoped_index.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
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
  class e3_lite;
  class e2_lite;
}

///
/// Namespace for geometry component of sheaf system.
///
namespace geometry
{

  // geometry name space includes fiber_bundle name space.

  using namespace sheaf;
  using namespace fiber_bundle;



  // ===========================================================
  // NON-MEMBER FUNCTIONS
  // ===========================================================
 
} // namespace geometry

#endif // ifndef GEOMETRY_H
