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
# This file contains declarations and functions unique to this component.
#

#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/component_functions.cmake)

#
# The current namespace
# The namespace should be ${COMPONENTS), but force it to remove all doubt.
#
set(NAME_SPACE tools CACHE STRING "C++ namespace for this project" FORCE)

#
# Create the build/include folder
#
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/${LPS_ID}/${NAME_SPACE})

#
# Define the clusters for this component.
#
if(BUILD_SHEAFSCOPE)
    set(clusters SheafScope common/client_server common/event common/gui common/util 
        util viewer/animation viewer/common viewer/event viewer/render viewer/table 
        viewer/user viewer/application)
else()
    set(clusters util)
endif()    
#
# Initialize all variables for this component.
#
set_component_vars()

#
# Add the clusters to the project
#
add_clusters("${clusters}")

#
# We don't have to use this decision structure. Windows and linux will ignore the other's lib vars. 
# Linux VARS will still show up in the CMake GUI unless we choose here.
#
if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    set(${COMPONENT}_IMPORT_LIBS  ${FIELDS_IMPORT_LIBS} 
        ${${COMPONENT}_IMPORT_LIB} 
        CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)

else()

    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_STATIC_LIBS ${FIELDS_STATIC_LIBS} 
        ${${COMPONENT}_STATIC_LIB} 
        CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_SHARED_LIBS ${FIELDS_SHARED_LIBS} 
        ${${COMPONENT}_SHARED_LIB} 
        CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)

endif()

#
# Set the cumulative Java binding library var for this component.
#
set(${COMPONENT}_JAVA_BINDING_LIBS ${FIELDS_JAVA_BINDING_LIBS} 
    ${${COMPONENT}_JAVA_BINDING_LIB} 
    CACHE STRING " Cumulative Java binding libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative Java binding jar variable for this component.
#
set(${COMPONENT}_JAVA_BINDING_JARS ${FIELDS_JAVA_BINDING_JARS} 
    ${PROJECT_NAME}_java_binding.jar 
    CACHE STRING "Cumulative Java bindings jars for ${PROJECT_NAME}")

#
# Set the cumulative Python binding library var for this component.
#
set(${COMPONENT}_PYTHON_BINDING_LIBS ${FIELDS_PYTHON_BINDING_LIBS} 
    ${${COMPONENT}_PYTHON_BINDING_LIB} 
    CACHE STRING " Cumulative Python binding libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative include path for this component.
#
#set(${COMPONENT}_IPATHS ${FIELDS_IPATHS} ${${COMPONENT}_IPATH} 
#    ${VTK_INCLUDE_DIRS} 
#    ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} ${TETGEN_INC_DIR} 
#    CACHE STRING " Cumulative include paths for ${PROJECT_NAME}")

#
# Specify component prerequisite include directories.
#
include_directories(${${COMPONENT}_IPATHS})

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Establish an aggregate list of files used to build the SHeafScope.
#
function(set_scope_sources)

    # clear the scope srcs var so consecutive cmake runs don't
    # list the same sources n times.
    unset(SHEAFSCOPE_SRCS CACHE)
    foreach(cluster ${clusters})
        file(GLOB scopesrcs . ${cluster}/*.java)
        set(SHEAFSCOPE_SRCS ${SHEAFSCOPE_SRCS} ${scopesrcs} 
            CACHE STRING "SheafScope java sources." FORCE)
    endforeach()
   string(REPLACE "\\" "/" SHEAFSCOPE_SRCS "${SHEAFSCOPE_SRCS}")
   # Write the contents of SHEAFSCOPE_SRCS to a file on disk.
   # We have to do this to overcome the Windows 8K character
   # command line limit in Windows.
   string(REGEX REPLACE ";" "\r" SHEAFSCOPE_SRCS "${SHEAFSCOPE_SRCS}")
   file(WRITE ${CMAKE_BINARY_DIR}/scopesrcs "${SHEAFSCOPE_SRCS}")
   mark_as_advanced(FORCE SHEAFSCOPE_SRCS)
   
endfunction(set_scope_sources)

#
# Create the library targets for this component.
#
function(add_library_targets)

    link_directories(${VTK_LIBRARY_DIRS})
        
    if(WIN64INTEL OR WIN64MSVC)
    
        # Tell the linker where to look for this project's libraries. 
        link_directories(${${COMPONENT}_OUTPUT_DIR})
    
        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_DYNAMIC_LIB} ${FIELDS_IMPORT_LIBS})
                 
        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${FIELDS_IMPORT_LIBS} 
            ${JNI_LIBRARIES} ${JAVA_AWT_LIBRARY} 
            ${JAVA_JVM_LIBRARY} ${VTK_LIBS} ) 
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} 
            PROPERTIES FOLDER "Library Targets")        
        
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS 
        # into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} 
            PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")
        
    else()

        # Linux
        
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_STATIC_LIB} 
            PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS})
    
        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES 
            OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIBS})
        
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
         
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} 
            PROPERTIES VERSION ${LIB_VERSION}) 
        
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIBS})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIBS})
    
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIBS} 
            ${JNI_LIBRARIES} ${JAVA_AWT_LIBRARY} ${JAVA_JVM_LIBRARY} ${VTK_LIBS})
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS} 
            ${JNI_LIBRARIES} ${JAVA_AWT_LIBRARY} ${JAVA_JVM_LIBRARY} ${VTK_LIBS})

    endif()
endfunction(add_library_targets)

#
# Create the bindings targets for this component.
#
function(add_bindings_targets)

    if(SWIG_FOUND AND BUILD_BINDINGS)  

        include_directories(${VTK_INCLUDE_DIRS})
        link_directories(${VTK_LIB_DIR}) 

        #
        # Java ################################################################
        #
        include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
        include_directories(${SHEAF_JAVA_BINDING_SRC_DIR})
        include_directories(${SHEAF_COMMON_BINDING_SRC_DIR})
        include_directories(${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR})
        include_directories(${FIBER_BUNDLES_COMMON_BINDING_SRC_DIR})
        include_directories(${GEOMETRY_JAVA_BINDING_SRC_DIR})
        include_directories(${GEOMETRY_COMMON_BINDING_SRC_DIR})
        include_directories(${FIELDS_JAVA_BINDING_SRC_DIR})
        include_directories(${FIELDS_COMMON_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_JAVA_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_COMMON_BINDING_SRC_DIR})
        
        
        set_source_files_properties(${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE} 
            PROPERTIES CPLUSPLUS ON)

        # Add the java binding library target
        swig_add_module(${${COMPONENT}_JAVA_BINDING_LIB} java 
            ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE})
        
        if(WIN64INTEL OR WIN64MSVC)
            add_dependencies(${${COMPONENT}_JAVA_BINDING_LIB} 
                ${FIELDS_JAVA_BINDING_LIBS} ${${COMPONENT}_IMPORT_LIBS})
            target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIBS} 
                ${FIELDS_JAVA_BINDING_LIBS} ${${COMPONENT}_IMPORT_LIBS})   
            set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} 
                PROPERTIES FOLDER "Binding Targets - Java")
        else()
            add_dependencies(${${COMPONENT}_JAVA_BINDING_LIB} 
                ${FIELDS_JAVA_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
            target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIBS} 
                ${${COMPONENT}_SHARED_LIB})   
        endif()
        
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} 
            PROPERTIES LINKER_LANGUAGE CXX)
                
        # Define the library version.
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} 
            PROPERTIES VERSION ${LIB_VERSION})

        target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} 
            ${${COMPONENT}_SHARED_LIB} 
            ${FIELDS_JAVA_BINDING_LIBS} ${VTK_LIBS} ${JDK_LIBS}) 

        list(APPEND ${COMPONENT}_CLASSPATH ${FIELDS_CLASSPATH} 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${${COMPONENT}_JAVA_BINDING_JAR} 
                ${VTK_JAR} ${JMF_JAR})
        set(${COMPONENT}_CLASSPATH ${${COMPONENT}_CLASSPATH} 
            CACHE STRING "Cumulative classpath for ${PROJECT_NAME}" FORCE)
        
         # Create the bindings jar file 
        if(WIN64INTEL OR WIN64MSVC)

            add_custom_target(${PROJECT_NAME}_java_binding.jar ALL
                   DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_JAR}
                   set_target_properties(${PROJECT_NAME}_java_binding.jar 
                   PROPERTIES FOLDER "Component Binding Jars")                           
                   COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
                   COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${FIELDS_CLASSPATH} ${VTK_JAR} ${JMF_JAR}" -d . *.java
                   COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
                   COMMAND ${Java_JAR_EXECUTABLE} cvf 
                    ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${${COMPONENT}_JAVA_BINDING_JAR}  
                   ${JAVA_BINDINGS_ROOT}/*.class
                 )
                             
            # Java documentation
            if(DOC_TARGETS)
                add_custom_target(${PROJECT_NAME}-java-docs ALL
                        COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle 
                        "${PROJECT_NAME} documentation" -classpath "${FIELDS_CLASSPATH}" 
                        -d  ${CMAKE_BINARY_DIR}/documentation/java/${PROJECT_NAME}  
                        *.java WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        DEPENDS ${${COMPONENT}_JAVA_BINDING_JAR}
                     )
            set_target_properties(${PROJECT_NAME}-java-docs PROPERTIES FOLDER "Documentation Targets")                                                  
            endif()
        else()
        
            # The default list item separator in cmake is ";". If Linux, then exchange ";" for  the UNIX style ":"
            # and store the result in parent_classpath.
            string(REGEX REPLACE ";" ":" parent_classpath "${FIELDS_CLASSPATH}")
            string(REGEX REPLACE ";" ":" this_classpath "${${COMPONENT}_CLASSPATH}")
            add_custom_target(${PROJECT_NAME}_java_binding.jar ALL
                   DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_JAR}
                   COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
                   COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${parent_classpath}" -d . *.java
                   COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
                   COMMAND ${Java_JAR_EXECUTABLE} cvf 
                   ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR}  
                   ${JAVA_BINDINGS_ROOT}/*.class
                 )
            
            # Java documentation
             if(DOC_TARGETS)            
                add_custom_target(${PROJECT_NAME}-java-docs ALL
                        COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle 
                        "${PROJECT_NAME} documentation" -classpath "${this_classpath}" 
                        -d  ${CMAKE_BINARY_DIR}/documentation/java/${PROJECT_NAME}  
                        *.java WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        DEPENDS ${${COMPONENT}_JAVA_BINDING_JAR}
                     )
            endif()                                      
        endif()

        set_target_properties(${PROJECT_NAME}_java_binding.jar PROPERTIES FOLDER "Library Jars") 
        mark_as_advanced(FORCE ${COMPONENT}_CLASSPATH) 
     
         # Establish the SheafScope jar dir
         set(LIB_JAR_DIR ${CMAKE_BINARY_DIR}/SheafScope)
    if(BUILD_SHEAFSCOPE)   
         # Build the SheafScope jar
        if(WIN64INTEL OR WIN64MSVC)
             add_custom_target(SheafScope.jar ALL 
                     DEPENDS ${PROJECT_NAME}_java_binding.jar 
                     COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}
                     COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
                     COMMAND ${Java_JAVAC_EXECUTABLE} -classpath 
                         "${${COMPONENT}_CLASSPATH}" -g -d ${LIB_JAR_DIR} 
                         @${CMAKE_BINARY_DIR}/scopesrcs
	                 COMMAND ${CMAKE_COMMAND} -E make_directory 
	                     ${LIB_JAR_DIR}/tools/common/gui/resources
	                 COMMAND ${CMAKE_COMMAND} -E make_directory 
	                     ${LIB_JAR_DIR}/tools/viewer/resources/docs
                     COMMAND ${CMAKE_COMMAND} -E make_directory 
                         ${LIB_JAR_DIR}/tools/SheafScope/resources/docs

	                 COMMAND ${CMAKE_COMMAND} -E copy_directory 
	                     ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/common/gui/resources
	                     ${LIB_JAR_DIR}/tools/common/gui/resources
	                 COMMAND ${CMAKE_COMMAND} -E copy_directory 
	                     ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/viewer/resources
	                     ${LIB_JAR_DIR}/tools/viewer/resources
	                 COMMAND ${CMAKE_COMMAND} -E copy_directory 
	                     ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/viewer/resources/docs
	                     ${LIB_JAR_DIR}/tools/viewer/resources/docs
	                 COMMAND ${CMAKE_COMMAND} -E copy_directory 
	                     ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/resources      
	                     ${LIB_JAR_DIR}/tools/SheafScope/resources
	                 COMMAND ${CMAKE_COMMAND} -E copy_directory 
	                 ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/resources/docs 
	                 ${LIB_JAR_DIR}/tools/SheafScope/resources/docs 

                     COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
                     COMMAND ${Java_JAR_EXECUTABLE} cvmf 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/manifest.txt 
                         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/SheafScope.jar  
                         -C ${LIB_JAR_DIR} .
                  )
        else()
         # Build the SheafScope jar
             add_custom_target(SheafScope.jar ALL 
                     DEPENDS ${PROJECT_NAME}_java_binding.jar 
                     COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}
                     COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
                     COMMAND ${Java_JAVAC_EXECUTABLE} -classpath 
                     "${this_classpath}" -g -d ${LIB_JAR_DIR} @${CMAKE_BINARY_DIR}/scopesrcs
                     COMMAND ${CMAKE_COMMAND} -E make_directory 
                         ${LIB_JAR_DIR}/tools/common/gui/resources
                     COMMAND ${CMAKE_COMMAND} -E make_directory 
                         ${LIB_JAR_DIR}/tools/viewer/resources/docs
                     COMMAND ${CMAKE_COMMAND} -E make_directory 
                         ${LIB_JAR_DIR}/tools/SheafScope/resources/docs
        
                     COMMAND ${CMAKE_COMMAND} -E copy_directory 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/common/gui/resources      
                         ${LIB_JAR_DIR}/tools/common/gui/resources
                     COMMAND ${CMAKE_COMMAND} -E copy_directory 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/viewer/resources          
                         ${LIB_JAR_DIR}/tools/viewer/resources
                     COMMAND ${CMAKE_COMMAND} -E copy_directory 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/viewer/resources/docs     
                         ${LIB_JAR_DIR}/tools/viewer/resources/docs
                     COMMAND ${CMAKE_COMMAND} -E copy_directory 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/resources      
                         ${LIB_JAR_DIR}/tools/SheafScope/resources
                     COMMAND ${CMAKE_COMMAND} -E copy_directory 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/resources/docs 
                         ${LIB_JAR_DIR}/tools/SheafScope/resources/docs 
        
                     COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
                     COMMAND ${Java_JAR_EXECUTABLE} cvmf 
                         ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/manifest.txt 
                         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SheafScope.jar -C ${LIB_JAR_DIR} .
                  )
        endif()
        
        set_target_properties(SheafScope.jar PROPERTIES FOLDER "Executable Jars") 
 
        add_dependencies(${PROJECT_NAME}-bindings ${PROJECT_NAME}_java_binding.jar SheafScope 
            ${PROJECT_NAME}-python-binding)
    endif()  # BUILD_SHEAFSCOPE      
        # Guard these until we can get the VS solution explorer aesthetic issues sorted
        if(LINUX64GNU OR LINUX64INTEL) 
            add_dependencies(${PROJECT_NAME}-java-binding ${PROJECT_NAME}_java_binding.jar)    
            add_dependencies(${PROJECT_NAME}-python-binding ALL fields-python-binding)
            add_dependencies(${PROJECT_NAME}-python-binding ALL fields-python-binding)
        endif() 
        
    endif()
    
endfunction(add_bindings_targets)

# 
# Set the commands for the install target
#
function(add_install_target)

    if(LINUX64INTEL OR LINUX64GNU)
        if(BUILD_SHEAFSCOPE)
            install(TARGETS ${${COMPONENT}_SHARED_LIB} EXPORT ${${COMPONENT}_SHARED_LIB} 
                LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            install(TARGETS ${${COMPONENT}_STATIC_LIB} ARCHIVE 
                DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        endif()                     
        if(SWIG_FOUND AND BUILD_BINDINGS)
            install(TARGETS ${${COMPONENT}_JAVA_BINDING_LIB} LIBRARY 
                DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR}
                 DESTINATION ${CMAKE_BUILD_TYPE}/lib)  
            install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SheafScope.jar 
                DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            install(PROGRAMS ${JMF_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            install(PROGRAMS ${VTK_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            install(PROGRAMS ${JDK_LIBS} DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            # Only install python binding if the component has a target for it.
            if(TARGET ${${COMPONENT}_PYTHON_BINDING_LIB})
                install(TARGETS ${${COMPONENT}_PYTHON_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            endif()
        endif()
            install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dumpsheaf 
                DESTINATION ${CMAKE_BUILD_TYPE}/bin)
        
    elseif(WIN64INTEL OR WIN64MSVC)

        # The BUILD_TYPE variable will be set while CMake is processing the install files. It is not set at configure time
        # for this project. We pass it literally here. 
        if(BUILD_SHEAFSCOPE)
            install(TARGETS ${${COMPONENT}_IMPORT_LIB} EXPORT 
                ${${COMPONENT}_IMPORT_LIB} ARCHIVE 
                DESTINATION lib/\${BUILD_TYPE})
            install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_DYNAMIC_LIB}_d.pdb 
                DESTINATION bin/\${BUILD_TYPE} OPTIONAL)
            install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_DYNAMIC_LIB}.pdb 
                DESTINATION bin/\${BUILD_TYPE} OPTIONAL)
            install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/SheafScope.jar 
                DESTINATION bin/\${BUILD_TYPE} OPTIONAL)
        endif()    
                
        if(SWIG_FOUND AND BUILD_BINDINGS)
            install(TARGETS ${${COMPONENT}_JAVA_BINDING_LIB} 
                RUNTIME DESTINATION bin/\${BUILD_TYPE})
            # Add the pdb files               
            install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_JAVA_BINDING_LIB}_d.pdb 
                DESTINATION bin/\${BUILD_TYPE} OPTIONAL)                
            install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_JAVA_BINDING_LIB}.pdb 
                DESTINATION bin/\${BUILD_TYPE} OPTIONAL)              
            install(PROGRAMS ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_JAVA_BINDING_JAR} 
                DESTINATION lib/\${BUILD_TYPE} OPTIONAL)  
            install(PROGRAMS ${JMF_JAR} DESTINATION lib/\${BUILD_TYPE} OPTIONAL)
            install(PROGRAMS ${VTK_JAR} DESTINATION lib/\${BUILD_TYPE} OPTIONAL)
            install(PROGRAMS ${JDK_LIBS} DESTINATION lib/\${BUILD_TYPE} OPTIONAL)
        endif()
    endif()
    
    install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/dumpsheaf.exe 
        DESTINATION bin/\${BUILD_TYPE} OPTIONAL)
    install(FILES ${${COMPONENT}_INCS} DESTINATION include) 
                         
endfunction(add_install_target)

function(add_dumpsheaf_target)

    add_executable(dumpsheaf ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/util/dumpsheaf.cc)
    
    # Make sure the library is up to date
    if(WIN64MSVC OR WIN64INTEL)
        add_dependencies(dumpsheaf ${FIBER_BUNDLE_IMPORT_LIB})
        target_link_libraries(dumpsheaf ${FIBER_BUNDLE_IMPORT_LIBS})
    else()
        add_dependencies(dumpsheaf ${FIBER_BUNDLE_SHARED_LIB})
        target_link_libraries(dumpsheaf ${FIBER_BUNDLE_SHARED_LIB})
    endif()

    # Supply the *_DLL_IMPORTS directive to preprocessor
    set_target_properties(dumpsheaf PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
    # Put the target in the Utilities VS folder.
    set_target_properties(dumpsheaf PROPERTIES FOLDER "Utilities")
                
endfunction(add_dumpsheaf_target)

function(add_sheafscope_wrapper_target)

    add_executable(sheafscope ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/util/SheafScope.cc)
    
    # Make sure the library is up to date
    if(WIN64MSVC OR WIN64INTEL)
        add_dependencies(sheafscope ${TOOLS_IMPORT_LIB})
        target_link_libraries(sheafscope ${TOOLS_IMPORT_LIBS})
    else()
        add_dependencies(sheafscope ${TOOLS_SHARED_LIB})
        target_link_libraries(sheafscope ${TOOLS_SHARED_LIBS})
    endif()

    # Supply the *_DLL_IMPORTS directive to preprocessor
    set_target_properties(sheafscope PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
    # Put the target in the Utilities VS folder.
    set_target_properties(sheafscope PROPERTIES FOLDER "Utilities")
                
endfunction(add_sheafscope_wrapper_target)
