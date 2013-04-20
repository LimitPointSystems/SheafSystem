//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Swig module interface for fiber_bundles cluster (python version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module fiber_bundles_python_binding

//=============================================================================

%include "sheaves_common_binding_includes.i"
%import  "sheaves_python_binding.i"

%include "fiber_bundles_common_binding.i"

//=============================================================================

//$$ISSUE: Repeated from sheaves_python_binding.i.
//         Why do we have to do this?

%include carrays.i
%array_class(double, doubleArray);
%array_class(int, intArray);

%include cpointer.i
%pointer_class(double, doublePtr);
%pointer_class(int, intPtr);

//$$HACK: "raise" is a python keyword. We rename it to "Raise".
%rename(Raise) raise;

//$$HACK: The python bindings need to have some way to include the
//        ".h" files from some of the sheaves classes that are not
//        included anywhere in fiber_bundles.  So we just list them
//        here until we find a better way to do this.         

// %{

// //From sheaves/io:
// #include "attributes_record.h"
// #include "biorder_iterator.h"
// #include "block_decomposition_iterator.h"
// #include "data_converter.h"
// #include "dof_tuple_class_names_record.h"
// #include "dof_tuple_col_bounds_record.h"
// #include "dof_tuple_domain_offsets_record.h"
// #include "dof_tuple_schema_ids_record.h"
// #include "dof_tuple_schema_versions_record.h"
// #include "dof_tuple_types_record.h"
// #include "file_data_type_map.h"
// #include "filtered_depth_first_member_iterator.h"
// #include "id_space_names_record.h"
// #include "linkorder_iterator.h"
// #include "postorder_member_iterator.h"
// #include "preorder_member_iterator.h"
// #include "record.h"
// #include "record_queue.h"
// #include "variable_length_record.h"

// //From sheaves/maps:
// #include "array_id_map.h"
// #include "array_id_map_external_iterator.h"
// #include "array_id_map_internal_iterator.h"
// #include "identity_id_map.h"

// //From sheaves/support:
// #include "int_set.h"

// %}

//=============================================================================
// Swig warning messages to suppress.
//=============================================================================
// #pragma SWIG nowarn=302 //$$TODO: Describe what these messages relate to.
// #pragma SWIG nowarn=312
// #pragma SWIG nowarn=314
// #pragma SWIG nowarn=315
// #pragma SWIG nowarn=317
// #pragma SWIG nowarn=383
// #pragma SWIG nowarn=384
// #pragma SWIG nowarn=389
// #pragma SWIG nowarn=401
// #pragma SWIG nowarn=451
// #pragma SWIG nowarn=503
// #pragma SWIG nowarn=509
// #pragma SWIG nowarn=516
// #pragma SWIG nowarn=822
