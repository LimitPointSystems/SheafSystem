
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
// SWIG module interface to sheaves cluster (csharp version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module sheaf_csharp_binding

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

%include "sheaf_common_binding.i  "

//=============================================================================

