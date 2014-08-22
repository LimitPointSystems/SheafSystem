
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

// Interface for class differentiable_section_evaluator

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_DIFFERENTIABLE_SECTION_EVALUATOR_H
#define COM_LIMITPOINT_FIBER_BUNDLE_DIFFERENTIABLE_SECTION_EVALUATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SECTION_EVALUATOR_H
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#endif 

namespace fiber_bundle
{

using namespace sheaf;

///
/// An abstract section evaluator that can be differentiated.
///
class SHEAF_DLL_SPEC differentiable_section_evaluator : public section_evaluator
{

  // ===========================================================
  /// @name DIFFERENTIABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Copy constructor.
  ///
  ///
  differentiable_section_evaluator(const differentiable_section_evaluator& xother);

  ///
  /// Destructor
  ///
  virtual ~differentiable_section_evaluator();
 
  ///
  /// First partial derivative of this with respect to
  /// local coordinate xlocal_coord_index.
  ///
  virtual void dxi_local(size_type xlocal_coord_index,
                         const dof_type xsource_dofs[],
                         size_type xsource_dofs_ub,
                         dof_type xresult_dofs[],
                         size_type xresult_dofs_ub) const = 0;


  ///
  /// First partial derivative of this with respect to
  /// local coordinate xlocal_coord_index.
  ///
  void dxi_local(size_type xlocal_coord_index,
                 const block<dof_type>& xsource_dofs,
                 block<dof_type>& xresult_dofs) const;

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
  /// The result of the preceding call to jacobian.
  ///
  const value_type* jacobian_values() const;

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

  ///
  /// Default constructor
  ///
  ///
  differentiable_section_evaluator();

  ///
  /// The result of the preceding call to "jacobian".
  ///
  value_type* _jacobian_values;

private:

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual differentiable_section_evaluator* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  ///
  virtual differentiable_section_evaluator& operator=(const differentiable_section_evaluator& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// The deep size of the referenced object of type differentiable_section_evaluator.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const differentiable_section_evaluator& xe,
          bool xinclude_shallow = true);
 

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_DIFFERENTIABLE_SECTION_EVALUATOR_H
