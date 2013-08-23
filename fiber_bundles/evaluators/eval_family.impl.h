
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

/// @file
/// Member function template definitions for class eval_family.

#ifndef EVAL_FAMILY_IMPL_H
#define EVAL_FAMILY_IMPL_H

template <typename S>
S*
fiber_bundle::eval_family::
member(pod_index_type xtype_id)
{
  // Preconditions:


  // Body:

  S* result = dynamic_cast<S*>(member(xtype_id));

  // Postconditions:


  // Exit:

  return result;
}

template <typename S>
S*
fiber_bundle::eval_family::
member(const poset_state_handle& xhost, pod_index_type xhub_id)
{
  // Preconditions:


  // Body:

  S* result = dynamic_cast<S*>(member(xhost, xhub_id));

  // Postconditions:


  // Exit:

  return result;
}

template <typename S>
S*
fiber_bundle::eval_family::
member(const poset_state_handle& xhost, const scoped_index& xid)
{
  // Preconditions:


  // Body:

  S* result = dynamic_cast<S*>(member(xhost, xid.hub_pod()));

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  

#endif // ifndef EVAL_FAMILY_IMPL_H
