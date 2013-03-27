// $RCSfile: kd_zone_cohort.cc,v $ $Revision: 1.4 $ $Date: 2013/03/13 00:59:00 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_zone_cohort

#include "kd_zone_cohort.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "cohort.h"
#include "geometry_namespace.h"
#include "kd_lattice.h"
#include "kd_zone.h"
#include "namespace_poset.h"

using namespace geometry;

 
// ===========================================================
// KD_ZONE_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_zone_cohort::
kd_zone_cohort(kd_lattice& xkd_host, const string& xname)
{
  // Preconditions:

  require(xkd_host.base_space().in_jim_edit_mode());
  require(!xname.empty());
  require(xkd_host.name_space().state_is_read_accessible());
  require(xkd_host.name_space().member_poset(xkd_host.base_space().prototypes_poset_name(), false).state_is_read_accessible());
  require(xkd_host.name_space().member_poset(xkd_host.base_space().prototypes_poset_name(), false).contains_member("part"));
  require(xkd_host.name_space().member_poset(xkd_host.base_space().prototypes_poset_name(), false).contains_member("point"));
  require(xkd_host.name_space().member_poset(xkd_host.base_space().prototypes_poset_name(), false).contains_member(kd_zone::prototype_name()));
  
  // Body:

  d_cells_cohort::new_state(xkd_host.base_space(), xname, kd_zone::prototype_name());

  // Set the alignment in the dof tuple.

  kd_member::row_dofs_type* ldof_tuple = 
    reinterpret_cast<kd_member::row_dofs_type*>(_host->row_dof_tuple(_dof_tuple_id, true));
  ldof_tuple->alignment = NOT_AXIS_ALIGNED;

  // Set the data members.

  _kd_host = &xkd_host;

  // Postconditions:

  ensure(&kd_host() == &(xkd_host));
  ensure(&host() == &(xkd_host.base_space()));
  ensure(name() == xname);
  ensure(sp().name() == name());
  ensure(id_space().name() == name());
  ensure(client_id_space().name() == name() + "_client_id_space");

  ensure(host().contains_row_dof_tuple(dof_tuple_id()));
  ensure(host().row_dof_tuple(dof_tuple_id(), false)->type_name == kd_zone::prototype_name());

  ensure(host().contains_member(inactive_part_id(), false));
  ensure(host().contains_member(inactive_bottom_id(), false));  
  ensure(host().contains_member(inactive_uc_id(), false));
  ensure(host().contains_member(inactive_lc_id(), false));  

  // Exit:

  return;
}

geometry::kd_zone_cohort::
~kd_zone_cohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}

geometry::kd_lattice&
geometry::kd_zone_cohort::
kd_host()
{
  return *_kd_host;
}

const geometry::kd_lattice&
geometry::kd_zone_cohort::
kd_host() const
{
  return *_kd_host;
}

void
geometry::kd_zone_cohort::
unleaf(const scoped_index& xid)
{
  // cout << endl << "Entering kd_zone_cohort::unleaf." << endl;

  // Preconditions:

  // Body:

  _host->jims().remove_member(xid);
  _kd_host->leaves().remove_member(xid, false);
  _kd_host->zone_leaves().remove_member(xid, false);

  // Postconditions:

  ensure(!host().jims().contains_member(xid));
  ensure(!kd_host().leaves().contains(xid));
  ensure(!kd_host().zone_leaves().contains(xid));

  // Exit:

  // cout << "Leaving kd_zone_cohort::unleaf." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_zone_cohort::
kd_zone_cohort()
{
  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:
  
  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
geometry::kd_zone_cohort::
post_creation_action(const scoped_index& xnew_mbr_id)
{
  // cout << endl << "Entering kd_zone_cohort::post_creation_action." << endl;

  // Preconditions:

  require(host().state_is_read_write_accessible());
  require(host().contains_member(xnew_mbr_id));
  
  // Body:

  d_cells_cohort::post_creation_action(xnew_mbr_id);

  _kd_host->leaves().insert_member(xnew_mbr_id);

  _kd_host->zone_leaves().insert_member(xnew_mbr_id);

  // Postconditions:

  ensure(d_cells_sp().contains_member(xnew_mbr_id));
  ensure(d_cells_sp().id_space().contains(xnew_mbr_id));
  ensure(host().jims().contains_member(xnew_mbr_id));
  ensure(kd_host().leaves().contains(xnew_mbr_id));
  ensure(kd_host().zone_leaves().contains(xnew_mbr_id));
  
  // Exit:

  // cout << "Leaving kd_zone_cohort::post_creation_action." << endl;
  return;
}

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, kd_zone_cohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
