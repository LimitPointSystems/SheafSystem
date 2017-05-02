
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

// Implementation for class biorder_iterator

#include "SheafSystem/biorder_iterator.h"
#include "SheafSystem/assert_contract.h"

sheaf::biorder_iterator::
biorder_iterator()
    : filtered_depth_first_iterator()
{

  // Preconditions:

  // Body:

  initialize_order(BIORDER);

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

sheaf::biorder_iterator::
biorder_iterator(const biorder_iterator& xother)
    : filtered_depth_first_iterator(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::biorder_iterator::
~biorder_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

}


bool
sheaf::biorder_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const biorder_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::biorder_iterator*
sheaf::biorder_iterator::
clone() const
{
  biorder_iterator* result;

  // Preconditions:

  // Body:

  result = new biorder_iterator;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
sheaf::biorder_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(filtered_depth_first_iterator::invariant());
  invariance(order()==BIORDER);

  // Postconditions:

  // Exit

  return result;
}

// OTHER CONSTRUCTORS


sheaf::biorder_iterator::
biorder_iterator(const abstract_poset_member& xanchor,
                 bool xdown,
                 bool xstrict)
    : filtered_depth_first_iterator(xanchor, xdown, xstrict, BIORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::biorder_iterator::
biorder_iterator(const abstract_poset_member& xanchor,
                 const subposet& xfilter,
                 bool xdown,
                 bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter, xdown, xstrict, BIORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::biorder_iterator::
biorder_iterator(const abstract_poset_member& xanchor,
                 pod_index_type xfilter_index,
                 bool xdown,
                 bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_index, xdown, xstrict, BIORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::biorder_iterator::
biorder_iterator(const abstract_poset_member& xanchor,
                 const scoped_index& xfilter_index,
                 bool xdown,
                 bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_index, xdown, xstrict, BIORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::biorder_iterator::
biorder_iterator(const abstract_poset_member& xanchor,
                 const std::string& xfilter_name,
                 bool xdown,
                 bool xstrict)
    : filtered_depth_first_iterator(xanchor, xfilter_name, xdown, xstrict, BIORDER)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}
