
// $RCSfile: gln_table_dofs_type.h,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:01 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class gln_table_dofs_type

#ifndef GLN_TABLE_DOFS_TYPE_H
#define GLN_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif
  
namespace fiber_bundle
{  
  
//==============================================================================
// CLASS GLN_TABLE_DOFS_TYPE_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs of gln.
///
class SHEAF_DLL_SPEC gln_table_dofs_type
{
public:

  ///
  /// The path of the underlying scalar space.
  ///
  c_string scalar_space_path;

  ///
  /// The path of the underlying vector space.
  ///
  c_string vector_space_path;

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n;

};



} // namespace fiber_bundle

#endif // ifndef GLN_TABLE_DOFS_TYPE_H






