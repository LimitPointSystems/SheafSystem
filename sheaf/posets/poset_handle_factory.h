
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

// Interface for class poset_handle_factory

#ifndef COM_LIMITPOINT_SHEAF_POSET_HANDLE_FACTORY_H
#define COM_LIMITPOINT_SHEAF_POSET_HANDLE_FACTORY_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_TYPE_H
#include "ComLimitPoint/sheaf/poset_type.h"
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
class poset_state_handle;
  
///
/// A factory for creating poset handles.
///
class SHEAF_DLL_SPEC poset_handle_factory
{
public:

  // ===========================================================
  // POSET_HANDLE_FACTORY FACET
  // ===========================================================

  ///
  /// Default constructor.
  ///
  ///
  poset_handle_factory();

  ///
  /// Destructor
  ///
  virtual ~poset_handle_factory();

  ///
  /// Creates an unattached handle of type xclient_class_name
  /// or type xsheaf_base_class_id if no prototype for xclient_class_name.
  ///
  poset_state_handle* new_poset_handle(const std::string& xclient_class_name,
                                       poset_type xsheaf_base_class_id);

  ///
  /// Sets xprototype as the prototype for its client class.
  ///
  void insert_prototype(const poset_state_handle* xprototype);

  ///
  /// Sets xprototype as the prototype for type xtype_id.
  ///
  void insert_prototype(poset_type xtype_id,
                        const poset_state_handle* xprototype);

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
  bool contains_prototype(poset_type xtype_id) const;

private:

  ///
  /// Copy constructor; disabled.
  ///
  ///
  poset_handle_factory(const poset_handle_factory& xother)
  {}
  ;

  ///
  /// The type of the poset handle prototypes map.
  ///
  typedef std::map<std::string, poset_state_handle*> prototypes_map_type;

  ///
  /// The client poset handle prototypes map.
  ///
  prototypes_map_type _prototypes_map;

  ///
  /// The sheaf base class handle prototypes map.
  ///
  block<poset_state_handle*> _sheaf_prototypes_map;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POSET_HANDLE_FACTORY_H
