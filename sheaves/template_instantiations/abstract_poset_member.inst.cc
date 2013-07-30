
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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


