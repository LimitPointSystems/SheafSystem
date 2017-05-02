
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

//

/// @file
/// Interface for class sec_ed_invertible

#ifndef SEC_ED_INVERTIBLE_H
#define SEC_ED_INVERTIBLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SEC_ED_H
#include "SheafSystem/sec_ed.h"
#endif

#ifndef GEOMETRY_H
#include "SheafSystem/geometry.h"
#endif

namespace sheaf
{
class poset_path;
}

namespace fiber_bundle
{
class chart_point;
class chart_point_3d;
}

namespace geometry
{

class point_locator;

///
/// An abstract invertible section of a fiber bundle with a
/// d-dimensional base space and a d-dimensional Euclidean vector space fiber.
///
class SHEAF_DLL_SPEC sec_ed_invertible : public sec_ed
{

  // ===========================================================
  /// @name SEC_ED_INVERTIBLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_ed_invertible();

  ///
  /// Copy constructor; creates a new sec_ed_invertible handle
  /// and attaches it to the same state as xother.
  ///
  sec_ed_invertible(const sec_ed& xother);

  ///
  /// Creates a new sec_ed_invertible handle attached to
  /// the member state with index xindex in xhost.
  ///
  sec_ed_invertible(sec_rep_space* xhost, const scoped_index& xindex);

  ///
  /// Creates a new sec_ed_invertible handle attached to
  /// the member state with name xname in xhost.
  ///
  sec_ed_invertible(sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new sec_ed_invertible handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_ed_invertible(namespace_poset* xnamespace,
                    const poset_path& xpath,
                    bool xauto_access);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_ed_invertible& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_ed_invertible& operator=(const sec_ed_invertible& xother);

  ///
  /// Assignment operator.
  ///
  sec_ed_invertible& operator=(const ed& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_ed_invertible& operator=(const ed_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_ed_invertible();

  ///
  /// True if this is a uniform coordinate field.
  ///
  bool is_uniform() const;

  ///
  /// If true default inverter initialization uses d_array_point_locator
  /// other wise uses d_tree_point_locator. Ignored if is_uniform() true.
  /// Note that the return is a reference which can be used to change the
  /// default.
  ///*
  static bool& use_d_array_point_locator();

  ///
  /// Initializes point locater search structure using default values.
  ///
  virtual void initialize_point_locator(bool xauto_access);

  ///
  /// Initializes search structure using d_array_point_locater with
  /// bin_ub computed from size of mesh.
  ///
  virtual void initialize_d_array_point_locator(bool xauto_access);

  ///
  /// Initializes search structure using d_array_point_locater with xbin_ub[i]
  /// as the upper bound on the i-th bin index.
  ///
  virtual void initialize_d_array_point_locator(const block<size_type>& xbin_ub,
                                                bool xauto_access);

  ///
  /// Initializes search structure using d_tree_point_locater with depth
  /// computed from the size of the mesh.
  ///
  virtual void initialize_d_tree_point_locator(bool xauto_access);

  ///
  /// Initializes search structure using d_tree_point_locater with xdepth
  /// as maximum depth of the tree.
  ///
  virtual void initialize_d_tree_point_locator(size_type xdepth,
                                               bool xauto_access);

  ///
  /// Initializes search structure using d_uniform_point_locater.
  ///
  virtual void initialize_d_uniform_point_locator(bool xauto_access);

  ///
  /// Updates search structure to current value of this.
  ///
  virtual void update_inversion();

  ///
  /// True if this can be inverted.
  ///
  bool is_invertible() const;

  ///
  /// The search structure used for inversion.
  ///
  const geometry::point_locator& inverter() const;

  ///
  /// Finds a chart point which is the preimage in this of xr;
  /// auto-allocated version.
  ///
  virtual chart_point* point_at_value(const ed& xr);

  ///
  /// Finds a chart point which is the preimage in this of xvalue;
  /// pre-allocated version.
  ///
  virtual void point_at_value_pa(const ed& xvalue, chart_point& xresult);

  ///
  /// Finds a chart point which is the preimage in this of xvalue;
  /// unattached version.
  ///
  virtual void point_at_value_ua(const sec_vd_dof_type* xvalue,
                                 size_type xvalue_ub,
                                 chart_point& xresult);


  ///
  /// Finds all chart points at which this has value xvalue
  /// and appends them to xresult.
  /// Note that charts overlap at their boundaries and hence if xvalue
  /// lies on a boundary it is contained in more than one chart.
  ///
  virtual void all_points_at_value_ua(const sec_vd_value_type* xvalue,
                                      size_type xvalue_ub,
                                      block<chart_point_3d>& xresult);

  ///
  /// Finds one chart point in each branch at which this
  /// has value xvalue and appends them to xresult.
  ///
  virtual void branch_points_at_value_ua(const sec_vd_value_type* xvalue,
                                         size_type xvalue_ub,
                                         block<branch_point_pair>& xresult);

protected:

  ///
  /// Initializes handle data members when attaching
  /// to a different member in the same host.
  ///
  virtual void attach_handle_data_members();

private:

  ///
  /// The search structure for inverting this section.
  ///
  point_locator* _inverter;

  //@}


  // ===========================================================
  /// @name SEC_VD FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual sec_ed_invertible* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_ed_invertible* clone(bool xnew_state, bool xauto_access = true)
  {
    return static_cast<sec_ed_invertible*>
      (sec_ed::clone(xnew_state, xauto_access));
  }

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* other) const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};
 
} // namespace geometry

#endif // ifndef SEC_ED_INVERTIBLE_H
