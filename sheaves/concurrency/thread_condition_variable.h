
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

// Interface for class THREAD_CONDITION_VARIABLE

#ifndef THREAD_CONDITION_VARIABLE_H
#define THREAD_CONDITION_VARIABLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifdef _PTHREADS
#include "pthread.h"

namespace sheaf
{
  
///
class SHEAF_DLL_SPEC thread_condition_variable
{

public:

  // queries:

  ///
  /// Class invariant.
  ///
  bool  invariant() const;

  // actions:

  ///
  /// Releases all threads that are waiting.
  ///
  void  broadcast();

  ///
  /// Obtain a mutex_lock.  Only 1 thread at a time can obtain a mutex_lock
  /// on a given instance of this class.  Any other thread attempting to gain
  /// a lock will wait until the thread which is holding the lock calls
  /// unlock_mutex().
  ///
  void  lock_mutex();

  ///
  /// Releases 1 thread (which one is not predicable) among those that are
  /// waiting
  ///
  void  signal();

  ///
  /// Waits a specified time for a signal or broadcast from another thread.
  ///
  void  timedwait(timespec *xtime);

  ///
  /// Release a mutex_lock.
  ///
  void  unlock_mutex();

  ///
  /// Places the calling thread into a wait state until some other thread
  /// executes broadcast() or signal(). <br>
  /// <br>
  /// The idiom for using wait() is: <br>
  /// <font face="Cursor"><br><dl>
  /// <dt> lock_mutex();
  /// <dt> while(some condition worth waiting for)
  /// <dt><dd> wait();
  /// <dt><dd> unlock_mutex();
  /// </dl></font>
  /// <br><br>
  /// Here's how it works:<br>
  /// <br><dl>
  /// <dt> <font face="Cursor">lock_mutex()</font> /// guarantees that only a
  ///      single thread can check the condition that follows
  /// <dt> <font face="Cursor">while(condition)</font>
  /// <dt><dd> <font face="Cursor">wait()</font> /// decides that that single
  ///          thread has to wait for "condition" to change.  It unlocks the
  ///          mutex, allowing other threads to progress, and waits for a
  ///          signal or broadcast.  When it is awakened by a signal or
  ///          broadcast, it reacquires the lock, and checks "condition",
  ///          repeating this process until "condition" is false.
  /// <dt><dd> <font face="Cursor">unlock_mutex()</font> /// releases the mutex
  ///          lock obtained on the last wakeup from wait().
  /// </dl><br>
  ///
  void  wait();

  // constructors:

  ///
  /// Default Constructor
  ///
  thread_condition_variable();

  ///
  /// Destructor
  ///
  ~thread_condition_variable();

private:

  // data:

  pthread_mutex_t     pthread_mutex;
  pthread_cond_t      pthread_cond;

};
 
} //namespace sheaf

#endif // ifdef _PTHREADS

#endif // ifndef THREAD_CONDITION_VARIABLE_H
