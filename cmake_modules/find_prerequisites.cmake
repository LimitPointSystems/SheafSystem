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
# Functions for prerequisite discovery.
#


#
# Checks if the variable with name xvar_name is a valid absolute path to a directory.
#
function(SheafSystem_check_dir_prereq xvar_name)
   # message("Entering SheafSystem_check_dir_prereq")
   
   # Body:

   if(NOT IS_ABSOLUTE ${${xvar_name}})

      # Path is not absolute.
      
      message("Error in ${xvar_name}: path ${${xvar_name}} is not absolute.")
      set(LVAR_IS_VALID FALSE PARENT_SCOPE)

   elseif(NOT EXISTS ${${xvar_name}})

      # Path doesn't exist.
      
      message("Error in ${xvar_name}: path ${${xvar_name}} does not exist.")
      set(LVAR_IS_VALID FALSE PARENT_SCOPE)

   elseif(NOT IS_DIRECTORY  ${${xvar_name}})

      # Path doesn't refer to a directory.
      
      message("Error in ${xvar_name}: path ${${xvar_name}} refers to a file, not a directory.")
      set(LVAR_IS_VALID FALSE PARENT_SCOPE)

   else()
      
      set(LVAR_IS_VALID TRUE PARENT_SCOPE)
      
   endif()

   # message("Leaving SheafSystem_check_dir_prereq")
endfunction(SheafSystem_check_dir_prereq xvar_name)


#
# Checks if the variable with name xvar_name is a valid absolute path to a file.
#
function(SheafSystem_check_exe_prereq xvar_name)
   # message("Entering SheafSystem_check_exe_prereq")
   
   # Body:

   if(NOT IS_ABSOLUTE ${${xvar_name}})

      # Path is not absolute.
      
      message("Error in ${xvar_name}: path ${${xvar_name}} is not absolute.")
      set(LVAR_IS_VALID FALSE PARENT_SCOPE)

   elseif(NOT EXISTS ${${xvar_name}})

      # Path doesn't exist.
      
      message("Error in ${xvar_name}: path ${${xvar_name}} does not exist.")
      set(LVAR_IS_VALID FALSE PARENT_SCOPE)

   elseif(IS_DIRECTORY  ${${xvar_name}})

      # Path doesn't refer to a file.
      
      message("Error in ${xvar_name}: path ${${xvar_name}} refers to a directory, not a file.")
      set(LVAR_IS_VALID FALSE PARENT_SCOPE)

   else()
      
      set(LVAR_IS_VALID TRUE PARENT_SCOPE)
      
   endif()

   # message("Leaving SheafSystem_check_exe_prereq")
endfunction(SheafSystem_check_exe_prereq xvar_name)

#
# Initializes variable <xvar_name> of type <xtype> as a prerequisite variable
# refering to a directory.
#
function(SheafSystem_init_dir_prereq xpkg_name xvar_name xdoc_string xinternal_var_name)   
   # message("Entering SheafSystem_init_dir_prereq xpkg_name.")
   
   # Preconditions:

   # Body:

   if(NOT ${xvar_name})
      
      # Variable is either not defined or empty.

      if(DEFINED ENV{${xvar_name}})

         # Client has defined variable as environment variable;
         # make it into a cache variable.

         set(${xvar_name} $ENV{${xvar_name}} CACHE PATH ${xdoc_string} FORCE)

         # Check if the PREREQ variable is valid absolute directory path; sets LVAR_IS_VALID)

         SheafSystem_check_dir_prereq(${xvar_name})

         # message("LVAR_IS_VALID=${LVAR_IS_VALID}")
         
         if(LVAR_IS_VALID)

            # Set the internal variable from the PREREQ variable.

            set(${xinternal_var_name} ${${xvar_name}} CACHE PATH ${xdoc_string} FORCE)
            mark_as_advanced(FORCE ${xinternal_var_name})

            set(LVAR_INITIALIZED TRUE PARENT_SCOPE)
            
         else()

            # PREREQ variable is invalid.
            # Set internal variables as if find_program failed.
            
            unset(${xinternal_var_name} CACHE)
            mark_as_advanced(FORCE ${xinternal_var_name})

            set(${xpkg_name}_FOUND FALSE CACHE BOOL "True if ${xpkg_name} found." FORCE)
            mark_as_advanced(FORCE ${xpkg_name}_FOUND)

            set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

            set(LVAR_INITIALIZED FALSE PARENT_SCOPE)
            
         endif()

      else()

         # Initialize to empty.

         set(${xvar_name} CACHE PATH ${xdoc_string} FORCE)

         # Unset the internal variable.
   
         unset(${xinternal_var_name} CACHE)   

         # Call the find function

         set(LVAR_INITIALIZED TRUE PARENT_SCOPE)

      endif()

   else()

      # Variable is already defined, possibly by -D on cmake invocation.
      # It appears from experiment that, in spite of documentation to the contrary,
      # the variable set by -D is not a cache variableif the type is not specified
      # on the command line. So force it.

      set(${xvar_name} ${${xvar_name}}  CACHE PATH ${xdoc_string} FORCE)

      # Check if the PREREQ variable is valid absolute dir path; sets LVAR_IS_VALID.

      SheafSystem_check_dir_prereq(${xvar_name})
      
      if(LVAR_IS_VALID)

         # Set the internal variable from the PREREQ variable.

         set(${xinternal_var_name} ${${xvar_name}} CACHE PATH ${xdoc_string} FORCE)
         mark_as_advanced(FORCE ${xinternal_var_name})

         set(LVAR_INITIALIZED TRUE PARENT_SCOPE)
         
      else()

         # PREREQ variable is invalid.

         # Set internal variables as if find_package failed.
         
         unset(${xinternal_var_name} CACHE)
         mark_as_advanced(FORCE ${xinternal_var_name})
         
         set(${xpkg_name}_FOUND FALSE CACHE BOOL "True if ${xpkg_name} found." FORCE)
         mark_as_advanced(FORCE ${xpkg_name}_FOUND)

         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

         set(LVAR_INITIALIZED FALSE PARENT_SCOPE)
         
      endif()
       
   endif(NOT ${xvar_name})

   # Make sure the variable is not marked as advanced.

   mark_as_advanced(CLEAR ${xvar_name})
   
   # message("Leaving SheafSystem_init_dir_prereq xpkg_name.")
endfunction(SheafSystem_init_dir_prereq)

#
# Initializes variable <xvar_name> of type <xtype> as a prerequisite variable
# refering to an executable.
#
function(SheafSystem_init_exe_prereq xpkg_name xvar_name xdoc_string xinternal_var_name)   
   # message("Entering SheafSystem_init_exe_prereq xpkg_name.")
   
   # Preconditions:

   # Body:

   if(NOT ${xvar_name})
      
      # Variable is either not defined or empty.

      if(DEFINED ENV{${xvar_name}})

         # Client has defined variable as environment variable;
         # make it into a cache variable.

         set(${xvar_name} $ENV{${xvar_name}} CACHE FILEPATH ${xdoc_string} FORCE)

         # Check if the PREREQ variable is valid absolute file path; sets LVAR_IS_VALID)

         SheafSystem_check_exe_prereq(${xvar_name})

         # message("LVAR_IS_VALID=${LVAR_IS_VALID}")
         
         if(LVAR_IS_VALID)

            # Set the internal variable from the PREREQ variable.

            set(${xinternal_var_name} ${${xvar_name}} CACHE FILEPATH ${xdoc_string} FORCE)
            mark_as_advanced(FORCE ${xinternal_var_name})

            set(LVAR_INITIALIZED TRUE PARENT_SCOPE)
            
         else()

            # PREREQ variable is invalid but since it is set, if we try to use it
            # find_program will just return without checking it or setting any variables.
            # Set internal variables as if find_program failed.
            
            set(${xinternal_var_name} ${xinternal_var_name}-NOTFOUND CACHE FILEPATH ${xdoc_string} FORCE)
            mark_as_advanced(FORCE ${xinternal_var_name})

            set(${xpkg_name}_FOUND FALSE CACHE BOOL "True if ${xpkg_name} found." FORCE)
            mark_as_advanced(FORCE ${xpkg_name}_FOUND)

            set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

            set(LVAR_INITIALIZED FALSE PARENT_SCOPE)
            
         endif()

      else()

         # Initialize to empty.

         set(${xvar_name} CACHE FILEPATH ${xdoc_string} FORCE)

         # Unset the internal variable.
   
         unset(${xinternal_var_name} CACHE)   

         # Call the find function

         set(LVAR_INITIALIZED TRUE PARENT_SCOPE)

      endif()

   else()

      # Variable is already defined, possibly by -D on cmake invocation.
      # It appears from experiment that, in spite of documentation to the contrary,
      # the variable set by -D is not a cache variable if the type is not specified
      # on the command line. So force it.

      set(${xvar_name} ${${xvar_name}}  CACHE FILEPATH ${xdoc_string} FORCE)

      # Check if the PREREQ variable is valid absolute file path; sets LVAR_IS_VALID.

      SheafSystem_check_exe_prereq(${xvar_name})
      
      # message("LVAR_IS_VALID=${LVAR_IS_VALID}")
      
      if(LVAR_IS_VALID)

         # Set the internal variable from the PREREQ variable.

         set(${xinternal_var_name} ${${xvar_name}} CACHE FILEPATH ${xdoc_string} FORCE)
         mark_as_advanced(FORCE ${xinternal_var_name})

         # Call the find function

         set(LVAR_INITIALIZED TRUE PARENT_SCOPE)
         
      else()

         # PREREQ variable is invalid but since it is set, if we try to use it
         # find_program will just return without checking it or setting any variables.
         # Set internal variables as if find_program failed.
         
         set(${xinternal_var_name} ${xinternal_var_name}-NOTFOUND CACHE FILEPATH ${xdoc_string} FORCE)
         mark_as_advanced(FORCE ${xinternal_var_name})
         
         set(${xpkg_name}_FOUND FALSE CACHE BOOL "True if ${xpkg_name} found." FORCE)
         mark_as_advanced(FORCE ${xpkg_name}_FOUND)

         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

         set(LVAR_INITIALIZED FALSE PARENT_SCOPE)
         
      endif()
       
   endif(NOT ${xvar_name})

   # Make sure the variable is not marked as advanced.

   mark_as_advanced(CLEAR ${xvar_name})
   
   # message("Leaving SheafSystem_init_exe_prereq xpkg_name.")
endfunction(SheafSystem_init_exe_prereq)

#
# Find doxygen
#
function(SheafSystem_find_doxygen)
   # message("Entering SheafSystem_find_doxygen.")

   # Preconditions

   dbc_unexecutable_require("SheafSystem_find_dot called previously.")

   # Body:
   
   # Initialize the PREREQ variables.

   SheafSystem_init_exe_prereq(DOXYGEN PREREQ_DOXYGEN_EXECUTABLE "Path to doxygen executable." DOXYGEN_EXECUTABLE)

   # message("LVAR_INITIALIZED=${LVAR_INITIALIZED}")

   if(LVAR_INITIALIZED)

      find_program(DOXYGEN_EXECUTABLE doxygen)

      # find_program sets DOXYGEN_EXECUTABLE whether it finds it or not;
      # make sure it is marked advanced.

      mark_as_advanced(FORCE DOXYGEN_EXECUTABLE)

      if(DOXYGEN_EXECUTABLE)

         set(SHEAFSYSTEM_FOUND_DOXYGEN TRUE CACHE BOOL "True if found doxygen package" FORCE)

         # Update the PREREQ variable to where the executable  was actually found.

         set(PREREQ_DOXYGEN_EXECUTABLE ${DOXYGEN_EXECUTABLE} CACHE FILEPATH "Path to doxygen executable." FORCE)

         # Configure the doxygen options files.
         
         configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/dev_doxyfile.cmake.in
            ${CMAKE_BINARY_DIR}/dev_doxyfile)
         configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/user_doxyfile.cmake.in
            ${CMAKE_BINARY_DIR}/user_doxyfile)

         # Turn on document generation.
         
         set(SHEAFSYSTEM_DOC_TARGETS ON CACHE BOOL "ON to generate doc targets" FORCE)
         mark_as_advanced(FORCE SHEAFSYSTEM_DOC_TARGETS)
         
      else()

         set(SHEAFSYSTEM_FOUND_DOXYGEN FALSE CACHE BOOL "True if found doxygen package" FORCE)

         # Turn off document generation.

         set(SHEAFSYSTEM_DOC_TARGETS OFF CACHE BOOL "ON to generate doc targets" FORCE)
         mark_as_advanced(FORCE SHEAFSYSTEM_DOC_TARGETS)
         
         message("Unable to find doxygen executable. Documentation will not be generated.")
         
      endif()
      
   else()

         set(SHEAFSYSTEM_FOUND_DOXYGEN FALSE CACHE BOOL "True if found doxygen package" FORCE)

         # Turn off document generation.

         set(SHEAFSYSTEM_DOC_TARGETS OFF CACHE BOOL "ON to generate doc targets" FORCE)
         mark_as_advanced(FORCE SHEAFSYSTEM_DOC_TARGETS)      
         
         message("Unable to find doxygen executable. Documentation will not be generated.")

   endif(LVAR_INITIALIZED)

   dbc_ensure_defined(SHEAFSYSTEM_DOC_TARGETS)
   dbc_ensure_defined(SHEAFSYSTEM_FOUND_DOXYGEN)

   # message("Leaving SheafSystem_find_doxygen.")
endfunction(SheafSystem_find_doxygen)

#
# Find graphviz dot; must be called before SheafSystem_find_doxygen
# in order to configure doxygen option files correctly.
#
function(SheafSystem_find_dot)
   # message("Entering SheafSystem_find_dot.")
   
   # Initialize the PREREQ variable; sets LVAR_INITIALIZED.

   SheafSystem_init_exe_prereq(GRAPHVIZ PREREQ_GRAPHVIZ_DOT_EXECUTABLE
      "Path to graphviz dot executable." DOXYGEN_DOT_EXECUTABLE)

   # message("LVAR_INITIALIZED=${LVAR_INITIALIZED}")
   
   if(LVAR_INITIALIZED)

      find_program(DOXYGEN_DOT_EXECUTABLE dot)

      # find_program sets DOXYGEN_DOT_EXECUTABLE whether it finds it or not;
      # make sure it is marked advanced.

      mark_as_advanced(FORCE DOXYGEN_DOT_EXECUTABLE)

      set(SHEAFSYSTEM_FOUND_GRAPHVIZ ${DOXYGEN_DOT_FOUND} CACHE BOOL "True if found graphviz package" FORCE)

      if(DOXYGEN_DOT_EXECUTABLE)

         # Update the PREREQ variable to where the dot executable was actually found.

         set(PREREQ_GRAPHVIZ_DOT_EXECUTABLE ${DOXYGEN_DOT_EXECUTABLE}
            CACHE FILEPATH "Path to graphviz dot executable." FORCE)

         set(SHEAFSYSTEM_FOUND_GRAPHVIZ TRUE CACHE BOOL "True if found graphviz package" FORCE)

      else()
         
         message("Unable to find graphviz dot executable. Documentation will not contain diagrams.")      
         set(SHEAFSYSTEM_FOUND_GRAPHVIZ FALSE CACHE BOOL "True if found graphviz package" FORCE)
         
      endif()

   else()
      
      message("Unable to find graphviz dot executable. Documentation will not contain diagrams.")      
      set(SHEAFSYSTEM_FOUND_GRAPHVIZ FALSE CACHE BOOL "True if found graphviz package" FORCE)      
      
   endif(LVAR_INITIALIZED)

   # message("Leaving SheafSystem_find_dot.")
endfunction(SheafSystem_find_dot)

#
# Find HDF5.
#
function(SheafSystem_find_hdf5)

   # Initialize the PREREQ variable; sets LVAR_INITIALIED

   SheafSystem_init_dir_prereq(HDF5 PREREQ_HDF5_CONFIG_DIR
      "Path to folder containing hdf5-config.cmake" HDF5_DIR)
   
   if(LVAR_INITIALIZED)

      # Note that the find_package mechanism operates in two modes,
      # "MODULE" and "CONFIG" (= "NO_MODULE"). In MODULE mode it will
      # invoke Find<package>.cmake which typically invokes <package>-config.cmake
      # which typically imports the target export file <package>-targets.cmake.
      # In CONFIG mode, it skips the Find<package>.cmake module and goes directly
      # to the <package>-config.cmake module.
      # In version 1.8.16, HDF changed the targets exported by the hdf-targets.cmake
      # from "hdf" to "hdf-shared" and "hdf-static" so that both the static and static
      # libraries  could be created by a single build. Unfortunately, the FindHDF5.cmake
      # module supplied by CMake does not support these targets and fails to find HDF.
      # The work around, which is simpler and more direct anyway, is to use NO_MODULE
      # MODE. See the "Truobleshooting" section of the HDF5 documentation
      # at https://www.hdfgroup.org/HDF5/release/cmakebuild.html

      # Find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(HDF5_FOUND CACHE)
      
      find_package(HDF5 QUIET COMPONENTS C static NO_MODULE HINTS ${PREREQ_HDF5_CONFIG_DIR}
         NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH)

      # Find_package sets HDF5_DIR whether it finds HDF5 or not;
      # make it is advanced to keep the prereq settings uncluttered.
      #
      mark_as_advanced(FORCE HDF5_DIR)

      set(SHEAFSYSTEM_FOUND_HDF5 ${HDF5_FOUND} CACHE BOOL "True if found hdf5 package" FORCE)
      
      if(HDF5_FOUND)

         #
         # Update the PREREQ variable to where the config file was actually found.
         #
         set(PREREQ_HDF5_CONFIG_DIR "${HDF5_SHARE_DIR}" CACHE PATH "Path to folder containing hdf5-config.cmake" FORCE)

         #
         # Set HDF5_INCS cache variable; 
         # probably should extract this from hdf5 exports somehow.
         #
         set(HDF5_INCS 
            hdf5.h
            H5api_adpt.h
            H5public.h
            H5pubconf.h
            H5version.h
            H5Apublic.h
            H5ACpublic.h
            H5Cpublic.h
            H5Dpublic.h
            H5Epublic.h
            H5Epubgen.h
            H5Fpublic.h
            H5FDpublic.h
            H5Gpublic.h
            H5Ipublic.h
            H5Lpublic.h
            H5MMpublic.h
            H5Opublic.h
            H5Ppublic.h
            H5PLpublic.h
            H5Rpublic.h
            H5Spublic.h
            H5Tpublic.h
            H5Zpublic.h
            H5FDcore.h
            H5FDdirect.h
            H5FDfamily.h
            H5FDlog.h
            H5FDmpi.h
            H5FDmpio.h
            H5FDmulti.h
            H5FDsec2.h
            H5FDstdio.h
            CACHE STRING "HDF required includes" FORCE)

         if(WIN32)
            #
            # HDF5_INCS cache variable for Windows needs an additional entry.
            #
            set(HDF5_INCS ${HDF5_INCS} H5FDwindows.h CACHE STRING "HDF required includes" FORCE)
         endif()

         mark_as_advanced(FORCE HDF5_INCS)

         #
         # Convert normal HDF5_INCLUDE_DIR variable set by HDF exports file to cache variable.
         # Used in sheaves/component_definitions.cmake:add_library_targets.
         # 
         set(HDF5_INCLUDE_DIR "${HDF5_INCLUDE_DIR}" CACHE PATH "Path to HDF5 include directory" FORCE)
         mark_as_advanced(FORCE HDF5_INCLUDE_DIR)

         #
         # Set HDF5_LIBRARY_DIR cache variable.
         # The path to the library directory is not set by hdf5-config.cmake,
         # have to extract it from the lib target.
         # Don't ACTUALLY need HDF_LIBRARY_DIR any more;
         # all location info is transferred through targets.
         # But its reassuring to see it in the ccmake display.
         #
         get_target_property( __TMP_LOCATION "hdf5-static" LOCATION )
         get_filename_component(__TMP_DIR "${__TMP_LOCATION}" PATH)
         set(HDF5_LIBRARY_DIR "${__TMP_DIR}" CACHE PATH "" FORCE)
         mark_as_advanced(FORCE HDF5_LIBRARY_DIR)

      else()

         # Couldn't find HDF5; remind the client to set the PREREQ variable.

         message("Unable to find prerequisite HDF5; check setting of PREREQ_HDF5_CONFIG_DIR.")
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")
         
      endif(HDF5_FOUND)

   else()

      set(SHEAFSYSTEM_FOUND_HDF5 FALSE CACHE BOOL "True if found hdf5 package" FORCE)

      # Couldn't find HDF5; remind the client to set the PREREQ variable.

      message("Unable to find prerequisite HDF5; check setting of PREREQ_HDF5_CONFIG_DIR.")
      set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")
      
   endif(LVAR_INITIALIZED)
      

   dbc_ensure_defined(SHEAFSYSTEM_FOUND_HDF5)

endfunction(SheafSystem_find_hdf5)

#
# Find the JDK
#
function(SheafSystem_find_jdk)

   # Initialize the PREREQ variable; sets LVAR_INITIALIED

   SheafSystem_init_dir_prereq(JAVA PREREQ_JAVA_HOME
      "Path to top level folder of Java installation" JAVA_HOME)
   
   if(LVAR_INITIALIZED)

      # find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(Java_FOUND CACHE)
      
      find_package(Java 1.7 QUIET)

      set(SHEAFSYSTEM_FOUND_JAVA ${JAVA_FOUND} CACHE BOOL "True if found java package" FORCE)

      if(JAVA_FOUND)

         # Update the PREREQ variable to where java was actually found.
         # FindJava.cmake doesn't define a variable equivalent to JAVA_HOME,
         # have to extract it from the path to the java executable.

         get_filename_component(_bin_dir ${Java_JAVA_EXECUTABLE} DIRECTORY)
         get_filename_component(_home_dir ${_bin_dir} DIRECTORY)

         set(PREREQ_JAVA_HOME ${_home_dir} CACHE
            PATH "Path to top level folder of Java installation" FORCE)
         
      else()
         
         message("Unable to find prerequisite Java; check setting of PREREQ_JAVA_HOME.")
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")
         
      endif(JAVA_FOUND)

      # find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(JNI_FOUND CACHE)
      
      find_package(JNI QUIET)

      set(SHEAFSYSTEM_FOUND_JNI ${JNI_FOUND} CACHE BOOL "True if found jni package" FORCE)

      if(JNI_FOUND)
         
         # FindJNI.cmake called from find_package sets JAVA_AWT_LIBRARY to absolute path to libjawt
         # but does not provide libmawt which we need. Construct it here.

         get_filename_component(JAVA_XAWT_LIB_DIR ${JAVA_AWT_LIBRARY} DIRECTORY)
         set(JAVA_XAWT_LIB_DIR "${JAVA_XAWT_LIB_DIR}/xawt"
            CACHE STRING "Absolute path to directory containing libmawt.so" FORCE)
         mark_as_advanced(FORCE JAVA_XAWT_LIB_DIR)

         set(JAVA_MAWT_LIBRARY "${JAVA_XAWT_LIB_DIR}/libmawt.so"
            CACHE STRING "Absolute path to libmawt.so" FORCE)
         mark_as_advanced(FORCE JAVA_MAWT_LIBRARY)

         # JAVA_JDK_LIBS
         # ISSUE COM-523: this is not the correct collection of JAVA_JDK_LIBS; see file 
         # cmake_modules/java_defintions.cmake.in in snapshot-3-1-0-6

         set(JAVA_JDK_LIBS ${JNI_LIBRARIES} CACHE STRING "Absolute paths to libjawt.so and libjvm.so" FORCE)
         mark_as_advanced(FORCE JAVA_JDK_LIBS)

         # JAVA_JDK_LIB_DIR

         get_filename_component(JAVA_JDK_LIB_DIR ${JAVA_XAWT_LIB_DIR} DIRECTORY)
         set(JAVA_JDK_LIB_DIR "${JAVA_JDK_LIB_DIR}" CACHE STRING "Absolute path to directory containing libjawt.so" FORCE)
         mark_as_advanced(FORCE JAVA_JDK_LIB_DIR)

         # JAVA_JVM_LIB_DIR

         get_filename_component(JAVA_JVM_LIB_DIR ${JAVA_JVM_LIBRARY} DIRECTORY)
         set(JAVA_JVM_LIB_DIR "${JAVA_JVM_LIB_DIR}" CACHE STRING "Absolute path to directory jvm library" FORCE)
         mark_as_advanced(FORCE JAVA_JVM_LIB_DIR)

      else()

         message("Unable to find prerequisite JNI; check setting of PREREQ_JAVA_HOME.")
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

      endif(JNI_FOUND)

   else()

      set(SHEAFSYSTEM_FOUND_JAVA FALSE CACHE BOOL "True if found java package" FORCE)
      
      message("Unable to find prerequisite Java; check setting of PREREQ_JAVA_HOME.")
      set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")
      
   endif(LVAR_INITIALIZED)
   
   # Java and JNI required, so if we get this far we've found them.

   dbc_ensure_defined(SHEAFSYSTEM_FOUND_JAVA)

endfunction(SheafSystem_find_jdk)
   
#
# Find VTK.
#
function(SheafSystem_find_vtk)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   # Initialize the PREREQ variable; sets LVAR_INITIALIZED.

   SheafSystem_init_dir_prereq(VTK PREREQ_VTK_CONFIG_DIR
      "Path to folder containing VTKConfig.cmake" VTK_DIR)

   if(LVAR_INITIALIZED)

      # find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(VTK_FOUND CACHE)

      find_package(VTK 7.0.0 QUIET NO_MODULE HINTS ${PREREQ_VTK_CONFIG_DIR}
         NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH)

      # Find_package sets VTK_DIR whether it finds vtk or not;
      # make sure it is marked as advanced.

      mark_as_advanced(FORCE VTK_DIR)

      set(SHEAFSYSTEM_FOUND_VTK ${VTK_FOUND} CACHE BOOL "True if found vtk package" FORCE)

      if(VTK_FOUND)

         #
         # Update the PREREQ variable to where the config file was actually found.
         #
         set(PREREQ_VTK_CONFIG_DIR "${VTK_DIR}" CACHE PATH "Path to folder containing VTKConfig.cmake" FORCE)


         # VTKConfig.cmake included from find_package provides VTK_LIBRARIES, 
         # convert it to our nomenclature. 
         # $$ISSUE: This adds all the VTK libraries to the link, which is overkill.
         # We need to figure out which of the new, refactored libs we actually need.
         # Compare to the list in the now obsolete vtk_definitions.camke.in

         # VTK_LIBRARIES for some reason inserts "/usr/lib64/libpython2.6.so" into the middle of the list
         # of abbreviated library names, e.g. "vtkCommonCore". This prevents static link, so remove it.

         string(REPLACE ";/usr/lib64/libpython2.6.so;" ";" lshfsys_cleaned_vtk_libs "${VTK_LIBRARIES}")

         set(VTK_LIBS ${lshfsys_cleaned_vtk_libs} CACHE STRING "VTK required libs list" FORCE)

         # VTK uses a different set of configuration names than SheafSystem does.
         # Set up the configuration mapping so all our configurations
         # are mapped to the appropriate VTK configuration.
         # Note that since the VTK install layout can only support one debug
         # and one non-debug configuration, we have to map the Release_ configs
         # to RelWithDebInfo config.

         if(SHEAFSYSTEM_WINDOWS)
            
            set_target_properties(${VTK_LIBS} PROPERTIES
               MAP_IMPORTED_CONFIG_DEBUG_CONTRACTS Debug
               MAP_IMPORTED_CONFIG_DEBUG_NO_CONTRACTS Debug
               MAP_IMPORTED_CONFIG_RELEASE_CONTRACTS Release
               MAP_IMPORTED_CONFIG_RELEASE_NO_CONTRACTS Release
               MAP_IMPORTED_CONFIG_RELWITHDEBINFO_CONTRACTS RelWithDebInfo
               MAP_IMPORTED_CONFIG_RELWITHDEBINFO_NO_CONTRACTS RelWithDebInfo)

         elseif(SHEAFSYSTEM_LINUX)
            
            set_target_properties(${VTK_LIBS} PROPERTIES
               MAP_IMPORTED_CONFIG_DEBUG_CONTRACTS Debug
               MAP_IMPORTED_CONFIG_DEBUG_NO_CONTRACTS Debug
               MAP_IMPORTED_CONFIG_RELEASE_CONTRACTS Release
               MAP_IMPORTED_CONFIG_RELEASE_NO_CONTRACTS Release)

         endif()
      

         # VTK_LIB_DIR needed by set_env_vars.*.cmake.in.
         # VTK_INSTALL_PREFIX set by VTKConfig.cmake.

         set(VTK_LIB_DIR ${VTK_INSTALL_PREFIX}/lib CACHE STRING "VTK libraries directory." FORCE)

         # VTKConfig.cmake provides VTK_INCLUDE_DIRS, but make sure it is cached.

         set(VTK_INCLUDE_DIRS ${VTK_INCLUDE_DIRS} CACHE STRING "VTK include paths" FORCE)

         # VTKConfig.cmake does not provide an imported target for the vtk.jar file;
         # we have to use dead reckoning derived from inspecting the VTK cmake scripts that install vtk.jar.

         set(VTK_JAR ${VTK_INSTALL_PREFIX}/lib/vtk.jar CACHE STRING "VTK jar file." FORCE)

         # Mark all the vtk vars as advanced to keep the UI from getting cluttered.

         mark_as_advanced(FORCE VTK_DIR)
         mark_as_advanced(FORCE VTK_INCLUDE_DIRS)
         mark_as_advanced(FORCE VTK_JAR)
         mark_as_advanced(FORCE VTK_LIBS)
         mark_as_advanced(FORCE VTK_LIB_DIR)

      else()

         # Couldn't find VTK; remind the client to set the PREREQ variable.

         message("Unable to find prerequisite VTK; check setting of PREREQ_VTK_CONFIG_DIR.")
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

      endif(VTK_FOUND)

   else()

      set(SHEAFSYSTEM_FOUND_VTK FALSE CACHE BOOL "True if found vtk package" FORCE)

      # Couldn't find VTK; remind the client to set the PREREQ variable.

      message("Unable to find prerequisite VTK; check setting of PREREQ_VTK_CONFIG_DIR.")
      set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")
      
   endif(LVAR_INITIALIZED)
   
   #   dbc_ensure(SHEAFSYSTEM_FOUND_VTK)

endfunction(SheafSystem_find_vtk)
   
#
# Find Swig
#
function(SheafSystem_find_swig)

   # Initialize the PREREQ variable; sets LVAR_INITIALIZED.

   SheafSystem_init_exe_prereq(SWIG PREREQ_SWIG_EXECUTABLE "Path to swig executable." SWIG_EXECUTABLE)

   if(LVAR_INITIALIZED)

      # find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(SWIG_FOUND CACHE)

      find_package(SWIG QUIET)

      # find_package uses FindSwig in the CMake installation.
      # Sets the following variables:
      
      # SWIG_FOUND - (non-cache) set to true if SWIG is found
      # SWIG_DIR - (cache) the directory where swig is installed
      # SWIG_EXECUTABLE - (cache) the path to the swig executable
      # SWIG_VERSION   - (cache) the version number of the swig executable

      set(SHEAFSYSTEM_FOUND_SWIG ${SWIG_FOUND} CACHE BOOL "True if found swig package" FORCE)

      if(SWIG_FOUND)

         # Update the PREREQ variable to where the executable  was actually found.

         set(PREREQ_SWIG_EXECUTABLE ${SWIG_EXECUTABLE} CACHE FILEPATH "Path to swig executable." FORCE)

         include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseSWIG.cmake)
         #   include(UseSWIG)

         # Mark all the swig vars as advanced to keep the UI from getting cluttered.

         mark_as_advanced(FORCE SWIG_DIR)
         mark_as_advanced(FORCE SWIG_EXECUTABLE)
         mark_as_advanced(FORCE SWIG_VERSION)

      else()

         # Couldn't find swig; remind the client to set the PREREQ variable.

         message("Unable to find prerequisite swig; check setting of PREREQ_SWIG_EXECUTABLE.")
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

      endif(SWIG_FOUND)

   else()
      
      # Couldn't find swig; remind the client to set the PREREQ variable.

      message("Unable to find prerequisite swig; check setting of PREREQ_SWIG_EXECUTABLE.")
      set(SHEAFSYSTEM_FOUND_SWIG FALSE CACHE BOOL "True if found swig package" FORCE)
      set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

   endif(LVAR_INITIALIZED)

endfunction(SheafSystem_find_swig)

#
# Find C#
#
function(SheafSystem_find_csharp)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)
   
   if(SHEAFSYSTEM_WINDOWS)

      # FindCSharp.cmake on Windows has no search control, it knows where Windows puts the .NET Framework.
      # So don't initialize any PREREQ variable.
      
      # Add the SheafSystem module directory to the find_package search path
      # so we can use our own FindCSharp.cmake.
      
      set(CMAKE_MODULE_PATH ${SHEAFSYSTEM_CMAKE_MODULE_PATH})

      # find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(CSharp_FOUND CACHE)

      find_package(CSharp QUIET)

      # CMAKE_MODULE_PATH is undefined by default, put it back that way.

      unset(CMAKE_MODULE_PATH)

      set(SHEAFSYSTEM_FOUND_CSHARP ${CSHARP_FOUND} CACHE BOOL "True if found csharp package" FORCE)

      if(CSHARP_FOUND)

         # $$ISSUE: it would appear we don't use anythinhg from this module.

         include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseCSharp.cmake)

         # CSharp module defines several cache variables;
         # make then advanced so we don't clutter up the UI.

         mark_as_advanced(FORCE CSHARP_COMPILER)
         mark_as_advanced(FORCE CSHARP_PLATFORM)
         mark_as_advanced(FORCE CSHARP_TYPE)
         mark_as_advanced(FORCE CSHARP_VERSION)
         mark_as_advanced(FORCE CSHARP_FOUND)
         mark_as_advanced(FORCE MCS_EXECUTABLE)

      endif()

   elseif(SHEAFSYSTEM_LINUX)

      # Initialize the PREREQ variable; sets LVAR_INITIALIZED.
      # On Linux, FindCSharp.cmake looks for the Mono compiler mcs using find_program.

      SheafSystem_init_exe_prereq(CSHARP PREREQ_MCS_EXECUTABLE "Path to mcs executable." MCS_EXECUTABLE)

      if(LVAR_INITIALIZED)
         
         # Add the SheafSystem module directory to the find_package search path
         # so we can use our own FindCSharp.cmake.
         
         set(CMAKE_MODULE_PATH ${SHEAFSYSTEM_CMAKE_MODULE_PATH})

         # find_package won't search if _FOUND is set from some previous call, even if it is false.
         
         unset(CSharp_FOUND CACHE)

         find_package(CSharp QUIET)

         # CMAKE_MODULE_PATH is undefined by default, put it back that way.

         unset(CMAKE_MODULE_PATH)

         set(SHEAFSYSTEM_FOUND_CSHARP ${CSHARP_FOUND} CACHE BOOL "True if found csharp package" FORCE)

         if(CSHARP_FOUND)

            # Update PREREQ variable to where the executable was actually found.

            set(PREREQ_MCS_EXECUTABLE ${MCS_EXECUTABLE} CACHE FILEPATH "Path to mcs executable." FORCE)

            # $$ISSUE: it would appear we don't use anythinhg from this module.

            include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseCSharp.cmake)

            # CSharp module defines several cache variables;
            # make then advanced so we don't clutter up the UI.

            mark_as_advanced(FORCE CSHARP_COMPILER)
            mark_as_advanced(FORCE CSHARP_PLATFORM)
            mark_as_advanced(FORCE CSHARP_TYPE)
            mark_as_advanced(FORCE CSHARP_VERSION)
            mark_as_advanced(FORCE CSHARP_FOUND)
            mark_as_advanced(FORCE MCS_EXECUTABLE)

         else()

            message("Unable to find prerequisite CSharp/Mono; check setting of PREREQ_MCS_EXECUTABLE.")
            set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

         endif()
         
      else()
         
         message("Unable to find prerequisite CSharp/Mono; check setting of PREREQ_MCS_EXECUTABLE.")
         set(SHEAFSYSTEM_FOUND_CSHARP FALSE CACHE BOOL "True if found csharp package" FORCE)
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

      endif(LVAR_INITIALIZED)

   endif()

endfunction(SheafSystem_find_csharp)

#
# Find Python
#
function(SheafSystem_find_python)

   # Initialize the PREREQ variables; sets LVAR_INITIALIZED.
   # We don't really need the python interpreter,
   # but finding it first makes it simpler for the user to specify the location.

   SheafSystem_init_exe_prereq(PYTHON PREREQ_PYTHON_EXECUTABLE
      "Path to python interpreter executable." PYTHON_EXECUTABLE)
   
   if(LVAR_INITIALIZED)

      # find_package won't search if _FOUND is set from some previous call, even if it is false.
      
      unset(PythonInterp_FOUND CACHE)

      find_package(PythonInterp QUIET)

      # FindPythnInterp .cmake sets the following cache variables.
      #   PYTHONINTERP_FOUND         - Was the Python executable found
      #   PYTHON_EXECUTABLE          - path to the Python interpreter
      #
      #   PYTHON_VERSION_STRING      - Python version found e.g. 2.5.2
      #   PYTHON_VERSION_MAJOR       - Python major version found e.g. 2
      #   PYTHON_VERSION_MINOR       - Python minor version found e.g. 5
      #   PYTHON_VERSION_PATCH       - Python patch version found e.g. 2
      
      set(SHEAFSYSTEM_FOUND_PYTHONINTERP ${PYTHONINTERP_FOUND} CACHE BOOL "True if found pythonlibs package" FORCE)

      if(PYTHONINTERP_FOUND)

         # Update PREREQ variable to where the executable was actually found.

         set(PREREQ_PYTHON_EXECUTABLE ${PYTHON_EXECUTABLE} CACHE FILEPATH "Path to python interpeter executable." FORCE)

         # find_package won't search if _FOUND is set from some previous call, even if it is false.
         
         unset(PythonLibs_FOUND CACHE)
         
         find_package(PythonLibs QUIET)

         # FindPythonLibs called from ginf_package sets the following variables:
         #  PYTHONLIBS_FOUND           - have the Python libs been found
         #  PYTHON_LIBRARIES           - path to the python library
         #  PYTHON_INCLUDE_PATH        - path to where Python.h is found (deprecated)
         #  PYTHON_INCLUDE_DIRS        - path to where Python.h is found
         #  PYTHON_DEBUG_LIBRARIES     - path to the debug library (deprecated)
         #  PYTHONLIBS_VERSION_STRING  - version of the Python libs found (since CMake 2.8.8)

         set(SHEAFSYSTEM_FOUND_PYTHONLIBS ${PYTHONLIBS_FOUND} CACHE BOOL "True if found pythonlibs package" FORCE)

         if(PYTHONLIBS_FOUND)

            set(SHEAFSYSTEM_PYTHON_LIBRARIES ${PYTHON_LIBRARIES} CACHE PATH "Path to the python library" FORCE)
            mark_as_advanced(FORCE SHEAFSYSTEM_PYTHON_LIBRARIES)

            set(SHEAFSYSTEM_PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS} CACHE PATH "Path to where Python.h is found" FORCE)   
            mark_as_advanced(FORCE SHEAFSYSTEM_PYTHON_INCLUDE_DIRS)

         else()

            message("Unable to find prerequisite python LIBS; check setting of PREREQ_PYTHON_EXECUTABLE.")
            set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

         endif(PYTHONLIBS_FOUND)

      else()

         message("Unable to find prerequisite python interpreter; check setting of PREREQ_PYTHON_EXECUTABLE.")
         set(SHEAFSYSTEM_FOUND_PYTHONLIBS FALSE CACHE BOOL "True if found pythonlibs package" FORCE)
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

      endif(PYTHONINTERP_FOUND)

   else()

      message("Unable to find prerequisite python interpreter; check setting of PREREQ_PYTHON_EXECUTABLE.")
      set(SHEAFSYSTEM_FOUND_PYTHONINTERP FALSE CACHE BOOL "True if found pythonlibs package" FORCE)
      set(SHEAFSYSTEM_FOUND_PYTHONLIBS FALSE CACHE BOOL "True if found pythonlibs package" FORCE)
      set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")      

   endif(LVAR_INITIALIZED)

   dbc_ensure_defined(SHEAFSYSTEM_FOUND_PYTHONINTERP)
   dbc_ensure_defined(SHEAFSYSTEM_FOUND_PYTHONLIBS)

endfunction(SheafSystem_find_python)

#  
# Find the JMF
#
function(SheafSystem_find_jmf)

   # Initialize the PREREQ variable; sets LVAR_INITIALIZED.
   
   SheafSystem_init_exe_prereq(JMF PREREQ_JMF_EXECUTABLE "Path to jmfinit executable" JMF_JMFINIT_EXECUTABLE)

   if(LVAR_INITIALIZED)
      
      # Add the SheafSystem module directory to the find_package search path
      # so we can use our own FindJMF.cmake.
      
      set(CMAKE_MODULE_PATH ${SHEAFSYSTEM_CMAKE_MODULE_PATH})

      find_program(JMF_JMFINIT_EXECUTABLE jmfinit)

      # find_program sets JMF_JMFINIT_EXECUTABLE whether it finds it or not;
      # make sure it is marked advanced.

      mark_as_advanced(FORCE JMF_JMFINIT_EXECUTABLE)

      # CMAKE_MODULE_PATH is undefined by default, put it back that way.

      unset(CMAKE_MODULE_PATH)

      if(JMF_JMFINIT_EXECUTABLE)

         set(SHEAFSYSTEM_FOUND_JMF TRUE CACHE BOOL "True if found jmf package" FORCE)

         get_filename_component(JMF_BIN_DIR ${JMF_JMFINIT_EXECUTABLE} PATH)
         set(JMF_BIN_DIR ${JMF_BIN_DIR} CACHE STRING "Bin directory for JMF." FORCE)
         mark_as_advanced(FORCE JMF_BIN_DIR)

         get_filename_component(JMF_DIR ${JMF_BIN_DIR} PATH)
         find_path(JMF_LIB_DIR jmf.jar PATHS ${JMF_DIR}/lib)
         set(JMF_LIB_DIR ${JMF_LIB_DIR} CACHE STRING "Link directory for JMF." FORCE)
         mark_as_advanced(FORCE JMF_LIB_DIR)

         set(JMF_JAR ${JMF_LIB_DIR}/jmf.jar CACHE STRING "Jar file for JMF." FORCE)
         mark_as_advanced(FORCE JMF_JAR)

         # Update the PREREQ variable to where JMF was actually found.

         set(PREREQ_JMF_EXECUTABLE ${JMF_JMFINIT_EXECUTABLE} CACHE PATH "Path to jmfinit executable" FORCE)

      else()

         set(SHEAFSYSTEM_FOUND_JMF FALSE CACHE BOOL "True if found jmf package" FORCE)
         
         message("Unable to find prerequisite JMF; check setting of PREREQ_JMF_EXECUTABLE.")
         set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

      endif(JMF_JMFINIT_EXECUTABLE)

   else()
      
      message("Unable to find prerequisite JMF; check setting of PREREQ_JMF_HOME.")
      set(SHEAFSYSTEM_FOUND_JMF FALSE CACHE BOOL "True if found jmf package" FORCE)
      set(SHEAFSYSTEM_PREREQS_FOUND FALSE CACHE INTERNAL "")

   endif(LVAR_INITIALIZED)
   
   dbc_ensure_defined(SHEAFSYSTEM_FOUND_JMF)

endfunction(SheafSystem_find_jmf)

#
# Find all the prerequisites for the SheafSystem.
#
function(SheafSystem_find_prerequisites)

   # Logic below depends on SHEAFSYSTEM_BUILD_BINDINGS being on if SHEAFSYSTEM_BUILD_SHEAFSCOPE is.

   dbc_require_implies(SHEAFSYSTEM_BUILD_SHEAFSCOPE SHEAFSYSTEM_BUILD_BINDINGS)

   # Make sure all the found variables are defined and FALSE.

   set(SHEAFSYSTEM_FOUND_DOXYGEN FALSE CACHE BOOL "True if found doxygen package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_DOXYGEN)

   set(SHEAFSYSTEM_FOUND_GRAPHVIZ FALSE CACHE BOOL "True if found graphviz package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_GRAPHVIZ)

   set(SHEAFSYSTEM_FOUND_HDF5 FALSE CACHE BOOL "True if found hdf5 package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_HDF5)
   
   set(SHEAFSYSTEM_FOUND_JAVA FALSE CACHE BOOL "True if found java package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_JAVA)

   set(SHEAFSYSTEM_FOUND_JNI FALSE CACHE BOOL "True if found jni package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_JNI)

   set(SHEAFSYSTEM_FOUND_VTK FALSE CACHE BOOL "True if found vtk package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_VTK)

   set(SHEAFSYSTEM_FOUND_SWIG FALSE CACHE BOOL "True if found swig package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_SWIG)

   set(SHEAFSYSTEM_FOUND_CSHARP FALSE CACHE BOOL "True if found csharp package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_CSHARP)

   set(SHEAFSYSTEM_FOUND_PYTHONINTERP FALSE CACHE BOOL "True if found pythoninterp package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_PYTHONINTERP)

   set(SHEAFSYSTEM_FOUND_PYTHONLIBS FALSE CACHE BOOL "True if found pythonlibs package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_PYTHONLIBS)

   set(SHEAFSYSTEM_FOUND_JMF FALSE CACHE BOOL "True if found jmf package" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_FOUND_JMF)

   # Assume success.

   set(SHEAFSYSTEM_PREREQS_FOUND TRUE CACHE INTERNAL "")

   # Find Graphviz dot

   SheafSystem_find_dot()

   # Find Doxygen

   SheafSystem_find_doxygen()

   # Find HDF5

   SheafSystem_find_hdf5()

   if(SHEAFSYSTEM_BUILD_BINDINGS)

      # Find the JDK

      SheafSystem_find_jdk()

      # Find VTK

      SheafSystem_find_vtk()

      # Find Swig.

      SheafSystem_find_swig()

      # Find Csharp

      SheafSystem_find_csharp()

      # Find python

      SheafSystem_find_python()

      # Find Java media framework.

      SheafSystem_find_jmf()

   else()

      # Make sure the bindings PREREQ variables are unset,
      # so they don't appear in the user interface.

      unset(PREREQ_JAVA_HOME CACHE)
      unset(PREREQ_VTK_CONFIG_DIR CACHE)
      unset(PREREQ_SWIG_EXECUTABLE CACHE)
      unset(PREREQ_MONO_EXECUTABLE CACHE)
      unset(PREREQ_MCS_EXECUTABLE CACHE)
      unset(PREREQ_PYTHON_EXECUTABLE CACHE)
      unset(PREREQ_JMF_EXECUTABLE CACHE)

   endif(SHEAFSYSTEM_BUILD_BINDINGS)

   if(NOT SHEAFSYSTEM_PREREQS_FOUND)
      message(FATAL_ERROR "Unable to find some prereqs. Please review PREREQ variable settings")
   endif()

   # If we get here, we've successfully set the prereq varibles.
   # Configure the set_prereq_vars scripts.

   if(SHEAFSYSTEM_WINDOWS)
      configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/set_prereq_vars.bat.cmake.in
         ${CMAKE_BINARY_DIR}/set_prereq_vars.bat)      
   elseif(SHEAFSYSTEM_LINUX)
      configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/set_prereq_vars.csh.cmake.in
         ${CMAKE_BINARY_DIR}/set_prereq_vars.csh)
      configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/set_prereq_vars.sh.cmake.in
         ${CMAKE_BINARY_DIR}/set_prereq_vars.sh)
   endif()   

   dbc_ensure(SHEAFSYSTEM_FOUND_HDF5)
   dbc_ensure_implies(SHEAFSYSTEM_BUILD_BINDINGS SHEAFSYSTEM_FOUND_JAVA)
   dbc_ensure_implies(SHEAFSYSTEM_BUILD_BINDINGS SHEAFSYSTEM_FOUND_JNI)
   dbc_ensure_implies(SHEAFSYSTEM_BUILD_BINDINGS SHEAFSYSTEM_FOUND_VTK)
   dbc_ensure_implies(SHEAFSYSTEM_BUILD_BINDINGS SHEAFSYSTEM_FOUND_SWIG)
   dbc_ensure_implies(SHEAFSYSTEM_BUILD_BINDINGS SHEAFSYSTEM_FOUND_PYTHONLIBS)
   dbc_ensure_implies(SHEAFSYSTEM_BUILD_BINDINGS SHEAFSYSTEM_FOUND_JMF)

endfunction(SheafSystem_find_prerequisites)
