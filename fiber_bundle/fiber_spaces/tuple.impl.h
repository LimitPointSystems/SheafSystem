
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

/// @file
/// Implementation for tuple facet function templates.


#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TUPLE_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_TUPLE_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TUPLE_H
#include "ComLimitPoint/fiber_bundle/tuple.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_FIBER_BUNDLE_NAMESPACE_H
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#endif

namespace fiber_bundle
{

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename F>
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path(const std::string& xsuffix)
{
  // Preconditions:

  require(poset_path::is_valid_name(F::static_class_name()));
  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  
  // Body:

  poset_path result(F::static_class_name() + xsuffix, "");

  // Postconditions:

  ensure(result.poset_name() == F::static_class_name() + xsuffix);
  ensure(result.member_name().empty());

  // Exit:

  return result;
}

template <typename F>
bool
fiber_bundle::tuple::
standard_host_is_available(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(poset_path::is_valid_name(F::static_class_name()));
  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  
  // Body:

  if(xauto_access)
  {
    xns.get_read_access();
  }

  poset_path lpath = standard_host_path<F>(xsuffix);

  bool result =
    !xns.contains_poset(lpath, false) ||
    xns.contains_poset<typename F::host_type>(lpath, false);

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

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_TUPLE_IMPL_H
