// $RCSfile: id_block.cc,v $ $Revision: 1.21 $ $Date: 2013/03/13 00:59:08 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class id_block

#include "id_block.h"

#include "any.h"
#include "assert_contract.h"
#include "error_message.h"
#include "hub_index_space_handle.h"
#include "poset_state_handle.h"

// =============================================================================
// ANY FACET
// =============================================================================

///
bool
sheaf::id_block::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const id_block*>(other) != 0;

  // Postconditions:

  return result;
}

///
sheaf::id_block*
sheaf::id_block::
clone() const
{
  id_block* result;

  // Preconditions:

  // Body:

  result = new id_block(this->host(), id_space(), 0);

  // Postconditions:

  ensure(result != 0);
  ensure(unexecutable("is_same_type(result)"));
  ensure(&result->host() == &host());
  ensure(result->id_space() == id_space());
  ensure(result->ub() == 0);

  // Exit:

  return result;
}


///
sheaf::id_block&
sheaf::id_block::
operator=(const id_block& xother)
{

  // Preconditions:


  // Body:

  //block<int>::operator=(xother);
  block<scoped_index>::operator=(xother);

  _host = xother._host;
  _id_space = &xother._id_space->get_id_space();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

 

///
bool
sheaf::id_block::
invariant() const
{
  bool result = true;

  // Must satisfy base class invariant

  invariance(block<scoped_index>::invariant());

  // Invariances for this class:

  invariance(host().is_attached());

  // Exit

  return result;
}



// =============================================================================
// ID_BLOCK FACET
// =============================================================================

///
sheaf::id_block::
id_block(const id_block& xother)
  : block<scoped_index>::block(xother)
{

  // Preconditions:


  // Body:

  _host     = xother._host;
  _id_space = &xother._id_space->get_id_space();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
sheaf::id_block::
~id_block()
{
  // Preconditions:


  // Body:

  if(_id_space != 0)
  {
    _id_space->release_id_space();
  }

  // Postconditions:

  // Exit:

  return;
}

///
sheaf::id_block::
id_block(const poset_state_handle& xhost,
         const index_space_handle& xid_space,
         int xub,
         const scoped_index* xids,
         int xct)
    : block<scoped_index>::block(xub, xct, xids)
{
  // Preconditions:

  require(xhost.is_attached());
  require(xhost.member_id_spaces(true).contains(xid_space.index()));
  require(xub >= 0);
  require((0 <= xct) && (xct <= xub));
  require((xids != 0) == (xct > 0));

  // Body:

  _host     = const_cast<poset_state_handle*>(&xhost);
  _id_space = &xid_space.get_id_space();

  // Postconditions:

  ensure(&host() == &xhost);
  ensure(id_space() == xid_space);
  ensure(ub() >= xub);
  ensure(ct() == xct);
  ensure_for_all(i, 0, xct, item(i) == xids[i]);

  // Exit:

  return;
}

///
sheaf::poset_state_handle&
sheaf::id_block::
host()
{
  return *_host;
}

///
const sheaf::poset_state_handle&
sheaf::id_block::
host() const
{
  return *_host;
}


///
const sheaf::index_space_handle&
sheaf::id_block::
id_space() const
{
  return *_id_space;
}

///
void
sheaf::id_block::
put_id_space(const index_space_handle& xnew_id_space, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || host().state_is_read_accessible());
  require(host().member_id_spaces(xauto_access).contains(xnew_id_space.index()));

  // Body:

  if(xauto_access)
  {
    host().get_read_write_access();
  }

  if(xnew_id_space == (*_id_space))
  {
    // Nothing to do.
  }
  else
  {
    // The id space has changed.  Release the old id space.

    _id_space->release_id_space();

    // Have to convert ids.

    if(xnew_id_space == _host->member_hub_id_space(false))
    {
      // Just translate to top ids.

      for(int i=0; i<_ct; ++i)
      {
        item(i).put(xnew_id_space, _id_space->hub_pod(item(i)));
      }
    }
    else
    {
      // Translate to top id and then to new id space.

      for(int i=0; i<_ct; ++i)
      {
        item(i).put(xnew_id_space, xnew_id_space.pod(_id_space->hub_pod(item(i))));
      }
    }

    _id_space = &xnew_id_space.get_id_space();
  }

  if(xauto_access)
  {
    host().release_access();
  }

  // Postconditions:

  ensure(id_space() == xnew_id_space);

  // Exit:

  return;
}

///
void
sheaf::id_block::
put_member_id_space(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || host().state_is_read_accessible());

  // Body:

  put_id_space(host().member_hub_id_space(xauto_access), xauto_access);

  // Postconditions:

  ensure(id_space() == host().member_hub_id_space(xauto_access));

  // Exit:

  return;
}

///
bool
sheaf::id_block::
is_member_hub_id_space() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_id_space == &_host->member_hub_id_space(true));

  // Postconditions:

  ensure(result == (&id_space() == &host().member_hub_id_space(true)));

  // Exit:

  return result;
}

// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================

///
sheaf::id_block::
id_block()
    : block<scoped_index>::block(0)
{

  // Preconditions:


  // Body:

  // Not implementable because we don't have a host.

  not_implemented();

  // Postconditions:

  ensure(invariant());
  ensure(ct() == 0);

  // Exit:

  return;
}



// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

ostream&
sheaf::operator << (ostream& xos, const id_block& xblk)
{

  // Preconditions:

  require(xblk.host().state_is_read_accessible());


  // Body:

  xos << "host name: " << xblk.host().name()
      << " id space: " << xblk.id_space().name()
      << " ids: " << static_cast<const block<scoped_index>&>(xblk);

  // Postconditions:

  // Exit:

  return xos;

}


