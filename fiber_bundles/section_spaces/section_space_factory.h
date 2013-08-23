
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

// Interface for class section_space_factory

#ifndef SECTION_SPACE_FACTORY_H
#define SECTION_SPACE_FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ARG_LIST_H
#include "arg_list.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef POSET_PATH_H
#include "poset_path.h"
#endif

#ifndef SECTION_TRAITS_H
#include "section_traits.h"
#endif

#ifndef WSV_BLOCK_H
#include "wsv_block.h"
#endif

namespace sheaf
{
class subposet;
}

namespace fiber_bundle
{

using namespace sheaf;
  

class fiber_bundles_namespace;
class sec_rep_space;

///
/// A factory for making sec_rep_space objects with sections of type sec_type.
/// OBSOLETE: Use factory methods in fiber_bundles_namespace.
///
template <typename sec_type>
class SHEAF_DLL_SPEC section_space_factory
{

public:

  // =============================================================================
  // SECTION_SPACE_FACTORY FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  section_space_factory();

  ///
  /// Copy constructor.
  ///
  section_space_factory(const section_space_factory& xother);

  ///
  /// Destructor.
  ///
  virtual ~section_space_factory();

  ///
  /// Finds or creates a new section with name xname and one branch
  /// for each member of xbase_parts, auto-allocated version;
  /// creates section space, section space_schema, and fiber space if needed.
  ///
  sec_type* new_multi_section(fiber_bundles_namespace& xns,
                              const string& xname,
                              subposet& xbase_parts);

  ///
  /// Finds or creates a new section with name xname and one branch
  /// for each member of xbase_parts, pre-allocated version;
  /// creates section space, section space_schema, and fiber space if needed.
  ///
  void new_multi_section(fiber_bundles_namespace& xns,
                         const string& xname,
                         subposet& xbase_parts,
                         sec_type& xresult);

  ///
  /// Finds or creates a new multi-section with path xpath and one branch
  /// for each member of xbase_parts, auto-allocated version;
  /// creates section space, section space_schema, and fiber space if needed.
  ///
  sec_type* new_multi_section(fiber_bundles_namespace& xns,
                              const poset_path& xpath,
                              subposet& xbase_parts);

  ///
  /// Finds or creates a new multi-section with path xpath and one branch
  /// for each member of xbase_parts, pre-allocated version;
  /// creates section space, section space_schema, and fiber space if needed.
  ///
  void new_multi_section(fiber_bundles_namespace& xns,
                         const poset_path& xpath,
                         subposet& xbase_parts,
                         sec_type& xresult);

  ///
  /// The base space path.
  ///
  poset_path base_path;

  ///
  /// The representation descriptor path.
  ///
  poset_path rep_path;

  ///
  /// The fiber path.
  ///
  poset_path fiber_path;

  ///
  /// The fiber schema path.
  ///
  poset_path fiber_schema_path;

  ///
  /// The section space schema path
  ///
  poset_path section_space_schema_path;
  
  ///
  /// The vector space path for the fiber.
  ///
  poset_path vector_space_path;

  ///
  /// The standard, class defined, table dofs
  /// for the fiber space, if any.
  ///
  arg_list std_args;

  ///
  /// The non-standard, user defined, table dofs
  /// for the fiber space, if any.
  ///
  arg_list user_args;

  ///
  /// The path for the new section space.
  ///
  poset_path path;

  ///
  /// The section lower bound.
  ///
  wsv_block<sec_vd_value_type> lb;

  ///
  /// The section upper bound.
  ///
  wsv_block<sec_vd_value_type> ub;

  ///
  /// Initializes section dofs from bounds.
  ///
  void put_bounds(sec_type* xsec);

  ///
  /// True if new_section found an
  /// existing section rather than creating one.
  ///
  bool found_section() const;

  ///
  /// Makes all path members empty.
  ///
  void clear_paths();


private:

      ///@todo: Fix new_fiber.

  //  ///
  //  /// Creates a new fiber space.
  //  ///
  //  void new_fiber(fiber_bundles_namespace& xns,
  //                 const poset_path& xfiber_path,
  //		 const poset_path& xvector_space_path,
  //                 const poset_path& xfiber_schema_path);

  ///
  /// True if new_section found an
  /// existing section rather than creating one.
  ///
  bool _found_section;
};

// =============================================================================
// MEMBER FUNCTION SPECIALIZATIONS
// =============================================================================

   ///@todo: Fix new_fiber.

// template <>
// void
// section_space_factory<sec_vd>::
// new_fiber(fiber_bundles_namespace& xns,
//           const poset_path& xfiber_path,
//           const poset_path& xfiber_schema_path);

template <>
SHEAF_DLL_SPEC 
void
section_space_factory<sec_e1>::
put_bounds(sec_e1* xsec);

template <>
SHEAF_DLL_SPEC 
void
section_space_factory<sec_e1_uniform>::
put_bounds(sec_e1_uniform* xsec);

template <>
SHEAF_DLL_SPEC 
void
section_space_factory<sec_e2>::
put_bounds(sec_e2* xsec);

template <>
SHEAF_DLL_SPEC 
void
section_space_factory<sec_e2_uniform>::
put_bounds(sec_e2_uniform* xsec);

template <>
SHEAF_DLL_SPEC 
void
section_space_factory<sec_e3>::
put_bounds(sec_e3* xsec);

template <>
SHEAF_DLL_SPEC 
void
section_space_factory<sec_e3_uniform>::
put_bounds(sec_e3_uniform* xsec);


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================


} // namespace fiber_bundle

#endif // ifndef SECTION_SPACE_FACTORY_H
