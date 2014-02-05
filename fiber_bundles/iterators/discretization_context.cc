
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

// Implementation for class discretization_context

#include "discretization_context.h"

#include "assert_contract.h"
#include "error_message.h"

using namespace std;

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

std::ostream&
fiber_bundle::
operator<<(std::ostream& xos, const fiber_bundle::discretization_context& xc)
{
  // Preconditions:

  // Body:

  xos << "eval_id  = " << xc.eval_id << endl;
  xos << "local_id = " << xc.local_id << endl;
  xos << "disc_id =  " << xc.disc_id << endl;
  xos << "values =";
  for(int i=0; i<xc.values_ub; ++i)
  {
    xos << "  " << xc.values[i]; 
  }
  xos << endl;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
fiber_bundle::
deep_size(const discretization_context& xc, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}
