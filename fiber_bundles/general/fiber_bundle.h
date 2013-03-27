// $RCSfile: fiber_bundle.h,v $ $Revision: 1.17 $ $Date: 2013/01/12 17:17:07 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef FIBER_BUNDLE_H
#define FIBER_BUNDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

namespace sheaf
{
class poset_path;
}

///
/// Namespace for the fiber_bundles component of the sheaf system.
///
namespace fiber_bundle
{

using namespace sheaf;
  
// The following types are derived from the various roles that
// appear in the structure of a section of a fiber bundle, especially
// the most common category, vector bundle. They are defined here,
// as opposed to the classes which represent their logical origin,
// in order to avoid including the class headers just to get these types.
//
// Note that since the value of a section is a member of a fiber space,
// vd and sec_vd share the same value type. But since vd and sec_vd
// don't actually share dofs, they don't in principle  have the same dof type.
// Of course, all these types are double in practice.

///
/// The type of local coordinate in the base space;
/// the scalar type for the local coordinate vector space.
///
typedef double chart_point_coord_type;

///
/// The type of component in the fiber;
/// the scalar type in the fiber vector space.
///
typedef double vd_value_type;

///
/// The type of degree of freedom in the fiber space.
///
typedef double vd_dof_type;

///
/// The type of component in the value of a section at a point.
///
typedef vd_value_type sec_vd_value_type;

///
/// The type of degree of freedom in the section space.
///
typedef double sec_vd_dof_type;

///
/// The standard path for the section space with fiber space path
/// xfiber_path and base space path xbase_path.
///
poset_path SHEAF_DLL_SPEC standard_section_space_path(const poset_path& xfiber_path,
                                       const poset_path& xbase_path);

///
/// The standard path for the section space schema
///
poset_path SHEAF_DLL_SPEC standard_section_space_schema_path(const poset_path& xsection_space_path);

///
/// The standard path for the fiber
///
poset_path SHEAF_DLL_SPEC standard_fiber_path();

///
/// The standard path for the vector space
///
poset_path SHEAF_DLL_SPEC standard_vector_space_path();

};

#endif // ifndef FIBER_BUNDLE_H
