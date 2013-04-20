
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class ADJACENCY_EXTRACTOR

#include "adjacency_extractor.h"
#include "assert_contract.h"
#include "abstract_poset_member.h"
#include "list_cover_set.h"
#include "poset_state_handle.h"
#include "postorder_member_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
fiber_bundle::adjacency_extractor::
adjacency_extractor(const adjacency_extractor& xother)
    : poset_dft(xother.host())
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
fiber_bundle::adjacency_extractor&
fiber_bundle::adjacency_extractor::
operator=(const adjacency_extractor& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}


///
fiber_bundle::adjacency_extractor::
~adjacency_extractor()
{

  // Preconditions:

  // Body:

  _lower_level.detach_from_state();
  _upper_level.detach_from_state();


  // Postconditions:

}

///
bool
fiber_bundle::adjacency_extractor::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(poset_dft::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // unexecutable: lower_level have same dimension as host
    // see issue in previsit_action
    /// @todo make this invariant executable

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}


// ADJACENCY_EXTRACTOR INTERFACE

///
fiber_bundle::adjacency_extractor::
adjacency_extractor(const poset_state_handle* xhost,
                    const string& xlower_level_subposet_name,
                    const string& xupper_level_subposet_name)
  : poset_dft(xhost)
{

  // Preconditions:

  require(precondition_of(poset_dft::poset_dft));
  require(xhost->includes_subposet(xlower_level_subposet_name));
  require(xhost->includes_subposet(xupper_level_subposet_name));
  require(unexecutable(upper_level subposet id_space() != 0));
  require(unexecutable(members of lower_level subposet have maximal dimension for xhost));
  // See issue in previsit_action
  /// @todo make this precondition executable or remove limitation
  require(unexecutable(dimension of host == 2));
  // See issue in postvisit_action
  /// @todo make this precondition executable or remove limitation

  // Body:

  _lower_level.attach_to_state(xhost, xlower_level_subposet_name);
  _upper_level.attach_to_state(xhost, xupper_level_subposet_name);

  _adjacency_cts = 0;
  _adjacency_cts_ub = 0;
  _adjacency_cts_ct = 0;

  _adjacency = 0;
  _adjacency_ub = 0;
  _adjacency_ct = 0;


  // Postconditions:

  ensure(invariant());
  ensure(adjacency_cts_ct() == 0);
  ensure(adjacency_ct() == 0);

}

///
void
fiber_bundle::adjacency_extractor::
extract(const abstract_poset_member* xanchor,
        int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xadjacency_cts,
        int xadjacency_cts_ub,
        int* xadjacency,
        int xadjacency_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub >= domain_mbrs_ct(xanchor));
  require(xadjacency_cts != 0);
  require(xadjacency_cts_ub >= adjacency_cts_ct());
  // Preceeding call depends on call to domain_mbrs_ct() above
  require(xadjacency != 0);
  require(xadjacency_ub >= adjacency_ct());
  // Preceeding call depends on call to domain_mbrs_ct() above
  require(upper_level().has_id_space());

  // Body:

  _up_set.clear();

  _above_lower_level = false;
  _extracting = true;

  _adjacency_cts = xadjacency_cts;
  _adjacency_cts_ub = xadjacency_cts_ub;
  _adjacency_cts_ct = 0;

  _adjacency = xadjacency;
  _adjacency_ub = xadjacency_ub;
  _adjacency_ct = 0;


  int i = 0;
  postorder_member_iterator itr(*xanchor, _lower_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    xdomain_mbrs[i++] =
      lower_level().id_space().pod(itr.item().index());

    traverse(&(itr.item()), false, false);
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(adjacency_cts_ct() >= 0);
  ensure(adjacency_ct() >= 0);

  // Exit:

  return;
}

///
void
fiber_bundle::adjacency_extractor::
extract(const int* xdomain_mbrs,
        int xdomain_mbrs_ct,
        int* xadjacency_cts,
        int xadjacency_cts_ub,
        int* xadjacency,
        int xadjacency_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ct > 0);
  require(unexecutable(host contains members with client ids in xdomain_mbrs));
  /// @todo make above precondition executable
  require(xadjacency_cts != 0);
  require(xadjacency_cts_ub >= xdomain_mbrs_ct);
  require(xadjacency != 0);
  require(xadjacency_ub >= adjacency_ct(xdomain_mbrs, xdomain_mbrs_ct));
  require(upper_level().has_id_space());

  // Body:

  _up_set.clear();

  _above_lower_level = false;
  _extracting = true;

  _adjacency_cts = xadjacency_cts;
  _adjacency_cts_ub = xadjacency_cts_ub;
  _adjacency_cts_ct = 0;

  _adjacency = xadjacency;
  _adjacency_ub = xadjacency_ub;
  _adjacency_ct = 0;

  // Traverse the up set of each entry in xdomain_mbrs;
  // In order to avoid potentially (mesh size)**2 performance,
  // the has_been_visited bitvector will not be reset between calls.
  // Instead, postvisit action will reset only those bits that are on.

  total_poset_member pm;

  scoped_index pid(lower_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ct; i++)
  {
    // $$SCRIBBLE: attach will internalize id.
    //    pid = lower_level().id_space().pod(xdomain_mbrs[i]);

    pid = xdomain_mbrs[i];
    pm.attach_to_state(host(), pid);

    traverse(&pm, false, false);
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(adjacency_cts_ct() >= 0);
  ensure(adjacency_ct() >= 0);

  // Exit:

  return;
}



///
void
fiber_bundle::adjacency_extractor::
count(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));

  // Body:

  _up_set.clear();

  _above_lower_level = false;
  _extracting = false;

  _adjacency_cts = 0;
  _adjacency_cts_ub = 0;
  _adjacency_cts_ct = 0;

  _adjacency = 0;
  _adjacency_ub = 0;
  _adjacency_ct = 0;

  postorder_member_iterator itr(*xanchor, _lower_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    traverse(&(itr.item()), false, false);
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(adjacency_cts_ct() >= 0);
  ensure(adjacency_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::adjacency_extractor::
count(const int* xdomain_mbrs, int xdomain_mbrs_ct)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ct > 0);
  require(unexecutable(host contains members with client ids in xdomain_mbrs));
  /// @todo make above precondition executable

  // Body:

  _up_set.clear();

  _above_lower_level = false;
  _extracting = false;

  _adjacency_cts = 0;
  _adjacency_cts_ub = 0;
  _adjacency_cts_ct = 0;

  _adjacency = 0;
  _adjacency_ub = 0;
  _adjacency_ct = 0;

  total_poset_member pm;

  scoped_index pid(lower_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ct; i++)
  {
    // $$SCRIBBLE: attach will interalize id.
    //    pid = lower_level().id_space().hub_pod(xdomain_mbrs[i]);

    pid = xdomain_mbrs[i];
    pm.attach_to_state(host(), pid);

    traverse(&pm, false, false);
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(adjacency_cts_ct() >= 0);
  ensure(adjacency_ct() >= 0);

  // Exit:

  return;
}


void
fiber_bundle::adjacency_extractor::
previsit_action(abstract_poset_member* xmbr)
{
  // Preconditions:

  require(!is_nested_lower_level(xmbr));

  // Body:

  if (_above_lower_level)
  {
    _descend = !_upper_level.contains_member(xmbr);
  }
  else if (_lower_level.contains_member(xmbr))
  {
    // Turn on up set collection

    _above_lower_level = true;

    // Store the index of the first adjacency entry
    // for xmbr

    _first_entry = _adjacency_ct;

  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xmbr in lower_level implies _above_lower_level));

  // Exit:

  return;
}


void
fiber_bundle::adjacency_extractor::
link_action(abstract_poset_member* xmbr, abstract_poset_member* linked_mbr)
{
  // Preconditions:

  // Body:

  // Does nothing in this traverser

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


void
fiber_bundle::adjacency_extractor::
postvisit_action(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(has_been_visited(xmbr));

  // Body:

  if (_lower_level.contains_member(xmbr))
  {
    // Finished with this member of lower_level.

    // Remove up set from visited set
    // so members will be visited again from
    // any other lower_level that contains them.

    while(!_up_set.empty())
    {
      mark_not_visited(_up_set.front());
      _up_set.pop_front();
    }

    // If extracting save the number of adjacency entries for this member.

    if (_extracting)
    {
      _adjacency_cts[_adjacency_cts_ct] = _adjacency_ct - _first_entry;
    }

    // Count the member whether extracting or not.

    _adjacency_cts_ct++;

    // Not above an lower_level now.

    _above_lower_level = false;

  }
  else if (_above_lower_level)
  {
    // Enter member in up set

    _up_set.push_front((xmbr->index()).pod());

    if (_upper_level.contains_member(xmbr))
    {
      // Member is a vertex;
      // If extracting store the client id.

      if (_extracting)
      {
        _adjacency[_adjacency_ct] = _upper_level.id_space().pod(xmbr->index());
      }

      // Count the adjacency whether extracting or not.

      _adjacency_ct++;
    }
  }

  // Postconditions:

  ensure(invariant());
}


