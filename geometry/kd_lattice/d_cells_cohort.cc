// $RCSfile: d_cells_cohort.cc,v $ $Revision: 1.6 $ $Date: 2013/03/13 00:58:59 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class d_cells_cohort

#include "d_cells_cohort.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "namespace_poset.h"

using namespace geometry;


// ===========================================================
// D_CELLS_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::d_cells_cohort::
d_cells_cohort(base_space_poset& xhost, const string& xname, const string& xmember_prototype_name)
{
  // Preconditions:

  require(xhost.in_jim_edit_mode());
  require(!xname.empty());
  require(!xhost.includes_subposet(xname));
  require(!xmember_prototype_name.empty());
  require(xhost.name_space()->state_is_read_accessible());
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).state_is_read_accessible());
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).contains_member(xmember_prototype_name));
  require(unexecutable("member prototype db > 0"));
  
  // Body:

  new_state(xhost, xname, xmember_prototype_name);
  
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

  ensure(d_cells_sp().is_same_state(&xhost.d_cells(xhost.row_dof_tuple(dof_tuple_id(), false)->db)));

  // Exit:

  return;
}

geometry::d_cells_cohort::
~d_cells_cohort()
{
  // Preconditions:


  // Body:

  _d_cells_sp.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

const sheaf::subposet&
geometry::d_cells_cohort::
d_cells_sp() const
{
  return _d_cells_sp;
}

int
geometry::d_cells_cohort::
d() const
{
  return _d;
}

bool
geometry::d_cells_cohort::
d_cells_contains(const scoped_index& xid) const
{
  // cout << endl << "Entering d_cells_cohort::d_cells_contains." << endl;

  // Preconditions:
  
  require(host().state_is_read_accessible());
  require(xid.is_valid());

  // Body:

  bool result = _d_cells_sp.contains_member(xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving d_cells_cohort::d_cells_contains." << endl;
  return result;
}

bool
geometry::d_cells_cohort::
d_cells_is_active(const scoped_index& xid) const
{
  // Preconditions:

  require(host().state_is_read_accessible());
  require(xid.is_valid());
  
  // Body:

  bool result = _d_cells_sp.contains_member(xid)  && !_inactive_sp.contains_member(xid);

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
geometry::d_cells_cohort::
d_cells_cohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
// COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
geometry::d_cells_cohort::
new_state(base_space_poset& xhost, const string& xname, const string& xmember_prototype_name)
{
  // Preconditions:

  require(xhost.in_jim_edit_mode());
  require(!xname.empty());
  require(!xhost.includes_subposet(xname));
  require(!xmember_prototype_name.empty());
  require(xhost.name_space()->state_is_read_accessible());
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).state_is_read_accessible());
  require(xhost.name_space()->member_poset(xhost.prototypes_poset_name(), false).contains_member(xmember_prototype_name));
  
  // Body:

  abstract_cohort::new_state(xhost, xname);

  _dof_tuple_id = xhost.prototype_dof_tuple_id(xmember_prototype_name, 0, true, false);

  _d = xhost.row_dof_tuple(_dof_tuple_id, false)->db;
  
  _d_cells_sp.attach_to_state(&xhost.d_cells(_d));

  initialize_inactivation_structure(xname);
  
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

  ensure(d() == xhost.row_dof_tuple(dof_tuple_id(), false)->db);
  ensure(d_cells_sp().is_same_state(&xhost.d_cells(d())));

  // Exit:

  return;
}

void
geometry::d_cells_cohort::
post_creation_action(const scoped_index& xnew_mbr_id)
{
  // cout << endl << "Entering pooled_cohort::post_creation_action." << endl;

  // Preconditions:

  require(host().state_is_read_write_accessible());
  require(host().contains_member(xnew_mbr_id));
  
  // Body:

  _d_cells_sp.insert_member(xnew_mbr_id);
  _d_cells_sp.id_space().push_back(xnew_mbr_id);

  // Postconditions:

  ensure(d_cells_sp().contains_member(xnew_mbr_id));
  ensure(d_cells_sp().id_space().contains(xnew_mbr_id));
  
  // Exit:

  // cout << "Leaving pooled_cohort::post_creation_action." << endl;
  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, d_cells_cohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
