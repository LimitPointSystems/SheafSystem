
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/sheaves_read.cc

#include "assert_contract.h"

#ifdef _WIN32
#include "io.h"
#endif

#include "std_iostream.h"
#include "namespace_poset.h"
#include "storage_agent.h"



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
