
// $RCSfile: tetgen_generator.cc,v $ $Revision: 1.9 $ $Date: 2013/03/13 00:59:01 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for class tetgen_generator.

#include "tetgen_generator.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "cover_set_iterator.h"
#include "e3.h"
#include "index_space_iterator.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "std_iostream.h"
#include "std_string.h"
#include "std_sstream.h"
#include "std_vector.h"
#include "postorder_itr.h"
#include "section_space_schema_poset.h"
#include "subposet_member_iterator.h"
#include "unstructured_block.h"

using namespace geometry;
using namespace fiber_bundle::vd_algebra;
using namespace fiber_bundle::ed_algebra;
using namespace fiber_bundle::e3_algebra;

//#define DIAGNOSTIC_OUTPUT

// =============================================================================
// TETGEN_GENERATOR FACET
// =============================================================================

geometry::tetgen_generator::
tetgen_generator()
  : _name_space(0), _base_space(0), _base_member(0), _coords(0)
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

geometry::tetgen_generator::
tetgen_generator(fiber_bundles_namespace& xns,
                 const poset_path& xbase_member_path,
                 const poset_path& xcoords_member_path,
                 const string& xswitches)
  : _name_space(&xns), _tetgen_switches(xswitches)
{

#ifdef DIAGNOSTIC_OUTPUT
  cout << "Entering tetgen_generator::tetgen_generator" << endl;
  cout << "  xbase_member_path = " << xbase_member_path << endl;
  cout << "  xcoords_member_path = " << xcoords_member_path << endl;
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_member_path));
  require(xns.contains_poset_member(xcoords_member_path));

  // Body:

  _base_member = new base_space_member(&xns, xbase_member_path);

  _base_space = dynamic_cast<base_space_poset*>(_base_member->host());

  _coords = new sec_e3(&xns, xcoords_member_path);

  _volume_base_space_path.put_poset_name("volume_base_space");
  _volume_base_space_path.put_member_name(xbase_member_path.member_name());

  _volume_coordinates_path.put_poset_name("volume_coordinates_space");
  _volume_coordinates_path.put_member_name(xcoords_member_path.member_name());
  

  // Postconditions:

  ensure(_name_space = &xns);
  ensure(_base_member != 0);
  ensure(_base_space == _base_member->host());
  ensure(_coords != 0);

  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "Leaving tetgen_generator::tetgen_generator" << endl;
#endif

}

geometry::tetgen_generator::
~tetgen_generator()
{
  // Preconditions:

  // Body:

  if(_base_member != 0)
  {
    _base_member->detach_from_state();
    delete _base_member;
    _base_member = 0;
  }

  if(_base_space != 0)
  {
    //_base_space->detach_from_state(); // Protected
    _base_space = 0;
  }

  if(_coords != 0)
  {
     _coords->detach_from_state();
     delete _coords;
     _coords = 0;
  }

  // Postconditions:

  ensure(_base_member == 0);
  ensure(_coords == 0);

  // Exit:
}

fiber_bundles_namespace&
geometry::tetgen_generator::
name_space() const
{
  // Preconditions:

  require(_name_space != 0);

  // Body:

  fiber_bundles_namespace& result = *_name_space;

  // Postconditions:

  ensure(&result == _name_space);

  // Exit:

  return result;
}

base_space_poset&
geometry::tetgen_generator::
base_space() const
{
  // Preconditions:

  require(_base_space != 0);

  // Body:

  base_space_poset& result = *_base_space;

  // Postconditions:

  ensure(&result == _base_space);

  // Exit:

  return result;
}


base_space_member&
geometry::tetgen_generator::
base_member() const
{
  // Preconditions:

  require(_base_member != 0);

  // Body:

  base_space_member& result = *_base_member;

  // Postconditions:

  ensure(&result == _base_member);

  // Exit:

  return result;
}

const index_space_handle&
geometry::tetgen_generator:: 
vertices_id_space() const
{
  // Preconditions:

  // Body:

  const index_space_handle& result = base_space().vertices().id_space();

  // Postconditions:

  ensure(result == base_space().vertices().id_space());

  // Exit:

  return result;
}

sec_e3&
geometry::tetgen_generator::
coords() const
{
  // Preconditions:

  require(_coords != 0);

  // Body:

  sec_e3& result = *_coords;

  // Postconditions:

  ensure(&result == _coords);

  // Exit:

  return result;
}

const string&
geometry::tetgen_generator::
prototypes_poset_name()
{

  // Preconditions:

  // Body:

  static const string& result = unstructured_block::prototypes_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const poset_path&
geometry::tetgen_generator::
rep_path()
{
  // Preconditions:

  // Body:

  static const poset_path result("sec_rep_descriptors", "vertex_cells_dlinear");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const poset_path&
geometry::tetgen_generator::
tetra_proto_path()
{
  // Preconditions:

  // Body:

  static const poset_path result(prototypes_poset_name(), "tetra_complex");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const vector<mesh_generator::pod_type>&
geometry::tetgen_generator::
tri_connectivities() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _tri_connectivities;
}

const vector<e3_lite>&
geometry::tetgen_generator::
tri_coordinates() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _tri_coordinates;
}

const vector<mesh_generator::pod_type>&
geometry::tetgen_generator::
tet_connectivities() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _tet_connectivities;
}

const vector<e3_lite>&
geometry::tetgen_generator::
tet_coordinates() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _tet_coordinates;
}

const poset_path&
geometry::tetgen_generator::
volume_base_space_path() const
{
  return _volume_base_space_path;
}

const poset_path&
geometry::tetgen_generator::
volume_coordinates_path() const
{
  return _volume_coordinates_path;
}

void
geometry::tetgen_generator::
make_names(base_space_poset& xbase_space, int xd, const string& xroot)
{
  // Preconditions:

  // Body:

  // Create names for all members of subposet d_cells(xd).
  // Name are of the form "xroot_#" where "#" is sequential
  // from 0 to d_cells(xd).ct()-1.

  base_space_member lmbr;

  subposet& lsp = xbase_space.d_cells(xd);
  subposet_member_iterator* litr = lsp.member_iterator();
  size_type i = 0;
  while(!litr->is_done())
  {
    lmbr.attach_to_state(&xbase_space, litr->index());

    stringstream lstr;
    lstr << xroot << "_" << i;
    lmbr.put_name(lstr.str(), true, true);
    i++;

    litr->next();
  }

  lmbr.detach_from_state();

  delete litr;

  // Postconditions:

  ensure(unexecutable("All members of .d_cells(xd) have names"));

  // Exit:

  return;
}

base_space_poset*
geometry::tetgen_generator::
create_volume_base_space()
{
  // Preconditions:

  require(name_space().state_is_read_write_accessible());

  // Body:

  // Create a base space.

  const string& lbase_name = volume_base_space_path().poset_name();
  const string& lmbr_name  = volume_base_space_path().member_name();

  // @todo remove test when new_base_space fixed to find existing space; see issue 456.

  base_space_poset* lbase_space;
  if(name_space().contains_poset(lbase_name, false))
  {
    // The base space already exists, just get a reference to it.

    lbase_space = &name_space().member_poset<base_space_poset>(volume_base_space_path(), false);
  }
  else
  {
    // The base space does not exist; create it.

    lbase_space = &name_space().new_base_space<unstructured_block> (lbase_name, "", "", 3, true);
  }
  

  lbase_space->get_read_write_access();

  unstructured_block lblock(lbase_space,
                            tetra_proto_path(),
                            &_tet_connectivities[0],
                            _tet_connectivities.size(),
                            true);

  lblock.put_name(lmbr_name, true, false);

#ifdef DIAGNOSTIC_OUTPUT

  // Give members names.

  make_names(*lbase_space, 3, "tet");
  make_names(*lbase_space, 2, "face");
  make_names(*lbase_space, 1, "edge");
  make_names(*lbase_space, 0, "vertex");

#endif

  lblock.detach_from_state();

  // Postconditions:

  ensure(lbase_space->is_attached());

  // Exit:

  return lbase_space;
}

sec_at1_space*
geometry::tetgen_generator::
create_volume_coordinates_section()
{
  // Preconditions:

  require(name_space().state_is_read_write_accessible());

  // Body:

  const poset_path& lbase_path = volume_base_space_path();
  const string& lspace_name    = volume_coordinates_path().poset_name();
  const string& lmbr_name      = volume_coordinates_path().member_name();
  const poset_path& lrep_path  = rep_path();

  // Find or create the coordinates section space.

  sec_at1_space* lcoords_space;
  
  if(name_space().contains_poset(lspace_name, false))
  {
    // Coordinates space already exists,
    // must have previously created a mesh in it.
    // The current mesh has extend the base space,
    // so make sure the schema is up-to-date.

    lcoords_space = &name_space().member_poset<sec_at1_space>(volume_coordinates_path(), false);

    poset_path lscalar_path;
    sec_at0_space* lscalar_space;

    // Coordinates vector section space.

    lcoords_space->get_read_access();
    lcoords_space->schema().host()->update_hub_id_space(true);
    lcoords_space->schema().force_cache_update();
    lscalar_path = lcoords_space->scalar_space_path();
    lcoords_space->release_access();

    // Coordinates scalar section space.

    lscalar_space = &name_space().member_poset<sec_at0_space>(lscalar_path, false);
    lscalar_space->get_read_access();
    lscalar_space->schema().host()->update_hub_id_space(true);
    lscalar_space->schema().force_cache_update();
    lscalar_space->release_access();    
  }
  else
  {
    // Coordinates space doesn't exist, create it.

    // Create the section space on the top of these base space,
    // since we may generate meshes for multiple subvolumes.

    poset_path ltop_path(lbase_path.poset_name(), "top");
    
    lcoords_space =
      &(name_space().new_section_space<sec_e3> (lspace_name, ltop_path, lrep_path, true));
  }
  

  lcoords_space->get_read_write_access();

  // Create a coordinates section on the current base, which may not be the top.

  base_space_member lbase_mbr(&name_space(), lbase_path);

  sec_e3 lcoords(lcoords_space, lbase_mbr);

  lcoords.put_name(lmbr_name, true, false);

  // Add the coordinates to the coordinates section.

  size_type i = 0;
  //  index_space_iterator* litr = vertices_id_space().iterator(true);
  index_space_iterator& litr =
    lcoords.schema().discretization_id_space().get_iterator();
  while(!litr.is_done())
  {
    //    lcoords.put_fiber(litr->id(), _tet_coordinates[i++]);
    lcoords.put_fiber(litr.pod(), _tet_coordinates[i++]);
    litr.next();
  }
  lcoords.schema().discretization_id_space().release_iterator(litr);

  lbase_mbr.detach_from_state();
  lcoords.detach_from_state();

  // Postconditions:

  ensure(lcoords_space->is_attached());

  // Exit:

  return lcoords_space;
}

void
geometry::tetgen_generator::
invoke_tetgen(tetgenio& xtetgen_out) const
{
  // Preconditions:

  require(!tri_coordinates().empty());
  require(!tri_connectivities().empty());

  // Body:

  tetgenio  ltetgen_in;
  tetgenio* lbgmin = 0;

  //$$SCRIBBLE: If we want to add constrained points (tetgen "-i" option)
  //            laddin has to contain the points and lb->insertaddpoints
  //            below has to be true (1).
           
  tetgenio* laddin = 0;

  // Add the nodal coordinates.

  size_type lsize = _tri_coordinates.size();

  ltetgen_in.firstnumber = 0;
  ltetgen_in.numberofpoints = lsize;

  ltetgen_in.pointlist = new double[lsize*3];

  for(int i=0, j=0; i<lsize; ++i)
  {
    const e3_lite& lcoords = _tri_coordinates[i];
    ltetgen_in.pointlist[j++] = lcoords[0];
    ltetgen_in.pointlist[j++] = lcoords[1];
    ltetgen_in.pointlist[j++] = lcoords[2];
  }

#ifdef DIAGNOSTIC_OUTPUT
  ltetgen_in.save_nodes(const_cast<char*>("tetgen"));
#endif

  //============================================================================

  // Add the surface triangle connectivities.

  size_type ltriangle_ct = _tri_connectivities.size()/3;

  ltetgen_in.numberoffacets = ltriangle_ct;
  ltetgen_in.facetlist = new tetgenio::facet[ltriangle_ct];
  ltetgen_in.facetmarkerlist = new int[ltriangle_ct];

  tetgenio::facet* lfacet;
  tetgenio::polygon* lpolygon;

  for(int i=0, j=0; i<ltriangle_ct; ++i)
  {
    lfacet = &ltetgen_in.facetlist[i];
    lfacet->numberofpolygons = 1;
    lfacet->polygonlist = new tetgenio::polygon[lfacet->numberofpolygons];
    lfacet->numberofholes = 0;
    lfacet->holelist = NULL;
    lpolygon = &lfacet->polygonlist[0];
    lpolygon->numberofvertices = 3;
    lpolygon->vertexlist = new int[lpolygon->numberofvertices];

    lpolygon->vertexlist[0] = _tri_connectivities[j++];
    lpolygon->vertexlist[1] = _tri_connectivities[j++];
    lpolygon->vertexlist[2] = _tri_connectivities[j++];

    ltetgen_in.facetmarkerlist[i] = 0;
  }

#ifdef DIAGNOSTIC_OUTPUT
  ltetgen_in.save_poly(const_cast<char*>("tetgen"));
#endif

  //============================================================================

  // Invoke tetgen's tetrahedralize function which generates a
  // mesh of tetrahedrons.

  // Tetgen wants (command line) switches to be of type char*;
  // so cast away constness.

  char* switches = const_cast<char*>(_tetgen_switches.c_str());

  tetgenbehavior lb;
  if(!lb.parse_commandline(switches))
  {
    post_fatal_error_message(
      "Unregognized tetgen switch in " + _tetgen_switches);
  }
  tetrahedralize(&lb, &ltetgen_in, &xtetgen_out, laddin, lbgmin);

  //============================================================================

#ifdef DIAGNOSTIC_OUTPUT
  xtetgen_out.save_nodes(const_cast<char*>("tetgen"));
  xtetgen_out.save_elements(const_cast<char*>("tetgen"));
  xtetgen_out.save_faces(const_cast<char*>("tetgen"));
#endif

  // Postconditions:

  ensure(unexecutable(\
    "xtetgen_out contains generated tetrahedrons faces, edges, & vertices"));

  // Exit:

  return;
}

void
geometry::tetgen_generator::
collect_surface_coordinates()
{
  // Preconditions:


  require(coords().is_attached());
  
  // Body:

  coords().get_read_access();

  _tri_coordinates.clear();

  e3_lite lfiber;

  //  size_type j = 0;

  //  index_space_iterator* litr = vertices_id_space().iterator(true);
  index_space_iterator& litr =
    _coords->schema().discretization_id_space().get_iterator();
  while(!litr.is_done())
  {
#ifdef DIAGNOSTIC_OUTPUT
    cout << litr.pod() << endl;
#endif

    //    coords().get_fiber(litr->id(), lfiber);
    coords().get_fiber(litr.pod(), lfiber);
    _tri_coordinates.push_back(lfiber);

#ifdef DIAGNOSTIC_OUTPUT
    //    cout << j << "  " << lfiber << endl;
    cout << litr.pod() << "  " << lfiber << endl;
#endif

    //    ++j;
    litr.next();
  }

  _coords->schema().discretization_id_space().release_iterator(litr);

  coords().release_access();

  // Postconditions:

  ensure(unexecutable("_tri_coordinates contains the surface coordinates"));
  ensure(unexecutable(\
    "xvertex_map contains a map from internal ids to tetgen ids"));
  ensure(unexecutable(\
    "xvertex_ids contains a map from tetgen ids to internal ids"));

  // Exit:

  return;
}

void
geometry::tetgen_generator::
collect_tri_connectivities()
{
  // Preconditions:

  require(base_space().is_attached());
  require(base_member().is_attached());
  
  // Body:

  // Get the triangle connectivities.  Have to make sure that the
  // nodal ordering in consistent (right hand rule).

  //============================================================================

  // The lower cover of the active surface contains triangles and
  // polygon boundaries.  So, use the triangles subposet
  // as a filter.

  const subposet& ltriangles_sp = base_space().d_cells(2);

  //============================================================================

  _tri_connectivities.clear();

  pod_type lvertex_ids0[2];
  pod_type lvertex_ids2[2];

  hash_set_postorder_itr ltri_itr(base_member(), ltriangles_sp, DOWN, NOT_STRICT);
  while(!ltri_itr.is_done())
  {
    const scoped_index& ltriangle_id = ltri_itr.index();

    index_space_iterator& lseg_itr = base_space().get_cover_id_space_iterator(LOWER, ltriangle_id);

    // Compare first and third segments.
    // Find the common vertex which is the start vertex.
    // The second vertex is the other vertex of the first segment.
    // The third vertex is the other vertex of the third segment.

    pod_index_type ls0 = lseg_itr.hub_pod();
    index_space_iterator& lvertex_itr = base_space().get_cover_id_space_iterator(LOWER, ls0);
    lvertex_ids0[0] = lvertex_itr.hub_pod();
    lvertex_itr.next();
    lvertex_ids0[1] = lvertex_itr.hub_pod();
    base_space().release_cover_id_space_iterator(lvertex_itr);

    // Skip to third segment.

    lseg_itr.next();
    lseg_itr.next();

    pod_index_type ls2 = lseg_itr.hub_pod();
    lvertex_itr = base_space().get_cover_id_space_iterator(LOWER, ls2);
    lvertex_ids2[0] = lvertex_itr.hub_pod();
    lvertex_itr.next();
    lvertex_ids2[1] = lvertex_itr.hub_pod();
    base_space().release_cover_id_space_iterator(lvertex_itr);

    // Get the indices into lvertex_ids0 (i0 & i1) and lvertex_ids2 (i2).

    size_type i0, i1, i2;
    if(lvertex_ids0[0] == lvertex_ids2[0])
    {
      i0 = 0; i1 = 1; i2 = 1;
    } 
    else if(lvertex_ids0[0] == lvertex_ids2[1])
    {
      i0 = 0; i1 = 1; i2 = 0;
    }
    else if(lvertex_ids0[1] == lvertex_ids2[0])
    {
      i0 = 1; i1 = 0; i2 = 1;
    } 
    else if(lvertex_ids0[1] == lvertex_ids2[1])
    {
      i0 = 1; i1 = 0; i2 = 0;
    } 

    _tri_connectivities.push_back(lvertex_ids0[i0]);
    _tri_connectivities.push_back(lvertex_ids0[i1]);
    _tri_connectivities.push_back(lvertex_ids2[i2]);

    base_space().release_cover_id_space_iterator(lseg_itr);
 
    ltri_itr.truncate();
  }

  // Convert the sheaf connectivity internal ids to tetgen ids (0 - (n-1)).

  // Printout the ids if debugging, 

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl;
  cout << "Internal ids:" << endl;
  for(size_type i=0; i<_tri_connectivities.size(); ++i)
  {
    cout << "  " << _tri_connectivities[i];
    if((i+1)%3 == 0) cout << endl;
  }
  cout << endl;
#endif

  // The id space for the vertices/_d_cells[0] provides th mapping from/to
  // internal ids to/from client/tetgen ids.

  //  const index_space& lindex_space = vertices_id_space();
  const index_space_handle& lindex_space =
    _coords->schema().discretization_id_space();
  scoped_index lmbr_id(base_space().member_id(false));
  for(size_type i=0; i<_tri_connectivities.size(); ++i)
  {
    //    _tri_connectivities[i] = lindex_space.pod(_tri_connectivities[i]);
    lmbr_id.put_pod(_tri_connectivities[i]);
    _tri_connectivities[i] = lindex_space.pod(lmbr_id);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "Client/Tetgen ids:" << endl;
  for(size_type i=0; i<_tri_connectivities.size(); ++i)
  {
    cout << "  " << _tri_connectivities[i];
    if((i+1)%3 == 0) cout << endl;
  }
  cout << endl;
#endif


  // Postconditions:

  ensure(unexecutable("_tri_connectivities contains the triangle connectivities"));

  // Exit:

  return;;
}


void
geometry::tetgen_generator::
collect_tetgen_results(const tetgenio& xtetgen_out)
{
  // Preconditions:

  require(unexecutable(
    "xtetgen_out contains the results from tetgen::tetrahedralize."));
  
  // Body:

  size_type lpoint_ct = xtetgen_out.numberofpoints;
  size_type lpoint_attr_ct = xtetgen_out.numberofpointattributes;
  size_type lfirst_index = xtetgen_out.firstnumber;
  double*   lpointlist = xtetgen_out.pointlist;
  double*   lpoint_attr_list = xtetgen_out.pointattributelist;
  int*      lpoint_mkr_list = xtetgen_out.pointmarkerlist;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "Nodes:" << endl;
  cout << xtetgen_out.numberofpoints << "  " <<  xtetgen_out.mesh_dim << "  "
       << xtetgen_out.numberofpointattributes << "  "
       << (xtetgen_out.pointmarkerlist != NULL ? 1 : 0)
       << endl;
#endif

  _tet_coordinates.clear();

  e3_lite lnode;

  for(size_type i=0; i<lpoint_ct; ++i)
  {
    lnode[0] = lpointlist[i*3];
    lnode[1] = lpointlist[i*3+1];
    lnode[2] = lpointlist[i*3+2];
    _tet_coordinates.push_back(lnode);

#ifdef DIAGNOSTIC_OUTPUT
    cout << endl;
    cout << setw(8)  << i+lfirst_index
         << setw(12) << lnode[0]
         << setw(12) << lnode[1]
         << setw(12) << lnode[2];

    for(size_type j=0; j<lpoint_attr_ct; ++j)
    {
      cout << setw(12) << lpoint_attr_list[i*lpoint_attr_ct+j];
    }

    if(lpoint_mkr_list != NULL)
    {
      cout << setw(6) << lpoint_mkr_list[i];
    }
    cout << endl;
#endif

  }

  //============================================================================

  size_type ltet_ct        = xtetgen_out.numberoftetrahedra;
  size_type lnodes_per_tet = xtetgen_out.numberofcorners;
  size_type ltet_attr_ct   = xtetgen_out.numberoftetrahedronattributes;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "Elements:" << endl;
  cout << "  numberoftetrahedra = " <<  ltet_ct << endl;
  cout << "  numberofcorners = " << lnodes_per_tet << endl; 
  cout << "  numberoftetrahedronattributes = " <<  ltet_attr_ct << endl;
  cout << "  firstnumber = " << lfirst_index << endl;
#endif

 _tet_connectivities.clear();

  for(size_type i=0; i<ltet_ct; ++i)
  {
    size_type ltmp = i*lnodes_per_tet;

    // Reorder tetgen connectivities so the volumes are positive.

    pod_type lindex_0 = xtetgen_out.tetrahedronlist[ltmp];
    pod_type lindex_1 = xtetgen_out.tetrahedronlist[ltmp+1];
    pod_type lindex_2 = xtetgen_out.tetrahedronlist[ltmp+2];
    pod_type lindex_3 = xtetgen_out.tetrahedronlist[ltmp+3];

   _tet_connectivities.push_back(lindex_0);
   _tet_connectivities.push_back(lindex_2);
   _tet_connectivities.push_back(lindex_1);
   _tet_connectivities.push_back(lindex_3);

#ifdef DIAGNOSTIC_OUTPUT
    cout << setw(8) << i+lfirst_index;
    for( size_type j=0; j<lnodes_per_tet; ++j)
    {
      cout << setw(8) << xtetgen_out.tetrahedronlist[ltmp+j];
    }
    ltmp = i*ltet_attr_ct;
    for( size_type j=0; j<ltet_attr_ct; ++j)
    {
      cout << setw(12)
           << xtetgen_out.tetrahedronattributelist[ltmp+j];

    }
    cout << endl;
#endif

  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl;
#endif

  //============================================================================

  // Postconditions:

  require(unexecutable(
    " _tet_coordinates contains the coordinates returned by tetgen"));
  require(unexecutable(
    "_tet_connectivities contains the connectivities for the tets returned by tetgen"));

  // Exit:

  return;
}



void
geometry::tetgen_generator::
update_name_space()
{
  // Preconditions:

  require(!tet_coordinates().empty());
  require(!tet_connectivities().empty());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
    for(int i=0; i<_tet_coordinates.size(); ++i)
    {
      cout << setw(8) << i << " : " << _tet_coordinates[i] << endl;
    }
    cout << endl;

    for(int i=0, j=0; i<_tet_connectivities.size()/4; ++i)
    {
      cout << setw(8) << i << " :"
           << setw(8) << _tet_connectivities[j++]
           << setw(8) << _tet_connectivities[j++]
           << setw(8) << _tet_connectivities[j++]
           << setw(8) << _tet_connectivities[j++] << endl;
    }
    cout << endl;
#endif

  // Create a new base space with the tetrahedrons generated by tetgen.

    base_space_poset* lbase = create_volume_base_space();

#ifdef DIAGNOSTIC_OUTPUT
  cout << *lbase << endl;
#endif

  // Create a new coordinates section with the coordinates generated by tetgen.

  sec_at1_space* lcoords = create_volume_coordinates_section();

#ifdef DIAGNOSTIC_OUTPUT
  cout << *lcoords << endl;
#endif

  //============================================================================

  lbase->release_access(); // $$ISSUE: Do we need this?

  //============================================================================

  // Postconditions:

  ensure(lbase != 0); 
  ensure(lcoords != 0); 

  // Exit:

  return;
}

double
geometry::tetgen_generator::
compute_tri_areas() const
{
  // Preconditions:

  require(!tri_coordinates().empty());
  require(!tri_connectivities().empty());
 
  // Body:

  //$$SCRIBBLE: We could use an eval_iterator here which will
  //            provide the correct evaluators and, thus, allow
  //            computing the volumes/areas.  However, the evaluator
  //            in this case is linear_2d which does not presently
  //            compute the normals.  Also, we have collected the
  //            triangle connectivities and coordinates in order
  //            to easily feed them to tetgen. So, here we just
  //            compute areas via the vector cross product.

  // Iterate over all of the surface triangles computing and printing
  // their areas and normals for testing. Also compute and print
  // the total surface area.

  double ltotal_area = 0;

  size_type lct = _tri_connectivities.size();
  for(size_type i=0; i<lct; i+=3)
  {
    size_type lid0 = _tri_connectivities[i];
    size_type lid1 = _tri_connectivities[i+1];
    size_type lid2 = _tri_connectivities[i+2];

    e3_lite lp0 = _tri_coordinates[lid0];
    e3_lite lp1 = _tri_coordinates[lid1];
    e3_lite lp2 = _tri_coordinates[lid2];

    subtract_equal(lp1, lp0);
    subtract_equal(lp2, lp0);

    cross_equal(lp1, lp2);  // lp1 is now cross product.
    double larea = 0.5*length(lp1);

    ltotal_area += larea;

    e3_lite lnormal = lp1;
    divide(lp1, 2.0*larea, lnormal);

    cout << endl;
    cout << "  " << lid0 << "  " << _tri_coordinates[lid0] << endl;
    cout << "  " << lid1 << "  " << _tri_coordinates[lid1] << endl;
    cout << "  " << lid2 << "  " << _tri_coordinates[lid2] << endl;
    cout << "      area   = " << larea << endl;
    cout << "      normal = " << lnormal << endl;

  }

  cout << endl;
  cout << "      Total area   = " << ltotal_area << endl;
  cout << endl;

  double result = ltotal_area;

  // Postconditions:

  ensure(unexecutable("result == total area of the surface triangles"));

  // Exit:

  return result;
}

double
geometry::tetgen_generator::
compute_tet_volumes() const
{
  // Preconditions:

  require(!tet_coordinates().empty());
  require(!tet_connectivities().empty());
 
  // Body:

  //$$SCRIBBLE: See SCRIBBLE in compute_tri_areas.

  // Iterate over all of the tetrahedrons computing and printing
  // their volumes for testing. Also compute and print
  // the total volume.

  double ltotal_vol = 0;

  size_type lid0, lid1, lid2, lid3;
  size_type ltet_ct = _tet_connectivities.size();
  for(size_type i=0; i<ltet_ct; i+=4)
  {
    lid0 = _tet_connectivities[i];
    lid1 = _tet_connectivities[i+1];
    lid2 = _tet_connectivities[i+2];
    lid3 = _tet_connectivities[i+3];

    e3_lite lp0 = _tet_coordinates[lid0]; // a
    e3_lite lp1 = _tet_coordinates[lid1]; // b
    e3_lite lp2 = _tet_coordinates[lid2]; // c
    e3_lite lp3 = _tet_coordinates[lid3]; // d

    e3_lite l03;
    e3_lite l13;
    e3_lite l23;

    subtract(lp0, lp3, l03); // a-d
    subtract(lp1, lp3, l13); // b-d
    subtract(lp2, lp3, l23); // c-d

    cross_equal(l13, l23);  // l13 is now the cross product.

    double lvol = dot(l03, l13)/6.0;

    ltotal_vol += lvol;

    cout << endl;
    cout << "  " << lid0 << "  " << _tet_coordinates[lid0] << endl;
    cout << "  " << lid1 << "  " << _tet_coordinates[lid1] << endl;
    cout << "  " << lid2 << "  " << _tet_coordinates[lid2] << endl;
    cout << "  " << lid3 << "  " << _tet_coordinates[lid3] << endl;
    cout << "      volume   = " << lvol << endl;
  }

  cout << endl;
  cout << "      Total volume   = " << ltotal_vol << endl;
  cout << endl;

  double result = ltotal_vol;

  // Postconditions:

  ensure(unexecutable("result == total volume of the tetrahedrons"));

  // Exit:

  return result;
}

// =============================================================================
// MESH_GENERATOR FACET
// =============================================================================

void
geometry::tetgen_generator::
generate()
{
#ifdef DIAGNOSTIC_OUTPUT
  cout << "Entering tetgen_generator::generate()" << endl;
#endif

  // Preconditions:

  require(_name_space != 0);
  require(_name_space->state_is_read_write_accessible());
  require(_base_space != 0);
  require(_base_member != 0);
  require(_coords != 0);

  // Body:

  // Get read access to the base space.

  base_space().get_read_access();

  // Collect the coordinates at the triangle vertices.

  collect_surface_coordinates();

  // Collect the connectivity of the surface triangles.

  collect_tri_connectivities();

#ifdef DIAGNOSTIC_OUTPUT

  // Compute the areas (and normals) for the surface triangles and
  // print them out for debugging.

  compute_tri_areas();

#endif

  base_space().release_access();

  // Invoke tetgen and return the results in ltetgen_ou.

  tetgenio ltetgen_out;
  invoke_tetgen(ltetgen_out);

  // Collect the tetgen results.

  collect_tetgen_results(ltetgen_out);

#ifdef DIAGNOSTIC_OUTPUT

  // Compute the volumes of the generated tetrahedrons and
  // print them out for debugging.

  compute_tet_volumes();

#endif

  // Add the tetgen results to the namespace.

  update_name_space();

  // Postconditions:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "Leaving tetgen_generator::generate()" << endl;
#endif

  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::tetgen_generator::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const tetgen_generator*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;
}

geometry::tetgen_generator*
geometry::tetgen_generator::
clone() const
{
  tetgen_generator* result;
  
  // Preconditions:

  // Body:
  
  result = new tetgen_generator();
  //result = 0;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
geometry::tetgen_generator::
invariant() const
{
  bool result = true;
 
  // Preconditions:

  // Body:
 
  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(any::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// =============================================================================
//  NON-MEMBER FUNCTIONS
// =============================================================================


//#undef DIAGNOSTIC_OUTPUT
