
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
/// Implementation for class chart_point

#include "chart_point.h"

#include "assert_contract.h"
#include "chart_point_1d.h"
#include "chart_point_2d.h"
#include "chart_point_3d.h"
#include "error_message.h"
#include "std_algorithm.h"
#include "std_iomanip.h"
#include "std_sstream.h"

using namespace fiber_bundle; // Workaround for bug in MS C++.

// ===========================================================
// CHART_POINT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::chart_point*
fiber_bundle::chart_point::
new_chart_point(int xdb)
{
  chart_point* result;

  // Preconditions:

  require((1 <= xdb) && (xdb < 4));

  // Body:

  switch(xdb)
  {
  case 1:
    result = new chart_point_1d();
    break;
  case 2:
    result = new chart_point_2d();
    break;
  case 3:
    result = new chart_point_3d();
    break;
  default:
    post_fatal_error_message("Invalid chart point dimension");
    break;
  }

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

fiber_bundle::chart_point::
~chart_point()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

sheaf::pod_index_type
fiber_bundle::chart_point::
chart_id() const
{
  return _chart_id;
}

void
fiber_bundle::chart_point::
put_chart_id(pod_index_type xchart_id)
{
  // Preconditions:

  // Body:

  _chart_id = xchart_id;

  // Postconditions:

  ensure(chart_id() == xchart_id);

  // Exit:

  return;
}

void
fiber_bundle::chart_point::
put_chart_id(const scoped_index& xchart_id)
{
  // Preconditions:

  // Body:

  put_chart_id(xchart_id.hub_pod());

  // Postconditions:

  ensure(chart_id() == xchart_id.hub_pod());

  // Exit:

  return;
}

int
fiber_bundle::chart_point::
db() const
{
  int result = -1; // The dimension of the empty set.

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result >= -1);

  // Exit:

  return result;
}

fiber_bundle::chart_point::coord_type
fiber_bundle::chart_point::
local_coord(int xi) const
{
  coord_type result = 0;

  // Preconditions:

  require((0 <= xi) && (xi < db()));

  // Body:

  is_abstract();


  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::chart_point::
put_local_coord(int xi, coord_type xvalue)
{
  // Preconditions:

  require((0 <= xi) && (xi < db()));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(local_coord(xi), xvalue));

  // Exit:

  return;
}

fiber_bundle::chart_point::coord_type*
fiber_bundle::chart_point::
local_coords()
{
  coord_type* result = 0;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

const fiber_bundle::chart_point::coord_type*
fiber_bundle::chart_point::
local_coords() const
{
  const coord_type* result = 0;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

void
fiber_bundle::chart_point::
put_local_coords(const coord_type* xvalues, size_type xvalues_ub)
{
  // Preconditions:

  require(xvalues != 0);
  require(xvalues_ub >= db());

  // Body:

  for(size_type i=0; i<db(); ++i)
  {
    put_local_coord(i, xvalues[i]);
  }

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, db(), isunordered_or_equals(local_coord(i), xvalues[i]));

  // Exit:

  return;
}

void
fiber_bundle::chart_point::
put_local_coords_zero()
{
  // Preconditions:


  // Body:

  for(size_type i=0; i<db(); ++i)
  {
    put_local_coord(i, 0.0);
  }

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, db(), local_coord(i) == 0.0);

  // Exit:

  return;
}

bool
fiber_bundle::chart_point::
is_valid() const
{
  bool result;

  // Preconditions:

  // Body:

  result = sheaf::is_valid(_chart_id);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::chart_point::
invalidate()
{
  // Preconditions:

  // Body:

  _chart_id = invalid_pod_index();

  for(int i=0; i<db(); ++i)
  {
    put_local_coord(i, 0.0);
  }

  // Postconditions:

  ensure(!is_valid());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::chart_point::
chart_point()
  : _chart_id(invalid_pod_index())
{
  // Preconditions:

  // Body:

  // Does nothing.

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

fiber_bundle::chart_point::
chart_point(const chart_point& xother)
{
  // Preconditions:

  // Body:

  _chart_id = xother._chart_id;

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xother.chart_id());

  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::chart_point::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(any::invariant());

    // The following is unexecutable because db() is pure virtual.

    invariance(unexecutable(db() >= -1));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::chart_point::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const chart_point*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::chart_point&
fiber_bundle::chart_point::
operator=(const chart_point& xother)
{

  // Preconditions:
  
  // Body:

  _chart_id = xother.chart_id();

  int lthis_db = db();
  int lother_db = xother.db();
  int lmin_db = min(lthis_db, lother_db);

  coord_type* lthis_coords = local_coords();
  coord_type* lother_coords = const_cast<chart_point&>(xother).local_coords();

  for(int i=0; i<lmin_db; ++i)
  {
    lthis_coords[i] = lother_coords[i];
  }

  for(int i=lmin_db; i<lthis_db; ++i)
  {
    lthis_coords[i] = 0.0;
  }


  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xother.chart_id());
  ensure_for_all(i, 0, (min(db(), xother.db())), isunordered_or_equals(local_coord(i), xother.local_coord(i)));
  ensure_for_all(i, (min(db(), xother.db())), db(), local_coord(i) == 0.0);

  // Exit

  return *this;
}

bool
fiber_bundle::chart_point::
operator==(const chart_point& xother) const
{

  // Preconditions:

  // Body:

  bool result = (db() == xother.db());

  result = result && (chart_id() == xother.chart_id());

  for(int i=0; result && (i<db()); ++i)
  {
    result = (local_coord(i) == xother.local_coord(i));
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::chart_point::
to_stream(ostream& xos) const
{
  xos << *this;
}

string
fiber_bundle::chart_point::
to_string() const
{
  ostringstream oss;
  oss << *this;
  return oss.str();
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream&
fiber_bundle::
operator<<(ostream& os, const fiber_bundle::chart_point& xpt)
{

  // Preconditions:

  // Body:

  os << setw(6) << xpt.chart_id();

  for(int i=0; i<xpt.db(); i++)
  {
    os  << ", " << setw(10) << xpt.local_coord(i);
  }

  // Postconditions:

  // Exit:

  return os;
}
