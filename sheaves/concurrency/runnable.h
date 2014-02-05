
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
