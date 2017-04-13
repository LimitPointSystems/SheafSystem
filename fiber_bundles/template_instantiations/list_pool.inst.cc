
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

 
// Explicit instantiations for class list_pool.

#include "SheafSystem/list_pool.impl.h"

#include "SheafSystem/i_adjacency_implicit_index_space_iterator.h"
#include "SheafSystem/i_connectivity_implicit_index_space_iterator.h"
#include "SheafSystem/ij_adjacency_implicit_index_space_iterator.h"
#include "SheafSystem/ij_connectivity_implicit_index_space_iterator.h"
#include "SheafSystem/ijk_adjacency_implicit_index_space_iterator.h"
#include "SheafSystem/ijk_connectivity_implicit_index_space_iterator.h"
#include "SheafSystem/section_space_schema_jims_index_space_handle.h"
#include "SheafSystem/section_space_schema_jims_index_space_iterator.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// i_adjacency_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::i_adjacency_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::i_adjacency_implicit_index_space_iterator>(const list_pool<fiber_bundle::i_adjacency_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// i_connectivity_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::i_connectivity_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::i_connectivity_implicit_index_space_iterator>(const list_pool<fiber_bundle::i_connectivity_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// ij_adjacency_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::ij_adjacency_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::ij_adjacency_implicit_index_space_iterator>(const list_pool<fiber_bundle::ij_adjacency_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// ij_connectivity_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::ij_connectivity_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::ij_connectivity_implicit_index_space_iterator>(const list_pool<fiber_bundle::ij_connectivity_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// ijk_adjacency_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::ijk_adjacency_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::ijk_adjacency_implicit_index_space_iterator>(const list_pool<fiber_bundle::ijk_adjacency_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// ijk_connectivity_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::ijk_connectivity_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::ijk_connectivity_implicit_index_space_iterator>(const list_pool<fiber_bundle::ijk_connectivity_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// section_space_schema_jims_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::section_space_schema_jims_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::section_space_schema_jims_index_space_handle>(const list_pool<fiber_bundle::section_space_schema_jims_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// section_space_schema_jims_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<fiber_bundle::section_space_schema_jims_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<fiber_bundle::section_space_schema_jims_index_space_iterator>(const list_pool<fiber_bundle::section_space_schema_jims_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
