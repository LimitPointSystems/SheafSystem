
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class section_pusher_pullback_action

#ifndef SECTION_PUSHER_PULLBACK_ACTION_H
#define SECTION_PUSHER_PULLBACK_ACTION_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef DISCRETIZATION_PUSH_ACTION_H
#include "discretization_push_action.h"
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
/// A discretization push action for section_pusher;
/// pulls a range discretization member back into the domain base space.
///
class SHEAF_DLL_SPEC section_pusher_pullback_action : public discretization_push_action
{

  // ===========================================================
  /// @name SECTION_PUSHER_PULLBACK_ACTION FACET
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
  typedef std::pair<pb_map_itr_type, pb_map_itr_type> pb_map_range_type;

  // No default constructor.

  ///
  /// Creates an instance using global coordinates xdomain_coords
  /// and pullback map xmap.
  ///
  section_pusher_pullback_action(geometry::sec_ed_invertible& xglobal_coords,
                                 pb_map_type& xmap);

  // Default memberwise copy constructor will do.

  ///
  /// Destructor
  ///
  virtual ~section_pusher_pullback_action();

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

#endif // ifndef SECTION_PUSHER_PULLBACK_ACTION_H
