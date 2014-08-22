
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

/// @file
/// Interface for class field_eval_iterator


#ifndef FIELD_EVAL_ITERATOR_H
#define FIELD_EVAL_ITERATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DEPTH_FIRST_ITERATOR_H
#include "ComLimitPoint/sheaf/depth_first_iterator.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_H
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

namespace fiber_bundle
{
class base_space_poset;
class eval_family;
class section_space_schema_member;
class section_evaluator;
class sec_rep_descriptor;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
  
class field_vd;

///
/// An iterator which concurrently traverses the schema of both the
/// coordinates and property sections of a field. The two schema
/// must share the same base space and evaluation subposet.
///
class SHEAF_DLL_SPEC field_eval_iterator : public depth_first_iterator
{

  // ===========================================================
  /// @name FIELD_EVAL_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an iterator over the schema of xfield.
  ///
  field_eval_iterator(const field_vd& xfield);

  ///
  /// Creates an iterator anchored at xcoordinate_schema_anchor.base_space().
  ///
  field_eval_iterator(
    const section_space_schema_member& xcoordinate_schema_anchor,
    const section_space_schema_member& xproperty_schema_anchor);

  ///
  /// Destructor.
  ///
  ~field_eval_iterator();

  ///
  /// The coordinates field schema member which is being iterated over.
  ///
  section_space_schema_member& coordinate_schema_anchor() const;

  ///
  /// The property field schema member which is being iterated over.
  ///
  section_space_schema_member& property_schema_anchor() const;

  ///
  /// The base space shared by both schema.
  ///
  const base_space_poset& base_space() const;

  ///
  /// The evaluation subposet shared by both schema.
  ///
  const subposet& evaluation() const;

  ///
  /// The dimension of the current evaluation member.
  ///
  int db() const;

  ///
  /// The type id of the current member.
  ///
  pod_index_type type_id() const;

  ///
  /// The type name of the current member.
  ///
  std::string type_name() const;

  ///
  /// The coordinate field evaluator associated
  /// with the current evaluation member.
  ///
  section_evaluator& coordinate_evaluator() const;

  ///
  /// The property field evaluator associated
  /// with the current evaluation member.
  ///
  section_evaluator& property_evaluator() const;

  ///
  /// The coordinate discretization members in
  /// the downset of the current evaluation member.
  ///
  const block<scoped_index>& coordinate_discretization_members() const;

  ///
  /// The property discretization members in
  /// the downset of the current evaluation member.
  ///
  const block<scoped_index>& property_discretization_members() const;

  ///
  /// True if xhub_id is the hub id of a property discretization member
  /// that has been visited previously.
  ///
  bool property_has_been_visited(pod_index_type xhub_id) const;

  ///
  /// True if xid is the id of a property discretization member
  /// that has been visited previously.
  ///
  bool property_has_been_visited(const scoped_index& xid) const;

  ///
  /// Gather the coordinate dofs for the current
  /// evaluation member from xcoord into xdofs.
  ///
  void gather_coordinate_dofs(const sec_vd& xcoord,
                              block<sec_vd::dof_type>& xdofs);

  ///
  /// The refinement depth; the number of evaluation members
  /// the current evaluation member is contained in.
  ///
  size_type refinement_depth() const;

  ///
  /// Updates capacity of internal data structures to
  /// match any changes in the size of the base space. Only needed
  /// in traversals that modify the base space, e.g. refinement.
  ///
  void update_capacity();

  ///
  /// True if the internal data structures have enough
  /// capacity for the current size of base_space().
  ///
  bool enough_capacity() const;

protected:

  ///
  /// Initializes the coordinate schema anchor.
  ///
  void initialize_coordinate_schema(const section_space_schema_member& xanchor);

  ///
  /// Initializes the property schema anchor.
  ///
  void initialize_property_schema(const section_space_schema_member& xanchor);

  ///
  /// Initializes the set of evaluation member prototypes
  /// for which the discretization member order correction is applied.
  ///
  void initialize_discretization_order_correction();

  ///
  /// Ensures correct order of the discretization members.
  ///
  void ensure_discretization_order(block<scoped_index>& xdisc_mbrs);

private:

  ///
  /// Default constructor; disabled.
  ///
  field_eval_iterator() {};

  ///
  /// Copy constructor; disabled.
  ///
  field_eval_iterator(const field_eval_iterator& xother) {};

  ///
  /// The schema of the coordinate field.
  ///
  section_space_schema_member* _coordinate_schema_anchor;

  ///
  /// The schema of the property field.
  ///
  section_space_schema_member* _property_schema_anchor;

  ///
  /// The base space shared by both schema.
  ///
  base_space_poset* _base_space;

  ///
  /// The evaluation subposet shared by both schema.
  ///
  subposet _evaluation;

  ///
  /// True if down set collection is enabled.
  ///
  bool _down_set_collection_enabled;

  ///
  /// The evaluator family associated with coordinate_schema_anchor().
  ///
  eval_family* _coordinate_evaluators;

  ///
  /// The evaluator family associated with property_schema_anchor().
  ///
  eval_family* _property_evaluators;

  ///
  /// The coordinate discretization members in the downset of the current evaluation member.
  ///
  block<scoped_index> _coordinate_discretization_members;

  ///
  /// The property discretization members in the downset of the current evaluation member.
  ///
  block<scoped_index> _property_discretization_members;

  ///
  /// Markers for property discretization members that have been visited previously.
  ///
  zn_to_bool* _property_has_been_visited;

  ///
  /// The non-discretization members in the down set of the current eval member.
  ///
  block<scoped_index> _non_discretization_members;

  ///
  /// The index of the current evaluation member.
  ///
  scoped_index _evaluator_id;

  ///
  /// The refinement depth of the current evaluation member.
  ///
  int _evaluator_refinement_depth;

  ///
  /// True if coordinate discretization is vertices.
  ///
  bool _coordinate_vertex_discretization;

  ///
  /// True if coordinate discretization member order
  /// correction is enabled for the current evaluation member.
  ///
  bool _coordinate_correction_enabled;

  ///
  /// True if property discretization is vertices.
  ///
  bool _property_vertex_discretization;

  ///
  /// True if property discretization member order
  /// correction is enabled for the current evaluation member.
  ///
  bool _property_correction_enabled;

  ///
  /// The set of evaluation member prototypes for which
  /// connectivity order correction is applied.
  ///
  std::set<pod_index_type> _correction_set;

  ///
  /// The initial size of the downset collection buffers.
  ///
  //  static const int BUFFER_UB = 16;
  enum static_const_int {BUFFER_UB = 16};


  ///
  /// The depth of the original, unrefined zone on the current path.
  ///
  int _top_zone_depth;

  //@}


  // ===========================================================
  /// @name DEPTH_FIRST_ITERATOR FACET
  // ===========================================================
  //@{

public:

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
  virtual void next(bool xtruncate);

  ///
  /// Repeats the iteration over the down set of index().
  /// If index() refers to a zone that has just been refined and
  /// removed from the evaluation subposet, call with xwas_eval_member == true,
  /// so this will update_capacity() and properly increment refinement_depth().
  ///
  void repeat(bool xwas_eval_member);

  ///
  /// Restarts the iteration.
  ///
  virtual void reset(bool xreset_markers = true);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual field_eval_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  //@}

};

} // namespace fields

#endif // ifndef FIELD_EVAL_ITERATOR_H
