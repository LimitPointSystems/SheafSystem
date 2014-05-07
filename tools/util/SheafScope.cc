
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

/// @example examples/SheafScope.cc

#include "jvm_launcher.h"
#include "lps_environment.h" // for CLASSPATH & LD_LIBRARY_PATH

int main(int argc, char* argv[])
{
#ifdef __WIN32
	  return jvm_launcher::launch("SheafScope", argc, argv,
	                              CLASSPATH, PATH);
//#else
//  return jvm_launcher::launch("SheafScope", argc, argv,
//                              CLASSPATH, LD_LIBRARY_PATH);
#endif
}
