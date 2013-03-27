
// $RCSfile: jcb_table_dofs_type.h,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:01 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class jcb_table_dofs_type.

#ifndef JCB_TABLE_DOFS_TYPE_H
#define JCB_TABLE_DOFS_TYPE_H

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
// CLASS JCB_TABLE_DOFS_TYPE_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs type for class jcb.
///
class SHEAF_DLL_SPEC jcb_table_dofs_type
{
public:

  // Order has to conform to order in schema,
  // which has to conform to order in dof id space of top.

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

  ///
  /// Dimension of the domain.
  ///
  int dd;

  ///
  /// The path of the domain vector space.
  ///
  c_string domain_path;

  ///
  /// The path of the range vector space.
  ///
  c_string range_path;

  ///
  /// Dimension of the range.
  ///
  int dr;

};


} // namespace fiber_bundle


#endif // ifndef JCB_TABLE_DOFS_TYPE_H
