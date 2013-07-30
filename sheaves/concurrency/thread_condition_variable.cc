
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

// Implementation for class THREAD_CONDITION_VARIABLE

#ifndef THREAD_CONDITION_VARIABLE_H
#include "thread_condition_variable.h"
#endif

#ifdef _PTHREADS

#include "std_iostream.h"

#include "assert_contract.h"

///
sheaf::thread_condition_variable::
thread_condition_variable()
{

  // body:

#ifdef _PTHREADS
  int rtncode = pthread_cond_init(&pthread_cond,0);
  if (rtncode == 0)
    rtncode = pthread_mutex_init(&pthread_mutex,0);

  // postconditions:

  ensure(rtncode == 0);
#endif

  ensure(invariant());
}

///
sheaf::thread_condition_variable::
~thread_condition_variable()
{

#ifdef _PTHREADS

  // body:

  int rtncode = pthread_cond_destroy(&pthread_cond);
  if (rtncode == 0)
    rtncode = pthread_mutex_destroy(&pthread_mutex);

  // postconditions:

  ensure(rtncode == 0);

#endif
}


///
bool
sheaf::thread_condition_variable::
invariant() const
{

  return true; /// $$HACK: placebo.  @todo develop a REAL invariant
}


///
void
sheaf::thread_condition_variable::
broadcast()
{

#ifdef _PTHREADS

  // body:

  int rtncode = pthread_cond_broadcast(&pthread_cond);

  // postconditions:

  ensure(rtncode == 0);

#endif
}


///
void
sheaf::thread_condition_variable::
signal()
{

#ifdef _PTHREADS

  // body:

  int rtncode = pthread_cond_signal(&pthread_cond);

  // postconditions:

  ensure(rtncode == 0);

#endif
}


///
void
sheaf::thread_condition_variable::
timedwait(timespec* xtime)
{

  // preconditions:

  require(xtime != 0);

#ifdef _PHTHREADS

  // body:

  int rtncode = pthread_cond_timedwait(&pthread_cond, &pthread_mutex, xtime);

  // postcondition:

  ensure(rtncode == 0);

#endif

}


///
void
sheaf::thread_condition_variable::
wait()
{

#ifdef _PTHREADS

  // body:

  int rtncode = pthread_cond_wait(&pthread_cond, &pthread_mutex);

  // postconditions:

  ensure(rtncode == 0);

#endif
}


///
void
sheaf::thread_condition_variable::
lock_mutex()
{

#ifdef _PTHREADS

  // body:

  int rtncode;

  rtncode = pthread_mutex_lock(&pthread_mutex);

  // postconditions:

  ensure(rtncode == 0);

#endif
}


///
void
sheaf::thread_condition_variable::
unlock_mutex()
{

#ifdef _PTHREADS

  // body:

  int rtncode = pthread_mutex_unlock(&pthread_mutex);

  // postconditions:

  ensure(rtncode == 0);

#endif
}

#endif // _PTHREADS
