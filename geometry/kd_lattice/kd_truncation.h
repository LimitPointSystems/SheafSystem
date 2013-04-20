

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_truncation

#ifndef KD_TRUNCATION_H
#define KD_TRUNCATION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif
 
namespace geometry
{
  
///
/// A description of the truncation relationships at a truncation point.
///
class SHEAF_DLL_SPEC kd_truncation
{

  // ===========================================================
  /// @name KD_TRUNCATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Static const ints; hack to make MSC++ happy.
  ///
  enum static_const_int{SURFACE_UB = 2};
  
  ///
  /// Number of surfaces that meet at the point.
  ///
  size_type surface_ct;
  
  ///
  /// Ids for surfaces that meet at the point.
  ///
  scoped_index surface_ids[SURFACE_UB];
  
  ///
  /// Number of segments from each surface incident at the point.
  ///
  size_type segment_cts[SURFACE_UB];

  ///
  /// Default constructor
  ///
  kd_truncation();

  ///
  /// Creates and instance for the point with id xid in kd_lattice xhost.
  ///
  kd_truncation(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Destructor. Not virtual, can not be a base class.
  ///
  ~kd_truncation();

  ///
  /// Truncation relationship.
  ///
  enum trunc_type
  {
    MUTUALLY_TRUNCATED = 2,
    NORMAL_TRUNCATION = 3,
    MUTUALLY_TRUNCATING = 4,
    NOT_A_TRUNCATION // must be last
  };

  ///
  /// The total number of segments incident at the point.
  ///
  size_type segment_ct() const;
  
  ///
  /// True if this a truncation of a surface with itself.
  ///
  bool is_self_truncation() const;

  ///
  /// True if this a truncation of a surface with one other surface.
  ///
  bool is_binary_truncation() const;

  ///
  /// True if this a truncation of a surface with more than one other surface.
  ///
  bool is_higher_order_truncation() const;
  
  ///
  /// Conversion from int to trunc_type.
  ///
  static trunc_type type(int xi);
  
  ///
  /// Type of truncation.
  ///
  trunc_type type() const;
  
  ///
  /// The truncated surface for a normal truncation.
  ///
  const scoped_index& truncated() const;
  
  ///
  /// The truncating surface for a normal truncation.
  ///
  const scoped_index& truncating() const;

  ///
  /// True if and only if the surface with id xid
  /// is the truncated surface at the point.
  ///
  bool is_truncated(const scoped_index& xid) const;

  ///
  /// True if and only if the surface with id xid
  /// is the truncating surface at the point.
  ///
  bool is_truncating(const scoped_index& xid) const;

  ///
  /// Sets surface_ct == 0 and initializes surface_ids and segment_cts.
  ///
  void clear();

  ///
  /// True if xother is the same truncation as this.
  ///
  bool is_same(const kd_truncation& xother) const;

  ///
  /// True if xother is the reverse truncation of this.
  ///
  bool is_reverse(const kd_truncation& xother) const;
  
  ///
  /// True if xother has the same surfaces as this.
  ///
  bool has_same_surfaces(const kd_truncation& xother) const;

  ///
  /// Equality comparison.
  ///
  bool operator==(const kd_truncation& xother) const;

//   ///
//   /// The truncation with surfaces transposed.
//   ///
//   kd_truncation transpose() const;
  
  
  

protected:


private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
///
/// Insert kd_truncation::trunc_type& xn into ostream& xos.
///
SHEAF_DLL_SPEC ostream & operator << (ostream &xos, const kd_truncation::trunc_type& xn); 
 
///
/// Insert kd_truncation& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_truncation& xn);
  
} // end namespace geometry

#endif // ifndef KD_TRUNCATION_H
