

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class local_base_space_member.

#include "local_base_space_member.h"

#include "chart_point.h"
#include "namespace_poset.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "assert_contract.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// LOCAL_BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::chart_point*
fiber_bundle::local_base_space_member::
refine_point(const chart_point& xpt) const
{
  chart_point* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xpt.db() == db());

  // Body:

  /// @todo remove when clone();

  chart_point& lpt = const_cast<chart_point&>(xpt);

  result = lpt.clone();
  refine_point_pa(xpt, *result);

  // Postconditions:

  ensure(covers(result->chart_id()));

  // Exit:

  return result;
}

void
fiber_bundle::local_base_space_member::
refine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(result.is_same_type(&xpt));

  require(xpt.chart_id() == index().pod());

  require(xpt.db() == db());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(covers(result.chart_id()));

  // Exit:

  return;
}

fiber_bundle::chart_point*
fiber_bundle::local_base_space_member::
unrefine_point(const chart_point& xpt) const
{
  chart_point* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(covers(xpt.chart_id()));
  require(xpt.db() == db());


  // Body:

  /// @todo remove when clone();

  chart_point& lpt = const_cast<chart_point&>(xpt);

  result = lpt.clone();
  unrefine_point_pa(xpt, *result);

  // Postconditions:

  ensure(result->chart_id() == index().pod());

  // Exit:

  return result;
}

void
fiber_bundle::local_base_space_member::
unrefine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  require(covers(xpt.chart_id()));

  require(result.is_same_type(&xpt));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result.chart_id() == index().pod());

  // Exit:

  return;
}

void
fiber_bundle::local_base_space_member::
refine()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!is_jim());

  // Exit:

  return;
}


void
fiber_bundle::local_base_space_member::
unrefine()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_jim());

  // Exit:

  return;
}

void
fiber_bundle::local_base_space_member::
simplify()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!is_jim());

  // Exit:

  return;
}

void
fiber_bundle::local_base_space_member::
unsimplify()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_jim());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::local_base_space_member::
local_base_space_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// TOTAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::local_base_space_member::
invariant() const
{
  // Preconditions:

  // Body:

  // Must satisfy base class invariant


  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(base_space_member::invariant());

    /// @issue what are the invariants for this class
    /// @todo implement local_base_space_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

bool
fiber_bundle::local_base_space_member::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const local_base_space_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::local_base_space_member&
fiber_bundle::local_base_space_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

fiber_bundle::local_base_space_member&
fiber_bundle::local_base_space_member::
operator=(const local_base_space_member& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body

  not_implemented();
  
  // Postconditions

  ensure(invariant());

  // Exit

  return *this;
  
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
