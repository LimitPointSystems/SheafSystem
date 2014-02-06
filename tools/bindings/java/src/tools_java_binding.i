
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
// Swig module interface file for tools (java version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module tools_java_binding

//=============================================================================

%include "sheaves_common_binding_includes.i"
%include "fiber_bundles_common_binding_includes.i"
%include "geometry_common_binding_includes.i"
%include "fields_common_binding_includes.i"
%import  "sheaves_java_binding.i"
%import  "fiber_bundles_java_binding.i"
%import  "geometry_java_binding.i"
%import "fields_java_binding.i"

%include "tools_common_binding.i"

//=============================================================================

//$$ISSUE: Swig complains about the methods because the base type has a
//         different return type.
//$$TODO: Find a better solution than "%ignore".

%ignore double_dof_tuple::values();
%ignore float_dof_tuple::values();
%ignore int_dof_tuple::values();

//=============================================================================


