
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

#include "ComLimitPoint/fiber_bundle/fiber_bundle.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.impl.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/sheaf/poset_path.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

///
sheaf::poset_path
fiber_bundle::
standard_section_space_path(const poset_path& xfiber_path,
                            const poset_path& xbase_path)
{
  poset_path result;

  // Preconditions:


  // Body:

  result.put_poset_name(xfiber_path.poset_name() + "_on_" + xbase_path.poset_name());

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());

  // Exit:

  return result;
}

///
sheaf::poset_path
fiber_bundle::
standard_section_space_schema_path(const poset_path& xsection_space_path)
{
  poset_path result;

  // Preconditions:


  // Body:

  result.put_member_name(xsection_space_path.poset_name() + "_schema");
  result.put_poset_name(result.member_name() + "_host");

  // Postconditions:

  ensure(!result.empty());
  ensure( result.full());

  // Exit:

  return result;
}


