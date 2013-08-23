
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

// Interface for class index_scope

#ifndef INDEX_SCOPE_H
#define INDEX_SCOPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CSTDDEF_H
#include "std_cstddef.h"
#endif

namespace sheaf
{

class id_map;
class scoped_index;
  
///
/// Default id map for objects of type scoped_index.
/// A convenient and safe mechanism for managing
/// scoped_index::default_scope().
///
class SHEAF_DLL_SPEC index_scope
{

  // ===========================================================
  // INDEX_SCOPE FACET
  // ===========================================================

public:

  ///
  /// Sets scoped_index::default_map() to xmap.
  ///
  index_scope(const immutable_id_map* xmap);

  ///
  /// Destructor; restores scoped_index::default_scope() to old_scope().
  /// Not virtual; this class can not be used as a base class.
  ///
  ~index_scope();

  ///
  /// The current scope.
  ///
  const immutable_id_map* scope() const;

  ///
  /// Sets scoped_index::default_scope() to xmap.
  ///
  void put_scope(const immutable_id_map* xmap);

  ///
  /// The scope before this was created.
  ///
  const immutable_id_map* old_scope() const;

protected:

  ///
  /// The scope before this was created.
  ///
  const immutable_id_map* _old_scope;


private:

  ///
  /// Default constructor; disabled.
  ///
  index_scope()
  {}
  ;

  ///
  /// Copy constructor; disabled
  ///
  ///
  index_scope(const index_scope& )
  {}
  ;

  ///
  /// Assignment operator; disabled.
  ///
  ///
  index_scope& operator=(const index_scope&)
  {}
  ;

  ///
  /// Operator new(); disabled to force allocation on stack.
  ///
  static void* operator new(size_t)
  {
    return reinterpret_cast<void *>(1);
  }
  ; // return 0 causes compiler warning

  ///
  /// Operator new[](); disabled to force allocation on stack.
  ///
  static void* operator new[] ( size_t );

  ///
  /// Operator delete(); disabled to force allocation on stack.
  ///
  static void operator delete(void*)
  {}
  ;

  ///
  /// Operator delete[](); disabled to force allocation on stack.
  ///
  static void operator delete[](void *);

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf


#endif // ifndef INDEX_SCOPE_H
