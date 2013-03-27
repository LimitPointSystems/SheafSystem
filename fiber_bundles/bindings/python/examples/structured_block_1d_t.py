#! /usr/bin/env python
##
## $RCSfile: structured_block_1d_t.py,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:16:55 $
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
# main(file_name):
###############################################################################

def main(argv):

    ## Handle command line arguments.
    
    size_0 = 1
    if(len(argv) >= 2): size_0 = int(argv[1])

    path = argv[0][0:-3] ## Splice off ".py" from name
    name = (os.path.split(path))[1]

    ## Create the namespace poset.
    
    lns = fiber_bundles_namespace(name)
    lns.get_read_write_access()

    lmesh = structured_block_1d.new_host(lns, name + "_mesh")

    lblock = structured_block_1d(lmesh, size_0, TRUE)
    lblock.get_read_write_access()
    lblock.put_name(name +"_block", TRUE, FALSE)

    ##lmesh.to_stream()

    ## Test the refinement map.

    print "\n##### Begin refinement map test ###############\n"

    lpt = chart_point_1d(lblock.index(), -1.0)

    lref_pt = chart_point_1d()

    coords = [-1.0, -0.5, 0.0, 0.5, 1.0]

    for lxcoord in coords:
        lpt.put_local_coord(0, lxcoord)
        lblock.refine_point_pa(lpt, lref_pt)
        print "point:", lpt.to_string(),
        print "\trefined point:", lref_pt.to_string(),
        lblock.unrefine_point_pa(lref_pt, lpt)
        print "\tunrefined point:", lpt.to_string(), "\n"
                 
    print "\n##### End refinement map test ###############\n"


    ## Make uniform (coordinate) sec_rep_space.

    luniform_path = poset_path("sec_rep_descriptors", "vertex_block_dlinear")

    luniform_schema_path = sec_e1.make_schema(lns,
                                    "coordinate_section_space_schema",
                                    luniform_path,
                                    lblock.path())

    luniform_space = sec_e1.new_host(lns,
                                  "coordinate_section_space",
                                  luniform_schema_path)

    ## Make non-uniform (property) sec_rep_space.

    lnon_uniform_path= poset_path ("sec_rep_descriptors", "vertex_element_dlinear")

    lnon_uniform_schema_path = sec_at0.make_schema(lns,
                                        "property_section_space_schema",
                                        lnon_uniform_path,
                                        lblock.path());

    lnon_uniform_space = sec_at0.new_host(lns,
                                      "property_section_space",
                                      lnon_uniform_schema_path);

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
    
    if len(sys.argv) > 2:
        print 'Usage: ' + sys.argv[0] + ' [size_0]' 
    else:
        main(sys.argv)
