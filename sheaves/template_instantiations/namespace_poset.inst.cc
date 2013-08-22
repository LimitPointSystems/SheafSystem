
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#include "namespace_poset.impl.h"
#include "poset.h"
#include "poset_state_handle.h"
#include "refinable_poset.h"

using namespace sheaf; // workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS NAMESPACE_POSET_SCHEMA
//==============================================================================
 
template
SHEAF_DLL_SPEC
sheaf::primitives_poset&
sheaf::namespace_poset::
member_poset<sheaf::primitives_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<sheaf::primitives_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<sheaf::primitives_poset>(const poset_path& xpath, bool xauto_access) const;


//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS PRIMITIVES_POSET_SCHEMA
//==============================================================================
 
template
SHEAF_DLL_SPEC
sheaf::primitives_poset_schema&
sheaf::namespace_poset::
member_poset<sheaf::primitives_poset_schema>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<sheaf::primitives_poset_schema>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<sheaf::primitives_poset_schema>(const poset_path& xpath, bool xauto_access) const;

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS NAMESPACE_POSET_SCHEMA
//==============================================================================
 
template
SHEAF_DLL_SPEC
sheaf::namespace_poset_schema&
sheaf::namespace_poset::
member_poset<sheaf::namespace_poset_schema>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<sheaf::namespace_poset_schema>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<sheaf::namespace_poset_schema>(const poset_path& xpath, bool xauto_access) const;

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS REFINABLE_POSET
//==============================================================================
  
template
SHEAF_DLL_SPEC
sheaf::refinable_poset&
sheaf::namespace_poset::
new_member_poset(const string& xname, const poset_path& xschema_path,
                 const arg_list& xargs, bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::refinable_poset&
sheaf::namespace_poset::
member_poset<sheaf::refinable_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<sheaf::refinable_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<sheaf::refinable_poset>(const poset_path& xpath, bool xauto_access) const;

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS POSET
//==============================================================================
  
template
SHEAF_DLL_SPEC
sheaf::poset&
sheaf::namespace_poset::
new_member_poset<sheaf::poset>(const string& xname, const poset_path& xschema_path, const arg_list& xargs, bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset&
sheaf::namespace_poset::
member_poset<sheaf::poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<sheaf::poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<sheaf::poset>(const poset_path& xpath, bool xauto_access) const;

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS POSET_STATE_HANDLE
//==============================================================================

template
SHEAF_DLL_SPEC
sheaf::poset_state_handle&
sheaf::namespace_poset::
member_poset<sheaf::poset_state_handle>(const sheaf::poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<sheaf::poset_state_handle>(const sheaf::poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<sheaf::poset_state_handle>(const poset_path& xpath, bool xauto_access) const;
