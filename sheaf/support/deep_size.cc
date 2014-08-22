
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

// Implementation for deep_size functions

#include "ComLimitPoint/sheaf/deep_size.impl.h"

size_t
sheaf::deep_size(const std::string& xp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  //
  // @hack This calculation is a guess and should be revisited.
  //

  result += xp.size() * sizeof(char);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

