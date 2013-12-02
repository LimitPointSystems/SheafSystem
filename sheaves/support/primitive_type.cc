
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

// Definitions relating to sheaf system primitive types.

#include "primitive_type.h"

#include "assert_contract.h"
#include "error_message.h"
#include "primitive_attributes.h"
#include "std_iomanip.h"

namespace
{
const int PRIMITIVE_TYPE_CT = sheaf::PRIMITIVE_TYPE_END - sheaf::PRIMITIVE_TYPE_BEGIN;

template <typename T>
class alignment
{
public:
  char pad;
  T prim;
};
}

// =============================================================================
// PRIMITIVE TYPES FACET
// =============================================================================

///
sheaf::primitive_type&
sheaf::
operator++(primitive_type& x)
{
  x = (x == PRIMITIVE_TYPE_END) ? PRIMITIVE_TYPE_BEGIN : primitive_type(x+1);
  return x;
};

///
bool
sheaf::
is_primitive_index(pod_index_type xindex)
{
  bool result;

  // Preconditions:

  // Body:

  result = (PRIMITIVE_TYPE_BEGIN <= xindex) && (xindex < PRIMITIVE_TYPE_END);

  // Postconditions:

  // Exit

  return result;
}

///
std::ostream&
sheaf::
operator<<(std::ostream& os, const primitive_type& xpt)
{
  // Preconditions:


  // Body:

  os << primitive_attributes::name(xpt);

  // Postconditions:


  // Exit:

  return os;
}

///
std::istream&
sheaf::
operator>>(std::istream& is, primitive_type& xpt)
{
  // Preconditions:


  // Body:

  string ltmp;
  is >> ltmp;
  xpt = primitive_attributes::id(ltmp);

  // Postconditions:


  // Exit:

  return is;
}


// =============================================================================
// PRIMITIVE DESCRIPTORS FACET
// =============================================================================

///
std::ostream&
sheaf::
operator<<(std::ostream& os, const primitive_descriptor& xpd)
{
  // Preconditions:


  // Body:

  os << setw(4) << xpd.size
  << setw(4) << xpd.alignment
  << setw(4) << xpd.index
  << "  " << primitive_attributes::name(xpd.index);


  // Postconditions:


  // Exit:

  return os;
}










