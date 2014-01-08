
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

// Implementation for deep_size functions

#ifndef DEEP_SIZE_IMPL_H
#define DEEP_SIZE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DEEP_SIZE_H
#include "deep_size.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef PRIMITIVE_TRAITS_H
#include "primitive_traits.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif


//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace sheaf
{
  
//=============================================================================
// deep size map properties
//=============================================================================

template <typename M>
size_t
no_deep_size_policy<M>::
items_deep_size(const M& xp)
{
  size_t result = 0;
  
  // Preconditions:

  // Body:

  // Do nothing.

  // Postconditions:

  ensure(result == 0);
  
  // Exit:

  return result;
}

template <typename M>
size_t
value_ptr_deep_size_policy<M>::
items_deep_size(const M& xp)
{
  size_t result = 0;
  
  // Preconditions:

  // Body:

  typename M::const_iterator litr;
  for(litr = xp.begin(); litr != xp.end(); ++litr)
  {
    if(litr->second != 0)
      result += deep_size(*(litr->second), false);
  }

  // Postconditions:

  ensure(result >= 0);
  
  // Exit:

  return result;
}

template <typename M>
size_t
key_deep_size_policy<M>::
items_deep_size(const M& xp)
{
  size_t result = 0;
  
  // Preconditions:

  // Body:

  typename M::const_iterator litr;
  for(litr = xp.begin(); litr != xp.end(); ++litr)
  {
    result += deep_size(litr->first, false);
  }

  // Postconditions:

  ensure(result >= 0);
  
  // Exit:

  return result;
}

template <typename M>
size_t
value_deep_size_policy<M>::
items_deep_size(const M& xp)
{
  size_t result = 0;
  
  // Preconditions:

  // Body:

  typename M::const_iterator litr;
  for(litr = xp.begin(); litr != xp.end(); ++litr)
  {
    result += deep_size(litr->second, false);
  }

  // Postconditions:

  ensure(result >= 0);
  
  // Exit:

  return result;
}

template <typename M>
size_t
key_value_deep_size_policy<M>::
items_deep_size(const M& xp)
{
  size_t result = 0;
  
  // Preconditions:

  // Body:

  typename M::const_iterator litr;
  for(litr = xp.begin(); litr != xp.end(); ++litr)
  {
    result += deep_size(litr->first, false);
    result += deep_size(litr->second, false);
  }

  // Postconditions:

  ensure(result >= 0);
  
  // Exit:

  return result;
}

template <typename K, typename V, typename S, typename H, typename E, typename A>
size_t
deep_size(const SHEAF_UNORDERED_NAMESPACE::unordered_multimap<K, V, H, E, A>& xp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  using namespace std;

  result = xinclude_shallow ? sizeof(xp) : 0;

  // @hack Using the same calculation ashash map.  Should review.

  // Since we have no easy access to the memory allocation in STL class unordered_map
  // (or map) we use the following as a best guess:
  //    deep_size = load_factor * (bucket_count) * sizeof(value_type);

  // We believe, based on some experiments, that the load factor is 2.

  static const int load_factor = 2;

  // The value_type for our data members is pair<int, int>, so the our best guess
  // for the size is:

  size_t lbucket_count = xp.bucket_count();
  size_t ldeep_size = load_factor * lbucket_count * sizeof(pair<K, V>);

  result += ldeep_size;

  // Use the deep_size policy to calculate the size of the key and value objects.

  result += S::items_deep_size(xp);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

template <typename K, typename V, typename S, typename H, typename E, typename A>
size_t
deep_size(const SHEAF_UNORDERED_NAMESPACE::unordered_map<K, V, H, E, A>& xp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  using namespace std;

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Since we have no easy access to the memory allocation in STL class unordered_map
  // (or map) we use the following as a best guess:
  //    deep_size = load_factor * (bucket_count) * sizeof(value_type);

  // We believe, based on some experiments, that the load factor is 2.

  static const int load_factor = 2;

  // The value_type for our data members is pair<int, int>, so the our best guess
  // for the size is:

  size_t lbucket_count = xp.bucket_count();
  size_t ldeep_size = load_factor * lbucket_count * sizeof(pair<K, V>);

  result += ldeep_size;

  // Use the deep_size policy to calculate the size of the key and value objects.

  result += S::items_deep_size(xp);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

template <typename K, typename V, typename S>
size_t
deep_size(const std::map<K, V>& xp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  using namespace std;

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  //
  // @hack This is guess at the size of the map structure.  This calculation
  //       should be revisited.
  //

  size_t lsize = xp.size();
  size_t ldeep_size = lsize * sizeof(pair<K, V>);

  result += ldeep_size;

  // Use the deep_size policy to calculate the size of the key and value objects.

  result += S::items_deep_size(xp);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

template <typename T>
size_t
deep_size(const std::list<T>& xp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  //
  // @hack This is guess at the size of the list structure.  This calculation
  //       should be revisited.
  //

  // Add the constributions from the pointers in the list.

  result += xp.size() * 2*sizeof(void*);

  // Add the deep size of the members.

  typename std::list<T>::const_iterator litr = xp.begin();
  for(; litr != xp.end(); ++litr)
  {
    deep_size(*litr, true);
  }

  // Postconitions:

  ensure(result >= 0);

  // Exit:

  return result;
}

//=============================================================================
// Function for primitive
//=============================================================================

template <typename T>
size_t
deep_size(const T& xvalue, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  result = xinclude_shallow ? primitive_traits<T>::size() : 0;
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

} // namespace sheaf

#endif // ifndef DEEP_SIZE_IMPL_H
