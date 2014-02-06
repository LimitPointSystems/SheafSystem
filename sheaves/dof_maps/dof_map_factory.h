
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

// Interface for class dof_map_factory

#ifndef DOF_MAP_FACTORY_H
#define DOF_MAP_FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef DOF_TUPLE_TYPE_H
#include "dof_tuple_type.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif



namespace sheaf
{
class poset_dof_map;  
///
/// A factory for creating dof maps.
///
class SHEAF_DLL_SPEC dof_map_factory
{

  friend class poset_dof_map;

public:

  // ===========================================================
  // DOF_MAP_FACTORY FACET
  // ===========================================================

  ///
  /// Destructor
  ///
  virtual ~dof_map_factory();

  ///
  /// Creates an uninitialized dof map of type xclient_class_name
  /// or type xsheaf_base_class_id if no prototype for xclient_class_name.
  ///
  poset_dof_map* new_dof_map(const std::string& xclient_class_name,
                             dof_tuple_type xsheaf_base_class_id);

  ///
  /// Sets xprototype as the prototype for its client class.
  ///
  void insert_prototype(const poset_dof_map* xprototype);

  ///
  /// Sets xprototype as the prototype for type xtype_id.
  ///
  void insert_prototype(dof_tuple_type xtype_id, const poset_dof_map* xprototype);

  ///
  /// Removes the prototype for handles of type xclass_name.
  ///
  void delete_prototype(const std::string& xclass_name);

  ///
  /// True if the set of prototypes contains a
  /// prototype for handles of type xclass_name.
  ///
  bool contains_prototype(const std::string& xclass_name) const;

  ///
  /// True if the set of prototypes contains a
  /// prototype for handles of type xtype_id.
  ///
  bool contains_prototype(dof_tuple_type xtype_id) const;

private:

  ///
  /// Default constructor; private to ensure only one instance.
  ///
  ///
  dof_map_factory();

  ///
  /// Copy constructor; disabled.
  ///
  ///
  dof_map_factory(const dof_map_factory& xother)
  {}
  ;

  ///
  /// The type of the prototypes map.
  ///
  typedef std::map<std::string, poset_dof_map*> prototypes_map_type;

  ///
  /// The client prototypes map.
  ///
  prototypes_map_type _prototypes_map;

  ///
  /// The sheaf base class prototypes map.
  ///
  block<poset_dof_map*> _sheaf_prototypes_map;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef DOF_MAP_FACTORY_H
