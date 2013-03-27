
//
// $RCSfile: geometry_java_binding.i,v $ $Revision: 1.4 $ $Date: 2013/01/12 17:17:29 $
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

//$$ISSUE: We might want to build the geometry bindings but not components/tools.
//         So what do we do here?

%import "fiber_bundles_java_binding.i"
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
                                                                                                    
