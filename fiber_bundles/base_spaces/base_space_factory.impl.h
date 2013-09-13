
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

// Implementation for class base_space_factory

#ifndef BASE_SPACE_FACTORY_IMPL_H
#define BASE_SPACE_FACTORY_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_FACTORY_H
#include "base_space_factory.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

namespace fiber_bundle
{
  
// =============================================================================
// BASE_SPACE_FACTORY FACET
// =============================================================================

///
template <typename base_type>
base_space_factory<base_type>::
base_space_factory()
{

  // Preconditions:

  // Body:

  path = "";
  schema_path = "";
  local_cell_prototype_path = "";
  index_ubs = "";

  // Postconditions:

  // Exit:

  return;
}


///
template <typename base_type>
base_space_factory<base_type>::
~base_space_factory()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


///
template <typename base_type>
base_space_poset*
base_space_factory<base_type>::
new_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_accessible());
  require(!path.empty());
  require(poset_path::is_valid_name(path.poset_name()));

  // Body:

  base_space_poset* result;

  if(xns.contains_poset(path, false))
  {
    result = dynamic_cast<base_space_poset*>(&xns.member_poset(path, false));
  }
  else
  {
    result = &base_type::standard_host(xns, path.poset_name(), false);
  }

  // Get

  // Postconditions:

  ensure(result->path(true) == path);

  // Exit:

  return result;
}


///
template <typename base_type>
base_type*
base_space_factory<base_type>::
new_base(fiber_bundles_namespace& xns, const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_accessible());
  require(xbase_path.full());

  // Body:

  path = xbase_path.poset_name();

  base_type* result = new_base(xns, xbase_path.member_name());

  // Get

  // Postconditions:

  ensure(result->path(true) == xbase_path);

  // Exit:

  return result;
}


///
template <typename base_type>
base_type*
base_space_factory<base_type>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_accessible());
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)));

  // Body:

  base_type* result = new base_type;

  poset_path lbase_path(path.poset_name(), xbase_name);

  result->attach_to_state(&xns, lbase_path);

  // Get

  // Postconditions:

  ensure(result->path() == poset_path(path.poset_name(), xbase_name));

  // Exit:

  return result;
}




// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

} // namespace fiber_bundle
 
#endif // BASE_SPACE_FACTORY_IMPL_H
