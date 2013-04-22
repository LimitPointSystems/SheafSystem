

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class hash_index_space_state

#ifndef HASH_INDEX_SPACE_STATE_H
#define HASH_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_STATE_H
#include "mutable_index_space_state.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

namespace sheaf
{
  
class hash_index_space_state;
class hash_index_space_iterator;

///
/// An hash map implementation of class mutable_index_space_state.
/// This representation is intended to efficiently represent
/// id spaces that are possibly negative and are sparse, that is,
/// end() is much greater than ct() and hence uses hash maps to
/// represent both directions of the map.
///
class SHEAF_DLL_SPEC hash_index_space_state : public mutable_index_space_state
{

  friend class hash_index_space_iterator;
  friend class namespace_poset;
  friend SHEAF_DLL_SPEC size_t deep_size(const hash_index_space_state& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name HASH_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an arg list for constructing an instance of this.
  ///
  static arg_list make_arg_list(size_type xcapacity);

protected:

  ///
  /// Default constructor
  ///
  hash_index_space_state();

  ///
  /// Copy constructor; disabled
  ///
  hash_index_space_state(const hash_index_space_state& xother) { };

  ///
  /// Constructor: Creates an instance from arguments xargs.
  ///
  hash_index_space_state(const arg_list& xargs);

  ///
  /// Destructor
  ///
  virtual ~hash_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name MUTABLE INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  using mutable_index_space_state::update_extrema;

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

protected:

  ///
  /// Inserts entry (xdomain_id, xrange_id) into the map representation.
  ///
  virtual void map_rep_insert_entry(pod_type xdomain_id, pod_type xrange_id);

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
  /// The type of the range id to domain id map.
  ///
  typedef hash_map<pod_type, pod_type> map_type;

  ///
  /// The type of the range id to domain id map.
  ///
  typedef map_type to_domain_type;

  ///
  /// The representation of the range id to domain id map.
  ///
  to_domain_type _to_domain;

  ///
  /// The type of the domain id to range id map.
  ///
  typedef map_type to_range_type;

  ///
  /// The representation of the domain id to range id map.
  ///
  to_range_type _to_range;

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
  virtual hash_index_space_state& operator=(const explicit_index_space_state& xother);

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
  /// The pod index in the hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

protected:

private:

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
  static list_pool<hash_index_space_iterator>& iterators();

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@}

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// Virtual constructor; create a new instance of the same type at this
  /// with arguments xargs.
  ///
  virtual hash_index_space_state* clone(const arg_list& xargs) const;

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
 
///
/// The deep size of hash_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const hash_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef HASH_INDEX_SPACE_STATE_H
