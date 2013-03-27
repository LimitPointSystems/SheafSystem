// $RCSfile: index_space_family.inst.cc,v $ $Revision: 1.6 $ $Date: 2013/03/13 00:58:54 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class index_space_family.

#include "index_space_family.impl.h"

#include "section_space_schema_jims_index_space_handle.h"

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

//==============================================================================
// section_space_schema_jims_index_space_handle
//==============================================================================

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<fiber_bundle::section_space_schema_jims_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
fiber_bundle::section_space_schema_jims_index_space_handle&
sheaf::index_space_family::
get_id_space<fiber_bundle::section_space_schema_jims_index_space_handle>(const string& xname) const;

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_family::
handle_conforms_to_state<fiber_bundle::section_space_schema_jims_index_space_handle>(pod_type xid) const;

template
SHEAF_DLL_SPEC
fiber_bundle::section_space_schema_jims_index_space_handle&
sheaf::index_space_family::
get_id_space<fiber_bundle::section_space_schema_jims_index_space_handle>(pod_type xid) const;

