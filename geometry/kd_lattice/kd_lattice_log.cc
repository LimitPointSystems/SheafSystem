//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_lattice_log

#include "kd_lattice_log.h"

#include "assert_contract.h"
#include "kd_lattice.h"
#include "kd_plane.h"
#include "std_sstream.h"
#include "std_fstream.h"
#include "e3.h"

using namespace geometry;  // Workaround for MSVC++ bug


// ===========================================================
// KD_LATTICE_LOG::RECORD FACET
// ===========================================================

geometry::kd_lattice_log::record::
record()
{
  return;
}

geometry::kd_lattice_log::record::
record(kd_lattice_log::record_type xid)
{
  id = xid;
  return;
}

geometry::kd_lattice_log::record::
operator string() const
{
  return "";
}

geometry::kd_lattice_log::record::
~record()
{
  return;
}

// ===========================================================
// KD_LATTICE_LOG::CONSTRUCTOR_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::constructor_record::
constructor_record()
  : record(CONSTRUCTOR)
{
  return;
}

geometry::kd_lattice_log::constructor_record::
~constructor_record()
{
  return;
}

geometry::kd_lattice_log::constructor_record::
constructor_record(const string& xname, 
		   const e3_lite& xlb, 
		   const e3_lite& xub)
  : record(CONSTRUCTOR)
{
  name = xname;
  lb[0] = xlb[0];
  lb[1] = xlb[1];
  lb[2] = xlb[2];
  ub[0] = xub[0];
  ub[1] = xub[1];
  ub[2] = xub[2];
};

geometry::kd_lattice_log::constructor_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::constructor" << endl;
  lstr << "  name = " << name << endl;
  lstr << "  lb " << lb[0] << "  "  << lb[1] << "  "  << lb[2] << endl;
  lstr << "  ub " << ub[0] << "  "  << ub[1] << "  "  << ub[2] << endl;

  string result(lstr.str());

  // Postconditions:

  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::UPDATE_SECTION_SPACE_SCHEMA_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::update_section_space_schema_record::
update_section_space_schema_record()
  : record(UPDATE_SECTION_SPACE_SCHEMA)
{
  return;
}

geometry::kd_lattice_log::update_section_space_schema_record::
~update_section_space_schema_record()
{
  return;
}
    
geometry::kd_lattice_log::update_section_space_schema_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::update_section_space_schema_record" << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::CREATE_ACTIVE_SECTIONS_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::create_active_sections_record::
create_active_sections_record()
  : record(CREATE_ACTIVE_SECTIONS)
{
  return;
}

geometry::kd_lattice_log::create_active_sections_record::
~create_active_sections_record()
{
  return;
}
    
geometry::kd_lattice_log::create_active_sections_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::create_active_sections_record" << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::INSERT_PLANE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::insert_plane_record::
insert_plane_record()
  : record(INSERT_PLANE)
{
  return;
}

geometry::kd_lattice_log::insert_plane_record::
~insert_plane_record()
{
  return;
}
    
geometry::kd_lattice_log::insert_plane_record::
insert_plane_record(const kd_plane& xp)
  : record(INSERT_PLANE)
{
  alignment = xp.int_alignment();
  distance = xp.distance();
};    

geometry::kd_lattice_log::insert_plane_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::insert_plane_record" << endl;
  lstr << "  alignment " << alignment << endl;
  lstr << "  distance " << distance << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::PUT_PLANE_TOLERANCE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::put_plane_tolerance_record::
put_plane_tolerance_record()
  : record(PUT_PLANE_TOLERANCE)
{
  return;
}

geometry::kd_lattice_log::put_plane_tolerance_record::
~put_plane_tolerance_record()
{
  return;
}
    
geometry::kd_lattice_log::put_plane_tolerance_record::
put_plane_tolerance_record(const e3_lite& xtolerance)
  : record(PUT_PLANE_TOLERANCE)
{
  tolerance[0] = xtolerance[0];
  tolerance[1] = xtolerance[1];
  tolerance[2] = xtolerance[2];
};    

geometry::kd_lattice_log::put_plane_tolerance_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::put_plane_tolerance_record" << endl;
  lstr << "  tolerance " << tolerance[0] << "  "  << tolerance[1] << "  "  << tolerance[2] << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::PUT_POINT_TOLERANCE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::put_point_tolerance_record::
put_point_tolerance_record()
  : record(PUT_POINT_TOLERANCE)
{
  return;
}

geometry::kd_lattice_log::put_point_tolerance_record::
~put_point_tolerance_record()
{
  return;
}
    
geometry::kd_lattice_log::put_point_tolerance_record::
put_point_tolerance_record(const e3_lite& xtolerance)
  : record(PUT_POINT_TOLERANCE)
{
  tolerance[0] = xtolerance[0];
  tolerance[1] = xtolerance[1];
  tolerance[2] = xtolerance[2];
};    

geometry::kd_lattice_log::put_point_tolerance_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::put_point_tolerance_record" << endl;
  lstr << "  tolerance " << tolerance[0] << "  "  << tolerance[1] << "  "  << tolerance[2] << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::PUT_TRUNCATION_TOLERANCE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::put_truncation_tolerance_record::
put_truncation_tolerance_record()
  : record(PUT_TRUNCATION_TOLERANCE)
{
  return;
}

geometry::kd_lattice_log::put_truncation_tolerance_record::
~put_truncation_tolerance_record()
{
  return;
}
    
geometry::kd_lattice_log::put_truncation_tolerance_record::
put_truncation_tolerance_record(const e3_lite& xtolerance)
  : record(PUT_TRUNCATION_TOLERANCE)
{
  tolerance[0] = xtolerance[0];
  tolerance[1] = xtolerance[1];
  tolerance[2] = xtolerance[2];
};    

geometry::kd_lattice_log::put_truncation_tolerance_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::put_truncation_tolerance_record" << endl;
  lstr << "  tolerance " << tolerance[0] << "  "  << tolerance[1] << "  "  << tolerance[2] << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::PUT_INTERSECTION_TOLERANCE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::put_intersection_tolerance_record::
put_intersection_tolerance_record()
  : record(PUT_INTERSECTION_TOLERANCE)
{
  return;
}

geometry::kd_lattice_log::put_intersection_tolerance_record::
~put_intersection_tolerance_record()
{
  return;
}
    
geometry::kd_lattice_log::put_intersection_tolerance_record::
put_intersection_tolerance_record(const e3_lite& xtolerance)
  : record(PUT_INTERSECTION_TOLERANCE)
{
  tolerance[0] = xtolerance[0];
  tolerance[1] = xtolerance[1];
  tolerance[2] = xtolerance[2];
};    

geometry::kd_lattice_log::put_intersection_tolerance_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::put_intersection_tolerance_record" << endl;
  lstr << "  tolerance " << tolerance[0] << "  "  << tolerance[1] << "  "  << tolerance[2] << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG:FORCE_LINE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::force_line_record::
force_line_record()
  : record(FORCE_LINE)
{
  x = 0;
  y = 0;
  z = 0;
  return;
}

geometry::kd_lattice_log::force_line_record::
~force_line_record()
{
  if(x != 0) delete [] x;
  if(y != 0) delete [] y;
  if(z != 0) delete [] z;
  return;
}

geometry::kd_lattice_log::force_line_record::
force_line_record(pt_list& xline, const kd_plane& xp) 
  : record(FORCE_LINE)
{
  pt_ct = xline.size();
  x = new vd_value_type[pt_ct];
  y = new vd_value_type[pt_ct];
  z = new vd_value_type[pt_ct];

  pt_list::const_iterator itr = xline.begin();
  for(int i = 0; itr != xline.end() ; ++i, ++itr)
  {
    x[i] = (*itr)[0];
    y[i] = (*itr)[1];
    z[i] = (*itr)[2];
  }

  alignment = xp.int_alignment();
  distance = xp.distance();
};    

geometry::kd_lattice_log::force_line_record::
operator string() const
{
  // Preconditions:


  // Body:

  stringstream lstr;
  lstr << "kd_lattice::force_line_record" << endl;
  lstr << "  pt_ct: " << pt_ct << endl;
  lstr << "  pt coordinates:" << endl;
  for(size_type i=0; i<pt_ct; ++i)
  {
    lstr << "  " << x[i] << "  " << y[i] << "  " << z[i] << endl;
  }
  lstr << "  alignment " << alignment << endl;
  lstr << "  distance " << distance << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG:INSERT_LINE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::insert_line_record::
insert_line_record()
  : record(INSERT_LINE)
{
  x = 0;
  y = 0;
  z = 0;
  return;
}

geometry::kd_lattice_log::insert_line_record::
~insert_line_record()
{
  if(x != 0) delete [] x;
  if(y != 0) delete [] y;
  if(z != 0) delete [] z;
  return;
}

geometry::kd_lattice_log::insert_line_record::
insert_line_record(pt_list& xline, const kd_plane& xp) 
  : record(INSERT_LINE)
{
  pt_ct = xline.size();
  x = new vd_value_type[pt_ct];
  y = new vd_value_type[pt_ct];
  z = new vd_value_type[pt_ct];

  pt_list::const_iterator itr = xline.begin();
  for(int i = 0; itr != xline.end() ; ++i, ++itr)
  {
    x[i] = (*itr)[0];
    y[i] = (*itr)[1];
    z[i] = (*itr)[2];
  }

  alignment = xp.int_alignment();
  distance = xp.distance();
};    

geometry::kd_lattice_log::insert_line_record::
operator string() const
{
  // Preconditions:


  // Body:

  stringstream lstr;
  lstr << "kd_lattice::insert_line_record" << endl;
  lstr << "  pt_ct: " << pt_ct << endl;
  lstr << "  pt coordinates:" << endl;
  for(size_type i=0; i<pt_ct; ++i)
  {
    lstr << "  " << x[i] << "  " << y[i] << "  " << z[i] << endl;
  }
  lstr << "  alignment " << alignment << endl;
  lstr << "  distance " << distance << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::REMOVE_LINE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::remove_line_record::
remove_line_record()
  : record(REMOVE_LINE)
{
  return;
}

geometry::kd_lattice_log::remove_line_record::
~remove_line_record()
{
  return;
}
    
geometry::kd_lattice_log::remove_line_record::
remove_line_record(pod_index_type xhub_id)
  : record(REMOVE_LINE)
{
  hub_id = xhub_id;
};    

geometry::kd_lattice_log::remove_line_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::remove_line_record" << endl;
  lstr << "  hub_id " << hub_id << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::PUT_AUTO_TRIANGULATE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::put_auto_triangulate_record::
put_auto_triangulate_record()
  : record(PUT_AUTO_TRIANGULATE)
{
  return;
}

geometry::kd_lattice_log::put_auto_triangulate_record::
~put_auto_triangulate_record()
{
  return;
}
    
geometry::kd_lattice_log::put_auto_triangulate_record::
put_auto_triangulate_record(bool xvalue)
  : record(PUT_AUTO_TRIANGULATE)
{
  value = xvalue;
};    

geometry::kd_lattice_log::put_auto_triangulate_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::put_auto_triangulate_record" << endl;
  lstr << "  value " << value << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::RETRIANGULATE_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::retriangulate_record::
retriangulate_record()
  : record(RETRIANGULATE)
{
  return;
}

geometry::kd_lattice_log::retriangulate_record::
~retriangulate_record()
{
  return;
}
    
geometry::kd_lattice_log::retriangulate_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::retriangulate_record" << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::INSERT_REGION_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::insert_region_record::
insert_region_record()
  : record(INSERT_REGION)
{
  return;
}

geometry::kd_lattice_log::insert_region_record::
~insert_region_record()
{
  return;
}

geometry::kd_lattice_log::insert_region_record::
insert_region_record(const e3_lite& xlb, 
		     const e3_lite& xub)
  : record(INSERT_REGION)
{
  lb[0] = xlb[0];
  lb[1] = xlb[1];
  lb[2] = xlb[2];
  ub[0] = xub[0];
  ub[1] = xub[1];
  ub[2] = xub[2];
};

geometry::kd_lattice_log::insert_region_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::insert_region_record" << endl;
  lstr << "  lb " << lb[0] << "  "  << lb[1] << "  "  << lb[2] << endl;
  lstr << "  ub " << ub[0] << "  "  << ub[1] << "  "  << ub[2] << endl;

  string result(lstr.str());

  // Postconditions:

  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG::EXTRACT_SUBVOLUME_SURFACES_RECORD FACET
// =========================================================== 

geometry::kd_lattice_log::extract_subvolume_surfaces_record::
extract_subvolume_surfaces_record()
  : record(EXTRACT_SUBVOLUME_SURFACES)
{
  return;
}

geometry::kd_lattice_log::extract_subvolume_surfaces_record::
~extract_subvolume_surfaces_record()
{
  return;
}
    
geometry::kd_lattice_log::extract_subvolume_surfaces_record::
operator string() const
{
  // Preconditions:

  // Body:

  stringstream lstr;
  lstr << "kd_lattice::extract_subvolume_surfaces_record" << endl;
  
  string result(lstr.str());

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// KD_LATTICE_LOG FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_lattice_log::
kd_lattice_log()
{
  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_lattice_log::
kd_lattice_log(const kd_lattice_log& xother)
{
  
  // Preconditions:

    
  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_lattice_log::
~kd_lattice_log()
{  
  // Preconditions:

    
  // Body:
  
  for(size_type i=0; i< _records.ct(); ++i)
  {
    delete _records[i];
  }
  
  // Postconditions:

  // Exit:

  return; 
}

sheaf::block<geometry::kd_lattice_log::record*>&
geometry::kd_lattice_log::
records()
{
  return _records;
}

const sheaf::block<geometry::kd_lattice_log::record*>&
geometry::kd_lattice_log::
records() const
{
  return _records;
}


// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_lattice_log::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_lattice_log*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_lattice_log*
geometry::kd_lattice_log::
clone() const
{
  kd_lattice_log* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_lattice_log();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_lattice_log&
geometry::kd_lattice_log::
operator=(const kd_lattice_log& xother)
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

bool
geometry::kd_lattice_log::
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


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
istream& 
geometry::
operator >> (istream& xis, geometry::kd_lattice_log& xn)
{
  // Preconditions:

  // Body:

  kd_lattice_log::record* lrecord;

  // Get the file to os conversion type (eg: DOS2UNIX).

  kd_lattice_log::conversion_type lconv_type = get_conversion_type(xis);
  
  istringstream lstr;
  
  while(xis)
  {
    lrecord = 0;

    // Function get_log_line handles file type conversion
    // (dos or linux/unix). It also ignores comments which
    // begin with a '#' character.

    get_log_line(xis, lconv_type, lstr);

    if(lstr.str().empty())
    {
      // Empty line; do nothing.
    }
    else if(lstr.str().find("Log File") != string::npos)
    {
      // Header record; do nothing.
    }
    else if(lstr.str().find("constructor") != string::npos)
    {
      // Constructor record.

      typedef kd_lattice_log::constructor_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Name.
      
      get_log_line(xis, lconv_type, lstr);
      lrec->name = lstr.str().substr(lstr.str().find("=")+2);

      // Lower bound.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->lb[0] >> lrec->lb[1] >> lrec->lb[2] ;

      // Upper bound.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->ub[0] >> lrec->ub[1] >> lrec->ub[2] ;

      lrecord = lrec;
    }
    else if(lstr.str().find("update_section_space_schema") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::update_section_space_schema_record rec_type;
      rec_type* lrec = new rec_type;

      lrecord = lrec;
    }
    else if(lstr.str().find("create_active_sections") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::create_active_sections_record rec_type;
      rec_type* lrec = new rec_type;

      lrecord = lrec;
    }
    else if(lstr.str().find("insert_plane") != string::npos)
    {
      // Insert plane record.

      typedef kd_lattice_log::insert_plane_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Alignment.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->alignment;

      // Distance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->distance;

      lrecord = lrec;
    }
    else if(lstr.str().find("put_plane_tolerance") != string::npos)
    {
      // Insert plane record.

      typedef kd_lattice_log::put_plane_tolerance_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Tolerance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->tolerance[0] >> lrec->tolerance[1] >> lrec->tolerance[2];

      lrecord = lrec;
    }
    else if(lstr.str().find("put_point_tolerance") != string::npos)
    {
      // Insert point record.

      typedef kd_lattice_log::put_point_tolerance_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Tolerance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->tolerance[0] >> lrec->tolerance[1] >> lrec->tolerance[2];

      lrecord = lrec;
    }
    else if(lstr.str().find("put_truncation_tolerance") != string::npos)
    {
      // Insert truncation record.

      typedef kd_lattice_log::put_truncation_tolerance_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Tolerance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->tolerance[0] >> lrec->tolerance[1] >> lrec->tolerance[2];

      lrecord = lrec;
    }
    else if(lstr.str().find("put_intersection_tolerance") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::put_intersection_tolerance_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Tolerance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->tolerance[0] >> lrec->tolerance[1] >> lrec->tolerance[2];

      lrecord = lrec;
    }
    else if(lstr.str().find("force_line") != string::npos)
    {
      // Insert plane record.

      typedef kd_lattice_log::force_line_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Point count
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->pt_ct;

      // Pt coordinates

      get_log_line(xis, lconv_type, lstr);

      // X, y, z

      lrec->x = new vd_value_type[lrec->pt_ct];
      lrec->y = new vd_value_type[lrec->pt_ct];
      lrec->z = new vd_value_type[lrec->pt_ct];

      for(int i = 0; i < lrec->pt_ct; ++i)
      {
	get_log_line(xis, lconv_type, lstr);

	lstr >> lrec->x[i] >> lrec->y[i] >> lrec->z[i];
      }

      // Alignment.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->alignment;

      // Distance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->distance;

      lrecord = lrec;
    }
    else if(lstr.str().find("insert_line") != string::npos)
    {
      // Insert plane record.

      typedef kd_lattice_log::insert_line_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Point count
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->pt_ct;

      // Pt coordinates

      get_log_line(xis, lconv_type, lstr);

      // X, y, z

      lrec->x = new vd_value_type[lrec->pt_ct];
      lrec->y = new vd_value_type[lrec->pt_ct];
      lrec->z = new vd_value_type[lrec->pt_ct];

      for(int i = 0; i < lrec->pt_ct; ++i)
      {
	get_log_line(xis, lconv_type, lstr);

	lstr >> lrec->x[i] >> lrec->y[i] >> lrec->z[i];
      }

      // Alignment.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->alignment;

      // Distance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->distance;

      lrecord = lrec;
    }
    else if(lstr.str().find("remove_line") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::remove_line_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Tolerance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->hub_id;

      lrecord = lrec;
    }
    else if(lstr.str().find("put_auto_triangulate") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::put_auto_triangulate_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Tolerance.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->value;

      lrecord = lrec;
    }
    else if(lstr.str().find("retriangulate") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::retriangulate_record rec_type;
      rec_type* lrec = new rec_type;

      lrecord = lrec;
    }
    else if(lstr.str().find("insert_region") != string::npos)
    {
      // Constructor record.

      typedef kd_lattice_log::insert_region_record rec_type;
      rec_type* lrec = new rec_type;
      string ls0;

      // Lower bound.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->lb[0] >> lrec->lb[1] >> lrec->lb[2] ;

      // Upper bound.
      
      get_log_line(xis, lconv_type, lstr);
      lstr >> ls0 >> lrec->ub[0] >> lrec->ub[1] >> lrec->ub[2] ;

      lrecord = lrec;
    }
    else if(lstr.str().find("extract_subvolume_surfaces") != string::npos)
    {
      // Insert intersection record.

      typedef kd_lattice_log::extract_subvolume_surfaces_record rec_type;
      rec_type* lrec = new rec_type;

      lrecord = lrec;
    }
    else
    {
      cerr << "Unrecognized log record: " << lstr.str() << endl;
      post_fatal_error_message("Unrecognized log record.");
    }

    if(lrecord != 0)
    {
      // Put record into record block.

      xn.records().push_back(lrecord);
    }
    
  }
  
  // Postconditions:

  // Exit:

  return xis;
}

ostream& 
geometry::
operator << (ostream& xos, const geometry::kd_lattice_log& xn)
{
  for(size_type i=0; i<xn.records().ct(); ++i)
  {
    xos << *(xn.records()[i]) << endl;
  }

  return xos;
}

ostream& 
geometry::
operator << (ostream& xos, const geometry::kd_lattice_log::record& xn)
{
  xos << static_cast<string>(xn);

  return xos;
}

// ===========================================================
// ===========================================================

kd_lattice_log::conversion_type
geometry::
get_conversion_type(istream& xis)
{
  // Preconditions:

  // Body:

  kd_lattice_log::conversion_type result = kd_lattice_log::NONE;

  //SCRIBBLE: Currently only handling the conversion between Unix and Windows.
  //          Will have to extend the code if handling MACs becomes necessary.

  // Determine whether the current os is windows (or not).
  // We could use the predefined _WIN32. To do that would require
  // precompiler "#ifdef", etc. here.  Instead take advantage
  // of the fact that endl inserts "\r\n" into a stream on windows.

  ostringstream lstr;
  lstr << endl;
  string ls = lstr.str();
  bool los_is_dos = ((ls.length()==2) && (ls[0]=='\r'));

  // The first line of a log file is blank (Have to ensure this).
  // So get the first character in the stream.  If the file is a
  // windows/dos file, the first character will be '\r' (carriage return).
  // If it is a unix/linix file, the first // character will be '\n'.

  char c = xis.get();

  // Put the character back into the stream.

  xis.unget(); 

  bool lfile_is_dos = (c == '\r');

  if(lfile_is_dos && !los_is_dos)
  {
    result = kd_lattice_log::DOS2UNIX;
  }
  else if(!lfile_is_dos && los_is_dos)
  {
    result = kd_lattice_log::UNIX2DOS;  
  }

  // Postconditions:

  // Exit:

  return result;
}

void
geometry::
get_log_line(istream& xis, kd_lattice_log::conversion_type xconv_type,
             istringstream& xresult)
{
  // Preconditions:

  // Body:

  static string ls;

  // Recurse until we get an empty line or a line with
  // something in it besides a comment.

  while(true)
  {
    getline(xis, ls);

    // If it is a dos file, delete the carriage return on linux
    // (The getline call above strips off the '\n', so the '\r'
    // is the now the last character).

    if((xconv_type == kd_lattice_log::DOS2UNIX) && (!ls.empty()))
    {
      ls.erase(ls.length()-1);
    }

    // Ignore comments: Everything from the first '#' to the end
    // of the line.

    if(!ls.empty())
    {
      size_t loc = ls.find('#');
      if(loc != string::npos)
      {
        ls.erase(loc);
      }

      // If the string now contains anything other than white space,
      // break out and return; otherwise read the next line.

      const size_t lnon_white = ls.find_first_not_of(" \t");
      if(lnon_white != string::npos)
      {
        break;
      }
    }
    else
    {
      // Empty line; just return.

      break;
    }
  }

  xresult.clear();
  xresult.str(ls);

  // Postconditions:

  // Exit:
}


// ===========================================================
// EXPLICIT INSTANTIATIONS
// ===========================================================

#include "block.impl.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::kd_lattice_log::record*>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::kd_lattice_log::record*, sheaf::un_block_initialization_policy<geometry::kd_lattice_log::record*> >;

template class 
SHEAF_DLL_SPEC
sheaf::block<geometry::kd_lattice_log::record*>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << (ostream& xos, const block<geometry::kd_lattice_log::record*>& xblk);
 



