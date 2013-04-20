

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/write_sheaves_namespace.cc
/// An example of what a standard namespace might look like.

// NOTE: This example, produces the equivalent namespace to
//       one obtained by instantiating a sheaves_namespace
//       and writing it out.

#include "abstract_poset_member.h"
#include "namespace_poset.h"
#include "index_iterator.h"
#include "namespace_poset_member.h"
#include "poset.h"
#include "poset_member_iterator.h"
#include "postorder_iterator.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "schema_poset_member.h"
#include "assert_contract.h"
#include "storage_agent.h"

using namespace sheaf;

// Creates schema for standard base space types.

void make_base_space_definitions();

//Create local coordinate schema, poset, and poset members.

void make_local_coordinate_definitions();

// Create local coordinates schema.

void make_local_coordinates_schema();

// Creates a member (jim) in the local coordinates poset.

void make_local_coordinates_jim(const string& name,
                                int dimension,
                                int orientation);

// Create cell definitions
void make_cell_definitions();
void make_vertex();
void make_edge();
void make_triangle();
void make_quad();
void make_tetrahedron();
void make_hexahedron();
void make_wedge();

// Globals (for convenience)
namespace_poset* ns;
poset* cell_definitions;
poset* local_coordinates;

int main()
{
  // Make sure the standard lps environment setting script has been executed.

  //  check_lps_script_has_run();

  // Create the namespace poset and name it.

  ns = new namespace_poset("sheaves_namespace");

  // Get read-write access to the namespace.

  ns->get_read_write_access();

  // Make base space definitions.

  make_base_space_definitions();

  // Write it to a file.

  storage_agent sa("sheaves_namespace.hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(*ns);

  ns->detach_from_state();
  delete ns;

  return 0;
}


///
void
make_base_space_definitions()
{

  // Preconditions:

  // Body:

  make_local_coordinate_definitions();

  make_cell_definitions();

  //   // Make base space definitions group (jrm)

  //   namespace_poset_member local_coordinates_defs(ns, "local coordinate definitions");
  //   namespace_poset_member cell_defs(ns, "cell definitions");
  //   total_poset_member* base_defs = local_coordinates_defs.l_join(&cell_defs);
  //   base_defs->put_name("base space definitions", true, false);

  //   local_coordinates_defs.detach_from_state();
  //   cell_defs.detach_from_state();
  //   base_defs->detach_from_state();
  //   delete base_defs;

  // Postconditions:

  // Exit

  return;
}


///
void
make_local_coordinate_definitions()
{
  // Preconditions:

  // Body:

  // Make schema for local coordinates

  make_local_coordinates_schema();

  // Make local coordinates

  total_poset_member local_coordinates_schema_mbr(ns,
      "local_coordinates_schema/local_coordinates_schema");

  local_coordinates = new poset(ns, &local_coordinates_schema_mbr,
                                "local_coordinates");

  local_coordinates->begin_jim_edit_mode();

  make_local_coordinates_jim("vertex", 0, 1);
  make_local_coordinates_jim("edge", 1, 1);
  make_local_coordinates_jim("triangle", 2, 1);
  make_local_coordinates_jim("quad", 2, 1);
  make_local_coordinates_jim("tetrahedron", 3, 1);
  make_local_coordinates_jim("hexahedron", 3, 1);
  make_local_coordinates_jim("wedge", 3, 1);


  // Finished writing to local_coordinates,
  // but base space constructions
  // will need read access.

  local_coordinates->end_jim_edit_mode();
  local_coordinates->get_read_access();

  // Make local coordinates definitions group (jrm)

  namespace_poset_member lm1(ns, "local_coordinates_schema");
  namespace_poset_member lm2(ns, "local_coordinates");

  total_poset_member* local_coordinates_defns = lm1.l_join(&lm2);
  local_coordinates_defns->put_name("local coordinate definitions", true, false);
  local_coordinates_defns->detach_from_state();
  delete local_coordinates_defns;

  // Detach handles allocated on stack so state will not be
  // deleted when pass out of scope

  local_coordinates_schema_mbr.detach_from_state();
  lm1.detach_from_state();
  lm2.detach_from_state();

  // Postconditions:

  // Exit

  return;
}


///
void
make_local_coordinates_schema()
{
  // Preconditions:

  // Body:

  total_poset_member* primitives_schema =  &(ns->primitives().schema());
  poset* local_coordinates_schema = new poset(ns, primitives_schema,
                                    "local_coordinates_schema");

  local_coordinates_schema->begin_jim_edit_mode();

  subposet table_dofs(local_coordinates_schema);
  subposet row_dofs(local_coordinates_schema);

  poset_dof_map* pdof_map = &ns->primitives().member_dof_map(INT);

  total_poset_member mbr;

  mbr.new_jim_state(local_coordinates_schema, pdof_map, false, false);
  mbr.put_name("dimension", true, false);
  row_dofs.insert_member(&mbr);

  mbr.new_jim_state(local_coordinates_schema, pdof_map, false, false);
  mbr.put_name("orientation", true, false);
  row_dofs.insert_member(&mbr);

  local_coordinates_schema->end_jim_edit_mode();

  /// @hack create a jem for the top just so we can give it a name
  /// Can remove jem creation when we support multiple names for poset members

  local_coordinates_schema->get_read_write_access();
  total_poset_member* local_coordinates_schema_mbr =
    new total_poset_member(local_coordinates_schema->top(), true);
  local_coordinates_schema_mbr->put_name("local_coordinates_schema", true, false);

  // Schematize the poset and all its members

  mbr.detach_from_state();
  local_coordinates_schema->schematize(&table_dofs, &row_dofs, true);
  table_dofs.detach_from_state();
  row_dofs.detach_from_state();
  local_coordinates_schema->release_access();

  // Postconditions:

  // Exit:

}


///




void
make_local_coordinates_jim(const string& xname,
                           int xdimension,
                           int xorientation)
{
  // Preconditions:

  require(!xname.empty());
  require(xdimension >= 0);
  require(xorientation >= 0);

  // Body:

  typedef struct
  {
    int dimension;
    int orientation;
  }
  Local_coordinates_row_dofs;

  Local_coordinates_row_dofs* local_coordinates_dofs =
    new Local_coordinates_row_dofs();
  local_coordinates_dofs->dimension = xdimension;
  local_coordinates_dofs->orientation = xorientation;

  total_poset_member mbr;
  mbr.new_jim_state(local_coordinates, 0, false, false);
  mbr.put_name(xname, true, false);
  mbr.put_dof_tuple(reinterpret_cast<void*>(local_coordinates_dofs),
                    sizeof(Local_coordinates_row_dofs));
  mbr.detach_from_state();

  // Postconditions:

  // Exit

  return;
}

///
void
make_cell_definitions()
{

  // Preconditions:

  // Body:

  total_poset_member local_coordinates_schema_mbr(ns,
      "local_coordinates_schema/local_coordinates_schema");

  cell_definitions = new poset(ns, &local_coordinates_schema_mbr,
                               "cell definitions");

  cell_definitions->get_read_write_access();
  cell_definitions->begin_jim_edit_mode();

  make_vertex();
  make_edge();
  make_triangle();
  make_quad();
  make_tetrahedron();
  make_hexahedron();
  make_wedge();

  cell_definitions->end_jim_edit_mode();
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member mbr;
  mbr.new_jim_state(cell_definitions, pdof_map, true, false);
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true, false);
  v0.put_name("edge-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true, false);
  v1.put_name("edge-vertex 1", true, false);

  local_coordinates_mbr.attach_to_state(local_coordinates, "edge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e(cell_definitions, pdof_map, true, false);
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true, false);
  v0.put_name("triangle-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true, false);
  v1.put_name("triangle-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true, false);
  v2.put_name("triangle-vertex 2", true, false);

  local_coordinates_mbr.attach_to_state(local_coordinates, "edge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true, false);
  e0.put_name("triangle-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true, false);
  e1.put_name("triangle-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true, false);
  e2.put_name("triangle-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  local_coordinates_mbr.attach_to_state(local_coordinates, "triangle");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member t(cell_definitions, pdof_map, true, false);
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true, false);
  v0.put_name("quad-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true, false);
  v1.put_name("quad-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true, false);
  v2.put_name("quad-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true, false);
  v3.put_name("quad-vertex 3", true, false);

  local_coordinates_mbr.attach_to_state(local_coordinates, "edge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true, false);
  e0.put_name("quad-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true, false);
  e1.put_name("quad-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true, false);
  e2.put_name("quad-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v3);

  total_poset_member e3(cell_definitions, pdof_map, true, false);
  e3.put_name("quad-edge 3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v0);

  local_coordinates_mbr.attach_to_state(local_coordinates, "quad");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member q(cell_definitions, pdof_map, true, false);
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true, false);
  v0.put_name("tetrahedron-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true, false);
  v1.put_name("tetrahedron-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true, false);
  v2.put_name("tetrahedron-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true, false);
  v3.put_name("tetrahedron-vertex 3", true, false);

  local_coordinates_mbr.attach_to_state(local_coordinates, "edge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true, false);
  e0.put_name("tetrahedron-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true, false);
  e1.put_name("tetrahedron-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true, false);
  e2.put_name("tetrahedron-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  total_poset_member e3(cell_definitions, pdof_map, true, false);
  e3.put_name("tetrahedron-edge 3", true, false);
  e3.create_cover_link(&v2);
  e3.create_cover_link(&v3);

  total_poset_member e4(cell_definitions, pdof_map, true, false);
  e4.put_name("tetrahedron-edge 4", true, false);
  e4.create_cover_link(&v3);
  e4.create_cover_link(&v1);

  total_poset_member e5(cell_definitions, pdof_map, true, false);
  e5.put_name("tetrahedron-edge 5", true, false);
  e5.create_cover_link(&v3);
  e5.create_cover_link(&v0);

  local_coordinates_mbr.attach_to_state(local_coordinates, "triangle");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f0(cell_definitions, pdof_map, true, false);
  f0.put_name("tetrahedron-face 0", true, false);
  f0.create_cover_link(&e0);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e2);

  total_poset_member f1(cell_definitions, pdof_map, true, false);
  f1.put_name("tetrahedron-face 1", true, false);
  f1.create_cover_link(&e2);
  f1.create_cover_link(&e3);
  f1.create_cover_link(&e5);

  total_poset_member f2(cell_definitions, pdof_map, true, false);
  f2.put_name("tetrahedron-face 2", true, false);
  f2.create_cover_link(&e5);
  f2.create_cover_link(&e4);
  f2.create_cover_link(&e0);

  total_poset_member f3(cell_definitions, pdof_map, true, false);
  f3.put_name("tetrahedron-face 3", true, false);
  f3.create_cover_link(&e1);
  f3.create_cover_link(&e3);
  f3.create_cover_link(&e4);

  local_coordinates_mbr.attach_to_state(local_coordinates, "tetrahedron");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member t(cell_definitions, pdof_map, true, false);
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true, false);
  v0.put_name("hexahedron-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true, false);
  v1.put_name("hexahedron-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true, false);
  v2.put_name("hexahedron-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true, false);
  v3.put_name("hexahedron-vertex 3", true, false);

  total_poset_member v4(cell_definitions, pdof_map, true, false);
  v4.put_name("hexahedron-vertex 4", true, false);

  total_poset_member v5(cell_definitions, pdof_map, true, false);
  v5.put_name("hexahedron-vertex 5", true, false);

  total_poset_member v6(cell_definitions, pdof_map, true, false);
  v6.put_name("hexahedron-vertex 6", true, false);

  total_poset_member v7(cell_definitions, pdof_map, true, false);
  v7.put_name("hexahedron-vertex 7", true, false);

  local_coordinates_mbr.attach_to_state(local_coordinates, "edge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true, false);
  e0.put_name("hexahedron-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true, false);
  e1.put_name("hexahedron-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true, false);
  e2.put_name("hexahedron-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v3);

  total_poset_member e3(cell_definitions, pdof_map, true, false);
  e3.put_name("hexahedron-edge 3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v0);

  total_poset_member e4(cell_definitions, pdof_map, true, false);
  e4.put_name("hexahedron-edge 4", true, false);
  e4.create_cover_link(&v4);
  e4.create_cover_link(&v5);

  total_poset_member e5(cell_definitions, pdof_map, true, false);
  e5.put_name("hexahedron-edge 5", true, false);
  e5.create_cover_link(&v5);
  e5.create_cover_link(&v6);

  total_poset_member e6(cell_definitions, pdof_map, true, false);
  e6.put_name("hexahedron-edge 6", true, false);
  e6.create_cover_link(&v6);
  e6.create_cover_link(&v7);

  total_poset_member e7(cell_definitions, pdof_map, true, false);
  e7.put_name("hexahedron-edge 7", true, false);
  e7.create_cover_link(&v7);
  e7.create_cover_link(&v4);

  total_poset_member e8(cell_definitions, pdof_map, true, false);
  e8.put_name("hexahedron-edge 8", true, false);
  e8.create_cover_link(&v3);
  e8.create_cover_link(&v7);

  total_poset_member e9(cell_definitions, pdof_map, true, false);
  e9.put_name("hexahedron-edge 9", true, false);
  e9.create_cover_link(&v2);
  e9.create_cover_link(&v6);

  total_poset_member e10(cell_definitions, pdof_map, true, false);
  e10.put_name("hexahedron-edge 10", true, false);
  e10.create_cover_link(&v1);
  e10.create_cover_link(&v5);

  total_poset_member e11(cell_definitions, pdof_map, true, false);
  e11.put_name("hexahedron-edge 11", true, false);
  e11.create_cover_link(&v0);
  e11.create_cover_link(&v4);

  local_coordinates_mbr.attach_to_state(local_coordinates, "quad");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f0(cell_definitions, pdof_map, true, false);
  f0.put_name("hexahedron-face 0", true, false);
  f0.create_cover_link(&e0);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e2);
  f0.create_cover_link(&e3);

  total_poset_member f1(cell_definitions, pdof_map, true, false);
  f1.put_name("hexahedron-face 1", true, false);
  f1.create_cover_link(&e4);
  f1.create_cover_link(&e5);
  f1.create_cover_link(&e6);
  f1.create_cover_link(&e7);

  total_poset_member f2(cell_definitions, pdof_map, true, false);
  f2.put_name("hexahedron-face 2", true, false);
  f2.create_cover_link(&e10);
  f2.create_cover_link(&e5);
  f2.create_cover_link(&e9);
  f2.create_cover_link(&e1);

  total_poset_member f3(cell_definitions, pdof_map, true, false);
  f3.put_name("hexahedron-face 3", true, false);
  f3.create_cover_link(&e11);
  f3.create_cover_link(&e7);
  f3.create_cover_link(&e8);
  f3.create_cover_link(&e3);

  total_poset_member f4(cell_definitions, pdof_map, true, false);
  f4.put_name("hexahedron-face 4", true, false);
  f4.create_cover_link(&e0);
  f4.create_cover_link(&e10);
  f4.create_cover_link(&e4);
  f4.create_cover_link(&e11);

  total_poset_member f5(cell_definitions, pdof_map, true, false);
  f5.put_name("hexahedron-face 5", true, false);
  f5.create_cover_link(&e2);
  f5.create_cover_link(&e9);
  f5.create_cover_link(&e6);
  f5.create_cover_link(&e8);

  //make_6(h, name, f0, f1, f2, f3, f4, f5);

  local_coordinates_mbr.attach_to_state(local_coordinates, "hexahedron");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member h(cell_definitions, pdof_map, true, false);
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
  local_coordinates_mbr.attach_to_state(local_coordinates, "vertex");

  poset_dof_map* pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member v0(cell_definitions, pdof_map, true, false);
  v0.put_name("wedge-vertex 0", true, false);

  total_poset_member v1(cell_definitions, pdof_map, true, false);
  v1.put_name("wedge-vertex 1", true, false);

  total_poset_member v2(cell_definitions, pdof_map, true, false);
  v2.put_name("wedge-vertex 2", true, false);

  total_poset_member v3(cell_definitions, pdof_map, true, false);
  v3.put_name("wedge-vertex 3", true, false);

  total_poset_member v4(cell_definitions, pdof_map, true, false);
  v4.put_name("wedge-vertex 4", true, false);

  total_poset_member v5(cell_definitions, pdof_map, true, false);
  v5.put_name("wedge-vertex 5", true, false);


  local_coordinates_mbr.attach_to_state(local_coordinates, "edge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member e0(cell_definitions, pdof_map, true, false);
  e0.put_name("wedge-edge 0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  total_poset_member e1(cell_definitions, pdof_map, true, false);
  e1.put_name("wedge-edge 1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  total_poset_member e2(cell_definitions, pdof_map, true, false);
  e2.put_name("wedge-edge 2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  total_poset_member e3(cell_definitions, pdof_map, true, false);
  e3.put_name("wedge-edge 3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v4);

  total_poset_member e4(cell_definitions, pdof_map, true, false);
  e4.put_name("wedge-edge 4", true, false);
  e4.create_cover_link(&v4);
  e4.create_cover_link(&v5);

  total_poset_member e5(cell_definitions, pdof_map, true, false);
  e5.put_name("wedge-edge 5", true, false);
  e5.create_cover_link(&v5);
  e5.create_cover_link(&v3);

  total_poset_member e6(cell_definitions, pdof_map, true, false);
  e6.put_name("wedge-edge 6", true, false);
  e6.create_cover_link(&v0);
  e6.create_cover_link(&v3);

  total_poset_member e7(cell_definitions, pdof_map, true, false);
  e7.put_name("wedge-edge 7", true, false);
  e7.create_cover_link(&v1);
  e7.create_cover_link(&v4);

  total_poset_member e8(cell_definitions, pdof_map, true, false);
  e8.put_name("wedge-edge 8", true, false);
  e8.create_cover_link(&v2);
  e8.create_cover_link(&v5);


  local_coordinates_mbr.attach_to_state(local_coordinates, "quad");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f0(cell_definitions, pdof_map, true, false);
  f0.put_name("wedge-face 0", true, false);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e8);
  f0.create_cover_link(&e4);
  f0.create_cover_link(&e7);

  total_poset_member f1(cell_definitions, pdof_map, true, false);
  f1.put_name("wedge-face 1", true, false);
  f1.create_cover_link(&e2);
  f1.create_cover_link(&e6);
  f1.create_cover_link(&e5);
  f1.create_cover_link(&e8);

  total_poset_member f2(cell_definitions, pdof_map, true, false);
  f2.put_name("wedge-face 2", true, false);
  f2.create_cover_link(&e0);
  f2.create_cover_link(&e7);
  f2.create_cover_link(&e3);
  f2.create_cover_link(&e6);


  local_coordinates_mbr.attach_to_state(local_coordinates, "triangle");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member f3(cell_definitions, pdof_map, true, false);
  f3.put_name("wedge-face 3", true, false);
  f3.create_cover_link(&e0);
  f3.create_cover_link(&e1);
  f3.create_cover_link(&e2);

  total_poset_member f4(cell_definitions, pdof_map, true, false);
  f4.put_name("wedge-face 4", true, false);
  f4.create_cover_link(&e3);
  f4.create_cover_link(&e4);
  f4.create_cover_link(&e5);

  local_coordinates_mbr.attach_to_state(local_coordinates, "wedge");
  pdof_map = &(local_coordinates_mbr.dof_map());

  total_poset_member w(cell_definitions, pdof_map, true, false);
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

