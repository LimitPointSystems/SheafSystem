
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

//
/// @file
/// Implementation for class avg_section_pusher
// A map from one sec_rep_space to another.
//

#include "avg_section_pusher.h"
#include "assert_contract.h"
#include "sec_ed_invertible.h"

using namespace fields; // Workaround for MS C++ bug.

// =============================================================================
// AVG_SECTION_PUSHER FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::avg_section_pusher::
avg_section_pusher(const sec_rep_space& xdomain,
                   const sec_rep_space& xrange,
                   const geometry::sec_ed_invertible& xdom_coord,
                   const sec_ed& xran_coord,
                   bool xauto_access)
    : section_pusher(xdomain, xrange, xdom_coord, xran_coord, xauto_access)
{
  // Preconditions:

  require(precondition_of(section_pusher(xdomain, xrange, xdom_coord, xran_coord)));

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(section_pusher(xdomain, xrange, xdomain_inverter, xran_coord)));


  // Exit:
}


// PROTECTED MEMBER FUNCTIONS

fields::avg_section_pusher::
avg_section_pusher()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}

void
fields::avg_section_pusher::
extend(sec_vd& result, const scoped_index& xdisc_id)
{
  // Preconditions:

  require(result.state_is_read_write_accessible());
  require(range().schema().discretization().contains_member(xdisc_id));

  // Body:

  // Define result by averaging the values of the source field
  // nearest to the discretization point identified by xdisc_id.

  not_implemented();

  // Postconditions:

  // Exit:
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::avg_section_pusher::
avg_section_pusher(const avg_section_pusher& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  /// @issue does anything need to happen or does section_pusher
  /// handle it all?

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fields::avg_section_pusher::
~avg_section_pusher()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}


bool
fields::avg_section_pusher::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(section_pusher::invariant());

  // Postconditions:

  // Exit

  return result;
}
