
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

// Interface for class linear_3d

#ifndef LINEAR_3D_H
#define LINEAR_3D_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef LINEAR_FCN_SPACE_H
#include "SheafSystem/linear_fcn_space.h"
#endif

namespace fiber_bundle
{

///
/// A section evaluator using linear interpolation
/// over a tetrahedral 3D domain.
///
class SHEAF_DLL_SPEC linear_3d : public linear_fcn_space
{

  // ===========================================================
  /// @name LINEAR_3D FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  linear_3d();

  ///
  /// Copy constructor.
  ///
  linear_3d(const linear_3d& xother);

  ///
  /// Destructor.
  ///
  virtual ~linear_3d();


  //   ///
  ///   ///
  //   ///
  //   double inverse_jacobian(const double xjacobian[3][3],
  //                           double xinverse_jacobian[3][3]);

  //   ///
  ///   ///
  //   ///
  //   double determinant(const dof_type xcoord_dofs[],
  //                      size_type xcoord_dofs_ub,
  //                      const coord_type xlocal_coords[],
  //                      size_type xlocal_coords_ub);

protected:

  double determinant_3x3(double a00, double a01, double a02,
                         double a10, double a11, double a12,
                         double a20, double a21, double a22);

private:

  ///
  /// The dimension of this function space; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DL = 4};  

  ///
  /// Storage for the result of the preceeding call to basis_at_coord.
  ///
  value_type _basis_value_buffer[DL];

  ///
  /// Storage for the result of the preceeding call to basis_derivs_at_coord.
  ///
  value_type _basis_deriv_value_buffer[3*DL];

  ///
  /// Storage for the result of the preceeding call to jacobian.
  ///
  //value_type _jacobian_value_buffer[4];
  value_type _jacobian_value_buffer[128]; ///@todo Fix!

  //block<int[2]> _jacobian_value_block;
  //vector<int[2]> _jacobian_value_vector;

  //@}

  // ===========================================================
  /// @name CONSTANT_FCN_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}

  // ===========================================================
  /// @name LINEAR_FCN_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The dimension of this function space.
  ///
  virtual int dl() const;

  ///
  /// Computes the value of each basis function at local coordinates xlocal_coord.
  ///
  virtual void basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub);

  ///
  ///
  ///
  void basis_derivs_at_coord(const dof_type xlocal_coords[],
                             size_type xlocal_coords_ub);

protected:

private:

  //@}

  // ===========================================================
  /// @name INTEGRABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Determinant of Jacobian matrix (square)
  ///
  value_type jacobian_determinant(const dof_type xcoord_dofs[],
                                  size_type xcoord_dofs_ub,
                                  size_type xdf,
                                  const coord_type xlocal_coords[],
                                  size_type xlocal_coords_ub);

  value_type volume(const dof_type xcoord_dofs[],
                    size_type xcoord_dofs_ub, size_type xdf);

  ///
  /// Computes the value of the integral of the integrand array...
  ///
  virtual void integrate(const dof_type xcoord_dofs[],
                         size_type xcoord_dofs_ub,
                         size_type xdf,
                         const dof_type xintegrands[],
                         size_type xintegrands_ub,
                         value_type xresult_integrals[],
                         size_type xresult_integrals_ub);

  ///
  /// Computes the value of the integral of the integrand...
  ///
  virtual void integrate(const dof_type xcoord_dofs[],
                         size_type xcoord_dofs_ub,
                         size_type xdf,
                         const dof_type xintegrand,
                         value_type xresult_integrals[],
                         size_type xresult_integrals_ub);

protected:

  void gauss_point(pod_index_type xindex,
                   coord_type xresult[],
                   size_type xresult_ub);

private:

  //@}

  // ===========================================================
  /// @name DIFFERENTIABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// 1st partial derivative of this with respect to local coordinate xcrd.
  ///
  virtual void dxi_local(size_type xcrd,
                         const dof_type xsource_dofs[],
                         size_type xsource_dofs_ub,
                         dof_type xresult_dofs[],
                         size_type xresult_dofs_ub) const;

  ///
  /// Jacobian matrix
  ///
  void jacobian(const dof_type xcoord_dofs[],
                size_type xcoord_dofs_ub,
                size_type xdf,
                const dof_type xlocal_coords[],
                size_type xlocal_coords_ub);

  //   ///
  ///   ///
  //   ///
  //   double jacobian(const dof_type xcoord_dofs[],
  //                   size_type xcoord_dofs_ub,
  //                   const coord_type xlocal_coords[],
  //                   size_type xlocal_coords_ub,
  //                   double xjacobian[3][3] = NULL);

protected:

private:

  //@}

  // ===========================================================
  /// @name DOMAIN FACET
  // ===========================================================
  //@{

public:

  ///
  /// The base dimension; the dimension of the
  /// local coordinates (independent variable).
  ///
  virtual int db() const;

  ///
  /// The local coordinates of the dof with local index xindex.
  ///
  virtual void local_coordinates(pod_index_type xindex,
                                 coord_type xresult[],
                                 size_type xresult_ub) const;
  ///
  /// The local coordinates at the center of the evaluator.
  ///
  virtual void center(coord_type xresult[], size_type xresult_ub) const;

  ///
  /// Return true if the specified local coordinates are in the "standard"
  /// domain; otherwise return false.
  ///
  virtual bool in_standard_domain(const dof_type xlocal_coords[],
                                  size_type xlocal_coords_ub) const;

protected:

private:

  //@}

  // ===========================================================
  /// @name EVALUATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The local coordinates of a point at which
  /// the field has the value xvalue.
  /// The dofs are assumed to be interleaved (x0, y0, z0, x1, y1, z1, ...).
  ///
  virtual void coord_at_value(const dof_type xdofs[],
                              size_type xdofs_ub,
                              const dof_type xglobal_coords[],
                              size_type xglobal_coord_ub,
                              dof_type xlocal_coords[],
                              size_type xlocal_coords_ub) const;

protected:

private:

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, creates a new instance of the same type as this.
  ///
  virtual linear_3d* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual linear_3d& operator=(const section_evaluator& xother);

  ///
  /// Assignment operator
  ///
  linear_3d& operator=(const linear_3d& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

protected:

private:

  //@}

};

} // namespace fiber_bundle

#endif // ifndef LINEAR_3D_H
