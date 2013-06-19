

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_lattice

#include "kd_lattice.impl.h"

#include "array_section_dof_map.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "base_space_member.h"
#include "base_space_member_prototype.h"
#include "base_space_poset.h"
#include "block.impl.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.impl.h"
#include "geometry_namespace.h"
#include "hash_set_filter.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_bounding_box.h"
#include "kd_display.h"
#include "kd_edge.h"
#include "kd_edge_cohort.h"
#include "kd_face.h"
#include "kd_face_cohort.h"
#include "kd_line.h"
#include "kd_line_fragment.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_region.h"
#include "kd_segment.h"
#include "kd_surface.h"
#include "kd_triangle.h"
#include "kd_vertex.h"
#include "kd_vertex_cohort.h"
#include "kd_zone.h"
#include "kd_zone_cohort.h"
#include "linkorder_itr.h"
#include "postorder_itr.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_tuple_space.h"
#include "sec_e3.h"
#include "std_fstream.h"
#include "std_sstream.h"
#include "std_stdexcept.h"
#include "subcohort.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace fiber_bundle;
using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;
using namespace fiber_bundle::sec_vd_algebra;

// ===========================================================
// KD_LATTICE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_lattice::
kd_lattice(geometry_namespace& xns,
	   const string& xname,
	   const e3_lite& xlb,
	   const e3_lite& xub,
	   bool xlogging,
	   const string& xlogfile_dir_path)
{
  // Preconditions:


  // Body:

  // Turn off logging to start.  The logging facility will capture the
  // constructor arguments when it is turned on.

  _logging = false;

  // Set the name space.

  _name_space = &xns;

  // Create the base space.
  
  create_base_space(xname);

  // Create cohorts for the various groups 
  // of base space members; segments, lines, etc.
  
  create_cohorts();

  // Create the initial zone in the kd-tree; have to do this before
  // creating the coordinates because that requires a nonempty discretization.

  _base_space->begin_jim_edit_mode(true);
  _top_zone = new kd_zone(*this);
  _base_space->new_link(_base_space->top().index(), _top_zone->id());
  _base_space->end_jim_edit_mode(true, true);

  // Create the coordinate and splitting plane section spaces and sections.
  
  create_sections();

  // Set the vertex coordinates of the initial zone.
  
  _coords->get_read_write_access();
  _top_zone->put_coord_bounds(xlb, xub);
  _coords->release_access();

  // Set the bounding box of the initial zone.

  kd_bounding_box lbox(xlb, xub);
  put_bounding_box(_top_zone->id(), lbox);

  // Set the bounding boxes for the initial faces.

  _coords->get_read_access();

  scoped_index lf_ids[kd_zone::FACE_CT];
  _top_zone->faces(lf_ids);
  
  for(int i=0; i<kd_zone::FACE_CT; ++i)
  {
    kd_bounding_box lbox;
    kd_face::coord_bounds(*this, lf_ids[i], lbox.lb(), lbox.ub());
    put_bounding_box(lf_ids[i], lbox);
  }

  // Set the bounding boxes for the initial edges.

  scoped_index le_ids[kd_zone::EDGE_CT];
  _top_zone->edges(le_ids);
  
  for(int i=0; i<kd_zone::EDGE_CT; ++i)
  {
    kd_bounding_box lbox;
    kd_edge::coord_bounds(*this, le_ids[i], lbox.lb(), lbox.ub());
    put_bounding_box(le_ids[i], lbox);
  }
  
  _coords->release_access();

  // Set the splitting plane for the top zone to default.

  _cells_to_planes_map.reserve(1024); // Arbitrary, avoids small reallocations
  _cells_to_planes_map.set_ct(_cells_to_planes_map.ub());  
  kd_plane lp;
  put_plane(_top_zone->id(), lp);

  // Set the plane tolerance and point tolerance.

  e3_lite ldiagonal(xub);
  ldiagonal -= xlb;
  e3_lite ltolerance(ldiagonal);
  ltolerance *= 0.001;
  put_plane_tolerance(ltolerance);
  put_point_tolerance(ltolerance);
  put_truncation_tolerance(ltolerance);
  put_intersection_tolerance(ltolerance);

  // Create an unattached handle for the region of interest.

  _region_of_interest = new kd_region(*this);

  // Set default modes.

  _auto_clear_notify_sets = true;
  _auto_triangulate = true;

  // Initialize the display pointer to null;
  // will be created later if needed.

  _display = 0;
  
  put_logging(xname, xlb, xub, xlogging, xlogfile_dir_path);

  // Postconditions:

  // @todo Finish postconditions.

  ensure(base_space().name() == xname);
  ensure(bounding_box().lb() == xlb);
  ensure(bounding_box().ub() == xub);
  ensure(auto_clear_notify_sets());
  ensure(auto_triangulate());
  ensure(logging() == xlogging);
  
  // Exit:

  return;
}

geometry::kd_lattice::
~kd_lattice()
{  
  // Preconditions:

    
  // Body:

  // Delete the dipslay object.

  if(_display != 0)
  {
    delete _display;
  }

  // Region of interest.

  delete _region_of_interest;

  // Cohorts:  

  delete _leaves;
  delete _zone_leaves;
  delete _vertices;
  delete _edges;
  delete _x_edges;
  delete _y_edges;
  delete _z_edges;
  delete _faces;
  delete _x_faces;
  delete _y_faces;
  delete _z_faces;
  delete _zones;  
  delete _points;  
  delete _truncation_points;
  delete _truncation_mid_points;
  delete _truncation_reversal_points;
  delete _intersection_points;
  delete _edge_points;
  delete _centroids;
  delete _segments;
  delete _line_segments;
  delete _first_segments;
  delete _last_segments;
  delete _boundary_segments;
  delete _diagonal_segments;
  delete _truncation_segments;
  delete _lines;
  delete _line_webs;
  delete _triangles;
  delete _polygons;
  delete _surfaces;
  delete _subvolume_surfaces;
  delete _interior_triangles;
  
  // Leave base space and coordinates in name space,
  // but delete the member handles we allocated.

  _coords->detach_from_state();
  delete _coords;
  
  _active_part->detach_from_state();
  delete _active_part;
  
  delete _top_zone;
  
  // Postconditions:

  // Exit:

  return; 
}

geometry::geometry_namespace&
geometry::kd_lattice::
name_space()
{
  return *_name_space;
}

const geometry::geometry_namespace&
geometry::kd_lattice::
name_space() const
{
  return *_name_space;
}

fiber_bundle::base_space_poset&
geometry::kd_lattice::
base_space()
{
  return *_base_space;
}

const fiber_bundle::base_space_poset&
geometry::kd_lattice::
base_space() const
{
  return *_base_space;
}

fiber_bundle::base_space_member&
geometry::kd_lattice::
active_part()
{
  return *_active_part;
}

const fiber_bundle::base_space_member&
geometry::kd_lattice::
active_part() const
{
  return *_active_part;
}

fiber_bundle::sec_e3&
geometry::kd_lattice::
coords()
{
  return *_coords;
}

const fiber_bundle::sec_e3&
geometry::kd_lattice::
coords() const
{
  return *_coords;
}

void
geometry::kd_lattice::
create_active_sections()
{
  // Preconditions:

  // Body:

  if(logging())
  {
    kd_lattice_log::create_active_sections_record lrec;
    log(lrec);
  }

  // @hack Visualizer won't find segments and vertices in triangles
  // if it traverses line web first. Join triangles so we have a
  // base space member that does not include line webs.

  _active_part->get_read_write_access();
  
  subposet* lactive_down_sp = _active_part->down();
  
  subposet* lactive_triangles_sp =
    lactive_down_sp->p_intersection(&_triangles->sp());

  base_space_member lactive_triangles;

  if(lactive_triangles_sp->is_empty())
  {
    // No triangles found, make lactive_triangles same as lactive_part.

    lactive_triangles = *_active_part;
    
    cerr << "Warning: no triangles found in structure; ";
    cerr << " active_surface_coordinates will be empty" << endl;
  }
  else
  {
    // Found some triangles; join them.

    lactive_triangles_sp->l_join_pa(&lactive_triangles, true);
  }
  lactive_triangles.put_name("active_surface", false, true);

  delete lactive_triangles_sp;
  delete lactive_down_sp;
  lactive_triangles.detach_from_state();

  _active_part->release_access();

  // @hack Make sure section space schema is up to date with base space.

  update_section_space_schema();

  //   // Create the polygon_segments subposet

  //   _base_space->get_read_write_access();
  //   subposet lpolygon_segments(_base_space);
  //   _line_segments_sp->p_union_pa(_boundary_segments_sp, &lpolygon_segments);
  //   lpolygon_segments.put_name("polygon_segments", true, false);
  //   _base_space->release_access();

  //   base_space_member lpolygon_boundary;
  //   lpolygon_segments.l_join_pa(&lpolygon_boundary, true);
  //   lpolygon_boundary.put_name("polygon_boundary", true, true);

  //   base_space_member lboundary;
  //   if(_boundary_segments_sp->is_empty())
  //   {
  //     // No boundary segments found, 
  //     // make lboundary same as lactive_part.

  //     lboundary = lactive_part;
    
  //     cerr << "Warning: no boundary segments found in structure; ";
  //     cerr << " surface_boundary_line_coordinates will be empty" << endl;
  //   }
  //   else
  //   {
  //     // Found some boundary segments; join them.

  //     _boundary_segments_sp->l_join_pa(&lboundary, true);
  //   }
  //   lboundary.put_name("surface_boundary", false, true);


  //  lboundary.detach_from_state();
  //  lpolygon_boundary.detach_from_state();
  //  lpolygon_segments.detach_from_state();


  // Postconditions:

  // Exit:

  return;
}

void
geometry::kd_lattice::
write_dot(const string& xname) const
{
  // cout << endl << "Entering kd_lattice::to_dot." << endl;

  // Preconditions:

  require(!xname.empty());
  

  // Body:

  string lname(xname);
  ofstream lgv_file(lname.c_str());
  
  lgv_file << "digraph " << base_space().name() << " {" << endl;
  lgv_file << "ratio = 1.0;" << endl;

  base_space_member ltop_zone(&base_space(), _top_zone->id());
  
  zn_to_bool_linkorder_itr litr(ltop_zone, DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    lgv_file << "\t";
    lgv_file << base_space().member_name(litr.greater_index());
    lgv_file << " -> ";
    lgv_file << base_space().member_name(litr.lesser_index());
    lgv_file <<  ";";
    lgv_file << endl;
    litr.next();
  }
  
  lgv_file << "}" << endl;
    

  ltop_zone.detach_from_state();

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::to_dot." << endl;
  return;
}

void
geometry::kd_lattice::
update_section_space_schema()
{
  if(logging())
  {
    kd_lattice_log::update_section_space_schema_record lrec;
    log(lrec);
  }

  sec_at1_space* lvector_space;
  poset_path lscalar_path;
  
  // Base space has changed; force a cache update in section schema.

  // Coordinates vector section space.

  lvector_space = _coords->host();
  lvector_space->get_read_access();
  lvector_space->schema().host()->update_hub_id_space(true);
  lvector_space->schema().force_cache_update();
  lscalar_path = lvector_space->scalar_space_path();
  lvector_space->release_access();

  // Coordinates scalar section space.

  sec_at0_space& lscalar_space = _name_space->member_poset<sec_at0_space>(lscalar_path, true);
  lscalar_space.get_read_access();
  lscalar_space.schema().host()->update_hub_id_space(true);
  lscalar_space.schema().force_cache_update();
  lscalar_space.release_access();

  //   // Splitting planes section space.

  //   sec_tuple_space* lplanes_space = _cells_to_planes_map->host();
  //   lplanes_space->get_read_access();
  //   lplanes_space->schema().host()->update_top_id_space(true);
  //   lplanes_space->schema().force_cache_update();
  //   lplanes_space->release_access();

  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_lattice::
kd_lattice()
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_lattice::
kd_lattice(const kd_lattice& xother)
{
  
  // Preconditions:

    
  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}


// PRIVATE MEMBER FUNCTIONS


void
geometry::kd_lattice::
create_base_space(const string& xname)
{
  // Preconditions:


  // Body:

  // Base space with schema for kd_member.

  _base_space = &_name_space->new_base_space<kd_member>(xname, "", "", 3, true);

  // The d_cells and cells subposets are volatile
  // by default; make them persistent, the 
  // section space schema will refer to them.

  _base_space->cells().put_is_persistent(true);

  for(int i=0; i<= _base_space->max_db(); ++i)
  {
    _base_space->d_cells(i).put_is_persistent(true);
  }

  // The cohorts create an inactivation structure below a special inactive_part.
  // Create its complement - the active part.

  _active_part = new base_space_member(_base_space, "part", true, true);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_lattice::
create_cohorts()
{
  // Preconditions:

  // Body:

  base_space_poset& lbase = *_base_space;
  
  _name_space->base_space_member_prototypes_poset().get_read_access();
  lbase.begin_jim_edit_mode(true);

  // kd cohorts

  _leaves   =   new cohort(lbase, "kd_leaves", false);
  _zone_leaves   =   new cohort(lbase, "kd_zone_leaves", false);

  _vertices = new kd_vertex_cohort(*this, "kd_vertices");

  _edges    =   new cohort(lbase, "kd_edges", true);

  _x_edges = new kd_edge_cohort(*this, "kd_x_edges", X_AXIS_ALIGNED);

  _y_edges = new kd_edge_cohort(*this, "kd_y_edges", Y_AXIS_ALIGNED);

  _z_edges = new kd_edge_cohort(*this, "kd_z_edges", Z_AXIS_ALIGNED);

  _faces =   new cohort(lbase, "faces", true);

  _x_faces = new kd_face_cohort(*this, "kd_x_faces", X_AXIS_ALIGNED);

  _y_faces = new kd_face_cohort(*this, "kd_y_faces", Y_AXIS_ALIGNED);

  _z_faces = new kd_face_cohort(*this, "kd_z_faces", Z_AXIS_ALIGNED);

  _zones= new kd_zone_cohort(*this, "kd_zones");  

  // d=0 cohorts

  _points = new vertex_cohort(lbase, "points");
  
  _truncation_points= new cohort(lbase, "truncation_points", true);
  
  _truncation_mid_points= new subcohort(lbase, "truncation_mid_points", *_points);
  
  _truncation_reversal_points= new cohort(lbase, "truncation_reversal_points", true);
  
  _intersection_points= new cohort(lbase, "intersection_points", true);

  _edge_points= new cohort(lbase, "edge_points", true);

  _centroids= new subcohort(lbase, "centroids", *_points);

  // d=1 cohorts

  _segments= new d_cells_cohort(lbase, "segments", "segment");

  _line_segments= new subcohort(lbase, "line_segments", *_segments);

  _first_segments= new cohort(lbase, "first_segments", false);

  _last_segments= new cohort(lbase, "last_segments", false);

  _boundary_segments= new subcohort(lbase, "boundary_segments", *_segments);

  _diagonal_segments= new subcohort(lbase, "diagonal_segments", *_segments);

  _truncation_segments= new subcohort(lbase, "truncation_segments", *_segments);

  _lines= new jim_cohort(lbase, "lines", "part");

  _line_webs= new jim_cohort(lbase, "line_webs", "part");

  // d=2 cohorts.
  
  _triangles= new d_cells_cohort(lbase, "triangles", "triangle");

  _polygons= new d_cells_cohort(lbase, "polygons", "general_polygon");
  
  _surfaces= new jim_cohort(lbase, "surfaces", "part");

  _subvolume_surfaces = new subcohort(lbase, "subvolume_surfaces", *_surfaces);

  _interior_triangles = new cohort(lbase, "interior_triangles", false);
  
  lbase.end_jim_edit_mode(true, true);
  _name_space->base_space_member_prototypes_poset().release_access();  
  
  // Postconditions:

  // Exit

  return;
}

void
geometry::kd_lattice::
create_sections()
{
  // Preconditions:


  // Body:

  poset_path lpath;
  poset_path lbase_path;
  poset_path lrep_path;

  // Create the coordinate section space.

  lpath = "coordinates";
  lbase_path = _base_space->top().path();
  lrep_path = "sec_rep_descriptors/vertex_cells_dlinear";

  sec_at1_space& lcoord_space =  
    _name_space->new_section_space<sec_e3>(lpath, lbase_path, lrep_path, true);

  lcoord_space.get_read_write_access();

  // Create the coord section.

  _coords = new sec_e3(&lcoord_space);
  _coords->put_name("coordinates", true, false);

  // Keep a pointer to the dof map for efficient access in create_line.

  _coords_dof_map = reinterpret_cast<array_section_dof_map*>(&(_coords->dof_map(true)));

  lcoord_space.release_access();

  // Postconditions:


  // Exit:

  return;
}

// ===========================================================
// LOGGING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_lattice::
logging() const
{
  return _logging;
}

const string&
geometry::kd_lattice::
logfile_dir_path() const
{
  return _logfile_dir_path;
}

const string&
geometry::kd_lattice::
logfile_name() const
{
  return _logfile_name;
}

geometry::kd_lattice*
geometry::kd_lattice::
restart(geometry_namespace& xns,
	const string& xlogfile_path,
        bool xskip_last_record,
        bool xlogging,
        const string& xlogfile_dir_path,
        string& xerr_msg)
{
  // Preconditions:


  // Body:

  // Read the log file.

  kd_lattice_log llog;
  
  string llogfile_path(xlogfile_path);
  ifstream llogfile(llogfile_path.c_str());
  if(!llogfile)
  {
    cerr << "open failed for file " << llogfile_path << endl;
    return 0;
  }
  llogfile >> llog;
  llogfile.close();
  
  // Recreate the kd_lattice without populating it.
  
  kd_lattice* result = restart(xns,
			  llog,
			  xskip_last_record,
			  xlogging,
			  xlogfile_dir_path,
			  xerr_msg);
  
  // Postconditions:

  ensure(unexecutable("result != 0 || restart failed"));
  ensure(result != 0 ? result->logging() == xlogging : true);
  
  // Exit:

  return result;
}

geometry::kd_lattice*
geometry::kd_lattice::
restart(geometry_namespace& xns,
	const kd_lattice_log& xlog,
        bool xskip_last_record,
        bool xlogging,
        const string& xlogfile_dir_path,
        string& xerr_msg)
{
  // Preconditions:


  // Body:

  // Recreate the kd_lattice without populating it.
  
  int lnext_record;
  kd_lattice* result = recreate(xns, xlog, xlogging, xlogfile_dir_path, lnext_record);

  int lrecord_ub =
    xskip_last_record ? xlog.records().ct() - 1 : xlog.records().ct();
  if(result != 0)
  {
    // Populate the structure from the log records.
  
    for(int i=lnext_record; i<lrecord_ub; ++i)
    {
      if(!result->execute_log_record(*xlog.records()[i], xerr_msg))
      {
	// Crashed; Can't restart.

	delete result;
	result = 0 ;
	break;
      }
    }  
  }
  
  // Postconditions:

  ensure(unexecutable("result != 0 || restart failed"));
  ensure(result != 0 ? result->logging() == xlogging : true);
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
geometry::kd_lattice::
log(const string& xmessage) const
{
  // Preconditions:

  require(logging());
  require(!xmessage.empty());

  // Body:

  // In order to make sure nothing is lost on a crash, exception, etc.,
  // the file is opened before every write and then closed.

  ofstream los;
  los.open(_logfile_name.c_str(), ios::out | ios::app);
  if(los.is_open())
  {
    los << xmessage << endl;
    los.close();
  }

  // Postconditions:

  // Exit

  return;
}

void
geometry::kd_lattice::
put_logging(const string& xname,
            const e3_lite& xlb, 
	    const e3_lite& xub, 
	    bool xlogging,
	    const string& xlogfile_dir_path)
{
  // Preconditions:

  require(unexecutable("if xlogging then xlogfile_dir_path is empty or terminated with path delimiter"));

  // Body:

  _logging = xlogging;
  _logfile_dir_path = xlogfile_dir_path;

  if(_logging)
  {
    // Create a unique log file name
    // using the encoded date and time.

    time_t lnow;
    time(&lnow);

    stringstream lstr;
    lstr << "kd_lattice_" << lnow << ".log";
    
    _logfile_name = _logfile_dir_path + lstr.str();

    // Open a file with the unique log file name.
    // Add a header line.

    stringstream lstr2;
    lstr2<< endl;
    lstr2<< "Kd_lattice Log File: " << _logfile_name << endl;
    lstr2<< endl;
    log(lstr2.str());

    // Add the constructor log record.

    kd_lattice_log::constructor_record lrec (xname, 
					xlb, 
					xub);

    log(lrec);

    cout << "Created log file " << _logfile_name << endl;
  }

  // Postconditions:

  ensure(logging() == xlogging);
  
  // Exit:

  return;
}

geometry::kd_lattice*
geometry::kd_lattice::
recreate(geometry_namespace& xns,
	 const kd_lattice_log& xlog,
         bool xlogging,
         const string& xlogfile_dir_path,
         int& xnext_record)
{
  // Preconditions:


  // Body:

  kd_lattice* result = 0;
  
  for(int i=0; i<xlog.records().ct(); ++i)
  {
    kd_lattice_log::record* lrecord = xlog.records()[i];

#ifdef DIAGNOSTIC_OUTPUT
    cout << endl << *lrecord;
#endif

    xnext_record = i+1;

    if(lrecord->id == kd_lattice_log::CONSTRUCTOR)
    {
      typedef kd_lattice_log::constructor_record rec_type;
      const rec_type& lrec = reinterpret_cast<const rec_type&>(*lrecord);
      e3_lite lb;
      lb[0] = lrec.lb[0];
      lb[1] = lrec.lb[1];
      lb[2] = lrec.lb[2];
      e3_lite ub;
      ub[0] = lrec.ub[0];
      ub[1] = lrec.ub[1];
      ub[2] = lrec.ub[2];

#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::kd_lattice()" << endl;
	  cout << "  name = " << lrec.name << endl;
	  cout << "  lb = " << lb[0] << ", " << lb[1] << ",  " << lb[2] << endl;
	  cout << "  ub = " << ub[0] << ", " << ub[1] << ",  " << ub[2] << endl;
#endif
      result = new kd_lattice(xns, lrec.name, lb, ub, xlogging, xlogfile_dir_path);
      break;
    }
  }  

  // Postconditions:

  ensure((result == 0) == (xnext_record == xlog.records().ct()));
  ensure(result != 0 ? result->logging() == xlogging : true);
  
  
  // Exit:

  return result;
}

bool
geometry::kd_lattice::
execute_log_record(const kd_lattice_log::record& xrecord,
                   string& xerr_msg)
{
  // Preconditions:

  // Body:

  bool result;

  try
  {    
    result = execute_log_record_dbg(xrecord, xerr_msg);
  }
  catch(std::logic_error& lexception)
  {
    stringstream lerr_msg;
    lerr_msg << "Unable to execute log record; ";
    lerr_msg << "violated assertion: " << lexception.what();
    xerr_msg = lerr_msg.str();
    result = false;
  }
  
  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::kd_lattice::
execute_log_record_dbg(const kd_lattice_log::record& xrecord,
                       string& xerr_msg)
{
  // Preconditions:

  // Body:

  bool result = true;
  xerr_msg.clear();
  stringstream lerr_msg;

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << xrecord;
#endif

  switch(xrecord.id)
  {
    case kd_lattice_log::UPDATE_SECTION_SPACE_SCHEMA:
      {
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::update_section_space_schema()" << endl;
#endif
	update_section_space_schema();
      }
      break;
      
    case kd_lattice_log::CREATE_ACTIVE_SECTIONS:
      {
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::create_active_sections()" << endl;
#endif
	create_active_sections();
      }
      break;
      
    case kd_lattice_log::INSERT_PLANE:
      {
	typedef kd_lattice_log::insert_plane_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	kd_plane lplane;
	lplane.put(lrec.alignment, lrec.distance);
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::insert_plane()" << endl;
	cout << "  xplane = " << lplane << endl;
#endif
	insert_plane(lplane);
      }
      break;
      
    case kd_lattice_log::PUT_PLANE_TOLERANCE:
      {
	typedef kd_lattice_log::put_plane_tolerance_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	e3_lite ltolerance(lrec.tolerance[0], lrec.tolerance[1], lrec.tolerance[2]);
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::put_plane_tolerance()" << endl;
	cout << "  xtolerance = " << ltolerance << endl;
#endif
	put_plane_tolerance(ltolerance);
      }
      break;
      
    case kd_lattice_log::PUT_POINT_TOLERANCE:
      {
	typedef kd_lattice_log::put_point_tolerance_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	e3_lite ltolerance(lrec.tolerance[0], lrec.tolerance[1], lrec.tolerance[2]);
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::put_point_tolerance()" << endl;
	cout << "  xtolerance = " << ltolerance << endl;
#endif
	put_point_tolerance(ltolerance);
      }
      break;
      
    case kd_lattice_log::PUT_TRUNCATION_TOLERANCE:
      {
	typedef kd_lattice_log::put_truncation_tolerance_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	e3_lite ltolerance(lrec.tolerance[0], lrec.tolerance[1], lrec.tolerance[2]);
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::put_truncation_tolerance()" << endl;
	cout << "  xtolerance = " << ltolerance << endl;
#endif
	put_truncation_tolerance(ltolerance);
      }
      break;
      
    case kd_lattice_log::PUT_INTERSECTION_TOLERANCE:
      {
	typedef kd_lattice_log::put_intersection_tolerance_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	e3_lite ltolerance(lrec.tolerance[0], lrec.tolerance[1], lrec.tolerance[2]);
#ifdef DIAGNOSTIC_OUTPUT
	cout << "kd_lattice::put_intersection_tolerance()" << endl;
	cout << "  xtolerance = " << ltolerance << endl;
#endif
	put_intersection_tolerance(ltolerance);
      }
      break;
      
    case kd_lattice_log::FORCE_LINE:
      {
	typedef kd_lattice_log::force_line_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	pt_list lline;
	for(int i = 0; i < lrec.pt_ct; ++i)
	{
	  e3_lite lpt(lrec.x[i], lrec.y[i], lrec.z[i]);

	  lline.push_back(lpt);
	}
	
	kd_plane lplane;
	lplane.put(lrec.alignment, lrec.distance);

	lplane = equivalent_plane(lplane);
	if(!lplane.is_valid())
	{
	  cerr << "force_line_record could not find plane with alignment '"
	       << lrec.alignment << "' and distance '" << lrec.distance
	       << "'." << endl;
	  cerr << "skipping force_line." << endl;
	}
	else
	{
#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::force_line()" << endl;
	  cout << "  xline = " << endl;
	  for(pt_list::const_iterator itr = lline.begin();
	      itr != lline.end(); ++itr)
	  {
	    cout << "  " << (*itr)[0] << ", " << (*itr)[1] << ", " << (*itr)[2] << endl;
	  }
	  cout << "  xplane = " << lplane << endl;
#endif
	  force_line(lline, lplane);
	}
      }
      break;
      
    case kd_lattice_log::INSERT_LINE:
      {
	typedef kd_lattice_log::insert_line_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	pt_list lline;
	for(int i = 0; i < lrec.pt_ct; ++i)
	{
	  e3_lite lpt(lrec.x[i], lrec.y[i], lrec.z[i]);

	  lline.push_back(lpt);
	}
	
	kd_plane lplane;
	lplane.put(lrec.alignment, lrec.distance);

	lplane = equivalent_plane(lplane);
	if(!lplane.is_valid())
	{
	  cerr << "insert_line_record could not find plane with alignment '"
	       << lrec.alignment << "' and distance '" << lrec.distance
	       << "'." << endl;
	  cerr << "skipping insert_line." << endl;
	}
	else
	{
#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::insert_line()" << endl;
	  cout << "  xline = " << endl;
	  for(pt_list::const_iterator itr = lline.begin();
	      itr != lline.end(); ++itr)
	  {
	    cout << "  " << (*itr)[0] << ", " << (*itr)[1] << ", " << (*itr)[2] << endl;
	  }
	  cout << "  xplane = " << lplane << endl;
#endif
	  insert_line(lline, lplane);
	}
      }
      break;
      
    case kd_lattice_log::REMOVE_LINE:
      {
	typedef kd_lattice_log::remove_line_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	if(!lines().contains(lrec.hub_id))
	{
	  cerr << "remove_line: could not find line with id '" << lrec.hub_id << "'." << endl;
	  cerr << "skipping remove_line." << endl;
	}
	else
	{
#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::remove_line()" << endl;
	  cout << "  xhub_id = " << lrec.hub_id << endl;
#endif
	  remove_line(base_space().member_id(lrec.hub_id, true));
	}
      }
      break;
      
    case kd_lattice_log::PUT_AUTO_TRIANGULATE:
      {
	typedef kd_lattice_log::put_auto_triangulate_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::put_auto_triangulate()" << endl;
	  cout << "  xvalue = " << lrec.value << endl;
#endif
	put_auto_triangulate(lrec.value);
      }
      break;
      
    case kd_lattice_log::RETRIANGULATE:
      {
#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::retriangulate()" << endl;
#endif
	retriangulate();
      }
      break;
      
    case kd_lattice_log::INSERT_REGION:
      {
	typedef kd_lattice_log::insert_region_record rec_type;
	const rec_type& lrec = reinterpret_cast<const rec_type&>(xrecord);
	e3_lite lb(lrec.lb[0], lrec.lb[1], lrec.lb[2]);
	e3_lite ub(lrec.ub[0], lrec.ub[1], lrec.ub[2]);

#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::insert_region()" << endl;
	  cout << "  lb = " << lb[0] << ", " << lb[1] << ",  " << lb[2] << endl;
	  cout << "  ub = " << ub[0] << ", " << ub[1] << ",  " << ub[2] << endl;
#endif
	  insert_region(lb, ub);
      }
      break;

    case kd_lattice_log::EXTRACT_SUBVOLUME_SURFACES:
      {
#ifdef DIAGNOSTIC_OUTPUT
	  cout << "kd_lattice::extract_subvolume_surfaces()" << endl;
#endif
	  extract_subvolume_surfaces();
      }
      break;
      
    default:
      lerr_msg << "Ignored record of type: " << xrecord.id << endl;
      xerr_msg = lerr_msg.str();
      break;
  }
  
  // Postconditions:


  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// DISPLAY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


double&
geometry::kd_lattice::
display_expansion_factor()
{
  // cout << endl << "Entering kd_lattice::display_expansion_factor." << endl;

  // Preconditions:


  // Body:

  static double result = 1.0;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display_expansion_factor." << endl;
  return result;
}


bool&
geometry::kd_lattice::
display_insert_plane()
{
  // cout << endl << "Entering kd_lattice::display_insert_plane." << endl;

  // Preconditions:


  // Body:

  static bool result = false;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display_insert_plane." << endl;
  return result;
}

bool&
geometry::kd_lattice::
display_insert_line()
{
  // cout << endl << "Entering kd_lattice::display_insert_line." << endl;

  // Preconditions:


  // Body:

  static bool result = false;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display_insert_line." << endl;
  return result;
}

bool&
geometry::kd_lattice::
display_untriangulated_insert_line()
{
  // cout << endl << "Entering kd_lattice::display_untriangulated_insert_line." << endl;

  // Preconditions:


  // Body:

  static bool result = false;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display_untriangulated_insert_line." << endl;
  return result;
}

bool&
geometry::kd_lattice::
display_remove_line()
{
  // cout << endl << "Entering kd_lattice::display_remove_line." << endl;

  // Preconditions:


  // Body:

  static bool result = false;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display_remove_line." << endl;
  return result;
}

void
geometry::kd_lattice::
display(bool xexploded, bool xpt_labels)
{
  // cout << endl << "Entering kd_lattice::display." << endl;

  // Preconditions:


  // Body:

#ifdef USE_VTK

  if(_display == 0)
  {
    _display = new kd_display;
  }

  _display->display_point_labels = xpt_labels;
  _display->display(*this, xexploded);

#endif

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display." << endl;
  return;
}

void
geometry::kd_lattice::
display_subvolumes(bool xexploded, bool xpt_labels)
{
  // cout << endl << "Entering kd_lattice::display." << endl;

  // Preconditions:


  // Body:

#ifdef USE_VTK

  if(_display == 0)
  {
    _display = new kd_display;
  }

  _display->display_point_labels = xpt_labels;
  _display->display_subvolumes(*this, xexploded);

#endif

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::display." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// NOTIFICATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
geometry::kd_lattice::
clear_notify_sets()
{
  // cout << endl << "Entering kd_lattice::clear_notify_sets." << endl;

  // Preconditions:


  // Body:

  _deleted_points.clear();
  _modified_points.clear();
  _new_points.clear();

  _deleted_lines.clear();
  _modified_lines.clear();
  _new_lines.clear();

  _deleted_surfaces.clear();
  _modified_surfaces.clear();
  _new_surfaces.clear();

  // Postconditions:

  ensure(deleted_points().empty());
  ensure(modified_points().empty());
  ensure(new_points().empty());

  ensure(deleted_lines().empty());
  ensure(modified_lines().empty());
  ensure(new_lines().empty());

  ensure(deleted_surfaces().empty());
  ensure(modified_surfaces().empty());
  ensure(new_surfaces().empty());

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::clear_notify_sets." << endl;
  return;
}

bool
geometry::kd_lattice::
auto_clear_notify_sets() const
{
  return _auto_clear_notify_sets;
}

void
geometry::kd_lattice::
put_auto_clear_notify_sets(bool xval)
{
  // cout << endl << "Entering kd_lattice::put_auto_clear_notify_sets." << endl;

  // Preconditions:


  // Body:

  _auto_clear_notify_sets = xval;
  

  // Postconditions:

  ensure(auto_clear_notify_sets() == xval);

  // Exit:

  // cout << "Leaving kd_lattice::put_auto_clear_notify_sets." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// KD_VERTEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


geometry::vertex_cohort&
geometry::kd_lattice::
vertices()
{
  return *_vertices;
}

const geometry::vertex_cohort&
geometry::kd_lattice::
vertices() const
{
  return *_vertices;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
 
// ===========================================================
// KD_EDGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
edges()
{
  return *_edges;
}

const geometry::cohort&
geometry::kd_lattice::
edges() const
{
  return *_edges;
}

geometry::kd_edge_cohort&
geometry::kd_lattice::
x_edges()
{
  return *_x_edges;
}

const geometry::kd_edge_cohort&
geometry::kd_lattice::
x_edges() const
{
  return *_x_edges;
}

geometry::kd_edge_cohort&
geometry::kd_lattice::
y_edges()
{
  return *_y_edges;
}

const geometry::kd_edge_cohort&
geometry::kd_lattice::
y_edges() const
{
  return *_y_edges;
}

geometry::kd_edge_cohort&
geometry::kd_lattice::
z_edges()
{
  return *_z_edges;
}

const geometry::kd_edge_cohort&
geometry::kd_lattice::
z_edges() const
{
  return *_z_edges;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
// KD_FACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
faces()
{
  return *_faces;
}

const geometry::cohort&
geometry::kd_lattice::
faces() const
{
  return *_faces;
}

geometry::kd_face_cohort&
geometry::kd_lattice::
x_faces()
{
  return *_x_faces;
}

const geometry::kd_face_cohort&
geometry::kd_lattice::
x_faces() const
{
  return *_x_faces;
}

geometry::kd_face_cohort&
geometry::kd_lattice::
y_faces()
{
  return *_y_faces;
}

const geometry::kd_face_cohort&
geometry::kd_lattice::
y_faces() const
{
  return *_y_faces;
}

geometry::kd_face_cohort&
geometry::kd_lattice::
z_faces()
{
  return *_z_faces;
}

const geometry::kd_face_cohort&
geometry::kd_lattice::
z_faces() const
{
  return *_z_faces;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
// KD_ZONE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_zone_cohort&
geometry::kd_lattice::
zones()
{
  return *_zones;
}

const geometry::kd_zone_cohort&
geometry::kd_lattice::
zones() const
{
  return *_zones;
}

geometry::kd_zone&
geometry::kd_lattice::
top_zone()
{
  return *_top_zone;
}

const geometry::kd_zone&
geometry::kd_lattice::
top_zone() const
{
  return *_top_zone;
}

const geometry::pod_id_hash_set&
geometry::kd_lattice::
cleared_zones() const
{
  return _cleared_zones;
}

geometry::pod_id_hash_set&
geometry::kd_lattice::
cleared_zones()
{
  return _cleared_zones;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// KD_LEAF FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
leaves()
{
  return *_leaves;
}

const geometry::cohort&
geometry::kd_lattice::
leaves() const
{
  return *_leaves;
}

geometry::cohort&
geometry::kd_lattice::
zone_leaves()
{
  return *_zone_leaves;
}

const geometry::cohort&
geometry::kd_lattice::
zone_leaves() const
{
  return *_zone_leaves;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
// KD_PLANE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_lattice::
contains_plane(const kd_plane& xp) const
{
  // cout << endl << "Entering kd_lattice::contains_plane." << endl;

  // Preconditions:


  // Body:

  bool result = (_planes.find(xp) != _planes.end());

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::contains_plane." << endl;
  return result;
}

bool
geometry::kd_lattice::
contains_equivalent_plane(const kd_plane& xp) const
{
  // cout << endl << "Entering kd_lattice::contains_plane." << endl;

  // Preconditions:


  // Body:

  bool result = (equivalent_plane(xp).is_valid());
  
  // Postconditions:

  ensure(result == (equivalent_plane(xp).is_valid()));

  // Exit:

  // cout << "Leaving kd_lattice::contains_plane." << endl;
  return result;
}

geometry::kd_plane
geometry::kd_lattice::
equivalent_plane(const kd_plane& xp) const
{
  // cout << endl << "Entering kd_lattice::equivalent_plane." << endl;

  // Preconditions:

  require(xp.is_valid());
  
  // Body:

  kd_plane result; // Invalid by default.

  set<kd_plane>::const_iterator litr = _planes.lower_bound(xp);

  if(litr != _planes.end())
  {
    // Found an entry that is not less than xp;
    // check the entry for equivalence..

    if(a_eql(xp, *litr, _plane_tolerance))
    {
      result = *litr;
    }
  }

  if(!result.is_valid() && (litr != _planes.begin()))
  {
    // Preceeding entry might be equivalent; check it.

    --litr;
    
    if(a_eql(xp, *litr, _plane_tolerance))
    {
      result = *litr;
    }
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::equivalent_plane." << endl;
  return result;
}

geometry::kd_plane
geometry::kd_lattice::
get_equivalent_plane(kd_alignment xalign, vd_value_type xdist) const
{
  // cout << endl << "Entering kd_lattice::get_equivalent_plane." << endl;

  // Preconditions:

  // Body:

  kd_plane result(xalign, xdist); // Invalid by default.

  kd_plane lp_eqv(equivalent_plane(result));
  if(lp_eqv.is_valid())
  {
    result = lp_eqv;
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::get_equivalent_plane." << endl;
  return result;
}

const geometry::kd_plane&
geometry::kd_lattice::
plane(const scoped_index& xid) const
{
  // cout << endl << "Entering kd_lattice::plane." << endl;

  // Preconditions:
  
  require(base_space().contains_member(xid));
  
  // Body:

  const kd_plane& result = _cells_to_planes_map[xid.hub_pod()];

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::plane." << endl;
  return result;
}

void
geometry::kd_lattice::
put_plane(const scoped_index& xid, const kd_plane& xp)
{
  // cout << endl << "Entering kd_lattice::put_plane." << endl;

  // Preconditions:
  
  require(base_space().contains_member(xid));
  require(!contains_plane(xp));
  
  // Body:

  _cells_to_planes_map.force_item(xid.hub_pod(), xp);

  // Postconditions:

  ensure(plane(xid) == xp);
  
  // Exit:

  // cout << "Leaving kd_lattice::put_plane." << endl;
  return;
}


void
geometry::kd_lattice::
insert_plane(const kd_plane& xp)
{
  // cout << endl << "Entering kd_lattice::insert_plane." << endl;
  
  // Preconditions:

  require(xp.is_valid());
  require(!contains_equivalent_plane(xp));
  
  // Body:

  if(logging())
  {
    kd_lattice_log::insert_plane_record lrec(xp);
    log(lrec);
  }

  if(auto_clear_notify_sets())
  {
    clear_notify_sets();
  }

  _base_space->begin_jim_edit_mode(true);
  _coords->get_read_write_access();

  // Remove existing triangles from the zones
  // intersected by the plane.

  hash_set<pod_index_type> ldeleted;
  _top_zone->clear_contents(xp, ldeleted);

  // Clear_contents leaves the deleted triangles in the lower cover of
  // the surfaces containing them because it is too inefficient to delete
  // them one at a time. Instead it marks the surfaces as modified and
  // returns the set of deleted ids so we can delete them all at once here.

  // $$SCRIBBLE: this process and the subsequent update
  // of the surfaces in kd_lattice::insert_line and here
  // can be made more efficeint by grouping the triangles 
  // by surface in the lower cover of the zone and inserting 
  // the jrm in the lower cover of the surface. See also
  // kd_zone::clear_contents.

  // cout << "ldeleted: " << ldeleted << endl;

  hash_set_filter lfilter(ldeleted);
  for(id_set::iterator s=modified_surfaces().begin(); s!=modified_surfaces().end(); ++s)
  {
    // cout << "removing triangles for lower cover of surface: " << _base_space->member_name(*s) << endl;
    // cout << "before: " << _base_space->cover_iterator(LOWER, *s) << endl;
      
    _base_space->remove_cover_members(lfilter, LOWER, *s);

    // cout << "after: " << _base_space->cover_iterator(LOWER, *s) << endl;
  }
  

  _top_zone->insert_plane(xp);

  _planes.insert(xp);
  
  _coords->release_access();
  _base_space->end_jim_edit_mode(false, true);

  
  if(display_insert_plane())
  {
    display(true, true);
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::insert_plane." << endl << endl;
  return;
}

void
geometry::kd_lattice::
remove_plane(const scoped_index& xid)
{
  // Preconditions:


  // Body:

  if(auto_clear_notify_sets())
  {
    clear_notify_sets();
  }

  not_implemented();

  // Postconditions:


  // Exit:

  return;
}

const fiber_bundle::e3_lite&
geometry::kd_lattice::
plane_tolerance() const
{
  return _plane_tolerance;
}

void
geometry::kd_lattice::
put_plane_tolerance(const e3_lite& xtolerance)
{
  // cout << endl << "Entering kd_lattice::put_plane_tolerance." << endl;

  // Preconditions:


  // Body:

  if(logging())
  {
    kd_lattice_log::put_plane_tolerance_record lrec(xtolerance);
    log(lrec);
  }

  _plane_tolerance[0] = abs(xtolerance[0]);
  _plane_tolerance[1] = abs(xtolerance[1]);
  _plane_tolerance[2] = abs(xtolerance[2]);

  // Postconditions:

  ensure(plane_tolerance()[0] == abs(xtolerance[0]));
  ensure(plane_tolerance()[1] == abs(xtolerance[1]));
  ensure(plane_tolerance()[2] == abs(xtolerance[2]));

  // Exit:

  // cout << "Leaving kd_lattice::put_plane_tolerance." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// KD_BOUNDING_BOX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const geometry::kd_bounding_box&
geometry::kd_lattice::
bounding_box() const
{
  return bounding_box(_top_zone->id());
}

geometry::kd_bounding_box&
geometry::kd_lattice::
bounding_box(const scoped_index& xid)
{
  // cout << endl << "Entering kd_lattice::bounding_box." << endl;

  // Preconditions:
  
  require(base_space().contains_member(xid));
  require(unexecutable("xid refers to a tree cell"));
  
  // Body:

  kd_bounding_box& result = _cells_to_bounding_boxes_map[xid.hub_pod()];

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::bounding_box." << endl;
  return result;
}

const geometry::kd_bounding_box&
geometry::kd_lattice::
bounding_box(const scoped_index& xid) const
{
  // cout << endl << "Entering kd_lattice::bounding_box." << endl;

  // Preconditions:
  
  require(base_space().contains_member(xid));
  require(unexecutable("xid refers to a tree cell"));
  
  // Body:

  const kd_bounding_box& result = _cells_to_bounding_boxes_map[xid.hub_pod()];

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::bounding_box." << endl;
  return result;
}

void
geometry::kd_lattice::
put_bounding_box(const scoped_index& xid, const kd_bounding_box& xb)
{
  // cout << endl << "Entering kd_lattice::put_bounding_box." << endl;

  // Preconditions:
  
  require(base_space().contains_member(xid));
  
  // Body:

  _cells_to_bounding_boxes_map.force_item(xid.hub_pod(), xb);

  // Postconditions:

  ensure(bounding_box(xid) == xb);
  
  // Exit:

  // cout << "Leaving kd_lattice::put_bounding_box." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
  
// ===========================================================
// POINT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::vertex_cohort&
geometry::kd_lattice::
points()
{
  return *_points;
}

const geometry::vertex_cohort&
geometry::kd_lattice::
points() const
{
  return *_points;
}

void
geometry::kd_lattice::
points(const scoped_index& xid, id_list& xpoints) const
{
  // cout << endl << "Entering kd_lattice::points." << endl;

  // Preconditions:

  require(base_space().state_is_read_accessible());

  // Body:

  base_space_member lanchor(_base_space, xid);

  hash_set_postorder_itr litr(lanchor, "points", DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xpoints.push_back(litr.index());
    litr.next();
  }

  lanchor.detach_from_state();
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::points." << endl;
  return;
}

scoped_index
geometry::kd_lattice::
locate_point(const e3_lite& xpt, int xd)
{
  // cout << endl << "Entering kd_lattice::locate_point." << endl;

  // Preconditions:


  // Body:

  _coords->get_read_access();

  scoped_index result;

  const kd_bounding_box& lbox = bounding_box();

  if(lbox.out_code_3d(xpt) == kd_bounding_box::INSIDE_3D)
  {
    // Point in either on the boundary or in the interior.

    int lcode = lbox.in_code_3d(xpt);
    
    if(lcode == kd_bounding_box::STRICT_INSIDE_3D)
    {
      // Find it in the interior

      result = _top_zone->locate_point(xpt, xd);
    }
    else
    {
      // Find it in the boundary.

      int llocal_cell_id, ld;
      kd_bounding_box::local_cell_id(lcode, llocal_cell_id, ld);
      switch(ld)
      {
        case 0:
          result = _top_zone->vertex(llocal_cell_id);
          break;
        case 1:
          result = _top_zone->edge(llocal_cell_id);
          break;
        case 2:
          result = _top_zone->face(llocal_cell_id);
          break;
        default:
          // Should be unreachable, but if not, do nothing; 
          // result is invalid by default.
          break;
      }
    }
  }
  else
  {
    // Point is outside the domain;
    // do nothing, result is invalid by default.
  }
    

  _coords->release_access();

  // Postconditions:

  ensure(!result.is_valid() || cell_contains_point(result, xpt));

  // Exit:

  // cout << "Leaving kd_lattice::locate_point." << endl;
  return result;
}

void
geometry::kd_lattice::
find_face_leaf(const kd_plane& xp, const pt_list& xline, scoped_index& xresult) const
{
  // cout << endl << "Entering kd_lattice::find_face_leaf." << endl;

  // Preconditions:

  require(xp.contains_line(xline));
  
  // Body:

  _coords->get_read_access();

  const kd_bounding_box& lbox = bounding_box();

  // Initial point is either on the boundary or in the interior.

  int lcode = lbox.in_code_3d(xline.front());
    
  if(lcode == kd_bounding_box::STRICT_INSIDE_3D)
  {
    // The intial point is in the interior, find it.

    _top_zone->find_face_leaf(xp, xline, xresult);
  }
  else
  {
    //  Find the initial point in the boundary.

    int lface_id = kd_bounding_box::local_face_id(lcode);
    xresult = _top_zone->face(lface_id);
    kd_face::leaf(*this, xresult, xline, xresult);
  }

  _coords->release_access();

  // Postconditions:

  ensure(cell_contains_point(xresult, xline.front()));

  // Exit:

  // cout << "Leaving kd_lattice::find_face_leaf." << endl;
  return;
}

void
geometry::kd_lattice::
find_face_leaves(const kd_plane& xp, id_list& xresult) const
{
  // cout << endl << "Entering kd_lattice::find_face_leaves." << endl;

  // Preconditions:

  require(contains_plane(xp));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  _coords->get_read_access();

  // First look in the boundary.

  scoped_index lface_ids[kd_zone::FACE_CT];
  _top_zone->faces(lface_ids);
  
  bool lfound = false;
  for(int i=0; i<kd_zone::FACE_CT; ++i)
  {
    if(kd_face::in_plane(*this, lface_ids[i], xp))
    {
      kd_face::leaves(*this, lface_ids[i], xresult);
      lfound = true;
    }
  }
  
  if(!lfound)
  {
    // Plane wasn't in the boundary,
    // look in the interior.

    _top_zone->find_face_leaves(xp, xresult);
  }

  _coords->release_access();

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_lattice::find_face_leaves." << endl;
  return;
}

void
geometry::kd_lattice::
find_face_leaves(const kd_bounding_box& xb, const kd_plane& xp, id_list& xresult) const
{
  // cout << endl << "Entering kd_lattice::find_face_leaves." << endl;

  // Preconditions:

  require(contains_plane(xp));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  // $$SCRIBBLE reimplement so find_face_leaves(xp, xresult) calls
  // this function and tree traversal doesn't go outside bounding box.

  find_face_leaves(xp, xresult);
  
  for(id_list::iterator lf = xresult.begin(); lf != xresult.end(); )
  {
    if(!xb.contains(bounding_box(*lf)))
    {
      xresult.erase(lf++);
    }
    else
    {
      ++lf;
    }
  }
    
  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_lattice::find_face_leaves." << endl;
  return;
}

const fiber_bundle::e3_lite&
geometry::kd_lattice::
point_tolerance() const
{
  return _point_tolerance;
}

void
geometry::kd_lattice::
put_point_tolerance(const e3_lite& xtolerance)
{
  // cout << endl << "Entering kd_lattice::put_point_tolerance." << endl;

  // Preconditions:


  // Body:

  if(logging())
  {
    kd_lattice_log::put_point_tolerance_record lrec(xtolerance);
    log(lrec);
  }

  _point_tolerance[0] = abs(xtolerance[0]);
  _point_tolerance[1] = abs(xtolerance[1]);
  _point_tolerance[2] = abs(xtolerance[2]);

  // Postconditions:

  ensure(point_tolerance()[0] == abs(xtolerance[0]));
  ensure(point_tolerance()[1] == abs(xtolerance[1]));
  ensure(point_tolerance()[2] == abs(xtolerance[2]));

  // Exit:

  // cout << "Leaving kd_lattice::put_point_tolerance." << endl;
  return;
}

bool
geometry::kd_lattice::
contains_point(const e3_lite& xpt) const
{
  return bounding_box().contains_point(xpt);
}

bool
geometry::kd_lattice::
interior_contains_point(const e3_lite& xpt) const
{
  return bounding_box().interior_contains_point(xpt);
}

bool
geometry::kd_lattice::
boundary_contains_point(const e3_lite& xpt) const
{
  return bounding_box().boundary_contains_point(xpt);
}

bool
geometry::kd_lattice::
cell_contains_point(const scoped_index& xid, const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_lattice::cell_contains_point." << endl;

  // Preconditions:


  // Body:

  _coords->get_read_access();
  
  bool result = false;
  if(_zones->contains(xid))
  {
    result = kd_zone::contains_point(*this, xid, xpt);
  }
  else if(_faces->contains(xid))
  {
    result = kd_face::contains_point(*this, xid, xpt);
  }
  else if(_edges->contains(xid))
  {
    result = kd_edge::contains_point(*this, xid, xpt);
  }
  else if(_vertices->contains(xid))
  {
    result = kd_vertex::contains_point(*this, xid, xpt);
  }

  _coords->release_access();
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::cell_contains_point." << endl;
  return result;
}

geometry::id_set&
geometry::kd_lattice::
new_points()
{
  return _new_points;
}

const geometry::id_set&
geometry::kd_lattice::
new_points() const
{
  return _new_points;
}

geometry::id_set&
geometry::kd_lattice::
modified_points()
{
  return _modified_points;
}

const geometry::id_set&
geometry::kd_lattice::
modified_points() const
{
  return _modified_points;
}

geometry::id_set&
geometry::kd_lattice::
deleted_points()
{
  return _deleted_points;
}

const geometry::id_set&
geometry::kd_lattice::
deleted_points() const
{
  return _deleted_points;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// TRUNCATION_POINTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
truncation_points()
{
  return *_truncation_points;
}

const geometry::cohort&
geometry::kd_lattice::
truncation_points() const
{
  return *_truncation_points;
}

const fiber_bundle::e3_lite&
geometry::kd_lattice::
truncation_tolerance() const
{
  return _truncation_tolerance;
}

void
geometry::kd_lattice::
put_truncation_tolerance(const e3_lite& xtolerance)
{
  // cout << endl << "Entering kd_lattice::put_truncation_tolerance." << endl;

  // Preconditions:


  // Body:

  if(logging())
  {
    kd_lattice_log::put_truncation_tolerance_record lrec(xtolerance);
    log(lrec);
  }

  _truncation_tolerance[0] = abs(xtolerance[0]);
  _truncation_tolerance[1] = abs(xtolerance[1]);
  _truncation_tolerance[2] = abs(xtolerance[2]);

  // Postconditions:

  ensure(truncation_tolerance()[0] == abs(xtolerance[0]));
  ensure(truncation_tolerance()[1] == abs(xtolerance[1]));
  ensure(truncation_tolerance()[2] == abs(xtolerance[2]));

  // Exit:

  // cout << "Leaving kd_lattice::put_point_tolerance." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// TRUNCATION_REVERSAL_POINTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
truncation_mid_points()
{
  return *_truncation_mid_points;
}

const geometry::subcohort&
geometry::kd_lattice::
truncation_mid_points() const
{
  return *_truncation_mid_points;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// TRUNCATION_REVERSAL_POINTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
truncation_reversal_points()
{
  return *_truncation_reversal_points;
}

const geometry::cohort&
geometry::kd_lattice::
truncation_reversal_points() const
{
  return *_truncation_reversal_points;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// INTERSECTION_POINTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
intersection_points()
{
  return *_intersection_points;
}

const geometry::cohort&
geometry::kd_lattice::
intersection_points() const
{
  return *_intersection_points;
}

const fiber_bundle::e3_lite&
geometry::kd_lattice::
intersection_tolerance() const
{
  return _intersection_tolerance;
}

void
geometry::kd_lattice::
put_intersection_tolerance(const e3_lite& xtolerance)
{
  // cout << endl << "Entering kd_lattice::put_intersection_tolerance." << endl;

  // Preconditions:


  // Body:

  if(logging())
  {
    kd_lattice_log::put_intersection_tolerance_record lrec(xtolerance);
    log(lrec);
  }

  _intersection_tolerance[0] = abs(xtolerance[0]);
  _intersection_tolerance[1] = abs(xtolerance[1]);
  _intersection_tolerance[2] = abs(xtolerance[2]);

  // Postconditions:

  ensure(intersection_tolerance()[0] == abs(xtolerance[0]));
  ensure(intersection_tolerance()[1] == abs(xtolerance[1]));
  ensure(intersection_tolerance()[2] == abs(xtolerance[2]));

  // Exit:

  // cout << "Leaving kd_lattice::put_point_tolerance." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


 
// ===========================================================
// EDGE_POINTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
edge_points()
{
  return *_edge_points;
}

const geometry::cohort&
geometry::kd_lattice::
edge_points() const
{
  return *_edge_points;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// CENTROID FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
centroids()
{
  return *_centroids;
}

const geometry::subcohort&
geometry::kd_lattice::
centroids() const
{
  return *_centroids;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// SEGMENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::d_cells_cohort&
geometry::kd_lattice::
segments()
{
  return *_segments;
}

const geometry::d_cells_cohort&
geometry::kd_lattice::
segments() const
{
  return *_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// LINE_SEGMENTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
line_segments()
{
  return *_line_segments;
}

const geometry::subcohort&
geometry::kd_lattice::
line_segments() const
{
  return *_line_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
 
// ===========================================================
// FIRST_SEGMENTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
first_segments()
{
  return *_first_segments;
}

const geometry::cohort&
geometry::kd_lattice::
first_segments() const
{
  return *_first_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
 
// ===========================================================
// LAST_SEGMENTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort&
geometry::kd_lattice::
last_segments()
{
  return *_last_segments;
}

const geometry::cohort&
geometry::kd_lattice::
last_segments() const
{
  return *_last_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
 
// ===========================================================
// BOUNDARY_SEGMENTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
boundary_segments()
{
  return *_boundary_segments;
}

const geometry::subcohort&
geometry::kd_lattice::
boundary_segments() const
{
  return *_boundary_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
 
// ===========================================================
// DIAGONAL_SEGMENTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
diagonal_segments()
{
  return *_diagonal_segments;
}

const geometry::subcohort&
geometry::kd_lattice::
diagonal_segments() const
{
  return *_diagonal_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
 
// ===========================================================
// TRUNCATION_SEGMENTS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
truncation_segments()
{
  return *_truncation_segments;
}

const geometry::subcohort&
geometry::kd_lattice::
truncation_segments() const
{
  return *_truncation_segments;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// LINE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::jim_cohort&
geometry::kd_lattice::
lines()
{
  return *_lines;
}

const geometry::jim_cohort&
geometry::kd_lattice::
lines() const
{
  return *_lines;
}

void
geometry::kd_lattice::
force_line(pt_list& xline, const kd_plane& xp)
{
  // cout << endl << "Entering kd_lattice::force_line." << endl;

  // Preconditions:

  require(xp.is_valid());
  
  // Body:

  if(logging())
  {
    kd_lattice_log::force_line_record lrec(xline, xp);
    log(lrec);
  }

  int lc = xp.int_alignment();
  
  for(pt_list::iterator p=xline.begin(); p!=xline.end(); ++p)
  {
    (*p)[lc] = xp.distance();
  }
  
  // Postconditions:

  ensure(xline.empty() || xp.contains_line(xline));

  // Exit:

  // cout << "Leaving kd_lattice::force_line." << endl << endl;
  return;
}

scoped_index
geometry::kd_lattice::
insert_line(pt_list& xline, const kd_plane& xp)
{
  // cout << endl << "Entering kd_lattice::insert_line." << endl;
  // cout << "plane: " << xp << endl;
  // cout << "line: " << xline << endl;
  
  // Preconditions:

  require(contains_equivalent_plane(xp));
  require(!xline.empty());
  require(xp.contains_line(xline));
  require(bounding_box().contains_line(xline));
  
  // Body:

  if(logging())
  {
    kd_lattice_log::insert_line_record lrec(xline, xp);
    log(lrec);
  }

  if(auto_clear_notify_sets())
  {
    clear_notify_sets();
  }

  // Convert the line input to a kd_face::line_list.

  kd_face::line_list lline(xline.begin(), xline.end());

  _base_space->begin_jim_edit_mode(true);
  _coords->get_read_write_access();

  // Find the face leaf containing the first point.

  scoped_index lface_id;
  find_face_leaf(xp, xline, lface_id);

  // Insert the first point.

  lline.front().pt_id  = kd_face::insert_point(*this, lface_id, lline.front().pt);

  // Check for closed line.

  if(fiber_bundle::vd_algebra::a_eql(lline.front().pt, lline.back().pt, _intersection_tolerance))
  {
    // First and last point are the same, within tolerance.
    // Make them identical.

    // cout << "First and last point are the same; line is closed." << endl;

    lline.back().pt = lline.front().pt;
    lline.back().pt_id = lline.front().pt_id;
  }  

  id_list lline_mbrs;  
  lline_mbrs.push_back(lline.front().pt_id);

  // Insert the rest of the line.
  // Use a set to store face ids to avoid duplicates.

  id_set lface_ids;
  while(lface_id.is_valid())
  {
    lface_ids.insert(lface_id);
    lface_id = kd_face::insert_line(*this, lface_id, lline, lline_mbrs);
  }

  // cout << "inserted line: " << lline_mbrs << endl;
  
  // Create the line member.
  
  scoped_index result;
  kd_line::new_line(*this, lline_mbrs, result);

  // Find the surfaces the line connects to.

  id_set lsurfs;
  kd_line::surfaces(*this, result, lsurfs);
  
  scoped_index lsurf_id;
  if(!lsurfs.empty())
  {
    // Line intersected lines of other surfaces,
    // connects surfaces into a single surface.

    kd_surface::merge(*this, lsurfs);
    lsurf_id = *lsurfs.begin();  

    // Put the line in the surface.

    kd_surface::insert_line(*this, lsurf_id, result);
    
    // Surface has multiple lines, re-triangulate the 
    // zones bounding the faces the line was inserted in.

    id_list lzone_ids;
    pod_id_hash_set ldeleted;

    // First clear out all the existing triangles.
    // Deleting one triangle at a time from the lower cover
    // of the surface results in O(total_triangle_Ct*deleted_triangle_ct)
    // performance, so we have to accumulate deleted triangles in a filter
    // and remove them in a single pass. Have to do this all before
    // we create any new triangles, otherwise triangle member reactivation
    // will conflict with deletion.

    for(id_set::iterator i = lface_ids.begin(); i != lface_ids.end(); ++i)
    {
      lzone_ids.clear();
      kd_face::zones(*this, *i, lzone_ids);
      for(id_list::iterator j = lzone_ids.begin(); j != lzone_ids.end(); ++j)
      {
        kd_zone::clear_contents(*this, *j, ldeleted);
      }
    }

    // Clear_contents leaves the deleted triangles in the lower cover of
    // the surfaces containing them because it is too inefficient to delete
    // them one at a time. Instead it marks the surfaces as modified and
    // returns the set of deleted ids so we can delete them all at once here.

    // $$SCRIBBLE: this process and the subsequent update
    // of the surfaces in kd_lattice::insert_line and here
    // can be made more efficeint by grouping the triangles 
    // by surface in the lower cover of the zone and inserting 
    // the jrm in the lower cover of the surface. See also
    // kd_zone::clear_contents.

    // cout << "ldeleted: " << ldeleted << endl;

    hash_set_filter lfilter(ldeleted);
    for(id_set::iterator s=modified_surfaces().begin(); s!=modified_surfaces().end(); ++s)
    {
      // cout << "removing triangles for lower cover of surface: " << _base_space->member_name(*s) << endl;
      // cout << "before: " << _base_space->cover_iterator(LOWER, *s) << endl;
      
      _base_space->remove_cover_members(lfilter, LOWER, *s);

      // cout << "after: " << _base_space->cover_iterator(LOWER, *s) << endl;
    }

    if(display_untriangulated_insert_line())
    {
      display(false, true);
    }

    if(_auto_triangulate)
    {
      // Retriangulate the zones.

      retriangulate_cleared_zones();
    }    
  }
  else
  {
    // Didn't connect to any existing surfaces;
    // create one for it.

    kd_surface::new_surface(*this, lsurf_id);

    // Link the surface to the active part.

    _base_space->new_link(_active_part->index(), lsurf_id);

    // Put the line in the surface.

    kd_surface::insert_line(*this, lsurf_id, result);

    // Surface contains a single line, can't be triangulated.

    // cout << "Surface contains a single line, can't be triangulated." << endl;
  }

  // We're done.

  _coords->release_access();
  _base_space->end_jim_edit_mode(false, true);
  
  if(display_insert_line())
  {
    display(false, false);
  }
  
  
  // Postconditions:

  ensure(lines().contains(result));
  ensure(new_lines().find(result) != new_lines().end());

  // Exit:

  // cout << "Leaving kd_lattice::insert_line." << endl << endl;
  return result;
}

void
geometry::kd_lattice::
remove_line(const scoped_index& xid)
{
  // cout << endl << "Entering kd_lattice::remove_line." << endl;

  // Preconditions:

  require(lines().contains(xid));

  // Body:

  if(logging())
  {
    kd_lattice_log::remove_line_record lrec(xid.hub_pod());
    log(lrec);
  }

  if(auto_clear_notify_sets())
  {
    clear_notify_sets();
  }

  // Get the surface containing the line.

  scoped_index lsurface_id;
  kd_line::surface(*this, xid, lsurface_id);

  // Get the faces and zones containing the segments of the line.

  id_list lface_ids, lzone_ids;
  kd_line::cells(*this, xid, lface_ids, lzone_ids);

  // Clear the triangles from the zones.

  _base_space->begin_jim_edit_mode(true);

  pod_id_hash_set ltriangles;  
  for(id_list::iterator i = lzone_ids.begin(); i != lzone_ids.end(); ++i)
  {
    kd_zone::clear_contents(*this, *i, ltriangles);
  }

  // Remove the triangles from the surfaces.

  // cout << "ltriangles: " << ltriangles << endl;

  hash_set_filter lfilter(ltriangles);
  for(id_set::iterator s=modified_surfaces().begin(); s!=modified_surfaces().end(); ++s)
  {
    // cout << "removing triangles for lower cover of surface: " << _base_space->member_name(*s) << endl;
    // cout << "before: " << _base_space->cover_iterator(LOWER, *s) << endl;
      
    _base_space->remove_cover_members(lfilter, LOWER, *s);

    // cout << "after: " << _base_space->cover_iterator(LOWER, *s) << endl;
  }
  
  // Remove the line.

  pod_id_hash_set lseg_pods;
  kd_line::clear(*this, xid, lseg_pods);
  kd_line::deactivate(*this, xid);
  
  // Remove the segments from the faces.

  hash_set_filter lseg_filter(lseg_pods);
  bool lall_faces_empty = true;
  for(id_list::iterator i=lface_ids.begin(); i!=lface_ids.end(); ++i)
  {
    _base_space->remove_cover_members(lseg_filter, LOWER, *i);
    lall_faces_empty = lall_faces_empty && kd_face::is_empty(*this, *i);
  }

  if(lall_faces_empty)
  {
    // All the faces are now empty, remove the plane.

    post_information_message("Plane removal not yet implemented.");
  }

  //   cover_set_iterator litr = _base_space->cover_iterator(LOWER, lsurface_id);
  //   while(!litr.is_done())
  //   {
  //     cout << litr.item() << "  " << _base_space->member_name(litr.item()) << endl;
  //     litr.next();
  //   }

  if(_base_space->cover_is_empty(LOWER, lsurface_id))
  {
    // The line was the last line in its surface;
    // deactivate the surface.

    _base_space->delete_link(_active_part->index(), lsurface_id);
    kd_surface::deactivate(*this, lsurface_id);
  }
  else
  {
    // Removing the line may have broken its surface into
    // disconnected components. 

    id_list lnew_surface_ids;
    kd_surface::decompose(*this, lsurface_id, lnew_surface_ids);
  }
  
    
  if(_auto_triangulate)
  {
    // Retriangulate the zones.

    retriangulate_cleared_zones();
  }

  _base_space->end_jim_edit_mode(false, true);

  
  if(display_remove_line())
  {
    display(true, true);
  }

  // Postconditions:

  ensure(!lines().is_active(xid));
  

  // Exit:

  // cout << "Leaving kd_lattice::remove_line." << endl;
  return;
}

void
geometry::kd_lattice::
implicit_lines(const kd_plane& xp, pt_list_list& xresult)
{
  // cout << endl << "Entering kd_lattice::implicit_lines." << endl;

  // Preconditions:

  require(xp.is_valid());
  require(!contains_equivalent_plane(xp));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  _coords->get_read_access();

  // Extract the intersection of the plane with existing surfaces.

  _iline_pts.clear();
  _iline_map.clear();
  
  frag_list lifrags;
  _top_zone->intersect_plane(xp, lifrags);

  // cout << endl << "plane-triangle intersection points: " << endl << _iline_pts << endl;

  // Assemble the frag list into lines.

  frag_list lofrags;
  kd_line_fragment::assemble(*this, lifrags, lofrags);

  // Convert the frag list to points.

  for(frag_list::iterator lf = lofrags.begin(); lf != lofrags.end(); ++lf)
  {
    //     pt_list lpts;
    //     xresult.push_back(lpts);
    
    //     for(id_list::iterator li = lf->pt_ids.begin(); li != lf->pt_ids.end(); ++li)
    //     {
      
    //       xresult.back().push_back(_iline_pts[li->pod()]);
    //     }

    if(!lf->pt_ids.empty())
    {
      size_type lsegment_ct = 0;
      pt_list lpts;
      xresult.push_back(lpts);
      id_list::iterator li = lf->pt_ids.begin();
      xresult.back().push_back(_iline_pts[li->pod()]);
      ++li;
      while(li != lf->pt_ids.end())
      {
        e3_lite& lpt = _iline_pts[li->pod()];
        
        if(!fiber_bundle::vd_algebra::c_eql(xresult.back().back(), lpt))
        {
          // The segment defined the previous point 
          // and the current point is greater than the
          // welding distance, add this segment to the line.

          xresult.back().push_back(lpt);
          lsegment_ct++;
        }
        else
        {
          // This segment is shorter than the welding tolerance;
          // just skip this point.
        }
        
        ++li;
      }

      if(lsegment_ct == 0)
      {
        // Didn't find at least 2 points.

        xresult.pop_back();
      }
      else
      {
        // Force the line precisely into the plane.

        force_line(xresult.back(), xp);
      }
    }
  }

  _coords->release_access();

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);

  // Exit:

  // cout << "Leaving kd_lattice::implicit_lines." << endl;
  return;
}

sheaf::block<fiber_bundle::e3_lite>&
geometry::kd_lattice::
iline_pts()
{
  return _iline_pts;
}

const sheaf::block<fiber_bundle::e3_lite>&
geometry::kd_lattice::
iline_pts() const
{
  return _iline_pts;
}

geometry::kd_lattice::iline_map_type&
geometry::kd_lattice::
iline_map()
{
  return _iline_map;
}

const geometry::kd_lattice::iline_map_type&
geometry::kd_lattice::
iline_map() const
{
  return _iline_map;
}

geometry::id_set&
geometry::kd_lattice::
new_lines()
{
  return _new_lines;
}

const geometry::id_set&
geometry::kd_lattice::
new_lines() const
{
  return _new_lines;
}

geometry::id_set&
geometry::kd_lattice::
modified_lines()
{
  return _modified_lines;
}

const geometry::id_set&
geometry::kd_lattice::
modified_lines() const
{
  return _modified_lines;
}

geometry::id_set&
geometry::kd_lattice::
deleted_lines()
{
  return _deleted_lines;
}

const geometry::id_set&
geometry::kd_lattice::
deleted_lines() const
{
  return _deleted_lines;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// LINE_WEB FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::jim_cohort&
geometry::kd_lattice::
line_webs()
{
  return *_line_webs;
}

const geometry::jim_cohort&
geometry::kd_lattice::
line_webs() const
{
  return *_line_webs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
// TRIANGLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::d_cells_cohort&
geometry::kd_lattice::
triangles()
{
  return *_triangles;
}

const geometry::d_cells_cohort&
geometry::kd_lattice::
triangles() const
{
  return *_triangles;
}

bool
geometry::kd_lattice::
auto_triangulate() const
{
  return _auto_triangulate;
}

void
geometry::kd_lattice::
put_auto_triangulate(bool xvalue)
{
  // cout << endl << "Entering kd_lattice::put_auto_triangulate." << endl;

  // Preconditions:

  // Body:

  if(logging())
  {
    kd_lattice_log::put_auto_triangulate_record lrec(xvalue);
    log(lrec);
  }

  _auto_triangulate = xvalue;

  // Postconditions:

  ensure(auto_triangulate() == xvalue);
  
  // Exit:

  // cout << "Leaving kd_lattice::put_auto_triangulate." << endl;
  return;
}


void
geometry::kd_lattice::
retriangulate()
{
  // cout << endl << "Entering kd_lattice::retriangulate." << endl;

  // Preconditions:


  // Body:

  if(logging())
  {
    kd_lattice_log::retriangulate_record lrec;
    log(lrec);
  }

  _base_space->begin_jim_edit_mode(true);
  _coords->get_read_write_access();

  // Clear the triangles out of all zones.

  // $$SCRIBBLE: this doesn't clear triangles out of
  // the faces of the region of interest.

  pod_id_hash_set ldeleted;
  
  index_space_iterator& lz_itr = _zone_leaves->id_space().get_iterator();
  scoped_index lz_id(_zone_leaves->id_space());
  while(!lz_itr.is_done())
  {
    lz_id = lz_itr.pod();
    kd_zone::clear_contents(*this, lz_id, ldeleted);
    lz_itr.next();
  }
  _zone_leaves->id_space().release_iterator(lz_itr);
  
  // Clear_contents leaves the deleted triangles in the lower cover of
  // the surfaces containing them because it is too inefficient to delete
  // them one at a time. Instead it marks the surfaces as modified and
  // returns the set of deleted ids so we can delete them all at once here.

  // cout << "ldeleted: " << ldeleted << endl;

  hash_set_filter lfilter(ldeleted);
  for(id_set::iterator s=modified_surfaces().begin(); s!=modified_surfaces().end(); ++s)
  {
    // cout << "removing triangles for lower cover of surface: " << _base_space->member_name(*s) << endl;
    // cout << "before: " << _base_space->cover_iterator(LOWER, *s) << endl;
      
    _base_space->remove_cover_members(lfilter, LOWER, *s);

    // cout << "after: " << _base_space->cover_iterator(LOWER, *s) << endl;
  }

  for(pod_id_hash_set::iterator i = _cleared_zones.begin(); i != _cleared_zones.end(); ++i)
  {
    kd_zone::triangulate(*this, _base_space->member_id(*i, false));
  }

  _cleared_zones.clear();

  _coords->release_access();
  _base_space->end_jim_edit_mode(false, true);

  // Postconditions:

  ensure(cleared_zones().empty());
  
  // Exit:

  // cout << "Leaving kd_lattice::retriangulate." << endl;
  return;
}

void
geometry::kd_lattice::
retriangulate_cleared_zones()
{
  // cout << endl << "Entering kd_lattice::retriangulate_cleared_zones." << endl;

  // Preconditions:


  // Body:

  for(pod_id_hash_set::iterator i = _cleared_zones.begin(); i != _cleared_zones.end(); ++i)
  {
    kd_zone::triangulate(*this, _base_space->member_id(*i, false));
  }

  _cleared_zones.clear();

  // Postconditions:

  ensure(cleared_zones().empty());
  
  // Exit:

  // cout << "Leaving kd_lattice::retriangulate_cleared_zones." << endl;
  return;
}



// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
// POLYGON FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::d_cells_cohort&
geometry::kd_lattice::
polygons()
{
  return *_polygons;
}

const geometry::d_cells_cohort&
geometry::kd_lattice::
polygons() const
{
  return *_polygons;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

 


// ===========================================================
// SURFACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::jim_cohort&
geometry::kd_lattice::
surfaces()
{
  return *_surfaces;
}

const geometry::jim_cohort&
geometry::kd_lattice::
surfaces() const
{
  return *_surfaces;
}


geometry::id_set&
geometry::kd_lattice::
new_surfaces()
{
  return _new_surfaces;
}

const geometry::id_set&
geometry::kd_lattice::
new_surfaces() const
{
  return _new_surfaces;
}

geometry::id_set&
geometry::kd_lattice::
modified_surfaces()
{
  return _modified_surfaces;
}

const geometry::id_set&
geometry::kd_lattice::
modified_surfaces() const
{
  return _modified_surfaces;
}

geometry::id_set&
geometry::kd_lattice::
deleted_surfaces()
{
  return _deleted_surfaces;
}

const geometry::id_set&
geometry::kd_lattice::
deleted_surfaces() const
{
  return _deleted_surfaces;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// SUVOLUME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::subcohort&
geometry::kd_lattice::
subvolume_surfaces()
{
  return *_subvolume_surfaces;
}

const geometry::subcohort&
geometry::kd_lattice::
subvolume_surfaces() const
{
  return *_subvolume_surfaces;
}

geometry::kd_region&
geometry::kd_lattice::
region_of_interest()
{
  return *_region_of_interest;
}

const geometry::kd_region&
geometry::kd_lattice::
region_of_interest() const
{
  return *_region_of_interest;
}

geometry::cohort&
geometry::kd_lattice::
interior_triangles()
{
  return *_interior_triangles;
}

const geometry::cohort&
geometry::kd_lattice::
interior_triangles() const
{
  return *_interior_triangles;
}

void
geometry::kd_lattice::
insert_region(const e3_lite& xlb, const e3_lite& xub)
{
  // cout << endl << "Entering kd_lattice::insert_region." << endl;

  // Preconditions:

  require(!region_of_interest().id().is_valid());
  require(contains_point(xlb));
  require(contains_point(xub));
  require(xlb.c_lt(xub));

  define_old_variable(size_type old_surfaces_ct = surfaces().ct());
  
  // Body:

  if(logging())
  {
    kd_lattice_log::insert_region_record lrec(xlb, xub);
    log(lrec);
  }

  _base_space->begin_jim_edit_mode(true);
  _coords->get_read_write_access();

  scoped_index lid;
  kd_region::new_region(*this, xlb, xub, lid);
  _region_of_interest->put_id(lid);
  
  _coords->release_access();
  _base_space->end_jim_edit_mode(false, true);


  //   update_section_space_schema();
  //   display(false, true);


  // Postconditions:

  ensure(region_of_interest().id().is_valid());
  ensure(surfaces().contains(region_of_interest().id()));
  ensure(surfaces().ct() == old_surfaces_ct + 1);
  ensure(new_surfaces().find(region_of_interest().id()) != new_surfaces().end());
  ensure(modified_surfaces().find(region_of_interest().id()) == modified_surfaces().end());
  ensure(deleted_surfaces().find(region_of_interest().id()) == deleted_surfaces().end());

  // Exit:

  // cout << "Leaving kd_lattice::insert_region." << endl;
  return;
}

void
geometry::kd_lattice::
extract_subvolume_surfaces()
{
  // cout << endl << "Entering kd_lattice::extract_subvolume_surfaces." << endl;

  // Preconditions:

  require(region_of_interest().id().is_valid());
  require(subvolume_surfaces().ct() == 0);
  
  // Body:

  if(logging())
  {
    kd_lattice_log::extract_subvolume_surfaces_record lrec;
    log(lrec);
  }

  _base_space->begin_jim_edit_mode(true);
  _coords->get_read_write_access();
  
  id_list lsubvolumes;
  _region_of_interest->subvolumes(lsubvolumes);

  //  cout << *_region_of_interest << endl;

  // Create coordinates restriction for each subvolume.

  update_section_space_schema();
  index_space_iterator& lsv_itr = subvolume_surfaces().id_space().get_iterator();
  while(!lsv_itr.is_done())
  {
    base_space_member lsv_base(_base_space, lsv_itr.hub_pod());
    sec_e3 lsv_coords(_coords->host(), lsv_base);

    stringstream lstr;
    lstr << "subvolume_" << lsv_itr.pod();
    lsv_coords.put_name(lstr.str(), true, false);

    assign(lsv_coords, *_coords, false);

    lsv_coords.detach_from_state();
    lsv_base.detach_from_state();

    lsv_itr.next();
  }
  subvolume_surfaces().id_space().release_iterator(lsv_itr);
  
  
  _coords->release_access();
  _base_space->end_jim_edit_mode(false, true);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_lattice::extract_subvolume_surfaces." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_lattice::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_lattice*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_lattice*
geometry::kd_lattice::
clone() const
{
  kd_lattice* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_lattice();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
geometry::kd_lattice::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

geometry::kd_lattice&
geometry::kd_lattice::
operator=(const kd_lattice& xother)
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_lattice&
geometry::kd_lattice::
operator=(const any& xother)
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}



// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, const kd_lattice& xl)
{
  // Preconditions:

  // Body:

  xos << xl.base_space() << endl;
  xos << *(xl.coords().host()) << endl;
  //  xos << *(xl.planes().host()) << endl;

  xl.coords().get_read_access();

  const base_space_poset& lbase = xl.base_space();


  xos << "#### ZONES ####" << endl << endl;
  
  index_space_iterator& lzitr = xl.zones().id_space().get_iterator();
  scoped_index lzid(xl.zones().id_space());
  while(!lzitr.is_done())
  {
    lzid = lzitr.pod();
    kd_zone lz(const_cast<kd_lattice&>(xl), lzid);
    xos << lz;
    lzitr.next();
  }
  xl.zones().id_space().release_iterator(lzitr);

  xos << endl;
  xos << "#### FACES ####" << endl << endl;

  index_space_iterator& lfitr = xl.faces().id_space().get_iterator();
  scoped_index lfid(xl.faces().id_space());
  while(!lfitr.is_done())
  {
    lfid = lfitr.pod();
    kd_face lf(const_cast<kd_lattice&>(xl), lfid);
    xos << lf;
    lfitr.next();
  }
  xl.faces().id_space().release_iterator(lfitr);

  xos << endl;
  xos << "#### EDGES ####" << endl << endl;

  index_space_iterator& leitr = xl.edges().id_space().get_iterator();
  scoped_index leid(xl.edges().id_space());
  while(!leitr.is_done())
  {
    leid = leitr.pod();
    kd_edge le(const_cast<kd_lattice&>(xl), leid);
    xos << le;
    leitr.next();
  }
  xl.edges().id_space().release_iterator(leitr);

  xos << endl;
  xos << "#### VERTICES ####" << endl << endl;

  index_space_iterator& lvitr = xl.vertices().id_space().get_iterator();
  scoped_index lvid(xl.vertices().id_space());
  while(!lvitr.is_done())
  {
    lvid = lvitr.pod();
    kd_vertex lv(const_cast<kd_lattice&>(xl), lvid);
    xos << lv;
    lvitr.next();
  }
  xl.vertices().id_space().release_iterator(lvitr);
    
  xl.coords().release_access();

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const geometry::kd_lattice& xn, bool xinclude_shallow)
{
  size_t result = 0;

  // Preconditions:

  // Body:

  not_implemented();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

// ===========================================================
// SPECIALIZATIONS
// ===========================================================
 
template<>
const sheaf::subposet&
geometry::kd_lattice::
member_filter<kd_zone>()
{
  return _zones->sp();
}
