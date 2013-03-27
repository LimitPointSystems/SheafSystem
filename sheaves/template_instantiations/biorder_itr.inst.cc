// $RCSfile: biorder_itr.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:49 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Istantiations for class biorder_itr<T>.

 
#include "biorder_itr.impl.h"

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
biorder_itr<sheaf::zn_to_bool>;

//==============================================================================
// set<pod_index_type>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::
biorder_itr< set<sheaf::pod_index_type> >;

//==============================================================================
// hash_set<pod_index_type>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::
biorder_itr< hash_set<sheaf::pod_index_type> >;
