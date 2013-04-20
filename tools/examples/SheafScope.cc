

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/SheafScope.cc

#include "jvm_launcher.h"
#include "lps_environment.h" // for CLASSPATH & LD_LIBRARY_PATH

int main(int argc, char* argv[])
{
#ifdef __WIN32
	  return jvm_launcher::launch("SheafScope", argc, argv,
	                              CLASSPATH, PATH);
#else
  return jvm_launcher::launch("SheafScope", argc, argv,
                              CLASSPATH, LD_LIBRARY_PATH);
#endif
}
