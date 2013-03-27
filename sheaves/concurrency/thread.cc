// $RCSfile: thread.cc,v $ $Revision: 1.16 $ $Date: 2013/01/12 17:17:33 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class THREAD

#ifndef THREAD_H
#include "thread.h"
#endif

#ifdef _PTHREADS

#include "assert_contract.h"

#ifndef RUNNABLE_H
#include "runnable.h"
#endif

#include "std_slist.h"

slist<thread *> *
sheaf::thread::
_thread_list = 0;

///
sheaf::thread::
thread()
{

  // body:

  _is_alive = false;
  _runnable = 0;

  if (_thread_list == 0)
    _thread_list = new slist<thread *>;

  int old_list_size = _thread_list->size();

  _thread_list->push_front(this);

  // postconditions:

  ensure(invariant());
  ensure(_thread_list->size() == old_list_size+1);
  ensure(! is_alive(this));
};


///
sheaf::thread::
thread(runnable* xrunnable)
{

  // preconditions:

  require(xrunnable != 0);

  // body:

  _is_alive = false;
  _runnable = xrunnable;

  if (_thread_list == 0)
    _thread_list = new slist<thread *>;

  int old_list_size = _thread_list->size();

  _thread_list->push_front(this);

  // postconditions:

  ensure(invariant());
  ensure(_thread_list->size() == old_list_size+1);
  ensure(! is_alive(this));

}


///
sheaf::thread::
~thread()
{

  // preconditions:

  require(_thread_list != 0);

  // body:

}

bool
sheaf::thread::
invariant() const
{

  bool result;

  result = (_thread_list != 0);

  return result;
}


///
void
sheaf::thread::
join()
{

  // preconditions:

  /// @issue only one thread can call this.  If Current is available in other
  /// threads (and there is no way to prevent it) the call will fail.  We'll have
  /// to control this somehow.

  // body:

  int rtn_code = pthread_join(pthread,0);

  // postconditions:

  ensure(rtn_code == 0);
}


///
void
sheaf::thread::
run()
{

  // body:

  // No-op intended to be overriden in descendant classes.
}


///
void
sheaf::thread::
start()
{

  // body:

  int rtncode = pthread_create(&pthread,                              // start a new thread
                               reinterpret_cast<pthread_attr_t *>(0), // with default attributes
                               static_run,                            // beginning execution at static function "static_run"
                               reinterpret_cast<void *>(this));       // with "this" as argument

  // postconditions:

  ensure(rtncode == 0);

}


void *
sheaf::thread::
static_run(thread* This)
{

  // preconditions:

  require(This != 0);
  require(! is_alive(This));

  // body:

  pthread_cleanup_push(cleanup,This);

  This->_is_alive = true;

  if (This->_runnable == 0)
    This->run();
  else
    This->_runnable->run();

  This->_is_alive = false;

  pthread_cleanup_pop(1);

  // postconditions:

  ensure(! is_alive(This));

}


///
void
sheaf::thread::
sleep(unsigned int seconds)
{

  // body:

  ::sleep(seconds);
}


///
bool
sheaf::thread::
is_alive(thread* other)
{

  // preconditions:

  require(other != 0);

  // body:

  /// @issue
  /// We're assuming other is alive if it's in the thread_list
  /// and has the _is_alive field set to true,
  /// but it might not be in the thread list an instant after
  /// it's been found here.  Java's isAlive() would seem to
  /// suffer from the same problem.

  bool result;

  if(_thread_list != 0)
  {

    slist<thread *>::iterator it  = _thread_list->begin();
    slist<thread *>::iterator end = _thread_list->end();

    for (; it != end && *it != other; ++it)
      ;

    if (it != end && (*it)->_is_alive)
      result = true;
    else
      result = false;
  }
  else
    result = false;

  return result;
}


///
thread *
sheaf::thread::
current_thread()
{

  // body:

  pthread_t self = pthread_self();

  thread *result;

  slist<thread *> *list = sheaf::thread::_thread_list;

  if (list != 0)
  {

    slist<thread *>::iterator it  = list->begin();
    slist<thread *>::iterator end = list->end();

    for (; it != end && (pthread_equal(self,(*it)->pthread) == 0); ++it)
      ;

    if (it == end)
      result = 0; // called from main thread - outside a "thread"
    else
      result = *it;
  }
  else
    result = 0;

  return result;

}


void
sheaf::thread::
cleanup(thread* This)
{

  // preconditions:

  require(This != 0);
  require(! is_alive(This));

  // body:

  slist<thread *>::iterator it  = _thread_list->begin();
  slist<thread *>::iterator end = _thread_list->end();

  for (; it != end && *it != This; ++it)
    ;

  assertion(it != end);

  This->_thread_list->erase(it);

  // postconditions:

}


///
int
sheaf::thread::
active_count()
{

  // body:

  int result;

  slist<thread *> *list = sheaf::thread::_thread_list;

  result = list->size();

  // postconditions:

  /// @issue this isn't quite the same as java.  We're only counting the threads
  /// we created and not the thread of the main() program.

  ensure(result >= 0);

  return result;

}


///
void
sheaf::thread::
stop()
{

  // body:

  int rtncode = pthread_cancel(pthread);

  // postconditions:

  ensure(rtncode == 0);

}

#endif // _PTHREADS
