
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
/// Interface for class body_pusher.

#ifndef COM_LIMITPOINT_FIELDS_BODY_PUSHER_H
#define COM_LIMITPOINT_FIELDS_BODY_PUSHER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_H
#include "ComLimitPoint/fiber_bundle/chart_point.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_BODY_PUSHER_PULLBACK_ACTION_H
#include "ComLimitPoint/fields/body_pusher_pullback_action.h"
#endif

#ifndef COM_LIMITPOINT_GEOMETRY_SEC_ED_INVERTIBLE_H
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace fiber_bundle
{
class base_space_poset;
class base_space_member;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle; 

///
/// The general push-forward operator for base space members;
/// moves a base space member from one base space to another
/// using the map implied by the global coordinate fields on each base space.
///
class SHEAF_DLL_SPEC body_pusher : public any
{

  // ===========================================================
  /// @name BODY_PUSHER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of local coordinate variables.
  ///
  typedef sec_ed::coord_type coord_type;

  ///
  /// The type for section degrees of freedom.
  ///
  typedef sec_vd::dof_type dof_type;

  ///
  /// The type for section values.
  ///
  typedef sec_vd::value_type value_type;


  ///
  /// Creates the push-forward from the base space of
  /// xdomain_coord to the base space of xrange_coord
  /// induced by the composition xrange_coord with the
  /// inverse of xdomain_coord.
  ///
  body_pusher(const geometry::sec_ed_invertible& xdomain_coord,
              const sec_ed& xrange_coord,
              bool xauto_access);

  ///
  /// The domain of the push-forward map.
  ///
  const base_space_poset& domain() const;

  ///
  /// The coordinate field for the domain.
  ///
  const geometry::sec_ed_invertible& domain_coord() const;

  ///
  /// The range of the push-forward map.
  ///
  const base_space_poset& range() const;

  ///
  /// The coordinate field for the range.
  ///
  const sec_ed& range_coord() const;

  ///
  /// Pushes member xinput from domain() to
  /// base_space_poset range(), auto-allocated.
  ///
  base_space_member* push(const base_space_member& xinput,
                          bool xcompute_upper_bound,
                          bool xauto_access);

  ///
  /// Pushes member xinput from base_space_poset domain() to
  /// base_space_poset range(), pre-allocated.
  ///
  void push_pa(const base_space_member& xinput,
               base_space_member& result,
               bool xcompute_upper_bound,
               bool xauto_access);

  ///
  /// Pushes all members of xinput from domain() to
  /// base_space_poset range(), auto-allocated.
  ///
  subposet* push(const subposet& xinput,
                 bool xcompute_upper_bound,
                 bool xauto_access);

  ///
  /// Pushes all members of xinput from base_space_poset domain() to
  /// base_space_poset range(), pre-allocated.
  ///
  void push_pa(const subposet& xinput,
               subposet& result,
               bool xcompute_upper_bound,
               bool xauto_access);

  ///
  /// True if destination body should be named from the source body.
  ///
  const bool& push_name() const;

  ///
  /// Prefix for destination name.
  ///
  std::string& name_prefix();

  ///
  /// Suffix for destination name.
  ///
  std::string& name_suffix();

  ///
  /// True if and only if xcoord1 and xcoord2 have the same fiber type and dimension.
  ///
  bool same_fiber(const sec_ed& xcoord1, const sec_ed& xcoord2,
                  bool xauto_access) const;


protected:

  ///
  /// Default constructor; protected to prevent default construction.
  ///
  body_pusher();


private:

  ///
  /// The domain of the push-forward operator.
  ///
  base_space_poset* _domain;

  ///
  /// The coordinate field for the domain.
  ///
  geometry::sec_ed_invertible* _domain_coord;

  ///
  /// The range of the push-forward operator.
  ///
  base_space_poset* _range;

  ///
  /// The coordinate field for the range.
  ///
  sec_ed _range_coord;

  ///
  /// The section space schema used for body pushing.
  ///
  binary_section_space_schema_member* _body_schema;

  ///
  /// The mapped type in the pullback map.
  ///
  typedef body_pusher_pullback_action::pb_type pb_type;

  ///
  /// The type for the domain evaluation member to range pullback map.
  ///
  typedef body_pusher_pullback_action::pb_map_type pb_map_type;

  ///
  /// The type of iterator for the pullback map.
  ///
  typedef body_pusher_pullback_action::pb_map_itr_type pb_map_itr_type;

  ///
  /// The type of iterator range for the pullback map.
  ///
  typedef body_pusher_pullback_action::pb_map_range_type pb_map_range_type;

  ///
  /// The domain evaluation member to range pullback map.
  ///
  pb_map_type _pb_map;

  ///
  /// True if destination body should be named from the source body.
  ///
  bool _push_name;

  ///
  /// Prefix for destination name.
  ///
  std::string _name_prefix;

  ///
  /// Suffix for destination name.
  ///
  std::string _name_suffix;

  ///
  /// Pulls the range disc back into the domain.
  ///
  void pull_back_range_disc();

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Copy constructor.
  ///
  body_pusher(const body_pusher& xother);

  ///
  /// Destructor.
  ///
  virtual ~body_pusher();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef COM_LIMITPOINT_FIELDS_BODY_PUSHER_H
