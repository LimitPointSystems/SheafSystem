// $RCSfile: section_pusher_pullback_action.cc,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:26 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class section_pusher_pullback_action

#include "section_pusher_pullback_action.h"

#include "assert_contract.h"
#include "block.h"
#include "error_message.h"
#include "sec_ed_invertible.h"

using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// SECTION_PUSHER_PULLBACK_ACTION FACET
// ===========================================================

fields::section_pusher_pullback_action::
section_pusher_pullback_action(geometry::sec_ed_invertible& xglobal_coords,
                               pb_map_type& xmap)
    : _domain_coords(xglobal_coords),
    _pb_map(xmap)
{

  // Preconditions:

  require(xglobal_coords.state_is_read_accessible());

  // Body:

  if(!domain_coords().is_invertible())
  {
    // Initialize inversion using defaults.

    domain_coords().initialize_point_locator(false);
  }

  _pb.disc_id.invalidate();
  _pb.domain_pt.put(scoped_index::INVALID(), 0.0, 0.0, 0.0);


  // Postconditions:

  ensure(&domain_coords() == &xglobal_coords);
  ensure(domain_coords().is_invertible());

  // Exit:

  return;
}

fields::section_pusher_pullback_action::
~section_pusher_pullback_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


void
fields::section_pusher_pullback_action::
operator()(const scoped_index& xdisc_id, block<sec_vd_value_type>& xcoords)
{
  // Preconditions:

  require(domain_coords().state_is_read_accessible());
  require(domain_coords().is_invertible());

  // Body:

  _pb.disc_id = xdisc_id;

  // Invert the domain global coordinates to get the pull back of
  // the range discretization point into domain local coordinates.

  _domain_coords.point_at_value_ua(xcoords.base(), xcoords.ub(), _pb.domain_pt);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in pb push action: coords: ";
  for(int i=0; i< xcoords.ct(); ++i)
  {
    cout << setw(10) << xcoords[i];
  }
  cout << " pb map entry:" << _pb << endl;
#endif

  // Insert the pullback in the pullback map.

  _pb_map.insert(_pb);

  // Postconditions:


  // Exit:

  return;
}

geometry::sec_ed_invertible&
fields::section_pusher_pullback_action::
domain_coords( )
{
  // Preconditions:

  // Body:

  geometry::sec_ed_invertible& result = _domain_coords;

  // Postconditions:

  // Exit:

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
