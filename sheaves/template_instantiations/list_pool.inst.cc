
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

#include "SheafSystem/array_implicit_index_space_iterator.h"
#include "SheafSystem/array_index_space_handle.h"
#include "SheafSystem/array_index_space_iterator.h"
#include "SheafSystem/constant_implicit_index_space_iterator.h"
#include "SheafSystem/explicit_index_space_handle.h"
#include "SheafSystem/forwarding_index_space_handle.h"
#include "SheafSystem/hash_index_space_handle.h"
#include "SheafSystem/hash_index_space_iterator.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/hub_index_space_iterator.h"
#include "SheafSystem/interval_index_space_handle.h"
#include "SheafSystem/interval_index_space_iterator.h"
#include "SheafSystem/list_index_space_iterator.h"
#include "SheafSystem/list_index_space_handle.h"
#include "SheafSystem/offset_index_space_handle.h"
#include "SheafSystem/offset_index_space_iterator.h"
#include "SheafSystem/primary_index_space_handle.h"
#include "SheafSystem/primary_index_space_iterator.h"
#include "SheafSystem/primitives_index_space_handle.h"
#include "SheafSystem/primitives_index_space_iterator.h"
#include "SheafSystem/ragged_array_implicit_index_space_iterator.h"
#include "SheafSystem/reserved_primary_index_space_handle.h"
#include "SheafSystem/reserved_primary_index_space_iterator.h"
#include "SheafSystem/singleton_implicit_index_space_iterator.h"
#include "SheafSystem/singleton_index_space_handle.h"
#include "SheafSystem/singleton_index_space_iterator.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// array_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::array_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::array_implicit_index_space_iterator>(const list_pool<array_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// array_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::array_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::array_index_space_handle>(const list_pool<array_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// array_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::array_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::array_index_space_iterator>(const list_pool<array_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// constant_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::constant_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::constant_implicit_index_space_iterator>(const list_pool<constant_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// forwarding_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::forwarding_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::forwarding_index_space_handle>(const list_pool<forwarding_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// hash_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::hash_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::hash_index_space_handle>(const list_pool<hash_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// hash_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::hash_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::hash_index_space_iterator>(const list_pool<hash_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// hub_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::hub_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::hub_index_space_handle>(const list_pool<hub_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// hub_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::hub_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::hub_index_space_iterator>(const list_pool<hub_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// interval_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::interval_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::interval_index_space_handle>(const list_pool<interval_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// interval_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::interval_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::interval_index_space_iterator>(const list_pool<interval_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// list_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::list_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::list_index_space_handle>(const list_pool<list_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// list_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::list_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::list_index_space_iterator>(const list_pool<list_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// offset_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::offset_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::offset_index_space_handle>(const list_pool<offset_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// offset_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::offset_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::offset_index_space_iterator>(const list_pool<offset_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// primary_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::primary_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::primary_index_space_handle>(const list_pool<primary_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// primary_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::primary_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::primary_index_space_iterator>(const list_pool<primary_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// primitives_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::primitives_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::primitives_index_space_handle>(const list_pool<primitives_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// primitives_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::primitives_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::primitives_index_space_iterator>(const list_pool<primitives_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// ragged_array_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::ragged_array_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::ragged_array_implicit_index_space_iterator>(const list_pool<ragged_array_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// reserved_primary_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::reserved_primary_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::reserved_primary_index_space_handle>(const list_pool<reserved_primary_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// reserved_primary_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::reserved_primary_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::reserved_primary_index_space_iterator>(const list_pool<reserved_primary_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// singleton_implicit_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::singleton_implicit_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::singleton_implicit_index_space_iterator>(const list_pool<singleton_implicit_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// singleton_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::singleton_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::singleton_index_space_handle>(const list_pool<singleton_index_space_handle>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// singleton_index_space_iterator
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::singleton_index_space_iterator>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::singleton_index_space_iterator>(const list_pool<singleton_index_space_iterator>& xpool, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

