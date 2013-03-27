// $RCSfile: query_mesh.cc,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:16:59 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/query_mesh.cc

#include "adjacency_extractor.h"
#include "connectivity_extractor.h"
#include "id_map.h"
#include "namespace_poset.h"
#include "neighborhood_extractor.h"
#include "postorder_member_iterator.h"
#include "std_iostream.h"
#include "stencil_extractor.h"
#include "storage_agent.h"

using namespace fiber_bundle;

/// @issue Had to cast literal string to char *

char* sp_names[3] = {const_cast<char *>("__vertices"),
                     const_cast<char *>("__edges"),
                     const_cast<char *>("__elements")};


void
init_id_array(poset* mesh, const string& sp_name, int* domain_mbrs)
{
  subposet sp(mesh, sp_name);

  id_map* id_map = sp.id_map();
  int i=0;
  postorder_member_iterator itr(mesh->top(), &sp);
  while(!itr.is_done())
  {
    domain_mbrs[i++] = id_map->domain_id(itr.item().index());
    itr.next();
  }

  sp.detach_from_state();
}


void
print_it(int* ids, int* ids_cts, int* domain_mbrs, int domain_mbrs_ct)
{
  int* ids_p = ids;

  cout << endl;
  for(int i=0; i<domain_mbrs_ct; i++)
  {
    cout << "mbr= " << setw(5) << domain_mbrs[i] << " ids=";

    for(int j=0; j<ids_cts[i]; j++)
    {
      cout << " " << setw(5) << *ids_p;
      ids_p++;
    }
    cout << endl;
  }
  cout << endl << endl;
}


void
query_connectivity(poset* mesh, int upper_level, int lower_level, bool use_poset_api)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  cout << endl << endl;
  cout << "connectivity for " << ll_name << " and " << ul_name << endl;

  // Make a  connectivity extractor

  connectivity_extractor ae(mesh, ll_name, ul_name);

  // Get the number of entries in the connectivity array

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int conn_cts_ct = ae.connectivity_cts_ct();
  int conn_ct = ae.connectivity_ct();

  // Allocate the connectivity counts and connectivity arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* conn_cts = new int[conn_cts_ct];
  int* conn = new int[conn_ct];

  // Extract the connectivity

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, conn_cts, conn_cts_ct, conn, conn_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ul_name, domain_mbrs);

    ae.extract(domain_mbrs, domain_mbrs_ct, conn_cts, conn_cts_ct, conn, conn_ct);
  }

  // Print it

  print_it(conn, conn_cts, domain_mbrs, domain_mbrs_ct);

}


void
query_adjacency(poset* mesh, int upper_level, int lower_level, bool use_poset_api)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ul_name(sp_names[upper_level]);
  string ll_name(sp_names[lower_level]);

  cout << endl << endl;
  cout << "adjacency for " << ll_name << " and " << ul_name << endl;

  // Make a  adjacency extractor

  adjacency_extractor ae(mesh, ll_name, ul_name);

  // Get the number of entries in the adjacency array for the bottom

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int adj_cts_ct = ae.adjacency_cts_ct();
  int adj_ct = ae.adjacency_ct();

  // Allocate the adjacency counts and adjacency arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* adj_cts = new int[adj_cts_ct];
  int* adj = new int[adj_ct];

  // Extract the adjacency

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, adj_cts, adj_cts_ct, adj, adj_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ll_name, domain_mbrs);

    ae.extract(domain_mbrs, domain_mbrs_ct, adj_cts, adj_cts_ct, adj, adj_ct);
  }


  // Print it

  print_it(adj, adj_cts, domain_mbrs, domain_mbrs_ct);

}

void
query_neighborhood(poset* mesh,
                   int upper_level,
                   int lower_level,
                   bool includes_center,
                   bool use_poset_api)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  cout << endl << endl;
  cout << "neighborhood for " << ll_name << " and " << ul_name << endl;

  // Make a  neighborhood extractor

  neighborhood_extractor ae(mesh, ll_name, ul_name, includes_center);

  // Get the number of entries in the neighborhood array

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int nbr_cts_ct = ae.neighborhood_cts_ct();
  int nbr_ct = ae.neighborhood_ct();

  // Allocate the neighborhood counts and neighborhood arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* nbr_cts = new int[nbr_cts_ct];
  int* nbr = new int[nbr_ct];

  // Extract the neighborhood

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, nbr_cts, nbr_cts_ct, nbr, nbr_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ul_name, domain_mbrs);

    ae.extract(domain_mbrs, domain_mbrs_ct, nbr_cts, nbr_cts_ct, nbr, nbr_ct);
  }


  // Print it

  print_it(nbr, nbr_cts, domain_mbrs, domain_mbrs_ct);

}



void
query_stencil(poset* mesh,
              int upper_level,
              int lower_level,
              bool includes_center,
              bool use_poset_api)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  cout << endl << endl;
  cout << "stencil for " << ll_name << " and " << ul_name << endl;

  // Make a  stencil extractor

  stencil_extractor ae(mesh, ll_name, ul_name, includes_center);

  // Get the number of entries in the stencil array

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int sten_cts_ct = ae.stencil_cts_ct();
  int sten_ct = ae.stencil_ct();

  // Allocate the stencil counts and stencil arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* sten_cts = new int[sten_cts_ct];
  int* sten = new int[sten_ct];

  // Extract the stencil

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, sten_cts, sten_cts_ct, sten, sten_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ll_name, domain_mbrs);

    ae.extract(domain_mbrs, domain_mbrs_ct, sten_cts, sten_cts_ct, sten, sten_ct);
  }


  // Print it

  print_it(sten, sten_cts, domain_mbrs, domain_mbrs_ct);

}


void
query_mesh(namespace_poset* ns,
           const string& mesh_name,
           bool use_poset_api)
{
  // Get a handle to the top of the mesh poset

  poset* mesh = new poset(ns, mesh_name);
  mesh->get_read_access();

  // Query element-nodal connectivity

  query_connectivity(mesh, 2, 0, false);
  if (use_poset_api)
    query_connectivity(mesh, 2, 0, true);

  // Query element-edge connectivity

  query_connectivity(mesh, 2, 1, false);
  if (use_poset_api)
    query_connectivity(mesh, 2, 1, true);

  // Query edge-nodal connectivity

  query_connectivity(mesh, 1, 0, false);
  if (use_poset_api)
    query_connectivity(mesh, 1, 0, true);

  // Query element-nodal adjacency,

  query_adjacency(mesh, 2, 0, false);
  if (use_poset_api)
    query_adjacency(mesh, 2, 0, true);

  // Query element-edge adjacency,

  query_adjacency(mesh, 2, 1, false);
  if (use_poset_api)
    query_adjacency(mesh, 2, 1, true);

  // Query edge-nodal adjacency,

  query_adjacency(mesh, 1, 0, false);
  if (use_poset_api)
    query_adjacency(mesh, 1, 0, true);

  // Query element-nodal neighborhood

  query_neighborhood(mesh, 2, 0, false, false);
  if (use_poset_api)
    query_neighborhood(mesh, 2, 0, true, true);

  // Query element-edge neighborhood

  query_neighborhood(mesh, 2, 1, false, false);
  if (use_poset_api)
    query_neighborhood(mesh, 2, 1, true, true);

  // Query edge-nodal neighborhood

  query_neighborhood(mesh, 1, 0, false, false);
  if (use_poset_api)
    query_neighborhood(mesh, 1, 0, true, true);

  // Query element-nodal stencil

  query_stencil(mesh, 2, 0, false, false);
  if (use_poset_api)
    query_stencil(mesh, 2, 0, true, true);

  // Query element-edge stencil

  query_stencil(mesh, 2, 1, false, false);
  if (use_poset_api)
    query_stencil(mesh, 2, 1, true, true);

  // Query edge-nodal stencil

  query_stencil(mesh, 1, 0, false, false);
  if (use_poset_api)
    query_stencil(mesh, 1, 0, true, true);

}


int
main(int argc, char** argv)
{
  string filename;
  string mesh_name;

  if (argc > 2)
  {
    filename = argv[1];
    mesh_name = argv[2];
  }
  else
  {
    cerr << "usage: query_mesh sheaf_file mesh_name [use_poset_api]\n";
    exit(1);
  }

  bool use_poset_api = argc > 3;

  storage_agent sa(filename, sheaf_file::READ_ONLY, false);

  namespace_poset ns;

  sa.read_entire(ns);

  ns.get_read_access();

  query_mesh(&ns, mesh_name, use_poset_api);

  return 0;
}
