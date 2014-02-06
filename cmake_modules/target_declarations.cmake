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


#
# Library targets
#

if(LINUX64GNU OR LINUX64INTEL)

    include(${CMAKE_MODULE_PATH}/help_targets.cmake)

     # "shared-libs" builds solely shared libs
    add_custom_target(shared-libs)

    # "static-libs" builds solely static libs
    add_custom_target(static-libs)
    
    if(BUILD_TOOLS)
        # Because the library dependencies are correct, we only
        # need to list the leaf nodes in the dependency list for shared libs.
        add_dependencies(shared-libs tools-shared-lib)
    
        # Because the library dependencies are correct, we only
        # need to list the leaf nodes in the dependency list for static libs.
        add_dependencies(static-libs tools-static-lib)
    else()
        # Because the library dependencies are correct, we only
        # need to list the leaf nodes in the dependency list for shared libs.
        add_dependencies(shared-libs fields-shared-lib)
    
        # Because the library dependencies are correct, we only
        # need to list the leaf nodes in the dependency list for static libs.
        add_dependencies(static-libs fields-static-lib)
    endif()   
 
    # Alias for shared lib; backward naming compatability with gnu system
    add_custom_target(lib)
    add_dependencies(lib shared-libs)
    
    # Add a shared and static library target for each component
    foreach(comp ${COMPONENTS})
        add_custom_target(${comp}-shared-lib)
        add_custom_target(${comp}-static-lib)   
    endforeach()  
    
    #
    # clean targets
    #
    add_custom_target(realclean 
            COMMAND ${CMAKE_COMMAND} --build  ${CMAKE_BINARY_DIR} --target clean
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/documentation) 
endif()

#
# Bindings Documentation targets
#
if(DOC_TARGETS)
    if(BUILD_BINDINGS)
        add_custom_target(java-docs)
        # $$TODO: this list, and the one for bindings above, should be populated programmatically,
        # NOT by hand. Fix it.
        add_dependencies(java-docs sheaves-java-docs fiber_bundles-java-docs geometry-java-docs
                         fields-java-docs solvers-java-docs tools-java-docs)
        set_target_properties(java-docs PROPERTIES FOLDER "Documentation Targets")
                             
        add_custom_target(alldocs DEPENDS doc java-docs)
        set_target_properties(alldocs PROPERTIES FOLDER "Documentation Targets")
    endif()
endif()  
  
#
# Bindings targets
#

# "make bindings" builds libs and bindings for all components.
# <component>-bindings builds all prerequisite libs and bindings for <component>
if(BUILD_BINDINGS)
    add_custom_target(bindings)
    set_target_properties(bindings PROPERTIES FOLDER "Binding Targets - Component")
     
    foreach(comp ${COMPONENTS})
        add_custom_target(${comp}-bindings)
        if(LINUX64GNU OR LINUX64INTEL)
            add_custom_target(${comp}-java-binding)
            add_custom_target(${comp}-python-binding)
            add_custom_target(${comp}-csharp-binding)
        endif()    
        set_target_properties(${comp}-bindings PROPERTIES FOLDER "Binding Targets - Component") 
    endforeach()

    # Because the library dependencies are correct, we only
    # need to list the leaf nodes in the dependency list for bindings.
    # Tools is the leaf, but doesnt have python binding. Need to build it's java,
    # and python from fields
    add_dependencies(bindings tools-bindings fields-bindings SheafScope)
    #Review this. These convenience targets clutter the Solution Explorer.
    # Turning them off in windows for now.
   if(LINUX64GNU OR LINUX64INTEL)        

        # Aggregate java bindings target
        add_custom_target(java-bindings)
        foreach(comp ${COMPONENTS})
            list(APPEND JAVA_BINDING_TARGETS ${comp}-java-binding)
        endforeach()
        add_dependencies(java-bindings ${JAVA_BINDING_TARGETS})

        # Aggregate python bindings target
        add_custom_target(python-bindings)
        foreach(comp ${COMPONENTS})
            list(APPEND PYTHON_BINDING_TARGETS ${comp}-python-binding)
        endforeach()
        add_dependencies(python-bindings ${PYTHON_BINDING_TARGETS})

        # Aggregate csharp bindings target
        add_custom_target(csharp-bindings)
        foreach(comp ${COMPONENTS})
            list(APPEND CSHARP_BINDING_TARGETS ${comp}-csharp-binding)
        endforeach()
        add_dependencies(csharp-bindings ${CSHARP_BINDING_TARGETS})
   endif()
   
   # Add an "all" target to the system.
   if(WIN64INTEL OR WIN64MSVC)
       add_custom_target(all)
       if(DOC_TARGETS)
           add_dependencies(all fields-bindings tools-bindings doc)
       else()
           add_dependencies(all fields-bindings tools-bindings)
       endif()          
       set_target_properties(all PROPERTIES FOLDER "Library Targets")
   endif()           
endif()


