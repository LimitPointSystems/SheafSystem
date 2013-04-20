
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class index_space_family.

#include "index_space_family.impl.h"

#include "forwarding_index_space_handle.h"
#include "explicit_index_space_handle.h"
#include "ij_product_structure.h"
#include "ijk_product_structure.h"
#include "interval_index_space_handle.h"
#include "mutable_index_space_handle.h"
#include "offset_index_space_handle.h"
#include "primary_index_space_handle.h"
#include "reserved_primary_index_space_handle.h"
#include "singleton_index_space_handle.h"
#include "sum_index_space_handle.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

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
