
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
#include "std_sstream.h"
#include "std_string.h"

#ifdef _WIN32
#include "windows.h" // Compiling with MS C++, needed for OutputDebugString.
#endif

using namespace sheaf;  // Workaround for MSVC++ bug

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

#ifdef _WIN32

	// Compiling for MS C++;
	// Dump message to the output window.

	stringstream ldebug_msg;
	ldebug_msg << lmsg.str() << endl;
	
    OutputDebugString(ldebug_msg.str().c_str());
#endif

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

#ifdef _WIN32

	// Compiling for MS C++;
	// Dump message to the output window.

	stringstream ldebug_msg;
	ldebug_msg << lmsg.str() << endl;
	
    OutputDebugString(ldebug_msg.str().c_str());
#endif

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

#ifdef _WIN32

	// Compiling for MS C++;
	// Dump message to the output window.

	stringstream ldebug_msg;
	ldebug_msg << lmsg.str() << endl;
	
    OutputDebugString(ldebug_msg.str().c_str());
#endif

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

#ifdef _WIN32

	// Compiling for MS C++;
	// Dump message to the output window.

	stringstream ldebug_msg;
	ldebug_msg << lmsg.str() << endl;
	
    OutputDebugString(ldebug_msg.str().c_str());
#endif

  throw std::logic_error(lmsg.str());
};    
