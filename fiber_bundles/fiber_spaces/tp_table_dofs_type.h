
// $RCSfile: tp_table_dofs_type.h,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:03 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class tp_table_dofs_type

#ifndef TP_TABLE_DOFS_TYPE_H
#define TP_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

namespace fiber_bundle
{
  
//==============================================================================
// CLASS TP_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs type for class tp.
///
class SHEAF_DLL_SPEC tp_table_dofs_type
{
public:

  ///
  ///  Number of factors (components) in tuple.
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
  /// The degree of the tensor; 
  /// the sum of the contravariant and covariant degrees.
  int p;

  ///
  /// Dimension of the underlying vector space.
  ///
  int dd;

  ///
  /// The path of the underlying vector space.
  ///
  c_string vector_space_path;

};


} // namespace fiber_bundle


#endif // ifndef TP_TABLE_DOFS_TYPE_H
