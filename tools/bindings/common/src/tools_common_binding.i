//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Common Swig interface file for tools modules
//

//=============================================================================

//$$SCRIBBLE: This file contains only the part of the Swig interface which
//            is to be lists the classes, etc. to be wrapped.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "tools_common_binding_includes.i" as well.

//=============================================================================

// Include the list of files to be inserted into the generated code.

%include "tools_common_binding_includes.i"

//=============================================================================

// The list of classes, etc for which wrappers will be generated.

//$$SCRIBBLE: Note that order is important in the following list.  It must
//            follow the class hierarchies.

//=============================================================================

%include "vtk_poly_data_builder.h"
%include "vtk_abstract_grid_builder.h"
%include "vtk_unstructured_grid_builder.h"
