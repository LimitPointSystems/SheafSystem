
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

// Implementation for class preorder_iterator

#include "preorder_iterator.h"
#include "assert_contract.h"

sheaf::preorder_iterator::
preorder_iterator()
    : filtered_depth_first_iterator()
{

  // Preconditions:

  // Body:

  initialize_order(PREORDER);

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

sheaf::preorder_iterator::
preorder_iterator(const preorder_iterator& xother)
    : filtered_depth_first_iterator(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::preorder_iterator::
~preorder_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

}


bool
sheaf::preorder_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const preorder_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::preorder_iterator*
sheaf::preorder_iterator::
clone() const
{
  preorder_iterator* result;

  // Preconditions:

  // Body:

  result = new preorder_iterator;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
sheaf::preorder_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(filtered_depth_first_iterator::invariant());
  invariance(order()==PREORDER);

  // Postconditions:

  // Exit

  return result;
}

// OTHER CONSTRUCTORS

sheaf::preorder_iterator::
preorder_iterator(const abstract_poset_member& xanchor,
                  bool xdown,
                  bool xstrict)
    : filtered_depth_first_iterator(xanchor, xdown, xstrict, PREORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::preorder_iterator::
preorder_iterator(const abstract_poset_member& xanchor,
                  const subposet& xfilter,
                  bool xdown,
                  bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter, xdown, xstrict, PREORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::preorder_iterator::
preorder_iterator(const abstract_poset_member& xanchor,
                  pod_index_type xfilter_index,
                  bool xdown,
                  bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_index, xdown, xstrict, PREORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::preorder_iterator::
preorder_iterator(const abstract_poset_member& xanchor,
                  const scoped_index& xfilter_index,
                  bool xdown,
                  bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_index, xdown, xstrict, PREORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::preorder_iterator::
preorder_iterator(const abstract_poset_member& xanchor,
                  const string& xfilter_name,
                  bool xdown,
                  bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_name, xdown, xstrict, PREORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}
