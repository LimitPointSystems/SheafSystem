

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class tuple_table_dofs_type.

#ifndef TUPLE_TABLE_DOFS_TYPE_H
#define TUPLE_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

//==============================================================================
// CLASS TUPLE_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs type for class tuple_table_dofs_type.
///
class SHEAF_DLL_SPEC tuple_table_dofs_type
{
public:

  ///
  /// Number of factors (components) in tuple.
  ///
  int factor_ct;

};

} // namespace fiber_bundle

#endif // ifndef TUPLE_TABLE_DOFS_TYPE_H
