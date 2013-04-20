
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef TERNARY_INDEX_SPACE_H
#define TERNARY_INDEX_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TERNARY_INDEX_H
#include "ternary_index.h"
#endif

#ifndef RAGGED_ARRAY_H
#include "ragged_array.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A bounded domain for ternary_index objects.
///
class SHEAF_DLL_SPEC ternary_index_space
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
  /// Upper bound for the third index.
  ///
  unary_index k_size;

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
    invariance(k_size >= 0);
    invariance(size == i_size*j_size*k_size);
    return true;
  }


  ///
  /// Creates an instance with bound (0,0,0).
  ///
  ternary_index_space()
  {
    // Preconditions:

    // Body:

    put_bounds(0, 0, 0);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == 0);
    ensure(j_size == 0);
    ensure(k_size == 0);

    // Exit:

    return;
  };

  ///
  /// Creates an instance with bound (xi_size, xj_size, xk_size).
  ///
  ternary_index_space(unary_index xi_size, unary_index xj_size, unary_index xk_size)
  {
    // Preconditions:

    require(xi_size >= 0);
    require(xj_size >= 0);
    require(xk_size >= 0);

    // Body:

    put_bounds(xi_size, xj_size, xk_size);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xi_size);
    ensure(j_size == xj_size);
    ensure(k_size == xk_size);

    // Exit:

    return;
  };

  ///
  /// Sets i_size = xi_size, j_size = xj_size, k_size = xk_size and recomputes size.
  ///
  void put_bounds(unary_index xi_size, unary_index xj_size, unary_index xk_size)
  {
    // Preconditions:

    // Body:

    i_size = xi_size;
    j_size = xj_size;
    k_size = xk_size;
    size = i_size*j_size*k_size;

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xi_size);
    ensure(j_size == xj_size);
    ensure(k_size == xk_size);

    // Exit:

    return;
  };

  ///
  /// Conversion from unary_index; interpreted as cube.
  ///
  ternary_index_space(unary_index xl)
  {
    // Preconditions:

    // Body:

    put_bounds(xl, xl, xl);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xl);
    ensure(j_size == xl);
    ensure(k_size == xl);

    // Exit:

    return;
  };

  ///
  /// Sum.
  ///
  ternary_index_space operator+(const ternary_index_space& xother) const
  {
    // Preconditions:

    // Body:

    ternary_index_space result(i_size+xother.i_size,
                               j_size+xother.j_size,
                               k_size+xother.k_size);

    // Postconditions:

    ensure(invariant());
    ensure(result.i_size == i_size+xother.i_size);
    ensure(result.j_size == j_size+xother.j_size);
    ensure(result.k_size == k_size+xother.k_size);

    // Exit:

    return result;
  };

  ///
  /// Cartesian product.
  ///
  ternary_index_space operator*(const ternary_index_space& xother) const
  {
    // Preconditions:

    // Body:

    ternary_index_space result(i_size*xother.i_size,
                               j_size*xother.j_size,
                               k_size*xother.k_size);

    // Postconditions:

    ensure(invariant());
    ensure(result.i_size == i_size*xother.i_size);
    ensure(result.j_size == j_size*xother.j_size);
    ensure(result.k_size == k_size*xother.k_size);

    // Exit:

    return result;
  };

  ///
  /// True if xindex is in this space.
  ///
  bool contains(const ternary_index& xindex) const
  {
    // Preconditions:

    // Body:

    bool result =
      ((0 <= xindex.i) && (xindex.i < i_size) &&
       (0 <= xindex.j) && (xindex.j < j_size) &&
       (0 <= xindex.k) && (xindex.k < k_size));

    // Postconditions:

    ensure(result ==
           ((0 <= xindex.i) && (xindex.i < i_size) &&
            (0 <= xindex.j) && (xindex.j < j_size) &&
            (0 <= xindex.k) && (xindex.k < k_size)));

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
  unary_index to_row_major_offset(const ternary_index& xindex) const
  {
    // Preconditions:

    // Body:

    unary_index result = xindex.k + k_size*(xindex.j + j_size*xindex.i);

    // Postconditions:

    ensure(result == (xindex.i*j_size*k_size + xindex.j*k_size + xindex.k));

    // Exit:

    return result;
  };

  ///
  /// Converts (xi, xj, xk) to a unary_index using row-major ordering.
  ///
  unary_index to_row_major_offset(const unary_index xi, const unary_index xj, const unary_index xk) const
  {
    // Preconditions:

    // Body:

    unary_index result = xk + k_size*(xj + j_size*xi);

    // Postconditions:

    ensure(result == (xi*j_size*k_size + xj*k_size + xk));

    // Exit:

    return result;
  };

  ///
  /// Converts xindex to a ternary_index using row-major ordering.
  ///
  ternary_index from_row_major_offset(const unary_index& xindex) const
  {
    // Preconditions:

    require((0 <= xindex) && (xindex < size));

    // Body:

    // offset = k_size*j_size*i + k_size*j + k;

    // Precondition ensures 0 <= i < i_size.

    ternary_index result(xindex/(k_size*j_size), (xindex/k_size)%j_size, xindex%k_size);

    // Postconditions:

    ensure(to_row_major_offset(result) == xindex );

    // Exit:

    return result;
  };

  ///
  /// Converts xindex to a unary_index using col-major ordering.
  ///
  unary_index to_col_major_offset(const ternary_index& xindex) const
  {
    // Preconditions:

    // Body:

    unary_index result = xindex.i + i_size*(xindex.j + j_size*xindex.k);

    // Postconditions:

    ensure(result == (xindex.i + i_size*xindex.j + i_size*j_size*xindex.k));

    // Exit:

    return result;
  };

  ///
  /// Converts xindex to a unary_index using col-major ordering.
  ///
  unary_index to_col_major_offset(const unary_index xi, const unary_index xj, const unary_index xk) const
  {
    // Preconditions:

    // Body:

    unary_index result = xi + i_size*(xj + j_size*xk);

    // Postconditions:

    ensure(result == (xi + i_size*xj + i_size*j_size*xk));

    // Exit:

    return result;
  };

  ///
  /// Converts xindex to a ternary_index using col-major ordering.
  ///
  ternary_index from_col_major_offset(const unary_index& xindex) const
  {
    // Preconditions:

    require((0 <= xindex) && (xindex < size));

    // Body:

    // offset = i + i_size*j + i_size*j_size*k;

    // Precondition ensures 0 <= i < i_size.

    ternary_index result(xindex%i_size, (xindex/i_size)%j_size, xindex/(i_size*j_size));

    // Postconditions:

    ensure(to_row_major_offset(result) == xindex);

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
/// Insert ternary_index_space& xbis into ostream& os.
///
SHEAF_DLL_SPEC ostream& operator<<(ostream& os, const ternary_index_space& xbis);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle

#endif // ifndef TERNARY_INDEX_SPACE_H
