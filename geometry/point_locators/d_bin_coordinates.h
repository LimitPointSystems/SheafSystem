
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
/// Interface for class d_bin_coordinates

#ifndef D_BIN_COORDINATES_H
#define D_BIN_COORDINATES_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SECTION_EVALUATOR_H
#include "SheafSystem/section_evaluator.h"
#endif

#ifndef SHEAF_H
#include "SheafSystem/sheaf.h"
#endif

#ifndef STD_CMATH_H
#include "SheafSystem/std_cmath.h"
#endif

#ifndef STD_IOSTREAM_H
#include "SheafSystem/std_iostream.h"
#endif

namespace geometry
{

using namespace sheaf;
using namespace fiber_bundle; 

///
/// Fixed point relative coordinates for a tree domain.
///
template <int DC, int DB>
class SHEAF_DLL_SPEC d_bin_coordinates
{

  // ===========================================================
  /// @name D_BIN_COORDINATES FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type used for floating point coordinates.
  ///
  typedef section_evaluator::value_type value_type;

  ///
  /// An unsigned integral type used to represent sizes and capacities.
  ///
  typedef typename sheaf::size_type size_type;

  ///
  /// The type used for integer coordinates.
  ///
  typedef unsigned long long int_type;

  ///
  /// Default constructor
  ///
  d_bin_coordinates();

  ///
  /// Copy constructor
  ///
  d_bin_coordinates(const d_bin_coordinates<DC, DB>& xother);

  ///
  /// Converts xcoord to a d_bin_coordinates
  ///
  d_bin_coordinates(const value_type* xcoord);

  ///
  /// Destructor
  ///
  ~d_bin_coordinates();

  ///
  /// Class invariant.
  ///
  bool invariant() const;

  ///
  /// Assignment from d_bin_coordinates.
  ///
  d_bin_coordinates& operator=(const d_bin_coordinates<DC, DB>& xother);

  ///
  /// Assignment from value_type.
  ///
  d_bin_coordinates& operator=(const value_type* xcoord);

  ///
  /// True if and only if this has the same value as xother.
  ///
  bool operator==(const d_bin_coordinates<DC, DB>& xother) const;

  ///
  /// True if and only if each component of this has the same value as xother.
  ///
  bool operator==(int_type xother) const;

  ///
  /// True if and only if the value of this is less than the value of xother.
  ///
  bool operator<(const d_bin_coordinates<DC, DB>& xother) const;

  ///
  /// True if and only if the value of this is less than
  /// or equal to the value of xother.
  ///
  bool operator<=(const d_bin_coordinates<DC, DB>& xother) const;

  ///
  /// Right shift and assignment of this by xbits.
  ///
  d_bin_coordinates<DC, DB>& operator>>=(int xbits);

  ///
  /// Substraction and assignemnt.
  ///
  d_bin_coordinates& operator-=(const d_bin_coordinates<DC, DB>& xother);

  ///
  /// The branch index at bit position xbit.
  ///
  size_type branch(size_type xbit) const;

  ///
  /// Set the branch index at bit position xbit to xbranch.
  ///
  void put_branch(size_type xbit, size_type xbranch);

  ///
  /// The upper bound for components.
  ///
  static int_type ub();

  ///
  /// The number of bits in a tree coordinate.
  ///
  static size_type bits();

  ///
  /// The index of the leftmost bit.
  ///
  static size_type leftmost_bit_id();

  ///
  /// The index of the rightmost bit.
  ///
  static size_type rightmost_bit_id();

  ///
  /// The degree of the tree this is a coordinate for.
  ///
  static size_type degree();

  ///
  /// The dimension of the tree this is a coordinate for.
  ///
  static size_type dc();

  ///
  /// The value of this as an int_type.
  ///
  const int_type* int_value() const;

  ///
  /// The xi-th coordinate of this.
  ///
  const int_type& operator[](size_type xi) const;

  ///
  /// The xi-th coordinate of this.
  ///
  int_type& operator[](size_type xi);


private:

  ///
  /// Converts xint_value to a d_bin_coordinates
  ///
  d_bin_coordinates(int_type xint_value);

  ///
  /// The representation.
  ///
  int_type _int_value[DC];

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

// #ifndef STD_BITSET_H
// #include "SheafSystem/std_bitset.h"
// #endif

///
/// Insert d_bin_coordinates xcoords in stream xos.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
std::ostream&
operator<<(std::ostream& xos, const d_bin_coordinates<DC, DB>& xcoords);


// ===========================================================
// SPECIALIZATIONS
// ===========================================================

//
// The branch index at bit position xbit (1d specialization).
//
template<>
SHEAF_DLL_SPEC
d_bin_coordinates<1, 1>::size_type
d_bin_coordinates<1, 1>::branch(size_type xbit) const;

//
// Set the branch index at bit position xbit to xbranch (1d specialization).
//
template<>
SHEAF_DLL_SPEC
void
d_bin_coordinates<1, 1>::put_branch(size_type xbit, size_type xbranch);

//
// The branch index at bit position xbit (2d specialization).
//
template<>
SHEAF_DLL_SPEC
d_bin_coordinates<2, 2>::size_type
d_bin_coordinates<2, 2>::branch(size_type xbit) const;

//
// Set the branch index at bit position xbit to xbranch (2d specialization).
//
template<>
SHEAF_DLL_SPEC
void
d_bin_coordinates<2, 2>::put_branch(size_type xbit, size_type xbranch);

//
// The branch index at bit position xbit.
//
template<>
SHEAF_DLL_SPEC
d_bin_coordinates<3, 3>::size_type
d_bin_coordinates<3, 3>::branch(size_type xbit) const;

//
// Set the branch index at bit position xbit to xbranch (3d specialization).
//
template<>
SHEAF_DLL_SPEC
void
d_bin_coordinates<3, 3>::put_branch(size_type xbit, size_type xbranch);

//
// The branch index at bit position xbit (4d specialization).
//
template<>
SHEAF_DLL_SPEC
d_bin_coordinates<4, 4>::size_type
d_bin_coordinates<4, 4>::branch(size_type xbit) const;

//
// Set the branch index at bit position xbit to xbranch (4d specialization).
//
template<>
SHEAF_DLL_SPEC
void
d_bin_coordinates<4, 4>::put_branch(size_type xbit, size_type xbranch);

} // namespace geometry

#endif // ifndef D_BIN_COORDINATES_H
