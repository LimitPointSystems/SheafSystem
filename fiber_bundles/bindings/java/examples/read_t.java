
//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Class read_t
//

import bindings.java.*;

public class read_t extends base_example
{

  static final String moduleName = "fiber_bundles_java_binding";
  static final String className  = "read_t";

  public read_t()
  {
    super(moduleName);
  }

  public read_t(String module_name)
  {
    super(module_name);
  }

  public static void usage()
  {
    String nl = System.getProperty("line.separator");

    StringBuffer sb = new StringBuffer();
    sb.append("Usage: java [-cp CLASSPATH] " + className
              + " hdf_file_name").append(nl);

    System.out.println(sb);
    System.exit(1);
  }

  public static void main(String[] args)
  {

    // Handle command line arguments.

    String fileName = null;

    if(args.length < 1)
    {
      usage();
    }
    else
    {
      fileName = args[0];
    }

    // Instantiate "this" class (loads the libraries, etc.).

    read_t test = new read_t();

    // Make the namespace poset.
    // (Note: We have to supply the default args in Java).

    namespace_poset the_namespace =
      new namespace_poset("test", 8, 16, 4);

    // Read the namespace poset from the file.

    test.readHdfFile(the_namespace, fileName);

    // Output a text version to stdout.

    System.out.println(the_namespace.to_string());

  }
}

