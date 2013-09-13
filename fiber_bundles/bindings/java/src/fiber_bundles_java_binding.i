
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

//
// Swig module interface for fiber_bundles cluster (java version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module fiber_bundles_java_binding

//=============================================================================

%include "arrays_java.i"

%include "sheaves_common_binding_includes.i"
%import "sheaves_java_binding.i"

%include "fiber_bundles_common_binding.i"

//=============================================================================

// Add  "dynamic_cast" functions to classes which have a "class_name" function.

%extend fiber_bundle::base_space_poset 
{
    static base_space_poset  *dynamic_cast(sheaf::poset_state_handle *xpsh)
    {
        return dynamic_cast<base_space_poset  *>(xpsh);
    }
};

%extend fiber_bundle::sec_rep_space
{
    static sec_rep_space *dynamic_cast(sheaf::poset_state_handle *xpsh)
    {
        return dynamic_cast<sec_rep_space *>(xpsh);
    }
};

%extend fiber_bundle::binary_section_space_schema_poset
{
    static binary_section_space_schema_poset *dynamic_cast(sheaf::poset_state_handle *xpsh)
    {
        return dynamic_cast<binary_section_space_schema_poset *>(xpsh);
    }
};

//%extend fiber_bundle::ternary_section_space_schema_poset
//{
//    static ternary_section_space_schema_poset *dynamic_cast(sheaf::poset_state_handle *xpsh)
//    {
//        return dynamic_cast<ternary_section_space_schema_poset *>(xpsh);
//    }
//};
