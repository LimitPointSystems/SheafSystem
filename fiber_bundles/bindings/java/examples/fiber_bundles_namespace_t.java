//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Class fiber_bundles_namespace_t
//

import bindings.java.*;

public class fiber_bundles_namespace_t extends base_example
{
  static final String moduleName = "fiber_bundles_java_binding";
  static final String className  = "fiber_bundles_namespace_t";

  public fiber_bundles_namespace_t()
  {
    super(moduleName);
  }

  public fiber_bundles_namespace_t(String module_name)
  {
    super(module_name);
  }

  public static void usage()
  {
    String nl = System.getProperty("line.separator");

    StringBuffer sb = new StringBuffer();
    sb.append("Usage: java [-cp CLASSPATH] " + className
              + " [-option]").append(nl)
    .append(nl)
    .append("where options include:").append(nl)
    .append("    -help  Print this message and exit.").append(nl)
    .append("    -h     Print this message and exit.").append(nl)
    .append(nl);

    System.out.println(sb);
    System.exit(1);
  }

  public static void main(String[] args) //throws java.rmi.RemoteException
  {
    // Handle command line arguments.

    if(args.length > 0)
    {
      usage();
    }

    // Instantiate "this" class (loads the libraries, etc.).

    fiber_bundles_namespace_t test = new fiber_bundles_namespace_t();

    // Make the fiber_bundles namespace.

    fiber_bundles_namespace the_namespace =
      new fiber_bundles_namespace(className);

    // Output a text version to stdout.

    //System.out.println(the_namespace.to_string());

    // Write it to a file

    test.writeHdfFile(the_namespace, className +".hdf");

  }
}
