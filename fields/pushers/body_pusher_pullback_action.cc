// $RCSfile: body_pusher_pullback_action.cc,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:26 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class body_pusher_pullback_action

#include "body_pusher_pullback_action.h"

#include "assert_contract.h"
#include "block.h"
#include "error_message.h"
#include "sec_ed_invertible.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// BODY_PUSHER_PULLBACK_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::body_pusher_pullback_action::
body_pusher_pullback_action(geometry::sec_ed_invertible& xglobal_coords, pb_map_type& xmap)
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

  // Reserve some initial space in _domain_pts; will resize if needed.

  _domain_pts.reserve(32);

  // Postconditions:

  ensure(&domain_coords() == &xglobal_coords);
  ensure(domain_coords().is_invertible());

  // Exit:

  return;
}

fields::body_pusher_pullback_action::
~body_pusher_pullback_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


void
fields::body_pusher_pullback_action::
operator()(const scoped_index& xdisc_id, block<sec_vd_value_type>& xcoords)
{
  // Preconditions:

  require(domain_coords().state_is_read_accessible());
  require(domain_coords().is_invertible());

  // Body:

  // Invert the domain global coordinates to get the pull back of
  // the range discretization point into domain local coordinates.

  _domain_pts.set_ct(0);
  _domain_coords.all_points_at_value_ua(xcoords.base(), xcoords.ub(), _domain_pts);

  _pb.disc_id = xdisc_id;

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in body pusher pb action: disc id = " << xdisc_id;

  cout << "\tcoords: ";
  for(int i=0; i< xcoords.ct(); ++i)
  {
    cout << setw(10) << xcoords[i];
  }

  cout << "\tpb ct = " << _domain_pts.ct() << endl;
#endif

  for(size_type i=0; i<_domain_pts.ct(); ++i)
  {
    _pb.domain_pt = _domain_pts[i];

#ifdef DIAGNOSTIC_OUTPUT

    cout << "\tpb map entry: " << _pb << endl;
#endif

    // Insert the pullback in the pullback map.

    _pb_map.insert(_pb);

  }


  // Postconditions:


  // Exit:

  return;
}

geometry::sec_ed_invertible&
fields::body_pusher_pullback_action::
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
