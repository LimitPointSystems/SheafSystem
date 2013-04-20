

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class chart_point_2d

#ifndef CHART_POINT_2D_H
#define CHART_POINT_2D_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CHART_POINT_H
#include "chart_point.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A point in a 2D chart space.
///
class SHEAF_DLL_SPEC chart_point_2d : public chart_point
{
  // ===========================================================
  /// @name CHART_POINT_2D FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  chart_point_2d();

  ///
  /// Copy constructor
  ///
  ///
  chart_point_2d(const chart_point_2d& xother);

  ///
  /// Destructor.
  ///
  virtual ~chart_point_2d();

  ///
  /// Creates an instance with chart_id() == xchart_id, u() == xu.  v() == xv.
  ///
  chart_point_2d(pod_index_type xchart_id, coord_type xu, coord_type xv);

  ///
  /// Creates an instance with chart_id() == xchart_id.hub_pod,
  /// u() == xu.  v() == xv.
  ///
  chart_point_2d(const scoped_index& xchart_id, coord_type xu, coord_type xv);

  ///
  /// Creates an instance with chart_id() == xchart_id and
  /// local_coord(i) == xlocal_coords[i].
  ///
  chart_point_2d(pod_index_type xchart_id,
                 const coord_type* xlocal_coords,
                 size_type xlocal_coords_ub);

  ///
  /// Creates an instance with chart_id() == xchart.hub_pod() and
  /// local_coord(i) == xlocal_coords[i].
  ///
  chart_point_2d(const scoped_index& xchart_id,
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
  /// The 0-th local coordinate of this.
  ///
  const coord_type& u() const;

  ///
  /// The 1-th local coordinate of this.
  ///
  const coord_type& v() const;

  ///
  /// Sets chart_id() == xchart_id, u() == xu, v() == xv.
  ///
  void put(pod_index_type xchart, coord_type xu, coord_type xv);

  ///
  /// Sets chart_id() == xchart_id.hub_pod(), u() == xu, v() == xv.
  ///
  void put(const scoped_index& xchart_id, coord_type xu, coord_type xv);

protected:

  ///
  /// The local coordinates of this point
  ///
  coord_type _local_coords[2];

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
  virtual chart_point_2d* clone() const;

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
  chart_point_2d& operator=(const chart_point& xother)
  {
    return reinterpret_cast<chart_point_2d&>(chart_point::operator=(xother));
  };

  ///
  /// Assignment operator
  ///
  ///
  chart_point_2d& operator=(const chart_point_2d& xother);

protected:

private:

  //@}
};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// The deep size of the referenced object of type chart_point_2d.
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC
size_t deep_size(const chart_point_2d& xp, bool xinclude_shallow = true);

} // namespace fiber_bundle


#endif // ifndef CHART_POINT_2D_H