// $RCSfile: sum_index_space_handle.h,v $ $Revision: 1.3 $ $Date: 2013/01/15 22:23:45 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class sum_index_space_handle

#ifndef SUM_INDEX_SPACE_HANDLE_H
#define SUM_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "explicit_index_space_handle.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

namespace sheaf
{

class sum_index_space_state;
  
///
/// An implemenation of class explicit_index_space_handle that has
/// a sum id space state.
///
class SHEAF_DLL_SPEC sum_index_space_handle : public explicit_index_space_handle
{

  // ===========================================================
  /// @name SUM_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  sum_index_space_handle();

  ///
  /// Copy constructor
  ///
  sum_index_space_handle(const sum_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  sum_index_space_handle(const index_space_family& xid_spaces,
			 pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  sum_index_space_handle(const index_space_family& xid_spaces,
			 const string& xname);

  ///
  /// Assignment operator.
  ///
  sum_index_space_handle& operator=(const sum_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~sum_index_space_handle();

protected:

  using explicit_index_space_handle::state;

  ///
  /// The sum id space state (mutable version).
  ///
  sum_index_space_state& state();

  ///
  /// The sum id space state (const version).
  ///
  const sum_index_space_state& state() const;

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
  bool contains_rep(pod_type xhub_id) const;

  ///
  /// True if and only if hub id xhub_id is the
  /// only member of its equivalence class.
  ///
  bool contains_unique_rep(pod_type xhub_id) const;

  ///
  /// The representative member of the equivalence class of hub id xhub_id.
  ///
  pod_type rep(pod_type xhub_id) const;

  ///
  /// The host id associated with the representative member 
  /// of the equivalence class of hub id xhub_id.
  ///
  pod_type host_rep(pod_type xhub_id) const;

  ///
  /// Beginning index of the terms in this sum.
  ///
  pod_type term_id_begin() const;

  ///
  /// Ending index of the terms in this sum.
  ///
  pod_type term_id_end() const;

  ///
  /// True if this map contains the xi-th term.
  ///
  bool contains_term_id(pod_type xi) const;

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
  void clear();

protected:

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual sum_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using explicit_index_space_handle::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const;

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
 
} // end namespace sheaf

#endif // ifndef SUM_INDEX_SPACE_HANDLE_H
