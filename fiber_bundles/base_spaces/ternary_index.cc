
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

// Implementation for class ternary_index

#include "SheafSystem/ternary_index.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_iostream.h"


// Member functions all inlined in header file.

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream&
fiber_bundle::
operator<<(std::ostream& xos, const fiber_bundle::ternary_index& xbi)
{
  xos << xbi.i << "," << xbi.j << "," << xbi.k;
  return xos;
}

