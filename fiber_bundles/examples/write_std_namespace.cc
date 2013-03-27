// $RCSfile: write_std_namespace.cc,v $ $Revision: 1.30 $ $Date: 2013/01/12 17:16:59 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/write_std_namespace.cc
/// An example of what a standard namespace might look like.

// NOTE: This example, produces the equivalent namespace to
//       one obtained by instantiating a fiber_bundles_namespace
//       and using a storage_agent to write it out.  Briefly, the
//       code would look like this (without error checking):
//       ...
//       fiber_bundles_namespace ns("std_namespace");
//       storage_agent sa("std_namespace.hdf");
//       sa.write_entire(ns);
//       ...
//


#include "at0.h"
#include "at1.h"
#include "atp.h"
#include "binary_section_space_schema_poset.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "ed.h"
#include "gl3.h"
#include "gln.h"
#include "itp.h"
#include "jcb.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_ed.h"
#include "met.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "namespace_poset_member.h"
#include "section_space_schema_poset.h"
#include "sec_rep_descriptor.h"
#include "sheaves_namespace.h"
#include "storage_agent.h"
#include "st2.h"
#include "st2_e2.h"
#include "st2_e3.h"
#include "state_tuple.h"
#include "state_tuple_component.h"
#include "stp.h"
#include "t11.h"
#include "ternary_section_space_schema_poset.h"
#include "tuple.h"
#include "tuv.h"
#include "vd.h"

using namespace fiber_bundle;

// Create cell definitions
void make_cell_definitions();
void make_vertex();
void make_edge();
void make_triangle();
void make_quad();
void make_tetrahedron();
void make_hexahedron();
void make_wedge();

// Create schema posets for standard fiber space types
void make_fiber_space_schema();

// Create standard section representation descriptors
void make_section_space_definitions();


// Globals (for convenience)
namespace_poset* ns;
poset* cell_definitions;
poset* local_coordinates;

int
main()
{
  // Create the namespace poset and name it.

  ns = new sheaves_namespace("std_namespace");

  // Get read-write access to the namespace.

  ns->get_read_write_access();

  // Make various definition groups.

  make_fiber_space_schema();

  // Make base space definitions.

  make_section_space_definitions();

  // Save the namespace to a file.

  storage_agent sa("std_namespace.hdf");
  sa.write_entire(*ns);

  delete ns;

  return 0;
}


///
void
make_cell_definitions()
{

  // Preconditions:

  // Body:

  schema_poset_member local_coordinates_schema_mbr(ns,
      "local_coordinates_schema/local_coordinates_schema", false);

  cell_definitions = new poset(ns, &local_coordinates_schema_mbr,
                               "cell definitions");

  cell_definitions->get_read_write_access();

  make_vertex();
  make_edge();
  make_triangle();
  make_quad();
  make_tetrahedron();
  make_hexahedron();
  make_wedge();

  cell_definitions->release_access();

  local_coordinates_schema_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_vertex()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member mbr;
  mbr.new_jim_state(cell_definitions, pdof_map, true);
  mbr.put_name("vertex", true, false);

  mbr.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_edge()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true);
  v0.put_name("edge-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true);
  v1.put_name("edge-vertex 1", true, false);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/edge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e(cell_definitions, pdof_map, true);
  e.put_name("edge", true, false);

  e.create_cover_link(&v0);
  e.create_cover_link(&v1);

  e.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_triangle()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true);
  v0.put_name("triangle-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true);
  v1.put_name("triangle-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true);
  v2.put_name("triangle-vertex 2", true, false);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/edge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true);
  e0.put_name("triangle-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true);
  e1.put_name("triangle-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true);
  e2.put_name("triangle-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/triangle", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member t(cell_definitions, pdof_map, true);
  t.put_name("triangle", true, false);
  t.create_cover_link(&e0);
  t.create_cover_link(&e1);
  t.create_cover_link(&e2);

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  t.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_quad()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true);
  v0.put_name("quad-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true);
  v1.put_name("quad-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true);
  v2.put_name("quad-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true);
  v3.put_name("quad-vertex 3", true, false);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/edge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true);
  e0.put_name("quad-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true);
  e1.put_name("quad-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true);
  e2.put_name("quad-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v3);

  total_poset_member e3(cell_definitions, pdof_map, true);
  e3.put_name("quad-edge 3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v0);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/quad", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member q(cell_definitions, pdof_map, true);
  q.put_name("quad", true, false);
  q.create_cover_link(&e0);
  q.create_cover_link(&e1);
  q.create_cover_link(&e2);
  q.create_cover_link(&e3);

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  q.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_tetrahedron()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true);
  v0.put_name("tetrahedron-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true);
  v1.put_name("tetrahedron-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true);
  v2.put_name("tetrahedron-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true);
  v3.put_name("tetrahedron-vertex 3", true, false);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/edge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true);
  e0.put_name("tetrahedron-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true);
  e1.put_name("tetrahedron-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true);
  e2.put_name("tetrahedron-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  total_poset_member e3(cell_definitions, pdof_map, true);
  e3.put_name("tetrahedron-edge 3", true, false);
  e3.create_cover_link(&v2);
  e3.create_cover_link(&v3);

  total_poset_member e4(cell_definitions, pdof_map, true);
  e4.put_name("tetrahedron-edge 4", true, false);
  e4.create_cover_link(&v3);
  e4.create_cover_link(&v1);

  total_poset_member e5(cell_definitions, pdof_map, true);
  e5.put_name("tetrahedron-edge 5", true, false);
  e5.create_cover_link(&v3);
  e5.create_cover_link(&v0);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/triangle", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f0(cell_definitions, pdof_map, true);
  f0.put_name("tetrahedron-face 0", true, false);
  f0.create_cover_link(&e0);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e2);

  total_poset_member f1(cell_definitions, pdof_map, true);
  f1.put_name("tetrahedron-face 1", true, false);
  f1.create_cover_link(&e2);
  f1.create_cover_link(&e3);
  f1.create_cover_link(&e5);

  total_poset_member f2(cell_definitions, pdof_map, true);
  f2.put_name("tetrahedron-face 2", true, false);
  f2.create_cover_link(&e5);
  f2.create_cover_link(&e4);
  f2.create_cover_link(&e0);

  total_poset_member f3(cell_definitions, pdof_map, true);
  f3.put_name("tetrahedron-face 3", true, false);
  f3.create_cover_link(&e1);
  f3.create_cover_link(&e3);
  f3.create_cover_link(&e4);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/tetrahedron", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member t(cell_definitions, pdof_map, true);
  t.put_name("tetrahedron", true, false);
  t.create_cover_link(&f0);
  t.create_cover_link(&f1);
  t.create_cover_link(&f2);
  t.create_cover_link(&f3);

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();
  e5.detach_from_state();
  f0.detach_from_state();
  f1.detach_from_state();
  f2.detach_from_state();
  f3.detach_from_state();
  t.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_hexahedron()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true);
  v0.put_name("hexahedron-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true);
  v1.put_name("hexahedron-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true);
  v2.put_name("hexahedron-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true);
  v3.put_name("hexahedron-vertex 3", true, false);

  total_poset_member v4(cell_definitions, pdof_map, true);
  v4.put_name("hexahedron-vertex 4", true, false);

  total_poset_member v5(cell_definitions, pdof_map, true);
  v5.put_name("hexahedron-vertex 5", true, false);

  total_poset_member v6(cell_definitions, pdof_map, true);
  v6.put_name("hexahedron-vertex 6", true, false);

  total_poset_member v7(cell_definitions, pdof_map, true);
  v7.put_name("hexahedron-vertex 7", true, false);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/edge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true);
  e0.put_name("hexahedron-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true);
  e1.put_name("hexahedron-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true);
  e2.put_name("hexahedron-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v3);

  total_poset_member e3(cell_definitions, pdof_map, true);
  e3.put_name("hexahedron-edge 3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v0);

  total_poset_member e4(cell_definitions, pdof_map, true);
  e4.put_name("hexahedron-edge 4", true, false);
  e4.create_cover_link(&v4);
  e4.create_cover_link(&v5);

  total_poset_member e5(cell_definitions, pdof_map, true);
  e5.put_name("hexahedron-edge 5", true, false);
  e5.create_cover_link(&v5);
  e5.create_cover_link(&v6);

  total_poset_member e6(cell_definitions, pdof_map, true);
  e6.put_name("hexahedron-edge 6", true, false);
  e6.create_cover_link(&v6);
  e6.create_cover_link(&v7);

  total_poset_member e7(cell_definitions, pdof_map, true);
  e7.put_name("hexahedron-edge 7", true, false);
  e7.create_cover_link(&v7);
  e7.create_cover_link(&v4);

  total_poset_member e8(cell_definitions, pdof_map, true);
  e8.put_name("hexahedron-edge 8", true, false);
  e8.create_cover_link(&v3);
  e8.create_cover_link(&v7);

  total_poset_member e9(cell_definitions, pdof_map, true);
  e9.put_name("hexahedron-edge 9", true, false);
  e9.create_cover_link(&v2);
  e9.create_cover_link(&v6);

  total_poset_member e10(cell_definitions, pdof_map, true);
  e10.put_name("hexahedron-edge 10", true, false);
  e10.create_cover_link(&v1);
  e10.create_cover_link(&v5);

  total_poset_member e11(cell_definitions, pdof_map, true);
  e11.put_name("hexahedron-edge 11", true, false);
  e11.create_cover_link(&v0);
  e11.create_cover_link(&v4);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/quad", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f0(cell_definitions, pdof_map, true);
  f0.put_name("hexahedron-face 0", true, false);
  f0.create_cover_link(&e0);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e2);
  f0.create_cover_link(&e3);

  total_poset_member f1(cell_definitions, pdof_map, true);
  f1.put_name("hexahedron-face 1", true, false);
  f1.create_cover_link(&e4);
  f1.create_cover_link(&e5);
  f1.create_cover_link(&e6);
  f1.create_cover_link(&e7);

  total_poset_member f2(cell_definitions, pdof_map, true);
  f2.put_name("hexahedron-face 2", true, false);
  f2.create_cover_link(&e10);
  f2.create_cover_link(&e5);
  f2.create_cover_link(&e9);
  f2.create_cover_link(&e1);

  total_poset_member f3(cell_definitions, pdof_map, true);
  f3.put_name("hexahedron-face 3", true, false);
  f3.create_cover_link(&e11);
  f3.create_cover_link(&e7);
  f3.create_cover_link(&e8);
  f3.create_cover_link(&e3);

  total_poset_member f4(cell_definitions, pdof_map, true);
  f4.put_name("hexahedron-face 4", true, false);
  f4.create_cover_link(&e0);
  f4.create_cover_link(&e10);
  f4.create_cover_link(&e4);
  f4.create_cover_link(&e11);

  total_poset_member f5(cell_definitions, pdof_map, true);
  f5.put_name("hexahedron-face 5", true, false);
  f5.create_cover_link(&e2);
  f5.create_cover_link(&e9);
  f5.create_cover_link(&e6);
  f5.create_cover_link(&e8);

  //make_6(h, name, f0, f1, f2, f3, f4, f5);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/hexahedron", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member h(cell_definitions, pdof_map, true);
  h.put_name("hexahedron", true, false);
  h.create_cover_link(&f0);
  h.create_cover_link(&f1);
  h.create_cover_link(&f2);
  h.create_cover_link(&f3);
  h.create_cover_link(&f4);
  h.create_cover_link(&f5);

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  v4.detach_from_state();
  v5.detach_from_state();
  v6.detach_from_state();
  v7.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();
  e5.detach_from_state();
  e6.detach_from_state();
  e7.detach_from_state();
  e8.detach_from_state();
  e9.detach_from_state();
  e10.detach_from_state();
  e11.detach_from_state();
  f0.detach_from_state();
  f1.detach_from_state();
  f2.detach_from_state();
  f3.detach_from_state();
  f4.detach_from_state();
  f5.detach_from_state();
  h.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_wedge()
{
  // Preconditions:

  // Body:

  total_poset_member local_coordinates_mbr;
  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/vertex", false);

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true);
  v0.put_name("wedge-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true);
  v1.put_name("wedge-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true);
  v2.put_name("wedge-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true);
  v3.put_name("wedge-vertex 3", true, false);

  total_poset_member v4(cell_definitions, pdof_map, true);
  v4.put_name("wedge-vertex 4", true, false);

  total_poset_member v5(cell_definitions, pdof_map, true);
  v5.put_name("wedge-vertex 5", true, false);


  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/edge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true);
  e0.put_name("wedge-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true);
  e1.put_name("wedge-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true);
  e2.put_name("wedge-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  total_poset_member e3(cell_definitions, pdof_map, true);
  e3.put_name("wedge-edge 3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v4);

  total_poset_member e4(cell_definitions, pdof_map, true);
  e4.put_name("wedge-edge 4", true, false);
  e4.create_cover_link(&v4);
  e4.create_cover_link(&v5);

  total_poset_member e5(cell_definitions, pdof_map, true);
  e5.put_name("wedge-edge 5", true, false);
  e5.create_cover_link(&v5);
  e5.create_cover_link(&v3);

  total_poset_member e6(cell_definitions, pdof_map, true);
  e6.put_name("wedge-edge 6", true, false);
  e6.create_cover_link(&v0);
  e6.create_cover_link(&v3);

  total_poset_member e7(cell_definitions, pdof_map, true);
  e7.put_name("wedge-edge 7", true, false);
  e7.create_cover_link(&v1);
  e7.create_cover_link(&v4);

  total_poset_member e8(cell_definitions, pdof_map, true);
  e8.put_name("wedge-edge 8", true, false);
  e8.create_cover_link(&v2);
  e8.create_cover_link(&v5);


  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/quad", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f0(cell_definitions, pdof_map, true);
  f0.put_name("wedge-face 0", true, false);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e8);
  f0.create_cover_link(&e4);
  f0.create_cover_link(&e7);

  total_poset_member f1(cell_definitions, pdof_map, true);
  f1.put_name("wedge-face 1", true, false);
  f1.create_cover_link(&e2);
  f1.create_cover_link(&e6);
  f1.create_cover_link(&e5);
  f1.create_cover_link(&e8);

  total_poset_member f2(cell_definitions, pdof_map, true);
  f2.put_name("wedge-face 2", true, false);
  f2.create_cover_link(&e0);
  f2.create_cover_link(&e7);
  f2.create_cover_link(&e3);
  f2.create_cover_link(&e6);


  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/triangle", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f3(cell_definitions, pdof_map, true);
  f3.put_name("wedge-face 3", true, false);
  f3.create_cover_link(&e0);
  f3.create_cover_link(&e1);
  f3.create_cover_link(&e2);

  total_poset_member f4(cell_definitions, pdof_map, true);
  f4.put_name("wedge-face 4", true, false);
  f4.create_cover_link(&e3);
  f4.create_cover_link(&e4);
  f4.create_cover_link(&e5);

  local_coordinates_mbr.attach_to_state(ns, "local_coordinates/wedge", false);
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member w(cell_definitions, pdof_map, true);
  w.put_name("wedge", true, false);

  w.create_cover_link(&f0);
  w.create_cover_link(&f1);
  w.create_cover_link(&f2);
  w.create_cover_link(&f3);
  w.create_cover_link(&f4);

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  v4.detach_from_state();
  v5.detach_from_state();

  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();
  e5.detach_from_state();
  e6.detach_from_state();
  e7.detach_from_state();
  e8.detach_from_state();

  f0.detach_from_state();
  f1.detach_from_state();
  f2.detach_from_state();
  f3.detach_from_state();
  f4.detach_from_state();

  w.detach_from_state();
  local_coordinates_mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}

///
void
make_fiber_space_schema()
{
  // Preconditions:

  // Body:

  total_poset_member* primitives_schema =  &(ns->primitives().schema());
  poset* fiber_definitions = new poset(ns, primitives_schema, "fiber_space_schema");
  fiber_definitions->get_read_write_access();

  subposet table_dofs(fiber_definitions);
  table_dofs.put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  subposet row_dofs(fiber_definitions);
  row_dofs.put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  // Make the various schema

  tuple::make_standard_schema(*ns);
  state_tuple::make_standard_schema(*ns);
  state_tuple_component::make_standard_schema(*ns);
  vd::make_standard_schema(*ns);
  jcb::make_standard_schema(*ns);
  jcb_ed::make_standard_schema(*ns);
  jcb_e13::make_standard_schema(*ns);
  jcb_e23::make_standard_schema(*ns);
  jcb_e33::make_standard_schema(*ns);
  tuv::make_standard_schema(*ns);
  t11::make_standard_schema(*ns);
  gln::make_standard_schema(*ns);
  gl3::make_standard_schema(*ns);
  stp::make_standard_schema(*ns);
  st2::make_standard_schema(*ns);
  met::make_standard_schema(*ns);
  met_ed::make_standard_schema(*ns);
  met_e1::make_standard_schema(*ns);
  met_e2::make_standard_schema(*ns);
  met_e3::make_standard_schema(*ns);
  atp::make_standard_schema(*ns);
  at0::make_standard_schema(*ns);
  itp::make_standard_schema(*ns);
  at1::make_standard_schema(*ns);
  ed::make_standard_schema(*ns);
  e1::make_standard_schema(*ns);
  e2::make_standard_schema(*ns);
  e3::make_standard_schema(*ns);
  st2_e2::make_standard_schema(*ns);
  st2_e3::make_standard_schema(*ns);

  // Schematize the poset and all its members

  fiber_definitions->schematize(&table_dofs, &row_dofs, true);

  table_dofs.detach_from_state();
  row_dofs.detach_from_state();

  fiber_definitions->release_access();

  // Postconditions:

  // Exit

  return;
}


///
void
make_section_space_definitions()
{
  // Preconditions:

  // Body:

  // Make the section space schema schema.

  sec_rep_descriptor::make_schema(ns);
  section_space_schema_poset::make_schema(ns);
  binary_section_space_schema_poset::make_schema(ns);
  ternary_section_space_schema_poset::make_schema(ns);

  // Make some standard sec rep descriptors

  poset* sec_rep_desc =
    new poset(ns,
              "sec_rep_descriptor_schema/sec_rep_descriptor_schema",
              "sec_rep_descriptors" );

  sec_rep_desc->get_read_write_access();

  sec_rep_descriptor v_e_dlinear;

  v_e_dlinear.new_jim_state(sec_rep_desc);
  v_e_dlinear.put_name("vertex_element_dlinear", true, false);
  v_e_dlinear.put_discretization_subposet_name("__vertices");
  v_e_dlinear.put_evaluation_subposet_name("__elements");
  v_e_dlinear.put_evaluator_family_name("dlinear");
  v_e_dlinear.put_url("www.lpsweb.com/libSheaf/std_namespace.html");
  v_e_dlinear.put_multiplicity(1);

  sec_rep_descriptor e_e_const;

  e_e_const.new_jim_state(sec_rep_desc);
  e_e_const.put_name("element_element_constant", true, false);
  e_e_const.put_discretization_subposet_name("__elements");
  e_e_const.put_evaluation_subposet_name("__elements");
  e_e_const.put_evaluator_family_name("const");
  e_e_const.put_url("www.lpsweb.com/libSheaf/std_namespace.html");
  e_e_const.put_multiplicity(1);

  // Make sec rep space definitions group (jrm)

  namespace_poset_member lm1(ns, "sec_rep_descriptor_schema");
  namespace_poset_member lm2(ns, "sec_rep_descriptors");

  total_poset_member* sec_defns = lm1.l_join(&lm2);
  sec_defns->put_name("section space definitions", true, false);
  sec_defns->detach_from_state();
  delete sec_defns;

  // Detach all the handles allocated on the stack

  e_e_const.detach_from_state();
  v_e_dlinear.detach_from_state();
  lm1.detach_from_state();
  lm2.detach_from_state();

  // Release access

  sec_rep_desc->release_access();

  // Postconditions:

  // Exit

  return;
}


