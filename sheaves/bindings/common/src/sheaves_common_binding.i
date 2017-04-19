
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

//
//
// Common SWIG interface to sheaves cluster
//

//=============================================================================

//$$SCRIBBLE: This file contains only the part of the Swig interface which
//            is to be lists the classes, etc. to be wrapped.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "sheaves_common_binding_includes.i" as well.

//=============================================================================

// Some standard swig stuff.

%include "std_string.i"
%include "carrays.i"

#ifdef SWIGWIN
%include <windows.i>
#endif

%array_class(double, doubleArray);
%array_class(int, intArray);

%include "cpointer.i"
%pointer_class(double, doublePtr);
%pointer_class(int, intPtr);

//=============================================================================
// Ignore directives:
//=============================================================================

//$$TODO: Find fixes for all of these "%ignores".

%ignore *::operator=;
%ignore *::operator[];

// Unresolved symbols caused by no -DSHEAF_DLL_IMPORTS when compiling.

/* // The following cause unresolved symbol errors during the Windows link phase: */

/* %ignore sheaf::poset_state_handle::default_name; */
/* %ignore sheaf::depth_first_iterator::NULL_FILTER; */
/* %ignore sheaf::poset_bounds_descriptor::BOTTOM_TOP; */
/* %ignore sheaf::poset_bounds_descriptor::BOTTOM_BOTTOM; */

/* %ignore sheaf::storage_agent::RELEASE_ALL; */
/* %ignore sheaf::storage_agent::RETAIN_READ; */
/* %ignore sheaf::storage_agent::ABORT; */
/* %ignore sheaf::storage_agent::COMMIT; */

/* // these methods in storage agent need to be ignored because they reference BOTTOM_TOP in their method signatures. */
/* // $$ISSUE: this should be looked into even though these methods will not be called directly by the end user. */
/* %ignore sheaf::storage_agent::read; */
/* %ignore sheaf::storage_agent::write; */
/* %ignore sheaf::storage_agent::begin_read_transaction; */
/* %ignore sheaf::storage_agent::begin_read_write_transaction; */
/* %ignore sheaf::storage_agent::begin_write_transaction; */
/* //%ignore sheaf::storage_agent::transaction::transaction; */



%ignore sheaf::scoped_index_hub_pod;
%ignore sheaf::scoped_index::operator~() const;
%ignore sheaf::scoped_index::operator==(scoped_index_hub_pod) const;
%ignore sheaf::scoped_index::operator!=(scoped_index_hub_pod) const;

//$$ISSUE: We are ignoring the following methods because swig is currently having
//         trouble with them.  It thinks that their return types are being
//         multiply defined!

%ignore sheaf::subposet::member_iterator() const;
%ignore sheaf::poset_bounds::descriptor() const;

//$$ISSUE: We are ignoring poset::type_id() because it is being confused with
//         poset_type_id() in poset_type.h

%ignore sheaf::poset::type_id() const;

//=============================================================================

//=============================================================================

//$$ISSUE: We are not currently wrapping class "factory" due to what appears
//         to be a bug in g++ version 3.4.6.

//=============================================================================

// Include the list of files to be inserted into the generated code.

%include "sheaves_common_binding_includes.i"

//=============================================================================

//$$HACK: Swig still cannot handle nested classes/structs in c++.
//        So to get "arg_list" with nested struct "arg_type" to
//        build, we do the following: first reproduce the arg_type
//        definition globally (has to be kept in sync with the one
//        in arg_list.h), then use a typedef to make the compiler happy.

struct arg_type
{
  string name;
  primitive_type type() const;
  void put_type(primitive_type xid);
  void put_type(int xid);
  primitive_value value;
  arg_type();
  arg_type(const string& xname);
};

%{
typedef sheaf::arg_list::arg_type arg_type;
%}

//=============================================================================

// The list of classes, etc for which wrappers will be generated.

//$$SCRIBBLE: Note that order is important in the following list.  It must
//            follow the class hierarchies.

//=============================================================================

%include "SheafSystem/std_string.h"

%include "SheafSystem/sheaf_dll_spec.h"
%include "SheafSystem/sheaf.h"
%include "SheafSystem/poset_type.h"
%include "SheafSystem/pod_types.h"
%include "SheafSystem/primitive_attributes.h"
%include "SheafSystem/primitive_value.h"
%include "SheafSystem/primitive_type.h"
%include "SheafSystem/standard_dof_tuple_index.h"
%include "SheafSystem/standard_member_index.h"
%include "SheafSystem/standard_subposet_index.h"
%include "SheafSystem/standard_version_index.h"
%include "SheafSystem/dof_tuple_type.h"
%include "SheafSystem/namespace_relative_member_index.h"
%include "SheafSystem/namespace_relative_subposet_index.h"
%include "SheafSystem/rc_ptr.h"
%include "SheafSystem/any.h"
%include       "SheafSystem/abstract_product_structure.h"
%include             "SheafSystem/ij_product_structure.h"
%include             "SheafSystem/ijk_product_structure.h"
%include       "SheafSystem/data_converter.h"
%include       "SheafSystem/data_type_map.h"
%include             "SheafSystem/file_data_type_map.h"
%include             "SheafSystem/poset_data_type_map.h"
%include       "SheafSystem/depth_first_iterator.h"
%include             "SheafSystem/filtered_depth_first_iterator.h"
%include                   "SheafSystem/biorder_iterator.h"
%include                   "SheafSystem/linkorder_iterator.h"
%include                   "SheafSystem/postorder_iterator.h"
%include                   "SheafSystem/preorder_iterator.h"
%include                   "SheafSystem/triorder_iterator.h"
%include       "SheafSystem/depth_first_itr.h"
%include             "SheafSystem/filtered_depth_first_itr.h"
%include                   "SheafSystem/biorder_itr.h"
%include                   "SheafSystem/linkorder_itr.h"
%include                   "SheafSystem/postorder_itr.h"
%include                   "SheafSystem/preorder_itr.h"
%include                   "SheafSystem/triorder_itr.h"
%include       "SheafSystem/error_message.h"
%include       "SheafSystem/filtered_depth_first_member_iterator.h"
%include             "SheafSystem/postorder_member_iterator.h"
%include             "SheafSystem/preorder_member_iterator.h"
%include       "SheafSystem/index_equivalence_class.h"
%include       "SheafSystem/index_equivalence_iterator.h"
%include       "SheafSystem/index_space_collection.h"
%include             "SheafSystem/explicit_index_space_collection.h"
%include             "SheafSystem/index_space_interval.h"
%include                   "SheafSystem/array_index_space_interval.h"
%include                   "SheafSystem/explicit_index_space_interval.h"
%include                   "SheafSystem/ragged_array_index_space_interval.h"
%include                   "SheafSystem/singleton_index_space_interval.h"
%include       "SheafSystem/index_space_family.h"
%include       "SheafSystem/index_space_family_iterator.h"
%include       "SheafSystem/index_space_handle.h"
%include             "SheafSystem/forwarding_index_space_handle.h"
%include             "SheafSystem/explicit_index_space_handle.h"
%include                   "SheafSystem/gathered_insertion_index_space_handle.h"
%include                   "SheafSystem/scattered_insertion_index_space_handle.h"
%include                         "SheafSystem/array_index_space_handle.h"
%include                         "SheafSystem/hash_index_space_handle.h"
%include                         "SheafSystem/interval_index_space_handle.h"
%include                         "SheafSystem/list_index_space_handle.h"
%include                   "SheafSystem/offset_index_space_handle.h"
%include                   "SheafSystem/primary_index_space_handle.h"
%include                         "SheafSystem/reserved_primary_index_space_handle.h"
%include                   "SheafSystem/primitives_index_space_handle.h"
%include                   "SheafSystem/singleton_index_space_handle.h"
%include                   "SheafSystem/sum_index_space_handle.h"
%include                         "SheafSystem/hub_index_space_handle.h"
%include       "SheafSystem/explicit_index_space_state.h"
%include             "SheafSystem/gathered_insertion_index_space_state.h"
%include                   "SheafSystem/scattered_insertion_index_space_state.h"
%include                        "SheafSystem/array_index_space_state.h"
%include                        "SheafSystem/hash_index_space_state.h"
%include                        "SheafSystem/interval_index_space_state.h"
%include                   "SheafSystem/list_index_space_state.h"
%include             "SheafSystem/offset_index_space_state.h"
%include             "SheafSystem/primary_index_space_state.h"
%include                   "SheafSystem/reserved_primary_index_space_state.h"
%include             "SheafSystem/primitives_index_space_state.h"
%include             "SheafSystem/singleton_index_space_state.h"
%include             "SheafSystem/sum_index_space_state.h"
%include                   "SheafSystem/primary_sum_index_space_state.h"
%include       "SheafSystem/index_space_interval_iterator.h"
%include       "SheafSystem/index_space_iterator.h"
%include             "SheafSystem/explicit_index_space_iterator.h"
%include                   "SheafSystem/array_index_space_iterator.h"
%include                   "SheafSystem/hash_index_space_iterator.h"
%include                   "SheafSystem/hub_index_space_iterator.h"
%include                   "SheafSystem/interval_index_space_iterator.h"
%include                   "SheafSystem/list_index_space_iterator.h"
%include                   "SheafSystem/offset_index_space_iterator.h"
%include                   "SheafSystem/primary_index_space_iterator.h"
%include                   "SheafSystem/primitives_index_space_iterator.h"
%include                   "SheafSystem/reserved_primary_index_space_iterator.h"
%include                   "SheafSystem/singleton_index_space_iterator.h"
%include             "SheafSystem/implicit_index_space_iterator.h"
%include                   "SheafSystem/array_implicit_index_space_iterator.h"
%include                   "SheafSystem/constant_implicit_index_space_iterator.h"
%include                   "SheafSystem/ragged_array_implicit_index_space_iterator.h"
%include                   "SheafSystem/singleton_implicit_index_space_iterator.h"
%include       "SheafSystem/name_multimap.h"
%include       "SheafSystem/poset_bounds.h"
%include       "SheafSystem/poset_bounds_descriptor.h"
%include       "SheafSystem/poset_crg_state.h"
%include       "SheafSystem/poset_dof_iterator.h"
%include       "SheafSystem/poset_dof_map.h"
%include             "SheafSystem/array_poset_dof_map.h"
%include             "SheafSystem/namespace_poset_dof_map.h"
%include             "SheafSystem/primitives_poset_dof_map.h"
%include       "SheafSystem/poset_joiner.h"
%include       "SheafSystem/poset_powerset_state.h"
%include       "SheafSystem/poset_scaffold.h"
%include       "SheafSystem/poset_table_state.h"
%include       "SheafSystem/poset_traverser.h"
%include             "SheafSystem/poset_dft.h"
%include                   "SheafSystem/poset_orderer.h"
%include                   "SheafSystem/poset_slicer.h"
%include       "SheafSystem/rc_any.h"
%include             "SheafSystem/ragged_array.h"
%include       "SheafSystem/read_write_monitor.h"
%include             "SheafSystem/poset_state.h"
%include       "SheafSystem/read_write_monitor_handle.h"
%include             "SheafSystem/poset_component.h"
%include                   "SheafSystem/abstract_poset_member.h"
%include                         "SheafSystem/partial_poset_member.h"
%include                               "SheafSystem/poset_member.h"
%include                         "SheafSystem/total_poset_member.h"
%include                               "SheafSystem/namespace_poset_member.h"
%include                               "SheafSystem/poset_member_iterator.h"
//%include                                     "SheafSystem/filtered_iterator.h"
%include                                     "SheafSystem/subposet_member_iterator.h"
%include                               "SheafSystem/schema_poset_member.h"
%include                   "SheafSystem/subposet.h"
%include             "SheafSystem/poset_state_handle.h"
%include                   "SheafSystem/namespace_poset.h"
%include                         "SheafSystem/sheaves_namespace.h"
%include                   "SheafSystem/namespace_poset_schema.h"
%include                   "SheafSystem/poset.h"
%include                         "SheafSystem/refinable_poset.h"
%include                   "SheafSystem/primitives_poset.h"
%include                   "SheafSystem/primitives_poset_schema.h"
%include       "SheafSystem/record.h"
%include             "SheafSystem/variable_length_record.h"
%include                   "SheafSystem/attributes_record.h"
%include                         "SheafSystem/dof_tuple_class_names_record.h"
%include                         "SheafSystem/dof_tuple_col_bounds_record.h"
%include                         "SheafSystem/dof_tuple_domain_offsets_record.h"
%include                         "SheafSystem/dof_tuple_schema_ids_record.h"
%include                         "SheafSystem/dof_tuple_schema_versions_record.h"
%include                         "SheafSystem/dof_tuple_types_record.h"
%include                         "SheafSystem/id_space_names_record.h"
%include                         "SheafSystem/member_names_record.h"
%include                         "SheafSystem/poset_general_record.h"
%include                         "SheafSystem/subposet_names_record.h"
%include                         "SheafSystem/table_dof_tuple_record.h"
%include                   "SheafSystem/member_record.h"
%include       "SheafSystem/record_queue.h"
%include       "SheafSystem/record_set.h"
%include             "SheafSystem/attributes_record_set.h"
%include             "SheafSystem/dof_tuple_record_set.h"
%include             "SheafSystem/member_record_set.h"
%include       "SheafSystem/schema_descriptor.h"
%include       "SheafSystem/sheaf_file.h"
%include       "SheafSystem/storage_agent.h"
%include "SheafSystem/arg_list.h"
%include "SheafSystem/auto_block.h"
%include       "SheafSystem/block.h"
%include             "SheafSystem/binary_index_block.h"
%include             "SheafSystem/id_block.h"
%include             "SheafSystem/wsv_block.h"
%include "SheafSystem/dof_descriptor_array.h"
%include "SheafSystem/dof_map_factory.h"
//%include "SheafSystem/factory.h"
%include "SheafSystem/index_iterator.h"
%include "SheafSystem/int_set.h"
%include "SheafSystem/plot.h"
%include "SheafSystem/pool.h"
%include "SheafSystem/poset_handle_factory.h"
%include "SheafSystem/poset_path.h"
%include "SheafSystem/ptr_linked_pool.h"
%include "SheafSystem/record_index.h"
%include "SheafSystem/record_map.h"
%include "SheafSystem/runnable.h"
%include "SheafSystem/scoped_index.h"
%include "SheafSystem/stop_watch.h"
%include "SheafSystem/subposet_state.h"
%include "SheafSystem/tern.h"
%include "SheafSystem/thread.h"
%include "SheafSystem/thread_condition_variable.h"
%include "SheafSystem/thread_mutex.h"
%include "SheafSystem/zn_to_bool.h"

%include "SheafSystem/deep_size.h"

//=============================================================================
// Template directives.
//=============================================================================

//$$ISSUE: Use %template directive to instantiate a ragged_array<scoped_index > type. 
//%template(ragged_array_pmi) sheaf::ragged_array<sheaf::scoped_index >;

%template(block_double) sheaf::block<double>; 
%template(wsv_block_double) sheaf::wsv_block<double>; 

//=============================================================================
// Swig warning messages to suppress.
//=============================================================================
#pragma SWIG nowarn=125 //  Use of the include path to find the input file is deprecated and will not work with ccache.
#pragma SWIG nowarn=302 // Identifier 'name' redefined (ignored).
#pragma SWIG nowarn=312 // Nested classes not currently supported (ignored).
#pragma SWIG nowarn=314 // 'identifier' is a lang keyword.
#pragma SWIG nowarn=315 // Nothing known about 'identifier'.
#pragma SWIG nowarn=317 // Specialization of non-template 'name'.
#pragma SWIG nowarn=325 // Nested class not currently supported.
#pragma SWIG nowarn=361 // operator! ignored.
#pragma SWIG nowarn=383 // operator++ ignored.
#pragma SWIG nowarn=384 // operator-- ignored.
#pragma SWIG nowarn=389 // operator[] ignored.
#pragma SWIG nowarn=401 // Nothing known about class 'name'. Ignored.
#pragma SWIG nowarn=451 // Setting const char * variable may leak memory.
#pragma SWIG nowarn=503 // Can't wrap 'identifier' unless renamed to a valid
                        //   identifier.
#pragma SWIG nowarn=508 //  Declaration of 'operator ==' shadows declaration
                        //   accessible via operator->()
#pragma SWIG nowarn=509 // Overloaded declaration is shadowed by declaration
                        //   at file:line.
#pragma SWIG nowarn=516 // Overloaded method declaration ignored. Method
                        //   declaration at file:line used.
#pragma SWIG nowarn=822 // Covariant return types not supported in Java. Proxy
                        //   method will return basetype (Java).
#pragma SWIG nowarn=842 // Covariant return types not supported in CSharp. Proxy
                        //   method will return basetype (CSharp).

