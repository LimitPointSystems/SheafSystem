// $RCSfile: thread_mutex.h,v $ $Revision: 1.15 $ $Date: 2013/01/12 17:17:33 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
