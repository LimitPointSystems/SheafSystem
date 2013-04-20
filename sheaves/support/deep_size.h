
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for deep_size functions

#ifndef DEEP_SIZE_H
#define DEEP_SIZE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CSTDDEF_H
#include "std_cstddef.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

namespace sheaf
{
  
///
/// Do not call deep_size on either the key or value.
///
template <typename M>
class no_deep_size_policy
{
public:

  ///
  /// The deep_size of the items in xp.
  ///
  static size_t items_deep_size(const M& xp);
};

///
/// Call deep_size on the dereferenced pointer of the value.
///
template <typename M>
class value_ptr_deep_size_policy
{
public:

  ///
  /// The deep_size of the items in xp.
  ///
  static size_t items_deep_size(const M& xp);
};

///
/// Call deep_size on the key.
///
template <typename M>
class key_deep_size_policy
{
 public:

  ///
  /// The deep_size of the items in xp.
  ///
  static size_t items_deep_size(const M& xp);
};

///
/// Call deep_size on the value
///
template <typename M>
class value_deep_size_policy
{
 public:

  ///
  /// The deep_size of the items in xp.
  ///
  static size_t items_deep_size(const M& xp);
};

///
/// Call deep_size on the key and the value
///
template <typename M>
class key_value_deep_size_policy
{
 public:

  ///
  /// The deep_size of the items in xp.
  ///
  static size_t items_deep_size(const M& xp);
};

///
/// The deep size of the referenced object of type hash_multimap;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template <typename K, typename V, typename S, typename H, typename E, typename A>
size_t deep_size(const hash_multimap<K, V, H, E, A>& xp, bool xinclude_shallow);

///
/// The deep size of the referenced object of type hash_map;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template <typename K, typename V, typename S, typename H, typename E, typename A>
size_t deep_size(const hash_map<K, V, H, E, A>& xp, bool xinclude_shallow);

///
/// The deep size of the referenced object of type map;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template <typename K, typename V, typename S>
size_t
deep_size(const map<K, V>& xp, bool xinclude_shallow);

///
/// The deep size of the referenced object of type list;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template <typename T>
size_t
deep_size(const list<T>& xp, bool xinclude_shallow);

///
/// The deep size of the referenced primitive of type T.
///
template <typename T>
size_t
deep_size(const T& xvalue, bool xinclude_shallow);

///
/// The deep size of the referenced object of type string;
/// if xinclude_shallow, add the sizeof xp to the result.
/// 
SHEAF_DLL_SPEC
size_t
deep_size(const string& xp, bool xinclude_shallow);

} // namespace sheaf

#endif // ifndef DEEP_SIZE_H

