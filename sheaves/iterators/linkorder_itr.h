
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

/// @file
/// Interface for class linkorder_itr

#ifndef LINKORDER_ITR_H
#define LINKORDER_ITR_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_ITR_H
#include "SheafSystem/filtered_depth_first_itr.h"
#endif

namespace sheaf
{
  
///
/// Specialization of the general depth-first iterator which exposes
/// the LINK_ACTION to the client.
///
template <typename T>
class SHEAF_DLL_SPEC linkorder_itr : public filtered_depth_first_itr<T>
{
  // ===========================================================
  /// @name LINKORDER_ITR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  linkorder_itr();

  ///
  /// Copy constructor
  ///
  linkorder_itr(const linkorder_itr& xother);

  ///
  /// Destructor
  ///
  ~linkorder_itr();

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor, with no filter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  linkorder_itr(const abstract_poset_member& xanchor,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  linkorder_itr(const abstract_poset_member& xanchor,
		const subposet& xfilter,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  linkorder_itr(const abstract_poset_member& xanchor,
		pod_index_type xfilter_index,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  linkorder_itr(const abstract_poset_member& xanchor,
		const scoped_index& xfilter_index,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  linkorder_itr(const abstract_poset_member& xanchor,
		const std::string& xfilter_name,
		bool xdown,
		bool xstrict);

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual linkorder_itr* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}
};

///
/// Linkorder_itr<T> using zn_to_bool for _has_visited markers.
///
typedef linkorder_itr<zn_to_bool> zn_to_bool_linkorder_itr;

///
/// Linkorder_itr<T> using set for _has_visited markers.
///
typedef linkorder_itr< std::set<pod_index_type> > set_linkorder_itr;

///
/// Linkorder_itr<T> using unordered_set for _has_visited markers.
///
typedef linkorder_itr< unordered::unordered_set<pod_index_type> > unordered_set_linkorder_itr;
 
} // namespace sheaf

#endif // ifndef LINKORDER_ITERATOR_H
