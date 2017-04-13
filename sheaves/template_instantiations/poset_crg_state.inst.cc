
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

// Explicit instantiations for class poset_crg_state.

#include "SheafSystem/poset_crg_state.impl.h"

#include "SheafSystem/array_index_space_handle.h"
#include "SheafSystem/hash_index_space_handle.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/list_index_space_handle.h"
#include "SheafSystem/scattered_insertion_index_space_handle.h"
#include "SheafSystem/offset_index_space_handle.h"
#include "SheafSystem/singleton_index_space_handle.h"
#include "SheafSystem/set_filter.h"
#include "SheafSystem/unordered_set_filter.h"
#include "SheafSystem/zn_to_bool_filter.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

template 
SHEAF_DLL_SPEC
sheaf::array_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::array_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
SHEAF_DLL_SPEC
sheaf::hash_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::hash_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
SHEAF_DLL_SPEC
sheaf::hub_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::hub_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
SHEAF_DLL_SPEC
sheaf::list_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::list_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
SHEAF_DLL_SPEC
sheaf::scattered_insertion_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::scattered_insertion_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
SHEAF_DLL_SPEC
sheaf::offset_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::offset_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
SHEAF_DLL_SPEC
sheaf::singleton_index_space_handle& 
sheaf::poset_crg_state::
get_cover_id_space<sheaf::singleton_index_space_handle>(bool xlower, pod_index_type xmbr_index) const;

template 
void 
sheaf::poset_crg_state::
remove_cover_members<sheaf::unordered_set_filter>(const unordered_set_filter& xfilter,
					     bool xlower,
					     pod_index_type xmbr_index);

template 
void 
sheaf::poset_crg_state::
remove_cover_members<sheaf::set_filter>(const set_filter& xfilter,
					bool xlower,
					pod_index_type xmbr_index);

template 
void 
sheaf::poset_crg_state::
remove_cover_members<sheaf::zn_to_bool_filter>(const zn_to_bool_filter& xfilter,
					       bool xlower,
					       pod_index_type xmbr_index);

