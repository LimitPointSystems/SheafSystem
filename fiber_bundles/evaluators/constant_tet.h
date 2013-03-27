// $RCSfile: constant_tet.h,v $ $Revision: 1.20 $ $Date: 2013/03/20 21:56:05 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class constant_tet

#ifndef CONSTANT_TET_H
#define CONSTANT_TET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CONSTANT_FCN_SPACE_H
#include "constant_fcn_space.h"
#endif

namespace fiber_bundle
{

///
/// A section evaluator with a constant value
/// over a tetrahedral 3D domain.
///
class SHEAF_DLL_SPEC constant_tet : public constant_fcn_space
{

  // ===========================================================
  /// @name CONSTANT_TET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  constant_tet();

  ///
  /// Copy constructor.
  ///
  constant_tet(const constant_tet& xother);

  ///
  /// Destructor.
  ///
  virtual ~constant_tet();


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
  enum domain_constants {DB=3};

  ///
  /// Storage for the result of the preceeding call to basis_derivs_at_coord.
  ///
  value_type _basis_deriv_value_buffer[int(DB)*int(DL)];

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
  virtual constant_tet* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual constant_tet& operator=(const section_evaluator& xother);

  ///
  /// Assignment operator
  ///
  constant_tet& operator=(const constant_tet& xother);

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

#endif // ifndef CONSTANT_TET_H
