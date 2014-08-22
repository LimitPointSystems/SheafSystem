
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

// Interface for class THREAD

#ifndef COM_LIMITPOINT_SHEAF_THREAD_H
#define COM_LIMITPOINT_SHEAF_THREAD_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifdef _PTHREADS
#include "pthread.h"

#ifndef STD_UNISTD_H
#include "std_unistd.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SINGLY_LINKED_LIST_H
#include "ComLimitPoint/sheaf/singly_linked_list.h"
#endif

namespace sheaf
{

class runnable;
  
///
/// A very simple class that mimics Java's thread class. Uses
/// POSIX threads in implementation.
///
class SHEAF_DLL_SPEC thread
{

private:

  // data:

  bool                     _is_alive;
  pthread_t                 pthread;
  runnable                *_runnable;
  static singly_linked_list<thread *>  *_thread_list; // $$ISSUE. destroying a thread or querying for is_alive requires
  // a linear search through the list.  For small numbers of threads
  // this is probably ok, but for large numbers a hash table would be
  // better.

  // actions:

  static void   cleanup(thread *This);
  static void  *static_run(thread *This);

public:

  // queries:

  ///
  static int       active_count();

  ///
  singly_linked_list<thread *> *thread_list();

  ///
  /// Class Invarient
  ///
  bool             invariant() const;

  ///
  /// still running?
  ///
  static bool      is_alive(thread *other);

  // actions:

  ///
  static thread *current_thread();

  ///
  /// wait for thread to finish
  ///
  void           join();

  ///
  /// meant to be overridden
  ///
  virtual void   run();

  ///
  /// interupt thread for specified number of seconds
  ///
  void           sleep(unsigned int seconds);

  ///
  /// start a new thread and run function (if not NULL) or run
  /// method of descendant class
  ///
  void           start();

  ///
  /// stop a thread
  ///
  void           stop();

  // constructors:

  ///
  /// Default Constructor
  ///
  thread();

  ///
  /// Constructor taking a runnable class as only argument
  ///
  thread(runnable *xrunnable);

  ///
  /// Destructor
  ///
  ~thread();
};

} // namespace sheaf

#endif // _PTHREADS

#endif // ifndef THREAD_H
