
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

//
/// @file
/// Implementation for class discretization_pusher
//
#include "SheafSystem/discretization_pusher.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/chart_point.h"
#include "SheafSystem/binary_section_space_schema_member.h"
#include "SheafSystem/discretization_iterator.h"
#include "SheafSystem/discretization_push_action.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/eval_family.h"
#include "SheafSystem/eval_iterator.h"
#include "SheafSystem/postorder_iterator.h"
#include "SheafSystem/field_eval_iterator.h"
#include "SheafSystem/sec_vd.h"
#include "SheafSystem/sec_rep_descriptor.h"
#include "SheafSystem/section_evaluator.h"
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystem/structured_block_2d.h"
#include "SheafSystem/structured_block_3d.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// DISCRETIZATION_PUSHER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::discretization_pusher::
discretization_pusher()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

fields::discretization_pusher::
~discretization_pusher()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

void
fields::discretization_pusher::
push(const section_space_schema_member& xsrc,
     const sec_vd& xglobal_coord,
     discretization_push_action& xpush_action,
     bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xsrc.state_is_read_accessible());
  require(xauto_access || xglobal_coord.state_is_read_accessible());

  if(xauto_access)
  {
    xsrc.get_read_access();
    xglobal_coord.get_read_access();
  }

  require(xsrc.base_space().is_same_state(&xglobal_coord.schema().base_space()));
  require(dynamic_cast<const binary_section_space_schema_member*>\
    (&xglobal_coord.schema()));

  // Body:

  const subposet& lsrc_disc_sp  = xsrc.discretization();
  const subposet& lsrc_eval_sp  = xsrc.evaluation();
  const subposet& lcoord_disc_sp = xglobal_coord.schema().discretization();
  const subposet& lcoord_eval_sp = xglobal_coord.schema().evaluation();

  // Push discretization back into the global coordinates.

  // Implementation of the push depends on 3 conditions:
  //
  // 1) Do we need to gather the coordinate dofs?
  //    If the coord evaluation subposet contains only
  //    one member then the dofs are already gathered, otherwise
  //    we need to gather them for each eval member.
  //
  // 2) Do we need to map the local coord of the source disc to the local
  //    coord of the global coord field? If the source eval subposet is the
  //    same as the global coord, we can just feed the local coord from
  //    the range evaluator to the global coord evaluator. If the source
  //    eval subposet is finer than the global coord eval subposet, then
  //    we need a map from each source eval member to the global coord
  //    eval member that contains it.
  //
  // 3) Do we need to evaluate the global coord at the local coord
  //    associated with each source disc member? If the source and the
  //    global coord share the same disc, we can just gather the global
  //    coord dofs, we don't need to evaluate the interploation method.
  //
  // These conditions are not entirely independent. In particular,
  // if we don't need to evaluate then we don't need to map.

  bool lmust_gather   = must_gather(xsrc, xglobal_coord.schema());
  bool lmust_map      = must_map(xsrc, xglobal_coord.schema());
  bool lmust_evaluate = must_evaluate(xsrc, xglobal_coord.schema());

  /// @error Not all the combinations of lmust_gather, lmust_map and
  /// lmust_evaluate are supported.

  if(lmust_gather && lmust_map && lmust_evaluate)
  {
    post_fatal_error_message("(lmust_gather && lmust_map && lmust_evaluate) is not implemented");
  }
  else if(lmust_gather && lmust_map && !lmust_evaluate)
  {
    post_fatal_error_message("(lmust_gather && lmust_map && !lmust_evaluate) is not implemented");
  }
  else if(lmust_gather && !lmust_map && lmust_evaluate)
  {
    push_gather_no_map_evaluate(xsrc, xglobal_coord, xpush_action);
  }
  else if(lmust_gather && !lmust_map && !lmust_evaluate)
  {
    push_gather_no_map_no_evaluate(xsrc, xglobal_coord, xpush_action);
  }
  else if(!lmust_gather && lmust_map && lmust_evaluate)
  {
    push_no_gather_map_evaluate(xsrc, xglobal_coord, xpush_action);
  }
  else if(!lmust_gather && lmust_map && !lmust_evaluate)
  {
    post_fatal_error_message("(!lmust_gather && lmust_map && !lmust_evaluate) is not implemented");
  }
  else if(!lmust_gather && !lmust_map && lmust_evaluate)
  {
    post_fatal_error_message("(!lmust_gather && !lmust_map && lmust_evaluate) is not implemented");
  }
  else if(!lmust_gather && !lmust_map && !lmust_evaluate)
  {
    post_fatal_error_message("(!lmust_gather && !lmust_map && !lmust_evaluate) is not implemented");
  }

  // Postconditions:

  if(xauto_access)
  {
    xsrc.release_access();
    xglobal_coord.release_access();
  }

  // Exit:
}


// PRIVATE MEMBER FUNCTIONS

bool
fields::discretization_pusher::
must_gather(const section_space_schema_member& xrange_schema,
            const section_space_schema_member& xglobal_coord_schema) const
{
  bool result;

  // Preconditions:

  // Body:

  // True if range coord evaluation subposet contains more
  // than a single member.

  result = (xglobal_coord_schema.evaluation().member_ct() > 1);

  // Postconditions:

  // Exit:

  return result;
}

bool
fields::discretization_pusher::
must_map(const section_space_schema_member& xsrc,
         const section_space_schema_member& xglobal_coord_schema) const
{
  bool result;

  // Preconditions:

  // Body:

  const subposet& lrange_eval = xsrc.evaluation();
  const subposet& lglobal_coord_eval = xglobal_coord_schema.evaluation();

  // True if source eval is strictly finer than global coord eval.

  /// @hack assume that source eval is finer if it is not the same.
  /// @error this will work for the uniform mesh cases we are currently
  /// dealing with, but will fail in general.

  result = !lrange_eval.is_same_state(&lglobal_coord_eval);

  // Postconditions:

  // Exit:

  return result;
}

bool
fields::discretization_pusher::
must_evaluate(const section_space_schema_member& xsrc,
              const section_space_schema_member& xglobal_coord_schema) const
{
  bool result;

  // Preconditions:

  // Body:

  const subposet& lrange_disc = xsrc.discretization();
  const subposet& lglobal_coord_disc = xglobal_coord_schema.discretization();

  // True if source disc is not the same as the  global coord disc.

  result = !lrange_disc.is_same_state(&lglobal_coord_disc);

  // Postconditions:

  // Exit:

  return result;
}

void
fields::discretization_pusher::
push_gather_no_map_no_evaluate(const section_space_schema_member& xsrc,
                               const sec_vd& xglobal_coord,
                               discretization_push_action& xpush_action)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("push_gather_no_map_no_evaluate:");
#endif

  // Preconditions:

  require(xsrc.state_is_read_accessible());
  require(xglobal_coord.state_is_read_accessible());
  require(dynamic_cast<const binary_section_space_schema_member*>(&xglobal_coord.schema()));
  require(xsrc.base_space().is_same_state(&xglobal_coord.schema().base_space()));
  require(xsrc.discretization().is_same_state(&xglobal_coord.schema().discretization()));

  // Body:

  // Allocate a buffer for the global coordinate dofs associated with a disc member.
  // Binary schema requirement ensures there are df dofs for each disc member.

  /// @issue requires binary schema.

  int ldc = xglobal_coord.schema().df();
  block<sec_vd_dof_type> lcoord_dofs(ldc);
  lcoord_dofs.set_ct(ldc);

  discretization_iterator lsrc_disc_itr(xsrc);
  while(!lsrc_disc_itr.is_done())
  {
    scoped_index ldisc_id = lsrc_disc_itr.discretization_member_index();

    // Gather the global coordinate field dofs for this discretization member.
    // Uses the precondition that the source and the global coordinate
    // discretizations are the same to avoid evaluating the coordinates.

    xglobal_coord.get_fiber(ldisc_id, lcoord_dofs.base(),
			    lcoord_dofs.ub()*sizeof(sec_vd_dof_type), false);

    // Execute the push action.

    xpush_action(ldisc_id, lcoord_dofs);

    // Move to the next discretization member

    lsrc_disc_itr.next();
  }

  // Postconditions:

  // Exit:

  return;
}

void
fields::discretization_pusher::
push_gather_no_map_evaluate(const section_space_schema_member& xsrc,
                            const sec_vd& xglobal_coord,
                            discretization_push_action& xpush_action)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("push_gather_no_map_evaluate:");
#endif

  // Preconditions:

  require(xsrc.state_is_read_accessible());
  require(xglobal_coord.state_is_read_accessible());
  require(xsrc.base_space().is_same_state(&xglobal_coord.schema().base_space()));

  // Body:

  // Allocate a buffer for the global coordinate dofs associated with an eval member.
  // Binary schema requirement ensures there are df dofs for each disc member.
  // Assume some number of disc members, e.g. 32, will auto resize if needed.

  /// @issue depends on binary schema for efficiency (but not very strongly).

  block<sec_vd_dof_type> lcoord_dofs(xglobal_coord.schema().df()*32);

  // Allocate a buffer for the local and global coordinates associated
  // with a source discretization member.

  block<chart_point_coord_type> lsrc_lc(xsrc.db());
  lsrc_lc.set_ct(xsrc.db());
  block<sec_vd_dof_type> lsrc_gc(xglobal_coord.schema().df());
  lsrc_gc.set_ct(xglobal_coord.schema().df());


  field_eval_iterator litr(xglobal_coord.schema(), xsrc);
  while(!litr.is_done())
  {
    // Get the evaluators for this member of the evaluation subposet.

    section_evaluator& lsrc_evlr = litr.property_evaluator();
    section_evaluator& lcoord_evlr = litr.coordinate_evaluator();

    // Gather the global coordinate dofs for this evaluation member.

    litr.gather_coordinate_dofs(xglobal_coord, lcoord_dofs);

    // Iterate over the source discretization members for this evaluation member.

    const block<scoped_index>& lsrc_disc_ids =
      litr.property_discretization_members();
    size_type lsrc_disc_ct = lsrc_disc_ids.ct();

    for(size_type i=0; i<lsrc_disc_ct; ++i)
    {
      scoped_index ldisc_id = lsrc_disc_ids[i];

      if(!litr.property_has_been_visited(ldisc_id))
      {
        // Get the local coordinates of this discretization member.

        lsrc_evlr.local_coordinates(i, lsrc_lc.base(), lsrc_lc.ub());

        // Evaluate the global coordinates at the local coordinates
        // of this source discretization member.

        lcoord_evlr.value_at_coord(lcoord_dofs.base(),
                                   lcoord_dofs.ct(),
                                   lsrc_lc.base(),
                                   lsrc_lc.ct(),
                                   lsrc_gc.base(),
                                   lsrc_gc.ct());

        // Execute the push action.

        xpush_action(ldisc_id, lsrc_gc);
      }
    }

    // Move to the next evaluation member.

    litr.next();
  }

  // Postconditions:

  // Exit:
}


void
fields::discretization_pusher::
push_no_gather_map_evaluate(const section_space_schema_member& xsrc,
                            const sec_vd& xglobal_coord,
                            discretization_push_action& xpush_action)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("push_no_gather_map_evaluate:");
#endif

  // Preconditions:

  require(xsrc.state_is_read_accessible());
  require(xglobal_coord.state_is_read_accessible());
  require(xsrc.base_space().is_same_state(&xglobal_coord.schema().base_space()));

  // Body:

  // !must_gather implies the coordinate field has a single eval member.
  // must_map implies the eval sp of the property is finer than the coordinates,
  // which in turn implies we will have to evaluate the coordinate field.

  /// @hack the only such case we support at the current time is
  /// uniform fields on structured blocks. Use that knowledge.

  // Allocate two chart points for the property discretization members;
  // one will use the "refined" local coordinates of the property eval sp,
  // the other will use the "unrefined" local coordinates of the coordinates
  // eval sp.

  int ldb = xsrc.db();
  chart_point* lref_prop_lc = chart_point::new_chart_point(ldb);
  chart_point* lunref_prop_lc = chart_point::new_chart_point(ldb);


  // Allocate a buffer for the global coordinates associated
  // with a property discretization member.

  block<sec_vd_dof_type> lprop_gc(xglobal_coord.schema().df());
  lprop_gc.set_ct(lprop_gc.ub());

  // Allocate a buffer for the dofs of a propert disc member.

  block<sec_vd_dof_type> lprop_dofs(xsrc.df());
  lprop_dofs.set_ct(lprop_dofs.ub());

  // Get the base space for the coordinates.
  /// @hack assume its a structured block.

  structured_block* lbase;
  switch(ldb)
  {
  case 1:
    lbase = new structured_block_1d(xglobal_coord.schema().base_space());
    break;
  case 2:
    lbase = new structured_block_2d(xglobal_coord.schema().base_space());
    break;
  case 3:
    lbase = new structured_block_3d(xglobal_coord.schema().base_space());
    break;
  default:
    post_fatal_error_message("Unsupported base space dimension");
    break;
  }

  // Get the evaluator for the coordinates field.

  string lfamily_name(xglobal_coord.schema().rep().evaluator_family_name());
  eval_family* lfamily =
    eval_family::new_family(lfamily_name, *xglobal_coord.name_space());
  section_evaluator* lcoords_evlr = lfamily->member(lbase->type_id());

  // Get the dofs for the coordinates field.
  // Note that given the uniform mesh hack, this is not a large array.

  block<sec_vd_dof_type> lcoords_dofs(xglobal_coord.schema().row_dof_ct());
  lcoords_dofs.set_ct(lcoords_dofs.ub());
  xglobal_coord.dof_tuple(lcoords_dofs.base(), lcoords_dofs.ct());

#ifdef DIAGNOSTIC_OUTPUT

  cout << "  global coords dofs:";
  for(size_type c=0; c<lcoords_dofs.ub(); ++c)
  {
    cout << setw(6) << lcoords_dofs[c];
  }
  cout << endl;
#endif

  // Allocate a marker for discretization members we've already visited.

  zn_to_bool lvisited(xsrc.base_space().host()->member_index_ub().pod());

  eval_iterator lprop_eval_itr(xsrc);
  while(!lprop_eval_itr.is_done())
  {
    // Get the evaluator for this eval member.

    section_evaluator& lprop_evlr = lprop_eval_itr.evaluator();

    // Set the chart id for the refined local coordinates.

    lref_prop_lc->put_chart_id(lprop_eval_itr.index());

    // Iterate over the property discretization members for this eval member.

    block<scoped_index>& lprop_disc_ids =
      lprop_eval_itr.discretization_members();
    size_type lprop_disc_ct = lprop_disc_ids.ct();

    for(size_type i=0; i<lprop_disc_ct; ++i)
    {
      scoped_index ldisc_id = lprop_disc_ids[i];

      if(!lvisited[ldisc_id.pod()])
      {
        // Haven't evaluated this member yet.

        // Get its local coordinates in the property (refined) mesh.

        lprop_evlr.local_coordinates(i,
                                     lref_prop_lc->local_coords(),
                                     lref_prop_lc->db());

        // Map the refined local coordinates to the unrefined local coordinates.


        lbase->unrefine_point_pa(*lref_prop_lc, *lunref_prop_lc);

        // Evaluate the global coordinates at the unrefined local coordinates.

        lcoords_evlr->value_at_coord(lcoords_dofs.base(),
                                     lcoords_dofs.ct(),
                                     lunref_prop_lc->local_coords(),
                                     lunref_prop_lc->db(),
                                     lprop_gc.base(),
                                     lprop_gc.ct());

        // Execute the push action.

        xpush_action(ldisc_id, lprop_gc);


        // Mark this member so we don't process it again.

        lvisited.put(ldisc_id.pod(), true);

#ifdef DIAGNOSTIC_OUTPUT

        index_space_handle& ldisc_space = xsrc.discretization().id_space();
        cout << endl
	     << "  disc_id: " << setw(5) << ldisc_space.pod(ldisc_id)
	     << endl;

        cout << "  refined property point:" << *lref_prop_lc << endl;
        cout << "  unrefined property point:" << *lunref_prop_lc << endl;

        cout << "  disc mbr global coords:";
        for(size_type c=0; c<lprop_gc.ub(); ++c)
        {
          cout << setw(6) << lprop_gc[c];
        }
        cout << endl;
#endif

      }
    }

    // Move to the next evaluation member.

    lprop_eval_itr.next();
  }

  // Clean up.

  lbase->detach_from_state();
  delete lfamily;

  // Postconditions:

  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::discretization_pusher::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(any::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    // State has required access:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

