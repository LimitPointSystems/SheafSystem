
//
// $RCSfile: fields_java_binding.i,v $ $Revision: 1.5 $ $Date: 2013/01/12 17:17:19 $
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// SWIG interface to fields cluster (java version)
//

//=============================================================================

%module fields_java_binding

%include "arrays_java.i"

//$$ISSUE: We might want to build the fields bindings but not components/tools.
//         So what do we do here?

%import "geometry_java_binding.i"
%include "fields_common_binding.i"

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
                                                                                                    
