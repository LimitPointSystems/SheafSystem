
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/fiber_bundles_read.cc

#include "base_space_poset.h"

#ifdef _WIN32
#include "io.h"
#endif

#include "namespace_poset.h"
#include "poset_handle_factory.h"
#include "std_iostream.h"
#include "storage_agent.h"

/// @hack force initialization of static data members:

#include "fiber_bundles_namespace.h"

using namespace fiber_bundle;

string filename;

int
main(int argc, char** argv)
{
 if (argc > 1)
  {
    // test for existence of file
    // if the filename is not valid, then exit 0 with warning message

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
    cerr << "usage: fiber_bundles_read sheaf_file [enable_error_report]\n";
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
