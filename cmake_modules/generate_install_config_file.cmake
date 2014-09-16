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
# Generate the installed <project>-exports file. Replace hardcoded vars with cmake substitution vars.
#
#file(READ ${CMAKE_INSTALL_PREFIX}/cmake/SheafSystem.cmake INSTALL_FILE_CONTENTS)

#string(REPLACE "${CMAKE_INSTALL_PREFIX}" "\@SHEAFSYSTEM_HOME\@" 
#    MASSAGED_OUTPUT "${INSTALL_FILE_CONTENTS}")

#file(WRITE ${CMAKE_INSTALL_PREFIX}/cmake/SheafSystem.cmake.in "${MASSAGED_OUTPUT}")
#file(APPEND ${CMAKE_INSTALL_PREFIX}/cmake/SheafSystem.cmake.in "\n")
    
# glob all the cmake files. Replace the value of CMAKE_INSTALL_PREFIX with @SHEAFSYSTEM_HOME@
file(GLOB CONFIG_FILES "${CMAKE_INSTALL_PREFIX}/cmake//SheafSystem*.cmake")
foreach(file ${CONFIG_FILES})
    file(READ ${file} ${file}_contents)
    string(REPLACE ${CMAKE_INSTALL_PREFIX} "\@SHEAFSYSTEM_HOME\@" ${file}_pass1 "${${file}_contents}")
#        file(WRITE ${file} "${${file}_OUTPUT}")
#    file(READ ${file} ${file}_contents)         
    string(REPLACE "BUILD_TYPE" "OutDir" ${file}_pass2 "${${file}_pass1}")     
    file(WRITE ${file}.in "${${file}_pass2}")     
    file(REMOVE ${file})
endforeach()