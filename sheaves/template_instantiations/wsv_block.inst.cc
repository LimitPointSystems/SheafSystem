// $RCSfile: wsv_block.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:50 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Instantiation for class template wsv_list

#include "wsv_block.impl.h"

using namespace sheaf; // workaround for MS C++ bug.


//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================


template class 
SHEAF_DLL_SPEC
sheaf::wsv_block<bool>;

template class 
SHEAF_DLL_SPEC
sheaf::wsv_block<int>;

template class 
SHEAF_DLL_SPEC
sheaf::wsv_block<double>;

template class 
SHEAF_DLL_SPEC
sheaf::wsv_block<unsigned>;

// $$ISSUE: size_type is typedef'd to unsigned long
// but while MS C++ will tolerate explicit instantiations on both types,
// g++ 4.2.2 will not. This may become a problem if we need an unsigned long
// explicit instantiation.

//template class 
//SHEAF_DLL_SPEC
//sheaf::wsv_block<unsigned long>;

template class 
SHEAF_DLL_SPEC
sheaf::wsv_block<size_type>;

#include "schema_descriptor.h"

template class 
SHEAF_DLL_SPEC
sheaf::wsv_block<sheaf::schema_descriptor>;

// #include "arg_list.h"
// template class wsv_block<arg_list>;
