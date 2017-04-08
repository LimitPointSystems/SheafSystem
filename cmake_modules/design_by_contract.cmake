#
# Copyright (c) 2016 Limit Point Systems, Inc. 
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


#
# Simple implementation of essential support for design by contract.
#
# Usage note: As a convenience to the caller, all these functions are 
# setup for "pass by reference" as opposed to "pass by value". 
# For example, it the condition you want to test is in the variable
# named "xcondition", invoke dbc_requires(xcondition) not dbc_requires(${xcondition}).
#

#
# Print message and throw a fatal error if the variable with name xvar_name is not defined.
#
function(dbc_require_defined xvar_name)

   if(NOT(DEFINED "${xvar_name}"))
      message(FATAL_ERROR "Variable ${xvar_name} is not defined.")
   endif()

endfunction(dbc_require_defined xvar_name)
 
#
# Precondition: display message and throw fatal error if 
# the value of the variable with name xcondition_name is not true.
#
function(dbc_require xcondition_name)

   dbc_require_defined(${xcondition_name})

   if(NOT "${${xcondition_name}}")
      message(FATAL_ERROR "Precondition violated.")
   endif()

endfunction(dbc_require)

#
# Precondition: display message and throw fatal error if 
# it is not true the first condition implies the second condition.
# (More precisely if it is not true that the value of the variable 
# with name xcondition_name1 equals true implies the value of the 
# variable with name xcondition_name2 is also true.)
#
function(dbc_require_implies xcondition_name1 xcondition_name2)

   dbc_require_defined(${xcondition_name1})
   dbc_require_defined(${xcondition_name2})

   if("${${xcondition_name1}}" AND (NOT "${${xcondition_name2}}"))
      message(FATAL_ERROR "Precondition violated.")
   endif()

endfunction(dbc_require_implies)

#
# Precondition: display message and throw fatal error if 
# neither the first condition nor the second condition is true.
# (More precisely if neither the value of the variable 
# with name xcondition_name1 nor the value of the 
# variable with name xcondition_name2 is true.)
#
function(dbc_require_or xcondition_name1 xcondition_name2)

   dbc_require_defined(${xcondition_name1})
   dbc_require_defined(${xcondition_name2})

   if(NOT("${${xcondition_name1}}" OR "${${xcondition_name2}}"))
      message(FATAL_ERROR "Precondition violated.")
   endif()

endfunction(dbc_require_or)

#
# Place holder for unexecutable precondition.
# Essentially a comment; does nothing.
#
function(dbc_unexecutable_require xcondition)

   if(FALSE)
      message(FATAL_ERROR "Precondition violated.")
   endif()

endfunction(dbc_unexecutable_require)
 
#
# Precondition: display message and throw fatal error if 
# the target with name xtarget_name does not exist.
#
function(dbc_require_target xtarget_name)

   if(DEFINED "${xtarget_name}")
      if(NOT (TARGET "${${xtarget_name}}"))
         message(FATAL_ERROR "Target precondition violated: target ${${xtarget_name}} not defined.")
      endif()
   else()
      if(NOT (TARGET "${xtarget_name}"))
         message(FATAL_ERROR "Target precondition violated: target ${xtarget_name} not defined.")
      endif()
   endif()

endfunction(dbc_require_target)


#
# Assertion: display message and throw fatal error if 
# the value of the variable with name xcondition_name is not true.
#
function(dbc_assert xcondition_name)

   dbc_require_defined(${xcondition_name})

   if(NOT "${${xcondition_name}}")
      message(FATAL_ERROR "Assertion violated.")
   endif()

endfunction(dbc_assert)

#
# Assertion: display message and throw fatal error if 
# it is not true the first condition implies the second condition.
# (More precisely if it is not true that the value of the variable 
# with name xcondition_name1 equals true implies the value of the 
# variable with name xcondition_name2 is also true.)
#
function(dbc_assert_implies xcondition_name1 xcondition_name2)

   dbc_require_defined(${xcondition_name1})
   dbc_require_defined(${xcondition_name2})

   if("${${xcondition_name1}}" AND (NOT "${${xcondition_name2}}"))
      message(FATAL_ERROR "Assertion violated.")
   endif()

endfunction(dbc_assert_implies)

#
# Assertion: display message and throw fatal error if 
# neither the first condition nor the second condition is true.
# (More precisely if neither the value of the variable 
# with name xcondition_name1 nor the value of the 
# variable with name xcondition_name2 is true.)
#
function(dbc_assert_or xcondition_name1 xcondition_name2)

   dbc_require_defined(${xcondition_name1})
   dbc_require_defined(${xcondition_name2})

   if(NOT("${${xcondition_name1}}" OR "${${xcondition_name2}}"))
      message(FATAL_ERROR "Assertion violated.")
   endif()

endfunction(dbc_assert_or)

#
# Place holder for unexecutable assertion.
# Essentially a comment; does nothing.
#
function(dbc_unexecutable_assert xcondition)

   if(FALSE)
      message(FATAL_ERROR "Assertion violated.")
   endif()

endfunction(dbc_unexecutable_assert)
 
#
# Assertion: display message and throw fatal error if 
# the target with name xtarget_name does not exist.
#
function(dbc_assert_target xtarget_name)

   if(DEFINED "${xtarget_name}")
      if(NOT (TARGET "${${xtarget_name}}"))
         message(FATAL_ERROR "Target assertion violated: target ${${xtarget_name}} not defined.")
      endif()
   else()
      if(NOT (TARGET "${xtarget_name}"))
         message(FATAL_ERROR "Target assertion violated: target ${xtarget_name} not defined.")
      endif()
   endif()

endfunction(dbc_assert_target)

#
# Print message and throw a fatal error if the variable with name xvar_name is not defined.
#
function(dbc_ensure_defined xvar_name)

   if(NOT(DEFINED "${xvar_name}"))
      message(FATAL_ERROR "Postcondition violation: variable ${xvar_name} is not defined.")
   endif()

endfunction(dbc_ensure_defined xvar_name)

#
# Postcondition: display message and throw fatal error if 
# the value of the variable with name xcondition_name is not true.
#
function(dbc_ensure xcondition_name)

   dbc_require_defined(${xcondition_name})

   if(NOT "${${xcondition_name}}")
      message(FATAL_ERROR "Postcondition violated.")
   endif()

endfunction(dbc_ensure)

#
# Postcondition: display message and throw fatal error if 
# it is not true the first condition implies the second condition.
# (More precisely if it is not true that the value of the variable 
# with name xcondition_name1 equals true implies the value of the 
# variable with name xcondition_name2 is also true.)
#
function(dbc_ensure_implies xcondition_name1 xcondition_name2)

   dbc_require_defined(${xcondition_name1})
   dbc_require_defined(${xcondition_name2})

   if("${${xcondition_name1}}" AND (NOT "${${xcondition_name2}}"))
      message(FATAL_ERROR "Postcondition violated.")
   endif()

endfunction(dbc_ensure_implies)

#
# Postcondition: display message and throw fatal error if 
# neither the first condition nor the second condition is true.
# (More precisely if neither the value of the variable 
# with name xcondition_name1 nor the value of the 
# variable with name xcondition_name2 is true.)
#
function(dbc_ensure_or xcondition_name1 xcondition_name2)

   dbc_require_defined(${xcondition_name1})
   dbc_require_defined(${xcondition_name2})

   if(NOT("${${xcondition_name1}}" OR "${${xcondition_name2}}"))
      message(FATAL_ERROR "Postcondition violated.")
   endif()

endfunction(dbc_ensure_or)

#
# Place holder for unexecutable postcondition.
# Essentially a comment; does nothing.
#
function(dbc_unexecutable_ensure xcondition)

   if(FALSE)
      message(FATAL_ERROR "Postcondition violated.")
   endif()

endfunction(dbc_unexecutable_ensure)

 
#
# Postcondition: display message and throw fatal error if 
# the target with name xtarget_name does not exist.
#
function(dbc_ensure_target xtarget_name)

   if(DEFINED "${xtarget_name}")
      if(NOT (TARGET "${${xtarget_name}}"))
         message(FATAL_ERROR "Target postcondition violated: target ${${xtarget_name}} not defined.")
      endif()
   else()
      if(NOT (TARGET "${xtarget_name}"))
         message(FATAL_ERROR "Target postcondition violated: target ${xtarget_name} not defined.")
      endif()
   endif()

endfunction(dbc_ensure_target)
