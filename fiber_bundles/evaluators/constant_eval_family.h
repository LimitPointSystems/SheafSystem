// $RCSfile: constant_eval_family.h,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:16:57 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class constant_eval_family

#ifndef CONSTANT_EVAL_FAMILY_H
#define CONSTANT_EVAL_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EVAL_FAMILY
#include "eval_family.h"
#endif

namespace fiber_bundle
{

///
/// A family of section evaluators containing
/// members for constant functions on primitive cells.
///
class SHEAF_DLL_SPEC constant_eval_family : public eval_family
{

  friend class eval_family;

public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  constant_eval_family(const constant_eval_family& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual constant_eval_family* clone() const;

  ///
  /// Destructor
  ///
  virtual ~constant_eval_family();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  // CONSTANT_EVAL_FAMILY FACET

  ///
  /// Creates an instance containing all the dlinear evaluators defined in
  /// the namespace xname_space.
  ///
  constant_eval_family(const namespace_poset& xname_space);

  ///
  /// The name of this family.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class of families.
  ///
  static const string& static_class_name();

  ///
  /// Initializes this to contain members for name space xname_space.
  ///
  virtual void initialize(const namespace_poset& xname_space);

  ///
  /// True if the dofs used by the members of this family are section values,
  /// that is, the evaluators are interpolation functions.
  ///
  virtual bool dofs_are_values() const;

  ///
  /// True if the extrema (minima or maxima) of the members of this family
  /// occur at the discretization points.
  ///
  virtual bool extrema_are_dofs() const;

private:

  ///
  /// Default constructor; disabled.
  ///
  ///
  constant_eval_family();

};

} // namespace fiber_bundle

#endif // ifndef CONSTANT_EVAL_FAMILY_H






