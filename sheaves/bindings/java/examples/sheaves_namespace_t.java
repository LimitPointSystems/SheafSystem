//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Class sheaves_namespace_t
//

import bindings.java.*;

public class sheaves_namespace_t extends base_example
{
  static final String moduleName = "sheaves_java_binding";
  static final String className  = "sheaves_namespace_t";

  public sheaves_namespace_t()
  {
    super(moduleName);
  }

  public sheaves_namespace_t(String module_name)
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

    sheaves_namespace_t test = new sheaves_namespace_t();

    // Make the sheaves namespace.

    sheaves_namespace the_namespace = new sheaves_namespace(className);

    // Output a text version to stdout.

    //System.out.println(the_namespace.to_string());

    // Write it to a file

    test.writeHdfFile(the_namespace, className +".hdf");

  }
}
