

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



// Implementation for class read_write_monitor_handle

#include "read_write_monitor_handle.h"
#include "assert_contract.h"
#include "poset_state.h"
#include "read_write_monitor.h"

#undef DEBUG

#ifdef DEBUG
#include "poset_state_handle.h"
#endif

///
bool
sheaf::read_write_monitor_handle::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const read_write_monitor_handle*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::read_write_monitor_handle*
sheaf::read_write_monitor_handle::
clone() const
{
  read_write_monitor_handle* result = 0;

  // Preconditions:

  // Body:

  // Does nothing, since this class is abstract;
  // just redefines the postcondition.

  // Should never be called.

  not_implemented();

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}

///
sheaf::read_write_monitor_handle::
~read_write_monitor_handle()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}

// ===========================================================
// GLOBAL ACCESS CONTROL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::read_write_monitor_handle::
access_control_disabled()
{
  return read_write_monitor::access_control_disabled();
}

// void
// sheaf::read_write_monitor_handle::
// disable_access_control()
// {
//   // cout << endl << "Entering read_write_monitor_handle::disable_access_control." << endl;

//   // Preconditions:

//   // Body:

//   read_write_monitor::disable_access_control();

//   // Postconditions:

//   ensure(access_control_disabled());

//   // Exit:

//   // cout << "Leaving read_write_monitor_handle::disable_access_control." << endl;
//   return;
// }

void
sheaf::read_write_monitor_handle::
enable_access_control()
{
  // cout << endl << "Entering read_write_monitor_handle::enable_access_control." << endl;

  // Preconditions:

  // Body:

  read_write_monitor::enable_access_control();

  // Postconditions:

  ensure(!access_control_disabled());

  // Exit:

  // cout << "Leaving read_write_monitor_handle::enable_access_control." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// HANDLE INTERFACE

///
bool
sheaf::read_write_monitor_handle::
is_attached() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (state_obj() != 0);

  // Postconditions:

  // Exit

  return result;
}


// ACCESS CONTROL INTERFACE

bool
sheaf::read_write_monitor_handle::
state_is_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // None

  // Body:

  // Meaning of is_attached is stricter in descendants, we don't want that
  // so use scope operator to make sure we get the right definition

  result = sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_read_only_accessible();

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure((is_attached() && access_control_disabled()) ? !result : true);

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor_handle::
state_is_not_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // None

  // Body:

  // Meaning of is_attached is stricter in descendants, we don't want that
  // so use scope operator to make sure we get the right definition

  result = sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_not_read_only_accessible();

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure((is_attached() && access_control_disabled()) ? result : true);
  ensure((is_attached() && !access_control_disabled()) ? result == !state_is_read_only_accessible() : true);

  // Exit:

  return result;
}


bool
sheaf::read_write_monitor_handle::
state_is_read_accessible() const
{
  bool result;

  // Preconditions:

  // None

  // Body:

  // Meaning of is_attached is stricter in descendants, we don't want that
  // so use scope operator to make sure we get the right definition

  result = (sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_read_accessible());

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure((is_attached() && access_control_disabled()) ? result : true);
  ensure((is_attached() && !access_control_disabled()) ? 
         result == (state_is_read_only_accessible() || state_is_read_write_accessible()) :
         true);

  // None

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor_handle::
state_is_not_read_accessible() const
{
  bool result;

  // Preconditions:

  // None

  // Body:

  // Meaning of is_attached is stricter in descendants, we don't want that
  // so use scope operator to make sure we get the right definition

  result = (sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_not_read_accessible());


  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure((is_attached() && access_control_disabled()) ? result : true);
  ensure((is_attached() && !access_control_disabled()) ? result == !state_is_read_accessible() : true);

  // None

  // Exit:

  return result;
}


///
bool
sheaf::read_write_monitor_handle::
state_is_auto_read_accessible(bool xauto_access) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (xauto_access ? is_attached() : state_is_read_accessible());

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure(result == (xauto_access ? is_attached() : state_is_read_accessible()));
  ensure((is_attached() && access_control_disabled()) ? result : true);

  // Exit:

  return result;
}


bool
sheaf::read_write_monitor_handle::
state_is_read_write_accessible() const
{
  bool result;

  // Preconditions:

  // None

  // Body:

  // Meaning of is_attached is stricter in descendants, we don't want that
  // so use scope operator to make sure we get the right definition

  result = (sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_read_write_accessible());

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure((is_attached() && access_control_disabled()) ? result : true);

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor_handle::
state_is_not_read_write_accessible() const
{
  bool result;

  // Preconditions:

  // None

  // Body:


  result = (sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_not_read_write_accessible());

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure((is_attached() && access_control_disabled()) ? result : true);
  ensure((is_attached() && !access_control_disabled()) ? (result == !state_is_read_write_accessible()) : true);

  // Exit:

  return result;
}

///
bool
sheaf::read_write_monitor_handle::
state_is_auto_read_write_accessible(bool xauto_access) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (xauto_access ? is_attached() : state_is_read_write_accessible());

  // Postconditions:

  ensure(!is_attached() ? !result : true);
  ensure(result == (xauto_access ? is_attached() : state_is_read_write_accessible()));
  ensure((is_attached() && access_control_disabled()) ? result : true);

  // Exit:

  return result;
}



///
int
sheaf::read_write_monitor_handle::
access_request_depth() const
{
  int result;

  // Preconditions:

  require(is_attached());

  // None

  // Body:

  result =  state_obj()->access_request_depth();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}


///
void
sheaf::read_write_monitor_handle::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  int old_access_request_depth = state_obj()->access_request_depth();

  state_obj()->get_read_access();

#ifdef DEBUG

  poset_state_handle* lpsh = dynamic_cast<poset_state_handle*>(this);
  if(lpsh != 0)
  {
    int lindex = lpsh->index();
    cout << "read locking poset " << lindex << " level " << state_obj()->access_request_depth() << endl;
  }

  abstract_poset_member* lapm = dynamic_cast<abstract_poset_member*>(this);
  if(lapm != 0)
  {
    int lindex = lapm->host()->index();
    cout << "read locking poset by mbr " << lindex << " level " << state_obj()->access_request_depth() << endl;
  }

#endif

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit:

  return;
}


///
void
sheaf::read_write_monitor_handle::
get_read_write_access(bool xrelease_read_only_access)
{

  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);


  // Body:

  int old_access_request_depth = state_obj()->access_request_depth();

  state_obj()->get_read_write_access(xrelease_read_only_access);

#ifdef DEBUG

  poset_state_handle* lpsh = dynamic_cast<poset_state_handle*>(this);
  if(lpsh != 0)
  {
    int lindex = lpsh->index();
    cout << "write locking poset " << lindex << " level " << state_obj()->access_request_depth() << endl;
  }

  abstract_poset_member* lapm = dynamic_cast<abstract_poset_member*>(this);
  if(lapm != 0)
  {
    int lindex = lapm->host()->index();
    cout << "write locking poset by mbr " << lindex << " level " << state_obj()->access_request_depth() << endl;
  }

#endif

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit:

  return;
}


///
void
sheaf::read_write_monitor_handle::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = state_obj()->access_request_depth();

  state_obj()->release_access(xall);

#ifdef DEBUG

  poset_state_handle* lpsh = dynamic_cast<poset_state_handle*>(this);
  if(lpsh != 0)
  {
    int lindex = lpsh->index();
    cout << "releasing poset " << lindex << " level " << state_obj()->access_request_depth() << endl;
  }

  abstract_poset_member* lapm = dynamic_cast<abstract_poset_member*>(this);
  if(lapm != 0)
  {
    int lindex = lapm->host()->index();
    cout << "releasing poset by mbr " << lindex << " level " << state_obj()->access_request_depth() << endl;
  }

#endif

  // Postconditions:

  ensure(!xall ? access_request_depth() == old_access_request_depth - 1 :
         access_request_depth() == 0);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);

  // Exit:

  return;
}

// MODE LOCK CONTROL INTERFACE

///
bool
sheaf::read_write_monitor_handle::
state_is_mode_locked() const
{
  bool result;

  // Preconditions:

  // None

  // Body:

  // Meaning of is_attached is stricter in descendants, we don't want that
  // so use scope operator to make sure we get the right definition

  result = sheaf::read_write_monitor_handle::is_attached() && state_obj()->is_mode_locked();

  // Postconditions:

  // None

  // Exit:

  return result;
}


///
int
sheaf::read_write_monitor_handle::
mode_lock_ct() const
{
  int result;

  // Preconditions:

  require(is_attached());

  // None

  // Body:

  result =  state_obj()->mode_lock_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}




///
void
sheaf::read_write_monitor_handle::
get_mode_lock() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  state_obj()->get_mode_lock();

  // Postconditions:

  ensure(state_is_mode_locked());

  // Exit:

  return;
}


///
void
sheaf::read_write_monitor_handle::
release_mode_lock()
{
  // Preconditions:

  require(state_is_mode_locked());

  // Body:

  state_obj()->release_mode_lock();

  // Postconditions:


  // Exit:

  return;
}


///
bool
sheaf::read_write_monitor_handle::
state_is_modified() const
{
  bool result;

  // Preconditions:

  require(is_attached());

  // Body:

  result = state_obj()->is_modified();

  // Postconditions:

  // Exit

  return result;
}


///
void
sheaf::read_write_monitor_handle::
clear_state_is_modified()
{

  // Preconditions:

  require(is_attached());

  // Body:

  state_obj()->clear_is_modified();

  // Postconditions:

  ensure(!state_is_modified());

  // Exit

  return;
}
