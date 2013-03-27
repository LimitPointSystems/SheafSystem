// $RCSfile: abstract_cohort.cc,v $ $Revision: 1.5 $ $Date: 2013/03/13 00:58:59 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class abstract_cohort

#include "abstract_cohort.h"
#include "array_index_space_state.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "index_space_handle.h"
#include "std_sstream.h"

using namespace geometry;

// ===========================================================
// ABSTRACT_COHORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::abstract_cohort::
~abstract_cohort()
{
  // Preconditions:


  // Body:

  _sp.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::base_space_poset&
geometry::abstract_cohort::
host()
{
  return *_host;
}

const fiber_bundle::base_space_poset&
geometry::abstract_cohort::
host() const
{
  return *_host;
}


string
geometry::abstract_cohort::
name() const
{
  // Preconditions:

  require(sp().state_is_read_accessible());
  
  // Body:

  // Postconditions:

  // Exit:

  return _sp.name();
}

sheaf::size_type
geometry::abstract_cohort::
ct() const
{
  return _ct;
}

bool
geometry::abstract_cohort::
contains(const scoped_index& xid) const
{
  // cout << endl << "Entering abstract_cohort::contains." << endl;

  // Preconditions:
  
  require(host().state_is_read_accessible());
  require(xid.is_valid());

  // Body:

  bool result = contains(xid.hub_pod());

  // Postconditions:


  // Exit:

  // cout << "Leaving abstract_cohort::contains." << endl;
  return result;
}

bool
geometry::abstract_cohort::
contains(pod_index_type xid) const
{
  // cout << endl << "Entering abstract_cohort::contains." << endl;

  // Preconditions:
  
  require(host().state_is_read_accessible());

  // Body:

  bool result = _sp.contains_member(xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving abstract_cohort::contains." << endl;
  return result;
}

// sheaf::subposet&
// geometry::abstract_cohort::
// sp()
// {
//   return _sp;
// }

const sheaf::subposet&
geometry::abstract_cohort::
sp() const
{
  return _sp;
}

// sheaf::index_space_handle&
// geometry::abstract_cohort::
// id_space()
// {
//   return *_id_space;
// }

const sheaf::mutable_index_space_handle&
geometry::abstract_cohort::
id_space() const
{
  return *_id_space;
}

sheaf::mutable_index_space_handle&
geometry::abstract_cohort::
client_id_space()
{
  return *_client_id_space;
}

const sheaf::mutable_index_space_handle&
geometry::abstract_cohort::
client_id_space() const
{
  return *_client_id_space;
}

bool&
geometry::abstract_cohort::
auto_name_members()
{
  // Preconditions:


  // Body:

  static bool result = true;

  // Postconditions:


  // Exit:

  return result;
}

bool&
geometry::abstract_cohort::
auto_output_cts()
{
  // Preconditions:


  // Body:

  static bool result = false;

  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS
 
geometry::abstract_cohort::
abstract_cohort()
{
  // Preconditions:


  // Body:

  _host = 0;
  _ct = 0;

  // Postconditions:

  ensure(ct() == 0);
  
  // Exit:

  return;
}


void
geometry::abstract_cohort::
new_state(base_space_poset& xhost, const string& xname)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());
  
  // Body:

  _host = &xhost;
  _ct = 0;
 
  if(xhost.includes_subposet(xname))
  {
    // Subposet already eists; attach to it.

    _sp.attach_to_state(&xhost, xname);
    _sp.put_is_persistent(true);
  }
  else
  {
    // Subposet does not already exist; create it.

    _sp.new_state(&xhost);
    _sp.put_name(xname, true, false);
    _sp.put_is_persistent(true);
  }
  
  if(_sp.has_id_space())
  {
    // Id space already exists; just save aa pointer to it.

    _id_space = &_sp.id_space();
  }
  else
  {
    // Create the id space.

    arg_list lid_map_args = array_index_space_state::make_arg_list(0);
    _id_space = &_sp.new_id_space("array_index_space_state", lid_map_args);
  }

  string lclient_id_space_name = xname + "_client_id_space";

  if(xhost.member_id_spaces(false).contains(lclient_id_space_name))
  {
    // Client id space already exists; just save a pointer to it.

    _client_id_space = &xhost.member_id_spaces(false).get_id_space<mutable_index_space_handle>(lclient_id_space_name);
  }
  else
  {
    // Create the client id space.

    arg_list lspace_args = array_index_space_state::make_arg_list(0);

    pod_index_type lid =
      xhost.member_id_spaces(false).new_secondary_state(lclient_id_space_name,
							"array_index_space_state",
							lspace_args, true);

    _client_id_space = &xhost.member_id_spaces(false).get_id_space<mutable_index_space_handle>(lid);
  }
  

  // Postconditions:

  ensure(name() == xname);
  ensure(sp().name() == name());
  ensure(id_space().name() == name());
  ensure(client_id_space().name() == name() + "_client_id_space");
  ensure(ct() == 0);

  // Exit:

  return;
}

// void
// geometry::abstract_cohort::
// new_state(base_space_poset& xhost, int xd)
// {
//   // Preconditions:

//   require(xhost.state_is_read_write_accessible());
//   require((0 <= xd) && (xd <= xhost.max_db()));
  
//   // Body:

//   _host = &xhost;

//   // Attach to the existing subposet and id space.

//   _sp.attach_to_state(&xhost.d_cells(xd));
//   _id_space = &_sp.id_space();


//   string lclient_id_space_name = _id_space->name() + "_client_id_space";

//   if(xhost.contains_id_space(lclient_id_space_name))
//   {
//     // Client id space already exists; just save a pointer to it.

//     _client_id_space = &xhost.id_space(lclient_id_space_name);
//   }
//   else
//   {
//     // Create the client id space.

//     arg_list lid_map_args = array_index_map::make_arg_list(0);
//     arg_list lid_space_args =
//       simple_index_space::make_arg_list("array_index_map", lid_map_args);

//     pod_index_type lid = xhost.new_id_space(lclient_id_space_name, "simple_index_space", lid_space_args, true);
//     _client_id_space = &xhost.id_space(lid);
//   }

//   // Postconditions:

//   ensure(name() == xhost.d_cells(xd).name());
//   ensure(sp().name() == name());
//   ensure(id_space().name() == name());
//   ensure(client_id_space().name() == name() + "_client_id_space");

//   // Exit:

//   return;
// }

string
geometry::abstract_cohort::
member_name(const scoped_index& xid)
{
  // Preconditions:


  // Body:

  pod_index_type lpod = _id_space->pod(xid);
  stringstream lstr;
  lstr << name() << "_" << lpod;
  string result = lstr.str();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

void
geometry::abstract_cohort::
name_member(const scoped_index& xid)
{
  // Preconditions:


  // Body:

  _host->put_member_name(xid, member_name(xid), false, false);

  // Postconditions:

  // Exit:

  return;
}

void
geometry::abstract_cohort::
unname_member(const scoped_index& xid)
{
  // Preconditions:


  // Body:

  _host->delete_member_name(member_name(xid), false);

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
operator << (ostream& xos, abstract_cohort& xn)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return xos;
}
