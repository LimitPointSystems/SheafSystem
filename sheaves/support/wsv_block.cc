
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

// Instantiation for class template wsv_list

#include "wsv_block.impl.h"

using namespace std;

using namespace sheaf; // workaround for MS C++ bug.


//=============================================================================
// MEMBER FUNCTION SPECIALIZATIONS
//=============================================================================

// Specialization for T == bool:

//$$SCRIBBLE: This specialization requires that all lower
//            case is used in xlist; eg: "true false" as
//            opposed to  "TRUE FALSE"". This limitation
//            could be eliminated with a "bool to_bool(string)"
//            function.

template <>
wsv_block<bool>&
wsv_block<bool>::
operator=(const std::string& xlist)
{
  // Preconditions:

  // Body:

  stringstream lval_stream;
  lval_stream.str(xlist);

  bool lval;
  while(lval_stream >> boolalpha >> lval)
  {
    push_back(lval);
  }

  // Postconditions:

  ensure(!xlist.empty() ? this->ct() > 0 : true);

  // Exit:

  return *this;
}

