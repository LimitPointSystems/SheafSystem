
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

// Explicit instantiations for class index_space_family.

#include "ComLimitPoint/sheaf/index_space_family.impl.h"

#include "ComLimitPoint/sheaf/array_index_space_handle.h"
#include "ComLimitPoint/sheaf/explicit_index_space_handle.h"
#include "ComLimitPoint/sheaf/forwarding_index_space_handle.h"
#include "ComLimitPoint/sheaf/hash_index_space_handle.h"
#include "ComLimitPoint/sheaf/hub_index_space_handle.h"
#include "ComLimitPoint/sheaf/ij_product_structure.h"
#include "ComLimitPoint/sheaf/ijk_product_structure.h"
#include "ComLimitPoint/sheaf/interval_index_space_handle.h"
#include "ComLimitPoint/sheaf/list_index_space_handle.h"
#include "ComLimitPoint/sheaf/mutable_index_space_handle.h"
#include "ComLimitPoint/sheaf/offset_index_space_handle.h"
#include "ComLimitPoint/sheaf/primary_index_space_handle.h"
#include "ComLimitPoint/sheaf/reserved_primary_index_space_handle.h"
#include "ComLimitPoint/sheaf/singleton_index_space_handle.h"
#include "ComLimitPoint/sheaf/sum_index_space_handle.h"

using namespace std;
using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

//==============================================================================
// array_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::array_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::array_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::array_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::array_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::array_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::array_index_space_handle>(pod_type xid) const;

//==============================================================================
// explicit_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::explicit_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::explicit_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::explicit_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::explicit_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::explicit_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::explicit_index_space_handle>(pod_type xid) const;

//==============================================================================
// forwarding_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::forwarding_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::forwarding_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::forwarding_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::forwarding_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::forwarding_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::forwarding_index_space_handle>(pod_type xid) const;

//==============================================================================
// hash_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::hash_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::hash_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::hash_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::hash_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::hash_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::hash_index_space_handle>(pod_type xid) const;

//==============================================================================
// hub_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::hub_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::hub_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::hub_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::hub_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::hub_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::hub_index_space_handle>(pod_type xid) const;

//==============================================================================
// ij_product_structure
//==============================================================================

template
SHEAF_DLL_SPEC
const sheaf::ij_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ij_product_structure>(const string& xname) const;

template
SHEAF_DLL_SPEC
const sheaf::ij_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ij_product_structure>(pod_type xspace_id) const;

template
SHEAF_DLL_SPEC
sheaf::ij_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ij_product_structure>(const string& xname);

template
SHEAF_DLL_SPEC
sheaf::ij_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ij_product_structure>(pod_type xspace_id);

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
product_structure_conforms_to<sheaf::ij_product_structure>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
product_structure_conforms_to<sheaf::ij_product_structure>(pod_type xspace_id) const; 

//==============================================================================
// ijk_product_structure
//==============================================================================

template
SHEAF_DLL_SPEC
const sheaf::ijk_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ijk_product_structure>(const string& xname) const;

template
SHEAF_DLL_SPEC
const sheaf::ijk_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ijk_product_structure>(pod_type xspace_id) const;

template
SHEAF_DLL_SPEC
sheaf::ijk_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ijk_product_structure>(const string& xname);

template
SHEAF_DLL_SPEC
sheaf::ijk_product_structure&
sheaf::index_space_family::
product_structure<sheaf::ijk_product_structure>(pod_type xspace_id);

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
product_structure_conforms_to<sheaf::ijk_product_structure>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
product_structure_conforms_to<sheaf::ijk_product_structure>(pod_type xspace_id) const; 

//==============================================================================
// interval_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::interval_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::interval_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::interval_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::interval_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::interval_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::interval_index_space_handle>(pod_type xid) const;

//==============================================================================
// list_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::list_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::list_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::list_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::list_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::list_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::list_index_space_handle>(pod_type xid) const;

//==============================================================================
// mutable_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::mutable_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::mutable_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::mutable_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::mutable_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::mutable_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::mutable_index_space_handle>(pod_type xid) const;

//==============================================================================
// offset_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::offset_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::offset_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::offset_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::offset_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::offset_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::offset_index_space_handle>(pod_type xid) const;

//==============================================================================
// primary_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::primary_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::primary_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::primary_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::primary_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::primary_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::primary_index_space_handle>(pod_type xid) const;

//==============================================================================
// reserved_primary_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::reserved_primary_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::reserved_primary_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::reserved_primary_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::reserved_primary_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::reserved_primary_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::reserved_primary_index_space_handle>(pod_type xid) const;

//==============================================================================
// singleton_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::singleton_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::singleton_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::singleton_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::singleton_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::singleton_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::singleton_index_space_handle>(pod_type xid) const;

//==============================================================================
// sum_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::sum_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
sheaf::sum_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::sum_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<sheaf::sum_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
sheaf::sum_index_space_handle&
sheaf::index_space_family::
get_id_space<sheaf::sum_index_space_handle>(pod_type xid) const;

