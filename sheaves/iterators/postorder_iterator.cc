
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class postorder_iterator

#include "postorder_iterator.h"
#include "assert_contract.h"

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
                   const string& xfilter_name,
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