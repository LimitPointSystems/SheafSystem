
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
/// Interface for class postorder_itr

#ifndef COM_LIMITPOINT_SHEAF_POSTORDER_ITR_H
#define COM_LIMITPOINT_SHEAF_POSTORDER_ITR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_FILTERED_DEPTH_FIRST_ITR_H
#include "ComLimitPoint/sheaf/filtered_depth_first_itr.h"
#endif

namespace sheaf
{
  
///
/// Specialization of the filtered depth-first iterator which exposes
/// the POSTVISIT_ACTION to the client.
///
template <typename T>
class SHEAF_DLL_SPEC postorder_itr : public filtered_depth_first_itr<T>
{
  // ===========================================================
  /// @name POSTORDER_ITR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  postorder_itr();

  ///
  /// Copy constructor
  ///
  postorder_itr(const postorder_itr& xother);

  ///
  /// Destructor
  ///
  ~postorder_itr();

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor, with no filter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_itr(const abstract_poset_member& xanchor,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_itr(const abstract_poset_member& xanchor,
		const subposet& xfilter,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_itr(const abstract_poset_member& xanchor,
		pod_index_type xfilter_index,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_itr(const abstract_poset_member& xanchor,
		const scoped_index& xfilter_index,
		bool xdown,
		bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_name.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  postorder_itr(const abstract_poset_member& xanchor,
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
  virtual postorder_itr* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}
};

///
/// Postorder_itr<T> using zn_to_bool for _has_visited markers.
///
typedef postorder_itr<zn_to_bool> zn_to_bool_postorder_itr;

///
/// Postorder_itr<T> using set for _has_visited markers.
///
typedef postorder_itr< std::set<pod_index_type> > set_postorder_itr;

///
/// Postorder_itr<T> using unordered_set for _has_visited markers.
///
typedef postorder_itr< unordered::unordered_set<pod_index_type> > unordered_set_postorder_itr;
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POSTORDER_ITR_H
