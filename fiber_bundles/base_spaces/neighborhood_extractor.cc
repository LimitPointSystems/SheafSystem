// $RCSfile: neighborhood_extractor.cc,v $ $Revision: 1.24 $ $Date: 2013/01/12 17:16:52 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class NEIGHBORHOOD_EXTRACTOR

#include "neighborhood_extractor.h"
#include "assert_contract.h"
#include "abstract_poset_member.h"
#include "list_cover_set.h"
#include "poset_state_handle.h"
#include "postorder_member_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
fiber_bundle::neighborhood_extractor::
neighborhood_extractor(const neighborhood_extractor& xother)
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
fiber_bundle::neighborhood_extractor&
fiber_bundle::neighborhood_extractor::
operator=(const neighborhood_extractor& xother)
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
fiber_bundle::neighborhood_extractor::
~neighborhood_extractor()
{

  // Preconditions:

  // Body:

  _lower_level.detach_from_state();
  _upper_level.detach_from_state();
  delete _up_set_visited;


  // Postconditions:

}

///
bool
fiber_bundle::neighborhood_extractor::
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


// NEIGHBORHOOD_EXTRACTOR INTERFACE

///
fiber_bundle::neighborhood_extractor::
neighborhood_extractor(const poset_state_handle* xhost,
                       const string& xlower_level_subposet_name,
                       const string& xupper_level_subposet_name,
                       bool xincludes_center)
    : poset_dft(xhost)
{

  // Preconditions:

  require(precondition_of(poset_dft::poset_dft));
  require(xhost->includes_subposet(xlower_level_subposet_name));
  require(xhost->includes_subposet(xupper_level_subposet_name));
  require(unexecutable(upper_level subposet id_space() != 0));
  require(unexecutable(lower_level subposet id_space() != 0));
  /// @issue precondition of previsit action is that upper level
  /// subposet must be an antichain. Is this the place to enforce this?
  /// Lower level should also be an antichain.

  // Body:

  _lower_level.attach_to_state(xhost, xlower_level_subposet_name);
  _upper_level.attach_to_state(xhost, xupper_level_subposet_name);

  // Visited marker for down set portion of traversal has been
  // allocated in poset_traverser::poset_traverser, save a
  // pointer to it.

  _down_set_visited = _visited;

  // Allocate visited marker for up set portion of traversal

  _up_set_visited = new zn_to_bool(member_index_ub().pod());

  _includes_center = xincludes_center;

  _neighborhood_cts = 0;
  _neighborhood_cts_ub = 0;
  _neighborhood_cts_ct = 0;

  _neighborhood = 0;
  _neighborhood_ub = 0;
  _neighborhood_ct = 0;


  // Postconditions:

  ensure(invariant());
  ensure(neighborhood_cts_ct() == 0);
  ensure(neighborhood_ct() == 0);

}






///
void
fiber_bundle::neighborhood_extractor::
extract(const abstract_poset_member* xanchor,
        int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xneighborhood_cts,
        int xneighborhood_cts_ub,
        int* xneighborhood,
        int xneighborhood_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub >= domain_mbrs_ct(xanchor));
  require(xneighborhood_cts != 0);
  require(xneighborhood_cts_ub >= neighborhood_cts_ct());
  // Preceeding call depends on call to domain_mbrs_ct() above
  require(xneighborhood != 0);
  require(xneighborhood_ub >= neighborhood_ct());
  // Preceeding call depends on call to domain_mbrs_ct() above
  require(upper_level().has_id_space());

  // Body:

  _down_set.clear();
  _up_set.clear();

  _below_upper_level = false;
  _extracting = true;

  _neighborhood_cts = xneighborhood_cts;
  _neighborhood_cts_ub = xneighborhood_cts_ub;
  _neighborhood_cts_ct = 0;

  _neighborhood = xneighborhood;
  _neighborhood_ub = xneighborhood_ub;
  _neighborhood_ct = 0;


  bool reset = true;
  int i = 0;
  postorder_member_iterator itr(*xanchor, _upper_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    xdomain_mbrs[i++] =
      upper_level().id_space().pod(itr.item().index());

    traverse(&(itr.item()), true, reset);
    reset = false;
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(neighborhood_cts_ct() >= 0);
  ensure(neighborhood_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::neighborhood_extractor::
extract(const int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xneighborhood_cts,
        int xneighborhood_cts_ub,
        int* xneighborhood,
        int xneighborhood_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub > 0);
  require(unexecutable(host contains members with client ids in xdomain_mbrs));
  /// @todo make above precondition executable
  require(xneighborhood_cts != 0);
  require(xneighborhood_cts_ub >= xdomain_mbrs_ub);
  require(xneighborhood != 0);
  require(xneighborhood_ub >= neighborhood_ct(xdomain_mbrs, xdomain_mbrs_ub));
  require(lower_level().has_id_space());

  // Body:

  _down_set.clear();
  _up_set.clear();

  _below_upper_level = false;
  _extracting = true;

  _neighborhood_cts = xneighborhood_cts;
  _neighborhood_cts_ub = xneighborhood_cts_ub;
  _neighborhood_cts_ct = 0;

  _neighborhood = xneighborhood;
  _neighborhood_ub = xneighborhood_ub;
  _neighborhood_ct = 0;

  // Traverse the down set of each entry in xdomain_mbrs;
  // In order to avoid potentially O((mesh size)**2) performance,
  // the has_been_visited bitvector will not be reset between calls.
  // Instead, postvisit action will reset only those bits that are on.

  total_poset_member pm;
  bool reset = true;

  scoped_index pid(upper_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ub; i++)
  {
    // $$SCRIBBLE: attach will interalize id.
    //    pid = upper_level().id_space().hub_pod(xdomain_mbrs[i]);

    pid = xdomain_mbrs[i];

    pm.attach_to_state(host(), pid);

    // cout << endl << "in extract: index = " << pm.index() << endl;

    traverse(&pm, true, reset);
    reset = false;
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(neighborhood_cts_ct() >= 0);
  ensure(neighborhood_ct() >= 0);

  // Exit:

  return;
}



///
void
fiber_bundle::neighborhood_extractor::
count(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));

  // Body:

  _down_set.clear();
  _up_set.clear();

  _below_upper_level = false;
  _extracting = false;

  _neighborhood_cts = 0;
  _neighborhood_cts_ub = 0;
  _neighborhood_cts_ct = 0;

  _neighborhood = 0;
  _neighborhood_ub = 0;
  _neighborhood_ct = 0;

  bool reset = true;
  postorder_member_iterator itr(*xanchor, _upper_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    // cout << endl << "in count: index = " << itr.index() << endl;

    traverse(&(itr.item()), true, reset);
    reset = false;
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(neighborhood_cts_ct() >= 0);
  ensure(neighborhood_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::neighborhood_extractor::
count(const int* xdomain_mbrs, int xdomain_mbrs_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub > 0);
  require(unexecutable(host contains members with client ids in xdomain_mbrs));
  /// @todo make above precondition executable

  // Body:

  _down_set.clear();
  _up_set.clear();

  _below_upper_level = false;
  _extracting = false;

  _neighborhood_cts = 0;
  _neighborhood_cts_ub = 0;
  _neighborhood_cts_ct = 0;

  _neighborhood = 0;
  _neighborhood_ub = 0;
  _neighborhood_ct = 0;

  total_poset_member pm;
  bool reset = true;

  scoped_index pid(upper_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ub; i++)
  {
    // $$SCRIBBLE: attach will interalize id.
    //    pid = upper_level().id_space().hub_pod(xdomain_mbrs[i]);

    pid = xdomain_mbrs[i];

    pm.attach_to_state(host(), pid);

    // cout << endl << "in count: index = " << pm.index() << endl;

    traverse(&pm, true, reset);
    reset = false;
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(neighborhood_cts_ct() >= 0);
  ensure(neighborhood_ct() >= 0);

  // Exit:

  return;
}


void
fiber_bundle::neighborhood_extractor::
previsit_action(abstract_poset_member* xmbr)
{
  // Preconditions:

  require(has_been_visited(xmbr));
  require(_in_down_set ? !is_nested_upper_level(xmbr) : true);
  /// @issue The proper statement of this precondition is that
  /// the upper level subposet is an antichain. How do we evaluate this?
  /// @issue lower level subposet should be an antichain too.

  // Body:

  // cout << "in pre index = " << xmbr->index() << endl;

  if (_below_upper_level)
  {
    // Below the upper level

    if (_in_down_set)
    {
      // Traversing down set

      _down_set.push_front(xmbr->index().pod());

      if (_lower_level.contains_member(xmbr))
      {
        // We're in the pre postion of
        // a lower level member.

        // Reverse order of descent;
        // start to look at up set.

        _in_down_set = false;
        _visited = _up_set_visited;
        _visited->put(xmbr->index().pod(), true);

        // _up_set stores non-strict up set
        // because lower level mbr must be marked
        // visited to satisfy precondition in
        // postvisit action.
        // So lower level members are in
        // both down and up sets.

        _up_set.push_front(xmbr->index().pod());
      }
      // Upper level case: should be unreachable
      /// @issue upper level subposet should be an antichain.

      // Else case: nothing to do.
    }
    else
    {
      // Traversing up set of some lower level member

      _up_set.push_front(xmbr->index().pod());

      // Lower level case: should be unreachable.
      /// @issue lower level subposet should be an antichain.

      if (_upper_level.contains_member(xmbr))
      {
        // We're in the pre position of an upper
        // level member.

        // Don't look any further up in the up set

        _descend = false;
      }

      // Else case: nothing to do.

    }
  }
  else
  {
    // Not below upper level

    // Lower level case: nothing to do

    if (_upper_level.contains_member(xmbr))
    {
      // We're not already below the upper level
      // and we're in the pre position of an
      // upper level member.

      // _down_set stores strict down set, so don't
      // insert this member

      // Turn on down set collection.

      _below_upper_level = true;

      // This is the center of the neighborhood.

      _center = xmbr->index().pod();

      // Store the index of the first neighborhood entry

      _first_entry = _neighborhood_ct;
    }

    // Else case: Nothing to do.
  }

  // Postconditions:






  ensure(unexecutable(xmbr in upper_level implies _below_upper_level));

  // Exit:

  return;
}


void
fiber_bundle::neighborhood_extractor::
link_action(abstract_poset_member* xmbr, abstract_poset_member* linked_mbr)
{
  // Preconditions:

  // Body:

  // Does nothing in this traverser

  // Postconditions:

  // Exit:

  return;
}


void
fiber_bundle::neighborhood_extractor::
postvisit_action(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(has_been_visited(xmbr));

  // Body:

  // cout << "in post index = " << xmbr->index() << endl;

  if (_below_upper_level)
  {
    // Below an upper level member

    if (_in_down_set)
    {
      // Traversing down set of an upper level member

      // Lower level case: shouldn't occur because
      // post position of lower level only occurs
      // in up set traversal.

      if (_upper_level.contains_member(xmbr))
      {
        // We're in the post position of an
        // upper level member, so we're finished with it.

        // Remove strict down set from visited set
        // so members will be visited again from
        // any other upper_level that contains them.
        // Strict down set because we don't want to
        // visit upper level member itself again.

        // cout << "\tclearing down set:";

        while(!_down_set.empty())
        {
          // cout << " " << _down_set.front();

          _down_set_visited->put(_down_set.front(), false);
          _down_set.pop_front();
        }

        // cout << endl;


        // Remove non-strict up set from visited set
        // so members will be visited again from
        // any other loew_level that is contained in them.
        // Non-strict because lower level member itself
        // must be marked visited to satisfy precondition.

        // cout << "\tclearing up set:";

        while(!_up_set.empty())
        {
          // cout << " " << _up_set.front();
          _up_set_visited->put(_up_set.front(), false);
          _up_set.pop_front();
        }
        // cout << endl;

        if (_extracting)
        {
          // Save the number of neighborhood entries for this member.

          _neighborhood_cts[_neighborhood_cts_ct] = _neighborhood_ct - _first_entry;
        }

        // Count the member whether extracting or not.

        _neighborhood_cts_ct++;

        // Not above an upper_level now.

        _below_upper_level = false;
      }
      // else case: nothing to do.

    } // end _in_down_set





    else
    {
      // Traversing up set of a lower level member.

      if (_lower_level.contains_member(xmbr))
      {
        // We're in the post position of the
        // up set traversal of a lower level member.
        // So we're finshed with this up set traversal.

        // Reverse traversal direction

        _in_down_set = true;
        _visited = _down_set_visited;
      }
      else if (_upper_level.contains_member(xmbr))
      {
        // Member is a neighbor;

        if ( _includes_center || (xmbr->index().pod() != _center) )
        {
          // We're including the center or xmbr is not the center.
          // If we're extracting, add it to the neighborhood.

          if (_extracting)
          {
            _neighborhood[_neighborhood_ct] =
              _upper_level.id_space().pod(xmbr->index());
          }

          // Count the neighborhood member whether extracting or not.

          _neighborhood_ct++;
        }
      }

      // Else case: nothing to do.

    } // end !_in_down_set
  } // end _below_upper_level

  // Esle case: Not below an upper level member, do nothing


  // Postconditions:

}


