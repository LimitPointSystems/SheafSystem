// $RCSfile: jim_cohort.cc,v $ $Revision: 1.4 $ $Date: 2013/03/13 00:58:59 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class jim_cohort

#include "jim_cohort.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "namespace_poset.h"

using namespace geometry;


// ===========================================================
// JIM_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::jim_cohort::
jim_cohort(base_space_poset& xhost, const string& xname, const string& xmember_prototype_name)
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

  // Exit:

  return;
}

geometry::jim_cohort::
~jim_cohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}
 
geometry::jim_cohort::
jim_cohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// sheaf::scoped_index
// geometry::jim_cohort::
// new_member()
// {
//   // Preconditions:

//   require(host().in_jim_edit_mode());

//   // Body:

//   // Try to activate an inactive member.
//   // Implementation depends on fact that cover members are
//   // inserted at end of cover list but we remove at front,
//   // effectively emulating a queue.

//   scoped_index result = _host->first_cover_member(LOWER, _inactive_uc_id);
//   if(result == _inactive_lc_id)
//   {
//     // No inactive members to activate, create a new one.

//     result = _host->new_member(true, _dof_tuple_id);

//     _sp.insert_member(result);
//     _id_space->id_map<mutable_index_map>().push_back(result);

//     _cts[0]++;

//     if(auto_output_cts())
//     {
//       output_cts(cout, "newed");
//     }

//     if(auto_name_members())
//     {
//       name_member(result);
//     }
//   }
//   else
//   {
//     // Found an inactive member; delete links from inactive bounds.
//     // member and bounds should be first in each others respective cover
//     // lists, so should take O(1) time.
    
//     _host->delete_link(_inactive_uc_id, result);
//     _host->delete_link(result, _inactive_lc_id);

//     if(_host->cover_is_empty(LOWER, _inactive_uc_id))
//     {
//       // Just activated the last inactive member;
//       // Upper cover of lower bound should also be empty.

//       assertion(_host->cover_is_empty(UPPER, _inactive_lc_id));      

//       // Link upper bound to lower bound.

//       _host->new_link(_inactive_uc_id, _inactive_lc_id);
//     }

//     // Remove member from inactive subposet.

//     _inactive_sp.remove_member(result);

//     _cts[1]--;
//     _cts[2]++;

//     if(auto_output_cts())
//     {
//       output_cts(cout, "reactivated");
//     }
//   }

//   // Postconditions:

//   ensure(host().contains_member(result));
//   ensure(is_active(result));
//   ensure(host().cover_is_empty(LOWER, result));
//   ensure(host().cover_is_empty(UPPER, result));
//   ensure(sp().contains_member(result));
//   ensure(id_space().contains(result));

//   // Exit:

//   return result;
// }

// void
// geometry::jim_cohort::
// delete_member(const scoped_index& xid)
// {
//   // Preconditions:

//   require(contains(xid));
//   require(host().in_jim_edit_mode());
//   require(host().cover_is_empty(UPPER, xid));
//   require(host().cover_is_empty(LOWER, xid));
  
//   // Body:
  
//   // Make sure id used in cover links below is in
//   // the internal id space, not some client id space 
//   // from which it may be deleted.

//   scoped_index lid(_host->internal_id(xid.internal_pod()));

//   if(_host->first_cover_member(LOWER, _inactive_uc_id) == _inactive_lc_id)
//   {
//     // There are no inactive members currently;
//     // unlink the inactive upper bound from the inactive lower bound.

//     _host->delete_link(_inactive_uc_id, _inactive_lc_id);

//     // Now the upper cover of the lower bound and 
//     // the lower cover of the upper bound should be empty.

//     assertion(_host->cover_is_empty(UPPER, _inactive_lc_id));
//     assertion(_host->cover_is_empty(LOWER, _inactive_uc_id));
//   }
  
//   // Link the member between the bounds

//   _host->new_link(_inactive_uc_id, lid);
//   _host->new_link(lid, _inactive_lc_id);

//   // Insert the member in the inactive subposet.

//   _inactive_sp.insert_member(lid);

//   _cts[1]++;

//   if(auto_output_cts())
//   {
//     output_cts(cout, "deleted");
//   }

//   // Postconditions:

//   ensure(!is_active(xid));
//   ensure(sp().contains_member(xid));
//   ensure(id_space().contains(xid));
  
//   // Exit:

//   return;
// }

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, jim_cohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
