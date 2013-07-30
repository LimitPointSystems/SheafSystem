
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Interface for class constant_fcn_space

#ifndef CONSTANT_FCN_SPACE_H
#define CONSTANT_FCN_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef LINEAR_FCN_SPACE_H
#include "linear_fcn_space.h"
#endif

namespace fiber_bundle
{

///
/// An section evaluator with a constant value over an abstract domain.
///
class SHEAF_DLL_SPEC constant_fcn_space : public linear_fcn_space
{

  // ===========================================================
  /// @name CONSTANT_FCN_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  constant_fcn_space();

  ///
  /// Copy constructor.
  ///
  constant_fcn_space(const constant_fcn_space& xother);

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
  /// Computes the value of the derivatives of each basis function at
  /// local coordinates xlocal_coords.
  ///
  virtual void basis_derivs_at_coord(const dof_type xlocal_coords[],
                                     size_type xlocal_coords_ub);

protected:

  ///
  /// The dimension of this function space; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DL = 1};  

  ///
  /// Storage for the result of the preceeding call to basis_at_coord.
  ///
  value_type _basis_value_buffer[DL];

private:

  //@}

  // ===========================================================
  /// @name INTEGRABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  using linear_fcn_space::integrate;

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
  /// The local coordinates of the gauss point with index xindex.
  ///
  virtual void gauss_point(pod_index_type xindex,
                           coord_type xresult[],
                           size_type xresult_ub);

protected:

private:

  //@}

  // ===========================================================
  /// @name DIFFERENTIABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// First partial derivative of this with respect to
  /// local coordinate xlocal_coord_index.
  ///
  virtual void dxi_local(size_type xlocal_coord_index,
                         const dof_type xsource_dofs[],
                         size_type xsource_dofs_ub,
                         dof_type xresult_dofs[],
                         size_type xresult_dofs_ub) const;

  ///
  /// Computes the the jacobian matrix at local coordinates
  /// xlocal_coords with coordinate dofs xcoord_dofs.
  ///
  virtual void jacobian(const dof_type xcoord_dofs[],
                        size_type xcoord_dofs_ub,
                        size_type xdf,
                        const dof_type xlocal_coords[],
                        size_type xlocal_coords_ub);

  ///
  /// Computes the the determinant of the jacobian matrix at local coordinates
  /// xlocal_coords with coordinate dofs xcoord_dofs.
  ///
  virtual value_type jacobian_determinant(const dof_type xcoord_dofs[],
                                          size_type xcoord_dofs_ub,
                                          size_type xdf,
                                          const coord_type xlocal_coords[],
                                          size_type xlocal_coords_ub);

protected:

private:

  //@}

  // ===========================================================
  /// @name DOMAIN FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}

  // ===========================================================
  /// @name EVALUATION FACET
  // ===========================================================
  //@{

public:

  using linear_fcn_space::value_at_coord;

  ///
  /// Computes the value of the function at local coordinates
  /// xlocal_coords using the degrees of freedom xdofs.
  ///
  virtual void value_at_coord(const dof_type xdofs[],
                              size_type xdofs_ub,
                              const dof_type xlocal_coords[],
                              size_type xlocal_coords_ub,
                              dof_type xresult[],
                              size_type xresult_ub) const;

  ///
  /// The local coordinates of a point at which
  /// the field has the value xvalue.
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
  virtual constant_fcn_space* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  virtual constant_fcn_space& operator=(const section_evaluator& xother);

  ///
  /// Assignment operator
  ///
  constant_fcn_space& operator=(const constant_fcn_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~constant_fcn_space();

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

#endif // ifndef CONSTANT_FCN_SPACE_H
