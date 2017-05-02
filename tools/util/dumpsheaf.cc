
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


#include "SheafSystem/base_space_poset.h"

#ifdef _WIN32
#include "io.h"
#endif

#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/poset_handle_factory.h"
#include "SheafSystem/std_fstream.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"

/// @hack force initialization of static data members:

#include "SheafSystem/fiber_bundles_namespace.h"

using namespace std;
using namespace fiber_bundle;

string filename;

int
main(int argc, char** argv)
{
  if (argc > 1)
  {
    // test for existence of file
    // if the filename is not valid, then exit 0 with warning message

    ifstream ltest(argv[1]);
    if (ltest.is_open())
    {
      filename = argv[1];
      ltest.close();
    }
    else
    {
      cout << "warning: no such filename " << argv[1] << "\n";
      exit(0);
    }
  }
  else
  {
    cerr << "usage: dumpsheaf sheaf_file [enable_error_report]\n";
    exit(0);
  }

  /// @hack prototype instantiation bug.

  fiber_bundles_namespace::initialize_prototypes();

  // Make the default namespace

  namespace_poset ns("test");

  // Read the namespace from the file;
  // need write access in order to read it.

  ns.get_read_write_access();
  storage_agent sa(filename, sheaf_file::READ_ONLY, false);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.read_entire(ns);

  // Output a text version to stdout

  cout << ns << endl;

  return 0;
}
