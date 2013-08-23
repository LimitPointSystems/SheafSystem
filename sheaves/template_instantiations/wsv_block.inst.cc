
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
