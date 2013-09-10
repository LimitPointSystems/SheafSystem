
//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// SWIG interface to geometry cluster (java version)
//

//=============================================================================

%module geometry_java_binding

%include "arrays_java.i"

%include "sheaves_common_binding_includes.i"
%include "fiber_bundles_common_binding_includes.i"
%import  "sheaves_java_binding.i"
%import  "fiber_bundles_java_binding.i"

%include "geometry_common_binding.i"

//=============================================================================
//=============================================================================

%{
#include "std_iostream.h"
%}
                                                                                                    
%inline %{
ostream* get_cout()
{
   return &cout;
}
%}
                                                                                                    
