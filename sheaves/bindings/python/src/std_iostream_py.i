//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Swig interface for std::iostream (python version)
//

%{
#include "std_iostream.h"
%}

%inline %{
ostream* get_cout()
{
   return &cout;
}
%}
