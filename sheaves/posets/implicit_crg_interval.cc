

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class implicit_crg_interval.

#include "implicit_crg_interval.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "list_index_space_state.h"
#include "poset_state_handle.h"

// ===========================================================
// IMPLICIT_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::implicit_crg_interval::
implicit_crg_interval()
  : _private_data_initialized(false),
    _dof_tuple_ids_initialized(false),
    _is_finalized(false)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit:

  return;
}

sheaf::implicit_crg_interval::
~implicit_crg_interval()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// IMPLICIT INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::pod_index_type
sheaf::implicit_crg_interval::
implicit_begin() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.offset()+1;
}

void
sheaf::implicit_crg_interval::
implicit_begin(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  result.put(hub_id_space(), implicit_begin());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::implicit_crg_interval::
interval_member() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return begin();
}

void
sheaf::implicit_crg_interval::
interval_member(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  begin(result);

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_interval::
is_interval_member(pod_index_type xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return (_local_id_space.offset() == xindex);
}

bool
sheaf::implicit_crg_interval::
is_interval_member(const scoped_index& xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return is_interval_member(xindex.hub_pod());
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// COVER SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

string
sheaf::implicit_crg_interval::
implicit_cover_name(bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:

  // Body:

  string suffix = xlower ? "_lower_cover" : "_upper_cover";

  string result = poset_path::make_reserved_name("implicit_", xmbr_index, suffix);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
sheaf::implicit_crg_interval::
implicit_cover_name(bool xlower, const scoped_index& xmbr_index)
{
  // Preconditions:

  // Body:

  return implicit_cover_name(xlower, xmbr_index.hub_pod());
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::implicit_crg_interval::
is_jim(pod_index_type xmbr_index) const
{
  bool result = false; // Just to silence the compiler warnings.

  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::implicit_crg_interval::
is_jim(const scoped_index& xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  return is_jim(xmbr_index.hub_pod());
}

sheaf::pod_index_type
sheaf::implicit_crg_interval::
dof_tuple_id(const scoped_index& xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  return dof_tuple_id(xmbr_index.hub_pod());
}

sheaf::block<sheaf::pod_index_type>&
sheaf::implicit_crg_interval::
dof_tuple_ids()
{
  return _dof_tuple_ids;
}

const sheaf::block<sheaf::pod_index_type>&
sheaf::implicit_crg_interval::
dof_tuple_ids() const
{
  return _dof_tuple_ids;
}

void
sheaf::implicit_crg_interval::
initialize_dof_tuple_ids(const block<pod_index_type>& xdof_tuple_ids)
{
  // Preconditions:


  // Body:

  _dof_tuple_ids.reserve(xdof_tuple_ids.ct());
  _dof_tuple_ids.set_ct(xdof_tuple_ids.ct());

  for(int i=0; i<xdof_tuple_ids.ct(); ++i)
  {
    _dof_tuple_ids[i] = xdof_tuple_ids[i];
  }

  _dof_tuple_ids_initialized = true;

  // Postconditions:

  ensure(dof_tuple_ids_initialized());
  ensure(dof_tuple_ids().ct() == xdof_tuple_ids.ct());
  ensure_for_all(i, 0, xdof_tuple_ids.ct(), dof_tuple_ids()[i] == xdof_tuple_ids[i]);

  // Exit:

  return;
}

bool
sheaf::implicit_crg_interval::
dof_tuple_ids_initialized() const
{
  return _dof_tuple_ids_initialized;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
sheaf::implicit_crg_interval::
clean_cover(bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  /// @todo Reimplement or design out of the io system.

  // Posconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// PRIVATE_DATA FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::size_type
sheaf::implicit_crg_interval::
private_data_size() const
{
  // Preconditions:

  // Body:

  // Initialize to the implicit private data size.

  size_type result = implicit_private_data_size();

  // Add explicit member upper and lower cover sizes.

  result += 2;

  explicit_cover_map_type::const_iterator litr;

  // Count explicit upper covers.

  for(litr = _explicit_upper_cover_map.begin(); litr != _explicit_upper_cover_map.end(); ++litr)
  {
    // Add the member id, size of cover and cover members.

    result += (2+ _id_spaces->ct(litr->second));
  }

  // Count explicit lower covers.

  for(litr = _explicit_lower_cover_map.begin(); litr != _explicit_lower_cover_map.end(); ++litr)
  {
    // Add the member id, size of cover and cover members.

    result += (2+ _id_spaces->ct(litr->second));
  }

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::implicit_crg_interval::
get_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  xdata.reserve(private_data_size());

  // Insert implicit private data.

  get_implicit_private_data(xdata);

  // Insert explicit private data.

  explicit_cover_map_type::const_iterator litr;

  // Insert explicit upper covers.

  xdata.push_back(_explicit_upper_cover_map.size());

  for(litr = _explicit_upper_cover_map.begin(); litr != _explicit_upper_cover_map.end(); ++litr)
  {
    // The private data has the member id, size of cover and cover members.

    xdata.push_back(litr->first);
    xdata.push_back(_id_spaces->ct(litr->second));

    index_space_iterator& lcover_itr = _id_spaces->get_id_space_iterator(litr->second);
    while(!lcover_itr.is_done())
    {
      xdata.push_back(lcover_itr.hub_pod());

      lcover_itr.next();
    }
    _id_spaces->release_id_space_iterator(lcover_itr);
  }

  // Insert explicit lower covers.

  xdata.push_back(_explicit_lower_cover_map.size());

  for(litr = _explicit_lower_cover_map.begin(); litr != _explicit_lower_cover_map.end(); ++litr)
  {
    // The private data has the member id, size of cover and cover members.

    xdata.push_back(litr->first);
    xdata.push_back(_id_spaces->ct(litr->second));

    index_space_iterator& lcover_itr = _id_spaces->get_id_space_iterator(litr->second);
    while(!lcover_itr.is_done())
    {
      xdata.push_back(lcover_itr.hub_pod());

      lcover_itr.next();
    }
    _id_spaces->release_id_space_iterator(lcover_itr);
  }

  // Postconditions:

  ensure(xdata.ct() == private_data_size());

  // Exit:

  return;
}

void
sheaf::implicit_crg_interval::
put_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  // Body:

  // Read the implicit private data.

  put_implicit_private_data(xdata);

  // Read the explicit private data.

  pod_index_type idx = implicit_private_data_size();
  size_type lmember_ct;
  pod_index_type lmember_id;
  size_type lcover_ct;
  interval_index_space_handle* lcover;

  // Read upper cover.

  lmember_ct = xdata[idx];
  for(pod_index_type i = 0; i < lmember_ct; ++i)
  {
    // Read member id.

    lmember_id = xdata[++idx];

    // Read cover.

    lcover_ct = xdata[++idx];
    pod_index_type lcover_id =
      _id_spaces->new_secondary_state(explicit_cover_name(UPPER, lmember_id),
				      "list_index_space_state",
				      list_index_space_state::make_arg_list(),
				      false);
    mutable_index_space_handle& lcover =
      _id_spaces->get_id_space<mutable_index_space_handle>(lcover_id);

    for(pod_index_type j = 0; j < lcover_ct; ++j)
    {
      lcover.push_back(xdata[++idx]);
    }

    _id_spaces->release_id_space(lcover);

    // Insert cover into the map.

    _explicit_upper_cover_map[lmember_id] = lcover_id;
  }

  // Read lower cover.

  lmember_ct = xdata[++idx];
  for(pod_index_type i = 0; i < lmember_ct; ++i)
  {
    // Read member id.

    lmember_id = xdata[++idx];

    // Read cover.

    lcover_ct = xdata[++idx];
    pod_index_type lcover_id =
      _id_spaces->new_secondary_state(explicit_cover_name(LOWER, lmember_id),
				      "list_index_space_state",
				      list_index_space_state::make_arg_list(),
				      false);
    mutable_index_space_handle& lcover =
      _id_spaces->get_id_space<mutable_index_space_handle>(lcover_id);

    for(pod_index_type j = 0; j < lcover_ct; ++j)
    {
      lcover.push_back(xdata[++idx]);
    }

    _id_spaces->release_id_space(lcover);

    // Insert cover into the map.

    _explicit_lower_cover_map[lmember_id] = lcover_id;
  }

  // Mark private data as initialized.

  _private_data_initialized = true;

  // Postconditions:

  ensure(private_data_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_interval::
private_data_initialized() const
{
  return _private_data_initialized;
}

// PROTECTED DATA MEMBERS

sheaf::size_type
sheaf::implicit_crg_interval::
implicit_private_data_size() const
{
  size_type result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::implicit_crg_interval::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
sheaf::implicit_crg_interval::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// FINIALIZE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
sheaf::implicit_crg_interval::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_accessible());

  // Body:

  // Have enough information to determine jims() membership.

  for(pod_index_type i=begin(); i<end(); ++i)
  {
    if(is_jim(i))
    {
      xhost.jims().insert_member(i);
    }
  }

  _is_finalized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
sheaf::implicit_crg_interval::
initialize(const namespace_poset& xnamespace)
{
  // Preconditions:

  // Body:

  crg_interval::initialize(xnamespace);

  _private_data_initialized = true;
  _dof_tuple_ids_initialized = true;
  _is_finalized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_interval::
is_initialized() const
{
  bool result =
    _private_data_initialized &&
    _dof_tuple_ids_initialized &&
    _is_finalized;

  return result;
}

const string&
sheaf::implicit_crg_interval::
class_name() const
{
  static const string result("implicit_crg_interval");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::implicit_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const implicit_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::implicit_crg_interval*
sheaf::implicit_crg_interval::
clone() const
{
  implicit_crg_interval* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::implicit_crg_interval::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(crg_interval::invariant());

    // Invariances for this class:

    invariance(local_id_space_initialized() ? implicit_begin() == local_id_space().offset()+1 : true);
    invariance(local_id_space_initialized() ? interval_member() == begin() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
sheaf::deep_size(const implicit_crg_interval& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the deep size of the data members.

  if(xp._dof_tuple_ids_initialized)
    result += deep_size(xp._dof_tuple_ids, false);

  if(xp._private_data_initialized)
    result += xp.private_data_size();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

