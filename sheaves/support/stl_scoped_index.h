
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

// Interface for class stl_scoped_index.

#ifndef STL_SCOPED_INDEX_H
#define STL_SCOPED_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef SCOPED_INDEX_H
#include "SheafSystem/scoped_index.h"
#endif

namespace sheaf
{

///
/// A stl_scoped_index comparison policy for lexographical
/// comparison.
///
class SHEAF_DLL_SPEC lexographical_compare_policy
{
 public:

  ///
  /// True, if xindex1 is less than xindex2.
  ///
  static bool less_than(const scoped_index& xindex1,
			const scoped_index& xindex2);

  ///
  /// True, if xindex1 is equal to xindex2.
  ///
  static bool equal(const scoped_index& xindex1,
		    const scoped_index& xindex2);
};

///
/// A stl_scoped_index comparison policy for equivalence
/// comparison.
///
class SHEAF_DLL_SPEC equivalence_compare_policy
{
 public:

  ///
  /// True, if xindex1 is less than xindex2.
  ///
  static bool less_than(const scoped_index& xindex1,
			const scoped_index& xindex2);

  ///
  /// True, if xindex1 is equal to xindex2.
  ///
  static bool equal(const scoped_index& xindex1,
		    const scoped_index& xindex2);
};

///
/// Wrapper for scoped_index used for standard template library
/// tree containers (set, multiset, map, multimap).  This class
/// redefines operator< to guarantee strict work ordering
/// regardless of the id space.
///
template <typename T = lexographical_compare_policy>
class SHEAF_DLL_SPEC stl_scoped_index
{
  // ===========================================================
  // STL_SCOPED_INDEX FACET
  // ===========================================================

 public:

  ///
  /// The type of compare policy.
  ///
  typedef T compare_policy;

  ///
  /// Creates a wrapper of scoped_index, xindex.
  ///
  stl_scoped_index(const scoped_index& xindex);

  ///
  /// Destructor.
  /// Not virtual; this can not be a base class.
  ///
  ~stl_scoped_index();

  ///
  /// Class invariant.
  ///
  inline bool invariant() const
  {
    return _index.invariant();
  };

  ///
  /// scoped_index being wrapped.
  ///
  inline const scoped_index& index() const
  {
    return _index;
  };

  ///
  /// Conversion operator to scoped_index.
  ///
  operator scoped_index () const;

  ///
  /// True if this is less than xother.
  ///
  bool operator<(const stl_scoped_index<T>& xother) const;

  ///
  /// True if this is equivalent to xother.
  ///
  bool operator==(const stl_scoped_index<T>& xother) const;

 private:

  ///
  /// Index to wrap.
  ///
  scoped_index _index; 
};

} // namespace sheaf

#endif // ifndef STL_SCOPED_INDEX_H
