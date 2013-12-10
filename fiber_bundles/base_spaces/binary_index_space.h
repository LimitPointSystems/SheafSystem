
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

#ifndef BINARY_INDEX_SPACE_H
#define BINARY_INDEX_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BINARY_INDEX_H
#include "binary_index.h"
#endif

#ifndef RAGGED_ARRAY_H
#include "ragged_array.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A bounded domain for binary_index objects.
///
class SHEAF_DLL_SPEC binary_index_space
{
public:
  ///
  /// Upper bound for the first index.
  ///
  unary_index i_size;

  ///
  /// Upper bound for the second index.
  ///
  unary_index j_size;

  ///
  /// Number in the space.
  ///
  unary_index size;

  ///
  /// Class invariant.
  ///
  bool invariant() const
  {
    invariance(i_size >= 0);
    invariance(j_size >= 0);
    invariance(size == i_size*j_size);
    return true;
  }


  ///
  /// Creates an instance with bound (0,0).
  ///
  binary_index_space()
  {
    // Preconditions:

    // Body:

    put_bounds(0, 0);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == 0);
    ensure(j_size == 0);

    // Exit:

    return;
  };

  ///
  /// Creates an instance with bounds (xi_size, xj_size).
  ///
  binary_index_space(unary_index xi_size, unary_index xj_size)
  {
    // Preconditions:

    require(xi_size >= 0);
    require(xj_size >= 0);

    // Body:

    put_bounds(xi_size, xj_size);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xi_size);
    ensure(j_size == xj_size);

    // Exit:

    return;
  };

  ///
  /// Sets i_size = xi_size and j_size = xj_size and recomputes size.
  ///
  void put_bounds(unary_index xi_size = 0, unary_index xj_size = 0)
  {
    // Preconditions:

    // Body:

    i_size = xi_size;
    j_size = xj_size;
    size = i_size*j_size;

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xi_size);
    ensure(j_size == xj_size);

    // Exit:

    return;
  };

  ///
  /// Conversion from unary_index; interpreted as square.
  ///
  binary_index_space(unary_index xl)
  {
    // Preconditions:

    // Body:

    put_bounds(xl, xl);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xl);
    ensure(j_size == xl);

    // Exit:

    return;
  };

  ///
  /// Sum.
  ///
  binary_index_space operator+(const binary_index_space& xother) const
  {
    // Preconditions:

    // Body:

    binary_index_space result(i_size+xother.i_size, j_size+xother.j_size);

    // Postconditions:

    ensure(invariant());
    ensure(result.i_size == i_size+xother.i_size);
    ensure(result.j_size == j_size+xother.j_size);

    // Exit:

    return result;
  };

  ///
  /// Cartesian product.
  ///
  binary_index_space operator*(const binary_index_space& xother) const
  {
    // Preconditions:

    // Body:

    binary_index_space result(i_size*xother.i_size, j_size*xother.j_size);

    // Postconditions:

    ensure(invariant());
    ensure(result.i_size == i_size*xother.i_size);
    ensure(result.j_size == j_size*xother.j_size);

    // Exit:

    return result;
  };

  ///
  /// True if xindex is in this space.
  ///
  bool contains(const binary_index& xindex) const
  {
    // Preconditions:

    // Body:

    bool result =
      ((0 <= xindex.i) && (xindex.i < i_size) &&
       (0 <= xindex.j) && (xindex.j < j_size));

    // Postconditions:

    ensure(result ==
           ((0 <= xindex.i) && (xindex.i < i_size) &&
            (0 <= xindex.j) && (xindex.j < j_size)));

    // Exit:

    return result;
  };

  ///
  /// True if xindex is in this space.
  ///
  bool contains(const unary_index& xindex) const
  {
    // Preconditions:

    // Body:

    bool result = ((0 <= xindex) && (xindex < size));

    // Postconditions:

    ensure( result == ((0 <= xindex) && (xindex < size)));

    // Exit:

    return result;
  };

  ///
  /// Converts xindex to a unary_index using row-major ordering.
  ///
  unary_index to_row_major_offset(const binary_index& xindex) const
  {
    // Preconditions:

    // Body:

    unary_index result = j_size*xindex.i+ xindex.j;

    // Postconditions:

    ensure(result == (j_size*xindex.i+ xindex.j));

    // Exit:

    return result;
  };

  ///
  /// Converts (xi, xj) to a unary_index using row-major ordering.
  ///
  unary_index to_row_major_offset(const unary_index xi, const unary_index xj) const
  {
    // Preconditions:

    // Body:

    unary_index result = xj + j_size*xi;

    // Postconditions:

    ensure(result == (xi*j_size + xj));

    // Exit:

    return result;
  };

  ///
  /// Converts xindex to a binary_index using row-major ordering.
  ///
  binary_index from_row_major_offset(const unary_index& xindex) const
  {
    // Preconditions:

    // Body:

    binary_index result(xindex/j_size, xindex%j_size);

    // Postconditions:

    ensure(to_row_major_offset(result) == xindex );

    // Exit:

    return result;
  };

  ///
  /// Create a ragged array containing the row major offsets
  /// of the neighbors of each index in the index space.
  ///
  ragged_array<unary_index>* neighbor_list() const;
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert binary_index_space& xbis into ostream& os.
///
SHEAF_DLL_SPEC 
std::ostream& operator<<(std::ostream& os, const binary_index_space& xbis);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle

#endif // ifndef BINARY_INDEX_SPACE_H
