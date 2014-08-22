
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

/// @file
/// Interface for class field_factory_2

#ifndef COM_LIMITPOINT_FIELDS_FIELD_FACTORY_2_H
#define COM_LIMITPOINT_FIELDS_FIELD_FACTORY_2_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ARG_LIST_H
#include "ComLimitPoint/sheaf/arg_list.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_PATH_H
#include "ComLimitPoint/sheaf/poset_path.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_WSV_BLOCK_H
#include "ComLimitPoint/sheaf/wsv_block.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_TRAITS_H
#include "ComLimitPoint/fields/field_traits.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT0_H
#include "ComLimitPoint/fields/field_at0.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT1_H
#include "ComLimitPoint/fields/field_at1.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT2_H
#include "ComLimitPoint/fields/field_at2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT2_E2_H
#include "ComLimitPoint/fields/field_at2_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT2_E3_H
#include "ComLimitPoint/fields/field_at2_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT3_H
#include "ComLimitPoint/fields/field_at3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_AT3_E3_H
#include "ComLimitPoint/fields/field_at3_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ATP_H
#include "ComLimitPoint/fields/field_atp.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E1_H
#include "ComLimitPoint/fields/field_e1.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E1_UNIFORM_H
#include "ComLimitPoint/fields/field_e1_uniform.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E2_H
#include "ComLimitPoint/fields/field_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E2_UNIFORM_H
#include "ComLimitPoint/fields/field_e2_uniform.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E3_H
#include "ComLimitPoint/fields/field_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E3_UNIFORM_H
#include "ComLimitPoint/fields/field_e3_uniform.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_E4_H
#include "ComLimitPoint/fields/field_e4.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ED_H
#include "ComLimitPoint/fields/field_ed.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_H
#include "ComLimitPoint/fields/field_jcb.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_E13_H
#include "ComLimitPoint/fields/field_jcb_e13.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_E23_H
#include "ComLimitPoint/fields/field_jcb_e23.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_E33_H
#include "ComLimitPoint/fields/field_jcb_e33.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_ED_H
#include "ComLimitPoint/fields/field_jcb_ed.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_MET_H
#include "ComLimitPoint/fields/field_met.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_MET_E1_H
#include "ComLimitPoint/fields/field_met_e1.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_MET_E2_H
#include "ComLimitPoint/fields/field_met_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_MET_E3_H
#include "ComLimitPoint/fields/field_met_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_MET_ED_H
#include "ComLimitPoint/fields/field_met_ed.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST2_H
#include "ComLimitPoint/fields/field_st2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST2_E2_H
#include "ComLimitPoint/fields/field_st2_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST2_E3_H
#include "ComLimitPoint/fields/field_st2_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST3_H
#include "ComLimitPoint/fields/field_st3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST3_E3_H
#include "ComLimitPoint/fields/field_st3_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST4_H
#include "ComLimitPoint/fields/field_st4.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST4_E2_H
#include "ComLimitPoint/fields/field_st4_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ST4_E3_H
#include "ComLimitPoint/fields/field_st4_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_STP_H
#include "ComLimitPoint/fields/field_stp.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T2_H
#include "ComLimitPoint/fields/field_t2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T2_E2_H
#include "ComLimitPoint/fields/field_t2_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T2_E3_H
#include "ComLimitPoint/fields/field_t2_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T3_H
#include "ComLimitPoint/fields/field_t3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T3_E3_H
#include "ComLimitPoint/fields/field_t3_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T4_H
#include "ComLimitPoint/fields/field_t4.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T4_E2_H
#include "ComLimitPoint/fields/field_t4_e2.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_T4_E3_H
#include "ComLimitPoint/fields/field_t4_e3.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_TP_H
#include "ComLimitPoint/fields/field_tp.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_VD_H
#include "ComLimitPoint/fields/field_vd.h"
#endif

namespace fiber_bundle
{
class point_block_1d;
class point_block_2d;
class point_block_3d;
class fiber_bundles_namespace;
class structured_block_1d;
class structured_block_2d;
class structured_block_3d;
class unstructured_block;
}

namespace fields
{

using namespace fiber_bundle;
  

///
/// A factory for making field_vd objects with coordinates section
/// of type coord_type, property section of type prop_type and
/// base space of type base_type.
///
template <typename coord_type, typename prop_type, typename base_type>
class SHEAF_DLL_SPEC field_factory_2
{

  //===========================================================================
  /// @name FIELD_FACTORY_2 FACET
  //===========================================================================
  //@{

public:

  ///
  /// Typedef: The type of the field to create.
  ///
  typedef typename field_traits<prop_type>::field_type field_type;

  ///
  /// Default constructor.
  ///
  field_factory_2();

  ///
  /// Destructor.
  ///
  virtual ~field_factory_2();

  ///
  /// Creates a new field with base specified by xbase_path,
  /// coordinates specified by xcoord_path, and property
  /// specified by xprop_path. Note that poset names specified
  /// by xcoord_path and xprop_path must exist and be accessible..
  ///
  field_type* new_field(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const poset_path& xcoord_path,
                        const poset_path& xprop_path,
			bool xauto_access);

  ///
  /// Creates a new field with base specified by xbase_path,
  /// coordinates with name xcoord_name, and property with name xprop_name.
  /// Standard section space hosts will be used for the coordinate
  /// and property sections.
  ///
  field_type* standard_field(fiber_bundles_namespace& xns,
			     const poset_path& xbase_path,
			     const std::string& xcoord_name,
			     const std::string& xprop_name,
			     bool xauto_access);

  //@}


  //===========================================================================
  /// @name BASE SPACE FACET
  //===========================================================================
  //@{

public:

  ///
  /// The base space schema path.
  ///
  poset_path& base_schema_path();

  ///
  /// The base space index bounds.
  ///
  wsv_block<int>& base_index_ubs();

  ///
  /// The path of the local cell prototype for unstructured meshes.
  ///
  poset_path& local_cell_prototype_path();


private:

  ///
  /// The base space schema path.
  ///
  poset_path _base_schema_path;

  ///
  /// The base space index bounds.
  ///
  wsv_block<int> _base_index_ubs;

  ///
  /// The path of the local cell prototype for unstructured meshes.
  ///
  poset_path _local_cell_prototype_path;

  //@}


  //===========================================================================
  /// @name COORDINATES SECTION FACET
  //===========================================================================
  //@{

public:

  ///
  /// The coordinates representation descriptor path.
  ///
  poset_path& coord_rep_path();

  ///
  /// The fiber suffix for the coordinates section space.
  ///
  std::string& coord_fiber_suffix();

  ///
  /// The section suffix for the coordinates section space.
  ///
  std::string& coord_section_suffix();

  ///
  /// The coordinates lower bound.
  ///
  wsv_block<sec_vd_value_type>& coord_lb();

  ///
  /// The coordinates upper bound.
  ///
  wsv_block<sec_vd_value_type>& coord_ub();


private:

  ///
  /// The coordinates representation descriptor path.
  ///
  poset_path _coord_rep_path;

  ///
  /// The fiber suffix for the coordinates section space.
  ///
  std::string _coord_fiber_suffix;

  ///
  /// The section suffix for the coordinates section space.
  ///
  std::string _coord_section_suffix;

  ///
  /// The coordinates lower bound.
  ///
  wsv_block<sec_vd_value_type> _coord_lb;

  ///
  /// The coordinates upper bound.
  ///
  wsv_block<sec_vd_value_type> _coord_ub;

  //@}


  //===========================================================================
  /// @name PROPERTY SECTION FACET
  //===========================================================================
  //@{

public:

  ///
  /// The property representation descriptor path.
  ///
  poset_path& prop_rep_path();

  ///
  /// The fiber suffix for the property section space.
  ///
  std::string& prop_fiber_suffix();

  ///
  /// The section suffix for the property section space.
  ///
  std::string& prop_section_suffix();

  ///
  /// The property lower bound.
  ///
  wsv_block<sec_vd_value_type>& prop_lb();

  ///
  /// The property upper bound.
  ///
  wsv_block<sec_vd_value_type>& prop_ub();


private:

  ///
  /// The property representation descriptor path.
  ///
  poset_path _prop_rep_path;

  ///
  /// The fiber suffix for the property section space.
  ///
  std::string _prop_fiber_suffix;

  ///
  /// The section suffix for the property section space.
  ///
  std::string _prop_section_suffix;

  ///
  /// The property lower bound.
  ///
  wsv_block<sec_vd_value_type> _prop_lb;

  ///
  /// The property upper bound.
  ///
  wsv_block<sec_vd_value_type> _prop_ub;

  //@}

};

//=============================================================================
// NON-MEMBER FUNCTIONS
//=============================================================================

template <typename base_type>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                base_type& xresult);

template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                structured_block_1d& xresult);
				
template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                structured_block_2d& xresult);
				
template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                structured_block_3d& xresult);			
				
template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                point_block_1d& xresult);
				
template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                point_block_2d& xresult);
				
template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                point_block_3d& xresult);
				
template <>
SHEAF_DLL_SPEC
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                unstructured_block& xresult);

} // namespace fields

#endif // ifndef COM_LIMITPOINT_FIELDS_FIELD_FACTORY_2_H
