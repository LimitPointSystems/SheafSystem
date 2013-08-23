
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

// Explicit instantiations for class poset_crg_state.

#include "poset_crg_state.impl.h"

#include "hash_set_filter.h"
#include "set_filter.h"
#include "zn_to_bool_filter.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

template 
void 
sheaf::poset_crg_state::
remove_cover_members<sheaf::hash_set_filter>(const hash_set_filter& xfilter,
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

