
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
// Interface for class binary_index

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BINARY_INDEX_H
#define COM_LIMITPOINT_FIBER_BUNDLE_BINARY_INDEX_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_UNARY_INDEX_H
#include "ComLimitPoint/fiber_bundle/unary_index.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

namespace fiber_bundle
{
  
///
/// A pair of indices (i,j).
///
class SHEAF_DLL_SPEC binary_index
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
  /// Default Constructor; creates an instance with i == j == 0;
  ///
  binary_index()
  {
    // Preconditions:

    // Body:

    i = 0;
    j = 0;

    // Postconditions:

    ensure(i == 0);
    ensure(j == 0);

    // Exit:

    return;
  };

  ///
  /// Creates an instance with i == xi, j == xj.
  ///
  binary_index(unary_index xi, unary_index xj)
  {
    // Preconditions:

    // Body:

    i = xi;
    j = xj;

    // Postconditions:

    ensure(i == xi);
    ensure(j == xj);

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
  binary_index operator+(const binary_index& xother) const
  {
    // Preconditions:

    // Body:

    binary_index result(i+xother.i, j+xother.j);

    // Postconditions:

    ensure(result.i = i + xother.i);
    ensure(result.j = j + xother.j);

    // Exit:

    return result;
  };

  ///
  /// Self-allocated sum.
  ///
  binary_index& operator+=(const binary_index& xother)
  {
    // Preconditions:

    // Body:

    define_old_variable(unary_index old_i = i);
    define_old_variable(unary_index old_j = j);

    i += xother.i;
    j += xother.j;

    // Postconditions:

    ensure(i = old_i + xother.i);
    ensure(j = old_j + xother.j);

    // Exit:

    return *this;
  };
};

// NON-MEMBER FUNCTIONS

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert binary_index& xbi into ostream& os.
///
SHEAF_DLL_SPEC 
std::ostream& operator<<(std::ostream& os, const binary_index& xbi);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle 


#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_BINARY_INDEX_H
