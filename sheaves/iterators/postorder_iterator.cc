
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

// Implementation for class postorder_iterator

#include "SheafSystem/postorder_iterator.h"
#include "SheafSystem/assert_contract.h"

sheaf::postorder_iterator::
postorder_iterator()
    : filtered_depth_first_iterator()
{

  // Preconditions:

  // Body:

  initialize_order(POSTORDER);

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

sheaf::postorder_iterator::
postorder_iterator(const postorder_iterator& xother)
    : filtered_depth_first_iterator(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::postorder_iterator::
~postorder_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

}


bool
sheaf::postorder_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const postorder_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::postorder_iterator*
sheaf::postorder_iterator::
clone() const
{
  postorder_iterator* result;

  // Preconditions:

  // Body:

  result = new postorder_iterator;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
sheaf::postorder_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(filtered_depth_first_iterator::invariant());
  invariance(order()==POSTORDER);

  // Postconditions:

  // Exit

  return result;
}

// OTHER CONSTRUCTORS

sheaf::postorder_iterator::
postorder_iterator(const abstract_poset_member& xanchor,
                   bool xdown,
                   bool xstrict)
    : filtered_depth_first_iterator(xanchor, xdown, xstrict, POSTORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::postorder_iterator::
postorder_iterator(const abstract_poset_member& xanchor,
                   const subposet& xfilter,
                   bool xdown,
                   bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter, xdown, xstrict, POSTORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::postorder_iterator::
postorder_iterator(const abstract_poset_member& xanchor,
                   pod_index_type xfilter_index,
                   bool xdown,
                   bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_index, xdown, xstrict, POSTORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::postorder_iterator::
postorder_iterator(const abstract_poset_member& xanchor,
                   const scoped_index& xfilter_index,
                   bool xdown,
                   bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_index, xdown, xstrict, POSTORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::postorder_iterator::
postorder_iterator(const abstract_poset_member& xanchor,
                   const std::string& xfilter_name,
                   bool xdown,
                   bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_name, xdown, xstrict, POSTORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}
