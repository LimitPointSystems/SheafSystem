
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Specializations for class d_bin_coordinates,

#include "d_bin_coordinates.impl.h"

#include "std_iostream.h"

using namespace geometry; // Workaround for MS C++ bug.

//==============================================================================
// SPECIALIZATIONS
//==============================================================================

template<>
geometry::d_bin_coordinates<1, 1>::size_type
geometry::d_bin_coordinates<1, 1>::
branch(d_bin_coordinates<1, 1>::size_type xbit) const
{
  d_bin_coordinates<1, 1>::size_type result;

  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;

  result = (_int_value[0] & lbranch_mask) ? 1 : 0;

  // Postconditions:

  ensure(result < degree());

  // Exit:

  return result;
}

template<>
void
geometry::d_bin_coordinates<1, 1>::
put_branch(d_bin_coordinates<1, 1>::size_type xbit, d_bin_coordinates<1, 1>::size_type xbranch)
{
  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));
  require(xbranch < degree());

  // Body:

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;
  int_type lnot_branch_mask = ~lbranch_mask;

  _int_value[0] =
    (xbranch & 1) ? _int_value[0] | lbranch_mask : _int_value[0] & lnot_branch_mask;

  // Postconditions:

  ensure(branch(xbit) == xbranch);

  // Exit:

  return;
}

template<>
geometry::d_bin_coordinates<2, 2>::size_type
geometry::d_bin_coordinates<2, 2>::
branch(d_bin_coordinates<2, 2>::size_type xbit) const
{
  d_bin_coordinates<2, 2>::size_type result;

  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;

  result = (_int_value[0] & lbranch_mask) ? 2 : 0;
  result = (_int_value[1] & lbranch_mask) ? result + 1 : result;

  // Postconditions:

  ensure(result < degree());

  // Exit:

  return result;
}

template<>
void
geometry::d_bin_coordinates<2, 2>::
put_branch(d_bin_coordinates<2, 2>::size_type xbit, d_bin_coordinates<2, 2>::size_type xbranch)
{
  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));
  require(xbranch < degree());

  // Body:

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;
  int_type lnot_branch_mask = ~lbranch_mask;

  _int_value[0] =
    (xbranch & 2) ? _int_value[0] | lbranch_mask : _int_value[0] & lnot_branch_mask;
  _int_value[1] =
    (xbranch & 1) ? _int_value[1] | lbranch_mask : _int_value[1] & lnot_branch_mask;

  // Postconditions:

  ensure(branch(xbit) == xbranch);

  // Exit:

  return;
}

template<>
geometry::d_bin_coordinates<3, 3>::size_type
geometry::d_bin_coordinates<3, 3>::
branch(d_bin_coordinates<3, 3>::size_type xbit) const
{
  d_bin_coordinates<3, 3>::size_type result;

  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;

  result = (_int_value[0] & lbranch_mask) ? 4 : 0;
  result = (_int_value[1] & lbranch_mask) ? result + 2 : result;
  result = (_int_value[2] & lbranch_mask) ? result + 1 : result;

  // Postconditions:

  ensure(result < degree());

  // Exit:

  return result;
}

template<>
void
geometry::d_bin_coordinates<3, 3>::
put_branch(d_bin_coordinates<3, 3>::size_type xbit, d_bin_coordinates<3, 3>::size_type xbranch)
{
  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));
  require(xbranch < degree());

  // Body:

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;
  int_type lnot_branch_mask = ~lbranch_mask;

  _int_value[0] =
    (xbranch & 4) ? _int_value[0] | lbranch_mask : _int_value[0] & lnot_branch_mask;
  _int_value[1] =
    (xbranch & 2) ? _int_value[1] | lbranch_mask : _int_value[1] & lnot_branch_mask;
  _int_value[2] =
    (xbranch & 1) ? _int_value[2] | lbranch_mask : _int_value[2] & lnot_branch_mask;

  // Postconditions:

  ensure(branch(xbit) == xbranch);

  // Exit:

  return;
}

template<>
geometry::d_bin_coordinates<4, 4>::size_type
geometry::d_bin_coordinates<4, 4>::
branch(d_bin_coordinates<4, 4>::size_type xbit) const
{
  d_bin_coordinates<4, 4>::size_type result;

  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;

  result = (_int_value[0] & lbranch_mask) ? 8 : 0;
  result = (_int_value[1] & lbranch_mask) ? result +4 : result;
  result = (_int_value[2] & lbranch_mask) ? result + 2 : result;
  result = (_int_value[3] & lbranch_mask) ? result + 1 : result;

  // Postconditions:

  ensure(result < degree());

  // Exit:

  return result;
}

template<>
void
geometry::d_bin_coordinates<4, 4>::
put_branch(d_bin_coordinates<4, 4>::size_type xbit, d_bin_coordinates<4, 4>::size_type xbranch)
{
  // Preconditions:

  require((rightmost_bit_id() <= xbit) && (xbit <= leftmost_bit_id()));
  require(xbranch < degree());

  // Body:

  int_type lbranch_mask = static_cast<int_type>(1) << xbit;
  int_type lnot_branch_mask = ~lbranch_mask;

  _int_value[0] =
    (xbranch & 8) ? _int_value[0] | lbranch_mask : _int_value[0] & lnot_branch_mask;
  _int_value[1] =
    (xbranch & 4) ? _int_value[1] | lbranch_mask : _int_value[1] & lnot_branch_mask;
  _int_value[2] =
    (xbranch & 2) ? _int_value[2] | lbranch_mask : _int_value[2] & lnot_branch_mask;
  _int_value[3] =
    (xbranch & 1) ? _int_value[3] | lbranch_mask : _int_value[3] & lnot_branch_mask;

  // Postconditions:

  ensure(branch(xbit) == xbranch);

  // Exit:

  return;
}
