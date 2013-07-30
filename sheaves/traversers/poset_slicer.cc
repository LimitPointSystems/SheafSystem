
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class POSET_SLICER

#include "poset_slicer.h"
#include "assert_contract.h"
#include "poset.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "total_poset_member.h"

// inlines placed here so they will be visible when called
// Not put in header file because they are olny used here and
// to avoid including poset_member.h in poset_slicer.h

inline bool
sheaf::poset_slicer::
only_shallowest()
{
  return ( (_mode == MAXIMAL) && _in_down_set) || ((_mode == MINIMAL) && !_in_down_set);
}

inline bool
sheaf::poset_slicer::
only_deepest()
{
  return ( (_mode == MINIMAL) && _in_down_set) || ((_mode == MAXIMAL) && !_in_down_set);
}

inline bool
sheaf::poset_slicer::
layer_contains_member(const abstract_poset_member* xmbr)
{
  return ( (_layer == 0) || _layer->contains_member(xmbr) );
}

inline bool
sheaf::poset_slicer::
slice_contains_member(abstract_poset_member* xmbr)
{
  return ( (_slice == 0) || _slice->contains_member(xmbr) );
}

inline void
sheaf::poset_slicer::
insert_member(abstract_poset_member* xmbr)
{
  _slice->insert_member(xmbr);
}


///
bool
sheaf::poset_slicer::
invariant() const
{
  bool result = true;

  result = result && poset_traverser::invariant();
  //   result = result && ( (_layer != 0) ? ( _layer->host() == _host ) : true );
  //   result = result && ( (_slice != 0) ? ( _slice->host() == _host ) : true );
  result = result && ( (_layer != 0) ? ( _layer->host()->is_same_state(_host) ) : true );
  result = result && ( (_slice != 0) ? ( _slice->host()->is_same_state(_host) ) : true );

  return result;
}


///
sheaf::poset_slicer::
poset_slicer(const poset_state_handle* xhost)
    : poset_dft(xhost)
{

  // preconditions:

  require(xhost != 0);

  // body:

  // initialize data members

  _layer = 0;
  _slice = 0;

  // postconditions:

  ensure(invariant());
}


///
sheaf::poset_slicer::
~poset_slicer()
{

  // preconditions:

  // body:

  // postconditions:

}


///
sheaf::subposet*
sheaf::poset_slicer::
find(abstract_poset_member* xanchor, subposet* xlayer, bool xdown, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(xlayer));

  // Body:

  result = new subposet(_host);
  find_pa(xanchor, xlayer, xdown, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(has_same_host(result));
  ensure(unexecutable(result is intersection(xmode members of xdown set
                        of xanchor, xlayer)));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
find_pa(abstract_poset_member* xanchor, subposet* xlayer, bool xdown, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(xlayer != 0 ? has_same_host(xlayer) : true);
  require(has_same_host(result));

  // Body:

  _layer = xlayer;
  _slice = result;
  _mode  = xmode;
  _select_only_shallowest = only_shallowest();
  _select_only_deepest    = only_deepest();
  _depth_below_shallowest = -1;
  _height_above_deepest = -1;


  traverse(xanchor, xdown);

  // clean up

  _slice = 0;


  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(intersection(xdown set
                        of xanchor, xlayer), old result)));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
find(subposet* xanchor, subposet* xlayer, bool xdown, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(xlayer));

  // Body:

  result = new subposet(_host);
  find_pa(xanchor, xlayer, xdown, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(has_same_host(result));
  ensure(unexecutable(result is intersection(xmode memberss of xdown set
                        of xanchor, xlayer)));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
find_pa(const subposet* xanchor, subposet* xlayer, bool xdown, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(xlayer != 0 ? has_same_host(xlayer) : true);
  require(has_same_host(result));
  require(!xanchor->is_same_state(result));

  // Body:

  _layer = xlayer;
  _slice = result;
  _mode = xmode;
  _in_down_set = xdown;
  _select_only_shallowest = only_shallowest();
  _select_only_deepest    = only_deepest();
  _depth_below_shallowest = -1;
  _height_above_deepest = -1;

  // The down or up set of a subposet is the union of the
  // down or up sets of its members. In order to get the
  // down or up sets of all the members, start a DFT at
  // each member. Take the union implicitly (and efficiently)
  // by accumulating in a single result and by not
  // resetting the _visited markers between traversals.

  mark_members_not_visited();

  poset_member_iterator* itr = xanchor->member_iterator();
  while(!itr->is_done())
  {
    if(!has_been_visited(itr))
    {
      // traverse down or up set of itr without resetting markers
      traverse(itr, _in_down_set, false);
    }
    itr->next();
  }

  delete itr;

  // clean up

  _anchor = 0;
  _slice = 0;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(intersection(xdown set
                        of xanchor, xlayer), old result) ));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
find_jims(abstract_poset_member* xanchor, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));

  // Body:

  result = new subposet(_host);
  find_jims_pa(xanchor, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(has_same_host(result));
  ensure(unexecutable(result is xmode jims of xanchor));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
find_jims_pa(abstract_poset_member* xanchor, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));

  // Body:

  subposet* jims = &(host()->jims());

  //  find_pa(xanchor, jims, sheaf_constants::DOWN, result, xmode);
  find_pa(xanchor, jims, true, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(jims of xanchor, old result)));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
find_jims(const subposet* xanchor, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));

  // Body:

  result = new subposet(_host);
  find_jims_pa(xanchor, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode jims of xanchor));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
find_jims_pa(const subposet* xanchor, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));
  require(!xanchor->is_same_state(result));

  // Body:

  _layer = &(host()->jims());

  _slice = result;
  _mode = xmode;
  _in_down_set = true;
  _select_only_shallowest = only_shallowest();
  _select_only_deepest    = only_deepest();
  _depth_below_shallowest = -1;
  _height_above_deepest = -1;


  // The down set of a subposet is the union of the
  // down sets of its members. In order to get the
  // down sets of all the members, start a DFT at
  // each member. Take the union implicitly (and efficiently)
  // by accumulating in a single result and by not
  // resetting the _visited markers between traversals.

  mark_members_not_visited();

  poset_member_iterator* itr = xanchor->member_iterator();
  while(!itr->is_done())
  {
    if(!has_been_visited(itr))
    {
      // traverse down set of itr without resetting markers
      traverse(itr, _in_down_set, false);
    }
    itr->next();
  }

  delete itr;

  // forget pointer to anchor and result

  _anchor = 0;
  _slice = 0;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(jims of xanchor, old result)));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
down_set(abstract_poset_member* xanchor, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));

  // Body:

  result = new subposet(_host);
  down_set_pa(xanchor, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(has_same_host(result));
  ensure(unexecutable(result is xmode members of down set
                        of xanchor));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
down_set_pa(abstract_poset_member* xanchor, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));

  // Body:

  find_pa(xanchor, 0, true, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is union(xmode members of down set
                                        of xanchor, old result)));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
up_set(abstract_poset_member* xanchor, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));

  // Body:

  result = new subposet(_host);
  up_set_pa(xanchor, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(has_same_host(result));
  ensure(unexecutable(result is xmode members of up set
                        of xanchor));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
up_set_pa(abstract_poset_member* xanchor, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));

  // Body:

  //  find_pa(xanchor, 0, sheaf_constants::UP, result, xmode);
  find_pa(xanchor, 0, false, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(up set
                        of xanchor, old result)));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
down_set(const subposet* xanchor, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));

  // Body:

  result = new subposet(_host);
  down_set_pa(xanchor, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of down set
                        of xanchor));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
down_set_pa(const subposet* xanchor, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));
  require(!xanchor->is_same_state(result));

  // Body:

  vertical_set_pa(xanchor, result, xmode, true);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(down set
                        of xanchor, old result)));

  // Exit

  return;
}


///
sheaf::subposet*
sheaf::poset_slicer::
up_set(const subposet* xanchor, slice_mode xmode)
{
  subposet* result;

  // Preconditions:

  require(has_same_host(xanchor));

  // Body:

  result = new subposet(_host);
  up_set_pa(xanchor, result, xmode);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of up set
                        of xanchor));

  // Exit

  return result;
}


///
void
sheaf::poset_slicer::
up_set_pa(const subposet* xanchor, subposet* result, slice_mode xmode)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));
  require(!xanchor->is_same_state(result));

  // Body:

  vertical_set_pa(xanchor, result, xmode, false);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(up set
                        of xanchor, old result)));

  // Exit

  return;
}


void
sheaf::poset_slicer::
vertical_set_pa(const subposet* xanchor, subposet* result, slice_mode xmode, bool xdown)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(has_same_host(result));
  require(!xanchor->is_same_state(result));

  // Body:

  _layer = 0;
  _slice = result;
  _mode = xmode;
  _in_down_set = xdown;
  _select_only_shallowest = only_shallowest();
  _select_only_deepest    = only_deepest();
  _depth_below_shallowest = -1;
  _height_above_deepest = -1;

  // The down (up) set of a subposet is the union of the
  // down (up) sets of its members. In order to get the
  // down (up) sets of all the members, start a DFT at
  // each member. Take the union implicitly (and efficiently)
  // by accumulating in a single result and by not
  // resetting the _visited markers between traversals.

  mark_members_not_visited();

  poset_member_iterator* itr = xanchor->member_iterator();
  while(!itr->is_done())
  {
    if(!has_been_visited(itr))
    {
      // traverse down set of itr without resetting markers
      traverse(itr, _in_down_set, false);
    }
    itr->next();
  }

  delete itr;

  // clean up

  _anchor = 0;
  _slice = 0;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(xdown set
                        of xanchor, old result)));

  // Exit

  return;
}

void
sheaf::poset_slicer::
previsit_action(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(xmbr != 0);
  require(xmbr->is_attached());
  require(xmbr->host() == host());
  require(has_been_visited(xmbr));

  // Body:

  // If we are below the shallowest selected member, we're getting deeper.

  if(_depth_below_shallowest >= 0)
    _depth_below_shallowest++;

  // We're going down, so we don't know if were above the deepest member yet.

  _height_above_deepest = -1;

  // If selecting all or shallowest, look for them on the way down

  if( ( (_mode == ALL) || (_select_only_shallowest && ( _depth_below_shallowest < 0)) ) &&
      layer_contains_member(xmbr) )
  {
    // Found the shallowest member;
    // insert it in result

    insert_member(xmbr);

    // Depth below shallowest is 0 now.

    _depth_below_shallowest = 0;
  }

  // Postconditions:

  // Exit:

  return;
}


void
sheaf::poset_slicer::
link_action(abstract_poset_member* xmbr, abstract_poset_member* linked_mbr)
{

  // Preconditions:

  // Body:

  // If xmbr is below a shallowest member and linked_mbr
  // has previously been accepted as a shallowest member,
  // remove it.

  if( (_select_only_shallowest && (_depth_below_shallowest >= 0))  && slice_contains_member(linked_mbr))
  {
    _slice->remove_member(linked_mbr);
  }
  else if( (_select_only_deepest && (_height_above_deepest < 0))  && slice_contains_member(linked_mbr))
  {
    _height_above_deepest = 1;
  }

  // Postconditions:

  // Exit

  return;
}


void
sheaf::poset_slicer::
postvisit_action(abstract_poset_member* xmbr)
{

  // Preconditions:

  // Body:

  // If we're below the shallowest member, we're getting shallower

  if(_depth_below_shallowest >= 0)
    _depth_below_shallowest--;

  // If we're above the deepest member, we're getting higher.

  if(_height_above_deepest >= 0)
    _height_above_deepest++;

  // If selecting only deepest members, look for them on the way up.

  if(_select_only_deepest && (_height_above_deepest < 0) && layer_contains_member(xmbr) )
  {
    // Found the deepest member;
    // insert it in the result

    insert_member(xmbr);

    // height above deepest is 0 now

    _height_above_deepest = 0;
  }

  // Postconditions:

  // Exit

  return;
}


void
sheaf::poset_slicer::
find_pa(const block<scoped_index>& xanchor,
        subposet* xlayer,
        bool xdown,
        subposet* result,
        slice_mode xmode)
{
  // Preconditions:

  require(xlayer != 0 ? has_same_host(xlayer) : true);
  require(host()->contains_members(xanchor));
  require(has_same_host(result));

  // Body:

  _layer = xlayer;
  _slice = result;
  _mode = xmode;
  _in_down_set = xdown;
  _select_only_shallowest = only_shallowest();
  _select_only_deepest    = only_deepest();
  _depth_below_shallowest = -1;
  _height_above_deepest = -1;

  // The down set of a subposet is the union of the
  // down sets of its members. In order to get the
  // down sets of all the members, start a DFT at
  // each member. Take the union implicitly (and efficiently)
  // by accumulating in a single result and by not
  // resetting the _visited markers between traversals.

  mark_members_not_visited();

  total_poset_member lanchor;

  for(int i=0; i < xanchor.ct(); i++)
  {
    lanchor.attach_to_state(host(), xanchor[i]);

    if(!has_been_visited(&lanchor))
    {
      // Traverse down set of itr without resetting markers.

      traverse(&lanchor, _in_down_set, false);
    }
  }

  lanchor.detach_from_state();

  // clean up

  _anchor = 0;
  _slice = 0;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result is xmode members of union(intersection(xdown set
                        of xanchor, xlayer), old result) ));

  // Exit

  return;
}









