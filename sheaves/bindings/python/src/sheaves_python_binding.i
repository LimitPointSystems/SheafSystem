
//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// SWIG module interface to sheaves cluster (python version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module sheaves_python_binding

//=============================================================================

// Python string handling.

%include "std_string_py.i"
%array_class(string, stringArray);

%pointer_class(string, stringPtr);

//=============================================================================

//$$HACK: "print" is a python keyword. We rename it to "Print".

%rename(Print) print;

//=============================================================================

%include "sheaves_common_binding.i"
