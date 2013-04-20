

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class index_space_family_iterator

#ifndef INDEX_SPACE_FAMILY_ITERATOR_H
#define INDEX_SPACE_FAMILY_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef INDEX_SPACE_FAMILY_H
#include "index_space_family.h"
#endif

#ifndef INDEX_SPACE_INTERVAL_ITERATOR_H
#include "index_space_interval_iterator.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

///
/// An abstract iterator over the id spaces of a interval.
///
class SHEAF_DLL_SPEC index_space_family_iterator : public any
{

  // ===========================================================
  /// @name INDEX_SPACE_FAMILY_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Constructor: Creates an instance with id_spaces() == xid_spaces and
  ///              only_persistent() == xonly_persistent.
  ///
  index_space_family_iterator(const index_space_family& xid_spaces,
			      bool xonly_persistent);

  ///
  /// Destructor
  ///
  virtual ~index_space_family_iterator();

  ///
  /// Assignment operator.
  ///
  index_space_family_iterator& operator=(const index_space_family_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  bool operator==(const index_space_family_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  index_space_family_iterator* clone() const;

  ///
  /// True if only the persistent id spaces are iterated over.
  ///
  bool only_persistent() const;

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
  /// The current host id space interval being iterated over.
  ///
  const index_space_interval& host() const;

  ///
  /// The index of the current id space in the iteration.
  ///
  pod_type index() const;

  ///
  /// The name of the current id space in the iteration.
  ///
  string name() const;

protected:

  ///
  /// Default constructor; disabled.
  ///
  index_space_family_iterator() { };

  ///
  /// Copy constructor.
  ///
  index_space_family_iterator(const index_space_family_iterator& xother);

  ///
  /// Increment to the next id space in the interval.
  ///
  void next_id_space();

  ///
  /// Type of interval map.
  ///
  typedef index_space_family::interval_map_type interval_map_type;

  ///
  /// Type of interval map iterator.
  ///
  typedef interval_map_type::const_iterator const_interval_iterator_type;

  ///
  /// The index space family.
  ///
  const index_space_family* _id_spaces;

  ///
  /// The stl iterator over the intervals.
  ///
  const_interval_iterator_type _interval_itr;

  ///
  /// The iterator over id spaces for the current id space interval.
  ///
  index_space_interval_iterator _id_space_itr;

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

#endif // ifndef INDEX_SPACE_FAMILY_ITERATOR_H
