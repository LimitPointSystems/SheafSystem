

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class pooled_cohort

#include "pooled_cohort.h"
#include "assert_contract.h"
#include "base_space_poset.h"

using namespace geometry;

// ===========================================================
// POOLED_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::pooled_cohort::
~pooled_cohort()
{
  // Preconditions:


  // Body:

  _inactive_sp.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

const sheaf::scoped_index&
geometry::pooled_cohort::
dof_tuple_id() const
{
  return _dof_tuple_id;
}

bool
geometry::pooled_cohort::
is_active(const scoped_index& xid) const
{
  // Preconditions:

  require(host().state_is_read_accessible());
  require(xid.is_valid());
  
  // Body:

  bool result = _sp.contains_member(xid)  && !_inactive_sp.contains_member(xid);

  // Postconditions:


  // Exit:

  return result;
}


const scoped_index&
geometry::pooled_cohort::
inactive_part_id() const
{
  return _inactive_part_id;
}

const scoped_index&
geometry::pooled_cohort::
inactive_bottom_id() const
{
  return _inactive_bottom_id;
}

const sheaf::scoped_index&
geometry::pooled_cohort::
inactive_uc_id() const
{
  return _inactive_uc_id;
}

const sheaf::scoped_index&
geometry::pooled_cohort::
inactive_lc_id() const
{
  return _inactive_lc_id;
}

const int*
geometry::pooled_cohort::
cts() const
{
  return _cts;
}

void
geometry::pooled_cohort::
output_cts(ostream& xos, const string& xaction)
{
  // Preconditions:


  // Body:

  xos << xaction << " " 
      << name() << " member" 
      << "  newed: " << _cts[0]
      << "  deleted: " << _cts[1]
      << "  recycled: " << _cts[2]
      << endl;

  // Postconditions:


  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS
 
geometry::pooled_cohort::
pooled_cohort()
{
  // Preconditions:


  // Body:

  _cts[0] = 0;
  _cts[1] = 0;
  _cts[2] = 0;

  // Postconditions:
  
  // Exit:

  return;
}

void
geometry::pooled_cohort::
initialize_inactivation_structure(const string& xname)
{
  // Preconditions:

  require(host().in_jim_edit_mode());

  // Body:

  initialize_inactive_sp();
  
  initialize_global_bounds();
  
  initialize_local_bounds(xname);

  // Postconditions:

  ensure(host().contains_member(inactive_part_id(), false));
  ensure(host().contains_member(inactive_bottom_id(), false));  
  ensure(host().contains_member(inactive_uc_id(), false));
  ensure(host().contains_member(inactive_lc_id(), false));  

  // Exit:

  return;
}

void
geometry::pooled_cohort::
initialize_inactive_sp()
{
  // Preconditions:

  require(host().state_is_read_write_accessible());
  
  // Body:

  if(_host->includes_subposet("inactive"))
  {
    _inactive_sp.attach_to_state(_host, "inactive");
  }
  else
  {
    _inactive_sp.new_state(_host, true, false);
    _inactive_sp.put_name("inactive", true, false);
  }

  // Postconditions:

  ensure(_inactive_sp.is_attached());
  
  // Exit:

  return;
}

void
geometry::pooled_cohort::
initialize_global_bounds()
{
  // Preconditions:

  require(_host->in_jim_edit_mode());

  // Body:

  scoped_index lpoint_dof_tuple_id = _host->prototype_dof_tuple_id("point", 0, true, false);
  scoped_index lpart_dof_tuple_id = _host->prototype_dof_tuple_id("part", 0, true, false);

  _host->member_id("inactive_part", _inactive_part_id, false);
  if(!_inactive_part_id.is_valid())
  {
    // Global bounds have not been created yet.

    // Create the least upper bound for all inactive members.
    // Set db to max_db so db and order relation will be consistent.

    _host->row_dof_tuple(lpart_dof_tuple_id, true)->db = _host->max_db();
    _host->new_member(true, lpart_dof_tuple_id, _inactive_part_id);
    _host->put_member_name(_inactive_part_id, "inactive_part", true, false);

    // Link inactive part below top; leave its lower cover empty.

    _host->new_link(_host->top().index(), _inactive_part_id);

    // Create the greatest lower bound for all inactive members.
    // Use point dof tuple (db == 0) so db and ordering relation will be consistent.
    // Don't want any section schema to find this "point", so don't put it in d_cells(0);

    _host->new_member(true, lpoint_dof_tuple_id, _inactive_bottom_id);
    _host->put_member_name(_inactive_bottom_id, "inactive_bottom", true, false);

    // Link inactive bottom above bottom; leave its upper cover empty.

    _host->new_link(_inactive_bottom_id, _host->bottom().index());
  }
  else
  {
    // Global bounds have been created; get the greatest loer bound.

    _host->member_id("inactive_bottom", _inactive_bottom_id, false);
  }

  // Postconditions:

  ensure(host().contains_member(inactive_part_id(), false));
  ensure(host().member_dof_tuple(inactive_part_id(), false)->db == host().max_db());
  ensure(host().contains_member(inactive_bottom_id(), false));  
  ensure(host().member_dof_tuple(inactive_bottom_id(), false)->db == 0);

  // Exit:

  return;
}

void
geometry::pooled_cohort::
initialize_local_bounds(const string& xname)
{
  // Preconditions:

  require(host().in_jim_edit_mode());

  // Body:

  scoped_index lpoint_dof_tuple_id = _host->prototype_dof_tuple_id("point", 0, true, false);
  scoped_index lpart_dof_tuple_id = _host->prototype_dof_tuple_id("part", 0, true, false);

  // Create the least upper bound for inactive members in this set.
  // Dof tuple db set to max_db above so db and order relation will be consistent.

  _host->new_member(true, lpart_dof_tuple_id, _inactive_uc_id);
  string lname = "inactive_" + xname + "_ub";
  _host->put_member_name(_inactive_uc_id, lname, true, false);

  // Create the greatest lower bound for inactive members of this set.
  // Use point dof tuple (db == 0) so db and ordering relation will be consistent.
  // Don't want any section schema to find this "point", so don't put it in d_cells(0);

  _host->new_member(true, lpoint_dof_tuple_id, _inactive_lc_id);
  lname = "inactive_" + xname + "_lb";
  _host->put_member_name(_inactive_lc_id, lname, true, false);

  // Link inactive part to upper bound to lower bound to inactive bottom.

  _host->new_link(_inactive_part_id, _inactive_uc_id);
  _host->new_link(_inactive_uc_id, _inactive_lc_id);
  _host->new_link(_inactive_lc_id, _inactive_bottom_id);

  // Postconditions:

  ensure(host().contains_member(inactive_uc_id(), false));
  ensure(host().member_dof_tuple(inactive_uc_id(), false)->db == host().max_db());
  ensure(host().contains_member(inactive_lc_id(), false));  
  ensure(host().member_dof_tuple(inactive_lc_id(), false)->db == 0);

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// ABSTRACT_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

 
sheaf::scoped_index
geometry::pooled_cohort::
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
    // Found an inactive member; delete links from inactive bounds.
    // member and bounds should be first in each others respective cover
    // lists, so should take O(1) time.
    
    _host->delete_link(_inactive_uc_id, result);
    _host->delete_link(result, _inactive_lc_id);

    if(_host->cover_is_empty(LOWER, _inactive_uc_id))
    {
      // Just activated the last inactive member;
      // Upper cover of lower bound should also be empty.

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
  ensure(host().cover_is_empty(LOWER, result));
  ensure(host().cover_is_empty(UPPER, result));
  ensure(sp().contains_member(result));
  ensure(id_space().contains(result));
  ensure(ct() == old_ct + 1);

  // Exit:

  return result;
}

void
geometry::pooled_cohort::
delete_member(const scoped_index& xid)
{
  // Preconditions:

  require(contains(xid));
  require(host().in_jim_edit_mode());
  require(host().cover_is_empty(UPPER, xid));
  require(host().cover_is_empty(LOWER, xid));
  
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
  }

  // Link the member between the bounds.

  _host->new_link(_inactive_uc_id, lid);
  _host->new_link(lid, _inactive_lc_id);

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
  ensure(ct() == old_ct - 1);
  
  // Exit:

  return;
}

void
geometry::pooled_cohort::
post_creation_action(const scoped_index& xnew_mbr_id)
{
  // cout << endl << "Entering pooled_cohort::post_creation_action." << endl;

  // Preconditions:


  // Body:

  // Does nothing in this class; intended for redefinition in descendants.

  // Postconditions:


  // Exit:

  // cout << "Leaving pooled_cohort::post_creation_action." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, pooled_cohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
