

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
