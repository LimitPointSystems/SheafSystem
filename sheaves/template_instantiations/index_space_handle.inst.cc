
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

// Explicit instantiations for class index_space_handle.

#include "index_space_handle.impl.h"

#include "ij_product_structure.h"
#include "ijk_product_structure.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

//==============================================================================
// ij_product_structure
//==============================================================================

template
SHEAF_DLL_SPEC
const sheaf::ij_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ij_product_structure>() const;

template
SHEAF_DLL_SPEC
sheaf::ij_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ij_product_structure>();

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_handle::
product_structure_conforms_to<sheaf::ij_product_structure>() const; 

//==============================================================================
// ijk_product_structure
//==============================================================================

template
SHEAF_DLL_SPEC
const sheaf::ijk_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ijk_product_structure>() const;

template
SHEAF_DLL_SPEC
sheaf::ijk_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ijk_product_structure>();

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_handle::
product_structure_conforms_to<sheaf::ijk_product_structure>() const; 
