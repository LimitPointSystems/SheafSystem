

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class cohort

#include "cohort.h"
#include "array_index_space_state.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "std_sstream.h"

using namespace geometry;

// ===========================================================
// COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::cohort::
cohort(base_space_poset& xhost, const string& xname, bool xauto_update_id_space)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  _auto_update_id_space = xauto_update_id_space;
  
  new_state(xhost, xname);

  // Postconditions:

  ensure(name() == xname);
  ensure(sp().name() == name());
  ensure(id_space().name() == name());
  ensure(client_id_space().name() == name() + "_client_id_space");
  ensure(auto_update_id_space() == xauto_update_id_space);
  ensure(ct() == 0);

  // Exit:

  return;
}

geometry::cohort::
~cohort()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}

void
geometry::cohort::
insert_member(const scoped_index& xid)
{
  // cout << endl << "Entering cohort::insert_member." << endl;

  // Preconditions:

  require(host().state_is_read_write_accessible());
  define_old_variable(size_type old_ct = _ct);
  
  // Body:

  if(!_sp.contains_member(xid))
  {  
    _sp.insert_member(xid);

    if(_auto_update_id_space)
    {
      _id_space->push_back(xid);
    }
  }

  ++_ct;
  
  
  // Postconditions:

  ensure(contains(xid));
  ensure(auto_update_id_space() ? id_space().contains(xid) : true);
  ensure(ct() == old_ct + 1);
  
  // Exit:

  // cout << "Leaving cohort::insert_member." << endl;
  return;
}

void
geometry::cohort::
remove_member(const scoped_index& xid, bool xupdate_id_space_extrema)
{
  // cout << endl << "Entering cohort::insert_member." << endl;

  // Preconditions:

  require(host().state_is_read_write_accessible());

  define_old_variable(size_type old_ct = _ct);
  define_old_variable(bool old_contains_xid = contains(xid));
  
  // Body:

  if(_sp.contains_member(xid))
  {
    _sp.remove_member(xid);

    if(_auto_update_id_space)
    {
      _id_space->remove(xid, xupdate_id_space_extrema);
    }

    --_ct;
  }  
  
  // Postconditions:

  ensure(!contains(xid));
  ensure(auto_update_id_space() ? !id_space().contains(xid) : true);
  ensure(!old_contains_xid || (ct() == old_ct - 1));
  
  // Exit:

  // cout << "Leaving cohort::insert_member." << endl;
  return;
}

bool
geometry::cohort::
auto_update_id_space() const
{
  return _auto_update_id_space;
}


// PROTECTED MEMBER FUNCTIONS
 
geometry::cohort::
cohort()
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
 
