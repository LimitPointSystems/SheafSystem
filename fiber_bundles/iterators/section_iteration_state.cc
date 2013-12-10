
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

// Implementation for class section_iteration_state

#include "section_iteration_state.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "block.impl.h"
#include "error_message.h"
#include "eval_family.h"
#include "section_evaluator.h"
#include "section_space_schema_member.h"
#include "section_space_schema_poset.h"
#include "sec_vd.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

///
fiber_bundle::section_iteration_state::
section_iteration_state()
{
  // Preconditions:


  // Body:

  schema = 0;
  df = 0;
  row_dof_ct = 0;
  evaluators = 0;
  is_uniform = false;
  eval_id.invalidate();
  eval_type_id = sheaf::invalid_pod_index();
  eval = 0;
  eval_mbr = 0;
  disc_to_seq_map = 0;
  next_seq_id = 0;
  local_id = sheaf::invalid_pod_index();
  vertex_discretization = false;
  correction_enabled = false;

  // Postconditions:


  // Exit:

  return;
}

///
fiber_bundle::section_iteration_state::
~section_iteration_state()
{
  // Don't delete schema, it belongs to someone else.

  if(evaluators != 0)
  {
    delete evaluators;
  }

  eval_sp.detach_from_state();

  for(int i=1; i<eval_mbrs.ct(); ++i)
  {
    structured_block* lblk = eval_mbrs[i];
    lblk->detach_from_state();
    delete lblk;
  }

  disc_sp.detach_from_state();

  if(disc_to_seq_map != 0)
  {
    delete disc_to_seq_map;
  }
}

///
void
fiber_bundle::section_iteration_state::
initialize(const section_space_schema_member& xschema)
{
  // Preconditions:

  require(xschema.state_is_read_accessible());

  // Body:

  // Anchor features.

  // Avoid clone, initialization of schema features is expensive.
  //  schema = xschema.clone(false, false);

  schema = &xschema;
  df = xschema.df();
  row_dof_ct = xschema.row_dof_ct();

  base_space_host = &xschema.host()->base_space();

  // Evaluation features.

  down_set.reserve(32); // Arbitrary, but enough to avoid small reallocations.
  visited.extend_to(base_space_host->member_index_ub().pod());

  if(evaluators == 0)
  {
    evaluators = eval_family::new_family(xschema.evaluator_family_name(),
                                         *xschema.name_space());
  }

  if(!eval_sp.is_attached())
  {
    eval_sp.attach_to_state(&xschema.evaluation());
  }

  eval_id.invalidate();
  eval = 0;

  if(eval_mbrs.ub() == 0)
  {
    eval_mbrs.reserve(4);
    eval_mbrs[0] = 0;
    eval_mbrs[1] = new structured_block_1d();
    eval_mbrs[2] = new structured_block_2d();
    eval_mbrs[3] = new structured_block_3d();
    eval_mbrs.set_ct(4);
  }

  eval_mbr = 0;

  // Discretization features.

  if(!disc_sp.is_attached())
  {
    if(xschema.evaluator_family_name() == "uniform")
    {
      /// @hack uniform rep hack. treat uniform disc as if same as eval.
      /// @todo reimplement uniform sec rep so disc is same as eval.

      is_uniform = true;
      disc_sp.attach_to_state(&xschema.evaluation());
      vertex_discretization = false;
    }
    else
    {
      is_uniform = false;
      disc_sp.attach_to_state(&xschema.discretization());
      vertex_discretization = (disc_sp.name() == "__vertices");
    }

    disc_to_seq_map = new hash_map<pod_index_type, pod_index_type>();
  }
  else
  {
    disc_to_seq_map->clear();
  }

  next_seq_id = 0;
  local_id = 0;

  // Down set gather buffers.

  // Choose some arbitrary initial size for disc buffer.
  // Should be large enough to avoid many small reallocations.

  const size_type ldisc_ub = 16;
  discretization_members.reserve(ldisc_ub);
  dofs.reserve(ldisc_ub*df);


  // Discretization order correction features.

  if(correction_set.empty())
  {
    initialize_correction_set();
  }

  correction_enabled = false;

  // Postconditions:

  // Exit

  return;
};

///
void
fiber_bundle::section_iteration_state::
initialize(const base_space_poset& xbase_space_host)
{
  // Preconditions:

  require(xbase_space_host.state_is_read_accessible());

  // Body:

  // Anchor features.

  schema = 0;
  df = 3;
  row_dof_ct = 0;

  base_space_host = &xbase_space_host;

  // Evaluation features.

  down_set.reserve(1024); // Arbitrary, but enough to avoid small reallocations.
  visited.extend_to(base_space_host->member_index_ub().pod());


  if(evaluators == 0)
  {
    evaluators = eval_family::new_family("dlinear",
                                         *base_space_host->name_space());
  }

  if(!eval_sp.is_attached())
  {
    eval_sp.attach_to_state(&base_space_host->elements());
  }

  eval_id.invalidate();
  eval = 0;

  if(eval_mbrs.ub() == 0)
  {
    eval_mbrs.reserve(4);
    eval_mbrs[0] = 0;
    eval_mbrs[1] = new structured_block_1d();
    eval_mbrs[2] = new structured_block_2d();
    eval_mbrs[3] = new structured_block_3d();
    eval_mbrs.set_ct(4);
  }

  eval_mbr = 0;

  // Discretization features.

  if(!disc_sp.is_attached())
  {
    is_uniform = false;
    disc_sp.attach_to_state(&base_space_host->vertices());
    disc_to_seq_map = new hash_map<pod_index_type, pod_index_type>();
    vertex_discretization = true;
  }
  else
  {
    disc_to_seq_map->clear();
  }

  next_seq_id = 0;
  local_id = 0;

  // Down set gather buffers.

  // Choose some arbitrary initial size for disc buffer.
  // Should be large enough to avoid many small reallocations.

  const size_type ldisc_ub = 16;

  discretization_members.reserve(ldisc_ub);
  dofs.reserve(ldisc_ub*df);

  // Discretization order correction features.

  if(correction_set.empty())
  {
    initialize_correction_set();
  }

  correction_enabled = false;

  // Postconditions:

  // Exit

  return;
};


///
void
fiber_bundle::section_iteration_state::
initialize_correction_set()
{
  // Preconditions:

  // Body:

  // The connectivity reversal trick should be applied to evaluation
  // members which are 2D and have edges in their down set. This
  // includes prototypes "triangle", "quad", "tri_shell", and "quad_shell".
  // Currently only "quad" is supported in the base_space_member_prototypes
  // poset.

  correction_set.insert(base_space_host->prototype_type_id("triangle_complex"));

  correction_set.insert(base_space_host->prototype_type_id("quad_complex"));

  // Postconditions:


  // Exit:

  return;
};


///
void
fiber_bundle::section_iteration_state::
ensure_discretization_order(const scoped_index& xgreater_index)
{
  // Preconditions:

  require(discretization_members.ct() == 2);

  // Body:

  // We assume that the current evaluator is 2-D, that its
  // downset contains edges and vertices, and that the
  // current discretization point is a vertex.
  //
  // The first evaluator to contain the edge which contains the
  // current discretization point is the evaluator which constructed
  // that edge, and it constructed that edge in a "positive"
  // orientation wrt that evaluator.  An edge in a 2-d space
  // separates that space into 2 parts.  So at most 1 other
  // evaluator can share that edge and, if it exists, that evaluator
  // views the edge as "negatively" oriented.  In addition,
  // that evaluator will be the second evaluator in the upper
  // cover of that edge.

  // greater_index() refers to the edge containing this discretization
  // point in the path from the current evaluator.  If the current
  // evaluator is the first evaluator in that edge's upper cover, then
  // it constructed the edge, and the edge is in the positive orientation.
  // Otherwise, the current evaluator did not construct the edge,
  // the edge is negatively oriented, and the discretization member
  // order should be reversed.

  pod_index_type  first_eval =
    base_space_host->first_cover_member(UPPER, xgreater_index.hub_pod());

  bool is_reversed = (eval_id != first_eval);

  if(is_reversed)
  {
    scoped_index save   = discretization_members[0].disc_id;
    discretization_members[0].disc_id = discretization_members[1].disc_id;
    discretization_members[1].disc_id = save;
  }

  // Postconditions:


  // Exit:

  return;
};

///
void
fiber_bundle::section_iteration_state::
initialize_order_correction()
{
  // Enable discretization order correction if possible.

  correction_enabled =
    vertex_discretization &&
    (correction_set.find(base_space_host->type_id(eval_id)) !=
     correction_set.end());

};

///
void
fiber_bundle::section_iteration_state::
set_and_attach_evaluation_member(const scoped_index& xindex)
{
  // Preconditions:

  require(xindex.is_hub_scope());

  // Body:

  eval_id = xindex;
  local_id = 0;
  eval_type_id = base_space_host->type_id(eval_id);
  eval = evaluators->member(eval_type_id);
  eval_mbr = eval_mbrs[base_space_host->db(eval_id)];
  eval_mbr->attach_to_state(base_space_host, eval_id);

  // Postconditions:

  ensure(eval_id == xindex);
  ensure(local_id == 0);
  ensure(eval != 0);
  ensure(eval_mbr != 0);
  ensure(eval_mbr->is_attached());

  // Exit:

  return;
}

///
void
fiber_bundle::section_iteration_state::
set_evaluation_member(const scoped_index& xindex)
{
  // Preconditions:

  require(xindex.is_hub_scope());

  // Body:

  eval_id = xindex;
  local_id = 0;
  eval_type_id = base_space_host->type_id(eval_id);
  eval = evaluators->member(eval_type_id);

  // Postconditions:

  ensure(eval_id == xindex);
  ensure(local_id == 0);
  ensure(eval != 0);

  // Exit:

  return;
}

///
void
fiber_bundle::section_iteration_state::
gather_discretization_member(const scoped_index& xindex,
                             const scoped_index& xgreater_index)
{
  // Ensure there's enough room in the buffer.

  size_type lct = discretization_members.ct();

  if(lct == discretization_members.ub())
  {
    discretization_members.reserve(2*lct);
  }

  // "Allocate" the next member in the buffer by incrementing the count.

  discretization_members.set_ct(lct+1);

  // Store the context in the new member;
  // avoid an unnecessary copy by getting a reference.

  discretization_context& ldisc_context = discretization_members[lct];
  ldisc_context.eval_id   = eval_id;
  ldisc_context.local_id  = local_id;
  ldisc_context.disc_id   = xindex;

  if(correction_enabled && (discretization_members.ct() == 2))
  {
    ensure_discretization_order(xgreater_index);
  }
}

///
void
fiber_bundle::section_iteration_state::
gather_discretization_member(const scoped_index& xindex)
{
  // Ensure there's enough room in the buffer.

  size_type lct = discretization_members.ct();

  if(lct == discretization_members.ub())
  {
    discretization_members.reserve(2*lct);
  }

  // "Allocate" the next member in the buffer by incrementing the count.

  discretization_members.set_ct(lct+1);

  // Store the context in the new member;
  // avoid an unnecessary copy by getting a reference.

  discretization_context& ldisc_context = discretization_members[lct];
  ldisc_context.eval_id   = eval_id;
  ldisc_context.local_id  = local_id;
  ldisc_context.disc_id   = xindex;
}

///
void
fiber_bundle::section_iteration_state::
gather_dofs(const sec_vd& xsec)
{
  // Preconditions:

  require(xsec.state_is_read_accessible());
  //  require(xsec.schema().is_same_state(schema));

  // dofs ub and  indexing below only correct for binary schema.
  /// @todo revise when ternary schema are supported.

  require(dynamic_cast<const binary_section_space_schema_member*>(&xsec.schema()) != 0);


  // Body:

  if(is_uniform)
  {
    /// @hack uniform rep hack. treat uniform disc as if same as eval.
    /// @todo reimplement uniform sec rep so disc is same as eval.

    size_type ldofs_ct = row_dof_ct;
    dofs.reserve(row_dof_ct);
    xsec.dof_tuple(dofs.base(), row_dof_ct);
    dofs.set_ct(row_dof_ct);
  }
  else
  {
    size_type ldisc_ct = discretization_members.ct();

    dofs.reserve(ldisc_ct*df);

    size_type ldofs_ct = 0;
    size_type ldofs_ub = dofs.ub();
    sec_vd::dof_type* ldofs = dofs.base();

    for(size_type i=0; i<ldisc_ct; ++i)
    {
      scoped_index ldisc_id = discretization_members[i].disc_id;
      xsec.get_fiber(ldisc_id, ldofs, ldofs_ub*sizeof(sec_vd::dof_type), false);
      ldofs += df;
      ldofs_ct += df;
      ldofs_ub -= df;
    }

    dofs.set_ct(ldofs_ct);
  }



  // Postconditions:


  // Exit:

  return;
}

///
void
fiber_bundle::section_iteration_state::
gather_dofs(const sec_vd& xsec, const block<discretization_context>& xother_pts)
{
  // Preconditions:

  require(xsec.state_is_read_accessible());
  //  require(xsec.schema().is_same_state(schema));
  require_for_all(i, 0, xother_pts.ct(), disc_sp.contains_member(xother_pts[i].disc_id));

  /// @hack required because discretization_context::values capacity is fixed at 3.

  require(df <= 3);


  // Body:

  size_type lother_ct = xother_pts.ct();
  for(size_type i=0; i<lother_ct; ++i)
  {
    discretization_context& lcontext = xother_pts[i];
    xsec.get_fiber(lcontext.disc_id, lcontext.values, 
		   3*sizeof(sec_vd::dof_type), false);
  }

  // Postconditions:


  // Exit:

  return;
}

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

