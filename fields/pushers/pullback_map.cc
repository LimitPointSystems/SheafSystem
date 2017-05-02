
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
/// Implementation for class discretization_point

#include "SheafSystem/pullback_map.h"

#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream&
fields::operator<<(std::ostream& xos, const pullback_map_entry& xentry)
{

  // Preconditions:

  // Body:

  xos << "disc_id: " << setw(6) << xentry.disc_id << " domain_pt: " << xentry.domain_pt;

  // Postconditions:

  // Exit:

  return xos;
}
