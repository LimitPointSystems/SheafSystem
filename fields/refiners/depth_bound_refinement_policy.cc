// $RCSfile: depth_bound_refinement_policy.cc,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:27 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class depth_bound_refinement_policy

#include "depth_bound_refinement_policy.h"

#include "assert_contract.h"
#include "factory.impl.h"
#include "field_refinement_buffer.h"
#include "field_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// DEPTH_BOUND_REFINEMENT_POLICY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::depth_bound_refinement_policy::
depth_bound_refinement_policy(size_type xrefinement_depth_ub)
    : field_refinement_policy(xrefinement_depth_ub)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(refinement_depth_ub() == xrefinement_depth_ub);


  // Exit:

  return;
}


fields::depth_bound_refinement_policy::
depth_bound_refinement_policy(const depth_bound_refinement_policy& xother)
    : field_refinement_policy(xother)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


fields::depth_bound_refinement_policy::
~depth_bound_refinement_policy()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

bool
fields::depth_bound_refinement_policy::
_has_prototype = make_prototype();

bool
fields::depth_bound_refinement_policy::
make_prototype()
{
  bool result = true;

  // Preconditions:


  // Body:

  depth_bound_refinement_policy* lproto =
    new depth_bound_refinement_policy();

  policy_factory().insert_prototype(lproto);

  // Postconditions:

  ensure(policy_factory().contains_prototype(static_class_name()));

  // Exit:

  return result;
}


// ===========================================================
// FIELD_REFINEMENT_POLICY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::depth_bound_refinement_policy::
should_refine(field_refinement_buffer& xbuffer, size_type xrefinement_depth) const
{
  bool result;

  // Preconditions:

  require(xbuffer.source.state_is_read_accessible());
  require(xbuffer.target.state_is_read_accessible());
  require(xbuffer.target.same_evaluation());

  // Body:

  result = (xrefinement_depth < _refinement_depth_ub);

  // Postconditions:

  ensure( result ? xrefinement_depth < refinement_depth_ub() : true);

  // Exit:

  return result;
}

const string&
fields::depth_bound_refinement_policy::
class_name() const
{

  // Preconditions:


  // Body:

  const string& result = static_class_name();

  // Postconditions:


  // Exit:

  return result;
}

const string&
fields::depth_bound_refinement_policy::
static_class_name()
{

  // Preconditions:


  // Body:

  static const string result("depth_bound_refinement_policy");

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::depth_bound_refinement_policy::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const depth_bound_refinement_policy*>(other) != 0;

  // Postconditions:

  return result;
}

fields::depth_bound_refinement_policy*
fields::depth_bound_refinement_policy::
clone() const
{
  depth_bound_refinement_policy* result;

  // Preconditions:

  // Body:

  result = new depth_bound_refinement_policy(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::depth_bound_refinement_policy&
fields::depth_bound_refinement_policy::
operator=(const field_refinement_policy& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fields::depth_bound_refinement_policy&
fields::depth_bound_refinement_policy::
operator=(const depth_bound_refinement_policy& xother)
{

  // Preconditions:


  // Body:

  _refinement_depth_ub = xother._refinement_depth_ub;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::depth_bound_refinement_policy::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

