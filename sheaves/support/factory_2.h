

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class factory_2

#ifndef FACTORY_2_H
#define FACTORY_2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class namespace_poset;
class arg_list;

template <typename T>
class rc_ptr;

// Forward declarations to enable friend declaration.

template <typename T, typename R>
class factory_2;

template <typename T, typename R>
ostream& operator << (ostream &os, const factory_2<T, R>& xf);


///
/// A factory for instanting descendants of an abstract type T,
/// given the class name of the descendant.
/// Requires:
///  virtual const string& T::class_name()
///     the actual (descendant) class name of the prototype.
///  virtual R T::clone()
///     virtual default constructor
///  virtual R T::clone(S& xarg)
///     virtual constructor
///
template <typename T, typename R = T*>
class factory_2
{
  friend ostream& operator << <T, R> (ostream& xos, const factory_2<T, R>& xf);

  // ===========================================================
  /// @name FACTORY_2 FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  factory_2();

  ///
  /// Destructor
  ///
  virtual ~factory_2();

//   ///
//   /// Creates an instance of type xclient_class_name.
//   ///
//   R new_instance(const string& xclient_class_name);

  ///
  /// Creates an instance of type xclient_class_name with arguments xargs.
  ///
  R new_instance(const string& xclient_class_name, const arg_list& xargs);

  ///
  /// Sets xprototype as the prototype for its client class.
  ///
  void insert_prototype(T* xprototype);

  ///
  /// Removes the prototype for handles of type xclass_name.
  ///
  void delete_prototype(const string& xclass_name);

  ///
  /// True if the set of prototypes contains a
  /// prototype for handles of type xclass_name.
  ///
  bool contains_prototype(const string& xclass_name) const;

protected:

private:

  ///
  /// Copy constructor; disabled.
  ///
  ///
  factory_2(const factory_2& xother);

  ///
  /// The type of the prototypes map.
  ///
  typedef map<string, T*> prototypes_map_type;

  ///
  /// The client prototypes map.
  ///
  prototypes_map_type _prototypes_map;

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts factory_2& xf in stream xos.
///
template <typename T, typename R>
ostream& operator << (ostream& xos, const factory_2<T, R>& xf);
 
} // namespace sheaf

#endif // ifndef FACTORY_2_H
