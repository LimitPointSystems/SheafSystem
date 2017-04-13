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
# System level library targets
#
function(SheafSystem_add_system_library_targets)

   # Preconditions:

   # Requires component level targets already defined.

   dbc_require(SHEAFSYSTEM_LINUX)
   dbc_require_target(fields-shared-lib)
   dbc_require_target(fields-static-lib)

   if(SHEAFSYSTEM_BUILD_BINDINGS)
      dbc_require_target(tools-shared-lib)
      dbc_require_target(tools-static-lib)
   endif()

   # Body:

   # "shared-libs" builds solely shared libs
   # Depends directly on tools, tools depends on fields, etc.,
   # but tools libs only built if bindings are on.

   add_custom_target(shared-libs)
   if(SHEAFSYSTEM_BUILD_BINDINGS)
      add_dependencies(shared-libs tools-shared-lib)
   else()
      add_dependencies(shared-libs fields-shared-lib)
   endif()

   # "static-libs" builds solely static libs
   # Depends directly on tools, tools depends on fields, etc.,
   # but tools libs only built if bindings are on.

   add_custom_target(static-libs)
   if(SHEAFSYSTEM_BUILD_BINDINGS)
      add_dependencies(static-libs tools-static-lib)
   else()
      add_dependencies(static-libs fields-static-lib)
   endif()
   
   # Alias for shared lib; backward naming compatability with gnu system

   add_custom_target(lib)
   add_dependencies(lib shared-libs)


endfunction(SheafSystem_add_system_library_targets)

#
# Realclean target.
#
function(SheafSystem_add_realclean_target)

   # Preconditions:

   dbc_require(SHEAFSYSTEM_LINUX)

   # Body:

   add_custom_target(realclean 
      COMMAND ${CMAKE_COMMAND} --build  ${CMAKE_BINARY_DIR} --target clean
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/documentation) 

endfunction(SheafSystem_add_realclean_target)

#
# System level bindings Documentation targets
#
function(SheafSystem_add_system_bindings_sheafsystem_doc_targets)

   # Preconditions:

   # Can't add bindings doc targets unless both bindings and docs are enabled.

   dbc_require(SHEAFSYSTEM_DOC_TARGETS)
   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   # Also requires component doc targets already defined; 
   # not sure how to implement that.

   dbc_unexecutable_require("Component doc targets already defined.")

   # Body:

   add_custom_target(java-docs)

   # $$TODO: this list, and the one for bindings above, should be populated programmatically,
   # NOT by hand. Fix it.

   add_dependencies(java-docs sheaves-java-docs fiber_bundles-java-docs geometry-java-docs
      fields-java-docs tools-java-docs)

   set_target_properties(java-docs PROPERTIES FOLDER "Documentation Targets")
   
   add_custom_target(alldocs DEPENDS doc java-docs)
   set_target_properties(alldocs PROPERTIES FOLDER "Documentation Targets")

endfunction(SheafSystem_add_system_bindings_sheafsystem_doc_targets)

#
# System level bindings targets
#
function(SheafSystem_add_system_bindings_targets)

   # Can't add bindings doc targets unless both bindings and docs are enabled.

   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   # Also requires component doc targets already defined; 
   # not sure how to implement that.

   dbc_unexecutable_require("Component binding targets already defined.")

   # "make bindings" builds libs and bindings for all components.
   # <component>-bindings builds all prerequisite libs and bindings for <component>

   add_custom_target(bindings)
   set_target_properties(bindings PROPERTIES FOLDER "Binding Targets - Component")

   add_dependencies(bindings tools-bindings fields-bindings)

   #Review this. These convenience targets clutter the Solution Explorer.
   # Turning them off in windows for now.

   if(SHEAFSYSTEM_LINUX)        

      # Aggregate java bindings target

      add_custom_target(java-bindings)
      add_dependencies(java-bindings tools-java-binding fields-java-binding)

      # Aggregate python bindings target

      add_custom_target(python-bindings)
      add_dependencies(python-bindings fields-python-binding)

      # Aggregate csharp bindings target

      add_custom_target(csharp-bindings)
      add_dependencies(csharp-bindings fields-csharp-binding)

   endif()
   

endfunction(SheafSystem_add_system_bindings_targets)

#
# Add the documentation targets.
# Default Doc state is "Dev"
#
function(SheafSystem_add_sheafsystem_doc_targets)

   if(SHEAFSYSTEM_DOC_TARGETS)
      if(SHEAFSYSTEM_DOC_STATE MATCHES Dev OR SHEAFSYSTEM_DOC_STATE MATCHES dev OR SHEAFSYSTEM_DOC_STATE MATCHES DEV)
         add_custom_target(doc 
            # ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Generating Developer Documentation ... " 
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/dev_doxyfile
            )
      else()
         add_custom_target(doc 
            # ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Generating User Documentation ... "  
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/user_doxyfile
            )
      endif()
      set_target_properties(doc PROPERTIES FOLDER "Documentation Targets")    
   endif() 

endfunction(SheafSystem_add_sheafsystem_doc_targets)


# 
#  Make emacs tags
#
function(SheafSystem_add_tags_target)

   # Preconditions:

   dbc_require(SHEAFSYSTEM_LINUX)

   # Body:

   add_custom_target(tags
      COMMAND find ${CMAKE_CURRENT_SOURCE_DIR} -name build -prune -o -name "*.cc" -print -o -name "*.h" -print -o -name "*.t.cc" -print | etags --c++ --members -
      )

endfunction(SheafSystem_add_tags_target) 

#
# Add the help targets.
#
function(SheafSystem_add_help_targets)


   add_custom_target(help-help
      COMMAND ${CMAKE_COMMAND} -E echo "    "     
      COMMAND ${CMAKE_COMMAND} -E echo "    "  
      COMMAND ${CMAKE_COMMAND} -E echo "The following help targets are available: "
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "    help-targets -- lists available system targets."
      COMMAND ${CMAKE_COMMAND} -E echo "    help-cmake-options -- Things you can say to cmake to affect the build system state."
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "")
   
   add_custom_target(help-cmake-options
      COMMAND ${CMAKE_COMMAND} -E echo "" 
      COMMAND ${CMAKE_COMMAND} -E echo "SHEAFSYSTEM_BUILD_SHEAFSCOPE:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Toggles generation of SheafScope target. "
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: boolean"         
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: OFF"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DSHEAFSYSTEM_BUILD_SHEAFSCOPE=ON"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DSHEAFSYSTEM_BUILD_SHEAFSCOPE=ON .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_BUILD_TYPE:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Sets the default build type for this run. Only meaningful in Linux "
      COMMAND ${CMAKE_COMMAND} -E echo "    as build type is chosen at compile time in Visual Studio."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: string"         
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: Debug_contracts"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DCMAKE_BUILD_TYPE=Release_contracts"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DCMAKE_BUILD_TYPE=Release_contracts .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "ENABLE_COVERAGE:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Toggles Intel compiler flag for generating coverage data. "
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: boolean"         
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: OFF"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DENABLE_COVERAGE=ON"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DENABLE_COVERAGE=ON .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "SHEAFSYSTEM_DOC_STATE:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Changes nature of generated documentation. "
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: string"         
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: user"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DSHEAFSYSTEM_DOC_STATE=dev"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DSHEAFSYSTEM_DOC_STATE=dev .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "SHEAFSYSTEM_INSTALL_DOCS:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Toggles installation of generated documentation. "
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: boolean"         
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: OFF"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DSHEAFSYSTEM_INSTALL_DOCS=ON"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DSHEAFSYSTEM_INSTALL_DOCS=ON .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "SHEAFSYSTEM_BUILD_BINDINGS:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Toggles bindings targets. Implies BUILD_TOOLS=ON "
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: boolean"         
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: OFF"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DSHEAFSYSTEM_BUILD_BINDINGS=ON"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DSHEAFSYSTEM_BUILD_BINDINGS=ON .."  
      COMMAND ${CMAKE_COMMAND} -E echo "")
   
   add_custom_target(help-targets
      COMMAND ${CMAKE_COMMAND} -E echo "" 
      COMMAND ${CMAKE_COMMAND} -E echo "The fundamental targets are: "
      COMMAND ${CMAKE_COMMAND} -E echo "    all"
      COMMAND ${CMAKE_COMMAND} -E echo "    bindings"
      COMMAND ${CMAKE_COMMAND} -E echo "    coverage"
      COMMAND ${CMAKE_COMMAND} -E echo "    doc"
      COMMAND ${CMAKE_COMMAND} -E echo "    dumpsheaf"
      COMMAND ${CMAKE_COMMAND} -E echo "    lib"        
      COMMAND ${CMAKE_COMMAND} -E echo "    shared-libs"
      COMMAND ${CMAKE_COMMAND} -E echo "    static-libs"
      COMMAND ${CMAKE_COMMAND} -E echo "    SheafScope"


      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "all [default]:"
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the entire system -- shared libraries, static libraries, bindings, dumpsheaf, and all docs. "
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "bindings:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the shared libraries, bindings libraries, "
      COMMAND ${CMAKE_COMMAND} -E echo "    and associated jar files for all system components."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        Bindings targets can be invoked per component as well as per component-language."
      COMMAND ${CMAKE_COMMAND} -E echo "        All prerequisite libraries will be constructed in dependency order if needed."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-bindings"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-java-binding"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-python-binding"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-csharp-binding"     	
      COMMAND ${CMAKE_COMMAND} -E echo "    "            
      COMMAND ${CMAKE_COMMAND} -E echo "coverage:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Only available if C++ compiler is Intel."
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds all shared libraries and unit test routines using '-prof-gen=srcpos' on  " 
      COMMAND ${CMAKE_COMMAND} -E echo "    linux, or '/Qprof-gen:srcpos' on Windows , executes the unit tests, and generates coverage documentation."
      COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all"
      COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving"
      COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If make -j greater than 1, behavior may vary."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        Coverage targets can be invoked per component. All prerequisite libraries "
      COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-coverage"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves-coverage"
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "doc:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Constructs system-scope C++ library documentation, placing the output in CMAKE_BINARY_DIR/documentation."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"                    
      COMMAND ${CMAKE_COMMAND} -E echo "        java-docs -- Builds the system bindings and constructs java documentation for same."
      COMMAND ${CMAKE_COMMAND} -E echo "                     Does not construct the C++ library docs."
      COMMAND ${CMAKE_COMMAND} -E echo "        alldocs   -- Contructs C++ and java documentation    "
      COMMAND ${CMAKE_COMMAND} -E echo ""              
      COMMAND ${CMAKE_COMMAND} -E echo "dumpsheaf:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the dumpsheaf utility and its required shared libraries." 
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: none"
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "lib:"
      COMMAND ${CMAKE_COMMAND} -E echo "    Alias for shared-libs."
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the shared libraries, and only the shared libraries, for all system components."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: shared-libs"
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        [comp]-shared-lib will invoke the shared library target for [comp], dealing"
      COMMAND ${CMAKE_COMMAND} -E echo "        with dependencies in order."
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-shared-lib"   
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "shared-libs:"
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the shared libraries, and only the shared libraries, for all system components."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: lib"
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        [comp]-shared-lib will invoke the shared library target for [comp], dealing"
      COMMAND ${CMAKE_COMMAND} -E echo "        with dependencies in order."
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-shared-lib"   
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "static-libs:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the static libraries, and only the static libraries, for all system components.     "
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        \"<comp>\"-static-lib will invoke the static library target for \"<comp>\", dealing"
      COMMAND ${CMAKE_COMMAND} -E echo "        with dependencies in order."
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-static-lib"   
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "SheafScope:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds the SheafScope and all dependent shared libraries, bindings libraries, and jar files."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "    
      )

endfunction(SheafSystem_add_help_targets)


#
# Add all the system level targets.
#
function(SheafSystem_add_system_targets)

   if(SHEAFSYSTEM_LINUX)
      SheafSystem_add_system_library_targets()
      SheafSystem_add_tags_target()
      SheafSystem_add_realclean_target()
   endif()

   SheafSystem_add_sheafsystem_doc_targets()

   if(SHEAFSYSTEM_BUILD_BINDINGS)
      SheafSystem_add_system_bindings_sheafsystem_doc_targets()
      SheafSystem_add_system_bindings_targets()
   endif()

   # Add help targets.

   SheafSystem_add_help_targets()

endfunction(SheafSystem_add_system_targets)

