
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Interface for class uniform_eval_family

#ifndef UNIFORM_EVAL_FAMILY_H
#define UNIFORM_EVAL_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EVAL_FAMILY
#include "eval_family.h"
#endif

namespace fiber_bundle
{

///
/// A family of evaluators for uniform meshes.
///
class SHEAF_DLL_SPEC uniform_eval_family : public eval_family
{

  friend class eval_family;

public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  uniform_eval_family(const uniform_eval_family& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this.
  ///
  virtual uniform_eval_family* clone() const;

  ///
  /// Destructor
  ///
  virtual ~uniform_eval_family();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  // UNIFORM_EVAL_FAMILY FACET

  ///
  /// Creates an instance containing all the uniform evaluators defined in
  /// the namespace xname_space.
  ///
  uniform_eval_family(const namespace_poset& xname_space);

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
  /// Default constructor.
  ///
  ///
  uniform_eval_family();

};

} // namespace fiber_bundle

#endif // ifndef UNIFORM_EVAL_FAMILY_H






