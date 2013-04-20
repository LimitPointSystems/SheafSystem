
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Test driver for structured_block_1d.java

import bindings.java.*;

public class structured_block_1d_t extends base_example
{
  static final String moduleName = "fiber_bundles_java_binding";
  static final String className  = "structured_block_1d_t";

  public structured_block_1d_t()
  {
    super(moduleName);
  }

  public structured_block_1d_t(String module_name)
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

    if(argv.length > 1)
    {
      usage();
    }
    else if( (argv.length == 1) &&
             (("-help".equals(argv[0])) || ("-h".equals(argv[0]))) )
    {
      usage();
    }


    long i_size = 1;
    if(argv.length == 1)
    {
      i_size = (new Long(argv[0])).longValue();
    }

    // Instantiate "this" class (loads the libraries, etc.).

    structured_block_1d_t test = new structured_block_1d_t();

    // Make the fiber_bundles namespace.

    fiber_bundles_namespace lns = new fiber_bundles_namespace(className);

    lns.get_read_write_access(false);

    // Make the mesh

    base_space_poset lmesh =
      structured_block_1d.new_host(lns, "structured_block_1d_mesh");
    lmesh.begin_jim_edit_mode(true);

    structured_block_1d lblock =
      new structured_block_1d(lmesh, i_size, true);

    lblock.put_name("1D_structured_block", true, false);

    lmesh.end_jim_edit_mode(true, true);

    lblock.get_read_access();

    // Output a text version to stdout

    //System.out.println(lns.to_string());

    // Test the refinement map.

    System.out.println("\n##### Refinement map test ###############\n");

    chart_point_1d lpt;
    chart_point_1d lref_pt = new chart_point_1d();

    for(double lcoord= -1.0; lcoord <= 1.0; lcoord += 0.1)
    {
      lpt = new chart_point_1d(lblock.index(), lcoord);
      lblock.refine_point_pa(lpt, lref_pt);
      System.out.print("point: ");
      System.out.print(lpt.to_string());
      System.out.print("\trefined point: ");
      System.out.print(lref_pt.to_string());
      lblock.unrefine_point_pa(lref_pt, lpt);
      System.out.print("\tunrefined point: ");
      System.out.println(lpt.to_string());
    }

    System.out.println("\n##### End refinement map test ###############\n");

    // Make uniform (coordinate) sec_rep_space.

    poset_path luniform_path =
      new poset_path("sec_rep_descriptors", "vertex_block_dlinear");

    poset_path luniform_schema_path =
      sec_e1.make_schema(lns,
                         "coordinate_section_space_schema",
                         luniform_path,
                         lblock.path(true),
                         true);

    sec_rep_space luniform_space =
      sec_e1.new_host(lns, "coordinate_section_space",
                      luniform_schema_path, true);

    // Make non-uniform (property) sec_rep_space.

    poset_path lnon_uniform_path =
      new poset_path("sec_rep_descriptors", "vertex_element_dlinear");

    poset_path lnon_uniform_schema_path =
      sec_at0.make_schema(lns,
                          "property_section_space_schema",
                          lnon_uniform_path,
                          lblock.path(true),
                          true);

    sec_rep_space lnon_uniform_space =
      sec_at0.new_host(lns, "property_section_space",
                       lnon_uniform_schema_path, true);

    // Write namespace to file.

    test.writeHdfFile(lns, className +".hdf");

    // Clean-up

    lblock.release_access(false);
    lblock.detach_from_state();
    lns.release_access(false);
  }
}
