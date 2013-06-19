//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_lattice_log

#ifndef KD_LATTICE_LOG_H
#define KD_LATTICE_LOG_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

namespace geometry
{
  
///
/// Wrapper for a kd_lattice log file.
///
class SHEAF_DLL_SPEC kd_lattice_log : public any
{

  // ===========================================================
  /// @name KD_LATTICE_LOG FACET
  // ===========================================================
  //@{

public:

  ///
  /// Enumeration for log record types.
  ///
  enum record_type 
  { 
    HEADER, 
    CONSTRUCTOR,
    UPDATE_SECTION_SPACE_SCHEMA,
    CREATE_ACTIVE_SECTIONS,
    INSERT_PLANE, 
    PUT_PLANE_TOLERANCE,
    PUT_POINT_TOLERANCE,
    PUT_TRUNCATION_TOLERANCE,
    PUT_INTERSECTION_TOLERANCE,
    FORCE_LINE,
    INSERT_LINE,
    REMOVE_LINE,
    PUT_AUTO_TRIANGULATE,
    RETRIANGULATE,
    INSERT_REGION,
    EXTRACT_SUBVOLUME_SURFACES
  };

  ///
  /// Enumeration for file conversion types.
  ///
  enum conversion_type {NONE, DOS2UNIX, UNIX2DOS};

  ///
  /// Base class for log records.
  ///
  struct SHEAF_DLL_SPEC record
  {
    record_type id;
    
    record();

    virtual ~record();

    record(record_type xid);

    virtual operator string() const;
  };

  ///
  /// Constructor record.
  ///
  struct SHEAF_DLL_SPEC constructor_record : public record
  {
    string name;
    vd_value_type lb[3];
    vd_value_type ub[3];
    
    constructor_record();    

    virtual ~constructor_record();
    
    constructor_record(const string& xname, 
		       const e3_lite& xlb, 
		       const e3_lite& xub);    

    virtual operator string() const;
  };

  ///
  /// Update section space schema record.
  ///
  struct SHEAF_DLL_SPEC update_section_space_schema_record : public record
  {
    update_section_space_schema_record();

    virtual ~update_section_space_schema_record();
    
    virtual operator string() const;
  };

  ///
  /// Create active sections record.
  ///
  struct SHEAF_DLL_SPEC create_active_sections_record : public record
  {
    create_active_sections_record();

    virtual ~create_active_sections_record();
    
    virtual operator string() const;
  };

  ///
  /// Insert plane record.
  ///
  struct SHEAF_DLL_SPEC insert_plane_record : public record
  {
    int alignment;
    vd_value_type distance;
    
    insert_plane_record();

    virtual ~insert_plane_record();
    
    insert_plane_record(const kd_plane& xp);    

    virtual operator string() const;
  };

  ///
  /// Put plane tolerance record.
  ///
  struct SHEAF_DLL_SPEC put_plane_tolerance_record : public record
  {
    vd_value_type tolerance[3];

    put_plane_tolerance_record();

    virtual ~put_plane_tolerance_record();
    
    put_plane_tolerance_record(const e3_lite& xtolerance);

    virtual operator string() const;
  };

  ///
  /// Put point tolerance record.
  ///
  struct SHEAF_DLL_SPEC put_point_tolerance_record : public record
  {
    vd_value_type tolerance[3];

    put_point_tolerance_record();

    virtual ~put_point_tolerance_record();
    
    put_point_tolerance_record(const e3_lite& xtolerance);

    virtual operator string() const;
  };

  ///
  /// Put truncation tolerance record.
  ///
  struct SHEAF_DLL_SPEC put_truncation_tolerance_record : public record
  {
    vd_value_type tolerance[3];

    put_truncation_tolerance_record();

    virtual ~put_truncation_tolerance_record();
    
    put_truncation_tolerance_record(const e3_lite& xtolerance);

    virtual operator string() const;
  };

  ///
  /// Put intersection tolerance record.
  ///
  struct SHEAF_DLL_SPEC put_intersection_tolerance_record : public record
  {
    vd_value_type tolerance[3];

    put_intersection_tolerance_record();

    virtual ~put_intersection_tolerance_record();
    
    put_intersection_tolerance_record(const e3_lite& xtolerance);

    virtual operator string() const;
  };

  ///
  /// Force line record.
  ///
  struct SHEAF_DLL_SPEC force_line_record : public record
  {
    vd_value_type *x;
    vd_value_type *y;
    vd_value_type *z;
    size_type pt_ct;

    int alignment;
    vd_value_type distance;

    force_line_record();

    virtual ~force_line_record();
    
    force_line_record(pt_list& xline, const kd_plane& xp);

    virtual operator string() const;
  };

  ///
  /// Insert line record.
  ///
  struct SHEAF_DLL_SPEC insert_line_record : public record
  {
    vd_value_type *x;
    vd_value_type *y;
    vd_value_type *z;
    size_type pt_ct;

    int alignment;
    vd_value_type distance;

    insert_line_record();

    virtual ~insert_line_record();
    
    insert_line_record(pt_list& xline, const kd_plane& xp);

    virtual operator string() const;
  };

  ///
  /// Remove line record.
  ///
  struct SHEAF_DLL_SPEC remove_line_record : public record
  {
    pod_index_type hub_id;

    remove_line_record();

    virtual ~remove_line_record();
    
    remove_line_record(pod_index_type xid);

    virtual operator string() const;
  };

  ///
  /// Put auto triangulate record.
  ///
  struct SHEAF_DLL_SPEC put_auto_triangulate_record : public record
  {
    bool value;

    put_auto_triangulate_record();

    virtual ~put_auto_triangulate_record();
    
    put_auto_triangulate_record(bool xvalue);

    virtual operator string() const;
  };

  ///
  /// Retriangulate record.
  ///
  struct SHEAF_DLL_SPEC retriangulate_record : public record
  {
    retriangulate_record();

    virtual ~retriangulate_record();
    
    virtual operator string() const;
  };

  ///
  /// Insert region record.
  ///
  struct SHEAF_DLL_SPEC insert_region_record : public record
  {
    vd_value_type lb[3];
    vd_value_type ub[3];
    
    insert_region_record();    

    virtual ~insert_region_record();
    
    insert_region_record(const e3_lite& xlb, 
			 const e3_lite& xub);    

    virtual operator string() const;
  };

  ///
  /// Extract subvolume surfaces record.
  ///
  struct SHEAF_DLL_SPEC extract_subvolume_surfaces_record : public record
  {
    extract_subvolume_surfaces_record();

    virtual ~extract_subvolume_surfaces_record();
    
    virtual operator string() const;
  };

  ///
  /// Default constructor
  ///
  kd_lattice_log();

  ///
  /// Copy constructor
  ///
  kd_lattice_log(const kd_lattice_log& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_lattice_log();

  ///
  /// Records from file.
  ///
  block<record*>& records();

  ///
  /// Records from file, const version
  ///
  const block<record*>& records() const;


protected:

  ///
  /// Records from file.
  ///
  block<record*> _records;

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual kd_lattice_log* clone() const;

  ///
  /// Assignment operator
  ///
  kd_lattice_log& operator=(const kd_lattice_log& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Extract kd_lattice_log& xn from istream& xos.
///
SHEAF_DLL_SPEC 
istream & operator >> (istream &xis, kd_lattice_log& xn);
 
///
/// Insert kd_lattice_log& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_lattice_log& xn);
 
///
/// Insert kd_lattice_log::record& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_lattice_log::record& xn);

///
/// Determine the log file type conversion necessary (for example:
/// windows/dos file type to unix file type).
///
SHEAF_DLL_SPEC 
kd_lattice_log::conversion_type get_conversion_type(istream& xis);

///
/// Get a line from the log file stream xis and insert it into
/// the istringstream xresult after any necessary conversion specified
/// by xconv_type.  Also removes comments (everything from the first
/// '#' character to the end of the line).
///
SHEAF_DLL_SPEC 
void get_log_line(istream& xis, kd_lattice_log::conversion_type xconv_type,
                  istringstream& xresult);
  
} // end namespace geometry


#endif // ifndef KD_LATTICE_LOG_H
