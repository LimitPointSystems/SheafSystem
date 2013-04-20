

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class chart_point_3d

#include "chart_point_3d.h"
#include "assert_contract.h"

using namespace fiber_bundle; // Workaround for bug in MS C++.

// ===========================================================
// CHART_POINT_3D FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::chart_point_3d::
chart_point_3d()
{
  // Preconditions:

  // Body:

  _chart_id = invalid_pod_index();

  // Postconditions:

  ensure(invariant());
  ensure(!is_valid());

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::
chart_point_3d(const chart_point_3d& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::
~chart_point_3d()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::
chart_point_3d(pod_index_type xchart_id,
               coord_type xu,
               coord_type xv,
               coord_type xw)
{
  // Preconditions:

  // Body:

  _chart_id = xchart_id;
  _local_coords[0] = xu;
  _local_coords[1] = xv;
  _local_coords[2] = xw;

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xchart_id);
  ensure(isunordered_or_equals(u(), xu));
  ensure(isunordered_or_equals(v(), xv));
  ensure(isunordered_or_equals(w(), xw));

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::
chart_point_3d(const scoped_index& xchart_id,
               coord_type xu,
               coord_type xv,
               coord_type xw)
{
  // Preconditions:

  // Body:

  _chart_id = xchart_id.hub_pod();
  _local_coords[0] = xu;
  _local_coords[1] = xv;
  _local_coords[2] = xw;

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xchart_id.hub_pod());
  ensure(isunordered_or_equals(u(), xu));
  ensure(isunordered_or_equals(v(), xv));
  ensure(isunordered_or_equals(w(), xw));

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::
chart_point_3d(pod_index_type xchart_id,
               const coord_type* xlocal_coords,
               size_type xlocal_coords_ub)
{

  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  _chart_id = xchart_id;
  put_local_coords(xlocal_coords, xlocal_coords_ub);

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xchart_id);
  ensure_for_all(i, 0, db(), isunordered_or_equals(local_coord(i), xlocal_coords[i]));

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::
chart_point_3d(const scoped_index& xchart_id,
               const coord_type* xlocal_coords,
               size_type xlocal_coords_ub)
{

  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  _chart_id = xchart_id.hub_pod();
  put_local_coords(xlocal_coords, xlocal_coords_ub);

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xchart_id.hub_pod());
  ensure_for_all(i, 0, db(), isunordered_or_equals(local_coord(i), xlocal_coords[i]));

  // Exit:

  return;
}

int
fiber_bundle::chart_point_3d::
db() const
{
  int result;

  // Preconditions:

  // Body:

  result = 3;

  // Postconditions:

  ensure(result == 3);

  // Exit:

  return result;
}

fiber_bundle::chart_point_3d::coord_type
fiber_bundle::chart_point_3d::
local_coord(int xi) const
{
  coord_type result;

  // Preconditions:

  require((0 <= xi) && (xi < db()));

  // Body:

  result = _local_coords[xi];

  // Postconditions:

  /// @todo uncomment when invariant changed to invariant() const;
  ///  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::chart_point_3d::
put_local_coord(int xi, coord_type xvalue)
{
  // Preconditions:

  require((0 <= xi) && (xi < db()));

  // Body:

  _local_coords[xi] = xvalue;

  // Postconditions:

  /// @todo uncomment when invariant changed to invariant() const;
  ///  ensure(invariant());

    ensure(isunordered_or_equals(local_coord(xi), xvalue));

  // Exit:

  return;
}

fiber_bundle::chart_point_3d::coord_type*
fiber_bundle::chart_point_3d::
local_coords()
{
  coord_type* result;

  // Preconditions:

  // Body:

  result = _local_coords;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

const fiber_bundle::chart_point_3d::coord_type*
fiber_bundle::chart_point_3d::
local_coords() const
{
  const coord_type* result;

  // Preconditions:


  // Body:

  result = _local_coords;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

const fiber_bundle::chart_point_3d::coord_type&
fiber_bundle::chart_point_3d::
u() const
{

  // Preconditions:

  // Body:

  const coord_type& result = _local_coords[0];

  // Postconditions:

  /// @todo uncomment when invariant changed to invariant() const;
  ///  ensure(invariant());

    ensure(isunordered_or_equals(result, local_coord(0)));

  // Exit:

  return result;
}

const fiber_bundle::chart_point_3d::coord_type&
fiber_bundle::chart_point_3d::
v() const
{
  // Preconditions:

  // Body:

  const coord_type& result = _local_coords[1];

  // Postconditions:

  /// @todo uncomment when invariant changed to invariant() const;
  ///  ensure(invariant());

    ensure(isunordered_or_equals(result,  local_coord(1)));

  // Exit:

  return result;
}

const fiber_bundle::chart_point_3d::coord_type&
fiber_bundle::chart_point_3d::
w() const
{
  // Preconditions:

  // Body:

  const coord_type& result = _local_coords[2];

  // Postconditions:

  /// @todo uncomment when invariant changed to invariant() const;
  ///  ensure(invariant());

    ensure(isunordered_or_equals(result, local_coord(2)));

  // Exit:

  return result;
}

void
fiber_bundle::chart_point_3d::
put(pod_index_type xchart_id, coord_type xu, coord_type xv, coord_type xw)
{
  // Preconditions:

  // Body:

  _chart_id = xchart_id;
  _local_coords[0] = xu;
  _local_coords[1] = xv;
  _local_coords[2] = xw;

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xchart_id);
  ensure(isunordered_or_equals(u(), xu));
  ensure(isunordered_or_equals(v(), xv));
  ensure(isunordered_or_equals(w(), xw));

  // Exit:

  return;
}

void
fiber_bundle::chart_point_3d::
put(const scoped_index& xchart_id, coord_type xu, coord_type xv, coord_type xw)
{
  // Preconditions:

  // Body:

  put(xchart_id.hub_pod(), xu, xv, xw);

  // Postconditions:

  ensure(invariant());
  ensure(chart_id() == xchart_id.hub_pod());
  ensure(isunordered_or_equals(u(), xu));
  ensure(isunordered_or_equals(v(), xv));
  ensure(isunordered_or_equals(w(), xw));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// CHART_POINT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::chart_point_3d*
fiber_bundle::chart_point_3d::
clone() const
{
  chart_point_3d* result;

  // Preconditions:

  // Body:

  result = new chart_point_3d();

  // Postconditions:

  ensure(result->is_same_type(this));

  // Exit:

  return result;
}

bool
fiber_bundle::chart_point_3d::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(chart_point::invariant());
    invariance(db() == 3);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::chart_point_3d::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const chart_point_3d*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::chart_point_3d&
fiber_bundle::chart_point_3d::
operator=(const chart_point_3d& xother)
{
  // Preconditions:
  
  // Body:

  _chart_id = xother._chart_id;
  _local_coords[0] = xother._local_coords[0];
  _local_coords[1] = xother._local_coords[1];
  _local_coords[2] = xother._local_coords[2];

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(*this == xother));

  // Exit

  return *this;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

size_t
fiber_bundle::
deep_size(const chart_point_3d& xvalue, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}


