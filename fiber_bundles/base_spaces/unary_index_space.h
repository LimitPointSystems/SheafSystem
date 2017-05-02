
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

#ifndef UNARY_INDEX_SPACE_H
#define UNARY_INDEX_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef UNARY_INDEX_H
#include "SheafSystem/unary_index.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef RAGGED_ARRAY_H
#include "SheafSystem/ragged_array.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A bounded domain for unary_index objects.
///
class SHEAF_DLL_SPEC unary_index_space
{
public:
  ///
  /// Upper bound for the i index.
  ///
  unary_index i_size;

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
    invariance(size == i_size);
    return true;
  }


  ///
  /// Creates an instance with bound (0,0).
  ///
  unary_index_space()
  {
    // Preconditions:

    // Body:

    put_bounds(0);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == 0);

    // Exit:

    return;
  };

  ///
  /// Creates an instance with bound (xct).
  ///
  unary_index_space(unary_index xct)
  {
    // Preconditions:

    require(xct >= 0);

    // Body:

    put_bounds(xct);

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xct);

    // Exit:

    return;
  };

  ///
  /// Sets i_size = xct and recomputes size.
  ///
  void put_bounds(unary_index xct = 0)
  {
    // Preconditions:

    // Body:

    i_size = xct;
    size = xct;

    // Postconditions:

    ensure(invariant());
    ensure(i_size == xct);

    // Exit:

    return;
  };

  ///
  /// Sum.
  ///
  unary_index_space operator+(const unary_index_space& xother) const
  {
    // Preconditions:

    // Body:

    unary_index_space result(i_size+xother.i_size);

    // Postconditions:

    ensure(invariant());
    ensure(result.i_size == i_size+xother.i_size);

    // Exit:

    return result;
  };

  ///
  /// Cartesian product.
  ///
  unary_index_space operator*(const unary_index_space& xother) const
  {
    // Preconditions:

    // Body:

    unary_index_space result(i_size*xother.i_size);

    // Postconditions:

    ensure(invariant());
    ensure(result.i_size == i_size*xother.i_size);

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

    bool result = ((0 <= xindex) && (xindex < i_size));

    // Postconditions:

    ensure(result == ((0 <= xindex) && (xindex < i_size)));

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
/// Insert unary_index_space& xbis into ostream& os.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream& os, const unary_index_space& xbis);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle


#endif // ifndef UNARY_INDEX_SPACE_H
