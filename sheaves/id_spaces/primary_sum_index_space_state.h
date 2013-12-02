
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
/// Interface for class primary_sum_index_space_state

#ifndef PRIMARY_SUM_INDEX_SPACE_STATE_H
#define PRIMARY_SUM_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SUM_INDEX_SPACE_STATE_H
#include "sum_index_space_state.h"
#endif

#ifndef LIST_POOL_H
#include "list_pool.h"
#endif

#ifndef INTERVAL_INDEX_SPACE_HANDLE_H
#include "interval_index_space_handle.h"
#endif
 
#ifndef INTERVAL_SET_H
#include "interval_set.h"
#endif

#ifndef RESERVED_PRIMARY_INDEX_SPACE_HANDLE_H
#include "reserved_primary_index_space_handle.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
#endif

namespace sheaf
{

class interval_index_space_handle;
class primary_index_space_handle;
class hub_index_space_iterator;
  
///
/// An implementation of class sum_index_space_state intended for use as
/// the sum of the primary id spaces.
///
/// Class primary_sum_index_space_state has a mutable equivalence
/// relation which is interpreted as defining the hub id space as 
/// the quotient space of the primary sum id space by the equivalence relation. 
/// That is, the equivalence relation is interpreted as gluing members of
/// the primary sum id space together to form the hub id space.
///
/// The implementation of this class takes advantage of two unique features:
///
/// (1) The hub id space is an explicit subset of the primary sum id space,
///     so the equivalence relation can represented using the rem function. We
///     can thus make the equivalence relation mutable by storing the rem
///     function and its inverse in mutable form and deriving the id spaces
///     from the equivalence relation.
///
/// (2) In practice, relatively few sum ids are glued, so most of the
///     equivalence classes contain only a single member and most
///     of the entries in the rem function are reflexive (rem(s) = s).
///     We can thus store only the reflexive reduction of rem and its inverse.
///
class SHEAF_DLL_SPEC primary_sum_index_space_state : public sum_index_space_state
{

  friend class hub_index_space_iterator;
  friend class namespace_poset;
  friend SHEAF_DLL_SPEC size_t deep_size(const primary_sum_index_space_state& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new primary sum id space in the id space family xid_space
  /// at the next available id space index with name xname.
  /// Returns a handle to the id space created.
  ///
  static hub_index_space_handle new_space(index_space_family& xid_spaces,
					  const std::string& xname);

  ///
  /// Create a new primary sum id space in the id space family xid_space
  /// at the id space index xid with name xname.
  /// Returns a handle to the id space created.
  ///
  static hub_index_space_handle new_space(index_space_family& xid_spaces,
					  pod_type xid,
					  const std::string& xname);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIMARY_SUM_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor
  ///
  primary_sum_index_space_state();

  ///
  /// Copy constructor; disabled.
  ///
  primary_sum_index_space_state(const primary_sum_index_space_state& xother) { };

  ///
  /// Destructor
  ///
  virtual ~primary_sum_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name PRIMARY SUM INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocate the next available id in this space.
  ///
  pod_type new_id();

  ///
  /// Allocate the id xid in this space.
  ///
  pod_type new_id(pod_type xid);

  ///
  /// Deallocate the id xid in this space.
  ///
  void delete_id(pod_type xid);

  ///
  /// True if and only if the reserved term containing xid is
  /// already a reserved term or is available for allocation.
  ///
  bool is_valid_reserved_id(pod_type xid) const;

  ///
  /// The next available id.
  ///
  pod_type next_id() const;

  ///
  /// Create a new primary term [next_id(), next_id()+xct).
  /// Returns the index of the term created.
  ///
  pod_type new_primary_term(size_type xct);

  ///
  /// Create a new primary term [xid, xid+xct).
  /// Returns the index of the term created.
  ///
  pod_type new_primary_term(pod_type xid, size_type xct);

  ///
  /// Remove xi-th term of this sum.
  ///
  void remove_term(pod_type xi);

  ///
  /// Extends the last term to ct() == xct.
  ///
  void extend_last_term(size_type xct);

  ///
  /// True if all ids in the interval [xbegin, xend) are in this space.
  ///
  bool interval_is_full(pod_type xbegin, pod_type xend) const;

  ///
  /// True if all ids in the interval [xbegin, xend) are not in this space.
  ///
  bool interval_is_empty(pod_type xbegin, pod_type xend) const;

  ///
  /// True if the ids in the interval [xbegin, xend) are available in this space.
  ///
  bool interval_is_available(pod_type xbegin, pod_type xend) const;

protected:

  /// Prefix of the term id spaces.
  ///
  static const std::string& term_prefix();

  ///
  /// Name of the next term id space.
  ///
  std::string next_term_name();

  ///
  /// Creates a new reserved term starting above next_hub_id().
  /// Returns the index of the term created.
  ///
  pod_type new_reserved_term();

  ///
  /// Creates a new reserved term starting at id xid.
  /// Returns the index of the term created.
  ///
  pod_type new_reserved_term(pod_type xid);  

  ///
  /// Insert term with id xterm_id into the interval .
  ///
  void add_term(pod_type xterm_id, pod_type xbegin, pod_type xend);

  ///
  /// True if the reserved interval for id xid is available for allocation.
  ///
  bool reserved_interval_is_available(pod_type xid) const;

  ///
  /// Update the id extrema.
  ///
  void update_extrema();

  ///
  /// Set of members in the domain of this map.
  ///
  interval_set _members;

  ///
  /// The next available id.
  ///
  pod_type _next_id;

  ///
  /// The current reserved term.
  ///
  reserved_primary_index_space_handle _reserved_term;

  ///
  /// The set of reserved term ids.
  ///
  hash_set<pod_type> _reserved_term_ids;
  
private:

  //@}


  // ===========================================================
  /// @name GLUING FACET
  // ===========================================================
  //@{

public:

  ///
  /// Glues xid to xrep; adds xid to the equivalence class
  /// with representative member xrep.
  ///
  void glue(pod_type xid, pod_type xrep);
  
  ///
  /// Unglues xid; makes xid its own representative.
  ///
  void unglue(pod_type xid);
  
  ///
  /// Unglue all ids glued to representative xrep_id; 
  /// makes each id in the equivalence class of xrep_id
  /// its own representative.
  ///
  void unglue_all(pod_type xrep_id);

  ///
  /// Ture if there is any gluing.
  ///
  bool has_gluing() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name GATHERED ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Construct a gathered id space from this id space.
  /// If xexclude_bottom, construct the id space without BOTTOM_INDEX.
  ///
  const index_space_handle& new_gathered_id_space(bool xexclude_bottom);

  ///
  /// Update the gathered id space.
  ///
  void update_gathered_id_space();

  ///
  /// The gathered id space.
  ///
  const index_space_handle& gathered_id_space() const;

  ///
  /// True, if the gathered id space exists.
  ///
  bool has_gathered_id_space() const;

  ///
  /// True, if the gathered id space excludes BOTTOM_INDEX.
  ///
  bool gathered_id_space_excludes_bottom() const;

  ///
  /// Name of the gathered id space.
  ///
  static const std::string& gathered_hub_id_space_name();

protected:

  ///
  /// Update the gathered id space.
  /// If xexclude_bottom, construct the id space without BOTTOM_INDEX.
  ///
  void update_gathered_id_space(bool xexclude_bottom);

  ///
  /// The gathered id space.
  ///
  interval_index_space_handle _gathered_id_space;

private:

  //@}


  // ===========================================================
  /// @name STANDARD IDS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make end() the standard id end.
  ///
  void update_standard_ids();

  ///
  /// True if and only if there are only standard ids.
  ///
  bool has_only_standard_ids() const;

  ///
  /// Deallocate all non-standard ids.
  ///
  void clear_ids();

protected:

  ///
  /// The end id of the standard ids.
  ///
  pod_type _standard_id_end;

private:

  //@}


  // ===========================================================
  /// @name SUM INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if hub id xhub_id is the
  /// representative member of its equivalence class.
  ///
  virtual bool contains_rep(pod_type xhub_id) const;

  ///
  /// The representative member of the equivalence class of hub id xhub_id.
  ///
  virtual pod_type rep(pod_type xhub_id) const;

  ///
  /// The host id associated with the representative member 
  /// of the equivalence class of hub id xhub_id.
  ///
  virtual pod_type host_rep(pod_type xhub_id) const;

  ///
  /// Beginning index of the terms in this sum.
  ///
  virtual pod_type term_id_begin() const;

  ///
  /// Ending index of the terms in this sum.
  ///
  virtual pod_type term_id_end() const;

  ///
  /// True if this map contains the xi-th term.
  ///
  virtual bool contains_term_id(pod_type xi) const;

  ///
  /// Deletes all entries.
  ///
  virtual void clear();

protected:

  ///
  /// The type of rem map.
  ///
  typedef hash_map<pod_type, pod_type> rem_type;

  ///
  /// The reflexive reduction of the rem map.
  ///
  rem_type _rem;

  ///
  /// Beginning index of the terms in this sum.
  ///
  pod_type _term_id_begin;

  ///
  /// Ending index of the terms in this sum.
  ///
  pod_type _term_id_end;

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
  virtual primary_sum_index_space_state& operator=(const explicit_index_space_state& xother);

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
  /// True if this space contains an id equivalent to xid in the glued hub id space.
  ///
  virtual bool contains_glued_hub(pod_type xid) const;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

  ///
  /// The pod index in the glued primary sum id space equivalent to xid in this id space.
  ///
  virtual pod_type glued_hub_pod(pod_type xid) const;

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
  static list_pool<hub_index_space_handle>& handles();

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
  /// The iterator pool.
  ///
  static list_pool<hub_index_space_iterator>& iterators();

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
  virtual primary_sum_index_space_state* clone() const;

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
/// The deep size of primary_sum_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const primary_sum_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef PRIMARY_SUM_INDEX_SPACE_STATE_H
