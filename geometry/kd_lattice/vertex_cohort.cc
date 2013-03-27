// $RCSfile: vertex_cohort.cc,v $ $Revision: 1.5 $ $Date: 2013/03/13 00:59:00 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class vertex_cohort

#include "vertex_cohort.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "namespace_poset.h"

using namespace geometry;

 
// ===========================================================
// VERTEX_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::vertex_cohort::
vertex_cohort(base_space_poset& xhost, const string& xname, const string& xmember_prototype_name)
{
  // Preconditions:

  require(xhost.in_jim_edit_mode());
  require(xhost.name_space()->state_is_read_accessible());
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).state_is_read_accessible());
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).contains_member("part"));
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).contains_member("point"));
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).contains_member(xmember_prototype_name));
  require(!xname.empty());
  
  // Body:

  d_cells_cohort::new_state(xhost, xname, xmember_prototype_name);

  // Store index of bottom locally for convenience and efficiency.

  _bottom_id = xhost.bottom().index();

  // Postconditions:

  ensure(name() == xname);
  ensure(sp().name() == name());
  ensure(id_space().name() == name());
  ensure(client_id_space().name() == name() + "_client_id_space");

  ensure(xhost.contains_row_dof_tuple(dof_tuple_id()));
  ensure(xhost.row_dof_tuple(dof_tuple_id(), false)->type_name == xmember_prototype_name);

  ensure(host().contains_member(inactive_part_id(), false));
  ensure(host().contains_member(inactive_bottom_id(), false));  
  ensure(host().contains_member(inactive_uc_id(), false));
  ensure(host().contains_member(inactive_lc_id(), false));  

  // Exit:

  return;
}

geometry::vertex_cohort::
~vertex_cohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::vertex_cohort::
vertex_cohort()
{
  // Preconditions:


  // Body:

  // Postconditions:
  
  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


sheaf::scoped_index
geometry::vertex_cohort::
new_member()
{
  // Preconditions:

  require(host().in_jim_edit_mode());

  define_old_variable(size_type old_ct = _ct);

  // Body:

  // Try to activate an inactive member.
  // Implementation depends on fact that cover members are
  // inserted at end of cover list but we remove at front,
  // effectively emulating a queue.

  scoped_index result;
  _host->first_cover_member(LOWER, _inactive_uc_id, result);
  if(result == _inactive_lc_id)
  {
    // No inactive members to activate, create a new one.

    _host->new_member(true, _dof_tuple_id, result);

    _sp.insert_member(result);
    _id_space->push_back(result);

    _cts[0]++;

    if(auto_output_cts())
    {
      output_cts(cout, "newed");
    }

    if(auto_name_members())
    {
      name_member(result);
    }

    post_creation_action(result);    
  }
  else
  {
    // Found an inactive member; delete links from inactive upper bound.
    // Member and bound should be first in each others respective cover
    // lists, so should take O(1) time.
    // Member is already linked to bottom, don't need to change lower cover.
    
    _host->delete_link(_inactive_uc_id, result);

    if(_host->cover_is_empty(LOWER, _inactive_uc_id))
    {
      // Just activated the last inactive member;
      // unlink the lower bound from the inactive part.

      _host->delete_link(_inactive_part_id, _inactive_lc_id);

      // Now upper cover of lower bound should be empty.

      assertion(_host->cover_is_empty(UPPER, _inactive_lc_id));      

      // Link upper bound to lower bound.

      _host->new_link(_inactive_uc_id, _inactive_lc_id);
    }

    // Remove member from inactive subposet.

    _inactive_sp.remove_member(result);

    _cts[1]--;
    _cts[2]++;

    if(auto_output_cts())
    {
      output_cts(cout, "reactivated");
    }
  }

  ++_ct;
  
  // Postconditions:

  ensure(host().contains_member(result));
  ensure(is_active(result));
  ensure(host().first_cover_member(LOWER, result.hub_pod()) == host().bottom().index().pod());
  ensure(host().cover_is_empty(UPPER, result));
  ensure(sp().contains_member(result));
  ensure(id_space().contains(result));
  ensure(ct() == old_ct + 1);

  // Exit:

  return result;
}

void
geometry::vertex_cohort::
delete_member(const scoped_index& xid)
{
  // Preconditions:

  require(contains(xid));
  require(host().in_jim_edit_mode());
  require(host().cover_is_empty(UPPER, xid));
  
  define_old_variable(size_type old_ct = _ct);

  // Body:

  // Make sure id used in cover links below is in
  // the internal id space, not some client id space 
  // from which it may be deleted.

  scoped_index lid(_host->member_id(xid.hub_pod(), false));

  if(_host->first_cover_member(LOWER, _inactive_uc_id.hub_pod()) == _inactive_lc_id.hub_pod())
  {
    // There are no inactive members currently;
    // unlink the inactive upper bound from the inactive lower bound.

    _host->delete_link(_inactive_uc_id, _inactive_lc_id);

    // Now the upper cover of the lower bound and 
    // the lower cover of the upper bound should be empty.

    assertion(_host->cover_is_empty(UPPER, _inactive_lc_id));
    assertion(_host->cover_is_empty(LOWER, _inactive_uc_id));

    // Vertices don't get linked to lower bound, see below. 
    // So relink lower bound to inactive part so it's not dangling.

    _host->new_link(_inactive_part_id, _inactive_lc_id);
  }
  
  // Link the member below the upper bound; leave it linked to 
  // bottom in order to avoid O(#vertices) search to delete link. 

  _host->new_link(_inactive_uc_id, lid);

  // Insert the member in the inactive subposet.

  _inactive_sp.insert_member(lid);

  _cts[1]++;

  if(auto_output_cts())
  {
    output_cts(cout, "deleted");
  }

  --_ct;

  // Postconditions:

  ensure(!is_active(xid));
  ensure(sp().contains_member(xid));
  ensure(id_space().contains(xid));
  ensure(unexecutable("lower cover of xid unchanged"));
  ensure(ct() == old_ct - 1);
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
geometry::vertex_cohort::
post_creation_action(const scoped_index& xnew_mbr_id)
{
  // cout << endl << "Entering vertex_cohort::post_creation_action." << endl;

  // Preconditions:

  require(host().state_is_read_write_accessible());
  require(host().contains_member(xnew_mbr_id));
  
  // Body:

  d_cells_cohort::post_creation_action(xnew_mbr_id);

  // Vertex always covers bottom.
  // Deleting from the upper cover of bottom is O(number of vertices),
  // so for efficiency, we have to link each vertex to bottom once
  // and leave it there, rather than unlinking when we inactivate
  // and relinking when we activate.

  _host->new_link(xnew_mbr_id, _bottom_id);

  // Postconditions:

  ensure(d_cells_sp().contains_member(xnew_mbr_id));
  ensure(d_cells_sp().id_space().contains(xnew_mbr_id));
  ensure(host().first_cover_member(LOWER, xnew_mbr_id.hub_pod()) == host().bottom().index().pod());
  
  // Exit:

  // cout << "Leaving vertex_cohort::post_creation_action." << endl;
  return;
}

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, vertex_cohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
