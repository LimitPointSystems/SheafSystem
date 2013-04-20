

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE

#ifndef SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H
#define SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H

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
/// Table dofs type for class sec_rep_descriptor_poset.
///
class SHEAF_DLL_SPEC sec_rep_descriptor_table_dofs_type
{
public:

  ///
  /// The base space prototypes path.
  ///
  c_string prototypes_path;

};

} // namespace fiber_bundle

#endif // SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H
