
//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Common SWIG interface to geometry cluster
//

//=============================================================================

//$$SCRIBBLE: This file contains only the part of the Swig interface which
//            is to be lists the classes, etc. to be wrapped.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "geometry_common_binding_includes.i" as well.

//=============================================================================

// Include the list of files to be inserted into the generated code.

%include "geometry_common_binding_includes.i"

//=============================================================================

//$$ISSUE: Ingoring the shift operators because it causes errors when
//         building the python bindings.  These errors appeared when
//         the namespaces were introduced.

%ignore *::operator<<;
%ignore *::operator>>;

//$$ISSUE: Ingoring intersect. It causes unresolved symbol errors during win32 link phase.
%ignore geometry::intersect;

//=============================================================================

// The list of classes, etc. for which wrappers will be generated.

//$$SCRIBBLE: Note that order is important in the following list.  It must
//            follow the class hierarchies.

//=============================================================================

%include "geometry.h"

%include "d_bin_coordinates.h"
%include "d_bounding_box.h"
%include "d_tree_point_locator_node.h"
%include "d_tree_point_locator_path.h"

%include "point_locator.h"
%include       "cylindrical_point_locator.h"
%include             "array_cylindrical_point_locator.h"
%include       "d_bin_point_locator.h"
%include             "d_array_point_locator.h"
%include             "d_tree_point_locator.h"
%include       "d_uniform_point_locator.h"
%include       "db0_point_locator.h"

%include "sec_ed_invertible.h"

//=============================================================================
