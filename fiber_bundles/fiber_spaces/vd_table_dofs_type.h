

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class vd_table_dofs_type.

#ifndef VD_TABLE_DOFS_TYPE_H
#define VD_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif
 
namespace fiber_bundle
{
  using namespace sheaf;
  
//==============================================================================
// CLASS VD_TABLE_DOFS_TYPE
//==============================================================================
 
///
/// Table dofs type for class vd_table_dofs_type.
///
class SHEAF_DLL_SPEC vd_table_dofs_type
{
public:

  ///
  /// Number of factors (components) in tuple.
  ///
  int factor_ct;

  ///
  /// Dimension of this as a vector space.
  ///
  int d;

  ///
  /// The path of the underlying scalar space.
  ///
  c_string scalar_space_path;

};



} // namespace fiber_bundle

#endif // ifndef VD_TABLE_DOFS_TYPE_H
