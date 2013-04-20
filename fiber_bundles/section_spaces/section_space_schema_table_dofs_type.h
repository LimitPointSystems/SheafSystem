

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE

#ifndef SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H
#define SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "namespace_relative_member_index.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

///
/// Table dofs type for class section_space_schema_poset.
///
class SHEAF_DLL_SPEC section_space_schema_table_dofs_type
{
public:

  ///
  /// The section representation path.
  ///
  c_string rep_path;

  ///
  /// The base space path.
  ///
  c_string base_space_path;

  ///
  /// The fiber schema space path.
  ///
  c_string fiber_space_path;

};

} // namespace fiber_bundle

#endif // SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H
