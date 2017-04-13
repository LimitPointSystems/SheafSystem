
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
/// Interface for class chart_point

#ifndef CHART_POINT_H
#define CHART_POINT_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "SheafSystem/any.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "SheafSystem/fiber_bundle.h"
#endif

#ifndef SCOPED_INDEX_H
#include "SheafSystem/scoped_index.h"
#endif

#ifndef STD_IOSTREAM_H
#include "SheafSystem/std_iostream.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A point in chart space.
///
class SHEAF_DLL_SPEC chart_point : public any
{
  // ===========================================================
  /// @name CHART_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of local coordinate;
  /// the scalar type for the local coordinate vector space.
  ///
  typedef chart_point_coord_type coord_type;


  ///
  /// Factory method; creates a chart point with db() == xdb.
  ///
  static chart_point* new_chart_point(int xdb);

  ///
  /// Destructor.
  ///
  virtual ~chart_point();

  ///
  /// The id of the chart this point is in.
  ///
  pod_index_type chart_id() const;

  ///
  /// Sets chart_id() to xchart_id.
  ///
  void put_chart_id(pod_index_type xchart);

  ///
  /// Sets chart_id() to xchart_id.hub_pod().
  ///
  void put_chart_id(const scoped_index& xchart);

  ///
  /// The dimension of this chart.
  ///
  virtual int db() const = 0;

  ///
  /// The xi-th local coordinate of this point
  ///
  virtual coord_type local_coord(int xi) const = 0;

  ///
  /// Sets the xi-th local coordinate of this point to xvalue.
  ///
  virtual void put_local_coord(int xi, coord_type xvalue) = 0;

  ///
  /// The array of local coordinates.
  ///
  virtual coord_type* local_coords() = 0;

  ///
  /// The array of local coordinates.
  ///
  virtual const coord_type* local_coords() const = 0;

  ///
  /// Sets the local coordinates to the values in xvalues.
  ///
  void put_local_coords(const coord_type* xvalues, size_type xvalues_ub);

  ///
  /// Sets the local coordinates to the zero vector.
  ///
  void put_local_coords_zero();

  ///
  /// True if this ia a valid point in a chart.
  ///
  bool is_valid() const;

  ///
  /// Makes this invalid.
  ///
  void invalidate();

protected:

  ///
  /// Default constructor.
  ///
  chart_point();

  ///
  /// The id of the chart this point is in.
  ///
  pod_index_type _chart_id;

private:

  ///
  /// Copy constructor; disbaled
  ///
  ///
  chart_point(const chart_point& xother);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================

public:

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual chart_point* clone() const = 0;

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
  ///
  chart_point& operator=(const chart_point& xother);

  ///
  /// Equality operator.
  ///
  bool operator==(const chart_point& xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DEBUGGING FACET
  // ===========================================================

public:

  ///
  ///  Write instance information to an ostream (default = stdout).
  ///
  void to_stream(std::ostream& xos = std::cout) const;


  ///
  /// Get instance information as a string.
  ///
  std::string to_string() const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert chart_point_1d& xpt into ostream& os.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream &os, const chart_point& xpt);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle


#endif // ifndef CHART_POINT_H
