#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#
  
#
# Include functions and definitions common to all components.
# .
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Define the clusters for this component.
#
set(clusters concurrency dof_iterators dof_maps examples id_spaces io general
    iterators maps posets support traversers template_instantiations)

#
# Initialize all variables for this component.
#
set_component_vars()
#
# Add the clusters to the project
#
add_clusters("${clusters}")

#
# We don't have to use this decision structure. Windows and linux will ignore the other's lib vars. Just keeps things tidy in the CMake GUI.
#
if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    if(ENABLE_STATIC_PREREQS)
        set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIB}  CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)
    else()
        set(${COMPONENT}_IMPORT_LIBS ${HDF5_DLL_LIBRARY} ${${COMPONENT}_IMPORT_LIB}  CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)        
    endif()
    
else()

     if(ENABLE_STATIC_PREREQS)
        #
        # Set the cumulative static library var for this component.
        #
        set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)   
        #
        # Set the cumulative shared library var for this component.
        #
        set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)
    else()
        #
        # Set the cumulative static library var for this component.
        #
        set(${COMPONENT}_STATIC_LIBS ${HDF5_LIBRARIES} ${${COMPONENT}_STATIC_LIB} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)
        #
        # Set the cumulative shared library var for this component.
        #
        set(${COMPONENT}_SHARED_LIBS ${HDF5_LIBRARIES} ${${COMPONENT}_SHARED_LIB} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)
    endif()   
endif()

#
# Set the cumulative Java binding library var for this component.
#
set(${COMPONENT}_JAVA_BINDING_LIBS ${${COMPONENT}_JAVA_BINDING_LIB} CACHE STRING " Cumulative Java binding libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative Java binding jar variable for this component.
#
set(${COMPONENT}_JAVA_BINDING_JARS ${PROJECT_NAME}_java_binding.jar CACHE STRING "Cumulative Java bindings jars for ${PROJECT_NAME}")

#
# Set the cumulative Python binding library var for this component.
#
set(${COMPONENT}_PYTHON_BINDING_LIBS ${${COMPONENT}_PYTHON_BINDING_LIB} CACHE STRING " Cumulative Python binding libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative include path for this component.
#
set(${COMPONENT}_IPATHS ${${COMPONENT}_IPATH} ${CMAKE_BINARY_DIR}/include CACHE STRING " Cumulative include paths for ${PROJECT_NAME}" FORCE)

include_directories(${${COMPONENT}_IPATHS})

#
# Check for the presence of system cxx includes.
#
check_cxx_includes()
    
#
# Configure the STD header files
#
configure_std_headers()

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)
    if(WIN64INTEL OR WIN64MSVC)
        
        # Tell the linker where to look for this project's libraries.
        link_directories(${${COMPONENT}_OUTPUT_DIR})
        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} LINK_PRIVATE debug ${HDF5_LIBRARY_DIRS}/hdf5d.lib optimized ${HDF5_LIBRARY_DIRS}/hdf5.lib) 

   
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

    else()

        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES LINK_INTERFACE_LIBRARIES "") 
        target_link_libraries(${${COMPONENT}_STATIC_LIB} LINK_PRIVATE ${HDF5_LIBRARIES})
        
        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES LINK_INTERFACE_LIBRARIES "")        
        target_link_libraries(${${COMPONENT}_SHARED_LIB} LINK_PRIVATE ${HDF5_LIBRARIES})        

        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
 
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION})  
    
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIB})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIB})

    endif()

endfunction(add_library_targets)

#
# Create the bindings targets for this component.
#
function(add_bindings_targets)

    if(SWIG_FOUND AND BUILD_BINDINGS)

        include(${SWIG_USE_FILE})
        
        #
        # Java ################################################################
        #
 
        set(SWIG_CXX_EXTENSION "cxx" CACHE STRING "Swig source file extension")
        set(CMAKE_SWIG_FLAGS -package bindings.java CACHE STRING "Swig flags")

        include_directories(${JDK_INC_DIR} ${JDK_PLATFORM_INC_DIR})
        include_directories(${${COMPONENT}_JAVA_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_COMMON_BINDING_SRC_DIR})
        
        set_source_files_properties(${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE} PROPERTIES CPLUSPLUS ON)
     
        # Add the java binding library target
        swig_add_module(${${COMPONENT}_JAVA_BINDING_LIB} java ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE})
        
        if(WIN64INTEL OR WIN64MSVC)
            add_dependencies(${${COMPONENT}_JAVA_BINDING_LIB} ${${COMPONENT}_IMPORT_LIB} ${${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE} ${${COMPONENT}_SWIG_COMMON_INTERFACE})
            target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIBS} ${${COMPONENT}_IMPORT_LIB})
            set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES FOLDER "Binding Targets - Java")   
        else()
            add_dependencies(${${COMPONENT}_JAVA_BINDING_LIB} ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE} ${${COMPONENT}_SWIG_COMMON_INTERFACE})
            target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIBS} ${${COMPONENT}_SHARED_LIB})   
        endif()
        
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
        # Define the library version.
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES VERSION ${LIB_VERSION})
          
        # Create the bindings jar file
        # Output path in windows differs slightly from Linux. Cmake wont allow a conditional inside add_custom_target
        # So we have to do it outside.
        if(WIN64INTEL OR WIN64MSVC)
            set(${COMPONENT}_CLASSPATH ${OUTDIR}/${${COMPONENT}_JAVA_BINDING_JAR} CACHE STRING "Cumulative classpath for ${PROJECT_NAME}" FORCE)         
            add_custom_target(${PROJECT_NAME}_java_binding.jar ALL
                           DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB}
                           set_target_properties(${PROJECT_NAME}_java_binding.jar PROPERTIES FOLDER "Component Binding Jars")
    					   COMMAND ${CMAKE_COMMAND} -E copy ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/base_client.java ${CMAKE_CURRENT_BINARY_DIR}
                           COMMAND ${CMAKE_COMMAND} -E copy ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/base_server.java ${CMAKE_CURRENT_BINARY_DIR}
                           COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
                           COMMAND ${JAVAC_EXECUTABLE} -classpath . -d . *.java
                           COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
                           COMMAND ${JAR_EXECUTABLE} cvf ${OUTDIR}/${${COMPONENT}_JAVA_BINDING_JAR}  bindings/java/*.class
            )
        else()
            set(${COMPONENT}_CLASSPATH ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR} CACHE STRING "Cumulative classpath for ${PROJECT_NAME}" FORCE)   
            add_custom_target(${PROJECT_NAME}_java_binding.jar ALL
                           DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB}
    					   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/base_client.java ${CMAKE_CURRENT_BINARY_DIR}
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/base_server.java ${CMAKE_CURRENT_BINARY_DIR}
                           COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
                           COMMAND ${JAVAC_EXECUTABLE} -classpath . -d . *.java
                           COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
                           COMMAND ${JAR_EXECUTABLE} cvf ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR}  bindings/java/*.class
             )        
        endif()

        set_target_properties(${PROJECT_NAME}_java_binding.jar PROPERTIES FOLDER "Library Jars") 
        mark_as_advanced(FORCE ${COMPONENT}_CLASSPATH)        

        # Java documentation
        add_custom_target(${PROJECT_NAME}-java-docs ALL
                    COMMAND ${JDK_BIN_DIR}/javadoc -quiet -windowtitle "${PROJECT_NAME} documentation" -classpath "${${COMPONENT}_CLASSPATH}" 
                    -d  ${CMAKE_BINARY_DIR}/documentation/java/${PROJECT_NAME}  
                    *.java WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    DEPENDS ${${COMPONENT}_JAVA_BINDING_JAR}
                    )
        set_target_properties(${PROJECT_NAME}-java-docs PROPERTIES FOLDER "Documentation Targets")

        
        #
        # CSharp ##############################################################
        #
        
        #set(CMAKE_SWIG_FLAGS -c++ -w842 -namespace sheaf)
        set(CMAKE_SWIG_FLAGS -c++ -namespace sheaf)        

        # Add the csharp binding library target
        set_source_files_properties(${${COMPONENT}_CSHARP_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_CSHARP_INTERFACE} PROPERTIES CPLUSPLUS ON)
        swig_add_module(${${COMPONENT}_CSHARP_BINDING_LIB} csharp ${${COMPONENT}_CSHARP_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_CSHARP_INTERFACE})

        if(WIN64INTEL OR WIN64MSVC)
            add_dependencies(${${COMPONENT}_CSHARP_BINDING_LIB} ${${COMPONENT}_IMPORT_LIB})
            target_link_libraries(${${COMPONENT}_CSHARP_BINDING_LIB} ${${COMPONENT}_IMPORT_LIB} ${CSHARP_LIBRARY})
            set_target_properties(${${COMPONENT}_CSHARP_BINDING_LIB} PROPERTIES FOLDER "Binding Targets - CSharp")
        else()
            add_dependencies(${${COMPONENT}_CSHARP_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
            target_link_libraries(${${COMPONENT}_CSHARP_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
        endif()    
        
        set_target_properties(${${COMPONENT}_CSHARP_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
    
        # Define the library version.
        set_target_properties(${${COMPONENT}_CSHARP_BINDING_LIB} PROPERTIES VERSION ${LIB_VERSION})

        # Create the csharp assembly
        if(WIN64INTEL OR WIN64MSVC)
            add_custom_target(${${COMPONENT}_CSHARP_BINDING_ASSY} ALL
                        COMMAND ${CMAKE_COMMAND} -E echo ""
                        COMMAND ${CMAKE_COMMAND} -E echo "Creating Csharp Binding for ${PROJECT_NAME} ..."
                        COMMAND ${CMAKE_COMMAND} -E echo ""                           
                        COMMAND ${CSHARP_COMPILER} /nologo /noconfig /warn:1 /errorreport:prompt /target:library /out:${OUTDIR}/${${COMPONENT}_CSHARP_BINDING_ASSY}  ${CMAKE_CURRENT_BINARY_DIR}/*.cs
                            DEPENDS ${${COMPONENT}_CSHARP_BINDING_ASSY} ${${COMPONENT}_CSHARP_BINDING_LIB}
            )
        else()
            add_custom_target(${${COMPONENT}_CSHARP_BINDING_ASSY} ALL
                        COMMAND ${CSHARP_COMPILER} -target:library -nowarn:0114,0108 -out:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_CSHARP_BINDING_ASSY}  ${CMAKE_CURRENT_BINARY_DIR}/*.cs
            )
       
        endif()
        add_dependencies(${${COMPONENT}_CSHARP_BINDING_ASSY} ${${COMPONENT}_CSHARP_BINDING_LIB})       
        set_target_properties(${${COMPONENT}_CSHARP_BINDING_ASSY} PROPERTIES FOLDER "CSharp Assembly Targets")


        #
        # Python ############################################################## 
        #

        set(CMAKE_SWIG_FLAGS -c++ )
        
        include_directories(${PYTHON_INCLUDE_DIRS})
        
        set_source_files_properties(${${COMPONENT}_PYTHON_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_PYTHON_INTERFACE} PROPERTIES CPLUSPLUS ON)
        swig_add_module(${${COMPONENT}_PYTHON_BINDING_LIB} python ${${COMPONENT}_PYTHON_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_PYTHON_INTERFACE})
        
        if(WIN64INTEL OR WIN64MSVC)
            add_dependencies(${${COMPONENT}_PYTHON_BINDING_LIB} ${${COMPONENT}_IMPORT_LIB} ${${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE} ${${COMPONENT}_SWIG_COMMON_INTERFACE})
            # Including both release and debug libs here. Linker is smart enough to know which one to use, and since the build type is a run-time decision in VS
            # we have no way to choose when generating the make file.
            target_link_libraries(${${COMPONENT}_PYTHON_BINDING_LIB} ${${COMPONENT}_IMPORT_LIB} ${PYTHON_LIBRARY} ${PYTHON_DEBUG_LIBRARY} )
            set_target_properties(${${COMPONENT}_PYTHON_BINDING_LIB} PROPERTIES FOLDER "Binding Targets - Python")
        else()
            add_dependencies(${${COMPONENT}_PYTHON_BINDING_LIB} ${${COMPONENT}_SHARED_LIB}${${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE} ${${COMPONENT}_SWIG_COMMON_INTERFACE})
            target_link_libraries(${${COMPONENT}_PYTHON_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
        endif()
        
        set_target_properties(${${COMPONENT}_PYTHON_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
    
        # Define the library version.
        set_target_properties(${${COMPONENT}_PYTHON_BINDING_LIB} PROPERTIES VERSION ${LIB_VERSION})  
 
        # Guard these until we can get the VS solution explorer aesthetic issues sorted
        if(LINUX64GNU OR LINUX64INTEL) 
            add_dependencies(${PROJECT_NAME}-java-binding ${PROJECT_NAME}_java_binding.jar)    
            add_dependencies(${PROJECT_NAME}-python-binding ${${COMPONENT}_PYTHON_BINDING_LIB})
            add_dependencies(${PROJECT_NAME}-csharp-binding ${${COMPONENT}_CSHARP_BINDING_LIB})
        endif()

        # bindings target aliases already declared at system level. Add dependencies here.
        add_dependencies(${PROJECT_NAME}-bindings ${PROJECT_NAME}_java_binding.jar ${${COMPONENT}_PYTHON_BINDING_LIB} ${${COMPONENT}_CSHARP_BINDING_LIB})
        
    endif()

endfunction(add_bindings_targets)

# 
# Set the commands for the install target
#
function(add_install_target)

        if(LINUX64INTEL OR LINUX64GNU)
            install(TARGETS ${${COMPONENT}_SHARED_LIB} EXPORT ${${COMPONENT}_SHARED_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
            install(TARGETS ${${COMPONENT}_STATIC_LIB} ARCHIVE DESTINATION ${CMAKE_BUILD_TYPE}/lib)

            if(SWIG_FOUND AND BUILD_BINDINGS)
                install(TARGETS ${${COMPONENT}_JAVA_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
                install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)  
                # Only install python binding if the component has a target for it.
                if(TARGET ${${COMPONENT}_PYTHON_BINDING_LIB})
                    install(TARGETS ${${COMPONENT}_PYTHON_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
                endif()
                install(TARGETS ${${COMPONENT}_CSHARP_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
                install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_CSHARP_BINDING_ASSY} DESTINATION ${CMAKE_BUILD_TYPE}/lib)             
            endif()
            
        elseif(WIN64INTEL OR WIN64MSVC)

            # The BUILD_TYPE variable will be set while CMake is processing the install files. It is not set at configure time
            # for this project. We pass it literally here.
            
            install(TARGETS ${${COMPONENT}_IMPORT_LIB} EXPORT ${${COMPONENT}_IMPORT_LIB} ARCHIVE DESTINATION lib/\${BUILD_TYPE})
            install(TARGETS ${${COMPONENT}_DYNAMIC_LIB} RUNTIME DESTINATION bin/\${BUILD_TYPE})

            # Only try to install the pdb files if they exist. Easier to determine existence than the current config type in win32.
            if(EXISTS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug-contracts/${${COMPONENT}_DYNAMIC_LIB}.pdb")
                install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug-contracts/${${COMPONENT}_DYNAMIC_LIB}.pdb DESTINATION bin/\${BUILD_TYPE})
            elseif(EXISTS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug-no-contracts/${${COMPONENT}_DYNAMIC_LIB}.pdb")
                install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug-no-contracts/${${COMPONENT}_DYNAMIC_LIB}.pdb DESTINATION bin/\${BUILD_TYPE})               
            endif()
              
            if(SWIG_FOUND AND BUILD_BINDINGS)
                install(TARGETS ${${COMPONENT}_JAVA_BINDING_LIB} RUNTIME DESTINATION bin/\${BUILD_TYPE})
                install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_JAVA_BINDING_JAR} DESTINATION lib/\${BUILD_TYPE})  
                # Only install python binding if the component has a target for it.
                if(TARGET ${${COMPONENT}_PYTHON_BINDING_LIB})
                    install(TARGETS ${${COMPONENT}_PYTHON_BINDING_LIB} ARCHIVE DESTINATION lib/\${BUILD_TYPE})
                endif()
                install(TARGETS ${${COMPONENT}_CSHARP_BINDING_LIB} RUNTIME DESTINATION bin/\${BUILD_TYPE})
                install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${BUILD_TYPE}/${${COMPONENT}_CSHARP_BINDING_ASSY} DESTINATION bin/\${BUILD_TYPE})              
            endif()
        endif()

        install(FILES ${${COMPONENT}_INCS} DESTINATION include) 
        install(FILES ${STD_HEADERS} DESTINATION include)
                     
endfunction(add_install_target)

