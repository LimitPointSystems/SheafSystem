

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class geometry

#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STL_SCOPED_INDEX_H
#include "stl_scoped_index.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif
 
#ifndef STD_SET_H
#include "std_set.h"
#endif


namespace sheaf
{
  template <class T>
  class block;
}

namespace fiber_bundle
{
  class chart_point_3d;
  class e3_lite;
  class e2_lite;
}

///
/// Namespace for geometry component of sheaf system.
///
namespace geometry
{

  // geometry name space includes fiber_bundle name space.

  using namespace sheaf;
  using namespace fiber_bundle;

  // Forward declarations for classes.

  class abstract_cohort;
  class cohort;
  class d_cells_cohort;
  class geometry_namespace;
  class jim_cohort;
  class kd_bounding_box;
  class kd_edge;
  class kd_edge_cohort;
  class kd_face;
  class kd_face_cohort;
  class kd_jim_cohort;
  class kd_lattice;
  class kd_line;
  class kd_line_fragment;
  class kd_member;
  class kd_plane;
  class kd_point;
  class kd_region;
  class kd_segment;
  class kd_surface;
  class kd_truncation_pair;
  class kd_truncation;
  class kd_vertex;
  class kd_zone;
  class kd_zone_cohort;
  class pooled_cohort;
  class subcohort;
  class vertex_cohort;

  ///
  /// The type of the function for computing
  /// the property dofs at given global coordinates.
  ///
  typedef void (*property_dof_function_type)
    (block<sec_vd_value_type>& xglobal_coords,
     block<sec_vd_dof_type>& xproperty_dofs);


  ///
  /// A point in base space paired with a branch in section space.
  ///
  typedef pair<scoped_index, chart_point_3d> branch_point_pair;

  ///
  /// A pair of POD ids.
  ///
  typedef pair<pod_index_type, pod_index_type> pod_pair;

  ///
  /// Insert pod_pair xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const pod_pair& xn);
  
  ///
  /// A list of pod_pairs.
  ///
  typedef list<pod_pair> pod_pair_list;

  ///
  /// Insert pod_pair_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const pod_pair_list& xn);
  
  ///
  /// A set of pod_pairs.
  ///
  typedef set<pod_pair> pod_pair_set;

  ///
  /// Insert pod_pair_set xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const pod_pair_set& xn);

  ///
  /// A set of POD ids.
  ///
  typedef set<pod_index_type> pod_id_set;

  ///
  /// A hash set of POD ids.
  ///
  typedef hash_set<pod_index_type> pod_id_hash_set;

  ///
  /// Insert pod_id_hash_set xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const pod_id_hash_set& xn);
  
  ///
  /// A list of POD ids.
  ///
  typedef list<pod_index_type> pod_id_list;

  ///
  /// A set of scoped_index ids.
  ///
  typedef set< stl_scoped_index<equivalence_compare_policy> > id_set;

  ///
  /// Insert id_set xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const id_set& xn);

  ///
  /// A hash set of scoped_index ids.
  ///
  typedef hash_set< stl_scoped_index<equivalence_compare_policy> > id_hash_set;
  
  ///
  /// A list of scoped_index ids.
  ///
  typedef list<scoped_index> id_list;

  ///
  /// Insert id_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const id_list& xn);

  ///
  /// A list of lists of scoped_index ids.
  ///
  typedef list<id_list> id_list_list;

  ///
  /// Insert id_list_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const id_list_list& xn);

  ///
  /// Sets xresult to the intersection of x1 and x2.
  ///
  void intersect(const id_list& x1, const id_list& x2, id_list& xresult);

  ///
  /// Sets x2 to the intersection of x1 and x2.
  ///
  void intersect(const id_list& x1, id_list& x2);

  ///
  /// A pair of scoped_index ids.
  ///
  typedef pair<scoped_index, scoped_index> id_pair;

  ///
  /// Insert id_pair xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const id_pair& xn);
  
  ///
  /// A list of id_pairs.
  ///
  typedef list<id_pair> id_pair_list;

  ///
  /// Insert id_pair_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const id_pair_list& xn);
  

  ///
  /// A list of e3_lite point coordinates.
  ///
  typedef list<e3_lite> pt_list;  

  ///
  /// Insert pt_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const pt_list& xn);

  ///
  /// A list of lists of e3_lite point coordinates.
  ///
  typedef list<pt_list> pt_list_list;  

  ///
  /// Insert pt_list_list xn into ostream& xos.
  ///
  SHEAF_DLL_SPEC 
  ostream & operator << (ostream &xos, const pt_list_list& xn);

  ///
  /// A list of line fragments.
  ///
  typedef list<kd_line_fragment> frag_list;

  // ===========================================================
  // NON-MEMBER FUNCTIONS
  // ===========================================================
 
} // namespace geometry

#endif // ifndef GEOMETRY_H
