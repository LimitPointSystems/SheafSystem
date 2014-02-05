
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

// Interface for class postorder_member_iterator

#ifndef POSTORDER_MEMBER_ITERATOR_H
#define POSTORDER_MEMBER_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_MEMBER_ITERATOR_H
#include "filtered_depth_first_member_iterator.h"
#endif

namespace sheaf
{

class subposet;
class zn_to_bool;
  
///
/// @deprecated No replacement.
/// Iterates in postorder over the intersection of a subposet filter
/// with a directional (up or down) set of a poset member anchor.
/// Attaches an a handle of type abstract_poset_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC postorder_member_iterator : public filtered_depth_first_member_iterator
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  postorder_member_iterator();

  ///
  /// Copy constructor
  ///
  postorder_member_iterator(const postorder_member_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual postorder_member_iterator& operator=(const filtered_depth_first_member_iterator& xother);

  ///
  /// Assignment operator
  ///
  postorder_member_iterator& operator=(const postorder_member_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~postorder_member_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual postorder_member_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor, no filter.
  /// Iterates in direction xdown. If xstrict, iterate over strict
  /// up/down set only.
  ///
  postorder_member_iterator(const abstract_poset_member& xanchor,
			    bool xdown,
			    bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_member_iterator(const abstract_poset_member& xanchor,
			    const subposet& xfilter,
			    bool xdown,
			    bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_member_iterator(const abstract_poset_member& xanchor,
                            pod_index_type xfilter_index,
                            bool xdown,
                            bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_member_iterator(const abstract_poset_member& xanchor,
                            const scoped_index& xfilter_index,
                            bool xdown,
                            bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_name.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_member_iterator(const abstract_poset_member& xanchor,
                            const std::string& xfilter_name,
                            bool xdown,
                            bool xstrict);

protected:

  ///
  /// Covariant constructor; supports virtual construction of data members.
  ///
  postorder_member_iterator(filtered_depth_first_iterator* xitr,
                            abstract_poset_member* xitem);

};
 
} // namespace sheaf

#endif // ifndef POSTORDER_MEMBER_ITERATOR_H
