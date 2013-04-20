
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class section_iteration_state

#ifndef SECTION_ITERATION_STATE_H
#define SECTION_ITERATION_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef DISCRETIZATION_CONTEXT_H
#include "discretization_context.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;


class structured_block;
class eval_family;
class section_evaluator;
class section_space_schema_member;
class sec_vd;

///
/// Descriptor for iteration state of individual section.
/// Intended for implementing various iterators, especially
/// concurrent iterations over multiple sections.
///
class SHEAF_DLL_SPEC section_iteration_state
{
public:
  ///
  /// The schema of the section.
  ///
  const section_space_schema_member* schema;

  ///
  /// The fiber dimension.
  ///
  int df;

  ///
  /// The row dof count.
  ///
  int row_dof_ct;

  ///
  /// The host of the base space of the section.
  ///
  const base_space_poset* base_space_host;

  ///
  /// The strict down set of the evalaution member.
  ///
  block<scoped_index> down_set;

  ///
  /// Markers for this section.
  ///
  zn_to_bool visited;

  ///
  /// The evaluator family associated with schema.
  ///
  eval_family* evaluators;

  /// @hack uniform rep hack; the following member is needed
  /// only to support the hack.

  ///
  /// True if evaluator family is uniform evaluator family.
  ///
  bool is_uniform;

  ///
  /// The evaluation subposet associated with schema.
  ///
  subposet eval_sp;

  ///
  /// The index of the current evaluation member.
  ///
  scoped_index eval_id;

  ///
  /// The type id of the current eval member.
  ///
  pod_index_type eval_type_id;

  ///
  /// The current evaluator
  ///
  section_evaluator* eval;

  ///
  /// A family of evaluation member handles.
  ///
  block<structured_block*> eval_mbrs;

  ///
  /// The current evaluation member handle.
  ///
  structured_block* eval_mbr;

  ///
  /// The discretization subposet associated with schema.
  ///
  subposet disc_sp;

  ///
  /// The map from discretization to sequence ids.
  ///
  hash_map<pod_index_type, pod_index_type>* disc_to_seq_map;

  ///
  /// The next sequence id.
  ///
  pod_index_type next_seq_id;

  ///
  /// The local index of the current disc member
  /// with respect to the current eval member.
  ///
  int local_id;

  ///
  /// True if discretization is vertices.
  ///
  bool vertex_discretization;

  ///
  /// The discretization members in the
  /// downset of the current evaluation member.
  ///
  block<discretization_context> discretization_members;

  ///
  /// Buffer for dofs of gathered disc members.
  ///
  block<sec_vd_dof_type> dofs;

  ///
  /// The set of evaluation member prototypes for which
  /// connectivity order correction is applied.
  ///
  set<pod_index_type> correction_set;

  ///
  /// True if discretization member order
  /// correction is enabled for the current evaluation member.
  ///
  bool correction_enabled;

  ///
  /// True

  ///
  /// Default constructor.
  ///
  section_iteration_state();

  ///
  /// Destructor.
  ///
  ~section_iteration_state();

  ///
  /// Inializes an instance with schema xschema.
  ///
  void initialize(const section_space_schema_member& xschema);

  ///
  /// Inializes an instance with base space xbase_space_host.
  ///
  void initialize(const base_space_poset& xbase_space_host);

  ///
  /// Initializes the set of evaluation member prototypes
  /// for which the discretization member order correction is applied.
  ///
  void initialize_correction_set();

  ///
  /// Ensures correct order of the discretization members.
  ///
  void ensure_discretization_order(const scoped_index& xgreater_index);

  ///
  /// Previsit action for eval_sp members.
  ///
  void initialize_order_correction();

  ///
  /// Sets eval_id to xindex, initializes local_id and eval, and attaches eval_mbr.
  ///
  void set_and_attach_evaluation_member(const scoped_index& xindex);

  ///
  /// Sets eval_id to xindex, initializes local_id and eval.
  ///
  void set_evaluation_member(const scoped_index& xindex);

  ///
  /// Puts xindex into the discretization gather buffer
  /// and, if enabled, corrects discretization order
  ///
  void gather_discretization_member(const scoped_index& xindex,
                                    const scoped_index& xgreater_index);

  ///
  /// Puts xindex into the discretization gather buffer.
  ///
  void gather_discretization_member(const scoped_index& xindex);

  ///
  /// Gathers dofs from xsec into the dofs buffer.
  ///
  void gather_dofs(const sec_vd& xsec);

  ///
  /// Gathers dofs from xsec into xother_pts.
  ///
  void gather_dofs(const sec_vd& xsec, const block<discretization_context>& xother_pts);
};


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================


} // namespace fiber_bundle

#endif // ifndef SECTION_ITERATION_STATE_H
