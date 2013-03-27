#! /usr/bin/env python
##
## $RCSfile: unstructured_block_t.py,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:16:55 $
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##

from sheaves_python_binding import *
from fiber_bundles_python_binding import *
import os

TRUE = 1
FALSE = 0

###############################################################################
# make_unstructured_block_0d(xns, xi_size):
###############################################################################

def make_unstructured_block_0d(xns, xi_size):

    lmesh = unstructured_block.new_host(xns, "unstructured_mesh_base_space_0d", 1);
    lmesh.get_read_write_access()

    lproto_path = poset_path(unstructured_block.prototypes_poset_name(),
                             "point")

    lblock = unstructured_block(lmesh, lproto_path, xi_size)
    lblock.put_name("unstructured_block_0d", TRUE, FALSE);
    lblock.detach_from_state();

    lmesh.release_access();

###############################################################################
# make_unstructured_block_1d(xns, xi_size):
###############################################################################

def make_unstructured_block_1d(xns, xi_size):

    lmesh = unstructured_block.new_host(xns, "unstructured_mesh_base_space_1d", 1);
    lmesh.get_read_write_access()

    lproto_path = poset_path(unstructured_block.prototypes_poset_name(),
                             "segment_complex")

    lblock = unstructured_block(lmesh, lproto_path, xi_size)
    lblock.put_name("unstructured_block_1d", TRUE, FALSE);
    lblock.detach_from_state();

    lmesh.release_access();

###############################################################################
# make_unstructured_block_2d(xns, xi_size, xj_size):
###############################################################################

def make_unstructured_block_2d(xns, xi_size, xj_size):

    lmesh = unstructured_block.new_host(xns, "unstructured_mesh_base_space_2d", 2);
    lmesh.get_read_write_access()

    ## Make quad block.

    lproto_quad_path = poset_path(unstructured_block.prototypes_poset_name(),
                                  "quad_complex")

    lquad_block = unstructured_block(lmesh, lproto_quad_path, xi_size, xj_size)
    lquad_block.put_name("unstructured_quad_block_2d", TRUE, FALSE);
    lquad_block.detach_from_state();

    ## Make triangle block.

    lproto_triangle_path = poset_path(unstructured_block.prototypes_poset_name(),
                                      "triangle_nodes")

    ltriangle_block = unstructured_block(lmesh, lproto_triangle_path, xi_size, xj_size)
    ltriangle_block.put_name("unstructured_triangle_block_2d", TRUE, FALSE);
    ltriangle_block.detach_from_state();

    lmesh.release_access();

###############################################################################
# make_unstructured_block_3d(xns, xi_size, xj_size, xk_size):
###############################################################################

def make_unstructured_block_3d(xns, xi_size, xj_size, xk_size):

    lmesh = unstructured_block.new_host(xns, "unstructured_mesh_base_space_3d", 3);
    lmesh.get_read_write_access()

    lproto_path = poset_path(unstructured_block.prototypes_poset_name(),
                             "hex_nodes")

    lblock = unstructured_block(lmesh, lproto_path, xi_size, xj_size, xk_size)
    lblock.put_name("unstructured_quad_block_3d", TRUE, FALSE);
    lblock.detach_from_state();

    lmesh.release_access();
    
###############################################################################
# make_hex_faces_nodes_block(xns, xi_size, xj_size, xk_size):
###############################################################################

def make_hex_faces_nodes_block(xns, xi_size, xj_size, xk_size):

    lmesh = unstructured_block.new_host(xns, "hex_faces_nodes_base_space", 3);
    lmesh.get_read_write_access()

    lproto_path = poset_path(unstructured_block.prototypes_poset_name(),
                             "hex_faces_nodes")

    lblock = unstructured_block(lmesh, lproto_path, xi_size, xj_size, xk_size)
    lblock.put_name("hex_faces_nodes_block", TRUE, FALSE);
    lblock.detach_from_state();

    lmesh.release_access();

###############################################################################
# main(file_name):
###############################################################################

def main(argv):

    ## Handle command line arguments.

    i_size = 1
    if(len(argv) >= 2): i_size = int(argv[1])

    j_size = 1
    if(len(argv) >= 3): j_size = int(argv[2])

    k_size = 1
    if(len(argv) >= 4): k_size = int(argv[3])

    path = argv[0][0:-3] ## Splice off ".py" from name
    name = (os.path.split(path))[1]

    ## Create the namespace poset.
    
    lns = fiber_bundles_namespace(name)
    lns.get_read_write_access()

    make_unstructured_block_0d(lns, i_size);
    make_unstructured_block_1d(lns, i_size);
    make_unstructured_block_2d(lns, i_size, j_size);
    make_unstructured_block_3d(lns, i_size, j_size, k_size);
    make_hex_faces_nodes_block(lns, i_size, j_size, k_size);

    ##  Write the namespace to a file.

    sa = storage_agent(name +".hdf")
    sa.write_entire(lns)

    del lns

    
###############################################################################

if __name__ == '__main__':  
    import sys
    
    if len(sys.argv) > 4:
        print 'Usage: ' + sys.argv[0] + ' [size_0 size_1 size_2]' 
    else:
        main(sys.argv)
