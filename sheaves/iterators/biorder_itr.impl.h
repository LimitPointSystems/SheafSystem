
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
/// Implementation for class biorder_itr

#ifndef BIORDER_ITR_IMPL_H
#define BIORDER_ITR_IMPL_H

#ifndef BIORDER_ITR_H
#include "SheafSystem/biorder_itr.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif


namespace sheaf
{
  
// ===========================================================
// BIORDER_ITR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
biorder_itr<T>::
biorder_itr()
    : filtered_depth_first_itr<T>::filtered_depth_first_itr()
{

  // Preconditions:

  // Body:

  this->initialize_order(depth_first_itr<T>::BIORDER);

  // Postconditions:

  ensure(invariant());
  ensure(!this->is_initialized());

  // Exit

  return;
}

template <typename T>
biorder_itr<T>::
biorder_itr(const biorder_itr& xother)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

template <typename T>
biorder_itr<T>::
~biorder_itr()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

// OTHER CONSTRUCTORS

template <typename T>
biorder_itr<T>::
biorder_itr(const abstract_poset_member& xanchor,
            bool xdown,
            bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xdown, xstrict, depth_first_itr<T>::BIORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
biorder_itr<T>::
biorder_itr(const abstract_poset_member& xanchor,
            const subposet& xfilter,
            bool xdown,
            bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter, xdown, xstrict, depth_first_itr<T>::BIORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
biorder_itr<T>::
biorder_itr(const abstract_poset_member& xanchor,
            pod_index_type xfilter_index,
            bool xdown,
            bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter_index, xdown, xstrict, depth_first_itr<T>::BIORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
biorder_itr<T>::
biorder_itr(const abstract_poset_member& xanchor,
            const scoped_index& xfilter_index,
            bool xdown,
            bool xstrict)
  : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter_index.hub_pod(), xdown, xstrict, depth_first_itr<T>::BIORDER)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

template <typename T>
biorder_itr<T>::
biorder_itr(const abstract_poset_member& xanchor,
            const std::string& xfilter_name,
            bool xdown,
            bool xstrict)
    : filtered_depth_first_itr<T>::filtered_depth_first_itr(xanchor, xfilter_name, xdown, xstrict, depth_first_itr<T>::BIORDER)
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
biorder_itr<T>::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const biorder_itr*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

template <typename T>
biorder_itr<T>*
biorder_itr<T>::
clone() const
{
  biorder_itr* result;

  // Preconditions:

  // Body:

  result = new biorder_itr;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

template <typename T>
bool
biorder_itr<T>::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(filtered_depth_first_itr<T>::invariant());
  invariance(this->order() == depth_first_itr<T>::BIORDER);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


} // namespace sheaf

#endif // ifndef BIORDER_ITR_IMPL_H
