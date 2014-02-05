
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

/// @file
/// Implementation for class assert_contract

#include "assert_contract.h"
#include "std_stdexcept.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "std_string.h"

#ifdef _WIN32
#include "windows.h" // Compiling with MS C++, needed for OutputDebugString.
#endif

using namespace std;
using namespace sheaf;  // Workaround for MSVC++ bug

namespace
{

//
// Output message xmsg of type xmsg_type to the VisualStudio Output Window.
// Only implemented if _WIN32 is defined.
//
void
print_output_message(const string& xmsg_type, const string& xmsg)
{
#ifdef _WIN32
  
  // Output Header.
  
  int ltype_len = xmsg_type.length();
  int lmsg_len = xmsg.length();
  int lline_len = lmsg_len - ltype_len - 4;

  OutputDebugString("\n== ");
  OutputDebugString(xmsg_type.c_str());
  OutputDebugString(" ");
  for(int i=0; i < lline_len; i++)
  {
    OutputDebugString("=");
  }

  // Output Message.
  
  OutputDebugString("\n\n");
  OutputDebugString(xmsg.c_str());
  OutputDebugString("\n\n");
  
  // Output Footer
  
  for(int i=0; i < lmsg_len; i++)
  {
    OutputDebugString("=");
  }
  
  OutputDebugString("\n\n");

  // Output message to standard error so it appears in the
  // Command Consile.

  std::cerr << xmsg << std::endl;
#endif
};

} // end unnamed namespace.

// ===========================================================
// ASSERT_CONTRACT FACET
// ===========================================================

void 
sheaf::
check_contract(bool xcond, const char* xmsg, const char* xfile, int xline)
{
  if(!xcond)
  {
    string lfilepath(xfile);
    string::size_type lidx = lfilepath.find_last_of("/\\");
    string lfilename = (lidx != string::npos) ? lfilepath.substr(lidx+1) : lfilepath;
    
    stringstream lmsg;
    lmsg << "'" << xmsg << "'" << " in file " << lfilename << " at line " << xline;

	print_output_message("CONTRACT VIOLATION", lmsg.str());
    throw std::logic_error(lmsg.str());
  }
};  

void 
sheaf::
check_contract(bool xcond, const char* xcond_msg, int xi, const char* xi_msg, const char* xfile, int xline)
{
  if(!xcond)
  {
    string lfilepath(xfile);
    string::size_type lidx = lfilepath.find_last_of("/\\");
    string lfilename = (lidx != string::npos) ? lfilepath.substr(lidx+1) : lfilepath;
    
    stringstream lmsg;
    lmsg << "'" << xcond_msg << "'" 
	 << " failed at " << xi_msg << " = " << xi
	 << " in file " << lfilename << " at line " << xline;

	print_output_message("CONTRACT VIOLATION", lmsg.str());
    throw std::logic_error(lmsg.str());
  }
};  
 

void 
sheaf::
post_there_exists_failed(const char* xcond_msg, int xi, const char* xi_msg, int xmin, int xub, const char* xfile, int xline)
{
  string lfilepath(xfile);
  string::size_type lidx = lfilepath.find_last_of("/\\");
  string lfilename = (lidx != string::npos) ? lfilepath.substr(lidx+1) : lfilepath;
    
  stringstream lmsg;
  lmsg << "'" << xcond_msg << "'" 
       << " not true for any " << xi_msg << " in [" << xmin << ", " << xub << ")"
       << " in file " << lfilename << " at line " << xline;

  print_output_message("CONTRACT VIOLATION", lmsg.str());
  throw std::logic_error(lmsg.str());
};  

void 
sheaf::
post_unimplemented(const char* xcond_msg, const char* xfile, int xline)
{
  string lfilepath(xfile);
  string::size_type lidx = lfilepath.find_last_of("/\\");
  string lfilename = (lidx != string::npos) ? lfilepath.substr(lidx+1) : lfilepath;
    
  stringstream lmsg;
  lmsg << "Function in file " << lfilename << " at line " << xline << " " << xcond_msg;

  print_output_message("UNIMPLEMENTED", lmsg.str());
  throw std::logic_error(lmsg.str());
};    
