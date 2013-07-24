#! /usr/bin/env python
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##


from sheaves_python_binding import *

## Make the default namespace.

test_namespace = sheaves_namespace("test_namespace")

test_namespace.make_triangle(test_namespace);

test_namespace.get_read_access()

## Use standard triangle in sheaves_namespace as the test case.
## Member indexing and Correct order of iterations can be 
## deduced by inspection of output from sheaves_namespace_t.py

print "\n##### 1\n"

##path = poset_path("cell definitions", "triangle")

print "\n##### 1a\n"

triangle = poset_member(test_namespace, "cells/standard triangle")

print "\n##### 2\n"

## Create some subposets to use as tests.

triangle.get_read_write_access()

## Just the 0-cells

print "\n##### 3\n"
lsp0 = subposet(triangle.host())
lsp0.put_name("0-cells", TRUE, FALSE)

lsp0.insert_member(relative_index(6))
lsp0.insert_member(relative_index(7))
lsp0.insert_member(relative_index(8))

## Just the 1-cells

print "\n##### 4\n"
lsp1 = subposet(triangle.host())
lsp1.put_name("1-cells", TRUE, FALSE)
lsp1.insert_member(relative_index(9))
lsp1.insert_member(relative_index(10))
lsp1.insert_member(relative_index(11))

## Both the 0-cells and 1-cells

print "\n##### 5\n"
lsp01 = subposet(triangle.host())
lsp01.put_name("0- and 1-cells", TRUE, FALSE)
lsp0.p_union_pa(lsp1, lsp01)
  
lsp0.detach_from_state();
lsp1.detach_from_state();

print "\n##### begin SUBPOSET::minimals test #####"

lmins = lsp01.minimals()
  
##lmins_itr = lmins.member_iterator()  ## Not working in python module yet.
lmins_itr = subposet_member_iterator(lmins)

print "",
while not lmins_itr.is_done():
    print lmins_itr.index(),
    lmins_itr.next() 
print
  
print "should be:"
print " 6 7 8"

print "##### end   SUBPOSET::minimals test #####\n"

print "\n##### begin SUBPOSET::maximals test #####"

lmaxs = lsp01.maximals()
  
##lmins_itr = lmaxs.member_iterator()  ## Not working in python module yet.
lmaxs_itr = subposet_member_iterator(lmaxs)

print "",
while not lmaxs_itr.is_done():
    print lmaxs_itr.index(),
    lmaxs_itr.next() 
print
  
print "should be:"
print " 9 10 11"

print "##### end   SUBPOSET::maximals test #####\n"


## Detach so destructor won't complain about needing write access.

lsp01.detach_from_state();
triangle.detach_from_state();
test_namespace.detach_from_state()
