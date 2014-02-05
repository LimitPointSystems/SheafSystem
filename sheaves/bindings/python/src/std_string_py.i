
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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

