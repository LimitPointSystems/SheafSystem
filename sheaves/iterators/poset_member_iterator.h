
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

// Interface for class poset_member_iterator

#ifndef POSET_MEMBER_ITERATOR_H
#define POSET_MEMBER_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

namespace sheaf
{
  
///
/// @deprecated. No replacement.
/// Iterator over members of a subposet
///
class SHEAF_DLL_SPEC poset_member_iterator : public total_poset_member
{
public:

  

  ///
  /// True if iteration finished
  ///
  virtual bool is_done() const = 0;

  ///
  /// Makes this the next member of the subset
  ///
  virtual void next() = 0;

  ///
  /// Restarts the iteration, makes this the first member of subposet()
  ///
  virtual void reset() = 0;
};
  
} // namespace sheaf

#endif // ifndef POSET_MEMBER_ITERATOR_H
