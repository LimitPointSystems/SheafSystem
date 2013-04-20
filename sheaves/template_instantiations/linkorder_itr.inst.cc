
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Istantiations for class linkorder_itr<T>.

 
#include "linkorder_itr.impl.h"

#include "zn_to_bool.h"
#include "std_set.h"
#include "std_hash_set.h"

using namespace sheaf; // workaround for MS C++ bug.

//==============================================================================
// zn_to_bool
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::
linkorder_itr<sheaf::zn_to_bool>;

//==============================================================================
// set<pod_index_type>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::
linkorder_itr< set<sheaf::pod_index_type> >;

//==============================================================================
// hash_set<pod_index_type>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::
linkorder_itr< hash_set<sheaf::pod_index_type> >;