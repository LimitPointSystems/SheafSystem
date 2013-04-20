
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Test driver for field_vd.java

//$$SCRIBBLE: This is just a placeholder.  It will be
//            further developed as part of the field algebra project.

import bindings.java.*;

public class field_vd_t extends base_example
{
  static final String moduleName = "fields_java_binding";
  static final String className  = "field_vd_t";

  public field_vd_t()
  {
    super(moduleName);
  }

  public field_vd_t(String module_name)
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
    .append("    i_size (default = 1)").append(nl)
    .append("    -help  Print this message and exit.").append(nl)
    .append("    -h     Print this message and exit.").append(nl)
    .append(nl);

    System.out.println(sb);
    System.exit(1);
  }

  public static void main(String argv[])
  {
    // Handle command line arguments.

    if(argv.length > 0)
    {
      usage();
    }

    // Instantiate "this" class (loads the libraries, etc.).

    field_vd_t test = new field_vd_t();

    // Make the fiber_bundles namespace.

    fiber_bundles_namespace lns = new fiber_bundles_namespace(className);

    // Output a text version to stdout.

    //System.out.println(the_namespace.to_string());

    // Write namespace to file.

    test.writeHdfFile(lns, className +".hdf");

  }
}
