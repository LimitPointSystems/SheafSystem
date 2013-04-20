

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class sum_index_space_state

#ifndef SUM_INDEX_SPACE_STATE_H
#define SUM_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_STATE_H
#include "explicit_index_space_state.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif
 
#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

namespace sheaf
{

class sum_index_space_state;
  
///
/// An abstract id space of alternate integer identifiers which is the
/// sum (disjoint union) of two or more id spaces.
///
/// Every sum_index_space_state defines an equivalence relation on the
/// sum id space. An equivalence relation R on a set S partitions S into
/// a set of equivalence classes called the quotient of S by R and denoted
/// S/R. There are 3 useful maps associated with the equivalence relation:
///
///    1) the modulo or projection function: S -> S/R which associates
///       each member of S with it's equivalence class;
///    2) the rep function: S/R -> Q subset of S which associates each 
///       equivalence class with a representative member;
///    3) the rem function: S -> Q which associates each member of S with
///       the representative of its equivalence class.
///
/// The rem function and it's inverse are particularly useful for
/// representing the equivalence relation.
/// 
/// Representations of sum_index_space_state differentiate on the
/// interpretation and implementation of the equivalence relation. Class
/// primary_sum_index_space_state has a mutable equivalence relation which
/// is interpreted as defining the hub id space as the quotient space of the
/// primary sum id space by the equivalence relation. That is, the equivalence
/// relation is interpreted as gluing members of the terms together to form
/// the hub id space.
/// 
/// Class glued_sum_index_space_state interprets the hub id space as given
/// and has an immutable equivalence relation derived from the term id spaces.
///
class SHEAF_DLL_SPEC sum_index_space_state : public explicit_index_space_state
{

  friend SHEAF_DLL_SPEC size_t deep_size(const sum_index_space_state& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name SUM_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor
  ///
  sum_index_space_state();

  ///
  /// Copy constructor; disabled
  ///
  sum_index_space_state(const sum_index_space_state& xother) { };

  ///
  /// Constructor: Creates an instance from arguments, xargs.
  ///
  sum_index_space_state(const arg_list& xargs);

  ///
  /// Destructor
  ///
  virtual ~sum_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name SUM INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type used to represent an equivalence class.
  ///
  typedef list<pod_type> equivalence_class_type;

  ///
  /// The equivalence class associated with the hub id xhub_id.
  ///
  void equivalence_class(pod_type xhub_id, equivalence_class_type& result) const;

  ///
  /// The number of members of the equivalence class of hub id xhub_id.
  ///
  size_type equivalence_ct(pod_type xhub_id) const;

  ///
  /// True if and only if hub id xhub_id is the
  /// representative member of its equivalence class.
  ///
  virtual bool contains_rep(pod_type xhub_id) const = 0;

  ///
  /// True if and only if hub id xhub_id is the
  /// only member of its equivalence class.
  ///
  bool contains_unique_rep(pod_type xhub_id) const;

  ///
  /// The representative member of the equivalence class of hub id xhub_id.
  ///
  virtual pod_type rep(pod_type xhub_id) const = 0;

  ///
  /// The host id associated with the representative member 
  /// of the equivalence class of hub id xhub_id.
  ///
  virtual pod_type host_rep(pod_type xhub_id) const = 0;

  ///
  /// Beginning index of the terms in this sum.
  ///
  virtual pod_type term_id_begin() const = 0;

  ///
  /// Ending index of the terms in this sum.
  ///
  virtual pod_type term_id_end() const = 0;

  ///
  /// True if this map contains the xi-th term.
  ///
  virtual bool contains_term_id(pod_type xi) const = 0;

  ///
  /// The xi-th term.
  ///
  const index_space_handle& term(pod_type xi) const;

  ///
  /// The term containing id xid.
  ///
  const index_space_handle& term_of(pod_type xid) const;

  ///
  /// The term contains id xid.
  ///
  const index_space_handle& term_of(const scoped_index& xid) const;

  ///
  /// The last term.
  ///
  const index_space_handle& last_term() const;

  ///
  /// Beginning id of the xi-th term.
  ///
  pod_type term_begin(pod_type xi) const;

  ///
  /// Ending id of the xi-th term.
  ///
  pod_type term_end(pod_type xi) const;

  ///
  /// Beginning hub id of the xi-th term.
  ///
  pod_type term_hub_begin(pod_type xi) const;

  ///
  /// Ending hub id of the xi-th term.
  ///
  pod_type term_hub_end(pod_type xi) const;

  ///
  /// The id of the term containing id xid.
  ///
  pod_type term_id(pod_type xid) const;

  ///
  /// Converts simple index xindex to its binary components xterm_id and xlocal_id.
  ///
  void binary(pod_type xindex, pod_type& xterm_id, pod_type& xlocal) const;
  
  ///
  /// Converts binary components xterm_id, xlocal_id to simple index xindex.
  ///
  void simple(pod_type xterm_id, pod_type xlocal_id, pod_type& xindex) const;

  ///
  /// Deletes all entries.
  ///
  virtual void clear();

protected:

  ///
  /// The type of the inverse of the rem map.
  ///
  typedef hash_multimap<pod_type, pod_type> rem_inv_type;

  ///
  /// The inverse rem map.
  ///
  rem_inv_type _rem_inv;

  ///
  /// The type of the terms block initialization policy.
  ///
  typedef zero_block_initialization_policy<index_space_handle*> terms_init_type;

  ///
  /// The type of the terms block.
  ///
  typedef auto_block<index_space_handle*, terms_init_type> terms_type;

  ///
  /// The terms of this sum.
  ///
  terms_type _terms;

  ///
  /// The beginning of the interval in the sum id space for each term.
  ///
  block<pod_type> _term_begin;

  ///
  /// The end of the interval in the sum id space for each term.
  ///
  block<pod_type> _term_end;

  ///
  /// The type of sum_to_term_map.
  ///
  typedef map<pod_type, pod_type> sum_to_term_type;
  
  ///
  /// The term id corresponding to each sum id.
  ///
  sum_to_term_type _sum_to_term_map;

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
  virtual sum_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

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
  virtual bool is_ancestor_of(const any* other) const;

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
/// The deep size of sum_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const sum_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef SUM_INDEX_SPACE_STATE_H
