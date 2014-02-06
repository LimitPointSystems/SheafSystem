
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
/// Interface for class index_equivalence_iterator

#ifndef INDEX_EQUIVALENCE_ITERATOR_H
#define INDEX_EQUIVALENCE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef INDEX_EQUIVALENCE_CLASS_H
#include "index_equivalence_class.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

namespace sheaf
{

class index_space_family;

///
/// An iterator over members of an id equivalence class.
///
class SHEAF_DLL_SPEC index_equivalence_iterator : public any
{

  // ===========================================================
  /// @name INDEX_EQUIVALENCE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The member type for the equivalence id list.  The first value in
  /// the pair is the index of the id space, the second value in the
  /// pair is the pod.
  ///
  typedef index_equivalence_class::member_type member_type;

  ///
  /// Creates an instance for the id equivalence iterator
  /// of representative xrep_id in id space family xid_spaces.
  /// If xonly_persistent, only iterate over the persistent id spaces.
  /// If xsort_ids, sort the ids in increased space id order.
  ///
  index_equivalence_iterator(const index_space_family& xid_spaces,
			     pod_index_type xrep_id,
			     bool xonly_persistent,
			     bool xsort_ids);

  ///
  /// Creates an instance for the id equivalence iterator
  /// of representative xrep_id in id space family xid_spaces.
  /// If xonly_persistent, only iterate over the persistent id spaces.
  /// If xsort_ids, sort the ids in increased space id order.
  ///
  index_equivalence_iterator(const index_space_family& xid_spaces,
			     const scoped_index& xrep_id,
			     bool xonly_persistent,
			     bool xsort_ids);

  ///
  /// Creates an instance for the id equivalence iterator
  /// of invalid representative id in id space family xid_spaces.
  /// If xonly_persistent, only iterate over the persistent id spaces.
  /// If xsort_ids, sort the ids in increased space id order.
  ///
  index_equivalence_iterator(const index_space_family& xid_spaces,
			     bool xonly_persistent,
			     bool xsort_ids);

  ///
  /// Destructor
  ///
  virtual ~index_equivalence_iterator();

  ///
  /// The id space family of this equivalence class.
  ///
  const index_space_family& id_spaces() const;

  ///
  /// The representative id in the top id space of this equivalence class.
  ///
  pod_index_type rep_id() const;

  ///
  /// The representative id of this equivalence class.
  ///
  void rep_id(scoped_index& result) const;

  ///
  /// True, if only persistent id spaces should be iterated over.
  ///
  bool only_persistent() const;

  ///
  /// True, if the ids are sorted in increasing space id order.
  ///
  bool is_sorted() const;

  ///
  /// Sets rep_id() to xrep_id.
  ///
  void put_rep_id(pod_index_type xrep_id);

  ///
  /// Sets rep_id() to xrep_id.
  ///
  void put_rep_id(const scoped_index& xrep_id);

  ///
  /// The current equivalence class member.
  ///
  const member_type& item() const;

  ///
  /// True if iteration is finished.
  ///
  bool is_done() const;

  ///
  /// The number of items in the current equivalence list being iterated over.
  ///
  size_type ct() const;

  ///
  /// Makes item() the next item in the equivalence class.
  ///
  void next();

  ///
  /// Restarts the iteration.
  ///
  void reset();

protected:

  ///
  /// The type of iterator for the equivalence id list.
  ///
  typedef index_equivalence_class::list_type::const_iterator iterator_type;

  ///
  /// Default constructor; disabled.
  ///
  index_equivalence_iterator() { };

  ///
  /// The id space family to iterate over.
  ///
  const index_space_family* _id_spaces;

  ///
  /// The representative of this equivalence class.
  ///
  pod_index_type _rep_id;

  ///
  /// True, if only persistent id spaces should be iterated over.
  ///
  bool _only_persistent;

  ///
  /// True, if the ids are sorted in increasing space id order.
  ///
  bool _is_sorted;

  ///
  /// The equivalence class to iterate over.
  ///
  index_equivalence_class _equivalence_class;

  ///
  /// The current equivalence list iterator.
  ///
  iterator_type _itr;

  ///
  /// The end of the current list begin iterated over.
  ///
  iterator_type _end;

  ///
  /// The current equivalence class member.
  ///
  member_type _item;

  ///
  /// True if iteration is finished.
  ///
  bool _is_done;

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual index_equivalence_iterator* clone() const;

  ///
  /// Assignment operator.
  ///
  index_equivalence_iterator& operator=(const index_equivalence_iterator& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef INDEX_EQUIVALENCE_ITERATOR_H
