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
# Generate the installed exports file. Replace hardcoded vars with cmake substitution vars.
#
    
# Glob all the cmake files in CWD. Replace the value of CMAKE_INSTALL_PREFIX with @SHEAFSYSTEM_HOME@
file(GLOB CONFIG_FILES "${CMAKE_INSTALL_PREFIX}/cmake//SheafSystem*.cmake")
foreach(file ${CONFIG_FILES})
    # Read the file. Store contents in ${file}_contents}
    file(READ ${file} ${file}_contents)
   #Replace the value of CMAKE_INSTALL_PREFIX with @SHEAFSYSTEM_HOME@
    string(REPLACE "${CMAKE_INSTALL_PREFIX}" "\@SHEAFSYSTEM_HOME\@" ${file}_tmp1 "${${file}_contents}")
     #Replace BUILD_TYPE with the VS macro OutDir. 
    if(WIN32) 
        string(REPLACE "BUILD_TYPE" "OutDir" ${file}_pass2 "${${file}_tmp1}")
    else() # Linux
        string(REPLACE "BUILD_TYPE" "CMAKE_BUILD_TYPE" ${file}_tmp2 "${${file}_tmp1}")
    endif()
    # Write the result out to a ".in"     
    file(WRITE ${file}.in "${${file}_tmp2}")
    #Throw away the original cmake file     
    file(REMOVE ${file})
endforeach()