
//
// $RCSfile: sheaves_csharp_binding.i,v $ $Revision: 1.3 $ $Date: 2012/03/01 00:41:16 $
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// SWIG module interface to sheaves cluster (csharp version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module sheaves_csharp_binding

//=============================================================================

%include <arrays_csharp.i>
%include "arrays_csharp.i"

//=============================================================================
// Ignore directives:
//=============================================================================

// These enums cause compile errors when making the csharp assembly.

%ignore sheaf::poset_dof_iterator::anchor_version_index;

// $$HACK: Ignore static_const_int enums to remove warnings.

%ignore *::static_const_int;


//=============================================================================

// Set all NOT_A_... macro values to int.MaxValue.

%csconstvalue("int.MaxValue") NOT_A_PRIMITIVE_TYPE;
%csconstvalue("int.MaxValue") NOT_A_STANDARD_DOF_TUPLE_INDEX;
%csconstvalue("int.MaxValue") NOT_A_STANDARD_MEMBER_INDEX;
%csconstvalue("int.MaxValue") NOT_A_STANDARD_VERSION_INDEX;
%csconstvalue("int.MaxValue") NOT_A_STANDARD_SUBPOSET_INDEX;

//=============================================================================

%include "sheaves_common_binding.i"

//=============================================================================

