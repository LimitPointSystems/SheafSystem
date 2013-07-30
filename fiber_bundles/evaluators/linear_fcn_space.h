
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

// Interface for class linear_fcn_space

#ifndef LINEAR_FCN_SPACE_H
#define LINEAR_FCN_SPACE_H

#ifndef INTEGRABLE_SECTION_EVALUATOR_H
#include "integrable_section_evaluator.h"
#endif

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

 
namespace fiber_bundle
{

///
/// An abstract integrable section evaluator which is a member of a linear function space.
///
class SHEAF_DLL_SPEC linear_fcn_space : public integrable_section_evaluator
{

  // ===========================================================
  /// @name LINEAR_FCN_SPACE FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Copy constructor.
  ///
  linear_fcn_space(const linear_fcn_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~linear_fcn_space();

  ///
  /// The dimension of this function space.
  ///
  virtual int dl() const = 0;

  ///
  /// Computes the value of each basis function at local coordinates xlocal_coords.

  virtual void basis_at_coord(const dof_type xlocal_coords[],
                              size_type xlocal_coords_ub) = 0;

  ///
  /// Computes the value of the derivatives of each basis function at
  /// local coordinates xlocal_coords.
  ///
  virtual void basis_derivs_at_coord(const dof_type xlocal_coords[],
                                     size_type xlocal_coords_ub) = 0;

  ///
  /// The result of the preceding call to basis_at_coord.
  ///
  const value_type* basis_values() const;

  ///
  /// The result of the preceding call to basis_derivs_at_coord.
  ///
  const value_type* basis_deriv_values() const;

protected:

  ///
  /// Default constructor.
  ///
  linear_fcn_space();

  ///
  /// The result of the preceding call to basis_at_coord.
  ///
  value_type* _basis_values;

  ///
  /// The result of the preceding call to basis_derivs_at_coord.
  ///
  value_type* _basis_deriv_values;

private:

  //@}

  // ===========================================================
  /// @name EVALUATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of dofs required for each
  /// component of the dependent variable.
  ///
  virtual size_type dof_ct() const;

  using integrable_section_evaluator::value_at_coord;
  
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
  virtual linear_fcn_space* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  virtual linear_fcn_space& operator=(const section_evaluator& xother);

  ///
  /// Assignment operator
  ///
  linear_fcn_space& operator=(const linear_fcn_space& xother);

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

#endif // ifndef LINEAR_FCN_SPACE_H
