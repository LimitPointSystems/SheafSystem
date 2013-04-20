
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 
// Explicit instantiations for class list_pool.

#include "list_pool.impl.h"

#include "array_implicit_index_space_iterator.h"
#include "array_index_space_iterator.h"
#include "constant_implicit_index_space_iterator.h"
#include "explicit_index_space_handle.h"
#include "forwarding_index_space_handle.h"
#include "hash_index_space_iterator.h"
#include "hub_index_space_handle.h"
#include "hub_index_space_iterator.h"
#include "interval_index_space_handle.h"
#include "interval_index_space_iterator.h"
#include "list_index_space_iterator.h"
#include "mutable_index_space_handle.h"
#include "offset_index_space_handle.h"
#include "offset_index_space_iterator.h"
#include "primary_index_space_handle.h"
#include "primary_index_space_iterator.h"
#include "primitives_index_space_iterator.h"
#include "ragged_array_implicit_index_space_iterator.h"
#include "reserved_primary_index_space_handle.h"
#include "reserved_primary_index_space_iterator.h"
#include "singleton_implicit_index_space_iterator.h"
#include "singleton_index_space_handle.h"
#include "singleton_index_space_iterator.h"

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
// explicit_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::explicit_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::explicit_index_space_handle>(const list_pool<explicit_index_space_handle>& xpool, bool xinclude_shallow);
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
// mutable_index_space_handle
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::list_pool<sheaf::mutable_index_space_handle>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::mutable_index_space_handle>(const list_pool<mutable_index_space_handle>& xpool, bool xinclude_shallow);
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

