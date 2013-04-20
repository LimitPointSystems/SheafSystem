
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class binary_section_dof_iterator

#include "binary_section_dof_iterator.h"

#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "poset_state_handle.h"
#include "assert_contract.h"
#include "discretization_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

///
fiber_bundle::binary_section_dof_iterator::
binary_section_dof_iterator()
    : section_dof_iterator()
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}


///
fiber_bundle::binary_section_dof_iterator::
binary_section_dof_iterator(const binary_section_dof_iterator& xother)
    : section_dof_iterator(xother)
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));

  // Exit

  return;
}

///
fiber_bundle::binary_section_dof_iterator&
fiber_bundle::binary_section_dof_iterator::
operator=(const poset_dof_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  (void) section_dof_iterator::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);
  ensure(is_initialized() ? item().is_same_type(&xother.item()) : true);
  ensure(unexecutable(this is first member of iteration or is_done()));
  // Exit

  return *this;
}

///
fiber_bundle::binary_section_dof_iterator&
fiber_bundle::binary_section_dof_iterator::
operator=(const binary_section_dof_iterator& xother)
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


///
fiber_bundle::binary_section_dof_iterator::
~binary_section_dof_iterator()
{

  // Preconditions:

  // Body:

  // Nothing to do - base class does it all.

  // Postconditions:

  // Exit:

  return;
}

///
bool
fiber_bundle::binary_section_dof_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const binary_section_dof_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

///
fiber_bundle::binary_section_dof_iterator*
fiber_bundle::binary_section_dof_iterator::
clone() const
{
  binary_section_dof_iterator* result;

  // Preconditions:

  // Body:

  result = new binary_section_dof_iterator;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

///
bool
fiber_bundle::binary_section_dof_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && section_dof_iterator::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    invariance(dynamic_cast<binary_section_space_schema_member*>(_anchor) != 0);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
fiber_bundle::binary_section_dof_iterator::
binary_section_dof_iterator(const binary_section_space_schema_member& xanchor,
                            bool xis_table_dof,
                            int xversion)
    : section_dof_iterator()
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->is_schematized(false));
  require(xanchor.has_version(xversion));


  // Body:

  initialize(xanchor, xis_table_dof, xversion);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.unaliased_version(xversion));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}


// ITERATOR FACET

///
fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_dof_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  binary_section_space_schema_member& result =
    reinterpret_cast<binary_section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

///
const fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_dof_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  binary_section_space_schema_member& result =
    reinterpret_cast<binary_section_space_schema_member&>(*_anchor);

  // Postconditions:

  // Exit

  return result;
}

// MEMBER ITERATOR FACET

///
fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_dof_iterator::
item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  binary_section_space_schema_member& result =
    reinterpret_cast<binary_section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}

///
const fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_dof_iterator::
item() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  binary_section_space_schema_member& result =
    reinterpret_cast<binary_section_space_schema_member&>(*_item);

  // Postconditions:

  // Exit

  return result;
}
 

///
bool
fiber_bundle::binary_section_dof_iterator::
item_is_ancestor_of(const schema_poset_member& xmbr) const
{
  bool result;

  // Preconditions:

  // Body:

  // Always true in this class;
  // intended to be redefined in descendants.

  result = dynamic_cast<const binary_section_space_schema_member*>(&xmbr) != 0;

  // Postconditions:

  // Exit

  return result;
}


// PROTECTED MEMBER FUNCTIONS


///
void
fiber_bundle::binary_section_dof_iterator::
reset_item()
{
  // Preconditions:

  // Body:

  if(_item == 0)
  {
    // Create the item handle.

    _item = new binary_section_space_schema_member;
  }

  assertion(is_initialized());

  // Attach the handle.

  update_item();

  // Postconditions:

  ensure(is_initialized());
  ensure(!is_done() == item().is_attached());

  // Exit

  return;
}

///
void
fiber_bundle::binary_section_dof_iterator::
update_item()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  if(_discretization_itr->is_done())
  {
    item().detach_from_state();
  }
  else
  {
    /// @issue resets host, which is unnecessary except when called from
    /// reset_item. Would be more efficient to just reset indices; avoids
    /// call to _item.init_handle_data_members

    item().attach_to_state(anchor().host(), _discretization_itr->index(), _itr.index());
  }

  // Postconditions:

  ensure(!is_done() == item().is_attached());

  // Exit

  return;
}

///
void
fiber_bundle::binary_section_dof_iterator::
initialize(const binary_section_space_schema_member& xanchor,
           bool xis_table_dof,
           int xversion)
{

  // Preconditions:

  require(item_is_ancestor_of(xanchor));
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->is_schematized(false));
  require(xanchor.has_version(xversion));


  // Body:

  // Initialize the discretization iterator.

  _is_table_dof = xis_table_dof;
  if(_is_table_dof)
  {
    // Iterating over table dofs.
    // Table dofs are {base.bottom()} x {fiber schema table dofs}.
    // Bottom is in every version, so it doesn't matter what version.

    _discretization_itr = new postorder_iterator();
  }
  else
  {
    _discretization_itr = new discretization_iterator();
  }

  // Set the anchor

  put_anchor(&xanchor, xversion);

  // Reset the iterator.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));
  ensure(anchor().version() == xanchor.unaliased_version(xversion));
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(item().is_attached() == !is_done());

  return;
}


