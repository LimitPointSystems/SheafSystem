
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

// Interface for class ternary_index

#ifndef TERNARY_INDEX_H
#define TERNARY_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef UNARY_INDEX_H
#include "unary_index.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

namespace fiber_bundle
{
  
///
/// A triple of indices (i,j, k).
///
class SHEAF_DLL_SPEC ternary_index
{
public:

  ///
  /// The first index.
  ///
  unary_index i;

  ///
  /// The second index.
  ///
  unary_index j;

  ///
  /// The third index.
  ///
  unary_index k;

  ///
  /// Default Constructor; creates an instance with i == j == k == 0;
  ///
  ternary_index()
  {
    // Preconditions:

    // Body:

    i = 0;
    j = 0;
    k = 0;

    // Postconditions:

    ensure(i == 0);
    ensure(j == 0);
    ensure(k == 0);

    // Exit:

    return;
  };

  ///
  /// Creates an instance with i == xi, j == xj, k == xk.
  ///
  ternary_index(unary_index xi, unary_index xj, unary_index xk)
  {
    // Preconditions:

    // Body:

    i = xi;
    j = xj;
    k = xk;

    // Postconditions:

    ensure(i == xi);
    ensure(j == xj);
    ensure(k == xk);

    // Exit:

    return;
  };

  //
  // Copy constructor not defined;
  // uses default memberwise initialization
  //

  //
  // Assignment operator not defined;
  // uses default memberwise assignment.
  //

  //
  // Destructor not defined;
  // uses default memberwise destruction.
  //

  ///
  /// Sum.
  ///
  ternary_index operator+(const ternary_index& xother) const
  {
    // Preconditions:

    // Body:

    ternary_index result(i+xother.i, j+xother.j, k+xother.k);

    // Postconditions:

    ensure(result.i = i + xother.i);
    ensure(result.j = j + xother.j);
    ensure(result.k = k + xother.k);

    // Exit:

    return result;
  };

  ///
  /// Self-allocated sum.
  ///
  ternary_index& operator+=(const ternary_index& xother)
  {
    // Preconditions:

    // Body:

    define_old_variable(unary_index old_i = i);
    define_old_variable(unary_index old_j = j);
    define_old_variable(unary_index old_k = k);

    i += xother.i;
    j += xother.j;
    k += xother.k;

    // Postconditions:

    ensure(i = old_i + xother.i);
    ensure(j = old_j + xother.j);
    ensure(k = old_k + xother.k);

    // Exit:

    return *this;
  };
};

// NON-MEMBER FUNCTIONS

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert ternary_index& xbi into ostream& os.
///
SHEAF_DLL_SPEC std::ostream & operator << (std::ostream& os, const ternary_index& xbi);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle 


#endif // ifndef TERNARY_INDEX_H
