
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

// Interface for class THREAD_MUTEX

#ifndef THREAD_MUTEX_H
#define THREAD_MUTEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifdef _PTHREADS
#include "pthread.h"

namespace sheaf
{
  
///
/// Wrapper for p-threads mutex data type.
///
class SHEAF_DLL_SPEC thread_mutex
{

private:

  // data:

  pthread_mutex_t       pthread_mutex;
  pthread_mutexattr_t   pthread_mutexattr;

public:

  // queries:

  ///
  /// Return pointer to pthread_mutex_t
  ///
  pthread_mutex_t *get_pthread_mutex();

  ///
  /// Class Invariant
  ///
  bool             invariant() const;

  // actions:

  ///
  /// Lock the thread
  ///
  void  lock()
    ;

  ///
  /// did you actually get a lock?
  ///
  bool  trylock();

  ///
  /// Unlock the thread
  ///
  void  unlock();

  // constructors:

  ///
  /// Default Constructor
  ///
  thread_mutex();

  ///
  /// Destructor
  ///
  ~thread_mutex();
};
 
} // namespace sheaf

#endif // _PTHREADS

#endif // ifndef THREAD_MUTEX_H
