
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

// Interface for class constant_point

#ifndef CONSTANT_POINT_H
#define CONSTANT_POINT_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef CONSTANT_FCN_SPACE_H
#include "SheafSystem/constant_fcn_space.h"
#endif

namespace fiber_bundle
{

///
/// A section evaluator with a constant value over a 1D domain.
///
class SHEAF_DLL_SPEC constant_point : public constant_fcn_space
{

  // ===========================================================
  /// @name CONSTANT_POINT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  constant_point();

  ///
  /// Copy constructor.
  ///
  constant_point(const constant_point& xother);

protected:

private:

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

protected:

  ///
  /// The base dimension; the dimension of the
  /// local coordinates (static const version).
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum domain_constants {DB=0};

  /// @hack For point, db = 0 and there really aren't any derivatives,
  /// but we don't gaurd against that exceptional case, so
  /// just allocate a single value; see also constant_fcn_space::basis_derivs_at_coord.

  ///
  /// Storage for the result of the preceeding call to basis_derivs_at_coord.
  ///
  value_type _basis_deriv_value_buffer[DL];

private:

  //@}

  // ===========================================================
  /// @name INTEGRABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Volume for specified coordinate dofs xcoord_dofs
  /// and fiber space dimension xdf.
  ///
  virtual value_type volume(const dof_type xcoord_dofs[],
                            size_type xcoord_dofs_ub,
                            size_type xdf); 

protected:

private:

  //@}

  // ===========================================================
  /// @name DIFFERENTIABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

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
  virtual constant_point* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual constant_point& operator=(const section_evaluator& xother);

  ///
  /// Assignment operator
  ///
  constant_point& operator=(const constant_point& xother);

  ///
  /// Destructor.
  ///
  virtual ~constant_point();

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

#endif // ifndef CONSTANT_POINT_H
