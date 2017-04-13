
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
/// Interface for class chart_point_1d

#ifndef CHART_POINT_1D_H
#define CHART_POINT_1D_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef CHART_POINT_H
#include "SheafSystem/chart_point.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A point in a 1D chart space.
///
class SHEAF_DLL_SPEC chart_point_1d : public chart_point
{
  // ===========================================================
  /// @name CHART_POINT_1D FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  chart_point_1d();

  ///
  /// Copy constructor
  ///
  ///
  chart_point_1d(const chart_point_1d& xother);

  ///
  /// Destructor.
  ///
  virtual ~chart_point_1d();

  ///
  /// Creates an instance with chart_id() == xchart_id, u() == xu.
  ///
  chart_point_1d(pod_index_type xchart_id, coord_type xu);

  ///
  /// Creates an instance with chart_id() == xchart.hub_pod(), u() == xu.
  ///
  chart_point_1d(const scoped_index& xchart_id, coord_type xu);

  ///
  /// Creates an instance with chart_id() == xchart_id and
  /// local_coord(i) == xlocal_coords[i].
  ///
  chart_point_1d(pod_index_type xchart_id,
                 const coord_type* xlocal_coords,
                 size_type xlocal_coords_ub);

  ///
  /// Creates an instance with chart_id() == xchart_id.hub_pod() and
  /// local_coord(i) == xlocal_coords[i].
  ///
  chart_point_1d(const scoped_index& xchart_id,
                 const coord_type* xlocal_coords,
                 size_type xlocal_coords_ub);

  ///
  /// The dimension of this chart.
  ///
  virtual int db() const;

  ///
  /// The xi-th local coordinate of this point
  ///
  virtual coord_type local_coord(int xi) const;

  ///
  /// Sets the xi-th local coordinate of this point to xvalue.
  ///
  virtual void put_local_coord(int xi, coord_type xvalue);

  ///
  /// The array of local coordinates.
  ///
  coord_type* local_coords();

  ///
  /// The array of local coordinates, const version.
  ///
  const coord_type* local_coords() const;

  ///
  /// The 0-th (and only) local coordinate of this; mutable version.
  ///
  coord_type& u();

  ///
  /// The 0-th (and only) local coordinate of this; const version.
  ///
  const coord_type& u() const;

  ///
  /// Sets chart_id() == xchart_id, u() == xu.
  ///
  void put(pod_index_type xchart_id, coord_type xu);

  ///
  /// Sets chart_id() == xchart_id.hub_pod(), u() == xu.
  ///
  void put(const scoped_index& xchart_id, coord_type xu);

protected:

  ///
  /// The local coordinates of this point
  ///
  coord_type _local_coords[1];

private:

  //@}


  // ===========================================================
  /// @name CHART_POINT FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================

public:

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual chart_point_1d* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Assignment operator
  ///
  chart_point_1d& operator=(const chart_point& xother)
  {
    return reinterpret_cast<chart_point_1d&>(chart_point::operator=(xother));
  };

  ///
  /// Assignment operator
  ///
  chart_point_1d& operator=(const chart_point_1d& xother);

protected:

private:

  //@}
};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// The deep size of the referenced object of type chart_point_1d.
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC
size_t deep_size(const chart_point_1d& xp, bool xinclude_shallow = true);

  
} // namespace fiber_bundle

#endif // ifndef CHART_POINT_1D_H
