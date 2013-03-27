#! /usr/bin/env python

##
## $RCSfile: poset_t.py,v $ $Revision: 1.6 $ $Date: 2013/01/12 17:17:33 $
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##



from sheaves_python_binding import *

TRUE = 1
FALSE = 0

###############################################################################
# empty_poset_test():
###############################################################################

def empty_poset_test():

    global empty_poset
    
    test_namespace.get_read_write_access()
    empty_poset = \
      poset(test_namespace, test_namespace.primitives().schema(), "empty")
    ##empty_poset.detach_from_state()   
    test_namespace.release_access()


###############################################################################
# new_top_level_test():
###############################################################################

def new_top_level_test():

    global R2_schema

    ## Get read-write access to the namespace.

    test_namespace.get_read_write_access()

    ## Iterate over its jims.

    print "Iterating over jims of test_namespace."

    itr = postorder_member_iterator(test_namespace.top(), "jims");
    while not itr.is_done():
        print itr.item().index(), "  ",
        itr.next()
    print

    ## Print out its members.

    print "test_namespace contains:"
    test_namespace.to_stream()
    
    ## Make handles for the primitive types.

    primitives = test_namespace.primitives();

    print "primitives poset contains:"
    primitives.to_stream() 

    ## Print out primitives_poset_schema.

    print "primitives poset schema contains:"
    primitives.schema().host().to_stream()
 
    ## Make a new poset.

    R2_schema = poset(test_namespace, primitives.schema(), "R2_schema")

    ## Get read-write access to it.

    R2_schema.get_read_write_access()

    ltable_dofs = subposet(R2_schema)
    lrow_dofs = subposet(R2_schema)

    ## Enter edit mode.

    R2_schema.begin_jim_edit_mode()

    ##  Make the jims.

    x_comp = total_poset_member(R2_schema, primitives.double_type().dof_map(FALSE))
    ##x_comp.put_name("x_component", true, false)
    x_comp.put_name("x_component", TRUE, FALSE)
    lrow_dofs.insert_member(x_comp)

    y_comp = total_poset_member(R2_schema, primitives.double_type().dof_map(FALSE))
    ##y_comp.put_name("y_component", true, false)
    y_comp.put_name("y_component", TRUE, FALSE)
    lrow_dofs.insert_member(y_comp)

    ## Exit edit mode.

    R2_schema.end_jim_edit_mode()

    ## Schematize the poset and all of its members.

    R2_schema.schematize(ltable_dofs, lrow_dofs, TRUE);

    x_comp.detach_from_state()
    y_comp.detach_from_state()
    
    ltable_dofs.detach_from_state()
    lrow_dofs.detach_from_state()

    ## Print it out.

    print "R2_schema contains:"
    R2_schema.to_stream()
    
    ## Release access to posets.
    
    R2_schema.release_access()
    test_namespace.release_access()
    

###############################################################################
# product_rep_test():
###############################################################################

def product_rep_test():

    global R2

    test_namespace.get_read_write_access()
    R2_schema.get_read_access()

    R2 = poset(test_namespace, R2_schema.top(), "R2")
    R2.get_read_write_access()

    R2.begin_jim_edit_mode()

    ##$$ISSUE: Must be a better way to do this in python!
    ##$$ISSUE: Need a sizeof function.
    dofs = doubleArray(2)
    dofs_size = 2*8
    
    mbr = total_poset_member(R2)
    mbr.put_name("zero", TRUE, FALSE)
    dofs[0] = 0.0
    dofs[1] = 0.0
    mbr.put_dof_tuple(dofs, dofs_size)

    mbr.new_jim_state(R2)
    mbr.put_name("i-hat", TRUE, FALSE)
    dofs[0] = 1.0
    dofs[1] = 0.0
    mbr.put_dof_tuple(dofs, dofs_size)

    mbr.new_jim_state(R2)
    mbr.put_name("j-hat", TRUE, FALSE)
    dofs[0] = 0.0
    dofs[1] = 1.0
    mbr.put_dof_tuple(dofs, dofs_size)

    R2.end_jim_edit_mode()

    mbr.detach_from_state()

    print "R2 contains:"
    R2.to_stream()

    ##  Test is_schema()

##    print "R2_schema.is_schema() == ", R2_schema.is_schema()
##    print "R2.is_schema() == ", R2.is_schema()

    R2.release_access()
    ##R2.detach_from_state()

    R2_schema.release_access()
    test_namespace.release_access()
   

###############################################################################
#  new_jim_test():
###############################################################################

def new_jim_test():

    print "\n*** ENTERING NEW_JIM_TEST *************************\n"

    global cells, t, e0, e1, e2, v0, v1, v2

    ## Make a triangle.

    ##       t
    ##       *
    ##      ***
    ##     * * *
    ##    *  *  *
    ##   *   *   *
    ## e0    e1   e2
    ## *     *     *
    ## **   ***   **
    ## * * * * * * *
    ## *  *  *  *  *
    ## * * * * * * *
    ## **   ***   **
    ## *     *     *
    ## v0    v1   v2

    ## Get read-write access to the namespace.

    test_namespace.get_read_write_access()

    primitives = test_namespace.primitives()

    ref_type = primitives.poset_member_index_type()

    ## Primitives already schematized, can just use them as schema.

    cells = poset(test_namespace, ref_type, "cells")
    cells.get_read_write_access()
    cells.begin_jim_edit_mode()

    ##$$ISSUE: Must be a better way to do this in python!
    dof = doubleArray(1)
    dof_size = 8

    v = total_poset_member(cells)
    v.put_name("standard vertex", TRUE, FALSE)
    dof[0] = 2
    v.put_dof_tuple(dof, dof_size)

    e = total_poset_member(cells)
    e.put_name("standard edge", TRUE, FALSE)
    dof[0] = 3
    e.put_dof_tuple(dof, dof_size)

    t = total_poset_member(cells)
    t.put_name("standard triangle", TRUE, FALSE)
    dof[0] = 4
    t.put_dof_tuple(dof, dof_size)

    e0 = total_poset_member(cells)
    e0.put_name("e0", TRUE, FALSE)
    dof[0] = 3
    e0.put_dof_tuple(dof, dof_size)

    e1 = total_poset_member(cells)
    e1.put_name("e1", TRUE, FALSE)
    dof[0] = 3
    e1.put_dof_tuple(dof, dof_size)

    e2 = total_poset_member(cells)
    e2.put_name("e2", TRUE, FALSE)
    dof[0] = 3
    e2.put_dof_tuple(dof, dof_size)

    v0 = total_poset_member(cells)
    v0.put_name("v0", TRUE, FALSE)
    dof[0] = 2
    v0.put_dof_tuple(dof, dof_size)

    v1 = total_poset_member(cells)
    v1.put_name("v1", TRUE, FALSE)
    dof[0] = 2
    v1.put_dof_tuple(dof, dof_size)

    v2 = total_poset_member(cells)
    v2.put_name("v2", TRUE, FALSE)
    dof[0] = 2
    v2.put_dof_tuple(dof, dof_size)

    t.create_cover_link(e0)
    t.create_cover_link(e1)
    t.create_cover_link(e2)
    
    e0.create_cover_link(v0)
    e0.create_cover_link(v1)

    e1.create_cover_link(v0)
    e1.create_cover_link(v2)

    e2.create_cover_link(v1)
    e2.create_cover_link(v2)

    cells.end_jim_edit_mode()
    
    print "Cells poset contains:"
    cells.to_stream()

    ## Release access to namespace.

    test_namespace.release_access()

    v.detach_from_state()
    e.detach_from_state()

    print
    print "\n*** LEAVING NEW_JIM_TEST *************************\n"
    print

###############################################################################
# new_jrm_test():
###############################################################################

def new_jrm_test():

    print "\n*** ENTERING NEW_JRM_TEST *********************\n"

    ## Get read-write access to the namespace

    test_namespace.get_read_write_access()

    ## Now make some jrms in the cells lattice

    ## jrm containing 2 vertices

    print "\n*** NEW_JRM_TEST 1 *********************\n"

    v0 = total_poset_member()
    v1 = total_poset_member()
    ##$$ISSUE: vertex2_ids is now an array of type relative_index!
    ##vertex2_ids = intArray(2)
    vertex2_ids = relative_indexArray(2)
    vertex2_ids[0] = v0.index()
    vertex2_ids[1] = v1.index()

    print "\n*** NEW_JRM_TEST 2 *********************\n"

    vertexs2 = total_poset_member()
    cells = poset()
    
    print "\n*** NEW_JRM_TEST 3 *********************\n"

    vertexs2.new_jrm_state(cells, vertex2_ids, 2, tern.TRUE, FALSE)

    print "\n*** NEW_JRM_TEST 4 *********************\n"

    vertexs2.put_name("2 vertices")

    print "Cells lattice with 2 vertexs jrm:"
    cells.to_stream()

    ## jrm containing other 2 vertices

    vertexo2_ids = relative_indexArray(2)
    vertexo2_ids[0] = v2.index()
    vertexo2_ids[1] = v1.index()

    vertexso2 = total_poset_member()
    vertexso2.new_jrm_state(cells, vertexo2_ids, 2)
    vertexso2.put_name("other 2 vertices")

    print "Cells lattice with other 2 vertexs jrm:"
    cells.to_stream()

    ## join of vertexs2 and vertexso2

    vertexs2o2 = vertexs2.l_join(vertexso2)
    vertexs2o2.put_name("2 join other 2")

    print "Cells lattice with vertex pairs joined jrm:"
    cells.to_stream()

    ## jrm containing all vertices

    vertex_ids = intArray(3)
    vertex_ids[0] = v0.index()
    vertex_ids[1] = v1.index()
    vertex_ids[2] = v2.index()

    vertexs = total_poset_member(cells, vertex_ids, 3)
    vertexs.put_name("all vertices")

    print "Cells lattice with vertexs jrm:"
    cells.to_stream()

    ## Jrm containing all edges.
    ## Use the direct jrm constructor and direct linking.

    cells.begin_jim_edit_mode()

    ## Create the jrm

    edges = total_poset_member()
    edges.new_jrm_state(cells)
    edges.put_name("edges")

    ## Jrm goes between the triangle and its current lower cover.
    ## Unlink the triangle from its lower cover.

    t.delete_cover_link(vertexs)
    t.delete_cover_link(e0)
    t.delete_cover_link(e1)
    t.delete_cover_link(e2)

    ## Link the jrm.

    t.create_cover_link(edges)
    edges.create_cover_link(vertexs)
    edges.create_cover_link(e0)
    edges.create_cover_link(e1)
    edges.create_cover_link(e2)

    cells.end_jim_edit_mode()

    print "Cells lattice with edges jrm:"
    cells.to_stream()

    ## Release access to top level

    test_namespace.release_access()

    edges.detach_from_state()
    vertexs.detach_from_state()
    vertexso2.detach_from_state()
    vertexs2.detach_from_state()

    print "\n*** LEAVING NEW_JRM_TEST ***********************\n"


###############################################################################
# main():
###############################################################################

def main():

    ## Make the default namespace

    global test_namespace
    test_namespace = namespace_poset("test_namespace")

    empty_poset_test()

    new_top_level_test()

##    multiple_names_test()

    product_rep_test()

##    filtered_iterator_test()

##    subposet_iterator_test()

    ## Write it to a file;
    ## need read access in order to write it.

    test_namespace.get_read_write_access()
    sa = storage_agent("poset_t.hdf", sheaf_file.READ_WRITE, TRUE, FALSE)
    sa.put_member_record_buffer_ub(15)
    sa.put_dof_tuple_record_size(64)
    sa.put_dof_tuple_record_buffer_ub(15)
    sa.write_entire(test_namespace)
    
##    test_namespace.to_stream()
    
    del test_namespace


###############################################################################

if __name__ == '__main__':
    main()
