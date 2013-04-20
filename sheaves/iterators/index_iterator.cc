

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 

// Implementation for class index_iterator

#include "index_iterator.h"
#include "assert_contract.h"

#include "std_bitset.h"
#include "std_limits.h"
#include "zn_to_bool.h"

///
sheaf::index_iterator::
index_iterator()
{
  // Preconditions:

  // Body:


  // Initialize data members;
  // default initialization on _index is ok.

  _host = 0;
  _delete_host = false;
  _word_index = 0;
  _word_ub = 0;
  _word = 0;
  _bit_index = 0;
  _bit_ub = 0;
  _item = 0;
  _next_item = 0;
  _item_ub = 0;

  // Postcondition

  ensure(is_done());

  return;
}

///
sheaf::index_iterator::
index_iterator(const zn_to_bool* xhost, const index_space_handle& xid_space, bool xdelete_host)
{
  // Preconditions:

  require(xhost != 0);

  // Body:

  /// @hack host should be a reference counted pointer; see destructor.

  reset(xhost, xid_space, xdelete_host);

  // Postcondition

  return;
}

///
sheaf::index_iterator::
~index_iterator()
{
  // Preconditions:


  // Body:

  /// @hack host should be a reference counted pointer.
  /// @todo convert _host to reference counted pointer
  /// and remove _delete_host member.
  /// (Requires zn_to_bool inherit rc_any.)

  if(_delete_host)
  {
    delete _host;
  }

  // Postconditions:


  // Exit:

  return;
}

 

///
const sheaf::zn_to_bool*
sheaf::index_iterator::
host() const
{
  return _host;
}

///
int
sheaf::index_iterator::
item()
{
  int result;

  // Preconditions:

  require(!is_done());

  // Body:

  result = _item;

  // Postconditions:

  ensure((*host())[result]);

  // Exit

  return result;
}

 

const sheaf::scoped_index&
sheaf::index_iterator::
index() const
{
  // Preconditions:

  require(!is_done());

  // Body:

   
  define_old_variable(const scoped_index& result = _index);

  _index = _item;

  // Postconditions:

  ensure((*host())[result.pod()]);

  // Exit

  return _index;
}


 

///
bool
sheaf::index_iterator::
is_done() const
{
  bool result;

  // Preconditions:

  // Body:

  // You're done when there are no more items to be examined.

  result = (_item >= _item_ub);

  // Postconditions:

  // None - is_done is a primitive query.
  // In particular, note that it is next() that ensures
  // the semantics of item(), not is_done()

  // Exit

  return result;
}

 

///
bool
sheaf::index_iterator::
is_last() const
{
  bool result;

  // Preconditions:

  // Body:

  result = ((_next_item >= _item_ub) && (_item < _item_ub));

  // Postconditions:

  ensure(unexecutable(result implies is_done() after next()));

  // Exit

  return result;
}

///
inline
void
sheaf::index_iterator::
find_next_item()
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool lfound = false;
  while(!lfound)
  {
    _next_item++;
    if(_next_item >= _item_ub)
      break;

    assertion(_next_item < _item_ub);

    _bit_index++;

    if(_bit_index >= _bit_ub)
    {
      // Move to the 0th bit of the next word

      _bit_index = 0;
      _word_index++;

      assertion(_word_index < _word_ub); // implied by _next_item < _item_ub
    }

    lfound =  (*host())[_next_item];

  }

  assertion(lfound || (_next_item == _item_ub));

  // Postcondition

  ensure((_next_item < _item_ub) ? (*host())[_next_item] : true);

  return;
}

///
void
sheaf::index_iterator::
next()
{
  // Preconditions:

  require(!is_done());

  // Body:

  define_old_variable(int old_item = _item);

  _item = _next_item;
  if(_next_item < _item_ub)
  {
    find_next_item();
  }

  // Postcondition

  ensure(!is_done() ? item() > old_item : true);
  ensure(!is_done() ? (*host())[item()] : true);

  return;
}

///
void
sheaf::index_iterator::
reset()
{
  // Preconditions:

  // Body:

  require(host() != 0);

  // Initialize host independent data members

  _word_index = -1;
  _bit_index = _bit_ub - 1; // == -1 mod _bit_ub
  _item = -1;
  _next_item = -1;

  // Find the first subset member

  find_next_item();
  next();

  // Postcondition

  ensure(!is_done() ? (*host())[item()] : true);

  return;
}

///
void
sheaf::index_iterator::
reset(const zn_to_bool* xhost, const index_space_handle& xid_space, bool xdelete_host)
{
  // Preconditions:

  require(xhost != 0);

  // Body:

  /// @hack host should be a reference counted pointer; see destructor.


  // Initialize host dependent data members

  _host = xhost;
  _index.put_scope(xid_space);
  _delete_host = xdelete_host;
  _word_ub = _host->_word_ub;
  //  _bit_ub = _host->_bits_per_word;
  _bit_ub = zn_to_bool::BITS_PER_WORD;
  _item_ub = _host->_ub;

  // Perform same-host reset

  reset();

  // Postcondition

  ensure(!is_done() ? (*host())[_item] : true);

  return;
}

