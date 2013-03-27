// $RCSfile: differentiable_section_evaluator.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:16:57 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class differentiable_section_evaluator

#ifndef DIFFERENTIABLE_SECTION_EVALUATOR_H
#define DIFFERENTIABLE_SECTION_EVALUATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_EVALUATOR_H
#include "section_evaluator.h"
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

#endif // ifndef DIFFERENTIABLE_SECTION_EVALUATOR_H
