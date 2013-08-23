#! /usr/bin/env python
#
# Copyright (c) 2013 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

## Test driver for class section_pusher (3d version).


import os, sys
from fields_python_binding import *
from fiber_bundles_python_binding import *
from sheaves_python_binding import *

###############################################################################
# Convenience function to print  test case headers.:
###############################################################################

def print_header(title):

    print
    print "==================================================================="
    print title
    print "==================================================================="
    print


###############################################################################
# make_test_case_3d_uniform:
###############################################################################

def make_test_case_3d_uniform(xname,
                               xns,
                               xi_size,
                               xj_size,
                               xmin,
                               ymin,
                               xmax,
                               ymax):
    
    bounds = doubleArray(4)
    bounds[0] = xmin
    bounds[1] = ymin
    bounds[2] = xmax
    bounds[3] = ymax

    result = test_case_3d_uniform(xname, xns, xi_size, xj_size, bounds, 4)

    return result


###############################################################################
# make_test_case_3d_general_quads:
###############################################################################

def make_test_case_3d_general_quads(xname,
                                     xns,
                                     xi_size,
                                     xj_size,
                                     xmin,
                                     ymin,
                                     xmax,
                                     ymax):
    
    corner_coords = doubleArray(8)
    corner_coords[0] = xmin
    corner_coords[1] = ymin
    corner_coords[2] = xmax
    corner_coords[3] = ymin
    corner_coords[4] = xmax
    corner_coords[5] = ymax
    corner_coords[6] = xmin
    corner_coords[7] = ymax

    result = test_case_3d_general(xname, xns,  xi_size, xj_size,
                                   corner_coords, 8,
                                   block_connectivity.QUAD)

    return result



###############################################################################
# make_test_case_3d_general_triangles:
###############################################################################

def make_test_case_3d_general_triangles(xname,
                                         xns,
                                         xi_size,
                                         xj_size,
                                         xmin,
                                         ymin,
                                         xmax,
                                         ymax):
    
    corner_coords = doubleArray(8)
    corner_coords[0] = xmin
    corner_coords[1] = ymin
    corner_coords[2] = xmax
    corner_coords[3] = ymin
    corner_coords[4] = xmax
    corner_coords[5] = ymax
    corner_coords[6] = xmin
    corner_coords[7] = ymax

    result = test_case_3d_general(xname, xns,  xi_size, xj_size,
                                   corner_coords, 8,
                                   block_connectivity.TRIANGLE)

    return result


###############################################################################
# print_push:
###############################################################################

def print_push(source, destination, xdest_field):

    print
    print "==================================================================="
    print "Push from:", source.test_scalar().name(), " in", source.test_space().name()
    print "       to:", xdest_field.name(), " in", destination.test_space().name()
    print "==================================================================="
    
    print
    print "Source:"
    print "======="

    source.print_dofs(source.test_scalar())

    print
    print "Destination:"
    print "============"

    destination.print_dofs(xdest_field)

    print

###############################################################################
# push:
###############################################################################

def push(source, destination):

    ## Create a section pusher from the source to destination section spaces.

    sp = section_pusher(source.test_space(),
                        destination.test_space(),
                        source.coords(),
                        destination.coords())

    ## Push the source field to the destination.

    result = destination.test_scalar().clone()
    result.put_name("push_of_"+source.test_scalar().name())

    sp.push_pa(source.test_scalar(), result)

    ## Print the results of the push.

    print_push(source, destination, result)

    return result



###############################################################################
# test_uniform_to_hex_to_uniform:
###############################################################################

def test_uniform_to_hex_to_uniform():

    print_header("Test uniform to hex to uniform. Uniform = fine, hex = coarse.")

    lns = fiber_bundles_namespace("test")
    lns.get_read_write_access()

    ## An 4x4x4 uniform mesh on with bounds (-2, -2, -2) and (2, 2, 2).

    fine = test_case_3d_uniform("fine", lns, 4, 4, 4, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## A 2x2x2 hex mesh on with bounds (-2, -2, -2) and (2, 2, 2).

    coarse = test_case_3d_uniform("coarse", lns, 2, 2, 2, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## Push the "fine" field to the "coarse" field.

    push(fine, coarse)

    ## Push the "coarse" field back to the "fine" field.

    push(coarse, fine)



###############################################################################
# test_fine_to_coarse_to_fine:
###############################################################################

def test_fine_to_coarse_to_fine():

    print_header("Test fine to coarse to fine (all hexes)")

    lns = fiber_bundles_namespace("test")
    lns.get_read_write_access()

    ## An 4x4x4 hex (fine) mesh on with bounds (-2, -2, -2) and (2, 2, 2).

    fine = test_case_3d_general("fine", lns, 4, 4, 4, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## A 2x2x2 hex (coarse) mesh on with bounds (-2, -2, -2) and (2, 2, 2).

    coarse = test_case_3d_general("coarse", lns, 2, 2, 2, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## Push the "fine" field to the "coarse" field.

    push(fine, coarse)

    ## Push the "coarse" field back to the "fine" field.

    push(coarse, fine)



###############################################################################
# test_coarse_to_fine_to_coarse:
###############################################################################
    
def test_coarse_to_fine_to_coarse():

    print_header("Test coarse to fine to coarse (all hexes)")

    lns = fiber_bundles_namespace("test")
    lns.get_read_write_access()

    ## A 2x2x2 hex (coarse) mesh on with bounds (-2, -2, -2) and (2, 2, 2).

    coarse = test_case_3d_general("coarse", lns, 2, 2, 2, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## An 4x4x4 hex (fine) mesh on with bounds (-2, -2, -2) and (2, 2, 2).

    fine = test_case_3d_general("fine", lns, 4, 4, 4, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## Push the "coarse" field to the "fine" field.

    push(coarse, fine)

    ## Push the "fine" field back to the "coarse" field.

    push(fine, coarse)



###############################################################################
# test_small_to_large_to_small:
###############################################################################

def test_small_to_large_to_small():

    print_header("Test extension")

    lns = fiber_bundles_namespace("test")
    lns.get_read_write_access()


    ## Make "small" test case.
    ## A 2x2x2 hex mesh on a square with bounds (-2, -2, -2) and (2, 2, 2).

    small = test_case_3d_general("small", lns, 2, 2, 2, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0)

    ## Make "large" test case.
    ## A 4x4x4 hex mesh on a square with bounds (-3, -3, -3) and (3, 3, 3).

    large = test_case_3d_general("large", lns, 4, 4, 4, -3.0, -3.0, -3.0, 3.0, 3.0, 3.0)

    ## Push the "small" field to the "large" field.

    push(small, large)

    ## Push the "large" field back to the "small" field.

    push(large, small)


###############################################################################
# test_combination:
###############################################################################

def test_combination():

    ## Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
    ## that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
    ## fine->fine.  Also tests cases:
    ##
    ## 1)  the destination coordinate is not within any source edge
    ## 2)  the destination coordinate is identical to some source coordinate
    ## 3)  the destination coordinate is within some source edge but not
    ## identical to any source coordinate
    ##
    ## All meshes start with coordinate 0 (exactly).  This tests 2).
    ##
    ## To test 1), every push should be from a "short" mesh to a "long"
    ## mesh.  If we arrange the maximum coordinate of each mesh thusly:
    ##      fine2 < coarse < fine1
    ## then we guarantee that we test condition 1).
    ##
    ## To test 3), the destination mesh must have an edge length < total length
    ## of the source mesh but not an integer multiple of the source mesh edge
    ## length.
    ##
    ## The following conditions are desirable.  They ensure that the test
    ## exercises extension.
    ##
    ##     coarse_mesh_max_coord < fine_mesh_1_max_coord
    ##     fine_mesh_2_max_coord < coarse_mesh_max_coord
    ##
    ##   int fine_mesh_1_edge_ct = 5;
    ##   int fine_mesh_2_edge_ct = 4;
    ##   int coarse_mesh_edge_ct = 2;
  
    ##   double fine_mesh_1_min_coord =  0;
    ##   double fine_mesh_2_min_coord =  0;
    ##   double coarse_mesh_min_coord =  0;
  
    ##   double fine_mesh_1_max_coord = 10;
    ##   double fine_mesh_2_max_coord =  6;
    ##   double coarse_mesh_max_coord =  8;
  
    print_header("Test combination")

    lns = fiber_bundles_namespace("test")
    lns.get_read_write_access()
  
    ## Make the "fine_1" test case (quads).

    fine_1 = test_case_3d_general("fine_1", lns, 5, 5, 5, 0.0, 0.0, 0.0, 10.0, 10.0, 10.0)
  
    ## Make the "fine_2" test case (triangles).

    fine_2 = test_case_3d_general("fine_2", lns, 4, 4, 4, 0.0, 0.0, 0.0, 6.0, 6.0, 6.0)

    ## Make the "coarse" test case.

    coarse = test_case_3d_general("coarse", lns, 2, 2, 2, 0.0, 0.0, 0.0, 8.0, 8.0, 8.0)

    ## Case 1: fine mesh 1 -> fine mesh 2

    push(fine_1, fine_2)

    ## Case 2: fine mesh 2 -> coarse mesh

    push(fine_2, coarse)

    ## Case 3: coarse mesh -> fine mesh 1

    push(coarse, fine_1)


###############################################################################
# main():
###############################################################################

def main():

    ## Test uniform to hex to uniform.

    test_uniform_to_hex_to_uniform()

    ## Test fine to coarse to fine (all hexs).

    test_fine_to_coarse_to_fine()

    ## Test coarse to fine to coarse (all hexs).

    test_coarse_to_fine_to_coarse()

    ## Test small domain to large domain to small domain (all hexs).
    ## Small domain only partially covers large domain.

    test_small_to_large_to_small()

    ## Test a combination of meshes.
    ## Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
    ## that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
    ## fine->fine.  Also tests cases:
    ##
    ## 1)  the destination coordinate is not within any source edge
    ## 2)  the destination coordinate is identical to some source coordinate
    ## 3)  the destination coordinate is within some source edge but not
    ##     identical to any source coordinate.

    test_combination()


###############################################################################

if __name__ == '__main__':
    main()

    import os
    os._exit(0)

###############################################################################

