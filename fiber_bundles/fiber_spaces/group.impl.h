

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for group facet function templates.


#ifndef GROUP_IMPL_H
#define GROUP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GROUP_H
#include "group.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

namespace fiber_bundle
{

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename G>
sheaf::poset_path
fiber_bundle::group::
standard_host_path(const string& xsuffix)
{
  // Preconditions:

  require(poset_path::is_valid_name(G::static_class_name()));
  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  
  // Body:

  poset_path result(G::static_class_name() + xsuffix, "");

  // Postconditions:

  ensure(result.poset_name() == G::static_class_name() + xsuffix);
  ensure(result.member_name().empty());

  // Exit:

  return result;
}

template <typename G>
bool
fiber_bundle::group::
standard_host_is_available(namespace_type& xns, const string& xsuffix, bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(poset_path::is_valid_name(G::static_class_name()));
  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  
  // Body:

  if(xauto_access)
  {
    xns.get_read_access();
  }

  poset_path lpath = standard_host_path<G>(xsuffix);

  bool result =
    !xns.contains_poset(lpath, false) ||
    xns.contains_poset<typename G::host_type>(lpath, false);

  if(xauto_access)
  {
    xns.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

} // end namespace fiber_bundle

#endif // ifndef GROUP_IMPL_H
