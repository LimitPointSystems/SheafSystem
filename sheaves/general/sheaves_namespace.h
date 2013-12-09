
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

// Interface for class sheaves_namespace

#ifndef SHEAVES_NAMESPACE_H
#define SHEAVES_NAMESPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif

namespace sheaf
{
  
///
/// The standard sheaves name space.
///
class SHEAF_DLL_SPEC sheaves_namespace : public namespace_poset
{


public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  // CANONICAL MEMBERS

  ///
  /// Destructor
  ///
  virtual ~sheaves_namespace();

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a sheaves namespace with name xname.
  ///
  sheaves_namespace(const std::string& xname);

  ///
  /// Creates a triangle schema using the primatives poset.  This
  /// static function is used for test drivers.
  ///
  static void make_triangle(sheaves_namespace* xns);

protected:

  ///
  /// Default constructor; creates an unattached handle.
  ///
  sheaves_namespace();

  ///
  /// Covariant constructor.
  ///
  sheaves_namespace(namespace_poset_member* xtop, namespace_poset_member* xbottom);

  ///
  /// Copy constructor; disabled.
  ///
  sheaves_namespace(const sheaves_namespace& xother) { };


};
  
} // namespace sheaf

#endif // ifndef SHEAVES_NAMESPACE_H
