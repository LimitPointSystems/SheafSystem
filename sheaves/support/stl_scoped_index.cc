

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
 
//

/// @file
/// Implementation for class stl_scoped_index.

#include "stl_scoped_index.h"
#include "assert_contract.h"

using namespace sheaf;

// ===========================================================
// LEXOGRAPHICAL_COMPARE_POLICY
// ===========================================================

bool
sheaf::lexographical_compare_policy::
less_than(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  require(xindex1.is_scoped());
  require(xindex2.is_scoped());

  // Body:

  bool result;

  if(xindex1.scope_id() == xindex2.scope_id())
    result = (xindex1.pod() < xindex2.pod());
  else
    result = (xindex1.scope_id() < xindex2.scope_id());

  // Postconditions:

  ensure((xindex1.scope_id() == xindex2.scope_id()) ?
	 result == xindex1.pod() < xindex2.pod() :
	 (xindex1.scope_id() < xindex2.scope_id()));

  // Exit:

  return result;
}

bool
sheaf::lexographical_compare_policy::
equal(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  // Body:

  bool result = (xindex1 == xindex2);
  
  // Postconditions:

  ensure(result == (xindex1 == xindex2));

  // Exit:

  return result;
}

// ===========================================================
// EQUIVALENCE_COMPARE_POLICY
// ===========================================================

bool
sheaf::equivalence_compare_policy::
less_than(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  require(xindex1.is_scoped());
  require(xindex2.is_scoped());

  // Body:

  bool result = (xindex1 <~ xindex2);

  // Postconditions:

  ensure(result == (xindex1 <~ xindex2));

  // Exit:

  return result;
}

bool
sheaf::equivalence_compare_policy::
equal(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  require(xindex1.is_scoped());
  require(xindex2.is_scoped());

  // Body:

  bool result = (xindex1 ==~ xindex2);
  
  // Postconditions:

  ensure(result == (xindex1 ==~ xindex2));

  // Exit:

  return result;
}
