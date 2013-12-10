
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Interface for class pullback_map

#ifndef PULLBACK_MAP_H
#define PULLBACK_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
#endif

namespace fields
{

using namespace fiber_bundle;

///
/// An entry in a discretization map.
///
class SHEAF_DLL_SPEC pullback_map_entry
{

  // =============================================================================
  /// @name PULLBACK_MAP_ENTRY FACET
  // =============================================================================
  //@{

public:

  ///
  /// The id of a discretization member
  ///
  scoped_index disc_id;

  ///
  /// The location of the discretization member.
  ///
  chart_point_3d domain_pt;

  ///
  /// Default constructor; creates an instance with unspecied values.
  ///
  pullback_map_entry() {};

  ///
  /// Creates an instance with domain_pt().chart_id == xchart_id and
  /// other values uninitalized.
  ///
  pullback_map_entry(pod_index_type xchart_id)
  {
    domain_pt.put_chart_id(xchart_id);
  };

  ///
  /// Creates an instance with domain_pt().chart_id == xchart_id.hub_pod() and
  /// other values uninitalized.
  ///
  pullback_map_entry(const scoped_index& xchart_id)
  {
    domain_pt.put_chart_id(xchart_id.hub_pod());
  };

  ///
  /// Creates an instance with disc_id == xdisc_id and domain_pt == xdomain_pt.
  ///
  pullback_map_entry(const scoped_index& xdisc_id, chart_point_3d xdomain_pt)
  {
    disc_id = xdisc_id;
    domain_pt = xdomain_pt;
  };

  ///
  /// True if domain_pt.chart == xother.domain_pt.chart;
  /// equality operator for pullback map.
  ///
  bool operator==(const pullback_map_entry& xother) const
  {
    return domain_pt.chart_id() == xother.domain_pt.chart_id();
  };

  //@}
};

///
/// A hash function class for discretization map entries.
///
struct SHEAF_DLL_SPEC discretization_hash
{
  ///
  /// Hash the chart id associated with the map entry x.
  ///
  size_t operator()(const pullback_map_entry& x) const
  {
    // Chart ids may be in different id spaces,
    // but we have to hash them in some specific
    // id space; poset internal id space is the
    // obvious candidate.

    return x.domain_pt.chart_id();
  };
};

///
/// A map from members of a discretization subposet to points in a base space.
///
class SHEAF_DLL_SPEC pullback_map : public
hash_multiset<pullback_map_entry, discretization_hash> {};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert pullback_map_entry& xentry into ostream& os.
///
std::ostream& operator<<(std::ostream& xos, const pullback_map_entry& xentry);
 
} // namespace fields

#endif // ifndef PULLBACK_MAP_H
