
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

// Implementation for class section_dof_iterator

#include "section_dof_iterator.h"

#include "poset_state_handle.h"
#include "section_space_schema_member.h"
#include "section_space_schema_poset.h"
#include "assert_contract.h"
#include "discretization_iterator.h"
#include "postorder_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

fiber_bundle::section_dof_iterator&
fiber_bundle::section_dof_iterator::
operator=(const poset_dof_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));
  require(xother.is_done());

  // Body:

  poset_dof_iterator::operator=(xother);

  const section_dof_iterator& cother = reinterpret_cast<const section_dof_iterator&>(xother);
  section_dof_iterator& lother = const_cast<section_dof_iterator&>(cother);

  _itr = lother._itr;

  if(lother.is_initialized())
  {
    _discretization_itr = lother._discretization_itr->clone();
  }
  else
  {
    _discretization_itr = 0;
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(is_table_dof() == xother.is_table_dof());

  // Exit

  return *this;
}

fiber_bundle::section_dof_iterator&
fiber_bundle::section_dof_iterator::
operator=(const section_dof_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}


fiber_bundle::section_dof_iterator::
~section_dof_iterator()
{

  // Preconditions:

  // Body:

  // Delete the existing discretization iterator if it exists.

  if(is_initialized())
  {
    delete _discretization_itr;
  }

  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::section_dof_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_dof_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_dof_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance( poset_dof_iterator::invariant() );

  if(invariant_check())
  {
    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// ITERATOR FACET

bool
fiber_bundle::section_dof_iterator::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = poset_dof_iterator::is_initialized();
  result = result && (_discretization_itr != 0);
  result = result && _discretization_itr->is_initialized();

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::section_dof_iterator::
put_anchor(const schema_poset_member* xanchor, int xversion)
{
  // Preconditions:

  require(xanchor != 0);
  require(item_is_ancestor_of(*xanchor));
  require(xanchor->state_is_read_accessible());
  require(xanchor->host()->is_schematized(false));
  require(xanchor->has_version(xversion));


  // Body:

  if(_anchor == 0)
  {
    // Create the anchor handle

    _anchor = xanchor->clone();
  }

  // Attach the handle to the same state and
  // (possibly aliased) version as xanchor.

  _anchor->attach_to_state(xanchor);

  // Set the version, making sure it is unaliased.

  _anchor->put_version(xversion, true);

  // Get the anchor of appropriate type.

  section_space_schema_member* lanchor = reinterpret_cast<section_space_schema_member*>(_anchor);

  // Reset the base component iterator

  if(_is_table_dof)
  {
    // Iterating over table dofs.
    // Table dofs are {base.bottom()} x {fiber schema table dofs}.
    // Bottom is in every version, so it doesn't matter what version.

    postorder_iterator* litr =
      reinterpret_cast<postorder_iterator*>(_discretization_itr);
    litr->put_anchor(&(lanchor->host()->base_space().bottom()));
  }
  else
  {
    discretization_iterator* litr =
      reinterpret_cast<discretization_iterator*>(_discretization_itr);
    litr->put_schema_anchor(*lanchor);
  }

  // Reset the index iterator.

  string ldof_sp_name = schema_poset_member::dof_subposet_name("top", _is_table_dof);
  _itr.put_anchor(&(lanchor->fiber_schema()));
  _itr.put_filter(ldof_sp_name);

  // Reset the item

  reset_item();

  // Force the iterator to be done.

  force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().is_same_state(xanchor));
  ensure(anchor().is_same_type(xanchor));
  ensure(anchor().version() == xanchor->unaliased_version(xversion));

  // Exit:

}

bool
fiber_bundle::section_dof_iterator::
is_done() const
{
  bool result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _discretization_itr->is_done();

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::section_dof_iterator::
force_is_done()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Virtual redefinition of is_done means
  // discretization iterator must be shut down first
  // so that is_done will will true is postcondition
  // of poset_dof_iterator::force_is_done.

  /// @issue the above requirement is probably a symptom
  /// of bad design. Either is_done should not be virtual
  /// or this class should not inherit poset_dof_iterator,
  /// because poset_dof_iterator::force_is_done has no way
  /// to actually ensure the virtual is_done postcondition.

  _discretization_itr->force_is_done();
  poset_dof_iterator::force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit:
}

void
fiber_bundle::section_dof_iterator::
next()
{

  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  _itr.next();

  if(_itr.is_done())
  {
    // Fiber schema is done;
    // move to next base item.

    _discretization_itr->next();

    if(!_discretization_itr->is_done())
    {
      // Base iteration is not done;
      // reset the fiber schema.

      _itr.reset();
    }
  }

  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() == item().is_attached());
  ensure(unexecutable(postorder - have visited all of the members of the strict down set
                        of item()));

  // Exit

  return;
}

void
fiber_bundle::section_dof_iterator::
reset(bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  define_old_variable(int old_anchor_version = anchor().version());

  // Body:

  _itr.reset(xreset_markers);

  if(_itr.is_done())
  {
    _discretization_itr->force_is_done();
  }
  else
  {
    _discretization_itr->reset(xreset_markers);

    if(_discretization_itr->is_done())
      _itr.force_is_done();
  }

  update_item();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(item().is_attached() == !is_done());
  ensure(anchor().version() == old_anchor_version);

  // Exit

  return;
}

int
fiber_bundle::section_dof_iterator::
ct(bool xreset)
{
  int result = 0;

  // Preconditions:

  require(is_initialized());
  require(xreset ? anchor().state_is_read_accessible(): true);

  // Body:

  result = _discretization_itr->ct(xreset)*_itr.ct(xreset);
  update_item();

  // Postconditions:

  ensure(result >= 0);
  ensure(is_done());

  // Exit

  return result;
}

bool
fiber_bundle::section_dof_iterator::
has_visited(pod_index_type xhub_id) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  result = _discretization_itr->has_visited(anchor().host()->get_base_space_id_from_index(xhub_id)) &&
           _itr.has_visited(anchor().host()->get_fiber_schema_id_from_index(xhub_id)) ;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_dof_iterator::
has_visited(const schema_poset_member& xmbr) const
{
  bool result;

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(item_is_ancestor_of(xmbr));
  require(xmbr.is_attached());
  require(anchor().host()->is_same_state(xmbr.host()));

  // Body:

  const section_space_schema_member& lmbr = reinterpret_cast<const section_space_schema_member&>(xmbr);

  result = _discretization_itr->has_visited(lmbr.base_space_id()) &&
           _itr.has_visited(lmbr.fiber_schema_id());

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::section_dof_iterator::
put_has_visited(pod_index_type xhub_id, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  _discretization_itr->put_has_visited(anchor().host()->get_base_space_id_from_index(xhub_id), xvalue);
  _itr.put_has_visited(anchor().host()->get_fiber_schema_id_from_index(xhub_id), xvalue) ;

  // Postconditions:

  ensure(has_visited(xhub_id) == xvalue);

  // Exit:

  return;
}

// MEMBER ITERATOR FACET

fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    reinterpret_cast<section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_dof_iterator::
item_is_ancestor_of(const schema_poset_member& xmbr) const
{
  bool result;

  // Preconditions:

  // Body:

  // Always true in this class;
  // intended to be redefined in descendants.

  result = dynamic_cast<const section_space_schema_member*>(&xmbr) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_dof_iterator::
section_dof_iterator()
    : poset_dof_iterator()
{

  // Preconditions:


  // Body:

  _discretization_itr = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

fiber_bundle::section_dof_iterator::
section_dof_iterator(const section_dof_iterator& xother)
    : poset_dof_iterator(xother)
{

  // Preconditions:

  // Body:

  section_dof_iterator& lother = const_cast<section_dof_iterator&>(xother);

  _itr = lother._itr;

  if(lother.is_initialized())
  {
    _discretization_itr = lother._discretization_itr->clone();
  }
  else
  {
    _discretization_itr = 0;
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? anchor().version() == xother.anchor().version() : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(is_table_dof() == xother.is_table_dof());
  // Exit

  return;
}

