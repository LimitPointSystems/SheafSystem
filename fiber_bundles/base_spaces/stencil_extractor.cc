
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class STENCIL_EXTRACTOR

#include "stencil_extractor.h"
#include "assert_contract.h"
#include "abstract_poset_member.h"
#include "list_cover_set.h"
#include "poset_state_handle.h"
#include "postorder_member_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
fiber_bundle::stencil_extractor::
stencil_extractor(const stencil_extractor& xother)
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
fiber_bundle::stencil_extractor&
fiber_bundle::stencil_extractor::
operator=(const stencil_extractor& xother)
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
fiber_bundle::stencil_extractor::
~stencil_extractor()
{

  // Preconditions:

  // Body:

  _lower_level.detach_from_state();
  _upper_level.detach_from_state();
  delete _down_set_visited;

  // Postconditions:

  ensure(invariant());

}

///
bool
fiber_bundle::stencil_extractor::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(poset_dft::invariant());

  if(invariant_check())
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


// STENCIL_EXTRACTOR INTERFACE

///
fiber_bundle::stencil_extractor::
stencil_extractor(const poset_state_handle* xhost,
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

  // Visited marker for up set portion of traversal has been
  // allocated in poset_traverser::poset_traverser, save a
  // pointer to it.

  _up_set_visited = _visited;

  // Allocate visited marker for up set portion of traversal

  _down_set_visited = new zn_to_bool(member_index_ub().pod());

  _includes_center = xincludes_center;

  _stencil_cts = 0;
  _stencil_cts_ub = 0;
  _stencil_cts_ct = 0;

  _stencil = 0;
  _stencil_ub = 0;
  _stencil_ct = 0;


  // Postconditions:

  ensure(invariant());
  ensure(stencil_cts_ct() == 0);
  ensure(stencil_ct() == 0);

}






///
void
fiber_bundle::stencil_extractor::
extract(const abstract_poset_member* xanchor,
        int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xstencil_cts,
        int xstencil_cts_ub,
        int* xstencil,
        int xstencil_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub >= domain_mbrs_ct(xanchor));
  require(xstencil_cts != 0);
  require(xstencil_cts_ub >= stencil_cts_ct());
  // Preceeding call depends on call to domain_mbrs_ct() above
  require(xstencil != 0);
  require(xstencil_ub >= stencil_ct());
  // Preceeding call depends on call to domain_mbrs_ct() above
  require(upper_level().has_id_space());

  // Body:

  _down_set.clear();
  _up_set.clear();

  _above_lower_level = false;
  _extracting = true;

  _stencil_cts = xstencil_cts;
  _stencil_cts_ub = xstencil_cts_ub;
  _stencil_cts_ct = 0;

  _stencil = xstencil;
  _stencil_ub = xstencil_ub;
  _stencil_ct = 0;


  bool reset = true;
  int i = 0;
  postorder_member_iterator itr(*xanchor, _lower_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    xdomain_mbrs[i++] =
      lower_level().id_space().pod(itr.item().index());

    // cout << endl << "in extract: index = " << itr.index() << endl;

    traverse(&(itr.item()), false, reset);
    reset = false;
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(stencil_cts_ct() >= 0);
  ensure(stencil_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::stencil_extractor::
extract(const int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xstencil_cts,
        int xstencil_cts_ub,
        int* xstencil,
        int xstencil_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub > 0);
  require(unexecutable(host contains members with client ids in xdomain_mbrs));
  /// @todo make above precondition executable
  require(xstencil_cts != 0);
  require(xstencil_cts_ub >= xdomain_mbrs_ub);
  require(xstencil != 0);
  require(xstencil_ub >= stencil_ct(xdomain_mbrs, xdomain_mbrs_ub));
  require(lower_level().has_id_space());

  // Body:

  _down_set.clear();
  _up_set.clear();

  _above_lower_level = false;
  _extracting = true;

  _stencil_cts = xstencil_cts;
  _stencil_cts_ub = xstencil_cts_ub;
  _stencil_cts_ct = 0;

  _stencil = xstencil;
  _stencil_ub = xstencil_ub;
  _stencil_ct = 0;

  // Traverse the up set of each entry in xdomain_mbrs;
  // In order to avoid potentially O((mesh size)**2) performance,
  // the has_been_visited bitvector will not be reset between calls.
  // Instead, postvisit action will reset only those bits that are on.

  total_poset_member pm;
  bool reset = true;

  scoped_index pid(lower_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ub; i++)
  {
    // $$SCRIBBLE: attach will interalize id.
    //    pid = lower_level().id_space().hub_pod(xdomain_mbrs[i]);

    pid = xdomain_mbrs[i];

    pm.attach_to_state(host(), pid);

    // cout << endl << "in extract: index = " << pm.index() << endl;

    traverse(&pm, false, reset);
    reset = false;
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(stencil_cts_ct() >= 0);
  ensure(stencil_ct() >= 0);

  // Exit:

  return;
}



///
void
fiber_bundle::stencil_extractor::
count(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));

  // Body:

  _down_set.clear();
  _up_set.clear();

  _above_lower_level = false;
  _extracting = false;

  _stencil_cts = 0;
  _stencil_cts_ub = 0;
  _stencil_cts_ct = 0;

  _stencil = 0;
  _stencil_ub = 0;
  _stencil_ct = 0;

  bool reset = true;
  postorder_member_iterator itr(*xanchor, _lower_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    // cout << endl << "in count: index = " << itr.index() << endl;

    traverse(&(itr.item()), false, reset);
    reset = false;
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(stencil_cts_ct() >= 0);
  ensure(stencil_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::stencil_extractor::
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

  _above_lower_level = false;
  _extracting = false;

  _stencil_cts = 0;
  _stencil_cts_ub = 0;
  _stencil_cts_ct = 0;

  _stencil = 0;
  _stencil_ub = 0;
  _stencil_ct = 0;

  total_poset_member pm;
  bool reset = true;

  scoped_index pid(lower_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ub; i++)
  {
    // $$SCRIBBLE: attach will interalize id.
    //    pid = lower_level().id_space().hub_pod(xdomain_mbrs[i]);

    pid = xdomain_mbrs[i];

    pm.attach_to_state(host(), pid);

    // cout << endl << "in count: index = " << pm.index() << endl;

    traverse(&pm, false, reset);
    reset = false;
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(stencil_cts_ct() >= 0);
  ensure(stencil_ct() >= 0);

  // Exit:

  return;
}


void
fiber_bundle::stencil_extractor::
previsit_action(abstract_poset_member* xmbr)
{
  // Preconditions:

  require(has_been_visited(xmbr));
  require(!_in_down_set ? !is_nested_lower_level(xmbr) : true);
  /// @issue The proper statement of this precondition is that
  /// the lower level subposet is an antichain. How do we evaluate this?
  /// @issue lower level subposet should be an antichain too.

  // Body:

  // cout << "in pre index = " << xmbr->index() << endl;

  if(_above_lower_level)
  {
    // Above the lower level

    if(!_in_down_set)
    {
      // Traversing up set

      _up_set.push_front(xmbr->index().pod());

      if(_upper_level.contains_member(xmbr))
      {
        // We're in the pre postion of
        // a upper level member.

        // Reverse order of descent;
        // start to look at down set.

        _in_down_set = true;
        _visited = _down_set_visited;
        _visited->put(xmbr->index().pod(), true);

        // _down_set stores non-strict down set
        // because upper level mbr must be marked
        // visited to satisfy precondition in
        // postvisit action.
        // So upper level members are in
        // both down and up sets.

        _down_set.push_front(xmbr->index().pod());
      }
      // Lower level case: should be unreachable
      /// @issue lower level subposet should be an antichain.

      // Else case: nothing to do.
    }
    else
    {
      // Traversing down set of some upper level member

      _down_set.push_front(xmbr->index().pod());

      // Upper level case: should be unreachable.
      /// @issue upper level subposet should be an antichain.

      if(_lower_level.contains_member(xmbr))
      {
        // We're in the pre position of an lower
        // level member.

        // Don't look any further down in the down set

        _descend = false;
      }

      // Else case: nothing to do.

    }
  }
  else
  {
    // Not above lower level

    // Upper level case: nothing to do

    if(_lower_level.contains_member(xmbr))
    {
      // We're not already above the lower level
      // and we're in the pre position of an
      // lower level member.

      // _up_set stores strict up set, so don't
      // insert this member

      // Turn on up set collection.

      _above_lower_level = true;

      // This is the center of the stencil.

      _center = xmbr->index().pod();

      // Store the index of the first stencil entry

      _first_entry = _stencil_ct;
    }

    // Else case: Nothing to do.
  }

  // Postconditions:




  ensure(invariant());
  ensure(unexecutable(xmbr in lower_level implies _above_lower_level));

  // Exit:

  return;
}


void
fiber_bundle::stencil_extractor::
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
fiber_bundle::stencil_extractor::
postvisit_action(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(has_been_visited(xmbr));

  // Body:

  // cout << "in post index = " << xmbr->index() << endl;

  if(_above_lower_level)
  {
    // Above an lower level member

    if(!_in_down_set)
    {
      // Traversing up set of an lower level member

      // Upper level case: shouldn't occur because
      // post position of upper level only occurs
      // in down set traversal.

      if(_lower_level.contains_member(xmbr))
      {
        // We're in the post position of an
        // lower level member, so we're finished with it.

        // Remove strict up set from visited set
        // so members will be visited again from
        // any other lower_level that contains them.
        // Strict up set because we don't want to
        // visit lower level member itself again.

        // cout << "\tclearing up set:";

        while(!_up_set.empty())
        {
          // cout << " " << _up_set.front();

          _up_set_visited->put(_up_set.front(), false);
          _up_set.pop_front();
        }

        // cout << endl;


        // Remove non-strict down set from visited set
        // so members will be visited again from
        // any other lower_level that is contained in them.
        // Non-strict because upper level member itself
        // must be marked visited to satisfy precondition.

        // cout << "\tclearing down set:";

        while(!_down_set.empty())
        {
          _down_set_visited->put(_down_set.front(), false);
          _down_set.pop_front();
        }
        // cout << endl;

        if(_extracting)
        {
          // Save the number of stencil entries for this member.

          _stencil_cts[_stencil_cts_ct] = _stencil_ct - _first_entry;
        }

        // Count the member whether extracting or not.

        _stencil_cts_ct++;

        // Not above an lower_level now.

        _above_lower_level = false;
      }
      // else case: nothing to do.

    } // end !_in_down_set




    else
    {
      // Traversing down set of a upper level member.

      if(_upper_level.contains_member(xmbr))
      {
        // We're in the post position of the
        // down set traversal of a upper level member.
        // So we're finshed with this down set traversal.

        // Reverse traversal direction

        _in_down_set = false;
        _visited = _up_set_visited;
      }
      else if(_lower_level.contains_member(xmbr))
      {
        // Member is a neighbor;

        if( _includes_center || (xmbr->index().pod() != _center) )
        {
          // We're including the center or xmbr is not the center.
          // If we're extracting, add it to the stencil.

          if(_extracting)
          {
            _stencil[_stencil_ct] =
              _lower_level.id_space().pod(xmbr->index());
          }

          // Count the stencil member whether extracting or not.

          _stencil_ct++;
        }
      }

      // Else case: nothing to do.

    } // end !_in_down_set
  } // end _above_lower_level

  // Else case: Not above an lower level member, do nothing


  // Postconditions:




  ensure(invariant());
}


