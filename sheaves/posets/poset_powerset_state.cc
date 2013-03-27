// $RCSfile: poset_powerset_state.cc,v $ $Revision: 1.38 $ $Date: 2013/03/13 00:59:06 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class poset_powerset_state

#include "poset_powerset_state.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "factory_2.h"
#include "index_space_iterator.h"
#include "hub_index_space_handle.h"
#include "std_sstream.h"

// ===========================================================
// CANONICAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_powerset_state::
poset_powerset_state(size_type xcapacity, const scoped_index& xsubposet_member_index_ub)
{
  // Preconditions:

  require(xsubposet_member_index_ub.is_hub_scope());
  require(xsubposet_member_index_ub >= 0);

  // Body:

  // Prevent recursive calls to invariant.

  disable_invariant_check();

  // Initialize the upper bound of the subposets.

  _subposet_index_ub.put(hub_id_space(), 0);

  // Initialize upper bound on subposet member index

  _subposet_member_index_ub = xsubposet_member_index_ub;

  // Reserve space in the subposet block.

  _subposets.reserve(xcapacity);

  // Invariant not satisfied until standard subposets initialized by client,
  // leave invarant check disabled.

  // Postconditions:

  ensure(subposet_index_ub().is_hub_scope());
  ensure(subposet_member_index_ub() == xsubposet_member_index_ub);
}

sheaf::poset_powerset_state::
~poset_powerset_state()
{
  // Detach the standard subposets.

  _coarsest_common_refinement.detach_from_state();
  _coarsest_common_refinement_jims.detach_from_state();
  _whole.detach_from_state();
  _jims.detach_from_state();
  _table_dof_subposet.detach_from_state();
  _row_dof_subposet.detach_from_state();

  // Delete the members.

  index_space_iterator& litr = hub_id_space().get_iterator();
  while(!litr.is_done())
  {
    delete _subposets[litr.pod()];

    litr.next();
  }
  hub_id_space().release_iterator(litr);
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUBPOSETS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::subposet_state&
sheaf::poset_powerset_state::
member(pod_index_type xindex)
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  subposet_state& result = *_subposets[xindex];

  // Postconditions:

  // Exit:

  return result;
}

sheaf::subposet_state&
sheaf::poset_powerset_state::
member(const scoped_index& xindex)
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  subposet_state& result = *_subposets[xindex.hub_pod()];

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet_state&
sheaf::poset_powerset_state::
member(pod_index_type xindex) const
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  const subposet_state& result = *_subposets[xindex];

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet_state&
sheaf::poset_powerset_state::
member(const scoped_index& xindex) const
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  const subposet_state& result = *_subposets[xindex.hub_pod()];

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_powerset_state::
new_subposet(bool xinitialize)
{
  // Preconditions:

  // Body:

  define_old_variable(scoped_index old_subposet_index_ub = subposet_index_ub());
  define_old_variable(size_type old_subposet_ct = subposet_ct());

  // Create an id in the id space family.

  /// @issue Do we want to reuse the subposet index when the last member is deleted?
  /// If so, uncomment the code below (including the postcondition).  This was
  /// working before because _subposet_index_ub was not updated when a member
  /// was deleted.
  ///scoped_index result = _id_spaces.new_id(subposet_index_ub());

  pod_index_type result = _id_spaces.new_id();

  // Create the subposet

  _subposets.force_item(result, new subposet_state());
  _subposets[result]->initialize(_subposet_member_index_ub,
				 hub_id(result), xinitialize);

  // Set the subposet index upper bound.

  _subposet_index_ub = hub_id_space().end();

  // Postconditions:

  //ensure(subposet_index_ub() == old_subposet_index_ub + 1);
  ensure(subposet_index_ub() > old_subposet_index_ub);
  ensure(subposet_ct() == old_subposet_ct + 1);
  ensure(hub_id_space().contains(result));
  ensure(contains_subposet(result));
  ensure(member(result).is_persistent());

  // Exit:

  return result;
}

void
sheaf::poset_powerset_state::
new_subposet(bool xinitialize,
	     scoped_index& result)
{
  // Preconditions:

  // Body:

  define_old_variable(scoped_index old_subposet_index_ub = subposet_index_ub());
  define_old_variable(size_type old_subposet_ct = subposet_ct());

  result.put(hub_id_space(), new_subposet(xinitialize));

  // Postconditions:

  //ensure(subposet_index_ub() == old_subposet_index_ub + 1);
  ensure(subposet_index_ub() > old_subposet_index_ub);
  ensure(subposet_ct() == old_subposet_ct + 1);
  ensure(result.is_hub_scope());
  ensure(result.in_scope());
  ensure(contains_subposet(result));
  ensure(member(result).is_persistent());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::poset_powerset_state::
new_subposet(const block<pod_index_type>& xmembers)
{
  // Preconditions:

  // Body:

  define_old_variable(scoped_index old_subposet_index_ub = subposet_index_ub());
  define_old_variable(size_type old_subposet_ct = subposet_ct());

  // Create an id in the id space family.

  /// @issue Do we want to reuse the subposet index when the last member is deleted?
  /// If so, uncomment the code below (including the postcondition).  This was
  /// working before because _subposet_index_ub was not updated when a member
  /// was deleted.
  ///scoped_index result = _id_spaces.new_id(subposet_index_ub());

  pod_index_type result = _id_spaces.new_id();

  // Create the subposet

  _subposets.force_item(result, new subposet_state());
  _subposets[result]->initialize(_subposet_member_index_ub,
				 hub_id(result), xmembers);

  // Set the subposet index upper bound.

  _subposet_index_ub = hub_id_space().end();

  // Postconditions:

  //ensure(subposet_index_ub() == old_subposet_index_ub + 1);
  ensure(subposet_index_ub() > old_subposet_index_ub);
  ensure(subposet_ct() == old_subposet_ct + 1);
  ensure(hub_id_space().contains(result));
  ensure(contains_subposet(result));
  ensure(member(result).is_persistent());

  // Exit:

  return result;
}

void
sheaf::poset_powerset_state::
new_subposet(const block<scoped_index>& xmembers, scoped_index& result)
{
  // Preconditions:

  // Body:

  define_old_variable(scoped_index old_subposet_index_ub = subposet_index_ub());
  define_old_variable(size_type old_subposet_ct = subposet_ct());

  // Create an id in the id space family.

  /// @issue Do we want to reuse the subposet index when the last member is deleted?
  /// If so, uncomment the code below (including the postcondition).  This was
  /// working before because _subposet_index_ub was not updated when a member
  /// was deleted.
  ///scoped_index result = _id_spaces.new_id(subposet_index_ub());

  result.put(hub_id_space(), _id_spaces.new_id());

  // Create the subposet

  _subposets.force_item(result, new subposet_state());
  _subposets[result]->initialize(_subposet_member_index_ub,
				 result, xmembers);

  // Set the subposet index upper bound.

  _subposet_index_ub = hub_id_space().end();

  // Postconditions:

  //ensure(subposet_index_ub() == old_subposet_index_ub + 1);
  ensure(subposet_index_ub() > old_subposet_index_ub);
  ensure(subposet_ct() == old_subposet_ct + 1);
  ensure(result.is_hub_scope());
  ensure(result.in_scope());
  ensure(contains_subposet(result));
  ensure(member(result).is_persistent());

  // Exit:

  return;
}

void
sheaf::poset_powerset_state::
delete_subposet(pod_index_type xindex)
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  // Delete the subposet.

  delete _subposets[xindex];
  
  // Remove the subposet from the collection.

  _subposets[xindex] = 0;

  // Delete the member from the id spaces.

  _id_spaces.delete_id(xindex);

  // Set the subposet index upper bound.

  _subposet_index_ub = !hub_id_space().is_empty() ? hub_id_space().end() : 0;

  // Postconditions:

  ensure(!contains_subposet(xindex));

  // Exit:

  return;
}

void
sheaf::poset_powerset_state::
delete_subposet(const scoped_index& xindex)
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  delete_subposet(xindex.hub_pod());

  // Postconditions:

  ensure(!contains_subposet(xindex));

  // Exit:

  return;
}

const sheaf::scoped_index&
sheaf::poset_powerset_state::
subposet_index_ub() const
{
  return _subposet_index_ub;
}

sheaf::size_type
sheaf::poset_powerset_state::
subposet_ct() const
{
  return hub_id_space().ct();
}

sheaf::index_space_iterator&
sheaf::poset_powerset_state::
get_subposet_id_space_iterator() const
{
  // Preconditions:

  // Body:

  index_space_iterator& result =  hub_id_space().get_iterator();

  // Postconditions:

  ensure(hub_id_space().allocated_iterator(result));

  // Exit:

  return result;
}

void
sheaf::poset_powerset_state::
release_subposet_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(hub_id_space().allocated_iterator(xitr));

  // Body:

  hub_id_space().release_iterator(xitr);

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::poset_powerset_state::
contains_subposet(pod_index_type xindex) const
{
  // Preconditions:

  // Body:

  bool result = hub_id_space().contains(xindex);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_powerset_state::
contains_subposet(const scoped_index& xindex) const
{
  return contains_subposet(xindex.hub_pod());
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ID SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::poset_powerset_state::
id_spaces() const
{
  return _id_spaces;
}

const sheaf::hub_index_space_handle&
sheaf::poset_powerset_state::
hub_id_space() const
{
  return _id_spaces.hub_id_space();
}

const sheaf::scoped_index&
sheaf::poset_powerset_state::
hub_id() const
{
  // Preconditions:

  // Body:

  const scoped_index& result = subposet_index_ub();

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_powerset_state::
hub_id(pod_index_type xid) const
{
  // Preconditions:

  // Body:

  scoped_index result(hub_id());
  result = xid;

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUBPOSET NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_powerset_state::subposet_name_map_type&
sheaf::poset_powerset_state::
subposet_name_map()
{
  return _subposet_name_map;
}

const sheaf::poset_powerset_state::subposet_name_map_type&
sheaf::poset_powerset_state::
subposet_name_map() const
{
  return _subposet_name_map;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUBPOSET MEMBERSHIP FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::scoped_index&
sheaf::poset_powerset_state::
subposet_member_index_ub() const
{
  return _subposet_member_index_ub;
}

void
sheaf::poset_powerset_state::
put_subposet_member_index_ub(const scoped_index& xub)
{
  // Preconditions:

  require(xub.same_scope(subposet_member_index_ub()));

  // Body:

  if(_subposet_member_index_ub < xub)
  {
    _subposet_member_index_ub = xub.pod();

    index_space_iterator& itr = hub_id_space().get_iterator();
    while(!itr.is_done())
    {
      _subposets[itr.pod()]->members()->extend_to(_subposet_member_index_ub);
      itr.next();
    }
    hub_id_space().release_iterator(itr);
  }

  // Postconditions:

  ensure(subposet_member_index_ub() >= xub);

  return;
}

bool
sheaf::poset_powerset_state::
is_dof_subposet(pod_index_type xindex) const
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  bool result = _subposets[xindex]->is_dof_subposet();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_powerset_state::
is_dof_subposet(const scoped_index& xindex) const
{
  // Preconditions:

  require(contains_subposet(xindex));

  // Body:

  bool result = _subposets[xindex.hub_pod()]->is_dof_subposet();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::poset_powerset_state::
delete_poset_member(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  // Remove member from all subposets.

  index_space_iterator& itr = hub_id_space().get_iterator();
  while(!itr.is_done())
  {
    _subposets[itr.pod()]->members()->put(xindex, false);

    itr.next();
  }
  hub_id_space().release_iterator(itr);

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::poset_powerset_state::
delete_poset_member(const scoped_index& xindex)
{
  delete_poset_member(xindex.hub_pod());
}

bool
sheaf::poset_powerset_state::
subposet_contains_member(pod_index_type xsubposet_index,
                         pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_subposet(xsubposet_index));

  // Body:

  bool result =
    (*_subposets[xsubposet_index]->members())[xmbr_index];

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_powerset_state::
subposet_contains_member(const scoped_index& xsubposet_index,
                         const scoped_index& xmbr_index) const
{
  // Preconditions:

  require(contains_subposet(xsubposet_index));

  // Body:

  bool result =
    (*_subposets[xsubposet_index.hub_pod()]->members())[xmbr_index.hub_pod()];

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STANDARD SUBPOSETS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::subposet&
sheaf::poset_powerset_state::
coarsest_common_refinement()
{
  return _coarsest_common_refinement;
}

const sheaf::subposet&
sheaf::poset_powerset_state::
coarsest_common_refinement() const
{
  return _coarsest_common_refinement;
}

sheaf::subposet&
sheaf::poset_powerset_state::
coarsest_common_refinement_jims()
{
  return _coarsest_common_refinement_jims;
}

const sheaf::subposet&
sheaf::poset_powerset_state::
coarsest_common_refinement_jims() const
{
  return _coarsest_common_refinement_jims;
}

sheaf::subposet&
sheaf::poset_powerset_state::
whole()
{
  return _whole;
}

sheaf::subposet&
sheaf::poset_powerset_state::
jims()
{
  return _jims;
}

sheaf::subposet&
sheaf::poset_powerset_state::
table_dof_subposet()
{
  return _table_dof_subposet;
}

const sheaf::subposet&
sheaf::poset_powerset_state::
table_dof_subposet() const
{
  return _table_dof_subposet;
}

sheaf::subposet&
sheaf::poset_powerset_state::
row_dof_subposet()
{
  return _row_dof_subposet;
}

const sheaf::subposet&
sheaf::poset_powerset_state::
row_dof_subposet() const
{
  return _row_dof_subposet;
}

int
sheaf::poset_powerset_state::
standard_subposet_ct() const
{
  return _standard_subposet_ct;
}

void
sheaf::poset_powerset_state::
put_standard_subposet_ct(int xct)
{
  // Preconditions:

  // Body:

  _standard_subposet_ct = xct;

  // Postconditions:

  ensure(standard_subposet_ct() == xct);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_powerset_state::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_powerset_state*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_powerset_state*
sheaf::poset_powerset_state::
clone() const
{
  poset_powerset_state* result = 0;

  // Preconditions:

  // Body:

  /// @todo implement poset_powerset_state::clone

  not_implemented();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::poset_powerset_state::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls.

    disable_invariant_check();

    invariance(subposet_member_index_ub().is_hub_scope());
    invariance(subposet_member_index_ub() >= 0);

    // @todo implement remaining assertions in poset_powerset_state::invariant

    // for all subposets in _subposets: name != 0 implies _name_table[name] = index

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NONMEBER FUNCTIONS
// ===========================================================

ostream & 
sheaf::
operator<<(ostream &os, const poset_powerset_state& p)
{

  // Preconditions:

  // Body:

  os << endl
     << "ROW GRAPH SUBPOSETS" << endl
     << "-------------------" << endl
     << endl;

  os << "Subposets" << endl
     << "---------" << endl
     << endl;

  size_type lmax_name_len = 0;
  
  // Find the length of the longest name

  index_space_iterator& itr = p.get_subposet_id_space_iterator();
  while(!itr.is_done())
  {
    poset_powerset_state::subposet_name_map_type::name_list_type lname_list =
      p.subposet_name_map().all_names(itr.pod());

    poset_powerset_state::subposet_name_map_type::const_name_iterator lname_itr =
      lname_list.begin();


    while(lname_itr != lname_list.end())
    {
      size_type lname_len = lname_itr->size();
      lmax_name_len = (lname_len > lmax_name_len) ? lname_len : lmax_name_len;
      ++lname_itr;
    }

    itr.next();
  }

  const int ID_WIDTH = 8;
  int lname_width = lmax_name_len + 2;
  itr.reset();
  scoped_index lid(p.hub_id_space());
  while(!itr.is_done())
  {
    lid = itr.pod();

    // Output the id; must be fixed length test field.

    stringstream lstr;
    lstr << lid;
    
    os << "index: " << setw(ID_WIDTH) << right << lstr.str();

    poset_powerset_state::subposet_name_map_type::name_list_type lname_list =
      p.subposet_name_map().all_names(itr.pod());

    poset_powerset_state::subposet_name_map_type::const_name_iterator lname_itr =
      lname_list.begin();

    string lfirst_name;
    if(lname_itr != lname_list.end())
    {
      lfirst_name = *lname_itr;
      ++lname_itr;
    }

    os << "  " << setw(lname_width) << left << lfirst_name << right
       << "  " << *p._subposets[itr.pod()]
       << endl;

    while(lname_itr != lname_list.end())
    {
      os << setw(7 + ID_WIDTH) << " "
	 << "  " << setw(lname_width) << left << *lname_itr << right 
	 << endl;
      ++lname_itr;
    }

    itr.next();
  }

  p.release_subposet_id_space_iterator(itr);

  // Subposet id space family.

  os << endl
     << "Subposet Id Space Family" << endl
     << "----------------------" << endl
     << endl;

  os << p.id_spaces()
     << endl;


  // Postconditions:

  // Exit

  return os;
}

size_t
sheaf::
deep_size(const poset_powerset_state& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the contributions from _id_spaces.

  result += deep_size(xp._id_spaces, false);

  // Add the contributions from _subposets

  result += deep_size(xp._subposets, false);

  // Add the contributions from _subposet_name_map.

  // @issue Should we be calculating the size of the name map, or are the
  // names owned by a different class.

  result += deep_size(xp._subposet_name_map, false);

  // Determine the deep size of data members:
  //   subposet _coarsest_common_refinement;
  //   subposet _coarsest_common_refinement_jims;
  //   subposet _whole;
  //   subposet _jims;
  //   subposet _table_dof_subposet;
  //   subposet _row_dof_subposet;

  result += deep_size(xp._coarsest_common_refinement, false);
  result += deep_size(xp._coarsest_common_refinement_jims, false);
  result += deep_size(xp._whole, false);
  result += deep_size(xp._jims, false);

  // @issue dof subposets do not have read access.

  //result += deep_size(xp._table_dof_subposet, false);
  //result += deep_size(xp._row_dof_subposet, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
