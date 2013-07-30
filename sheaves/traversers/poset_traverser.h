
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

// Interface for class POSET_TRAVERSER

#ifndef POSET_TRAVERSER_H
#define POSET_TRAVERSER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace sheaf
{

class abstract_poset_member;
class poset_state_handle;
class poset_component;
class total_poset_member;
  
///
/// Abstract traverser (internal iterator) for poset.
///
class SHEAF_DLL_SPEC poset_traverser: public any
{

  /// @todo properly redefine features from any

public:

  // constructors:

  ///
  /// Constructor
  ///
  poset_traverser(const poset_state_handle* xanchor);

  ///
  /// Destructor
  ///
  ~poset_traverser();

  // queries:

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

  ///
  /// The poset being traversed (mutable version).
  ///
  inline poset_state_handle* host()
  {
    return _host;
  };

  ///
  /// The poset being traversed (const version).
  ///
  inline const poset_state_handle* host() const
  {
    return _host;
  };

  ///
  /// True if other is not void and is attached to the same host as this
  ///
  bool has_same_host(const poset_component* other) const;

  ///
  /// The member which is the starting point of this traversal (mutable verison).
  ///
  virtual abstract_poset_member* anchor();

  ///
  /// The member which is the starting point of this traversal (const version).
  ///
  virtual const abstract_poset_member* anchor() const;

  

  ///
  /// True if traversing down from anchor().
  ///
  inline bool in_down_set() const
  {
    return _in_down_set;
  };

  ///
  /// Traverse the down set (down == true) or up set (down == false) of xanchor.
  /// If reset_markers, reset all visited markers to false before begining.
  ///
  void traverse(const abstract_poset_member* xanchor, bool down, bool reset_markers = true);

protected:

  ///
  /// The poset being traversed.
  ///
  poset_state_handle* _host;

  ///
  /// The markers for previously visited members.
  ///
  zn_to_bool* _visited;

  ///
  /// The member which is the starting point of this traversal.
  ///
  abstract_poset_member* _anchor;

  ///
  /// True if traversing down from anchor().
  ///
  bool _in_down_set;

  ///
  /// True if xmbr has been previously visited.
  ///
  bool has_been_visited(const abstract_poset_member* xmbr) const;

  

  ///
  /// True if the member with index xindex has been previously visited.
  ///
  inline bool has_been_visited(int xindex) const
  {
    return (*_visited)[xindex];
  };

  ///
  /// The upper bound on the member index.
  ///
  scoped_index member_index_ub() const;

  ///
  /// True if no members have been visited.
  ///
  bool no_members_visited() const;

  ///
  /// True if all members have been visited.
  ///
  bool all_members_visited() const;

  ///
  /// Sets the visited markers false for all members.
  ///
  void mark_members_not_visited();

  ///
  /// Sets the visited marker true for xmbr.
  ///
  void mark_visited(const abstract_poset_member* xmbr);

  ///
  /// Sets the visited markers true for the emebr with index xindex.
  ///
  inline void mark_visited(int xindex)
  {
    _visited->force(xindex, true);
  };

  ///
  /// Sets the visited markers false for the emebr with index xindex.
  ///
  inline void mark_not_visited(int xindex)
  {
    _visited->force(xindex, false);
  };

  ///
  /// Implements the traversal.
  ///
  virtual void private_traverse() = 0;

  ///
  /// Ensures the visited bit vector is large enough.
  ///
  inline void ensure_visited_ub()
  {
    if(_visited->ub() < member_index_ub().pod())
      _visited->extend_to(member_index_ub().pod());
  }

};
  
} // namespace sheaf

#endif
