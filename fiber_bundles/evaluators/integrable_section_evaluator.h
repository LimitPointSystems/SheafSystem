// $RCSfile: integrable_section_evaluator.h,v $ $Revision: 1.10 $ $Date: 2013/03/20 21:56:05 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class integrable_section_evaluator

#ifndef INTEGRABLE_SECTION_EVALUATOR_H
#define INTEGRABLE_SECTION_EVALUATOR_H

#ifndef DIFFERENTIABLE_SECTION_EVALUATOR_H
#include "differentiable_section_evaluator.h"
#endif

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

///
/// An abstract section evaluator with a bounded domain 
/// that supports integration (volume calculation) as well as
/// differntiation. 
///
class SHEAF_DLL_SPEC integrable_section_evaluator : public differentiable_section_evaluator
{

  // ===========================================================
  /// @name INTEGRABLE_SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Copy constructor.
  ///
  ///
  integrable_section_evaluator(const integrable_section_evaluator& xother);

  ///
  /// Destructor
  ///
  virtual ~integrable_section_evaluator();

  ///
  /// Volume for specified coordinate dofs xcoord_dofs
  /// and fiber space dimension xdf.
  ///
  virtual value_type volume(const dof_type xcoord_dofs[],
                            size_type xcoord_dofs_ub,
                            size_type xdf) = 0; 

  ///
  /// Computes the value of the integral of the integrand array...
  ///
  virtual void integrate(const dof_type xcoord_dofs[],
                         size_type xcoord_dofs_ub,
                         size_type xdf,
                         const dof_type xintegrands[],
                         size_type xintegrands_ub,
                         value_type xresult_integrals[],
                         size_type xresult_integrals_ub) = 0;

  ///
  /// Computes the value of the integral of the integrand...
  ///
  virtual void integrate(const dof_type xcoord_dofs[],
                         size_type xcoord_dofs_ub,
                         size_type xdf,
                         const dof_type xintegrand,
                         value_type xresult_integrals[],
                         size_type xresult_integrals_ub);

  ///
  /// The local coordinates of the gauss point with index xindex.
  ///
  virtual void gauss_point(pod_index_type xindex,
                           coord_type xresult[],
                           size_type xresult_ub) = 0;

protected:

  ///
  /// Default constructor
  ///
  ///
  integrable_section_evaluator();

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
  /// @name ANY FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual integrable_section_evaluator* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  ///
  virtual integrable_section_evaluator& operator=(const integrable_section_evaluator& xother);

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
/// The deep size of the referenced object of type integrable_section_evaluator.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const integrable_section_evaluator& xe,
          bool xinclude_shallow = true);


} // namespace fiber_bundle

#endif // ifndef INTEGRABLE_SECTION_EVALUATOR_H
