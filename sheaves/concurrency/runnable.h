// $RCSfile: runnable.h,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:33 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class RUNNABLE

#ifndef RUNNABLE_H
#define RUNNABLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifdef _PTHREADS

namespace sheaf
{
  
///
/// Intended to mimic Java's runnable class.
///
class SHEAF_DLL_SPEC runnable
{

public:
  ///
  /// meant to be overridden
  ///
  virtual void run();
};
 
} // namespace sheaf

#endif // _PTHREADS

#endif // ifndef RUNNABLE_H
