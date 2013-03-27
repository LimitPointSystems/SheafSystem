//
// $RCSfile: std_iostream_py.i,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:33 $
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
