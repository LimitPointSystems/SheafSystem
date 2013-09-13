
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

// Interface for class base_space_factory

#ifndef BASE_SPACE_FACTORY_H
#define BASE_SPACE_FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_PATH_H
#include "poset_path.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef WSV_BLOCK_H
#include "wsv_block.h"
#endif

namespace fiber_bundle
{

class base_space_poset;
class fiber_bundles_namespace;

  using namespace sheaf;

///
/// A factory for making base space objects of type base_type.
///
template <typename base_type>
class base_space_factory
{

public:

  // =============================================================================
  // BASE_SPACE_FACTORY FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  base_space_factory();

  ///
  /// Destructor.
  ///
  virtual ~base_space_factory();

  ///
  /// Finds or creates the base space poset specified by path
  /// in namespace xns.
  ///
  base_space_poset* new_space(fiber_bundles_namespace& xns);

  ///
  /// Finds or creates the base space specified
  /// by xbase_path in namespace xns.
  ///
  base_type* new_base(fiber_bundles_namespace& xns, const poset_path& xbase_path);

  ///
  /// Finds or creates the base space member with name xbase_name
  /// in the host with path path in namespace xns.
  ///
  base_type* new_base(fiber_bundles_namespace& xns, const string& xbase_name);

  ///
  /// The base space host path.
  ///
  poset_path path;

  ///
  /// The base space schema path.
  ///
  poset_path schema_path;

  ///
  /// The base space index bounds.
  ///
  wsv_block<int> index_ubs;

  ///
  /// The path of the local cell prototype for unstructured meshes.
  ///
  poset_path local_cell_prototype_path;

private:

};

// =============================================================================
// MEMBER FUNCTION SPECIALIZATIONS
// =============================================================================

class structured_block_1d;
template <>
SHEAF_DLL_SPEC 
structured_block_1d*
base_space_factory<structured_block_1d>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class structured_block_2d;
template <>
SHEAF_DLL_SPEC
structured_block_2d*
base_space_factory<structured_block_2d>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class structured_block_3d;
template <>
SHEAF_DLL_SPEC
structured_block_3d*
base_space_factory<structured_block_3d>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class point_block_1d;
template <>
SHEAF_DLL_SPEC
point_block_1d*
base_space_factory<point_block_1d>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class point_block_2d;
template <>
SHEAF_DLL_SPEC
point_block_2d*
base_space_factory<point_block_2d>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class point_block_3d;
template <>
SHEAF_DLL_SPEC
point_block_3d*
base_space_factory<point_block_3d>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class zone_nodes_block;
template <>
SHEAF_DLL_SPEC
base_space_poset*
base_space_factory<zone_nodes_block>::
new_space(fiber_bundles_namespace& xns);

template <>
SHEAF_DLL_SPEC
zone_nodes_block*
base_space_factory<zone_nodes_block>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);

class unstructured_block;
template <>
SHEAF_DLL_SPEC
base_space_poset*
base_space_factory<unstructured_block>::
new_space(fiber_bundles_namespace& xns);

template <>
SHEAF_DLL_SPEC
unstructured_block*
base_space_factory<unstructured_block>::
new_base(fiber_bundles_namespace& xns, const string& xbase_name);


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace fiber_bundle


#endif // ifndef BASE_SPACE_FACTORY_H
