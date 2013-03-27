// $RCSfile: poset_crg_state.inst.cc,v $ $Revision: 1.4 $ $Date: 2013/03/13 00:59:08 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

