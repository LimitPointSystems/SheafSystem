
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
//
// SWIG module interface to sheaves cluster (java version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module sheaves_java_binding

//=============================================================================

%include "arrays_java.i"

//=============================================================================

// Change the return types for the "javabody" typemap from "rpotected" to "public".

SWIG_JAVABODY_METHODS(public, public, SWIGTYPE *, \
                      SWIGTYPE &, SWIGTYPE [], SWIGTYPE (CLASS::*))

//=============================================================================

//$$HACK: "clone" is a method of "Object.java". We rename it to "klone".

%rename(klone) clone;

//=============================================================================

//$$HACK: "class_name" is a a method of several sheaves classes.
//         We rename them to "klass_name".

%rename(klass_name) class_name;

//=============================================================================

%include "sheaves_common_binding.i"

//=============================================================================

// Add  "dynamic_cast" functions to classes which have a "class_name" function.

%extend sheaf::namespace_poset
{
    static namespace_poset *dynamic_cast(poset_state_handle *xpsh)
    {
        return dynamic_cast<namespace_poset *>(xpsh);
    }
};

%extend sheaf::primitives_poset
{
    static primitives_poset *dynamic_cast(poset_state_handle *xpsh)
    {
        return dynamic_cast<primitives_poset *>(xpsh);
    }
};

%extend sheaf::primitives_poset_schema
{
    static primitives_poset_schema *dynamic_cast(poset_state_handle *xpsh)
    {
        return dynamic_cast<primitives_poset_schema *>(xpsh);
    }
};

%extend sheaf::namespace_poset_schema
{
    static namespace_poset_schema *dynamic_cast(poset_state_handle *xpsh)
    {
        return dynamic_cast<namespace_poset_schema *>(xpsh);
    }
};

%extend sheaf::poset
{
    static poset *dynamic_cast(poset_state_handle *xpsh)
    {
        return dynamic_cast<poset *>(xpsh);
    }
};

//=============================================================================
