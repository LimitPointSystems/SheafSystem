
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class RUNNABLE

#include "assert_contract.h"

#ifndef RUNNABLE_H
#include "runnable.h"
#endif

#ifdef _PTHREADS

///
void
sheaf::runnable::
run()
{

  // No-op.  meant to be overridden
}

#endif
