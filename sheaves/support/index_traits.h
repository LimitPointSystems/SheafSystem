
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

// Interface for class index_traits

#ifndef INDEX_TRAITS_H
#define INDEX_TRAITS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_LIMITS_H
#include "std_limits.h"
#endif

namespace sheaf
 {
  
///
/// Features describing T as an index type.
///
template <typename T>
struct SHEAF_DLL_SPEC index_traits
{
  ///
  /// The index type.
  ///
  typedef T index_type;

  ///
  /// An integral type representing a relative index.
  ///
  typedef T pod_type;

  ///
  /// Converts an index type xindex to pod_type.
  ///
  static inline pod_type pod(const T& xindex)
  {
    return xindex;
  };

  ///
  /// Sets the pod of index type xindex to xpod.
  ///
  static inline void put_pod(T& xindex, pod_type& xpod)
  {
    xindex = xpod;
    return;
  };

  ///
  /// The invalid index value.
  ///
  static inline T invalid()
  {
    return numeric_limits<T>::max();
  };

  ///
  /// True if xindex is valid.
  ///
  static inline bool is_valid(const T& xindex)
  {
    return xindex != invalid();
  }

  ///
  /// The additive identity.
  ///
  static inline T zero()
  {
    return 0;
  };

  ///
  /// The multiplicative identity.
  ///
  static inline T one()
  {
    return 1;
  };

  ///
  /// True if xindex is >= zero().
  ///
  static inline bool is_positive(const T& xindex)
  {
    return xindex >= 0;
  }

  ///
  /// True if xindex is > zero().
  ///
  static inline bool is_positive_definite(const T& xindex)
  {
    return xindex > 0;
  }

  ///
  /// The maximum valid value.
  ///
  static inline T max()
  {
    return numeric_limits<T>::max() - 1;
  };

  ///
  /// The minimum valid value.
  ///
  static inline T min()
  {
    return numeric_limits<T>::min();
  };
};
 
} // namespace sheaf

#endif // ifndef INDEX_TRAITS_H






