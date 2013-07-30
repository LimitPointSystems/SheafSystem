
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

// Interface for class eval_iterator


#ifndef EVAL_ITERATOR_H
#define EVAL_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DEPTH_FIRST_ITERATOR_H
#include "depth_first_iterator.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h" // just to get typedefs
#endif

namespace sheaf
{
class index_space_handle;
}

namespace fiber_bundle
{

using namespace sheaf;


class eval_family;
class section_space_schema_member;
class section_evaluator;
class sec_rep_descriptor;

///
/// An iterator over the members of the evaluation subposet
/// contained in the downset of the base space of a section_space_schema_member.
/// Extracts the connectivity (that is, the discretization members in
/// the downset) of each evaluation member.
///
class SHEAF_DLL_SPEC eval_iterator : public depth_first_iterator
{
public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator.
  ///
  eval_iterator();

  ///
  /// Copy constructor
  ///
  eval_iterator(const eval_iterator& xother);

  ///
  /// Destructor
  ///
  ~eval_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual eval_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xschema_anchor.base_space()
  /// with visit_once() == xvisit_once.
  ///
  eval_iterator(const section_space_schema_member& xschema_anchor, bool xvisit_once = true);

  // ITERATOR FACET

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  virtual bool is_initialized() const;

  ///
  /// Force the iterator to be done.
  ///
  virtual void force_is_done();

  ///
  /// Makes this the next member of the subset.
  ///
  inline void next()
  {
    next(false);
  }

  ///
  /// Makes this the next member of the subset.
  /// If xtruncate, new this is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  ///
  void next(bool xtruncate);

  // EVALUATION ITERATOR FACET

  ///
  /// The schema member whose base space is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  section_space_schema_member& schema_anchor();

  ///
  /// The schema member whose base space is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  const section_space_schema_member& schema_anchor() const;

  ///
  /// Set schema_anchor() to the same state as xschema_anchor.
  ///
  void put_schema_anchor(const section_space_schema_member& xschema_anchor);

  ///
  /// Set schema_anchor() to the member identified by xschema_anchor_index.
  ///
  void put_schema_anchor(pod_index_type xschema_anchor_index);

  ///
  /// Set schema_anchor() to the member identified by xschema_anchor_index.
  ///
  void put_schema_anchor(const scoped_index& xschema_anchor_index);

  ///
  /// The host of the anchor (mutable version).
  ///
  base_space_poset& base_space();

  ///
  /// The host of the anchor (const version).
  ///
  const base_space_poset& base_space() const;

  ///
  /// The dimension of the current evaluation member.
  ///
  int db() const;

  ///
  /// The type id of the current evaluation member.
  ///
  pod_index_type type_id() const;

  ///
  /// The client id of the current evaluation member.
  ///
  scoped_index client_id() const;

  ///
  /// The section evaluator associated with the current evaluation member (mutable version).
  ///
  section_evaluator& evaluator();

  ///
  /// The section evaluator associated with the current evaluation member (const version).
  ///
  const section_evaluator& evaluator() const;

  ///
  /// The discretization members in the downset of the current evaluation member (mutable version).
  ///
  block<scoped_index>& discretization_members();

  ///
  /// The discretization members in the downset of the current evaluation member (const version).
  ///
  const block<scoped_index>& discretization_members() const;

  ///
  /// The client id of the xi-th discretization member
  /// in the downset of the current evaluation member.
  ///
  scoped_index discretization_client_id(size_type xi);

  ///
  /// Gathers the dofs for the current evalaution member from section xsec
  /// and appends them to the back of xdofs.
  ///
  void gather_dofs(const sec_vd& xsec, block<sec_vd::dof_type>& xdofs);

  ///
  /// Scatters the dofs for the current evalaution member from the
  /// location xindex and following of xdofs into section xsec.
  ///
  void scatter_dofs(sec_vd& xsec, const block<sec_vd::dof_type>& xdofs, size_type xindex);

protected:

  ///
  /// Initializes the schema anchor.
  ///
  void initialize_schema_anchor(const section_space_schema_member& xanchor);


private:

  ///
  /// The schema member whose base space is being iterated over;
  /// the top member of the domain of iteration.
  ///
  section_space_schema_member* _schema_anchor;

  ///
  /// The host of the anchor.
  ///
  base_space_poset* _base_space;

  ///
  /// True if down set collection is enabled.
  ///
  bool _down_set_collection_enabled;

  ///
  /// The evaluator family associated with schema_anchor().
  ///
  eval_family* _evaluators;

  ///
  /// The discretization members in the downset of the current evaluation member.
  ///
  block<scoped_index> _discretization_members;

  ///
  /// The non-discretization members in the down set of the current eval member.
  ///
  block<scoped_index> _non_discretization_members;

  ///
  /// The index of the current evaluation member.
  ///
  scoped_index _evaluator_id;

  ///
  /// The index of the current maximal evaluation member.
  /// Same as above _evaluator_id except used to terminate
  /// post action.
  ///
  scoped_index _maximal_eval_id;

  ///
  /// True if d == 2 and discretization is vertices.
  ///
  bool _vertex_discretization;

  ///
  /// True if discretization member order reversal is enabled
  /// for the current evaluation member.
  ///
  bool _disc_reversal_enabled;

  ///
  /// The id space for the evaluation subposet.
  ///
  index_space_handle* _eval_id_space;

  ///
  /// The id space for the discretization subposet.
  ///
  index_space_handle* _disc_id_space;

  ///
  /// The evaluation subposet.
  ///
  subposet* _eval_sp;

  ///
  /// The discretization subposet.
  ///
  subposet* _disc_sp;

  ///
  /// The monovalent subposet, if any.
  ///
  subposet* _mono_sp;

  ///
  /// Sets local pointers to schema variables.
  ///
  void put_schema_variables();

};

} // namespace fiber_bundle

#endif // ifndef EVAL_ITERATOR_H
