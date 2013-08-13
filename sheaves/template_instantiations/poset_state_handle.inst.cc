
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class poset_state_handle.

#include "poset_state_handle.impl.h"

#include "hash_set_filter.h"
#include "set_filter.h"
#include "zn_to_bool_filter.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

template 
SHEAF_DLL_SPEC
void 
sheaf::poset_state_handle::
remove_cover_members<sheaf::hash_set_filter>(const sheaf::hash_set_filter& xfilter,
					     bool xlower,
					     const sheaf::scoped_index& xmbr_index);

template 
SHEAF_DLL_SPEC
void 
sheaf::poset_state_handle::
remove_cover_members<sheaf::hash_set_filter>(const sheaf::hash_set_filter& xfilter,
					     bool xlower,
					     pod_index_type xmbr_hub_id);

template
SHEAF_DLL_SPEC
void
sheaf::poset_state_handle::
remove_cover_members<sheaf::set_filter>(const sheaf::set_filter& xfilter,
					bool xlower,
					const sheaf::scoped_index& xmbr_index);

template
SHEAF_DLL_SPEC
void
sheaf::poset_state_handle::
remove_cover_members<sheaf::set_filter>(const sheaf::set_filter& xfilter,
					bool xlower,
					 pod_index_type xmbr_hub_id);

template 
SHEAF_DLL_SPEC
void 
sheaf::poset_state_handle::
remove_cover_members<sheaf::zn_to_bool_filter>(const sheaf::zn_to_bool_filter& xfilter,
					       bool xlower,
					       const sheaf::scoped_index& xmbr_index);
 
template <typename filter_type>
void remove_cover_members(const filter_type& xfilter,
			    bool xlower,
			    pod_index_type xmbr_hub_id);
