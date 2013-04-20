

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
