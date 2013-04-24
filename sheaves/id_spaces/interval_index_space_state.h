

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class interval_index_space_state

#ifndef INTERVAL_INDEX_SPACE_STATE_H
#define INTERVAL_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "auto_block.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_STATE_H
#include "mutable_index_space_state.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

namespace sheaf
{

class interval_index_space_handle;
class interval_index_space_state;
class interval_index_space_iterator;

///
/// An STL map implementation of class mutable_index_space_state
/// optimized to efficiently represent id spaces that 
/// consist of a collection of closed intervals [begin, end]
/// in both the domain id space and the range id space.
/// Each entry (domain_end, range_end) in the _to_domain map 
/// represents the end of a interval in the range id space. If the
/// range interval is not mapped to an domain interval, domain_end
/// is the invalid index value. _to_domain.lower_bound(i) returns the
/// end of the interval containing i and, if domain_end is valid,
/// pod(i) can be computed from i, range_end, and domain_end.
/// 
/// The _to_range map and hub_pod(i) work in a similar manner. 
/// See the comments in function insert_interval for a more detailed
/// discussion.
///
class SHEAF_DLL_SPEC interval_index_space_state : public mutable_index_space_state
{

  friend class interval_index_space_iterator;
  friend class namespace_poset;
  friend SHEAF_DLL_SPEC size_t deep_size(const interval_index_space_state& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name INTERVAL_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an arg list for constructing an instance of this.
  /// If xmerge_mode is true, compatible intervals will be merged.
  /// Otherwise, intervals will not be merged.
  ///
  static arg_list make_arg_list(bool xmerge_mode);

protected:

  ///
  /// Maps the interval [xdomain_begin, xdomain_end] to
  // [xrange_begin, xrange_end] in map xmap.
  ///
  static void insert_map_interval(pod_type xdomain_begin, 
				  pod_type xdomain_end, 
				  pod_type xrange_begin, 
				  pod_type xrange_end,
				  map<pod_type, pod_type>& xmap,
				  bool xmerge_mode);

  ///
  /// The value of map xmap at id xid.
  ///
  static pod_type map_value(pod_type xid, const map<pod_type, pod_type>& xmap);

  ///
  /// Default constructor
  ///
  interval_index_space_state();

  ///
  /// Copy constructor; disabled
  ///
  interval_index_space_state(const interval_index_space_state& xother) { };

  ///
  /// Constructor: Creates an instance from arguments xargs.
  ///
  interval_index_space_state(const arg_list& xargs);

  ///
  /// Destructor
  ///
  virtual ~interval_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name INTERVAL INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make the closed interval [xbegin, xend] equivalent to
  /// [xbegin.hub_pod(), xhub_end.hub_pod()].
  /// synonym for insert_interval(xbegin, xend, xhub_begin.hub_pod(), xhub_end.hub_pod()).
  ///
  void insert_interval(pod_type xbegin,
		       pod_type xend,
		       const scoped_index& xhub_begin, 
		       const scoped_index& xhub_end);
  
  ///
  /// Make the closed interval [xbegin, xend] equivalent to
  /// [xhub_begin, xhub_end].
  ///
  void insert_interval(pod_type xbegin, 
		       pod_type xend, 
		       pod_type xhub_begin, 
		       pod_type xhub_end);

  ///
  /// Push the closed interval [xhub_begin.hub_pod(), xhub_end.hub_pod()]
  /// to the end of this space.
  /// synonym for push_interval(xhub_begin.hub_pod(), xhub_end.hub_pod()).
  ///
  void push_interval(const scoped_index& xhub_begin,
		     const scoped_index& xhub_end);

  ///
  /// Push the closed interval [xhub_begin, xhub_end] to the end of this space.
  ///
  void push_interval(pod_type xhub_begin, pod_type xhub_end);
  
  ///
  /// Removes the equivalance associated with the interval
  /// [xhub_begin.hub_pod(), xhub_end.hub_pod()].
  /// synonym for remove_hub_interval(xhub_begin.hub_pod(), xhub_end.hub_pod()).
  /// Returns the number of entries actually removed, if any.
  ///
  size_type remove_interval(const scoped_index& xhub_begin,
			    const scoped_index& xhub_end);

  ///
  /// Removes the equivalance associated with the interval
  /// [xhub_begin, xhub_end].
  /// Returns the number of entries actually removed, if any.
  ///
  size_type remove_hub_interval(pod_type xhub_begin, pod_type xhub_end);  

  ///
  /// Removes the equivalance associated with the interval
  /// [xbegin, xend].
  /// Returns the number of entries actually removed, if any.
  ///
  size_type remove_interval(pod_type xbegin, pod_type xend);  

  ///
  /// The beginning of the interval containing xid.hub_pod().
  /// synonym for internval_begin(xid.hub_pod()).
  ///
  pod_type interval_begin(const scoped_index& xid) const;
  
  ///
  /// The beginning of the interval containing xhub_id.
  ///
  pod_type interval_begin(pod_type xhub_id) const;
  
  ///
  /// The end of the interval containing xid.hub_pod.
  /// synonym for internval_end(xid.hub_pod()).
  ///
  pod_type interval_end(const scoped_index& xid) const;
  
  ///
  /// The end of the interval containing xhub_id.
  ///
  pod_type interval_end(pod_type xhub_id) const;
  
  ///
  /// True if and only if compatible intervals should be merged.
  ///
  bool merge_mode() const;

  ///
  /// Sets merge_mode() to xvalue.
  ///
  void put_merge_mode(bool xvalue);

protected:

  ///
  /// The number of entries in the interval [xhub_begin, xhub_end]
  /// that have invalid map values.
  ///
  size_type invalid_entry_ct(pod_type xhub_begin, pod_type xhub_end) const;

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

  ///
  /// Inserts the map representation into ostream xos.
  ///
  void print_map_rep(ostream& xos) const;
  
protected:

  ///
  /// Inserts the intervals [xdomain_begin, xdomain_end] and
  /// [xrange_begin, xrange_end] into the map representation.
  ///
  void map_rep_insert_interval(pod_type xdomain_begin, 
			       pod_type xdomain_end, 
			       pod_type xrange_begin, 
			       pod_type xrange_end);

  ///
  /// Makes the interval [xbegin, xend) and 
  /// its image unmapped in the map representation.
  /// Returns the number of entries actually unmapped, if any.
  ///
  size_type map_rep_remove_interval(pod_type xbegin,
				    pod_type xend,
				    bool xis_range_id);  

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
  /// The type of the id maps.
  ///
  typedef map<pod_type, pod_type> map_type;

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

  ///
  /// The capacity of this map.
  ///
  pod_type _capacity;

  ///
  /// True if and only if compatible intervals should be merged.
  ///
  bool _merge_mode;

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
  virtual interval_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  using mutable_index_space_state::contains;

  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const;

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
  static list_pool<interval_index_space_handle>& handles();

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
  static list_pool<interval_index_space_iterator>& iterators();

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
  virtual interval_index_space_state* clone(const arg_list& xargs) const;

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
/// The deep size of interval_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const interval_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef INTERVAL_INDEX_SPACE_STATE_H
