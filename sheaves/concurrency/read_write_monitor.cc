
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

// Implementation for class READ_WRITE_MONITOR

#include "read_write_monitor.h"
#include "assert_contract.h"
#include "std_cstdlib.h"
#include "std_iostream.h"

// ===========================================================
// READ_WRITE_MONITOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


sheaf::read_write_monitor::
read_write_monitor()
{

  // Preconditions:

  // None.

  // Body:

  // Prevent recursive calls to invariant and disable access guards.

  disable_invariant_check();
  disable_access_guards();

#ifdef _PTHREADS

  int rtncode = pthread_mutex_init(&read_write_monitor_mutex,0);
  if (rtncode == 0)
  {
    rtncode = pthread_cond_init(&lock_free,0);
  }

  // postconditions:

  ensure(rtncode == 0);

  rtncode = pthread_mutex_lock(&read_write_monitor_mutex);
  if (rtncode == 0)
  {
#endif

    // Set initial state to no access

    _ro_ct = 0;
    _mode_lock_ct = 0;
    _rw_ct = 0;

    initialize_thread_state();
    access_mode() = 0;

    // Postconditions:

    ensure(invariant());

#ifdef _PTHREADS

    rtncode = pthread_mutex_unlock(&read_write_monitor_mutex);
  }

  ensure(rtncode == 0);

#endif

  // Re-enable access guards and invariant.

  enable_access_guards();
  enable_invariant_check();
}


sheaf::read_write_monitor::
~read_write_monitor()
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // None.

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// GLOBAL ACCESS CONTROL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::read_write_monitor::
access_control_disabled()
{
  return private_access_control_disabled();
}

// void
// sheaf::read_write_monitor::
// disable_access_control()
// {
//   // cout << endl << "Entering read_write_monitor::disable_access_control." << endl;

//   // Preconditions:

//   // Body:

//   private_access_control_disabled() = true;

//   // Postconditions:

//   ensure(access_control_disabled());

//   // Exit:

//   // cout << "Leaving read_write_monitor::disable_access_control." << endl;
//   return;
// }

void
sheaf::read_write_monitor::
enable_access_control()
{
  // cout << endl << "Entering read_write_monitor::enable_access_control." << endl;

  // Preconditions:

  // Body:

  private_access_control_disabled() = false;

  // Postconditions:

  ensure(!access_control_disabled());

  // Exit:

  // cout << "Leaving read_write_monitor::enable_access_control." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool&
sheaf::read_write_monitor::
private_access_control_disabled()
{
  // cout << endl << "Entering read_write_monitor::private_access_control_disabled." << endl;

  // Preconditions:


  // Body:

  static bool result = true;

  // Postconditions:


  // Exit:

  // cout << "Leaving read_write_monitor::private_access_control_disabled." << endl;
  return result;
}
 

// ===========================================================
// PER-THREAD ACCESS CONTROL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::read_write_monitor::
is_read_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result = is_read_only_accessible() || is_read_write_accessible();

  // Postconditions:

  ensure(result == (is_read_only_accessible() || is_read_write_accessible()));

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor::
is_not_read_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result = access_control_disabled() || !is_read_accessible();

  // Postconditions:

  ensure(result == (access_control_disabled() || !is_read_accessible()));

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor::
is_read_write_accessible() const
{
  bool result;

  // Body:


  // Is accessible if access guards disabled.

  result = access_control_disabled() || access_guards_disabled() || uncontrolled_is_read_write_accessible();

  // Postcondition:

  ensure((access_control_disabled() || access_guards_disabled()) ? result : true);

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor::
is_not_read_write_accessible() const
{

  // Body:

  bool result = access_control_disabled() ? true: !is_read_write_accessible();


  // Postcondition:

  ensure(result == (access_control_disabled() ? true: !is_read_write_accessible()));

  // Exit:

  return result;
}

bool
sheaf::read_write_monitor::
is_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // Body:


  // Is not accessible if access guards disabled.

  result = !access_control_disabled() && !access_guards_disabled() && uncontrolled_is_read_only_accessible();

  // Postcondition:

  ensure((access_control_disabled() || access_guards_disabled()) ? !result : true);

  // Exit:

  return result;
}


bool
sheaf::read_write_monitor::
is_not_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  // This function is not really necessary,
  // it is provided only for symmetry with the
  // other is_not functions, makes it easier
  // to read and unserstand code in some places.

  result = !is_read_only_accessible();

  // Postcondition:

  ensure(result == !is_read_only_accessible());

  // Exit:

  // Note that there's no race condition in returning the result
  // since each thread has its own copy of result on its own stack.

  return result;
}

int
sheaf::read_write_monitor::
access_request_depth() const
{
  int result;

  // Preconditions:

  // Body:

#ifdef _PTHREADS

  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  result = abs(access_mode());

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return result;
}

void
sheaf::read_write_monitor::
get_read_access() const
{

  // Preconditions:

  // Body:

  if(uncontrolled_is_read_write_accessible())
  {
    // Read_write access implies read access, so if the thread
    // already has read_write access, request it again.
    // This will just increase the request nesting depth.

    request_read_write_access();
  }
  else
  {
    // The thread either has no access or read_only access
    // Either way, request read_only access. If the thread already
    // has access, this will just increase the request nesting depth

    request_read_only_access();
  }


  // Postconditions:

  ensure(is_read_accessible());

  // Exit

  return;
}


///
void
sheaf::read_write_monitor::
get_read_write_access(bool xrelease_read_only_access)
{

  // Preconditions:

  require(xrelease_read_only_access || !is_read_only_accessible());

  // Body:

  int old_access_request_depth = access_request_depth();

  if(xrelease_read_only_access && uncontrolled_is_read_only_accessible())
  {
    // The client requested that read only access be released and
    // this is read only accessible. Release the read-only access
    // and request the same level of read-write access.

    // Set the switch level so we can restore read-only
    // access when this write access is released.

    switch_depth() = old_access_request_depth;

    // Release all the read-only access.

    while(uncontrolled_is_read_only_accessible())
    {
      release_read_only_access();
    }

    // Request the same level of read-write-access.

    while(access_request_depth() < old_access_request_depth)
    {
      request_read_write_access();
    }

    assertion(uncontrolled_is_read_write_accessible() &&
           (access_request_depth() == old_access_request_depth));
  }

  // Request read/write access.

  request_read_write_access();

  // Postconditions:

  ensure(is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit

  return;
}

void
sheaf::read_write_monitor::
release_access(bool xall) const
{

  // Preconditions:

  require(is_read_accessible());

  // Body.

  if(uncontrolled_is_read_write_accessible())
  {
    // Release at least one level of read-write access,
    // and if xall, release all levels.

    do
    {
      release_read_write_access();
    }
    while(xall && uncontrolled_is_read_write_accessible());

    if(uncontrolled_is_read_write_accessible() && (access_request_depth() == switch_depth()))
    {
      // We didn't release all levels and we're at the switch level.
      // Convert remaining read-write access levels
      // back to read-only levels.

      while(uncontrolled_is_read_write_accessible())
      {
        release_read_write_access();
      }

      while(access_request_depth() < switch_depth())
      {
        request_read_only_access();
      }

      assertion(uncontrolled_is_read_only_accessible() && (access_request_depth() == switch_depth()));

      switch_depth() = 0;
    }
  }
  else if(uncontrolled_is_read_only_accessible())
  {
    // Release at least one level of read-only access,
    // and if xall, release all levels.

    do
    {
      release_read_only_access();
    }
    while(xall && uncontrolled_is_read_only_accessible());
  }

  // Postconditions:

  ensure(xall ? is_not_read_accessible() : true);

  // Exit:

  return;
}



// PROTECTED MEMBER FUNCTIONS




// ===========================================================
// PRIVATE MEMEBR FUNCTIONS FACET
// ===========================================================

bool
sheaf::read_write_monitor::
access_guards_disabled() const
{
  // Exit:

  return _access_guards_disabled;
}

void
sheaf::read_write_monitor::
disable_access_guards()
{
  _access_guards_disabled = true;

  return;
}

void
sheaf::read_write_monitor::
enable_access_guards()
{
  _access_guards_disabled = false;

  return;
}

// PRIVATE MEMBER FUNCTIONS 


// bool
// sheaf::read_write_monitor::
// uncontrolled_is_read_write_accessible() const
// {
//   bool result;

//   // Body:

// #ifdef _PTHREADS

//   pthread_mutex_lock(&read_write_monitor_mutex);
// #endif

//   // Is accessible is access guards disabled.

//   result = access_guards_disabled() || (access_mode() > 0);

// #ifdef _PTHREADS

//   pthread_mutex_unlock(&read_write_monitor_mutex);
// #endif

//   // Postcondition:

//   ensure(access_guards_disabled() ? result : true);

//   // Exit:

//   // Note that there's no race condition in returning the result
//   // since each thread has its own copy of result on its own stack.

//   return result;
// }

bool
sheaf::read_write_monitor::
uncontrolled_is_read_write_accessible() const
{
  bool result;

  // Body:

#ifdef _PTHREADS

  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  result = (access_mode() > 0);

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Postcondition:

  // Exit:

  // Note that there's no race condition in returning the result
  // since each thread has its own copy of result on its own stack.

  return result;
}


// bool
// sheaf::read_write_monitor::
// uncontrolled_is_read_only_accessible() const
// {
//   bool result;

//   // Preconditions:

//   // Body:

// #ifdef _PTHREADS

//   pthread_mutex_lock(&read_write_monitor_mutex);
// #endif

//   result = !access_guards_disabled() && (access_mode() < 0);

// #ifdef _PTHREADS

//   pthread_mutex_unlock(&read_write_monitor_mutex);
// #endif

//   // Postcondition:

//   ensure(access_guards_disabled() ? !result : true);

//   // Exit:

//   // Note that there's no race condition in returning the result
//   // since each thread has its own copy of result on its own stack.

//   return result;
// }


bool
sheaf::read_write_monitor::
uncontrolled_is_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

#ifdef _PTHREADS

  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  result = (access_mode() < 0);

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Postcondition:

  // Exit:

  // Note that there's no race condition in returning the result
  // since each thread has its own copy of result on its own stack.

  return result;
}


void
sheaf::read_write_monitor::
initialize_thread_state()
{
#ifdef _PTHREADS

  // Preconditions:

  require(!contains_thread_state());

  // Body:

  // Create a new state initialized to no access and not modified.

  thread_state_t new_thread_state = {0, false};

  // Insert the new state in the map for this thread..

  unordered_map<pthread_t, thread_state_t>::value_type lval(pthread_self(), new_thread_state);
  _thread_state.insert(lval);

  // Postconditions:

  ensure(contains_thread_state());

#else

  // Preconditions:

  // Always contains thread state.

  // Body:

  // There's only one thread, just initialize data member
  // to no access, no switch, and not modified.

  _thread_state._access_mode = 0;
  _thread_state._switch_depth = 0;
  _thread_state._is_modified = false;

  // Postconditions:

  ensure(contains_thread_state());

#endif

}

bool
sheaf::read_write_monitor::
contains_thread_state() const
{
  bool result;

  // Preconditions:


  // Body:

#ifdef _PTHREADS

  // Thread state exists if it's in the thread map.

  result = (_thread_state.find(pthread_self()) != _thread_state.end());

#else

  // There's only one thread and state is a data member.

  result = true;

#endif

  // Postconditions:


  // Exit:

  return result;
}


sheaf::read_write_monitor::thread_state_t&
sheaf::read_write_monitor::
thread_state() const
{
  // Preconditions:

  require(contains_thread_state());

  // Body:

#ifdef _PTHREADS

  return *_thread_state.find(pthread_self());

#else

  return _thread_state;

#endif

}

int&
sheaf::read_write_monitor::
access_mode() const
{
  // Preconditions:

  require(contains_thread_state());

  // Body:

  // Postconditions:


  // Exit:

  return thread_state()._access_mode;
}


size_t&
sheaf::read_write_monitor::
switch_depth() const
{
  // Preconditions:

  require(contains_thread_state());

  // Body:

  // Postconditions:


  // Exit:

  return thread_state()._switch_depth;
}

void
sheaf::read_write_monitor::
request_read_only_access() const
{

#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  // Preconditions:

  require( access_mode() <= 0 );

  // Body:

#ifdef _PTHREADS

  // wait until any writer has released access

  while( _rw_ct > 0 )
  {
    pthread_cond_wait(&lock_free, &read_write_monitor_mutex);
  }

#endif

  // Grab read-only access.

  int& state = access_mode();
  if(state == 0)
  {
    // Thread is just becoming a reader;
    // increment the thread reader count.

    _ro_ct++;

    // Access request nesting depth is -1.
    // ( < 0 for read-only, 1 for first request)

    state = -1;
  }
  else
  {
    // Thread already has read-only access,
    // just increase the access request nesting depth.

    state--;
  }


  // Postconditions:

  ensure(invariant());
  ensure(_rw_ct == 0);
  ensure(_ro_ct > 0);

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return;
}

void
sheaf::read_write_monitor::
request_read_write_access() const
{

#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  // Preconditions:

  require(access_mode() >= 0);

  // Body:

  int& state = access_mode();
  if( state > 0 )
  {
    // This thread already has read_write access.
    // Assuming a "proper" client, this must be a nested call;
    // Just increase the access request nesting depth

    state++;
  }
  else
  {
    // This thread does not have read_write access;

#ifdef _PTHREADS

    // wait until the writer and all readers release access.

    while( _ro_ct > 0 || _rw_ct > 0)
    {
      pthread_cond_wait(&lock_free, &read_write_monitor_mutex);
    }

#endif

    // grab read_write access

    _rw_ct = 1;
    state = 1;

  }


  // postconditions:

  ensure(invariant());
  ensure(_ro_ct == 0);
  ensure(_rw_ct == 1);
  ensure(access_mode() > 0);

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  return;
}


void
sheaf::read_write_monitor::
release_read_only_access() const
{


#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif


  // Preconditions:

  require( access_mode() < 0 );

  // Body:

  // Get the thread state

  int& state = access_mode();

  // Decrease the request nesting depth

  state++;

  // Save the number of readers for the postcondition

  define_old_variable(int old_ro_ct = _ro_ct);

  // If this thread is no longer a reader,
  // Decrement the number of readers.

  if(state == 0)
    _ro_ct--;


#ifdef _PTHREADS

  // If no readers left, unlock for writers

  // Use signal instead of broadcast since only writers
  // should be queued up waiting for access and only 1
  // writer at a time can get access.

  if (_ro_ct == 0)
    pthread_cond_signal(&lock_free);

#endif


  // Postconditions:

  ensure(invariant());
  ensure((_ro_ct == old_ro_ct) || (_ro_ct == old_ro_ct - 1));

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  return;
}

///
void
sheaf::read_write_monitor::
release_read_write_access() const
{

#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  // Preconditions:

  require( access_mode() > 0 );

  // Body:

  // Get the thread access state

  int& state = access_mode();

  // Decrease the nesting depth of write requests

  state--;

  // Save counter for use in postcondition

  define_old_variable(int old_rw_ct = _rw_ct);

  if(state == 0)
  {
    // This thread is no longer a writer,
    // decrement the number of writers.

    _rw_ct = 0;

#ifdef _PTHREADS

    // Set the modified flag on all threads, including this thread.

    unordered_map<pthread_t, thread_state_t>::iterator itr = _thread_state.begin();

    while(itr != _thread_state.end())
    {
      itr->second._is_modified = true;
      itr++;
    }

    // Unlock for other readers or writers.
    // Use broadcast since there might be a lot of readers queued up for
    // access.  All of them should be permitted access simultaneously.

    pthread_cond_broadcast(&lock_free);

#else

    // Set the modified flag on this (the only) thread

    _thread_state._is_modified = true;

#endif

  }

  // Postconditions:

  ensure(invariant());
  ensure((_rw_ct == old_rw_ct) || (_rw_ct == old_rw_ct - 1));
  ensure(unexecutable("for all client threads: is_modified()"));

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  return;
}


// ===========================================================
// NOTIFICATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::read_write_monitor::
is_modified() const
{
  bool result;

  // Preconditions:

  // Body:

#ifdef _PTHREADS

  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  result = thread_state()._is_modified;

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return result;
}


void
sheaf::read_write_monitor::
clear_is_modified()
{
  // Preconditions:

  // Body:

#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  thread_state()._is_modified = false;

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return;
}

// ===========================================================
// MODEL LOCK CCONTROL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::read_write_monitor::
is_mode_locked() const
{
  bool result;

  // Preconditions:

  // Body:

#ifdef _PTHREADS

  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  result = ( access_guards_disabled() || (_mode_lock_ct > 0));

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return result;
}


int
sheaf::read_write_monitor::
mode_lock_ct() const
{
  int result;

  // Preconditions:

  // Body:

#ifdef _PTHREADS

  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  result = _mode_lock_ct;

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return result;
}

///
void
sheaf::read_write_monitor::
get_mode_lock()
{

#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif

  // Preconditions:

  // A client can lock the write sub-mode as long as no other
  // client is actually using the mode. This can be ensured
  // by requiring that no other client has write access, which
  // in turn is ensured by this client having either read-only
  // or read-write access.

  require( access_mode() != 0 );
  // client has either read-only or read-write access

  // Body:

#ifdef _PTHREADS

  // wait until any writer has released access

  while( _rw_ct > 0 )
  {
    pthread_cond_wait(&lock_free, &read_write_monitor_mutex);
  }

#endif

  // Save the number of object readers for the postcondition

  define_old_variable(int old_mode_lock_ct = _mode_lock_ct);

  // Increment mode lock ct.

  _mode_lock_ct++;

  // Postconditions:

  ensure(invariant());
  ensure(_mode_lock_ct == old_mode_lock_ct + 1);
  ensure(_mode_lock_ct > 0);

#ifdef _PTHREADS

  ensure(_rw_ct == 0);
  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  // Exit:

  return;
}


void
sheaf::read_write_monitor::
release_mode_lock()
{


#ifdef _PTHREADS
  pthread_mutex_lock(&read_write_monitor_mutex);
#endif


  // Preconditions:

  require( _mode_lock_ct >  0 );
  // is_mode_locked

  // Body:

  // Save the number of object readers for the postcondition

  define_old_variable(int old_mode_lock_ct = _mode_lock_ct);

  // Decrement the number of object readers.

  _mode_lock_ct--;


#ifdef _PTHREADS

  // If no readers left, unlock for writers

  // Use signal instead of broadcast since only writers
  // should be queued up waiting for access and only 1
  // writer at a time can get access.

  if (_ro_ct == 0)
    pthread_cond_signal(&lock_free);

#endif


  // Postconditions:

  ensure(invariant());
  ensure(_mode_lock_ct == old_mode_lock_ct - 1);

#ifdef _PTHREADS

  pthread_mutex_unlock(&read_write_monitor_mutex);
#endif

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::read_write_monitor::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const read_write_monitor*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


sheaf::read_write_monitor*
sheaf::read_write_monitor::
clone() const
{
  read_write_monitor* result;

  // Preconditions:

  // Body:

  result = new read_write_monitor;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::read_write_monitor::
invariant() const
{
  bool result = true;

  // NOTE:
  // In the threaded case,
  // invariant() should only be called from within a locked read_write_monitor_mutex.
  // The reason for this is that one can't compute a true value of the invariant if
  // other threads may be manipulating it while the computation is in progress.  Yet
  // we can't and don't want to lock the invariant itself with read_write_monitor_mutex.
  // We can't do so because invariant is properly called from within other
  // read_write_monitor procedures (to check their validity).  These other procedures
  // have already locked read_write_monitor_mutex, and pthreads doesn't allow us to
  // lock it again.  We don't want to do so because we want the check of the invariant
  // to follow immediately after a change of state of the read_write_monitor.  If an
  // unlock of read_write_monitor_mutex occurs after an operation is done on the state
  // of read_write_monitor, but before invariant is actually called, then it isn't
  // clear what operations the invariant is checking.
  //

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls

    disable_invariant_check();

    result = result && _ro_ct >= 0;
    result = result && _mode_lock_ct >= 0;
    result = result && ( (_rw_ct == 0) || (_rw_ct == 1) );
    result = result && !( (_rw_ct == 1) && (_ro_ct > 0) );

    // Re-enable invariant check

    enable_invariant_check();
  }


  return result;

}
