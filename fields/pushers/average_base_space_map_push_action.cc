// $RCSfile: average_base_space_map_push_action.cc,v $ $Revision: 1.18 $ $Date: 2013/01/12 17:17:26 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class average_base_space_map_push_action

#include "average_base_space_map_push_action.h"

#include "assert_contract.h"
#include "block.h"
#include "error_message.h"
#include "index_space_iterator.h"
#include "preorder_iterator.h"
#include "sec_vd.h"
#include "section_space_schema_poset.h"

using namespace fields; // Workaround for MS C++ bug.


// =============================================================================
// AVERAGE_BASE_SPACE_MAP_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::average_base_space_map_push_action::
average_base_space_map_push_action()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}




fields::average_base_space_map_push_action::
~average_base_space_map_push_action()
{
  // Preconditions:


  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}


// =============================================================================
// BASE_SPACE_MAP_PUSH_ACTION FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::average_base_space_map_push_action::
operator()(pullback_map::iterator& xitr,
           block<sec_vd*>& xoutputs,
           block< block<sec_vd_dof_type>* >& xout_dofs)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering average_base_space_map_push_action::operator()");
#endif

  // Preconditions:

  require(xoutputs.ct() > 0);
  require(xout_dofs.ct() >= xoutputs.ct());
  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_accessible());
  require_for_all(i, 0, xoutputs.ct(), xout_dofs[i]->ub() >= xoutputs[i]->schema().df());

  // Body:

  for(int lout_id = 0; lout_id<xoutputs.ct(); ++lout_id)
  {
    sec_vd& loutput = *xoutputs[lout_id];

    sec_vd_dof_type* lout_dofs_base = _out_dofs[lout_id].base();
    int lout_dofs_ct = _out_dofs[lout_id].ct();

    sec_vd_dof_type* xout_dofs_base = xout_dofs[lout_id]->base();
    int xout_dofs_ct = xout_dofs[lout_id]->ct();

    loutput.get_fiber(xitr->disc_id, lout_dofs_base,
		      lout_dofs_ct*sizeof(sec_vd_dof_type), false);

#ifdef DIAGNOSTIC_OUTPUT

    cout << "disc id: " << setw(4) << xitr->disc_id
    << " _out_dofs: " << _out_dofs[lout_id];
#endif

    for(int i=0; i<xout_dofs_ct; ++i)
    {
      xout_dofs_base[i] += lout_dofs_base[i];
    }

    ++_branch_cts[xitr->disc_id.pod()];

#ifdef DIAGNOSTIC_OUTPUT

    cout << " xout_dofs: " << *xout_dofs[lout_id]
    << " ct: " << _branch_cts[xitr->disc_id]
    << endl;
#endif

  }

  // Postconditions:

  ensure(unexecutable("xdst_dofs += xdst dofs"));

  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving average_base_space_map_push_action::operator()");
#endif

  return;
}


void
fields::average_base_space_map_push_action::
initialize(block<sec_vd*>& xoutputs)
{
  // Preconditions:

  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_write_accessible());

  // Body:


  section_space_schema_member& lschema0 = xoutputs[0]->schema();

  _disc_id_space = &lschema0.discretization().id_space();

  int lid_ub = lschema0.host()->base_space().member_index_ub().pod();

  _branch_cts.reserve(lid_ub);
  _branch_cts.set_ct(lid_ub);
  _branch_cts.assign(0);

  int lct = xoutputs.ct();

  _out_dofs.reserve(lct);
  _out_dofs.set_ct(lct);

  for(int i=0; i<lct; ++i)
  {
    sec_vd& loutput = *xoutputs[i];
    section_space_schema_member& lschema = loutput.schema();

    block<sec_vd_dof_type>& lout_dofs = _out_dofs[i];
    lout_dofs.reserve(lschema.df());
    lout_dofs.set_ct(lschema.df());
    lout_dofs.assign(0.0);

    // Initialize the output section to zero.

    //loutput.zero_sa();
    assign(loutput, 0.0, false);
  }

  // Postconditions:


  // Exit:

  return;
}

void
fields::average_base_space_map_push_action::
finalize(block<sec_vd*>& xoutputs)
{
  // Preconditions:

  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_write_accessible());

  // Body:

  // Normalize the accumulated dofs for each output.

  for(int lout_id=0; lout_id<xoutputs.ct(); ++lout_id)
  {
    sec_vd& loutput = *xoutputs[lout_id];

    sec_vd_dof_type* lout_dofs_base = _out_dofs[lout_id].base();
    int lout_dofs_ct = _out_dofs[lout_id].ct();

    // Normalize the accumulated dofs for this output.

    pod_index_type lindex;

    index_space_iterator& litr =
      loutput.schema().discretization_id_space().get_iterator();
    while(!litr.is_done())
    {
      lindex = litr.pod();

      loutput.get_fiber(lindex, lout_dofs_base,
			lout_dofs_ct*sizeof(sec_vd_dof_type));

      int lbranch_ct = _branch_cts[_disc_id_space->hub_pod(lindex)];

      if(lbranch_ct != 0)
      {
	for(int k=0; k<lout_dofs_ct; ++k)
	{
	  lout_dofs_base[k] /= lbranch_ct;
	}
      }

      loutput.put_fiber(lindex, lout_dofs_base,
			lout_dofs_ct*sizeof(sec_vd_dof_type));
    }

    loutput.schema().discretization_id_space().release_iterator(litr);
  }

  // Postconditions:


  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::average_base_space_map_push_action::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const average_base_space_map_push_action*>(xother) != 0;

  // Postconditions:

  return result;
}

fields::average_base_space_map_push_action*
fields::average_base_space_map_push_action::
clone() const
{
  average_base_space_map_push_action* result;

  // Preconditions:

  // Body:

  result = new average_base_space_map_push_action(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::average_base_space_map_push_action&
fields::average_base_space_map_push_action::
operator=(const base_space_map_push_action& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fields::average_base_space_map_push_action&
fields::average_base_space_map_push_action::
operator=(const average_base_space_map_push_action& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::average_base_space_map_push_action::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(base_space_map_push_action::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

