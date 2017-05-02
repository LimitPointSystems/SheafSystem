
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

/// @example examples/sheaves_read.cc

#include "SheafSystem/assert_contract.h"

#ifdef _WIN32
#include "SheafSystem/io.h"
#endif

#include "SheafSystem/std_iostream.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/storage_agent.h"



using namespace sheaf;

string filename;

int
main(int argc, char** argv)
{

  if (argc > 1)
  {
    // test for existence of file
    // if the filename is not valid, then exit 0 with warning message.
  
    if (access(argv[1],0) == 0)
    {
      filename = argv[1];
    }
    else
    {
      cout << "warning: no such filename " << argv[1] << "\n";
      exit(0);
    }
  }
  else
  {
    cerr << "usage: sheaves_read sheaf_file [enable_error_report]\n";
    exit(0);
  }

  bool lenable_error_report = (argc > 2);

  /// @hack prototype instantiation bug.

  namespace_poset::initialize_prototypes();

  // Make the default namespace

  namespace_poset ns("test");

  // Read the namespace from the file;
  // need write access in order to read it.

  ns.get_read_write_access();
  storage_agent sa(filename, sheaf_file::READ_ONLY, false, lenable_error_report);
  sa.put_member_record_buffer_ub(15);

  sa.read_entire(ns);

  // Output a text version to stdout

  cout << ns << endl;

  return 0;
}
