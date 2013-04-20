
//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// SWIG interface to Geometry cluster (python version)
//

//=============================================================================

%module geometry_python_binding

%include "sheaves_common_binding_includes.i"
%include "fiber_bundles_common_binding_includes.i"
%import  "sheaves_python_binding.i"
%import  "fiber_bundles_python_binding.i"

%include "geometry_common_binding.i"

//=============================================================================

//$$ISSUE: Repeated from sheaves_python_binding.swg.
//         Why do we have to do this?

%include carrays.i
%array_class(double, doubleArray);
%array_class(int, intArray);

%include cpointer.i
%pointer_class(double, doublePtr);
%pointer_class(int, intPtr);

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

//=============================================================================
