#! /usr/bin/env python
##
##
## Copyright (c) 2014 Limit Point Systems, Inc.
##

from sheaf_python_binding import *
from fiber_bundle_python_binding import *
import os

TRUE = 1
FALSE = 0

###############################################################################
# main(file_name):
###############################################################################

def main(argv):

    ## Handle command line arguments.

    size_0 = 1
    if(len(argv) >= 2): size_0 = int(argv[1])

    size_1 = 1
    if(len(argv) >= 3): size_1 = int(argv[2])

    size_2 = 1
    if(len(argv) >= 4): size_2 = int(argv[3])

    path = argv[0][0:-3] ## Splice off ".py" from name
    name = (os.path.split(path))[1]

    ## Create the namespace poset.
    
    lns = fiber_bundles_namespace(name)
    lns.get_read_write_access()

    lmesh = structured_block_3d.new_host(lns, name + "_mesh")

    lblock = structured_block_3d(lmesh, size_0, size_1, size_2, TRUE)
    lblock.get_read_write_access()
    lblock.put_name(name +"_block", TRUE, FALSE)

    ##lmesh.to_stream()

    ## Test the refinement map.

    print "\n##### Begin refinement map test ###############\n"

    lpt = chart_point_3d(lblock.index(), -1.0, -1.0, -1.0)

    lref_pt = chart_point_3d()

    coords = [-1.0, -0.5, 0.0, 0.5, 1.0]

    for lxcoord in coords:
        lpt.put_local_coord(0, lxcoord)
        for lycoord in coords:
            lpt.put_local_coord(1,  lycoord)
            for lzcoord in coords:
                lpt.put_local_coord(2,  lzcoord)
                lblock.refine_point_pa(lpt, lref_pt)
                print "point:", lpt.to_string(),
                print "\trefined point:", lref_pt.to_string(),
                lblock.unrefine_point_pa(lref_pt, lpt)
                print "\tunrefined point:", lpt.to_string(), "\n"
                 
    print "\n##### End refinement map test ###############\n"

    ## Cleanup.

    lblock.detach_from_state()
    lmesh.release_access()

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
