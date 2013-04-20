//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Swig typemaps for std::string (python version)
//

// ------------------------------------------------------------------------
// std::string is typemapped by value
// This can prevent exporting methods which return a string
// in order for the user to modify it.
// However, I think I'll wait until someone asks for it...
// ------------------------------------------------------------------------

%include exception.i

%{
#include "std_string.h"
%}

namespace std {

    class string;

    // Overloading check

    %typemap(typecheck) string = char *;
    %typemap(typecheck) string * = char *;
    %typemap(typecheck) const string & = char *;

    %typemap(in) string {
        if (PyString_Check($input))
            $1 = string(PyString_AsString($input));
        else
            SWIG_exception(SWIG_TypeError, "string expected");
    }

    %typemap(in) const string & (string temp) {
        if (PyString_Check($input)) {
            temp = string(PyString_AsString($input));
            $1 = &temp;
        } else {
            SWIG_exception(SWIG_TypeError, "string expected");
        }
    }

    %typemap(out) string {
        $result = PyString_FromString($1.c_str());
    }

    %typemap(out) const string & {
        $result = PyString_FromString($1->c_str());
    }

    %typemap(out) string & {
        $result = PyString_FromString($1->c_str());
    }
}

