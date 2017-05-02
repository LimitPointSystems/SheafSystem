
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
/// Interface for class list_index_space_state

#ifndef LIST_INDEX_SPACE_STATE_H
#define LIST_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef LIST_POOL_H
#include "SheafSystem/list_pool.h"
#endif

#ifndef GATHERED_INSERTION_INDEX_SPACE_STATE_H
#include "SheafSystem/gathered_insertion_index_space_state.h"
#endif

#ifndef STD_LIST_H
#include "SheafSystem/std_list.h"
#endif

namespace sheaf
{

class list_index_space_handle;
class list_index_space_state;
class list_index_space_iterator;
 
///
/// The deep size of list_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const list_index_space_state& xn, bool xinclude_shallow);

///
/// An list implementation of class gathered_insertion_index_space_state.
/// This representation is intended to efficiently represent
/// id spaces that are gathered, that is, the domain ids are in the domain [0, end()).  
/// This representation is optimized for sequential access and will have 
/// linear asymptotic performance in time for random access lookup and remove.
///
class SHEAF_DLL_SPEC list_index_space_state : public gathered_insertion_index_space_state
{

  friend class list_index_space_iterator;
  friend class namespace_poset;
  friend SHEAF_DLL_SPEC size_t deep_size(const list_index_space_state& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new list id space in the id space family xid_space
  /// at the next available id space index with name xname,
  /// and persistence xis_persistent.
  /// Returns a handle to the id space created.
  ///
  static list_index_space_handle new_space(index_space_family& xid_spaces,
					   const std::string& xname,
					   bool xis_persistent);

  ///
  /// Create a new list id space in the id space family xid_space
  /// at the id space index xid with name xname, and persistence
  /// xis_persistent.
  /// Returns a handle to the id space created.
  ///
  static list_index_space_handle new_space(index_space_family& xid_spaces,
					   pod_type xid,
					   const std::string& xname,
					   bool xis_persistent);

protected:

private:

  //@}


  // ===========================================================
  /// @name LIST_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Reverse the order, for instance hub_pod(new 0) = hub_pod(old last);
  ///
  void reverse(bool xupdate_extrema);

  ///
  /// The front of the list used to represent this id space;
  /// equivalent to hub_pod(begin()).
  ///
  pod_type front() const;

  ///
  /// The back of the list used to represent this id space;
  /// equivalent to hub_pod(last id).
  ///
  pod_type back() const;

  ///
  /// Pushes hub id xhub_id onto the front of the list used to represent this id space;
  /// increments the domain ids of all existing members.
  ///
  void push_front(pod_type xhub_id);

  ///
  /// Replaces xold_range_id with xnew_range_id.
  ///
  void replace_range_id(pod_type xold_range_id, pod_type xnew_range_id);

protected:

  ///
  /// Default constructor
  ///
  list_index_space_state();

  ///
  /// Copy constructor; disabled
  ///
  list_index_space_state(const list_index_space_state& xother) { };

  ///
  /// Destructor
  ///
  virtual ~list_index_space_state();
  

private:

  //@}


  // ===========================================================
  /// @name GATHERED_INSERTION INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  using gathered_insertion_index_space_state::update_extrema;

  ///
  /// Update the id extrema.
  ///
  virtual void update_extrema();

  ///
  /// Reserve enough memory for xcapacity number of ids.
  ///
  virtual void reserve(size_type xcapacity);

  ///
  /// The number of ids reserved in memory.
  ///
  virtual size_type capacity() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name MAP REPRESENTATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the domain id to range id map.
  ///
  typedef std::list<pod_type> to_range_type;

  ///
  /// The representation of the domain id to range id map.
  /// Warning: direct manipulation of the to_range map can invalid
  /// the state of the index space, make sure to invoke
  /// update_extrema_after_remove() before using the rest of the index space interface.
  ///
  to_range_type& to_range();

  ///
  /// The representation of the domain id to range id map, const version.
  /// Warning: direct manipulation of the to_range map can invalid
  /// the state of the index space, make sure to invoke
  /// update_extrema_after_remove() before using the rest of the index space interface.
  ///
  const to_range_type& to_range() const;

protected:

  ///
  /// Inserts entry (next_id(), xrange_id) into the map representation.
  ///
  virtual void map_rep_push_back(pod_type xrange_id);

  ///
  /// Inserts entry (xitr.pod(), xrange_id) into the map representation.
  /// Increments all domain ids greater than xitr.pod() by one.  Sets
  /// xitr to the entry at xitr.pod()+1.
  ///
  virtual void map_rep_push(index_space_iterator& xitr, pod_type xrange_id);

  ///
  /// Removes the entry containing range id xid (xis_range_id true) or
  /// domain id xid (xis_range_id false) from the map representation;
  /// returns the number of entries actully removed, either 0 or 1.
  ///
  virtual size_type map_rep_remove_entry(pod_type xid, bool xis_range_id);

  ///
  /// Removes the equivalence associated with id xitr.pod()/
  /// Increments xitr to the next entry if any.
  ///
  virtual void map_rep_remove_entry(index_space_iterator& xitr);

  ///
  /// Removes all entrires from the map representation.
  ///
  virtual void map_rep_clear();

  ///
  /// Gathers the map representation into an interval.
  ///
  virtual void map_rep_gather();

  ///
  /// The representation of the domain id to range id map.
  ///
  to_range_type _to_range;

  ///
  /// The capacity of this map.
  ///
  pod_type _capacity;

  ///
  /// An iterator pointing to the _to_range entry with
  /// range id (xis_range_id true) or domain id (xis_range_id false) xid.
  ///
  to_range_type::iterator to_range_itr(pod_type xid, bool xis_range_id);

  ///
  /// A const_iterator pointing to the _to_range entry with 
  /// range id (xis_range_id true) or domain id (xis_range_id false) xid.
  ///
  to_range_type::const_iterator to_range_const_itr(pod_type xid, bool xis_range_id) const;
  

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const explicit_index_space_state& xother) const;

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual list_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const;

  ///
  /// True if this space contains an id xid equivalent to xhub_id in
  /// the hub id space.
  ///
  virtual bool contains(pod_type xid, pod_type xhub_id) const;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of handles in the pool.
  ///
  static size_type handle_pool_ct();

  ///
  /// The deep size of the handle pool.
  ///
  static size_type handle_pool_deep_size();

  ///
  /// The id space handle with this state.
  ///
  virtual index_space_handle& get_id_space() const;

  ///
  /// Release the id space handle xid_space.
  ///
  virtual void release_id_space(index_space_handle& xid_space) const;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space(const index_space_handle& xid_space) const;

protected:

private:

  ///
  /// The handle pool.
  ///
  static list_pool<list_index_space_handle>& handles();

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of iterators in the pool.
  ///
  static size_type iterator_pool_ct();

  ///
  /// The deep size of the iterator pool.
  ///
  static size_type iterator_pool_deep_size();

  ///
  /// Allocates an id space iterator from the iterator pool.
  ///
  virtual index_space_iterator& get_iterator() const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_iterator(const index_space_iterator& xitr) const;

protected:

private:

  ///
  /// Pool of iterators.
  ///
  static list_pool<list_index_space_iterator>& iterators();

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@}

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// Virtual constructor; create a new instance of the same type at this.
  ///
  virtual list_index_space_state* clone() const;

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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
  
} // end namespace sheaf

#endif // ifndef LIST_INDEX_SPACE_STATE_H
