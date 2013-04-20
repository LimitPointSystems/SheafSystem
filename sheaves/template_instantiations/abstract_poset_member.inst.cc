
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class abstract_poset_member

#include "abstract_poset_member.impl.h"

using namespace sheaf; // workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================
 
template
SHEAF_DLL_SPEC 
sheaf::abstract_poset_member::table_dofs_type& 
sheaf::table_dofs<sheaf::abstract_poset_member>(abstract_poset_member& x0);

template 
SHEAF_DLL_SPEC
const sheaf::abstract_poset_member::table_dofs_type& 
sheaf::table_dofs<sheaf::abstract_poset_member>(const abstract_poset_member& x0);

template 
SHEAF_DLL_SPEC
sheaf::abstract_poset_member::table_dofs_type& 
sheaf::table_dofs<sheaf::abstract_poset_member>(abstract_poset_member& x0,
						                        bool xauto_access);

template 
SHEAF_DLL_SPEC
const sheaf::abstract_poset_member::table_dofs_type& 
sheaf::table_dofs<sheaf::abstract_poset_member>(const abstract_poset_member& x0,
						                        bool xauto_access);

template 
SHEAF_DLL_SPEC
sheaf::abstract_poset_member::row_dofs_type& 
sheaf::row_dofs<sheaf::abstract_poset_member>(abstract_poset_member& x0);

template 
SHEAF_DLL_SPEC
const sheaf::abstract_poset_member::row_dofs_type& 
sheaf::row_dofs<sheaf::abstract_poset_member>(const abstract_poset_member& x0);

template 
SHEAF_DLL_SPEC
sheaf::abstract_poset_member::row_dofs_type& 
sheaf::row_dofs<sheaf::abstract_poset_member>(abstract_poset_member& x0,
					                          bool xauto_access);

template 
SHEAF_DLL_SPEC
const sheaf::abstract_poset_member::row_dofs_type& 
sheaf::row_dofs<sheaf::abstract_poset_member>(const abstract_poset_member& x0,
					                          bool xauto_access);


