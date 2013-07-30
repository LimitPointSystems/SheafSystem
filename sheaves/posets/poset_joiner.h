
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

// Interface for class POSET_JOINER

#ifndef POSET_JOINER_H
#define POSET_JOINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class abstract_poset_member;
class tern;
class poset_state_handle;
class scoped_index;
class subposet;

///
/// Computes the join of given poset members.
///
class SHEAF_DLL_SPEC poset_joiner
{
public:

  ///
  /// Creates a joiner for poset xhost.
  ///
  poset_joiner(const poset_state_handle* xhost);

  ///
  /// Destructor; not virtual, can not be base class.
  ///
  ~poset_joiner();

  ///
  /// The join of the members of xexpansion
  ///
  void join(const scoped_index* xexpansion,
	    int xexpansion_ct,
	    const tern& xgreatest,
	    abstract_poset_member& xresult);

  ///
  /// The join of the members of xexpansion
  ///
  void join(subposet* xexpansion,
	    const tern& xgreatest,
	    abstract_poset_member& xresult);

  ///
  /// The host poset.
  ///
  poset_state_handle* host() const;

private:

  ///
  /// The host poset.
  ///
  poset_state_handle* _host;
};
 

} // namespace sheaf

#endif // ifndef POSET_JOINER_H
