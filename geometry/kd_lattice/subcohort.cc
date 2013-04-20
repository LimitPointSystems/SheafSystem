

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class subcohort

#include "subcohort.h"
#include "assert_contract.h"
#include "vertex_cohort.h"
#include "base_space_poset.h"
#include "pooled_cohort.h"

using namespace geometry;

 

// ===========================================================
// SUBCOHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS 

geometry::subcohort::
subcohort(base_space_poset& xhost, const string& xname, pooled_cohort& xbase_cohort)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());
  
  // Body:

  abstract_cohort::new_state(xhost, xname);

  _base_cohort = &xbase_cohort;

  // Postconditions:

  ensure(name() == xname);
  ensure(sp().name() == name());
  ensure(id_space().name() == name());
  ensure(client_id_space().name() == name() + "_client_id_space");

  // Exit:

  return;
}

geometry::subcohort::
~subcohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}

geometry::pooled_cohort&
geometry::subcohort::
base_cohort()
{
  return *_base_cohort;
}

const geometry::pooled_cohort&
geometry::subcohort::
base_cohort() const
{
  return *_base_cohort;
}

bool
geometry::subcohort::
is_vertex_cohort() const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<vertex_cohort*>(_base_cohort) != 0;

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::subcohort::
is_active(const scoped_index& xid) const
{
  // Preconditions:

  require(host().state_is_read_accessible());
  
  // Body:

  bool result = _base_cohort->is_active(xid);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::scoped_index
geometry::subcohort::
new_member()
{
  // Preconditions:

  require(host().in_jim_edit_mode());

  define_old_variable(size_type old_ct = _ct);

  // Body:

  scoped_index result = _base_cohort->new_member();
  
  _sp.insert_member(result);
  _id_space->push_back(result);

  if(auto_name_members())
  {
    name_member(result);
  }

  ++_ct;
  
  // Postconditions:

  ensure(host().contains_member(result));
  ensure(is_active(result));
  ensure(is_vertex_cohort() ? 
	 host().first_cover_member(LOWER, result.hub_pod()) == host().bottom().index().pod() : 
	 host().cover_is_empty(LOWER, result));
  ensure(host().cover_is_empty(UPPER, result));
  ensure(sp().contains_member(result));
  ensure(id_space().contains(result));
  ensure(base_cohort().sp().contains_member(result));
  ensure(base_cohort().id_space().contains(result));
  ensure(ct() == old_ct + 1);

  // Exit:

  return result;
}

void
geometry::subcohort::
delete_member(const scoped_index& xid)
{
  // Preconditions:

  require(contains(xid));
  require(host().in_jim_edit_mode());
  require(host().cover_is_empty(UPPER, xid));
  require(is_vertex_cohort() || host().cover_is_empty(LOWER, xid));
  
  define_old_variable(size_type old_ct = _ct);

  // Body:

  if(auto_name_members())
  {
    unname_member(xid);
  }

  _id_space->remove(xid, true);
  _sp.remove_member(xid);

  _base_cohort->delete_member(xid);

  --_ct;
  
  // Postconditions:

  //  ensure(!is_active(xid));
  ensure(!sp().contains_member(xid));
  ensure(!id_space().contains(xid));
  ensure(base_cohort().sp().contains_member(xid));
  ensure(base_cohort().id_space().contains(xid));
  ensure(ct() == old_ct - 1);
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::subcohort::
subcohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, subcohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
