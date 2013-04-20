
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Test driver for structured_block_2d.java

import bindings.java.*;

public class structured_block_2d_t extends base_example
{
  static final String moduleName = "fiber_bundles_java_binding";
  static final String className  = "structured_block_2d_t";

  public structured_block_2d_t()
  {
    super(moduleName);
  }

  public structured_block_2d_t(String module_name)
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
    .append("    i_size j_size (default = 1 1)").append(nl)
    .append("    -help  Print this message and exit.").append(nl)
    .append("    -h     Print this message and exit.").append(nl)
    .append(nl);

    System.out.println(sb);
    System.exit(1);
  }

  public static void main(String argv[])
  {
    // Handle command line arguments.

    if(argv.length > 2)
    {
      usage();
    }
    else if( (argv.length == 1) &&
             (("-help".equals(argv[0])) || ("-h".equals(argv[0]))) )
    {
      usage();
    }

    long i_size = 1;
    long j_size = 1;

    if(argv.length >= 1)
    {
      i_size = (new Long(argv[0])).longValue();
    }

    if(argv.length == 2)
    {
      j_size = (new Long(argv[1])).longValue();
    }

    // Instantiate "this" class (loads the libraries, etc.).

    structured_block_2d_t test = new structured_block_2d_t();

    // Make the fiber_bundles namespace.

    fiber_bundles_namespace lns = new fiber_bundles_namespace(className);

    lns.get_read_write_access(false);

    // Make the mesh

    base_space_poset lmesh =
      structured_block_2d.new_host(lns, "structured_block_2d_mesh");
    lmesh.begin_jim_edit_mode(true);

    structured_block_2d lblock =
      new structured_block_2d(lmesh, i_size, j_size, true);

    lblock.put_name("2D_structured_block", true, false);

    lmesh.end_jim_edit_mode(true, true);

    lblock.get_read_access();

    // Output a text version to stdout

    //System.out.println(lns.to_string());

    // Test the refinement map.

    System.out.println("\n##### Refinement map test ###############\n");

    chart_point_2d lpt;
    chart_point_2d lref_pt = new chart_point_2d();

    for(double lxcoord= -1.0; lxcoord <= 1.0; lxcoord += 0.1)
    {
      for(double lycoord= -1.0; lycoord <= 1.0; lycoord += 0.1)
      {
        lpt = new chart_point_2d(lblock.index(), lxcoord, lycoord);
        lblock.refine_point_pa(lpt, lref_pt);
        System.out.print("point: ");
        System.out.print(lpt.to_string());
        System.out.print("\trefined point: ");
        System.out.print(lref_pt.to_string());
        lblock.unrefine_point_pa(lref_pt, lpt);
        System.out.print("\tunrefined point: ");
        System.out.println(lpt.to_string());
      }
    }

    System.out.println("\n##### End refinement map test ###############\n");


    // Write namespace to file.

    test.writeHdfFile(lns, className +".hdf");

    //     storage_agent sa = new storage_agent("structured_block_2d_t.hdf",
    //                                          sheaf_file.access_mode.READ_WRITE,
    //                                          true,
    //                                          false);
    //     sa.put_member_record_buffer_ub(15);
    //     sa.put_dof_tuple_record_buffer_ub(15);
    //     sa.write_entire(lns);

    // Clean-up

    lblock.release_access(false);
    lblock.detach_from_state();
    lns.release_access(false);

  }
}
