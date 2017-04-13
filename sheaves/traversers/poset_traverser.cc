
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Implementation for class POSET_TRAVERSER

#ifndef POSET_TRAVERSER_H
#include "SheafSystem/poset_traverser.h"
#endif

#include "SheafSystem/assert_contract.h"

#ifndef POSET_H
#include "SheafSystem/poset.h"
#endif

#ifndef POSET_MEMBER_H
#include "SheafSystem/total_poset_member.h"
#endif

#ifndef POSET_MEMBER_ITERATOR_H
#include "SheafSystem/poset_member_iterator.h"
#endif

#ifndef BIT_VECTOR_H
#include "SheafSystem/zn_to_bool.h"
#endif

///
bool
sheaf::poset_traverser::
invariant() const
{
  bool result = true;

  result = result && (_host != 0);
  result = result && (_host->state_is_read_accessible());

  result = result && (_visited != 0);
  result = result && ( (_anchor != 0) ? _visited->ub() >= member_index_ub().pod() : true);

  result = result && ( (_anchor != 0) ? _anchor->is_attached() : true);
  result = result && ( (_anchor != 0) ? _anchor->host() == _host : true);

  return result;
}




///
bool
sheaf::poset_traverser::
has_same_host(const poset_component* other) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (other != 0) && (other->host() == host());

  // Postconditions:

  ensure(result == ( (other != 0) && (other->host() == host()) ));

  // Exit

  return result;
}

///
sheaf::abstract_poset_member*
sheaf::poset_traverser::
anchor()
{
  abstract_poset_member* result;

  // Preconditions:

  // Body:

  result = _anchor;

  // Postconditions:

  // Exit:

  return result;
}



///
const sheaf::abstract_poset_member*
sheaf::poset_traverser::
anchor() const
{
  abstract_poset_member* result;

  // Preconditions:

  // Body:

  result = _anchor;

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::poset_traverser::
poset_traverser(const poset_state_handle* xhost)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // body:

  _host  = const_cast<poset_state_handle*>(xhost);
  _visited = new zn_to_bool(member_index_ub().pod());
  _anchor = 0;
  _in_down_set = true;


  // postconditions:

  ensure(invariant());
}


///
sheaf::poset_traverser::
~poset_traverser()
{

  // body:

  delete _visited;
}


///
void
sheaf::poset_traverser::
traverse(const abstract_poset_member* xanchor, bool down, bool reset_markers)
{
  // Preconditions:

  require(has_same_host(xanchor));
  require(xanchor->state_is_read_accessible());

  // Body:

  _anchor = const_cast<abstract_poset_member*>(xanchor);
  _in_down_set = down;

  // Make sure there are enough visited markers

  ensure_visited_ub();

  // make sure the visited markers are all off

  if(reset_markers)
    mark_members_not_visited();

  // execute traversal defined by descendant

  private_traverse();

  // forget pointer to anchor

  _anchor = 0;

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(private_traverse()));
  ensure(anchor() == 0);

  // Exit:

  return;
}



///
bool
sheaf::poset_traverser::
has_been_visited(const abstract_poset_member* xmbr) const
{

  // Preconditions:

  require(xmbr != 0);
  require(xmbr->is_attached());
  require(xmbr->host() == host());

  // body:

  bool result = (*_visited)[xmbr->index().pod()];

  return result;
}



///
sheaf::scoped_index
sheaf::poset_traverser::
member_index_ub() const
{
  // Preconditions:

  // Body:

  scoped_index result = _host->member_index_ub();

  // Postconditions:

  // Exit

  return result;
}



bool
sheaf::poset_traverser::
no_members_visited() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _visited->is_false();

  // Postconditions:

  ensure(result == unexecutable(no member is marked visited));

  // Exit

  return result;
}



bool
sheaf::poset_traverser::
all_members_visited() const
{
  bool result = true;

  // Preconditions:

  // Body:

  index_iterator itr = _host->member_iterator();

  while(result && !itr.is_done())
  {
    result = result && (*_visited)[itr.index().pod()];

    itr.next();
  }


  // Postconditions:

  ensure(unexecutable(result if and only if every member is marked visited))
      ;

  // Exit

  return result;
}



void
sheaf::poset_traverser::
mark_members_not_visited()
{

  // Preconditions:

  // None.

  // Body:

  _visited->make_false_sa();

  // Postconditions:

  ensure(no_members_visited());

  // Exit:

  return;
}



void
sheaf::poset_traverser::
mark_visited(const abstract_poset_member* xmbr)
{

  // preconditions:

  require(xmbr != 0);
  require(xmbr->is_attached());
  require(xmbr->host() == _anchor->host());

  // body:

  _visited->force(xmbr->index().pod(), true);

  // postconditions:

  ensure(has_been_visited(xmbr));
}
