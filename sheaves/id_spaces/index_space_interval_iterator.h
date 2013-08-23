
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Interface for class index_space_interval_iterator

#ifndef INDEX_SPACE_INTERVAL_ITERATOR_H
#define INDEX_SPACE_INTERVAL_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class hub_index_space_handle;
class index_space_interval;
class index_space_family;
class index_space_handle;
class index_space_iterator;

///
/// An abstract iterator over the id spaces of a interval.
///
class SHEAF_DLL_SPEC index_space_interval_iterator : public any
{

  friend class index_space_family;
  friend class index_space_family_iterator;

  // ===========================================================
  /// @name INDEX_SPACE_INTERVAL_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Destructor
  ///
  virtual ~index_space_interval_iterator();

  ///
  /// Assignment operator.
  ///
  index_space_interval_iterator& operator=(const index_space_interval_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  bool operator==(const index_space_interval_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  index_space_interval_iterator* clone() const;

  ///
  /// The host id space interval being iterated over.
  ///
  const index_space_interval& host() const;

  ///
  /// True if only the persistent id spaces are iterated over.
  ///
  bool only_persistent() const;

  ///
  /// The upper bound of the id spaces.
  ///
  size_type ub() const;

  ///
  /// Makes id_space() the next id space in the iteration.
  ///
  void next();

  ///
  /// True if iteration is finished.
  ///
  bool is_done() const;

  ///
  /// Restarts the iteration.
  ///
  void reset();

  ///
  /// The index of the current id space in the iteration.
  ///
  pod_type index() const;

protected:

  ///
  /// Default constructor; disabled.
  ///
  index_space_interval_iterator() { };

  ///
  /// Copy constructor.
  ///
  index_space_interval_iterator(const index_space_interval_iterator& xother);

  ///
  /// Constructor: Creates an instance with only_persistent() == xonly_persistent.
  ///
  index_space_interval_iterator(bool xonly_persistent);

  ///
  /// Attach this iterator to the host xhost.
  ///
  void attach_to(index_space_interval& xhost);

  ///
  /// Detach this iterator.
  ///
  void detach();

  ///
  /// True, if this iterator is attached.
  ///
  bool is_attached() const;

  ///
  /// The host id space interval being iterated over.
  ///
  index_space_interval* _host;

  ///
  /// True if only the persistent id spaces are iterated over.
  ///
  bool _only_persistent;

  ///
  /// The local id of the current id space in the iteration.
  ///
  pod_type _local_id;

  ///
  /// The upper bound of the iteration.
  ///
  size_type _ub;

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id space family for this (const version).
  ///
  const index_space_family& id_spaces() const;

  ///
  /// The id space family for this (mutable version).
  ///
  index_space_family& id_spaces();

  ///
  /// The hub id space.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// The number of members.
  ///
  size_type ct() const;

  ///
  /// Beginning id of this space.
  ///
  pod_type begin() const;

  ///
  /// Ending id of this space.
  ///
  pod_type end() const;

  ///
  /// True if this space contains id xid.
  ///
  bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  bool contains_hub(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  bool contains_unglued_hub(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the glued hub id space.
  ///
  bool contains_glued_hub(pod_type xid) const;

  ///
  /// True if this space contains an id xid equivalent to xhub_id in
  /// the hub id space.
  ///
  bool contains(pod_type xid, pod_type xhub_id) const;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  pod_type hub_pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  pod_type unglued_hub_pod(pod_type xid) const;

  ///
  /// The pod index in the glued hub id space equivalent to xid in this id space.
  ///
  pod_type glued_hub_pod(pod_type xid) const;

  ///
  /// True if this id space should be written to disk.
  ///
  bool is_persistent() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space handle from the handle pool attached to the
  /// current id space state.
  ///
  index_space_handle& get_id_space() const;

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  void release_id_space(index_space_handle& xid_space) const;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  bool allocated_id_space(index_space_handle& xid_space) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space iterator from the iterator pool attached to the
  /// current id space state.
  ///
  index_space_iterator& get_id_space_iterator() const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  void release_id_space_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  bool allocated_id_space_iterator(index_space_iterator& xitr) const;

protected:

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

#endif // ifndef INDEX_SPACE_INTERVAL_ITERATOR_H
