

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
/// Implementation for class scoped_index

#include "scoped_index.h"

#include "poset_state_handle.h"
#include "std_iomanip.h"

// ===========================================================
// SCOPED_INDEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS
 
sheaf::scoped_index::
scoped_index(const poset_state_handle& xhost, const string& xname)
  : _id_spaces(&xhost.member_id_spaces(false)),
    _scope_id(xhost.member_id_spaces(false).index(xname)),
    _pod(invalid_pod())
{
  // Preconditions:

  require(xhost.state_is_read_accessible());
  require(!xname.empty());
  require(xhost.member_id_spaces(false).contains(xname));
  
  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(id_spaces().name(scope_id()) == xname);
  ensure(&id_spaces() == &xhost.member_id_spaces(false));
  ensure(!is_valid());
  
  // Exit:

  return;
}

sheaf::scoped_index::
scoped_index(pod_type xpod, const poset_state_handle& xhost, const string& xname)
  : _id_spaces(&xhost.member_id_spaces(false)),
    _scope_id(xhost.member_id_spaces(false).index(xname)),
    _pod(xpod)
{
  // Preconditions:

  require(xhost.state_is_read_accessible());
  require(!xname.empty());
  require(xhost.member_id_spaces(false).contains(xname));
  
  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(id_spaces().name(scope_id()) == xname);
  ensure(&id_spaces() == &xhost.member_id_spaces(false));
  ensure(pod() == xpod);
  
  // Exit:

  return;
}

sheaf::scoped_index::
scoped_index(const scoped_index& xother, const poset_state_handle& xhost, const string& xname)
  : _id_spaces(&xhost.member_id_spaces(false)),
    _scope_id(xhost.member_id_spaces(false).index(xname))
{
  // Preconditions:

  require(xhost.state_is_read_accessible());
  require(!xname.empty());
  require(xhost.member_id_spaces(false).contains(xname));
  
  // Body:

  _pod = _id_spaces->pod(_scope_id, xother);

  // Postconditions:

  ensure(invariant());
  ensure(id_spaces().name(scope_id()) == xname);
  ensure(&id_spaces() == &xhost.member_id_spaces(false));
  ensure((*this) ==~ xother);
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream&
sheaf::operator<<(ostream& xos, const scoped_index& xid)
{
  if(xid.is_scoped())
  {
    xos << " (" << xid.scope_id() << ", " << xid.pod()<< ")";
  }
  else
  {
    xos << " (" << invalid_pod_index() << ", " << xid.pod() << ")";
  }
  
  return xos;
}

istream&
sheaf::operator>>(istream& xis, scoped_index& xid)
{
  scoped_index::pod_type lpod;
  xis >> lpod;
  xid.put_pod(lpod);

  return xis;
}

size_t
sheaf::deep_size(const scoped_index& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}


// ===========================================================
// TEMPLATE SPECIALIZATIONS
// ===========================================================

SHEAF_BEGIN_HASH_NAMESPACE

size_t
hash<sheaf::scoped_index>::
operator()(sheaf::scoped_index xindex) const
{
  return xindex.hub_pod();
}

SHEAF_END_HASH_NAMESPACE

