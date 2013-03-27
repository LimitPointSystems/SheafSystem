// $RCSfile: list_pool.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:17 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 
// Explicit instantiations for class list_pool.

#include "list_pool.impl.h"

#include "i_adjacency_implicit_index_space_iterator.h"
#include "i_connectivity_implicit_index_space_iterator.h"
#include "ij_adjacency_implicit_index_space_iterator.h"
#include "ij_connectivity_implicit_index_space_iterator.h"
#include "ijk_adjacency_implicit_index_space_iterator.h"
#include "ijk_connectivity_implicit_index_space_iterator.h"
#include "section_space_schema_jims_index_space_handle.h"
#include "section_space_schema_jims_index_space_iterator.h"

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
