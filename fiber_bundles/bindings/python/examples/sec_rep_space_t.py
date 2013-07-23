#! /usr/bin/env python
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##

from sheaves_python_binding import *
from fiber_bundles_python_binding import *

from array import array

TRUE = 1
FALSE = 0

global cells

###############################################################################
# make_fiber_schema():
###############################################################################

def make_fiber_schema():

    global R2_schema, x_comp, y_comp, dim

    ## Get read-write access to the namespace.

    test_namespace.get_read_write_access()

    primitives = test_namespace.primitives();

    ## Make a new poset.

    R2_schema = poset(test_namespace, primitives.schema(), "R2_schema")

    ## Get read-write access to it.

    R2_schema.get_read_write_access()

    ## Enter edit mode.

    R2_schema.begin_jim_edit_mode()

    ltable_dofs = subposet(R2_schema)
    lrow_dofs = subposet(R2_schema)

    ##  Make the jims.

    dim = total_poset_member(R2_schema, primitives.int_type().dof_map(FALSE))
    dim.put_name("dim", TRUE, FALSE)
    ltable_dofs.insert_member(dim)

    x_comp = total_poset_member(R2_schema, primitives.double_type().dof_map(FALSE))
    x_comp.put_name("x_component", TRUE, FALSE)
    lrow_dofs.insert_member(x_comp)

    y_comp = total_poset_member(R2_schema, primitives.double_type().dof_map(FALSE))
    y_comp.put_name("y_component", TRUE, FALSE)
    lrow_dofs.insert_member(y_comp)

    ## Exit edit mode.

    R2_schema.end_jim_edit_mode()

    R2_schema.schematize(ltable_dofs, lrow_dofs, TRUE);
    
    ltable_dofs.detach_from_state()
    lrow_dofs.detach_from_state()    

    ## Release access to posets.
    
    R2_schema.release_access()
    test_namespace.release_access()
    
    print "\n############### A\n"

    return


###############################################################################
# make_base_space():
###############################################################################

def make_base_space():

##    global cells, t, e0, e1, e2, v0, v1, v2
    global t, e0, e1, e2, v0, v1, v2

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

    ## Primitives already schematized, can just use them as schema.

    ppath = poset_path("local_coordinates_schema/local_coordinates_schema")

    cells = poset(test_namespace, ppath, "cells")
    cells.get_read_write_access()
    cells.schema().get_read_access()
    cells.begin_jim_edit_mode()

    ##$$ISSUE: Must be a better way to do this in python!
    dof = intArray(2)
    dof_size = 2*8

    v = total_poset_member(cells)
    v.put_name("standard vertex", TRUE, FALSE)
    dof[0] = 0
    dof[1] = 1
    v.put_dof_tuple(dof, dof_size)

    e = total_poset_member(cells)
    e.put_name("standard edge", TRUE, FALSE)
    dof[0] = 1
    e.put_dof_tuple(dof, dof_size)

    t = total_poset_member(cells)
    t.put_name("standard triangle", TRUE, FALSE)
    dof[0] = 2
    t.put_dof_tuple(dof, dof_size)

    e0 = total_poset_member(cells)
    e0.put_name("e0", TRUE, FALSE)
    dof[0] = 1
    e0.put_dof_tuple(dof, dof_size)

    e1 = total_poset_member(cells)
    e1.put_name("e1", TRUE, FALSE)
    dof[0] = 1
    e1.put_dof_tuple(dof, dof_size)

    e2 = total_poset_member(cells)
    e2.put_name("e2", TRUE, FALSE)
    dof[0] = 1
    e2.put_dof_tuple(dof, dof_size)

    v0 = total_poset_member(cells)
    v0.put_name("v0", TRUE, FALSE)
    dof[0] = 0
    v0.put_dof_tuple(dof, dof_size)

    v1 = total_poset_member(cells)
    v1.put_name("v1", TRUE, FALSE)
    dof[0] = 0
    v1.put_dof_tuple(dof, dof_size)

    v2 = total_poset_member(cells)
    v2.put_name("v2", TRUE, FALSE)
    dof[0] = 0
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
    
    ## Release access.

    cells.schema().release_access()
    cells.release_access()
    test_namespace.release_access()

    v.detach_from_state()
    e.detach_from_state()

    return


###############################################################################
# make_section_space_definitions():
###############################################################################

def make_section_space_definitions():

    global sec_rep_desc
    
    ## Get read-write access to the namespace.

    test_namespace.get_read_write_access()

    primitives = test_namespace.primitives()

    ## Make some standard sec rep descriptors.

    ppath = poset_path("sec_rep_descriptor_schema/sec_rep_descriptor_schema")

    sec_rep_desc = poset(test_namespace, ppath, "sec_rep_descriptors")

    sec_rep_desc.get_read_write_access()
    sec_rep_desc.schema().get_read_access()

    sec_rep_desc.begin_jim_edit_mode()

    lsrd = sec_rep_descriptor()

    lsrd.new_jim_state(sec_rep_desc)
    lsrd.put_name("vertex_element_dlinear", TRUE, FALSE)
    lsrd.put_discretization_subposet_name("vertices")
    lsrd.put_evaluation_subposet_name("elements")
    lsrd.put_evaluator_family_name("dlinear")
    lsrd.put_url("www.lpsweb.com/libSheaf/std_namespace.html")
    lsrd.put_multiplicity(1)

    lsrd.new_jim_state(sec_rep_desc)
    lsrd.put_name("element_element_const", TRUE, FALSE)
    lsrd.put_discretization_subposet_name("elements")
    lsrd.put_evaluation_subposet_name("elements")
    lsrd.put_evaluator_family_name("const")
    lsrd.put_url("www.lpsweb.com/libSheaf/std_namespace.html")
    lsrd.put_multiplicity(1)

    sec_rep_desc.end_jim_edit_mode()

    ## Make sec rep space definitions group (jrm).

    lm1 = total_poset_member(test_namespace, "sec_rep_descriptor_schema")
    lm2 = total_poset_member(test_namespace, sec_rep_desc.index())

    sec_defns = lm1.l_join(lm2)
    sec_defns.put_name("section space definitions", TRUE, FALSE)
    sec_defns.detach_from_state()
    del sec_defns

    ## Detach all the handles allocated on the stack.

    lsrd.detach_from_state();
    lm1.detach_from_state();
    lm2.detach_from_state();

    ## Release access

    ## test_namespace.to_stream()

    sec_rep_desc.schema().release_access();
    sec_rep_desc.release_access();
    test_namespace.release_access();

    return


###############################################################################
# make_sec_rep_space():
###############################################################################

def make_sec_rep_space():

##    global cells, lsec_rep_space, R2, lmap
    global lsec_rep_space, R2, lmap
   
    test_namespace.get_read_write_access()

    ## Make the discretization subposet

    cells.get_read_write_access()
    ldisc =  subposet(cells, "__vertices");
    lmap = ldisc.client_id_map();

    ldisc.insert_member(relative_index(6));
    lmap.put_poset_id(relative_index(6));
    ldisc.insert_member(relative_index(7));
    lmap.put_poset_id(relative_index(7));
    ldisc.insert_member(relative_index(8));
    lmap.put_poset_id(relative_index(8));

##    ## Make the client id_map for the discretization

##    lmap = ldisc.new_client_id_map()
##    lct = 0
##    ##$$ISSUE: filtered_iterator is obsolete; should use postorder_iterator.
##    vitr = filtered_iterator(t, ldisc)
##    while not vitr.is_done():
##        print 'vitr.index(), lct ', vitr.index(), '  ', lct
##        lmap.put_ids(vitr.index(), lct)
##        lct+=1
##        vitr.next()

    ## Make the evaluation subposet

    leval = subposet(cells, "__elements");
    lmap = leval.client_id_map();
    t = base_space_member(cells, "standard_triangle");
    leval.insert_member(t);
    lmap.put_poset_id(t.index());

    ## Finished with the subposet handles

    ldisc.detach_from_state()
    leval.detach_from_state()

    ## Get a handle to the rep descriptor

    lpath = poset_path("sec_rep_descriptors", "vertex_element_dlinear")

    lrep_mbr = sec_rep_descriptor(test_namespace, lpath)
    lrep_mbr.get_read_access()

    ## Make the fiber space.
    
    ## Only one table dof, the dimension.

    ldim = intPtr()
    ldim.assign(2)
    sizeof_ldim = array('i').itemsize ##$$ISSUE: Need a sizeof() method
 
    R2_schema.get_read_access()
    R2 = poset(test_namespace, R2_schema.top(), "R2", ldim, sizeof_ldim)
    R2.get_read_access()

    ## Make the sec rep space

    lsec_rep_space = sec_rep_space(t, R2, lrep_mbr, "R2 on triangle")

    ## Get access

    lsec_rep_space.get_read_write_access()

    print "dimension = ", lsec_rep_space.df()

    ## Make a section
    
    lcoords = sec_rep_space_member(lsec_rep_space)
    lcoords.put_name("coordinates", TRUE, FALSE)

    lcoords_dofs = array('d', [0.0, 0.0, 2.0, 0.0, 0.0, 3.0])
    n = len(lcoords_dofs)
    dofs_ptr = doubleArray(n)
    sizeof_dofs = n*lcoords_dofs.itemsize
    for i in range(n): dofs_ptr[i] = lcoords_dofs[i]
    
    lcoords.put_dof_tuple(dofs_ptr, sizeof_dofs)

    ldisps = sec_rep_space_member(lsec_rep_space)
    ldisps.put_name("displacements", TRUE, FALSE)

    ldisps_dofs = array('d', [0.01, 0.02, 0.03, 0.04, 0.05, 0.06])

    do_one_at_a_time = TRUE  ## Change to try other method.
    if not do_one_at_a_time:
        n = len(ldisps_dofs)
        dofs_ptr = doubleArray(n)
        sizeof_dofs = n*ldisps_dofs.itemsize
        for i in range(n): dofs_ptr[i] = ldisps_dofs[i]

        ldisps.put_dof_tuple(dofs_ptr, sizeof_dofs)
        
    else:
        dof_ptr = doublePtr(); 
        sizeof_dof = ldisps_dofs.itemsize
        ldof_itr = lsec_rep_space.schema().row_dof_iterator()
        i = 0   
        while not ldof_itr.is_done():
            dof_ptr.assign(ldisps_dofs[i])
            ldisps.dof_map().put_dof(ldof_itr.item(), dof_ptr, sizeof_dof)
            ldof_itr.next()
            i += 1

        del ldof_itr

    print "restriction test:"

    e1 = total_poset_member (cells, "e1");
    ldisps.restrict_to(e1, x_comp)

    ldisps_schema = ldisps.schema()
    ldof_itr = ldisps_schema.row_dof_iterator()
    dof_ptr = doublePtr()
    while not ldof_itr.is_done():
        ldisps.dof_map().get_dof(ldof_itr.item(), dof_ptr, 8) ##$$ISSUE: Need a sizeof() method
        print "  ", dof_ptr.value(),
        ldof_itr.next()
    print

    del ldof_itr

    t.detach_from_state()
    e1.detach_from_state()
    lcoords.detach_from_state()
    ldisps.detach_from_state()

    ## Release access to all posets.

    lsec_rep_space.release_access()  
    R2.release_access()
    R2_schema.release_access()
    lrep_mbr.release_access()
    lrep_mbr.detach_from_state()
    cells.release_access()
    test_namespace.release_access()

    return


###############################################################################
# make_member_poset_test():
###############################################################################

def make_member_poset_test():

    ##$$ISSUE: Python has no equivalent to "dynamic_cast", so here we
    ##         just print out the member names.

    print "\n####### begin member poset test ####################\n"

    test_namespace.get_read_access()

    itr = postorder_member_iterator(test_namespace.top(), "jims")

    while not itr.is_done():          
        print itr.item().name()
        itr.next()

    test_namespace.release_access()

    print "\n####### end member poset test ######################\n"



###############################################################################
# main():
###############################################################################

def main():

    ## Make the default namespace

    global test_namespace
    test_namespace = sheaves_namespace("sec_rep_space_t")
    
    make_fiber_schema()

    print "\n############### B\n"

    ##$$ISSUE: Why does this core dump following the next call?
##    make_base_space()

##    make_section_space_definitions()
    
    make_sec_rep_space()

##    make_member_poset_test()

####    test_namespace.to_stream()

    ## Write it to a file; requires read/write access.

    test_namespace.get_read_write_access()

    print "\n############### C\n"

    sa = storage_agent("sec_rep_space_t.hdf", sheaf_file.READ_WRITE)

    print "\n############### D\n"

    sa.write_entire(test_namespace)

    print "\n############### E\n"


    print "############### 1"

    ## Cleanup

    dim.detach_from_state()
    x_comp.detach_from_state()
    y_comp.detach_from_state()
    R2_schema.detach_from_state()
    test_namespace.detach_from_state()

    ## Delete the namespace.


    del test_namespace

    print "############### 2"


###############################################################################

if __name__ == '__main__':
    main()

    ##$$ISSUE: The follow is used to simulate a return from main in a typical
    ##         application. We need to delete the "global" objects properly
    ##         in order to be able to remove it.
    ##$$TODO:  Resolve the above issue.
##    import os
##    os._exit(0)
    
