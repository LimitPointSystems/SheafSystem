#! /usr/bin/env python
#
# Copyright (c) 2014 Limit Point Systems, Inc. 
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

## Test driver for class section_pusher (1d version).


import os, sys
from fields_python_binding import *
from fiber_bundles_python_binding import *
from sheaves_python_binding import *

TRUE  = 1
FALSE = 0

###############################################################################
# post_information_message(xmsg):
###############################################################################

def post_information_message(xmsg):
    
    print xmsg

    
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

#################################################################################
### push:
#################################################################################

##def push(source, destination):

##    ## Create a section pusher from the source to destination section spaces.

##    sp = section_pusher(source.test_space(),
##                        destination.test_space(),
##                        source.coords(),
##                        destination.coords())

##    ## Push the source field to the destination.

##    result = destination.test_scalar().clone()
##    result.put_name("push_of_"+source.test_scalar().name())

##    sp.push_pa(source.test_scalar(), result)

##    ## Print the results of the push.

##    print_push(source, destination, result)

##    return result


###############################################################################
# test_auto_allocated_push():
###############################################################################

def test_auto_allocated_push():

  post_information_message("Entering test_auto_allocated_push")

  lns = fiber_bundles_namespace("section_pusher_1d_t")
  lns.get_read_write_access()

  ## An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  xlower = wsv_block_double("-2.0")
  xupper = wsv_block_double("2.0")

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  fine = field_factory.new_scalar_field_1d_uniform(lns,
            "fine", 8, xlower, xupper, fpl)

  ## A 3 element coarse mesh with the same coord bounds.

  lhost = sec_e1_uniform.new_host(lns, "coarse_mesh", 3, TRUE)
    
  coarse_coords = sec_e1_uniform(lhost, -2.0, 2.0, TRUE)
  coarse_coords.put_name("coarse_coords", TRUE, TRUE)

  ## Push the "fine" field to the "coarse" mesh and
  ## print the result compared to the exact value.

  lpusher = section_pusher(fine, coarse_coords, TRUE)
  coarse_prop = lpusher.push(fine.property(), TRUE)
  coarse_prop.put_name("coarse_prop", TRUE, TRUE)

  coarse = field_vd(coarse_coords, coarse_prop, TRUE)

  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing uniform fine >> uniform coarse:",
      TRUE,
      TRUE)

##  print lns.to_string()

  sa = storage_agent("section_pusher_1d_t.hdf",
                     sheaf_file.READ_WRITE, TRUE, FALSE);
  sa.write_entire(lns);

  coarse_prop.detach_from_state()
  coarse_coords.detach_from_state()

  post_information_message("Leaving test_auto_allocated_push");
  

#################################################################################
### test_fine_to_coarse_to_fine:
#################################################################################

def test_fine_to_coarse_to_fine():

  post_information_message("Entering test_fine_to_coarse_to_fine")

  lns = fiber_bundles_namespace("section_pusher_1d_t")
  lns.get_read_write_access()

  ## An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  xlower = wsv_block_double("-2.0")
  xupper = wsv_block_double("2.0")

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  fine = field_factory.new_scalar_field_1d_unstructured(lns,
            "fine", 8, xlower, xupper, fpl)


  ## A 3 element coarse mesh with the same bounds and property == 0.

  fpz = field_factory.property_dof_function("zero")
 
  coarse = field_factory.new_scalar_field_1d_unstructured(lns,
              "coarse", 3, xlower, xupper, fpz)

  ## Push the "fine" field to the "coarse" field and
  ## print the result compared to the exact value.

  push(fine, coarse, TRUE)
  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing unstructured fine >> unstructured coarse:",
      TRUE,
      TRUE)

  ## Set the coarse field to the exact value and zero out the fine field.

  ##$$ISSUE: Don't know why the preferred function calls fail below.
  ##         Temporarily we'll use the static function calls.
  ##$$TODO:  Fix the problem.
  ##  coarse.put_property_dofs(fpl, TRUE)
  field_vd.put_property_dofs(coarse.coordinates(), coarse.property(), fpl, TRUE)
  
  ##  fine.put_property_dofs(fpz, TRUE)
  field_vd.put_property_dofs(fine.coordinates(), fine.property(), fpz, TRUE)

  ## Push the "coarse" field to the "fine" field and
  ## print the result compared to the exact value.

  push(coarse, fine, TRUE)
  fine.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing unstructured coarse >> unstructured  fine:",
      TRUE,
      TRUE)

  post_information_message("Leaving test_fine_to_coarse_to_fine")

#################################################################################
### test_fine_to_coarse_to_fine_2:
#################################################################################

def test_fine_to_coarse_to_fine_2():

  post_information_message("Entering test_fine_to_coarse_to_fine_2")

  lns = fiber_bundles_namespace("section_pusher_1d_t")
  lns.get_read_write_access()

  ## An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  xlower = wsv_block_double("-2.0")
  xupper = wsv_block_double("2.0")

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  fine = field_factory.new_scalar_field_1d_uniform(lns,
            "fine", 8, xlower, xupper, fpl)

  ## A 3 element coarse mesh with the same bounds and property == 0.

  fpz = field_factory.property_dof_function("zero")
 
  coarse = field_factory.new_scalar_field_1d_unstructured(lns,
              "coarse", 3, xlower, xupper, fpz)

  ## Push the "fine" field to the "coarse" field and
  ## print the result compared to the exact value.

  push(fine, coarse, TRUE)
  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing uniform fine >> unstructured coarse:",
      TRUE,
      TRUE)

  ## Set the coarse field to the exact value and zero out the fine field.

  ##$$ISSUE: Don't know why the preferred function calls fail below.
  ##         Temporarily we'll use the static function calls.
  ##$$TODO:  Fix the problem.
  ##  coarse.put_property_dofs(fpl, TRUE)
  field_vd.put_property_dofs(coarse.coordinates(), coarse.property(), fpl, TRUE)
  
  ##  fine.put_property_dofs(fpz, TRUE)
  field_vd.put_property_dofs(fine.coordinates(), fine.property(), fpz, TRUE)

  ## Push the "coarse" field to the "fine" field and
  ## print the result compared to the exact value.

  push(coarse, fine, TRUE)
  fine.print_property_dofs(get_cout(),
                           fpl,
                           "After pushing unstructured coarse >> uniform fine:",
                           TRUE,
                           TRUE)

  post_information_message("Leaving test_fine_to_coarse_to_fine_2")

#################################################################################
### test_fine_to_coarse_to_fine_3:
#################################################################################

def test_fine_to_coarse_to_fine_3():

  post_information_message("Entering test_fine_to_coarse_to_fine_3")

  lns = fiber_bundles_namespace("section_pusher_1d_t")
  lns.get_read_write_access()

  ## An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  xlower = wsv_block_double("-2.0")
  xupper = wsv_block_double("2.0")

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  ppath = poset_path("sec_rep_descriptors/element_element_constant")

  fine = field_factory.new_scalar_field_1d_unstructured(lns,
            "fine", 8, xlower, xupper, fpl, ppath)

  ## A 3 element coarse mesh with the same bounds and property == 0.

  fpz = field_factory.property_dof_function("zero")
 
  coarse = field_factory.new_scalar_field_1d_unstructured(lns,
              "coarse", 3, xlower, xupper, fpz, ppath)

  ## Push the "fine" field to the "coarse" field and
  ## print the result compared to the exact value.

  push(fine, coarse, TRUE)
  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing constant unstructured fine >>  constant unstructured coarse:",
      TRUE,
      TRUE)

  ## Set the coarse field to the exact value and zero out the fine field.

  ##$$ISSUE: Don't know why the preferred function calls fail below.
  ##         Temporarily we'll use the static function calls.
  ##$$TODO:  Fix the problem.
  ##  coarse.put_property_dofs(fpl, TRUE)
  field_vd.put_property_dofs(coarse.coordinates(), coarse.property(), fpl, TRUE)
  
  ##  fine.put_property_dofs(fpz, TRUE)
  field_vd.put_property_dofs(fine.coordinates(), fine.property(), fpz, TRUE)

  ## Push the "coarse" field to the "fine" field and
  ## print the result compared to the exact value.

  push(coarse, fine, TRUE)
  fine.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing constant unstructured coarse >>  constant unstructured fine:",
      TRUE,
      TRUE)

  post_information_message("Leaving test_fine_to_coarse_to_fine_3")

#################################################################################
### test_coarse_to_fine_to_coarse:
#################################################################################
    
def test_coarse_to_fine_to_coarse():

  post_information_message("Entering test_coarse_to_fine_to_coarse")

  lns = fiber_bundles_namespace("section_pusher_1d_t")
  lns.get_read_write_access()

  ## An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  xlower = wsv_block_double("-2.0")
  xupper = wsv_block_double("2.0")

  fpz = field_factory.property_dof_function("zero")
  
  fine = field_factory.new_scalar_field_1d_unstructured(lns,
            "fine", 8, xlower, xupper, fpz)

  ## A 3 element coarse mesh with the same bounds and property == 0.

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  coarse = field_factory.new_scalar_field_1d_unstructured(lns,
              "coarse", 3, xlower, xupper, fpl)

  ## Push the "coarse" field to the "fine" field and
  ## print the result compared to the exact value.

  push(coars, fine, TRUE)
  fine.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing unstructured coarse >> unstructured fine:",
      TRUE,
      TRUE)

  ## Set the fine field to the exact value and zero out the coarse field.

  ##$$ISSUE: Don't know why the preferred function calls fail below.
  ##         Temporarily we'll use the static function calls.
  ##$$TODO:  Fix the problem.
  ##  coarse.put_property_dofs(fpl, TRUE)
  field_vd.put_property_dofs(coarse.coordinates(), coarse.property(), fpz, TRUE)
  
  ##  fine.put_property_dofs(fpz, TRUE)
  field_vd.put_property_dofs(fine.coordinates(), fine.property(), fpl, TRUE)

  ## Push the "fine" field to the "coarse" field and
  ## print the result compared to the exact value.

  push(fine, coarse, TRUE)
  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing unstructured fine >> unstructured coarse:",
      TRUE,
      TRUE)

  post_information_message("Leaving test_coarse_to_fine_to_coarse")


#################################################################################
### test_small_to_large_to_small:
#################################################################################

def test_small_to_large_to_small():

  post_information_message("Entering test_small_to_large_to_small")
  
  lns = fiber_bundles_namespace("section_pusher_1d_t")
  lns.get_read_write_access()

  ## An 2 element small mesh on with xmin = -2.0 and xmax = 2.0.

  xsmall_lower = wsv_block_double("-2.0")
  xsmall_upper = wsv_block_double("2.0")

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  small = field_factory.new_scalar_field_1d_unstructured(lns,
            "small", 2, xsmall_lower, xsmall_upper, fpl)

  ## A 4 element large mesh with xmin = -3.0 and xmax = 3.0.

  xlarge_lower = wsv_block_double("-3.0")
  xlarge_upper = wsv_block_double("3.0")

  fpz = field_factory.property_dof_function("zero")
 
  large = field_factory.new_scalar_field_1d_unstructured(lns,
              "large", 4, xlarge_lower, xlarge_upper, fpz)


  ## Push the "small" field to the "large" field and
  ## print the result compared to the exact value.

  push(small, large, TRUE)
  large.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing constant unstructured small >>  constant unstructured large:",
      TRUE,
      TRUE)

  ## Set the large field to the exact value and zero out the small field.

  ##$$ISSUE: Don't know why the preferred function calls fail below.
  ##         Temporarily we'll use the static function calls.
  ##$$TODO:  Fix the problem.
  ##  large.put_property_dofs(fpl, TRUE)
  field_vd.put_property_dofs(large.coordinates(), large.property(), fpl, TRUE)
  
  ##  small.put_property_dofs(fpz, TRUE)
  field_vd.put_property_dofs(small.coordinates(), small.property(), fpz, TRUE)

  ## Push the "large" field to the "small" field and
  ## print the result compared to the exact value.

  push(large, small, TRUE)
  small.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing unstructured large >> unstructured small:",
      TRUE,
      TRUE)

  post_information_message("Leaving test_small_to_large_to_small")


#################################################################################
### test_combination:
#################################################################################

def test_combination():

  post_information_message("Entering test_combination")

  ## Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
  ## that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
  ## fine->fine.  Also tests cases:
  ##
  ## (1)  the destination coordinate is not within any source edge
  ## (2)  the destination coordinate is identical to some source coordinate
  ## (3)  the destination coordinate is within some source edge but not
  ## identical to any source coordinate
  ##
  ## All meshes start with coordinate 0 (exactly).  This tests (2).
  ##
  ## To test (1), every push should be from a "short" mesh to a "long"
  ## mesh.  If we arrange the maximum coordinate of each mesh thusly:
  ##      fine2 < coarse < fine1
  ## then we guarantee that we test condition (1).
  ##
  ## To test (3), the destination mesh must have an edge length < total length
  ## of the source mesh but not an integer multiple of the source mesh edge
  ## length.
  ##
  ## The following conditions are desirable.  They ensure that the test
  ## exercises extension.
  ##
  ##     coarse_mesh_max_coord < fine_mesh_1_max_coord
  ##     fine_mesh_2_max_coord < coarse_mesh_max_coord

  lns = fiber_bundles_namespace("section_pusher_1d.t")
  lns.get_read_write_access()

  ## Make the "fine_1" test case.
  
  xfine_1_lower = wsv_block_double("0.0")
  xfine_1_upper = wsv_block_double("10.0")

  fpl = field_factory.property_dof_function("linear_scalar_fcn")

  fine_1 = field_factory.new_scalar_field_1d_unstructured(lns,
            "fine_1", 5, xfine_1_lower, xfine_1_upper, fpl)


  ## Make the "fine_2" test case.

  xfine_2_lower = wsv_block_double("0.0")
  xfine_2_upper = wsv_block_double("6.0")

  fpz = field_factory.property_dof_function("zero")

  fine_2 = field_factory.new_scalar_field_1d_unstructured(lns,
            "fine_2", 4, xfine_2_lower, xfine_2_upper, fpz)


  ## Make the "coarse" test case.

  xcoarse_lower = wsv_block_double("0.0")
  xcoarse_upper = wsv_block_double("8.0")

  coarse = field_factory.new_scalar_field_1d_unstructured(lns,
            "coarse", 2, xcoarse_lower, xcoarse_upper, fpz)


  ## Case 1: fine mesh 1 -> fine mesh 2 using section_pusher syntax.
  ## Section pusher syntax is more efficient if pushing more than one field
  ## between given section spaces because the inverter is only initialized once,
  ## instead on once for each field.

  sp = section_pusher(fine_1, fine_2, TRUE)
  sp.push_pa(fine_1.property(), fine_2.property(), TRUE)

  ## Print the results.

  fine_2.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing fine_1 >> fine_2:",
      TRUE,
      TRUE)

  ## Case 2: fine mesh 2 -> coarse mesh using member function syntax.
  ## Member function syntax is more convenient and just as efficient
  ## if pushing only a single field.

  push(fine_2, coarse, TRUE)

  ## Print the results.

  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing fine_2 >> coarse:",
      TRUE,
      TRUE)

  ## Case 3: coarse mesh -> fine mesh 1 using operator >> syntax.
  ## Operator syntax is most convenient of all, but you have to
  ## remember what it means.

  ## Zero out destination first so we'll know if we got the right answer.

  ##$$ISSUE: Don't know why the preferred function calls fail below.
  ##         Temporarily we'll use the static function calls.
  ##$$TODO:  Fix the problem.
  ##  fine_1.put_property_dofs(fpz, TRUE)
  field_vd.put_property_dofs(fine_1.coordinates(), fine_1.property(), fpz, TRUE)

  push(coarse, fine_1, TRUE)

  ## Print the results.

  fine_1.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing coarse >> fine_1:",
      TRUE,
      TRUE)

  ## Of course we could have just used operator syntax for the
  ## entire sequence. Reset everything and try it.

##  fine_1.put_property_dofs(fpl, TRUE)
##  fine_2.put_property_dofs(fpz, TRUE)
##  coarse.put_property_dofs(fpz, TRUE)

  field_vd.put_property_dofs(fine_1.coordinates(), fine_1.property(), fpl, TRUE)
  field_vd.put_property_dofs(fine_2.coordinates(), fine_2.property(), fpz, TRUE)
  field_vd.put_property_dofs(coarse.coordinates(), coarse.property(), fpz, TRUE)

  push(fine_1, fine_2, TRUE)
  push(fine_2, coarse, TRUE)
  push(coarse, fine_1, TRUE)

  fine_2.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing fine_1 >> fine_2 >> course >> fine_1:",
      TRUE,
      TRUE)

  coarse.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing fine_1 >> fine_2 >> course >> fine_1:",
      TRUE,
      TRUE)

  fine_1.print_property_dofs(
      get_cout(),
      fpl,
      "After pushing fine_1 >> fine_2 >> course >> fine_1:",
      TRUE,
      TRUE)

  post_information_message("Leaving test_combination")


###############################################################################
# main():
###############################################################################

def main():

    ## Test auto-allocated push.

    test_auto_allocated_push()

    ## Test fine uniform to coarse general to fine uniform.

    test_fine_to_coarse_to_fine_2()

    ## Test fine general to coarse general to fine general.

    test_fine_to_coarse_to_fine()

    ## Test fine general to coarse general to fine general with
    ## element_element_constant property representation..

    test_fine_to_coarse_to_fine_3()

    ## Test coarse general to fine general to coarse general.

    test_coarse_to_fine_to_coarse()

    ## Test small domain to large domain to small domain (all quads).
    ## Small domain only partially covers large domain.

    test_small_to_large_to_small()

    ## Test a combination of meshes.
    ## Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
    ## that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
    ## fine->fine.  Also tests cases:
    ##
    ## (1)  the destination coordinate is not within any source edge
    ## (2)  the destination coordinate is identical to some source coordinate
    ## (3)  the destination coordinate is within some source edge but not
    ##      identical to any source coordinate

    test_combination()


###############################################################################

if __name__ == '__main__':
    main()

###############################################################################

