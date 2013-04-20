//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Swig module interface for fiber_bundles cluster (java version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module fiber_bundles_java_binding

//=============================================================================

%include "arrays_java.i"

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
