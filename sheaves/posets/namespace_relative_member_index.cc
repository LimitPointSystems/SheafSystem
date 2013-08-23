
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

// Implementation for class NAMESPACE_RELATIVE_MEMBER_INDEX

// Most of the implementation is inline in namespace_relative_member_index.h

#include "namespace_relative_member_index.h"

ostream&
sheaf::operator<<(ostream& xos, const namespace_relative_member_index& xindex)
{
  // Preconditions:

  // Body:

  xos << xindex.poset_id << " " << xindex.member_id ;

  // Postconditions:

  // Exit:

  return xos;
}

istream&
sheaf::operator>>(istream& xis, namespace_relative_member_index& xindex)
{
  // Preconditions:

  // Body:

  scoped_index lposet_id, lmember_id;

  // Extract "poset_id member_id", checking each step so
  // when we return the stream state properly represents any failure.
  // In particular, the stream state should properly distinguish
  // a syntax or conversion failure from an end-of-file.
  //
  // Note that skipws may or may not be set, so we explicitly
  // skip white space to make sure it is dealt with properly.
  //
  // Also note that this operator does not modify xindex unless
  // the extraction succeeeds.

  if((xis >> ws >> lposet_id) && (xis >> ws >> lmember_id))
  {
    // Converted poset and member id successfully; set result.

    xindex.poset_id = lposet_id;
    xindex.member_id = lmember_id;
  }
  else
  {
    // Couldn't read poset and/or member id, set fail bit..

    xis.setstate(ios_base::failbit);
  }

  // Postconditions:

  // Exit:

  return xis;
}

