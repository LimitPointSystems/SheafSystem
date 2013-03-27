// $RCSfile: d_bin_coordinates.impl.h,v $ $Revision: 1.5 $ $Date: 2013/01/12 17:17:30 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class d_bin_coordinates

#ifndef D_BIN_COORDINATES_IMPL_H
#define D_BIN_COORDINATES_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef D_BIN_COORDINATES_H
#include "d_bin_coordinates.h"
#endif

#ifndef STD_BITSET_H
#include "std_bitset.h"
#endif

#ifndef STD_LIMITS_H
#include "std_limits.h"
#endif

namespace geometry
{
  
// ============================================================================
// D_BIN_COORDINATES FACET
// ============================================================================

template <int DC, int DB>
d_bin_coordinates<DC, DB>::
d_bin_coordinates()
{
  for(int i=0; i<DC; ++i)
  {
    _int_value[i] = 0;
  }

  // Postconditions:

  ensure(invariant());
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>::
d_bin_coordinates(const d_bin_coordinates<DC, DB>& xother)
{
  // Preconditions:

  require(precondition_of(operator=(xother)));

  // Body:

  *this = xother;

  // Postconditions:

  ensure(postcondition_of(operator=(xother)));
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>::
d_bin_coordinates(const value_type* xcoord)
{
  // Preconditions:

  require(precondition_of(operator=(xcoord)));

  // Body:

  *this = xcoord;

  // Postconditions:

  ensure(postcondition_of(operator=(xcoord)));
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>::
~d_bin_coordinates()
{}

template <int DC, int DB>
bool
d_bin_coordinates<DC, DB>::
invariant() const
{
  bool result = true;

  // The main reason for this existence
  // of this class is to maintain the
  // following invariance:

  invariance_for_all(i, 0, DC, int_value()[i] < ub());

  return result;
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>&
d_bin_coordinates<DC, DB>::
operator=(const d_bin_coordinates<DC, DB>& xother)
{
  for(int i=0; i<DC; ++i)
  {
    _int_value[i] = xother._int_value[i];
  }

  // Postconditions:

  ensure(invariant());

  return *this;
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>&
d_bin_coordinates<DC, DB>::
operator=(const value_type* xcoord)
{
  // Preconditions:

  require_for_all(i, 0, DC, 0.0 <= xcoord[i]);
  require_for_all(i, 0, DC, floor(xcoord[i]) < ub());

  // Body:

  for(int i=0; i<DC; ++i)
  {
    _int_value[i] = static_cast<int_type>(xcoord[i]);
  }

  // Postcondition:

  ensure(invariant());

  return *this;
}

template <int DC, int DB>
bool
d_bin_coordinates<DC, DB>::
operator==(const d_bin_coordinates<DC, DB>& xother) const
{
  bool result = true;
  for(int i=0; i<DC; ++i)
  {
    result = result && (_int_value[i] == xother._int_value[i]);
  }

  return result;
}

template <int DC, int DB>
bool
d_bin_coordinates<DC, DB>::
operator==(int_type xother) const
{
  bool result = true;
  for(int i=0; i<DC; ++i)
  {
    result = result && (_int_value[i] == xother);
  }

  return result;
}

template <int DC, int DB>
bool
d_bin_coordinates<DC, DB>::
operator<(const d_bin_coordinates<DC, DB>& xother) const
{
  bool result = true;
  for(int i=0; i<DC; ++i)
  {
    result = result && (_int_value[i] < xother._int_value[i]);
  }

  return result;
}

template <int DC, int DB>
bool
d_bin_coordinates<DC, DB>::
operator<=(const d_bin_coordinates<DC, DB>& xother) const
{
  bool result = true;
  for(int i=0; i<DC; ++i)
  {
    result = result && (_int_value[i] <= xother._int_value[i]);
  }

  return result;
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>&
d_bin_coordinates<DC, DB>::
operator>>=(int xbits)
{
  // Preconditions:

  require(xbits < bits());

  // Body:

  for(int i=0; i<DC; ++i)
  {
    _int_value[i] >>= xbits;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>&
d_bin_coordinates<DC, DB>::
operator-=(const d_bin_coordinates<DC, DB>& xother)
{
  // Preconditions:

  // Body:

  for(int i=0; i<DC; ++i)
  {
    _int_value[i] -= xother._int_value[i];
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

template <int DC, int DB>
size_type
d_bin_coordinates<DC, DB>::
branch(size_type xbit) const
{
  size_type result = 0;

  // Preconditions:

  // Implemented below for specialized values of DC=1, 2, 3 & 4.

  not_implemented();

  // Postconditions:

  // Exit:

  return result;
}

template <int DC, int DB>
void
d_bin_coordinates<DC, DB>::
put_branch(size_type xbit, size_type xbranch)
{
  // Preconditions:

  // Body:

  // Implemented below for specialized values of DC=1, 2, 3 & 4.

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}

template <int DC, int DB>
typename d_bin_coordinates<DC, DB>::int_type
d_bin_coordinates<DC, DB>::
ub()
{
  // Comparison and intersection logic in class octree_path
  // requires positions to have leftmost bit = 0.

  static const int_type result =
    static_cast<int_type>(1) << (numeric_limits<int_type>::digits - 1);

  return result;
}

template <int DC, int DB>
typename d_bin_coordinates<DC, DB>::size_type
d_bin_coordinates<DC, DB>::
bits()
{
  static const size_type result = numeric_limits<int_type>::digits;
  return result;
}

template <int DC, int DB>
size_type
d_bin_coordinates<DC, DB>::
leftmost_bit_id()
{
  return bits() - 1;
}

/// The index of the rightmost bit.
template <int DC, int DB>
size_type
d_bin_coordinates<DC, DB>::
rightmost_bit_id()
{
  return 0;
}

template <int DC, int DB>
size_type
d_bin_coordinates<DC, DB>::
degree()
{
  return 1<<DC;
}

template <int DC, int DB>
size_type
d_bin_coordinates<DC, DB>::
dc()
{
  return DC;
}

template <int DC, int DB>
const typename d_bin_coordinates<DC, DB>::int_type*
d_bin_coordinates<DC, DB>::
int_value() const
{
  return _int_value;
}

template <int DC, int DB>
const typename d_bin_coordinates<DC, DB>::int_type&
d_bin_coordinates<DC, DB>::
operator[](size_type xi) const
{
  // Preconditions:

  require(xi < DC);

  // Body:

  return _int_value[xi];
}

template <int DC, int DB>
typename d_bin_coordinates<DC, DB>::int_type&
d_bin_coordinates<DC, DB>::
operator[](size_type xi)
{
  // Preconditions:

  require(xi < DC);

  // Body:

  return _int_value[xi];
}

template <int DC, int DB>
d_bin_coordinates<DC, DB>::
d_bin_coordinates(int_type xint_value)
{
  // Preconditions:

  require(xint_value < ub());

  // Body:

  for(int i=0; i<DC; ++i)
  {
    _int_value[i] = xint_value;
  }

  // Postconditions:

  ensure(invariant());
}

} // namespace geometry

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <int DC, int DB>
ostream& geometry::operator<<(ostream& xos, const geometry::d_bin_coordinates<DC, DB>& xcoords)
{
  for(int i=0; i<xcoords.dc(); ++i)
  {
    xos << " "
    << bitset<numeric_limits<typename d_bin_coordinates<DC, DB>::int_type>
    ::digits>(xcoords.int_value()[i]);
  }
  return xos;
}
#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif // ifndef D_BIN_COORDINATES_IMPL_H
