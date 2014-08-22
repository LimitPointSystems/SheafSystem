
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
/// Explicit instantiations for class depth_first_itr.
 

#include "ComLimitPoint/sheaf/depth_first_itr.impl.h"

using namespace std;
using namespace unordered;

// =============================================================================
// MEMBER FUNCTION SPECIALIZATIONS
// =============================================================================

// =============================================================================
// ZN_TO_BOOL
// =============================================================================


#include "ComLimitPoint/sheaf/zn_to_bool.h"

template <>
void
sheaf::depth_first_itr<sheaf::zn_to_bool>::
clear_has_visited()
{
  _has_visited->make_false_sa();
}

template <>
void
sheaf::depth_first_itr<sheaf::zn_to_bool>::
reserve_has_visited(pod_index_type xub)
{
  _has_visited->extend_to(xub);
}

template <>
bool
sheaf::depth_first_itr<sheaf::zn_to_bool>::
has_visited(pod_index_type xindex) const
{

  // Preconditions:

  require(is_initialized());
  require(anchor().host()->contains_member(xindex, true));

  // Body:

  bool result = (*_has_visited)[xindex];

  return result;
}

template <>
void
sheaf::depth_first_itr<sheaf::zn_to_bool>::
initialize_has_visited(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  if(_has_visited != 0)
  {
    delete _has_visited;
  }

  _has_visited = new zn_to_bool(xanchor.host()->member_index_ub().pod());

  // Postconditions:

  ensure(_has_visited != 0);
  ensure(is_done());

  // Exit

  return;
}

template <>
void
sheaf::depth_first_itr<sheaf::zn_to_bool>::
put_has_visited(pod_index_type xindex, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().host()->contains_member(xindex, true));

  // Body:

  _has_visited->put(xindex, xvalue);

  // Postconditions:

  ensure(has_visited(xindex) == xvalue);

  return;
}

// =============================================================================
// SET
// =============================================================================

#include "std_set.h"

template <>
void
sheaf::depth_first_itr< std::set<sheaf::pod_index_type> >::
clear_has_visited()
{
  _has_visited->clear();
}

template <>
void
sheaf::depth_first_itr< std::set<sheaf::pod_index_type> >::
reserve_has_visited(sheaf::pod_index_type xub)
{
  // No action required.
}

template <>
bool
sheaf::depth_first_itr< std::set<sheaf::pod_index_type> >::
has_visited(pod_index_type xindex) const
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xindex));

  // Body:

  bool result =
    (_has_visited->find(xindex) != _has_visited->end());

  return result;
}

template <>
void
sheaf::depth_first_itr< std::set<sheaf::pod_index_type> >::
initialize_has_visited(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  if(_has_visited != 0)
  {
    delete _has_visited;
  }

  _has_visited = new std::set<pod_index_type>;

  // Postconditions:

  ensure(_has_visited != 0);
  ensure(is_done());

  // Exit

  return;
}

template <>
void
sheaf::depth_first_itr< std::set<sheaf::pod_index_type> >::
put_has_visited(pod_index_type xindex, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xindex));

  // Body:

  if(xvalue)
  {
    _has_visited->insert(xindex);
  }
  else
  {
    _has_visited->erase(xindex);
  }

  // Postconditions:

  ensure(has_visited(xindex) == xvalue);

  return;
}

// =============================================================================
// UNORDERED_SET
// =============================================================================

#include "std_unordered_set.h"

template <>
void
sheaf::depth_first_itr< unordered::unordered_set<sheaf::pod_index_type> >::
clear_has_visited()
{
  _has_visited->clear();
}

template <>
void
sheaf::depth_first_itr< unordered::unordered_set<sheaf::pod_index_type> >::
reserve_has_visited(pod_index_type xub)
{
  // Assume bucket load factor of 2.

  _has_visited->rehash(xub/2);
}

template <>
bool
sheaf::depth_first_itr< unordered::unordered_set<sheaf::pod_index_type> >::
has_visited(pod_index_type xindex) const
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xindex));

  // Body:

  bool result =
    (_has_visited->find(xindex) != _has_visited->end());

  return result;

}

template <>
void
sheaf::depth_first_itr< unordered::unordered_set<sheaf::pod_index_type> >::
initialize_has_visited(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  if(_has_visited != 0)
  {
    delete _has_visited;
  }

  _has_visited = new unordered_set<pod_index_type>;

  // Postconditions:

  ensure(_has_visited != 0);
  ensure(is_done());

  // Exit

  return;
}

template <>
void
sheaf::depth_first_itr< unordered::unordered_set<sheaf::pod_index_type> >::
put_has_visited(pod_index_type xindex, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xindex));

  // Body:

  if(xvalue)
  {
    _has_visited->insert(xindex);
  }
  else
  {
    _has_visited->erase(xindex);
  }

  // Postconditions:

  ensure(has_visited(xindex) == xvalue);

  return;
}

