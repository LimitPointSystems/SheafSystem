
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

// Implementation for class THREAD_MUTEX

#ifndef THREAD_MUTEX_H
#include "thread_mutex.h"
#endif

#ifdef _PTHREADS

#include "assert_contract.h"
#include "std_errno.h" // for EBUSY

///
sheaf::thread_mutex::
thread_mutex()
{

  // body:

  int rtncode = pthread_mutex_init(&pthread_mutex,&pthread_mutexattr);

  // postconditions:

  ensure(rtncode == 0);
}


///
sheaf::thread_mutex::
~thread_mutex()
{}

bool
sheaf::thread_mutex::
invariant() const
{

  return true; /// $$HACK: placebo.  @todo develop a REAL invariant.
}


///


void
sheaf::thread_mutex::
lock()
{

  // body:

  int rtncode = pthread_mutex_lock(&pthread_mutex);

  // postconditions:

  ensure(rtncode == 0);
}


///
void
sheaf::thread_mutex::
unlock()
{

  // body:

  int rtncode = pthread_mutex_unlock(&pthread_mutex);

  // postconditions:

  ensure(rtncode == 0);

}


///
bool
sheaf::thread_mutex::
trylock()
{

  // body:

  int rtncode = pthread_mutex_trylock(&pthread_mutex);

  bool result;

  if (rtncode == EBUSY)
    result = true;
  else
    result = false;

  return result;
}


///
pthread_mutex_t *
sheaf::thread_mutex::
get_pthread_mutex()
{

  return &pthread_mutex;
}

#endif // _PTHREADS
