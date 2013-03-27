// $RCSfile: client_index.h,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:40 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class client_index

#ifndef CLIENT_INDEX_H
#define CLIENT_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

namespace sheaf
{
  
///
/// OBSOLETE: use scoped_index instead.
/// Client defined index for identifying poset members.
///

typedef scoped_index client_index;
 
} // namespace sheaf

#endif // ifndef CLIENT_INDEX_H






