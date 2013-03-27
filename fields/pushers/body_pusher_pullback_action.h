// $RCSfile: body_pusher_pullback_action.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:26 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class body_pusher_pullback_action

#ifndef BODY_PUSHER_PULLBACK_ACTION_H
#define BODY_PUSHER_PULLBACK_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DISCRETIZATION_PUSH_ACTION_H
#include "discretization_push_action.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

#ifndef PULLBACK_MAP_H
#include "pullback_map.h"
#endif

namespace geometry
{
class sec_ed_invertible;
}

namespace fields
{

///
/// A discretization push action for body_pusher;
/// pulls a vertex back into the domain base space.
///
class SHEAF_DLL_SPEC body_pusher_pullback_action : public discretization_push_action
{

  // ===========================================================
  /// @name BODY_PUSHER_PULLBACK_ACTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of entry in the pullback map.
  ///
  typedef pullback_map_entry pb_type;

  ///
  /// The type for the domain evaluation member to range pullback map.
  ///
  typedef pullback_map pb_map_type;

  ///
  /// The type of iterator for the pullback map.
  ///
  typedef pb_map_type::iterator pb_map_itr_type;

  ///
  /// The type of iterator range for the pullback map.
  ///
  typedef pair<pb_map_itr_type, pb_map_itr_type> pb_map_range_type;

  // No default constructor.

  ///
  /// Creates an instance using global coordinates xdomain_coords
  /// and pullback map xmap.
  ///
  body_pusher_pullback_action(geometry::sec_ed_invertible& xglobal_coords,
                              pb_map_type& xmap);

  // Default memberwise copy constructor will do.

  ///
  /// Destructor
  ///
  virtual ~body_pusher_pullback_action();

  ///
  /// The push action.
  ///
  virtual void operator () (const scoped_index& xdisc_id,
                            block<sec_vd_value_type>& xglobal_coords);

  ///
  /// The global coordinates of the domain.
  ///
  geometry::sec_ed_invertible& domain_coords();

private:

  ///
  /// The global coordinates of the domain.
  ///
  geometry::sec_ed_invertible& _domain_coords;

  ///
  /// A buffer for domain chart points.
  ///
  block<chart_point_3d> _domain_pts;

  ///
  /// The pullback map.
  ///
  pb_map_type& _pb_map;

  ///
  /// A preallocated pullback object for use by operator().
  ///
  pb_type _pb;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef BODY_PUSHER_PULLBACK_ACTION_H
