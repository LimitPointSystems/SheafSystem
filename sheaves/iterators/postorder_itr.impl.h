

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class postorder_itr

#ifndef POSTORDER_ITR_IMPL_H
#define POSTORDER_ITR_IMPL_H

#ifndef POSTORDER_ITR_H
#include "postorder_itr.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif


namespace sheaf
{
  
// ===========================================================
// POSTORDER_ITR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
postorder_itr<T>::
postorder_itr()
    : filtered_depth_first_itr<T>::filtered_depth_first_itr()
{
  // Preconditions:

  // Body:

  this->initialize_order(depth_first_itr<T>::POSTORDER);

  // Postconditions:

  ensure(invariant());
  ensure(!this->is_initialized());

  // Exit

  return;
}

template <typename T>
postorder_itr<T>::
postorder_itr(const postorder_itr& xother)
    :  filtered_depth_first_itr<T>::filtered_depth_first_itr(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

template <typename T>
postorder_itr<T>::
~postorder_itr()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

// OTHER CONSTRUCTORS

template <typename T>
postorder_itr<T>::
postorder_itr(const abstract_poset_member& xanchor,
              bool xdown,
              bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xdown, xstrict, depth_first_itr<T>::POSTORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
postorder_itr<T>::
postorder_itr(const abstract_poset_member& xanchor,
              const subposet& xfilter,
              bool xdown,
              bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter, xdown, xstrict, depth_first_itr<T>::POSTORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
postorder_itr<T>::
postorder_itr(const abstract_poset_member& xanchor,
              pod_index_type xfilter_index,
              bool xdown,
              bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter_index, xdown, xstrict, depth_first_itr<T>::POSTORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
postorder_itr<T>::
postorder_itr(const abstract_poset_member& xanchor,
              const scoped_index& xfilter_index,
              bool xdown,
              bool xstrict)
  : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter_index.hub_pod(), xdown, xstrict, depth_first_itr<T>::POSTORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
postorder_itr<T>::
postorder_itr(const abstract_poset_member& xanchor,
              const string& xfilter_name,
              bool xdown,
              bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter_name, xdown, xstrict, depth_first_itr<T>::POSTORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
bool
postorder_itr<T>::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const postorder_itr*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

template <typename T>
postorder_itr<T>*
postorder_itr<T>::
clone() const
{
  postorder_itr* result;

  // Preconditions:

  // Body:

  result = new postorder_itr;

  // Postconditions:

  ensure(result != 0);
  ensure(this->is_same_type(result));
  ensure(!result->is_initialized());

  // Exit

  return result;
}

template <typename T>
bool
postorder_itr<T>::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(filtered_depth_first_itr<T>::invariant());
  invariance(this->order() == depth_first_itr<T>::POSTORDER);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


} // namespace sheaf

#endif // ifndef POSTORDER_ITR_IMPL_H
