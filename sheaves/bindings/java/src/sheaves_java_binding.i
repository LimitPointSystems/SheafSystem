
//
// $RCSfile: sheaves_java_binding.i,v $ $Revision: 1.5 $ $Date: 2013/01/12 17:17:32 $
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
