
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Test driver for unstructured_block.java

import bindings.java.*;

public class unstructured_block_t extends base_example
{
  static final String moduleName = "fiber_bundles_java_binding";
  static final String className  = "unstructured_block_t";

  public unstructured_block_t()
  {
    super(moduleName);
  }

  public unstructured_block_t(String module_name)
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
    .append("    i_size j_size k_size (default = 2 2 2)").append(nl)
    .append("    -help  Print this message and exit.").append(nl)
    .append("    -h     Print this message and exit.").append(nl)
    .append(nl);

    System.out.println(sb);
    System.exit(1);
  }

  public static void make_unstructured_block_1d(fiber_bundles_namespace xns,
      long xi_size)
  {
    base_space_poset lmesh =
      unstructured_block.new_host(xns, "unstructured_mesh_base_space_1d", 1);
    lmesh.get_read_write_access(true);

    poset_path lproto_path =
      new poset_path(unstructured_block.prototypes_poset_name(),
                     "segment_complex");

    unstructured_block lblock =
      new unstructured_block(lmesh, lproto_path, xi_size, true);
    lblock.put_name("unstructured_block_1d", true, false);
    lblock.detach_from_state();

    lmesh.release_access(false);
  }

  public static void make_unstructured_block_2d(fiber_bundles_namespace xns,
      long xi_size,
      long xj_size)
  {
    base_space_poset lmesh =
      unstructured_block.new_host(xns, "unstructured_mesh_base_space_2d", 2);
    lmesh.get_read_write_access(true);

    // Make quad block.

    poset_path lquad_proto_path =
      new poset_path(unstructured_block.prototypes_poset_name(),
                     "quad_nodes");

    unstructured_block lquad_block =
      new unstructured_block(lmesh, lquad_proto_path, xi_size, xj_size, true);
    lquad_block.put_name("unstructured_quad_block_2d", true, false);
    lquad_block.detach_from_state();

    // Make triangle block.

    poset_path ltriangle_proto_path =
      new poset_path(unstructured_block.prototypes_poset_name(),
                     "triangle_nodes");

    unstructured_block ltriangle_block =
      new unstructured_block(lmesh, ltriangle_proto_path, xi_size, xj_size, true);
    ltriangle_block.put_name("unstructured_triangle_block_2d", true, false);
    ltriangle_block.detach_from_state();

    lmesh.release_access(false);
  }

  public static void make_unstructured_block_3d(fiber_bundles_namespace xns,
      long xi_size,
      long xj_size,
      long xk_size)
  {
    // $$TODO: Implement this method after the java-bindings-dev-2 branch
    //         is merged with the inversion-dev-7 branch.
  }

  public static void main(String argv[])
  {
    // Handle command line arguments.

    if(argv.length > 3)
    {
      usage();
    }
    else if( (argv.length == 1) &&
             (("-help".equals(argv[0])) || ("-h".equals(argv[0]))) )
    {
      usage();
    }

    long i_size = 2;
    long j_size = 2;
    long k_size = 2;

    if(argv.length >= 1)
    {
      i_size = (new Long(argv[0])).longValue();
    }

    if(argv.length >= 2)
    {
      j_size = (new Long(argv[1])).longValue();
    }

    if(argv.length >= 3)
    {
      j_size = (new Long(argv[2])).longValue();
    }

    // Instantiate "this" class (loads the libraries, etc.).

    unstructured_block_t test = new unstructured_block_t();

    // Make the fiber_bundles namespace.

    fiber_bundles_namespace lns = new fiber_bundles_namespace(className);


    lns.get_read_write_access(false);

    make_unstructured_block_1d(lns, i_size);
    make_unstructured_block_2d(lns, i_size, j_size);
    make_unstructured_block_3d(lns, i_size, j_size, k_size);

    // Output a text version to stdout

    //System.out.println(lns.to_string());

    // Write namespace to file.

    test.writeHdfFile(lns, className +".hdf");

    //     storage_agent sa = new storage_agent("unstructured_block_t.hdf",
    //                                          sheaf_file.access_mode.READ_WRITE,
    //                                          true,
    //                                          false);
    //     sa.write_entire(lns);

  }
}
