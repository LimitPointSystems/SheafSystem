// $RCSfile: assert_contract.cc,v $ $Revision: 1.3 $ $Date: 2012/07/04 16:42:27 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class assert_contract

#include "assert_contract.h"
#include "std_stdexcept.h"
#include "std_sstream.h"
#include "std_string.h"

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
  throw std::logic_error(lmsg.str());
};    
