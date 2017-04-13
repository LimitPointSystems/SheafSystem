
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
/// Implementation for class section_pusher_pullback_action

#include "SheafSystem/section_pusher_pullback_action.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/sec_ed_invertible.h"

using namespace std;
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
