

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
 
//

/// @file
/// Interface for class sheaf_dll_spec

#ifndef SHEAF_DLL_SPEC_H
#define SHEAF_DLL_SPEC_H

#ifdef _WIN32

// Compiling for MS C++;
// set decspec for dlls.

#if defined SHEAF_DLL_EXPORTS

// Compiling library itself,
// set declspec to export.

#define SHEAF_DLL_SPEC __declspec(dllexport)

#elif defined SHEAF_DLL_IMPORTS

// Compiling clients of library,
// set declspec to import.

#define SHEAF_DLL_SPEC __declspec(dllimport)

#else

// Not compiling for dll
// make declspec disappear.

#define SHEAF_DLL_SPEC

#endif // ifdef SHEAF_EXPORTS

#else

// Not compiling for MS C++;
// make declspec disappear.

#define SHEAF_DLL_SPEC

#endif // ifdef _WIN32

#endif // ifndef SHEAF_DLL_SPEC_H
