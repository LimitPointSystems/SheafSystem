
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
//            is to be inserted directly into the generated code.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "geometry_common_binding.i" as well.

//=============================================================================

%{

#include "geometry.h"

#include "d_bin_coordinates.h"
#include "d_bounding_box.h"
#include "d_tree_point_locator_node.h"
#include "d_tree_point_locator_path.h"

#include "point_locator.h"
#include       "cylindrical_point_locator.h"
#include             "array_cylindrical_point_locator.h"
#include       "d_bin_point_locator.h"
#include             "d_array_point_locator.h"
#include             "d_tree_point_locator.h"
#include       "d_uniform_point_locator.h"
#include       "db0_point_locator.h"

#include "mesh_generator.h"
#include       "tetgen_generator.h"

#include "sec_ed_invertible.h"

using namespace geometry;

%}
