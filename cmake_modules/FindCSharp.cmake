#
# Copyright (c) 2013 Limit Point Systems, Inc. 
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
# A CMake Module for finding and using C# (.NET and Mono).
#
# The following variables are set:
#   CSHARP_FOUND - set to ON if C# is found
#   CSHARP_USE_FILE - the path to the C# use file
#   CSHARP_TYPE - the type of the C# compiler (eg. ".NET" or "Mono")
#   CSHARP_VERSION - the version of the C# compiler (eg. "v4.0" or "2.10.2")
#   CSHARP_COMPILER - the path to the C# compiler executable (eg. "C:/Windows/Microsoft.NET/Framework/v4.0.30319/csc.exe" or "/usr/bin/gmcs")
#   CSHARP_INTERPRETER - the path to interpreter needed to run CSharp executables
#
# This file is based on the work of GDCM:
# http://gdcm.svn.sf.net/viewvc/gdcm/trunk/CMake/FindCSharp.cmake
# Copyright (c) 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#

# TODO: ADD ABILITY TO SELECT WHICH C# COMPILER eg. .NET or Mono (if both exist). For the moment, .NET is selected above Mono.

# Make sure find package macros are included
include( FindPackageHandleStandardArgs )

unset( CSHARP_COMPILER CACHE )
unset( CSHARP_INTERPRETER CACHE )
unset( CSHARP_TYPE CACHE )
unset( CSHARP_VERSION CACHE )
unset( CSHARP_FOUND CACHE )

# By default use anycpu platform, allow the user to override
set( CSHARP_PLATFORM "anycpu" CACHE STRING "C# target platform: x86, x64, anycpu, or itanium" )
if( NOT ${CSHARP_PLATFORM} MATCHES "x86|x64|anycpu|itanium" )
  message( FATAL_ERROR "The C# target platform '${CSHARP_PLATFORM}' is not valid. Please enter one of the following: x86, x64, anycpu, or itanium" )
endif( )
if( WIN32 )
  find_package( DotNetFrameworkSdk )
  if( NOT CSHARP_DOTNET_FOUND )
    find_package( Mono )
  endif( )
else( UNIX )
  #find_package( Mono )
  FIND_PROGRAM(MONO_COMPILER mcs)
   if(MONO_COMPILER)
       set(CSHARP_MONO_FOUND TRUE)
   endif()
endif( )

if( CSHARP_DOTNET_FOUND )
  set( CSHARP_TYPE ".NET" CACHE STRING "Using the .NET compiler" )
  set( CSHARP_VERSION ${CSHARP_DOTNET_VERSION} CACHE STRING "C# .NET compiler version" FORCE )
  set( CSHARP_COMPILER ${CSHARP_DOTNET_COMPILER_${CSHARP_DOTNET_VERSION}} CACHE STRING "Full path to .NET compiler" FORCE )
  set( CSHARP_INTERPRETER "" CACHE INTERNAL "" FORCE )
elseif( CSHARP_MONO_FOUND )
  set( CSHARP_TYPE "Mono" CACHE STRING "Using the Mono compiler" )
  set( CSHARP_COMPILER ${MONO_COMPILER} CACHE STRING "Full path to Mono compiler" FORCE )
endif( )

# Handle WIN32 specific issues
if ( WIN32 )
  if ( CSHARP_COMPILER MATCHES "bat" )
    set( CSHARP_COMPILER "call ${CSHARP_COMPILER}" )
  endif ( )
endif( )
