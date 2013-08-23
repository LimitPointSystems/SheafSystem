
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

// Interface for class eval_family

#ifndef EVAL_FAMILY_H
#define EVAL_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BASE_SPACE_MEMBER_H
#include "base_space_member.h"
#endif

#ifndef AUOTO_BLOCK_H
#include "auto_block.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
template <class T> class factory;
class poset;
class poset_state_handle;
}

namespace fiber_bundle
{

using namespace sheaf;


class section_evaluator;

///
/// A family of compatible section evaluators, one for
/// each member of some family of cell types;
/// a map from cell type to section evaluator.
///
class SHEAF_DLL_SPEC eval_family : public any
{

public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  eval_family(const eval_family& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual eval_family* clone() const;

  ///
  /// Destructor
  ///
  virtual ~eval_family();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  // EVALUATOR_FAMILY FACET

  ///
  /// Creates an instance of the evaluator family associated with name xname.
  ///
  static eval_family* new_family(const string& xname);

  ///
  /// Creates an instance of the evaluator family associated with name xname
  /// and initialized with name space, xname_space.
  ///
  static eval_family* new_family(const string& xname, const namespace_poset& xname_space);

  ///
  /// Inserts xprototype in family_factory().
  ///
  static void insert_family_prototype(eval_family* xprototype);

  ///
  /// A factory for making eval_family objects.
  ///
  static factory<eval_family>& family_factory();

  ///
  /// The name of this family.
  ///
  virtual const string& class_name() const = 0;

  ///
  /// The evaluator associated with cell type xtype_id.
  /// Note that the result may be void.
  ///
  section_evaluator* member(pod_index_type xtype_id) const;

  ///
  /// The evaluator associated with cell type xtype_id.
  /// Note that the result may be void.
  ///
  template <typename S>
  S* member(pod_index_type xtype_id) const;

  ///
  /// The evaluator associated with the cell with
  /// hub id xhub_id in host xhost.
  /// Note that the result may be void.
  ///
  section_evaluator* member(const poset_state_handle& xhost, pod_index_type xhub_id);

  ///
  /// The evaluator associated with the cell with
  /// id xid in host xhost.
  /// Note that the result may be void.
  ///
  section_evaluator* member(const poset_state_handle& xhost, const scoped_index& xid);

  ///
  /// The evaluator associated with the cell with
  /// hub id xhub_id in host xhost.
  /// Note that the result may be void.
  ///
  template <typename S>
  S* member(const poset_state_handle& xhost, pod_index_type xhub_id);

  ///
  /// The evaluator associated with the cell with
  /// id xid in host xhost.
  /// Note that the result may be void.
  ///
  template <typename S>
  S* member(const poset_state_handle& xhost, const scoped_index& xd);

  ///
  /// The number of members of this family.
  ///
  size_type size() const;

  ///
  /// Initializes this to contain members for name space xname_space.
  ///
  virtual void initialize(const namespace_poset& xname_space) = 0;

  ///
  /// True if this has been populated with members.
  ///
  bool is_initialized() const;

  ///
  /// True if the dofs used by the members of this family are section values,
  /// that is, the evaluators are interpolation functions.
  ///
  virtual bool dofs_are_values() const = 0;

  ///
  /// True if the extrema (minima or maxima) of the members of this family
  /// occur at the discretization points.
  ///
  virtual bool extrema_are_dofs() const = 0;

protected:

  ///
  /// Default constructor.
  ///
  ///
  eval_family();

  ///
  /// Initialize storage for the members.
  ///
  void initialize_members(size_type xmembers_ub);

  ///
  /// Type of storage for members.
  ///
  typedef auto_block<section_evaluator*, zero_block_initialization_policy<section_evaluator*> > members_type;

  ///
  /// The members of the family.
  ///
  members_type _members;

  ///
  /// True if this has been populated with members.
  ///
  bool _is_initialized;

private:

  ///
  /// Initializes family factory with prototypes 
  /// for all families defined by system.
  ///
  static factory<eval_family>& initialize_family_factory();
};

} // namespace fiber_bundle

#endif // ifndef EVAL_FAMILY_H






